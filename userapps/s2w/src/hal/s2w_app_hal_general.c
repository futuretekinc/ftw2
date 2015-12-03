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
* $RCSfile: s2w_app_hal_general.c,v $
*
* Description : s2w GEPS interface file
******************************************************************/


/*****************************************************************
  * File Inclusions
  *****************************************************************/


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
#include "hal/s2w_cert_mgmt.h"
#include "fs/api/api_safe.h"
#include "fs/safe-flash/nor/flashdrv.h"
#include "hal/s2w_fs_if.h"
#include "main/gsn_br_flashldr.h"
#include "hal/s2w_config.h"
#include "web_prov\s2w_web_prov.h"
#include "app_rtc_mem.h"
#include "hal/s2w_net.h"
#include "modules/pwr_mgmt/gsn_pwr_mgmt.h"
#include "ext_app/app_ext_flash.h"
#include "parser/s2w_command.h"


/**
 ******************************************************************************
 * @ingroup AppResourceConfig
 * @brief Thread priority.
 *    These MACRO defines the priority of all the thread used in the system.
******************************************************************************/


#define S2W_SUCCESS     0
#define S2W_FAILURE     1

#define S2W_SPI_FS_CLK_HSRC 1
#define S2W_SPI_FS_CLK_PLL  0
#define S2W_SPI_HOST_WAKEUP_GPIO_BITMAP 0x2000000000
#define S2W_SPI_HOST_WAKEUP_GPIO_NUM    37
//PRIVATE GSN_CLK_CTL_CTX_T gsnBrClkCtlCtx1;

#ifdef S2W_DHCP_SERVER_ENABLE
extern UINT8 dhcpServerFlags;
#endif
/*****************************************************************************
      Private Variables
  ****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief Boot reason.
 *
 *    enumeration containing the reason for the latest SOC boot.
 *****************************************************************************/


extern UINT8 s2wSerialInputTaskStack[APP_CFG_SERIALINPUT_STACK_SIZE];

/* Semaphore to protect against concurrent UART write and putchar calls
 */
PRIVATE GSN_OSAL_SEM_T stUartWriteSemaphore;
PRIVATE GSN_OSAL_SEM_T stUartWriteSemaphore1;


/* Semaphore to wait for scan completion
 */

GSN_OSAL_SEM_T stScanSemaphore;

/* Semaphore to wait for disassociation completion
 */
PRIVATE GSN_OSAL_SEM_T stDisassocSemaphore;

//PRIVATE UINT32 fwflag =0;

GSN_OSAL_SEM_T stbyDelaySemaphore;

//PRIVATE GSN_CLK_CTL_CTX_T s2wClkCtlCtx;
/* Semaphore to prevent mixing of command response and
   incomming data
 */
PUBLIC GSN_OSAL_SEM_T s2wSyncSemID;
PUBLIC GSN_OSAL_SEM_T s2wSyncSemID1;
GSN_NOTIFICATION_FUNC_T s2wappMainTaskNotifier;

extern S2W_PROFILE_PARAMS_T profile_params;
extern S2W_LINK_STATE_T s2wLinkState ;
extern S2W_WLANINFO_T current_wlan_info;
extern VOID GsnHeIf_DriverSuspend();
extern PUBLIC GSN_STATUS
GsnWdd_KeepAliveTimeOutSet(GSN_WDD_CTX_T *pWdd, UINT8 timeOut);


GSN_SOFT_TMR_T  appDeepSleepTimer;

UINT8 AppS2wHal_MacAddrGet(UINT8* macAddr);
S2W_SERIAL_PORT_ID_T
AppS2w_SelectSerialDeviceId(APP_MAIN_CTX_T *pAppCtx);
S2W_SERIAL_PORT_ID_T
AppS2w_SelectSerialDeviceId1(APP_MAIN_CTX_T *pAppCtx);
void s2wUart_Config(GSN_UART_CONFIG_T * config);
VOID AppS2w_GpioWkUpDisable();

VOID
App_WpaSupplicantInit(APP_MAIN_CTX_T * pAppCtx);

#ifdef S2W_DUAL_INTERFACE_SUPPORT
PUBLIC UINT8
AppS2w_SerialPortInit2();
PUBLIC VOID
AppS2wHal_SpiFsNCharPut1(const VOID *buf,UINT32 len);
#endif

VOID AppS2w_SetWlanDfltParams(UINT8 profileNum);

VOID
App_InterfaceStart(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);

VOID
App_DefaultIfInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);

VOID
AppS2w_WlanRespTmrCb(VOID * context,GSN_SOFT_TMR_HANDLE_T timerHandle);
LONG64  APP_S2W_SPI_WAKEUP_GPIO_BITMAP = 0x800000000;

/*****************************************************************************
  *  Public Variables
  ****************************************************************************/

/* application context
 */
APP_MAIN_CTX_T *s2wappMainTaskCtxt;

/* Application Buffer to provide to UART open or SPI open
*/

#ifdef S2W_SDIO_ENABLE
extern UINT8 s2wSerialBuf[16384];
#else
extern UINT8 s2wSerialBuf[4096];
#endif

#ifdef S2W_DUAL_INTERFACE_SUPPORT
#ifdef S2W_SDIO_ENABLE_1
extern UINT8 s2wSerialBuf1[16384];
#else
extern UINT8 s2wSerialBuf1[4096];
#endif
#endif
GSN_OSAL_SEM_T s2wL2L3ConnectSemaphore;
#ifdef S2W_RF_TEST
GSN_OSAL_SEM_T s2wWlanOpSyncSem;
#endif

GSN_CLK_CTL_CM3_CLK_CFG_T cm3ClkCfg;		//app cm3 clk config 
extern GSN_EXTFLASH_CTX_T gsExtFlashCtxFs;
extern UINT32 S2wL3Wait;
/*****************************************************************************
  *  Private Functions
  *****************************************************************************/

extern UINT8 L3ConnectStatus;

PRIVATE void
AppS2wHal_SerialInputTask( UINT32 u32Address );
#ifdef S2W_DUAL_INTERFACE_SUPPORT
PRIVATE void
AppS2wHal_s2wSerial2InputTask( UINT32 u32Address );
#endif
extern PUBLIC UINT8
AppS2w_SerialPortInit(APP_MAIN_CTX_T *pAppCtx);
extern S2W_PROFILE_T s2wCurrent;
__no_init S2W_FLASH_PARAMS_T FlashParams;
PUBLIC VOID
App_ConnectCb(VOID *ctx, GSN_STATUS status);

VOID
App_FsInit();

/*Initialse File system for External Flash*/
VOID
App_ExtFlash_FsInit();

/* Serial port(UART/SPI) handler  for s2w application
     */

extern S2W_SERIAL_PORT_HANDLE_T  s2wSerialPortHandle;
#ifdef S2W_DUAL_INTERFACE_SUPPORT
extern S2W_SERIAL_PORT_HANDLE_T  s2wSerialPortHandle1;
#endif
PUBLIC VOID
AppS2wHal_SpiNCharPut(const VOID *buf,UINT32 len);
PUBLIC VOID
AppS2wHal_SpiNCharPut1(const VOID *buf,UINT32 len);

/* GPIO bit mask used for SPI host wake-up signal -gpio 37*/
LONG64  APP_S2W_SPI_HOST_WAKEUP_GPIO_BITMAP = 0x2000000000;

GSN_OSAL_SEM_T spiWriteLock;


PUBLIC VOID
S2wApp_WebserverStack_Free(UINT8* stackPtr);

PUBLIC VOID 
AppS2wHal_Cm3ClkCfg();

GSN_OSAL_SEM_T sdioWriteLock;

extern PUBLIC UINT8 *pS2wHttpdTaskStack;


/* SPI_HI APIS  */

PUBLIC  UINT8
AppS2wHal_SpiFsCharGet(UINT8 *rxData);

PUBLIC VOID
AppS2wHal_SpiFsCharPut(UINT8 ch);

PUBLIC VOID
AppS2wHal_SpiFsNCharGet(UINT8 *ch, UINT16 dataLen);

PUBLIC VOID
AppS2wHal_SpiFsNCharPut(const VOID *buf,UINT32 len);

VOID
App_WaitOnLock(VOID);

VOID
GsnHeIf_TrangGetSeed( UINT8* pBuf );

GSN_OSAL_SEM_T spiFsWriteLock;
GSN_OSAL_SEM_T spiFsWriteBuffLock;

extern GSN_SOFT_TMR_T sysTickTmr;
extern GSN_SOFT_TMR_T *pSysTickTmrHndl;

VOID 
App_SysTickCb(VOID* context, GSN_SOFT_TMR_HANDLE_T  timerHandle);

/*****************************************************************************
  *  Public Functions
  *****************************************************************************/

