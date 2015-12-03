
#include "rtos/tx_api.h"
#include "rtos/tx_initialize.h"
#include "gsn_includes.h"
#include "app_defines.h"
#include "gsn_ncm.h"
#include "main/app_main_ctx.h"
#include "config/app_resource_config.h"
#include "app_events.h"
#include "app_rtc_mem.h"
#include "hal/s2w_config.h"

#include "core/nvic/gsn_nvic_fpt.h"

VOID
APP_BootProcess();

GSN_SYS_STATS_T *statPtr;/*Used during debugging through debigger*/
/* Define main entry point.  */

INT32
App_Main()
{
  
#if   defined(S2W_FS_SPI_HI_ENABLE_1) || defined(S2W_FS_SPI_HI_ENABLE)
  
  *((UINT32 *)(0x20004088)) = (UINT32)__GsnSpi0FS_Isr;

  *((UINT32 *)(0x2000408c)) = (UINT32)__GsnSpi0FS_Isr;

  *((UINT32 *)(0x20004090)) = (UINT32)__GsnSpi0FS_Isr;

  *((UINT32 *)(0x20004094)) = (UINT32)__GsnSpi0FS_Isr;

  *((UINT32 *)(0x20004098)) = (UINT32)__GsnSpi0FS_Isr;
#endif
  
#ifdef  S2W_WPS_CERTIFICATION
extern int eap_peer_wsc_register_patch(void);
    *((UINT32 *)(0x2000533c)) = (UINT32)eap_peer_wsc_register_patch;
#endif
    
	APP_BootProcess();
    /* Create APP main task */
    AppMainCtx_Init();

    return 0;
}

VOID App_powerup_wlan()
{
    GsnRtc_Ldo1Enable();
    RTC_REG_RF_IO_CNTRL_SET(RTC,0); //may not be required
    GsnRtc_WlanCoreEn();
}

