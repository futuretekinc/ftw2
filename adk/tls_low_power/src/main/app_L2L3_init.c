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
* $RCSfile: app_L2L3_init.c,v $
*******************************************************************************/

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/

#include "gsn_includes.h"
#include "gsn_includes.h"
#include "config/app_cfg.h"
#include "fs_if/app_fsIf.h"
#include "gsn_ncm.h"
#include "app_main_ctx.h"
#include "app_sm.h"
#include "app_ncm.h"
#include "app_resource_config.h"
#include "app_events.h"
#include "app_debug.h"
#include "app_rtc_mem.h"
#include "gsn_httpd_config.h"
#include "app_fsIf.h"
#include "app_default_cfg.h"
/*****************************************************************************
 *Private definitions
 ****************************************************************************/
#define APP_DEV_INDX_0	0

extern APP_MAIN_CTX_T appCtx;
extern GSN_OSAL_THREAD_TCB_T appMainCtxThread;

/*****************************************************************************
 *Private variables
 ****************************************************************************/
/* WDD stuff */
PRIVATE UINT32 wddStack[APP_CFG_WDD_MSG_HDLR_STACK_SIZE/sizeof(UINT32)];

/*Hi message system */
PRIVATE UINT32 hiRecvTaskStack[APP_CFG_HI_RCV_TASK_STACK_SIZE/sizeof(UINT32)];

PRIVATE UINT32 sysCtrlTaskStack[APP_CFG_SYS_CTL_TASK_STACK_SIZE/sizeof(UINT32)];

/* Soft Timer*/
//UINT32 softTmrMsgHHdlrStack[ APP_CFG_SOFT_TMR_STACK_SIZE/sizeof(UINT32) ];
//UINT32 softTmrMsgHHdlrBuff[ APP_CFG_SOFT_TMR_MAX_MSG_IN_MBOX ];
INT8 ipStack[APP_NWIF_IP_THREAD_STACK_SIZE];
INT8 arpCache[APP_NWIF_IP_THREAD_ARP_CACHE_SIZE];

/* Boot indication synchronization mutex*/
GSN_OSAL_SEM_T syncSem;

GSN_HIF_STATS_T gsnHifStats = {0xaa, 0xbb, 0xff, 0xda};
GSN_WDD_STATS_T gsnWddStats;
GSN_NWIF_STATS_T gsnNwifStats;

PRIVATE GSN_SOFT_TMR_T	wlanRespTimeoutTmr;
PRIVATE GSN_SOFT_TMR_HANDLE_T wlanRespTimeoutTmrHndl;

/*****************************************************************************
 *Private Function prototypes
 ****************************************************************************/
extern VOID
App_LedStatusSet(UINT8 status);

PRIVATE VOID
AppInit_WddMsgHdlrInit(APP_MAIN_CTX_T *pAppCtx);

PRIVATE VOID
App_HiInit(APP_MAIN_CTX_T *pAppCtx);

PRIVATE VOID
App_WpaSupplicantInit(APP_MAIN_CTX_T * pAppCtx);

PRIVATE VOID
App_IfInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *ifInfo);

PRIVATE VOID
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
APP_BsdLayerInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);

PRIVATE VOID
App_SoftTimerInit(APP_MAIN_CTX_T *pAppCtx);

PRIVATE VOID
App_SysQualInit();

PRIVATE VOID
App_SysCtlInit(APP_MAIN_CTX_T *pAppCtx);

PRIVATE VOID
App_InterfaceStart(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);

extern VOID	App_Cm3ClkCfg(APP_MAIN_CTX_T *pAppCtx);

/*****************************************************************************
 *Public and Private functions
 ****************************************************************************/
PRIVATE VOID
App_CreateLock(VOID)
{
#if 1
	/*Create syncronisation semaphore*/
	GsnOsal_SemCreate(&syncSem, 0);
#endif
}

PRIVATE VOID
App_WaitOnLock(VOID)
{
#if 1
	/* Wait on semaphore */
	GsnOsal_SemAcquire(&syncSem, GSN_OSAL_WAIT_FOREVER);
	/* delete semaphore */
	GsnOsal_SemDelete(&syncSem);
#endif	
}

