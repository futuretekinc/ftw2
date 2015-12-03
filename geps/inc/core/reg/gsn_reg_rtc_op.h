/******************************************************************************
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
* $RCSfile: gsn_reg_rtc_op.h,v $
*
* Description : This file contains RTC register operation macros.
*****************************************************************************/


#ifndef _REG_RTC_MAC_H
#define _REG_RTC_MAC_H

/***************************************************
 *
 *             RTC
 *
 ***************************************************/


/*
 *  RTC_GPIO_IE register macros
 ****************************************************************************************
 */
#define RTC_GPIO_IE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_IE))
#define RTC_GPIO_IE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_IE, (value))
#define RTC_GPIO_IE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_IE, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_IE) | (value))
#define RTC_GPIO_IE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_IE, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_IE) & (~(value)))

/*
 *  RTC_GPIO_IE_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_GPIO_IE_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_GPIO_IE_VAL)


/*
 *  RTC_GPIO_IN register macros
 ****************************************************************************************
 */
#define RTC_GPIO_IN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_IN))

/*
 *  RTC_GPIO_IN_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_GPIO_IN_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_GPIO_IN_VAL)


/*
 *  RTC_GPIO_OUT register macros
 ****************************************************************************************
 */
#define RTC_GPIO_OUT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_OUT))
#define RTC_GPIO_OUT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_OUT, (value))
#define RTC_GPIO_OUT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_OUT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_OUT) | (value))
#define RTC_GPIO_OUT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_OUT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_OUT) & (~(value)))

/*
 *  RTC_GPIO_OUT_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_GPIO_OUT_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_GPIO_OUT_VAL)


/*
 *  RTC_GPIO_OE register macros
 ****************************************************************************************
 */
#define RTC_GPIO_OE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_OE))
#define RTC_GPIO_OE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_OE, (value))
#define RTC_GPIO_OE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_OE, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_OE) | (value))
#define RTC_GPIO_OE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_OE, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_OE) & (~(value)))

/*
 *  RTC_GPIO_OE_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_GPIO_OE_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_GPIO_OE_VAL)


/*
 *  RTC_GPIO_CTL register macros
 ****************************************************************************************
 */
#define RTC_GPIO_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_CTL))
#define RTC_GPIO_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_CTL, (value))
#define RTC_GPIO_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_CTL) | (value))
#define RTC_GPIO_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_GPIO_CTL) & (~(value)))

/*
 *  RTC_GPIO_CTL_0 bit field macros
 ****************************************************************************************
 */
#define RTC_GPIO_CTL_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_GPIO_CTL_0)
#define RTC_GPIO_CTL_0_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_GPIO_CTL_0, (value))

/*
 *  RTC_GPIO_CTL_1 bit field macros
 ****************************************************************************************
 */
#define RTC_GPIO_CTL_1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_GPIO_CTL_1)
#define RTC_GPIO_CTL_1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_GPIO_CTL_1, (value))

/*
 *  RTC_GPIO_CTL_2 bit field macros
 ****************************************************************************************
 */
#define RTC_GPIO_CTL_2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_GPIO_CTL_2)
#define RTC_GPIO_CTL_2_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_GPIO_CTL_2, (value))

/*
 *  RTC_GPIO_CTL_3 bit field macros
 ****************************************************************************************
 */
#define RTC_GPIO_CTL_3_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_GPIO_CTL_3)
#define RTC_GPIO_CTL_3_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_GPIO_CTL_3, (value))

/*
 *  RTC_GPIO_CTL_4 bit field macros
 ****************************************************************************************
 */
#define RTC_GPIO_CTL_4_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_GPIO_CTL_4)
#define RTC_GPIO_CTL_4_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_GPIO_CTL_4, (value))

/*
 *  RTC_GPIO_CTL_5 bit field macros
 ****************************************************************************************
 */
#define RTC_GPIO_CTL_5_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_GPIO_CTL_5)
#define RTC_GPIO_CTL_5_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_GPIO_CTL_5, (value))


/*
 *  RTC_DCDC_CTL register macros
 ****************************************************************************************
 */
#define RTC_DCDC_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_DCDC_CTL))
#define RTC_DCDC_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_DCDC_CTL, (value))
#define RTC_DCDC_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_DCDC_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_DCDC_CTL) | (value))
#define RTC_DCDC_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_DCDC_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_DCDC_CTL) & (~(value)))

/*
 *  RTC_DCDC_CTL_0 bit field macros
 ****************************************************************************************
 */
#define RTC_DCDC_CTL_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_DCDC_CTL_0)
#define RTC_DCDC_CTL_0_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_DCDC_CTL_0, 1)
#define RTC_DCDC_CTL_0_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_DCDC_CTL_0, 0)

/*
 *  RTC_DCDC_CTL_1 bit field macros
 ****************************************************************************************
 */
#define RTC_DCDC_CTL_1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_DCDC_CTL_1)
#define RTC_DCDC_CTL_1_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_DCDC_CTL_1, 1)
#define RTC_DCDC_CTL_1_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_DCDC_CTL_1, 0)


/*
 *  RTC_SM_WU_CTL register macros
 ****************************************************************************************
 */
#define RTC_SM_WU_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WU_CTL))
#define RTC_SM_WU_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WU_CTL, (value))
#define RTC_SM_WU_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WU_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WU_CTL) | (value))
#define RTC_SM_WU_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WU_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WU_CTL) & (~(value)))

/*
 *  RTC_SM_WU_CTL_POR_EVENT bit field macros
 ****************************************************************************************
 */
#define RTC_SM_WU_CTL_POR_EVENT_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_WU_CTL_POR_EVENT)
#define RTC_SM_WU_CTL_POR_EVENT_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_WU_CTL_POR_EVENT, 1)
#define RTC_SM_WU_CTL_POR_EVENT_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_WU_CTL_POR_EVENT, 0)

/*
 *  RTC_SM_WU_CTL_BOOT_CLK_ACTV bit field macros
 ****************************************************************************************
 */
#define RTC_SM_WU_CTL_BOOT_CLK_ACTV_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_WU_CTL_BOOT_CLK_ACTV)
#define RTC_SM_WU_CTL_BOOT_CLK_ACTV_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_WU_CTL_BOOT_CLK_ACTV, 1)
#define RTC_SM_WU_CTL_BOOT_CLK_ACTV_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_WU_CTL_BOOT_CLK_ACTV, 0)


/*
 *  RTC_SM_WU_SB_REQ register macros
 ****************************************************************************************
 */
#define RTC_SM_WU_SB_REQ_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WU_SB_REQ))
#define RTC_SM_WU_SB_REQ_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WU_SB_REQ, (value))
#define RTC_SM_WU_SB_REQ_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WU_SB_REQ, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WU_SB_REQ) | (value))
#define RTC_SM_WU_SB_REQ_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WU_SB_REQ, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WU_SB_REQ) & (~(value)))

/*
 *  RTC_SM_WU_SB_REQ_EN bit field macros
 ****************************************************************************************
 */
#define RTC_SM_WU_SB_REQ_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_WU_SB_REQ_EN)
#define RTC_SM_WU_SB_REQ_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_WU_SB_REQ_EN, 1)
#define RTC_SM_WU_SB_REQ_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_WU_SB_REQ_EN, 0)


/*
 *  RTC_SM_RTC_CLK_SEL register macros
 ****************************************************************************************
 */
#define RTC_SM_RTC_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_RTC_CLK_SEL))
#define RTC_SM_RTC_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_RTC_CLK_SEL, (value))
#define RTC_SM_RTC_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_RTC_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_RTC_CLK_SEL) | (value))
#define RTC_SM_RTC_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_RTC_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_RTC_CLK_SEL) & (~(value)))

/*
 *  RTC_SM_RTC_CLK_MUX_SEL bit field macros
 ****************************************************************************************
 */
#define RTC_SM_RTC_CLK_MUX_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_RTC_CLK_MUX_SEL)
#define RTC_SM_RTC_CLK_MUX_SEL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_RTC_CLK_MUX_SEL, 1)
#define RTC_SM_RTC_CLK_MUX_SEL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_RTC_CLK_MUX_SEL, 0)


/*
 *  RTC_SM_SB_CLK_REQ register macros
 ****************************************************************************************
 */
#define RTC_SM_SB_CLK_REQ_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_SB_CLK_REQ))
#define RTC_SM_SB_CLK_REQ_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_SB_CLK_REQ, (value))
#define RTC_SM_SB_CLK_REQ_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_SB_CLK_REQ, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_SB_CLK_REQ) | (value))
#define RTC_SM_SB_CLK_REQ_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_SB_CLK_REQ, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_SB_CLK_REQ) & (~(value)))

/*
 *  RTC_SM_SB_CLK_REQ_LP_RC bit field macros
 ****************************************************************************************
 */
#define RTC_SM_SB_CLK_REQ_LP_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_SB_CLK_REQ_LP_RC)
#define RTC_SM_SB_CLK_REQ_LP_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_SB_CLK_REQ_LP_RC, 1)
#define RTC_SM_SB_CLK_REQ_LP_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_SB_CLK_REQ_LP_RC, 0)

/*
 *  RTC_SM_SB_CLK_REQ_LP_XTAL bit field macros
 ****************************************************************************************
 */
#define RTC_SM_SB_CLK_REQ_LP_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_SB_CLK_REQ_LP_XTAL)
#define RTC_SM_SB_CLK_REQ_LP_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_SB_CLK_REQ_LP_XTAL, 1)
#define RTC_SM_SB_CLK_REQ_LP_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_SB_CLK_REQ_LP_XTAL, 0)

/*
 *  RTC_SM_SB_CLK_REQ_HS_RC bit field macros
 ****************************************************************************************
 */
#define RTC_SM_SB_CLK_REQ_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_SB_CLK_REQ_HS_RC)
#define RTC_SM_SB_CLK_REQ_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_SB_CLK_REQ_HS_RC, 1)
#define RTC_SM_SB_CLK_REQ_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_SB_CLK_REQ_HS_RC, 0)

/*
 *  RTC_SM_SB_CLK_REQ_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define RTC_SM_SB_CLK_REQ_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_SB_CLK_REQ_HS_XTAL)
#define RTC_SM_SB_CLK_REQ_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_SB_CLK_REQ_HS_XTAL, 1)
#define RTC_SM_SB_CLK_REQ_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_SB_CLK_REQ_HS_XTAL, 0)

/*
 *  RTC_SM_SB_CLK_REQ_PLL bit field macros
 ****************************************************************************************
 */
#define RTC_SM_SB_CLK_REQ_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_SB_CLK_REQ_PLL)
#define RTC_SM_SB_CLK_REQ_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_SB_CLK_REQ_PLL, 1)
#define RTC_SM_SB_CLK_REQ_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_SB_CLK_REQ_PLL, 0)


/*
 *  RTC_SM_WK_CLK_REQ register macros
 ****************************************************************************************
 */
#define RTC_SM_WK_CLK_REQ_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WK_CLK_REQ))
#define RTC_SM_WK_CLK_REQ_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WK_CLK_REQ, (value))
#define RTC_SM_WK_CLK_REQ_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WK_CLK_REQ, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WK_CLK_REQ) | (value))
#define RTC_SM_WK_CLK_REQ_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WK_CLK_REQ, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WK_CLK_REQ) & (~(value)))

/*
 *  RTC_SM_WK_CLK_REQ_LP_RC bit field macros
 ****************************************************************************************
 */
#define RTC_SM_WK_CLK_REQ_LP_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_WK_CLK_REQ_LP_RC)
#define RTC_SM_WK_CLK_REQ_LP_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_WK_CLK_REQ_LP_RC, 1)
#define RTC_SM_WK_CLK_REQ_LP_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_WK_CLK_REQ_LP_RC, 0)

/*
 *  RTC_SM_WK_CLK_REQ_LP_XTAL bit field macros
 ****************************************************************************************
 */
#define RTC_SM_WK_CLK_REQ_LP_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_WK_CLK_REQ_LP_XTAL)
#define RTC_SM_WK_CLK_REQ_LP_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_WK_CLK_REQ_LP_XTAL, 1)
#define RTC_SM_WK_CLK_REQ_LP_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_WK_CLK_REQ_LP_XTAL, 0)

/*
 *  RTC_SM_WK_CLK_REQ_HS_RC bit field macros
 ****************************************************************************************
 */
#define RTC_SM_WK_CLK_REQ_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_WK_CLK_REQ_HS_RC)
#define RTC_SM_WK_CLK_REQ_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_WK_CLK_REQ_HS_RC, 1)
#define RTC_SM_WK_CLK_REQ_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_WK_CLK_REQ_HS_RC, 0)

/*
 *  RTC_SM_WK_CLK_REQ_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define RTC_SM_WK_CLK_REQ_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_WK_CLK_REQ_HS_XTAL)
#define RTC_SM_WK_CLK_REQ_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_WK_CLK_REQ_HS_XTAL, 1)
#define RTC_SM_WK_CLK_REQ_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_WK_CLK_REQ_HS_XTAL, 0)

/*
 *  RTC_SM_WK_CLK_REQ_PLL bit field macros
 ****************************************************************************************
 */
#define RTC_SM_WK_CLK_REQ_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_WK_CLK_REQ_PLL)
#define RTC_SM_WK_CLK_REQ_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_WK_CLK_REQ_PLL, 1)
#define RTC_SM_WK_CLK_REQ_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_WK_CLK_REQ_PLL, 0)


/*
 *  RTC_SM_DCDC_TMR_CTL register macros
 ****************************************************************************************
 */
#define RTC_SM_DCDC_TMR_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_DCDC_TMR_CTL))
#define RTC_SM_DCDC_TMR_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_DCDC_TMR_CTL, (value))
#define RTC_SM_DCDC_TMR_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_DCDC_TMR_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_DCDC_TMR_CTL) | (value))
#define RTC_SM_DCDC_TMR_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_DCDC_TMR_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_DCDC_TMR_CTL) & (~(value)))

/*
 *  RTC_SM_DCDC_TMR_CTL_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_SM_DCDC_TMR_CTL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_DCDC_TMR_CTL_VAL)
#define RTC_SM_DCDC_TMR_CTL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_DCDC_TMR_CTL_VAL, (value))


/*
 *  RTC_SM_MASK_RST register macros
 ****************************************************************************************
 */
#define RTC_SM_MASK_RST_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_MASK_RST))
#define RTC_SM_MASK_RST_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_MASK_RST, (value))
#define RTC_SM_MASK_RST_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_MASK_RST, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_MASK_RST) | (value))
#define RTC_SM_MASK_RST_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_MASK_RST, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_MASK_RST) & (~(value)))

/*
 *  RTC_SM_MASK_RST_POR_ACM3 bit field macros
 ****************************************************************************************
 */
#define RTC_SM_MASK_RST_POR_ACM3_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_MASK_RST_POR_ACM3)
#define RTC_SM_MASK_RST_POR_ACM3_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_MASK_RST_POR_ACM3, 1)
#define RTC_SM_MASK_RST_POR_ACM3_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_MASK_RST_POR_ACM3, 0)

/*
 *  RTC_SM_MASK_RST_POR_WCM3 bit field macros
 ****************************************************************************************
 */
#define RTC_SM_MASK_RST_POR_WCM3_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_MASK_RST_POR_WCM3)
#define RTC_SM_MASK_RST_POR_WCM3_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_MASK_RST_POR_WCM3, 1)
#define RTC_SM_MASK_RST_POR_WCM3_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_MASK_RST_POR_WCM3, 0)

/*
 *  RTC_SM_MASK_RST_APP bit field macros
 ****************************************************************************************
 */
#define RTC_SM_MASK_RST_APP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_MASK_RST_APP)
#define RTC_SM_MASK_RST_APP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_MASK_RST_APP, 1)
#define RTC_SM_MASK_RST_APP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_MASK_RST_APP, 0)

/*
 *  RTC_SM_MASK_RST_WLAN bit field macros
 ****************************************************************************************
 */
#define RTC_SM_MASK_RST_WLAN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_MASK_RST_WLAN)
#define RTC_SM_MASK_RST_WLAN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_MASK_RST_WLAN, 1)
#define RTC_SM_MASK_RST_WLAN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_MASK_RST_WLAN, 0)

/*
 *  RTC_SM_MASK_RST_CRYPTO bit field macros
 ****************************************************************************************
 */
#define RTC_SM_MASK_RST_CRYPTO_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_MASK_RST_CRYPTO)
#define RTC_SM_MASK_RST_CRYPTO_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_MASK_RST_CRYPTO, 1)
#define RTC_SM_MASK_RST_CRYPTO_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_MASK_RST_CRYPTO, 0)


/*
 *  RTC_SM_WAKEUP_SOURCES register macros
 ****************************************************************************************
 */
#define RTC_SM_WAKEUP_SOURCES_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_WAKEUP_SOURCES))

/*
 *  RTC_SM_WAKEUP_SOURCE_ALARM bit field macros
 ****************************************************************************************
 */
#define RTC_SM_WAKEUP_SOURCE_ALARM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_WAKEUP_SOURCE_ALARM)

/*
 *  RTC_SM_WAKEUP_SOURCE_POR bit field macros
 ****************************************************************************************
 */
#define RTC_SM_WAKEUP_SOURCE_POR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_WAKEUP_SOURCE_POR)

/*
 *  RTC_SM_WAKEUP_SOURCE_TMR bit field macros
 ****************************************************************************************
 */
#define RTC_SM_WAKEUP_SOURCE_TMR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_WAKEUP_SOURCE_TMR)


