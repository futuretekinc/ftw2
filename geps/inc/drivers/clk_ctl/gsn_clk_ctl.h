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
* $RCSfile: gsn_clk_ctl.h,v $
*
* Description : This file contains function definations clock control.
*****************************************************************************/

/******************************************************************************
* File inclusion
******************************************************************************/

#ifndef _GSN_CLK_CTL_H_

#define _GSN_CLK_CTL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "core/reg/gsn_reg_rtc_spec.h"
#include "core/reg/gsn_reg_rtc_op.h"

/**
 *****************************************************************************
 * @file gsn_clk_ctl.h
 * @brief GSN CLK CTL API Definitions.
 *    This file contains the public APIs  definitions and
 *    structures of Clock Control driver.
 ****************************************************************************/


 /**
 *****************************************************************************
 * @ingroup driversdoc
 *
 * @{
 *****************************************************************************/


/**
*****************************************************************************
*   @defgroup GsnClkCtl GSN CLK CTL API
*   @brief API Functions for the Use of the Clock Control Interface.
*
*****************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/


#define GSN_CLK_CLT_BASE_ADDR 0x40070000
#define GSN_CLOCK_STABLE_INT 		38
#define GSN_RTC_BASE_ADDR 0x41000000

/**
 ******************************************************************************
 * @ingroup GsnClkCtl
 * @brief GSN CLk CTL Types.
 *    This enum defines CLK SEL values
 * @see  GSN_CLK_SEL_T  
 *    
 ******************************************************************************/
typedef enum GSN_CLK_SEL
{
	GSN_CLK_SEL_HS_RC,
	GSN_CLK_SEL_HS_XTAL,
	GSN_CLK_SEL_PLL,
	GSN_CLK_SEL_LP
}GSN_CLK_SEL_T;

/**
 ******************************************************************************
 * @ingroup GsnClkCtl
 * @brief GSN CLk CTL SRC Types.
 *    This enum defines CLK SEL SRC values
 * @see  GSN_CLK_CTL_CLK_SRC_T  
 *    
 ******************************************************************************/
typedef enum GSN_CLK_CTL_CLK_SRC
{
	GSN_CLK_CTL_CLK_NONE = 0,
	GSN_CLK_CTL_CLK_SRC_HS_RC = 1,
	GSN_CLK_CTL_CLK_SRC_HS_XTAL = 2,
	GSN_CLK_CTL_CLK_SRC_PLL = 4,
	GSN_CLK_CTL_CLK_SRC_LP = 8
}GSN_CLK_CTL_CLK_SRC_T;

/**
 ******************************************************************************
 * @ingroup GsnClkCtl
 * @brief GSN CLK CTL Structure.
 *    This structure defines a CLK CTL driver handling parameters
 * @see  GSN_CLK_CTL_CTX_T  
 *    
 ******************************************************************************/
typedef struct GSN_CLK_CTL_CTX
{
	UINT32 *pBaseClkCtl;
	UINT32 *pBaseRtc;
	UINT32 refCountHsRC;
	UINT32 refCountHsXTAL;
	UINT32 refCountPLL;
	UINT32 refCountLP;
	GSN_OSAL_SEM_T clkCtlSem;
}GSN_CLK_CTL_CTX_T;

/**
 ******************************************************************************
 * @ingroup GsnClkCtl
 * @brief GSN CLK CTL CNFG Structure.
 *    This structure defines a CLK CTL driver Config parameters
 * @see  GSN_CLK_CTL_CM3_CLK_CFG_T  
 *    
 ******************************************************************************/
typedef struct GSN_CLK_CTL_CM3_CLK_CFG
{
	GSN_CLK_CTL_CTX_T *pClkCtlCtx;
	UINT32 control; 					/**< controled by RTC or CORE */
	GSN_CLK_SEL_T cm3ClkSel;
	GSN_CLK_CTL_CLK_SRC_T sleepModeClkReq;
	GSN_CLK_CTL_CLK_SRC_T deepSleepModeClkReq;
	GSN_CLK_CTL_CLK_SRC_T activeModeClkReq;
}GSN_CLK_CTL_CM3_CLK_CFG_T;

