/*******************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
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
* $RCSfile: app_main_thread.c,v $
*******************************************************************************/

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_includes.h"
#include "main/app_main_ctx.h"
#include "app_defines.h"
#include "modules/persistent_timer/gsn_persistent_timer.h"
#include "config/app_resource_config.h"
#include "hal/s2w_hal.h"
#include "parser/s2w_process.h"
#include "app_rtc_mem.h"
#include "app_defines_builder.h"
#include "hal/s2w_types.h"
#include "fs/api/api_safe.h"
#include "hal/s2w.h"
#include "app_defines_builder.h"
#include "gsn_ncm_roam.h"

#include "ftw_config.h"
#include "ftw_uart.h"
#include "ftw_spi.h"
#include "ftw_net.h"
#include "ftw_httpd.h"
#include "ftw_battery.h"
#include "ftw_fs.h"
/*****************************************************************************
 *Private definitions
 ****************************************************************************/



#define APP_DEV_INDX_0	0

/*****************************************************************************
 *Private variables
 ****************************************************************************/

#ifdef FTW_SDIO_ENABLE
__no_init UINT8 s2wSerialBuf[16384];
#else
__no_init UINT8 s2wSerialBuf[4096];
#endif

#ifdef FTW_DUAL_INTERFACE_SUPPORT
#ifdef FTW_SDIO_ENABLE_1
__no_init UINT8 s2wSerialBuf1[16384];
#else
__no_init UINT8 s2wSerialBuf1[4096];
#endif
__no_init UINT8 s2wSerial2InputTaskStack[2048];
#endif
/** Buffer for data to be transmitted */
/*App main context*/
APP_MAIN_CTX_T appCtx;
FTW_SERIAL_PORT_HANDLE_T  s2wSerialPortHandle;
FTW_SERIAL_PORT_HANDLE_T  s2wSerialPortHandle1;

__no_init FTW_SCAN_DISPLAY_INFO_T scanDisplayInfo[20];

__no_init UINT8 s2wSerialInputTaskStack[APP_CFG_SERIALINPUT_STACK_SIZE];



/* Define the APP main task  */
PRIVATE GSN_OSAL_THREAD_TCB_T appMainCtxThread;
__no_init PRIVATE UINT32 appMainCtxThreadStack[APP_MAIN_STACK_SIZE/sizeof(UINT32)];
PUBLIC GSN_OSAL_QUEUE_T appMainThreadMsgQueue;
PRIVATE UINT32 appMainThreadMsgQueueBuf[ APP_CFG_APP_CTX_MAX_MSG_IN_MBOX ];

/* WDD stuff */
__no_init PRIVATE UINT32 wddStack[APP_CFG_WDD_TASK_STACK_SIZE/sizeof(UINT32)];
//PRIVATE UINT32 wddMbBuf[APP_CFG_WDD_MAX_MSG_IN_MBOX * sizeof(GSN_WDD_MESSAGE_T)/ sizeof(UINT32)];
//PRIVATE GSN_WDD_MESSAGE_T wddMsg;/* Message instance for handling received messages */

/*wif message system */
__no_init PRIVATE UINT32 hifMsgRcvTskStack[APP_CFG_HIF_MSG_RCV_STACK_SIZE/sizeof(UINT32)];
__no_init PRIVATE UINT32 sysCtrlTaskStack[APP_CFG_SYSCTL_TASK_STACK_SIZE/sizeof(UINT32)];

/* Soft Timer*/
__no_init UINT32 softTmrMsgHHdlrStack[ APP_CFG_SOFT_TMR_STACK_SIZE/sizeof(UINT32) ];
__no_init UINT32 softTmrMsgHHdlrBuff[ APP_CFG_SOFT_TMR_MAX_MSG_IN_MBOX ];
__no_init INT8 nwSbufPktPool[APP_NW_RX_SPKT_POOL_SIZE];
__no_init INT8 nwLbufPktPool[APP_NW_RX_LPKT_POOL_SIZE];
__no_init INT8 ipStack[APP_NWIF_IP_THREAD_STACK_SIZE];
__no_init INT8 arpCache[APP_NWIF_IP_THREAD_ARP_CACHE_SIZE];

/* Boot indication synchronization mutex*/
GSN_OSAL_SEM_T syscSem;
GSN_OSAL_SEM_T isoTxSem;

#ifdef  FTW_NCM_SUPPORT_ENABLE
/*Ncm */
VOID *NcmCtx;
__no_init UINT8 ncmMsgQueueBuf[APP_CFG_NCM_MSG_HDLR_MSG_IN_MBOX * sizeof(GSN_NCM_MSG_T)];
#endif

GSN_HIF_STATS_T gsnHifStats;
GSN_WDD_STATS_T gsnWddStats;
GSN_NWIF_STATS_T gsnNwifStats;

extern FTW_WLANINFO_T current_wlan_info;
extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;
extern GSN_OSAL_SEM_T dSendSem;
extern GSN_NOTIFICATION_FUNC_T s2wappMainTaskNotifier;

GSN_CLK_CTL_CTX_T* gsnBrClkCtlCtx2;
GSN_OTP_T   gsnBrOtpCtx1;
GSN_OTP_MM_CTX_T gsnBrOtpMmCtx1;

/*****************************************************************************
 *Private Function prototypes
 ****************************************************************************/

PRIVATE VOID
AppMainCtx_ThreadEntry(UINT32 arg);

PRIVATE VOID
AppInit_WddMsgHdlrInit(APP_MAIN_CTX_T *pAppCtx);

PRIVATE VOID
App_HiInit(APP_MAIN_CTX_T *pAppCtx);
VOID
App_WpaSupplicantInit(APP_MAIN_CTX_T * pAppCtx);

VOID
App_DefaultIfInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);

PRIVATE VOID
App_WifInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *ifInfo);

PRIVATE VOID
App_WddInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *ifInfo);


PRIVATE VOID
App_NwIfInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);

PRIVATE VOID
App_NwStackInit(APP_MAIN_CTX_T *pAppCtx);

PRIVATE GSN_STATUS
App_WlanBootReq(APP_MAIN_CTX_T *pAppCtx);

PUBLIC GSN_STATUS
App_MsgProcess(    APP_MAIN_CTX_T *pAppCtx, UINT32 msgId );

PRIVATE VOID
App_BsdLayerInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);

PRIVATE VOID
App_SoftTimerInit(APP_MAIN_CTX_T *pAppCtx);

PRIVATE VOID
App_SysQualInit();

PRIVATE VOID
App_SysCtlInit(APP_MAIN_CTX_T *pAppCtx);
VOID
App_InterfaceStart(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);
PUBLIC UINT32
AppMainCtx_IsDpSlpEnabled(VOID);

#ifdef FTW_WEB_SERVER
PUBLIC VOID
AppS2w_WebServerStart();
#endif
#ifdef FTW_WEB_PROV
PUBLIC VOID
S2wWebProv_WebProvStart();
#endif
PUBLIC VOID
AppS2w_RtcCfg();
VOID
App_RtcDump(VOID);

#ifdef  FTW_NCM_SUPPORT_ENABLE
PUBLIC VOID
AppNcm_Init(APP_MAIN_CTX_T *pAppCtx);
VOID
AppNcm_NcmExecuteCb(VOID *cbCtx, VOID* pNcm);

#endif //NCM_SUPPORT_ENABLE

extern	BOOL AppS2wRecv_Filter(GSN_NWIF_CTX_T *pNwIf, UINT32 pktLen,
						GSN_ETHERNET_FRAME_T *pEthFrame
						);
extern FTW_PROFILE_T s2wCurrent;
GSN_CLK_CTL_CTX_T gsnBrClkCtlCtx1;
extern UINT32 romFwImageFlashAddr;
PRIVATE VOID
App_RandomNumGenInit(VOID);

void GsnHeIf_DriverSuspend();

#ifdef  FTW_NCM_SUPPORT_ENABLE
extern VOID AppS2wNetConnMgr_Cb(VOID* ctext, VOID* pNcm, GSN_NCM_NOTIF_ID_T status);

extern BOOL ncmAutoMode;
#endif


VOID
App_WaitOnLock(VOID);
extern PUBLIC GSN_STATUS
GsnIsotx_Init(GSN_ISOTX_CTX_T *pIsotxCtx, GSN_ISOTX_INIT_PARAM_T *pInitParam);
extern PUBLIC GSN_STATUS
GsnSysCtl_Init_Patch(GSN_SYS_CTL_CTX_T *pSysCtlCtx, GSN_SYS_CTL_INIT_PARAM_T *pInitParam);
extern PUBLIC VOID
GsnSysCtl_BootReq_Patch(GSN_SYS_CTL_CTX_T *pSysCtlCtx, GSN_SYS_CTL_BOOT_REQ_PARAM_T *pBtReqParm,
					  GSN_SYS_CTL_BOOT_NOTIF_CB_T btIndCb, VOID * btIndCbCtx);

VOID
GsnHeIf_TrangGetSeed( UINT8* pBuf );

PRIVATE GSN_SOFT_TMR_T	wlanRespTimeoutTmr;
PRIVATE GSN_SOFT_TMR_HANDLE_T wlanRespTimeoutTmrHndl;
/*****************************************************************************
 *Public and Private functions
 ****************************************************************************/

