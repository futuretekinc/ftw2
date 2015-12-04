#include "gsn_types.h"
#include "gsn_includes.h"
#include "gsn_error.h"
#include "app_defines_builder.h"
#include "main/app_main_ctx.h"
#include "hal/s2w_hal_specific.h"
#include "hal/s2w.h"
#include "parser/s2w_process.h"
#include "hal/s2w_types.h"
#include "hal/s2w_hal.h"
#include "app_rtc_mem.h"
#include "config/app_resource_config.h"
#include "fs/api/api_safe.h"
#include "fs/safe-flash/nor/flashdrv.h"
#include "main/gsn_br_flashldr.h"
#include "ftw_config.h"
#include "web_prov\s2w_web_prov.h"
#include "app_rtc_mem.h"
#include "hal/s2w_net.h"
#include "modules/pwr_mgmt/gsn_pwr_mgmt.h"
#include "ext_app/app_ext_flash.h"
#include "parser/s2w_command.h"
#include "ftw_serial.h"
#include "ftw_uart.h"

PRIVATE VOID
AppS2wHal_SerialInputTask( UINT32 address );

extern UINT8 s2wSerialInputTaskStack[APP_CFG_SERIALINPUT_STACK_SIZE];

/* Semaphore to protect against concurrent UART write and putchar calls
*/

extern FTW_SERIAL_PORT_HANDLE_T  s2wSerialPortHandle;

extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;
extern FTW_PROFILE_PARAMS_T profile_params;

void    FTW_SERIAL_init(void)
{
    FTW_UART_CONFIG xConfig;

    FTW_UART_getConfig(FTW_UART0, &xConfig);

    if (FTW_UART_open(FTW_UART0, &xConfig) != FTW_RET_OK)
    {/*ERROR: UART port open failed */
        FTW_ASSERT(0);
    }
    
    //AppS2wHal_PrintBanner();
    
    GsnOsal_ThreadCreate(AppS2wHal_SerialInputTask,s2wappMainTaskCtxt,
                         &s2wappMainTaskCtxt->s2wSerialTask,
                         "S2wSerialInputTask",
                         APP_CFG_SERIALINPUT_THREAD_PRIORITY,
                         s2wSerialInputTaskStack,
                         sizeof(s2wSerialInputTaskStack),
                         GSN_OSAL_THREAD_INITIAL_READY);
}

/*****************************************************************************
*  Public Functions
*****************************************************************************/



VOID FTW_SERIAL_putc(FTW_SERIAL_ID xID, UINT8 ch)
{
    FTW_UART_putc(FTW_UART0, ch);
}

VOID FTW_SERIAL_put(FTW_SERIAL_ID xID, const void *buf, UINT32 len)
{
    FTW_UART_put(FTW_UART0, buf, len);
}


VOID FTW_SERIAL_get(FTW_SERIAL_ID xID, UINT8*buf, UINT32 len)
{
    FTW_UART_get(FTW_UART0, buf, len);
}


UINT8 FTW_SERIAL_getc(FTW_SERIAL_ID xID, UINT8*buf)
{
    return  FTW_UART_getc(FTW_UART0, buf);
}

/**
******************************************************************
* @ingroup S2w-Application
* @brief S2w Entry function for the Serial2WiFi thread.
*   This function Initializes the UART and calls
*   the Serial2WiFi core startup functions.
* @param address - IN the address information
* @retval UV_VALUE.
******************************************************************/
VOID
AppS2w_PersistantTmrCfg();

PRIVATE VOID
AppS2wHal_SerialInputTask( UINT32 address )
{
    while (1)
    {
        AppS2wProcess_SerialInput();
    }
}

#if 0
/**
 ************************************************************************
 * @ingroup S2w-Application.
 * @brief Process the serial data from the host.
 *    This function continuously polls the serial port, classifies the incoming
 *    characters into Serial2WiFi data and command based on the serial data
 *    encoding.
 *    This function should be called from serial input-output handler thread each
 *    time when a character arrives on serial interface.
 ************************************************************************/
static VOID     S2w_RawLenCharProcess(UINT8 ch);
static UINT32   S2w_RawLenCalculate();

static UINT8 hCid=INVALID_CID;
UINT8 lengthConvertIndex = 0;
UINT16 lengthSpecialCmd = 0;

/** Buffer for data to be transmitted */
#ifdef IP2WIFI
__no_init PRIVATE UINT8 dataBuffer[FTW_DATABUF_SIZE];
#else
__no_init PRIVATE UINT8 dataBuffer[FTW_DATABUF_SIZE-200];
#endif

