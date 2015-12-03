/******************************************************************************
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
* $RCSfile: gsn_rtc.h,v $
*
* Description : This file contains function declarations for RTC Driver.
*****************************************************************************/

#ifndef _GSN_RTC_H_
#define _GSN_RTC_H_

#include "gsn_includes.h"
#include "core/reg/gsn_reg_rtc_spec.h"
#include "core/reg/gsn_reg_rtc_op.h"
#include "core/reg/gsn_reg_gs2000tmr_spec.h"
#include "core/reg/gsn_reg_gs2000tmr_op.h"

/**
 *****************************************************************************
 * @file gsn_rtc.h
 * @brief GSN RTC Public Header.
 *
 *    This file contains the public APIs and structures for the RTC 
 * (real time clock) module.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup driversdoc
 *
 * @{
 *****************************************************************************/



/**
 *****************************************************************************
 * @defgroup GsnRTC GSN RTC API
 * @brief RTC and RTC-RAM Functions.
 *
 *   This module interacts with the RTC timer, which is always counting
 * when the SOC has DC power, and RTC memory, whose state is preserved as long
 * as DC power is available.
 *****************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/

typedef VOID ( *GSN_RTC_ALARM_CB_T ) (VOID *pCtx);

typedef enum GSN_RTC_ALARM
{
	GSN_RTC_ALARM_0,
	GSN_RTC_ALARM_1,
	GSN_RTC_ALARM_2,
	GSN_RTC_ALARM_3,
	GSN_RTC_ALARM_4
}GSN_RTC_ALARM_T;

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief Gsn RTC Enum for clock source.
 *    This enum defines RTC clk source type.
 * @see  GSN_RTC_CLK_SRC_T.   
 *****************************************************************************/
typedef enum GSN_RTC_CLK_SRC
{
	GSN_RTC_CLK_SRC_LP_RC,
	GSN_RTC_CLK_SRC_LP_XTAL
}GSN_RTC_CLK_SRC_T;

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief Gsn RTC gpio control type ENUM.
 *    This enum defines RTC gpio control type.
 * @see  GSN_RTC_GPIO_CTL_T.   
 *****************************************************************************/
typedef enum GSN_RTC_GPIO_CTL
{
	GSN_RTC_GPIO_CTL_DCDC,
	GSN_RTC_GPIO_CTL_DCDC_N,
	GSN_RTC_GPIO_CTL_RTC_CLK,
	GSN_RTC_GPIO_CTL_RIF_GPIO,
	GSN_RTC_GPIO_CTL_STROBE_0,
	GSN_RTC_GPIO_CTL_STROBE_0_N,
	GSN_RTC_GPIO_CTL_STROBE_1,
	GSN_RTC_GPIO_CTL_STROBE_1_N
}GSN_RTC_GPIO_CTL_T;

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief Gsn RTC DCDC control type ENUM.
 *    This enum defines RTC DCDC control type.
 * @see  GSN_RTC_DCDC_CTL_T.   
 *****************************************************************************/
typedef enum GSN_RTC_DCDC_CTL
{
	GSN_RTC_DCDC_CTL_DCDC,
	GSN_RTC_DCDC_CTL_DCDC_GPIO,
}GSN_RTC_DCDC_CTL_T;

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief Gsn RTC SRAM block type ENUM.
 *    This enum defines RTC SRAM block number.
 * @see  GSN_RTC_SRAM_BANK_T.   
 *****************************************************************************/
typedef enum GSN_RTC_SRAM_BANK
{
	GSN_RTC_SRAM_BANK0 = 1,
	GSN_RTC_SRAM_BANK1 = 2,
	GSN_RTC_SRAM_BANK2 = 4,
	GSN_RTC_SRAM_BANK3 = 8,
	GSN_RTC_SRAM_BANK_ALL = 15
}GSN_RTC_SRAM_BANK_T;

