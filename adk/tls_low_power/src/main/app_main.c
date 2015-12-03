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
* $RCSfile: app_main.c,v $
*******************************************************************************/

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "tx_api.h"
#include "tx_initialize.h"
#include "gsn_includes.h"
#include "gsn_includes.h"
#include "fs_if/app_fsIf.h"
#include "gsn_ncm.h"

#include "config/app_cfg.h"
#include "app_main_ctx.h"
#include "app_sm.h"
#include "app_ncm.h"
#include "app_resource_config.h"
#include "app_events.h"
#include "app_debug.h"
#include "app_rtc_mem.h"
#define RUN_ALL_FROM_RAM
#define RUN_ALL_FROM_FLASH

/* TEMPORARY - This will be removed once API is available in GEPS */
#ifdef NO_GEPS_BROWNOUT_API

typedef enum GSN_BROWNOUT_THRESHOLD
{
    GSN_BROWNOUT_THRESHOLD_1_2V,
    GSN_BROWNOUT_THRESHOLD_1_4V,
    GSN_BROWNOUT_THRESHOLD_2_4V,
    GSN_BROWNOUT_THRESHOLD_2_8V
}GSN_BROWNOUT_THRESHOLD_T;

INLINE VOID GsnRtc_BrownOutEn(GSN_BROWNOUT_THRESHOLD_T thres)
{
    RTC_SX_SX_EN_BO_SET(RTC);
    RTC_SX_BO_TH_CTRL_SET(RTC, thres);
    RTC_SX_LOAD_F_SET(RTC);
    RTC_SX_LOAD_F_CLEAR(RTC);
}
#endif

VOID
APP_BootProcess();

GSN_SYS_STATS_T *statPtr;/*Used during debugging through debigger*/

/* Define main entry point.  */
void * MEMCPY(void * _D, const void * _S, size_t _N)
{
  char *dst = _D;
  const char *src = _S;
  
  while(_N--)
  {
      *dst++ = *src++;
  };
}

 void * MEMSET(void * _D, int _C, size_t _N)
{
#if 0
  char *dest = _D;
  while(-- _N) *dest++ = _C;
#endif
    __aeabi_memset(_D, _N, _C);
    return _D;
}
INT32
App_Main()
{

	APP_BootProcess();
    /* Create APP main task */
    AppMainCtx_Init();
    return 0;
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
#ifdef ULTRA_LOW_POWER
               APP_RtcInit(3);
                /* Initial Boot */
                GSN_BOOTINFO_SET(GSN_WIF_SYS_BOOT_SW_RESET_BOOT, GSN_WIF_SYS_BOOTINFO_NORMALBOOT_ALARM);
#else
                GSN_BOOTINFO_SET(GSN_WIF_SYS_BOOT_NORMAL_BOOT,GSN_WIF_SYS_BOOTINFO_NORMALBOOT_ALARM);
#endif
                GSN_APP_REQ_SET(FALSE);
                GsnRtc_AlarmStatusClr();
                GsnRtc_StbWakeUpTmrClr();
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
                        APP_RtcInit(1);
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
            GsnRtc_GpioPullDownEn(0xF);     //Enable pulldown for rtc gpio
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