PUBLIC VOID
s2wUart_Config(GSN_UART_CONFIG_T * config)
{
    UINT32 baudrate;
    GSN_UART_PARITYBIT_T parity;

    switch (s2wCurrent.serialPortConf.conf.uart.baudrate)
    {
        case 9600:
            baudrate = GSN_UART_BAUDRATE_9K6;
            break;
        case 19200:
            baudrate = GSN_UART_BAUDRATE_19K2;
            break;
        case 38400:
            baudrate = GSN_UART_BAUDRATE_38K4;
            break;
        case 57600:
            baudrate = GSN_UART_BAUDRATE_57K6;
            break;
        case 115200:
            baudrate = GSN_UART_BAUDRATE_115K2;
            break;
        case 230400:
            baudrate = GSN_UART_BAUDRATE_230K4;
            break;
        case 460800:
            baudrate = GSN_UART_BAUDRATE_460K8;
            break;
        case 921600:
            baudrate = GSN_UART_BAUDRATE_921K6;
            break;
        default:
            baudrate = GSN_UART_BAUDRATE_9K6;
    }
    config->eBaudRate = (GSN_UART_BAUDRATE_T)baudrate;
    /* set the bits per char of uart
     */
    config->eCharFormat = (GSN_UART_CHARFORMAT_T) s2wCurrent.serialPortConf.conf.uart.bits;

    config->eStopBits = (GSN_UART_STOPBITS_T)s2wCurrent.serialPortConf.conf.uart.stop;


    switch (s2wCurrent.serialPortConf.conf.uart.parity)
    {
        case S2W_UARTCONF_PARITY_NONE:
            parity = GSN_UART_PARITYBIT_NONE;
            break;
        case S2W_UARTCONF_PARITY_ODD:
            parity = GSN_UART_PARITYBIT_ODD;
            break;
        case S2W_UARTCONF_PARITY_EVEN:
            parity = GSN_UART_PARITYBIT_EVEN;
            break;
        default:
           parity = GSN_UART_PARITYBIT_NONE;
    }
    config->eParityBits = parity;

    config->HwFlowSupport = (s2wCurrent.serialPortConf.conf.uart.hardflow ?
                           GSN_UART_HW_SUPPORT: GSN_UART_HW_NO_SUPPORT);
    config->swFlowSupport = s2wCurrent.serialPortConf.conf.uart.softflow ? 
                           GSN_UART_SWFLOW_SUPPORT: GSN_UART_SWFLOW_NO_SUPPORT;
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w uart charactor read function.
 *    This function read a char from the s2w uart.
 * @param ch - IN the address to which the char should store.
 * @retval UINT8 - the number of char read.
 ******************************************************************/
PUBLIC UINT8
AppS2wHal_UartCharGet(UINT8 *ch)
{
    /* Don't need a semaphore since this is called from only one thread
     */
    return GsnUart_Read(&s2wSerialPortHandle.uartHandle, ch, 1, 1, NULL,NULL);
}
#ifdef S2W_DUAL_INTERFACE_SUPPORT
PUBLIC UINT8
AppS2wHal_UartCharGet1(UINT8 *ch)
{
    /* Don't need a semaphore since this is called from only one thread
     */
    return GsnUart_Read(&s2wSerialPortHandle1.uartHandle, ch, 1, 1, NULL,NULL);
}


PUBLIC GSN_OSAL_QUEUE_T s2wSerialInputTaskQueue;
UINT32 s2wSerialInputTaskQueueBuffer[ 16 ];

PUBLIC GSN_OSAL_QUEUE_T s2wSerial2InputTaskQueue;
UINT32 s2wSerial2InputTaskBuffer[ 16 ];

VOID  AppS2wHal_UartCharGetNBCB( VOID* ctx,UINT32 numbers  )
{
	UINT32 msg =0;
    // post a message
    GsnOsal_QueuePut(&s2wSerialInputTaskQueue, (UINT8 *)&msg);

}




PUBLIC UINT8
AppS2wHal_UartCharGetNB(UINT8 *ch)
{
    /* Don't need a semaphore since this is called from only one thread
     */
    return GsnUart_Read(&s2wSerialPortHandle.uartHandle, ch, 1, 0, AppS2wHal_UartCharGetNBCB,s2wappMainTaskCtxt);
}


VOID  AppS2wHal_UartCharGetNB1CB( VOID* ctx,UINT32 numbers  )
{
	UINT32 msg =0;
    // post a message
    GsnOsal_QueuePut(&s2wSerial2InputTaskQueue, (UINT8 *)&msg);

}




PUBLIC UINT8
AppS2wHal_UartCharGetNB1(UINT8 *ch)
{
    /* Don't need a semaphore since this is called from only one thread
     */
    return GsnUart_Read(&s2wSerialPortHandle1.uartHandle, ch, 1, 0, AppS2wHal_UartCharGetNB1CB,s2wappMainTaskCtxt);
}

#endif

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w uart string write function.
 *    This function write a string of data to the s2w uart.
 * @param buf - IN the address of the string to send
 *.@param buf - IN the length of the string to send.
 * @retval VOID - None.
 ******************************************************************/
PUBLIC VOID
AppS2wHal_UartWrite(const VOID *buf, UINT32 len)
{

    GsnOsal_SemAcquire ( &stUartWriteSemaphore,
               GSN_OSAL_WAIT_FOREVER );

    GsnUart_Write(&s2wSerialPortHandle.uartHandle, (UINT8 *)buf, len, NULL,NULL);
    GsnOsal_SemRelease(&stUartWriteSemaphore);
}

#ifdef S2W_DUAL_INTERFACE_SUPPORT
PUBLIC VOID
AppS2wHal_UartWrite1(const VOID *buf, UINT32 len)
{

    GsnOsal_SemAcquire ( &stUartWriteSemaphore1,
               GSN_OSAL_WAIT_FOREVER );

    GsnUart_Write(&s2wSerialPortHandle1.uartHandle, (UINT8 *)buf, len, NULL,NULL);
    GsnOsal_SemRelease(&stUartWriteSemaphore1);
}
#endif

PUBLIC BOOL
S2wUart_TxStatusGet()
{
    return GsnUart_TxStatusGet(&s2wSerialPortHandle.uartHandle);
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w uart charactor write function.
 *    This function write a char to the s2w uart.
 * @param ch - IN the char which to be written.
 * @retval VOID - None.
 ******************************************************************/
PUBLIC VOID
AppS2wHal_UartCharPut(UINT8 ch)
{
    GsnOsal_SemAcquire ( &stUartWriteSemaphore,
                         GSN_OSAL_WAIT_FOREVER );

    GsnUart_Write(&s2wSerialPortHandle.uartHandle, &ch, 1, NULL,NULL);

    GsnOsal_SemRelease(&stUartWriteSemaphore);
}
#ifdef S2W_DUAL_INTERFACE_SUPPORT
 /******************************************************************/
PUBLIC VOID
AppS2wHal_UartCharPut1(UINT8 ch)
{
    GsnOsal_SemAcquire ( &stUartWriteSemaphore1,
                         GSN_OSAL_WAIT_FOREVER );

    GsnUart_Write(&s2wSerialPortHandle1.uartHandle, &ch, 1, NULL,NULL);

    GsnOsal_SemRelease(&stUartWriteSemaphore1);
}

#endif
PUBLIC VOID
AppS2wHal_UartCharNGet(UINT8 *ch, UINT16 dataLen)
{
   UINT32 dataLeft = 0;

   while(dataLen)
   {
      GsnUart_Read(&s2wSerialPortHandle.uartHandle, ch,
         (dataLeft = (dataLen >=500?500:dataLen)), 1, NULL,NULL);
      ch += dataLeft;
      dataLen -= dataLeft;
    }
}
#ifdef S2W_DUAL_INTERFACE_SUPPORT
PUBLIC VOID
AppS2wHal_UartCharNGet1(UINT8 *ch, UINT16 dataLen)
{
   UINT32 dataLeft = 0;

   while(dataLen)
   {
      GsnUart_Read(&s2wSerialPortHandle1.uartHandle, ch,
         (dataLeft = (dataLen >=500?500:dataLen)), 1, NULL,NULL);
      ch += dataLeft;
      dataLen -= dataLeft;
    }
}
#endif
VOID S2w_PutChar(UINT8 ch)
{
    s2wappMainTaskCtxt->s2wPutCharFn(ch);
}

VOID AppS2wHal_CharNPut(const void *buf, UINT32 len)
{
    s2wappMainTaskCtxt->s2wWriteFn(buf,len);
}


VOID AppS2wHal_CharNGet(UINT8*buf, UINT32 len)
{
    s2wappMainTaskCtxt->s2wGetNCharFn(buf,len);
}


UINT8 AppS2wHal_CharGet(UINT8*buf)
{
    return s2wappMainTaskCtxt->s2wGetCharFn(buf);
}

#ifdef S2W_DUAL_INTERFACE_SUPPORT
VOID S2w_PutChar1(UINT8 ch)
{
    s2wappMainTaskCtxt->s2wPutCharFn1(ch);
}
VOID AppS2wHal_CharNPut1(const void *buf, UINT32 len)
{

     s2wappMainTaskCtxt->s2wWriteFn1(buf,len);
}
VOID AppS2wHal_CharNGet1(UINT8*buf, UINT32 len)
{
	s2wappMainTaskCtxt->s2wGetNCharFn1(buf,len);

}
UINT8 AppS2wHal_CharGet1(UINT8*buf)
{
    return s2wappMainTaskCtxt->s2wGetCharFn1(buf);
}
#endif
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w SPI port charactor read function.
 *    This function read a char from the s2w  SPI port.
 * @param ch - IN the address to which the char should store.
 * @retval UINT8 - 0 - No charcter available to read
 *                         1  - One char read successfully
 ******************************************************************/
PUBLIC  UINT8
AppS2wHal_SpiCharGet(UINT8 *rxData)
{
	 GSN_SPI_TXRXCHANNEL_T txCh;
     txCh.buffer.pData = 	(UINT8*)rxData;
      txCh.buffer.size = 1;
      txCh.numberOfBytes = 1;
     txCh.funcCB       = NULL;
     txCh.contextCB    = NULL;
     GsnSpi_SlaveRead(&(s2wSerialPortHandle.spiHandle),&txCh);
   return 1;
}
#ifdef S2W_DUAL_INTERFACE_SUPPORT
PUBLIC  UINT8
AppS2wHal_SpiCharGet1(UINT8 *rxData)
{
	 GSN_SPI_TXRXCHANNEL_T txCh;
     txCh.buffer.pData = 	(UINT8*)rxData;
      txCh.buffer.size = 1;
      txCh.numberOfBytes = 0;
     txCh.funcCB       = NULL;
     txCh.contextCB    = NULL;
     GsnSpi_SlaveRead(&(s2wSerialPortHandle1.spiHandle),&txCh);
   return 1;
}

// non blocking
VOID  AppS2wHal_SpiCharGetNB1CB( VOID* ctx,UINT32 numbers  )
{
	UINT32 msg =0;
    // post a message
    GsnOsal_QueuePut(&s2wSerial2InputTaskQueue, (UINT8 *)&msg);

}

PUBLIC  UINT8
AppS2wHal_SpiCharGetNB1(UINT8 *rxData)
{
	 GSN_SPI_TXRXCHANNEL_T txCh;
     txCh.buffer.pData = 	(UINT8*)rxData;
     txCh.buffer.size = 1;
     txCh.numberOfBytes = 0;
     txCh.funcCB       = AppS2wHal_SpiCharGetNB1CB;
     txCh.contextCB    = s2wappMainTaskCtxt;
	 GsnSpi_SlaveRead(&(s2wSerialPortHandle1.spiHandle),
              &txCh);
    return 1;
}
#endif
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w SPI charactor write function.
 *    This function write a char to the s2w SPI.
 * @param ch - IN the char which to be written.
 * @retval VOID - None.
 ******************************************************************/
PUBLIC VOID
AppS2wHal_SpiCharPut(UINT8 ch)
{
   AppS2wHal_SpiNCharPut(&ch,1);
}
#ifdef S2W_DUAL_INTERFACE_SUPPORT
PUBLIC VOID
AppS2wHal_SpiCharPut1(UINT8 ch)
{
   AppS2wHal_SpiNCharPut1(&ch,1);
}
#endif

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w SPI port bulk read function.
 *    This function read a char from the s2w  SPI port.
 * @param ch - IN the address to which the char should store.
 * @param dataLen - IN  no of bytes to read
 * @retval None
 ******************************************************************/

PUBLIC VOID
AppS2wHal_SpiNCharGet(UINT8 *ch, UINT16 dataLen)
{
 	 GSN_SPI_TXRXCHANNEL_T txCh;
 	 UINT32 dataLeft=0;
      txCh.funcCB       = NULL;
      txCh.contextCB    = NULL;
     while(dataLen)
     {
		 ch += dataLeft;
		 txCh.buffer.pData = 	(UINT8*)ch;
		 dataLeft = (dataLen >=300?300:dataLen);

         txCh.buffer.size = dataLeft;
         txCh.numberOfBytes = dataLeft;
     GsnSpi_SlaveRead(&(s2wSerialPortHandle.spiHandle),&txCh);
         dataLen -= dataLeft;
	 }

}
#ifdef S2W_DUAL_INTERFACE_SUPPORT
PUBLIC VOID
AppS2wHal_SpiNCharGet1(UINT8 *ch, UINT16 dataLen)
{
 	 GSN_SPI_TXRXCHANNEL_T txCh;
      txCh.buffer.pData = 	(UINT8*)ch;
      txCh.buffer.size = dataLen;
      txCh.numberOfBytes = dataLen;
      txCh.funcCB       = NULL;
      txCh.contextCB    = NULL;
     GsnSpi_SlaveRead(&(s2wSerialPortHandle1.spiHandle),&txCh);
}
#endif
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w SPI  write function.
 *    This function write a string of data to the s2w SPI port.
 * @param buf - IN the address of the string to send
 *.@param buf - IN the length of the string to send.
 * @retval VOID - None.
 *
 ******************************************************************/
PUBLIC VOID
AppS2wHal_SpiNCharPut(const VOID *buf,UINT32 len)
{
   GSN_SPI_TXRXCHANNEL_T spiRW;

   GsnOsal_SemAcquire ( &spiWriteLock,
                  GSN_OSAL_WAIT_FOREVER );

   spiRW.funcCB       = NULL;
   spiRW.contextCB    = NULL;
   spiRW.buffer.pData = (UINT8*)buf;
   spiRW.buffer.size  = len;

   // make the data ready gpio high
   GsnGpio_OutIndvidualSet(APP_S2W_SPI_HOST_WAKEUP_GPIO_BITMAP);
   if(GSN_SUCCESS!=GsnSpi_SlaveWrite(&s2wSerialPortHandle.spiHandle,&spiRW))
   {//TBD: This should not happen.. Log the error

   }
   GsnGpio_OutClear(APP_S2W_SPI_HOST_WAKEUP_GPIO_BITMAP);
   GsnOsal_SemRelease(&spiWriteLock);

}
#ifdef S2W_DUAL_INTERFACE_SUPPORT
PUBLIC VOID
AppS2wHal_SpiNCharPut1(const VOID *buf,UINT32 len)
{
   GSN_SPI_TXRXCHANNEL_T spiRW;

   GsnOsal_SemAcquire ( &spiWriteLock,
                  GSN_OSAL_WAIT_FOREVER );

   spiRW.funcCB       = NULL;
   spiRW.contextCB    = NULL;
   spiRW.buffer.pData = (UINT8*)buf;
   spiRW.buffer.size  = len;

   // make the data ready gpio high
   GsnGpio_OutIndvidualSet(APP_S2W_SPI_HOST_WAKEUP_GPIO_BITMAP);
   if(GSN_SUCCESS!=GsnSpi_SlaveWrite(&s2wSerialPortHandle1.spiHandle,&spiRW))
   {//TBD: This should not happen.. Log the error

   }
   GsnGpio_OutClear(APP_S2W_SPI_HOST_WAKEUP_GPIO_BITMAP);
   GsnOsal_SemRelease(&spiWriteLock);

}

#endif


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w SPI port charactor read function.
 *    This function read a char from the s2w  SPI port.
 * @param ch - IN the address to which the char should store.
 * @retval UINT8 - 0 - No charcter available to read
 *                         1  - One char read successfully
 ******************************************************************/
PUBLIC  UINT8
AppS2wHal_SdioCharGet(UINT8 *rxData)
{
	GsnSdio_Read(&(s2wSerialPortHandle.sdioHandle),
              rxData,1,1,
              NULL,NULL);
    return 1;
}
#ifdef S2W_DUAL_INTERFACE_SUPPORT
PUBLIC  UINT8
AppS2wHal_SdioCharGet1(UINT8 *rxData)
{
	GsnSdio_Read(&(s2wSerialPortHandle1.sdioHandle),
              rxData,1,1,
              NULL,NULL);
    return 1;
}

// non blocking
VOID  AppS2wHal_SdioCharGetNB1CB( VOID* ctx,UINT32 numbers  )
{
	UINT32 msg =0;
    // post a message
    GsnOsal_QueuePut(&s2wSerial2InputTaskQueue, (UINT8 *)&msg);

}

PUBLIC  UINT8
AppS2wHal_SdioCharGetNB1(UINT8 *rxData)
{
	GsnSdio_Read(&(s2wSerialPortHandle1.sdioHandle),
              rxData,1,0,
              AppS2wHal_SdioCharGetNB1CB,s2wappMainTaskCtxt);
    return 1;
}

#endif

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w SPI charactor write function.
 *    This function write a char to the s2w SPI.
 * @param ch - IN the char which to be written.
 * @retval VOID - None.
 ******************************************************************/
PUBLIC VOID
AppS2wHal_SdioCharPut(UINT8 ch)
{

   GsnOsal_SemAcquire ( &sdioWriteLock,
                  GSN_OSAL_WAIT_FOREVER );
   GsnSdio_Write(&(s2wSerialPortHandle.sdioHandle),
                &ch,1,
                NULL, NULL);
   GsnOsal_SemRelease(&sdioWriteLock);
}
#ifdef S2W_DUAL_INTERFACE_SUPPORT
PUBLIC VOID
AppS2wHal_SdioCharPut1(UINT8 ch)
{

   GsnOsal_SemAcquire ( &sdioWriteLock,
                  GSN_OSAL_WAIT_FOREVER );
   GsnSdio_Write(&(s2wSerialPortHandle1.sdioHandle),
                &ch,1,
                NULL, NULL);
   GsnOsal_SemRelease(&sdioWriteLock);
}
#endif

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w SPI port bulk read function.
 *    This function read a char from the s2w  SPI port.
 * @param ch - IN the address to which the char should store.
 * @param dataLen - IN  no of bytes to read
 * @retval None
 ******************************************************************/

PUBLIC VOID
AppS2wHal_SdioNCharGet(UINT8 *rxData, UINT16 dataLen)
{

     GsnSdio_Read(&(s2wSerialPortHandle.sdioHandle),
              rxData,dataLen,1,
              NULL,NULL);
}

#ifdef S2W_DUAL_INTERFACE_SUPPORT
PUBLIC VOID
AppS2wHal_SdioNCharGet1(UINT8 *rxData, UINT16 dataLen)
{

     GsnSdio_Read(&(s2wSerialPortHandle1.sdioHandle),
              rxData,dataLen,1,
              NULL,NULL);
}

#endif
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w SPI  write function.
 *    This function write a string of data to the s2w SPI port.
 * @param buf - IN the address of the string to send
 *.@param buf - IN the length of the string to send.
 * @retval VOID - None.
 *
 ******************************************************************/
PUBLIC VOID
AppS2wHal_SdioNCharPut(const VOID *buf,UINT32 len)
{
   GsnOsal_SemAcquire ( &sdioWriteLock,
                  GSN_OSAL_WAIT_FOREVER );

   GsnSdio_Write(&(s2wSerialPortHandle.sdioHandle),
                (UINT8*)buf,len,

                NULL, NULL);



   GsnOsal_SemRelease(&sdioWriteLock);

}

#ifdef S2W_DUAL_INTERFACE_SUPPORT
PUBLIC VOID
AppS2wHal_SdioNCharPut1(const VOID *buf,UINT32 len)
{
   GsnOsal_SemAcquire ( &sdioWriteLock,
                  GSN_OSAL_WAIT_FOREVER );

   GsnSdio_Write(&(s2wSerialPortHandle1.sdioHandle),
                (UINT8*)buf,len,

                NULL, NULL);



   GsnOsal_SemRelease(&sdioWriteLock);

}
#endif

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w SPI_HI port charactor read function in .
 *    This function read a char from the s2w  SPI port.
 * @param ch - IN the address to which the char should store.
 * @retval UINT8 - 0 - No charcter available to read
 *                         1  - One char read successfully
 ******************************************************************/
PUBLIC  UINT8
AppS2wHal_SpiFsCharGet(UINT8 *rxData)
{
     GSN_SPI_FS_TXRXCHANNEL_T txCh;
     txCh.buffer.pData = 	(UINT8*)rxData;
     txCh.buffer.size = 1;
     txCh.numberOfBytes = 1;
     txCh.funcCB       = NULL;
     txCh.contextCB    = NULL;
     GsnSpiFS_SlaveRead(&(s2wSerialPortHandle.spiFsHandle),&txCh);
     return 1;
}

#ifdef S2W_DUAL_INTERFACE_SUPPORT
PUBLIC  UINT8
AppS2wHal_SpiFsCharGet1(UINT8 *rxData)
{
     GSN_SPI_FS_TXRXCHANNEL_T txCh;
     txCh.buffer.pData = 	(UINT8*)rxData;
     txCh.buffer.size = 1;
     txCh.numberOfBytes = 1;
     txCh.funcCB       = NULL;
     txCh.contextCB    = NULL;
     GsnSpiFS_SlaveRead(&(s2wSerialPortHandle1.spiFsHandle),&txCh);
     return 1;
}

// non blocking
VOID  AppS2wHal_SpiFsCharGetNB1CB( VOID* ctx,UINT32 numbers  )
{
	UINT32 msg =0;
    // post a message
    GsnOsal_QueuePut(&s2wSerial2InputTaskQueue, (UINT8 *)&msg);

}

PUBLIC  UINT8
AppS2wHal_SpiFsCharGetNB1(UINT8 *rxData)
{
     GSN_SPI_FS_TXRXCHANNEL_T txCh;
     txCh.buffer.pData = 	(UINT8*)rxData;
     txCh.buffer.size = 1;
     txCh.numberOfBytes = 0;
     txCh.funcCB       = AppS2wHal_SpiFsCharGetNB1CB;
     txCh.contextCB    = s2wappMainTaskCtxt;
     GsnSpiFS_SlaveRead(&(s2wSerialPortHandle1.spiFsHandle),
              &txCh);
    return 1;
}

#endif

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w SPI charactor write function.
 *    This function write a char to the s2w SPI.
 * @param ch - IN the char which to be written.
 * @retval VOID - None.
 ******************************************************************/
PUBLIC VOID
AppS2wHal_SpiFsCharPut(UINT8 ch)
{
  // GsnOsal_SemAcquire ( &spiFsWriteLock,GSN_OSAL_WAIT_FOREVER );
   
   AppS2wHal_SpiFsNCharPut(&ch,1);
   
 //  GsnOsal_SemRelease(&spiFsWriteLock);
}

#ifdef S2W_DUAL_INTERFACE_SUPPORT
PUBLIC VOID
AppS2wHal_SpiFsCharPut1(UINT8 ch)
{
  // GsnOsal_SemAcquire ( &spiFsWriteLock,GSN_OSAL_WAIT_FOREVER );

   AppS2wHal_SpiFsNCharPut1(&ch,1);

 //  GsnOsal_SemRelease(&spiFsWriteLock);
}
#endif
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w SPI port bulk read function.
 *    This function read a char from the s2w  SPI port.
 * @param ch - IN the address to which the char should store.
 * @param dataLen - IN  no of bytes to read
 * @retval None
 ******************************************************************/

PUBLIC VOID
AppS2wHal_SpiFsNCharGet(UINT8 *ch, UINT16 dataLen)
{
      GSN_SPI_FS_TXRXCHANNEL_T txCh;
      txCh.buffer.pData = 	(UINT8*)ch;
      txCh.numberOfBytes = dataLen;
      txCh.buffer.size   = dataLen;
      txCh.funcCB       = NULL;
      txCh.contextCB    = NULL;
      GsnSpiFS_SlaveRead(&(s2wSerialPortHandle.spiFsHandle),&txCh);
}

#ifdef S2W_DUAL_INTERFACE_SUPPORT
PUBLIC VOID
AppS2wHal_SpiFsNCharGet1(UINT8 *ch, UINT16 dataLen)
{
      GSN_SPI_FS_TXRXCHANNEL_T txCh;
      txCh.buffer.pData = 	(UINT8*)ch;
      txCh.numberOfBytes = dataLen;
      txCh.buffer.size   = dataLen;
      txCh.funcCB       = NULL;
      txCh.contextCB    = NULL;
      GsnSpiFS_SlaveRead(&(s2wSerialPortHandle1.spiFsHandle),&txCh);
}
#endif

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w SPI  write function.
 *    This function write a string of data to the s2w SPI port.
 * @param buf - IN the address of the string to send
 *.@param buf - IN the length of the string to send.
 * @retval VOID - None.
 *
 ******************************************************************/
#define S2W_MAX_SPI_DMA_BUFF_SIZE (1518 + 8)
UINT8 s2wSpiFsFlushbuff[S2W_MAX_SPI_DMA_BUFF_SIZE ];
UINT32 s2wSpiFsFlushbuffIndex =0;

#if 1

VOID s2wSpiFs_Flush()
{
	 GSN_SPI_FS_TXRXCHANNEL_T spiRW;
	 GsnOsal_SemAcquire ( &spiFsWriteBuffLock,
                  GSN_OSAL_WAIT_FOREVER );

     spiRW.funcCB       = NULL;
     spiRW.contextCB    = NULL;
     spiRW.buffer.pData = (UINT8*)s2wSpiFsFlushbuff;
     spiRW.buffer.size  = s2wSpiFsFlushbuffIndex;

     GsnSpiFS_SlaveWrite(&s2wSerialPortHandle.spiFsHandle,&spiRW);
     s2wSpiFsFlushbuffIndex = 0;
     GsnOsal_SemRelease(&spiFsWriteBuffLock);

}


PUBLIC VOID
AppS2wHal_SpiFsNCharPut(const VOID *buf,UINT32 len)
{
   UINT32 reLen=0,len1 =0;

   GsnOsal_SemAcquire ( &spiFsWriteBuffLock,
                  GSN_OSAL_WAIT_FOREVER );
   INT8* buff = (INT8*)buf;
   if((s2wSpiFsFlushbuffIndex + len) < S2W_MAX_SPI_DMA_BUFF_SIZE)
   {
       // store to buff
       memcpy(&s2wSpiFsFlushbuff[s2wSpiFsFlushbuffIndex],buf,len);
       s2wSpiFsFlushbuffIndex += len;
   }
   else
   {
	   reLen = S2W_MAX_SPI_DMA_BUFF_SIZE - s2wSpiFsFlushbuffIndex;
	   if(reLen) // still space available in buff copy that much
	   {
		  len1 = len < reLen?len:reLen;
          memcpy(&s2wSpiFsFlushbuff[s2wSpiFsFlushbuffIndex],buf,len1);
          s2wSpiFsFlushbuffIndex += len1;
	   }
	   // flush out first and store
	   //s2wSpiFs_Flush();
	   GSN_SPI_FS_TXRXCHANNEL_T spiRW;
       spiRW.funcCB       = NULL;
       spiRW.contextCB    = NULL;
       spiRW.buffer.pData = (UINT8*)s2wSpiFsFlushbuff;
       spiRW.buffer.size  = s2wSpiFsFlushbuffIndex;

       GsnSpiFS_SlaveWrite(&s2wSerialPortHandle.spiFsHandle,&spiRW);
       s2wSpiFsFlushbuffIndex = 0;
	   if(len-len1)
	   {
              buff += len1;
	      memcpy(&s2wSpiFsFlushbuff[s2wSpiFsFlushbuffIndex],buff,len-len1);
              s2wSpiFsFlushbuffIndex += (len - len1);
	   }

   }

   GsnOsal_SemRelease(&spiFsWriteBuffLock);

}


#else

PUBLIC VOID
AppS2wHal_SpiFsNCharPut(const VOID *buf,UINT32 len)
{
   GSN_SPI_FS_TXRXCHANNEL_T spiRW;

   GsnOsal_SemAcquire ( &spiFsWriteLock,
                  GSN_OSAL_WAIT_FOREVER );

   spiRW.funcCB       = NULL;
   spiRW.contextCB    = NULL;
   spiRW.buffer.pData = (UINT8*)buf;
   spiRW.buffer.size  = len;

   GsnSpiFS_SlaveWrite(&s2wSerialPortHandle.spiFsHandle,&spiRW);


   GsnOsal_SemRelease(&spiFsWriteLock);

}
#endif

#ifdef S2W_DUAL_INTERFACE_SUPPORT

#if 1
VOID
s2wSpiFs_Flush1()
{
	 GSN_SPI_FS_TXRXCHANNEL_T spiRW;
	 GsnOsal_SemAcquire ( &spiFsWriteBuffLock,
                  GSN_OSAL_WAIT_FOREVER );

     spiRW.funcCB       = NULL;
     spiRW.contextCB    = NULL;
     spiRW.buffer.pData = (UINT8*)s2wSpiFsFlushbuff;
     spiRW.buffer.size  = s2wSpiFsFlushbuffIndex;

     GsnSpiFS_SlaveWrite(&s2wSerialPortHandle1.spiFsHandle,&spiRW);
     s2wSpiFsFlushbuffIndex = 0;
     GsnOsal_SemRelease(&spiFsWriteBuffLock);

}


PUBLIC VOID
AppS2wHal_SpiFsNCharPut1(const VOID *buf,UINT32 len)
{
   UINT32 reLen=0,len1 =0;

   GsnOsal_SemAcquire ( &spiFsWriteBuffLock,
                  GSN_OSAL_WAIT_FOREVER );
   INT8* buff = (INT8*)buf;
   if((s2wSpiFsFlushbuffIndex + len) < S2W_MAX_SPI_DMA_BUFF_SIZE)
   {
       // store to buff
       memcpy(&s2wSpiFsFlushbuff[s2wSpiFsFlushbuffIndex],buf,len);
       s2wSpiFsFlushbuffIndex += len;
   }
   else
   {
	   reLen = S2W_MAX_SPI_DMA_BUFF_SIZE-s2wSpiFsFlushbuffIndex;
	   if(reLen)
	   {
		  len1 = len < reLen?len:reLen;
          memcpy(&s2wSpiFsFlushbuff[s2wSpiFsFlushbuffIndex],buf,len1);
          s2wSpiFsFlushbuffIndex =+ len1;
	   }
	   // flush out first and store
	   //s2wSpiFs_Flush1();
	   GSN_SPI_FS_TXRXCHANNEL_T spiRW;
       spiRW.funcCB       = NULL;
       spiRW.contextCB    = NULL;
       spiRW.buffer.pData = (UINT8*)s2wSpiFsFlushbuff;
       spiRW.buffer.size  = s2wSpiFsFlushbuffIndex;

       GsnSpiFS_SlaveWrite(&s2wSerialPortHandle1.spiFsHandle,&spiRW);
       s2wSpiFsFlushbuffIndex = 0;
	   if(len-len1)
	   {
		   buff += len1;
	       memcpy(&s2wSpiFsFlushbuff[s2wSpiFsFlushbuffIndex],buff,len-len1);
           s2wSpiFsFlushbuffIndex += (len - len1);
	   }

   }
   GsnOsal_SemRelease(&spiFsWriteBuffLock);

}


#else


PUBLIC VOID
AppS2wHal_SpiFsNCharPut1(const VOID *buf,UINT32 len)
{
   GSN_SPI_FS_TXRXCHANNEL_T spiRW;

   GsnOsal_SemAcquire ( &spiFsWriteLock,
                  GSN_OSAL_WAIT_FOREVER );

   spiRW.funcCB       = NULL;
   spiRW.contextCB    = NULL;
   spiRW.buffer.pData = (UINT8*)buf;
   spiRW.buffer.size  = len;

   GsnSpiFS_SlaveWrite(&s2wSerialPortHandle1.spiFsHandle,&spiRW);


   GsnOsal_SemRelease(&spiFsWriteLock);

}

#endif

#endif

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w application entry function.
 *    This function creates the s2w task for serial input.
 * @param bootInfo - IN the boot information
 * @retval VOID - None.
 ******************************************************************/


PUBLIC VOID
AppS2wHal_AppEntry (UINT32 bootInfo)
{
     GsnOsal_ThreadCreate(AppS2wHal_SerialInputTask,s2wappMainTaskCtxt,
                            &s2wappMainTaskCtxt->s2wSerialTask,
                            "S2wSerialInputTask",
                            APP_CFG_SERIALINPUT_THREAD_PRIORITY,
                            s2wSerialInputTaskStack,
                            sizeof(s2wSerialInputTaskStack),
                            GSN_OSAL_THREAD_INITIAL_READY);
#ifdef S2W_DUAL_INTERFACE_SUPPORT
     // create a message queue
     GsnOsal_QueueCreate(&s2wSerialInputTaskQueue, 1,
                          (UINT8*)s2wSerialInputTaskQueueBuffer,
                          (sizeof(s2wSerialInputTaskQueueBuffer)*1));

#endif
}

PUBLIC VOID
App_ConnectCb(VOID *ctx, GSN_STATUS status)
{
	volatile static UINT32 connStatus;
	/*APP_CTX_T *pAppCtx = (APP_CTX_T *)ctx;*/
	connStatus = status;

	/*Post message to main task*/
	{
		//INT32 msg = APP_EVENT_CONNECT_SUCCESS;
                INT32 msg = 0;
		AppMainCtx_TaskNotify(msg/*, NULL*/);
	}
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w wpa-psk key compute function.
 *    This function compute the psk key from the SSID and passphrase and
 *    returns that value
 * @param wpaPsk - IN the wpa-psk paramater structure pointer.
 * @retval S2W_SUCCESS.
 ******************************************************************/

int pbkdf2_sha1(const char *passphrase, const char *ssid, size_t ssid_len,
		int iterations, unsigned char *buf, size_t buflen); 
PUBLIC UINT8
AppS2wHal_WpaPskCompute(S2W_WPAPSK_T* wpaPsk )
{
    
  
   if(pbkdf2_sha1(wpaPsk->wpaPassPhrase,wpaPsk->ssid,wpaPsk->ssidLen,4096,wpaPsk->psk,S2W_PSK_LEN) != S2W_SUCCESS)
    
    return S2W_FAILURE;

	return S2W_SUCCESS;
}

 VOID
AppS2wDissociate_Cb ( VOID *ctx, GSN_STATUS status )
{
    if(status == GSN_SUCCESS)
    {
        s2wLinkState = S2W_LINK_STATE_DISCONNECTED;
    }
    /* Disconnect success, waiting in AppS2wHal_Disassociate()
     */
    GsnOsal_SemRelease ( &stDisassocSemaphore );

}


UINT8
AppS2wHal_Disassociate(UINT8 parentTask)
   {
	INT32 status;
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
	if(pAppRtcLtchInfo->arpCacheEn)
    {
    	AppArp_Invalidate();
    }
    s2wLinkState = S2W_LINK_STATE_DISCONNECTED;
    status = GsnWdd_Disconnect(&s2wappMainTaskCtxt->if0.wddCtx,8,AppS2wDissociate_Cb,s2wappMainTaskCtxt);

     /* If the operation is complete, then notify APP       */
       if (GSN_OPERATION_IN_PROGRESS != status)
       {
           AppS2wDissociate_Cb(NULL, status);
       }
       else
       {
           status = S2W_SUCCESS;
       }
#ifndef S2W_IP2WIFI_SUPPORT
	AppS2wHal_HttpdClose(parentTask);
#ifdef GSN_MDNS_ENABLE     
	AppS2wHal_MdnsDeInit(parentTask);
#endif	
#ifdef S2W_DHCP_SERVER_ENABLE        
         if(dhcpServerFlags & S2W_DHCP_SRVR_ENABLED)
         {
           GsnDhcpSrvr_Stop(&dhcpSrvr);
           dhcpServerFlags &= 0xfe;
         }
#endif   
                 
	AppS2wHal_NetCloseAll(1);
	GsnNwIf_Close(&s2wappMainTaskCtxt->if0.nwifCtx);
#endif
    GsnOsal_SemAcquire ( &stDisassocSemaphore, GSN_OSAL_WAIT_FOREVER );
	return status;
   }
UINT8 
AppS2wHal_NetworkConfig(S2W_NETCONF_T *params)
{
	UINT8 isStaticIP;
    GSN_NWIF_DHCP_PARAMS_T dhcpParams;
    GSN_NWIF_IP_CONFIG_T ipConfig;
    GSN_STATUS retVal;
	isStaticIP = !params->dhcp;
	 memset(&ipConfig,0,sizeof(ipConfig));
	 ipConfig.flag = GSN_NWIF_IPCONFIG_FLAG_IPV4_INIT;
	if (s2wLinkState == S2W_LINK_STATE_CONNECTED)
	{
		 if(isStaticIP)
         {
			 ipConfig.ipv4.staticIp = 1;
			 memcpy((UINT8*)&ipConfig.ipv4.ipAddr,s2wCurrent.netConf.ipAddr,4 );
			 memcpy((UINT8*)&ipConfig.ipv4.subnetMask,s2wCurrent.netConf.netMask,4 );
			 memcpy((UINT8*)&ipConfig.ipv4.gatewayIpAddr,s2wCurrent.netConf.gateway,4 );
			 memcpy((UINT8*)&ipConfig.ipv4.dnsPriSrvrIp,s2wCurrent.dns1,4);
			 memcpy((UINT8*)&ipConfig.ipv4.dnsSecSrvrIp,s2wCurrent.dns2,4);
		 }
		 else
		 {
			 ipConfig.ipv4.staticIp = 0;
			 L3ConnectStatus=0;
			 s2wappMainTaskCtxt->if0.nwifCtx.notifyCb = DHCP_notify;
			 memset(&dhcpParams,0,sizeof(dhcpParams));
			 dhcpParams.dhcpMaxRetryCnt = S2W_DHCP_MAX_RETRY_COUNT;
			 if(strlen((const char *)s2wCurrent.hostName) != 0)
			 {
				 memcpy(ipConfig.ipv4.hostName, s2wCurrent.hostName,
					 (GSN_NWIF_HOST_NAME_MAX_LEN + 1));
			 }
             dhcpParams.radioMode = s2wCurrent.netConf.dhcpRadioMode;
             dhcpParams.requestLeaseTime = s2wCurrent.dhcpRequestLeaseTime;
             dhcpParams.dhcpRetryTimeout = s2wCurrent.dhcpRetryTimeout;
		 }
         S2wL3Wait = TRUE;
		 retVal = GsnNwif_IPv4Configure(&s2wappMainTaskCtxt->if0.nwifCtx, &ipConfig.ipv4, &dhcpParams);
		 if(GSN_NW_IF_CLOSED == retVal)
		 {
			 retVal = GsnNwIf_Open(&s2wappMainTaskCtxt->if0.nwifCtx, &ipConfig, &dhcpParams);

		 }		
          if(isStaticIP)
          {
            L3ConnectStatus = TRUE;
            AppS2wHdrAndIpv4_Print();
            return S2W_SUCCESS;
            
          }
            
         else if(GSN_OPERATION_IN_PROGRESS != retVal) 
		 {
                   
			 DHCP_notify(GSN_FAILURE, &s2wappMainTaskCtxt->if0.nwifCtx);
                          
		 }
		 GsnOsal_SemAcquire ( &s2wL2L3ConnectSemaphore, GSN_OSAL_WAIT_FOREVER );
		 if(TRUE == L3ConnectStatus)
         {
             AppS2wHdrAndIpv4_Print();
             return S2W_SUCCESS;
         }
		 else
         {
             GsnNwIf_Close(&s2wappMainTaskCtxt->if0.nwifCtx);
             return S2W_ENOIP;
         }
	 }
        return S2W_SUCCESS;
}
UINT8 
AppS2wHal_McastRecvSet(UINT8 set)
   {
    if(set)
    {
        return GsnWdd_Ioctl(&s2wappMainTaskCtxt->if0.wddCtx,GSN_WDD_IOCTL_MCAST_RX_ON,&set);
    }
    else
    {
        return GsnWdd_Ioctl(&s2wappMainTaskCtxt->if0.wddCtx,GSN_WDD_IOCTL_MCAST_RX_OFF,&set);
    }
   }
UINT8 
AppS2wHal_SyncLossIntrvlSet(UINT32 interval)
   {
       GsnWdd_BeaconMissThresholdSet(&s2wappMainTaskCtxt->if0.wddCtx,0,interval);
	   return S2W_SUCCESS;
   }
UINT8 
AppS2wHal_RadioModeConfig(UINT8 mode)
   {
    if(mode)
    {
        return GsnWdd_Ioctl(&s2wappMainTaskCtxt->if0.wddCtx,GSN_WDD_IOCTL_RX_ACTIVE_MODE_ON,&mode);
    }
    else
    {
        return GsnWdd_Ioctl(&s2wappMainTaskCtxt->if0.wddCtx,GSN_WDD_IOCTL_RX_ACTIVE_MODE_OFF,&mode);
    }
   }
UINT8 
AppS2wHal_PowerSaveConfig(UINT8 mode)
   {
    if(mode)
    {
        return GsnWdd_Ioctl(&s2wappMainTaskCtxt->if0.wddCtx,GSN_WDD_IOCTL_RX_PS_MODE_ON,&mode);
   }
    else
   {
        return GsnWdd_Ioctl(&s2wappMainTaskCtxt->if0.wddCtx,GSN_WDD_IOCTL_RX_PS_MODE_OFF,&mode);
    }
   }
   
UINT8 
AppS2wHal_IeeePSConfig(UINT8 mode)
{
	if(mode)
	{
	    return GsnWdd_Ioctl(&s2wappMainTaskCtxt->if0.wddCtx,GSN_WDD_IOCTL_RX_IEEEPS_MODE_ON,&mode);
	}
	else
	{
	    return GsnWdd_Ioctl(&s2wappMainTaskCtxt->if0.wddCtx,GSN_WDD_IOCTL_RX_IEEEPS_MODE_OFF,&mode);
	}
}
UINT8 
AppS2wHal_PowerSaveConfigSet()
{
	GSN_WDD_STA_PS_CFG_SET_PARAM_T param;

	param.wakeupType = s2wCurrent.ieeePScfg.wakeupType;
	param.wakeupInterval = s2wCurrent.ieeePScfg.wakeupInterval;
	param.listenIntervalAssoc = s2wCurrent.ieeePScfg.listenIntervalAssoc;
	param.dataRxType = s2wCurrent.ieeePScfg.dataRxType;
	param.uapsdEnable = 0x00;
	param.txAtTbttWakeup = 0;
	param.beaconWaitTimeout = s2wCurrent.ieeePScfg.beaconWaitTimeout;
	if(0 == s2wCurrent.ieeePScfg.beaconWaitTimeout)
	{
			param.beaconWaitTimeout = 10;
	}
    param.activeToOffTimeout = s2wCurrent.ieeePScfg.activeToOffTimeout;
	
	GsnWdd_RadioPowerSaveCfgSet(&s2wappMainTaskCtxt->if0.wddCtx, &param);
        return  S2W_SUCCESS;
}
// profile param is after the rtc content and profile is after that

S2W_PROFILE_PARAMS_T*
S2w_ProfileParamInRTCPtrGet() // right after rtc contents
{
	return (S2W_PROFILE_PARAMS_T *)(GSN_RTC_SRAM_BLOCK0_ADDR + sizeof(APP_RTC_SECNDRY_MEM_INFO_T));

}

S2W_FLASH_PARAMS_T*
S2w_FlashParamInRTCPtrGet() // right after profile param
{
	return (S2W_FLASH_PARAMS_T *)(GSN_RTC_SRAM_BLOCK0_ADDR + sizeof(APP_RTC_SECNDRY_MEM_INFO_T) +
	                              sizeof(S2W_PROFILE_PARAMS_T));
}

VOID
S2w_macAddrRTCGet(UINT8* mac) // right after profile
{

	GSN_MAC_ADDR_T* macAddr = (GSN_MAC_ADDR_T*)(GSN_RTC_SRAM_BLOCK0_ADDR + sizeof(APP_RTC_SECNDRY_MEM_INFO_T) +
	         sizeof(S2W_PROFILE_PARAMS_T) + sizeof(S2W_FLASH_PARAMS_T));
	memcpy(mac,macAddr,6);
}

VOID
S2w_macAddrRTCSet(UINT8* mac)
{

	GSN_MAC_ADDR_T* macAddr = (GSN_MAC_ADDR_T*)(GSN_RTC_SRAM_BLOCK0_ADDR + sizeof(APP_RTC_SECNDRY_MEM_INFO_T) +
	         sizeof(S2W_PROFILE_PARAMS_T) + sizeof(S2W_FLASH_PARAMS_T));
	memcpy(macAddr, mac,6);
}


void
AppS2wHal_RTCRead(void)
{
    S2W_PROFILE_PARAMS_T* param = S2w_ProfileParamInRTCPtrGet();
    memcpy(&profile_params,param,sizeof(S2W_PROFILE_PARAMS_T));
    s2wFlashParams = S2w_FlashParamInRTCPtrGet();

}


S2W_FLASH_PARAMS_T *
AppS2wHal_FlashRead(void)
{
    GSN_STATUS status = GSN_FAILURE;
    
    status = S2w_LoadS2wProfileParams();
    
    if(status == S2W_SUCCESS)
    {
      AppS2wProcess_DefaulConfigtLoad(&FlashParams);
      status = S2w_LoadS2wProfile(&FlashParams.profile[profile_params.defaultProfile],profile_params.defaultProfile);
      S2w_LoadS2wProfile(&FlashParams.profile[!profile_params.defaultProfile],!profile_params.defaultProfile);
      // set the rtc mac
      UINT8 macAddr[6];
      S2w_LoadMacAddr(macAddr);
      S2w_macAddrRTCSet(macAddr); // set in the rtc also
      // read the AP mac address and update the current profile
      S2w_LoadApMacAddr(macAddr);
      memcpy(&FlashParams.profile[profile_params.defaultProfile].lmtdApConf.macAddr,macAddr,6);
    }
     else
    {
        status = S2W_FAILURE;
	}
      
    if (status != GSN_SUCCESS)
    {
        S2W_PROFILE_PARAMS_T def_profile_params;
        
        AppS2wProcess_DefaulConfigtLoad(&FlashParams);
        def_profile_params.vsersion = S2W_PROFILE_PARAM_DFLT_VERSION;
        def_profile_params.autoConnect = 0;
        def_profile_params.defaultProfile = 0;
        
        /* First time, no profile exists in filesystem, store default profile in profile 0 */
          S2w_SaveS2wProfileParams(&def_profile_params);
        S2w_SaveS2wProfile(&FlashParams, 0);
        S2w_SaveS2wProfile(&FlashParams, 1);
        // first time execution so read the otp to get the mac address and update it
        UINT8 mac[6];
        if(otpMac_Read(mac,GSN_OTP_MM_ID_MAC_ID0) == S2W_SUCCESS)
        {
			S2w_SaveMacAddr(mac);
			S2w_macAddrRTCSet(mac); // set in the rtc also
		}
		else
		{
            S2w_SaveMacAddr(S2W_DEFAULT_STA_MAC_ADDR);
            S2w_macAddrRTCSet((UINT8*)S2W_DEFAULT_STA_MAC_ADDR); // set in the rtc also
		}
          status = S2W_FAILURE;

        // read the ap mac and update the file system
        if(otpMac_Read(mac,GSN_OTP_MM_ID_MAC_ID1) == S2W_SUCCESS)
        {
			S2w_SaveApMacAddr(mac);

		}
		else
		{
            S2w_SaveApMacAddr(S2W_DEFAULT_AP_MAC_ADDR);

		}
    }
    

    return &FlashParams;
}

UINT8 
AppS2wHal_UartConfig(S2W_SERIAL_PORT_CONF_T *config)
{
    UINT32 baudrate,prevBaud;
    GSN_UART_PARITYBIT_T parity;
    UINT32 value;
    //UINT8 rxLevel=8;

    switch (config->conf.uart.baudrate)
    {
        case 9600:
            baudrate = GSN_UART_BAUDRATE_9K6;
            break;
        case 19200:
            baudrate = GSN_UART_BAUDRATE_19K2;
            break;
        case 38400:
            baudrate = GSN_UART_BAUDRATE_38K4;
            break;
        case 57600:
            baudrate = GSN_UART_BAUDRATE_57K6;
            break;
        case 115200:
            baudrate = GSN_UART_BAUDRATE_115K2;
            break;
        case 230400:
            baudrate = GSN_UART_BAUDRATE_230K4;
            break;
        case 460800:
            baudrate = GSN_UART_BAUDRATE_460K8;
            break;
        case 921600:
            baudrate = GSN_UART_BAUDRATE_921K6;
            break;
        default:
            return S2W_EINVAL;
    }

    prevBaud = GsnUart_BaudRateGet(&s2wSerialPortHandle.uartHandle);
    if(baudrate != prevBaud)
    {
         AppS2wProcess_StatusNotify(S2W_SUCCESS, 0);
		 GsnTaskSleep(10);
    }
    S2W_ASSERT(GSN_UART_CHARFORMAT_5 == S2W_UARTCONF_BITS_5);
    S2W_ASSERT(GSN_UART_CHARFORMAT_5 == 0);

    value = config->conf.uart.bits;
    if (value > GSN_UART_CHARFORMAT_8)
    {
        return S2W_EINVAL;
    }

    /* set the bits per char of uart
     */
   // GsnUart_CharFormatSet(&s2wSerialPortHandle.uartHandle, (GSN_UART_CHARFORMAT_T) value);

    S2W_ASSERT(GSN_UART_STOPBITS_1 == S2W_UARTCONF_STOP_1);
    S2W_ASSERT(GSN_UART_STOPBITS_1 == 0);

    value = config->conf.uart.stop;
    if (value > GSN_UART_STOPBITS_2)
    {
        return S2W_EINVAL;
    }

    /* set the stop bits of the uart
     */
    //GsnUart_StopBitsSet(&s2wSerialPortHandle.uartHandle, (GSN_UART_STOPBITS_T) value);

    switch (config->conf.uart.parity)
    {
        case S2W_UARTCONF_PARITY_NONE:
            parity = GSN_UART_PARITYBIT_NONE;
            break;
        case S2W_UARTCONF_PARITY_ODD:
            parity = GSN_UART_PARITYBIT_ODD;
            break;
        case S2W_UARTCONF_PARITY_EVEN:
            parity = GSN_UART_PARITYBIT_EVEN;
            break;
        default:
           return S2W_EINVAL;
    }

    /* set the hw flow support of the uart
     */
    GsnUart_HwFlowSupportSet(&s2wSerialPortHandle.uartHandle, config->conf.uart.hardflow ?
                           GSN_UART_HW_SUPPORT: GSN_UART_HW_NO_SUPPORT);
    /* if the h/w flow control enabled then set the rx level to 8
     */
    /* set the baud rate of the uart
     */
    GsnUart_BaudRateSet(&s2wSerialPortHandle.uartHandle, baudrate);
    value = config->conf.uart.bits;
    GsnUart_CharFormatSet(&s2wSerialPortHandle.uartHandle, (GSN_UART_CHARFORMAT_T) value);
    value = config->conf.uart.stop;
    GsnUart_StopBitsSet(&s2wSerialPortHandle.uartHandle, (GSN_UART_STOPBITS_T) value);
    GsnUart_ParityBitsSet(&s2wSerialPortHandle.uartHandle, parity);
   return S2W_SUCCESS;
}

UINT8 
AppS2wHal_MacAddrSet(UINT8* macAddr, BOOL flag)
   {
      UINT8 status;
      status = GsnWdd_PhyAddrSet(&appCtx.if0.wddCtx, (INT8*)macAddr,flag);
      if(status!= GSN_SUCCESS)
            return S2W_FAILURE;
      GsnNwif_UpdatePhyAddr(&appCtx.if0.nwifCtx);
	   return S2W_SUCCESS;
   }
UINT8 
AppS2wHal_PsPollIntervelset(UINT32 interval)
{
	GsnWdd_KeepAliveTimeOutSet(&appCtx.if0.wddCtx, (UINT8)interval);
	return S2W_SUCCESS;
}
UINT8 
AppS2wHal_PskKeyStore(UINT8* psk)
   {
	   return S2W_SUCCESS;
   }

UINT8 

AppS2wHal_MacAddrGet(UINT8* macAddr)
   {
           GsnWdd_PhyAddrGet(&appCtx.if0.wddCtx,(INT8*)macAddr);
	   return S2W_SUCCESS;
   }

VOID


s2wDisassocCb(VOID *ctx,GSN_WDD_DISASSOCIATION_CB_INFO *pDisAssocInfo)
{
  UINT32 msg = APP_EVENT_NW_LINK_FAILURE;
  if(s2wappMainTaskCtxt->dpSleep )
  {
        AppS2w_GpioWkUpDisable();
		AppS2w_ExitDpSleep();
  }
  // for auto connection (data pipe make the async gpio low-so that host will not send data)
  if(s2wIsAutoconnected)
  {
	   S2w_AsyncMsgGpioOp(0);
  }
  AppMainCtx_TaskNotify(msg);

}

VOID 
s2wDisassocSyncLossCb(VOID *ctx,UINT32 missBeacon)
{
  UINT32 msg = APP_EVENT_SYNC_LOSS_INDICATION;
  if(s2wappMainTaskCtxt->dpSleep )
  {
        AppS2w_GpioWkUpDisable();
		AppS2w_ExitDpSleep();
  }
  // for auto connection (data pipe make the async gpio low-so that host will not send data)
  if(s2wIsAutoconnected)
  {
	   S2w_AsyncMsgGpioOp(0);
  }
  AppMainCtx_TaskNotify(msg);
}


 PUBLIC VOID
 AppS2wHal_Register(GSN_NOTIFICATION_FUNC_T notifier, VOID *context)
 {
     s2wappMainTaskNotifier = notifier;
     s2wappMainTaskCtxt = context;

     //GsnWdd_DisassocIndCbReg(&s2wappMainTaskCtxt->if0.wddCtx, s2wDisassocCb, context);
     // GsnWdd_BeaconMissCbReg(&s2wappMainTaskCtxt->if0.wddCtx, s2wDisassocSyncLossCb, context);
     //GsnWdd_BeaconMissThresholdSet(&s2wappMainTaskCtxt->if0.wddCtx,0,S2W_DEFAULT_SYNCLOSS_INTERVAL);



}

 VOID
 AppS2wHal_PrintBanner()
 {
    UINT32 bootReason, bootInfo, bootCode, flag = 0, i,asyncMsgID=0, appflag = 0;
	GSN_SYS_RESET_INFO_T *pResetInfo = (GSN_SYS_RESET_INFO_T *)GSN_SYS_RESET_INFO_LOCATION_GET();

	/*Check Boot Reason*/
#ifndef S2W_ASYNC_MSG
    (void)asyncMsgID;/* Suppress the warning*/
#endif
    
 	bootReason = GSN_BOOT_REASON_GET();
 	bootInfo = GSN_BOOT_INFO_GET();
 	if ((S2W_WLANDATA_MODE_ISOTX  != s2wCurrent.mode) || (S2W_WLANDATA_MODE_15_4 != s2wCurrent.mode))
 	{	
 #ifdef S2W_PERSISTENT_TMR_SUPPORT
 	if(bootReason != GSN_WIF_SYS_BOOT_FIRST_BOOT)
 	{
 		GsnPersistTmr_Restore();
 	}
 #endif
	}
 	switch (bootReason)
 	{
 	case GSN_WIF_SYS_BOOT_FIRST_BOOT:
        bootCode = S2W_INITIAL_BOOT_MSG;
        asyncMsgID = S2W_ASYNC_INITIAL_BOOT_MSG;
 		break;
 	case GSN_WIF_SYS_BOOT_NORMAL_BOOT:
 		if(GSN_WIF_SYS_BOOTINFO_NORMALBOOT_RTC == bootInfo)
 		{
            bootCode = S2W_STBY_TMR_EVT;
            asyncMsgID =S2W_ASYNC_STBY_TMR_EVT;
 		}
 		else if(GSN_WIF_SYS_BOOTINFO_NORMALBOOT_ALARM == bootInfo)
 		{
            bootCode = S2W_STBY_ALM_EVT;
            asyncMsgID =S2W_ASYNC_STBY_ALM_EVT;
 		}
 		else
        {
            bootCode = S2W_BOOT_UNKNOWN;
            asyncMsgID = S2W_ASYNC_BOOT_UNKNOWN;
        }
 		break;
 	case GSN_WIF_SYS_BOOT_FW_UPDATE_BOOT:
        bootCode = S2W_BOOT_RST_EXT_FLASH_FWUP_SUCCESS;
        asyncMsgID = S2W_ASYNC_BOOT_RST_EXT_FLASH_FWUP_SUCCESS;
 		break;
 	case GSN_WIF_SYS_BOOT_WATCHDOG_BOOT:
 		if(GSN_WIF_SYS_BOOTINFO_WDOG_RESET_APP == bootInfo)
 		{
            bootCode = S2W_BOOT_RST_APP_WD;
            asyncMsgID = S2W_ASYNC_BOOT_RST_APP_WD;
 		}
 		else if(GSN_WIF_SYS_BOOTINFO_WDOG_RESET_WLAN == bootInfo)
 		{
 			flag = TRUE;
            bootCode = S2W_BOOT_RST_WLAN_WD;
            asyncMsgID = S2W_ASYNC_BOOT_RST_WLAN_WD;
 		}
 		else
 		{
            bootCode = S2W_BOOT_UNKNOWN;
            asyncMsgID = S2W_ASYNC_BOOT_UNKNOWN;
 		}
 		break;
 	case GSN_WIF_SYS_BOOT_SW_RESET_BOOT:
 		if (GSN_WIF_SYS_BOOTINFO_SWRESET_APP == bootInfo)
 		{
			appflag = TRUE;
            bootCode = S2W_BOOT_RST_APP_SW;
            asyncMsgID = S2W_ASYNC_BOOT_RST_APP_SW;
 		}
 		else //if(GSN_WIF_SYS_BOOTINFO_SWRESET_WLAN == bootInfo)
		{
 			bootCode = S2W_BOOT_RST_WLAN_SW;
 			asyncMsgID = S2W_ASYNC_BOOT_RST_WLAN_SW;
 			flag = TRUE;
		}
 		break;
 	case GSN_WIF_SYS_BOOT_EXCEPTION_BOOT:
		if(		(GSN_WIF_SYS_BOOTINFO_EXCP_APP_ABORT == bootInfo) ||
				(GSN_WIF_SYS_BOOTINFO_EXCP_APP_ASSERT == bootInfo))
		{
			appflag = TRUE;
			bootCode = S2W_BOOT_RST_APP_SW;
			asyncMsgID = S2W_ASYNC_BOOT_RST_APP_SW;
		}
		else if((GSN_WIF_SYS_BOOTINFO_EXCP_WLAN_ABORT == bootInfo) ||
				(GSN_WIF_SYS_BOOTINFO_EXCP_WLAN_ASSERT == bootInfo))
		{
			bootCode = S2W_BOOT_RST_WLAN_EXPT;
			asyncMsgID = S2W_ASYNC_BOOT_RST_WLAN_EXPT;
			flag = TRUE;
		}
		else
		{
			bootCode = S2W_BOOT_UNKNOWN;
			asyncMsgID = S2W_ASYNC_BOOT_UNKNOWN;
		}
		break;
 	case GSN_WIF_SYS_BOOT_EXT_RESET_BOOT:
 		bootCode = S2W_BOOT_EXT_RST;
 		asyncMsgID = S2W_ASYNC_BOOT_EXT_RST;
 		break;
 	case GSN_WIF_SYS_BOOT_FACTORY_FW_BOOT:
 		bootCode = S2W_BOOT_RST_EXT_FLASH_FWUP_SUCCESS;
 		asyncMsgID = S2W_ASYNC_BOOT_RST_EXT_FLASH_FWUP_SUCCESS;
 		break;
 	case GSN_WIF_SYS_BOOT_DBG_BOOT:
 		bootCode = S2W_BOOT_RST_JTAG;
 		asyncMsgID = S2W_ASYNC_BOOT_RST_JTAG;
 		break;
 	case GSN_WIF_SYS_BOOT_CRYPTO_SW_BOOT:
 		bootCode = S2W_BOOT_CRYPTO;
 		asyncMsgID = S2W_ASYNC_BOOT_CRYPTO;
 		break;
 	case GSN_WIF_SYS_BOOT_CORE_BROWNOUT_BOOT:
 		bootCode = S2W_BOOT_RST_BROWNOUT;
 		asyncMsgID = S2W_ASYNC_BOOT_RST_BROWNOUT;
 		break;
 	default:
 		bootCode = S2W_BOOT_UNKNOWN;
 		asyncMsgID = S2W_ASYNC_BOOT_UNKNOWN;
 		break;
	}
#ifdef S2W_ASYNC_MSG
	if(s2wCurrent.asyncMsgFormat && asyncMsgID != 0)
	{
		S2w_AsyncMsgGpioInit();
		AppS2wProcess_AsyncStatusNotify(asyncMsgID, 0);
	}
	else
#endif
	{
 	    //S2w_Printf(S2WBootPrint_List[bootCode]);
 	    AppS2wProcess_StatusNotify(bootCode, S2W_SUCCESS);
	}
 	if(flag)
 	{

        S2w_Printf("\r\n---MEM-DUMP-START:\r\n\n\rWLAN-ERROR-CODE:%x %x %x %x\r\n\r\nWLAN-ERROR-PARAM:\r\n",
        		pResetInfo->wlan.resetType,
        		pResetInfo->wlan.resetReason,
        		pResetInfo->wlan.resetInfoSize,
        		pResetInfo->wlan.resetAddlInfo);

        for(i=0;i<16;i++)
        {
            S2w_Printf("R[%2d]:%08x\r\n",i,pResetInfo->wlan.resetInfo[i]);
        }

        S2w_Printf("\n\r---MEM-DUMP-END:\r\n");

 	}

 	if((appflag) && (s2wCurrent.logLevel) )
 	{
 		GSN_SYS_RESET_INFO_T *pResetInfo = (GSN_SYS_RESET_INFO_T *)GSN_SYS_RESET_INFO_LOCATION_GET();

        S2w_Printf("\r\n---MEM-DUMP-START:\r\n\n\rAPP-ERROR-CODE:%x %x %x %x\r\n\r\nAPP-ERROR-PARAM:\r\n",
        		pResetInfo->app.resetType,
        		pResetInfo->app.resetReason,
        		pResetInfo->app.resetInfoSize,
        		pResetInfo->app.resetAddlInfo);

        for(i=0;i<16;i++)
        {
            S2w_Printf("R[%2d]:%08x\r\n",i,pResetInfo->app.resetInfo[i]);
        }

        S2w_Printf("\n\r---MEM-DUMP-END:\r\n");
 	}

	
	/*Clear The Reset Information - its already dumped*/
	memset((INT8 *)pResetInfo, 0, sizeof(GSN_SYS_RESET_INFO_T));
 	return;
 }



#ifdef S2W_DUAL_INTERFACE_SUPPORT

extern UINT8 s2wSerial2InputTaskStack[2048];
PUBLIC VOID
AppS2wHal_SerialInterface2Init(VOID)
{

    GsnOsal_QueueCreate(&s2wSerial2InputTaskQueue, 1,
                          (UINT8*)s2wSerial2InputTaskBuffer,
                          (sizeof(s2wSerial2InputTaskBuffer)*1));

    /* create the network  receive task
     */

    GsnOsal_ThreadCreate(AppS2wHal_s2wSerial2InputTask,s2wappMainTaskCtxt,
                                &s2wappMainTaskCtxt->s2wSerial2InputTask,
                                "&s2wSerial2InputTask",
                                APP_CFG_SERIALINPUT2_THREAD_PRIORITY,
                                s2wSerial2InputTaskStack,
                                sizeof(s2wSerial2InputTaskStack),
                                GSN_OSAL_THREAD_INITIAL_READY);

}


#endif

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
#ifdef S2W_DUAL_INTERFACE_SUPPORT
	UINT8 msgBuff[32] = "DataInterfaceReady";
#endif
    UINT32 bootReason;
    S2W_SERIAL_PORT_ID_T  portId;    /* Serial device ID - SPI/UART */
    /* create all semaphore needed for s2w app
     */
    GsnOsal_SemCreate  (&stUartWriteSemaphore,1);
    GsnOsal_SemCreate  (&stUartWriteSemaphore1,1);

    GsnOsal_SemCreate  ( &stScanSemaphore, 0 );

    GsnOsal_SemCreate  ( &stDisassocSemaphore, 0 );

    GsnOsal_SemCreate (&stbyDelaySemaphore, 0);

    GsnOsal_SemCreate (&s2wSyncSemID, 1);
    GsnOsal_SemCreate (&s2wSyncSemID1, 1);
    
    GsnOsal_SemCreate  ( &s2wL2L3ConnectSemaphore, 0 );
#ifdef S2W_RF_TEST
	GsnOsal_SemCreate  ( &s2wWlanOpSyncSem, 0 );
#endif	
#if defined(S2W_WEB_PROV) || defined(S2W_WEB_SERVER)
	GsnOsal_SemCreate(&s2wappMainTaskCtxt->webServerSync, 0 );
#endif
    GsnOsal_SemCreate (&(s2wappMainTaskCtxt->s2wDpSleepWakeUpSem), 0);
	GsnOsal_SemCreate( &(s2wappMainTaskCtxt->s2wTcpClientCntSyncSem), 1 );
    // select the serial port
    portId = AppS2w_SelectSerialDeviceId(s2wappMainTaskCtxt);


    /* Set the serial port device ID */
    APP_S2W_SET_SERIAL_DEVICE_ID(portId);

	f_enterFS();
    /* initialize s2w
     */
    AppS2w_Init();
	
    if(S2W_SUCCESS != AppS2w_SerialPortInit(s2wappMainTaskCtxt))
    {/* Serial interface init failed - can't proceed */
        S2W_ASSERT(0);
    }
//#if (!( defined S2W_ISOTX_SUPPORT  || defined S2W_15DOT4_SUPPORT ))
	if ((S2W_WLANDATA_MODE_ISOTX  != s2wCurrent.mode) || (S2W_WLANDATA_MODE_15_4 != s2wCurrent.mode))
	{
#ifdef S2W_PERSISTENT_TMR_SUPPORT    
    AppS2w_PersistantTmrCfg();
    AppS2w_PersistTmrInit( &appCtx);
#endif
//#endif
	}

#ifdef S2W_EXT_FLASH_FS_SUPPORT
	AppExtFlash_DataFsInit();
#endif
	App_DefaultIfInit(&appCtx, &appCtx.if0);

    App_WaitOnLock();
#if 1
			if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != GSN_BOOT_REASON_GET())
			{
				/*Open the interface. Need to open the interface after wdd and nwif initialisations?*/
				App_InterfaceStart(&appCtx, &appCtx.if0);
			}
		#endif

    // do the IP2WiFi specific init
    {
#ifdef S2W_IP2WIFI_SUPPORT
    /* Initialize wdd  */
    AppInit_L2DevInit(&appCtx);
    s2wL2Dev_Open((GSN_L2_DEV_T *)&(appCtx.s2wL2Dev),NULL,NULL,NULL,NULL);

#endif
    }

    AppS2w_SetWlanDfltParams(profile_params.defaultProfile);

	
	if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != GSN_BOOT_REASON_GET())
	{
		UINT8* randomSeed  = (UINT8 *)GSN_SYS_CRYPTO_SEED_LOCATION_GET();
		GsnHeIf_TrangGetSeed(randomSeed);
	}
    AppS2wHal_PrintBanner();
#ifdef S2W_DUAL_INTERFACE_SUPPORT
    S2W_SERIAL_PORT_ID_T  portId1;     // select the serial port for second interface
    portId1 = AppS2w_SelectSerialDeviceId1(s2wappMainTaskCtxt);

    s2wappMainTaskCtxt->serialDeviceId1 = portId1;
    AppS2w_SerialPortInit2();
    S2w_Printf1("%s\r\n",msgBuff);
    if(s2wappMainTaskCtxt->serialDeviceId1 == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush1();
    }
#endif
     GsnWdd_DisassocIndCbReg(&s2wappMainTaskCtxt->if0.wddCtx, s2wDisassocCb, s2wappMainTaskCtxt);
     GsnWdd_BeaconMissCbReg(&s2wappMainTaskCtxt->if0.wddCtx, s2wDisassocSyncLossCb, s2wappMainTaskCtxt);
	 bootReason = GSN_BOOT_REASON_GET();
	 if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != bootReason)
     GsnWdd_BeaconMissThresholdSet(&s2wappMainTaskCtxt->if0.wddCtx,0,S2W_DEFAULT_SYNCLOSS_INTERVAL);
    AppS2wProcess_AutoStart();
