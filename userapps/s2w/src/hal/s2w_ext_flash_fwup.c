/*****************************************************************
*
*               COPYRIGHT (c) 2009-2010 GainSpan Corporation
*                         All Rights Reserved
*
* The source code contained or described herein and all documents
* related to the source code ("Material") are owned by GainSpan
* Corporation or its licensors.  Title to the Material remains
* with GainSpan Corporation or its suppliers and licensors.
*
* The Material is protected by worldwide copyright and trade secret
* laws and treaty provisions. No part of the Material may be used,
* copied, reproduced, modified, published, uploaded, posted, transmitted,
* distributed, or disclosed in any way except in accordance with the
* applicable license agreement.
*
* No license under any patent, copyright, trade secret or other
* intellectual property right is granted to or conferred upon you by
* disclosure or delivery of the Materials, either expressly, by
* implication, inducement, estoppel, except in accordance with the
* applicable license agreement.
*
* Unless otherwise agreed by GainSpan in writing, you may not remove or
* alter this notice or any other notice embedded in Materials by GainSpan
* or GainSpan's suppliers or licensors in any way.
*
* $RCSfile: s2w_ext_flash_fwup.c,v $
*
*******************************************************************
*
* Description : This file contains the source code for the reference
*                   application on the TLS board.
*
*               The reference application collects data for
*               - Light Sensor (APDS-9005)
*               - Temperature sensor (Thermistor DO-35)
*               - Battery charge
*               - Signal strength of the last received data packet
*
*               It then packs all this raw data as per GainSpan Data Packet
*               format in a single UDP or TCP packet and sends it to the data
*               server. The translation of the raw data to the actual values is
*               done on the data server
*
******************************************************************************/

/********************************* File inclusion ****************************/
#if 1//def GSN_EXTERNAL_FLASH_FWUP

#include "gsn_includes.h"
#include "app_defines.h"
#include "app_events.h"
#include "hal/s2w_types.h"
#include "hal/s2w_hal.h"
#include "parser/s2w_process.h"
#include "hal/s2w_net.h"
#include "parser/s2w_command.h"
#include "hal/s2w.h"


#include "main/app_main_ctx.h"
#include "modules/ssl/gsn_ssl.h"
#include "modules/http/gsn_httpc.h"
#include "main/gsn_br_flashldr.h"
#include "modules/fwup/gsn_fwup.h"

#include "core/reg/gsn_reg_rtc_spec.h"
#include "core/reg/gsn_reg_rtc_op.h"
#include "ext_app/app_ext_flash.h"

#ifdef ADK_OTAFU
#include "gsn_otafu.h"
#include "gsn_ext_otafu.h"
#include "gsn_otafu_dsv.h"

#include "hal/s2w_cert_mgmt.h"
#if 0
#include "supplicant/crypto/crypto.h"
#include "supplicant/tls/tlsv1_client.h"

#include "supplicant/tls/tlsv1_common.h"
#include "supplicant/tls/tlsv1_record.h"

#include "supplicant/tls/tlsv1_client_i.h"
#include "supplicant/tls/x509v3.h"
#endif

//#include "tls/rsa.h"
#endif

//#include "s2w_ota_fwup_xml_schema.c"

/*****************************************************************************/

/************************ Private MACRO **************************************/



/****************************** Private data types ***************************/

/*****************************************************************************/



/************* Private Function prototype without function header ************/

/*****************************************************************************/

/*****************************************************************************/

/***************************** Public variable *******************************/

/*****************************************************************************/

/***************************** Private Variable ******************************/

/*****************************************************************************/



/************* External Flash Based Fimrware Update Related ************/



/************* Private Function prototype ************/




/************* Public Function prototype ************/

/*****************************************************************************/

/**************************** Public Function ********************************/

#define APP_S2W_FWUP_HTTP_TIMEOUT 75
#define APP_S2W_FWUP_DNS_REQ_DEF_TIME_OUT        5
#define APP_S2W_FWUP_DNS_REQ_DEF_RETRIES         3

//#define GSN_EXT_FLASH_FWUP_PULL_METHOD
//#define FWUP_DEBUG

#ifdef FWUP_DEBUG
#define FWUP_PRINT S2w_Printf
#else
#define FWUP_PRINT(...)
#endif

extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;
extern APP_MAIN_CTX_T appCtx;
extern S2W_OTA_FWUP_CONF_T OtaFwupConfParam;

#ifdef S2W_EXT_FLASH_FWUP_PULL_METHOD
extern GSN_HTTPC_CONF_INFO_T httpConfInfo;
extern GSN_HTTP_USER_HEADER_TYPE_T headerTypes[];
extern GSN_HTTP_USER_HEADER_TYPE_T headerTypesModified[];
#endif

#ifdef S2W_EXT_FLASH_FWUP_PULL_METHOD
extern INT8 *headerValues[GSN_HTTP_HEADER_ALL];
extern GSN_HTTP_USER_HEADER_TYPE_T headerTypes[GSN_HTTP_HEADER_ALL];
#endif
extern void nx_dns_retry_count_set(NX_DNS *dns_ptr,UINT retries);


PRIVATE void *httpsConn;
//PRIVATE GSN_OSAL_SEM_T extFlashUpdate;

#ifdef S2W_EXT_FLASH_FWUP_PULL_METHOD
//PRIVATE S2W_HTTP_DATA_T S2wFwupHttpData;
typedef struct GSN_OTAFU_PULL_CTX
{
	GSN_FWUP_CTX_T fwupCtx;

#ifdef ADK_OTAFU_DSV	
	GSN_OTAFU_DSV_CTX_T otafuDsvCtx;
#endif    

} GSN_OTAFU_PULL_CTX_T;
#endif

#ifdef ADK_OTAFU

PUBLIC VOID
AppOtafu_Cb(VOID *ctx, UINT8 event)
{
    if (event == GSN_OTAFU_EVENT_FWUP_SUCCESS)
    {
        UINT32 msg = APP_EVENT_FWUP_SUCCESS;
	    APP_MAIN_CTX_T* appCtx = (APP_MAIN_CTX_T*) ctx;
	    /* Notify APP */
	    (appCtx->taskNotifier)(msg, appCtx);
    }
}

GSN_OTAFU_CTX_T otafuCtx;