PRIVATE VOID
App_UnLock(VOID)
{
#if 1
	GsnOsal_SemRelease(&syncSem);
#endif
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
        
		randomSeed = pAppRtcLatchMemInfo->randomSeed;
	}

	srand(randomSeed);
}

GSN_CLK_CTL_CTX_T gsnBrClkCtlCtx1;
GSN_OTP_T appBrOtpCtx1;
GSN_OTP_MM_CTX_T appBrOtpMmCtx1;

/* Define the test threads.  */
VOID    
 AppL2L3_Init(APP_MAIN_CTX_T *pAppCtx)
{
	UINT32 wlanVer = 0;
	UINT32 pltVersion;
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();

    /*UINT status;*/
    APP_MAINTASK_MSG_T msg = {0};

	GsnClkCtl_Init(&gsnBrClkCtlCtx1);
	GsnExcpHdlr_Init();

    /* Initiailize the UART early to support prints */
#ifndef POWER_MEASUREMENT_ENABLE
    AppUart_Init();
#endif
	
	AppDbg_Printf("Boot Reason = %d\r\n", GSN_BOOT_REASON_GET());

	/*Initialse File system. File system is must and is also used by WLAN Sw*/
	/*App_FsInit(&pAppCtx->fs);*/

	/*Initialise Default configuration*/
	if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != GSN_BOOT_REASON_GET() )
	{
		App_FsInit(&pAppCtx->fs);
		/* initialize low level OTP driver */
	GSN_OTP_CTX_USES_OBJS_S otpUsesObjs;
		

	otpUsesObjs.pClkCtl = GsnClkCtl_CtxGet();
	GsnOtp_Init(&appBrOtpCtx1, &otpUsesObjs, NULL);

	/* initialize OTP MM module */
	GSN_OTP_MM_USES_OBJS_T otpMmUsesObjs;
	otpMmUsesObjs.otpDrv = &appBrOtpCtx1;
	GsnOtpMm_Init(&appBrOtpMmCtx1, &otpMmUsesObjs, NULL);
		AppConfig_DefaultInit(&pAppCtx->config);
	}
	if(GSN_WIF_SYS_BOOT_NORMAL_BOOT == GSN_BOOT_REASON_GET())
	{
		App_ReStoreStdbyData(pAppCtx);
	}
	
	/*Initialise SysQual*/
	App_SysQualInit();

	/*Initialise wif message system*/
	App_HiInit(pAppCtx);

	/*Initialise wif System Control message Handler */
	App_SysCtlInit(pAppCtx);

	/* Initialise Wpa Suppliacnt*/
	App_WpaSupplicantInit(pAppCtx);

	App_RandomNumGenInit();
	
	/* Give boot request */
#ifndef POWER_MEASUREMENT_ENABLE
	GsnGpio_OutIndvidualSet(LED_GPIO_8);
#endif

	App_WlanBootReq(pAppCtx);
	
	/*Initialise Wdd Message Handler */
	AppInit_WddMsgHdlrInit(pAppCtx);

	/*Initialize Nw statck. This is a one time initialisation*/
	App_NwStackInit(pAppCtx);

	/*Wait for Boot indication*/
	App_WaitOnLock();
#ifndef POWER_MEASUREMENT_ENABLE
	GsnGpio_OutClear(LED_GPIO_8);
