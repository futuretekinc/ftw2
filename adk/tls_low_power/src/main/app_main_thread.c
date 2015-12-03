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
 *Private variables
 ****************************************************************************/
/*App main context*/
APP_MAIN_CTX_T appCtx;

APP_MAIN_CTX_T *globalAppCtxPtr;

/* Define the APP main task  */
GSN_OSAL_THREAD_TCB_T appMainCtxThread;
UINT32 appMainCtxThreadStack[APP_MAIN_THREAD_STACK_SIZE/sizeof(UINT32)];
GSN_OSAL_QUEUE_T appMainThreadMsgQueue;
UINT32 appMainThreadMsgQueueBuf[ APP_CFG_APP_CTX_MAX_MSG_IN_MBOX *(sizeof(APP_MAINTASK_MSG_T)/4)];

UINT32 softTmrMsgHHdlrStack[ APP_CFG_SOFT_TMR_STACK_SIZE/sizeof(UINT32) ];
UINT32 softTmrMsgHHdlrBuff[ APP_CFG_SOFT_TMR_MAX_MSG_IN_MBOX ];

PRIVATE GSN_SOFT_TMR_T	sensorStablizeTmr;
PRIVATE GSN_SOFT_TMR_HANDLE_T sensorStablizeTmrHndl;

/* Boot indication synchronization mutex*/
GSN_OSAL_SEM_T sensorStablizeSem;

PRIVATE GSN_CLK_CTL_CTX_T appClkCtlCtx;


GSN_SOFT_TMR_T sysTickTmr;
GSN_SOFT_TMR_T *pSysTickTmrHndl;

extern UINT8 noFlashFetchFlag;

/*****************************************************************************
 *Private Function prototypes
 ****************************************************************************/
PRIVATE VOID
AppMainCtx_ThreadEntry(UINT32 arg);


PRIVATE VOID
App_DefaultIfInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);

PUBLIC GSN_STATUS
App_MsgProcess(    APP_MAIN_CTX_T *pAppCtx, UINT32 msgId );

PRIVATE VOID
App_Init(APP_MAIN_CTX_T * pAppCtx);

PRIVATE VOID
App_GpioInit();

PRIVATE VOID
App_SoftTimerInit(APP_MAIN_CTX_T *pAppCtx);

VOID
App_RtcDump(VOID);

extern VOID
AppL2L3_Init(APP_MAIN_CTX_T *pAppCtx);

VOID
App_ReStoreStdbyData(APP_MAIN_CTX_T *pAppCtx);

VOID
App_GotoStandby(APP_MAIN_CTX_T *pAppCtx);

VOID
AppS2w_RtcSRAMConfig(VOID);
/*****************************************************************************
 *Public and Private functions
 ****************************************************************************/
VOID
App_SysTickCb(VOID* context, GSN_SOFT_TMR_HANDLE_T  timerHandle)
{
    /* Generate software interrupt and call _tx_timer_interrupt in that ISR */
    NVIC_EnableIRQ(mbReceive7_IRQn);
    NVIC_SetPendingIRQ(mbReceive7_IRQn);

    return;
}

PUBLIC VOID
AppMainCtx_Init(VOID)
{
	UINT32 msgSizeInWords;

	globalAppCtxPtr = &appCtx;

	msgSizeInWords = GsnOsal_QueueMsgSizeInWords(sizeof(APP_MAINTASK_MSG_T));

	/**< Creating the Mailbox to receive messages */
	GsnOsal_QueueCreate( &appMainThreadMsgQueue, msgSizeInWords,
							( UINT8* )appMainThreadMsgQueueBuf,
							sizeof( appMainThreadMsgQueueBuf ));

    /**< Create the main Application Thread */
#ifdef GSN_DBG_STACK_PATTERN_FILL   /* Only for debug */
    MEMSET(appMainCtxThreadStack, 0x5a, sizeof(appMainCtxThreadStack));
#endif

    GsnOsal_ThreadCreate(AppMainCtx_ThreadEntry, &appCtx, &appMainCtxThread,
        "App Main Ctx", APP_CFG_MAIN_THREAD_PRIORITY, (UINT8 *)appMainCtxThreadStack,
        sizeof(appMainCtxThreadStack), GSN_OSAL_THREAD_INITIAL_READY);

}