PUBLIC VOID
AppOtafu_Init(APP_MAIN_CTX_T* pAppCtx)
{
    otafuCtx.cbFn =  AppOtafu_Cb;
    otafuCtx.cbFnCtx = pAppCtx;
#ifdef ADK_OTAFU_DSV	
	otafuCtx.otafuDsvCtx.rootCertName = "B:/certs/OTAFU_DSV_ROOT_CERT";
	otafuCtx.otafuDsvCtx.serverCertName = "B:/certs/OTAFU_DSV_CERT";
#endif
	GsnOtafu_Init(&otafuCtx);
#ifdef S2W_FACT_IMAGE_REQ
    GsnFwup_FactImgReqSet(&otafuCtx.fwupCtx);
#else
    GsnFwup_FactImgReqClear(&otafuCtx.fwupCtx);
#endif
}

PUBLIC VOID
AppExtOtafu_Init(APP_MAIN_CTX_T* pAppCtx)
{
	memset(&pAppCtx->extOtafuCtx, 0, sizeof(GSN_EXTOTAFU_CTX_T));

	if(pAppCtx->extFlashCtx.extFlashStatus == EXTFLASH_NOT_INITIALIZED)
	{
		AppExtFlash_Init(GSN_FLASH_SPI_DMA);
	}

	pAppCtx->extOtafuCtx.extFwupCtx.extFlashCtx = &pAppCtx->extFlashCtx;
	pAppCtx->extOtafuCtx.extFwupCtx.extFwupSpiMode = pAppCtx->extFlashCtx.spiFlagFs;

    pAppCtx->extOtafuCtx.otafuCtx.cbFn =  AppOtafu_Cb;
    pAppCtx->extOtafuCtx.otafuCtx.cbFnCtx = pAppCtx;

#ifdef ADK_OTAFU_DSV	
	pAppCtx->extOtafuCtx.otafuDsvCtx.rootCertName = "B:/certs/OTAFU_DSV_ROOT_CERT";
	pAppCtx->extOtafuCtx.otafuDsvCtx.serverCertName = "B:/certs/OTAFU_DSV_CERT";
#endif

	GsnExtOtafu_Init(&pAppCtx->extOtafuCtx);
	
#ifdef S2W_FACT_IMAGE_REQ
    GsnFwup_FactImgReqSet(&pAppCtx->extOtafuCtx.otafuCtx.fwupCtx);
#else
    GsnFwup_FactImgReqClear(&pAppCtx->extOtafuCtx.otafuCtx.fwupCtx);
#endif
}
#endif

#ifdef S2W_EXT_FLASH_FWUP_PULL_METHOD
#if defined(S2W_SSL_CLIENT_SUPPORT) || defined(S2W_SSL_SERVER_SUPPORT)
extern S2W_SSL_CONF_T s2wSslConf;
#endif

PRIVATE VOID*
AppS2w_FwupExtFlashConnOpen(struct sockaddr_storage *pSockAddr, S2W_OTA_FWUP_CONF_T *pOtaFwupConf)
{
    GSN_STATUS status;
    void *pHttpHandle = NULL;
    GSN_HTTPC_CONN_PARAMS_T connParams;

    if(pOtaFwupConf->sslFlag && pOtaFwupConf->proxyFlag)
    {
        httpConfInfo.reqPathPtr = (INT8 *)OtaFwupConfParam.connectReqatPath;
    }
	/*Make all the custom headers types as 255 - This is done to coply withi the ROM code which is
		compiled with header type array being defined as array of UINT8 */
	{
		UINT8 i;
		for( i = 0; i < S2W_HTTPC_MAX_HDR_SUPPORTED; i++)
		{
			if(headerTypes[i] >= (GSN_HTTP_USER_HEADER_TYPE_T)TM_HTTP_HEADER_CUSTOM)
			{
				headerTypesModified[i] = (GSN_HTTP_USER_HEADER_TYPE_T)TM_HTTP_HEADER_CUSTOM;
			}
			else
			{
				headerTypesModified[i] = headerTypes[i];
			}
		}
	}

    /* Open Http/Https connection */
    memset((INT8 *)&connParams, 0, sizeof(connParams));
    connParams.ConTimeout = 60;
    connParams.proxyPresent = pOtaFwupConf->proxyFlag;
    connParams.type = (GSN_HTTP_TYPE_T)pOtaFwupConf->sslFlag;

#if defined(S2W_SSL_CLIENT_SUPPORT)    
    if(pOtaFwupConf->sslFlag == TRUE)
    {        
        if(pOtaFwupConf->certAddr != NULL)
        { 
            connParams.sslParams.caCertLen  = *(UINT16 *)pOtaFwupConf->certAddr;   
            connParams.sslParams.caCert = pOtaFwupConf->certAddr + 2;    
            connParams.sslParams.caCertName = NULL;        
        }
    }
    if(0 != s2wSslConf.dnsBufferLen)
    {
        connParams.dnsBuf = gsn_malloc(sizeof(GSN_SSL_DNS_BUF_INFO_T));
        s2wSslConf.dnsNameBuf = gsn_malloc(s2wSslConf.dnsBufferLen);
        memset(s2wSslConf.dnsNameBuf, 0, s2wSslConf.dnsBufferLen);
        connParams.dnsBuf->bufStart = connParams.dnsBuf->bufCurrent =  s2wSslConf.dnsNameBuf;
        connParams.dnsBuf->bufLen = s2wSslConf.dnsBufferLen;
    }
    else
#endif		
    {
        connParams.dnsBuf = NULL;
    }
	status = GsnHttp_Start(&pHttpHandle, pSockAddr,
                          		 &connParams, &httpConfInfo);
    if(NULL != connParams.dnsBuf)
    	gsn_free(connParams.dnsBuf);
    connParams.dnsBuf = NULL;
    if(status == GSN_SUCCESS)
    {
        return pHttpHandle;
    }
    else
    {
        return NULL;
    }
}

#endif

PRIVATE GSN_STATUS
AppS2w_FwupExtFlashCheckStatus(GSN_FWUP_CTX_T *appFwupCtx, INT8 **DataBuff, UINT32 *DataLen)
{
    UINT8 flag = FALSE;
    GSN_STATUS retVal  = GSN_SUCCESS;
    UINT32 i = 0;
    INT8 *httpStatusParse;

	httpStatusParse = *DataBuff;

    if(appFwupCtx->downloadedSize == 0)
    {
        flag = TRUE;
    }

    if(flag)
    {
        if(0 == memcmp(*DataBuff, "200", 3))
		{
			while (!(httpStatusParse[i] == '\r' && httpStatusParse[i+1] == '\n'))
			{
			    i++;
			}

			i += 2;

            //FWUP_PRINT("\n\r200 OK\r\n");
        }
        else //if(memcmp(*DataBuff, "404", 3))
        {
            //To Be Done: Error Handling
            //FWUP_PRINT("\n\r%s\n\r", *DataBuff);
            //FWUP_PRINT("HTTP Status = %c%c%c \r\n",*DataBuff[0], *DataBuff[1], *DataBuff[2] );
            retVal = GSN_FAILURE;
        }

        *DataBuff = *DataBuff + i;
        *DataLen = *DataLen - i;
    }

    return retVal;

}