/*
 *  RTC_SM_ALARM_CLK_REQ register macros
 ****************************************************************************************
 */
#define RTC_SM_ALARM_CLK_REQ_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_ALARM_CLK_REQ))
#define RTC_SM_ALARM_CLK_REQ_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_ALARM_CLK_REQ, (value))
#define RTC_SM_ALARM_CLK_REQ_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_ALARM_CLK_REQ, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_ALARM_CLK_REQ) | (value))
#define RTC_SM_ALARM_CLK_REQ_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_ALARM_CLK_REQ, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SM_ALARM_CLK_REQ) & (~(value)))

/*
 *  RTC_SM_ALARM_CLK_REQ_LP_RC bit field macros
 ****************************************************************************************
 */
#define RTC_SM_ALARM_CLK_REQ_LP_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_ALARM_CLK_REQ_LP_RC)
#define RTC_SM_ALARM_CLK_REQ_LP_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_ALARM_CLK_REQ_LP_RC, 1)
#define RTC_SM_ALARM_CLK_REQ_LP_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_ALARM_CLK_REQ_LP_RC, 0)

/*
 *  RTC_SM_ALARM_CLK_REQ_LP_XTAL bit field macros
 ****************************************************************************************
 */
#define RTC_SM_ALARM_CLK_REQ_LP_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_ALARM_CLK_REQ_LP_XTAL)
#define RTC_SM_ALARM_CLK_REQ_LP_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_ALARM_CLK_REQ_LP_XTAL, 1)
#define RTC_SM_ALARM_CLK_REQ_LP_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_ALARM_CLK_REQ_LP_XTAL, 0)

/*
 *  RTC_SM_ALARM_CLK_REQ_HS_RC bit field macros
 ****************************************************************************************
 */
#define RTC_SM_ALARM_CLK_REQ_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_ALARM_CLK_REQ_HS_RC)
#define RTC_SM_ALARM_CLK_REQ_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_ALARM_CLK_REQ_HS_RC, 1)
#define RTC_SM_ALARM_CLK_REQ_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_ALARM_CLK_REQ_HS_RC, 0)

/*
 *  RTC_SM_ALARM_CLK_REQ_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define RTC_SM_ALARM_CLK_REQ_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_ALARM_CLK_REQ_HS_XTAL)
#define RTC_SM_ALARM_CLK_REQ_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_ALARM_CLK_REQ_HS_XTAL, 1)
#define RTC_SM_ALARM_CLK_REQ_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_ALARM_CLK_REQ_HS_XTAL, 0)

/*
 *  RTC_SM_ALARM_CLK_REQ_PLL bit field macros
 ****************************************************************************************
 */
#define RTC_SM_ALARM_CLK_REQ_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SM_ALARM_CLK_REQ_PLL)
#define RTC_SM_ALARM_CLK_REQ_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_ALARM_CLK_REQ_PLL, 1)
#define RTC_SM_ALARM_CLK_REQ_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SM_ALARM_CLK_REQ_PLL, 0)


/*
 *  RTC_TRNG_OSC_STOP_N register macros
 ****************************************************************************************
 */
#define RTC_TRNG_OSC_STOP_N_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_TRNG_OSC_STOP_N))
#define RTC_TRNG_OSC_STOP_N_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_TRNG_OSC_STOP_N, (value))
#define RTC_TRNG_OSC_STOP_N_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_TRNG_OSC_STOP_N, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_TRNG_OSC_STOP_N) | (value))
#define RTC_TRNG_OSC_STOP_N_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_TRNG_OSC_STOP_N, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_TRNG_OSC_STOP_N) & (~(value)))

/*
 *  RTC_TRNG_OSC_STOP_N_F bit field macros
 ****************************************************************************************
 */
#define RTC_TRNG_OSC_STOP_N_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_TRNG_OSC_STOP_N_F)
#define RTC_TRNG_OSC_STOP_N_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_TRNG_OSC_STOP_N_F, 1)
#define RTC_TRNG_OSC_STOP_N_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_TRNG_OSC_STOP_N_F, 0)


/*
 *  RTC_SRAM_ISO_EN register macros
 ****************************************************************************************
 */
#define RTC_SRAM_ISO_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SRAM_ISO_EN))
#define RTC_SRAM_ISO_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SRAM_ISO_EN, (value))
#define RTC_SRAM_ISO_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SRAM_ISO_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SRAM_ISO_EN) | (value))
#define RTC_SRAM_ISO_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SRAM_ISO_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SRAM_ISO_EN) & (~(value)))

/*
 *  RTC_SRAM_ISO_ENABLE bit field macros
 ****************************************************************************************
 */
#define RTC_SRAM_ISO_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SRAM_ISO_ENABLE)
#define RTC_SRAM_ISO_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SRAM_ISO_ENABLE, 1)
#define RTC_SRAM_ISO_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SRAM_ISO_ENABLE, 0)


/*
 *  RTC_PCNT_WU_LSB register macros
 ****************************************************************************************
 */
#define RTC_PCNT_WU_LSB_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_PCNT_WU_LSB))
#define RTC_PCNT_WU_LSB_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_PCNT_WU_LSB, (value))
#define RTC_PCNT_WU_LSB_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_PCNT_WU_LSB, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_PCNT_WU_LSB) | (value))
#define RTC_PCNT_WU_LSB_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_PCNT_WU_LSB, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_PCNT_WU_LSB) & (~(value)))

/*
 *  RTC_PCNT_WU_LSB_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_PCNT_WU_LSB_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_PCNT_WU_LSB_VAL)
#define RTC_PCNT_WU_LSB_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_PCNT_WU_LSB_VAL, (value))


/*
 *  RTC_PCNT_WU_MSB register macros
 ****************************************************************************************
 */
#define RTC_PCNT_WU_MSB_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_PCNT_WU_MSB))
#define RTC_PCNT_WU_MSB_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_PCNT_WU_MSB, (value))
#define RTC_PCNT_WU_MSB_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_PCNT_WU_MSB, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_PCNT_WU_MSB) | (value))
#define RTC_PCNT_WU_MSB_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_PCNT_WU_MSB, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_PCNT_WU_MSB) & (~(value)))

/*
 *  RTC_PCNT_WU_MSB_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_PCNT_WU_MSB_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_PCNT_WU_MSB_VAL)
#define RTC_PCNT_WU_MSB_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_PCNT_WU_MSB_VAL, (value))


/*
 *  RTC_RTC_PCNT_IRQ_STS register macros
 ****************************************************************************************
 */
#define RTC_RTC_PCNT_IRQ_STS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RTC_PCNT_IRQ_STS))

/*
 *  RTC_RTC_PCNT_IRQ_STATUS bit field macros
 ****************************************************************************************
 */
#define RTC_RTC_PCNT_IRQ_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RTC_PCNT_IRQ_STATUS)


/*
 *  RTC_RTC_PCNT_IRQ_MASK register macros
 ****************************************************************************************
 */
#define RTC_RTC_PCNT_IRQ_MASK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RTC_PCNT_IRQ_MASK))
#define RTC_RTC_PCNT_IRQ_MASK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RTC_PCNT_IRQ_MASK, (value))
#define RTC_RTC_PCNT_IRQ_MASK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RTC_PCNT_IRQ_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RTC_PCNT_IRQ_MASK) | (value))
#define RTC_RTC_PCNT_IRQ_MASK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RTC_PCNT_IRQ_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RTC_PCNT_IRQ_MASK) & (~(value)))

/*
 *  RTC_RTC_PCNT_IRQ_MASK_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_RTC_PCNT_IRQ_MASK_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RTC_PCNT_IRQ_MASK_VAL)
#define RTC_RTC_PCNT_IRQ_MASK_VAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RTC_PCNT_IRQ_MASK_VAL, 1)
#define RTC_RTC_PCNT_IRQ_MASK_VAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RTC_PCNT_IRQ_MASK_VAL, 0)


/*
 *  RTC_RTC_PCNT_IRQ_CLR register macros
 ****************************************************************************************
 */
#define RTC_RTC_PCNT_IRQ_CLR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RTC_PCNT_IRQ_CLR))
#define RTC_RTC_PCNT_IRQ_CLR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RTC_PCNT_IRQ_CLR, (value))
#define RTC_RTC_PCNT_IRQ_CLR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RTC_PCNT_IRQ_CLR, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RTC_PCNT_IRQ_CLR) | (value))
#define RTC_RTC_PCNT_IRQ_CLR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RTC_PCNT_IRQ_CLR, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RTC_PCNT_IRQ_CLR) & (~(value)))

/*
 *  RTC_RTC_PCNT_IRQ_CLEAR bit field macros
 ****************************************************************************************
 */
#define RTC_RTC_PCNT_IRQ_CLEAR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RTC_PCNT_IRQ_CLEAR)
#define RTC_RTC_PCNT_IRQ_CLEAR_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RTC_PCNT_IRQ_CLEAR, 1)
#define RTC_RTC_PCNT_IRQ_CLEAR_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RTC_PCNT_IRQ_CLEAR, 0)


/*
 *  RTC_ALARM_ENABLE register macros
 ****************************************************************************************
 */
#define RTC_ALARM_ENABLE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_ENABLE))
#define RTC_ALARM_ENABLE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_ENABLE, (value))
#define RTC_ALARM_ENABLE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_ENABLE, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_ENABLE) | (value))
#define RTC_ALARM_ENABLE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_ENABLE, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_ENABLE) & (~(value)))

/*
 *  RTC_ALARM_0_ENABLE bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_0_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_0_ENABLE)
#define RTC_ALARM_0_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_0_ENABLE, 1)
#define RTC_ALARM_0_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_0_ENABLE, 0)

/*
 *  RTC_ALARM_1_ENABLE bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_1_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_1_ENABLE)
#define RTC_ALARM_1_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_1_ENABLE, 1)
#define RTC_ALARM_1_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_1_ENABLE, 0)

/*
 *  RTC_ALARM_2_ENABLE bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_2_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_2_ENABLE)
#define RTC_ALARM_2_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_2_ENABLE, 1)
#define RTC_ALARM_2_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_2_ENABLE, 0)

/*
 *  RTC_ALARM_3_ENABLE bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_3_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_3_ENABLE)
#define RTC_ALARM_3_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_3_ENABLE, 1)
#define RTC_ALARM_3_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_3_ENABLE, 0)

/*
 *  RTC_ALARM_4_ENABLE bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_4_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_4_ENABLE)
#define RTC_ALARM_4_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_4_ENABLE, 1)
#define RTC_ALARM_4_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_4_ENABLE, 0)


/*
 *  RTC_ALARM_CORE_ENABLE register macros
 ****************************************************************************************
 */
#define RTC_ALARM_CORE_ENABLE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_CORE_ENABLE))
#define RTC_ALARM_CORE_ENABLE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_CORE_ENABLE, (value))
#define RTC_ALARM_CORE_ENABLE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_CORE_ENABLE, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_CORE_ENABLE) | (value))
#define RTC_ALARM_CORE_ENABLE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_CORE_ENABLE, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_CORE_ENABLE) & (~(value)))

/*
 *  RTC_ALARM_0_CORE_ENABLE bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_0_CORE_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_0_CORE_ENABLE)
#define RTC_ALARM_0_CORE_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_0_CORE_ENABLE, 1)
#define RTC_ALARM_0_CORE_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_0_CORE_ENABLE, 0)

/*
 *  RTC_ALARM_1_CORE_ENABLE bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_1_CORE_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_1_CORE_ENABLE)
#define RTC_ALARM_1_CORE_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_1_CORE_ENABLE, 1)
#define RTC_ALARM_1_CORE_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_1_CORE_ENABLE, 0)

/*
 *  RTC_ALARM_2_CORE_ENABLE bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_2_CORE_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_2_CORE_ENABLE)
#define RTC_ALARM_2_CORE_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_2_CORE_ENABLE, 1)
#define RTC_ALARM_2_CORE_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_2_CORE_ENABLE, 0)

/*
 *  RTC_ALARM_3_CORE_ENABLE bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_3_CORE_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_3_CORE_ENABLE)
#define RTC_ALARM_3_CORE_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_3_CORE_ENABLE, 1)
#define RTC_ALARM_3_CORE_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_3_CORE_ENABLE, 0)

/*
 *  RTC_ALARM_4_CORE_ENABLE bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_4_CORE_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_4_CORE_ENABLE)
#define RTC_ALARM_4_CORE_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_4_CORE_ENABLE, 1)
#define RTC_ALARM_4_CORE_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_4_CORE_ENABLE, 0)


/*
 *  RTC_ALARM_CONTROL register macros
 ****************************************************************************************
 */
#define RTC_ALARM_CONTROL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_CONTROL))
#define RTC_ALARM_CONTROL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_CONTROL, (value))
#define RTC_ALARM_CONTROL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_CONTROL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_CONTROL) | (value))
#define RTC_ALARM_CONTROL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_CONTROL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_CONTROL) & (~(value)))

/*
 *  RTC_ALARM_CTL bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_CTL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_CTL)
#define RTC_ALARM_CTL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_CTL, 1)
#define RTC_ALARM_CTL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_CTL, 0)


/*
 *  RTC_ALARM_POLARITY register macros
 ****************************************************************************************
 */
#define RTC_ALARM_POLARITY_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_POLARITY))
#define RTC_ALARM_POLARITY_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_POLARITY, (value))
#define RTC_ALARM_POLARITY_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_POLARITY, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_POLARITY) | (value))
#define RTC_ALARM_POLARITY_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_POLARITY, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_POLARITY) & (~(value)))

/*
 *  RTC_ALARM_0_POLARITY bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_0_POLARITY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_0_POLARITY)
#define RTC_ALARM_0_POLARITY_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_0_POLARITY, 1)
#define RTC_ALARM_0_POLARITY_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_0_POLARITY, 0)

/*
 *  RTC_ALARM_1_POLARITY bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_1_POLARITY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_1_POLARITY)
#define RTC_ALARM_1_POLARITY_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_1_POLARITY, 1)
#define RTC_ALARM_1_POLARITY_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_1_POLARITY, 0)

/*
 *  RTC_ALARM_2_POLARITY bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_2_POLARITY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_2_POLARITY)
#define RTC_ALARM_2_POLARITY_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_2_POLARITY, 1)
#define RTC_ALARM_2_POLARITY_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_2_POLARITY, 0)

/*
 *  RTC_ALARM_3_POLARITY bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_3_POLARITY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_3_POLARITY)
#define RTC_ALARM_3_POLARITY_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_3_POLARITY, 1)
#define RTC_ALARM_3_POLARITY_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_3_POLARITY, 0)

/*
 *  RTC_ALARM_4_POLARITY bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_4_POLARITY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_4_POLARITY)
#define RTC_ALARM_4_POLARITY_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_4_POLARITY, 1)
#define RTC_ALARM_4_POLARITY_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_4_POLARITY, 0)


/*
 *  RTC_ALARM_STATUS register macros
 ****************************************************************************************
 */
#define RTC_ALARM_STATUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_STATUS))

/*
 *  RTC_ALARM_0_STATUS bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_0_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_0_STATUS)

/*
 *  RTC_ALARM_1_STATUS bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_1_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_1_STATUS)

/*
 *  RTC_ALARM_2_STATUS bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_2_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_2_STATUS)

/*
 *  RTC_ALARM_3_STATUS bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_3_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_3_STATUS)

/*
 *  RTC_ALARM_4_STATUS bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_4_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_4_STATUS)


/*
 *  RTC_ALARM_IRQ_MASK register macros
 ****************************************************************************************
 */
#define RTC_ALARM_IRQ_MASK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_IRQ_MASK))
#define RTC_ALARM_IRQ_MASK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_IRQ_MASK, (value))
#define RTC_ALARM_IRQ_MASK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_IRQ_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_IRQ_MASK) | (value))
#define RTC_ALARM_IRQ_MASK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_IRQ_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_IRQ_MASK) & (~(value)))

/*
 *  RTC_ALARM_0_IRQ_MASK bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_0_IRQ_MASK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_0_IRQ_MASK)
#define RTC_ALARM_0_IRQ_MASK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_0_IRQ_MASK, 1)
#define RTC_ALARM_0_IRQ_MASK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_0_IRQ_MASK, 0)

/*
 *  RTC_ALARM_1_IRQ_MASK bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_1_IRQ_MASK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_1_IRQ_MASK)
#define RTC_ALARM_1_IRQ_MASK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_1_IRQ_MASK, 1)
#define RTC_ALARM_1_IRQ_MASK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_1_IRQ_MASK, 0)

/*
 *  RTC_ALARM_2_IRQ_MASK bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_2_IRQ_MASK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_2_IRQ_MASK)
#define RTC_ALARM_2_IRQ_MASK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_2_IRQ_MASK, 1)
#define RTC_ALARM_2_IRQ_MASK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_2_IRQ_MASK, 0)

/*
 *  RTC_ALARM_3_IRQ_MASK bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_3_IRQ_MASK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_3_IRQ_MASK)
#define RTC_ALARM_3_IRQ_MASK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_3_IRQ_MASK, 1)
#define RTC_ALARM_3_IRQ_MASK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_3_IRQ_MASK, 0)

/*
 *  RTC_ALARM_4_IRQ_MASK bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_4_IRQ_MASK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_4_IRQ_MASK)
#define RTC_ALARM_4_IRQ_MASK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_4_IRQ_MASK, 1)
#define RTC_ALARM_4_IRQ_MASK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_4_IRQ_MASK, 0)


/*
 *  RTC_ALARM_IRQ_CLEAR register macros
 ****************************************************************************************
 */