PRIVATE VOID
App_CreateSensorStablizeLock(VOID)
{
#if 1
	/*Create syncronisation semaphore*/
	GsnOsal_SemCreate(&sensorStablizeSem, 0);
#endif
}

PRIVATE VOID
App_WaitOnSensorStablizeLock(VOID)
{
#if 1
	/* Wait on semaphore */
	GsnOsal_SemAcquire(&sensorStablizeSem, GSN_OSAL_WAIT_FOREVER);
	/* delete semaphore */
	GsnOsal_SemDelete(&sensorStablizeSem);
#endif
}

PRIVATE VOID
App_SensorStablizeUnLock(VOID)
{
#if 1
	GsnOsal_SemRelease(&sensorStablizeSem);
#endif
}

PUBLIC VOID
AppMainCtx_TaskNotify(INT32 msgId, UINT32 msgInfo)
{
	APP_MAINTASK_MSG_T msg;
	msg.msgId = msgId;
	msg.msgInfo = msgInfo;
    /**< Signal APP */
    GsnOsal_QueuePut(&appMainThreadMsgQueue, (UINT8 *)&msg);
}
VOID App_powerup_wlan()
{
    INT32 *pLdo1 = (INT32 *)0x41000268;

    RTC_EN_PWR_WLAN_CORE_CLEAR(RTC);
    *pLdo1 = 3;
    RTC_REG_RF_IO_CNTRL_SET(RTC,0); //may not be required
    RTC_ISO_CTL_WLAN_CORE_CLEAR(RTC);

}

VOID App_powerup_mem()
{
	RTC_EN_PWR_APP_SRAM_CLEAR(RTC);
	RTC_EN_PWR_SHARE_MEM_CLEAR(RTC);
	RTC_EN_PWR_WLAN_SRAM_CLEAR(RTC);

	RTC_ISO_CTL_APP_SRAM_CLEAR(RTC);
	RTC_ISO_CTL_SHARE_MEM_CLEAR(RTC);
    RTC_ISO_CTL_WLAN_SRAM_CLEAR(RTC);
}
VOID
App_SensorStabilizeTmrCb( VOID* context,
    				GSN_SOFT_TMR_HANDLE_T  timerHandle )
{
	App_SensorStablizeUnLock();
}

GSN_STATUS
App_PersistantTmrInit(APP_MAIN_CTX_T *pAppCtx)
{
                APP_RTC_LATCH_MEM_INFO_T *pRtcLatchMemInfo = App_RtcLatchMemInfoPtrGet();

    /**< Initialize the persistent timer module */
    GsnPersistTmr_Init(pRtcLatchMemInfo->persistTmrInfoNVRAM, pRtcLatchMemInfo->persistTmrInfoNvds,
        APP_NUM_OF_VAR_PERSIST_TMR, APP_NUM_OF_CONST_PERSIST_TMR,
        pAppCtx->persistTmrTbl);

    return GSN_SUCCESS;
}

VOID
App_SensorReadTmrCb(void *ptr, GSN_SOFT_TMR_HANDLE_T handle)
{
#ifndef POWER_MEASUREMENT_ENABLE
    GsnGpio_OutIndvidualSet(LED_GPIO_9);
#endif
}

GSN_STATUS
App_SensorReadTmrStart()
{

    GsnPersistTmr_Create( 0, GSN_TIMER_TYPE_PERSISTENT_CONSTANT, GSN_SOFT_TMR_MILLISECONDS_TO_TICKS(1000 * 5) ,
                                                                                App_SensorReadTmrCb, (void *)NULL, TRUE);
}