PUBLIC VOID
AppMainCtx_Init(VOID)
{
	memset((INT8 *)&appCtx, 0, sizeof(appCtx));// REVERT REMOVE

#ifdef GSN_MEM_TRACE
    GsnDynAllChk_Init();
#endif
	/**< Creating the Mailbox to receive messages */
		GsnOsal_QueueCreate( &appMainThreadMsgQueue, 1,
								( UINT8* )appMainThreadMsgQueueBuf,
								sizeof( appMainThreadMsgQueueBuf ));

    /**< Create the main Application Thread */
#ifdef GSN_DBG_STACK_PATTERN_FILL   /* Only for debug */
    memset(appMainCtxThreadStack, 0x5a, sizeof(appMainCtxThreadStack));
#endif

    GsnOsal_ThreadCreate(AppMainCtx_ThreadEntry, &appCtx, &appMainCtxThread,
        "App Main Ctx", APP_MAIN_CTX_THREAD_PRI, (UINT8 *)appMainCtxThreadStack,
        sizeof(appMainCtxThreadStack), GSN_OSAL_THREAD_INITIAL_SUSPENDED);
}

#ifdef APP_NO_FLASHFETCH 
extern GSN_BYTE_POOL_LINK_T bytePool[];

#else
extern GSN_BYTE_POOL_LINK_T heapBytePool[];/* create up to 4 byte poola to be used as heap*/

#endif
VOID 
App_IdleHandlerLoop(VOID)
{
#ifdef APP_NO_FLASHFETCH 

    tx_byte_pool_create(&bytePool[2].bPool, NULL, (void*)0x20000400,
                               (UINT32)(1024 * 15) );

	pGsnBytePoolHead->pNext->pNext = &bytePool[2];
    bytePool[2].pNext = NULL;
#else

    tx_byte_pool_create(&heapBytePool[2].bPool, NULL, (void*)(void*)0x20000400,
                            (UINT32)(1024 * 15));
    pGsnBytePoolHead->pNext->pNext = &heapBytePool[2];
    heapBytePool[2].pNext = NULL;

#endif

    tx_thread_resume(&appMainCtxThread);
    
    while(1)
    {
#ifndef APP_NO_FLASHFETCH 
    
        if((0 == GsnPwrMgmt_DpSlpActivityGet()) && 
            (AppMainCtx_IsDpSlpEnabled() == 1) &&
            (FALSE  == GsnSq_TaskMonitorStarted()))
        {
            GSN_PWR_MGMT_CM3_SLEEP_DEEP_EN();   
        }
        __WFI();
#endif        
    }
    
}

PUBLIC UINT32
AppMainCtx_IsDpSlpEnabled(VOID)
{
    return appCtx.dpSleep;
}


PUBLIC VOID
AppMainCtx_TaskNotify(INT32 msg)
{
    /**< Signal APP */
    GsnOsal_QueuePut(&appMainThreadMsgQueue, (UINT8 *)&msg);
}

PUBLIC VOID
AppMainCtx_GsnCb(INT32 msg, VOID *context)
{
    AppMainCtx_TaskNotify(msg);
}

PRIVATE VOID App_Hw_Init()
{
    IOMUX_BONDOPT_0_PD_EN_SET(IOMUX);
    IOMUX_FLASHSPI_SIO0_PD_EN_SET(IOMUX);
    IOMUX_FLASHSPI_SIO1_PD_EN_SET(IOMUX);
    IOMUX_FLASHSPI_SIO2_PD_EN_SET(IOMUX);
    IOMUX_FLASHSPI_SIO3_PD_EN_SET(IOMUX);
    IOMUX_FLASHSPI_CS_PD_EN_SET(IOMUX);
    IOMUX_FLASHSPI_SCLK_PD_EN_SET(IOMUX);
    IOMUX_BONDOPT_1_PD_EN_SET(IOMUX);
    IOMUX_BONDOPT_2_PD_EN_SET(IOMUX);
    IOMUX_PROG_MODE120P_PD_EN_SET(IOMUX);
    IOMUX_PROG_MODE68P_PD_EN_SET(IOMUX);
    RTC_SX_EN_TS_F_CLEAR(RTC);

    GsnIoMux_PullDownDisable(10);     // WPS ~60uA
    GsnRtc_Ldo2Disable();
    CLKCTL_ACM3_GATE_EN_SET(CLKCTL, 0x3f03);

#if defined (FTW_I2C_SUPPORT) || defined (FTW_ADC_SUPPORT) || defined (FTW_PWM_SUPPORT)
	CLKCTL_ACM3_BUS_FORCE_SET(CLKCTL);
#endif

#if defined (FTW_SDIO_ENABLE) || defined (FTW_SDIO_ENABLE_1)
    CLKCTL_SDIO_BUSCLK_EN_SET(CLKCTL);
    CLKCTL_CREQ_SDIO_IDLE_SET(CLKCTL,1);
    CLKCTL_CREQ_SDIO_ACTIVE_SET(CLKCTL,1);
    CLKCTL_CREQ_ACM3_DSLEEP_SET(CLKCTL,0);
    CLKCTL_SDIO_GATE_FORCE_EN_SET(CLKCTL);
#endif

#if defined (FTW_FS_SPI_ENABLE ) || defined (FTW_FS_SPI_ENABLE_1)
    CLKCTL_AGSPI_BUSCLK_EN_SET (CLKCTL);
#endif
#if defined (FTW_FS_SPI_HI_ENABLE) || defined (FTW_FS_SPI_HI_ENABLE_1)
    CLKCTL_ADMA_GATE_FORCE_EN_SET(CLKCTL);
#endif


}
/* Define the test threads.  */

PRIVATE VOID
AppMainCtx_ThreadEntry(UINT32 ctx)
{
    /*UINT status;*/
    UINT32 msg = 0;
    APP_MAIN_CTX_T *pAppCtx;
    pAppCtx = (APP_MAIN_CTX_T *)ctx;
	GsnPwrMgmt_Init(&pAppCtx->pwrMgmtCtx);

    GsnClkCtl_Init(&gsnBrClkCtlCtx1);
    AppS2wHal_Cm3ClkCfg();

    /* Config RTC */
    AppS2w_RtcCfg();
    
    GsnExcpHdlr_Init();
    /* Used for sending messages to main task */
    pAppCtx->taskNotifier = AppMainCtx_GsnCb;


    /*Initialise wif message system*/
    App_HiInit(pAppCtx);

    /*Initialise wif System Control message Handler */
    App_SysCtlInit(pAppCtx);

	/*Enable WLAN WD*/
	GsnActlWwdog_Enable();
	
    /*Initialise Soft Timer */
    App_SoftTimerInit(pAppCtx);

	/*Initialise SysQual*/
	App_SysQualInit();

    
    /* Initialise File System . Note: WLAn uses FS during boot procedure. Keep yje FS initilised 
            before giving the boot request to WLAN*/
    if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != GSN_BOOT_REASON_GET())
    {
		FTW_FS_init();
		pAppCtx->fsInit = TRUE;
    }
    /* initialize low level OTP driver */
    GSN_OTP_CTX_USES_OBJS_S otpUsesObjs;

    gsnBrClkCtlCtx2 = GsnClkCtl_CtxGet();
    otpUsesObjs.pClkCtl = gsnBrClkCtlCtx2;
    GsnOtp_Init(&gsnBrOtpCtx1, &otpUsesObjs, NULL);

    /* initialize OTP MM module */
    GSN_OTP_MM_USES_OBJS_T otpMmUsesObjs;
    otpMmUsesObjs.otpDrv = &gsnBrOtpCtx1;
    GsnOtpMm_Init(&gsnBrOtpMmCtx1, &otpMmUsesObjs, NULL);
    /* Give boot request */
    App_WlanBootReq(pAppCtx);

    /*Initialise Wdd Message Handler */
    AppInit_WddMsgHdlrInit(pAppCtx);

    /*Initialize Nw statck. This is a one time initialisation*/
    App_NwStackInit(pAppCtx);

    App_Hw_Init();
    
    /* Initialise Wpa Suppliacnt*/
    if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != GSN_BOOT_REASON_GET())
    {
        GsnHeIf_DriverDeinit();
    }
    App_WpaSupplicantInit(pAppCtx);

    /*initialize the app profile*/
    AppS2w_ProfileInit();

    /*Initialize C library random number generator*/
    App_RandomNumGenInit();
    
    /* turn off cryopto engine. Will be turned on need bases. */
    //GsnHeIf_DriverSuspend();
    
    App_BsdLayerInit(pAppCtx, &pAppCtx->if0);

#ifdef  FTW_NCM_SUPPORT_ENABLE
    AppNcm_Init(pAppCtx);
#endif

    AppS2wHal_Register(pAppCtx->taskNotifier, pAppCtx);

    /*Initialise an interface on device Index 0 of Wlan Nw type STA*/
    AppS2wHal_AppEntry(0);
    
#ifdef FTW_EMU
    /*Initialise EMU*/
    AppEmu_Init(&(pAppCtx->appEmuCtx.emu),AppEmu_Callback,pAppCtx);  
#endif
    /**< Handle events forever */
    while( TRUE )
    {
        /**< wait on message queue */
        GsnOsal_QueueGet( &appMainThreadMsgQueue, ( UINT8* )&msg,
                            GSN_OSAL_WAIT_FOREVER );
        GsnSq_TaskMonitorStart(APP_CFG_SQ_MAIN_TASK_ID, msg);
        /**< Process the message */
        App_MsgProcess(pAppCtx, msg);
        GsnSq_TaskMonitorStop(APP_CFG_SQ_MAIN_TASK_ID);
    }
}