#define RTC_ALARM_IRQ_CLEAR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_IRQ_CLEAR))
#define RTC_ALARM_IRQ_CLEAR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_IRQ_CLEAR, (value))
#define RTC_ALARM_IRQ_CLEAR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_IRQ_CLEAR, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_IRQ_CLEAR) | (value))
#define RTC_ALARM_IRQ_CLEAR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_IRQ_CLEAR, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_IRQ_CLEAR) & (~(value)))

/*
 *  RTC_ALARM_0_IRQ_CLEAR bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_0_IRQ_CLEAR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_0_IRQ_CLEAR)
#define RTC_ALARM_0_IRQ_CLEAR_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_0_IRQ_CLEAR, 1)
#define RTC_ALARM_0_IRQ_CLEAR_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_0_IRQ_CLEAR, 0)

/*
 *  RTC_ALARM_1_IRQ_CLEAR bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_1_IRQ_CLEAR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_1_IRQ_CLEAR)
#define RTC_ALARM_1_IRQ_CLEAR_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_1_IRQ_CLEAR, 1)
#define RTC_ALARM_1_IRQ_CLEAR_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_1_IRQ_CLEAR, 0)

/*
 *  RTC_ALARM_2_IRQ_CLEAR bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_2_IRQ_CLEAR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_2_IRQ_CLEAR)
#define RTC_ALARM_2_IRQ_CLEAR_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_2_IRQ_CLEAR, 1)
#define RTC_ALARM_2_IRQ_CLEAR_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_2_IRQ_CLEAR, 0)

/*
 *  RTC_ALARM_3_IRQ_CLEAR bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_3_IRQ_CLEAR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_3_IRQ_CLEAR)
#define RTC_ALARM_3_IRQ_CLEAR_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_3_IRQ_CLEAR, 1)
#define RTC_ALARM_3_IRQ_CLEAR_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_3_IRQ_CLEAR, 0)

/*
 *  RTC_ALARM_4_IRQ_CLEAR bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_4_IRQ_CLEAR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_4_IRQ_CLEAR)
#define RTC_ALARM_4_IRQ_CLEAR_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_4_IRQ_CLEAR, 1)
#define RTC_ALARM_4_IRQ_CLEAR_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ALARM_4_IRQ_CLEAR, 0)


/*
 *  RTC_ALARM_TIMESTAMP0 register macros
 ****************************************************************************************
 */
#define RTC_ALARM_TIMESTAMP0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_TIMESTAMP0))

/*
 *  RTC_ALARM_TIME_STAMP0 bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_TIME_STAMP0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_TIME_STAMP0)


/*
 *  RTC_ALARM_TIMESTAMP1 register macros
 ****************************************************************************************
 */
#define RTC_ALARM_TIMESTAMP1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_TIMESTAMP1))

/*
 *  RTC_ALARM_TIME_STAMP1 bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_TIME_STAMP1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_TIME_STAMP1)


/*
 *  RTC_ALARM_TIMESTAMP2 register macros
 ****************************************************************************************
 */
#define RTC_ALARM_TIMESTAMP2_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_TIMESTAMP2))

/*
 *  RTC_ALARM_TIME_STAMP2 bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_TIME_STAMP2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_TIME_STAMP2)


/*
 *  RTC_ALARM_TIMESTAMP3 register macros
 ****************************************************************************************
 */
#define RTC_ALARM_TIMESTAMP3_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_TIMESTAMP3))

/*
 *  RTC_ALARM_TIME_STAMP3 bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_TIME_STAMP3_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_TIME_STAMP3)


/*
 *  RTC_ALARM_TIMESTAMP4 register macros
 ****************************************************************************************
 */
#define RTC_ALARM_TIMESTAMP4_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ALARM_TIMESTAMP4))

/*
 *  RTC_ALARM_TIME_STAMP4 bit field macros
 ****************************************************************************************
 */
#define RTC_ALARM_TIME_STAMP4_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ALARM_TIME_STAMP4)


/*
 *  RTC_SETTLE_LP_RC register macros
 ****************************************************************************************
 */
#define RTC_SETTLE_LP_RC_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_LP_RC))
#define RTC_SETTLE_LP_RC_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_LP_RC, (value))
#define RTC_SETTLE_LP_RC_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_LP_RC, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_LP_RC) | (value))
#define RTC_SETTLE_LP_RC_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_LP_RC, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_LP_RC) & (~(value)))

/*
 *  RTC_LP_RC_SETTLE bit field macros
 ****************************************************************************************
 */
#define RTC_LP_RC_SETTLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LP_RC_SETTLE)
#define RTC_LP_RC_SETTLE_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_LP_RC_SETTLE, (value))


/*
 *  RTC_SETTLE_LP_XTAL register macros
 ****************************************************************************************
 */
#define RTC_SETTLE_LP_XTAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_LP_XTAL))
#define RTC_SETTLE_LP_XTAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_LP_XTAL, (value))
#define RTC_SETTLE_LP_XTAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_LP_XTAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_LP_XTAL) | (value))
#define RTC_SETTLE_LP_XTAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_LP_XTAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_LP_XTAL) & (~(value)))

/*
 *  RTC_LP_XTAL_SETTLE bit field macros
 ****************************************************************************************
 */
#define RTC_LP_XTAL_SETTLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LP_XTAL_SETTLE)
#define RTC_LP_XTAL_SETTLE_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_LP_XTAL_SETTLE, (value))


/*
 *  RTC_SETTLE_HS_RC register macros
 ****************************************************************************************
 */
#define RTC_SETTLE_HS_RC_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_HS_RC))
#define RTC_SETTLE_HS_RC_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_HS_RC, (value))
#define RTC_SETTLE_HS_RC_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_HS_RC, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_HS_RC) | (value))
#define RTC_SETTLE_HS_RC_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_HS_RC, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_HS_RC) & (~(value)))

/*
 *  RTC_HS_RC_SETTLE bit field macros
 ****************************************************************************************
 */
#define RTC_HS_RC_SETTLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_HS_RC_SETTLE)
#define RTC_HS_RC_SETTLE_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_HS_RC_SETTLE, (value))


/*
 *  RTC_SETTLE_HS_XTAL register macros
 ****************************************************************************************
 */
#define RTC_SETTLE_HS_XTAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_HS_XTAL))
#define RTC_SETTLE_HS_XTAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_HS_XTAL, (value))
#define RTC_SETTLE_HS_XTAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_HS_XTAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_HS_XTAL) | (value))
#define RTC_SETTLE_HS_XTAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_HS_XTAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_HS_XTAL) & (~(value)))

/*
 *  RTC_HS_XTAL_SETTLE bit field macros
 ****************************************************************************************
 */
#define RTC_HS_XTAL_SETTLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_HS_XTAL_SETTLE)
#define RTC_HS_XTAL_SETTLE_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_HS_XTAL_SETTLE, (value))


/*
 *  RTC_SETTLE_PLL register macros
 ****************************************************************************************
 */
#define RTC_SETTLE_PLL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_PLL))
#define RTC_SETTLE_PLL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_PLL, (value))
#define RTC_SETTLE_PLL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_PLL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_PLL) | (value))
#define RTC_SETTLE_PLL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_PLL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SETTLE_PLL) & (~(value)))

/*
 *  RTC_PLL_SETTLE bit field macros
 ****************************************************************************************
 */
#define RTC_PLL_SETTLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_PLL_SETTLE)
#define RTC_PLL_SETTLE_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_PLL_SETTLE, (value))


/*
 *  RTC_CLK_EN_STATUS register macros
 ****************************************************************************************
 */
#define RTC_CLK_EN_STATUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CLK_EN_STATUS))

/*
 *  RTC_CLK_EN_STATUS_LP_RC_STABLE bit field macros
 ****************************************************************************************
 */
#define RTC_CLK_EN_STATUS_LP_RC_STABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CLK_EN_STATUS_LP_RC_STABLE)

/*
 *  RTC_CLK_EN_STATUS_LP_XTAL_STABLE bit field macros
 ****************************************************************************************
 */
#define RTC_CLK_EN_STATUS_LP_XTAL_STABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CLK_EN_STATUS_LP_XTAL_STABLE)


/*
 *  RTC_CLK_SEL_STATUS register macros
 ****************************************************************************************
 */
#define RTC_CLK_SEL_STATUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CLK_SEL_STATUS))
#define RTC_CLK_SEL_STATUS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CLK_SEL_STATUS, (value))
#define RTC_CLK_SEL_STATUS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CLK_SEL_STATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CLK_SEL_STATUS) | (value))
#define RTC_CLK_SEL_STATUS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CLK_SEL_STATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CLK_SEL_STATUS) & (~(value)))

/*
 *  RTC_CLOCK_SEL_STATUS bit field macros
 ****************************************************************************************
 */
#define RTC_CLOCK_SEL_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CLOCK_SEL_STATUS)
#define RTC_CLOCK_SEL_STATUS_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CLOCK_SEL_STATUS, (value))


/*
 *  RTC_ACM3_CLK_SEL register macros
 ****************************************************************************************
 */
#define RTC_ACM3_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ACM3_CLK_SEL))
#define RTC_ACM3_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ACM3_CLK_SEL, (value))
#define RTC_ACM3_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ACM3_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ACM3_CLK_SEL) | (value))
#define RTC_ACM3_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ACM3_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ACM3_CLK_SEL) & (~(value)))

/*
 *  RTC_ACM3_CLK_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_ACM3_CLK_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ACM3_CLK_SEL_VAL)
#define RTC_ACM3_CLK_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_ACM3_CLK_SEL_VAL, (value))


/*
 *  RTC_WCM3_CLK_SEL register macros
 ****************************************************************************************
 */
#define RTC_WCM3_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_WCM3_CLK_SEL))
#define RTC_WCM3_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_WCM3_CLK_SEL, (value))
#define RTC_WCM3_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_WCM3_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_WCM3_CLK_SEL) | (value))
#define RTC_WCM3_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_WCM3_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_WCM3_CLK_SEL) & (~(value)))

/*
 *  RTC_WCM3_CLK_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_WCM3_CLK_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_WCM3_CLK_SEL_VAL)
#define RTC_WCM3_CLK_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_WCM3_CLK_SEL_VAL, (value))


/*
 *  RTC_RBUS_CLK_SEL register macros
 ****************************************************************************************
 */
#define RTC_RBUS_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RBUS_CLK_SEL))
#define RTC_RBUS_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RBUS_CLK_SEL, (value))
#define RTC_RBUS_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RBUS_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RBUS_CLK_SEL) | (value))
#define RTC_RBUS_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RBUS_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RBUS_CLK_SEL) & (~(value)))

/*
 *  RTC_RBUS_CLOCK_SEL bit field macros
 ****************************************************************************************
 */
#define RTC_RBUS_CLOCK_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RBUS_CLOCK_SEL)
#define RTC_RBUS_CLOCK_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_RBUS_CLOCK_SEL, (value))


/*
 *  RTC_WCM3_CLK_EN register macros
 ****************************************************************************************
 */
#define RTC_WCM3_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_WCM3_CLK_EN))
#define RTC_WCM3_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_WCM3_CLK_EN, (value))
#define RTC_WCM3_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_WCM3_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_WCM3_CLK_EN) | (value))
#define RTC_WCM3_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_WCM3_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_WCM3_CLK_EN) & (~(value)))

/*
 *  RTC_WCM3_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define RTC_WCM3_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_WCM3_CLK_ENABLE)
#define RTC_WCM3_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_WCM3_CLK_ENABLE, 1)
#define RTC_WCM3_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_WCM3_CLK_ENABLE, 0)


/*
 *  RTC_CLK_RTC_DIV register macros
 ****************************************************************************************
 */
#define RTC_CLK_RTC_DIV_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CLK_RTC_DIV))
#define RTC_CLK_RTC_DIV_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CLK_RTC_DIV, (value))
#define RTC_CLK_RTC_DIV_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CLK_RTC_DIV, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CLK_RTC_DIV) | (value))
#define RTC_CLK_RTC_DIV_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CLK_RTC_DIV, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CLK_RTC_DIV) & (~(value)))

/*
 *  RTC_CLK_RTC_DIV_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_CLK_RTC_DIV_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CLK_RTC_DIV_VAL)
#define RTC_CLK_RTC_DIV_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CLK_RTC_DIV_VAL, (value))


/*
 *  RTC_RRH_REQ_RST register macros
 ****************************************************************************************
 */
#define RTC_RRH_REQ_RST_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_REQ_RST))
#define RTC_RRH_REQ_RST_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_REQ_RST, (value))
#define RTC_RRH_REQ_RST_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_REQ_RST, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_REQ_RST) | (value))
#define RTC_RRH_REQ_RST_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_REQ_RST, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_REQ_RST) & (~(value)))

/*
 *  RTC_RRH_REQ_RST_FWAPP bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_REQ_RST_FWAPP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_REQ_RST_FWAPP)
#define RTC_RRH_REQ_RST_FWAPP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_REQ_RST_FWAPP, 1)
#define RTC_RRH_REQ_RST_FWAPP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_REQ_RST_FWAPP, 0)

/*
 *  RTC_RRH_REQ_RST_FWWLAN bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_REQ_RST_FWWLAN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_REQ_RST_FWWLAN)
#define RTC_RRH_REQ_RST_FWWLAN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_REQ_RST_FWWLAN, 1)
#define RTC_RRH_REQ_RST_FWWLAN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_REQ_RST_FWWLAN, 0)

/*
 *  RTC_RRH_REQ_RST_FWCRYPTO bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_REQ_RST_FWCRYPTO_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_REQ_RST_FWCRYPTO)
#define RTC_RRH_REQ_RST_FWCRYPTO_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_REQ_RST_FWCRYPTO, 1)
#define RTC_RRH_REQ_RST_FWCRYPTO_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_REQ_RST_FWCRYPTO, 0)

/*
 *  RTC_RRH_REQ_RST_FWPOR bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_REQ_RST_FWPOR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_REQ_RST_FWPOR)
#define RTC_RRH_REQ_RST_FWPOR_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_REQ_RST_FWPOR, 1)
#define RTC_RRH_REQ_RST_FWPOR_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_REQ_RST_FWPOR, 0)


/*
 *  RTC_RRH_FWAPP_STAT register macros
 ****************************************************************************************
 */
#define RTC_RRH_FWAPP_STAT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWAPP_STAT))
#define RTC_RRH_FWAPP_STAT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWAPP_STAT, (value))
#define RTC_RRH_FWAPP_STAT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWAPP_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWAPP_STAT) | (value))
#define RTC_RRH_FWAPP_STAT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWAPP_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWAPP_STAT) & (~(value)))

/*
 *  RTC_RRH_FWAPP_STATUS bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_FWAPP_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_FWAPP_STATUS)
#define RTC_RRH_FWAPP_STATUS_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_FWAPP_STATUS, 1)
#define RTC_RRH_FWAPP_STATUS_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_FWAPP_STATUS, 0)


/*
 *  RTC_RRH_FWAPP_CTL register macros
 ****************************************************************************************
 */
#define RTC_RRH_FWAPP_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWAPP_CTL))
#define RTC_RRH_FWAPP_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWAPP_CTL, (value))
#define RTC_RRH_FWAPP_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWAPP_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWAPP_CTL) | (value))
#define RTC_RRH_FWAPP_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWAPP_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWAPP_CTL) & (~(value)))

/*
 *  RTC_RRH_FWAPP_CTL_REQ bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_FWAPP_CTL_REQ_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_FWAPP_CTL_REQ)
#define RTC_RRH_FWAPP_CTL_REQ_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_FWAPP_CTL_REQ, 1)
#define RTC_RRH_FWAPP_CTL_REQ_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_FWAPP_CTL_REQ, 0)

/*
 *  RTC_RRH_FWAPP_CTL_POR bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_FWAPP_CTL_COND_GET(addr) \
		 GET_WORD_BITFIELD_N(addr, RTC_RRH_FWAPP_CTL_COND)
#define RTC_RRH_FWAPP_CTL_COND_SET(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_FWAPP_CTL_COND, 1)
#define RTC_RRH_FWAPP_CTL_COND_CLEAR(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_FWAPP_CTL_COND, 0)


/*
 *  RTC_RRH_FWWLAN_STAT register macros
 ****************************************************************************************
 */
#define RTC_RRH_FWWLAN_STAT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWWLAN_STAT))
#define RTC_RRH_FWWLAN_STAT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWWLAN_STAT, (value))
#define RTC_RRH_FWWLAN_STAT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWWLAN_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWWLAN_STAT) | (value))
#define RTC_RRH_FWWLAN_STAT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWWLAN_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWWLAN_STAT) & (~(value)))

/*
 *  RTC_RRH_FWWLAN_STATUS bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_FWWLAN_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_FWWLAN_STATUS)
#define RTC_RRH_FWWLAN_STATUS_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_FWWLAN_STATUS, 1)
#define RTC_RRH_FWWLAN_STATUS_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_FWWLAN_STATUS, 0)


/*
 *  RTC_RRH_FWWLAN_CTL register macros
 ****************************************************************************************
 */
#define RTC_RRH_FWWLAN_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWWLAN_CTL))
#define RTC_RRH_FWWLAN_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWWLAN_CTL, (value))
#define RTC_RRH_FWWLAN_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWWLAN_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWWLAN_CTL) | (value))
#define RTC_RRH_FWWLAN_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWWLAN_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWWLAN_CTL) & (~(value)))