void HsRcCal()
{
    UINT32 calibOut;

    CLKCTL_CREQ_AIP_0_SET(CLKCTL, 3);
    CLKCTL_ACM3_CLK_SEL_SET(CLKCTL, 5);

    /* Set RC OSC default control */
    RTC_CX_CAL_ACCUM_ATTN_SET(RTC, 0);
    RTC_CX_CAL_ACCUM_INC_SET(RTC, 1);
    RTC_CX_CAL_FREQ_ACCU_SET(RTC, 0);
    RTC_CX_OSC_OPT_BIT_VAL_SET(RTC, 0);

    /* Start caliberation */
    RTC_CX_CAL_OVER_WRITE_F_CLEAR(RTC);
    RTC_CX_CAL_CLK_ENA_SET(RTC);
    RTC_CX_CAL_ENABLE_SET(RTC);

    while(!CLKCTL_CX_CAL_LOCK_DET_GET(CLKCTL));

    RTC_CX_CAL_CLK_ENA_CLEAR(RTC);
    RTC_CX_CAL_ENABLE_CLEAR(RTC);

    calibOut = CLKCTL_CX_CAL_REG_OUT_GET(CLKCTL);

    RTC_CX_CAL_OVER_WRITE_F_SET(RTC);
    RTC_CX_CAL_EXT_INPUT_SET(RTC, calibOut);

    CLKCTL_ACM3_CLK_SEL_SET(CLKCTL, 4);
    CLKCTL_CREQ_AIP_0_SET(CLKCTL, 0);
}

void App_RTCHwInit()
{
    RTC_RRH_FWWLAN_CTL_REQ_CLEAR(RTC);
    //RTC_RRH_ACM3AIRC_CTL_REQ_CLEAR(RTC);
    RTC_RRH_WCM3AIRC_CTL_REQ_CLEAR(RTC);
    *(int *)(0x410001F0) = 0;

    #pragma inline=forced
    //GsnRtc_GpioPullDownEn(0xF);

    RTC_SX_EN_TS_F_CLEAR(RTC);

    /* Disable Brownout */
    //RTC_SX_EN_BO_SET(RTC, 0);
    //RTC_SX_EN_BO_SET(RTC, 0);

}

void App_WlanPowerDown()
{
    INT32 *pLdo2 = (INT32 *)0x410002a8;
    INT32 *pLdo1 = (INT32 *)0x41000268;

	RTC_WCM3_CLK_ENABLE_CLEAR(RTC); 	 //Disable wlan clock

    RTC_ISO_CTL_WLAN_CORE_SET(RTC);      //isolate power
    RTC_REG_RF_IO_CNTRL_SET(RTC,0);

    //*(int *)0x41000218 = 1; //RTC_LDO_PG_VDD__0

    *pLdo2 = 3;
    *pLdo2 = 2;

    *pLdo1 = 3;
    *pLdo1 = 2;

    RTC_EN_PWR_WLAN_CORE_SET(RTC);
}