#ifdef S2W_DUAL_INTERFACE_SUPPORT
    AppS2wHal_SerialInterface2Init();
#endif

   while (1)
    {
        AppS2wProcess_SerialInput();
    }
}


#ifdef S2W_DUAL_INTERFACE_SUPPORT

PRIVATE void
AppS2wHal_s2wSerial2InputTask( UINT32 u32Address )
{

	while(1)
	{
		AppS2wProcess_Serial2Input();
		// wait on a msg queue


	}
}

#endif




#ifdef S2W_PERSISTENT_TMR_SUPPORT
VOID
AppS2w_PersistantTmrCfg()
{
	APP_PERSIST_TMR_CFG_T normalCfg;
	F_FILE *fp;

	fp = f_open("pstTmr", "r");
	if(fp == NULL)
	{
		fp = f_open("pstTmr", "w");
	    memset( normalCfg.persistTmrNvds, 0, sizeof( APP_PERSIST_TMR_CFG_T ));
	    f_write(&normalCfg, 1, sizeof(APP_PERSIST_TMR_CFG_T), fp);
	    f_close(fp);
    }
    else
    	f_close(fp);
}
     
VOID
AppS2w_PersistantTmrCfgGet(UINT8 *ptr)
{
	F_FILE *fp;

	fp = f_open("pstTmr", "r");
	if(fp != NULL)
	{
		f_read(ptr, 1, sizeof(APP_PERSIST_TMR_CFG_T), fp);
		f_close(fp);
	}
}

