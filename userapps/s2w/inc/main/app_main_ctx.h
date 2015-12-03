/*****************************************************************
*
*               COPYRIGHT (c) 2006-2010 GainSpan Corporation
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
* $RCSfile: app_main_ctx.h,v $
*
* Description : This file contains the application main task definitions.
*
******************************************************************/
#ifndef _APP_MAIN_CTX_H_
#define _APP_MAIN_CTX_H_

#include "gsn_includes.h"
#include "modules/persistent_timer/gsn_persistent_timer.h"
#include "config/app_resource_config.h"
#include "config/app_config.h"

//#include "batt_chk\app_batt_chk.h"
//#include "modules\gsn_file_sys.h"
//#include "modules\gsn_httpd.h"
#include "hal/s2w_types.h"
/* gsn mdns */
#include "modules/mdns_sd/gsn_mdns.h"
#include "gsn_ncm.h"
#include "main/s2w_l2_dev.h"

/*emu*/
#include "emu/app_emu.h"
#ifdef ADK_OTAFU
#include "gsn_otafu.h"
#include "gsn_ext_otafu.h"
#endif

/**
 ******************************************************************
 * @file app_main_ctx.h
 * @brief Application Main task public header.
 *      This file contains the main task implementation. This is the first task
 *      that gets created in the system. This task does the all the initialization
 *      and then moves on to do application specific processing.
 ******************************************************************/

/**
 ******************************************************************
 * @defgroup AppMainCtx
 *    This group contains the application main task implementation.
 ******************************************************************/

/* Serial Port ID - identifies UART or SPI port
*/

typedef enum S2W_SERIAL_PORT_ID
{
	S2W_PORT_UART,
	S2W_PORT_SPI,
        S2W_PORT_FS_SPI,
	S2W_PORT_SDIO
}S2W_SERIAL_PORT_ID_T;

//#define GSN_APP_MAIN_TASK_PRIORITY (GSN_SENSOR_PRIORITY_START + 2)
// TODO: igh-move this to a gsn_defines.h
#define APP_MAIN_TASK_PRIORITY 26

typedef struct APP_BATT_CHK_T
{
   UINT32 val;
  UINT8 battChckStarted;
} APP_BATT_CHK_T;

typedef struct APP_EXT_FS
{
	S2W_FILE_T fileInfo;
	UINT8 extDataBuffFs[1024];
} APP_EXT_FS_T;


typedef struct APP_IF_INFO
{
	UINT32 macIfNum;
	GSN_WIF_WLAN_NW_TYPE_T macIfType;

	/*Wif context*/
	GSN_WIF_CTX_T	wifCtx;
	/*Wdd (L2 Dev) context */
	GSN_WDD_CTX_T wddCtx;
	/*Nw If (L3 and above) context*/
	GSN_NWIF_CTX_T nwifCtx;
}APP_IF_INFO_T;