/*
 *  RTC_RRH_FWWLAN_CTL_REQ bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_FWWLAN_CTL_REQ_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_FWWLAN_CTL_REQ)
#define RTC_RRH_FWWLAN_CTL_REQ_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_FWWLAN_CTL_REQ, 1)
#define RTC_RRH_FWWLAN_CTL_REQ_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_FWWLAN_CTL_REQ, 0)

/*
 *  RTC_RRH_FWWLAN_CTL_POR bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_FWWLAN_CTL_COND_GET(addr) \
		 GET_WORD_BITFIELD_N(addr, RTC_RRH_FWWLAN_CTL_COND)
#define RTC_RRH_FWWLAN_CTL_COND_SET(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_FWWLAN_CTL_COND, 1)
#define RTC_RRH_FWWLAN_CTL_COND_CLEAR(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_FWWLAN_CTL_COND, 0)


/*
 *  RTC_RRH_FWCRYPTO_STAT register macros
 ****************************************************************************************
 */
#define RTC_RRH_FWCRYPTO_STAT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWCRYPTO_STAT))
#define RTC_RRH_FWCRYPTO_STAT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWCRYPTO_STAT, (value))
#define RTC_RRH_FWCRYPTO_STAT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWCRYPTO_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWCRYPTO_STAT) | (value))
#define RTC_RRH_FWCRYPTO_STAT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWCRYPTO_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWCRYPTO_STAT) & (~(value)))

/*
 *  RTC_RRH_FWCRYPTO_STATUS bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_FWCRYPTO_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_FWCRYPTO_STATUS)
#define RTC_RRH_FWCRYPTO_STATUS_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_FWCRYPTO_STATUS, 1)
#define RTC_RRH_FWCRYPTO_STATUS_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_FWCRYPTO_STATUS, 0)


/*
 *  RTC_RRH_FWCRYPTO_CTL register macros
 ****************************************************************************************
 */
#define RTC_RRH_FWCRYPTO_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWCRYPTO_CTL))
#define RTC_RRH_FWCRYPTO_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWCRYPTO_CTL, (value))
#define RTC_RRH_FWCRYPTO_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWCRYPTO_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWCRYPTO_CTL) | (value))
#define RTC_RRH_FWCRYPTO_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWCRYPTO_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWCRYPTO_CTL) & (~(value)))

/*
 *  RTC_RRH_FWCRYPTO_CTL_REQ bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_FWCRYPTO_CTL_REQ_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_FWCRYPTO_CTL_REQ)
#define RTC_RRH_FWCRYPTO_CTL_REQ_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_FWCRYPTO_CTL_REQ, 1)
#define RTC_RRH_FWCRYPTO_CTL_REQ_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_FWCRYPTO_CTL_REQ, 0)

/*
 *  RTC_RRH_FWCRYPTO_CTL_POR bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_FWCRYPTO_CTL_COND_GET(addr) \
		 GET_WORD_BITFIELD_N(addr, RTC_RRH_FWCRYPTO_CTL_COND)
#define RTC_RRH_FWCRYPTO_CTL_COND_SET(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_FWCRYPTO_CTL_COND, 1)
#define RTC_RRH_FWCRYPTO_CTL_COND_CLEAR(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_FWCRYPTO_CTL_COND, 0)


/*
 *  RTC_RRH_FWPOR_STAT register macros
 ****************************************************************************************
 */
#define RTC_RRH_FWPOR_STAT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWPOR_STAT))
#define RTC_RRH_FWPOR_STAT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWPOR_STAT, (value))
#define RTC_RRH_FWPOR_STAT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWPOR_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWPOR_STAT) | (value))
#define RTC_RRH_FWPOR_STAT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWPOR_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWPOR_STAT) & (~(value)))

/*
 *  RTC_RRH_FWPOR_STATUS bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_FWPOR_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_FWPOR_STATUS)
#define RTC_RRH_FWPOR_STATUS_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_FWPOR_STATUS, 1)
#define RTC_RRH_FWPOR_STATUS_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_FWPOR_STATUS, 0)


/*
 *  RTC_RRH_FWPOR_CTL register macros
 ****************************************************************************************
 */
#define RTC_RRH_FWPOR_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWPOR_CTL))
#define RTC_RRH_FWPOR_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWPOR_CTL, (value))
#define RTC_RRH_FWPOR_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWPOR_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWPOR_CTL) | (value))
#define RTC_RRH_FWPOR_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWPOR_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_FWPOR_CTL) & (~(value)))

/*
 *  RTC_RRH_FWPOR_CTL_REQ bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_FWPOR_CTL_REQ_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_FWPOR_CTL_REQ)
#define RTC_RRH_FWPOR_CTL_REQ_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_FWPOR_CTL_REQ, 1)
#define RTC_RRH_FWPOR_CTL_REQ_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_FWPOR_CTL_REQ, 0)

/*
 *  RTC_RRH_FWPOR_CTL_POR bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_FWPOR_CTL_COND_GET(addr) \
		 GET_WORD_BITFIELD_N(addr, RTC_RRH_FWPOR_CTL_COND)
#define RTC_RRH_FWPOR_CTL_COND_SET(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_FWPOR_CTL_COND, 1)
#define RTC_RRH_FWPOR_CTL_COND_CLEAR(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_FWPOR_CTL_COND, 0)


/*
 *  RTC_RRH_EXT_RST_STAT register macros
 ****************************************************************************************
 */
#define RTC_RRH_EXT_RST_STAT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_EXT_RST_STAT))
#define RTC_RRH_EXT_RST_STAT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_EXT_RST_STAT, (value))
#define RTC_RRH_EXT_RST_STAT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_EXT_RST_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_EXT_RST_STAT) | (value))
#define RTC_RRH_EXT_RST_STAT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_EXT_RST_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_EXT_RST_STAT) & (~(value)))

/*
 *  RTC_RRH_EXT_RST_STATUS bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_EXT_RST_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_EXT_RST_STATUS)
#define RTC_RRH_EXT_RST_STATUS_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_EXT_RST_STATUS, 1)
#define RTC_RRH_EXT_RST_STATUS_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_EXT_RST_STATUS, 0)


/*
 *  RTC_RRH_EXT_RST_CTL register macros
 ****************************************************************************************
 */
#define RTC_RRH_EXT_RST_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_EXT_RST_CTL))
#define RTC_RRH_EXT_RST_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_EXT_RST_CTL, (value))
#define RTC_RRH_EXT_RST_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_EXT_RST_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_EXT_RST_CTL) | (value))
#define RTC_RRH_EXT_RST_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_EXT_RST_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_EXT_RST_CTL) & (~(value)))

/*
 *  RTC_RRH_EXT_RST_CTL_REQ bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_EXT_RST_CTL_REQ_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_EXT_RST_CTL_REQ)
#define RTC_RRH_EXT_RST_CTL_REQ_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_EXT_RST_CTL_REQ, 1)
#define RTC_RRH_EXT_RST_CTL_REQ_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_EXT_RST_CTL_REQ, 0)

/*
 *  RTC_RRH_EXT_RST_CTL_POR bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_EXT_RST_CTL_COND_GET(addr) \
		 GET_WORD_BITFIELD_N(addr, RTC_RRH_EXT_RST_CTL_COND)
#define RTC_RRH_EXT_RST_CTL_COND_SET(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_EXT_RST_CTL_COND, 1)
#define RTC_RRH_EXT_RST_CTL_COND_CLEAR(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_EXT_RST_CTL_COND, 0)


/*
 *  RTC_RRH_ACM3AIRC_STAT register macros
 ****************************************************************************************
 */
#define RTC_RRH_ACM3AIRC_STAT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_ACM3AIRC_STAT))
#define RTC_RRH_ACM3AIRC_STAT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_ACM3AIRC_STAT, (value))
#define RTC_RRH_ACM3AIRC_STAT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_ACM3AIRC_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_ACM3AIRC_STAT) | (value))
#define RTC_RRH_ACM3AIRC_STAT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_ACM3AIRC_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_ACM3AIRC_STAT) & (~(value)))

/*
 *  RTC_RRH_ACM3AIRC_STATUS bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_ACM3AIRC_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_ACM3AIRC_STATUS)
#define RTC_RRH_ACM3AIRC_STATUS_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_ACM3AIRC_STATUS, 1)
#define RTC_RRH_ACM3AIRC_STATUS_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_ACM3AIRC_STATUS, 0)


/*
 *  RTC_RRH_ACM3AIRC_CTL register macros
 ****************************************************************************************
 */
#define RTC_RRH_ACM3AIRC_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_ACM3AIRC_CTL))
#define RTC_RRH_ACM3AIRC_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_ACM3AIRC_CTL, (value))
#define RTC_RRH_ACM3AIRC_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_ACM3AIRC_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_ACM3AIRC_CTL) | (value))
#define RTC_RRH_ACM3AIRC_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_ACM3AIRC_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_ACM3AIRC_CTL) & (~(value)))

/*
 *  RTC_RRH_ACM3AIRC_CTL_REQ bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_ACM3AIRC_CTL_REQ_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_ACM3AIRC_CTL_REQ)
#define RTC_RRH_ACM3AIRC_CTL_REQ_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_ACM3AIRC_CTL_REQ, 1)
#define RTC_RRH_ACM3AIRC_CTL_REQ_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_ACM3AIRC_CTL_REQ, 0)

/*
 *  RTC_RRH_ACM3AIRC_CTL_POR bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_ACM3AIRC_CTL_COND_GET(addr) \
		 GET_WORD_BITFIELD_N(addr, RTC_RRH_ACM3AIRC_CTL_COND)
#define RTC_RRH_ACM3AIRC_CTL_COND_SET(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_ACM3AIRC_CTL_COND, 1)
#define RTC_RRH_ACM3AIRC_CTL_COND_CLEAR(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_ACM3AIRC_CTL_COND, 0)


/*
 *  RTC_RRH_WCM3AIRC_STAT register macros
 ****************************************************************************************
 */
#define RTC_RRH_WCM3AIRC_STAT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_WCM3AIRC_STAT))
#define RTC_RRH_WCM3AIRC_STAT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_WCM3AIRC_STAT, (value))
#define RTC_RRH_WCM3AIRC_STAT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_WCM3AIRC_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_WCM3AIRC_STAT) | (value))
#define RTC_RRH_WCM3AIRC_STAT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_WCM3AIRC_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_WCM3AIRC_STAT) & (~(value)))

/*
 *  RTC_RRH_WCM3AIRC_STATUS bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_WCM3AIRC_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_WCM3AIRC_STATUS)
#define RTC_RRH_WCM3AIRC_STATUS_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_WCM3AIRC_STATUS, 1)
#define RTC_RRH_WCM3AIRC_STATUS_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_WCM3AIRC_STATUS, 0)


/*
 *  RTC_RRH_WCM3AIRC_CTL register macros
 ****************************************************************************************
 */
#define RTC_RRH_WCM3AIRC_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_WCM3AIRC_CTL))
#define RTC_RRH_WCM3AIRC_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_WCM3AIRC_CTL, (value))
#define RTC_RRH_WCM3AIRC_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_WCM3AIRC_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_WCM3AIRC_CTL) | (value))
#define RTC_RRH_WCM3AIRC_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_WCM3AIRC_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_WCM3AIRC_CTL) & (~(value)))

/*
 *  RTC_RRH_WCM3AIRC_CTL_REQ bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_WCM3AIRC_CTL_REQ_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_WCM3AIRC_CTL_REQ)
#define RTC_RRH_WCM3AIRC_CTL_REQ_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_WCM3AIRC_CTL_REQ, 1)
#define RTC_RRH_WCM3AIRC_CTL_REQ_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_WCM3AIRC_CTL_REQ, 0)

/*
 *  RTC_RRH_WCM3AIRC_CTL_POR bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_WCM3AIRC_CTL_COND_GET(addr) \
		 GET_WORD_BITFIELD_N(addr, RTC_RRH_WCM3AIRC_CTL_COND)
#define RTC_RRH_WCM3AIRC_CTL_COND_SET(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_WCM3AIRC_CTL_COND, 1)
#define RTC_RRH_WCM3AIRC_CTL_COND_CLEAR(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_WCM3AIRC_CTL_COND, 0)


/*
 *  RTC_RRH_AWDOG_STAT register macros
 ****************************************************************************************
 */
#define RTC_RRH_AWDOG_STAT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_AWDOG_STAT))
#define RTC_RRH_AWDOG_STAT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_AWDOG_STAT, (value))
#define RTC_RRH_AWDOG_STAT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_AWDOG_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_AWDOG_STAT) | (value))
#define RTC_RRH_AWDOG_STAT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_AWDOG_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_AWDOG_STAT) & (~(value)))

/*
 *  RTC_RRH_AWDOG_STATUS bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_AWDOG_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_AWDOG_STATUS)
#define RTC_RRH_AWDOG_STATUS_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_AWDOG_STATUS, 1)
#define RTC_RRH_AWDOG_STATUS_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_AWDOG_STATUS, 0)


/*
 *  RTC_RRH_AWDOG_CTL register macros
 ****************************************************************************************
 */
#define RTC_RRH_AWDOG_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_AWDOG_CTL))
#define RTC_RRH_AWDOG_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_AWDOG_CTL, (value))
#define RTC_RRH_AWDOG_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_AWDOG_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_AWDOG_CTL) | (value))
#define RTC_RRH_AWDOG_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_AWDOG_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_AWDOG_CTL) & (~(value)))

/*
 *  RTC_RRH_AWDOG_CTL_REQ bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_AWDOG_CTL_REQ_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_AWDOG_CTL_REQ)
#define RTC_RRH_AWDOG_CTL_REQ_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_AWDOG_CTL_REQ, 1)
#define RTC_RRH_AWDOG_CTL_REQ_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_AWDOG_CTL_REQ, 0)

/*
 *  RTC_RRH_AWDOG_CTL_POR bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_AWDOG_CTL_COND_GET(addr) \
		 GET_WORD_BITFIELD_N(addr, RTC_RRH_AWDOG_CTL_COND)
#define RTC_RRH_AWDOG_CTL_COND_SET(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_AWDOG_CTL_COND, 1)
#define RTC_RRH_AWDOG_CTL_COND_CLEAR(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_AWDOG_CTL_COND, 0)


/*
 *  RTC_RRH_CBO_STAT register macros
 ****************************************************************************************
 */
#define RTC_RRH_CBO_STAT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_CBO_STAT))
#define RTC_RRH_CBO_STAT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_CBO_STAT, (value))
#define RTC_RRH_CBO_STAT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_CBO_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_CBO_STAT) | (value))
#define RTC_RRH_CBO_STAT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_CBO_STAT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_CBO_STAT) & (~(value)))

/*
 *  RTC_RRH_CBO_STATUS bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_CBO_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_CBO_STATUS)
#define RTC_RRH_CBO_STATUS_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_CBO_STATUS, 1)
#define RTC_RRH_CBO_STATUS_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_CBO_STATUS, 0)


/*
 *  RTC_RRH_CBO_CTL register macros
 ****************************************************************************************
 */
#define RTC_RRH_CBO_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_CBO_CTL))
#define RTC_RRH_CBO_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_CBO_CTL, (value))
#define RTC_RRH_CBO_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_CBO_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_CBO_CTL) | (value))
#define RTC_RRH_CBO_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_CBO_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_RRH_CBO_CTL) & (~(value)))

/*
 *  RTC_RRH_CBO_CTL_REQ bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_CBO_CTL_REQ_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RRH_CBO_CTL_REQ)
#define RTC_RRH_CBO_CTL_REQ_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_CBO_CTL_REQ, 1)
#define RTC_RRH_CBO_CTL_REQ_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RRH_CBO_CTL_REQ, 0)

/*
 *  RTC_RRH_CBO_CTL_POR bit field macros
 ****************************************************************************************
 */
#define RTC_RRH_CBO_CTL_COND_GET(addr) \
		 GET_WORD_BITFIELD_N(addr, RTC_RRH_CBO_CTL_COND)
#define RTC_RRH_CBO_CTL_COND_SET(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_CBO_CTL_COND, 1)
#define RTC_RRH_CBO_CTL_COND_CLEAR(addr) \
		 SET_WORD_BITFIELD_N(addr, RTC_RRH_CBO_CTL_COND, 0)


/*
 *  RTC_LDO_STBY_0 register macros
 ****************************************************************************************
 */
#define RTC_LDO_STBY_0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_0))
#define RTC_LDO_STBY_0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_0, (value))
#define RTC_LDO_STBY_0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_0) | (value))
#define RTC_LDO_STBY_0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_0) & (~(value)))

/*
 *  RTC_LDO_STBY_0_IN_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_STBY_0_IN_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_STBY_0_IN_DIG)
#define RTC_LDO_STBY_0_IN_DIG_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_STBY_0_IN_DIG, 1)
#define RTC_LDO_STBY_0_IN_DIG_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_STBY_0_IN_DIG, 0)


/*
 *  RTC_LDO_STBY_1 register macros
 ****************************************************************************************
 */
#define RTC_LDO_STBY_1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_1))
#define RTC_LDO_STBY_1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_1, (value))
#define RTC_LDO_STBY_1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_1) | (value))
#define RTC_LDO_STBY_1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_1) & (~(value)))

/*
 *  RTC_LDO_STBY_1_IN_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_STBY_1_IN_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_STBY_1_IN_DIG)
#define RTC_LDO_STBY_1_IN_DIG_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_STBY_1_IN_DIG, 1)
#define RTC_LDO_STBY_1_IN_DIG_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_STBY_1_IN_DIG, 0)


/*
 *  RTC_LDO_CTRL_18100_0 register macros
 ****************************************************************************************
 */