#ifdef  FTW_NCM_SUPPORT_ENABLE
PUBLIC VOID
AppNcm_Init(APP_MAIN_CTX_T *pAppCtx)
{
	GSN_NCM_INIT_PARAM_T ncmInitParam;
	ncmInitParam.pNwif = &pAppCtx->if0.nwifCtx;
	ncmInitParam.pWdd = &pAppCtx->if0.wddCtx;
	ncmInitParam.msgQueueBuff = ( UINT8* )ncmMsgQueueBuf;
	ncmInitParam.msgQueueBuffSize = sizeof(ncmMsgQueueBuf);
	ncmInitParam.execMsgPostCb = AppNcm_NcmExecuteCb;
	ncmInitParam.execMsgPostCbCtx = NULL;
	ncmInitParam.notifCb = AppS2wNetConnMgr_Cb;
	ncmInitParam.notifCbCtx = NULL;
	GsnOsal_SemCreate(&pAppCtx->ncmOpsync, 0); 
	GsnNcm_Init(&pAppCtx->appNwConnMgrCtx, &ncmInitParam);
#ifdef FTW_NCM_ROAMING_SUPPORT 					
     GsnNcm_RoamInit(&(pAppCtx->appNwConnMgrCtx));
#endif
}
VOID
AppNcm_NcmExecuteCb(VOID *cbCtx, VOID* pNcm)
{
        NcmCtx = pNcm;
	AppMainCtx_TaskNotify(APP_EVENT_NCM_EXECUTE);
}
#endif //NCM_SUPPORT_ENABLE

GSN_OSAL_SEM_T AppWddDisconSem;
void
AppS2w_WddDisconCb(VOID *ctx, GSN_STATUS status)
{
	GsnOsal_SemRelease(&AppWddDisconSem);
}

VOID
App_InterfaceStop(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);

VOID
App_IfReinit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);