VOID
APP_BootProcess()
{
	UINT32 bootReason, bootInfo;
	
	RTC_CX_CLK_DIG4_ENA_CLEAR(RTC);      // PLL stuck issue??
    RTC_CX_CLK_SRC_SEL_SET(RTC, 1);
    RTC_CX_CLK_SRC_SEL_SET(RTC, 2);
	if(GsnRtc_IsPorEvent())
	{
		/* Enable RTC SRAM Bank 0*/
		GsnRtc_RtcSramBankEn(GSN_RTC_SRAM_BANK0);

		/*set time between DCDC assertion and reset release to the core. 1.25ms */
		GsnRtc_DcDcTmrValSet(APP_CFG_DCDC_TMR_VAL);

		/* Enable pulldown for rtc gpio */
		GsnRtc_GpioPullDownEn(0xF); 	

		/* Enable BrownOut circuit*/
		GsnRtc_BrownOutEn(GSN_BROWNOUT_THRESHOLD_1_4V);

		/* Enable BrownOut reset */
		RTC_RRH_CBO_CTL_REQ_SET(RTC);
		
		APP_RtcInit(1);

		/* Initial Boot */
		GSN_BOOTINFO_SET(GSN_WIF_SYS_BOOT_FIRST_BOOT, 0);

		GsnRtc_PorEventClr();
	}
	else
	{
		if (GSN_IS_RTC_RSVD_INFO_VALID())
		{
			if((GsnRtc_IsTmrWakeUp()) && (TRUE == GSN_APP_REQ_GET()))
			{
				GSN_BOOTINFO_SET(GSN_WIF_SYS_BOOT_NORMAL_BOOT, GSN_WIF_SYS_BOOTINFO_NORMALBOOT_RTC);
				GSN_APP_REQ_SET(FALSE);
				GsnRtc_StbWakeUpTmrClr();
				GsnRtc_CboRstClr();
			}
			else if((GsnRtc_IsAlarmWakeUp()) && (TRUE == GSN_APP_REQ_GET()))
			{
				APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
				if(pAppRtcLtchInfo->hibernate)
				{
					App_powerup_wlan();
					pAppRtcLtchInfo->hibernate = FALSE;
					/* Enable RTC SRAM Bank 0*/
					GsnRtc_RtcSramBankEn(GSN_RTC_SRAM_BANK0);
					/* Enable BrownOut circuit*/
					GsnRtc_BrownOutEn(GSN_BROWNOUT_THRESHOLD_1_4V);
					APP_RtcInit(1);
					GSN_BOOTINFO_SET(GSN_WIF_SYS_BOOT_FIRST_BOOT, 0);
				}
				else
				{
					GSN_BOOTINFO_SET(GSN_WIF_SYS_BOOT_NORMAL_BOOT,GSN_WIF_SYS_BOOTINFO_NORMALBOOT_ALARM);
				}
				GSN_APP_REQ_SET(FALSE);
				GsnRtc_AlarmStatusClr();
				GsnRtc_CboRstClr();
			}
			else 
			{
				APP_RtcInit(2);
				if(GsnRtc_IsAppWdWakeUp())
				{
					GSN_BOOTINFO_SET(GSN_WIF_SYS_BOOT_WATCHDOG_BOOT, GSN_WIF_SYS_BOOTINFO_WDOG_RESET_APP);
					GsnRtc_WDogRstClr();
				}
				else if(GsnRtc_IsAcm3Airc())
				{
					GSN_BOOTINFO_SET(GSN_WIF_SYS_BOOT_DBG_BOOT, 0);
					GsnRtc_Acm3AircClr();
				}
				else if(GsnRtc_IsFwCyptoRst())
				{
					GSN_BOOTINFO_SET(GSN_WIF_SYS_BOOT_CRYPTO_SW_BOOT, 0);
					GsnRtc_FwCryptoRstClr();
				}
				else if(GsnRtc_IsCboRst())
				{
					GSN_BOOTINFO_SET(GSN_WIF_SYS_BOOT_CORE_BROWNOUT_BOOT, 0);
					GsnRtc_CboRstClr();
				}
				else if(GsnRtc_IsWcm3Airc())
				{
					GSN_BOOTINFO_SET(GSN_WIF_SYS_BOOT_SW_RESET_BOOT, 0);
					GsnRtc_Wcm3AircClr();
				}
				else if(GsnRtc_IsPorRst())
				{
					GSN_BOOTINFO_SET(GSN_WIF_SYS_BOOT_CORE_BROWNOUT_BOOT, 0);
					GsnRtc_PorRstClr();
				}
				else
				{
					/* Reset Boot */
					if(TRUE == GSN_APP_REQ_GET())
					{
						bootReason = GSN_BOOT_REASON_GET();
						bootInfo = GSN_BOOT_INFO_GET();

						GSN_BOOTINFO_SET(bootReason, bootInfo);
						GsnRtc_FwAppRstClr();
						GSN_APP_REQ_SET(FALSE);
					}
					else
					{
						APP_RtcInit(2);    //Don't reset system info. bug id: 5819.
						GSN_BOOTINFO_SET(GSN_WIF_SYS_BOOT_EXT_RESET_BOOT, 0);
					}
				}
			}
		}
		else
		{
			/*Enable RTC SRAM Bank 0*/
			GsnRtc_RtcSramBankEn(GSN_RTC_SRAM_BANK0);

			/*set time between DCDC assertion and reset release to the core. 1.25ms */
			GsnRtc_DcDcTmrValSet(APP_CFG_DCDC_TMR_VAL);
			GsnRtc_GpioPullDownEn(0xF); 	//Enable pulldown for rtc gpio

			/* Enable BrownOut */
			GsnRtc_BrownOutEn(GSN_BROWNOUT_THRESHOLD_1_4V);

			/* Enable BrownOut reset */
			RTC_RRH_CBO_CTL_REQ_SET(RTC);

			APP_RtcInit(1);

			/* Initial Boot */
			GSN_BOOTINFO_SET(GSN_WIF_SYS_BOOT_FIRST_BOOT, 0);
		}
	}
	return;
}