#ifdef S2W_EXT_FLASH_FWUP_PULL_METHOD
PRIVATE VOID
AppS2w_FwupExtFlashRxCb(VOID   *ctx,
                                    GSN_HTTPC_CONN_HANDLE connHandle,
                                    INT8  *httpRxDataBuf,
                                    INT32 httpRxDataLen,
                                    INT32 *rxBufferMgmtstatus)
{
    GSN_STATUS retVal = GSN_SUCCESS;

	
	GSN_OTAFU_PULL_CTX_T *otafuPullCtx = (GSN_OTAFU_PULL_CTX_T *)ctx;

    retVal = AppS2w_FwupExtFlashCheckStatus(&otafuPullCtx->fwupCtx, &httpRxDataBuf,(UINT32 *) &httpRxDataLen);

    if(GSN_SUCCESS != retVal)
    {
        //FWUP_PRINT("Dwnd Failed In Cb: FwUP Check = %x\r\n", retVal);
       *rxBufferMgmtstatus = GSN_FAILURE;
       goto AppFwupCbExit;
    }

#ifdef FWUP_DEBUG_HTTP_RCV_DATA
    count = count + httpRxDataLen;

    //FWUP_PRINT("RcvdData=%d\r\n",count );
#endif

#ifdef ADK_OTAFU_DSV
	GsnOtafuDsv_Sha1Update(&otafuPullCtx->otafuDsvCtx, httpRxDataBuf, httpRxDataLen);
#endif

    retVal = GsnFwup_DownLoad(&otafuPullCtx->fwupCtx, (UINT8 *)httpRxDataBuf, httpRxDataLen);
    if(retVal != GSN_SUCCESS)
    {
       //appRtcMemData.smRtc.fwupErrCount++;
       //FWUP_PRINT("Dwnd Failed In Cb = %x\r\n", retVal);
       *rxBufferMgmtstatus = GSN_FAILURE;

    }
    else
    {
        *rxBufferMgmtstatus = GSN_SUCCESS;
    }

AppFwupCbExit:

    return;

}

#ifdef ADK_OTAFU_DSV
PRIVATE VOID
AppS2w_FwupExtFlashSignRxCb(VOID   *ctx,
                                    GSN_HTTPC_CONN_HANDLE connHandle,
                                    INT8  *httpRxDataBuf,
                                    INT32 httpRxDataLen,
                                    INT32 *rxBufferMgmtstatus)
{
    GSN_STATUS retVal = GSN_SUCCESS;
//    GSN_FWUP_CTX_T    *appFwupCtx = (GSN_FWUP_CTX_T *)ctx;
	GSN_OTAFU_PULL_CTX_T *otafuPullCtx = (GSN_OTAFU_PULL_CTX_T *)ctx;


    retVal = AppS2w_FwupExtFlashCheckStatus(&otafuPullCtx->fwupCtx, &httpRxDataBuf,(UINT32 *) &httpRxDataLen);

    if(GSN_SUCCESS != retVal)
    {
        //FWUP_PRINT("Dwnd Failed In Cb: FwUP Check = %x\r\n", retVal);
       *rxBufferMgmtstatus = GSN_FAILURE;
       goto AppFwupCbExit;
    }

#ifdef FWUP_DEBUG_HTTP_RCV_DATA
    count = count + httpRxDataLen;

    //FWUP_PRINT("RcvdData=%d\r\n",count );
#endif

	retVal = GsnOtafuDsv_SignUpdate(&otafuPullCtx->otafuDsvCtx, httpRxDataBuf, httpRxDataLen);

    if(retVal != GSN_SUCCESS)
    {
       //appRtcMemData.smRtc.fwupErrCount++;
       FWUP_PRINT("\r\nInvalid Signature\r\n");
       *rxBufferMgmtstatus = GSN_FAILURE;

    }
    else
    {
        *rxBufferMgmtstatus = GSN_SUCCESS;
    }

AppFwupCbExit:

    return;

}
#endif