VOID
AppS2w_StateExit(APP_MAIN_CTX_T *pAppSm)
{
	F_FILE *fp;
	if( GsnPersistTmr_Store())
    {
    	fp = f_open("pstTmr", "r+");
    	f_seek(fp, offsetof(APP_PERSIST_TMR_CFG_T, persistTmrNvds), F_SEEK_SET);
    	f_write(pAppSm->persistTmrNvds, 1, sizeof(pAppSm->persistTmrNvds), fp);
    	f_close(fp);
    }
}

GSN_STATUS
AppS2w_PersistTmrInit( APP_MAIN_CTX_T *pAppSm )
{
    ULONG64 period;
    APP_PERSIST_TMR_CFG_T normalCfg;
    APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchMemInfo = App_RtcLatchMemInfoPtrGet();
    AppS2w_PersistantTmrCfgGet((UINT8 *)&normalCfg);
    memcpy( pAppSm->persistTmrNvds, normalCfg.persistTmrNvds, sizeof(normalCfg.persistTmrNvds) );
    
    /**< Initialize the persistent timer module */
    GsnPersistTmr_Init( pAppRtcLtchMemInfo->persistTmr, pAppSm->persistTmrNvds, 
        APP_NUM_OF_VAR_PERSIST_TMR, APP_NUM_OF_CONST_PERSIST_TMR, 
        pAppSm->persistTmrTbl );
    
    return GSN_SUCCESS;
}
#endif

#if 0
VOID
AppSm_RemoteMgmtTimeoutHandle(void *ptr, GSN_SOFT_TMR_HANDLE_T handle)
{
	S2w_Printf("rm\n\r");
}

VOID
AppSm_KeepAliveTimeoutHandle(void *ptr, GSN_SOFT_TMR_HANDLE_T handle)
{
	S2w_Printf("kplv\n\r");
}

VOID
AppSm_HeartBeatTimeoutHandle(void *ptr, GSN_SOFT_TMR_HANDLE_T handle)
{
	S2w_Printf("htbt\n\r");
}

VOID
AppSm_TimeSyncTimeoutHandle(void *ptr, GSN_SOFT_TMR_HANDLE_T handle)
{
	S2w_Printf("tsync\n\r");
}

VOID
AppSm_SensorReadTimeoutHandle(void *ptr, GSN_SOFT_TMR_HANDLE_T handle)
{
	S2w_Printf("snrd\n\r");
}

GSN_STATUS
AppSm_PersistTmrStart( APP_MAIN_CTX_T *pAppSm, BOOL create )
{
    ULONG64 period;
    APP_PERSIST_TMR_CFG_T normalCfg;
    APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchMemInfo = App_RtcLatchMemInfoPtrGet();
    AppS2w_PersistantTmrCfgGet((UINT8 *)&normalCfg);
    memcpy( pAppSm->persistTmrNvds, normalCfg.persistTmrNvds, sizeof(normalCfg.persistTmrNvds) );
    
    /**< Initialize the persistent timer module */
    GsnPersistTmr_Init( pAppRtcLtchMemInfo->persistTmr, pAppSm->persistTmrNvds, 
        APP_NUM_OF_VAR_PERSIST_TMR, APP_NUM_OF_CONST_PERSIST_TMR, 
        pAppSm->persistTmrTbl );
	S2w_Printf("db1\n\r");
    if( TRUE == create )
    {
    	S2w_Printf("Create\n\r");
        /**< Create the required persistent timers. Mark the remote mgmt and 
        sensor read timer as autostart. All other timers are started only after 
        getting join success message */

        GsnPersistTmr_Create(0, 
                                GSN_TIMER_TYPE_PERSISTENT_CONSTANT, normalCfg.remoteMgmtFreq * TIMER_INTERRUPT_1_S, 
                                AppSm_RemoteMgmtTimeoutHandle, pAppSm, TRUE);

        /* Create association keep alive timer */
        GsnPersistTmr_Create(1, 
                                GSN_TIMER_TYPE_PERSISTENT_CONSTANT, normalCfg.assocKeepAliveFreq * TIMER_INTERRUPT_1_S,
                                AppSm_KeepAliveTimeoutHandle, pAppSm, TRUE);       
#ifdef OS_UVEL
        /* Create server heart beat timer */
        GsnPersistTmr_Create(2, 
                                GSN_TIMER_TYPE_PERSISTENT_CONSTANT, normalCfg.heartBeatFreq * TIMER_INTERRUPT_1_S, 
                                AppSm_HeartBeatTimeoutHandle, pAppSm, TRUE);
#endif
        /* Create time-sync timer */
        GsnPersistTmr_Create(3, 
                                GSN_TIMER_TYPE_PERSISTENT_CONSTANT, normalCfg.timeSyncOperationFreq * TIMER_INTERRUPT_1_S, 
                                AppSm_TimeSyncTimeoutHandle, pAppSm, TRUE);
        GsnPersistTmr_Create(4, 
                                GSN_TIMER_TYPE_PERSISTENT_VARIABLE, normalCfg.sensorReadFreq * TIMER_INTERRUPT_1_S, 
                                AppSm_SensorReadTimeoutHandle, pAppSm, TRUE);
    }
    else
    {
    	int flag = 1;
    	S2w_Printf("Restore\n\r");
    	//while(flag);
        GsnPersistTmr_Restore();
    }

    return GSN_SUCCESS;
}
#endif

S2W_SERIAL_PORT_ID_T
AppS2w_SelectSerialDeviceId(APP_MAIN_CTX_T *pAppCtx)
{

#if  defined(S2W_FORCE_UART_PORT) || defined(S2W_FORCE_SPI_PORT) || defined(S2W_FORCE_SDIO_PORT)|| defined(S2W_FORCE_SPI_FS_PORT)
//Forced selection
   #ifdef S2W_FORCE_UART_PORT
      return S2W_PORT_UART;
   #endif

   #ifdef S2W_FORCE_SPI_PORT
      #ifndef S2W_FS_SPI_ENABLE
         #error To use SPI port enable S2W_FS_SPI_ENABLE define
      #endif

      return S2W_PORT_SPI;
   #endif
   #ifdef S2W_FORCE_SPI_FS_PORT
      #ifndef S2W_FS_SPI_HI_ENABLE
         #error To use SPI port enable GSN_FS_SPI_ENABLE define
      #endif
      return S2W_PORT_FS_SPI;
   #endif
   #ifdef S2W_FORCE_SDIO_PORT
         return S2W_PORT_SDIO;
   #endif

#else
   return S2W_PORT_UART;
#endif



}/* AppS2w_SelectSerialDeviceId */

#ifdef S2W_DUAL_INTERFACE_SUPPORT

S2W_SERIAL_PORT_ID_T
AppS2w_SelectSerialDeviceId1(APP_MAIN_CTX_T *pAppCtx)
{

#if  defined(S2W_FORCE_UART_PORT1) || defined(S2W_FORCE_SPI_PORT1) || defined(S2W_FORCE_SDIO_PORT1)|| defined(S2W_FORCE_SPI_FS_PORT1)
//Forced selection
   #ifdef S2W_FORCE_UART_PORT1
      return S2W_PORT_UART;
   #endif

   #ifdef S2W_FORCE_SPI_PORT1
      return S2W_PORT_SPI;
   #endif
   #ifdef S2W_FORCE_SPI_FS_PORT1
      return S2W_PORT_FS_SPI;
   #endif
   #ifdef S2W_FORCE_SDIO_PORT1
         return S2W_PORT_SDIO;
   #endif

#else
   return S2W_PORT_UART;
#endif



}/* AppS2w_SelectSerialDeviceId */

#endif
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w serial interface initialisation
 *   This function initialises either UART or SPI port.
 * @param portId  - IN the port ID
 *
 * @retval  S2W_SUCCESS - Serial port initialisation success
 *              S2W_FAILURE   - Serial port initialisation failed
 ******************************************************************/
PUBLIC UINT8
AppS2w_SerialPortInit(APP_MAIN_CTX_T *pAppCtx)
{
UINT8                 retStatus=S2W_SUCCESS;
//int *p;
#ifdef S2W_SDIO_ENABLE
GSN_SDIO_CONFIG_T ptSdioConfig;
#endif
#ifdef  S2W_FS_SPI_ENABLE
    GSN_SPI_CONFIG_T   spiConfig;       /* Temporary structure to hold serial port config parameter */
#endif
#ifdef  S2W_FS_SPI_HI_ENABLE
    GSN_SPI_FS_CONFIG_T   spiFsConfig;       /* Temporary structure to hold serial port config parameter */
#endif 
#ifdef S2W_UART_ENABLE
GSN_OSAL_ERROR_T     tUartStatus;     /* UART operation status */
GSN_UART_CONFIG_T     tUartConfig;     /* Temporary structure to hold UART config parameter */
#endif
S2W_SERIAL_PORT_ID_T  portId;          /* Serial device ID - SPI/UART */
/* Initialize s2w serial port -  UART or SPI interface can be configured.
 * Selection of UART/SPI port depends on GPIO signal
 * If GPIO signal is LOW then UART will be selected else
 * SPI port will be selected.
 */

    portId = APP_S2W_GET_SERIAL_DEVICE_ID();
    if(portId == S2W_PORT_UART)
    {
        GsnIoMux_Sel(0, GSN_IOMUX_GPIO_0_AUART0_RXD);
        GsnIoMux_Sel(1, GSN_IOMUX_GPIO_1_AUART0_TXD);
        GsnIoMux_PullDownDisable(1);		// uart tx
        GsnIoMux_PullDownDisable(0);
        /* workaround for gpio35 since mux is configured in boot rom as pull down--fixed in C1 bootrom
         */
        GsnIoMux_Sel(35, GSN_IOMUX_GPIO_35_AGPIO_35);
        GsnIoMux_PullDownEnable(35);
	}
	else
	{

         GsnIoMux_Sel(33, GSN_IOMUX_GPIO_33_ASSP0_BI_CS);
         //GsnIoMux_PullDownEnable (15);

         GsnIoMux_Sel(34, GSN_IOMUX_GPIO_34_ASSP0_DIN);
         //GsnIoMux_PullDownEnable (16);

         GsnIoMux_Sel(35, GSN_IOMUX_GPIO_35_ASSP0_CLK);
         //GsnIoMux_PullDownEnable (17);

         GsnIoMux_Sel(36, GSN_IOMUX_GPIO_36_ASSP0_DOUT);
         //GsnIoMux_PullDownEnable (18);
        // gpio for spi
         GsnIoMux_Sel(37,GSN_IOMUX_GPIO_37_AGPIO_37);
         GsnIoMux_PullDownEnable (37);


	}
    if(portId == S2W_PORT_SDIO)
    {


	       GsnIoMux_Sel(32, GSN_IOMUX_GPIO_32_SDIO_DATA2);
	       GsnIoMux_PullDownDisable(32);
	       GsnIoMux_Sel(33, GSN_IOMUX_GPIO_33_SDIO_DATA3);
	       GsnIoMux_PullDownDisable(33);
	       GsnIoMux_Sel(34, GSN_IOMUX_GPIO_34_SDIO_CMD);
	       GsnIoMux_PullDownDisable(34);
	       GsnIoMux_Sel(35, GSN_IOMUX_GPIO_35_CLK_SDIO_PAD);
	       GsnIoMux_PullDownDisable(35);
	       GsnIoMux_Sel(36, GSN_IOMUX_GPIO_36_SDIO_DATA0);
	       GsnIoMux_PullDownDisable(36);
	       GsnIoMux_Sel(37, GSN_IOMUX_GPIO_37_SDIO_DATA1);
	       GsnIoMux_PullDownDisable(37);



	}

switch(portId)
{
   #ifdef  S2W_FS_SPI_ENABLE
   case S2W_PORT_SPI:
   {
       if(pAppCtx)
       {
           GSN_STATUS status;
           /*Load the profile and configure SPI interface */
           spiConfig.spiRxBuffer   = &(s2wSerialBuf[0]);    /* static buffer used for SPI recieve */
           spiConfig.spiRxBuffSize = sizeof(s2wSerialBuf);
           //tSpiConfig.spiNum = S2W_DEFAULT_SPI_NUMBER;
              spiConfig.spiMode             = GSN_SPI_OPERATION_MODE_SLAVE;
		       spiConfig.spiProtocol         = GSN_SPI_PROTOCOL_MOTOROLA;
		       spiConfig.clockPolarity       = s2wCurrent.serialPortConf.conf.spi.clockPolarity;
		       spiConfig.clockPhase          = s2wCurrent.serialPortConf.conf.spi.clockPhase;
		       spiConfig.dataWordSize        = GSN_SPI_DATAWORDSIZE_8;
		       spiConfig.SerialclockRate     = 0;
		       spiConfig.clockDivider        = 100;   // 100 - 500Khz, 50 - 1Mhz.
		       spiConfig.clockSelect         = GSN_SPI_CLK_HSRC;

		       spiConfig.dmaMode             = GSN_SPI_DMA_CLEAR;
		       spiConfig.sodMode             = GSN_SPI_SOD_CLEAR;
		       spiConfig.LoopBack            = GSN_SPI_LoopBack_CLEAR;
		       spiConfig.spiRxBuffer         = s2wSerialBuf;
		       spiConfig.spiRxBuffSize       = sizeof(s2wSerialBuf);
		       spiConfig.idleChar            = GSN_SPI_IDLE_CHAR;
		       spiConfig.byteStuff           = 1;
               //GsnClkCtl_Init(&gsnBrClkCtlCtx1);
		       status = GsnSpi_Open(&s2wSerialPortHandle.spiHandle, GSN_SPI_NUM_MSPI,&spiConfig);
		       if (GSN_SUCCESS != status)
		       {
		           //GSN_ASSERT(status == GSN_SUCCESS, GSN_ASSERT_DRIVER_FAILURE );
           }

           // create the semaphore
           GsnOsal_SemCreate  (&spiWriteLock,1);
           s2wappMainTaskCtxt->s2wGetCharFn = AppS2wHal_SpiCharGet;
           s2wappMainTaskCtxt->s2wWriteFn   = AppS2wHal_SpiNCharPut;
           s2wappMainTaskCtxt->s2wPutCharFn = AppS2wHal_SpiCharPut;
           s2wappMainTaskCtxt->s2wGetNCharFn= AppS2wHal_SpiNCharGet;
           //s2wappMainTaskCtxt->s2wDpSleepWakeUpCallBack = AppS2w_DpSleepWakeUpCallBack;
           // initialize the gpio 37 for host wakeup
           GsnGpio_Init(APP_S2W_SPI_HOST_WAKEUP_GPIO_BITMAP, ~APP_S2W_SPI_HOST_WAKEUP_GPIO_BITMAP);
           GsnGpio_OutClear(APP_S2W_SPI_HOST_WAKEUP_GPIO_BITMAP);
       }
       else
       {/*ERROR:  SPI init failed */
           retStatus=S2W_FAILURE;
       }
   }
   break;
   #endif

#ifdef  S2W_FS_SPI_HI_ENABLE
   case S2W_PORT_FS_SPI:
   {
       if(pAppCtx)
       {
           GSN_STATUS status;
           //GsnClkCtl_Init(&gsnBrClkCtlCtx1);
           
#ifdef  S2W_SPI_HI_FS_CLK_PLL
           
          GsnClkCtl_SysPllEn(GSN_CLK_CTL_PLL_FREQ_120MHZ);
#else
    //GsnClkCtl_Init(&gsnBrClkCtlCtx1);        
    cm3ClkCfg.pClkCtlCtx = GsnClkCtl_CtxGet();
    cm3ClkCfg.activeModeClkReq = GSN_CLK_CTL_CLK_SRC_HS_RC;
    cm3ClkCfg.sleepModeClkReq = GSN_CLK_CTL_CLK_SRC_HS_RC;
    cm3ClkCfg.deepSleepModeClkReq = (GSN_CLK_CTL_CLK_SRC_T)0;
    cm3ClkCfg.control = 1; //core control
    cm3ClkCfg.cm3ClkSel = GSN_CLK_SEL_HS_RC;
    GsnClkCtl_Cm3ClkCfg(&cm3ClkCfg);
    {
        GsnClkCtl_HsRcCal(&cm3ClkCfg);
    }
#endif
           
           
           /*Load the profile and configure SPI interface */
           spiFsConfig.spiRxBuffer         = &(s2wSerialBuf[0]);    /* static buffer used for SPI recieve */
           spiFsConfig.spiRxBuffSize       = sizeof(s2wSerialBuf);
           spiFsConfig.spiMode             = GSN_SPI_FS_OPERATION_MODE_SLAVE;
           spiFsConfig.spiProtocol         = GSN_SPI_FS_PROTOCOL_MOTOROLA;
           spiFsConfig.clockPolarity       = (GSN_SPI_FS_CLOCKPOLARITY_T)S2W_DEFAULT_SPI_POLARITY;//GSN_SPI_CLK_POL_INACTIVELOW;      // GSN_SPI_CLK_POL_INACTIVEHIGH.
           spiFsConfig.clockPhase          = (GSN_SPI_FS_CLOCKPHASE_T)S2W_DEFAULT_SPI_PHASE;//GSN_SPI_CLK_PHASE_180;            // GSN_SPI_CLK_PHASE_0.
           spiFsConfig.dataWordSize        = GSN_SPI_FS_DATAWORDSIZE_8;
           spiFsConfig.SerialclockRate     = 0;
           spiFsConfig.clockDivider        = 14;   
#ifdef  S2W_SPI_HI_FS_CLK_PLL
           spiFsConfig.clockSelect         = GSN_SPI_FS_CLK_PLL;
#else
           spiFsConfig.clockSelect         = GSN_SPI_FS_CLK_HSRC;
#endif

           spiFsConfig.dmaMode             = GSN_SPI_FS_DMA_SET;
           spiFsConfig.sodMode             = GSN_SPI_FS_SOD_CLEAR;
           spiFsConfig.LoopBack            = GSN_SPI_FS_LoopBack_CLEAR;
           spiFsConfig.spiRxBuffer         = s2wSerialBuf;
           spiFsConfig.spiRxBuffSize       = sizeof(s2wSerialBuf);
           spiFsConfig.idleChar            = GSN_SPI_FS_IDLE_CHAR;
           spiFsConfig.byteStuff           = 0;
           spiFsConfig.spiGpioBitMap       = S2W_SPI_HOST_WAKEUP_GPIO_BITMAP;
           spiFsConfig.spiGpioNum          = S2W_SPI_HOST_WAKEUP_GPIO_NUM;
           
           
           status = GsnSpiFS_Open(&s2wSerialPortHandle.spiFsHandle, GSN_FS_SPI_NUM_MSPI,&spiFsConfig);
           if (GSN_SUCCESS != status)
           {
               //GSN_ASSERT(status == GSN_SUCCESS, GSN_ASSERT_DRIVER_FAILURE );
           }

           /* create the semaphore */
           GsnOsal_SemCreate  (&spiFsWriteLock,1);
           GsnOsal_SemCreate(&spiFsWriteBuffLock,1);
           s2wappMainTaskCtxt->s2wGetCharFn = AppS2wHal_SpiFsCharGet;
           s2wappMainTaskCtxt->s2wWriteFn   = AppS2wHal_SpiFsNCharPut;
           s2wappMainTaskCtxt->s2wPutCharFn = AppS2wHal_SpiFsCharPut;
           s2wappMainTaskCtxt->s2wGetNCharFn= AppS2wHal_SpiFsNCharGet;
         
       }
       else
       {/*ERROR:  SPI init failed */
           retStatus=S2W_FAILURE;
       }
   }
   break;
   #endif


   #ifdef S2W_UART_ENABLE
   case S2W_PORT_UART:
   {
       /* configure and open the s2w uart
        */
       s2wUart_Config(&tUartConfig);
       tUartConfig.uartBuffer = &(s2wSerialBuf[0]);
       tUartConfig.uartBuffSize = sizeof(s2wSerialBuf);
       if(tUartConfig.HwFlowSupport == GSN_UART_HW_SUPPORT)
       {
           GsnIoMux_Sel(24, GSN_IOMUX_GPIO_24_AUART0_CTS_N);
           GsnIoMux_Sel(25, GSN_IOMUX_GPIO_25_AUART0_RTS_N);
           GsnIoMux_PullDownDisable(25);		// uart rts. These together consume 125uA
           //GsnIoMux_PullDownDisable(24);      // CTS
       }
       //tUartConfig.HwFlowSupport = GSN_UART_HW_NO_SUPPORT;
       tUartConfig.swFlowSupport = GSN_UART_SWFLOW_NO_SUPPORT;
       tUartConfig.dmaSupport = GSN_UART_DMA_NO_SUPPORT;
       tUartConfig.uartClk = GSN_UART_CLK_XTAL;
       /* Important note:
        *  If you are changing the UART port number, then appropriate
        *  changes must be done in 'AppS2wHal_PsDpSleepStart()' function to configure
        *  the mux pin for deep-sleep wake-up and update the macro 'APP_S2W_UART_EXT_WAKEUP_GPIO_NUM'
        */
       //GsnClkCtl_Init(&gsnBrClkCtlCtx1);
       tUartStatus = GsnUart_Open( GSN_UART_0, &(s2wSerialPortHandle.uartHandle), &tUartConfig );
       if ( GSN_UART_STATUS_OK != tUartStatus )
       {/*ERROR: UART port open failed */
           retStatus=S2W_FAILURE;
       }
       else
       {

           /* configure sw flow support
         */

           GsnUart_SwFlowSupportSet(&s2wSerialPortHandle.uartHandle,
                                     (GSN_UART_SWFLOW_T)s2wCurrent.serialPortConf.conf.uart.softflow);
       }
#ifndef S2W_DUAL_INTERFACE_SUPPORT
       s2wappMainTaskCtxt->s2wGetCharFn  = AppS2wHal_UartCharGet;
#else
       s2wappMainTaskCtxt->s2wGetCharFn  = AppS2wHal_UartCharGetNB;
#endif
       s2wappMainTaskCtxt->s2wWriteFn    = AppS2wHal_UartWrite;
       s2wappMainTaskCtxt->s2wPutCharFn  = AppS2wHal_UartCharPut;
       s2wappMainTaskCtxt->s2wGetNCharFn = AppS2wHal_UartCharNGet;
       /* Install the GPIO interrupt and register call back function for edge triggered GPIO interrupt
        *  This call back function is used for deep-sleep wake-up detection and event posting */
       //GsnGpio_IntCbRegister(GSN_GPIO_INT_EDGE_TRIG,AppS2w_GpioEdgeIntCallBack,s2wappMainTaskCtxt);
   }
   break;
#endif

#ifdef S2W_SDIO_ENABLE
   case S2W_PORT_SDIO:
     {

        GSN_CLK_CTL_CTX_T *pClkCtlCtx;


        pClkCtlCtx = GsnClkCtl_CtxGet();

        GsnClkCtl_ClkSrcEnable( pClkCtlCtx, (GSN_CLK_CTL_CLK_SRC_T)GSN_CLK_CTL_CLK_SRC_HS_XTAL);

        GSN_STATUS sdioStatus;
       	ptSdioConfig.csaSupport = GSN_SDIO_CSA_SUPPORT;
        ptSdioConfig.sdioBufferStart = &(s2wSerialBuf[0]);
        ptSdioConfig.sdioBuffSize = sizeof(s2wSerialBuf);
             //GsnClkCtl_Init(&gsnBrClkCtlCtx2);
        sdioStatus = GsnSdio_Open (&(s2wSerialPortHandle.sdioHandle),&ptSdioConfig);

        if(GSN_SDIO_STATUS_OK  != sdioStatus )
        {
             retStatus=S2W_FAILURE;
             return 1;
         }


			 // create the semaphore
         GsnOsal_SemCreate  (&sdioWriteLock,1);
         s2wappMainTaskCtxt->s2wGetCharFn = AppS2wHal_SdioCharGet;
         s2wappMainTaskCtxt->s2wWriteFn   = AppS2wHal_SdioNCharPut;
         s2wappMainTaskCtxt->s2wPutCharFn = AppS2wHal_SdioCharPut;
         s2wappMainTaskCtxt->s2wGetNCharFn= AppS2wHal_SdioNCharGet;
             //while(1);
   }
   break;
#endif



   default:
       /* This shoul not happen */
       retStatus=S2W_FAILURE;
       break;
   }

   return retStatus;
}/* AppS2w_SerialPortInit */