PUBLIC GSN_STATUS
App_MsgProcess(    APP_MAIN_CTX_T *pAppCtx, UINT32 msgId )
{
    //GSN_STATUS retCode = GSN_FAILURE;
	UINT8 status;
	UINT8 macAddr[FTW_MAC_ADDR_SIZE] = {0};

    switch ( msgId )
    {
#ifdef FTW_WEB_SERVER
        case APP_NOTIFICATION_SRVR_ONLY_STOP:
        {
        	pAppCtx->webServerStatus=STOP;
            FTW_NET_HTTPD_stop();
            break;
        }
        case APP_NOTIFICATION_SRVR_START:
        {
        	pAppCtx->webServerStatus=START;
            AppS2w_WebServerStart();
            break;
        }
#endif
#ifdef FTW_WEB_PROV
		case APP_NOTIFICATION_PROV_START:
		{
			pAppCtx->webProvStatus=START;
			S2wWebProv_WebProvStart();
			if((s2wCurrent.mode == FTW_WLANDATA_MODE_PROV_AP))
			{
#ifdef FTW_NCM_SUPPORT_ENABLE                          
				// update the ncmautoconn flag to start it automatically once the provision done
				pAppCtx->ncmAutoConEn = TRUE;
#endif                                
#ifdef  FTW_MDNS_ENABLE
				// start the mdns
				AppS2wHal_MdnsInit(NULL);
				// register the mdns names and announce the mdns services
				AppS2wCmd_MdnsAnnounceAll(NULL);
#endif
   		    }
			break;
		}
		case APP_NOTIFICATION_PROV_ONLY_STOP:
		{
			pAppCtx->webProvStatus=STOP;
			FTW_NET_HTTPD_stop();
			break;
		}
#endif
#if defined(FTW_WEB_SERVER) || defined(FTW_WEB_PROV)
        case APP_NOTIFICATION_SRVR_STOP:
        {
#ifdef FTW_WEB_PROV
            if(pAppCtx->webProvStatus== RUNNING)
            {
            	pAppCtx->webProvStatus=STOP;
            }
#endif
#ifdef FTW_WEB_SERVER
            if(pAppCtx->webServerStatus== RUNNING)
            {
            	pAppCtx->webServerStatus=STOP;
            }
#endif
            FTW_NET_HTTPD_stop();
            break;
        }
#endif
        case APP_EVENT_NW_LINK_FAILURE:
            AppS2wProcess_EventNotify(0);
            break;

        case APP_EVENT_SYNC_LOSS_INDICATION:
             AppS2wProcess_EventNotify(1);
            break;
#ifdef  FTW_MDNS_ENABLE
        case APP_EVENT_MDNS_EXECUTE:
             GsnMdns_Execute(&pAppCtx->mdns);
            break;            
#endif
        
#ifdef  FTW_NCM_SUPPORT_ENABLE
        case APP_EVENT_NCM_EXECUTE:
          GsnNcm_Execute((GSN_NCM_CTX_T*)NcmCtx);
            break;
		case APP_EVENT_NCM_L2CONNECT:
		{
        	// get the ncm config and fill
			GSN_NCM_CONFIG_T gNwConnConfig;
			GsnNcm_ConfigGet(&s2wappMainTaskCtxt->appNwConnMgrCtx, &gNwConnConfig);
			/* copy the ssid and len  and channel    -client  */
			if(ncmAutoMode == 0) 
			{
				memcpy(current_wlan_info.ssid,gNwConnConfig.wlanCfg.ssid.array,
					  gNwConnConfig.wlanCfg.ssid.length );
				current_wlan_info.ssidLen = gNwConnConfig.wlanCfg.ssid.length;

	/* associated ch will be at 0 index                */
				current_wlan_info.channel = gNwConnConfig.wlanCfg.channel[0];

				memcpy(current_wlan_info.bssid, gNwConnConfig.wlanCfg.bssid.array,GSN_WLAN_MAC_ADDR_LEN);
				current_wlan_info.validBssid = 1;
				current_wlan_info.mode = FTW_WLANDATA_MODE_INFRA;
				current_wlan_info.authMode = gNwConnConfig.wlanCfg.securityCfg.mode;
			  	if(gNwConnConfig.wlanCfg.securityCfg.mode == GSN_WDD_SEC_MODE_WEP)
				{
					if(gNwConnConfig.wlanCfg.securityCfg.wepConfig.authType == GSN_WDD_SEC_WEP_SHARED)
					{
				  		current_wlan_info.authMode = (GSN_WDD_SEC_MODE_T)FTW_AUTH_MODE_SHARED;
					}
					else
					{
					  current_wlan_info.authMode = (GSN_WDD_SEC_MODE_T)FTW_AUTH_MODE_OPEN;
					}
				}

				s2wCurrent.security.wpa.pskValid = gNwConnConfig.wlanCfg.securityCfg.pskConfig.pskValid;
			    if(gNwConnConfig.wlanCfg.securityCfg.pskConfig.pskValid)
			    {
					memcpy(s2wCurrent.security.wpa.psk,
			           gNwConnConfig.wlanCfg.securityCfg.pskConfig.psk, GSN_WDD_SEC_PMK_LEN);
					memset(s2wCurrent.security.wpa.ssid,0,FTW_MAX_SSID_LEN);
			    	memcpy(s2wCurrent.security.wpa.ssid,gNwConnConfig.wlanCfg.ssid.array,
			            gNwConnConfig.wlanCfg.ssid.length );
			            s2wCurrent.security.wpa.ssidLen = gNwConnConfig.wlanCfg.ssid.length;
			  	}
			}
            else
            {
            	memcpy(current_wlan_info.ssid,gNwConnConfig.wlanCfg.ssid.array,
			    gNwConnConfig.wlanCfg.ssid.length );
			  	current_wlan_info.ssidLen = gNwConnConfig.wlanCfg.ssid.length;
			  	current_wlan_info.channel = gNwConnConfig.wlanCfg.channel[0];
			  	memcpy(current_wlan_info.bssid, gNwConnConfig.wlanCfg.bssid.array,GSN_WLAN_MAC_ADDR_LEN);
			  	current_wlan_info.validBssid = 1;
			  	if((FTW_WLANDATA_MODE_PROV_AP == s2wCurrent.mode) || (FTW_WLANDATA_MODE_AP == s2wCurrent.mode ))					
			    	current_wlan_info.mode = 2;
			  	else
					current_wlan_info.mode = FTW_WLANDATA_MODE_ADHOC;

				current_wlan_info.authMode = gNwConnConfig.wlanCfg.securityCfg.mode;
			  	if(gNwConnConfig.wlanCfg.securityCfg.mode == GSN_WDD_SEC_MODE_WEP)
			  	{
					if(gNwConnConfig.wlanCfg.securityCfg.wepConfig.authType == GSN_WDD_SEC_WEP_SHARED)
				  	{
						current_wlan_info.authMode = (GSN_WDD_SEC_MODE_T)FTW_AUTH_MODE_SHARED;
				  	}
				  	else
				  	{
						current_wlan_info.authMode = (GSN_WDD_SEC_MODE_T)FTW_AUTH_MODE_OPEN;
				  	}
			  	}


			  	if(gNwConnConfig.wlanCfg.securityCfg.pskConfig.pskValid)
			  	{
				  	s2wCurrent.lmtdApConf.lmtdApPskValid=1;
			    	memcpy(s2wCurrent.lmtdApConf.lmtdApPsk,
			           gNwConnConfig.wlanCfg.securityCfg.pskConfig.psk, GSN_WDD_SEC_PMK_LEN);
			 	}
            }
		}			
		break;
        case APP_EVENT_NCM_L4CONNECT:
        	if( GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx) == TRUE)
            AppS2wProcess_NcmAutoConnectL4Connect();
            break;
#endif
        case APP_EVENT_DHCP_RENEW_IP_CHANGED:
            AppS2wProcess_DhcpIpChangeNotify();
            break;
        case APP_EVENT_DHCP_RENEW_FAILURE:
			AppS2wProcess_DhcpStop();
            AppS2wProcess_DhcpFailNotify();
            break;
        case APP_EVENT_DHCP_STOP_REQUEST:
            AppS2wProcess_DhcpStop();
            break;
    case APP_EVENT_DHCPv4_IP_CONFLICT:
            AppS2wProcess_IpConflict();
      break;

		case APP_EVENT_DHCP_LEASETIME_EXPIRED:
		{
			VOID DHCP_notify(INT32 status,void *ctx);
			GSN_NWIF_IPv4_CONFIG_T ipConfig = {0};
			GSN_NWIF_DHCP_PARAMS_T dhcpParams = {0};
			dhcpParams.dhcpMaxRetryCnt = 4;
			pAppCtx->if0.nwifCtx.notifyCb = DHCP_notify;
			ipConfig.staticIp = FALSE;
			GsnNwif_IPv4Configure(&pAppCtx->if0.nwifCtx, &ipConfig, &dhcpParams);
		}
			break;
#ifdef FTW_PING_TRACE
#if 0/*Ping is done in a separate thread*/
        case APP_EVENT_PING_REQUEST:
            s2wPingStart();
              break;
        case APP_EVENT_PING_STOP:
            s2wPingStop();
            break;
#endif			
#endif
#ifdef FTW_IPv6_SUPPORT
        case APP_EVENT_DHCPv6_STOP_REQUEST:
            s2wDhcpv6Stop();
            break;
#endif
#ifdef FTW_SECURITY_WPS_ENABLE
		case APP_NOTIFICATION_WPS_START:
		{
			GsnOsal_SemCreate(&AppWddDisconSem, 0);
			GsnWdd_Disconnect(&pAppCtx->if0.wddCtx,
									0, AppS2w_WddDisconCb, pAppCtx);
			GsnOsal_SemAcquire(&AppWddDisconSem, GSN_OSAL_WAIT_FOREVER);
			if(pAppCtx->if0.macIfType == GSN_WIF_WLAN_NW_TYPE_AP)
			{
				App_InterfaceStop(pAppCtx, &pAppCtx->if0);
				
				pAppCtx->if0.macIfType = GSN_WIF_WLAN_NW_TYPE_STA;
				pAppCtx->if0.macIfNum= APP_DEV_INDX_0;
				App_IfReinit(pAppCtx, &pAppCtx->if0);
				//App_InterfaceStart(pAppCtx, &pAppCtx->if0);
		       // status = S2w_LoadMacAddr(macAddr);
		       S2w_macAddrRTCGet(macAddr);
		        //if (status != FTW_SUCCESS)
				{
					//S2w_Printf("\r\nINVALID MAC ADDR\r\n");
				}
		        FTW_NET_macAddrSet(macAddr,TRUE);
                GsnWdd_Ioctl(&pAppCtx->if0.wddCtx,GSN_WDD_IOCTL_RX_MODE_COUNTER_CLEAR, NULL);
				GsnWdd_Ioctl(&pAppCtx->if0.wddCtx, GSN_WDD_IOCTL_RX_ACTIVE_MODE_ON, NULL);
			}
			GsnSq_TaskMonitorStop(APP_CFG_SQ_MAIN_TASK_ID);
			GsnSq_TaskMonitorDeregister(APP_CFG_SQ_MAIN_TASK_ID);
			GsnSq_TaskMonitorRegister(APP_CFG_SQ_MAIN_TASK_ID,NULL,APP_CFG_SQ_TICKS_FOR_MAIN_TASK_WPS);
			GsnSq_TaskMonitorStart(APP_CFG_SQ_MAIN_TASK_ID,0);
			status = FTW_NET_WPS_associate(&pAppCtx->wpsParams,&pAppCtx->wpsapSsid,1);
			if(status != FTW_SUCCESS)
				AppS2wProcess_StatusNotify(status, 0);
#ifdef	FTW_UART_ENABLE
			while(FTW_UART_txStatusGet());
#endif
#ifdef  FTW_FS_SPI_ENABLE
		  // AppS2w_FsSpiFlush();
#endif
#if 1
		  	if(status == FTW_SUCCESS)
		  	{
				GsnSys_Reset(GSN_RESET_REASON_APP_SW_RESET);
			}
			GsnSq_TaskMonitorStop(APP_CFG_SQ_MAIN_TASK_ID);
			GsnSq_TaskMonitorDeregister(APP_CFG_SQ_MAIN_TASK_ID);
			GsnSq_TaskMonitorRegister(APP_CFG_SQ_MAIN_TASK_ID,NULL,APP_CFG_SQ_TICKS_FOR_MAIN_TASK);
			GsnSq_TaskMonitorStart(APP_CFG_SQ_MAIN_TASK_ID,0);
#endif
			break;
		}
#endif
        case APP_EVENT_FWUP_SUCCESS:
            GsnTaskSleep(100);
        	GsnSys_Reset(GSN_RESET_REASON_APP_FWUP);
        	break;
 #ifdef FTW_SNTP
         case APP_TIME_SYNC_TIMER_INDICATION:
             AppS2wProcess_SntpTimerNotify();
             break;
 #endif

#ifdef FTW_PERSISTENT_TMR_SUPPORT
        case APP_EVENT_PERSISTANT_TMR_0_TIMEOUT:
            S2w_Printf("\n\rPRST TMR 0 TIMEOUT\n\r");
            break;
        case APP_EVENT_PERSISTANT_TMR_1_TIMEOUT:
            S2w_Printf("\n\rPRST TMR 1 TIMEOUT\n\r");
            break;
        case APP_EVENT_PERSISTANT_TMR_2_TIMEOUT:
            S2w_Printf("\n\rPRST TMR 2 TIMEOUT\n\r");
            break;
        case APP_EVENT_PERSISTANT_TMR_3_TIMEOUT:
            S2w_Printf("\n\rPRST TMR 3 TIMEOUT\n\r");
            break;
        case APP_EVENT_PERSISTANT_TMR_4_TIMEOUT:
            S2w_Printf("\n\rPRST TMR 4 TIMEOUT\n\r");
            break;
#endif
#ifdef FTW_SECURITY_WPS_ENABLE
        case APP_EVENT_WPS_ASSOC:
#if 0
            FTW_NET_WPS_associateNotify(pAppCtx);

			f_chdrive(1);
		  	//if(status == FTW_SUCCESS)
		  	{
				GsnSys_Reset(GSN_WIF_SYS_BOOT_SW_RESET_BOOT);
			}
			GsnSq_TaskMonitorStop(APP_SQ_MAIN_TASK_ID);
			GsnSq_TaskMonitorDeregister(APP_SQ_MAIN_TASK_ID);
			GsnSq_TaskMonitorRegister(APP_SQ_MAIN_TASK_ID,NULL,APP_CFG_SQ_TICKS_FOR_MAIN_TASK);
			GsnSq_TaskMonitorStart(APP_SQ_MAIN_TASK_ID,0);
#endif
            break;
#endif

       case APP_NOTIFICATION_AUTO_SEND:
            GsnSq_TaskMonitorStop(APP_CFG_SQ_MAIN_TASK_ID);
            GsnOsal_SemAcquire ( &dSendSem, GSN_OSAL_WAIT_FOREVER );
            AppS2w_DataBufferTransmit();
            GsnOsal_SemRelease(&dSendSem);
            break;
		case APP_NOTIFICATION_BATT_INDICATION:
		{
			FTW_BAT_CHECK_process();
			// flush the data for spi-dma interface
           FTW_SPI_flush(FTW_SPI_ALL);
		}
		break;
#ifdef FTW_15DOT4_SUPPORT                
		case APP_ZIP_DELAY_PROCESS_EVENT:
			VOID App_ZipDelayHandler( VOID );
			App_ZipDelayHandler( );
			break;
#endif                        
		case APP_EVENT_GRPPROV_VERIFICATION:
		{
#ifdef  FTW_MDNS_ENABLE
			// start the mdns
			AppS2wHal_MdnsInit(NULL);
			// register the mdns names and announce the mdns services
			AppS2wCmd_MdnsAnnounceAll(NULL);
#endif
			break;	
		}

		case APP_NOTIFICATION_APPLY_SYS_REST :
		{
			GsnTaskSleep(200);
			GsnSys_Reset(GSN_RESET_REASON_APP_SW_RESET);
			break;
		}

		case APP_EVENT_EXIT_DP_SLEEP:
		{
		    AppS2w_ExitDpSleep();
		    break;
		}
    case APP_EVENT_CID_FAILURE:
            GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
            AppS2wProcess_StatusNotify(FTW_FAILURE, 0);
            GsnOsal_SemRelease(&s2wSyncSemID);
		    break;

		case APP_EVENT_DATA_SEND_FAILURE:
		    GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
	        S2w_Printf("send() failed: %d\r\n", 1);
            GsnOsal_SemRelease(&s2wSyncSemID);
		    break;
		case APP_EVENT_FTW_EINVAL:
		    GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
		    AppS2wProcess_StatusNotify(FTW_EINVAL, 0);
		    GsnOsal_SemRelease(&s2wSyncSemID);
		    break;


    }
    return GSN_SUCCESS;
}

VOID
App_CreateLock(VOID)
{

	/*Create syncronisation semaphore*/
	GsnOsal_SemCreate(&syscSem, 0);

}
VOID
App_WaitOnLock(VOID)
{
	/* Wait on semaphore */
	GsnOsal_SemAcquire(&syscSem, GSN_OSAL_WAIT_FOREVER);
	/* delete semaphore */
	GsnOsal_SemDelete(&syscSem);
}

VOID
App_UnLock(VOID)
{

	GsnOsal_SemRelease(&syscSem);

}