#endif
	
	/*Initialise an interface on device Index 0 of Wlan Nw type STA*/	
	App_DefaultIfInit(pAppCtx, &pAppCtx->if0);

	APP_BsdLayerInit(pAppCtx, &pAppCtx->if0);
	
	AppSm_Init(pAppCtx);
	AppNcm_Init(pAppCtx);	
	AppDbg_Printf("%s [%s, %s]\r\n", AppConfig_GetAppNameAndVersion(), __DATE__,__TIME__);

	pltVersion = GsnVersion_Get();
	AppDbg_Printf("GEPS VERSION %d.%d.%d.%d\r\n",((pltVersion >> 24) & 0xff),
		               ((pltVersion >>16) & 0xff),((pltVersion>>8) & 0xff),(pltVersion & 0xff));

	GsnSysCtl_WlanFwVerGet(&pAppCtx->sysCtlCtx,&wlanVer);
	AppDbg_Printf("WLAN VERSION %d.%d.%d.%d\r\n",((wlanVer >> 24) & 0xff),
			            ((wlanVer >>16) & 0xff),((wlanVer>> 8 ) & 0xff),(wlanVer & 0xff));
	AppMainCtx_TaskNotify(APP_EVENT_NW_START_NCM, 0);	

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
	//param.msgQueueBuffSize = APP_CFG_WDD_MSG_HDLR_MAX_MSG_IN_MBOX * param.msgSize;

	/* FIX:Bug 5187 - Message Queue Buffer allocation is incorrect
	    Now the mesage que size is 16*4*4=256 bytes
	    each message size is 16 bytes and max of 16 messages can be put.
	*/
	param.msgQueueBuffSize = (APP_CFG_WDD_MSG_HDLR_MAX_MSG_IN_MBOX
							  * param.msgSize
							  * sizeof(UINT32) );

	param.msgQueueBuff = MALLOC(param.msgQueueBuffSize);
	if(NULL == param.msgQueueBuff)
	{
		while(1);
	}
	param.sysQualTskID = APP_CFG_SQ_WDD_MSG_HDLR_TASK_ID;
	param.sysQualTicks = APP_CFG_SQ_TICKS_FOR_WDD_MSG_HDLR_TASK;

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
	param.cTxRdyQSize = GSN_HI_CTX_RDY_Q_SIZE;
	param.cTxDoneQSize = GSN_HI_CTX_DONE_Q_SIZE;
	param.cRxSbufRdyQSize = GSN_HI_CRX_SBUF_RDY_Q_SIZE;
	param.cRxLbufRdyQsize = GSN_HI_CRX_LBUF_RDY_Q_SIZE;
	param.cRxDoneQsize = GSN_HI_CRX_DONE_Q_SIZE;
	param.hiRecvTskPrio = APP_HI_RECV_HANDLER_THREAD_PRIORITY;
	param.pHiRecvTskStack = (UINT8 *)hiRecvTaskStack;
	param.hiRecvTskStackSize = APP_CFG_HI_RCV_TASK_STACK_SIZE;
	param.sysQualTaskId = APP_CFG_SQ_HI_RECV_TASK_ID;
	param.sysQualTicks = APP_CFG_SQ_TICKS_FOR_HI_RECV_TASK;
	param.pStats = &gsnHifStats;
	GsnHi_Init(&pAppCtx->hiCtx,&param);
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
	//sysCtlInitParam.msgQueueBuffSize = APP_CFG_SYSCTL_MAX_MSG_IN_MBOX * sysCtlInitParam.msgSize;

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
		while(1);
	}	
	sysCtlInitParam.sysQualTskID = APP_CFG_SQ_SYS_CTL_TASK_ID;	
	sysCtlInitParam.fsDriveNum = 0;
	GsnSysCtl_Init_Patch(&pAppCtx->sysCtlCtx,&sysCtlInitParam);
}

PRIVATE VOID
App_NwStackInit(APP_MAIN_CTX_T *pAppCtx)
{
	GSN_NW_INIT_PARAMS_T param;

	param.sbufPktPoolPktSize = APP_NW_SPKT_POOL_PKT_SIZE;
	param.sbufPktPoolSize = APP_NW_SPKT_POOL_SIZE;
	param.sbufPktPoolStart = MALLOC(APP_NW_SPKT_POOL_SIZE);
	if(NULL == param.sbufPktPoolStart)
	{
		while(1);
	}
	param.LbufPktPoolPktSize = APP_NW_LPKT_POOL_PKT_SIZE;
	param.LbufPktPoolSize = APP_NW_LPKT_POOL_SIZE;
	param.LbufPktPoolStart = MALLOC(APP_NW_LPKT_POOL_SIZE);
	if(NULL ==param.LbufPktPoolStart)
	{
		while(1);
	}
	GsnNw_Init(&pAppCtx->nwCtx, &param);
}