#ifdef S2W_DUAL_INTERFACE_SUPPORT
PUBLIC UINT8
AppS2w_SerialPortInit2()
{
#ifdef S2W_SDIO_ENABLE_1
    GSN_SDIO_CONFIG_T ptSdioConfig;
#endif
#ifdef  S2W_FS_SPI_ENABLE_1
    GSN_SPI_CONFIG_T   spiConfig;       /* Temporary structure to hold serial port config parameter */
#endif
#ifdef  S2W_FS_SPI_HI_ENABLE_1
    GSN_SPI_FS_CONFIG_T   spiFsConfig;   /* Temporary structure to hold serial port config parameter */
#endif
#ifdef S2W_UART_ENABLE_1
 GSN_UART_CONFIG_T     uartConfig;
#endif
    S2W_SERIAL_PORT_ID_T  portId;        /* Serial device ID - SPI/UART */
    //UINT8 msgBuff[32] = "DataInterfaceReady";
    portId = s2wappMainTaskCtxt->serialDeviceId1;

    switch(portId)
    {
#ifdef S2W_UART_ENABLE_1

        case S2W_PORT_UART:
            GsnIoMux_Sel(32, GSN_IOMUX_GPIO_32_AUART1_TXD);
#ifdef GS2100
            GsnIoMux_Sel(30, GSN_IOMUX_GPIO_30_AUART1_RXD);
            GsnIoMux_Sel(33, GSN_IOMUX_GPIO_33_AUART1_RTS_N);
            GsnIoMux_Sel(34, GSN_IOMUX_GPIO_34_AUART1_CTS_N);

#else
            GsnIoMux_Sel(3, GSN_IOMUX_GPIO_3__AUART1_RXD);
            GsnIoMux_Sel(26,GSN_IOMUX_GPIO_26_AUART1_CTS_N);
            GsnIoMux_Sel(27,GSN_IOMUX_GPIO_27_AUART1_RTS_N);
#endif



            uartConfig.uartBuffer    =  s2wSerialBuf1;
            uartConfig.uartBuffSize  =  sizeof(s2wSerialBuf1);

            uartConfig.HwFlowSupport =  S2W_DFLT_INTERFACE2_UART_HWFLOW;
            uartConfig.swFlowSupport =  S2W_DFLT_INTERFACE2_UART_SWFLOW;
            uartConfig.dmaSupport    =  S2W_DFLT_INTERFACE2_UART_DMA;
            uartConfig.uartClk       =  GSN_UART_CLK_XTAL;
            uartConfig.eBaudRate     =  S2W_DFLT_INTERFACE2_UART_BAUD;
            uartConfig.eCharFormat   =  S2W_DFLT_INTERFACE2_UART_CHARFORMAT;
            uartConfig.eStopBits     =  S2W_DFLT_INTERFACE2_UART_STOPBITS;
            uartConfig.eParityBits   =  S2W_DFLT_INTERFACE2_UART_PARITY;
            GsnUart_Open( GSN_UART_1, &(s2wSerialPortHandle1.uartHandle), &uartConfig );
            //GsnUart_Write(&(s2wSerialPortHandle1.uartHandle),
            //    msgBuff, 20,
            //   NULL, NULL);

            //S2w_Printf1("jdahdha\r\n");

            s2wappMainTaskCtxt->s2wGetCharFn1  = AppS2wHal_UartCharGetNB1;
            s2wappMainTaskCtxt->s2wWriteFn1    = AppS2wHal_UartWrite1;
            s2wappMainTaskCtxt->s2wPutCharFn1  = AppS2wHal_UartCharPut1;
            s2wappMainTaskCtxt->s2wGetNCharFn1 = AppS2wHal_UartCharNGet1;

        break;
#endif //S2W_UART_ENABLE_1

#ifdef S2W_FS_SPI_HI_ENABLE_1
       case S2W_PORT_FS_SPI:
           GSN_STATUS status;
           GsnIoMux_Sel(33, GSN_IOMUX_GPIO_33_ASSP0_BI_CS);
           GsnIoMux_Sel(34, GSN_IOMUX_GPIO_34_ASSP0_DIN);
           GsnIoMux_Sel(35, GSN_IOMUX_GPIO_35_ASSP0_CLK);
           GsnIoMux_Sel(36, GSN_IOMUX_GPIO_36_ASSP0_DOUT);
           // gpio for spi
           GsnIoMux_Sel(37,GSN_IOMUX_GPIO_37_AGPIO_37);
           GsnIoMux_PullDownEnable (37);

#ifdef  S2W_SPI_HI_FS_CLK_PLL

          GsnClkCtl_SysPllEn(GSN_CLK_CTL_PLL_FREQ_120MHZ);
#else
           //GsnClkCtl_Init(&gsnBrClkCtlCtx1);
           cm3ClkCfg.pClkCtlCtx = GsnClkCtl_CtxGet();
           cm3ClkCfg.activeModeClkReq = GSN_CLK_CTL_CLK_SRC_HS_RC;
           cm3ClkCfg.sleepModeClkReq = GSN_CLK_CTL_CLK_SRC_HS_RC;
           cm3ClkCfg.deepSleepModeClkReq = (GSN_CLK_CTL_CLK_SRC_T)0;
           cm3ClkCfg.control = 1; //core control
           cm3ClkCfg.cm3ClkSel = GSN_CLK_SEL_HS_RC;
           GsnClkCtl_Cm3ClkCfg(&cm3ClkCfg);
           {
               GsnClkCtl_HsRcCal(&cm3ClkCfg);
           }
#endif
           /*Load the profile and configure SPI interface */
           spiFsConfig.spiRxBuffer         = &(s2wSerialBuf1[0]);    /* static buffer used for SPI recieve */
           spiFsConfig.spiRxBuffSize       = sizeof(s2wSerialBuf1);
           spiFsConfig.spiMode             = GSN_SPI_FS_OPERATION_MODE_SLAVE;
           spiFsConfig.spiProtocol         = GSN_SPI_FS_PROTOCOL_MOTOROLA;
           spiFsConfig.clockPolarity       = S2W_DFLT_INTERFACE2_SPI_POLARITY;//GSN_SPI_CLK_POL_INACTIVELOW;      // GSN_SPI_CLK_POL_INACTIVEHIGH.
           spiFsConfig.clockPhase          = S2W_DFLT_INTERFACE2_SPI_PHASE;//GSN_SPI_CLK_PHASE_180;            // GSN_SPI_CLK_PHASE_0.
           spiFsConfig.dataWordSize        = GSN_SPI_FS_DATAWORDSIZE_8;
           spiFsConfig.SerialclockRate     = 0;
           spiFsConfig.clockDivider        = 14;
#ifdef  S2W_SPI_HI_FS_CLK_PLL
           spiFsConfig.clockSelect         = GSN_SPI_FS_CLK_PLL;
#else
           spiFsConfig.clockSelect         = GSN_SPI_FS_CLK_HSRC;
#endif

           spiFsConfig.dmaMode             = GSN_SPI_FS_DMA_SET;
           spiFsConfig.sodMode             = GSN_SPI_FS_SOD_CLEAR;
           spiFsConfig.LoopBack            = GSN_SPI_FS_LoopBack_CLEAR;
           spiFsConfig.spiRxBuffer         = s2wSerialBuf1;
           spiFsConfig.spiRxBuffSize       = sizeof(s2wSerialBuf1);
           spiFsConfig.idleChar            = GSN_SPI_FS_IDLE_CHAR;
           spiFsConfig.byteStuff           = 0;
           spiFsConfig.spiGpioBitMap       = S2W_SPI_HOST_WAKEUP_GPIO_BITMAP;
           spiFsConfig.spiGpioNum          = S2W_SPI_HOST_WAKEUP_GPIO_NUM;


           status = GsnSpiFS_Open(&s2wSerialPortHandle1.spiFsHandle, GSN_FS_SPI_NUM_MSPI,&spiFsConfig);
           if (GSN_SUCCESS != status)
           {
               //GSN_ASSERT(status == GSN_SUCCESS, GSN_ASSERT_DRIVER_FAILURE );
           }

           /* create the semaphore */
           GsnOsal_SemCreate  (&spiFsWriteLock,1);
           GsnOsal_SemCreate(&spiFsWriteBuffLock,1);
           s2wappMainTaskCtxt->s2wGetCharFn1 = AppS2wHal_SpiFsCharGetNB1;
           s2wappMainTaskCtxt->s2wWriteFn1   = AppS2wHal_SpiFsNCharPut1;
           s2wappMainTaskCtxt->s2wPutCharFn1 = AppS2wHal_SpiFsCharPut1;
           s2wappMainTaskCtxt->s2wGetNCharFn1= AppS2wHal_SpiFsNCharGet1;

       break;

#endif //S2W_FS_SPI_HI_ENABLE_1

#ifdef  S2W_FS_SPI_ENABLE_1
      case S2W_PORT_SPI:
           //GSN_STATUS_T status;
           GsnIoMux_Sel(33, GSN_IOMUX_GPIO_33_ASSP0_BI_CS);
           GsnIoMux_Sel(34, GSN_IOMUX_GPIO_34_ASSP0_DIN);
           GsnIoMux_Sel(35, GSN_IOMUX_GPIO_35_ASSP0_CLK);
           GsnIoMux_Sel(36, GSN_IOMUX_GPIO_36_ASSP0_DOUT);
          // gpio for spi
           GsnIoMux_Sel(37,GSN_IOMUX_GPIO_37_AGPIO_37);
           GsnIoMux_PullDownEnable (37);
           /*Load the profile and configure SPI interface */
           spiConfig.spiRxBuffer   = &(s2wSerialBuf1[0]);    /* static buffer used for SPI recieve */
           spiConfig.spiRxBuffSize = sizeof(s2wSerialBuf1);
           //tSpiConfig.spiNum = S2W_DEFAULT_SPI_NUMBER;
           spiConfig.spiMode             = GSN_SPI_OPERATION_MODE_SLAVE;
           spiConfig.spiProtocol         = GSN_SPI_PROTOCOL_MOTOROLA;
           spiConfig.clockPolarity       = S2W_DFLT_INTERFACE2_SPI_POLARITY;//GSN_SPI_CLK_POL_INACTIVELOW;      // GSN_SPI_CLK_POL_INACTIVEHIGH.
           spiConfig.clockPhase          = S2W_DFLT_INTERFACE2_SPI_PHASE;//GSN_SPI_CLK_PHASE_180;            // GSN_SPI_CLK_PHASE_0.
           spiConfig.dataWordSize        = GSN_SPI_DATAWORDSIZE_8;
           spiConfig.SerialclockRate     = 0;
           spiConfig.clockDivider        = 100;   // 100 - 500Khz, 50 - 1Mhz.
           spiConfig.clockSelect         = GSN_SPI_CLK_HSRC;

           spiConfig.dmaMode             = GSN_SPI_DMA_CLEAR;
           spiConfig.sodMode             = GSN_SPI_SOD_CLEAR;
           spiConfig.LoopBack            = GSN_SPI_LoopBack_CLEAR;
           spiConfig.spiRxBuffer         = s2wSerialBuf1;
           spiConfig.spiRxBuffSize       = sizeof(s2wSerialBuf1);
           spiConfig.idleChar            = GSN_SPI_IDLE_CHAR;
           spiConfig.byteStuff           = 1;
               //GsnClkCtl_Init(&gsnBrClkCtlCtx1);
           GsnSpi_Open(&s2wSerialPortHandle1.spiHandle, GSN_SPI_NUM_MSPI,&spiConfig);
           //if (GSN_SUCCESS != status)
           {
               //GSN_ASSERT(status == GSN_SUCCESS, GSN_ASSERT_DRIVER_FAILURE );
           }

           // create the semaphore
           GsnOsal_SemCreate  (&spiWriteLock,1);
           s2wappMainTaskCtxt->s2wGetCharFn1 = AppS2wHal_SpiCharGetNB1;
           s2wappMainTaskCtxt->s2wWriteFn1   = AppS2wHal_SpiNCharPut1;
           s2wappMainTaskCtxt->s2wPutCharFn1 = AppS2wHal_SpiCharPut1;
           s2wappMainTaskCtxt->s2wGetNCharFn1= AppS2wHal_SpiNCharGet1;
           //s2wappMainTaskCtxt->s2wDpSleepWakeUpCallBack = AppS2w_DpSleepWakeUpCallBack;
           // initialize the gpio 37 for host wakeup
           GsnGpio_Init(APP_S2W_SPI_HOST_WAKEUP_GPIO_BITMAP, ~APP_S2W_SPI_HOST_WAKEUP_GPIO_BITMAP);
           GsnGpio_OutClear(APP_S2W_SPI_HOST_WAKEUP_GPIO_BITMAP);

     break;
#endif //S2W_FS_SPI_ENABLE_1


#ifdef S2W_SDIO_ENABLE_1
       case S2W_PORT_SDIO:
           GsnIoMux_Sel(32, GSN_IOMUX_GPIO_32_SDIO_DATA2);
           GsnIoMux_PullDownDisable(32);
           GsnIoMux_Sel(33, GSN_IOMUX_GPIO_33_SDIO_DATA3);
           GsnIoMux_PullDownDisable(33);
           GsnIoMux_Sel(34, GSN_IOMUX_GPIO_34_SDIO_CMD);
           GsnIoMux_PullDownDisable(34);
           GsnIoMux_Sel(35, GSN_IOMUX_GPIO_35_CLK_SDIO_PAD);
           GsnIoMux_PullDownDisable(35);
           GsnIoMux_Sel(36, GSN_IOMUX_GPIO_36_SDIO_DATA0);
           GsnIoMux_PullDownDisable(36);
           GsnIoMux_Sel(37, GSN_IOMUX_GPIO_37_SDIO_DATA1);
           GsnIoMux_PullDownDisable(37);
           GSN_CLK_CTL_CTX_T *pClkCtlCtx;

           pClkCtlCtx = GsnClkCtl_CtxGet();

           GsnClkCtl_ClkSrcEnable( pClkCtlCtx, (GSN_CLK_CTL_CLK_SRC_T)GSN_CLK_CTL_CLK_SRC_HS_XTAL);

           GSN_STATUS sdioStatus;
           ptSdioConfig.csaSupport = GSN_SDIO_CSA_SUPPORT;
           ptSdioConfig.sdioBufferStart = &(s2wSerialBuf1[0]);
           ptSdioConfig.sdioBuffSize = sizeof(s2wSerialBuf1);
             //GsnClkCtl_Init(&gsnBrClkCtlCtx2);
           sdioStatus = GsnSdio_Open (&(s2wSerialPortHandle1.sdioHandle),&ptSdioConfig);

           if(GSN_SDIO_STATUS_OK  != sdioStatus )
           {
               return 1;
           }
           // create the semaphore
           GsnOsal_SemCreate  (&sdioWriteLock,1);
           s2wappMainTaskCtxt->s2wGetCharFn1 = AppS2wHal_SdioCharGetNB1;
           s2wappMainTaskCtxt->s2wWriteFn1   = AppS2wHal_SdioNCharPut1;
           s2wappMainTaskCtxt->s2wPutCharFn1 = AppS2wHal_SdioCharPut1;
           s2wappMainTaskCtxt->s2wGetNCharFn1= AppS2wHal_SdioNCharGet1;
       break;
#endif //S2W_SDIO_ENABLE_1
    } // switch
    //S2w_Printf1("%s\r\n",msgBuff);
    return S2W_SUCCESS;
}/* AppS2w_SerialPortInit2 */

#endif