/*There is only one instance of wdd message handler. There may be multiple Wdd context, one per interface*/
PRIVATE VOID
AppInit_WddMsgHdlrInit(APP_MAIN_CTX_T *pAppCtx)
{
	GSN_WDD_MSG_HDLR_INIT_PARAM_T param;

	param.pStack = wddStack;
	param.stackSize = sizeof(wddStack);
	param.priority = APP_WDD_MSG_HDLR_THREAD_PRIORITY;

	param.msgSize = GsnOsal_QueueMsgSizeInWords(sizeof(GSN_WDD_MESSAGE_T));
	/* FIX:Bug 5187 - Message Queue Buffer allocation is incorrect
	    Now the mesage que size is 16*4*4=256 bytes
	    each message size is 16 bytes and max of 16 messages can be put.
	*/
	param.msgQueueBuffSize = (APP_CFG_WDD_MAX_MSG_IN_MBOX
							  * param.msgSize
							  * sizeof(UINT32) );
	param.msgQueueBuff = MALLOC(param.msgQueueBuffSize);
	if(NULL == param.msgQueueBuff)
	{
		return;
	}
	param.sysQualTskID = APP_CFG_SQ_WDD_MSG_HDLR_TASK_ID;
	param.sysQualTicks = 0;

	GsnWdd_MsgHdlrInit(&pAppCtx->wddMsgHdlrCtx, &param);

}

PRIVATE VOID
App_HiInit(APP_MAIN_CTX_T *pAppCtx)
{
	GSN_HI_INIT_PARAM_T param;
	param.dTxRdyQSize = GSN_HI_DTX_RDY_Q_SIZE;
	param.dTxDoneQSize = GSN_HI_DTX_DONE_Q_SIZE;
	param.dRxSbufRdyQSize = GSN_HI_DRX_SBUF_RDY_Q_SIZE;
	param.dRxLbufRdyQSize = GSN_HI_DRX_LBUF_RDY_Q_SIZE;
	param.dRxDoneQsize = GSN_HI_DRX_DONE_Q_SIZE;
	param.cTxRdyQSize = 4;/*GSN_HI_CTX_RDY_Q_SIZE;*/
	param.cTxDoneQSize = 4;/*GSN_HI_CTX_DONE_Q_SIZE;*/
	param.cRxSbufRdyQSize = GSN_HI_CRX_SBUF_RDY_Q_SIZE;
	param.cRxLbufRdyQsize = GSN_HI_CRX_LBUF_RDY_Q_SIZE;
	param.cRxDoneQsize = GSN_HI_CRX_DONE_Q_SIZE;
	param.hiRecvTskPrio = APP_HI_RECV_HANDLER_THREAD_PRIORITY;
	param.pHiRecvTskStack = (UINT8 *)hifMsgRcvTskStack;
	param.hiRecvTskStackSize = APP_CFG_HIF_MSG_RCV_STACK_SIZE;
	param.sysQualTaskId = APP_CFG_SQ_HI_RECV_TASK_ID;
	param.sysQualTicks = APP_CFG_SQ_TICKS_FOR_HIF_RECV_TASK;
	param.pStats = &gsnHifStats;
	GsnHi_Init(&pAppCtx->hiCtx,&param);
}

GSN_STATUS 
App_CalibDataWrIndCb(VOID *ctx, UINT8 *data, UINT32 size)
{
    APP_MAIN_CTX_T *pAppCtx = (APP_MAIN_CTX_T *)ctx;
    if(pAppCtx->fsInit != TRUE)
    {
		FTW_FS_init();
        pAppCtx->fsInit = TRUE;		
    }
    return GSN_SUCCESS;
    
}
PRIVATE VOID
App_SysCtlInit(APP_MAIN_CTX_T *pAppCtx)
{
	GSN_SYSIF_INIT_PARAM_T sysIfInitParam;
	GSN_SYS_CTL_INIT_PARAM_T sysCtlInitParam;
	sysIfInitParam.macIfNum = GSN_SYS_MACIF_NUM;
	sysIfInitParam.pHiCtx = &pAppCtx->hiCtx;
	GsnSysif_Init(&pAppCtx->sysifCtx,&sysIfInitParam);

	sysCtlInitParam.pSysifCtx = &pAppCtx->sysifCtx;
	sysCtlInitParam.macIfNum = GSN_SYS_MACIF_NUM;
	sysCtlInitParam.pStack = sysCtrlTaskStack;
	sysCtlInitParam.stackSize = sizeof(sysCtrlTaskStack);
	sysCtlInitParam.priority = APP_SYS_CTL_HANDLER_THREAD_PRIORITY;
	sysCtlInitParam.msgSize = GsnOsal_QueueMsgSizeInWords(sizeof(GSN_SYS_CTL_MESSAGE_T));
	/* FIX:Bug 5187 - Message Queue Buffer allocation is incorrect
	    Now the mesage que size is 8*2*4=64 bytes
	    each message size is 8 bytes and max of 8 messages can be put.
	*/
	sysCtlInitParam.msgQueueBuffSize = (APP_CFG_SYSCTL_MAX_MSG_IN_MBOX * 
										sysCtlInitParam.msgSize*
										sizeof(UINT32));
	sysCtlInitParam.msgQueueBuff = MALLOC(sysCtlInitParam.msgQueueBuffSize);
	if(NULL == sysCtlInitParam.msgQueueBuff)
	{
		return;
	}
	sysCtlInitParam.sysQualTskID = APP_CFG_SQ_SYS_CTL_TASK_ID;
	sysCtlInitParam.fsDriveNum = 0;
	GsnSysCtl_Init_Patch(&pAppCtx->sysCtlCtx,&sysCtlInitParam);
    GsnSysCtl_CalibDataWrIndCbReg(&pAppCtx->sysCtlCtx, App_CalibDataWrIndCb, pAppCtx);
}

VOID
App_IsotxCtrlNotifCb(VOID *ctx, UINT16 msgId, UINT16 msgLen,	VOID *pMsg)
{

    GsnOsal_SemRelease(&isoTxSem);
}

GSN_STATUS
App_IsotxDataNotifCb( VOID *pCtx, UINT16 msgLen, VOID *pMsg )
{
    return FTW_SUCCESS;
}

PRIVATE VOID
App_IsotxInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
	GSN_ISOTXIF_INIT_PARAM_T isotxifInitParam;
	GSN_ISOTX_INIT_PARAM_T isotxInitParam;

	isotxifInitParam.macIfNum = pIfInfo->macIfNum;
	isotxifInitParam.pHiCtx = &pAppCtx->hiCtx;

	GsnIsotxif_Init(&pAppCtx->isotxifCtx, &isotxifInitParam);

	isotxInitParam.macIfNum = pIfInfo->macIfNum;
	isotxInitParam.pIsotxifCtx = &pAppCtx->isotxifCtx;
	isotxInitParam.ctrlNotifCb = App_IsotxCtrlNotifCb;
	isotxInitParam.ctrlNotifCbCtx = pAppCtx;
	isotxInitParam.dataNotifCb = App_IsotxDataNotifCb;
	isotxInitParam.dataNotifCbCtx = pAppCtx;

	GsnIsotx_Init(&pAppCtx->isotxCtx, &isotxInitParam);

	// create a semaphore for isotx
    GsnOsal_SemCreate(&isoTxSem, 0);
}


PRIVATE VOID
App_NwStackInit(APP_MAIN_CTX_T *pAppCtx)
{
	GSN_NW_INIT_PARAMS_T param;

	param.sbufPktPoolPktSize = APP_NW_RX_SPKT_POOL_PKT_SIZE;
	param.sbufPktPoolSize = APP_NW_RX_SPKT_POOL_SIZE;
	param.sbufPktPoolStart = &nwSbufPktPool[0];

	param.LbufPktPoolPktSize = APP_NW_RX_LPKT_POOL_PKT_SIZE;
	param.LbufPktPoolSize = APP_NW_RX_LPKT_POOL_SIZE;
	param.LbufPktPoolStart = &nwLbufPktPool[0];

	GsnNw_Init(&pAppCtx->nwCtx, &param);
	_nx_system_ticks_per_second_update(10);/* a system tick at every 100 mSec*/
}

PRIVATE VOID
App_BsdLayerInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
	GSN_NWIF_BSD_INIT_PARAM_T bsdInitParam= {0};

	bsdInitParam.pIpHndl = &pIfInfo->nwifCtx.ipHndl;
	bsdInitParam.pBsdPktPoolHndl = GsnNw_PktPoolHndlGet(&pAppCtx->nwCtx, GSN_NW_LBUF_PKT_POOL);
	/*No separate task for BSD*/
	bsdInitParam.bsdTskStack = NULL;
	bsdInitParam.bsdTskStackSize = 0;
	bsdInitParam.bsdTskPrio = 0;

	GsnNwif_BsdInitialize(&pAppCtx->bsdCtx, &bsdInitParam);
}
VOID
App_WpaSupplicantInit(APP_MAIN_CTX_T * pAppCtx)
{
	GSN_WDD_WPA_SUP_INIT_PARAM_T param;
	
	param.pWddMsgHdlr = &pAppCtx->wddMsgHdlrCtx;
	if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != GSN_BOOT_REASON_GET())
	{
		param.randomNumSeed = NULL;
	}
	else
	{
	    param.randomNumSeed = (UINT32 *)GSN_SYS_CRYPTO_SEED_LOCATION_GET();
	}
	
	GsnWdd_WpaSupplicantInit(&param);	
}