#define GSN_RTC_SRAM_BLOCK_SIZE	(1024 *4)

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief Gsn RTC SRAM block address ENUM.
 *    This enum defines RTC SRAM block address.
 * @see  GSN_RTC_SRAM_BLOCK_ADDR_T.   
 *****************************************************************************/
typedef enum GSN_RTC_SRAM_BLOCK_ADDR
{
	GSN_RTC_SRAM_BLOCK0_ADDR = 0x41100000,
	GSN_RTC_SRAM_BLOCK1_ADDR = 0x41100000 + 0x1000,
	GSN_RTC_SRAM_BLOCK2_ADDR = 0x41100000 + 0x2000,
	GSN_RTC_SRAM_BLOCK3_ADDR = 0x41100000 + 0x3000
}GSN_RTC_SRAM_BLOCK_ADDR_T;

#define GSN_RTC_LATCH_MEM_BLOCK_SIZE	1024
#define GSN_RTC_LATCH_MEM_ADDR			0x41010000

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief Gsn RTC WAKEUP SOURCE ENUM.
 *    This enum defines RTC wakeup source.
 * @see  GSN_RTC_WAKEUP_SOURCE_T.   
 *****************************************************************************/
typedef enum GSN_RTC_WAKEUP_SOURCE
{
	GSN_RTC_WAKEUP_SOURCE_ANY_ALRM 	= 0x1F,
	GSN_RTC_WAKEUP_SOURCE_ALRM_0 	= (1 << 0),
	GSN_RTC_WAKEUP_SOURCE_ALRM_1 	= (1 << 1),
	GSN_RTC_WAKEUP_SOURCE_ALRM_2 	= (1 << 2),
	GSN_RTC_WAKEUP_SOURCE_ALRM_3 	= (1 << 3),
	GSN_RTC_WAKEUP_SOURCE_ALRM_4 	= (1 << 4),
	GSN_RTC_WAKEUP_SOURCE_POR 		= (1 << 0x5),/*Power On Wakeup*/
	GSN_RTC_WAKEUP_SOURCE_TIMER 	= (1 << 0x6),/*RTC Timer Wake up. Used for Standby*/

}GSN_RTC_WAKEUP_SOURCE_T;

typedef enum GSN_BROWNOUT_THRESHOLD
{
    GSN_BROWNOUT_THRESHOLD_1_2V,
    GSN_BROWNOUT_THRESHOLD_1_4V,
    GSN_BROWNOUT_THRESHOLD_2_4V,
    GSN_BROWNOUT_THRESHOLD_2_8V
}GSN_BROWNOUT_THRESHOLD_T;

typedef enum GSN_RTC_GPIO
{
    GSN_RTC_GPIO_0 = 4,
    GSN_RTC_GPIO_1 = 8,
    GSN_RTC_GPIO_2 = 16,
    GSN_RTC_GPIO_3 = 32
}GSN_RTC_GPIO_T;