PRIVATE VOID
APP_BsdLayerInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
	GSN_NWIF_BSD_INIT_PARAM_T bsdInitParam = {0};

	bsdInitParam.pIpHndl = &pIfInfo->nwifCtx.ipHndl;
	bsdInitParam.pBsdPktPoolHndl = GsnNw_PktPoolHndlGet(&pAppCtx->nwCtx, GSN_NW_LBUF_PKT_POOL);	
	/*No separate task for BSD*/
	bsdInitParam.bsdTskStack = NULL;
	bsdInitParam.bsdTskStackSize = 0;
	bsdInitParam.bsdTskPrio = 0;
	
	GsnNwif_BsdInitialize(&pAppCtx->bsdCtx, &bsdInitParam);
}

PRIVATE VOID
App_WpaSupplicantInit(APP_MAIN_CTX_T * pAppCtx)
{
	GSN_WDD_WPA_SUP_INIT_PARAM_T param;
	param.pWddMsgHdlr = &pAppCtx->wddMsgHdlrCtx;
	param.randomNumSeed = NULL;
    // fix for RNG....
    RTC_TRNG_OSC_STOP_N_F_SET(RTC);
	GsnWdd_WpaSupplicantInit(&param);
}

PRIVATE VOID
App_DefaultIfInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
	pIfInfo->macIfType = (GSN_INFRA_CLIENT == pAppCtx->config.networkConfig.networkMode)?
							GSN_WIF_WLAN_NW_TYPE_STA : GSN_WIF_WLAN_NW_TYPE_AP;	
	
	pIfInfo->macIfNum= APP_DEV_INDX_0;
	App_IfInit(pAppCtx, pIfInfo);
}

/*Thre may be multiple interfaces. each interfce will have its own wif, wdd and Nwif context*/
PRIVATE VOID
App_IfInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
	/* Wif init*/
	App_WifInit(pAppCtx, pIfInfo);

	if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != GSN_BOOT_REASON_GET())
	{
		/*Open the interface. Need to open the interface after wdd and nwif initialisations?*/
		App_InterfaceStart(pAppCtx, pIfInfo);
	}
	
	/* Wdd init*/
	App_WddInit(pAppCtx, pIfInfo);
		
	/* Nw interface init*/
	App_NwIfInit(pAppCtx, pIfInfo);
	
}

/*Thre may be multiple interfaces. each interfce will have its own wif, wdd and Nwif context*/
VOID
App_IfReinit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
	GSN_WIF_RE_INIT_PARAM_T wifReinitParam;
	GSN_WDD_REINIT_PARAM_T wddReinitParam;
	GSN_NWIF_REINIT_PARAMS_T nwifReinitParam = {0};
	
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
    GsnWdd_ScanParamSet(&pAppCtx->if0.wddCtx,DEFAULT_CLI_MIN_SCAN_TIME, 
    						DEFAULT_CLI_MAX_SCAN_TIME, 0);
	
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
	ifcStartReq.wlanApNumSta = 8;
	ifcStartReq.wlanStaType= GSN_SYS_CTL_STA_TYPE_LSSTA;
	ifcStartReq.dTxRdyQFrameTO = 0;
	GsnSysCtl_IfStartReq(&pAppCtx->sysCtlCtx, &ifcStartReq, App_InterfaceStartCb, NULL);
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

#ifdef ENABLE_STDBY_BTWN_BEACONS
VOID 
App_DabindCb(VOID *ctx)
{
	AppMainCtx_TaskNotify(APP_EVENT_DAB_INDIACTION, 0);	
}
#endif