/*Thre may be multiple interfaces. each interfce will have its own wif, wdd and Nwif context*/
VOID
App_DefaultIfInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
	pIfInfo->macIfNum= APP_DEV_INDX_0;
	pIfInfo->macIfType= (GSN_WIF_WLAN_NW_TYPE_T)s2wCurrent.mode;/*GSN_WIF_WLAN_NW_TYPE_STA;*/
	if( FTW_WLANDATA_MODE_PROV_AP == s2wCurrent.mode)
	{
		pIfInfo->macIfType = GSN_WIF_WLAN_NW_TYPE_AP;
	}
	App_IfInit(pAppCtx, pIfInfo);
}

PRIVATE VOID
App_RandomNumGenInit(VOID)
{
	
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLatchMemInfo = App_RtcLatchMemInfoPtrGet();
	UINT32 randomSeed = 0;
	if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != GSN_BOOT_REASON_GET())
	{		
		GsnHeIf_TrangGenerate((UINT8 *)&randomSeed, sizeof(randomSeed));
		pAppRtcLatchMemInfo->randomSeed = randomSeed;
	}
	else
	{
		pAppRtcLatchMemInfo->randomSeed++;
		randomSeed = pAppRtcLatchMemInfo->randomSeed;
	}

	srand(randomSeed);
}

PUBLIC VOID
App_IfInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{	
	if(GSN_WIF_WLAN_NW_TYPE_ISOTX == pIfInfo->macIfType)
	{
		/* ISOTX Initialisation */
		App_IsotxInit(pAppCtx, pIfInfo);
#if 0
		if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != GSN_BOOT_REASON_GET())
		{
			/*Open the interface. Need to open the interface after wdd and nwif initialisations?*/
			App_InterfaceStart(pAppCtx, pIfInfo);
		}
#endif                
	}
	else if(GSN_WIF_WLAN_NW_TYPE_15_4 == pIfInfo->macIfType)
	{
		VOID 
		App_WLRPANinit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);
		/* ISOTX Initialisation */
		App_WLRPANinit(pAppCtx, pIfInfo);
#if 0                
		if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != GSN_BOOT_REASON_GET())
		{
			/*Open the interface. Need to open the interface after wdd and nwif initialisations?*/
			App_InterfaceStart(pAppCtx, pIfInfo);
		}
#endif                
	}
#ifdef FTW_15DOT4_SUPPORT        
	else if(FTW_WLANDATA_MODE_ZIP == pIfInfo->macIfType)
	{
            VOID App_ZipInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);
            DBG_LOG(51);
            pIfInfo->macIfType = GSN_WIF_WLAN_NW_TYPE_15_4;
            
            /* ZIP Initialisation */
            App_ZipInit(pAppCtx, pIfInfo);
                          
	}
#endif        
	else if(GSN_WIF_WLAN_NW_TYPE_STA == pIfInfo->macIfType ||
		GSN_WIF_WLAN_NW_TYPE_AP == pIfInfo->macIfType )
	{
		/* Wif init*/
		App_WifInit(pAppCtx, pIfInfo);
#if 0
		if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != GSN_BOOT_REASON_GET())
		{
			/*Open the interface. Need to open the interface after wdd and nwif initialisations?*/
			App_InterfaceStart(pAppCtx, pIfInfo);
		}
		#endif
		GsnWdd_SetAssocTimeout(&s2wappMainTaskCtxt->if0.wddCtx, &s2wCurrent.assocConf);
		/* Wdd init*/
		App_WddInit(pAppCtx, pIfInfo);

		/* Nw interface init*/
		App_NwIfInit(pAppCtx, pIfInfo);
	}
}

/*Thre may be multiple interfaces. each interfce will have its own wif, wdd and Nwif context*/
VOID
App_IfReinit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
	GSN_WIF_RE_INIT_PARAM_T wifReinitParam;
	GSN_WDD_REINIT_PARAM_T wddReinitParam;
	GSN_NWIF_REINIT_PARAMS_T nwifReinitParam = {0};

	if(GSN_WIF_WLAN_NW_TYPE_AP == pIfInfo->macIfType ||
		GSN_WIF_WLAN_NW_TYPE_STA == pIfInfo->macIfType)
	{
	/* Close the interface*/

	/* Wif reinitialize*/
	wifReinitParam.macIfNum = pIfInfo->macIfNum;
	wifReinitParam.macIfType = pIfInfo->macIfType;

	GsnWif_Reinit(&pIfInfo->wifCtx, &wifReinitParam);

	/*Open the interface. Need to open the interface after wdd and nwif initialisations?*/
	App_InterfaceStart(pAppCtx, pIfInfo);

	/* Wdd init*/
    wddReinitParam.wlanNwType = wifReinitParam.macIfType = pIfInfo->macIfType;
	GsnWdd_Reinit(&pIfInfo->wddCtx, &wddReinitParam);

	/* Nw interface init*/
	GsnNwIf_Reinit(&pIfInfo->nwifCtx, &nwifReinitParam);

	/*The below are the things that needs to be reconfigured once we change interface*/

	/* set the min and max scan time msec */
    GsnWdd_ScanParamSet(&pAppCtx->if0.wddCtx,s2wCurrent.minScanTime,
                        s2wCurrent.registers[FTW_REG_SCAN_TIME],0);
	}
}

BOOL
App_SoftTmrMmsgHandlr(void *pCtx, void *pMsg)
{
    /*if(appCtx.dpSleep)
    {
        GSN_PWR_MGMT_CM3_SLEEP_DEEP_EN();
    }*/
    GsnSq_TaskMonitorStart(APP_CFG_SQ_SOFT_TMR_TASK_ID, *((INT32*)pMsg ));
    GsnSoftTmr_Run( pCtx, pMsg );
    GsnSq_TaskMonitorStop(APP_CFG_SQ_SOFT_TMR_TASK_ID);
 return 0;
}

GSN_SOFT_TMR_T sysTickTmr;
GSN_SOFT_TMR_T *pSysTickTmrHndl;

VOID 
App_SysTickCb(VOID* context, GSN_SOFT_TMR_HANDLE_T  timerHandle)
{
    /* Generate software interrupt and call _tx_timer_interrupt in that ISR */
    NVIC_EnableIRQ(mbReceive7_IRQn);
    NVIC_SetPendingIRQ(mbReceive7_IRQn);

    return;
}

PRIVATE VOID
App_SoftTimerInit(APP_MAIN_CTX_T *pAppCtx)
{
	APP_RTC_LATCH_MEM_INFO_T * pAppRtcLatc = App_RtcLatchMemInfoPtrGet();					
	GSN_MSG_HANDLER_CFG_T cfg1 = {"Soft Tmr Msg Handler1", softTmrMsgHHdlrStack,
					sizeof( softTmrMsgHHdlrStack ), APP_CFG_SOFT_TMR_THREAD_PRIORITY, ( UINT8* )softTmrMsgHHdlrBuff,
								sizeof( softTmrMsgHHdlrBuff ), 1};

	GsnMsgHandler_Create(&pAppCtx->softTmrMsgHdlrCtx, &cfg1, &pAppCtx->softTmrMsg,
						 App_SoftTmrMmsgHandlr, NULL);
	GsnSoftTmr_Init(0, &pAppCtx->softTmrMsgHdlrCtx);
	GsnTod_Init(GSN_SYS_TIME_OFFSET_LOC_GET());
	/* Stop ThreadX sysTick and start soft Timer sysTick */ 
    SysTick->CTRL = 0;
    pSysTickTmrHndl = GsnSoftTmr_Start(&sysTickTmr, GSN_SOFT_TMR_PERIODIC, 0,
                          MSEC_TO_SYSTIME(100), App_SysTickCb, NULL);
}

PRIVATE VOID App_InterfaceStartCb(VOID* ctx, GSN_STATUS status)
{
	App_UnLock();
}
PRIVATE VOID App_InterfaceStopCb(VOID* ctx, GSN_STATUS status)
{
	App_UnLock();
}
VOID
App_InterfaceStart(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
	GSN_SYS_CTL_IF_START_REQ_T ifcStartReq;

	/*Create syncronisation semaphore*/
	App_CreateLock();
	ifcStartReq.macIfNum = pIfInfo->macIfNum;
	ifcStartReq.macIfType = pIfInfo->macIfType;
	ifcStartReq.wlanApNumSta =s2wCurrent.lmtdApConf.noStations;
	ifcStartReq.wlanStaType= GSN_SYS_CTL_STA_TYPE_LSSTA;
	ifcStartReq.dTxRdyQFrameTO = 0;
#ifdef FTW_15DOT4_SUPPORT
    if( GSN_WIF_WLAN_NW_TYPE_15_4 == s2wCurrent.mode ||
        FTW_WLANDATA_MODE_ZIP == s2wCurrent.mode )
    {
#if 1      
        GSN_DOT154IF_START_DATA_T *pData = (GSN_DOT154IF_START_DATA_T *)ifcStartReq.reserved;
        pData->NumOfKeyTableEntries = FTW_MAX_NUM_OF_802_15_4_KEY_SUPPORTED;
        pData->NumOfDeviceTableEntries = FTW_MAX_NUM_OF_802_15_4_DEV_SUPPORTED;
        pData->NumOfSecurityLevelEntries = FTW_MAX_NUM_OF_802_15_4_SECURITY_LEVEL_SUPPORTED ;

        pData->modeOfOp = ( FTW_WLANDATA_MODE_ZIP == s2wCurrent.mode ) ? 
            GSN_DOT154IF_MODE_6LOWPAN : GSN_DOT154IF_MODE_802_15_4;
#endif
        ifcStartReq.macIfType = GSN_WIF_WLAN_NW_TYPE_15_4;
    }
#endif    
	GsnSysCtl_IfStartReq_Patch(&pAppCtx->sysCtlCtx, &ifcStartReq, App_InterfaceStartCb, NULL);

	App_WaitOnLock();
}