PRIVATE GSN_STATUS
AppS2w_ExtFwupDownLoadStart(GSN_HTTPC_CONN_HANDLE pHttpsConn,
                            GSN_OTAFU_PULL_CTX_T *otafuPullCtx,
                            UINT8 *url)
{
    UINT8 *pHttpRxDataBuf = NULL;
    UINT32 httpRxDataLen, retVal = GSN_FAILURE;

    /* allocate Buffer for recieving firmware */
    pHttpRxDataBuf = gsn_malloc(1024);

    if(pHttpRxDataBuf == NULL)
    {
        retVal = GSN_FAILURE;
        //FWUP_PRINT("Failure1\r\n");
        goto AppS2w_ExtFwupDownLoadStart_Exit;
    }
    memset(pHttpRxDataBuf, 0, 1024);
    httpRxDataLen = 1024;

    if(url != NULL)
    {
        httpConfInfo.reqPathPtr = (INT8 *)url;       //page to be opened
        /* set configuration to GET the Binary*/
        httpConfInfo.reqMethod = GSN_HTTP_METHOD_GET;  //Request method
        httpConfInfo.reqBodyLen = 0;           //Request body len
        httpConfInfo.reqBodyTotalLen = 0;      //Request body total len

        /* register call back function to process recieved part of firmware */
        httpConfInfo.rxBufferMgmtCb = AppS2w_FwupExtFlashRxCb;
        httpConfInfo.reqBodyPtr = NULL;              //Request body pointer

        httpConfInfo.rxBufferMgmtCbCtx = otafuPullCtx;

		/*Make all the custom headers types as 255 - This is done to coply withi the ROM code which is
		compiled with header type array being defined as array of UINT8 */
		{
			UINT8 i;
			for( i = 0; i < S2W_HTTPC_MAX_HDR_SUPPORTED; i++)
	        {
	        	if(headerTypes[i] >= (GSN_HTTP_USER_HEADER_TYPE_T)TM_HTTP_HEADER_CUSTOM)
				{
					headerTypesModified[i] = (GSN_HTTP_USER_HEADER_TYPE_T)TM_HTTP_HEADER_CUSTOM;
				}
				else
				{
	        		headerTypesModified[i] = headerTypes[i];
				}
	        }
		}
		/* Send Data */
		
		retVal = GsnHttp_Send(pHttpsConn, (INT8 *)pHttpRxDataBuf,
                       &httpRxDataLen, APP_S2W_FWUP_HTTP_TIMEOUT, &httpConfInfo);

        if(retVal != GSN_SUCCESS)
        {
            //FWUP_PRINT("HTTP Send Failed: %x\r\n", retVal);
            goto AppS2w_ExtFwupDownLoadStart_Exit;
        }


        if(NULL != pHttpRxDataBuf)
        {
            /* check the status */
            if(GSN_FAILURE == AppS2w_FwupExtFlashCheckStatus(&otafuPullCtx->fwupCtx, (INT8 **)&pHttpRxDataBuf, &httpRxDataLen))
            {
                retVal = GSN_FAILURE;
                //FWUP_PRINT("Failure2\r\n");
                goto AppS2w_ExtFwupDownLoadStart_Exit;
            }
#ifdef ADK_OTAFU_DSV
			GsnOtafuDsv_Sha1Update(&otafuPullCtx->otafuDsvCtx, pHttpRxDataBuf, httpRxDataLen);
#endif
            /* Write recieved chunk to external flash */
            retVal = GsnFwup_DownLoad(&otafuPullCtx->fwupCtx, (UINT8 *)pHttpRxDataBuf, httpRxDataLen);

            if(retVal != GSN_SUCCESS)
            {
                //FWUP_PRINT("Dwnd Failed = %d\r\n", retVal);
                goto AppS2w_ExtFwupDownLoadStart_Exit;
            }
        }


#ifndef ADK_OTAFU_DSV
        retVal = GsnFwup_DownLoadEnd(&otafuPullCtx->fwupCtx);
#endif

        if(retVal != GSN_SUCCESS)
        {
            //FWUP_PRINT("Dwnd End Failed = %d\r\n", retVal);
            goto AppS2w_ExtFwupDownLoadStart_Exit;
        }

    }
AppS2w_ExtFwupDownLoadStart_Exit:
    if(pHttpRxDataBuf != NULL)
        gsn_free(pHttpRxDataBuf);

#ifdef ADK_OTAFU_DSV
		GsnOtafuDsv_Sha1Finish(&otafuPullCtx->otafuDsvCtx);
#endif
    return retVal;
}

#ifdef ADK_OTAFU_DSV
PRIVATE GSN_STATUS
AppS2w_ExtFwupDownLoadDsv(GSN_HTTPC_CONN_HANDLE pHttpsConn,                     
			  GSN_OTAFU_PULL_CTX_T *otafuPullCtx,
                          UINT8 *url)
{
    UINT8 *pHttpRxDataBuf = NULL;
    UINT32 httpRxDataLen, retVal = GSN_FAILURE;

    /* allocate Buffer for recieving firmware */
    pHttpRxDataBuf = gsn_malloc(1024);

    if(pHttpRxDataBuf == NULL)
    {
        retVal = GSN_FAILURE;
        //FWUP_PRINT("Failure1\r\n");
        goto AppS2w_ExtFwupDownLoadStart_Exit;
    }
    memset(pHttpRxDataBuf, 0, 1024);
    httpRxDataLen = 1024;

    if(url != NULL)
    {
        httpConfInfo.reqPathPtr = (INT8 *)url;       //page to be opened
        /* set configuration to GET the Binary*/
        httpConfInfo.reqMethod = GSN_HTTP_METHOD_GET;  //Request method
        httpConfInfo.reqBodyLen = 0;           //Request body len
        httpConfInfo.reqBodyTotalLen = 0;      //Request body total len

        /* register call back function to process recieved part of firmware */
        httpConfInfo.rxBufferMgmtCb = AppS2w_FwupExtFlashSignRxCb;
        httpConfInfo.reqBodyPtr = NULL;              //Request body pointer

        httpConfInfo.rxBufferMgmtCbCtx = otafuPullCtx;

		/*Make all the custom headers types as 255 - This is done to coply withi the ROM code which is
		compiled with header type array being defined as array of UINT8 */
		{
			UINT8 i;
			for( i = 0; i < S2W_HTTPC_MAX_HDR_SUPPORTED; i++)
	        {
	        	if(headerTypes[i] >= (GSN_HTTP_USER_HEADER_TYPE_T)S2W_HTTPC_CFG_PARAM_HEADER_CUSTOM)
				{
					headerTypesModified[i] = (GSN_HTTP_USER_HEADER_TYPE_T)TM_HTTP_HEADER_CUSTOM;
				}
				else
				{
	        		headerTypesModified[i] = headerTypes[i];
				}
	        }
		}
		/* Send Data */
		
		retVal = GsnHttp_Send(pHttpsConn, (INT8 *)pHttpRxDataBuf,
                       &httpRxDataLen, APP_S2W_FWUP_HTTP_TIMEOUT, &httpConfInfo);

        if(retVal != GSN_SUCCESS)
        {
            //FWUP_PRINT("HTTP Send Failed: %x\r\n", retVal);
            goto AppS2w_ExtFwupDownLoadStart_Exit;
        }

        if(NULL != pHttpRxDataBuf)
        {
            /* check the status */
            if(GSN_FAILURE == AppS2w_FwupExtFlashCheckStatus(&otafuPullCtx->fwupCtx, (INT8 **)&pHttpRxDataBuf, &httpRxDataLen))
            {
                retVal = GSN_FAILURE;
                //FWUP_PRINT("Failure2\r\n");
                goto AppS2w_ExtFwupDownLoadStart_Exit;
            }

            /* Write recieved chunk to external flash */
			
			retVal = GsnOtafuDsv_SignUpdate(&otafuPullCtx->otafuDsvCtx, pHttpRxDataBuf, httpRxDataLen);

            if(retVal != GSN_SUCCESS)
            {                
				FWUP_PRINT("\r\nInvalid Signature\r\n", retVal);             
                goto AppS2w_ExtFwupDownLoadStart_Exit;
            }
        }
		
    }
	
AppS2w_ExtFwupDownLoadStart_Exit:
    if(pHttpRxDataBuf != NULL)
        gsn_free(pHttpRxDataBuf);
    return retVal;
}
#endif