/** Index into dataBuffer to indicate used amount */
PRIVATE UINT32 dataIndex=0;

/** Buffer for raw data len */
__no_init PRIVATE UINT8 rawLenBuff[20];
PRIVATE UINT32 rawLenIndex=0;
PRIVATE UINT32 rawLen=0;
#ifdef FTW_IP2WIFI_SUPPORT
PRIVATE UINT32 rawTotalIndex=0;
PRIVATE UINT32 rawColon =0;
#endif

PUBLIC VOID
AppS2wProcess_SerialInput(VOID)
{
	static char esc[4] = { '+', '+', '+', '+' };
    static UINT8 ipnum;
    static char atoibuf[6];
    static UINT8 digits;
    UINT8 status;
    static UINT8 prev = 0;
    static UINT8 prevprev = 0;
    UINT8 ch,softFlow;
  
	UINT8 respTimeOut=0;
    UINT32 elementType;
    
    while (FTW_SERIAL_getc(FTW_SERIAL_0, &ch) == 1)
    {


        if ((s2wCurrent.serialPortConf.commonConf.echo) && (s2wState == FTW_STATE_CMD))
        {
            if (ch != FTW_ESC)
            {
                GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                FTW_SERIAL_putc(FTW_SERIAL_0, ch);
                GsnOsal_SemRelease(&s2wSyncSemID);
            }
        }
        // switch to differnt state depends on the previous byte
        switch (s2wState)
        {
            /* special command comes with the length */

            case FTW_STATE_BULK_DATA:
                /* we must read 4 byte ascii lenth
                and then convert it to binary value */
            {
                //UINT8 *dataBufferPointer;
                lengthConvertIndex++;
                /* next after cid  char 2 to 5 */
                lengthSpecialCmd *= 10;
                lengthSpecialCmd += (ch - '0'); /* assuming number will come*/
                if(lengthConvertIndex == 4)
                {
                    FTW_SERIAL_get(FTW_SERIAL_0, dataBuffer, lengthSpecialCmd);
                    dataIndex = lengthSpecialCmd;

                    AppS2w_DataTransmit(dataBuffer);
                    s2wState =  FTW_STATE_CMD;
                }
            }
            break;
            case FTW_STATE_DATA_AUTO:
            {
                if (ch == '+' && auto_esc < 3 && 
					(s2wCurrent.autoExitTimeout))
		        {
		             auto_esc++;
		             AppS2wHal_TimerStop(&nagleTimer);

		             AppS2wHal_TimerStart(&auto_esc_timer,
		               s2wCurrent.autoExitTimeout);

		        }
		        else if (auto_esc && s2wCurrent.autoExitTimeout)
		        {
		             UINT8   i;
		             AppS2wHal_TimerStop(&auto_esc_timer);

		             esc[auto_esc] = ch;
		             i = 0;
		             AppS2wHal_TimerStart(&nagleTimer,
		                    s2wCurrent.registers[FTW_REG_NAGLE_WAIT_TIME]);
		             while (i <= auto_esc)
		             {
		                 AppS2w_DataCharProcess(esc[i++]);
		             }

		             esc[auto_esc] = '+';
		             auto_esc = 0;
		        }
		        else
			    {
		             auto_esc = 0;
		             AppS2w_DataCharProcess(ch);

		        }

			}
			break;
            case FTW_STATE_CMD:
                if (ch == FTW_ESC)
                {
                    s2wState = FTW_STATE_CMD_ESC;
                    continue;
                }
                AppS2w_CommandCharProcess(ch);
            break;

            case FTW_STATE_CMD_ESC:
                if (ch == 'S' || ch == 'u' || ch == 'U')
                {
                    s2wState = FTW_STATE_CID;
                }
#if defined(FTW_GSLINK) && defined(FTW_GSLINK_XML)
                else if(((ch == 'G')  || (ch == 'g'))&& s2wappMainTaskCtxt->xmlParseEn == 1 )
                {
                    rawLen=0;
                    rawLenIndex=0;
                    s2wState = FTW_STATE_GET_CID;
#ifdef FTW_WEB_SERVER			
					if(s2wappMainTaskCtxt->respTimeOut !=0 && s2wappMainTaskCtxt->responseInprogress == 1)
					{
						 if (GSN_SUCCESS != GsnSoftTmr_Stop(s2wappMainTaskCtxt->respTimeOutTmrHndl))
							 respTimeOut = 1;					
					}	
					s2wappMainTaskCtxt->responseInprogress = 0;
 #endif			
                }
#endif
                else if((ch == 'Z') || (ch == 'Y'))
                {
                    s2wState = FTW_STATE_CID;
                    lengthSpecialCmd = 0;
                    lengthConvertIndex = 0;
                }
#ifdef FTW_IP2WIFI_SUPPORT
                else if (ch == 'R' || ch == 'r')
                {
                    {
						rawLen=0;
                        rawLenIndex=0;
                        s2wState = FTW_STATE_RAW;
                    }
                }
#endif
                else if ((ch == 'c')|| (ch == 'C'))
                {
#ifndef FTW_IP2WIFI_SUPPORT
#ifdef FTW_PING_TRACE
                    if(s2wPingStarted)
                    {
                        AppS2wHal_PingClose();
                    }
                    if(s2wTrcStarted)
                    {
                      //  AppS2wHal_TraceRouteClose();
                      //  s2wTrcStarted = 0;
                    }
#endif
#endif
                    s2wState = FTW_STATE_CMD;
                }
                else if ((ch == 'w')|| (ch == 'W'))
		        {
		             s2wState = FTW_STATE_CERT;
		             status = AppS2wCertificateData(ch);
		             // flush the data for spi-dma interface
					 if(s2wappMainTaskCtxt->serialDeviceId == FTW_PORT_FS_SPI)
					 {
					     FTW_SPI_flush(FTW_SPI_ALL);
                     }
		                if((status == FTW_SUCCESS) || (status == FTW_FAILURE))
		                    s2wState = FTW_STATE_CMD;
		        }
#ifdef FTW_EXTFLASH_DRIVER_TEST
				else if ((ch == 'v')|| (ch == 'V'))
		        {
		             s2wState = FTW_STATE_EXTFLASH;
		             status = AppS2wExternalFlashData(ch);
		                if((status == FTW_SUCCESS) || (status == FTW_FAILURE))
		                    s2wState = FTW_STATE_CMD;
		        }
#endif
#ifdef FTW_EXT_FLASH_FS_SUPPORT
				else if((ch == 'f') || (ch == 'F'))
				{
					s2wState = FTW_STATE_FWRITE; 
					status = AppS2wHal_FileWriteDataGet(s2wappMainTaskCtxt->appExtFsCtx.fileInfo.fd, s2wappMainTaskCtxt->appExtFsCtx.fileInfo.size);
					if((status == FTW_SUCCESS) || (status == FTW_FAILURE))
					s2wState = FTW_STATE_CMD;
				}
#endif

		        else if ((ch == 'H')|| (ch == 'h'))
	            {
	                s2wState = FTW_STATE_HTTP_CONTENT_CID;
#if defined(FTW_WEB_SERVER) && defined(FTW_GSLINK_RAW)				
					if(s2wappMainTaskCtxt->respTimeOut !=0 && s2wappMainTaskCtxt->responseInprogress == 1)
					{
						 if (GSN_SUCCESS != GsnSoftTmr_Stop(s2wappMainTaskCtxt->respTimeOutTmrHndl))
							 respTimeOut = 1;					
					}
					s2wappMainTaskCtxt->responseInprogress = 0;
#endif			
		        }
		        else if ((ch == 'P')|| (ch == 'p'))
	            {
	                s2wState = FTW_STATE_COAP_CONTENT_CID;
	            }
#ifdef FTW_UNASSOC_TXRX_SUPPORT
                else if ((((ch == 'D')|| (ch == 'd')) && (s2wLinkState == FTW_LINK_STATE_DISCONNECTED)))
                {
                    s2wState = FTW_STATE_UNSOLICITED_DATA;
                    dataIndex = 0;
                }
#endif
                else
                {
                    s2wState = FTW_STATE_CMD;
                    AppS2w_CommandCharProcess(FTW_ESC);
                    AppS2w_CommandCharProcess(ch);
            }
            break;
#ifdef FTW_UNASSOC_TXRX_SUPPORT
            case FTW_STATE_UNSOLICITED_DATA:
                    dataBuffer[0]= ch;
                    if(s2wappMainTaskCtxt->frame.macFrameLen)
                    {
                        FTW_SERIAL_get(FTW_SERIAL_0, &dataBuffer[1], s2wappMainTaskCtxt->frame.macFrameLen-1);
                        dataIndex = s2wappMainTaskCtxt->frame.macFrameLen;
                        // first start the mode

						GSN_WDD_UAM_START_RESP_T resp;
                        status= GsnWdd_UAMStart(&(s2wappMainTaskCtxt->if0.wddCtx), 0, &resp);
                        if(status != GSN_SUCCESS)
                        {
							AppS2wProcess_StatusNotify(status, 0);
						}
						// configure the rx if it is requetsed
						if(s2wappMainTaskCtxt->frame.rxWaitTime)
						{
							s2wUamRx_Init();
							// first configure the rx
							status= GsnWdd_UAMDataRxConfig(&(s2wappMainTaskCtxt->if0.wddCtx), &s2wappMainTaskCtxt->RxParam);

                            // register the callback
                            GsnWdd_DataIndCbReg(&(s2wappMainTaskCtxt->if0.wddCtx), FTW_UnassocDataIndCB, s2wappMainTaskCtxt);
						}
						{

						    GSN_WDD_UAM_CCA_SET_RESP_T respCCa;
						    GsnWdd_UamCcaConfigSet(&(s2wappMainTaskCtxt->if0.wddCtx),0,s2wappMainTaskCtxt->ccaThr,
                                             (UINT16)s2wappMainTaskCtxt->ccaTimeout,&respCCa);
						}
						GSN_WIF_WLAN_UNASSOCIATED_DATACFM_T wStatus;
                        GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                        status = GsnWdd_UamDataSend_Patch(&(s2wappMainTaskCtxt->if0.wddCtx),&s2wappMainTaskCtxt->frame,
                                           dataBuffer, dataIndex,&wStatus);
                        // if the option enabled then send back the time stamp

                        if((wStatus.status) && (s2wappMainTaskCtxt->uamTimeStampReturn))
                        {
							S2w_Printf("\r\nTS:%x",wStatus.timeStamp);
						}
                        AppS2wProcess_StatusNotify(!wStatus.status, 0);
                        GsnOsal_SemRelease(&s2wSyncSemID);
                        // wait for the rx to complete the stop the mode
                        if(s2wappMainTaskCtxt->frame.rxWaitTime)
						{
							GsnTaskSleep(s2wappMainTaskCtxt->frame.rxWaitTime);
						}
                        // stop the mode
                        GSN_WDD_UAM_STOP_RESP_T resp1;
                        GsnWdd_UAMStop(&(s2wappMainTaskCtxt->if0.wddCtx), 0, &resp1);

					}
					s2wState = FTW_STATE_CMD;
            break;
#endif
            case FTW_STATE_DATA:
                if (ch == FTW_ESC)
                {
                    s2wState = FTW_STATE_DATA_ESC;
                    continue;
                }
                AppS2w_DataCharProcess(ch);
            break;

            case FTW_STATE_DATA_ESC:
                if(APP_FTW_GET_SERIAL_DEVICE_ID())
                {//Note: Is it not applicable for SPI interface - since we already apply stuffing  at lower layer
                    softFlow = 0x00;
                }
                else
                {
                    softFlow = s2wCurrent.serialPortConf.conf.uart.softflow;
                }
                if (ch == FTW_ESC)
                {
                    AppS2w_DataCharProcess(ch);
                    s2wState = FTW_STATE_DATA;
                }
                else if (ch == 'E' || ch == 'S' || ch == 'u' || ch == 'U')
                {
                    status = AppS2w_DataBufferTransmit();
                    GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                    AppS2wProcess_StatusNotify(status, 0);
                    GsnOsal_SemRelease(&s2wSyncSemID);
                    curCid = INVALID_CID;
                    s2wState = ch == 'E' ? FTW_STATE_CMD : FTW_STATE_CID;
                }
                else if (ch == 'C')
                {
                    status = AppS2w_DataBufferTransmit();
                    GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                    AppS2wProcess_StatusNotify(status, 0);
                    GsnOsal_SemRelease(&s2wSyncSemID);
                    AppS2wHal_NetClose(curCid);
                    s2wState = FTW_STATE_CMD;
                }
                else if ((ch == 'Q' || ch == 'T')
                          && (softFlow))
                {
                    AppS2w_DataCharProcess(ch == 'Q' ? FTW_XON : FTW_XOFF);
                    s2wState = FTW_STATE_DATA;
                }
                else
                {
                    s2wState = FTW_STATE_DATA;
                }
            break;

            case FTW_STATE_CID:
                curCid = AppS2w_CidValidate(ch);
                if (curCid == INVALID_CID)
                {
                    AppS2w_FailEscParse();
                }
                else
                {
                    digits = 0;
                    ipnum = 0;
#if  defined(FTW_FS_SPI_HI_ENABLE) || defined(FTW_SDIO_ENABLE)
#else

                    GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                    AppS2wProcess_StatusNotify(FTW_SUCCESS, 0);
                    GsnOsal_SemRelease(&s2wSyncSemID);
#endif
                    if (prev == 'S')
                        s2wState = FTW_STATE_DATA;
                    else if (prev == 'u')
                        s2wState = FTW_STATE_IPPORT;
                    else if (prev == 'U')
                        s2wState = FTW_STATE_IP_STRING;
                    else if (prev == 'Z')
                        s2wState = FTW_STATE_BULK_DATA;
                    else if(prev == 'Y')
                    {
                        prevprev = prev;
                        s2wState = FTW_STATE_IP_STRING;
                    }
                }
            break;

            case FTW_STATE_IPPORT:
                if (ipnum < 4)
                {
                    destAddr[ipnum] = ch;
                }
                else if (ipnum == 4)
                {
                    destPort = (UINT16) ch << 8;
                }
                else if (ipnum == 5)
                {
                    destPort |= ch;
                    s2wState = FTW_STATE_DATA;
                }
                ipnum++;
            break;

            case FTW_STATE_IP_STRING:
                if (digits < 3 && isdigit(ch))
                {
                    atoibuf[digits] = ch;
                    digits++;
                }
                else if (digits
                     && ((ipnum < 3 && ch == '.')
                     || (ipnum == 3 && ch == ':')))
                {
                    long temp;
                    atoibuf[digits] = '\0';
                    temp = atol(atoibuf);
                    if (temp < 0 || temp > 255)
                    {
                        AppS2w_FailEscParse();
                        continue;
                    }
                    destAddr[ipnum] = temp;
                    digits = 0;
                    ipnum++;
                    if (ipnum == 4)
                    {
                        ipnum = 0;
                        s2wState = FTW_STATE_PORT_STRING;
                    }
                }
                else
                {
                    AppS2w_FailEscParse();
                }
            break;

            case FTW_STATE_PORT_STRING:
                if (digits < 5 && isdigit(ch))
                {
                    atoibuf[digits] = ch;
                    digits++;
                }
                else if (digits && ch == ':')
                {
                    long    temp;
                    atoibuf[digits] = '\0';
                    temp = atol(atoibuf);
                    if (temp < 0 || temp > 65535)
                    {
                        AppS2w_FailEscParse();
                        continue;
                    }
                    destPort = temp;
                    if(prevprev == 'Y')
                    {
                        s2wState = FTW_STATE_BULK_DATA;
                        prevprev = 0;
                    }
                    else
                    {
                        s2wState = FTW_STATE_DATA;
                    }
                }
                else
                {
                     AppS2w_FailEscParse();
                }
            break;
          
            case FTW_STATE_HTTP_CONTENT_CID:
            {
                hCid = AppS2w_CidValidate(ch);
                if(( hCid != INVALID_CID )/* && ( AppS2w_ConnHttpStateGet(hCid) == 1)*/)
                {
                    UINT8 status=FTW_FAILURE;
#if defined (FTW_HTTPS_SUPPORT) || (FTW_HTTPC_SUPPORT)			
                  if((httpConfInfo.reqMethod == GSN_HTTP_METHOD_POST) || (httpConfInfo.reqMethod == GSN_HTTP_METHOD_PUT))
                  {
                      status = FTW_NET_HTTPD_contentDataGet(httpConfInfo.reqBodyTotalLen, hCid);
                  }
#endif
#if defined(FTW_GSLINK) &&  defined(FTW_GSLINK_RAW) && defined(FTW_WEB_SERVER)
				  if((s2wCidList[(hCid)].httpdCtx.method == GSN_HTTP_METHOD_GETRESP) ||  \
					 (s2wCidList[(hCid)].httpdCtx.method == GSN_HTTP_METHOD_POSTRESP))
                  {
					  if(respTimeOut == 0 )
					 	 status = FTW_NET_HTTPD_rawContentGet(s2wCidList[hCid].httpdCtx.reqBodyLen, hCid); 	  
                  }                                                           
#endif
                  s2wState = FTW_STATE_CMD;
				  	GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
                  AppS2wProcess_StatusNotify(status, 0);
				  	GsnOsal_SemRelease(&s2wSyncSemID);
             }
             else
             {
                 AppS2w_CommandCharProcess(ch);
                 s2wState = FTW_STATE_CMD;
             }
        }
        break;
            case FTW_STATE_COAP_CONTENT_CID:

            	hCid = AppS2w_CidValidate(ch);
                if( hCid != INVALID_CID )
                {
                	UINT8 status=FTW_FAILURE;

                	GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
				#ifdef FTW_COAP_SUPPORT
                	status = AppS2wHal_CoapContentDataGet( hCid);
				#endif
                	GsnOsal_SemRelease(&s2wSyncSemID);
                    s2wState = FTW_STATE_CMD;
                    AppS2wProcess_StatusNotify(status, 0);
                }
                else
                {
                    AppS2w_CommandCharProcess(ch);
                    s2wState = FTW_STATE_CMD;
                }
            break;

#if defined(FTW_GSLINK) && defined(FTW_GSLINK_XML)  
		 case FTW_STATE_GET_CID:   
			curCid = AppS2w_CidValidate(ch);
        	if (curCid == INVALID_CID)
   	    	{
           		 AppS2w_FailEscParse();
       		}
			else				
				s2wState =  FTW_STATE_XML_LEN;		
				elementType=1;

			break;
		 case FTW_STATE_XML_LEN :	/* XML data  length*/
	 		S2w_RawLenCharProcess(ch);
 			if(rawLenIndex == 4 )
			{
				rawLen = S2w_RawLenCalculate();
				rawLenIndex = 0;
				if(rawLen ==	FTW_XML_ATTRIBUTE_ID || rawLen == FTW_XML_COMPLEX_TAG_START_ID )
				{
					elementType=rawLen;					
					break;
				}
				else if(rawLen == 0 || rawLen == FTW_XML_COMPLEX_TAG_END_ID)										
					elementType=rawLen;
#ifdef FTW_HTTP_CUSTOM_SUPPORT
                else if((FTW_HTTP_RESPONSE_LINE == rawLen) || (FTW_HTTP_HEADER == rawLen))
                {
                    elementType = rawLen;
                    break;
                }
#endif
				else			
					/* Start receiving the tags*/
					FTW_SERIAL_get(FTW_SERIAL_0, dataBuffer, rawLen);
#ifdef FTW_WEB_SERVER					
                if(respTimeOut == 0 )
                {
#endif
#ifdef FTW_HTTP_CUSTOM_SUPPORT
                    if((FTW_HTTP_RESPONSE_LINE == elementType) || (FTW_HTTP_HEADER == elementType))
                    {
                        AppS2w_HttpDataProcess(curCid, dataBuffer, rawLen, elementType);
                    }
                    else
#endif
					{	
                        AppS2w_XmlDataProcess(curCid,dataBuffer,rawLen,elementType);
					}
#ifdef FTW_WEB_SERVER
                }
                respTimeOut =0;
#endif				
#if 0
					rawTotalIndex = 0;			   
#endif
					s2wState = FTW_STATE_CMD;
					rawLen =0;				
					rawLenIndex=0;
				}
				//else
					//s2wState = FTW_STATE_CMD;	

			break; 
#endif		
#ifdef FTW_IP2WIFI_SUPPORT
        case FTW_STATE_RAW:

            if(ch == FTW_COLON)
					{
                if(rawColon == 0)
						{
                   rawColon = 1;
							}
                else
							{
                   rawLen = S2w_RawLenCalculate();
                   if(rawLen > 1560)
							{
                       S2w_Printf("\r\nERROR:INVALID LENGTH\r\n");
							s2wState = FTW_STATE_CMD;
						}
						else
						{
  			           FTW_SERIAL_get(FTW_SERIAL_0, dataBuffer, rawLen);
		  		       dataIndex=rawLen;
		  		       S2w_RawDataBufferTransmit();
							s2wState = FTW_STATE_CMD;
	                   rawTotalIndex = 0;
	                   rawLen = 0;
					}
                   rawColon = 0;
					}
				 }
            else
            {
                S2w_RawLenCharProcess(ch);

				 }
				 break;
#endif
        }
        prev = ch;
    }
}

PRIVATE VOID S2w_RawLenCharProcess(UINT8 ch)
{

    rawLenBuff[rawLenIndex] = ch;
    rawLenIndex++;

}

PRIVATE UINT32 S2w_RawLenCalculate()
{
    UINT32 len = 0;

    rawLenBuff[rawLenIndex] = '\0';
    /* parse the ascii to get the len as integer */
    AppS2wParse_Int(rawLenBuff,&len);
    rawLenIndex = 0;
    return len;
}
#endif