void App_DpSleepEnable()
{

    UINT32 *pIoMux = (UINT32 *)0x40160000, i, *pRen = (UINT32 *)0x40160200;
    UINT32 *gpioctl = (UINT32 *)0x40000008;

    IOMUX_BONDOPT_0_PD_EN_SET(IOMUX);
    IOMUX_FLASHSPI_SIO0_PD_EN_SET(IOMUX);
    IOMUX_FLASHSPI_SIO1_PD_EN_SET(IOMUX);
    IOMUX_FLASHSPI_SIO2_PD_EN_SET(IOMUX);
    IOMUX_FLASHSPI_SIO3_PD_EN_SET(IOMUX);
    IOMUX_FLASHSPI_SCLK_PD_EN_SET(IOMUX);
    IOMUX_FLASHSPI_CS_PD_EN_SET(IOMUX);
    IOMUX_BONDOPT_1_PD_EN_SET(IOMUX);
    IOMUX_BONDOPT_2_PD_EN_SET(IOMUX);
    IOMUX_PROG_MODE120P_PD_EN_SET(IOMUX);
    IOMUX_PROG_MODE68P_PD_EN_SET(IOMUX);

    /* Turn off uLdo */
    //RTC_SX_EN_U_LDO_F_CLEAR(RTC);
    //RTC_SX_EN_U_LDO_F_CLEAR(RTC);

    RTC_SX_LOAD_F_SET(RTC);
    RTC_SX_LOAD_F_CLEAR(RTC);

    RTC_TRNG_OSC_STOP_N_F_CLEAR(RTC);
    RTC_TRNG_OSC_STOP_N_F_CLEAR(RTC);

	RTC_ISO_CTL_APP_SRAM_SET(RTC);
	RTC_ISO_CTL_SHARE_MEM_SET(RTC);
	RTC_ISO_CTL_WLAN_SRAM_SET(RTC);

	RTC_EN_PWR_APP_SRAM_SET(RTC);
	RTC_EN_PWR_SHARE_MEM_SET(RTC);
	RTC_EN_PWR_WLAN_SRAM_SET(RTC);

    /* Disable crypto */
    RTC_ISO_CTL_CRYPTO_SET(RTC);
    CLKCTL_CRYPTO_CLK_EN_SET( CLKCTL, 0);
    RTC_EN_PWR_CRYPTO_SET(RTC);

    GsnIoMux_PullDownDisable(10);            //wps pin

    GSN_PWR_MGMT_CM3_SLEEP_DEEP_EN();

}
void clock_config()
{
    RTC_SM_SB_CLK_REQ_LP_XTAL_SET(RTC);
    RTC_SM_WK_CLK_REQ_LP_XTAL_SET(RTC);
    RTC_SM_RTC_CLK_SEL_SET(RTC,1);

    CLKCTL_CREQ_ACM3_SLEEP_SET(CLKCTL, 1);
    CLKCTL_CREQ_ACM3_ACTIVE_SET(CLKCTL, 1);
    CLKCTL_CREQ_ACM3_DSLEEP_SET(CLKCTL, 0);
    CLKCTL_RBUS_CLK_SEL_SET(CLKCTL, CLKCTL_RBUS_CORE_CTL_BITMASK);
    CLKCTL_ACM3_CLK_SEL_SET(CLKCTL, 4);
    RTC_SM_WK_CLK_REQ_HS_XTAL_CLEAR(RTC);
    RTC_SM_WK_CLK_REQ_HS_RC_CLEAR(RTC);
    RTC_SM_WU_CTL_SET(RTC, 0);
}
/* Define the test threads.  */

#ifdef ULTRA_LOW_POWER
VOID App_enter_ultra_low_pwr()
{
	App_WlanPowerDown();

    /* Turn off uLDO */
    RTC_SX_EN_U_LDO_F_CLEAR(RTC);
    RTC_SX_EN_U_LDO_F_CLEAR(RTC);

    /* isolate and power down RTC SRAM */
    RTC_ISO_CTL_RTC_SARM_SET(RTC, 0xF);
    RTC_EN_PWR_RTC_SARM_SET(RTC, 0xF);

    //RTC_SRAM_ISO_ENABLE_SET(RTC);

    /* Config alarm to wake up */
    {
        UINT32 alarmBitmap = 1 << GSN_RTC_ALARM_2;
        RTC_ALARM_IRQ_CLEAR_SET(RTC, alarmBitmap);
        RTC_ALARM_ENABLE_SET(RTC, (RTC_ALARM_ENABLE_GET(RTC) | alarmBitmap));
        RTC_ALARM_POLARITY_SET(RTC, (RTC_ALARM_POLARITY_GET(RTC) & (~alarmBitmap)));                //low to high
        RTC_ALARM_IRQ_MASK_SET(RTC, RTC_ALARM_IRQ_MASK_GET(RTC) | alarmBitmap);
    }

	/*Configure Standby and WakeUp clock sources*/
	RTC_SM_WK_CLK_REQ_HS_XTAL_SET(RTC);
	RTC_SM_WK_CLK_REQ_HS_RC_SET(RTC);

    /* Cfg alarm wakeup clocks */
    RTC_SM_ALARM_CLK_REQ_LP_XTAL_SET(RTC);
    RTC_SM_ALARM_CLK_REQ_HS_XTAL_SET(RTC);
    RTC_SM_ALARM_CLK_REQ_HS_RC_SET(RTC);

    /* Disable all clocks in standby */
    RTC_SM_SB_CLK_REQ_SET(RTC, 0);

	GSN_APP_REQ_SET(TRUE);

    /* Go to standby */
    RTC_SM_WU_SB_REQ_EN_SET(RTC);
    while(1);
}
#endif