PUBLIC GSN_STATUS
APPS2w_ExtFlashStart( S2W_OTA_FWUP_CONF_T *pOtaFwupConf)
{
    UINT32  retVal = GSN_FAILURE, status;
	GSN_OTAFU_PULL_CTX_T otafuPullCtx;
	UINT8 tmp[20] = {0};
	struct sockaddr_storage sockAddr = {0};
	memset(&otafuPullCtx, 0, sizeof(GSN_OTAFU_PULL_CTX_T));

    /*Initialise ext flash */
    if(GSN_SUCCESS != GsnFwup_Init(&otafuPullCtx.fwupCtx))
    {
    	FWUP_PRINT("\r\nExternal flash init failed\n\r");
        return GSN_FAILURE;
    }

#ifdef ADK_OTAFU_DSV	
	if(GSN_SUCCESS != GsnOtafuDsv_Init(&otafuPullCtx.otafuDsvCtx))
    {
    	FWUP_PRINT("\r\nExternal flash init failed\n\r");
        return GSN_FAILURE;
    }
	otafuPullCtx.otafuDsvCtx.rootCertName = "B:/certs/OTAFU_DSV_ROOT_CERT";
	otafuPullCtx.otafuDsvCtx.serverCertName = "B:/certs/OTAFU_DSV_CERT";
	if(!s2wappMainTaskCtxt->fsInit)
    {
		App_FsInit();
		s2wappMainTaskCtxt->fsInit = TRUE;
        f_enterFS();
	}
#endif

#ifdef S2W_FACT_IMAGE_REQ
    GsnFwup_FactImgReqSet(&otafuPullCtx.fwupCtx);
#else
    GsnFwup_FactImgReqClear(&otafuPullCtx.fwupCtx);
#endif
    if(pOtaFwupConf->proxyFlag == 1)
    {
        memcpy((INT8 *)&sockAddr, (INT8*)&pOtaFwupConf->proxySockAddr, sizeof(pOtaFwupConf->proxySockAddr));
    }
    else if(pOtaFwupConf->fwSrvHostName != NULL)
    	{
        GSN_STATUS status;

        GsnNwIf_DnsRetryCountSet(&appCtx.if0.nwifCtx.dnsCliHndl,APP_S2W_FWUP_DNS_REQ_DEF_RETRIES);
        status = GsnNwIf_DnsHostByNameGet(&appCtx.if0.nwifCtx, (UINT8*)pOtaFwupConf->fwSrvHostName, &pOtaFwupConf->sockAddr.addr.ipv4.sin_addr.s_addr, APP_S2W_FWUP_DNS_REQ_DEF_TIME_OUT);

        if (status == GSN_SUCCESS)
        {
            pOtaFwupConf->sockAddr.addr.ipv4.sin_family = AF_INET;
            pOtaFwupConf->sockAddr.addr.ipv4.sin_addr.s_addr = htonl(pOtaFwupConf->sockAddr.addr.ipv4.sin_addr.s_addr);
            FWUP_PRINT("IP: %x\n\r", pOtaFwupConf->sockAddr.addr.ipv4.sin_addr.s_addr);
        }
        else
        {
#ifdef S2W_IPv6_SUPPORT            
            NXD_ADDRESS     host_ipduo_address;
            status = nxd_dns_host_by_name_get(&appCtx.if0.nwifCtx.dnsCliHndl,(UINT8*)pOtaFwupConf->fwSrvHostName, &host_ipduo_address, APP_S2W_FWUP_DNS_REQ_DEF_TIME_OUT*100, 0x6);
#endif                
            if (status != GSN_SUCCESS)
			{
				FWUP_PRINT("\r\nFWUP server Host Name not found\n\r");
                return S2W_FAILURE;
			}
#ifdef S2W_IPv6_SUPPORT    
            memcpy(pOtaFwupConf->sockAddr.addr.ipv6.sin6_addr.s6_addr32, host_ipduo_address.nxd_ip_address.v6, sizeof(host_ipduo_address.nxd_ip_address.v6));
            pOtaFwupConf->sockAddr.addr.ipv6.sin6_family = AF_INET6;
            FWUP_PRINT("\r\n%x:%x:%x:%x:%x:%x:%x:%x\r\n",*(((UINT16*)host_ipduo_address.nxd_ip_address.v6)+1),*((UINT16*)host_ipduo_address.nxd_ip_address.v6),*(((UINT16*)host_ipduo_address.nxd_ip_address.v6)+3),*(((UINT16*)host_ipduo_address.nxd_ip_address.v6)+2),*(((UINT16*)host_ipduo_address.nxd_ip_address.v6)+5),*(((UINT16*)host_ipduo_address.nxd_ip_address.v6)+4),*(((UINT16*)host_ipduo_address.nxd_ip_address.v6)+7),*(((UINT16*)host_ipduo_address.nxd_ip_address.v6)+6)); 
#endif                
    	}
        memcpy((INT8 *)&sockAddr, (INT8*)&pOtaFwupConf->sockAddr, sizeof(pOtaFwupConf->sockAddr));
    }
    else
    {
        memcpy((INT8 *)&sockAddr, (INT8*)&pOtaFwupConf->sockAddr, sizeof(pOtaFwupConf->sockAddr));
    }
    /*store the  CONNECT request path*/
    if(pOtaFwupConf->sslFlag && pOtaFwupConf->proxyFlag &&
        (NULL == OtaFwupConfParam.connectReqatPath))
    {

        OtaFwupConfParam.connectReqatPath = (UINT8 *)httpConfInfo.reqPathPtr;
    }

    AppS2wHal_RadioModeConfig(1);

#ifdef ADK_OTAFU_DSV	
    {
		/* Download Digital Signature */
        httpsConn = AppS2w_FwupExtFlashConnOpen(&sockAddr, pOtaFwupConf);

        if(NULL == httpsConn)
        {
            retVal = GSN_FAILURE;
        	goto APPS2w_ExtFlashStart_Exit;
        }
#if defined(S2W_SSL_CLIENT_SUPPORT)	
        if(pOtaFwupConf->sslFlag && (pOtaFwupConf->fwSrvHostName != NULL))
        {
            status = AppS2wHal_HttpCheckDns(pOtaFwupConf->fwSrvHostName);
            if((pOtaFwupConf->dnsError) && (S2W_SUCCESS != status))
            {
                if(NULL != s2wSslConf.dnsNameBuf)
                {
                	gsn_free(s2wSslConf.dnsNameBuf);
                	s2wSslConf.dnsNameBuf = NULL;
                	s2wSslConf.dnsBufferLen = 0;
                }
                retVal = GSN_FAILURE;
                GsnHttp_Close(httpsConn);
            	goto APPS2w_ExtFlashStart_Exit;
            }
        }
        else if((pOtaFwupConf->sslFlag) && (s2wSslConf.dnsNameBuf))
        {

        	inet_ntop(AF_INET,&(pOtaFwupConf->sockAddr.addr.ipv4.sin_addr.s_addr), tmp, sizeof(tmp));
            status = AppS2wHal_HttpCheckDns(tmp);
            if((pOtaFwupConf->dnsError) && (S2W_SUCCESS != status))
            {
                if(NULL != s2wSslConf.dnsNameBuf)
                {
                	gsn_free(s2wSslConf.dnsNameBuf);
                	s2wSslConf.dnsNameBuf = NULL;
                	s2wSslConf.dnsBufferLen = 0;
                }
                retVal = GSN_FAILURE;
                GsnHttp_Close(httpsConn);
            	goto APPS2w_ExtFlashStart_Exit;
            }
        }
#endif		
		retVal = AppS2w_ExtFwupDownLoadDsv(httpsConn, &otafuPullCtx,
					pOtaFwupConf->urls[S2W_OTAFU_URL_SIGN_IMAGE]);
        if(retVal != GSN_SUCCESS)
        {
#if defined(S2W_SSL_CLIENT_SUPPORT)
            if(NULL != s2wSslConf.dnsNameBuf)
            {
            	gsn_free(s2wSslConf.dnsNameBuf);
            	s2wSslConf.dnsNameBuf = NULL;
            	s2wSslConf.dnsBufferLen = 0;
            }
#endif
            /* WLAN firmware download failed. Abort update */
			FWUP_PRINT("\r\nDigital Signature download failed\r\n");
            GsnHttp_Close(httpsConn);
            goto APPS2w_ExtFlashStart_Exit;
        }
        GsnHttp_Close(httpsConn);
    }
#endif

	{
		/* Download Firmware */	
#ifdef ADK_OTAFU_DSV			
		GsnOtafuDsv_Sha1Init(&otafuPullCtx.otafuDsvCtx);
		if(pOtaFwupConf->proxyFlag == 1)
    	{
        	memcpy((INT8 *)&sockAddr, (INT8*)&pOtaFwupConf->proxySockAddr, sizeof(pOtaFwupConf->proxySockAddr));
    	}
    	else
    	{
    		memcpy((INT8 *)&sockAddr, (INT8*)&pOtaFwupConf->sockAddr, sizeof(pOtaFwupConf->sockAddr));
    	}
#endif
		httpsConn = AppS2w_FwupExtFlashConnOpen(&sockAddr, pOtaFwupConf);
		
		if(NULL == httpsConn)
		{
#if defined(S2W_SSL_CLIENT_SUPPORT)
	        if(NULL != s2wSslConf.dnsNameBuf)
	        {
	        	gsn_free(s2wSslConf.dnsNameBuf);
	        	s2wSslConf.dnsNameBuf = NULL;
	        	s2wSslConf.dnsBufferLen = 0;
	        }
#endif
			retVal = GSN_FAILURE;
			goto APPS2w_ExtFlashStart_Exit;
		}
#if defined(S2W_SSL_CLIENT_SUPPORT)			
        if(pOtaFwupConf->sslFlag && (pOtaFwupConf->fwSrvHostName != NULL))
        {
            status = AppS2wHal_HttpCheckDns(pOtaFwupConf->fwSrvHostName);
            if((pOtaFwupConf->dnsError) && (S2W_SUCCESS != status))
            {
                if(NULL != s2wSslConf.dnsNameBuf)
                {
                	gsn_free(s2wSslConf.dnsNameBuf);
                	s2wSslConf.dnsNameBuf = NULL;
                	s2wSslConf.dnsBufferLen = 0;
                }
                retVal = GSN_FAILURE;
                GsnHttp_Close(httpsConn);
            	goto APPS2w_ExtFlashStart_Exit;
            }
        }
        else if((pOtaFwupConf->sslFlag) && (s2wSslConf.dnsNameBuf))
        {

        	inet_ntop(AF_INET,&(pOtaFwupConf->sockAddr.addr.ipv4.sin_addr.s_addr), (char *)tmp, sizeof(tmp));
            status = AppS2wHal_HttpCheckDns(tmp);
            if((pOtaFwupConf->dnsError) && (S2W_SUCCESS != status))
            {
                if(NULL != s2wSslConf.dnsNameBuf)
                {
                	gsn_free(s2wSslConf.dnsNameBuf);
                	s2wSslConf.dnsNameBuf = NULL;
                	s2wSslConf.dnsBufferLen = 0;
                }
                retVal = GSN_FAILURE;
                GsnHttp_Close(httpsConn);
            	goto APPS2w_ExtFlashStart_Exit;
            }
        }
        if(NULL != s2wSslConf.dnsNameBuf)
        {
        	gsn_free(s2wSslConf.dnsNameBuf);
        	s2wSslConf.dnsNameBuf = NULL;
        	s2wSslConf.dnsBufferLen = 0;
        }

#endif		
		retVal = AppS2w_ExtFwupDownLoadStart(httpsConn, &otafuPullCtx,
					pOtaFwupConf->urls[S2W_OTAFU_URL_FW_IMAGE]);
		if(retVal != GSN_SUCCESS)
		{
			
			FWUP_PRINT("\r\nFirmware download failed\r\n");
			GsnHttp_Close(httpsConn);
			goto APPS2w_ExtFlashStart_Exit;
		}
		GsnHttp_Close(httpsConn);
	}
	
    /* Close http conn */
    AppS2wHal_RadioModeConfig(0);

#ifdef ADK_OTAFU_DSV	
	
	retVal = GsnOtafuDsv_Verify(&otafuPullCtx.otafuDsvCtx);
	if(retVal != GSN_SUCCESS)
	{
		FWUP_PRINT("\r\nsiganture Mismatch\r\n");
		goto APPS2w_ExtFlashStart_Exit;
	}
	else
	{
        retVal = GsnFwup_DownLoadEnd(&otafuPullCtx.fwupCtx);
		if(retVal != GSN_SUCCESS)
		{
			FWUP_PRINT("\r\nControl block update failed\r\n");
			goto APPS2w_ExtFlashStart_Exit;
		}
		FWUP_PRINT("\r\nFWUP Success\r\n");
		GsnOtafuDsv_DeInit(&otafuPullCtx.otafuDsvCtx);
	}
#endif

    /* Downloading to external flash complete*/
    //S2w_Printf("\n\rResetting....");
    GsnSys_Reset(GSN_RESET_REASON_APP_FWUP);
    while(1);
APPS2w_ExtFlashStart_Exit:
    AppS2wHal_RadioModeConfig(0);
    GsnFwup_DeInit(&otafuPullCtx.fwupCtx);
	
#ifdef ADK_OTAFU_DSV	
	GsnOtafuDsv_DeInit(&otafuPullCtx.otafuDsvCtx);
#endif
	FWUP_PRINT("\r\nFirmware update failed\r\n");
    return retVal;
}