#ifdef S2W_WEB_FS_AVAILABLE
UINT32 
App_WebFsAddrGet(UINT32 cbAddr)
{
	GSN_BRFLASHLDR_CTL_BLOCK_T CtlBlk;
	UINT32 cbSize, /*flashBlkDescAddr,*/ fsAddr, fsSize;
	UINT8 *pControlBlock, *pBlkDesc, *pBlkDescEnd;
	
	GsnFlashCache_BlkFetch(cbAddr, (UINT32)&CtlBlk, sizeof(GSN_BRFLASHLDR_CTL_BLOCK_T), NULL);
	cbSize = CtlBlk.ctlBlockSize + sizeof(GSN_BRFLASHLDR_CTL_BLOCK_T);
	//S2w_Printf("Cb size %d", cbSize);
	pControlBlock = MALLOC(cbSize);
	if(pControlBlock == NULL)
	{
		return 0;
	}
	GsnFlashCache_BlkFetch(cbAddr, (UINT32)pControlBlock, cbSize, NULL);
	pBlkDesc  = pControlBlock + sizeof(GSN_BRFLASHLDR_CTL_BLOCK_T);
	pBlkDescEnd = pBlkDesc + CtlBlk.ctlBlockSize;
	while(pBlkDesc < pBlkDescEnd)
	{
		//S2w_Printf("Off %x, size %x", ((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->offset, ((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->size);
		if((((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->owner == GSN_BRFLASHLDR_BLOCK_OWNER_AFW) && 
				(((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->flags & GSN_BRFLASHLDR_BLOCK_DESC_FLAG_WEBFS))
		{
			fsAddr = (cbAddr + ((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->offset);
			fsSize = ((GSN_BRFLASHLDR_BLOCK_DESC_T *)pBlkDesc)->size;
			s2w_config_web_fs(fsAddr, fsSize);
			return fsAddr;
		}
		pBlkDesc += sizeof(GSN_BRFLASHLDR_BLOCK_DESC_T);
	}
	return 0;
}

extern UINT32 webFsOffset;
extern 	UINT32 romFwImageFlashAddr;
#endif

VOID
App_FsInit()
{
	UINT32 memsize;
	INT32 rc;
	UINT8 *pFsBuff;

    s2w_config_fs();
	f_init();
	f_enterFS();

	memsize = fs_getmem_flashdrive(fs_phy_nor_n25q_32mb_3v_65nm);
	pFsBuff = gsn_malloc(memsize);

    if(pFsBuff != NULL)
    {
		rc = f_mountdrive(0, pFsBuff, memsize, (void *)fs_mount_flashdrive,
			fs_phy_nor_n25q_32mb_3v_65nm);
		if(rc == F_ERR_NOTFORMATTED)
		{
			f_format(0);
		}
	}
#ifdef S2W_WEB_FS_AVAILABLE
	//S2w_Printf("\n\rCb1  %x", romFwImageFlashAddr);
	webFsOffset = App_WebFsAddrGet(romFwImageFlashAddr);
	//S2w_Printf("\n\rweb %x", webFsOffset);
	if(webFsOffset != 0)
	{
		memsize = fs_getmem_flashdrive(fs_phy_nor_n25q_32mb_3v_65nm_1);
		pFsBuff = gsn_malloc(memsize);
		if(pFsBuff != NULL)
		{
			rc = f_mountdrive(1, pFsBuff, memsize, (void *)fs_mount_flashdrive,
					fs_phy_nor_n25q_32mb_3v_65nm_1);
			//S2w_Printf("\n\rFS %d", rc);		
		}
	}
#endif	
}

PUBLIC VOID
AppS2wHttpd_Stop()
{
    /*De init Gslink URI */
#ifdef S2W_WEB_SERVER 

    if(s2wappMainTaskCtxt->webServerStatus == STOP)
    {
        AppS2w_WebServerStop();
    }

#endif
    /*De init Provisioning URI URI */
#ifdef S2W_WEB_PROV
    if(s2wappMainTaskCtxt->webProvStatus == STOP)
    {
        S2wWebProv_WebProvStop();
    }
#endif
        if(
#ifdef S2W_WEB_SERVER 

           (s2wappMainTaskCtxt->webServerStatus == IDLE) &&
#endif

#ifdef S2W_WEB_PROV
           (s2wappMainTaskCtxt->webProvStatus == IDLE) &&
#endif
            (TRUE == GsnHttpd_IsRunning()))
    {   //S_Printf("\r\n GsnHttpd_Stop" );
        GsnHttpd_Stop();
        //w_Printf("\r\n GsnHttpd_Stop1" );
        S2wApp_WebserverStack_Free(pS2wHttpdTaskStack);
        pS2wHttpdTaskStack = NULL;
    }

    GsnOsal_SemRelease(&s2wappMainTaskCtxt->webServerSync);
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w wlan Rssi get function.
 *    This function returns the rssi value.
 * @param VOID.
 * @retval UINT32 - the Rssi value.
 ******************************************************************/
PUBLIC INT8
AppS2wHal_RssiGet(void)
{
    GSN_WIF_WLAN_RSSI_T    wRssi;
    if(GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx) == FALSE)
    {
        return 0;
    }
    /* call the geps API to get the RSSI value.
     */
    GsnWdd_RSSIGet(&s2wappMainTaskCtxt->if0.wddCtx, (INT8*)&wRssi, sizeof(GSN_WIF_WLAN_RSSI_T));

    return wRssi.rssi;


}

PUBLIC UINT8
AppS2wHal_InfoGet(S2W_WLANINFO_T *info)
{
    if (s2wLinkState != S2W_LINK_STATE_CONNECTED)
    {
        return S2W_FAILURE;
    }
    memset(info,0,sizeof(*info));
    /*
     * current_wlan_info is updated on association/joining/creation using one of
     * update_info_from_element or update_info_from_params.
     */
    memcpy(info, &current_wlan_info, sizeof(*info));
    return S2W_SUCCESS;
}

PUBLIC VOID 
AppS2wHal_Cm3ClkCfg()
{
    UINT32 bootReason;
#ifdef GS2100M
	GsnRtc_ClkSrcSel(GSN_RTC_CLK_SRC_LP_RC);
#else
	GsnRtc_ClkSrcSel(GSN_RTC_CLK_SRC_LP_XTAL);
#endif
	cm3ClkCfg.pClkCtlCtx = GsnClkCtl_CtxGet();
    cm3ClkCfg.activeModeClkReq = GSN_CLK_CTL_CLK_SRC_HS_RC;
    cm3ClkCfg.sleepModeClkReq = GSN_CLK_CTL_CLK_SRC_HS_RC;
    cm3ClkCfg.deepSleepModeClkReq = (GSN_CLK_CTL_CLK_SRC_T)0;
    cm3ClkCfg.control = 1; //core control
    cm3ClkCfg.cm3ClkSel = GSN_CLK_SEL_HS_RC;
	GsnClkCtl_Cm3ClkCfg(&cm3ClkCfg);
	//GsnClkCtl_Cm3ClkSwitch(&cm3ClkCfg, GSN_CLK_SEL_HS_XTAL);
    bootReason = GSN_BOOT_REASON_GET();
 	if(bootReason == GSN_WIF_SYS_BOOT_FIRST_BOOT)
 	{
 		GsnClkCtl_HsRcCal(&cm3ClkCfg);
 	}
	
}

PUBLIC VOID
AppS2w_GpioWkUpDisable()
{
#ifdef S2W_UART_ENABLE
	GsnGpio_PEIntDisable_Patch(0x00000001);
	GsnGpio_PEIntClear(0x00000001);
	GsnIoMux_Sel(0, GSN_IOMUX_GPIO_0_AUART0_RXD);
#else

	GsnGpio_PEIntDisable_Patch(APP_S2W_SPI_WAKEUP_GPIO_BITMAP);
	GsnGpio_PEIntClear(APP_S2W_SPI_WAKEUP_GPIO_BITMAP);
#endif
}
PRIVATE VOID
AppS2w_DeepSleepTimerCb( VOID* context, UINT32 TimerHandle  )
{
	AppS2w_GpioWkUpDisable();
	if(s2wappMainTaskCtxt->dpSleep)
	{
		AppS2w_ExitDpSleep();
    }
}



PRIVATE VOID 
AppS2w_AlarmCb(VOID *pCtx)
{
	AppS2w_GpioWkUpDisable();
	if(s2wappMainTaskCtxt->dpSleep)
	{
	    //AppS2w_ExitDpSleep();
	    s2wappMainTaskCtxt->dpSleep = 0;
	    GsnRtc_AlarmDisable(GSN_RTC_ALARM_2);
	    GsnRtc_AlarmDisable(GSN_RTC_ALARM_3);
	    (s2wappMainTaskNotifier)(APP_EVENT_EXIT_DP_SLEEP, s2wappMainTaskCtxt);
	    GsnSoftTmr_Stop( &appDeepSleepTimer);
	}
}


PRIVATE VOID
AppS2w_GpioCb(UINT8 gpioNum, void *pCtx)
{
	AppS2w_GpioWkUpDisable();
	if(s2wappMainTaskCtxt->dpSleep)
	{
	    s2wappMainTaskCtxt->dpSleep = 0;
		(s2wappMainTaskNotifier)(APP_EVENT_EXIT_DP_SLEEP, s2wappMainTaskCtxt);
            //stop the timer
            GsnSoftTmr_Stop( &appDeepSleepTimer);
    }
}

PUBLIC VOID 
AppS2w_ExitDpSleep()
{
	S2W_SERIAL_PORT_ID_T serialId = APP_S2W_GET_SERIAL_DEVICE_ID();

#ifdef S2W_UART_ENABLE
		GSN_UART_CONFIG_T	  tUartConfig;
#endif
#ifdef  S2W_FS_SPI_ENABLE
		GSN_SPI_CONFIG_T   spiConfig;		/* Temporary structure to hold serial port config parameter */
#endif
#ifdef  S2W_FS_SPI_HI_ENABLE
		GSN_SPI_FS_CONFIG_T   spiFsConfig;		 /* Temporary structure to hold serial port config parameter */
#endif
    s2wappMainTaskCtxt->dpSleep = 0;
    GSN_PWR_MGMT_CM3_SLEEP_DEEP_DISABLE();
	GsnSoftTmr_Stop( &appDeepSleepTimer);
	GsnRtc_AlarmDeRegisterCb(GSN_RTC_ALARM_2);
	GsnRtc_AlarmDeRegisterCb(GSN_RTC_ALARM_3);
    GsnHeIf_DriverInit((UINT32 *)GSN_SYS_CRYPTO_SEED_LOCATION_GET());
#ifdef S2W_UART_ENABLE
   if(S2W_PORT_SPI != serialId)
   {
		s2wUart_Config(&tUartConfig);
		tUartConfig.uartBuffer = &(s2wSerialBuf[0]);
		tUartConfig.uartBuffSize = sizeof(s2wSerialBuf);
		tUartConfig.dmaSupport = GSN_UART_DMA_NO_SUPPORT;
		tUartConfig.uartClk = GSN_UART_CLK_XTAL;
		GsnIoMux_Sel(0, GSN_IOMUX_GPIO_0_AUART0_RXD);
		GsnUart_Open( GSN_UART_0, &(s2wSerialPortHandle.uartHandle), &tUartConfig );
	}
#endif
#ifdef S2W_FS_SPI_ENABLE
    if(S2W_PORT_SPI == serialId)
    {
		  GsnIoMux_Sel(35, GSN_IOMUX_GPIO_35_ASSP0_CLK);
          spiConfig.spiRxBuffer   = &(s2wSerialBuf[0]);    /* static buffer used for SPI recieve */
           spiConfig.spiRxBuffSize = sizeof(s2wSerialBuf);
           //tSpiConfig.spiNum = S2W_DEFAULT_SPI_NUMBER;
              spiConfig.spiMode             = GSN_SPI_OPERATION_MODE_SLAVE;
		       spiConfig.spiProtocol         = GSN_SPI_PROTOCOL_MOTOROLA;
		       spiConfig.clockPolarity       = s2wCurrent.serialPortConf.conf.spi.clockPolarity;
		       spiConfig.clockPhase          = s2wCurrent.serialPortConf.conf.spi.clockPhase;
		       spiConfig.dataWordSize        = GSN_SPI_DATAWORDSIZE_8;
		       spiConfig.SerialclockRate     = 0;
		       spiConfig.clockDivider        = 100;   // 100 - 500Khz, 50 - 1Mhz.
		       spiConfig.clockSelect         = GSN_SPI_CLK_HSRC;

		       spiConfig.dmaMode             = GSN_SPI_DMA_CLEAR;
		       spiConfig.sodMode             = GSN_SPI_SOD_CLEAR;
		       spiConfig.LoopBack            = GSN_SPI_LoopBack_CLEAR;
		       spiConfig.spiRxBuffer         = s2wSerialBuf;
		       spiConfig.spiRxBuffSize       = sizeof(s2wSerialBuf);
		       spiConfig.idleChar            = GSN_SPI_IDLE_CHAR;
		       spiConfig.byteStuff           = 1;
               //GsnClkCtl_Init(&gsnBrClkCtlCtx1);
		       GsnSpi_Open(&s2wSerialPortHandle.spiHandle, GSN_SPI_NUM_MSPI,&spiConfig);
	}
#endif

#ifdef S2W_FS_SPI_HI_ENABLE
   if(S2W_PORT_FS_SPI == serialId) // spi with dma
   {
	       GsnIoMux_Sel(35, GSN_IOMUX_GPIO_35_ASSP0_CLK);
#ifdef  S2W_SPI_HI_FS_CLK_PLL

           GsnClkCtl_SysPllEn(GSN_CLK_CTL_PLL_FREQ_120MHZ);
#else
#if 0
           //GsnClkCtl_Init(&gsnBrClkCtlCtx1);
           cm3ClkCfg.pClkCtlCtx = GsnClkCtl_CtxGet();
           cm3ClkCfg.activeModeClkReq = GSN_CLK_CTL_CLK_SRC_HS_RC;
           cm3ClkCfg.sleepModeClkReq = GSN_CLK_CTL_CLK_SRC_HS_RC;
           cm3ClkCfg.deepSleepModeClkReq = (GSN_CLK_CTL_CLK_SRC_T)0;
           cm3ClkCfg.control = 1; //core control
           cm3ClkCfg.cm3ClkSel = GSN_CLK_SEL_HS_RC;
           GsnClkCtl_Cm3ClkCfg(&cm3ClkCfg);
           {
              GsnClkCtl_HsRcCal(&cm3ClkCfg);
           }
#endif
#endif
           /*Load the profile and configure SPI interface */
           spiFsConfig.spiRxBuffer         = &(s2wSerialBuf[0]);    /* static buffer used for SPI recieve */
           spiFsConfig.spiRxBuffSize       = sizeof(s2wSerialBuf);
           spiFsConfig.spiMode             = GSN_SPI_FS_OPERATION_MODE_SLAVE;
           spiFsConfig.spiProtocol         = GSN_SPI_FS_PROTOCOL_MOTOROLA;
           spiFsConfig.clockPolarity       = s2wCurrent.serialPortConf.conf.spi.clockPolarity;
           spiFsConfig.clockPhase          = s2wCurrent.serialPortConf.conf.spi.clockPhase;
           spiFsConfig.dataWordSize        = GSN_SPI_FS_DATAWORDSIZE_8;
           spiFsConfig.SerialclockRate     = 0;
           spiFsConfig.clockDivider        = 14;
#ifdef  S2W_SPI_HI_FS_CLK_PLL
           spiFsConfig.clockSelect         = GSN_SPI_FS_CLK_PLL;
#else
           spiFsConfig.clockSelect         = GSN_SPI_FS_CLK_HSRC;
#endif

           spiFsConfig.dmaMode             = GSN_SPI_FS_DMA_SET;
           spiFsConfig.sodMode             = GSN_SPI_FS_SOD_CLEAR;
           spiFsConfig.LoopBack            = GSN_SPI_FS_LoopBack_CLEAR;
           spiFsConfig.spiRxBuffer         = s2wSerialBuf;
           spiFsConfig.spiRxBuffSize       = sizeof(s2wSerialBuf);
           spiFsConfig.idleChar            = GSN_SPI_FS_IDLE_CHAR;
           spiFsConfig.byteStuff           = 0;
           spiFsConfig.spiGpioBitMap       = S2W_SPI_HOST_WAKEUP_GPIO_BITMAP;
           spiFsConfig.spiGpioNum          = S2W_SPI_HOST_WAKEUP_GPIO_NUM;


           GsnSpiFS_Open(&s2wSerialPortHandle.spiFsHandle, GSN_FS_SPI_NUM_MSPI,&spiFsConfig);

	}

#endif
	AppS2w_DeepSleepHandler();
	GsnOsal_SemRelease(&(s2wappMainTaskCtxt->s2wDpSleepWakeUpSem));
}

/**
 ******************************************************************
* @ingroup S2w-Application
* @brief S2w deep sleep request function.
*    This function request for deep sleep feature of GS1010.
* @retval S2W_SUCCESS.
*
*  Detailed description:
*      Deep Sleep handling procedure is described below.
*
*   A) S2w application with UART interface:
*
*      1. Enable deep-sleep
*      2. Configure UART RX pin as GPIO
*      3. Enable GPIO interrupt 
*      4. Call back function (AppS2w_GpioEdgeIntCallBack) of edge triggered 
*         GPIO interrupt shall release the semaphore(wake-up event),  
*         if current state of the node is deep-sleep. This callback function is 
*         registered during UART port initialisation.
*
*      5.  Wait for wake-up event(i.e. wait on semaphore)
*  
*      6. After detecting wake-up event,
*         - Configure back UART RX pin
*         - Disable GPIO interrupt
*
*      7. Disable deep-sleep
*
*      B) S2w application with SPI interface:
*
*         1. Before enabling deep-sleep, de-assert the host wake-up signal
*         2. Enable deep-sleep
*         3. Enable SPI Slave Rx Wake-up interrupt
*         4. Call back function (AppS2w_DpSleepWakeUpCallBack) of SPI slave wake-up 
*            interrupt shall release the semaphore(wake-up event),  if current state of 
*            the node is deep-sleep. This callback function is registered during SPI port initialisation
*
*         5. Wait for wake-up event(i.e. wait on semaphore)
*         6. After detecting wake-up event,
*             - Reset SPI FIFO and recieve Q
*             - Re-enable the SPI block, so that it will properly sync-up with the MASTER SPI
*         7. Disable deep-sleep
*
******************************************************************/

PUBLIC UINT8
AppS2wHal_PsDpSleepStart(UINT32 timeout, S2W_ALARM_INFO_T* data, UINT8 pwrMeasure)
{
   s2wappMainTaskCtxt->dpSleep = 1;

	S2W_SERIAL_PORT_ID_T serialId = APP_S2W_GET_SERIAL_DEVICE_ID();

    GsnHeIf_DriverSuspend();
    
#ifdef S2W_UART_ENABLE
   if(S2W_PORT_SPI != serialId)
   {    
        GsnUart_Close( &(s2wSerialPortHandle.uartHandle)); 
        GsnIoMux_Sel(0, GSN_IOMUX_GPIO_0_AGPIO_0);
	    GsnGpio_Init( 0x00000001, 0x00000001 );  
	    GsnGpio_IntCbRegister(0 ,AppS2w_GpioCb,NULL);
	    GsnGpio_PEIntEnable(0x00000001);
   }
#endif
#ifdef S2W_FS_SPI_ENABLE
   if(S2W_PORT_SPI == serialId) // normal spi
   {
        GsnSpi_Close(&s2wSerialPortHandle.spiHandle);
        GsnIoMux_Sel(35, GSN_IOMUX_GPIO_35_AGPIO_35);
	    GsnGpio_Init( APP_S2W_SPI_WAKEUP_GPIO_BITMAP, APP_S2W_SPI_WAKEUP_GPIO_BITMAP );
	    GsnGpio_IntCbRegister(35 ,AppS2w_GpioCb,NULL);
	    GsnGpio_PEIntEnable(APP_S2W_SPI_WAKEUP_GPIO_BITMAP);
   }
#endif
#ifdef S2W_FS_SPI_HI_ENABLE
   if(S2W_PORT_FS_SPI == serialId) // spi with dma
   {
        GsnSpiFS_Close(&s2wSerialPortHandle.spiFsHandle);
        GsnIoMux_Sel(35, GSN_IOMUX_GPIO_35_AGPIO_35);
	    GsnGpio_Init( APP_S2W_SPI_WAKEUP_GPIO_BITMAP, APP_S2W_SPI_WAKEUP_GPIO_BITMAP );
	    GsnGpio_IntCbRegister(35 ,AppS2w_GpioCb,NULL);
	    GsnGpio_PEIntEnable(APP_S2W_SPI_WAKEUP_GPIO_BITMAP);
   }

#endif
  /* start the timer */
    if(timeout)
    {
        GsnSoftTmr_Start( &appDeepSleepTimer, GSN_SOFT_TMR_ONESHOT,
                  0, ((timeout * TIMER_INTERRUPT_5_MS)/5),
               ( GSN_SOFT_TMR_CBR_T )AppS2w_DeepSleepTimerCb, NULL );
    }

   
    if(data->alarm1Valid)
    {
        GsnRtc_AlarmConfig(GSN_RTC_ALARM_2, data->alarm1Pol, TRUE);
        GsnRtc_AlarmRegisterCb(GSN_RTC_ALARM_2, AppS2w_AlarmCb, NULL);
    }
    if(data->alarm2Valid)
    {
        GsnRtc_AlarmConfig(GSN_RTC_ALARM_3, data->alarm2Pol, TRUE);
        GsnRtc_AlarmRegisterCb(GSN_RTC_ALARM_3, AppS2w_AlarmCb, NULL);
    }

    if(pwrMeasure)
    {
        GsnSoftTmr_Stop(pSysTickTmrHndl);
    }

   /* Wait here till the node wakes-up */
    GsnOsal_SemAcquire(&(s2wappMainTaskCtxt->s2wDpSleepWakeUpSem), GSN_OSAL_WAIT_FOREVER);
    if(data->alarm1Valid)
    {
        GsnRtc_AlarmDisable(GSN_RTC_ALARM_2);
    }
    if(data->alarm2Valid)
    {
		GsnRtc_AlarmDisable(GSN_RTC_ALARM_3);
    }
    
    if(pwrMeasure)
    {
        pSysTickTmrHndl = GsnSoftTmr_Start(&sysTickTmr, GSN_SOFT_TMR_PERIODIC, 0,
                          MSEC_TO_SYSTIME(100), App_SysTickCb, NULL);
    }
   return S2W_SUCCESS;	
}


#ifdef S2W_SECURITY_WPS_ENABLE

#define APP_NCM_CFG_DFLT_WPS_USR_NAME   "WFA-SimpleConfig-Enrollee-1-0"
UINT32 wpsConnDone = FALSE;
UINT8 wpsL2ConInfoStore = FALSE;
GH_SEM stWpsAssSemaphore;
/*****************************************************************************
*  Private Functions
********s*********************************************************************/
VOID
AppS2wHal_WpsManageCredentials()
{
	UINT8 ssid[33];
	INT8 chnl[4];
	UINT8 passphrase[65];
	UINT8 WepKey[20];
	//UINT32 message;
	S2W_FLASH_PARAMS_T s2wProfileParm;
    S2W_PROFILE_T *pS2wProfile;
	UINT32 i;
	GSN_WDD_WLAN_CFG_T *wlanConfig = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);
	//wpsConnDone = FALSE;
    memset(&s2wProfileParm, 0, sizeof(S2W_FLASH_PARAMS_T));    
	pS2wProfile = &s2wCurrent;/*Store values in current profile*/	
	memcpy(ssid, wlanConfig->ssid.array, wlanConfig->ssid.length);
	ssid[wlanConfig->ssid.length]= '\0';
	sprintf(chnl, "%u", wlanConfig->channel[0]);

	S2w_Printf("\r\nSSID=%s\r\nCHANNEL=%s\r\n", ssid, chnl);		
	if ((wlanConfig->securityCfg.mode & GSN_WDD_SEC_MODE_WPA2_PERSONAL) ||
	 (wlanConfig->securityCfg.mode & GSN_WDD_SEC_MODE_WPA_PERSONAL))
	{
		if(0 != wlanConfig->securityCfg.pskConfig.passPhrase.Len)
	{
		memcpy(passphrase, wlanConfig->securityCfg.pskConfig.passPhrase.Passphrase,
			wlanConfig->securityCfg.pskConfig.passPhrase.Len);
		passphrase[wlanConfig->securityCfg.pskConfig.passPhrase.Len ]= '\0';
			S2w_Printf("PASSPHRASE=%s\r\n", passphrase);
	}
		else if(1 == wlanConfig->securityCfg.pskConfig.pskValid)
	{
		memcpy(passphrase,wlanConfig->securityCfg.pskConfig.psk,
				sizeof(wlanConfig->securityCfg.pskConfig.psk));
		passphrase[sizeof(wlanConfig->securityCfg.pskConfig.psk)] = '\0';

			S2w_Printf("PASSPHRASE=");
			for(i = 0; i<sizeof(wlanConfig->securityCfg.pskConfig.psk); i++)
			{
				S2w_Printf("%02x", passphrase[i]);
			}
			S2w_Printf("\r\n");
		}
	}
	else if(wlanConfig->securityCfg.mode & GSN_WDD_SEC_MODE_WEP) 
	{
		UINT8 i = 0;
		memcpy(WepKey, wlanConfig->securityCfg.wepConfig.Key,
			   wlanConfig->securityCfg.wepConfig.KeyLen);
		S2w_Printf("WEPKEY=");
		for(i=0;i<wlanConfig->securityCfg.wepConfig.KeyLen;i++)
		{
			S2w_Printf("%02x",WepKey[i]);
		}
		S2w_Printf("\r\nWEPKEYINDEX=%d\r\n", wlanConfig->securityCfg.wepConfig.KeyId+1);
	}	
	if(TRUE == wpsL2ConInfoStore )
	{
		pS2wProfile->autoWlandata.ssidLen = wlanConfig->ssid.length;
		memset(pS2wProfile->autoWlandata.ssid,0,S2W_MAX_SSID_LEN);
		memcpy(pS2wProfile->autoWlandata.ssid, wlanConfig->ssid.array,
				wlanConfig->ssid.length);
		pS2wProfile->netConf.dhcp = 1;
		pS2wProfile->autoWlandata.channel = wlanConfig->channel[0];

		if ((wlanConfig->securityCfg.mode & GSN_WDD_SEC_MODE_WPA2_PERSONAL) ||
				(wlanConfig->securityCfg.mode & GSN_WDD_SEC_MODE_WPA_PERSONAL))
		{
			/* 
				if the pskvalid  flag was set after  WPS , then reset the passpharse. 
			*/	
			if(0 != wlanConfig->securityCfg.pskConfig.passPhrase.Len)
			{
				pS2wProfile->security.wpa.pskValid = 0;
				memset(pS2wProfile->security.wpa.wpaPassPhrase,0,S2W_PSK_PASSPHRASE_LEN_MAX);
				memcpy(pS2wProfile->security.wpa.wpaPassPhrase, wlanConfig->securityCfg.pskConfig.passPhrase.Passphrase,
						wlanConfig->securityCfg.pskConfig.passPhrase.Len);
				pS2wProfile->security.wpa.passPhraseLen =wlanConfig->securityCfg.pskConfig.passPhrase.Len;
			}				
			else if(1 == wlanConfig->securityCfg.pskConfig.pskValid)			
			{
				memcpy(pS2wProfile->security.wpa.psk,
				wlanConfig->securityCfg.pskConfig.psk, GSN_WDD_SEC_PMK_LEN);
				pS2wProfile->security.wpa.pskValid = 1;
				memset(pS2wProfile->security.wpa.ssid,0,S2W_MAX_SSID_LEN);
				memcpy(pS2wProfile->security.wpa.ssid,wlanConfig->ssid.array,wlanConfig->ssid.length);
				pS2wProfile->security.wpa.ssidLen = wlanConfig->ssid.length;
				memset(pS2wProfile->security.wpa.wpaPassPhrase,0,S2W_PSK_PASSPHRASE_LEN_MAX);
				pS2wProfile->security.wpa.passPhraseLen =0;
			}
				
		}
		else if(wlanConfig->securityCfg.mode& GSN_WDD_SEC_MODE_WEP)
		{				
			pS2wProfile->security.wep.keyIdx = 0;
			pS2wProfile->security.wep.keyLen[0] = wlanConfig->securityCfg.wepConfig.KeyLen;
			memcpy(pS2wProfile->security.wep.key[0], wlanConfig->securityCfg.wepConfig.Key,
				   wlanConfig->securityCfg.wepConfig.KeyLen);
		}
		pS2wProfile->securityType= SECTYPE_AUTO;
#ifdef  S2W_NCM_SUPPORT_ENABLE
		if(s2wappMainTaskCtxt->ncmAutoConEn)
		{
			pS2wProfile->ncmAutoMgr =  1;			
			pS2wProfile->mode =  1;
		}
		else
			pS2wProfile->ncmAutoMgr = 0;
#endif
		memcpy(&s2wProfileParm.profile[0], pS2wProfile, sizeof(S2W_PROFILE_T));
		S2w_SaveS2wProfile(&s2wProfileParm, 0);
	}
}
PRIVATE VOID
AppS2w_WpsAssociateCb(VOID *pCtx, INT32 status)
{
	/*stop timer*/
	GsnSoftTmr_Stop(s2wappMainTaskCtxt->wlanRespHndl);
   // UINT32 msg = APP_EVENT_WPS_ASSOC;
    if (GSN_SUCCESS == status)
    {
        /* return AP credentiials */
        wpsConnDone = TRUE;
    }
	else if(status == GSN_FAILURE/*GSN_WDD_WPS_CONNECT_FAILURE*/)
	{
		 wpsConnDone = FALSE;
		 wpsL2ConInfoStore=FALSE;
		 //AppS2wHal_WpsManageCredentials();
    }
    else if(GSN_WDD_WPS_SESSION_OVERLAP == status || GSN_WDD_SSID_NOT_FOUND == status )
    {
        /* return error */
        wpsConnDone = FALSE;
    }
    else if( GSN_WDD_WPS_DONE == status )
    {
		 wpsConnDone = FALSE;
    		 //AppS2wHal_WpsManageCredentials();
    }
    GsnOsal_SemRelease(&stWpsAssSemaphore);
    //AppMainCtx_TaskNotify(msg);


}

VOID
AppS2w_WpsAssociateNotify(VOID *pCtx/*, INT32 status*/)
{
	GSN_WDD_WLAN_CFG_T *pWlanConfig = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);


    if(TRUE == wpsConnDone || TRUE == wpsL2ConInfoStore )
    {
    	if( GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx) == TRUE)
    	{
        s2wLinkState = S2W_LINK_STATE_CONNECTED;
		}
    	else
    	{
    		s2wLinkState = S2W_LINK_STATE_DISCONNECTED;
		}
        /* get the info */
        /*GsnWdd_WlanConfigGet(&s2wappMainTaskCtxt->wdd, &wlanConfig);*/

        /* copy to the info structure and return
        */
        /* copy the ssid and len  and channel
        */
        memcpy(current_wlan_info.ssid,pWlanConfig->ssid.array,
           pWlanConfig->ssid.length );
        current_wlan_info.ssidLen = pWlanConfig->ssid.length;

        /* associated ch will be at 0 index
        */
        current_wlan_info.channel = pWlanConfig->channel[0];

        memcpy(current_wlan_info.bssid, pWlanConfig->bssid.array,6);
        current_wlan_info.validBssid = 1;

        {
            current_wlan_info.mode = S2W_WLANDATA_MODE_INFRA;
        }

/* not required */
#if 0
        /* get the security info this can be modifed to present more info
        */
        if(capability & GSN_MAC_CAPA_PRIVA)
        {
            if (pWlanConfig->securityCfg.mode/*encryptionType*/ & GSN_WDD_SEC_MODE_WPA2_PERSONAL /*GSN_MAC_ENC_WPA2*/)
            {
                current_wlan_info.authMode = (GSN_WDD_SEC_MODE_T)S2W_AUTH_MODE_WPA2;
            }
            else if (pWlanConfig->securityCfg.mode /*encryptionType*/ & GSN_WDD_SEC_MODE_WPA_PERSONAL /*GSN_MAC_ENC_WPA*/)
            {
                current_wlan_info.authMode = (GSN_WDD_SEC_MODE_T)S2W_AUTH_MODE_WPA;
            }
            else if (pWlanConfig->securityCfg.wepConfig.authType == S2W_AUTH_MODE_OPEN)
            {
                /* Open with WEP cannot be identified from capabilities */
                current_wlan_info.authMode = (GSN_WDD_SEC_MODE_T)S2W_AUTH_MODE_OPEN;
            }
            else
            {
                current_wlan_info.authMode = (GSN_WDD_SEC_MODE_T)S2W_AUTH_MODE_SHARED;
            }
        }
        else
        {
            current_wlan_info.authMode = (GSN_WDD_SEC_MODE_T)S2W_AUTH_MODE_AUTO;
        }
#endif
    }
    else
    {
        s2wLinkState = S2W_LINK_STATE_DISCONNECTED;
    }

    //GsnOsal_SemRelease(&stWpsAssSemaphore);

}

#define S2W_WPS_TIMEOUT  (150)
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w wps associate function.
 *    This function associates to the wlan where the wps pbc/pin method
 *    enabled.If it already associated first it will do a dissociate and then
 *    Associates.
 * @param params - IN the wlan parameter structure pointer
 * @retval S2W_SUCCESS - operation successful.
 * @retval S2W_FAILURE - operation failure.
 ******************************************************************/
//UINT8 const  pin[8] =  {'4', '1', '0','8', '5', '1', '8', '9'};
PUBLIC UINT8
AppS2wHal_WpsAssociate(S2W_WPS_T *params, GSN_MAC_SSID_T *ap_ssid,UINT8 parentTask)
{
#if 1

    GSN_WDD_SECURITY_CONFIG_T *pSecConfig;
    UINT32 connectFlags = 0;
    GSN_STATUS retCode;
    UINT8 wpsUserName[] = APP_NCM_CFG_DFLT_WPS_USR_NAME;
    GSN_WDD_WLAN_CFG_T *pWlanConfig = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);

    wpsConnDone = FALSE;
	wpsL2ConInfoStore = params->storeL2ConInfo;
    UINT8 WpsUuid[16] = {'g','a','i','n','s', 'p', 'a', 'n'};

#ifdef GSN_SECURITY_WPS_REGISTRAR_ENABLE
    if(s2wCurrent.mode == 2)
    {
        UINT8 pbc = 1;
        if ( params->type == 2 || params->type == 3)
        {
            pbc = 0;
        }
        GsnWps_Trigger( &s2wappMainTaskCtxt->wdd, pbc,  params->pin );
        return S2W_SUCCESS;
    }
#endif

    /* if already associated, disassociate */
    if (s2wLinkState != S2W_LINK_STATE_DISCONNECTED)
    {
        /* disassociate */
		s2wappMainTaskCtxt->wlanRespHndl= GsnSoftTmr_Start(&s2wappMainTaskCtxt->wlanRespTmr,
						   GSN_SOFT_TMR_ONESHOT,0,
							SEC_TO_SYSTIME(S2W_WLAN_RESPTIMEOUT),
						  ( GSN_SOFT_TMR_CBR_T )AppS2w_WlanRespTmrCb,NULL);
        AppS2wHal_Disassociate(parentTask);

		GsnSoftTmr_Stop(s2wappMainTaskCtxt->wlanRespHndl);
    }
    if(params->type == 3)
        connectFlags = GSN_WDD_CONNECT_FLAG_WPS_WITH_DFLT_PIN_METHOD;
    /* Get pointer to security config in NW config */
    pSecConfig = &pWlanConfig->securityCfg;

    /* We will wait on this semaphore after issueing the GsnWdd_connect().
    This will be released by wddConnect_cb() */
    GsnOsal_SemCreate(&stWpsAssSemaphore, 0);

    /* Set defaults */
    GsnWdd_WlanConfigDefaultInit(pWlanConfig);
    if(0 != s2wCurrent.listenInterval)
    {   /* overide the default. Set the configured listenInterval*/
        pWlanConfig->staSpecificCfg.listenInterval = s2wCurrent.listenInterval;
    }
    memcpy(pWlanConfig->ssid.array, ap_ssid->array, ap_ssid->length);
    pWlanConfig->ssid.length = ap_ssid->length;

    /* Compute private and public enrolee keys */
#if 0/*PSK key calculation is now done in wdd task context*/
    GsnFlashSplit_SuppWpsKeyCompute(pSecConfig->wpsConfig.privateKey,
                                pSecConfig->wpsConfig.publicKey);
//#else

	{
		UINT32 msg;

		s2wappMainTaskCtxt->pParamsExecInWddTsk = (VOID *)pSecConfig;
		/*post message */
		msg = S2W_MOD_NOTIF_WPS_KEY_CALC;

		GsnOsal_SemCreate(&s2wappMainTaskCtxt->lockExecInWddTsk, 0);

		GsnMsgHandler_Post(s2wappMainTaskCtxt->pMsgHdlrExecInWddTsk, &msg);

		GsnOsal_SemAcquire(&s2wappMainTaskCtxt->lockExecInWddTsk,GSN_OSAL_WAIT_FOREVER);
		GsnOsal_SemDelete(&s2wappMainTaskCtxt->lockExecInWddTsk);
  	}
#endif
    /* Now initiate wps connection */

    /* Prepare connection request flags */
    //connectFlags |= GSN_WDD_CONNECT_FLAG_SCAN_BEFORE_CONNECT;
    //connectFlags |= GSN_WDD_CONNECT_FLAG_ACTIVE_SCAN;
	connectFlags |= GSN_WDD_CONNECT_FLAG_WPS_MATHOD;
    //connectFlags |= GSN_WDD_CONNECT_FLAG_WPS_REGISTER;
#ifdef S2W_WPS_CERTIFICATION
    connectFlags |= GSN_WDD_CONNECT_FLAG_WPS_CERTIFICATION;
#endif
    /* Get the pin */
    memcpy(pSecConfig->wpsConfig.pin, params->pin , sizeof(pSecConfig->wpsConfig.pin));

    /* Get user name */
    pSecConfig->eapConfig.userName.Length = strlen((const char *)wpsUserName);
    memcpy(pSecConfig->eapConfig.userName.Name, wpsUserName,
           strlen((const char *)wpsUserName));

    /*set the channel list*/
    {
#if 0
          UINT8 domain;
          AppCfg_Get( APP_CFG_REG_DOMAIN_ID, &domain );
          AppS2w_ChannelFill(&s2wappMainTaskCtxt->if0.wddCtx,&pWlanConfig->wlanConfig.channel[0],domain);
#else
		pWlanConfig->channel[0] = 1;
		pWlanConfig->channel[1] = 2;
#if 1
		pWlanConfig->channel[2] = 3;
		pWlanConfig->channel[3] = 4;
		pWlanConfig->channel[4] = 5;
		pWlanConfig->channel[5] = 6;
		pWlanConfig->channel[6] = 7;
		pWlanConfig->channel[7] = 8;
		pWlanConfig->channel[8] = 9;
		pWlanConfig->channel[9] = 10;
		pWlanConfig->channel[10] = 11;
        pWlanConfig->channel[11] = 0;
        switch(s2wCurrent.regDomain)
        {
			case S2W_DOMAIN_FCC:
				pWlanConfig->channel[11] = 0;
			break;
			case S2W_DOMAIN_ETSI:
				pWlanConfig->channel[11] = 12;
				pWlanConfig->channel[12] = 13;
				pWlanConfig->channel[13] = 0;
			break;
			case S2W_DOMAIN_TELEC:
				pWlanConfig->channel[11] = 12;
				pWlanConfig->channel[12] = 13;
				pWlanConfig->channel[13] = 14;
				pWlanConfig->channel[14] = 0;
			break;
			default:
				pWlanConfig->channel[11] = 0;
			break;
		}
#endif

		//memcpy(pWlanConfig->securityCfg.wpsConfig.pin, pin, 8);
		//pWlanConfig->securityCfg.wpsConfig.pin[] =
		pSecConfig->wpsConfig.pDeviceName = "GainSpan WiFi Module";
		pSecConfig->wpsConfig.pManufacturer = "GainSpan";
		pSecConfig->wpsConfig.pModelName = S2W_HW_VERSION;
		pSecConfig->wpsConfig.pModelNumber = "2000";
		pSecConfig->wpsConfig.pSerialNumber = "12345678";
		pSecConfig->wpsConfig.rfBands = (GSN_WDD_WPS_RF_T)0x01;

        WpsUuid[7] &= 0x1F;
        WpsUuid[8] = 11;
        WpsUuid[9] = 12;
        GsnWdd_PhyAddrGet(&s2wappMainTaskCtxt->if0.wddCtx, (INT8 *)&WpsUuid[10]);
		pSecConfig->wpsConfig.pUuid = WpsUuid;


		pSecConfig->wpsConfig.pFriendlyName = NULL;
		pSecConfig->wpsConfig.pManufacturerUrl = "gainspan.com";
		pSecConfig->wpsConfig.pModelDescription = NULL;
		pSecConfig->wpsConfig.pModelUrl = NULL;
		pSecConfig->wpsConfig.pUpc = NULL;

		//pWlanConfig->securityCfg.wpsConfig.configMethods = GSN_WDD_WPS_CONFIG_LABEL;
#if 0
		if(params->type == APP_WPS_TYPE_PB)
		{
			pSecConfig->wpsConfig.configMethods = GSN_WDD_WPS_CONFIG_PUSHBUTTON;
		}
		if(params->type == APP_WPS_TYPE_PIN)
		{
			memcpy(pSecConfig->wpsConfig.pin, params->pin, sizeof(pSecConfig->wpsConfig.pin));
			pSecConfig->wpsConfig.configMethods = GSN_WDD_WPS_CONFIG_LABEL;
		}
#else
		pWlanConfig->securityCfg.wpsConfig.configMethods = (GSN_WDD_WPS_CONFIG_METHOD_T)(GSN_WDD_WPS_CONFIG_LABEL |
			    GSN_WDD_WPS_CONFIG_PUSHBUTTON |
			    GSN_WDD_WPS_CONFIG_VIRT_PUSHBUTTON);
#endif
		/* Only thing that needs to be */

#endif
    }

    GsnWdd_WlanConfigSet(&s2wappMainTaskCtxt->if0.wddCtx, pWlanConfig);

	/* start the timer*/
	s2wappMainTaskCtxt->wlanRespHndl= GsnSoftTmr_Start(&s2wappMainTaskCtxt->wlanRespTmr,
					   GSN_SOFT_TMR_ONESHOT,0,
						SEC_TO_SYSTIME(S2W_WPS_TIMEOUT),
					  ( GSN_SOFT_TMR_CBR_T )AppS2w_WlanRespTmrCb,NULL);

    /* Init crypto engine */
    GsnHeIf_DriverInit((UINT32 *)GSN_SYS_CRYPTO_SEED_LOCATION_GET());

    /* do L2 connection using WPS */
    retCode = GsnWdd_Connect(&s2wappMainTaskCtxt->if0.wddCtx,
                                (GSN_WDD_CONNECT_FLAG_T)connectFlags, pWlanConfig, NULL,
                                AppS2w_WpsAssociateCb, NULL);
    if(retCode != GSN_OPERATION_IN_PROGRESS)
    {
        /* it should be failuer */
        AppS2w_WpsAssociateCb(NULL, GSN_FAILURE);
    }

    /* wait for the call back to be get called */
    GsnOsal_SemAcquire( &stWpsAssSemaphore, GSN_OSAL_WAIT_FOREVER);

    /*Disable crypto */
    GsnHeIf_DriverSuspend();
    
    AppS2w_WpsAssociateNotify(s2wappMainTaskCtxt);
    if( wpsL2ConInfoStore == TRUE && wpsConnDone == FALSE )
    {
    	//wpsL2ConInfoStore = FALSE;
    	AppS2wHal_WpsManageCredentials();
    }
    else if(wpsConnDone == TRUE)
    {
		AppS2wHal_WpsManageCredentials();
		/*Clear Scan data base in Wlan*/
		//GsnWif_ClearScanDataBase(&s2wappMainTaskCtxt->if0.wifCtx);
#if 0
        /* start the ps poll */
        if(appRtcMemData.KeepAliveIntrvl == 0)
        {
            appRtcMemData.KeepAliveIntrvl = S2W_DEFAULT_KEEP_ALIVE_INTRVL;
        }
        AppS2wHal_PsPollIntervelset(appRtcMemData.KeepAliveIntrvl);
#endif
        retCode = S2W_SUCCESS;
#if 0
 if((status == GSN_SUCCESS) && (TRUE == GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx)))

        {
            GSN_NWIF_IP_CONFIG_T ipConfig;
            memset(&ipConfig,0,sizeof(ipConfig));
            GsnNwIf_Close(&s2wappMainTaskCtxt->if0.nwifCtx);
			ipConfig.flag =  GSN_NWIF_IPCONFIG_FLAG_IPV4_INIT
#ifdef S2W_IPv6_SUPPORT  
                         // | GSN_NWIF_IPCONFIG_FLAG_IPV6_INIT
#endif
                            ;
            ipConfig.ipv4.staticIp = !s2wCurrent.netConf.dhcp;
            if(ipConfig.ipv4.staticIp) // static ip
            {
                memcpy((UINT8*)&ipConfig.ipv4.ipAddr,s2wCurrent.netConf.ipAddr,4);
                memcpy((UINT8*)&ipConfig.ipv4.subnetMask, s2wCurrent.netConf.netMask, 4);
                memcpy((UINT8*)&ipConfig.ipv4.gatewayIpAddr,s2wCurrent.netConf.gateway,4);
                memcpy((UINT8*)&ipConfig.ipv4.dnsPriSrvrIp,s2wCurrent.dns1,4);
                memcpy((UINT8*)&ipConfig.ipv4.dnsSecSrvrIp,s2wCurrent.dns2,4);
                S2wL3Wait = TRUE;
            }
            s2wappMainTaskCtxt->if0.nwifCtx.notifyCb = DHCP_notify;
            memset(&dhcpParams,0,sizeof(dhcpParams));
            dhcpParams.dhcpMaxRetryCnt = S2W_DHCP_MAX_RETRY_COUNT;
              S2wL3Wait = TRUE;
           
            status = GsnNwIf_Open(&s2wappMainTaskCtxt->if0.nwifCtx, &ipConfig, &dhcpParams);
             if(status != GSN_OPERATION_IN_PROGRESS)
                {
                    DHCP_notify(status,NULL);
                }
            GsnOsal_SemAcquire ( &s2wL2L3ConnectSemaphore, GSN_OSAL_WAIT_FOREVER );
            if(L3ConnectStatus)
            {
                AppS2wHdrAndIp_Print();
			}

        }
    }
	if((GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx) == TRUE) && (L3ConnectStatus==1))
        {
                S2wL3Wait = FALSE;
                nx_arp_gratuitous_send(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl,NULL);
		return S2W_SUCCESS;
        }
        else if((GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx) == TRUE) && (L3ConnectStatus==0))
        {
                GsnNwIf_Close(&s2wappMainTaskCtxt->if0.nwifCtx);
                S2wL3Wait = FALSE;
            AppS2wProcess_DhcpFailNotify();
		return S2W_FAILURE;
        }
        else
          return S2W_FAILURE;