PRIVATE VOID
AppMainCtx_ThreadEntry(UINT32 ctx)
{
    APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
    APP_MAINTASK_MSG_T msg = {0};
    APP_MAIN_CTX_T *pAppCtx;
    UINT32 bootReason,bootInfo;

    pAppCtx = (APP_MAIN_CTX_T *)ctx;

	AppS2w_RtcSRAMConfig();

    GsnClkCtl_Init(&appClkCtlCtx);

    bootReason = GSN_BOOT_REASON_GET();
    bootInfo = GSN_BOOT_INFO_GET();
    clock_config();
    if(bootReason == GSN_WIF_SYS_BOOT_FIRST_BOOT)
    {
       HsRcCal();
       App_RTCHwInit();
#ifdef ULTRA_LOW_POWER
       //App_WlanPowerDown();
       App_DpSleepEnable();
       App_enter_ultra_low_pwr();
#endif
    }

    {
        RTC_SM_ALARM_CLK_REQ_LP_XTAL_CLEAR(RTC);
        RTC_SM_ALARM_CLK_REQ_HS_XTAL_CLEAR(RTC);
        RTC_SM_ALARM_CLK_REQ_HS_RC_CLEAR(RTC);
    }

    //if(bootInfo != GSN_WIF_SYS_BOOTINFO_NORMALBOOT_ALARM)
    {
        App_WlanPowerDown();
        App_DpSleepEnable();
    }

    App_GpioInit();

#ifndef NO_SENSOR
	AppTls_SensorPowerUp();

	App_CreateSensorStablizeLock();
#endif

	/*Initialise Soft Timer */
	App_SoftTimerInit(pAppCtx);

#ifndef ULTRA_LOW_POWER
	App_PersistantTmrInit(pAppCtx);

	if(bootReason == GSN_WIF_SYS_BOOT_FIRST_BOOT)
	{
		App_SensorReadTmrStart();
	}
	else
	{
		GsnPersistTmr_Restore();
	}
#endif


	/*pAppRtcLtchInfo->linkChkItern++;*/
	if(0 == pAppRtcLtchInfo->numDataTfrItern || bootInfo == GSN_WIF_SYS_BOOTINFO_NORMALBOOT_ALARM)
	{
		/*Note: !! The time out calculation is, 100mSec - (App+Wlan codeload and boot time).
		Presently (App+Wlan codeload and boot time) = ~43mSec. Hence the time out 57MSec.
		Every time (App+Wlan codeload and boot time) changes, this time out has to be tuned*/
#ifndef NO_SENSOR

		sensorStablizeTmrHndl = GsnSoftTmr_Start(&sensorStablizeTmr, GSN_SOFT_TMR_ONESHOT, 0,
												GSN_SOFT_TMR_MILLISECONDS_TO_TICKS(57),
												App_SensorStabilizeTmrCb, NULL);
		App_WaitOnSensorStablizeLock();
#endif
		// in case of alarm wake up dont disturb the cycle
		if(bootInfo != GSN_WIF_SYS_BOOTINFO_NORMALBOOT_ALARM)
			pAppRtcLtchInfo->numDataTfrItern = 1;

		pAppCtx->preStdbyLvl = APP_PRE_STBY_LEVEL_2;
		GSN_PWR_MGMT_CM3_SLEEP_DEEP_DISABLE();

		App_powerup_mem();
		App_powerup_wlan();

		/*Load Remaining Part of the code*/
#ifndef POWER_MEASUREMENT_ENABLE
		GsnGpio_OutIndvidualSet(LED_GPIO_8);
#endif

		if(0 == noFlashFetchFlag)
		{
			App_CodePostFetch();
		}

#ifndef POWER_MEASUREMENT_ENABLE
		GsnGpio_OutClear(LED_GPIO_8);
#endif
		/**/

		AppL2L3_Init(pAppCtx);
	}
	else
	{
#ifndef NO_SENSOR
		sensorStablizeTmrHndl = GsnSoftTmr_Start(&sensorStablizeTmr, GSN_SOFT_TMR_ONESHOT, 0,
												GSN_SOFT_TMR_MILLISECONDS_TO_TICKS(100),
												App_SensorStabilizeTmrCb, NULL);
		App_WaitOnSensorStablizeLock();
		/**/
		AppTls_TempOrLightGet(&pAppRtcLtchInfo->TLSdata[2]);
#endif

		pAppRtcLtchInfo->numDataTfrItern = 0;
		/*store the values, go to standby*/
		pAppCtx->preStdbyLvl = APP_PRE_STBY_LEVEL_1;
		GSN_PWR_MGMT_CM3_SLEEP_DEEP_DISABLE();
		App_GotoStandby(pAppCtx);
	}

	/**< Handle events forever */
	while( TRUE )
	{
		/**< wait on message queue */
		GsnOsal_QueueGet( &appMainThreadMsgQueue, ( UINT8* )&msg,
							GSN_OSAL_WAIT_FOREVER );
		/**< Process the message */
		GsnSq_TaskMonitorStart(APP_CFG_SQ_MAIN_TASK_ID, msg.msgId);
		AppSm_MsgProcess(pAppCtx, msg);
		GsnSq_TaskMonitorStop(APP_CFG_SQ_MAIN_TASK_ID);
	}
}