PRIVATE VOID
App_WddInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchMemInfo = App_RtcLatchMemInfoPtrGet();
	GSN_WDD_INIT_PARAM_T wddInitParam;
	GSN_WDD_STA_PS_CFG_SET_PARAM_T pscfg;

	/*Initialise WDD module*/
	wddInitParam.wlanNwType = pIfInfo->macIfType;
	wddInitParam.pWddMsgHdlr = &pAppCtx->wddMsgHdlrCtx;
	wddInitParam.pWifCtx = &pIfInfo->wifCtx;
	wddInitParam.pWddPersistInfo = &pAppRtcLtchMemInfo->ifc_1.wddRtcInfo;
	wddInitParam.pStats = &gsnWddStats;
    wddInitParam.pPmkCache  = NULL;
    wddInitParam.pmkCacheSize = 0;
	GsnWdd_Init(&pIfInfo->wddCtx, &wddInitParam, GSN_WDD_INIT_FLAG_NONE);

	GsnWdd_Ioctl(&pAppCtx->if0.wddCtx,GSN_WDD_IOCTL_MCAST_RX_ON, NULL);
	
	if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != GSN_BOOT_REASON_GET())
	{
		/* Note : Set this before Nwif init() is done. Initialise mac address*/
		GsnWdd_PhyAddrSet(&pAppCtx->if0.wddCtx, (INT8 *)pAppCtx->config.networkConfig.macAddr, 1);
	}
	else
	{/*It's NORMAL BOOT*/
		GsnWdd_PhyAddrSet(&pAppCtx->if0.wddCtx, (INT8 *)pAppCtx->config.networkConfig.macAddr, 0);
		GsnWdd_AssocStatusSet(&pAppCtx->if0.wddCtx);
	}

#ifdef ENABLE_STDBY_BTWN_BEACONS
	/**/
	GsnWdd_Ioctl(&pAppCtx->if0.wddCtx,GSN_WDD_IOCTL_RX_PS_MODE_ON, NULL);
	
	GsnWdd_DabDoneIndCbReg(&pAppCtx->if0.wddCtx, App_DabindCb, pAppCtx);
#else
	if((GSN_BOOT_REASON_GET() == GSN_WIF_SYS_BOOT_FIRST_BOOT) 
           || (GSN_BOOT_REASON_GET() == GSN_WIF_SYS_BOOT_SW_RESET_BOOT) )
	{
		// nothing to be done here as we are assuming that RX is off by default
		// so nothing to be switched off explicitly
		//GsnWdd_Ioctl(&pAppCtx->if0.wddCtx,GSN_WDD_IOCTL_RX_ACTIVE_MODE_OFF, NULL);
		//GsnWdd_Ioctl(&pAppCtx->if0.wddCtx,GSN_WDD_IOCTL_RX_PS_MODE_ON, NULL);
	}
#endif

	/* set the min and max scan time msec */
    GsnWdd_ScanParamSet(&pAppCtx->if0.wddCtx,DEFAULT_CLI_MIN_SCAN_TIME, 
    						DEFAULT_CLI_MAX_SCAN_TIME, 0);

	pscfg.wakeupType = GSN_WDD_STA_PS_WAKEUP_DTIM;
	pscfg.wakeupInterval = 5;
	pscfg.listenIntervalAssoc = 0;
	pscfg.dataRxType = GSN_WDD_STA_PS_DATA_RX_TYPE_PS_POLL;
	pscfg.uapsdEnable = 0;
    pscfg.txAtTbttWakeup = 0;
    pscfg.beaconWaitTimeout = 10;
    pscfg.activeToOffTimeout = 0;

	GsnWdd_RadioPowerSaveCfgSet(&pAppCtx->if0.wddCtx, &pscfg);
}

BOOL 
App_IsArpReqstPkt(GSN_NWIF_CTX_T *pNwIf, GSN_ETHERNET_FRAME_T *pEthFrame, 
                                                                                                                                UINT32 protocol)
{
	UINT32 ipAddr;
	ipAddr = htonl(GsnNwIf_IpV4AddrGet(pNwIf));
	/* An ARP Request Pkt with  Destination address being  the node address */
	return ((GSN_ETH_PROTO_TYPE_ARP == protocol) &&
			(GSN_NW_ARP_REQUEST ==
						htons((GsnNwIf_U16FieldGet)(pEthFrame->Data + GSN_NW_ARP_OP_OFFSET))) &&
			(0 == memcmp(&ipAddr, (pEthFrame->Data + GSN_NW_ARP_TAGET_IP_OFFSET), 4)));
}