#if 0
xml_ota_fwup_info_t ota_fwup_info;
xml_ota_fwup_gs1011m_info_t ota_fwup_gs1011;

GSN_STATUS
AppS2w_ExtFlashInfoXmlGet(S2W_OTA_FWUP_CONF_T *pOtaFwupConf)
{
	INT8 ipAddrString[20], *pHttpRxDataBuf;
	UINT16 caCertLen = 0, serverPort;
    UINT8 *caCertAddr = NULL;
	UINT32 httpRxDataLen, retVal;
	S2W_IPADDR_T fwSrvIp;

	if(pOtaFwupConf->proxyFlag == 1)
    {
    	/* Use proxy */
        sprintf(ipAddrString,"%d.%d.%d.%d",pOtaFwupConf->proxyIp[0] ,pOtaFwupConf->proxyIp[1],
									   pOtaFwupConf->proxyIp[2],pOtaFwupConf->proxyIp[3] );
        serverPort = pOtaFwupConf->proxyPort;
    }
    else
    {
        if(pOtaFwupConf->fwSrvHostName != NULL)
    	{
    		/* Fwup server host name present. */
	    	S2W_DNSINFO_T dnsInfo;
			UINT8 len;
			memset(&dnsInfo, 0, sizeof(S2W_DNSINFO_T));
	    	len = strlen((char *)pOtaFwupConf->fwSrvHostName);
	        memcpy(dnsInfo.hostName, pOtaFwupConf->fwSrvHostName, len);

			/* Find ip address from host name */
	        retVal = AppS2wHal_DnsFind(&dnsInfo);
			if(retVal != 0)
			{
				FWUP_PRINT("FWUP server Host Name not found\n\r");
				return GSN_FAILURE;
			}
			sprintf(ipAddrString,"%d.%d.%d.%d",dnsInfo.ipAddr[0], dnsInfo.ipAddr[1],
	    									   dnsInfo.ipAddr[2], dnsInfo.ipAddr[3] );
    	}
		else if(memcmp(pOtaFwupConf->fwSrvIp, fwSrvIp, sizeof(S2W_IPADDR_T)) != 0)
		{
	        sprintf(ipAddrString,"%d.%d.%d.%d",pOtaFwupConf->fwSrvIp[0] ,pOtaFwupConf->fwSrvIp[1],
	    									   pOtaFwupConf->fwSrvIp[2],pOtaFwupConf->fwSrvIp[3] );
		}
        serverPort = pOtaFwupConf->srvPort;
    }

	if(pOtaFwupConf->sslFlag == TRUE)
    {
        if(pOtaFwupConf->certAddr != NULL)
        {
            caCertLen = *(UINT16 *)pOtaFwupConf->certAddr;
            caCertAddr = pOtaFwupConf->certAddr + 2;
        }
    }
	/* Open http connection */
	httpsConn = AppS2w_FwupExtFlashConnOpen(ipAddrString, serverPort,
        pOtaFwupConf->sslFlag, caCertAddr, caCertLen, pOtaFwupConf->proxyFlag);

	//FWUP_PRINT("httpsConn = %x\n\r", httpsConn);
	if(httpsConn == NULL)
	{
		return GSN_FAILURE;
	}
	pHttpRxDataBuf = gsn_malloc(1024);
	if(pHttpRxDataBuf == NULL)
	{
		return GSN_FAILURE;
	}
    memset(pHttpRxDataBuf, 0, 1024);
    httpRxDataLen = 1024;

	httpConfInfo.reqPathPtr = (INT8 *)pOtaFwupConf->urls[3];       //page to be opened
    /* set configuration to GET the Binary*/
    httpConfInfo.reqMethod = GSN_HTTP_METHOD_GET;  //Request method
    httpConfInfo.reqBodyLen = 0;           //Request body len
    httpConfInfo.reqBodyTotalLen = 0;      //Request body total len

	httpConfInfo.rxBufferMgmtCb = NULL;
    httpConfInfo.reqBodyPtr = NULL;

	retVal = GsnHttp_Send(httpsConn, (INT8 *)pHttpRxDataBuf,
                &httpRxDataLen, APP_S2W_FWUP_HTTP_TIMEOUT, &httpConfInfo);
	//FWUP_PRINT("%s\n\r", pHttpRxDataBuf);
	if(retVal == GSN_SUCCESS)
    {
    	UINT8 *ParentNodeStart, *ParentNodeEnd;
		UINT8 *pApp0, *pApp1, *pWlan, *pVer, *pNewVer, *pWebImage;
		#ifdef GS1500M
		UINT8 *pMac;
		#endif
		ParentNodeStart = (UINT8 *)pHttpRxDataBuf;
		ParentNodeEnd = (UINT8 *)pHttpRxDataBuf + httpRxDataLen - 1;
		pHttpRxDataBuf[httpRxDataLen] = 0;
		memset(&ota_fwup_info, 0, sizeof(ota_fwup_info));

		/* Decode xml data */
    	retVal = GsnXml_Decode(ParentNodeStart, ParentNodeEnd,
                    (GSN_XML_COMPLEX_OBJ_T *) &xml_ota_fwup,
                    (UINT8 *) &ota_fwup_info);
		/* allocate memory for urls */
		pWlan = gsn_malloc(ota_fwup_info.fwupInfo.urlWlan.len+1);
		if(pWlan == NULL)
		{
			gsn_free(pHttpRxDataBuf);
			return GSN_FAILURE;
		}
		memset(pWlan, 0, ota_fwup_info.fwupInfo.urlWlan.len+1);

		#ifdef GS1500M
		pMac = gsn_malloc(ota_fwup_info.fwupInfo.urlMac.len+1);
		if(pMac == NULL)
		{
			gsn_free(pHttpRxDataBuf);
			return GSN_FAILURE;
		}
		memset(pMac, 0, ota_fwup_info.fwupInfo.urlMac.len+1);
		#endif
		pApp0 = gsn_malloc(ota_fwup_info.fwupInfo.urlApp0.len+1);
		if(pApp0 == NULL)
		{
			gsn_free(pHttpRxDataBuf);
			return GSN_FAILURE;
		}
		memset(pApp0, 0, ota_fwup_info.fwupInfo.urlApp0.len+1);

		pApp1 = gsn_malloc(ota_fwup_info.fwupInfo.urlApp1.len+1);
		if(pApp1 == NULL)
		{
			gsn_free(pHttpRxDataBuf);
			return GSN_FAILURE;
		}
		memset(pApp1, 0, ota_fwup_info.fwupInfo.urlApp1.len+1);

		pWebImage = gsn_malloc(ota_fwup_info.fwupInfo.urlWebImage.len+1);
		if(pWebImage == NULL)
		{
			gsn_free(pHttpRxDataBuf);
			return GSN_FAILURE;
		}
		memset(pWebImage, 0, ota_fwup_info.fwupInfo.urlWebImage.len+1);

		/* Copy urls */
		memcpy(pWlan, ota_fwup_info.fwupInfo.urlWlan.ptr, ota_fwup_info.fwupInfo.urlWlan.len);
#ifdef GS1500M
       memcpy(pMac, ota_fwup_info.fwupInfo.urlMac.ptr, ota_fwup_info.fwupInfo.urlMac.len);
#endif
		memcpy(pApp0, ota_fwup_info.fwupInfo.urlApp0.ptr, ota_fwup_info.fwupInfo.urlApp0.len);
		memcpy(pApp1, ota_fwup_info.fwupInfo.urlApp1.ptr, ota_fwup_info.fwupInfo.urlApp1.len);
		memcpy(pWebImage, ota_fwup_info.fwupInfo.urlWebImage.ptr, ota_fwup_info.fwupInfo.urlWebImage.len);
		pVer = gsn_malloc(ota_fwup_info.fwupInfo.fwVersion.len+1);
		if(pVer == NULL)
		{
			gsn_free(pHttpRxDataBuf);
			return GSN_FAILURE;
		}
		memset(pVer, 0, ota_fwup_info.fwupInfo.fwVersion.len+1);
		pNewVer = gsn_malloc(ota_fwup_info.fwupInfo.newFwVersion.len+1);
		if(pNewVer == NULL)
		{
			gsn_free(pHttpRxDataBuf);
			return GSN_FAILURE;
		}
		memset(pNewVer, 0, ota_fwup_info.fwupInfo.newFwVersion.len+1);
		memcpy(pVer, ota_fwup_info.fwupInfo.fwVersion.ptr, ota_fwup_info.fwupInfo.fwVersion.len);
		memcpy(pNewVer, ota_fwup_info.fwupInfo.newFwVersion.ptr, ota_fwup_info.fwupInfo.newFwVersion.len);
#if 0
		FWUP_PRINT("\n\rfmtver: %d",ota_fwup_info.formatVer);
		FWUP_PRINT("\n\rfwVer: %s",pVer);
		FWUP_PRINT("\n\rNewfwVer: %s",pNewVer);
		FWUP_PRINT("\r\nwlan: %s\n\r", pWlan);
		#ifdef GS1500M
		FWUP_PRINT("\r\nMac: %s\n\r", pMac);
		#endif
		FWUP_PRINT("app0: %s\n\r", pApp0);
		FWUP_PRINT("app1: %s\n\r", pApp1);
		FWUP_PRINT("\r\nWebImage: %s\n\r", pWebImage);
		FWUP_PRINT("\n\rchkSumApp0: %d",ota_fwup_info.fwupInfo.chkSumApp0);
		FWUP_PRINT("\n\rchkSumApp1: %d",ota_fwup_info.fwupInfo.chkSumApp1);
		FWUP_PRINT("\n\rchkSumWlan: %d\n\r",ota_fwup_info.fwupInfo.chkSumWlan);
		#ifdef GS1500M
		FWUP_PRINT("\n\rchkSumMac: %d\n\r",ota_fwup_info.fwupInfo.chkSumMac);
		#endif
		FWUP_PRINT("\n\rBackUp: %d\n\r", ota_fwup_info.fwupInfo.backUp);
#endif
		/* Save into S2W_OTA_FWUP_CONF structure*/
		if(pOtaFwupConf->urls[S2W_OTAFU_URL_WLAN] != NULL)
			gsn_free(pOtaFwupConf->urls[S2W_OTAFU_URL_WLAN]);
		if(pOtaFwupConf->urls[S2W_OTAFU_URL_APP1] != NULL)
			gsn_free(pOtaFwupConf->urls[S2W_OTAFU_URL_APP1]);
		if(pOtaFwupConf->urls[S2W_OTAFU_URL_APP2] != NULL)
			gsn_free(pOtaFwupConf->urls[S2W_OTAFU_URL_APP2]);
		if(pOtaFwupConf->urls[S2W_OTAFU_URL_WEB] != NULL)
			gsn_free(pOtaFwupConf->urls[S2W_OTAFU_URL_WEB]);
#ifdef GS1500M
		if(pOtaFwupConf->urls[S2W_OTAFU_URL_MAC] != NULL)
					gsn_free(pOtaFwupConf->urls[S2W_OTAFU_URL_MAC]);
#endif
		pOtaFwupConf->urls[S2W_OTAFU_URL_WLAN] = pWlan;
		pOtaFwupConf->urls[S2W_OTAFU_URL_APP1] = pApp0;
		pOtaFwupConf->urls[S2W_OTAFU_URL_APP2] = pApp1;
		pOtaFwupConf->urls[S2W_OTAFU_URL_WEB] = pWebImage;
#ifdef GS1500M
        pOtaFwupConf->urls[S2W_OTAFU_URL_MAC] = pMac;
#endif

		/* TODO copying versions */
		gsn_free(pVer);
		gsn_free(pNewVer);
	}
	gsn_free(pHttpRxDataBuf);
	GsnHttp_Close(httpsConn);
	return GSN_SUCCESS;
}
#endif
#endif

#endif


