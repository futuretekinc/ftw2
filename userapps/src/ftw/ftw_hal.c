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
#include "ftw_hal.h"
#include "ftw_hal_net.h"
#include "ftw_serial.h"
#include "ftw_uart.h"

extern FTW_LINK_STATE_T s2wLinkState ;
extern GSN_SOFT_TMR_T *pSysTickTmrHndl;
extern GSN_SOFT_TMR_T sysTickTmr;
extern FTW_PROFILE_PARAMS_T profile_params;


GSN_NOTIFICATION_FUNC_T s2wappMainTaskNotifier;
APP_MAIN_CTX_T *s2wappMainTaskCtxt;
PRIVATE GSN_OSAL_SEM_T stDisassocSemaphore;
GSN_OSAL_SEM_T s2wL2L3ConnectSemaphore;
GSN_SOFT_TMR_T  appDeepSleepTimer;
GSN_OSAL_SEM_T stbyDelaySemaphore;



VOID 
App_SysTickCb(VOID* context, GSN_SOFT_TMR_HANDLE_T  timerHandle);
VOID
App_WaitOnLock(VOID);
VOID
App_DefaultIfInit(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);
VOID
App_InterfaceStart(APP_MAIN_CTX_T *pAppCtx, APP_IF_INFO_T *pIfInfo);
VOID
GsnHeIf_TrangGetSeed( UINT8* pBuf );




PUBLIC VOID
AppS2wHal_Register(GSN_NOTIFICATION_FUNC_T notifier, VOID *context)
{
    GsnOsal_SemCreate (&stbyDelaySemaphore, 0);
    
    s2wappMainTaskNotifier = notifier;
    s2wappMainTaskCtxt = context;
    
    //GsnWdd_DisassocIndCbReg(&s2wappMainTaskCtxt->if0.wddCtx, s2wDisassocCb, context);
    // GsnWdd_BeaconMissCbReg(&s2wappMainTaskCtxt->if0.wddCtx, s2wDisassocSyncLossCb, context);
    //GsnWdd_BeaconMissThresholdSet(&s2wappMainTaskCtxt->if0.wddCtx,0,FTW_DEFAULT_SYNCLOSS_INTERVAL);
    
    
    
}

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
    UINT32 bootReason;
    /* create all semaphore needed for s2w app
    */
    GsnOsal_SemCreate (&s2wSyncSemID, 1);
    AppS2wHal_netInit();
    
#ifdef FTW_RF_TEST
	GsnOsal_SemCreate  ( &s2wWlanOpSyncSem, 0 );
#endif	
#if defined(FTW_WEB_PROV) || defined(FTW_WEB_SERVER)
	GsnOsal_SemCreate(&s2wappMainTaskCtxt->webServerSync, 0 );
#endif
    GsnOsal_SemCreate (&(s2wappMainTaskCtxt->s2wDpSleepWakeUpSem), 0);
	GsnOsal_SemCreate( &(s2wappMainTaskCtxt->s2wTcpClientCntSyncSem), 1 );
    // select the serial port
    
    /* Set the serial port device ID */
    APP_FTW_SET_SERIAL_DEVICE_ID(FTW_PORT_UART);
    
	f_enterFS();
    /* initialize s2w
    */
    AppS2w_Init();
	
    //#if (!( defined FTW_ISOTX_SUPPORT  || defined FTW_15DOT4_SUPPORT ))
	if ((FTW_WLANDATA_MODE_ISOTX  != s2wCurrent.mode) || (FTW_WLANDATA_MODE_15_4 != s2wCurrent.mode))
	{
#ifdef FTW_PERSISTENT_TMR_SUPPORT    
        AppS2w_PersistantTmrCfg();
        AppS2w_PersistTmrInit( &appCtx);
#endif
        //#endif
	}
    
#ifdef FTW_EXT_FLASH_FS_SUPPORT
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
#ifdef FTW_IP2WIFI_SUPPORT
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
    GsnWdd_DisassocIndCbReg(&s2wappMainTaskCtxt->if0.wddCtx, s2wDisassocCb, s2wappMainTaskCtxt);
    GsnWdd_BeaconMissCbReg(&s2wappMainTaskCtxt->if0.wddCtx, s2wDisassocSyncLossCb, s2wappMainTaskCtxt);
    bootReason = GSN_BOOT_REASON_GET();
    if(GSN_WIF_SYS_BOOT_NORMAL_BOOT != bootReason)
        GsnWdd_BeaconMissThresholdSet(&s2wappMainTaskCtxt->if0.wddCtx,0,FTW_DEFAULT_SYNCLOSS_INTERVAL);
    AppS2wProcess_AutoStart();
    
    FTW_SERIAL_init();
}