VOID
AppS2w_RtcSRAMConfig(VOID)
{
	if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != GSN_BOOT_REASON_GET())
	{
		/*Power UP (Enable) RTC SRAM Bank 0 during First Boot*/
		RTC_EN_PWR_RTC_SARM_SET(RTC, 0x0);
		RTC_ISO_CTL_RTC_SARM_SET(RTC, 0x0);/*Not Required??*/
	}

	if(GSN_WIF_SYS_BOOT_NORMAL_BOOT == GSN_BOOT_REASON_GET())
	{
        RTC_SX_SWT2LDO_SET(RTC,0);
        SX_EN_ULDO_CLEAR(RTC);
        RTC_SRAM_ISO_ENABLE_CLEAR(RTC);
	}

}

VOID
App_Cm3ClkCfg(APP_MAIN_CTX_T *pAppCtx)
{
	GSN_CLK_CTL_CM3_CLK_CFG_T *pCm3ClkCfg  = &pAppCtx->cm3ClkCfg;
#ifdef GS2100M
	GsnRtc_ClkSrcSel(GSN_RTC_CLK_SRC_LP_RC);
#else
	GsnRtc_ClkSrcSel(GSN_RTC_CLK_SRC_LP_XTAL);
#endif
	pCm3ClkCfg->pClkCtlCtx = GsnClkCtl_CtxGet();
    pCm3ClkCfg->activeModeClkReq = GSN_CLK_CTL_CLK_SRC_HS_RC;
    pCm3ClkCfg->sleepModeClkReq = GSN_CLK_CTL_CLK_SRC_HS_RC;
    pCm3ClkCfg->deepSleepModeClkReq = 0;
    pCm3ClkCfg->control = 1; //core control
    pCm3ClkCfg->cm3ClkSel = GSN_CLK_SEL_HS_RC;
	GsnClkCtl_Cm3ClkCfg(pCm3ClkCfg);
	//GsnClkCtl_Cm3ClkSwitch(&cm3ClkCfg, GSN_CLK_SEL_HS_XTAL);
	if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != GSN_BOOT_REASON_GET())
	{
		GsnClkCtl_HsRcCal(pCm3ClkCfg);
	}
}

PRIVATE VOID
App_GpioInit()
{
    /* Init leds and adc gpio here */
#ifdef DOOR_BELL
	GsnIoMux_Sel(31, GSN_IOMUX_GPIO_31_AGPIO_31); // DIN
	GsnGpio_Init(0x80300300,0x7fcffcff); // direction'0'out, 1' input

#else
	GsnGpio_Init(0x00300300,0xffcffcff);
#endif
	//GsnGpio_OutIndvidualSet(LED_GPIO_9);
}

#if 1
BOOL
App_SoftTmrMmsgHandlr(void *pCtx, void *pMsg)
{

	//GsnSq_TaskMonitorStart(APP_CFG_SQ_SOFT_TMR_TASK_ID, *(( INT32* )pMsg ));
	GsnSoftTmr_Run( pCtx, pMsg );

	//GsnSq_TaskMonitorStop(APP_CFG_SQ_SOFT_TMR_TASK_ID);
	return 0;
}