/**
 ******************************************************************************
 * @ingroup GsnClkCtl
 * @brief Clk ctl ctx Get.
 *
 * Initilizes ref counts, base register ptr and semophore   
 * @retval GSN_CLK_CTL_CTX_T context handle.
 * @note
 ******************************************************************************/

GSN_CLK_CTL_CTX_T *
GsnClkCtl_CtxGet();

/**
 *****************************************************************************
 * @ingroup GsnClkCtl
 * @brief ClkCtl Driver init API.
 *    This function initializes ref counts, base register ptr and semophore.
 * @param clkCtlCtx            - IN clock Control Handle.
 * @retval none
 * @note
 *****************************************************************************/
VOID
GsnClkCtl_Init(GSN_CLK_CTL_CTX_T *clkCtlCtx);

/**
 *****************************************************************************
 * @ingroup GsnClkCtl
 * @brief Clock Source Enable API.
 *    This function enables the clock source.
 * @param clkCtlCtx            - IN clock Control Handle.
 * @param src                  - IN clock source.
 * @return GSN_SUCCESS         - Enable successful.
 * @return GSN_FAILURE         - Enable failed.
 * @note
 *****************************************************************************/
GSN_STATUS_T
GsnClkCtl_ClkSrcEnable(GSN_CLK_CTL_CTX_T *clkCtlCtx, GSN_CLK_CTL_CLK_SRC_T src);

/**
 *****************************************************************************
 * @ingroup GsnClkCtl
 * @brief Clock Source Disable API.
 *    This function Disable the clock source.
 * @param clkCtlCtx            - IN clock Control Handle.
 * @param src                  - IN clock source.
 * @return GSN_SUCCESS         - Disable successful.
 * @return GSN_FAILURE         - Disable failed.
 * @note
 *****************************************************************************/
GSN_STATUS_T
GsnClkCtl_ClkSrcDisable(GSN_CLK_CTL_CTX_T *clkCtlCtx, GSN_CLK_CTL_CLK_SRC_T src);

/**
 *****************************************************************************
 * @ingroup GsnClkCtl
 * @brief Clock Source Switching API.
 *    This function switch between old to new clock source.
 * @param clkCtlCtx            - IN clock Control Handle.
 * @param oldSrc                  - IN old clock source.
 * @param newSrc                  - IN new clock source.
 * @return GSN_SUCCESS         - switching successful.
 * @return GSN_FAILURE         - switching failed.
 * @note
 *****************************************************************************/
GSN_STATUS_T
GsnClkCtl_ClkSrcSwitch(GSN_CLK_CTL_CTX_T *clkCtlCtx, GSN_CLK_CTL_CLK_SRC_T oldSrc,
		GSN_CLK_CTL_CLK_SRC_T newSrc);

/**
 *****************************************************************************
 * @ingroup GsnClkCtl
 * @brief Clock Config API.
 *    This function Configures the clock.
 * @param cm3ClkCfg            - IN clock configuration struct.
 * @return GSN_SUCCESS         - Disable successful.
 * @return GSN_FAILURE         - Disable failed.
 * @note
 *****************************************************************************/
GSN_STATUS_T
GsnClkCtl_Cm3ClkCfg(GSN_CLK_CTL_CM3_CLK_CFG_T *cm3ClkCfg);

/**
 *****************************************************************************
 * @ingroup GsnClkCtl
 * @brief Cm3 Clock Source Switch API.
 *    This function switch cm3 clock source.
 * @param pCm3ClkCfg            - IN cm3 clock configuration.
 * @param newClk                  - IN new clock source.
 * @return GSN_SUCCESS         - switching successful.
 * @return GSN_FAILURE         - switching failed.
 * @note
 *****************************************************************************/
GSN_STATUS_T
GsnClkCtl_Cm3ClkSwitch(GSN_CLK_CTL_CM3_CLK_CFG_T *pCm3ClkCfg, GSN_CLK_SEL_T newClk);


VOID
GsnClkCtl_HsRcCal(GSN_CLK_CTL_CM3_CLK_CFG_T *pCm3ClkCfg);