VOID FTW_HAL_printBanner(VOID)
{
    UINT32 bootReason, bootInfo, bootCode, flag = 0, i,asyncMsgID=0, appflag = 0;
	GSN_SYS_RESET_INFO_T *pResetInfo = (GSN_SYS_RESET_INFO_T *)GSN_SYS_RESET_INFO_LOCATION_GET();
    
	/*Check Boot Reason*/
#ifndef FTW_ASYNC_MSG
    (void)asyncMsgID;/* Suppress the warning*/
#endif
    
 	bootReason = GSN_BOOT_REASON_GET();
 	bootInfo = GSN_BOOT_INFO_GET();
 	if ((FTW_WLANDATA_MODE_ISOTX  != s2wCurrent.mode) || (FTW_WLANDATA_MODE_15_4 != s2wCurrent.mode))
 	{	
#ifdef FTW_PERSISTENT_TMR_SUPPORT
        if(bootReason != GSN_WIF_SYS_BOOT_FIRST_BOOT)
        {
            GsnPersistTmr_Restore();
        }
#endif
	}
 	switch (bootReason)
 	{
 	case GSN_WIF_SYS_BOOT_FIRST_BOOT:
        bootCode = FTW_INITIAL_BOOT_MSG;
        asyncMsgID = FTW_ASYNC_INITIAL_BOOT_MSG;
 		break;
 	case GSN_WIF_SYS_BOOT_NORMAL_BOOT:
 		if(GSN_WIF_SYS_BOOTINFO_NORMALBOOT_RTC == bootInfo)
 		{
            bootCode = FTW_STBY_TMR_EVT;
            asyncMsgID =FTW_ASYNC_STBY_TMR_EVT;
 		}
 		else if(GSN_WIF_SYS_BOOTINFO_NORMALBOOT_ALARM == bootInfo)
 		{
            bootCode = FTW_STBY_ALM_EVT;
            asyncMsgID =FTW_ASYNC_STBY_ALM_EVT;
 		}
 		else
        {
            bootCode = FTW_BOOT_UNKNOWN;
            asyncMsgID = FTW_ASYNC_BOOT_UNKNOWN;
        }
 		break;
 	case GSN_WIF_SYS_BOOT_FW_UPDATE_BOOT:
        bootCode = FTW_BOOT_RST_EXT_FLASH_FWUP_SUCCESS;
        asyncMsgID = FTW_ASYNC_BOOT_RST_EXT_FLASH_FWUP_SUCCESS;
 		break;
 	case GSN_WIF_SYS_BOOT_WATCHDOG_BOOT:
 		if(GSN_WIF_SYS_BOOTINFO_WDOG_RESET_APP == bootInfo)
 		{
            bootCode = FTW_BOOT_RST_APP_WD;
            asyncMsgID = FTW_ASYNC_BOOT_RST_APP_WD;
 		}
 		else if(GSN_WIF_SYS_BOOTINFO_WDOG_RESET_WLAN == bootInfo)
 		{
 			flag = TRUE;
            bootCode = FTW_BOOT_RST_WLAN_WD;
            asyncMsgID = FTW_ASYNC_BOOT_RST_WLAN_WD;
 		}
 		else
 		{
            bootCode = FTW_BOOT_UNKNOWN;
            asyncMsgID = FTW_ASYNC_BOOT_UNKNOWN;
 		}
 		break;
 	case GSN_WIF_SYS_BOOT_SW_RESET_BOOT:
 		if (GSN_WIF_SYS_BOOTINFO_SWRESET_APP == bootInfo)
 		{
			appflag = TRUE;
            bootCode = FTW_BOOT_RST_APP_SW;
            asyncMsgID = FTW_ASYNC_BOOT_RST_APP_SW;
 		}
 		else //if(GSN_WIF_SYS_BOOTINFO_SWRESET_WLAN == bootInfo)
		{
 			bootCode = FTW_BOOT_RST_WLAN_SW;
 			asyncMsgID = FTW_ASYNC_BOOT_RST_WLAN_SW;
 			flag = TRUE;
		}
 		break;
 	case GSN_WIF_SYS_BOOT_EXCEPTION_BOOT:
		if(		(GSN_WIF_SYS_BOOTINFO_EXCP_APP_ABORT == bootInfo) ||
           (GSN_WIF_SYS_BOOTINFO_EXCP_APP_ASSERT == bootInfo))
		{
			appflag = TRUE;
			bootCode = FTW_BOOT_RST_APP_SW;
			asyncMsgID = FTW_ASYNC_BOOT_RST_APP_SW;
		}
		else if((GSN_WIF_SYS_BOOTINFO_EXCP_WLAN_ABORT == bootInfo) ||
				(GSN_WIF_SYS_BOOTINFO_EXCP_WLAN_ASSERT == bootInfo))
		{
			bootCode = FTW_BOOT_RST_WLAN_EXPT;
			asyncMsgID = FTW_ASYNC_BOOT_RST_WLAN_EXPT;
			flag = TRUE;
		}
		else
		{
			bootCode = FTW_BOOT_UNKNOWN;
			asyncMsgID = FTW_ASYNC_BOOT_UNKNOWN;
		}
		break;
 	case GSN_WIF_SYS_BOOT_EXT_RESET_BOOT:
 		bootCode = FTW_BOOT_EXT_RST;
 		asyncMsgID = FTW_ASYNC_BOOT_EXT_RST;
 		break;
 	case GSN_WIF_SYS_BOOT_FACTORY_FW_BOOT:
 		bootCode = FTW_BOOT_RST_EXT_FLASH_FWUP_SUCCESS;
 		asyncMsgID = FTW_ASYNC_BOOT_RST_EXT_FLASH_FWUP_SUCCESS;
 		break;
 	case GSN_WIF_SYS_BOOT_DBG_BOOT:
 		bootCode = FTW_BOOT_RST_JTAG;
 		asyncMsgID = FTW_ASYNC_BOOT_RST_JTAG;
 		break;
 	case GSN_WIF_SYS_BOOT_CRYPTO_SW_BOOT:
 		bootCode = FTW_BOOT_CRYPTO;
 		asyncMsgID = FTW_ASYNC_BOOT_CRYPTO;
 		break;
 	case GSN_WIF_SYS_BOOT_CORE_BROWNOUT_BOOT:
 		bootCode = FTW_BOOT_RST_BROWNOUT;
 		asyncMsgID = FTW_ASYNC_BOOT_RST_BROWNOUT;
 		break;
 	default:
 		bootCode = FTW_BOOT_UNKNOWN;
 		asyncMsgID = FTW_ASYNC_BOOT_UNKNOWN;
 		break;
	}
#ifdef FTW_ASYNC_MSG
	if(s2wCurrent.asyncMsgFormat && asyncMsgID != 0)
	{
		S2w_AsyncMsgGpioInit();
		AppS2wProcess_AsyncStatusNotify(asyncMsgID, 0);
	}
	else
#endif
	{
 	    //S2w_Printf(S2WBootPrint_List[bootCode]);
 	    AppS2wProcess_StatusNotify(bootCode, FTW_SUCCESS);
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
    return FTW_SUCCESS;
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
UINT8 FTW_PS_modeSet(UINT8 bMode)
{
    if(bMode)
    {
        return GsnWdd_Ioctl(&s2wappMainTaskCtxt->if0.wddCtx,GSN_WDD_IOCTL_RX_PS_MODE_ON,&bMode);
    }
    else
    {
        return GsnWdd_Ioctl(&s2wappMainTaskCtxt->if0.wddCtx,GSN_WDD_IOCTL_RX_PS_MODE_OFF,&bMode);
    }
}

UINT8 
AppS2wHal_IeeePSConfig(UINT8 bMode)
{
	if(bMode)
	{
	    return GsnWdd_Ioctl(&s2wappMainTaskCtxt->if0.wddCtx,GSN_WDD_IOCTL_RX_IEEEPS_MODE_ON,&bMode);
	}
	else
	{
	    return GsnWdd_Ioctl(&s2wappMainTaskCtxt->if0.wddCtx,GSN_WDD_IOCTL_RX_IEEEPS_MODE_OFF,&bMode);
	}
}
UINT8 
FTW_PS_modeSave(void)
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
    return  FTW_SUCCESS;
}



PUBLIC VOID
AppS2w_GpioWkUpDisable()
{
#ifdef FTW_UART_ENABLE
	GsnGpio_PEIntDisable_Patch(0x00000001);
	GsnGpio_PEIntClear(0x00000001);
	GsnIoMux_Sel(0, GSN_IOMUX_GPIO_0_AUART0_RXD);
#else
    
	GsnGpio_PEIntDisable_Patch(APP_FTW_SPI_WAKEUP_GPIO_BITMAP);
	GsnGpio_PEIntClear(APP_FTW_SPI_WAKEUP_GPIO_BITMAP);
#endif
}
PRIVATE VOID
FTW_SYS_deepSleepTimerCB( VOID* context, UINT32 TimerHandle  )
{
	AppS2w_GpioWkUpDisable();
	if(s2wappMainTaskCtxt->dpSleep)
	{
		AppS2w_ExitDpSleep();
    }
}



PRIVATE VOID 
FTW_SYS_alarmCB(VOID *pCtx)
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
FTW_SYS_gpioCB(UINT8 gpioNum, void *pCtx)
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
	FTW_SERIAL_PORT_ID_T serialId = APP_FTW_GET_SERIAL_DEVICE_ID();
    
#ifdef FTW_UART_ENABLE
    GSN_UART_CONFIG_T	  tUartConfig;
#endif

    s2wappMainTaskCtxt->dpSleep = 0;
    GSN_PWR_MGMT_CM3_SLEEP_DEEP_DISABLE();
	GsnSoftTmr_Stop( &appDeepSleepTimer);
	GsnRtc_AlarmDeRegisterCb(GSN_RTC_ALARM_2);
	GsnRtc_AlarmDeRegisterCb(GSN_RTC_ALARM_3);
    GsnHeIf_DriverInit((UINT32 *)GSN_SYS_CRYPTO_SEED_LOCATION_GET());
#ifdef FTW_UART_ENABLE
    if(FTW_PORT_SPI != serialId)
    {
        FTW_UART_CONFIG xConfig;
        
		FTW_UART_getConfig(FTW_UART0, &xConfig);
        FTW_UART_open(FTW_UART0, &xConfig);
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
* @retval FTW_SUCCESS.
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
AppS2wHal_PsDpSleepStart(UINT32 timeout, FTW_ALARM_INFO_T* data, UINT8 pwrMeasure)
{
    s2wappMainTaskCtxt->dpSleep = 1;
    
	FTW_SERIAL_PORT_ID_T serialId = APP_FTW_GET_SERIAL_DEVICE_ID();
    
    GsnHeIf_DriverSuspend();
    
#ifdef FTW_UART_ENABLE
    FTW_UART_close(FTW_UART0);
    GsnIoMux_Sel(0, GSN_IOMUX_GPIO_0_AGPIO_0);
	GsnGpio_Init( 0x00000001, 0x00000001 );  
	GsnGpio_IntCbRegister(0 ,FTW_SYS_gpioCB, NULL);
	GsnGpio_PEIntEnable(0x00000001);
#endif

    /* start the timer */
    if(timeout)
    {
        GsnSoftTmr_Start( &appDeepSleepTimer, GSN_SOFT_TMR_ONESHOT,
                         0, ((timeout * TIMER_INTERRUPT_5_MS)/5),
                         ( GSN_SOFT_TMR_CBR_T )FTW_SYS_deepSleepTimerCB, NULL );
    }
    
    
    if(data->alarm1Valid)
    {
        GsnRtc_AlarmConfig(GSN_RTC_ALARM_2, data->alarm1Pol, TRUE);
        GsnRtc_AlarmRegisterCb(GSN_RTC_ALARM_2, FTW_SYS_alarmCB, NULL);
    }
    if(data->alarm2Valid)
    {
        GsnRtc_AlarmConfig(GSN_RTC_ALARM_3, data->alarm2Pol, TRUE);
        GsnRtc_AlarmRegisterCb(GSN_RTC_ALARM_3, FTW_SYS_alarmCB, NULL);
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
    return FTW_SUCCESS;	
}



PRIVATE VOID
AppS2wHal_StbyDelayTimerCb ( VOID* pu32Ptr, UINT32 TimerHandle )
{
    GsnOsal_SemRelease ( &stbyDelaySemaphore);
}


PUBLIC UINT8
AppS2wHal_PsStbyRequest(ULONG64 sleepTime,UINT32 delayTime,
                        FTW_ALARM_INFO_T* data)
{
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
	APP_RTC_SECNDRY_MEM_INFO_T *pAppRtcSecMemInfo = App_RtcSecMemInfoPtrGet();
	FTW_PROFILE_PARAMS_T *
        proParam =  S2w_ProfileParamInRTCPtrGet();
	FTW_FLASH_PARAMS_T *
        profiles =  S2w_FlashParamInRTCPtrGet();
	ULONG64 duration;
	GN_SYS_CTL_STDBY_REQ_PARAM_T stdbyReqParam;
	INT8 *pStdbyRespBuf;
	UINT32 stdbyRespBufLen; 
	GSN_SYS_CTL_STDBY_RESP_T *pStdbyResp;
    GSN_SOFT_TMR_HANDLE_T stbydelayTimerId = NULL;
    GSN_SOFT_TMR_T stbyDelayTimer;
    
	if((s2wCurrent.ncmAutoMgr) && (s2wLinkState == FTW_LINK_STATE_CONNECTED))
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
            return FTW_FAILURE;
        }
        GsnOsal_SemAcquire ( &stbyDelaySemaphore,
                            GSN_OSAL_WAIT_FOREVER );
    }
    {
        // for stby wakeup update the profile data structure in RTC
        memcpy(proParam,&profile_params,sizeof(FTW_PROFILE_PARAMS_T));
        memcpy(profiles,s2wFlashParams,sizeof(FTW_FLASH_PARAMS_T));
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
#ifdef FTW_PERSISTENT_TMR_SUPPORT     
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
    
    return FTW_SUCCESS;
}

VOID
AppS2wHal_PsHibernateRequest(FTW_ALARM_INFO_T *alarm)
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