PRIVATE VOID
App_SoftTimerInit(APP_MAIN_CTX_T *pAppCtx)
{
	ULONG64 systemTimeOffset = 0;
	GSN_MSG_HANDLER_CFG_T cfg1 = {"Soft Tmr Msg Handler1", softTmrMsgHHdlrStack,
					sizeof( softTmrMsgHHdlrStack ), 1, ( UINT8* )softTmrMsgHHdlrBuff,
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
#endif

VOID
App_RtcDump(VOID)
{
	UINT8 i;
	APP_RTC_LATCH_MEM_INFO_T *pRtcLatchMemInfo = App_RtcLatchMemInfoPtrGet();
	APP_RTC_SECNDRY_MEM_INFO_T *pRtcSecMemInfo = App_RtcSecMemInfoPtrGet();
	GSN_SYS_RESET_INFO_T *pResetInfo= &pRtcLatchMemInfo->sysResetInfo;

	AppDbg_Printf("\r\n");

	AppDbg_Printf("Boot Reason :    %d\r\n", GSN_BOOT_REASON_GET());
	AppDbg_Printf("Boot Info :      %d\r\n", GSN_BOOT_INFO_GET());
	AppDbg_Printf("Reset Type:      %d\r\n", pResetInfo->app.resetType);
	AppDbg_Printf("Reset Reason :   %d\r\n", pResetInfo->app.resetReason);
	AppDbg_Printf("Reset Info Size: %d\r\n", pResetInfo->app.resetInfoSize);
	AppDbg_Printf("Reset Addl Info: 0x%x\r\n", pResetInfo->app.resetAddlInfo);
	AppDbg_Printf("ResetInfo:\r\n");
	for(i = 0; i < 16; i++)
	{
	AppDbg_Printf("\t0x%08x\r\n", pResetInfo->app.resetInfo[i]);
	}
	AppDbg_Printf("\r\n");
}

VOID
App_StoreStdbyData(APP_MAIN_CTX_T *pAppCtx, GSN_SYS_CTL_STDBY_RESP_T * pStdbyResp)
{
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();

	APP_RTC_SECNDRY_MEM_INFO_T *pAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();
	/*Store WLAN data */
	if(NULL != pStdbyResp)
	{
		pAppRtcSecMemInfo->macStdbyCtxLen = pStdbyResp->totalSize;
		memcpy((INT8 *)pAppRtcSecMemInfo->macStdbyCtx, (const INT8 *)pStdbyResp->ctxData,
				pStdbyResp->totalSize);
	}

	/*Store IP Configuration*/

	if(APP_PRE_STBY_LEVEL_2 == pAppCtx->preStdbyLvl)
	{
		GsnNwIf_IpConfigGet(&pAppCtx->if0.nwifCtx, &pAppRtcLtchInfo->ipConfig);

		nx_arp_table_get(&pAppCtx->if0.nwifCtx.ipHndl,
								(VOID *)&pAppRtcLtchInfo->arpTablebuf[0],
								sizeof(pAppRtcLtchInfo->arpTablebuf),
								&pAppRtcLtchInfo->arpRecCount);
		GsnNwIf_dhcpClientCreateRecord(&pAppCtx->if0.nwifCtx,&pAppRtcSecMemInfo->dhcpClientRecord);
		memcpy((INT8 *)&pAppRtcSecMemInfo->networkConfig, (INT8 *)&pAppCtx->config.networkConfig, sizeof(pAppRtcSecMemInfo->networkConfig));
	}

}

VOID
App_GotoStandby(APP_MAIN_CTX_T *pAppCtx)
{
	ULONG64 duration, nextWakeup, currTime, sleepTimeInMsec;
	GN_SYS_CTL_STDBY_REQ_PARAM_T stdbyReqParam;
	INT8 *pStdbyRespBuf = NULL;
	UINT32 stdbyRespBufLen;
	GSN_SYS_CTL_STDBY_RESP_T *pStdbyResp;
	APP_RTC_SECNDRY_MEM_INFO_T *pAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();

	if(APP_PRE_STBY_LEVEL_2 == pAppCtx->preStdbyLvl)
	{

		pStdbyRespBuf = (INT8 *)MALLOC(MAX_WLAN_STANDBY_DATA_SIZE);
		if(NULL == pStdbyRespBuf)
		{
			while(1);
		}
		MEMSET((INT8 *)&stdbyReqParam, 0, sizeof(stdbyReqParam));
		stdbyRespBufLen = MAX_WLAN_STANDBY_DATA_SIZE;

		stdbyReqParam.wakeUpForWlanEvents = 0;
		stdbyReqParam.restoreIfBitMap = 0x1;
		stdbyReqParam.waitPeriod[0] = 0xFFFFFFFF;

		GsnSysCtl_StandByReq(&pAppCtx->sysCtlCtx, &stdbyReqParam, pStdbyRespBuf, stdbyRespBufLen);
	}
	/*Store Standby data */
	App_StoreStdbyData(pAppCtx, (GSN_SYS_CTL_STDBY_RESP_T *)pStdbyRespBuf);



    /*Issue the stby request
     */

	duration = GsnPersistTmr_RemainingTimeGet(0);
	//duration = GSN_SOFT_TMR_MILLISECONDS_TO_TICKS(1000 * 5);
	sleepTimeInMsec = (UINT32)GSN_SOFT_TMR_TICKS_TO_MILLISECONDS(duration);
	pAppRtcSecMemInfo->sleepTime += (UINT32)sleepTimeInMsec;

	{
		RTC_SRAM_ISO_ENABLE_SET(RTC);
		SX_EN_ULDO_SET(RTC);
		RTC_SX_SWT2LDO_SET(RTC,1);
	}
	GsnPersistTmr_Store();
	/* Config alarm to wake up */
    {
        UINT32 alarmBitmap = (1 << GSN_RTC_ALARM_2);
        RTC_ALARM_IRQ_CLEAR_SET(RTC, alarmBitmap);
        RTC_ALARM_ENABLE_SET(RTC, (RTC_ALARM_ENABLE_GET(RTC) | alarmBitmap));
        RTC_ALARM_POLARITY_SET(RTC, (RTC_ALARM_POLARITY_GET(RTC) & (~alarmBitmap)));                //low to high
        RTC_ALARM_IRQ_MASK_SET(RTC, RTC_ALARM_IRQ_MASK_GET(RTC) | alarmBitmap);
    }
	/*Configure Standby and WakeUp clock sources*/
    RTC_SM_SB_CLK_REQ_LP_XTAL_SET(RTC);
    RTC_SM_WK_CLK_REQ_HS_XTAL_SET(RTC);
    RTC_SM_WK_CLK_REQ_HS_RC_SET(RTC);

    /* Cfg alarm wakeup clocks */
    RTC_SM_ALARM_CLK_REQ_LP_XTAL_SET(RTC);
    RTC_SM_ALARM_CLK_REQ_HS_XTAL_SET(RTC);
    RTC_SM_ALARM_CLK_REQ_HS_RC_SET(RTC);

    App_WlanPowerDown();
    GSN_APP_REQ_SET(TRUE);
    GsnPwrMgmt_EnterStby(duration);
    {
       volatile UINT32 loop=1;
       while(loop);
    }
}


VOID
App_ReStoreStdbyData(APP_MAIN_CTX_T *pAppCtx)
{
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
	APP_RTC_SECNDRY_MEM_INFO_T *pAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();

	APP_CLIENT_CONFIG_T *pCliCfg;

	memcpy((INT8 *)&pAppCtx->config.networkConfig, (INT8 *)&pAppRtcSecMemInfo->networkConfig, sizeof(pAppRtcSecMemInfo->networkConfig));

	pCliCfg = &pAppCtx->config.networkConfig.clientConfig;

	/*Restore IP Configuration*/
	pCliCfg->ipAddress = ntohl(pAppRtcLtchInfo->ipConfig.ipv4.ipAddr);
	pCliCfg->subnetmask = ntohl(pAppRtcLtchInfo->ipConfig.ipv4.subnetMask);
	pCliCfg->gateway = ntohl(pAppRtcLtchInfo->ipConfig.ipv4.gatewayIpAddr);
	pCliCfg->dnsServer = ntohl(pAppRtcLtchInfo->ipConfig.ipv4.dnsPriSrvrIp);

	pCliCfg->dhcpFlag = FALSE;
}