VOID
App_InterfaceStop(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
	GSN_SYS_CTL_IF_STOP_PARAM_T ifcStopParam;
	/*Create syncronisation semaphore*/
	App_CreateLock();

	ifcStopParam.macIfNum = pIfInfo->macIfNum;
	ifcStopParam.macIfType = pIfInfo->macIfType;
	ifcStopParam.waitPeriod = 0;
	GsnSysCtl_IfStopReq(&pAppCtx->sysCtlCtx, &ifcStopParam, App_InterfaceStopCb, NULL);

	App_WaitOnLock();
}

PRIVATE VOID
App_WifInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
	GSN_WIF_INIT_PARAM_T wifInitParam;

	/*Initialise wif module*/
	wifInitParam.macIfNum = pIfInfo->macIfNum;
	wifInitParam.macIfType = pIfInfo->macIfType;
	wifInitParam.pHiCtx= &pAppCtx->hiCtx;

	/*Register for interface init*/
	GsnWif_Init(&pIfInfo->wifCtx, &wifInitParam);
}
#if 0
GSN_WPAIF_PMK_CACHE_ENTRY pmkCache[1];
#endif

PRIVATE VOID
App_WddInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchMemInfo = App_RtcLatchMemInfoPtrGet();
    APP_RTC_SECNDRY_MEM_INFO_T *pAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();
    
	GSN_WDD_INIT_FLAG_T initFlag = GSN_WDD_INIT_FLAG_NONE;
	GSN_WDD_INIT_PARAM_T wddInitParam;

	/*Initialise WDD module*/
	wddInitParam.wlanNwType = pIfInfo->macIfType;
	wddInitParam.pWddMsgHdlr = &pAppCtx->wddMsgHdlrCtx;
	wddInitParam.pWifCtx = &pIfInfo->wifCtx;
	wddInitParam.pWddPersistInfo = &pAppRtcLtchMemInfo->ifc_1.wddRtcInfo;
	wddInitParam.pStats = &gsnWddStats;
    wddInitParam.pPmkCache  = pAppRtcSecMemInfo->pmkCache;
    wddInitParam.pmkCacheSize = sizeof(pAppRtcSecMemInfo->pmkCache);

	if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != GSN_BOOT_REASON_GET())
	{
		initFlag = GSN_WDD_INIT_FLAG_FIRST_BOOT;
	}
	GsnWdd_Init(&pIfInfo->wddCtx, &wddInitParam, initFlag);
}

PRIVATE VOID
App_NwIfInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
	GSN_NWIF_INIT_PARAMS_T param;
	/*Big time initialization :( */

	param.flags = (GSN_NWIF_FLAGS_T)(GSN_NWIF_FLG_ARP_ENABLE |	GSN_NWIF_FLG_DHCP_CLIENT_ENABLE |
				  GSN_NWIF_FLG_DNS_CLIENT_ENABLE | GSN_NWIF_FLG_ICMP_ENABLE | GSN_NWIF_FLG_IGMP_ENABLE);
	param.nwIfName = "station";
    param.pNwCtx = &pAppCtx->nwCtx;
	param.pL2Dev = (GSN_L2_DEV_T *)&pIfInfo->wddCtx;

    /*[TO DO]*/ 			/**< Power management object for power save */
	param.mtu = GSN_NW_ETHER_MTU;
	param.ipRecvFilter = NULL;
	param.ipTskStackSize = APP_NWIF_IP_THREAD_STACK_SIZE;
	param.ipTskStack = &ipStack[0];
	param.ipTskPrio = APP_NWIF_IP_THREAD_PRIORITY;
	param.ipTskSysQualID = 20;
	param.ipTskSysQualTicks = 0;//APP_CFG_SQ_TICKS_FOR_IP_TASK;
	/* Using pre created packet pool. A new paket pool can be created using
	GsnNw_PktPoolCreate() and its handle can be given*/
#ifdef FTW_VARIABLE_PING_PKT_SIZE    
	param.pIpPktPoolHndl = GsnNw_PktPoolHndlGet(&pAppCtx->nwCtx, GSN_NW_LBUF_PKT_POOL);
#else
    param.pIpPktPoolHndl = GsnNw_PktPoolHndlGet(&pAppCtx->nwCtx, GSN_NW_SBUF_PKT_POOL);
#endif   

	param.arpCacheSize = APP_NWIF_IP_THREAD_ARP_CACHE_SIZE;
	param.arpCache = &arpCache[0];
	param.pStats = &gsnNwifStats;
	GsnNwIf_Init(&pIfInfo->nwifCtx, &param);
#ifdef FTW_IPv6_SUPPORT
        GsnNwif_IPv6Init(&pIfInfo->nwifCtx, NULL);
        GsnNwif_Ipv6AutoConfig(&pIfInfo->nwifCtx,TRUE);
#endif
    /* register the s2w filter */
    GsnNwIf_RecvFilterRegister(&pIfInfo->nwifCtx,AppS2wRecv_Filter);
}

VOID 
App_WlanRespTimeoutTmrCb( VOID* context,
    								GSN_SOFT_TMR_HANDLE_T  timerHandle )
{	
	GSN_ASSERT(FALSE);
}

PRIVATE VOID
App_WlanBootIndCb(VOID *ctx, INT32 status)
{
	GsnSoftTmr_Stop(wlanRespTimeoutTmrHndl);
	/**/
	App_UnLock();
}


UINT8 *moduleTypes[] = 
{
    "EIM1102",    //2011MIE
    "ZIM1102",    //2011MIZ
    "SEIM1102",   //2011MIES
    "SPIM1102",   //2011MIPS
    "EIM0012",    //2100MIE
    "PIM0012"     //2100MIP
};

PRIVATE GSN_STATUS
App_WlanBootReq(APP_MAIN_CTX_T *pAppCtx)
{
	GSN_SYS_CTL_BOOT_REQ_PARAM_T bootReqParm;
	APP_RTC_SECNDRY_MEM_INFO_T *PAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();
	//APP_RTC_LATCH_MEM_INFO_T *PAppRtcLatchMemInfo = App_RtcLatchMemInfoPtrGet();    
	F_FILE *pFile;
    UINT32 rfCalibDataSize, fileSize;
    UINT8 data[16]; 
    UINT16 dataLen, i;
    
	/*Create syncronisation semaphore*/
	App_CreateLock();

	/*Give Boot request to Wlan*/
	bootReqParm.bootReason = GSN_BOOT_REASON_GET();
	bootReqParm.bootSubreason = GSN_BOOT_INFO_GET();
	bootReqParm.bootTimeHigh = 0;
	bootReqParm.bootTimeLow = 0;
	bootReqParm.confLost = 1;
	bootReqParm.numIfs = 1;
	bootReqParm.ifTypes[0]= GSN_WIF_WLAN_NW_TYPE_STA;
	bootReqParm.fwFlashAddr = romFwImageFlashAddr;
	bootReqParm.stdbyCtxLen = PAppRtcSecMemInfo->macStdbyCtxLen;
	bootReqParm.pStdbyCtx = (UINT8*)PAppRtcSecMemInfo->macStdbyCtx;
	bootReqParm.modType = 0;

    
    if(GsnOtpMm_Read(10, 1, &dataLen, data) == GSN_SUCCESS)
    {
        for(i = 0; i < 6; i++)
        {
            if(strstr((char const *)(data+8), (char const *)moduleTypes[i]))
            {
                break;
            }
        }
        if(i < 6)
        {
            bootReqParm.modType = (i + 1);
        }
    }
    
    if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != GSN_BOOT_REASON_GET())
    {
        
        pFile = f_open(WLAN_RF_CALIB_DATA_FILE_NAME, "r");
        if(!pFile)
        {
            /*File Not present - Create new*/;
            pFile = f_open(WLAN_RF_CALIB_DATA_FILE_NAME, "w+");
            if(!pFile)
            {
                /*[TO DO ] Handle Error*/
            }
        }

        fileSize=f_filelength(WLAN_RF_CALIB_DATA_FILE_NAME);
        rfCalibDataSize = f_read(bootReqParm.rfCalibData, 1, fileSize, pFile);
        if(!rfCalibDataSize) 
         {
            /*[TO DO: handle failure]*/;
        }
        bootReqParm.rfCalibDataSize = rfCalibDataSize;

        
        /* Close the file*/
        f_close(pFile);
        
    }
    
	wlanRespTimeoutTmrHndl = GsnSoftTmr_Start(&wlanRespTimeoutTmr, GSN_SOFT_TMR_ONESHOT, 0,
												SEC_TO_SYSTIME(10),
												App_WlanRespTimeoutTmrCb, NULL);
	GsnSysCtl_BootReq_Patch(&pAppCtx->sysCtlCtx, &bootReqParm, App_WlanBootIndCb, pAppCtx);
    GsnSysCtl_DieTempSendTimerStart(&pAppCtx->sysCtlCtx, 5);
	/*Wait for Boot indication*/
	//App_WaitOnLock();
        return GSN_SUCCESS;
}