#define RTC_LDO_CTRL_18100_0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_18100_0))
#define RTC_LDO_CTRL_18100_0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_18100_0, (value))
#define RTC_LDO_CTRL_18100_0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_18100_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_18100_0) | (value))
#define RTC_LDO_CTRL_18100_0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_18100_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_18100_0) & (~(value)))

/*
 *  RTC_LDO_CTRL_18100_0_OUT_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_CTRL_18100_0_OUT_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_CTRL_18100_0_OUT_DIG)
#define RTC_LDO_CTRL_18100_0_OUT_DIG_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_CTRL_18100_0_OUT_DIG, 1)
#define RTC_LDO_CTRL_18100_0_OUT_DIG_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_CTRL_18100_0_OUT_DIG, 0)


/*
 *  RTC_LDO_CTRL_18100_1 register macros
 ****************************************************************************************
 */
#define RTC_LDO_CTRL_18100_1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_18100_1))
#define RTC_LDO_CTRL_18100_1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_18100_1, (value))
#define RTC_LDO_CTRL_18100_1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_18100_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_18100_1) | (value))
#define RTC_LDO_CTRL_18100_1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_18100_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_18100_1) & (~(value)))

/*
 *  RTC_LDO_CTRL_18100_1_OUT_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_CTRL_18100_1_OUT_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_CTRL_18100_1_OUT_DIG)
#define RTC_LDO_CTRL_18100_1_OUT_DIG_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_CTRL_18100_1_OUT_DIG, (value))


/*
 *  RTC_LDO_SEL_CTRL__0 register macros
 ****************************************************************************************
 */
#define RTC_LDO_SEL_CTRL__0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL__0))
#define RTC_LDO_SEL_CTRL__0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL__0, (value))
#define RTC_LDO_SEL_CTRL__0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL__0, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL__0) | (value))
#define RTC_LDO_SEL_CTRL__0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL__0, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL__0) & (~(value)))

/*
 *  RTC_LDO_SEL_CTRL__0_OUT_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_SEL_CTRL__0_OUT_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_CTRL__0_OUT_DIG)
#define RTC_LDO_SEL_CTRL__0_OUT_DIG_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_CTRL__0_OUT_DIG, 1)
#define RTC_LDO_SEL_CTRL__0_OUT_DIG_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_CTRL__0_OUT_DIG, 0)


/*
 *  RTC_LDO_SEL_CTRL__1 register macros
 ****************************************************************************************
 */
#define RTC_LDO_SEL_CTRL__1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL__1))
#define RTC_LDO_SEL_CTRL__1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL__1, (value))
#define RTC_LDO_SEL_CTRL__1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL__1, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL__1) | (value))
#define RTC_LDO_SEL_CTRL__1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL__1, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL__1) & (~(value)))

/*
 *  RTC_LDO_SEL_CTRL__1_OUT_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_SEL_CTRL__1_OUT_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_CTRL__1_OUT_DIG)
#define RTC_LDO_SEL_CTRL__1_OUT_DIG_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_CTRL__1_OUT_DIG, 1)
#define RTC_LDO_SEL_CTRL__1_OUT_DIG_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_CTRL__1_OUT_DIG, 0)


/*
 *  RTC_LDO_FORCE_ON__0 register macros
 ****************************************************************************************
 */
#define RTC_LDO_FORCE_ON__0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON__0))
#define RTC_LDO_FORCE_ON__0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON__0, (value))
#define RTC_LDO_FORCE_ON__0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON__0, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON__0) | (value))
#define RTC_LDO_FORCE_ON__0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON__0, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON__0) & (~(value)))

/*
 *  RTC_LDO_FORCE_ON__0_ON_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_FORCE_ON__0_ON_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_FORCE_ON__0_ON_DIG)
#define RTC_LDO_FORCE_ON__0_ON_DIG_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_FORCE_ON__0_ON_DIG, 1)
#define RTC_LDO_FORCE_ON__0_ON_DIG_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_FORCE_ON__0_ON_DIG, 0)


/*
 *  RTC_LDO_FORCE_ON__1 register macros
 ****************************************************************************************
 */
#define RTC_LDO_FORCE_ON__1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON__1))
#define RTC_LDO_FORCE_ON__1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON__1, (value))
#define RTC_LDO_FORCE_ON__1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON__1, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON__1) | (value))
#define RTC_LDO_FORCE_ON__1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON__1, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON__1) & (~(value)))

/*
 *  RTC_LDO_FORCE_ON__1_ON_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_FORCE_ON__1_ON_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_FORCE_ON__1_ON_DIG)
#define RTC_LDO_FORCE_ON__1_ON_DIG_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_FORCE_ON__1_ON_DIG, 1)
#define RTC_LDO_FORCE_ON__1_ON_DIG_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_FORCE_ON__1_ON_DIG, 0)


/*
 *  RTC_LDO_TEST_CTRL_18100__0 register macros
 ****************************************************************************************
 */
#define RTC_LDO_TEST_CTRL_18100__0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_18100__0))
#define RTC_LDO_TEST_CTRL_18100__0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_18100__0, (value))
#define RTC_LDO_TEST_CTRL_18100__0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_18100__0, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_18100__0) | (value))
#define RTC_LDO_TEST_CTRL_18100__0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_18100__0, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_18100__0) & (~(value)))

/*
 *  RTC_LDO_TEST_CTRL_18100__0_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_TEST_CTRL_18100__0_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_TEST_CTRL_18100__0_DIG)
#define RTC_LDO_TEST_CTRL_18100__0_DIG_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_TEST_CTRL_18100__0_DIG, (value))


/*
 *  RTC_LDO_TEST_CTRL_18100__1 register macros
 ****************************************************************************************
 */
#define RTC_LDO_TEST_CTRL_18100__1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_18100__1))
#define RTC_LDO_TEST_CTRL_18100__1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_18100__1, (value))
#define RTC_LDO_TEST_CTRL_18100__1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_18100__1, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_18100__1) | (value))
#define RTC_LDO_TEST_CTRL_18100__1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_18100__1, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_18100__1) & (~(value)))

/*
 *  RTC_LDO_TEST_CTRL_18100__1_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_TEST_CTRL_18100__1_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_TEST_CTRL_18100__1_DIG)
#define RTC_LDO_TEST_CTRL_18100__1_DIG_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_TEST_CTRL_18100__1_DIG, (value))


/*
 *  RTC_LDO_SEL_2P5V__0 register macros
 ****************************************************************************************
 */
#define RTC_LDO_SEL_2P5V__0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V__0))
#define RTC_LDO_SEL_2P5V__0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V__0, (value))
#define RTC_LDO_SEL_2P5V__0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V__0, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V__0) | (value))
#define RTC_LDO_SEL_2P5V__0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V__0, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V__0) & (~(value)))

/*
 *  RTC_LDO_SEL_2P5V__0_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_SEL_2P5V__0_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_2P5V__0_DIG)
#define RTC_LDO_SEL_2P5V__0_DIG_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_2P5V__0_DIG, 1)
#define RTC_LDO_SEL_2P5V__0_DIG_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_2P5V__0_DIG, 0)


/*
 *  RTC_LDO_SEL_2P5V__1 register macros
 ****************************************************************************************
 */
#define RTC_LDO_SEL_2P5V__1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V__1))
#define RTC_LDO_SEL_2P5V__1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V__1, (value))
#define RTC_LDO_SEL_2P5V__1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V__1, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V__1) | (value))
#define RTC_LDO_SEL_2P5V__1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V__1, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V__1) & (~(value)))

/*
 *  RTC_LDO_SEL_2P5V__1_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_SEL_2P5V__1_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_2P5V__1_DIG)
#define RTC_LDO_SEL_2P5V__1_DIG_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_2P5V__1_DIG, 1)
#define RTC_LDO_SEL_2P5V__1_DIG_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_2P5V__1_DIG, 0)


/*
 *  RTC_LDO_POWERGOOD__0 register macros
 ****************************************************************************************
 */
#define RTC_LDO_POWERGOOD__0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_POWERGOOD__0))

/*
 *  RTC_LDO_POWERGOOD__0_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_POWERGOOD__0_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_POWERGOOD__0_DIG)


/*
 *  RTC_LDO_POWERGOOD__1 register macros
 ****************************************************************************************
 */
#define RTC_LDO_POWERGOOD__1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_POWERGOOD__1))

/*
 *  RTC_LDO_POWERGOOD__1_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_POWERGOOD__1_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_POWERGOOD__1_DIG)


/*
 *  RTC_LDO_STBY_IND__0 register macros
 ****************************************************************************************
 */
#define RTC_LDO_STBY_IND__0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_IND__0))

/*
 *  RTC_LDO_STBY_IND__0_OUT_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_STBY_IND__0_OUT_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_STBY_IND__0_OUT_DIG)


/*
 *  RTC_LDO_STBY_IND__1 register macros
 ****************************************************************************************
 */
#define RTC_LDO_STBY_IND__1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_IND__1))

/*
 *  RTC_LDO_STBY_IND__1_OUT_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_STBY_IND__1_OUT_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_STBY_IND__1_OUT_DIG)


/*
 *  RTC_LDO_TEST_OUT__0 register macros
 ****************************************************************************************
 */
#define RTC_LDO_TEST_OUT__0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_OUT__0))

/*
 *  RTC_LDO_TEST_OUT__0_OUT_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_TEST_OUT__0_OUT_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_TEST_OUT__0_OUT_DIG)


/*
 *  RTC_LDO_TEST_OUT__1 register macros
 ****************************************************************************************
 */
#define RTC_LDO_TEST_OUT__1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_OUT__1))

/*
 *  RTC_LDO_TEST_OUT__1_OUT_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_TEST_OUT__1_OUT_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_TEST_OUT__1_OUT_DIG)


/*
 *  RTC_LDO_STBY_30300 register macros
 ****************************************************************************************
 */
#define RTC_LDO_STBY_30300_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_30300))
#define RTC_LDO_STBY_30300_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_30300, (value))
#define RTC_LDO_STBY_30300_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_30300, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_30300) | (value))
#define RTC_LDO_STBY_30300_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_30300, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_30300) & (~(value)))

/*
 *  RTC_LDO_STBY_30300_IN_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_STBY_30300_IN_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_STBY_30300_IN_DIG)
#define RTC_LDO_STBY_30300_IN_DIG_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_STBY_30300_IN_DIG, 1)
#define RTC_LDO_STBY_30300_IN_DIG_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_STBY_30300_IN_DIG, 0)


/*
 *  RTC_LDO_CTRL_30300 register macros
 ****************************************************************************************
 */
#define RTC_LDO_CTRL_30300_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_30300))
#define RTC_LDO_CTRL_30300_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_30300, (value))
#define RTC_LDO_CTRL_30300_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_30300, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_30300) | (value))
#define RTC_LDO_CTRL_30300_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_30300, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_CTRL_30300) & (~(value)))

/*
 *  RTC_LDO_CTRL_30300_OUT_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_CTRL_30300_OUT_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_CTRL_30300_OUT_DIG)
#define RTC_LDO_CTRL_30300_OUT_DIG_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_CTRL_30300_OUT_DIG, (value))


/*
 *  RTC_LDO_SEL_CTRL_30300 register macros
 ****************************************************************************************
 */
#define RTC_LDO_SEL_CTRL_30300_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL_30300))
#define RTC_LDO_SEL_CTRL_30300_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL_30300, (value))
#define RTC_LDO_SEL_CTRL_30300_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL_30300, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL_30300) | (value))
#define RTC_LDO_SEL_CTRL_30300_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL_30300, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_CTRL_30300) & (~(value)))

/*
 *  RTC_LDO_SEL_CTRL_30300_OUT_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_SEL_CTRL_30300_OUT_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_CTRL_30300_OUT_DIG)
#define RTC_LDO_SEL_CTRL_30300_OUT_DIG_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_CTRL_30300_OUT_DIG, 1)
#define RTC_LDO_SEL_CTRL_30300_OUT_DIG_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_CTRL_30300_OUT_DIG, 0)


/*
 *  RTC_LDO_FORCE_ON_30300 register macros
 ****************************************************************************************
 */
#define RTC_LDO_FORCE_ON_30300_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON_30300))
#define RTC_LDO_FORCE_ON_30300_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON_30300, (value))
#define RTC_LDO_FORCE_ON_30300_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON_30300, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON_30300) | (value))
#define RTC_LDO_FORCE_ON_30300_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON_30300, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_FORCE_ON_30300) & (~(value)))

/*
 *  RTC_LDO_FORCE_ON_30300_ON_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_FORCE_ON_30300_ON_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_FORCE_ON_30300_ON_DIG)
#define RTC_LDO_FORCE_ON_30300_ON_DIG_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_FORCE_ON_30300_ON_DIG, 1)
#define RTC_LDO_FORCE_ON_30300_ON_DIG_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_FORCE_ON_30300_ON_DIG, 0)


/*
 *  RTC_LDO_TEST_CTRL_30300 register macros
 ****************************************************************************************
 */
#define RTC_LDO_TEST_CTRL_30300_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_30300))
#define RTC_LDO_TEST_CTRL_30300_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_30300, (value))
#define RTC_LDO_TEST_CTRL_30300_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_30300, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_30300) | (value))
#define RTC_LDO_TEST_CTRL_30300_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_30300, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_CTRL_30300) & (~(value)))

/*
 *  RTC_LDO_TEST_CTRL_30300_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_TEST_CTRL_30300_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_TEST_CTRL_30300_DIG)
#define RTC_LDO_TEST_CTRL_30300_DIG_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_TEST_CTRL_30300_DIG, (value))


/*
 *  RTC_LDO_SEL_2P5V_30300 register macros
 ****************************************************************************************
 */
#define RTC_LDO_SEL_2P5V_30300_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V_30300))
#define RTC_LDO_SEL_2P5V_30300_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V_30300, (value))
#define RTC_LDO_SEL_2P5V_30300_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V_30300, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V_30300) | (value))
#define RTC_LDO_SEL_2P5V_30300_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V_30300, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_SEL_2P5V_30300) & (~(value)))

/*
 *  RTC_LDO_SEL_2P5V_30300_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_SEL_2P5V_30300_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_2P5V_30300_DIG)
#define RTC_LDO_SEL_2P5V_30300_DIG_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_2P5V_30300_DIG, 1)
#define RTC_LDO_SEL_2P5V_30300_DIG_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_SEL_2P5V_30300_DIG, 0)


/*
 *  RTC_LDO_PG_VDD_30300 register macros
 ****************************************************************************************
 */
#define RTC_LDO_PG_VDD_30300_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_PG_VDD_30300))
#define RTC_LDO_PG_VDD_30300_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_PG_VDD_30300, (value))
#define RTC_LDO_PG_VDD_30300_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_PG_VDD_30300, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_PG_VDD_30300) | (value))
#define RTC_LDO_PG_VDD_30300_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_PG_VDD_30300, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_PG_VDD_30300) & (~(value)))

/*
 *  RTC_LDO_PG_VDD_30300_PG_VDD bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_PG_VDD_30300_PG_VDD_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_PG_VDD_30300_PG_VDD)
#define RTC_LDO_PG_VDD_30300_PG_VDD_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_PG_VDD_30300_PG_VDD, 1)
#define RTC_LDO_PG_VDD_30300_PG_VDD_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_LDO_PG_VDD_30300_PG_VDD, 0)


/*
 *  RTC_LDO_POWERGOOD_30300 register macros
 ****************************************************************************************
 */
#define RTC_LDO_POWERGOOD_30300_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_POWERGOOD_30300))

/*
 *  RTC_LDO_POWERGOOD_30300_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_POWERGOOD_30300_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_POWERGOOD_30300_DIG)


/*
 *  RTC_LDO_STBY_IND_30300 register macros
 ****************************************************************************************
 */
#define RTC_LDO_STBY_IND_30300_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_STBY_IND_30300))

/*
 *  RTC_LDO_STBY_IND_30300_OUT_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_STBY_IND_30300_OUT_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_STBY_IND_30300_OUT_DIG)


/*
 *  RTC_LDO_TEST_OUT_30300 register macros
 ****************************************************************************************
 */
#define RTC_LDO_TEST_OUT_30300_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_LDO_TEST_OUT_30300))

/*
 *  RTC_LDO_TEST_OUT_30300_OUT_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_LDO_TEST_OUT_30300_OUT_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_LDO_TEST_OUT_30300_OUT_DIG)


/*
 *  RTC_BG_OK register macros
 ****************************************************************************************
 */
#define RTC_BG_OK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_BG_OK))

/*
 *  RTC_BG_OK_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_BG_OK_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_BG_OK_DIG)


/*
 *  RTC_BG_TEST_DATA register macros
 ****************************************************************************************
 */
#define RTC_BG_TEST_DATA_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_BG_TEST_DATA))

/*
 *  RTC_BG_TEST_DATA_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_BG_TEST_DATA_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_BG_TEST_DATA_VAL)


/*
 *  RTC_BG_TEST_CTRL register macros
 ****************************************************************************************
 */
#define RTC_BG_TEST_CTRL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_BG_TEST_CTRL))
#define RTC_BG_TEST_CTRL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_BG_TEST_CTRL, (value))
#define RTC_BG_TEST_CTRL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_BG_TEST_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_BG_TEST_CTRL) | (value))
#define RTC_BG_TEST_CTRL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_BG_TEST_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_BG_TEST_CTRL) & (~(value)))