typedef struct APP_MAIN_CTX
{
    /* Application main task */
    GSN_OSAL_THREAD_TCB_T task;
    //GSN_OSAL_MAILBOX_T    taskMsgQueue;
    GSN_NOTIFICATION_FUNC_T taskNotifier;

	/* HI ctx*/
	GSN_HI_CTX_T hiCtx;
	/*Sys Control Contexts*/
	GSN_SYSIF_CTX_T sysifCtx;
	GSN_SYS_CTL_CTX_T sysCtlCtx;

	/*ISOTX*/
	GSN_ISOTXIF_CTX_T isotxifCtx;
	GSN_ISOTX_CTX_T isotxCtx;
	
	/*Wdd message handler context*/
	GSN_WDD_MSG_HANDLER_T wddMsgHdlrCtx;
	/* Nw context */
	GSN_NW_CTX_T nwCtx;
	/* Bsd Layer Data structure*/
	GSN_NW_BSD_T bsdCtx;
	/*Interface 0 informmation*/
	APP_IF_INFO_T if0;

	GSN_PWR_MGMT_CTX_T pwrMgmtCtx;
#ifdef  S2W_EMU        
	/*Emu context*/
        APP_EMU_CTX_T appEmuCtx;
#endif
	GSN_MSG_HANDLER_CTX_T softTmrMsgHdlrCtx;
	UINT32 softTmrMsg;

    GSN_OSAL_THREAD_TCB_T s2wSerialTask;

    GSN_OSAL_THREAD_TCB_T s2wNetRxTask;

    GSN_OSAL_THREAD_TCB_T s2wWebServerTask;

    GSN_OSAL_THREAD_TCB_T s2wSerial2InputTask;

	/* S2w application serial interface selection flag */
    S2W_SERIAL_PORT_ID_T   serialDeviceId;     /* 0 - UART   1- SPI interface */
	//GSN_SPI_NUM_T          s2wSpiPort;         /* SPI port number */

	UINT32   dpSleep;  /* Flag to indicate deep-sleep is enabled or disabled */
   // GH_SEM   s2wDpSleepWakeUpSem;  /* Semaphore used for deep Sleep wake-up detection in case of SPI interface */
	VOID   (*s2wDpSleepWakeUpCallBack)(VOID *ctx);/**< S2w deep Sleep wake-up callback function pointer      */

	VOID   (*s2wWriteFn)    (const VOID *buf, UINT32 length);	/**< S2w serial port write function pointer      */
	UINT8  (*s2wGetCharFn)  ( UINT8 *rxChar);                   /**< S2w serial port read function pointer      */
	VOID   (*s2wPutCharFn)  (UINT8 txChar);                     /**< S2w serial port put char function pointer */
	VOID   (*s2wGetNCharFn)  (UINT8 *rxChar,UINT16 length);    /**< S2w serial port read bulk read function pointer   */

#if 1//def GSN_WEB_SERVER
	UINT8 currenturi[GSN_HTTPD_MAX_URI_LENGTH];
#endif
#if 1//defined(GSN_GSLINK_XML) || defined(GSN_GSLINK_RAW)
	UINT8 xmlParseEn;
	UINT8 gsLinkSendStatus;
#endif
#if 1//defined(S2W_WEB_PROV) || defined(GSN_WEB_SERVER)
	S2W_WBSERVER_CONFIG_T WebServerCfg;
        GSN_OSAL_SEM_T webServerSync;
        GSN_OSAL_SEM_T   s2wDpSleepWakeUpSem;  /* Semaphore used for deep Sleep wake-up detection in case of SPI interface */
	UINT32 formatVersion;
#endif
#if 1//def GSN_WEB_SERVER
	UINT8 responseInprogress;
	UINT32 respTimeOut;
	UINT8 webServerStatus;
	GSN_SOFT_TMR_T	respTimeOutTmr;
	GSN_SOFT_TMR_HANDLE_T  respTimeOutTmrHndl;
#endif
#if 1//def S2W_WEB_PROV
UINT8 rediruri[GSN_HTTPD_MAX_URI_LENGTH];
UINT8 webProvStatus;
UINT8 wpsInprogress;
#endif
GSN_MDNS_T mdns;

#ifdef S2W_NCM_SUPPORT_ENABLE
GSN_NCM_CTX_T appNwConnMgrCtx;

UINT32 ncmAutoConEn;
	UINT8 ncmAutoConStoreProfile;
GSN_OSAL_SEM_T ncmOpsync;
#endif //NCM_SUPPORT_ENABLE
UINT32 ipaddr;
UINT32 subnetMask;

#ifdef S2W_PING_TRACE
S2W_PINGDATA_T pingParams;
#endif
#ifdef S2W_SECURITY_WPS_ENABLE
S2W_WPS_T wpsParams;
GSN_MAC_SSID_T wpsapSsid;
#endif
#ifdef S2W_PERSISTENT_TMR_SUPPORT
    GSN_SOFT_TMR_T persistTmrTbl[ APP_NUM_OF_PERSIST_TMR ];
    UINT32 :0; /**< persistent tmr Nvds should start at word aligned addr */
    UINT8 persistTmrNvds[ GSN_P_TMR_NVDS_MEM_SIZE( APP_NUM_OF_PERSIST_TMR ) ];
#endif
#ifdef S2W_UNASSOC_TXRX_SUPPORT
GSN_WDD_UAM_DATA_HDR_T frame;
    INT8 ccaThr;
    UINT32 ccaTimeout;
UINT8 uamTimeStampReturn;
GSN_WDD_UAM_DRX_CONFIG_PARAM_T RxParam;
GSN_RING_BUF_T  s2wUamBufQ;
UINT32 s2wUamBufQBuf[S2W_NUM_UAM_BUFS+1];
#endif
#ifdef S2W_SNTP
GSN_SNTP_CTX_T sntpCtx;
UINT32 sntpTimerPeriod;
UINT32 sntpSrvIp;
UINT32 sntpSrvTimeout;
GSN_SOFT_TMR_T  appSntpTimer;
#endif
BOOL apConf; 
#ifdef S2W_15DOT4_SUPPORT
	GSN_DOT154IF_CTX_T dot154ifCtx;
	GSN_WLRPAN_T wlrpanCtx;

#endif
GSN_EXTFLASH_CTX_T extFlashCtx;
APP_EXT_FS_T appExtFsCtx;

UINT8 lastCidCreated;
#ifdef S2W_FILE_UPLOAD_API
UINT32 fileuploadCnt;
UINT8  fileOperationStatus;
#endif
UINT8 l2ConfigBitField;

#ifdef S2W_IP2WIFI_SUPPORT
    S2W_L2_DEV_T s2wL2Dev;
#endif
#ifdef S2W_ADC_SUPPORT
    GSN_ADC_HANDLE_T  appadchandle;
    GSN_ADC_CONFIG_T  appadcconfig;
    GSN_ADC_RW_ARGS_T appadcrw;
    UINT8 adcStartStatus;
#endif
#ifdef S2W_I2C_SUPPORT
    GSN_I2C_HANDLE_T app_i2cHandle;
    GSN_I2C_CONFIG_T app_i2cConf;
    UINT8 i2cStatus;
#endif

#ifdef S2W_DUAL_INTERFACE_SUPPORT
   S2W_SERIAL_PORT_ID_T   serialDeviceId1;
	VOID   (*s2wWriteFn1)    (const VOID *buf, UINT32 length);	/**< S2w serial port write function pointer      */
	UINT8  (*s2wGetCharFn1)  ( UINT8 *rxChar);                   /**< S2w serial port read function pointer      */
	VOID   (*s2wPutCharFn1)  (UINT8 txChar);                     /**< S2w serial port put char function pointer */
	VOID   (*s2wGetNCharFn1)  (UINT8 *rxChar,UINT16 length);    /**< S2w serial port read bulk read function pointer   */
#endif
UINT8 logLevel;

#ifdef ADK_OTAFU
	GSN_EXTOTAFU_CTX_T extOtafuCtx;
#endif
/*battery check module context*/
   APP_BATT_CHK_T battChk;  
   UINT8 fsInit;
   GSN_SOFT_TMR_T clkCaibTmr;
   GSN_SOFT_TMR_HANDLE_T clkCaibTmrHndl;
	/*Association timer*/
	GSN_SOFT_TMR_T wlanRespTmr;
   	GSN_SOFT_TMR_HANDLE_T wlanRespHndl;   
	BOOL bcastSsid;
	UINT8 dtimPeriod;
	UINT16 inactivityTimeoutInSec;
	UINT16 grpKeyUpdtIntrvl;
	GSN_OSAL_SEM_T s2wTcpClientCntSyncSem;	
} APP_MAIN_CTX_T;

extern APP_MAIN_CTX_T appCtx;

PUBLIC VOID
AppMainCtx_TaskNotify(INT32 msg);

PUBLIC VOID
AppMainCtx_Init(VOID);

#ifdef S2W_IP2WIFI_SUPPORT
VOID
AppInit_L2DevInit(APP_MAIN_CTX_T *pAppCtx);
#endif
UINT8
s2w_StartDhcpDnsServer();

PUBLIC VOID
App_IfInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);

#endif /*_APP_MAIN_CTX_H_*/