#endif
    }
    else
    {
        retCode = S2W_FAILURE;
    }
    /* Set the security to auto */
    s2wCurrent.securityType = 0;
    GsnOsal_SemDelete(&stWpsAssSemaphore);
    return retCode;


#else
	UINT8 wepKey[5]={0x11, 0x22, 0x33, 0x44, 0x55};
	UINT8 wepKey104[13]={0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd};
	UINT8 channelList[12] = {11};//{1,2,3,4,5,6,7,8,9,10,11};
	GSN_WDD_WLAN_CFG_T *pWlanConfig;
	GSN_WDD_CONNECT_FLAG_T flags;

	/*Connect request */
	pWlanConfig = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);
	GsnWdd_WlanConfigDefaultInit(pWlanConfig);
	pWlanConfig->ssid.length = 0;//strlen("GSDemo_B3");
	memcpy((INT8 *)pWlanConfig->ssid.array, "GSDemo_B3", pWlanConfig->ssid.length);
	pWlanConfig->channel[0] = 11;
	pWlanConfig->channel[1] = 0;

	/* Only thing that needs to be configured is the channel list*/
	memcpy(pWlanConfig->channel, channelList, 11);

	//memcpy(pWlanConfig->securityCfg.wpsConfig.pin, pin, 8);
    //pWlanConfig->securityCfg.wpsConfig.pin[] =
    pWlanConfig->securityCfg.wpsConfig.pDeviceName = "GS2000";
    pWlanConfig->securityCfg.wpsConfig.pManufacturer = "GainSpan";
    pWlanConfig->securityCfg.wpsConfig.pModelName = "wdd Test App";
    pWlanConfig->securityCfg.wpsConfig.pModelNumber = "2000";
    pWlanConfig->securityCfg.wpsConfig.pSerialNumber = "test1234";
    /*pWlanConfig->securityCfg.wpsConfig.rfBands;*/
    pWlanConfig->securityCfg.wpsConfig.pUuid = "gainspan.com";
    pWlanConfig->securityCfg.wpsConfig.pFriendlyName = NULL;
    pWlanConfig->securityCfg.wpsConfig.pManufacturerUrl = "gainspan.com";
    pWlanConfig->securityCfg.wpsConfig.pModelDescription = NULL;
    pWlanConfig->securityCfg.wpsConfig.pModelUrl = NULL;
    pWlanConfig->securityCfg.wpsConfig.pUpc = NULL;
    pWlanConfig->securityCfg.wpsConfig.configMethods = GSN_WDD_WPS_CONFIG_PUSHBUTTON;
    //pWlanConfig->securityCfg.wpsConfig.configMethods = GSN_WDD_WPS_CONFIG_LABEL;   

	/* Only thing that needs to be */
	flags = GSN_WDD_CONNECT_FLAG_WPS_MATHOD;

	GsnWdd_Connect(&s2wappMainTaskCtxt->if0.wddCtx, flags, pWlanConfig, NULL, 
				   App_ConnectCb, NULL);
    return S2W_SUCCESS;
#if 0

    GSN_WDD_SECURITY_CONFIG_T *pSecConfig;
    UINT32 connectFlags = 0;
    GSN_STATUS retCode;
    UINT8 wpsUserName[] = APP_NCM_CFG_DFLT_WPS_USR_NAME;
    GSN_WDD_WLAN_CFG_T *pWlanConfig = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);
    S2W_PROFILE_T *pS2wProfile;
    wpsConnDone = FALSE;
	pS2wProfile = &s2wCurrent;/*Store values in current profile*/
	wpsL2ConInfoStore = params->storeL2ConInfo;
	
	
#ifdef GSN_SECURITY_WPS_REGISTRAR_ENABLE    
    if(s2wCurrent.mode == 2)
    {
        UINT8 pbc = 1;
        if ( params->type == 2 )
        {
            pbc = 0;
        }
        GsnWps_Trigger( &s2wappMainTaskCtxt->wdd, pbc,  params->pin );
        return S2W_SUCCESS;
    }
#endif

    /* if already associated, disassociate */
    if (s2wLinkState != S2W_LINK_STATE_DISCONNECTED)
    {
        /* disassociate */
        AppS2wHal_Disassociate(parentTask);

    }

    /* Get pointer to security config in NW config */
    pSecConfig = &pWlanConfig->securityCfg;

    /* We will wait on this semaphore after issueing the GsnWdd_connect().
    This will be released by wddConnect_cb() */
    GsnOsal_SemCreate(&stWpsAssSemaphore, 0);

    /* Set defaults */
    GsnWdd_WlanConfigDefaultInit(pWlanConfig);
    if(0 != s2wCurrent.listenInterval)
    {   /* overide the default. Set the configured listenInterval*/
        pWlanConfig->staSpecificCfg.listenInterval = s2wCurrent.listenInterval;
    }
    memcpy(pWlanConfig->ssid.array, ap_ssid->array, ap_ssid->length);
    pWlanConfig->ssid.length = ap_ssid->length;

    /* Compute private and public enrolee keys */
#if 1/*PSK key calculation is now done in wdd task context*/
    GsnFlashSplit_SuppWpsKeyCompute(pSecConfig->wpsConfig.privateKey,
                                pSecConfig->wpsConfig.publicKey);
#else

	{
		UINT32 msg;
		
		s2wappMainTaskCtxt->pParamsExecInWddTsk = (VOID *)pSecConfig;
		/*post message */
		msg = S2W_MOD_NOTIF_WPS_KEY_CALC;
		
		GsnOsal_SemCreate(&s2wappMainTaskCtxt->lockExecInWddTsk, 0);
		
		GsnMsgHandler_Post(s2wappMainTaskCtxt->pMsgHdlrExecInWddTsk, &msg);
		
		GsnOsal_SemAcquire(&s2wappMainTaskCtxt->lockExecInWddTsk,GSN_OSAL_WAIT_FOREVER);
		GsnOsal_SemDelete(&s2wappMainTaskCtxt->lockExecInWddTsk);		
  	}
#endif
    /* Now initiate wps connection */

    /* Prepare connection request flags */
    connectFlags |= GSN_WDD_CONNECT_FLAG_SCAN_BEFORE_CONNECT;
    connectFlags |= GSN_WDD_CONNECT_FLAG_ACTIVE_SCAN;
    connectFlags |= GSN_WDD_CONNECT_FLAG_WPS_MATHOD;

    /* Get the pin */
    memcpy(pSecConfig->wpsConfig.pin, params->pin , sizeof(params->pin));

    /* Get user name */
    pSecConfig->eapConfig.userName.Length = strlen((const char *)wpsUserName);
    memcpy(pSecConfig->eapConfig.userName.Name, wpsUserName,
           strlen((const char *)wpsUserName));

    /*set the channel list*/
    {
          UINT8 domain;
          AppCfg_Get( APP_CFG_REG_DOMAIN_ID, &domain );
          AppS2w_ChannelFill(&s2wappMainTaskCtxt->wdd,&pWlanConfig->channel[0],domain);
    }

    GsnWdd_WlanConfigSet(&s2wappMainTaskCtxt->wdd, pWlanConfig);


    /* do L2 connection using WPS */
    retCode = GsnWdd_Connect(&s2wappMainTaskCtxt->wdd,
                                connectFlags, NULL,
                                AppS2w_WpsAssociateCb, NULL);
    if(retCode != GSN_OPERATION_IN_PROGRESS)
    {
        /* it should be failuer */
        AppS2w_WpsAssociateCb(GSN_FAILURE, NULL);
    }

    /* wait for the call back to be get called */
    GsnOsal_SemAcquire( &stWpsAssSemaphore, GSN_OSAL_WAIT_FOREVER);

    if(wpsConnDone == TRUE)
    {

        UINT8 ssid[33];
        INT8 chnl[4];
        UINT8 passphrase[65];
        UINT8 WepKey[20];
		UINT32 message;
		
        GSN_WDD_WLAN_CONFIG_T *wlanConfig = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->wdd);

        /* Get  AP credentials */
        /*GsnWdd_WlanConfigGet(&s2wappMainTaskCtxt->wdd ,wlanConfig);*/

        memcpy(ssid, wlanConfig->ssid.array, wlanConfig->ssid.length);
        ssid[wlanConfig->ssid.length]= '\0';
        sprintf(chnl, "%u", wlanConfig->channel[0]);

        memcpy(passphrase, wlanConfig->securityConfig.pskConfig.passPhrase.Passphrase,
                wlanConfig->securityConfig.pskConfig.passPhrase.Len);
        passphrase[wlanConfig->securityConfig.pskConfig.passPhrase.Len]= '\0';
        /* Send  AP credentials */
        //S2w_Printf("\r\nSSID=%s\r\nCHANNEL=%s\r\nPASSPHRASE=%s\r\n", ssid, chnl, passphrase);
        S2w_Printf("\r\nSSID=%s\r\nCHANNEL=%s\r\n", ssid, chnl);
        if(GSN_MAC_CAPA_PRIVA & wlanConfig->capabilityInfo)
        {
            if ((wlanConfig->securityConfig.encryptionType & GSN_MAC_ENC_WPA2) ||
             (wlanConfig->securityConfig.encryptionType & GSN_MAC_ENC_WPA))
            {
                S2w_Printf("PASSPHRASE=%s\r\n", passphrase);
            }
            else
            {
                UINT8 i = 0;
                memcpy(WepKey, wlanConfig->securityConfig.wepConfig.Key,
                       wlanConfig->securityConfig.wepConfig.KeyLen);

                S2w_Printf("WEPKEY=");
                for(i=0;i<wlanConfig->securityConfig.wepConfig.KeyLen;i++)
                {
                    S2w_Printf("%02x",WepKey[i]);
                }
                //S2w_Printf("\r\nWEPKEYINDEX=%d", wlanConfig->securityConfig.wepConfig.KeyId+1);
                //S2w_Printf("\r\n");
                S2w_Printf("\r\nWEPKEYINDEX=%d\r\n", wlanConfig->securityConfig.wepConfig.KeyId+1);
            }
        }
		if(TRUE == wpsL2ConInfoStore)
		{
			pS2wProfile->autoWlandata.ssidLen = wlanConfig->ssid.length;
			memcpy(pS2wProfile->autoWlandata.ssid, wlanConfig->ssid.array,
					wlanConfig->ssid.length);
			pS2wProfile->autoWlandata.channel = wlanConfig->channel[0];
			if(GSN_MAC_CAPA_PRIVA & wlanConfig->capabilityInfo)
	        {
	            if ((wlanConfig->securityConfig.encryptionType & GSN_MAC_ENC_WPA2) ||
	             	(wlanConfig->securityConfig.encryptionType & GSN_MAC_ENC_WPA))
	            {
	            	switch(wlanConfig->securityConfig.authType)
				    {
				       case GSN_MAC_AUTH_WPAPSK:
					   		pS2wProfile->securityType = SECTYPE_WPAPSK;
				       		break;
					    case GSN_MAC_AUTH_WPA:
					   		pS2wProfile->securityType = SECTYPE_WPA;
				       		break;
				       case GSN_MAC_AUTH_WPA2PSK:
					   		pS2wProfile->securityType = SECTYPE_WPA2PSK;
				       		break;
				       case GSN_MAC_AUTH_WPA2:
					   		pS2wProfile->securityType= SECTYPE_WPA2;
				       		break;

				    }
					pS2wProfile->security.wpa.passPhraseLen = strlen((const char *)passphrase);
					memcpy(pS2wProfile->security.wpa.wpaPassPhrase, passphrase, strlen((const char *)passphrase));
	            }
	            else if(wlanConfig->securityConfig.encryptionType & GSN_MAC_ENC_WEP)
	            {
	                UINT8 i = 0;
					pS2wProfile->securityType= SECTYPE_WEP;
					pS2wProfile->security.wep.keyIdx = 0;
					pS2wProfile->security.wep.keyLen[0] = wlanConfig->securityConfig.wepConfig.KeyLen;
	                memcpy(pS2wProfile->security.wep.key[0], wlanConfig->securityConfig.wepConfig.Key,
	                       wlanConfig->securityConfig.wepConfig.KeyLen);
	            }
				else
				{
					pS2wProfile->securityType= SECTYPE_NONE;
				}
	        }
			
#ifdef  S2W_NCM_SUPPORT_ENABLE
			/*update the mode if ncmauto connect is enabled*/
			if(s2wappMainTaskCtxt->ncmAutoConEn)
			{
				pS2wProfile->ncmAutoMgr =  1;			
				pS2wProfile->mode =  0;
			}
			else
				pS2wProfile->ncmAutoMgr = 0;
#endif
			memcpy(&s2wProfileParm.params.profile[0], pS2wProfile, sizeof(S2W_PROFILE_T));
			GsnNvds_Write(APPMIB_ID_PROFILE, 0, sizeof(s2wProfileParm),
		                        &s2wProfileParm);
		}
		
		/*Clear Scan data base in Wlan*/
		GsnWif_ClearScanDataBase(&s2wappMainTaskCtxt->wifCtx);
		
        /* start the ps poll */
        if(appRtcMemData.KeepAliveIntrvl == 0)
        {
            appRtcMemData.KeepAliveIntrvl = S2W_DEFAULT_KEEP_ALIVE_INTRVL;
        }
        AppS2wHal_PsPollIntervelset(appRtcMemData.KeepAliveIntrvl);
        retCode = S2W_SUCCESS;
    }
    else
    {
        retCode = S2W_FAILURE;
    }
    GsnOsal_SemDelete(&stWpsAssSemaphore);
    return retCode;