/*
 *  RTC_BG_TEST_CTRL_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_BG_TEST_CTRL_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_BG_TEST_CTRL_DIG)
#define RTC_BG_TEST_CTRL_DIG_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_BG_TEST_CTRL_DIG, (value))


/*
 *  RTC_BG_TRIM register macros
 ****************************************************************************************
 */
#define RTC_BG_TRIM_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_BG_TRIM))
#define RTC_BG_TRIM_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_BG_TRIM, (value))
#define RTC_BG_TRIM_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_BG_TRIM, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_BG_TRIM) | (value))
#define RTC_BG_TRIM_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_BG_TRIM, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_BG_TRIM) & (~(value)))

/*
 *  RTC_BG_TRIM_DIG bit field macros
 ****************************************************************************************
 */
#define RTC_BG_TRIM_DIG_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_BG_TRIM_DIG)
#define RTC_BG_TRIM_DIG_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_BG_TRIM_DIG, (value))


/*
 *  RTC_CX_BG_CTRL register macros
 ****************************************************************************************
 */
#define RTC_CX_BG_CTRL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_BG_CTRL))
#define RTC_CX_BG_CTRL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_BG_CTRL, (value))
#define RTC_CX_BG_CTRL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_BG_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_BG_CTRL) | (value))
#define RTC_CX_BG_CTRL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_BG_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_BG_CTRL) & (~(value)))

/*
 *  RTC_CX_BG_CTRL_F bit field macros
 ****************************************************************************************
 */
#define RTC_CX_BG_CTRL_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_BG_CTRL_F)
#define RTC_CX_BG_CTRL_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_BG_CTRL_F, (value))


/*
 *  RTC_CX_C1_CTRL register macros
 ****************************************************************************************
 */
#define RTC_CX_C1_CTRL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_C1_CTRL))
#define RTC_CX_C1_CTRL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_C1_CTRL, (value))
#define RTC_CX_C1_CTRL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_C1_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_C1_CTRL) | (value))
#define RTC_CX_C1_CTRL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_C1_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_C1_CTRL) & (~(value)))

/*
 *  RTC_CX_C1_CTRL_F bit field macros
 ****************************************************************************************
 */
#define RTC_CX_C1_CTRL_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_C1_CTRL_F)
#define RTC_CX_C1_CTRL_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_C1_CTRL_F, (value))


/*
 *  RTC_CX_C2_CTRL register macros
 ****************************************************************************************
 */
#define RTC_CX_C2_CTRL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_C2_CTRL))
#define RTC_CX_C2_CTRL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_C2_CTRL, (value))
#define RTC_CX_C2_CTRL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_C2_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_C2_CTRL) | (value))
#define RTC_CX_C2_CTRL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_C2_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_C2_CTRL) & (~(value)))

/*
 *  RTC_CX_C2_CTRL_F bit field macros
 ****************************************************************************************
 */
#define RTC_CX_C2_CTRL_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_C2_CTRL_F)
#define RTC_CX_C2_CTRL_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_C2_CTRL_F, (value))


/*
 *  RTC_CX_CAL_CTL register macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_CTL))
#define RTC_CX_CAL_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_CTL, (value))
#define RTC_CX_CAL_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_CTL) | (value))
#define RTC_CX_CAL_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_CTL) & (~(value)))

/*
 *  RTC_CX_CAL_CLK_ENA bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_CLK_ENA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CAL_CLK_ENA)
#define RTC_CX_CAL_CLK_ENA_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CAL_CLK_ENA, 1)
#define RTC_CX_CAL_CLK_ENA_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CAL_CLK_ENA, 0)

/*
 *  RTC_CX_OSC_IN_HOLD bit field macros
 ****************************************************************************************
 */
#define RTC_CX_OSC_IN_HOLD_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_OSC_IN_HOLD)
#define RTC_CX_OSC_IN_HOLD_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_OSC_IN_HOLD, 1)
#define RTC_CX_OSC_IN_HOLD_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_OSC_IN_HOLD, 0)

/*
 *  RTC_CX_RESET_CAL_N bit field macros
 ****************************************************************************************
 */
#define RTC_CX_RESET_CAL_N_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_RESET_CAL_N)
#define RTC_CX_RESET_CAL_N_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_RESET_CAL_N, 1)
#define RTC_CX_RESET_CAL_N_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_RESET_CAL_N, 0)


/*
 *  RTC_CX_CAL_ENA register macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_ENA_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ENA))
#define RTC_CX_CAL_ENA_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ENA, (value))
#define RTC_CX_CAL_ENA_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ENA, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ENA) | (value))
#define RTC_CX_CAL_ENA_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ENA, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ENA) & (~(value)))

/*
 *  RTC_CX_CAL_ENABLE bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CAL_ENABLE)
#define RTC_CX_CAL_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CAL_ENABLE, 1)
#define RTC_CX_CAL_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CAL_ENABLE, 0)


/*
 *  RTC_CX_CAL_EXT_IN register macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_EXT_IN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_EXT_IN))
#define RTC_CX_CAL_EXT_IN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_EXT_IN, (value))
#define RTC_CX_CAL_EXT_IN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_EXT_IN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_EXT_IN) | (value))
#define RTC_CX_CAL_EXT_IN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_EXT_IN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_EXT_IN) & (~(value)))

/*
 *  RTC_CX_CAL_EXT_INPUT bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_EXT_INPUT_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CAL_EXT_INPUT)
#define RTC_CX_CAL_EXT_INPUT_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CAL_EXT_INPUT, (value))


/*
 *  RTC_CX_CAL_OFF_VAL register macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_OFF_VAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_OFF_VAL))
#define RTC_CX_CAL_OFF_VAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_OFF_VAL, (value))
#define RTC_CX_CAL_OFF_VAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_OFF_VAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_OFF_VAL) | (value))
#define RTC_CX_CAL_OFF_VAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_OFF_VAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_OFF_VAL) & (~(value)))

/*
 *  RTC_CX_CAL_OFF_VALUE bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_OFF_VALUE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CAL_OFF_VALUE)
#define RTC_CX_CAL_OFF_VALUE_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CAL_OFF_VALUE, (value))


/*
 *  RTC_CX_CAL_OVER_WRITE register macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_OVER_WRITE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_OVER_WRITE))
#define RTC_CX_CAL_OVER_WRITE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_OVER_WRITE, (value))
#define RTC_CX_CAL_OVER_WRITE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_OVER_WRITE, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_OVER_WRITE) | (value))
#define RTC_CX_CAL_OVER_WRITE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_OVER_WRITE, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_OVER_WRITE) & (~(value)))

/*
 *  RTC_CX_CAL_OVER_WRITE_F bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_OVER_WRITE_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CAL_OVER_WRITE_F)
#define RTC_CX_CAL_OVER_WRITE_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CAL_OVER_WRITE_F, 1)
#define RTC_CX_CAL_OVER_WRITE_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CAL_OVER_WRITE_F, 0)


/*
 *  RTC_CX_CAL_REG_OUT register macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_REG_OUT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_REG_OUT))
#define RTC_CX_CAL_REG_OUT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_REG_OUT, (value))
#define RTC_CX_CAL_REG_OUT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_REG_OUT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_REG_OUT) | (value))
#define RTC_CX_CAL_REG_OUT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_REG_OUT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_REG_OUT) & (~(value)))

/*
 *  RTC_CX_CAL_REG_OUT_F bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_REG_OUT_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CAL_REG_OUT_F)
#define RTC_CX_CAL_REG_OUT_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CAL_REG_OUT_F, (value))


/*
 *  RTC_CX_CAL_ACC_ATTN register macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_ACC_ATTN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ACC_ATTN))
#define RTC_CX_CAL_ACC_ATTN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ACC_ATTN, (value))
#define RTC_CX_CAL_ACC_ATTN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ACC_ATTN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ACC_ATTN) | (value))
#define RTC_CX_CAL_ACC_ATTN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ACC_ATTN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ACC_ATTN) & (~(value)))

/*
 *  RTC_CX_CAL_ACCUM_ATTN bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_ACCUM_ATTN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CAL_ACCUM_ATTN)
#define RTC_CX_CAL_ACCUM_ATTN_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CAL_ACCUM_ATTN, (value))


/*
 *  RTC_CX_CAL_ACC_INC register macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_ACC_INC_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ACC_INC))
#define RTC_CX_CAL_ACC_INC_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ACC_INC, (value))
#define RTC_CX_CAL_ACC_INC_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ACC_INC, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ACC_INC) | (value))
#define RTC_CX_CAL_ACC_INC_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ACC_INC, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_ACC_INC) & (~(value)))

/*
 *  RTC_CX_CAL_ACCUM_INC bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_ACCUM_INC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CAL_ACCUM_INC)
#define RTC_CX_CAL_ACCUM_INC_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CAL_ACCUM_INC, (value))


/*
 *  RTC_CX_CAL_FREQ_ACCU_INC register macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_FREQ_ACCU_INC_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_FREQ_ACCU_INC))
#define RTC_CX_CAL_FREQ_ACCU_INC_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_FREQ_ACCU_INC, (value))
#define RTC_CX_CAL_FREQ_ACCU_INC_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_FREQ_ACCU_INC, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_FREQ_ACCU_INC) | (value))
#define RTC_CX_CAL_FREQ_ACCU_INC_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_FREQ_ACCU_INC, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CAL_FREQ_ACCU_INC) & (~(value)))

/*
 *  RTC_CX_CAL_FREQ_ACCU bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CAL_FREQ_ACCU_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CAL_FREQ_ACCU)
#define RTC_CX_CAL_FREQ_ACCU_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CAL_FREQ_ACCU, (value))


/*
 *  RTC_CX_CLK_PLL_ENABLE register macros
 ****************************************************************************************
 */
#define RTC_CX_CLK_PLL_ENABLE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CLK_PLL_ENABLE))
#define RTC_CX_CLK_PLL_ENABLE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CLK_PLL_ENABLE, (value))
#define RTC_CX_CLK_PLL_ENABLE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CLK_PLL_ENABLE, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CLK_PLL_ENABLE) | (value))
#define RTC_CX_CLK_PLL_ENABLE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CLK_PLL_ENABLE, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CLK_PLL_ENABLE) & (~(value)))

/*
 *  RTC_CX_CLK_DIG1_ENA bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CLK_DIG1_ENA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG1_ENA)
#define RTC_CX_CLK_DIG1_ENA_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG1_ENA, 1)
#define RTC_CX_CLK_DIG1_ENA_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG1_ENA, 0)

/*
 *  RTC_CX_CLK_DIG2_ENA bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CLK_DIG2_ENA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG2_ENA)
#define RTC_CX_CLK_DIG2_ENA_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG2_ENA, 1)
#define RTC_CX_CLK_DIG2_ENA_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG2_ENA, 0)

/*
 *  RTC_CX_CLK_DIG3_ENA bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CLK_DIG3_ENA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG3_ENA)
#define RTC_CX_CLK_DIG3_ENA_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG3_ENA, 1)
#define RTC_CX_CLK_DIG3_ENA_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG3_ENA, 0)

/*
 *  RTC_CX_CLK_DIG4_ENA bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CLK_DIG4_ENA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG4_ENA)
#define RTC_CX_CLK_DIG4_ENA_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG4_ENA, 1)
#define RTC_CX_CLK_DIG4_ENA_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG4_ENA, 0)

/*
 *  RTC_CX_CLK_DIG5_ENA bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CLK_DIG5_ENA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG5_ENA)
#define RTC_CX_CLK_DIG5_ENA_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG5_ENA, 1)
#define RTC_CX_CLK_DIG5_ENA_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG5_ENA, 0)

/*
 *  RTC_CX_CLK_DIG6_ENA bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CLK_DIG6_ENA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG6_ENA)
#define RTC_CX_CLK_DIG6_ENA_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG6_ENA, 1)
#define RTC_CX_CLK_DIG6_ENA_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DIG6_ENA, 0)

/*
 *  RTC_CX_CLK_ADC_ENA bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CLK_ADC_ENA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CLK_ADC_ENA)
#define RTC_CX_CLK_ADC_ENA_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CLK_ADC_ENA, 1)
#define RTC_CX_CLK_ADC_ENA_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CLK_ADC_ENA, 0)

/*
 *  RTC_CX_CLK_DAC_ENA bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CLK_DAC_ENA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DAC_ENA)
#define RTC_CX_CLK_DAC_ENA_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DAC_ENA, 1)
#define RTC_CX_CLK_DAC_ENA_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CLK_DAC_ENA, 0)


/*
 *  RTC_CX_FB_DIV_SEL register macros
 ****************************************************************************************
 */
#define RTC_CX_FB_DIV_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_FB_DIV_SEL))
#define RTC_CX_FB_DIV_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_FB_DIV_SEL, (value))
#define RTC_CX_FB_DIV_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_FB_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_FB_DIV_SEL) | (value))
#define RTC_CX_FB_DIV_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_FB_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_FB_DIV_SEL) & (~(value)))

/*
 *  RTC_CX_FB_DIV_SEL_PLL bit field macros
 ****************************************************************************************
 */
#define RTC_CX_FB_DIV_SEL_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_FB_DIV_SEL_PLL)
#define RTC_CX_FB_DIV_SEL_PLL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_FB_DIV_SEL_PLL, (value))


/*
 *  RTC_CX_LPF_MON_ENA register macros
 ****************************************************************************************
 */
#define RTC_CX_LPF_MON_ENA_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_LPF_MON_ENA))
#define RTC_CX_LPF_MON_ENA_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_LPF_MON_ENA, (value))
#define RTC_CX_LPF_MON_ENA_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_LPF_MON_ENA, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_LPF_MON_ENA) | (value))
#define RTC_CX_LPF_MON_ENA_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_LPF_MON_ENA, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_LPF_MON_ENA) & (~(value)))

/*
 *  RTC_CX_LPF_MON_EN bit field macros
 ****************************************************************************************
 */
#define RTC_CX_LPF_MON_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_LPF_MON_EN)
#define RTC_CX_LPF_MON_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_LPF_MON_EN, 1)
#define RTC_CX_LPF_MON_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_LPF_MON_EN, 0)


/*
 *  RTC_CX_OSC_OPT_BIT register macros
 ****************************************************************************************
 */
#define RTC_CX_OSC_OPT_BIT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_OSC_OPT_BIT))
#define RTC_CX_OSC_OPT_BIT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_OSC_OPT_BIT, (value))
#define RTC_CX_OSC_OPT_BIT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_OSC_OPT_BIT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_OSC_OPT_BIT) | (value))
#define RTC_CX_OSC_OPT_BIT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_OSC_OPT_BIT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_OSC_OPT_BIT) & (~(value)))

/*
 *  RTC_CX_OSC_OPT_BIT_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_CX_OSC_OPT_BIT_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_OSC_OPT_BIT_VAL)
#define RTC_CX_OSC_OPT_BIT_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_OSC_OPT_BIT_VAL, (value))


/*
 *  RTC_CX_PLL_OPT_BIT register macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_OPT_BIT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_OPT_BIT))
#define RTC_CX_PLL_OPT_BIT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_OPT_BIT, (value))
#define RTC_CX_PLL_OPT_BIT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_OPT_BIT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_OPT_BIT) | (value))
#define RTC_CX_PLL_OPT_BIT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_OPT_BIT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_OPT_BIT) & (~(value)))

/*
 *  RTC_CX_PLL_OPT_BIT_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_OPT_BIT_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_PLL_OPT_BIT_VAL)
#define RTC_CX_PLL_OPT_BIT_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_PLL_OPT_BIT_VAL, (value))


/*
 *  RTC_CX_DCOP register macros
 ****************************************************************************************
 */
#define RTC_CX_DCOP_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_DCOP))
#define RTC_CX_DCOP_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_DCOP, (value))
#define RTC_CX_DCOP_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_DCOP, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_DCOP) | (value))
#define RTC_CX_DCOP_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_DCOP, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_DCOP) & (~(value)))

/*
 *  RTC_CX_DCOP_F bit field macros
 ****************************************************************************************
 */
#define RTC_CX_DCOP_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_DCOP_F)
#define RTC_CX_DCOP_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_DCOP_F, 1)
#define RTC_CX_DCOP_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_DCOP_F, 0)


/*
 *  RTC_CX_EN_GSHIFT register macros
 ****************************************************************************************
 */
#define RTC_CX_EN_GSHIFT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_GSHIFT))
#define RTC_CX_EN_GSHIFT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_GSHIFT, (value))
#define RTC_CX_EN_GSHIFT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_GSHIFT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_GSHIFT) | (value))
#define RTC_CX_EN_GSHIFT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_GSHIFT, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_GSHIFT) & (~(value)))

/*
 *  RTC_CX_EN_G_SHIFT bit field macros
 ****************************************************************************************
 */
#define RTC_CX_EN_G_SHIFT_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_EN_G_SHIFT)
#define RTC_CX_EN_G_SHIFT_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_EN_G_SHIFT, 1)
#define RTC_CX_EN_G_SHIFT_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_EN_G_SHIFT, 0)


/*
 *  RTC_CX_GM register macros
 ****************************************************************************************
 */
#define RTC_CX_GM_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_GM))
#define RTC_CX_GM_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_GM, (value))
#define RTC_CX_GM_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_GM, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_GM) | (value))
#define RTC_CX_GM_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_GM, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_GM) & (~(value)))