typedef enum GSN_CLK_CTL_PLL_FREQ_SEL
{
    GSN_CLK_CTL_PLL_FREQ_20MHZ,
    GSN_CLK_CTL_PLL_FREQ_40MHZ,
    GSN_CLK_CTL_PLL_FREQ_80MHZ,
    GSN_CLK_CTL_PLL_FREQ_96MHZ,
    GSN_CLK_CTL_PLL_FREQ_120MHZ,
    GSN_CLK_CTL_PLL_FREQ_137MHZ,
    GSN_CLK_CTL_PLL_FREQ_160MHZ,
    GSN_CLK_CTL_PLL_FREQ_240MHZ,
    GSN_CLK_CTL_PLL_FREQ_480MHZ,
    GSN_CLK_CTL_PLL_FREQ_960MHZ
}GSN_CLK_CTL_PLL_FREQ_SEL_T;

INLINE VOID GsnClkCtl_SysPllEn(GSN_CLK_CTL_PLL_FREQ_SEL_T freq)
{
    RTC_CX_CLK_DIG6_ENA_SET(RTC);
    RTC_CX_PLL_SEL_DIG6_SET(RTC, freq);
}

INLINE VOID GsnClkCtl_SysPllDisable()
{
    RTC_CX_CLK_DIG6_ENA_CLEAR(RTC);
}

INLINE VOID GsnClkCtl_AdcPllEn(GSN_CLK_CTL_PLL_FREQ_SEL_T freq)
{
    RTC_CX_CLK_ADC_ENA_SET(RTC);
    RTC_CX_PLL_SEL_ADC_SET(RTC, freq);
}

INLINE VOID GsnClkCtl_AdcPllDisable()
{
    RTC_CX_CLK_ADC_ENA_CLEAR(RTC);
}

INLINE VOID GsnClkCtl_DacPllEn(GSN_CLK_CTL_PLL_FREQ_SEL_T freq)
{
    RTC_CX_CLK_DAC_ENA_SET(RTC);
    RTC_CX_PLL_SEL_DAC_SET(RTC, freq);
}

INLINE VOID GsnClkCtl_DacPllDisable()
{
    RTC_CX_CLK_DAC_ENA_CLEAR(RTC);
}

INLINE VOID GsnClkCtl_Dig5PllEn(GSN_CLK_CTL_PLL_FREQ_SEL_T freq)
{
    RTC_CX_CLK_DIG5_ENA_SET(RTC);
    RTC_CX_PLL_SEL_DIG5_SET(RTC, freq);
}

INLINE VOID GsnClkCtl_Dig5PllDisable()
{
    RTC_CX_CLK_DIG5_ENA_CLEAR(RTC);
}

INLINE VOID GsnClkCtl_Dig4PllEn(GSN_CLK_CTL_PLL_FREQ_SEL_T freq)
{
    RTC_CX_CLK_DIG4_ENA_SET(RTC);
    RTC_CX_PLL_SEL_DIG4_SET(RTC, freq);
}

INLINE VOID GsnClkCtl_Dig4PllDisable()
{
    RTC_CX_CLK_DIG4_ENA_CLEAR(RTC);
}

INLINE VOID GsnClkCtl_Dig3PllEn(GSN_CLK_CTL_PLL_FREQ_SEL_T freq)
{
    RTC_CX_CLK_DIG3_ENA_SET(RTC);
    RTC_CX_PLL_SEL_DIG3_SET(RTC, freq);
}

INLINE VOID GsnClkCtl_Dig3PllDisable()
{
    RTC_CX_CLK_DIG3_ENA_CLEAR(RTC);
}

INLINE VOID GsnClkCtl_Dig2PllEn(GSN_CLK_CTL_PLL_FREQ_SEL_T freq)
{
    RTC_CX_CLK_DIG2_ENA_SET(RTC);
    RTC_CX_PLL_SEL_DIG2_SET(RTC, freq);
}

INLINE VOID GsnClkCtl_Dig2PllDisable()
{
    RTC_CX_CLK_DIG2_ENA_CLEAR(RTC);
}

INLINE VOID GsnClkCtl_Dig1PllEn(GSN_CLK_CTL_PLL_FREQ_SEL_T freq)
{
    RTC_CX_CLK_DIG1_ENA_SET(RTC);
    RTC_CX_PLL_SEL_DIG1_SET(RTC, freq);
}

INLINE VOID GsnClkCtl_Dig1PllDisable()
{
    RTC_CX_CLK_DIG1_ENA_CLEAR(RTC);
}

#ifdef __cplusplus
		}
#endif
#endif 