typedef enum GSN_RTC_IO_DIR
{
    GSN_RTC_IO_DIR_IN,
    GSN_RTC_IO_DIR_OUT
}GSN_RTC_IO_DIR_T;
/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver APP SRAM Enable API.
 *    This function Enables the bank 0 and bank 1 of shared sram.
 *
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_SMemBank01En()
{
	RTC_EN_PWR_APP_SRAM_CLEAR(RTC);
	RTC_ISO_CTL_APP_SRAM_CLEAR(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver APP SRAM Enable API.
 *    This function disables the bank 0 and bank 1 of shared sram.
 *
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_SMemBank01Disable()
{
    RTC_ISO_CTL_APP_SRAM_SET(RTC);
    RTC_EN_PWR_APP_SRAM_SET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver Share SRAM Enable API.
 *    This function Enables the bank 2 of Shared sram.
 *
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_SMemBank2En()
{
	RTC_EN_PWR_SHARE_MEM_CLEAR(RTC);
	RTC_ISO_CTL_SHARE_MEM_CLEAR(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver Share SRAM Enable API.
 *    This function Disables the bank 2 of Shared sram.
 *
 * @return VOID
 * @note
 *
 *****************************************************************************/

INLINE VOID GsnRtc_SMemBank2Disable()
{
	RTC_ISO_CTL_SHARE_MEM_SET(RTC);
	RTC_EN_PWR_SHARE_MEM_SET(RTC);
	
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver WLAN SRAM Enable API.
 *    This function Enables the bank 3 and bank 4 of shared sram.
 *
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_SMemBank34En()
{
	RTC_EN_PWR_WLAN_SRAM_CLEAR(RTC);
	RTC_ISO_CTL_WLAN_SRAM_CLEAR(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver WLAN SRAM Enable API.
 *    This function Disables the bank 3 and bank 4 of shared sram.
 *
 * @return VOID
 * @note
 *
 *****************************************************************************/

INLINE VOID GsnRtc_SMemBank34Disable()
{
	RTC_ISO_CTL_WLAN_SRAM_SET(RTC);
	RTC_EN_PWR_WLAN_SRAM_SET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver Crypto Enable API.
 *    This function Enables the Crypto.
 *
 * @return VOID
 * @note
 *
 *****************************************************************************/
VOID GsnSoftTmr_Delay(UINT32 delay);
INLINE VOID GsnRtc_CryptoEn()
{
    RTC_TRNG_OSC_STOP_N_F_SET(RTC);
    GsnSoftTmr_Delay(1);
	RTC_EN_PWR_CRYPTO_CLEAR(RTC);
    GsnSoftTmr_Delay(1);
	RTC_ISO_CTL_CRYPTO_CLEAR(RTC);
}

INLINE VOID GsnRtc_CryptoDisable()
{
    CLKCTL_CRYPTO_CLK_EN_SET( CLKCTL, 0);
    RTC_ISO_CTL_CRYPTO_SET(RTC);
    GsnSoftTmr_Delay(1);
    RTC_EN_PWR_CRYPTO_SET(RTC);
    GsnSoftTmr_Delay(1);
    RTC_TRNG_OSC_STOP_N_F_CLEAR(RTC);
}


INLINE UINT32 GsnRtc_IsCryptoDisabled()
{
	return RTC_EN_PWR_CRYPTO_GET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver WLAN Core Enable API.
 *    This function Enables the WLAN core for RTC.
 *
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_WlanCoreEn()
{
	RTC_EN_PWR_WLAN_CORE_CLEAR(RTC);
	RTC_ISO_CTL_WLAN_CORE_CLEAR(RTC);
}

INLINE VOID GsnRtc_WlanCoreDisable()
{
	RTC_ISO_CTL_WLAN_CORE_SET(RTC);
	RTC_EN_PWR_WLAN_CORE_SET(RTC);
	
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver SRAM BLOCK Enable API.
 *    This function Enables the SRAM BLOCK for RTC.
 *
 * @param block		- IN enum to set RTC SRAM Block
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_RtcSramBankEn(GSN_RTC_SRAM_BANK_T block)
{
	RTC_EN_PWR_RTC_SARM_SET(RTC, ~block);
	RTC_ISO_CTL_RTC_SARM_SET(RTC, ~block);
}

INLINE VOID GsnRtc_RtcSramBankDisable(GSN_RTC_SRAM_BANK_T block)
{
	RTC_ISO_CTL_RTC_SARM_SET(RTC, block);
	RTC_EN_PWR_RTC_SARM_SET(RTC, block);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver DCDC control-0 API.
 *    This function Sets or Clears the DCDC control-0.
 *
 * @param ctl			- IN enum to set DCDC control or DCDC GPIO control
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_DcDcCtl_0(GSN_RTC_DCDC_CTL_T ctl)
{
	if(ctl)
	{
		RTC_DCDC_CTL_0_SET(RTC);
	}
	else
	{
		RTC_DCDC_CTL_0_CLEAR(RTC);
	}
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver DCDC control-1 API.
 *    This function Sets or Clears the DCDC control-1.
 *
 * @param ctl			 - IN enum to set DCDC control or DCDC GPIO control
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_DcDcCtl_1(GSN_RTC_DCDC_CTL_T ctl)
{
	if(ctl)
	{
		RTC_DCDC_CTL_1_SET(RTC);
	}
	else
	{
		RTC_DCDC_CTL_1_CLEAR(RTC);
	}
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver RTC GPIO-0 Config API.
 *    This function Sets RTC GPIO-0 configuration.
 *
 * @param cfg			 - IN enum of type GSN_RTC_GPIO_CTL_T
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_Gpio_0_Cfg(GSN_RTC_GPIO_CTL_T cfg)
{
	RTC_GPIO_CTL_0_SET(RTC, cfg);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver RTC GPIO-1 Config API.
 *    This function Sets RTC GPIO-1 configuration.
 *
 * @param cfg			 - IN enum of type GSN_RTC_GPIO_CTL_T
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_Gpio_1_Cfg(GSN_RTC_GPIO_CTL_T cfg)
{
	RTC_GPIO_CTL_1_SET(RTC, cfg);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver RTC GPIO-2 Config API.
 *    This function Sets RTC GPIO-2 configuration.
 *
 * @param cfg			 - IN enum of type GSN_RTC_GPIO_CTL_T
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_Gpio_2_Cfg(GSN_RTC_GPIO_CTL_T cfg)
{
	RTC_GPIO_CTL_2_SET(RTC, cfg);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver RTC GPIO-3 Config API.
 *    This function Sets RTC GPIO-3 configuration.
 *
 * @param cfg			 - IN enum of type GSN_RTC_GPIO_CTL_T
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_Gpio_3_Cfg(GSN_RTC_GPIO_CTL_T cfg)
{
	RTC_GPIO_CTL_3_SET(RTC, cfg);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver RTC GPIO-4 Config API.
 *    This function Sets RTC GPIO-4 configuration.
 *
 * @param cfg			 - IN enum of type GSN_RTC_GPIO_CTL_T
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_Gpio_4_Cfg(GSN_RTC_GPIO_CTL_T cfg)
{
	RTC_GPIO_CTL_4_SET(RTC, cfg);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver RTC GPIO-5 Config API.
 *    This function Sets RTC GPIO-5 configuration.
 *
 * @param cfg			 - IN enum of type GSN_RTC_GPIO_CTL_T
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_Gpio_5_Cfg(GSN_RTC_GPIO_CTL_T cfg)
{
	RTC_GPIO_CTL_5_SET(RTC, cfg);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver RTC Clock Source Select API.
 *    This function Selects RTC Clock Source.
 *
 * @param src			 - IN enum for defining rtc clock source
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_ClkSrcSel(GSN_RTC_CLK_SRC_T src)
{
	if(src == GSN_RTC_CLK_SRC_LP_XTAL)
	{
		RTC_SM_SB_CLK_REQ_LP_XTAL_SET(RTC);
		RTC_SM_WK_CLK_REQ_LP_XTAL_SET(RTC);
	}
	else
	{
		RTC_SM_SB_CLK_REQ_LP_RC_SET(RTC);
		RTC_SM_WK_CLK_REQ_LP_RC_SET(RTC);
	}
	RTC_SM_RTC_CLK_SEL_SET(RTC, src);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver LP_RC Settle Time Set API.
 *    This function Sets Low power RC settle time.
 *
 * @param time			 - IN time to settle
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_LpRcSettleTimeSet(UINT32 time)
{
	RTC_SETTLE_LP_RC_SET(RTC, time);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver LP_RC Settle Time Get API.
 *    This function used to Get Low power RC settle time.
 *
 * @return UINT32			 - time to settle
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_LpRcSettleTimeGet()
{
	return RTC_SETTLE_LP_RC_GET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver LP_XTAL Settle Time Set API.
 *    This function Sets Low power XTAL settle time.
 *
 * @param time			 - IN time to settle
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_LpXtalSettleTimeSet(UINT32 time)
{
	RTC_SETTLE_LP_XTAL_SET(RTC, time);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver LP_XTAL Settle Time Get API.
 *    This function used to Get Low power XTAL settle time.
 *
 * @return UINT32			 -  time to settle
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_LpXtalSettleTimeGet()
{
	return RTC_SETTLE_LP_XTAL_GET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver HSRC Settle Time Set API.
 *    This function Sets HSRC settle time.
 *
 * @param time			 - IN time to settle
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_HsRcSettleTimeSet(UINT32 time)
{
	RTC_SETTLE_HS_RC_SET(RTC, time);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver LP_XTAL Settle Time Get API.
 *    This function used to Get Low power XTAL settle time.
 *
 * @return UINT32			 -  time to settle
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_HsRcSettleTimeGet()
{
	return RTC_SETTLE_HS_RC_GET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver HS_XTAL Settle Time Set API.
 *    This function Sets HS_XTAL settle time.
 *
 * @param time			 - IN time to settle
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_HsXtalSettleTimeSet(UINT32 time)
{
	RTC_SETTLE_HS_XTAL_SET(RTC, time);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver LP_XTAL Settle Time Get API.
 *    This function used to Get Low power XTAL settle time.
 *
 * @return UINT32			 -  time to settle
 * @note
 *
 *****************************************************************************/

INLINE UINT32 GsnRtc_HsXtalSettleTimeGet()
{
	return RTC_SETTLE_HS_XTAL_GET(RTC);
}

INLINE VOID GsnRtc_PllSettleTimeSet(UINT32 time)
{
	RTC_SETTLE_PLL_SET(RTC, time);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver PLL Settle Time Get API.
 *    This function used to Get Low power PLL settle time.
 *
 * @return UINT32			 -  time to settle
 * @note
 *
 *****************************************************************************/

INLINE UINT32 GsnRtc_PllSettleTimeGet()
{
	return RTC_SETTLE_PLL_GET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver WakeUp Sources Get API.
 *    This function used to Get WakeUp Sources.
 *
 * @return UINT32			 -  Sources
 * @note
 *
 *****************************************************************************/

INLINE UINT32 GsnRtc_WakeUpSourcesGet()
{
	return RTC_SM_WAKEUP_SOURCES_GET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver IsTmrWakeUp API.
 *    Wake up is due to Time out configured in RTC Timer
 *
 * @return UINT32			 
 * @note
 *
 *****************************************************************************/

INLINE UINT32 GsnRtc_IsTmrWakeUp()
{	
	UINT32  status;
	status = RTC_RTC_PCNT_IRQ_STATUS_GET(RTC);
	if(status)
	{
		return (RTC_SM_WAKEUP_SOURCES_GET(RTC) & GSN_RTC_WAKEUP_SOURCE_TIMER);
	}
	else
	{
		return 0;
	}
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver IsPorWakeUp API.
 *    Wake up is due to Power On Reset
 *
 * @return UINT32			 
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_IsPorWakeUp()
{
	return (RTC_SM_WAKEUP_SOURCES_GET(RTC) & GSN_RTC_WAKEUP_SOURCE_POR);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver IsAlarmWakeUp API.
 *    Wake up is due to Any of the 5 Alarm Inputs
 *
 * @return UINT32			 
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_IsAlarmWakeUp()
{
	UINT32 wakeUpReason = RTC_SM_WAKEUP_SOURCES_GET(RTC);

	UINT32 alarm = RTC_ALARM_STATUS_GET(RTC);

	if(alarm)
		return (wakeUpReason & GSN_RTC_WAKEUP_SOURCE_ANY_ALRM);
	else
		return 0;

}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver IsAlarm0WakeUp API.
 *    Wake up is due to Alarm 1 Input
 *
 * @return UINT32			 
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_IsAlarm0WakeUp()
{
	UINT32 wakeUpReason = RTC_SM_WAKEUP_SOURCES_GET(RTC);
	return (wakeUpReason & GSN_RTC_WAKEUP_SOURCE_ALRM_0);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver IsAlarm1WakeUp API.
 *    Wake up is due to Alarm 2 Input
 *
 * @return UINT32			 
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_IsAlarm1WakeUp()
{
	UINT32 wakeUpReason = RTC_SM_WAKEUP_SOURCES_GET(RTC);
	return (wakeUpReason & GSN_RTC_WAKEUP_SOURCE_ALRM_1);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver IsAlarm2WakeUp API.
 *    Wake up is due to Alarm 3 Input
 *
 * @return UINT32			 
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_IsAlarm2WakeUp()
{
	UINT32 wakeUpReason = RTC_SM_WAKEUP_SOURCES_GET(RTC);
	return (wakeUpReason & GSN_RTC_WAKEUP_SOURCE_ALRM_2);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver IsAlarm3WakeUp API.
 *    Wake up is due to Alarm 4 Input
 *
 * @return UINT32			 
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_IsAlarm3WakeUp()
{
	UINT32 wakeUpReason = RTC_SM_WAKEUP_SOURCES_GET(RTC);
	return (wakeUpReason & GSN_RTC_WAKEUP_SOURCE_ALRM_3);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver IsAlarm4WakeUp API.
 *    Wake up is due to Alarm 5 Input
 *
 * @return UINT32			 
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_IsAlarm4WakeUp()
{
	UINT32 wakeUpReason = RTC_SM_WAKEUP_SOURCES_GET(RTC);
	return (wakeUpReason & GSN_RTC_WAKEUP_SOURCE_ALRM_4);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver IsAppWdWakeUp API.
 *    Wake up is due to App wd
 *
 * @return UINT32			 
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_IsAppWdWakeUp()
{
	return (RTC_RRH_AWDOG_STATUS_GET(RTC));
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver GPIO Pull Down Enable API.
 *
 * @param mask		- IN GPIO mask for RTC PDEN
 * @return VOID			 
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_GpioPullDownEn(UINT32 mask)
{
    UINT32 oldval;
    oldval = RTC_SX_PDEN_GET(RTC);
    oldval = oldval | mask;
    RTC_SX_PDEN_SET(RTC, oldval);
}

INLINE VOID GsnRtc_GpioPullDownDis(UINT32 mask)
{
    UINT32 oldval;
    oldval = RTC_SX_PDEN_GET(RTC);
    oldval = oldval & (~mask);
    RTC_SX_PDEN_SET(RTC, oldval);
}

INLINE VOID GsnRtc_GpioPullUpEn(UINT32 mask)
{
    UINT32 oldval;
    oldval = RTC_SX_PUEN_GET(RTC);
    oldval = oldval | mask;
    RTC_SX_PUEN_SET(RTC, oldval);
}

INLINE VOID GsnRtc_GpioPullUpDis(UINT32 mask)
{
    UINT32 oldval;
    oldval = RTC_SX_PUEN_GET(RTC);
    oldval = oldval & (~mask);
    RTC_SX_PUEN_SET(RTC, oldval);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver WatchDog Reset Clear API.
 *
 * @return VOID			 
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_WDogRstClr()
{
	RTC_RRH_AWDOG_STATUS_SET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver Por Reset Clear API.
 *
 * @return VOID			 
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_PorRstClr()
{
	RTC_RRH_FWPOR_STATUS_SET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver IsPor Reset API.
 *
 * @return UINT32			 
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_IsPorRst()
{
	return RTC_RRH_FWPOR_STATUS_GET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver StbWakeUpTmr Clear API.
 *
 * @return VOID			 
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_StbWakeUpTmrClr()
{
	RTC_PCNT_WU_LSB_SET(RTC, 0xFFFFFFFF);
	RTC_PCNT_WU_MSB_SET(RTC, 0xFFFF);
	RTC_RTC_PCNT_IRQ_MASK_VAL_CLEAR(RTC);
	RTC_RTC_PCNT_IRQ_CLEAR_SET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver AlarmStatus Clear API.
 *
 * @return VOID			 
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_AlarmStatusClr()
{
	UINT32 alarm = RTC_ALARM_STATUS_GET(RTC);
	RTC_ALARM_IRQ_CLEAR_SET(RTC, alarm);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver IsPorEvent API.
 *
 * @return UINT32			 
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_IsPorEvent()
{
	return RTC_SM_WU_CTL_POR_EVENT_GET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver IsPorEvent Clear API.
 *
 * @return VOID			 
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_PorEventClr()
{
	RTC_SM_WU_CTL_POR_EVENT_CLEAR(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver FwApp Reset Clear API.
 *
 * @return VOID			 
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_FwAppRstClr()
{
	RTC_RRH_FWAPP_STATUS_SET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver FwApp Reset API.
 *
 * @return UINT32			 
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_IsFwAppRst()
{
	return RTC_RRH_FWAPP_STATUS_GET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver FwWlan Reset Clear API.
 *
 * @return VOID			 
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_FwWlanRstClr()
{
	RTC_RRH_FWWLAN_STATUS_SET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver FwWlan Reset API.
 *
 * @return UINT32			 
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_IsFwWlanRst()
{
	return RTC_RRH_FWWLAN_STATUS_GET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver FwCrypto Reset Clear API.
 *
 * @return VOID			 
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_FwCryptoRstClr()
{
	RTC_RRH_FWCRYPTO_STATUS_SET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver FwCypto Reset API.
 *
 * @return UINT32			 
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_IsFwCyptoRst()
{
	return RTC_RRH_FWCRYPTO_STATUS_GET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver Acm3Airc Clear API.
 *
 * @return VOID			 
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_Acm3AircClr()
{
	RTC_RRH_ACM3AIRC_STATUS_SET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver IsAcm3Airc API.
 *
 * @return UINT32			 
 * @note
 *
 *****************************************************************************/

INLINE UINT32 GsnRtc_IsAcm3Airc()
{
	return RTC_RRH_ACM3AIRC_STAT_GET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver Wcm3Airc Clear API.
 *
 * @return VOID			 
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_Wcm3AircClr()
{
	RTC_RRH_WCM3AIRC_STATUS_SET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver IsWcm3Airc API.
 *
 * @return UINT32			 
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_IsWcm3Airc()
{
	return RTC_RRH_WCM3AIRC_STAT_GET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver Cbo Reset Clear API.
 *
 * @return VOID			 
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_CboRstClr()
{
	RTC_RRH_CBO_STATUS_SET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver IsCbo Reset API.
 *
 * @return UINT32			 
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_IsCboRst()
{
	return RTC_RRH_CBO_STATUS_GET(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver Alarm interrupt Status Get API.
 *
 * @return none			 
 * @note
 *
 *****************************************************************************/
INLINE UINT32 GsnRtc_AlarmIrqStatusGet()
{
	//return RTC_ALARM_STATUS_GET(RTC);
	return GS2000TMR_ALARM_IRQ_STATUS_GET(GS2000TMR);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver Alarm interrupt Clear API.
 *
 * @return none			 
 * @note
 *
 *****************************************************************************/
INLINE VOID GsnRtc_AlarmIrqClear(UINT32 bitmask)
{
	//RTC_ALARM_IRQ_CLEAR_SET(RTC, bitmask);
	GS2000TMR_ALARM_IRQ_CLEAR_SET(GS2000TMR, bitmask);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver Alarm interrupt Callback register API.
 *
 * @return none			 
 * @note
 *
 *****************************************************************************/
VOID GsnRtc_AlarmRegisterCb(UINT32 number, GSN_RTC_ALARM_CB_T CallBack, VOID *pCtx);

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver Alarm interrupt calback Deregister API.
 *
 * @return none			 
 * @note
 *
 *****************************************************************************/
VOID GsnRtc_AlarmDeRegisterCb(UINT32 number);

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC Driver Alarm input configure API.
 *
 * @return none			 
 * @note
 *
 *****************************************************************************/
VOID GsnRtc_AlarmCfg(UINT32 alarm, UINT32 polarity, UINT32 interrupt);

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief Crypto Block Reset API.
 *
 * @return none			 
 * @note
 *
 *****************************************************************************/

INLINE VOID GsnRtc_CryptoReset()
{
	RTC_RRH_FWCRYPTO_CTL_REQ_SET(RTC);
    GsnSoftTmr_Delay(1);
	RTC_RRH_REQ_RST_FWCRYPTO_SET(RTC);
}

VOID GsnRtc_AlarmConfig(UINT32 alarm, UINT32 polarity, UINT32 interrupt);

VOID GsnRtc_AlarmDisable(UINT32 alarm);

INLINE VOID GsnRtc_Ldo2Disable()
{
    INT32 *pLdo2 = (INT32 *)0x410002a8;
    *pLdo2 = 3;
    *pLdo2 = 2;
}

INLINE VOID GsnRtc_Ldo2Enable()
{
    INT32 *pLdo2 = (INT32 *)0x410002a8;
    *pLdo2 = 3;
}

INLINE VOID GsnRtc_Ldo1Disable()
{
    INT32 *pLdo1 = (INT32 *)0x41000268;
    *pLdo1 = 3;
    *pLdo1 = 2;
}

INLINE VOID GsnRtc_Ldo1Enable()
{
    INT32 *pLdo1 = (INT32 *)0x41000268;
    *pLdo1 = 3;
}

INLINE VOID GsnRtc_microLdoEnable()
{
    RTC_SX_EN_U_LDO_F_SET(RTC);
}

INLINE VOID GsnRtc_microLdoDisable()
{
    RTC_SX_EN_U_LDO_F_CLEAR(RTC);
}

INLINE VOID GsnRtc_DcDcTmrValSet(UINT16 val)
{
	RTC_SM_DCDC_TMR_CTL_SET(RTC, val);
}

INLINE VOID GsnRtc_BrownOutEn(GSN_BROWNOUT_THRESHOLD_T thres)
{
    RTC_SX_SX_EN_BO_SET(RTC);
    RTC_SX_BO_TH_CTRL_SET(RTC, thres);
    RTC_SX_LOAD_F_SET(RTC);
    RTC_SX_LOAD_F_CLEAR(RTC);
}

INLINE VOID GsnRtc_BrownOutDisable()
{
    RTC_SX_SX_EN_BO_CLEAR(RTC);
    RTC_SX_LOAD_F_SET(RTC);
    RTC_SX_LOAD_F_CLEAR(RTC);
}

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC GPIO config API.
 *
 * @return none			 
 * @note
 *
 *****************************************************************************/
VOID GsnRtc_IOConf(GSN_RTC_GPIO_T gpio, GSN_RTC_IO_DIR_T dir);

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC GPIO input value get API.
 *
 * @return none			 
 * @note
 *
 *****************************************************************************/
UINT32 GsnRtc_GpioInValGet(GSN_RTC_GPIO_T gpio);

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC GPIO output set API.
 *
 * @return none			 
 * @note
 *
 *****************************************************************************/
VOID GsnRtc_GpioOutSet(GSN_RTC_GPIO_T gpio, UINT32 val);

/**
 *****************************************************************************
 * @ingroup GsnRTC
 * @brief RTC GPIO output get API.
 *
 * @return none			 
 * @note
 *
 *****************************************************************************/
UINT32 GsnRtc_GpioOutGet(GSN_RTC_GPIO_T gpio);
#endif