/*
 *  RTC_CX_GM_F bit field macros
 ****************************************************************************************
 */
#define RTC_CX_GM_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_GM_F)
#define RTC_CX_GM_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_GM_F, (value))


/*
 *  RTC_CX_PLL_SEL_DIG1 register macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG1))
#define RTC_CX_PLL_SEL_DIG1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG1, (value))
#define RTC_CX_PLL_SEL_DIG1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG1, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG1) | (value))
#define RTC_CX_PLL_SEL_DIG1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG1, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG1) & (~(value)))

/*
 *  RTC_CX_PLL_SEL_DIG1_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG1_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_PLL_SEL_DIG1_VAL)
#define RTC_CX_PLL_SEL_DIG1_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_PLL_SEL_DIG1_VAL, (value))


/*
 *  RTC_CX_PLL_SEL_DIG2 register macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG2_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG2))
#define RTC_CX_PLL_SEL_DIG2_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG2, (value))
#define RTC_CX_PLL_SEL_DIG2_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG2, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG2) | (value))
#define RTC_CX_PLL_SEL_DIG2_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG2, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG2) & (~(value)))

/*
 *  RTC_CX_PLL_SEL_DIG2_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG2_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_PLL_SEL_DIG2_VAL)
#define RTC_CX_PLL_SEL_DIG2_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_PLL_SEL_DIG2_VAL, (value))


/*
 *  RTC_CX_PLL_SEL_DIG3 register macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG3_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG3))
#define RTC_CX_PLL_SEL_DIG3_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG3, (value))
#define RTC_CX_PLL_SEL_DIG3_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG3, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG3) | (value))
#define RTC_CX_PLL_SEL_DIG3_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG3, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG3) & (~(value)))

/*
 *  RTC_CX_PLL_SEL_DIG3_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG3_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_PLL_SEL_DIG3_VAL)
#define RTC_CX_PLL_SEL_DIG3_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_PLL_SEL_DIG3_VAL, (value))


/*
 *  RTC_CX_PLL_SEL_DIG4 register macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG4_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG4))
#define RTC_CX_PLL_SEL_DIG4_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG4, (value))
#define RTC_CX_PLL_SEL_DIG4_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG4, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG4) | (value))
#define RTC_CX_PLL_SEL_DIG4_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG4, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG4) & (~(value)))

/*
 *  RTC_CX_PLL_SEL_DIG4_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG4_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_PLL_SEL_DIG4_VAL)
#define RTC_CX_PLL_SEL_DIG4_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_PLL_SEL_DIG4_VAL, (value))


/*
 *  RTC_CX_PLL_SEL_DIG5 register macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG5_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG5))
#define RTC_CX_PLL_SEL_DIG5_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG5, (value))
#define RTC_CX_PLL_SEL_DIG5_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG5, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG5) | (value))
#define RTC_CX_PLL_SEL_DIG5_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG5, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG5) & (~(value)))

/*
 *  RTC_CX_PLL_SEL_DIG5_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG5_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_PLL_SEL_DIG5_VAL)
#define RTC_CX_PLL_SEL_DIG5_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_PLL_SEL_DIG5_VAL, (value))


/*
 *  RTC_CX_PLL_SEL_DIG6 register macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG6_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG6))
#define RTC_CX_PLL_SEL_DIG6_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG6, (value))
#define RTC_CX_PLL_SEL_DIG6_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG6, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG6) | (value))
#define RTC_CX_PLL_SEL_DIG6_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG6, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DIG6) & (~(value)))

/*
 *  RTC_CX_PLL_SEL_DIG6_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG6_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_PLL_SEL_DIG6_VAL)
#define RTC_CX_PLL_SEL_DIG6_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_PLL_SEL_DIG6_VAL, (value))


/*
 *  RTC_CX_PLL_SEL_ADC register macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_ADC_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_ADC))
#define RTC_CX_PLL_SEL_ADC_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_ADC, (value))
#define RTC_CX_PLL_SEL_ADC_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_ADC, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_ADC) | (value))
#define RTC_CX_PLL_SEL_ADC_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_ADC, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_ADC) & (~(value)))

/*
 *  RTC_CX_PLL_SEL_ADC_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_ADC_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_PLL_SEL_ADC_VAL)
#define RTC_CX_PLL_SEL_ADC_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_PLL_SEL_ADC_VAL, (value))


/*
 *  RTC_CX_PLL_SEL_DAC register macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DAC_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DAC))
#define RTC_CX_PLL_SEL_DAC_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DAC, (value))
#define RTC_CX_PLL_SEL_DAC_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DAC, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DAC) | (value))
#define RTC_CX_PLL_SEL_DAC_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DAC, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_PLL_SEL_DAC) & (~(value)))

/*
 *  RTC_CX_PLL_SEL_DAC_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DAC_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_PLL_SEL_DAC_VAL)
#define RTC_CX_PLL_SEL_DAC_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_PLL_SEL_DAC_VAL, (value))


/*
 *  RTC_CX_CLK_SRC_SEL register macros
 ****************************************************************************************
 */
#define RTC_CX_CLK_SRC_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CLK_SRC_SEL))
#define RTC_CX_CLK_SRC_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CLK_SRC_SEL, (value))
#define RTC_CX_CLK_SRC_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CLK_SRC_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CLK_SRC_SEL) | (value))
#define RTC_CX_CLK_SRC_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CLK_SRC_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_CLK_SRC_SEL) & (~(value)))

/*
 *  RTC_CX_CLK_SRC_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_CX_CLK_SRC_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_CLK_SRC_SEL_VAL)
#define RTC_CX_CLK_SRC_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_CLK_SRC_SEL_VAL, (value))


/*
 *  RTC_CX_EN_BB register macros
 ****************************************************************************************
 */
#define RTC_CX_EN_BB_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_BB))
#define RTC_CX_EN_BB_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_BB, (value))
#define RTC_CX_EN_BB_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_BB, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_BB) | (value))
#define RTC_CX_EN_BB_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_BB, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_BB) & (~(value)))

/*
 *  RTC_CX_EN_BB_F bit field macros
 ****************************************************************************************
 */
#define RTC_CX_EN_BB_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_EN_BB_F)
#define RTC_CX_EN_BB_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_EN_BB_F, 1)
#define RTC_CX_EN_BB_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_EN_BB_F, 0)


/*
 *  RTC_CX_EN_RF register macros
 ****************************************************************************************
 */
#define RTC_CX_EN_RF_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_RF))
#define RTC_CX_EN_RF_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_RF, (value))
#define RTC_CX_EN_RF_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_RF, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_RF) | (value))
#define RTC_CX_EN_RF_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_RF, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_EN_RF) & (~(value)))

/*
 *  RTC_CX_EN_RF_F bit field macros
 ****************************************************************************************
 */
#define RTC_CX_EN_RF_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_EN_RF_F)
#define RTC_CX_EN_RF_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_EN_RF_F, 1)
#define RTC_CX_EN_RF_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_EN_RF_F, 0)


/*
 *  RTC_CX_BYPASS register macros
 ****************************************************************************************
 */
#define RTC_CX_BYPASS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_BYPASS))
#define RTC_CX_BYPASS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_BYPASS, (value))
#define RTC_CX_BYPASS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_BYPASS, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_BYPASS) | (value))
#define RTC_CX_BYPASS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_BYPASS, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_CX_BYPASS) & (~(value)))

/*
 *  RTC_CX_BYPASS_F bit field macros
 ****************************************************************************************
 */
#define RTC_CX_BYPASS_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_CX_BYPASS_F)
#define RTC_CX_BYPASS_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_BYPASS_F, 1)
#define RTC_CX_BYPASS_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_CX_BYPASS_F, 0)


/*
 *  RTC_EN_PWR register macros
 ****************************************************************************************
 */
#define RTC_EN_PWR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_EN_PWR))
#define RTC_EN_PWR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_EN_PWR, (value))
#define RTC_EN_PWR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_EN_PWR, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_EN_PWR) | (value))
#define RTC_EN_PWR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_EN_PWR, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_EN_PWR) & (~(value)))

/*
 *  RTC_EN_PWR_RTC_SARM bit field macros
 ****************************************************************************************
 */
#define RTC_EN_PWR_RTC_SARM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_EN_PWR_RTC_SARM)
#define RTC_EN_PWR_RTC_SARM_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_EN_PWR_RTC_SARM, (value))

/*
 *  RTC_EN_PWR_WLAN_SRAM bit field macros
 ****************************************************************************************
 */
#define RTC_EN_PWR_WLAN_SRAM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_EN_PWR_WLAN_SRAM)
#define RTC_EN_PWR_WLAN_SRAM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_EN_PWR_WLAN_SRAM, 1)
#define RTC_EN_PWR_WLAN_SRAM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_EN_PWR_WLAN_SRAM, 0)

/*
 *  RTC_EN_PWR_APP_SRAM bit field macros
 ****************************************************************************************
 */
#define RTC_EN_PWR_APP_SRAM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_EN_PWR_APP_SRAM)
#define RTC_EN_PWR_APP_SRAM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_EN_PWR_APP_SRAM, 1)
#define RTC_EN_PWR_APP_SRAM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_EN_PWR_APP_SRAM, 0)

/*
 *  RTC_EN_PWR_SHARE_MEM bit field macros
 ****************************************************************************************
 */
#define RTC_EN_PWR_SHARE_MEM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_EN_PWR_SHARE_MEM)
#define RTC_EN_PWR_SHARE_MEM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_EN_PWR_SHARE_MEM, 1)
#define RTC_EN_PWR_SHARE_MEM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_EN_PWR_SHARE_MEM, 0)

/*
 *  RTC_EN_PWR_WLAN_CORE bit field macros
 ****************************************************************************************
 */
#define RTC_EN_PWR_WLAN_CORE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_EN_PWR_WLAN_CORE)
#define RTC_EN_PWR_WLAN_CORE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_EN_PWR_WLAN_CORE, 1)
#define RTC_EN_PWR_WLAN_CORE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_EN_PWR_WLAN_CORE, 0)

/*
 *  RTC_EN_PWR_CRYPTO bit field macros
 ****************************************************************************************
 */
#define RTC_EN_PWR_CRYPTO_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_EN_PWR_CRYPTO)
#define RTC_EN_PWR_CRYPTO_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_EN_PWR_CRYPTO, 1)
#define RTC_EN_PWR_CRYPTO_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_EN_PWR_CRYPTO, 0)


/*
 *  RTC_ISO_CTL register macros
 ****************************************************************************************
 */
#define RTC_ISO_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ISO_CTL))
#define RTC_ISO_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ISO_CTL, (value))
#define RTC_ISO_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ISO_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ISO_CTL) | (value))
#define RTC_ISO_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ISO_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_ISO_CTL) & (~(value)))

/*
 *  RTC_ISO_CTL_RTC_SARM bit field macros
 ****************************************************************************************
 */
#define RTC_ISO_CTL_RTC_SARM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ISO_CTL_RTC_SARM)
#define RTC_ISO_CTL_RTC_SARM_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_ISO_CTL_RTC_SARM, (value))

/*
 *  RTC_ISO_CTL_WLAN_SRAM bit field macros
 ****************************************************************************************
 */
#define RTC_ISO_CTL_WLAN_SRAM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ISO_CTL_WLAN_SRAM)
#define RTC_ISO_CTL_WLAN_SRAM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ISO_CTL_WLAN_SRAM, 1)
#define RTC_ISO_CTL_WLAN_SRAM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ISO_CTL_WLAN_SRAM, 0)

/*
 *  RTC_ISO_CTL_APP_SRAM bit field macros
 ****************************************************************************************
 */
#define RTC_ISO_CTL_APP_SRAM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ISO_CTL_APP_SRAM)
#define RTC_ISO_CTL_APP_SRAM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ISO_CTL_APP_SRAM, 1)
#define RTC_ISO_CTL_APP_SRAM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ISO_CTL_APP_SRAM, 0)

/*
 *  RTC_ISO_CTL_SHARE_MEM bit field macros
 ****************************************************************************************
 */
#define RTC_ISO_CTL_SHARE_MEM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ISO_CTL_SHARE_MEM)
#define RTC_ISO_CTL_SHARE_MEM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ISO_CTL_SHARE_MEM, 1)
#define RTC_ISO_CTL_SHARE_MEM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ISO_CTL_SHARE_MEM, 0)

/*
 *  RTC_ISO_CTL_WLAN_CORE bit field macros
 ****************************************************************************************
 */
#define RTC_ISO_CTL_WLAN_CORE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ISO_CTL_WLAN_CORE)
#define RTC_ISO_CTL_WLAN_CORE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ISO_CTL_WLAN_CORE, 1)
#define RTC_ISO_CTL_WLAN_CORE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ISO_CTL_WLAN_CORE, 0)

/*
 *  RTC_ISO_CTL_CRYPTO bit field macros
 ****************************************************************************************
 */
#define RTC_ISO_CTL_CRYPTO_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_ISO_CTL_CRYPTO)
#define RTC_ISO_CTL_CRYPTO_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ISO_CTL_CRYPTO, 1)
#define RTC_ISO_CTL_CRYPTO_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_ISO_CTL_CRYPTO, 0)


/*
 *  RTC_SX_EN_BIAS register macros
 ****************************************************************************************
 */
#define RTC_SX_EN_BIAS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BIAS))
#define RTC_SX_EN_BIAS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BIAS, (value))
#define RTC_SX_EN_BIAS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BIAS, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BIAS) | (value))
#define RTC_SX_EN_BIAS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BIAS, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BIAS) & (~(value)))

/*
 *  RTC_SX_EN_BIAS_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_EN_BIAS_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_EN_BIAS_F)
#define RTC_SX_EN_BIAS_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_EN_BIAS_F, 1)
#define RTC_SX_EN_BIAS_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_EN_BIAS_F, 0)


/*
 *  RTC_SX_EN_U_LDO register macros
 ****************************************************************************************
 */
#define RTC_SX_EN_U_LDO_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_U_LDO))
#define RTC_SX_EN_U_LDO_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_U_LDO, (value))
#define RTC_SX_EN_U_LDO_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_U_LDO, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_U_LDO) | (value))
#define RTC_SX_EN_U_LDO_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_U_LDO, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_U_LDO) & (~(value)))

/*
 *  RTC_SX_EN_U_LDO_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_EN_U_LDO_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_EN_U_LDO_F)
#define RTC_SX_EN_U_LDO_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_EN_U_LDO_F, 1)
#define RTC_SX_EN_U_LDO_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_EN_U_LDO_F, 0)


/*
 *  RTC_SX_SWT2LDO register macros
 ****************************************************************************************
 */
#define RTC_SX_SWT2LDO_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_SWT2LDO))
#define RTC_SX_SWT2LDO_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_SWT2LDO, (value))
#define RTC_SX_SWT2LDO_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_SWT2LDO, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_SWT2LDO) | (value))
#define RTC_SX_SWT2LDO_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_SWT2LDO, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_SWT2LDO) & (~(value)))

/*
 *  RTC_SX_SWT2LDO_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_SWT2LDO_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_SWT2LDO_F)
#define RTC_SX_SWT2LDO_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_SWT2LDO_F, 1)
#define RTC_SX_SWT2LDO_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_SWT2LDO_F, 0)


/*
 *  RTC_SX_TS_GAIN register macros
 ****************************************************************************************
 */
#define RTC_SX_TS_GAIN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TS_GAIN))
#define RTC_SX_TS_GAIN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TS_GAIN, (value))
#define RTC_SX_TS_GAIN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TS_GAIN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TS_GAIN) | (value))
#define RTC_SX_TS_GAIN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TS_GAIN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TS_GAIN) & (~(value)))

/*
 *  RTC_SX_TS_GAIN_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_TS_GAIN_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_TS_GAIN_F)
#define RTC_SX_TS_GAIN_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_TS_GAIN_F, 1)
#define RTC_SX_TS_GAIN_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_TS_GAIN_F, 0)


/*
 *  RTC_SX_EN_BO register macros
 ****************************************************************************************
 */
#define RTC_SX_EN_BO_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO))
#define RTC_SX_EN_BO_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO, (value))
#define RTC_SX_EN_BO_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO) | (value))
#define RTC_SX_EN_BO_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO) & (~(value)))

/*
 *  RTC_SX_SX_EN_BO bit field macros
 ****************************************************************************************
 */
#define RTC_SX_SX_EN_BO_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_EN_BO)
#define RTC_SX_SX_EN_BO_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_EN_BO, 1)
#define RTC_SX_SX_EN_BO_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_EN_BO, 0)


/*
 *  RTC_SX_EN_BO_FLASH register macros
 ****************************************************************************************
 */
#define RTC_SX_EN_BO_FLASH_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO_FLASH))
#define RTC_SX_EN_BO_FLASH_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO_FLASH, (value))
#define RTC_SX_EN_BO_FLASH_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO_FLASH, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO_FLASH) | (value))
#define RTC_SX_EN_BO_FLASH_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO_FLASH, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO_FLASH) & (~(value)))

/*
 *  RTC_SX_SX_EN_BO_FLASH bit field macros
 ****************************************************************************************
 */
#define RTC_SX_SX_EN_BO_FLASH_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_SX_EN_BO_FLASH)
#define RTC_SX_SX_EN_BO_FLASH_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_SX_EN_BO_FLASH, 1)
#define RTC_SX_SX_EN_BO_FLASH_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_SX_EN_BO_FLASH, 0)


/*
 *  RTC_SX_EN_BO_SAR register macros
 ****************************************************************************************
 */