BOOL 
App_IsArpReplyPkt(GSN_NWIF_CTX_T *pNwIf, GSN_ETHERNET_FRAME_T *pEthFrame, 
                                                                                                                                UINT32 protocol)
{
    UINT32 ipAddr;
    ipAddr = htonl(GsnNwIf_IpV4AddrGet(pNwIf));
    /* An ARP Request Pkt with  Destination address being  the node address */
    return ((GSN_ETH_PROTO_TYPE_ARP == protocol) &&
             (GSN_NW_ARP_RESPONSE == htons((GsnNwIf_U16FieldGet)(pEthFrame->Data + GSN_NW_ARP_OP_OFFSET))));
}

BOOL 
App_NwRecvFilter      (GSN_NWIF_CTX_T *pNwIf, UINT32 len , GSN_ETHERNET_FRAME_T *pEthFrame)
{
    BOOL filterPass = TRUE;
    UINT16 protocol;
    
    protocol = swap_16(pEthFrame->UpperProtocolType);
    if(GSN_ETH_PROTO_TYPE_ARP == protocol)
    {
        filterPass = FALSE;
        if(TRUE == App_IsArpReqstPkt(pNwIf, pEthFrame, protocol) || 
                        TRUE == App_IsArpReplyPkt(pNwIf, pEthFrame, protocol))
        {
			filterPass = TRUE;
        }
    }

    return filterPass;
}
                

PRIVATE VOID
App_NwIfInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo)
{
	GSN_NWIF_INIT_PARAMS_T param;

	param.flags = (GSN_NWIF_FLAGS_T)(GSN_NWIF_FLG_ARP_ENABLE |	GSN_NWIF_FLG_DHCP_CLIENT_ENABLE |
				  GSN_NWIF_FLG_DNS_CLIENT_ENABLE | GSN_NWIF_FLG_ICMP_ENABLE | GSN_NWIF_FLG_IGMP_ENABLE);
	param.nwIfName = "station";
    param.pNwCtx = &pAppCtx->nwCtx;
	param.pL2Dev = (GSN_L2_DEV_T *)&pIfInfo->wddCtx;

    /*[TO DO]*/ 			/**< Power management object for power save */
	param.mtu = GSN_NW_ETHER_MTU;
	param.ipRecvFilter = App_NwRecvFilter;
	param.ipTskStackSize = APP_NWIF_IP_THREAD_STACK_SIZE;
	param.ipTskStack = &ipStack[0];
	param.ipTskPrio = APP_NWIF_IP_THREAD_PRIORITY;
	param.ipTskSysQualID = APP_CFG_SQ_IP_TASK_ID;
	param.ipTskSysQualTicks = APP_CFG_SQ_TICKS_FOR_IP_TASK;
	/* Using pre created packet pool. A new paket pool can be created using
	GsnNw_PktPoolCreate() and its handle can be given*/
	param.pIpPktPoolHndl = GsnNw_PktPoolHndlGet(&pAppCtx->nwCtx, GSN_NW_SBUF_PKT_POOL);


	param.arpCacheSize = APP_NWIF_IP_THREAD_ARP_CACHE_SIZE;
	param.arpCache = &arpCache[0];
	memset(&arpCache[0], 0, sizeof(arpCache));
	param.pStats = &gsnNwifStats;
	GsnNwIf_Init(&pIfInfo->nwifCtx, &param);
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
	App_UnLock();

}

extern UINT32 romFwImageFlashAddr;/* This holds the starting address of the App Fw*/