PRIVATE VOID
App_SysQualInit()
{
    GsnSq_Init();
	GsnSq_TaskMonitorRegister(APP_CFG_SQ_SOFT_TMR_TASK_ID, NULL, APP_CFG_SQ_TICKS_FOR_SOFT_TMR_TASK);
	GsnSq_TaskMonitorRegister(APP_CFG_SQ_HI_RECV_TASK_ID, NULL, APP_CFG_SQ_TICKS_FOR_HIF_RECV_TASK);
	GsnSq_TaskMonitorRegister(APP_CFG_SQ_SYS_CTL_TASK_ID, NULL, APP_CFG_SQ_TICKS_FOR_SYS_CTL_TASK);	
	GsnSq_TaskMonitorRegister(APP_CFG_SQ_WDD_MSG_HDLR_TASK_ID, NULL, APP_CFG_SQ_TICKS_FOR_WDD_MSG_HDLR_TASK);
	GsnSq_TaskMonitorRegister(APP_CFG_SQ_IP_TASK_ID, NULL, APP_CFG_SQ_TICKS_FOR_IP_TASK);
	GsnSq_TaskMonitorRegister(APP_CFG_SQ_DHCPV4_TASK_ID, NULL, APP_CFG_SQ_TICKS_FOR_DHCPV4_TASK);
	GsnSq_TaskMonitorRegister(APP_CFG_SQ_HTTPD_TASK_ID, NULL, APP_CFG_SQ_TICKS_FOR_HTTPD_TASK);
	GsnSq_TaskMonitorRegister(APP_CFG_SQ_MAIN_TASK_ID, NULL, APP_CFG_SQ_TICKS_FOR_MAIN_TASK);
	GsnSq_TaskMonitorRegister(APP_CFG_SQ_NETRX_TASK_ID, NULL, APP_CFG_SQ_TICKS_FOR_NETRX_TASK);	
	GsnSq_TaskMonitorRegister(APP_CFG_SQ_SERIAL_INPUT_TASK_ID,NULL, APP_CFG_SQ_TICKS_FOR_SERIAL_INPUT_TASK);
}

VOID
App_RtcDump(VOID)
{
	UINT8 i;
	GSN_SYS_RESET_INFO_T *pResetInfo= (GSN_SYS_RESET_INFO_T *)GSN_SYS_RESET_INFO_LOCATION_GET();
	GSN_SYS_RESERVD_RTC_INFO_T *pResrvdInfo = (GSN_SYS_RESERVD_RTC_INFO_T *)RTC_LATCH_MEM_ADDR;

	S2w_Printf("\r\n");

	S2w_Printf("Boot Reason :    %d\r\n", pResrvdInfo->bootReason);
	S2w_Printf("Boot Info :      %d\r\n", pResrvdInfo->bootReason);
	S2w_Printf("Reset Type:      %d\r\n", pResetInfo->app.resetType);
	S2w_Printf("Reset Reason :   %d\r\n", pResetInfo->app.resetReason);
	S2w_Printf("Reset Info Size: %d\r\n", pResetInfo->app.resetInfoSize);
	S2w_Printf("Reset Addl Info: 0x%x\r\n", pResetInfo->app.resetAddlInfo);
	S2w_Printf("ResetInfo:\r\n");
	for(i = 0; i < 16; i++)
	{
	S2w_Printf("\t0x%08x\r\n", pResetInfo->app.resetInfo[i]);
	}
	S2w_Printf("\r\n");
}

PUBLIC VOID
AppS2w_RtcCfg()
{
	if(GSN_WIF_SYS_BOOT_NORMAL_BOOT == GSN_BOOT_REASON_GET())
	{/*Configure RTC SRAM Bank*/
        RTC_SX_SWT2LDO_SET(RTC,0);
        SX_EN_ULDO_CLEAR(RTC);
        RTC_SRAM_ISO_ENABLE_CLEAR(RTC);
	}
}



#ifdef FTW_IP2WIFI_SUPPORT
VOID
AppInit_L2DevInit(APP_MAIN_CTX_T *pAppCtx)
{
    s2wL2Dev_Init(&(pAppCtx->s2wL2Dev), "wif0",
                    (GSN_L2_DEV_T *)&(pAppCtx->if0.wddCtx));
}
#endif


UINT8
s2w_StartDhcpDnsServer()
{
#ifdef FTW_DHCP_SERVER_ENABLE
                if(s2wCurrent.mode == FTW_WLANDATA_MODE_PROV_AP)
                {
                    if(FTW_DEFAULT_GRP_PROV_DHCPSRVR_ENABLE)
                    {
                        memset(&dhcpSrvrCfg,0,sizeof(GSN_DHCP_SRVR_CFG_T));
                        dhcpSrvrCfg.numOfClients = FTW_DEFAULT_GRP_PROV_SUPPORTED_STATIONS;
                        dhcpSrvrCfg.startIpAddr =  FTW_DEFAULT_GRP_PROV_IP_START_ADDRESS;
                        dhcpSrvrCfg.leaseTime = FTW_DEFAULT_GRP_PROV_LEASE_TIME;
                        dhcpSrvrCfg.serverIpAddr = FTW_DEFAULT_GRP_PROV_IP_ADDRESS;
                        dhcpSrvrCfg.startIpAddr = FTW_DEFAULT_GRP_PROV_IP_START_ADDRESS;
                        dhcpSrvrCfg.subnetMask = FTW_DEFAULT_GRP_PROV_SUBNET_ADDRESS;
                        dhcpSrvrCfg.gateway = FTW_DEFAULT_GRP_PROV_GATE_ADDRESS;
                        dhcpSrvrCfg.dns1 = dhcpSrvrCfg.serverIpAddr;
                        dhcpSrvrCfg.pNwif = &s2wappMainTaskCtxt->if0.nwifCtx;
                        GsnDhcpSrvr_Start(&dhcpSrvr, &dhcpSrvrCfg);
#ifdef FTW_DNS_SERVER_ENABLE
                        GSN_DNS_INIT_PARAM_T gsnDnsInitParams;
                        if(FTW_DEFAULT_GRP_PROV_DNSSRVR_ENABLE)
                        {
                            GSN_NWIF_IP_CONFIG_T  ipconfig;
                            memset(&ipconfig,0,sizeof(GSN_NWIF_IP_CONFIG_T));
                            memset(&gsnDnsInitParams,0,sizeof(GSN_DNS_INIT_PARAM_T));
                            GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx,&ipconfig);
                            gsnDnsInitParams.flags = IP_VERSION_V4;
                            gsnDnsInitParams.serverIpAddr = ipconfig.ipv4.ipAddr;
                            GsnDnsSrvr_Start(&dnsServer,FTW_DEFAULT_GRP_PROV_DNS_NAME,&gsnDnsInitParams);
                        }
#endif
                        // fill the http server details
                        // grop prov will not support username/pwd authentication so rest it
                        memset(&s2wappMainTaskCtxt->WebServerCfg.username,0,sizeof(s2wappMainTaskCtxt->WebServerCfg.username));
                        memset(&s2wappMainTaskCtxt->WebServerCfg.passwd,0,sizeof(s2wappMainTaskCtxt->WebServerCfg.passwd));
                        s2wappMainTaskCtxt->WebServerCfg.sslEnabled = TRUE;
                        s2wappMainTaskCtxt->WebServerCfg.IdleTimeOut = FTW_DFLT_HTTP_SRVR_IDLE_TIMEOUT;
                        s2wappMainTaskCtxt->WebServerCfg.storeParams = TRUE;
                        // start the L4(web prov) if auto connection enabled
					    UINT32 message = APP_NOTIFICATION_PROV_START;
                        s2wappMainTaskCtxt->webProvStatus=START;
                        (s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
                    }
                }

                else if(s2wCurrent.lmtdApConf.dhcpServerEnable)
                {

                    if(!(dhcpServerFlags & FTW_DHCP_SRVR_CFG_DONE))
                    {
                      memset(&dhcpSrvrCfg,0,sizeof(GSN_DHCP_SRVR_CFG_T));
                      dhcpSrvrCfg.numOfClients = s2wCurrent.lmtdApConf.dhcpNumAddresses;
                      dhcpSrvrCfg.startIpAddr =  (s2wCurrent.lmtdApConf.dhcpAddressStart);
                      dhcpSrvrCfg.leaseTime = s2wCurrent.lmtdApConf.dhcpLeaseTime;
                    }

                    memcpy(&dhcpSrvrCfg.serverIpAddr,&s2wCurrent.lmtdApConf.ipAddress,4);

                    if((dhcpSrvrCfg.startIpAddr & 0xFFFFFF00) != (dhcpSrvrCfg.serverIpAddr & 0xFFFFFF00))
                    {
						dhcpSrvrCfg.startIpAddr = dhcpSrvrCfg.serverIpAddr + 1;
                    }
                    dhcpSrvrCfg.subnetMask = (s2wCurrent.lmtdApConf.subnetmask);
                    dhcpSrvrCfg.gateway = (s2wCurrent.lmtdApConf.gateway);
                    dhcpSrvrCfg.dns1 = dhcpSrvrCfg.serverIpAddr;
					dhcpSrvrCfg.pNwif = &s2wappMainTaskCtxt->if0.nwifCtx;
                    GsnDhcpSrvr_Start(&dhcpSrvr, &dhcpSrvrCfg);
#ifdef FTW_DNS_SERVER_ENABLE
                    GSN_DNS_INIT_PARAM_T gsnDnsInitParams;
                    if(s2wCurrent.lmtdApConf.dnsServerEnable)
                    {
                        memset(&gsnDnsInitParams,0,sizeof(GSN_DNS_INIT_PARAM_T));
                        S2wDnsConfigGet(&gsnDnsInitParams);
                        GsnDnsSrvr_Start(&dnsServer,s2wCurrent.lmtdApConf.dnsDomainName,&gsnDnsInitParams);
                    }

#endif
                }
#endif
return 0;
}