#define RTC_SX_EN_BO_SAR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO_SAR))
#define RTC_SX_EN_BO_SAR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO_SAR, (value))
#define RTC_SX_EN_BO_SAR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO_SAR, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO_SAR) | (value))
#define RTC_SX_EN_BO_SAR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO_SAR, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_BO_SAR) & (~(value)))

/*
 *  RTC_SX_SX_EN_BO_SAR bit field macros
 ****************************************************************************************
 */
#define RTC_SX_SX_EN_BO_SAR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_SX_EN_BO_SAR)
#define RTC_SX_SX_EN_BO_SAR_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_SX_EN_BO_SAR, 1)
#define RTC_SX_SX_EN_BO_SAR_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_SX_EN_BO_SAR, 0)


/*
 *  RTC_SX_OFF_SEN_FLASH register macros
 ****************************************************************************************
 */
#define RTC_SX_OFF_SEN_FLASH_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SEN_FLASH))
#define RTC_SX_OFF_SEN_FLASH_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SEN_FLASH, (value))
#define RTC_SX_OFF_SEN_FLASH_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SEN_FLASH, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SEN_FLASH) | (value))
#define RTC_SX_OFF_SEN_FLASH_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SEN_FLASH, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SEN_FLASH) & (~(value)))

/*
 *  RTC_SX_OFF_SEN_FLASH_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_OFF_SEN_FLASH_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_OFF_SEN_FLASH_F)
#define RTC_SX_OFF_SEN_FLASH_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_OFF_SEN_FLASH_F, 1)
#define RTC_SX_OFF_SEN_FLASH_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_OFF_SEN_FLASH_F, 0)


/*
 *  RTC_SX_OFF_SEN_SAR register macros
 ****************************************************************************************
 */
#define RTC_SX_OFF_SEN_SAR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SEN_SAR))
#define RTC_SX_OFF_SEN_SAR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SEN_SAR, (value))
#define RTC_SX_OFF_SEN_SAR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SEN_SAR, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SEN_SAR) | (value))
#define RTC_SX_OFF_SEN_SAR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SEN_SAR, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SEN_SAR) & (~(value)))

/*
 *  RTC_SX_OFF_SEN_SAR_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_OFF_SEN_SAR_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_OFF_SEN_SAR_F)
#define RTC_SX_OFF_SEN_SAR_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_OFF_SEN_SAR_F, 1)
#define RTC_SX_OFF_SEN_SAR_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_OFF_SEN_SAR_F, 0)


/*
 *  RTC_SX_BO_TH_CTRL register macros
 ****************************************************************************************
 */
#define RTC_SX_BO_TH_CTRL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_BO_TH_CTRL))
#define RTC_SX_BO_TH_CTRL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_BO_TH_CTRL, (value))
#define RTC_SX_BO_TH_CTRL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_BO_TH_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_BO_TH_CTRL) | (value))
#define RTC_SX_BO_TH_CTRL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_BO_TH_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_BO_TH_CTRL) & (~(value)))

/*
 *  RTC_SX_BO_TH_CTRL_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_BO_TH_CTRL_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_BO_TH_CTRL_F)
#define RTC_SX_BO_TH_CTRL_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_BO_TH_CTRL_F, (value))


/*
 *  RTC_SX_BO_DS register macros
 ****************************************************************************************
 */
#define RTC_SX_BO_DS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_BO_DS))
#define RTC_SX_BO_DS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_BO_DS, (value))
#define RTC_SX_BO_DS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_BO_DS, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_BO_DS) | (value))
#define RTC_SX_BO_DS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_BO_DS, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_BO_DS) & (~(value)))

/*
 *  RTC_SX_BO_DS_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_BO_DS_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_BO_DS_F)
#define RTC_SX_BO_DS_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_BO_DS_F, 1)
#define RTC_SX_BO_DS_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_BO_DS_F, 0)


/*
 *  RTC_SX_CX_1_CTRL register macros
 ****************************************************************************************
 */
#define RTC_SX_CX_1_CTRL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CX_1_CTRL))
#define RTC_SX_CX_1_CTRL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CX_1_CTRL, (value))
#define RTC_SX_CX_1_CTRL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CX_1_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CX_1_CTRL) | (value))
#define RTC_SX_CX_1_CTRL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CX_1_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CX_1_CTRL) & (~(value)))

/*
 *  RTC_SX_CX_1_CTRL_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_CX_1_CTRL_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_CX_1_CTRL_F)
#define RTC_SX_CX_1_CTRL_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_CX_1_CTRL_F, (value))


/*
 *  RTC_SX_CX_2_CTRL register macros
 ****************************************************************************************
 */
#define RTC_SX_CX_2_CTRL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CX_2_CTRL))
#define RTC_SX_CX_2_CTRL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CX_2_CTRL, (value))
#define RTC_SX_CX_2_CTRL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CX_2_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CX_2_CTRL) | (value))
#define RTC_SX_CX_2_CTRL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CX_2_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CX_2_CTRL) & (~(value)))

/*
 *  RTC_SX_CX_2_CTRL_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_CX_2_CTRL_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_CX_2_CTRL_F)
#define RTC_SX_CX_2_CTRL_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_CX_2_CTRL_F, (value))


/*
 *  RTC_SX_CL_CTRL register macros
 ****************************************************************************************
 */
#define RTC_SX_CL_CTRL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CL_CTRL))
#define RTC_SX_CL_CTRL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CL_CTRL, (value))
#define RTC_SX_CL_CTRL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CL_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CL_CTRL) | (value))
#define RTC_SX_CL_CTRL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CL_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_CL_CTRL) & (~(value)))

/*
 *  RTC_SX_CL_CTRL_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_CL_CTRL_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_CL_CTRL_F)
#define RTC_SX_CL_CTRL_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_CL_CTRL_F, (value))


/*
 *  RTC_SX_RL_CTRL register macros
 ****************************************************************************************
 */
#define RTC_SX_RL_CTRL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_RL_CTRL))
#define RTC_SX_RL_CTRL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_RL_CTRL, (value))
#define RTC_SX_RL_CTRL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_RL_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_RL_CTRL) | (value))
#define RTC_SX_RL_CTRL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_RL_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_RL_CTRL) & (~(value)))

/*
 *  RTC_SX_RL_CTRL_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_RL_CTRL_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_RL_CTRL_F)
#define RTC_SX_RL_CTRL_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_RL_CTRL_F, (value))


/*
 *  RTC_SX_GM_CTRL register macros
 ****************************************************************************************
 */
#define RTC_SX_GM_CTRL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_GM_CTRL))
#define RTC_SX_GM_CTRL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_GM_CTRL, (value))
#define RTC_SX_GM_CTRL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_GM_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_GM_CTRL) | (value))
#define RTC_SX_GM_CTRL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_GM_CTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_GM_CTRL) & (~(value)))

/*
 *  RTC_SX_GM_CTRL_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_GM_CTRL_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_GM_CTRL_F)
#define RTC_SX_GM_CTRL_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_GM_CTRL_F, (value))


/*
 *  RTC_SX_EN_TS register macros
 ****************************************************************************************
 */
#define RTC_SX_EN_TS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_TS))
#define RTC_SX_EN_TS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_TS, (value))
#define RTC_SX_EN_TS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_TS, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_TS) | (value))
#define RTC_SX_EN_TS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_TS, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_EN_TS) & (~(value)))

/*
 *  RTC_SX_EN_TS_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_EN_TS_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_EN_TS_F)
#define RTC_SX_EN_TS_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_EN_TS_F, 1)
#define RTC_SX_EN_TS_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_EN_TS_F, 0)


/*
 *  RTC_SX_OFF_SNS register macros
 ****************************************************************************************
 */
#define RTC_SX_OFF_SNS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SNS))
#define RTC_SX_OFF_SNS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SNS, (value))
#define RTC_SX_OFF_SNS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SNS, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SNS) | (value))
#define RTC_SX_OFF_SNS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SNS, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_OFF_SNS) & (~(value)))

/*
 *  RTC_SX_OFFSET_SNS bit field macros
 ****************************************************************************************
 */
#define RTC_SX_OFFSET_SNS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_OFFSET_SNS)
#define RTC_SX_OFFSET_SNS_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_OFFSET_SNS, 1)
#define RTC_SX_OFFSET_SNS_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_OFFSET_SNS, 0)


/*
 *  RTC_SX_TEST register macros
 ****************************************************************************************
 */
#define RTC_SX_TEST_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TEST))
#define RTC_SX_TEST_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TEST, (value))
#define RTC_SX_TEST_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TEST, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TEST) | (value))
#define RTC_SX_TEST_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TEST, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TEST) & (~(value)))

/*
 *  RTC_SX_TEST_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_SX_TEST_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_TEST_VAL)
#define RTC_SX_TEST_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_TEST_VAL, (value))


/*
 *  RTC_SX_TSADJ register macros
 ****************************************************************************************
 */
#define RTC_SX_TSADJ_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TSADJ))
#define RTC_SX_TSADJ_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TSADJ, (value))
#define RTC_SX_TSADJ_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TSADJ, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TSADJ) | (value))
#define RTC_SX_TSADJ_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TSADJ, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_TSADJ) & (~(value)))

/*
 *  RTC_SX_TSADJ_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_SX_TSADJ_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_TSADJ_VAL)
#define RTC_SX_TSADJ_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_TSADJ_VAL, (value))


/*
 *  RTC_SX_DC_OP register macros
 ****************************************************************************************
 */
#define RTC_SX_DC_OP_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_DC_OP))
#define RTC_SX_DC_OP_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_DC_OP, (value))
#define RTC_SX_DC_OP_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_DC_OP, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_DC_OP) | (value))
#define RTC_SX_DC_OP_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_DC_OP, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_DC_OP) & (~(value)))

/*
 *  RTC_SX_DC_OP_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_DC_OP_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_DC_OP_F)
#define RTC_SX_DC_OP_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_DC_OP_F, 1)
#define RTC_SX_DC_OP_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_DC_OP_F, 0)


/*
 *  RTC_SX_LOAD register macros
 ****************************************************************************************
 */
#define RTC_SX_LOAD_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_LOAD))
#define RTC_SX_LOAD_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_LOAD, (value))
#define RTC_SX_LOAD_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_LOAD, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_LOAD) | (value))
#define RTC_SX_LOAD_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_LOAD, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_LOAD) & (~(value)))
          
      

/*
 *  RTC_SX_LOAD_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_LOAD_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_LOAD_F)
#define RTC_SX_LOAD_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_LOAD_F, 1)
#define RTC_SX_LOAD_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_LOAD_F, 0)


/*
 *  RTC_SX_DS register macros
 ****************************************************************************************
 */
#define RTC_SX_DS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_DS))
#define RTC_SX_DS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_DS, (value))
#define RTC_SX_DS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_DS, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_DS) | (value))
#define RTC_SX_DS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_DS, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_DS) & (~(value)))

/*
 *  RTC_SX_DS_VAL bit field macros
 ****************************************************************************************
 */
#define RTC_SX_DS_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_DS_VAL)
#define RTC_SX_DS_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_DS_VAL, (value))


/*
 *  RTC_SX_PDEN register macros
 ****************************************************************************************
 */
#define RTC_SX_PDEN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_PDEN))
#define RTC_SX_PDEN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_PDEN, (value))
#define RTC_SX_PDEN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_PDEN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_PDEN) | (value))
#define RTC_SX_PDEN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_PDEN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_PDEN) & (~(value)))

/*
 *  RTC_SX_PDEN_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_PDEN_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_PDEN_F)
#define RTC_SX_PDEN_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_PDEN_F, (value))


/*
 *  RTC_SX_PUEN register macros
 ****************************************************************************************
 */
#define RTC_SX_PUEN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_PUEN))
#define RTC_SX_PUEN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_PUEN, (value))
#define RTC_SX_PUEN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_PUEN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_PUEN) | (value))
#define RTC_SX_PUEN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_PUEN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_PUEN) & (~(value)))

/*
 *  RTC_SX_PUEN_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_PUEN_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_PUEN_F)
#define RTC_SX_PUEN_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_PUEN_F, (value))


/*
 *  RTC_SX_REGDS register macros
 ****************************************************************************************
 */
#define RTC_SX_REGDS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGDS))
#define RTC_SX_REGDS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGDS, (value))
#define RTC_SX_REGDS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGDS, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGDS) | (value))
#define RTC_SX_REGDS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGDS, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGDS) & (~(value)))

/*
 *  RTC_SX_REGDS_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_REGDS_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_REGDS_F)
#define RTC_SX_REGDS_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_REGDS_F, (value))


/*
 *  RTC_SX_REGPDEN register macros
 ****************************************************************************************
 */
#define RTC_SX_REGPDEN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGPDEN))
#define RTC_SX_REGPDEN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGPDEN, (value))
#define RTC_SX_REGPDEN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGPDEN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGPDEN) | (value))
#define RTC_SX_REGPDEN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGPDEN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGPDEN) & (~(value)))

/*
 *  RTC_SX_REGPDEN_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_REGPDEN_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_REGPDEN_F)
#define RTC_SX_REGPDEN_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_REGPDEN_F, (value))


/*
 *  RTC_SX_REGPUEN register macros
 ****************************************************************************************
 */
#define RTC_SX_REGPUEN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGPUEN))
#define RTC_SX_REGPUEN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGPUEN, (value))
#define RTC_SX_REGPUEN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGPUEN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGPUEN) | (value))
#define RTC_SX_REGPUEN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGPUEN, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_SX_REGPUEN) & (~(value)))

/*
 *  RTC_SX_REGPUEN_F bit field macros
 ****************************************************************************************
 */
#define RTC_SX_REGPUEN_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_SX_REGPUEN_F)
#define RTC_SX_REGPUEN_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_SX_REGPUEN_F, (value))


/*
 *  RTC_REG_RF_IO_CNTRL register macros
 ****************************************************************************************
 */
#define RTC_REG_RF_IO_CNTRL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_REG_RF_IO_CNTRL))
#define RTC_REG_RF_IO_CNTRL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_REG_RF_IO_CNTRL, (value))
#define RTC_REG_RF_IO_CNTRL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_REG_RF_IO_CNTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_REG_RF_IO_CNTRL) | (value))
#define RTC_REG_RF_IO_CNTRL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_REG_RF_IO_CNTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_REG_RF_IO_CNTRL) & (~(value)))

/*
 *  RTC_RF_IO_RTC_READY bit field macros
 ****************************************************************************************
 */
#define RTC_RF_IO_RTC_READY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RF_IO_RTC_READY)
#define RTC_RF_IO_RTC_READY_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RF_IO_RTC_READY, 1)
#define RTC_RF_IO_RTC_READY_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_RF_IO_RTC_READY, 0)

/*
 *  RTC_RF_IO_RTC_IO_I bit field macros
 ****************************************************************************************
 */
#define RTC_RF_IO_RTC_IO_I_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RF_IO_RTC_IO_I)
#define RTC_RF_IO_RTC_IO_I_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_RF_IO_RTC_IO_I, (value))

/*
 *  RTC_RF_IO_RTC_IO_OE bit field macros
 ****************************************************************************************
 */
#define RTC_RF_IO_RTC_IO_OE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_RF_IO_RTC_IO_OE)
#define RTC_RF_IO_RTC_IO_OE_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, RTC_RF_IO_RTC_IO_OE, (value))


/*
 *  RTC_REG_RF_PWR_CNTRL register macros
 ****************************************************************************************
 */
#define RTC_REG_RF_PWR_CNTRL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_REG_RF_PWR_CNTRL))
#define RTC_REG_RF_PWR_CNTRL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_REG_RF_PWR_CNTRL, (value))
#define RTC_REG_RF_PWR_CNTRL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_REG_RF_PWR_CNTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_REG_RF_PWR_CNTRL) | (value))
#define RTC_REG_RF_PWR_CNTRL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_REG_RF_PWR_CNTRL, GET_WORD_EXCLUSIVE_BITFIELD(addr, RTC_REG_RF_PWR_CNTRL) & (~(value)))

/*
 *  RTC_AX_RTC_READY bit field macros
 ****************************************************************************************
 */
#define RTC_AX_RTC_READY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_AX_RTC_READY)
#define RTC_AX_RTC_READY_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_AX_RTC_READY, 1)
#define RTC_AX_RTC_READY_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_AX_RTC_READY, 0)

/*
 *  RTC_AX_AVDD_EN bit field macros
 ****************************************************************************************
 */
#define RTC_AX_AVDD_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_AX_AVDD_EN)
#define RTC_AX_AVDD_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_AX_AVDD_EN, 1)
#define RTC_AX_AVDD_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_AX_AVDD_EN, 0)

/*
 *  RTC_TX_PA_RTC_READY bit field macros
 ****************************************************************************************
 */
#define RTC_TX_PA_RTC_READY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, RTC_TX_PA_RTC_READY)
#define RTC_TX_PA_RTC_READY_SET(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_TX_PA_RTC_READY, 1)
#define RTC_TX_PA_RTC_READY_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, RTC_TX_PA_RTC_READY, 0)
          
          
          
/*
 *  SX_EN_ULDO register macros
 ****************************************************************************************
 */
#define SX_EN_ULDO_GET(addr) \
        GET_WORD_BITFIELD_N(addr, SX_EN_ULDO)
#define SX_EN_ULDO_SET(addr) \
        SET_WORD_BITFIELD_N(addr, SX_EN_ULDO, 1)
#define SX_EN_ULDO_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, SX_EN_ULDO, 0)          

#endif