PRIVATE GSN_STATUS
App_WlanBootReq(APP_MAIN_CTX_T *pAppCtx)
{
	GSN_SYS_CTL_BOOT_REQ_PARAM_T bootReqParm;
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchMemInfo = App_RtcLatchMemInfoPtrGet();
	APP_RTC_SECNDRY_MEM_INFO_T * pAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();
    UINT8 *stdbyCtx;
    F_FILE *pFile;
    UINT32 rfCalibDataSize, fileSize;
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
	/*bootReqParm.ifTypes[1] = GSN_WIF_WLAN_NW_TYPE_AP;*/
	bootReqParm.fwFlashAddr = romFwImageFlashAddr;
	bootReqParm.stdbyCtxLen = pAppRtcSecMemInfo->macStdbyCtxLen;
	bootReqParm.pStdbyCtx = (UINT8 *)pAppRtcSecMemInfo->macStdbyCtx;
	stdbyCtx = (UINT8 *)bootReqParm.pStdbyCtx;
	
	if(bootReqParm.bootReason != GSN_WIF_SYS_BOOT_NORMAL_BOOT)
	{
		bootReqParm.stdbyCtxLen = 0 ;
		bootReqParm.pStdbyCtx = NULL;
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
        //AppDbg_Printf("fileSize = %d\r\n",fileSize);
        if(!rfCalibDataSize) 
         {
            /*[TO DO: handle failure]*/;
        }
        bootReqParm.rfCalibDataSize = rfCalibDataSize;

        
        /* Close the file*/
        f_close(pFile);
	}
	AppDbg_Printf("Issue BootReq %x %x %x %x\r\n", bootReqParm.stdbyCtxLen, stdbyCtx[0],
															stdbyCtx[1], stdbyCtx[2]);

	wlanRespTimeoutTmrHndl = GsnSoftTmr_Start(&wlanRespTimeoutTmr, GSN_SOFT_TMR_ONESHOT, 0,
														SEC_TO_SYSTIME(10),
														App_WlanRespTimeoutTmrCb, NULL);
	GsnSysCtl_BootReq_Patch(&pAppCtx->sysCtlCtx, &bootReqParm, App_WlanBootIndCb, pAppCtx);

	AppDbg_Printf("BootReq %d %d\r\n", bootReqParm.bootReason, bootReqParm.bootSubreason);

        return GSN_SUCCESS;
}

PRIVATE VOID
App_SysQualInit(APP_MAIN_CTX_T * pAppCtx)
{	
    GsnSq_Init();
	GsnSq_TaskMonitorRegister(APP_CFG_SQ_SOFT_TMR_TASK_ID, &pAppCtx->softTmrMsgHdlrCtx.tcb,
								APP_CFG_SQ_TICKS_FOR_SOFT_TMR_TASK);	
	GsnSq_TaskMonitorRegister(APP_CFG_SQ_HI_RECV_TASK_ID, &pAppCtx->hiCtx.recvThreadHndl,
								APP_CFG_SQ_TICKS_FOR_HI_RECV_TASK);
	GsnSq_TaskMonitorRegister(APP_CFG_SQ_WDD_MSG_HDLR_TASK_ID, &pAppCtx->wddMsgHdlrCtx.tcb,
								APP_CFG_SQ_TICKS_FOR_WDD_MSG_HDLR_TASK);
	GsnSq_TaskMonitorRegister(APP_CFG_SQ_IP_TASK_ID, &pAppCtx->if0.nwifCtx.ipHndl.nx_ip_thread,
								APP_CFG_SQ_TICKS_FOR_IP_TASK);
	GsnSq_TaskMonitorRegister(APP_CFG_SQ_DHCPV4_TASK_ID, &pAppCtx->if0.nwifCtx.dhcpCliHndl.nx_dhcp_thread,
								APP_CFG_SQ_TICKS_FOR_DHCPV4_TASK);
	GsnSq_TaskMonitorRegister(APP_CFG_SQ_HTTPD_TASK_ID, NULL,
								APP_CFG_SQ_TICKS_FOR_HTTPD_TASK);	
	GsnSq_TaskMonitorRegister(APP_CFG_SQ_MAIN_TASK_ID, &appMainCtxThread,
								APP_CFG_SQ_TICKS_FOR_MAIN_TASK);
}