#endif
#endif
}
#if 0
/*****************************************************************************
*  Private Functions
********s*********************************************************************/
PRIVATE VOID
AppS2w_WpsAssociateCb(INT32 status, VOID *pCtx)
{
    GSN_WDD_WLAN_CONFIG_T *pWlanConfig = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->wdd);
    UINT16 capability;

    if (GSN_SUCCESS == status)
    {
        /* return AP credentiials */
        wpsConnDone = TRUE;
    }
    else if(GSN_WDD_WPS_SESSION_OVERLAP == status || GSN_WDD_SSID_NOT_FOUND == status)
    {
        /* return error */
        wpsConnDone = FALSE;
    }

    if(status == GSN_SUCCESS || GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->wdd) == TRUE)
    {
        s2wLinkState = S2W_LINK_STATE_CONNECTED;
        /* get the info */
        /*GsnWdd_WlanConfigGet(&s2wappMainTaskCtxt->wdd, &wlanConfig);*/

        /* copy to the info structure and return
        */
        /* copy the ssid and len  and channel
        */
        memcpy(current_wlan_info.ssid,pWlanConfig->ssid.array,
           pWlanConfig->ssid.length );
        current_wlan_info.ssidLen = pWlanConfig->ssid.length;

        /* associated ch will be at 0 index
        */
        current_wlan_info.channel = pWlanConfig->channel[0];

        memcpy(current_wlan_info.bssid, pWlanConfig->bssid.array,6);
        current_wlan_info.validBssid = 1;

        capability = pWlanConfig->capabilityInfo;
        if (capability & GSN_MAC_CAPA_IBSS)
        {
            current_wlan_info.mode = S2W_WLANDATA_MODE_ADHOC;
        }
        else
        {
            current_wlan_info.mode = S2W_WLANDATA_MODE_INFRA;
        }

        /* get the security info this can be modifed to present more info
        */
        if(capability & GSN_MAC_CAPA_PRIVA)
        {
            if (pWlanConfig->securityConfig.encryptionType & GSN_MAC_ENC_WPA2)
            {
                current_wlan_info.authMode = S2W_AUTH_MODE_WPA2;
            }
            else if (pWlanConfig->securityConfig.encryptionType & GSN_MAC_ENC_WPA)
            {
                current_wlan_info.authMode = S2W_AUTH_MODE_WPA;
            }
            else if (pWlanConfig->securityConfig.authType == S2W_AUTH_MODE_OPEN)
            {
                /* Open with WEP cannot be identified from capabilities */
                current_wlan_info.authMode = S2W_AUTH_MODE_OPEN;
            }
            else
            {
                current_wlan_info.authMode = S2W_AUTH_MODE_SHARED;
            }
        }
        else
        {
            current_wlan_info.authMode = S2W_AUTH_MODE_AUTO;
        }
    }
    else
    {
        s2wLinkState = S2W_LINK_STATE_DISCONNECTED;
    }

    GsnOsal_SemRelease(&stWpsAssSemaphore);

}
//#endif
#endif
#endif /*GSN_SECURITY_WPS_ENABLE*/

PRIVATE VOID
AppS2wHal_StbyDelayTimerCb ( VOID* pu32Ptr, UINT32 TimerHandle )
{
    GsnOsal_SemRelease ( &stbyDelaySemaphore);
}

VOID 
GratiousArpHandler(NX_IP *ip_ptr,NX_PACKET *packet_ptr)
{
  	nx_packet_release(packet_ptr);
  	nx_dhcp_decline(&s2wappMainTaskCtxt->if0.nwifCtx.dhcpCliHndl);
  	AppMainCtx_TaskNotify(APP_EVENT_DHCPv4_IP_CONFLICT);
}

PUBLIC UINT8
AppS2wHal_NwContextRestore()
{
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
	//APP_RTC_SECNDRY_MEM_INFO_T *pAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();
	GSN_NWIF_DHCP_PARAMS_T	dhcpParams;
	GSN_NWIF_IP_CONFIG_T ipConfig;
    GSN_WDD_WLAN_CFG_T *pWddConf;
    GSN_STATUS retVal;
    
	if(FALSE == GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx))
	{
		 return S2W_FAILURE;
	}
	/* Set L2 Configuration */
	pWddConf = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);
	//memset(&WddConf,0,sizeof(GSN_WDD_WLAN_CFG_T));
	s2wappMainTaskCtxt->if0.wddCtx.assocStatus = pAppRtcLtchInfo->AssocStatus;
	s2wLinkState = (S2W_LINK_STATE_T)s2wappMainTaskCtxt->if0.wddCtx.assocStatus;
	memcpy(&pWddConf->bssid, &pAppRtcLtchInfo->bssid, sizeof(GSN_WLAN_MAC_ADDR_T));
	memcpy(&current_wlan_info.bssid, &pWddConf->bssid, sizeof(GSN_WLAN_MAC_ADDR_T));
	current_wlan_info.validBssid = TRUE;
	memcpy(&pWddConf->ssid, &pAppRtcLtchInfo->ssid, sizeof(GSN_WLAN_MAC_SSID_T));
	pWddConf->securityCfg.mode = pAppRtcLtchInfo->wsec;
		pWddConf->securityCfg.wepConfig.authType = pAppRtcLtchInfo->authType;
	pWddConf->channel[0] = pAppRtcLtchInfo->channel;
    current_wlan_info.mode = pAppRtcLtchInfo->wmode;
	current_wlan_info.authMode = pWddConf->securityCfg.mode;
	current_wlan_info.channel = pWddConf->channel[0];
	memcpy(current_wlan_info.ssid, pWddConf->ssid.array, pWddConf->ssid.length);
	current_wlan_info.ssidLen = pWddConf->ssid.length;
	//GsnWdd_WlanConfigSet(&s2wappMainTaskCtxt->if0.wddCtx, &WddConf);

	/* Set IP config - read NW parameters from RTC
	   */
	ipConfig.flag = GSN_NWIF_IPCONFIG_FLAG_IPV4_INIT;
	ipConfig.ipv4.staticIp = pAppRtcLtchInfo->ipConfig.ipv4.staticIp;

	ipConfig.ipv4.ipAddr = pAppRtcLtchInfo->ipConfig.ipv4.ipAddr;
	ipConfig.ipv4.subnetMask = pAppRtcLtchInfo->ipConfig.ipv4.subnetMask;
	ipConfig.ipv4.gatewayIpAddr = pAppRtcLtchInfo->ipConfig.ipv4.gatewayIpAddr;
        
        s2wappMainTaskCtxt->ipaddr = pAppRtcLtchInfo->ipConfig.ipv4.ipAddr;
        s2wappMainTaskCtxt->subnetMask =  pAppRtcLtchInfo->ipConfig.ipv4.subnetMask;
        
	ipConfig.ipv4.dnsPriSrvrIp = pAppRtcLtchInfo->ipConfig.ipv4.dnsPriSrvrIp;
	ipConfig.ipv4.dnsSecSrvrIp = pAppRtcLtchInfo->ipConfig.ipv4.dnsSecSrvrIp;
	ipConfig.ipv4.dhcpLeaseExpireTime = pAppRtcLtchInfo->ipConfig.ipv4.dhcpLeaseExpireTime;
        memcpy(ipConfig.ipv4.hostName,pAppRtcLtchInfo->hostName,GSN_NWIF_HOST_NAME_MAX_LEN+1);

	memset(&dhcpParams,0,sizeof(dhcpParams));
	dhcpParams.dhcpMaxRetryCnt = S2W_DHCP_MAX_RETRY_COUNT;
	s2wappMainTaskCtxt->if0.nwifCtx.notifyCb = DHCP_notify;
        
        
    if(!pAppRtcLtchInfo->ipConfig.ipv4.staticIp)
    {
      // if(GsnNwIf_dhcpClientRestoreRecord(&s2wappMainTaskCtxt->if0.nwifCtx,&pAppRtcSecMemInfo->dhcpClientParams,((ULONG)pAppRtcSecMemInfo->sleepTime)/10) != GSN_SUCCESS)
      //   S2w_Printf("\r\nDHCP RESTORE FAILED\r\n");
         dhcpParams.timeElapsed = ((ULONG)pAppRtcLtchInfo->sleepTime)/100;
         dhcpParams.pDhcpCliRecord = &pAppRtcLtchInfo->dhcpClientParams;         
         dhcpParams.requestLeaseTime = s2wCurrent.dhcpRequestLeaseTime;
         dhcpParams.dhcpRetryTimeout = s2wCurrent.dhcpRetryTimeout;
         //S2wL3Wait = TRUE;
    }
    L3ConnectStatus = FALSE;
    retVal = GsnNwIf_Open(&s2wappMainTaskCtxt->if0.nwifCtx, &ipConfig, &dhcpParams);
    if(retVal == GSN_FAILURE)
    {
        if(s2wCurrent.logLevel > 0)S2w_Printf("\r\nIP CONFIG FAIL");
        GsnNwIf_Close(&s2wappMainTaskCtxt->if0.nwifCtx);
        return S2W_FAILURE;
    }
    else if(retVal == GSN_OPERATION_IN_PROGRESS)
    {
        S2wL3Wait = TRUE;
        GsnOsal_SemAcquire ( &s2wL2L3ConnectSemaphore, GSN_OSAL_WAIT_FOREVER );
        if(L3ConnectStatus == FALSE)
        {
            if(s2wCurrent.logLevel > 0)S2w_Printf("\r\nIP CONFIG FAIL");
            GsnNwIf_Close(&s2wappMainTaskCtxt->if0.nwifCtx);
            return S2W_FAILURE;
        }
    }
    //S2wL3Wait = FALSE;
    L3ConnectStatus = TRUE;   
    s2wCurrent.netConf.dhcp = !ipConfig.ipv4.staticIp; 	   
#if 0
		 memcpy(&s2wCurrent.netConf.ipAddr,(UINT8*)&(ipConfig.ipv4.ipAddr),4);
		 memcpy(&s2wCurrent.netConf.netMask,(UINT8*)&(ipConfig.ipv4.subnetMask),4);
		 memcpy(&s2wCurrent.netConf.gateway,(UINT8*)&(ipConfig.ipv4.gatewayIpAddr),4);
		 memcpy(&s2wCurrent.dns1,(UINT8*)&(ipConfig.ipv4.dnsPriSrvrIp),4);
		 memcpy(&s2wCurrent.dns2,(UINT8*)&(ipConfig.ipv4.dnsSecSrvrIp),4);
#endif
		
         
	if(pAppRtcLtchInfo->arpCacheEn)
	 nx_arp_table_set(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl, &pAppRtcLtchInfo->arpTablebuf[0], 
	 					pAppRtcLtchInfo->arpRecCount);
	 nx_arp_gratuitous_send(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl,GratiousArpHandler);
	 return S2W_SUCCESS;
}
  


UINT8
AppS2wHal_NwContextStore()
{

	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
	//APP_RTC_SECNDRY_MEM_INFO_T *pAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();
	GSN_WDD_WLAN_CFG_T *WddConf;
	UINT8 AssocStatus=0;
	GSN_NWIF_IP_CONFIG_T IpConfig;
	UINT32 arpCount = 0;
	NX_DHCP_CLIENT_RECORD dhcpClientRecord = {0};


	if(s2wLinkState == S2W_LINK_STATE_CONNECTED)
	{
		/*Store Nw parameters*/
		pAppRtcLtchInfo->ipConfig.ipv4.staticIp = !s2wCurrent.netConf.dhcp;

		GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx, &IpConfig);
			

		pAppRtcLtchInfo->ipConfig.ipv4.ipAddr =  IpConfig.ipv4.ipAddr ;
		pAppRtcLtchInfo->ipConfig.ipv4.subnetMask = IpConfig.ipv4.subnetMask;
		pAppRtcLtchInfo->ipConfig.ipv4.gatewayIpAddr = IpConfig.ipv4.gatewayIpAddr;
		pAppRtcLtchInfo->ipConfig.ipv4.dnsPriSrvrIp = IpConfig.ipv4.dnsPriSrvrIp;
		pAppRtcLtchInfo->ipConfig.ipv4.dnsSecSrvrIp = IpConfig.ipv4.dnsSecSrvrIp;
		pAppRtcLtchInfo->ipConfig.ipv4.dhcpLeaseExpireTime = 
				IpConfig.ipv4.dhcpLeaseExpireTime;
		
		GsnNwIf_dhcpClientCreateRecord(&s2wappMainTaskCtxt->if0.nwifCtx,&dhcpClientRecord);
		memcpy((VOID*)&pAppRtcLtchInfo->dhcpClientParams,(const VOID*)&dhcpClientRecord,sizeof(NX_DHCP_CLIENT_RECORD));
		memset(pAppRtcLtchInfo->hostName,0,GSN_NWIF_HOST_NAME_MAX_LEN+1);
		memcpy(pAppRtcLtchInfo->hostName,s2wCurrent.hostName,GSN_NWIF_HOST_NAME_MAX_LEN+1);



		/* Store arp table */
		if(pAppRtcLtchInfo->arpCacheEn)
			nx_arp_table_get(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl, 
								(VOID *)&pAppRtcLtchInfo->arpTablebuf[0], 
								sizeof(pAppRtcLtchInfo->arpTablebuf), 
								(ULONG*)&arpCount);
		pAppRtcLtchInfo->arpRecCount = (UINT8 )arpCount;
		/* Store L2 Conf */
		WddConf = GsnWdd_WlanConfigPtrGet(&s2wappMainTaskCtxt->if0.wddCtx);
		AssocStatus = GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx);
		memcpy(&pAppRtcLtchInfo->bssid, &WddConf->bssid, sizeof(GSN_WLAN_MAC_ADDR_T));
		memcpy(&pAppRtcLtchInfo->ssid, &WddConf->ssid, sizeof(GSN_WLAN_MAC_SSID_T));
		pAppRtcLtchInfo->wsec = WddConf->securityCfg.mode;
		pAppRtcLtchInfo->channel = WddConf->channel[0];
		pAppRtcLtchInfo->AssocStatus = AssocStatus;
		pAppRtcLtchInfo->wmode = s2wappMainTaskCtxt->if0.macIfType;
		pAppRtcLtchInfo->authType= WddConf->securityCfg.wepConfig.authType;
	}
	else // not connected
	{
		return S2W_LINK_LOST_EVT;
	}
	return S2W_SUCCESS;

}

PUBLIC UINT8
AppS2wHal_PsStbyRequest(ULONG64 sleepTime,UINT32 delayTime,
                  S2W_ALARM_INFO_T* data)
{
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
	APP_RTC_SECNDRY_MEM_INFO_T *pAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();
	S2W_PROFILE_PARAMS_T *
        proParam =  S2w_ProfileParamInRTCPtrGet();
	S2W_FLASH_PARAMS_T *
        profiles =  S2w_FlashParamInRTCPtrGet();
	ULONG64 duration;
	GN_SYS_CTL_STDBY_REQ_PARAM_T stdbyReqParam;
	INT8 *pStdbyRespBuf;
	UINT32 stdbyRespBufLen; 
	GSN_SYS_CTL_STDBY_RESP_T *pStdbyResp;
    GSN_SOFT_TMR_HANDLE_T stbydelayTimerId = NULL;
    GSN_SOFT_TMR_T stbyDelayTimer;
        
	if((s2wCurrent.ncmAutoMgr) && (s2wLinkState == S2W_LINK_STATE_CONNECTED))
	{

	   AppS2wHal_NwContextStore();
	}
	 /* start a timer for delay if needed before going to standby */
    if(delayTime > 0)
    {
        stbydelayTimerId = GsnSoftTmr_Start (&stbyDelayTimer, GSN_SOFT_TMR_ONESHOT,
                                0,((TIMER_INTERRUPT_5_MS * delayTime)/5),
                                ( GSN_SOFT_TMR_CBR_T )AppS2wHal_StbyDelayTimerCb,
                                  NULL );

        if ( NULL == stbydelayTimerId )
        {
            return S2W_FAILURE;
        }
        GsnOsal_SemAcquire ( &stbyDelaySemaphore,
        GSN_OSAL_WAIT_FOREVER );
    }
    {
			// for stby wakeup update the profile data structure in RTC
			memcpy(proParam,&profile_params,sizeof(S2W_PROFILE_PARAMS_T));
			memcpy(profiles,s2wFlashParams,sizeof(S2W_FLASH_PARAMS_T));
	}
    pAppRtcLtchInfo->sleepTime =   sleepTime;          
    duration = GSN_SOFT_TMR_MILLISECONDS_TO_TICKS(sleepTime);
    pAppRtcLtchInfo->psStbycmd = 1;

	stdbyReqParam.waitPeriod[1] = 0;

	pStdbyRespBuf = (INT8 *)MALLOC(MAX_WLAN_STANDBY_DATA_SIZE);
	memset((INT8 *)&stdbyReqParam, 0, sizeof(stdbyReqParam));
	stdbyReqParam.waitPeriod[0] = 0xFFFFFFFF;
	stdbyRespBufLen = MAX_WLAN_STANDBY_DATA_SIZE;
	GsnSysCtl_StandByReq(&s2wappMainTaskCtxt->sysCtlCtx, &stdbyReqParam, 
							pStdbyRespBuf, stdbyRespBufLen);
     
	/*Store wlan CPU data*/
	pStdbyResp = (GSN_SYS_CTL_STDBY_RESP_T *)pStdbyRespBuf;
	
	pAppRtcSecMemInfo->macStdbyCtxLen = pStdbyResp->totalSize;
	memcpy((INT8 *)pAppRtcSecMemInfo->macStdbyCtx, (const INT8 *)pStdbyResp->ctxData, 
			pStdbyResp->totalSize);
    RTC_SM_SB_CLK_REQ_LP_XTAL_SET(RTC);
    RTC_SM_WK_CLK_REQ_HS_XTAL_SET(RTC);
    RTC_SM_WK_CLK_REQ_HS_RC_SET(RTC);
    if(data->alarm1Valid)
    {
        GsnRtc_AlarmConfig(GSN_RTC_ALARM_2, data->alarm1Pol, TRUE);
    }
        else
    {
        GsnRtc_AlarmDisable(GSN_RTC_ALARM_2);
    }
    if(data->alarm2Valid)
    {
		GsnRtc_AlarmConfig(GSN_RTC_ALARM_3, data->alarm2Pol, TRUE);
    }
        else
    {
        GsnRtc_AlarmDisable(GSN_RTC_ALARM_3);
    }

	{/*Configure RTC SRAM Bank*/
		RTC_SRAM_ISO_ENABLE_SET(RTC);
		SX_EN_ULDO_SET(RTC);
		RTC_SX_SWT2LDO_SET(RTC,1);
	}   
    /*Issue the stby request
     */
#ifdef S2W_PERSISTENT_TMR_SUPPORT     
    AppS2w_StateExit(&appCtx);
    perstTmrTimeout = GsnPersistTmr_MinExpireTime();
    currentTime = GsnSoftTmr_CurrentSystemTime();
    perstTmrTimeout = perstTmrTimeout - currentTime;
    duration = (duration < perstTmrTimeout)? duration: perstTmrTimeout;
#endif    
    GsnPwrMgmt_EnterStby(duration);
    {
       volatile UINT32 loop=1;
       while(loop);
    }

    return S2W_SUCCESS;
}

VOID
AppS2wHal_PsHibernateRequest(S2W_ALARM_INFO_T *alarm)
{
    APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
    if(alarm->alarm1Valid)
    {
        GsnRtc_AlarmConfig(GSN_RTC_ALARM_2, alarm->alarm1Pol, TRUE);
    }
        else
    {
        GsnRtc_AlarmDisable(GSN_RTC_ALARM_2);
    }
    if(alarm->alarm2Valid)
    {
        GsnRtc_AlarmConfig(GSN_RTC_ALARM_3, alarm->alarm2Pol, TRUE);
    }
        else
    {
        GsnRtc_AlarmDisable(GSN_RTC_ALARM_3);
    }

    RTC_SX_LOAD_F_SET(RTC);
    RTC_SX_LOAD_F_CLEAR(RTC);
    
    RTC_TRNG_OSC_STOP_N_F_CLEAR(RTC);
    RTC_TRNG_OSC_STOP_N_F_CLEAR(RTC);

	/* Disable shared SRAM banks */
	GsnRtc_SMemBank01Disable();
	GsnRtc_SMemBank2Disable();
	GsnRtc_SMemBank34Disable();

    RTC_WCM3_CLK_ENABLE_CLEAR(RTC); 	 //Disable wlan clock

    RTC_REG_RF_IO_CNTRL_SET(RTC,0);

    /* Disable Ldo's */
    GsnRtc_Ldo1Disable();
    GsnRtc_Ldo2Disable();

    /* Disable WLAN core */
    GsnRtc_WlanCoreDisable();

    /* Disable crypto */
    GsnRtc_CryptoDisable();
    
    /* Turn off uLDO */
    GsnRtc_microLdoDisable();

    /* isolate and power down RTC SRAM */
    GsnRtc_RtcSramBankDisable(GSN_RTC_SRAM_BANK_ALL);
    
    /*Configure Standby and WakeUp clock sources*/
	RTC_SM_WK_CLK_REQ_HS_XTAL_SET(RTC);
	RTC_SM_WK_CLK_REQ_HS_RC_SET(RTC);
	RTC_SM_SB_CLK_REQ_LP_XTAL_SET(RTC);

    /* Cfg alarm wakeup clocks */
    RTC_SM_ALARM_CLK_REQ_LP_XTAL_SET(RTC);
    RTC_SM_ALARM_CLK_REQ_HS_XTAL_SET(RTC);
    RTC_SM_ALARM_CLK_REQ_HS_RC_SET(RTC);

    /* Disable all clocks in standby */
    RTC_SM_SB_CLK_REQ_SET(RTC, 0);

	GSN_APP_REQ_SET(TRUE);
	pAppRtcLtchInfo->hibernate = TRUE;
	/* Disable stby timer interrupt */
    RTC_RTC_PCNT_IRQ_MASK_VAL_CLEAR(RTC);

    GsnRtc_BrownOutDisable();
    
    /* Go to standby */
    RTC_SM_WU_SB_REQ_EN_SET(RTC);
    while(1);
}

