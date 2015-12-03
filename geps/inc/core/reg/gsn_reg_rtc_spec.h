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
* $RCSfile: gsn_reg_rtc_spec.h,v $
*
* Description : This file contains RTC registers specifications.
*****************************************************************************/


#ifndef _REG_RTC_H
#define _REG_RTC_H

/***************************************************
 *
 *             RTC
 *
 ***************************************************/


/*
 *  RTC instance offsets
 ****************************************************************************************
 */
 #define RTC 0x41000000

/*
 *  RTC_GPIO_IE register defines
 ****************************************************************************************
 */
#define RTC_GPIO_IE_OFFSETADDRESS      0x00000010  /* RW */
#define RTC_GPIO_IE_BITOFFSET          0
#define RTC_GPIO_IE_BITFIELDSIZE       32
#define RTC_GPIO_IE_BITMASK            0xFFFFFFFF
#define RTC_GPIO_IE_INIT               0x00000000
/*
 *  RTC_GPIO_IE_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_GPIO_IE_VAL_OFFSETADDRESS           RTC_GPIO_IE_OFFSETADDRESS
#define RTC_GPIO_IE_VAL_BITOFFSET               0
#define RTC_GPIO_IE_VAL_BITFIELDSIZE            6
#define RTC_GPIO_IE_VAL_BITMASK                 0x0000003f
#define RTC_GPIO_IE_VAL_INIT                    0x0

/*
 *  RTC_GPIO_IN register defines
 ****************************************************************************************
 */
#define RTC_GPIO_IN_OFFSETADDRESS      0x00000014  /* R */
#define RTC_GPIO_IN_BITOFFSET          0
#define RTC_GPIO_IN_BITFIELDSIZE       32
#define RTC_GPIO_IN_BITMASK            0xFFFFFFFF
#define RTC_GPIO_IN_INIT               0x00000000
/*
 *  RTC_GPIO_IN_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_GPIO_IN_VAL_OFFSETADDRESS           RTC_GPIO_IN_OFFSETADDRESS
#define RTC_GPIO_IN_VAL_BITOFFSET               0
#define RTC_GPIO_IN_VAL_BITFIELDSIZE            6
#define RTC_GPIO_IN_VAL_BITMASK                 0x0000003f
#define RTC_GPIO_IN_VAL_INIT                    0x0

/*
 *  RTC_GPIO_OUT register defines
 ****************************************************************************************
 */
#define RTC_GPIO_OUT_OFFSETADDRESS     0x00000018  /* RW */
#define RTC_GPIO_OUT_BITOFFSET         0
#define RTC_GPIO_OUT_BITFIELDSIZE      32
#define RTC_GPIO_OUT_BITMASK           0xFFFFFFFF
#define RTC_GPIO_OUT_INIT              0x00000000
/*
 *  RTC_GPIO_OUT_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_GPIO_OUT_VAL_OFFSETADDRESS          RTC_GPIO_OUT_OFFSETADDRESS
#define RTC_GPIO_OUT_VAL_BITOFFSET              0
#define RTC_GPIO_OUT_VAL_BITFIELDSIZE           6
#define RTC_GPIO_OUT_VAL_BITMASK                0x0000003f
#define RTC_GPIO_OUT_VAL_INIT                   0x0

/*
 *  RTC_GPIO_OE register defines
 ****************************************************************************************
 */
#define RTC_GPIO_OE_OFFSETADDRESS      0x0000001c  /* RW */
#define RTC_GPIO_OE_BITOFFSET          0
#define RTC_GPIO_OE_BITFIELDSIZE       32
#define RTC_GPIO_OE_BITMASK            0xFFFFFFFF
#define RTC_GPIO_OE_INIT               0x00000000
/*
 *  RTC_GPIO_OE_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_GPIO_OE_VAL_OFFSETADDRESS           RTC_GPIO_OE_OFFSETADDRESS
#define RTC_GPIO_OE_VAL_BITOFFSET               0
#define RTC_GPIO_OE_VAL_BITFIELDSIZE            6
#define RTC_GPIO_OE_VAL_BITMASK                 0x0000003f
#define RTC_GPIO_OE_VAL_INIT                    0x0

/*
 *  RTC_GPIO_CTL register defines
 ****************************************************************************************
 */
#define RTC_GPIO_CTL_OFFSETADDRESS     0x00000020  /* RW */
#define RTC_GPIO_CTL_BITOFFSET         0
#define RTC_GPIO_CTL_BITFIELDSIZE      32
#define RTC_GPIO_CTL_BITMASK           0xFFFFFFFF
#define RTC_GPIO_CTL_INIT              0x00000000
/*
 *  RTC_GPIO_CTL_0 bit field defines
 ****************************************************************************************
 */
#define RTC_GPIO_CTL_0_OFFSETADDRESS            RTC_GPIO_CTL_OFFSETADDRESS
#define RTC_GPIO_CTL_0_BITOFFSET                0
#define RTC_GPIO_CTL_0_BITFIELDSIZE             4
#define RTC_GPIO_CTL_0_BITMASK                  0x0000000f
#define RTC_GPIO_CTL_0_INIT                     0x0
/*
 *  RTC_GPIO_CTL_1 bit field defines
 ****************************************************************************************
 */
#define RTC_GPIO_CTL_1_OFFSETADDRESS            RTC_GPIO_CTL_OFFSETADDRESS
#define RTC_GPIO_CTL_1_BITOFFSET                4
#define RTC_GPIO_CTL_1_BITFIELDSIZE             4
#define RTC_GPIO_CTL_1_BITMASK                  0x000000f0
#define RTC_GPIO_CTL_1_INIT                     0x0
/*
 *  RTC_GPIO_CTL_2 bit field defines
 ****************************************************************************************
 */
#define RTC_GPIO_CTL_2_OFFSETADDRESS            RTC_GPIO_CTL_OFFSETADDRESS
#define RTC_GPIO_CTL_2_BITOFFSET                8
#define RTC_GPIO_CTL_2_BITFIELDSIZE             4
#define RTC_GPIO_CTL_2_BITMASK                  0x00000f00
#define RTC_GPIO_CTL_2_INIT                     0x0
/*
 *  RTC_GPIO_CTL_3 bit field defines
 ****************************************************************************************
 */
#define RTC_GPIO_CTL_3_OFFSETADDRESS            RTC_GPIO_CTL_OFFSETADDRESS
#define RTC_GPIO_CTL_3_BITOFFSET               12
#define RTC_GPIO_CTL_3_BITFIELDSIZE             4
#define RTC_GPIO_CTL_3_BITMASK                  0x0000f000
#define RTC_GPIO_CTL_3_INIT                     0x0
/*
 *  RTC_GPIO_CTL_4 bit field defines
 ****************************************************************************************
 */
#define RTC_GPIO_CTL_4_OFFSETADDRESS            RTC_GPIO_CTL_OFFSETADDRESS
#define RTC_GPIO_CTL_4_BITOFFSET               16
#define RTC_GPIO_CTL_4_BITFIELDSIZE             4
#define RTC_GPIO_CTL_4_BITMASK                  0x000f0000
#define RTC_GPIO_CTL_4_INIT                     0x0
/*
 *  RTC_GPIO_CTL_5 bit field defines
 ****************************************************************************************
 */
#define RTC_GPIO_CTL_5_OFFSETADDRESS            RTC_GPIO_CTL_OFFSETADDRESS
#define RTC_GPIO_CTL_5_BITOFFSET               20
#define RTC_GPIO_CTL_5_BITFIELDSIZE             4
#define RTC_GPIO_CTL_5_BITMASK                  0x00f00000
#define RTC_GPIO_CTL_5_INIT                     0x0

/*
 *  RTC_DCDC_CTL register defines
 ****************************************************************************************
 */
#define RTC_DCDC_CTL_OFFSETADDRESS     0x00000024  /* RW */
#define RTC_DCDC_CTL_BITOFFSET         0
#define RTC_DCDC_CTL_BITFIELDSIZE      32
#define RTC_DCDC_CTL_BITMASK           0xFFFFFFFF
#define RTC_DCDC_CTL_INIT              0x00000000
/*
 *  RTC_DCDC_CTL_0 bit field defines
 ****************************************************************************************
 */
#define RTC_DCDC_CTL_0_OFFSETADDRESS            RTC_DCDC_CTL_OFFSETADDRESS
#define RTC_DCDC_CTL_0_BITOFFSET                0
#define RTC_DCDC_CTL_0_BITFIELDSIZE             1
#define RTC_DCDC_CTL_0_BITMASK                  0x00000001
#define RTC_DCDC_CTL_0_INIT                     0x0
/*
 *  RTC_DCDC_CTL_1 bit field defines
 ****************************************************************************************
 */
#define RTC_DCDC_CTL_1_OFFSETADDRESS            RTC_DCDC_CTL_OFFSETADDRESS
#define RTC_DCDC_CTL_1_BITOFFSET                1
#define RTC_DCDC_CTL_1_BITFIELDSIZE             1
#define RTC_DCDC_CTL_1_BITMASK                  0x00000002
#define RTC_DCDC_CTL_1_INIT                     0x0

/*
 *  RTC_SM_WU_CTL register defines
 ****************************************************************************************
 */
#define RTC_SM_WU_CTL_OFFSETADDRESS    0x00000050  /* RW */
#define RTC_SM_WU_CTL_BITOFFSET        0
#define RTC_SM_WU_CTL_BITFIELDSIZE     32
#define RTC_SM_WU_CTL_BITMASK          0xFFFFFFFF
#define RTC_SM_WU_CTL_INIT             0x00000000
/*
 *  RTC_SM_WU_CTL_POR_EVENT bit field defines
 ****************************************************************************************
 */
#define RTC_SM_WU_CTL_POR_EVENT_OFFSETADDRESS   RTC_SM_WU_CTL_OFFSETADDRESS
#define RTC_SM_WU_CTL_POR_EVENT_BITOFFSET       0
#define RTC_SM_WU_CTL_POR_EVENT_BITFIELDSIZE    1
#define RTC_SM_WU_CTL_POR_EVENT_BITMASK         0x00000001
#define RTC_SM_WU_CTL_POR_EVENT_INIT            0x0
/*
 *  RTC_SM_WU_CTL_BOOT_CLK_ACTV bit field defines
 ****************************************************************************************
 */
#define RTC_SM_WU_CTL_BOOT_CLK_ACTV_OFFSETADDRESS RTC_SM_WU_CTL_OFFSETADDRESS
#define RTC_SM_WU_CTL_BOOT_CLK_ACTV_BITOFFSET   1
#define RTC_SM_WU_CTL_BOOT_CLK_ACTV_BITFIELDSIZE  1
#define RTC_SM_WU_CTL_BOOT_CLK_ACTV_BITMASK     0x00000002
#define RTC_SM_WU_CTL_BOOT_CLK_ACTV_INIT        0x0

/*
 *  RTC_SM_WU_SB_REQ register defines
 ****************************************************************************************
 */
#define RTC_SM_WU_SB_REQ_OFFSETADDRESS 0x00000054  /* RW */
#define RTC_SM_WU_SB_REQ_BITOFFSET     0
#define RTC_SM_WU_SB_REQ_BITFIELDSIZE  32
#define RTC_SM_WU_SB_REQ_BITMASK       0xFFFFFFFF
#define RTC_SM_WU_SB_REQ_INIT          0x00000000
/*
 *  RTC_SM_WU_SB_REQ_EN bit field defines
 ****************************************************************************************
 */
#define RTC_SM_WU_SB_REQ_EN_OFFSETADDRESS       RTC_SM_WU_SB_REQ_OFFSETADDRESS
#define RTC_SM_WU_SB_REQ_EN_BITOFFSET           0
#define RTC_SM_WU_SB_REQ_EN_BITFIELDSIZE        1
#define RTC_SM_WU_SB_REQ_EN_BITMASK             0x00000001
#define RTC_SM_WU_SB_REQ_EN_INIT                0x0

/*
 *  RTC_SM_RTC_CLK_SEL register defines
 ****************************************************************************************
 */
#define RTC_SM_RTC_CLK_SEL_OFFSETADDRESS 0x00000058  /* RW */
#define RTC_SM_RTC_CLK_SEL_BITOFFSET   0
#define RTC_SM_RTC_CLK_SEL_BITFIELDSIZE 32
#define RTC_SM_RTC_CLK_SEL_BITMASK     0xFFFFFFFF
#define RTC_SM_RTC_CLK_SEL_INIT        0x00000000
/*
 *  RTC_SM_RTC_CLK_MUX_SEL bit field defines
 ****************************************************************************************
 */
#define RTC_SM_RTC_CLK_MUX_SEL_OFFSETADDRESS    RTC_SM_RTC_CLK_SEL_OFFSETADDRESS
#define RTC_SM_RTC_CLK_MUX_SEL_BITOFFSET        0
#define RTC_SM_RTC_CLK_MUX_SEL_BITFIELDSIZE     1
#define RTC_SM_RTC_CLK_MUX_SEL_BITMASK          0x00000001
#define RTC_SM_RTC_CLK_MUX_SEL_INIT             0x0

/*
 *  RTC_SM_SB_CLK_REQ register defines
 ****************************************************************************************
 */
#define RTC_SM_SB_CLK_REQ_OFFSETADDRESS 0x0000005c  /* RW */
#define RTC_SM_SB_CLK_REQ_BITOFFSET    0
#define RTC_SM_SB_CLK_REQ_BITFIELDSIZE 32
#define RTC_SM_SB_CLK_REQ_BITMASK      0xFFFFFFFF
#define RTC_SM_SB_CLK_REQ_INIT         0x00000000
/*
 *  RTC_SM_SB_CLK_REQ_LP_RC bit field defines
 ****************************************************************************************
 */
#define RTC_SM_SB_CLK_REQ_LP_RC_OFFSETADDRESS   RTC_SM_SB_CLK_REQ_OFFSETADDRESS
#define RTC_SM_SB_CLK_REQ_LP_RC_BITOFFSET       0
#define RTC_SM_SB_CLK_REQ_LP_RC_BITFIELDSIZE    1
#define RTC_SM_SB_CLK_REQ_LP_RC_BITMASK         0x00000001
#define RTC_SM_SB_CLK_REQ_LP_RC_INIT            0x0
/*
 *  RTC_SM_SB_CLK_REQ_LP_XTAL bit field defines
 ****************************************************************************************
 */
#define RTC_SM_SB_CLK_REQ_LP_XTAL_OFFSETADDRESS RTC_SM_SB_CLK_REQ_OFFSETADDRESS
#define RTC_SM_SB_CLK_REQ_LP_XTAL_BITOFFSET     1
#define RTC_SM_SB_CLK_REQ_LP_XTAL_BITFIELDSIZE  1
#define RTC_SM_SB_CLK_REQ_LP_XTAL_BITMASK       0x00000002
#define RTC_SM_SB_CLK_REQ_LP_XTAL_INIT          0x0
/*
 *  RTC_SM_SB_CLK_REQ_HS_RC bit field defines
 ****************************************************************************************
 */
#define RTC_SM_SB_CLK_REQ_HS_RC_OFFSETADDRESS   RTC_SM_SB_CLK_REQ_OFFSETADDRESS
#define RTC_SM_SB_CLK_REQ_HS_RC_BITOFFSET       2
#define RTC_SM_SB_CLK_REQ_HS_RC_BITFIELDSIZE    1
#define RTC_SM_SB_CLK_REQ_HS_RC_BITMASK         0x00000004
#define RTC_SM_SB_CLK_REQ_HS_RC_INIT            0x0
/*
 *  RTC_SM_SB_CLK_REQ_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define RTC_SM_SB_CLK_REQ_HS_XTAL_OFFSETADDRESS RTC_SM_SB_CLK_REQ_OFFSETADDRESS
#define RTC_SM_SB_CLK_REQ_HS_XTAL_BITOFFSET     3
#define RTC_SM_SB_CLK_REQ_HS_XTAL_BITFIELDSIZE  1
#define RTC_SM_SB_CLK_REQ_HS_XTAL_BITMASK       0x00000008
#define RTC_SM_SB_CLK_REQ_HS_XTAL_INIT          0x0
/*
 *  RTC_SM_SB_CLK_REQ_PLL bit field defines
 ****************************************************************************************
 */
#define RTC_SM_SB_CLK_REQ_PLL_OFFSETADDRESS     RTC_SM_SB_CLK_REQ_OFFSETADDRESS
#define RTC_SM_SB_CLK_REQ_PLL_BITOFFSET         4
#define RTC_SM_SB_CLK_REQ_PLL_BITFIELDSIZE      1
#define RTC_SM_SB_CLK_REQ_PLL_BITMASK           0x00000010
#define RTC_SM_SB_CLK_REQ_PLL_INIT              0x0

/*
 *  RTC_SM_WK_CLK_REQ register defines
 ****************************************************************************************
 */
#define RTC_SM_WK_CLK_REQ_OFFSETADDRESS 0x00000060  /* RW */
#define RTC_SM_WK_CLK_REQ_BITOFFSET    0
#define RTC_SM_WK_CLK_REQ_BITFIELDSIZE 32
#define RTC_SM_WK_CLK_REQ_BITMASK      0xFFFFFFFF
#define RTC_SM_WK_CLK_REQ_INIT         0x00000000
/*
 *  RTC_SM_WK_CLK_REQ_LP_RC bit field defines
 ****************************************************************************************
 */
#define RTC_SM_WK_CLK_REQ_LP_RC_OFFSETADDRESS   RTC_SM_WK_CLK_REQ_OFFSETADDRESS
#define RTC_SM_WK_CLK_REQ_LP_RC_BITOFFSET       0
#define RTC_SM_WK_CLK_REQ_LP_RC_BITFIELDSIZE    1
#define RTC_SM_WK_CLK_REQ_LP_RC_BITMASK         0x00000001
#define RTC_SM_WK_CLK_REQ_LP_RC_INIT            0x0
/*
 *  RTC_SM_WK_CLK_REQ_LP_XTAL bit field defines
 ****************************************************************************************
 */
#define RTC_SM_WK_CLK_REQ_LP_XTAL_OFFSETADDRESS RTC_SM_WK_CLK_REQ_OFFSETADDRESS
#define RTC_SM_WK_CLK_REQ_LP_XTAL_BITOFFSET     1
#define RTC_SM_WK_CLK_REQ_LP_XTAL_BITFIELDSIZE  1
#define RTC_SM_WK_CLK_REQ_LP_XTAL_BITMASK       0x00000002
#define RTC_SM_WK_CLK_REQ_LP_XTAL_INIT          0x0
/*
 *  RTC_SM_WK_CLK_REQ_HS_RC bit field defines
 ****************************************************************************************
 */
#define RTC_SM_WK_CLK_REQ_HS_RC_OFFSETADDRESS   RTC_SM_WK_CLK_REQ_OFFSETADDRESS
#define RTC_SM_WK_CLK_REQ_HS_RC_BITOFFSET       2
#define RTC_SM_WK_CLK_REQ_HS_RC_BITFIELDSIZE    1
#define RTC_SM_WK_CLK_REQ_HS_RC_BITMASK         0x00000004
#define RTC_SM_WK_CLK_REQ_HS_RC_INIT            0x0
/*
 *  RTC_SM_WK_CLK_REQ_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define RTC_SM_WK_CLK_REQ_HS_XTAL_OFFSETADDRESS RTC_SM_WK_CLK_REQ_OFFSETADDRESS
#define RTC_SM_WK_CLK_REQ_HS_XTAL_BITOFFSET     3
#define RTC_SM_WK_CLK_REQ_HS_XTAL_BITFIELDSIZE  1
#define RTC_SM_WK_CLK_REQ_HS_XTAL_BITMASK       0x00000008
#define RTC_SM_WK_CLK_REQ_HS_XTAL_INIT          0x0
/*
 *  RTC_SM_WK_CLK_REQ_PLL bit field defines
 ****************************************************************************************
 */
#define RTC_SM_WK_CLK_REQ_PLL_OFFSETADDRESS     RTC_SM_WK_CLK_REQ_OFFSETADDRESS
#define RTC_SM_WK_CLK_REQ_PLL_BITOFFSET         4
#define RTC_SM_WK_CLK_REQ_PLL_BITFIELDSIZE      1
#define RTC_SM_WK_CLK_REQ_PLL_BITMASK           0x00000010
#define RTC_SM_WK_CLK_REQ_PLL_INIT              0x0

/*
 *  RTC_SM_DCDC_TMR_CTL register defines
 ****************************************************************************************
 */
#define RTC_SM_DCDC_TMR_CTL_OFFSETADDRESS 0x00000064  /* RW */
#define RTC_SM_DCDC_TMR_CTL_BITOFFSET  0
#define RTC_SM_DCDC_TMR_CTL_BITFIELDSIZE 32
#define RTC_SM_DCDC_TMR_CTL_BITMASK    0xFFFFFFFF
#define RTC_SM_DCDC_TMR_CTL_INIT       0x00000000
/*
 *  RTC_SM_DCDC_TMR_CTL_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_SM_DCDC_TMR_CTL_VAL_OFFSETADDRESS   RTC_SM_DCDC_TMR_CTL_OFFSETADDRESS
#define RTC_SM_DCDC_TMR_CTL_VAL_BITOFFSET       0
#define RTC_SM_DCDC_TMR_CTL_VAL_BITFIELDSIZE    8
#define RTC_SM_DCDC_TMR_CTL_VAL_BITMASK         0x000000ff
#define RTC_SM_DCDC_TMR_CTL_VAL_INIT            0x0

/*
 *  RTC_SM_MASK_RST register defines
 ****************************************************************************************
 */
#define RTC_SM_MASK_RST_OFFSETADDRESS  0x00000068  /* RW */
#define RTC_SM_MASK_RST_BITOFFSET      0
#define RTC_SM_MASK_RST_BITFIELDSIZE   32
#define RTC_SM_MASK_RST_BITMASK        0xFFFFFFFF
#define RTC_SM_MASK_RST_INIT           0x00000000
/*
 *  RTC_SM_MASK_RST_POR_ACM3 bit field defines
 ****************************************************************************************
 */
#define RTC_SM_MASK_RST_POR_ACM3_OFFSETADDRESS  RTC_SM_MASK_RST_OFFSETADDRESS
#define RTC_SM_MASK_RST_POR_ACM3_BITOFFSET      0
#define RTC_SM_MASK_RST_POR_ACM3_BITFIELDSIZE   1
#define RTC_SM_MASK_RST_POR_ACM3_BITMASK        0x00000001
#define RTC_SM_MASK_RST_POR_ACM3_INIT           0x0
/*
 *  RTC_SM_MASK_RST_POR_WCM3 bit field defines
 ****************************************************************************************
 */
#define RTC_SM_MASK_RST_POR_WCM3_OFFSETADDRESS  RTC_SM_MASK_RST_OFFSETADDRESS
#define RTC_SM_MASK_RST_POR_WCM3_BITOFFSET      1
#define RTC_SM_MASK_RST_POR_WCM3_BITFIELDSIZE   1
#define RTC_SM_MASK_RST_POR_WCM3_BITMASK        0x00000002
#define RTC_SM_MASK_RST_POR_WCM3_INIT           0x0
/*
 *  RTC_SM_MASK_RST_APP bit field defines
 ****************************************************************************************
 */
#define RTC_SM_MASK_RST_APP_OFFSETADDRESS       RTC_SM_MASK_RST_OFFSETADDRESS
#define RTC_SM_MASK_RST_APP_BITOFFSET           2
#define RTC_SM_MASK_RST_APP_BITFIELDSIZE        1
#define RTC_SM_MASK_RST_APP_BITMASK             0x00000004
#define RTC_SM_MASK_RST_APP_INIT                0x0
/*
 *  RTC_SM_MASK_RST_WLAN bit field defines
 ****************************************************************************************
 */
#define RTC_SM_MASK_RST_WLAN_OFFSETADDRESS      RTC_SM_MASK_RST_OFFSETADDRESS
#define RTC_SM_MASK_RST_WLAN_BITOFFSET          3
#define RTC_SM_MASK_RST_WLAN_BITFIELDSIZE       1
#define RTC_SM_MASK_RST_WLAN_BITMASK            0x00000008
#define RTC_SM_MASK_RST_WLAN_INIT               0x0
/*
 *  RTC_SM_MASK_RST_CRYPTO bit field defines
 ****************************************************************************************
 */
#define RTC_SM_MASK_RST_CRYPTO_OFFSETADDRESS    RTC_SM_MASK_RST_OFFSETADDRESS
#define RTC_SM_MASK_RST_CRYPTO_BITOFFSET        4
#define RTC_SM_MASK_RST_CRYPTO_BITFIELDSIZE     1
#define RTC_SM_MASK_RST_CRYPTO_BITMASK          0x00000010
#define RTC_SM_MASK_RST_CRYPTO_INIT             0x0

/*
 *  RTC_SM_WAKEUP_SOURCES register defines
 ****************************************************************************************
 */
#define RTC_SM_WAKEUP_SOURCES_OFFSETADDRESS 0x00000070  /* R */
#define RTC_SM_WAKEUP_SOURCES_BITOFFSET 0
#define RTC_SM_WAKEUP_SOURCES_BITFIELDSIZE 32
#define RTC_SM_WAKEUP_SOURCES_BITMASK  0xFFFFFFFF
#define RTC_SM_WAKEUP_SOURCES_INIT     0x00000000
/*
 *  RTC_SM_WAKEUP_SOURCE_ALARM bit field defines
 ****************************************************************************************
 */
#define RTC_SM_WAKEUP_SOURCE_ALARM_OFFSETADDRESS RTC_SM_WAKEUP_SOURCES_OFFSETADDRESS
#define RTC_SM_WAKEUP_SOURCE_ALARM_BITOFFSET    0
#define RTC_SM_WAKEUP_SOURCE_ALARM_BITFIELDSIZE  5
#define RTC_SM_WAKEUP_SOURCE_ALARM_BITMASK      0x0000001f
#define RTC_SM_WAKEUP_SOURCE_ALARM_INIT         0x0
/*
 *  RTC_SM_WAKEUP_SOURCE_POR bit field defines
 ****************************************************************************************
 */
#define RTC_SM_WAKEUP_SOURCE_POR_OFFSETADDRESS  RTC_SM_WAKEUP_SOURCES_OFFSETADDRESS
#define RTC_SM_WAKEUP_SOURCE_POR_BITOFFSET      5
#define RTC_SM_WAKEUP_SOURCE_POR_BITFIELDSIZE   1
#define RTC_SM_WAKEUP_SOURCE_POR_BITMASK        0x00000020
#define RTC_SM_WAKEUP_SOURCE_POR_INIT           0x0
/*
 *  RTC_SM_WAKEUP_SOURCE_TMR bit field defines
 ****************************************************************************************
 */
#define RTC_SM_WAKEUP_SOURCE_TMR_OFFSETADDRESS  RTC_SM_WAKEUP_SOURCES_OFFSETADDRESS
#define RTC_SM_WAKEUP_SOURCE_TMR_BITOFFSET      6
#define RTC_SM_WAKEUP_SOURCE_TMR_BITFIELDSIZE   1
#define RTC_SM_WAKEUP_SOURCE_TMR_BITMASK        0x00000040
#define RTC_SM_WAKEUP_SOURCE_TMR_INIT           0x0

/*
 *  RTC_SM_ALARM_CLK_REQ register defines
 ****************************************************************************************
 */
#define RTC_SM_ALARM_CLK_REQ_OFFSETADDRESS 0x00000074  /* RW */
#define RTC_SM_ALARM_CLK_REQ_BITOFFSET 0
#define RTC_SM_ALARM_CLK_REQ_BITFIELDSIZE 32
#define RTC_SM_ALARM_CLK_REQ_BITMASK   0xFFFFFFFF
#define RTC_SM_ALARM_CLK_REQ_INIT      0x00000000
/*
 *  RTC_SM_ALARM_CLK_REQ_LP_RC bit field defines
 ****************************************************************************************
 */
#define RTC_SM_ALARM_CLK_REQ_LP_RC_OFFSETADDRESS RTC_SM_ALARM_CLK_REQ_OFFSETADDRESS
#define RTC_SM_ALARM_CLK_REQ_LP_RC_BITOFFSET    0
#define RTC_SM_ALARM_CLK_REQ_LP_RC_BITFIELDSIZE  1
#define RTC_SM_ALARM_CLK_REQ_LP_RC_BITMASK      0x00000001
#define RTC_SM_ALARM_CLK_REQ_LP_RC_INIT         0x0
/*
 *  RTC_SM_ALARM_CLK_REQ_LP_XTAL bit field defines
 ****************************************************************************************
 */
#define RTC_SM_ALARM_CLK_REQ_LP_XTAL_OFFSETADDRESS RTC_SM_ALARM_CLK_REQ_OFFSETADDRESS
#define RTC_SM_ALARM_CLK_REQ_LP_XTAL_BITOFFSET  1
#define RTC_SM_ALARM_CLK_REQ_LP_XTAL_BITFIELDSIZE  1
#define RTC_SM_ALARM_CLK_REQ_LP_XTAL_BITMASK    0x00000002
#define RTC_SM_ALARM_CLK_REQ_LP_XTAL_INIT       0x0
/*
 *  RTC_SM_ALARM_CLK_REQ_HS_RC bit field defines
 ****************************************************************************************
 */
#define RTC_SM_ALARM_CLK_REQ_HS_RC_OFFSETADDRESS RTC_SM_ALARM_CLK_REQ_OFFSETADDRESS
#define RTC_SM_ALARM_CLK_REQ_HS_RC_BITOFFSET    2
#define RTC_SM_ALARM_CLK_REQ_HS_RC_BITFIELDSIZE  1
#define RTC_SM_ALARM_CLK_REQ_HS_RC_BITMASK      0x00000004
#define RTC_SM_ALARM_CLK_REQ_HS_RC_INIT         0x0
/*
 *  RTC_SM_ALARM_CLK_REQ_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define RTC_SM_ALARM_CLK_REQ_HS_XTAL_OFFSETADDRESS RTC_SM_ALARM_CLK_REQ_OFFSETADDRESS
#define RTC_SM_ALARM_CLK_REQ_HS_XTAL_BITOFFSET  3
#define RTC_SM_ALARM_CLK_REQ_HS_XTAL_BITFIELDSIZE  1
#define RTC_SM_ALARM_CLK_REQ_HS_XTAL_BITMASK    0x00000008
#define RTC_SM_ALARM_CLK_REQ_HS_XTAL_INIT       0x0
/*
 *  RTC_SM_ALARM_CLK_REQ_PLL bit field defines
 ****************************************************************************************
 */
#define RTC_SM_ALARM_CLK_REQ_PLL_OFFSETADDRESS  RTC_SM_ALARM_CLK_REQ_OFFSETADDRESS
#define RTC_SM_ALARM_CLK_REQ_PLL_BITOFFSET      4
#define RTC_SM_ALARM_CLK_REQ_PLL_BITFIELDSIZE   1
#define RTC_SM_ALARM_CLK_REQ_PLL_BITMASK        0x00000010
#define RTC_SM_ALARM_CLK_REQ_PLL_INIT           0x0

/*
 *  RTC_TRNG_OSC_STOP_N register defines
 ****************************************************************************************
 */
#define RTC_TRNG_OSC_STOP_N_OFFSETADDRESS 0x00000078  /* RW */
#define RTC_TRNG_OSC_STOP_N_BITOFFSET  0
#define RTC_TRNG_OSC_STOP_N_BITFIELDSIZE 32
#define RTC_TRNG_OSC_STOP_N_BITMASK    0xFFFFFFFF
#define RTC_TRNG_OSC_STOP_N_INIT       0x00000000
/*
 *  RTC_TRNG_OSC_STOP_N_F bit field defines
 ****************************************************************************************
 */
#define RTC_TRNG_OSC_STOP_N_F_OFFSETADDRESS     RTC_TRNG_OSC_STOP_N_OFFSETADDRESS
#define RTC_TRNG_OSC_STOP_N_F_BITOFFSET         0
#define RTC_TRNG_OSC_STOP_N_F_BITFIELDSIZE      1
#define RTC_TRNG_OSC_STOP_N_F_BITMASK           0x00000001
#define RTC_TRNG_OSC_STOP_N_F_INIT              0x0

/*
 *  RTC_SRAM_ISO_EN register defines
 ****************************************************************************************
 */
#define RTC_SRAM_ISO_EN_OFFSETADDRESS  0x0000007c  /* RW */
#define RTC_SRAM_ISO_EN_BITOFFSET      0
#define RTC_SRAM_ISO_EN_BITFIELDSIZE   32
#define RTC_SRAM_ISO_EN_BITMASK        0xFFFFFFFF
#define RTC_SRAM_ISO_EN_INIT           0x00000000
/*
 *  RTC_SRAM_ISO_ENABLE bit field defines
 ****************************************************************************************
 */
#define RTC_SRAM_ISO_ENABLE_OFFSETADDRESS       RTC_SRAM_ISO_EN_OFFSETADDRESS
#define RTC_SRAM_ISO_ENABLE_BITOFFSET           0
#define RTC_SRAM_ISO_ENABLE_BITFIELDSIZE        1
#define RTC_SRAM_ISO_ENABLE_BITMASK             0x00000001
#define RTC_SRAM_ISO_ENABLE_INIT                0x0

/*
 *  RTC_PCNT_WU_LSB register defines
 ****************************************************************************************
 */
#define RTC_PCNT_WU_LSB_OFFSETADDRESS  0x00000088  /* RW */
#define RTC_PCNT_WU_LSB_BITOFFSET      0
#define RTC_PCNT_WU_LSB_BITFIELDSIZE   32
#define RTC_PCNT_WU_LSB_BITMASK        0xFFFFFFFF
#define RTC_PCNT_WU_LSB_INIT           0x00000000
/*
 *  RTC_PCNT_WU_LSB_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_PCNT_WU_LSB_VAL_OFFSETADDRESS       RTC_PCNT_WU_LSB_OFFSETADDRESS
#define RTC_PCNT_WU_LSB_VAL_BITOFFSET           0
#define RTC_PCNT_WU_LSB_VAL_BITFIELDSIZE       32
#define RTC_PCNT_WU_LSB_VAL_BITMASK             0xffffffff
#define RTC_PCNT_WU_LSB_VAL_INIT                0x0

/*
 *  RTC_PCNT_WU_MSB register defines
 ****************************************************************************************
 */
#define RTC_PCNT_WU_MSB_OFFSETADDRESS  0x0000008c  /* RW */
#define RTC_PCNT_WU_MSB_BITOFFSET      0
#define RTC_PCNT_WU_MSB_BITFIELDSIZE   32
#define RTC_PCNT_WU_MSB_BITMASK        0xFFFFFFFF
#define RTC_PCNT_WU_MSB_INIT           0x00000000
/*
 *  RTC_PCNT_WU_MSB_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_PCNT_WU_MSB_VAL_OFFSETADDRESS       RTC_PCNT_WU_MSB_OFFSETADDRESS
#define RTC_PCNT_WU_MSB_VAL_BITOFFSET           0
#define RTC_PCNT_WU_MSB_VAL_BITFIELDSIZE       32
#define RTC_PCNT_WU_MSB_VAL_BITMASK             0xffffffff
#define RTC_PCNT_WU_MSB_VAL_INIT                0x0

/*
 *  RTC_RTC_PCNT_IRQ_STS register defines
 ****************************************************************************************
 */
#define RTC_RTC_PCNT_IRQ_STS_OFFSETADDRESS 0x00000090  /* R */
#define RTC_RTC_PCNT_IRQ_STS_BITOFFSET 0
#define RTC_RTC_PCNT_IRQ_STS_BITFIELDSIZE 32
#define RTC_RTC_PCNT_IRQ_STS_BITMASK   0xFFFFFFFF
#define RTC_RTC_PCNT_IRQ_STS_INIT      0x00000000
/*
 *  RTC_RTC_PCNT_IRQ_STATUS bit field defines
 ****************************************************************************************
 */
#define RTC_RTC_PCNT_IRQ_STATUS_OFFSETADDRESS   RTC_RTC_PCNT_IRQ_STS_OFFSETADDRESS
#define RTC_RTC_PCNT_IRQ_STATUS_BITOFFSET       0
#define RTC_RTC_PCNT_IRQ_STATUS_BITFIELDSIZE    1
#define RTC_RTC_PCNT_IRQ_STATUS_BITMASK         0x00000001
#define RTC_RTC_PCNT_IRQ_STATUS_INIT            0x0

/*
 *  RTC_RTC_PCNT_IRQ_MASK register defines
 ****************************************************************************************
 */
#define RTC_RTC_PCNT_IRQ_MASK_OFFSETADDRESS 0x00000094  /* RW */
#define RTC_RTC_PCNT_IRQ_MASK_BITOFFSET 0
#define RTC_RTC_PCNT_IRQ_MASK_BITFIELDSIZE 32
#define RTC_RTC_PCNT_IRQ_MASK_BITMASK  0xFFFFFFFF
#define RTC_RTC_PCNT_IRQ_MASK_INIT     0x00000000
/*
 *  RTC_RTC_PCNT_IRQ_MASK_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_RTC_PCNT_IRQ_MASK_VAL_OFFSETADDRESS RTC_RTC_PCNT_IRQ_MASK_OFFSETADDRESS
#define RTC_RTC_PCNT_IRQ_MASK_VAL_BITOFFSET     0
#define RTC_RTC_PCNT_IRQ_MASK_VAL_BITFIELDSIZE  1
#define RTC_RTC_PCNT_IRQ_MASK_VAL_BITMASK       0x00000001
#define RTC_RTC_PCNT_IRQ_MASK_VAL_INIT          0x0

/*
 *  RTC_RTC_PCNT_IRQ_CLR register defines
 ****************************************************************************************
 */
#define RTC_RTC_PCNT_IRQ_CLR_OFFSETADDRESS 0x00000098  /* RW */
#define RTC_RTC_PCNT_IRQ_CLR_BITOFFSET 0
#define RTC_RTC_PCNT_IRQ_CLR_BITFIELDSIZE 32
#define RTC_RTC_PCNT_IRQ_CLR_BITMASK   0xFFFFFFFF
#define RTC_RTC_PCNT_IRQ_CLR_INIT      0x00000000
/*
 *  RTC_RTC_PCNT_IRQ_CLEAR bit field defines
 ****************************************************************************************
 */
#define RTC_RTC_PCNT_IRQ_CLEAR_OFFSETADDRESS    RTC_RTC_PCNT_IRQ_CLR_OFFSETADDRESS
#define RTC_RTC_PCNT_IRQ_CLEAR_BITOFFSET        0
#define RTC_RTC_PCNT_IRQ_CLEAR_BITFIELDSIZE     1
#define RTC_RTC_PCNT_IRQ_CLEAR_BITMASK          0x00000001
#define RTC_RTC_PCNT_IRQ_CLEAR_INIT             0x0

/*
 *  RTC_ALARM_ENABLE register defines
 ****************************************************************************************
 */
#define RTC_ALARM_ENABLE_OFFSETADDRESS 0x000000c0  /* RW */
#define RTC_ALARM_ENABLE_BITOFFSET     0
#define RTC_ALARM_ENABLE_BITFIELDSIZE  32
#define RTC_ALARM_ENABLE_BITMASK       0xFFFFFFFF
#define RTC_ALARM_ENABLE_INIT          0x00000000
/*
 *  RTC_ALARM_0_ENABLE bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_0_ENABLE_OFFSETADDRESS        RTC_ALARM_ENABLE_OFFSETADDRESS
#define RTC_ALARM_0_ENABLE_BITOFFSET            0
#define RTC_ALARM_0_ENABLE_BITFIELDSIZE         1
#define RTC_ALARM_0_ENABLE_BITMASK              0x00000001
#define RTC_ALARM_0_ENABLE_INIT                 0x0
/*
 *  RTC_ALARM_1_ENABLE bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_1_ENABLE_OFFSETADDRESS        RTC_ALARM_ENABLE_OFFSETADDRESS
#define RTC_ALARM_1_ENABLE_BITOFFSET            1
#define RTC_ALARM_1_ENABLE_BITFIELDSIZE         1
#define RTC_ALARM_1_ENABLE_BITMASK              0x00000002
#define RTC_ALARM_1_ENABLE_INIT                 0x0
/*
 *  RTC_ALARM_2_ENABLE bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_2_ENABLE_OFFSETADDRESS        RTC_ALARM_ENABLE_OFFSETADDRESS
#define RTC_ALARM_2_ENABLE_BITOFFSET            2
#define RTC_ALARM_2_ENABLE_BITFIELDSIZE         1
#define RTC_ALARM_2_ENABLE_BITMASK              0x00000004
#define RTC_ALARM_2_ENABLE_INIT                 0x0
/*
 *  RTC_ALARM_3_ENABLE bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_3_ENABLE_OFFSETADDRESS        RTC_ALARM_ENABLE_OFFSETADDRESS
#define RTC_ALARM_3_ENABLE_BITOFFSET            3
#define RTC_ALARM_3_ENABLE_BITFIELDSIZE         1
#define RTC_ALARM_3_ENABLE_BITMASK              0x00000008
#define RTC_ALARM_3_ENABLE_INIT                 0x0
/*
 *  RTC_ALARM_4_ENABLE bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_4_ENABLE_OFFSETADDRESS        RTC_ALARM_ENABLE_OFFSETADDRESS
#define RTC_ALARM_4_ENABLE_BITOFFSET            4
#define RTC_ALARM_4_ENABLE_BITFIELDSIZE         1
#define RTC_ALARM_4_ENABLE_BITMASK              0x00000010
#define RTC_ALARM_4_ENABLE_INIT                 0x0

/*
 *  RTC_ALARM_CORE_ENABLE register defines
 ****************************************************************************************
 */
#define RTC_ALARM_CORE_ENABLE_OFFSETADDRESS 0x000000c4  /* RW */
#define RTC_ALARM_CORE_ENABLE_BITOFFSET 0
#define RTC_ALARM_CORE_ENABLE_BITFIELDSIZE 32
#define RTC_ALARM_CORE_ENABLE_BITMASK  0xFFFFFFFF
#define RTC_ALARM_CORE_ENABLE_INIT     0x00000000
/*
 *  RTC_ALARM_0_CORE_ENABLE bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_0_CORE_ENABLE_OFFSETADDRESS   RTC_ALARM_CORE_ENABLE_OFFSETADDRESS
#define RTC_ALARM_0_CORE_ENABLE_BITOFFSET       0
#define RTC_ALARM_0_CORE_ENABLE_BITFIELDSIZE    1
#define RTC_ALARM_0_CORE_ENABLE_BITMASK         0x00000001
#define RTC_ALARM_0_CORE_ENABLE_INIT            0x0
/*
 *  RTC_ALARM_1_CORE_ENABLE bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_1_CORE_ENABLE_OFFSETADDRESS   RTC_ALARM_CORE_ENABLE_OFFSETADDRESS
#define RTC_ALARM_1_CORE_ENABLE_BITOFFSET       1
#define RTC_ALARM_1_CORE_ENABLE_BITFIELDSIZE    1
#define RTC_ALARM_1_CORE_ENABLE_BITMASK         0x00000002
#define RTC_ALARM_1_CORE_ENABLE_INIT            0x0
/*
 *  RTC_ALARM_2_CORE_ENABLE bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_2_CORE_ENABLE_OFFSETADDRESS   RTC_ALARM_CORE_ENABLE_OFFSETADDRESS
#define RTC_ALARM_2_CORE_ENABLE_BITOFFSET       2
#define RTC_ALARM_2_CORE_ENABLE_BITFIELDSIZE    1
#define RTC_ALARM_2_CORE_ENABLE_BITMASK         0x00000004
#define RTC_ALARM_2_CORE_ENABLE_INIT            0x0
/*
 *  RTC_ALARM_3_CORE_ENABLE bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_3_CORE_ENABLE_OFFSETADDRESS   RTC_ALARM_CORE_ENABLE_OFFSETADDRESS
#define RTC_ALARM_3_CORE_ENABLE_BITOFFSET       3
#define RTC_ALARM_3_CORE_ENABLE_BITFIELDSIZE    1
#define RTC_ALARM_3_CORE_ENABLE_BITMASK         0x00000008
#define RTC_ALARM_3_CORE_ENABLE_INIT            0x0
/*
 *  RTC_ALARM_4_CORE_ENABLE bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_4_CORE_ENABLE_OFFSETADDRESS   RTC_ALARM_CORE_ENABLE_OFFSETADDRESS
#define RTC_ALARM_4_CORE_ENABLE_BITOFFSET       4
#define RTC_ALARM_4_CORE_ENABLE_BITFIELDSIZE    1
#define RTC_ALARM_4_CORE_ENABLE_BITMASK         0x00000010
#define RTC_ALARM_4_CORE_ENABLE_INIT            0x0

/*
 *  RTC_ALARM_CONTROL register defines
 ****************************************************************************************
 */
#define RTC_ALARM_CONTROL_OFFSETADDRESS 0x000000c8  /* RW */
#define RTC_ALARM_CONTROL_BITOFFSET    0
#define RTC_ALARM_CONTROL_BITFIELDSIZE 32
#define RTC_ALARM_CONTROL_BITMASK      0xFFFFFFFF
#define RTC_ALARM_CONTROL_INIT         0x00000000
/*
 *  RTC_ALARM_CTL bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_CTL_OFFSETADDRESS             RTC_ALARM_CONTROL_OFFSETADDRESS
#define RTC_ALARM_CTL_BITOFFSET                 0
#define RTC_ALARM_CTL_BITFIELDSIZE              1
#define RTC_ALARM_CTL_BITMASK                   0x00000001
#define RTC_ALARM_CTL_INIT                      0x0

/*
 *  RTC_ALARM_POLARITY register defines
 ****************************************************************************************
 */
#define RTC_ALARM_POLARITY_OFFSETADDRESS 0x000000cc  /* RW */
#define RTC_ALARM_POLARITY_BITOFFSET   0
#define RTC_ALARM_POLARITY_BITFIELDSIZE 32
#define RTC_ALARM_POLARITY_BITMASK     0xFFFFFFFF
#define RTC_ALARM_POLARITY_INIT        0x00000000
/*
 *  RTC_ALARM_0_POLARITY bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_0_POLARITY_OFFSETADDRESS      RTC_ALARM_POLARITY_OFFSETADDRESS
#define RTC_ALARM_0_POLARITY_BITOFFSET          0
#define RTC_ALARM_0_POLARITY_BITFIELDSIZE       1
#define RTC_ALARM_0_POLARITY_BITMASK            0x00000001
#define RTC_ALARM_0_POLARITY_INIT               0x0
/*
 *  RTC_ALARM_1_POLARITY bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_1_POLARITY_OFFSETADDRESS      RTC_ALARM_POLARITY_OFFSETADDRESS
#define RTC_ALARM_1_POLARITY_BITOFFSET          1
#define RTC_ALARM_1_POLARITY_BITFIELDSIZE       1
#define RTC_ALARM_1_POLARITY_BITMASK            0x00000002
#define RTC_ALARM_1_POLARITY_INIT               0x0
/*
 *  RTC_ALARM_2_POLARITY bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_2_POLARITY_OFFSETADDRESS      RTC_ALARM_POLARITY_OFFSETADDRESS
#define RTC_ALARM_2_POLARITY_BITOFFSET          2
#define RTC_ALARM_2_POLARITY_BITFIELDSIZE       1
#define RTC_ALARM_2_POLARITY_BITMASK            0x00000004
#define RTC_ALARM_2_POLARITY_INIT               0x0
/*
 *  RTC_ALARM_3_POLARITY bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_3_POLARITY_OFFSETADDRESS      RTC_ALARM_POLARITY_OFFSETADDRESS
#define RTC_ALARM_3_POLARITY_BITOFFSET          3
#define RTC_ALARM_3_POLARITY_BITFIELDSIZE       1
#define RTC_ALARM_3_POLARITY_BITMASK            0x00000008
#define RTC_ALARM_3_POLARITY_INIT               0x0
/*
 *  RTC_ALARM_4_POLARITY bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_4_POLARITY_OFFSETADDRESS      RTC_ALARM_POLARITY_OFFSETADDRESS
#define RTC_ALARM_4_POLARITY_BITOFFSET          4
#define RTC_ALARM_4_POLARITY_BITFIELDSIZE       1
#define RTC_ALARM_4_POLARITY_BITMASK            0x00000010
#define RTC_ALARM_4_POLARITY_INIT               0x0

/*
 *  RTC_ALARM_STATUS register defines
 ****************************************************************************************
 */
#define RTC_ALARM_STATUS_OFFSETADDRESS 0x000000d0  /* R */
#define RTC_ALARM_STATUS_BITOFFSET     0
#define RTC_ALARM_STATUS_BITFIELDSIZE  32
#define RTC_ALARM_STATUS_BITMASK       0xFFFFFFFF
#define RTC_ALARM_STATUS_INIT          0x00000000
/*
 *  RTC_ALARM_0_STATUS bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_0_STATUS_OFFSETADDRESS        RTC_ALARM_STATUS_OFFSETADDRESS
#define RTC_ALARM_0_STATUS_BITOFFSET            0
#define RTC_ALARM_0_STATUS_BITFIELDSIZE         1
#define RTC_ALARM_0_STATUS_BITMASK              0x00000001
#define RTC_ALARM_0_STATUS_INIT                 0x0
/*
 *  RTC_ALARM_1_STATUS bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_1_STATUS_OFFSETADDRESS        RTC_ALARM_STATUS_OFFSETADDRESS
#define RTC_ALARM_1_STATUS_BITOFFSET            1
#define RTC_ALARM_1_STATUS_BITFIELDSIZE         1
#define RTC_ALARM_1_STATUS_BITMASK              0x00000002
#define RTC_ALARM_1_STATUS_INIT                 0x0
/*
 *  RTC_ALARM_2_STATUS bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_2_STATUS_OFFSETADDRESS        RTC_ALARM_STATUS_OFFSETADDRESS
#define RTC_ALARM_2_STATUS_BITOFFSET            2
#define RTC_ALARM_2_STATUS_BITFIELDSIZE         1
#define RTC_ALARM_2_STATUS_BITMASK              0x00000004
#define RTC_ALARM_2_STATUS_INIT                 0x0
/*
 *  RTC_ALARM_3_STATUS bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_3_STATUS_OFFSETADDRESS        RTC_ALARM_STATUS_OFFSETADDRESS
#define RTC_ALARM_3_STATUS_BITOFFSET            3
#define RTC_ALARM_3_STATUS_BITFIELDSIZE         1
#define RTC_ALARM_3_STATUS_BITMASK              0x00000008
#define RTC_ALARM_3_STATUS_INIT                 0x0
/*
 *  RTC_ALARM_4_STATUS bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_4_STATUS_OFFSETADDRESS        RTC_ALARM_STATUS_OFFSETADDRESS
#define RTC_ALARM_4_STATUS_BITOFFSET            4
#define RTC_ALARM_4_STATUS_BITFIELDSIZE         1
#define RTC_ALARM_4_STATUS_BITMASK              0x00000010
#define RTC_ALARM_4_STATUS_INIT                 0x0

/*
 *  RTC_ALARM_IRQ_MASK register defines
 ****************************************************************************************
 */
#define RTC_ALARM_IRQ_MASK_OFFSETADDRESS 0x000000d4  /* RW */
#define RTC_ALARM_IRQ_MASK_BITOFFSET   0
#define RTC_ALARM_IRQ_MASK_BITFIELDSIZE 32
#define RTC_ALARM_IRQ_MASK_BITMASK     0xFFFFFFFF
#define RTC_ALARM_IRQ_MASK_INIT        0x00000000
/*
 *  RTC_ALARM_0_IRQ_MASK bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_0_IRQ_MASK_OFFSETADDRESS      RTC_ALARM_IRQ_MASK_OFFSETADDRESS
#define RTC_ALARM_0_IRQ_MASK_BITOFFSET          0
#define RTC_ALARM_0_IRQ_MASK_BITFIELDSIZE       1
#define RTC_ALARM_0_IRQ_MASK_BITMASK            0x00000001
#define RTC_ALARM_0_IRQ_MASK_INIT               0x0
/*
 *  RTC_ALARM_1_IRQ_MASK bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_1_IRQ_MASK_OFFSETADDRESS      RTC_ALARM_IRQ_MASK_OFFSETADDRESS
#define RTC_ALARM_1_IRQ_MASK_BITOFFSET          1
#define RTC_ALARM_1_IRQ_MASK_BITFIELDSIZE       1
#define RTC_ALARM_1_IRQ_MASK_BITMASK            0x00000002
#define RTC_ALARM_1_IRQ_MASK_INIT               0x0
/*
 *  RTC_ALARM_2_IRQ_MASK bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_2_IRQ_MASK_OFFSETADDRESS      RTC_ALARM_IRQ_MASK_OFFSETADDRESS
#define RTC_ALARM_2_IRQ_MASK_BITOFFSET          2
#define RTC_ALARM_2_IRQ_MASK_BITFIELDSIZE       1
#define RTC_ALARM_2_IRQ_MASK_BITMASK            0x00000004
#define RTC_ALARM_2_IRQ_MASK_INIT               0x0
/*
 *  RTC_ALARM_3_IRQ_MASK bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_3_IRQ_MASK_OFFSETADDRESS      RTC_ALARM_IRQ_MASK_OFFSETADDRESS
#define RTC_ALARM_3_IRQ_MASK_BITOFFSET          3
#define RTC_ALARM_3_IRQ_MASK_BITFIELDSIZE       1
#define RTC_ALARM_3_IRQ_MASK_BITMASK            0x00000008
#define RTC_ALARM_3_IRQ_MASK_INIT               0x0
/*
 *  RTC_ALARM_4_IRQ_MASK bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_4_IRQ_MASK_OFFSETADDRESS      RTC_ALARM_IRQ_MASK_OFFSETADDRESS
#define RTC_ALARM_4_IRQ_MASK_BITOFFSET          4
#define RTC_ALARM_4_IRQ_MASK_BITFIELDSIZE       1
#define RTC_ALARM_4_IRQ_MASK_BITMASK            0x00000010
#define RTC_ALARM_4_IRQ_MASK_INIT               0x0

/*
 *  RTC_ALARM_IRQ_CLEAR register defines
 ****************************************************************************************
 */
#define RTC_ALARM_IRQ_CLEAR_OFFSETADDRESS 0x000000d8  /* RW */
#define RTC_ALARM_IRQ_CLEAR_BITOFFSET  0
#define RTC_ALARM_IRQ_CLEAR_BITFIELDSIZE 32
#define RTC_ALARM_IRQ_CLEAR_BITMASK    0xFFFFFFFF
#define RTC_ALARM_IRQ_CLEAR_INIT       0x00000000
/*
 *  RTC_ALARM_0_IRQ_CLEAR bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_0_IRQ_CLEAR_OFFSETADDRESS     RTC_ALARM_IRQ_CLEAR_OFFSETADDRESS
#define RTC_ALARM_0_IRQ_CLEAR_BITOFFSET         0
#define RTC_ALARM_0_IRQ_CLEAR_BITFIELDSIZE      1
#define RTC_ALARM_0_IRQ_CLEAR_BITMASK           0x00000001
#define RTC_ALARM_0_IRQ_CLEAR_INIT              0x0
/*
 *  RTC_ALARM_1_IRQ_CLEAR bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_1_IRQ_CLEAR_OFFSETADDRESS     RTC_ALARM_IRQ_CLEAR_OFFSETADDRESS
#define RTC_ALARM_1_IRQ_CLEAR_BITOFFSET         1
#define RTC_ALARM_1_IRQ_CLEAR_BITFIELDSIZE      1
#define RTC_ALARM_1_IRQ_CLEAR_BITMASK           0x00000002
#define RTC_ALARM_1_IRQ_CLEAR_INIT              0x0
/*
 *  RTC_ALARM_2_IRQ_CLEAR bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_2_IRQ_CLEAR_OFFSETADDRESS     RTC_ALARM_IRQ_CLEAR_OFFSETADDRESS
#define RTC_ALARM_2_IRQ_CLEAR_BITOFFSET         2
#define RTC_ALARM_2_IRQ_CLEAR_BITFIELDSIZE      1
#define RTC_ALARM_2_IRQ_CLEAR_BITMASK           0x00000004
#define RTC_ALARM_2_IRQ_CLEAR_INIT              0x0
/*
 *  RTC_ALARM_3_IRQ_CLEAR bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_3_IRQ_CLEAR_OFFSETADDRESS     RTC_ALARM_IRQ_CLEAR_OFFSETADDRESS
#define RTC_ALARM_3_IRQ_CLEAR_BITOFFSET         3
#define RTC_ALARM_3_IRQ_CLEAR_BITFIELDSIZE      1
#define RTC_ALARM_3_IRQ_CLEAR_BITMASK           0x00000008
#define RTC_ALARM_3_IRQ_CLEAR_INIT              0x0
/*
 *  RTC_ALARM_4_IRQ_CLEAR bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_4_IRQ_CLEAR_OFFSETADDRESS     RTC_ALARM_IRQ_CLEAR_OFFSETADDRESS
#define RTC_ALARM_4_IRQ_CLEAR_BITOFFSET         4
#define RTC_ALARM_4_IRQ_CLEAR_BITFIELDSIZE      1
#define RTC_ALARM_4_IRQ_CLEAR_BITMASK           0x00000010
#define RTC_ALARM_4_IRQ_CLEAR_INIT              0x0

/*
 *  RTC_ALARM_TIMESTAMP0 register defines
 ****************************************************************************************
 */
#define RTC_ALARM_TIMESTAMP0_OFFSETADDRESS 0x000000e0  /* R */
#define RTC_ALARM_TIMESTAMP0_BITOFFSET 0
#define RTC_ALARM_TIMESTAMP0_BITFIELDSIZE 32
#define RTC_ALARM_TIMESTAMP0_BITMASK   0xFFFFFFFF
#define RTC_ALARM_TIMESTAMP0_INIT      0x00000000
/*
 *  RTC_ALARM_TIME_STAMP0 bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_TIME_STAMP0_OFFSETADDRESS     RTC_ALARM_TIMESTAMP0_OFFSETADDRESS
#define RTC_ALARM_TIME_STAMP0_BITOFFSET         0
#define RTC_ALARM_TIME_STAMP0_BITFIELDSIZE     10
#define RTC_ALARM_TIME_STAMP0_BITMASK           0x000003ff
#define RTC_ALARM_TIME_STAMP0_INIT              0x0

/*
 *  RTC_ALARM_TIMESTAMP1 register defines
 ****************************************************************************************
 */
#define RTC_ALARM_TIMESTAMP1_OFFSETADDRESS 0x000000e4  /* R */
#define RTC_ALARM_TIMESTAMP1_BITOFFSET 0
#define RTC_ALARM_TIMESTAMP1_BITFIELDSIZE 32
#define RTC_ALARM_TIMESTAMP1_BITMASK   0xFFFFFFFF
#define RTC_ALARM_TIMESTAMP1_INIT      0x00000000
/*
 *  RTC_ALARM_TIME_STAMP1 bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_TIME_STAMP1_OFFSETADDRESS     RTC_ALARM_TIMESTAMP1_OFFSETADDRESS
#define RTC_ALARM_TIME_STAMP1_BITOFFSET         0
#define RTC_ALARM_TIME_STAMP1_BITFIELDSIZE     10
#define RTC_ALARM_TIME_STAMP1_BITMASK           0x000003ff
#define RTC_ALARM_TIME_STAMP1_INIT              0x0

/*
 *  RTC_ALARM_TIMESTAMP2 register defines
 ****************************************************************************************
 */
#define RTC_ALARM_TIMESTAMP2_OFFSETADDRESS 0x000000e8  /* R */
#define RTC_ALARM_TIMESTAMP2_BITOFFSET 0
#define RTC_ALARM_TIMESTAMP2_BITFIELDSIZE 32
#define RTC_ALARM_TIMESTAMP2_BITMASK   0xFFFFFFFF
#define RTC_ALARM_TIMESTAMP2_INIT      0x00000000
/*
 *  RTC_ALARM_TIME_STAMP2 bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_TIME_STAMP2_OFFSETADDRESS     RTC_ALARM_TIMESTAMP2_OFFSETADDRESS
#define RTC_ALARM_TIME_STAMP2_BITOFFSET         0
#define RTC_ALARM_TIME_STAMP2_BITFIELDSIZE     10
#define RTC_ALARM_TIME_STAMP2_BITMASK           0x000003ff
#define RTC_ALARM_TIME_STAMP2_INIT              0x0

/*
 *  RTC_ALARM_TIMESTAMP3 register defines
 ****************************************************************************************
 */
#define RTC_ALARM_TIMESTAMP3_OFFSETADDRESS 0x000000ec  /* R */
#define RTC_ALARM_TIMESTAMP3_BITOFFSET 0
#define RTC_ALARM_TIMESTAMP3_BITFIELDSIZE 32
#define RTC_ALARM_TIMESTAMP3_BITMASK   0xFFFFFFFF
#define RTC_ALARM_TIMESTAMP3_INIT      0x00000000
/*
 *  RTC_ALARM_TIME_STAMP3 bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_TIME_STAMP3_OFFSETADDRESS     RTC_ALARM_TIMESTAMP3_OFFSETADDRESS
#define RTC_ALARM_TIME_STAMP3_BITOFFSET         0
#define RTC_ALARM_TIME_STAMP3_BITFIELDSIZE     10
#define RTC_ALARM_TIME_STAMP3_BITMASK           0x000003ff
#define RTC_ALARM_TIME_STAMP3_INIT              0x0

/*
 *  RTC_ALARM_TIMESTAMP4 register defines
 ****************************************************************************************
 */
#define RTC_ALARM_TIMESTAMP4_OFFSETADDRESS 0x000000f0  /* R */
#define RTC_ALARM_TIMESTAMP4_BITOFFSET 0
#define RTC_ALARM_TIMESTAMP4_BITFIELDSIZE 32
#define RTC_ALARM_TIMESTAMP4_BITMASK   0xFFFFFFFF
#define RTC_ALARM_TIMESTAMP4_INIT      0x00000000
/*
 *  RTC_ALARM_TIME_STAMP4 bit field defines
 ****************************************************************************************
 */
#define RTC_ALARM_TIME_STAMP4_OFFSETADDRESS     RTC_ALARM_TIMESTAMP4_OFFSETADDRESS
#define RTC_ALARM_TIME_STAMP4_BITOFFSET         0
#define RTC_ALARM_TIME_STAMP4_BITFIELDSIZE     10
#define RTC_ALARM_TIME_STAMP4_BITMASK           0x000003ff
#define RTC_ALARM_TIME_STAMP4_INIT              0x0

/*
 *  RTC_SETTLE_LP_RC register defines
 ****************************************************************************************
 */
#define RTC_SETTLE_LP_RC_OFFSETADDRESS 0x00000100  /* RW */
#define RTC_SETTLE_LP_RC_BITOFFSET     0
#define RTC_SETTLE_LP_RC_BITFIELDSIZE  32
#define RTC_SETTLE_LP_RC_BITMASK       0xFFFFFFFF
#define RTC_SETTLE_LP_RC_INIT          0x00000000
/*
 *  RTC_LP_RC_SETTLE bit field defines
 ****************************************************************************************
 */
#define RTC_LP_RC_SETTLE_OFFSETADDRESS          RTC_SETTLE_LP_RC_OFFSETADDRESS
#define RTC_LP_RC_SETTLE_BITOFFSET              0
#define RTC_LP_RC_SETTLE_BITFIELDSIZE           8
#define RTC_LP_RC_SETTLE_BITMASK                0x000000ff
#define RTC_LP_RC_SETTLE_INIT                   0x0

/*
 *  RTC_SETTLE_LP_XTAL register defines
 ****************************************************************************************
 */
#define RTC_SETTLE_LP_XTAL_OFFSETADDRESS 0x00000104  /* RW */
#define RTC_SETTLE_LP_XTAL_BITOFFSET   0
#define RTC_SETTLE_LP_XTAL_BITFIELDSIZE 32
#define RTC_SETTLE_LP_XTAL_BITMASK     0xFFFFFFFF
#define RTC_SETTLE_LP_XTAL_INIT        0x00000000
/*
 *  RTC_LP_XTAL_SETTLE bit field defines
 ****************************************************************************************
 */
#define RTC_LP_XTAL_SETTLE_OFFSETADDRESS        RTC_SETTLE_LP_XTAL_OFFSETADDRESS
#define RTC_LP_XTAL_SETTLE_BITOFFSET            0
#define RTC_LP_XTAL_SETTLE_BITFIELDSIZE         8
#define RTC_LP_XTAL_SETTLE_BITMASK              0x000000ff
#define RTC_LP_XTAL_SETTLE_INIT                 0x0

/*
 *  RTC_SETTLE_HS_RC register defines
 ****************************************************************************************
 */
#define RTC_SETTLE_HS_RC_OFFSETADDRESS 0x00000108  /* RW */
#define RTC_SETTLE_HS_RC_BITOFFSET     0
#define RTC_SETTLE_HS_RC_BITFIELDSIZE  32
#define RTC_SETTLE_HS_RC_BITMASK       0xFFFFFFFF
#define RTC_SETTLE_HS_RC_INIT          0x00000000
/*
 *  RTC_HS_RC_SETTLE bit field defines
 ****************************************************************************************
 */
#define RTC_HS_RC_SETTLE_OFFSETADDRESS          RTC_SETTLE_HS_RC_OFFSETADDRESS
#define RTC_HS_RC_SETTLE_BITOFFSET              0
#define RTC_HS_RC_SETTLE_BITFIELDSIZE           8
#define RTC_HS_RC_SETTLE_BITMASK                0x000000ff
#define RTC_HS_RC_SETTLE_INIT                   0x0

/*
 *  RTC_SETTLE_HS_XTAL register defines
 ****************************************************************************************
 */
#define RTC_SETTLE_HS_XTAL_OFFSETADDRESS 0x0000010c  /* RW */
#define RTC_SETTLE_HS_XTAL_BITOFFSET   0
#define RTC_SETTLE_HS_XTAL_BITFIELDSIZE 32
#define RTC_SETTLE_HS_XTAL_BITMASK     0xFFFFFFFF
#define RTC_SETTLE_HS_XTAL_INIT        0x00000000
/*
 *  RTC_HS_XTAL_SETTLE bit field defines
 ****************************************************************************************
 */
#define RTC_HS_XTAL_SETTLE_OFFSETADDRESS        RTC_SETTLE_HS_XTAL_OFFSETADDRESS
#define RTC_HS_XTAL_SETTLE_BITOFFSET            0
#define RTC_HS_XTAL_SETTLE_BITFIELDSIZE         8
#define RTC_HS_XTAL_SETTLE_BITMASK              0x000000ff
#define RTC_HS_XTAL_SETTLE_INIT                 0x0

/*
 *  RTC_SETTLE_PLL register defines
 ****************************************************************************************
 */
#define RTC_SETTLE_PLL_OFFSETADDRESS   0x00000110  /* RW */
#define RTC_SETTLE_PLL_BITOFFSET       0
#define RTC_SETTLE_PLL_BITFIELDSIZE    32
#define RTC_SETTLE_PLL_BITMASK         0xFFFFFFFF
#define RTC_SETTLE_PLL_INIT            0x00000000
/*
 *  RTC_PLL_SETTLE bit field defines
 ****************************************************************************************
 */
#define RTC_PLL_SETTLE_OFFSETADDRESS            RTC_SETTLE_PLL_OFFSETADDRESS
#define RTC_PLL_SETTLE_BITOFFSET                0
#define RTC_PLL_SETTLE_BITFIELDSIZE             8
#define RTC_PLL_SETTLE_BITMASK                  0x000000ff
#define RTC_PLL_SETTLE_INIT                     0x0

/*
 *  RTC_CLK_EN_STATUS register defines
 ****************************************************************************************
 */
#define RTC_CLK_EN_STATUS_OFFSETADDRESS 0x00000114  /* R */
#define RTC_CLK_EN_STATUS_BITOFFSET    0
#define RTC_CLK_EN_STATUS_BITFIELDSIZE 32
#define RTC_CLK_EN_STATUS_BITMASK      0xFFFFFFFF
#define RTC_CLK_EN_STATUS_INIT         0x00000000
/*
 *  RTC_CLK_EN_STATUS_LP_RC_STABLE bit field defines
 ****************************************************************************************
 */
#define RTC_CLK_EN_STATUS_LP_RC_STABLE_OFFSETADDRESS RTC_CLK_EN_STATUS_OFFSETADDRESS
#define RTC_CLK_EN_STATUS_LP_RC_STABLE_BITOFFSET  0
#define RTC_CLK_EN_STATUS_LP_RC_STABLE_BITFIELDSIZE  1
#define RTC_CLK_EN_STATUS_LP_RC_STABLE_BITMASK  0x00000001
#define RTC_CLK_EN_STATUS_LP_RC_STABLE_INIT     0x0
/*
 *  RTC_CLK_EN_STATUS_LP_XTAL_STABLE bit field defines
 ****************************************************************************************
 */
#define RTC_CLK_EN_STATUS_LP_XTAL_STABLE_OFFSETADDRESS RTC_CLK_EN_STATUS_OFFSETADDRESS
#define RTC_CLK_EN_STATUS_LP_XTAL_STABLE_BITOFFSET  1
#define RTC_CLK_EN_STATUS_LP_XTAL_STABLE_BITFIELDSIZE  1
#define RTC_CLK_EN_STATUS_LP_XTAL_STABLE_BITMASK 0x00000002
#define RTC_CLK_EN_STATUS_LP_XTAL_STABLE_INIT   0x0

/*
 *  RTC_CLK_SEL_STATUS register defines
 ****************************************************************************************
 */
#define RTC_CLK_SEL_STATUS_OFFSETADDRESS 0x00000118  /* RW */
#define RTC_CLK_SEL_STATUS_BITOFFSET   0
#define RTC_CLK_SEL_STATUS_BITFIELDSIZE 32
#define RTC_CLK_SEL_STATUS_BITMASK     0xFFFFFFFF
#define RTC_CLK_SEL_STATUS_INIT        0x00000000
/*
 *  RTC_CLOCK_SEL_STATUS bit field defines
 ****************************************************************************************
 */
#define RTC_CLOCK_SEL_STATUS_OFFSETADDRESS      RTC_CLK_SEL_STATUS_OFFSETADDRESS
#define RTC_CLOCK_SEL_STATUS_BITOFFSET          0
#define RTC_CLOCK_SEL_STATUS_BITFIELDSIZE       2
#define RTC_CLOCK_SEL_STATUS_BITMASK            0x00000003
#define RTC_CLOCK_SEL_STATUS_INIT               0x0

/*
 *  RTC_ACM3_CLK_SEL register defines
 ****************************************************************************************
 */
#define RTC_ACM3_CLK_SEL_OFFSETADDRESS 0x0000011c  /* RW */
#define RTC_ACM3_CLK_SEL_BITOFFSET     0
#define RTC_ACM3_CLK_SEL_BITFIELDSIZE  32
#define RTC_ACM3_CLK_SEL_BITMASK       0xFFFFFFFF
#define RTC_ACM3_CLK_SEL_INIT          0x00000000
/*
 *  RTC_ACM3_CLK_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_ACM3_CLK_SEL_VAL_OFFSETADDRESS      RTC_ACM3_CLK_SEL_OFFSETADDRESS
#define RTC_ACM3_CLK_SEL_VAL_BITOFFSET          0
#define RTC_ACM3_CLK_SEL_VAL_BITFIELDSIZE       2
#define RTC_ACM3_CLK_SEL_VAL_BITMASK            0x00000003
#define RTC_ACM3_CLK_SEL_VAL_INIT               0x0

/*
 *  RTC_WCM3_CLK_SEL register defines
 ****************************************************************************************
 */
#define RTC_WCM3_CLK_SEL_OFFSETADDRESS 0x00000120  /* RW */
#define RTC_WCM3_CLK_SEL_BITOFFSET     0
#define RTC_WCM3_CLK_SEL_BITFIELDSIZE  32
#define RTC_WCM3_CLK_SEL_BITMASK       0xFFFFFFFF
#define RTC_WCM3_CLK_SEL_INIT          0x00000000
/*
 *  RTC_WCM3_CLK_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_WCM3_CLK_SEL_VAL_OFFSETADDRESS      RTC_WCM3_CLK_SEL_OFFSETADDRESS
#define RTC_WCM3_CLK_SEL_VAL_BITOFFSET          0
#define RTC_WCM3_CLK_SEL_VAL_BITFIELDSIZE       2
#define RTC_WCM3_CLK_SEL_VAL_BITMASK            0x00000003
#define RTC_WCM3_CLK_SEL_VAL_INIT               0x0

/*
 *  RTC_RBUS_CLK_SEL register defines
 ****************************************************************************************
 */
#define RTC_RBUS_CLK_SEL_OFFSETADDRESS 0x00000124  /* RW */
#define RTC_RBUS_CLK_SEL_BITOFFSET     0
#define RTC_RBUS_CLK_SEL_BITFIELDSIZE  32
#define RTC_RBUS_CLK_SEL_BITMASK       0xFFFFFFFF
#define RTC_RBUS_CLK_SEL_INIT          0x00000000
/*
 *  RTC_RBUS_CLOCK_SEL bit field defines
 ****************************************************************************************
 */
#define RTC_RBUS_CLOCK_SEL_OFFSETADDRESS        RTC_RBUS_CLK_SEL_OFFSETADDRESS
#define RTC_RBUS_CLOCK_SEL_BITOFFSET            0
#define RTC_RBUS_CLOCK_SEL_BITFIELDSIZE         2
#define RTC_RBUS_CLOCK_SEL_BITMASK              0x00000003
#define RTC_RBUS_CLOCK_SEL_INIT                 0x0

/*
 *  RTC_WCM3_CLK_EN register defines
 ****************************************************************************************
 */
#define RTC_WCM3_CLK_EN_OFFSETADDRESS  0x00000128  /* RW */
#define RTC_WCM3_CLK_EN_BITOFFSET      0
#define RTC_WCM3_CLK_EN_BITFIELDSIZE   32
#define RTC_WCM3_CLK_EN_BITMASK        0xFFFFFFFF
#define RTC_WCM3_CLK_EN_INIT           0x00000000
/*
 *  RTC_WCM3_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define RTC_WCM3_CLK_ENABLE_OFFSETADDRESS       RTC_WCM3_CLK_EN_OFFSETADDRESS
#define RTC_WCM3_CLK_ENABLE_BITOFFSET           0
#define RTC_WCM3_CLK_ENABLE_BITFIELDSIZE        1
#define RTC_WCM3_CLK_ENABLE_BITMASK             0x00000001
#define RTC_WCM3_CLK_ENABLE_INIT                0x0

/*
 *  RTC_CLK_RTC_DIV register defines
 ****************************************************************************************
 */
#define RTC_CLK_RTC_DIV_OFFSETADDRESS  0x0000012c  /* RW */
#define RTC_CLK_RTC_DIV_BITOFFSET      0
#define RTC_CLK_RTC_DIV_BITFIELDSIZE   32
#define RTC_CLK_RTC_DIV_BITMASK        0xFFFFFFFF
#define RTC_CLK_RTC_DIV_INIT           0x00000000
/*
 *  RTC_CLK_RTC_DIV_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_CLK_RTC_DIV_VAL_OFFSETADDRESS       RTC_CLK_RTC_DIV_OFFSETADDRESS
#define RTC_CLK_RTC_DIV_VAL_BITOFFSET           0
#define RTC_CLK_RTC_DIV_VAL_BITFIELDSIZE        2
#define RTC_CLK_RTC_DIV_VAL_BITMASK             0x00000003
#define RTC_CLK_RTC_DIV_VAL_INIT                0x0

/*
 *  RTC_RRH_REQ_RST register defines
 ****************************************************************************************
 */
#define RTC_RRH_REQ_RST_OFFSETADDRESS  0x00000160  /* RW */
#define RTC_RRH_REQ_RST_BITOFFSET      0
#define RTC_RRH_REQ_RST_BITFIELDSIZE   32
#define RTC_RRH_REQ_RST_BITMASK        0xFFFFFFFF
#define RTC_RRH_REQ_RST_INIT           0x00000000
/*
 *  RTC_RRH_REQ_RST_FWAPP bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_REQ_RST_FWAPP_OFFSETADDRESS     RTC_RRH_REQ_RST_OFFSETADDRESS
#define RTC_RRH_REQ_RST_FWAPP_BITOFFSET         0
#define RTC_RRH_REQ_RST_FWAPP_BITFIELDSIZE      1
#define RTC_RRH_REQ_RST_FWAPP_BITMASK           0x00000001
#define RTC_RRH_REQ_RST_FWAPP_INIT              0x0
/*
 *  RTC_RRH_REQ_RST_FWWLAN bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_REQ_RST_FWWLAN_OFFSETADDRESS    RTC_RRH_REQ_RST_OFFSETADDRESS
#define RTC_RRH_REQ_RST_FWWLAN_BITOFFSET        1
#define RTC_RRH_REQ_RST_FWWLAN_BITFIELDSIZE     1
#define RTC_RRH_REQ_RST_FWWLAN_BITMASK          0x00000002
#define RTC_RRH_REQ_RST_FWWLAN_INIT             0x0
/*
 *  RTC_RRH_REQ_RST_FWCRYPTO bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_REQ_RST_FWCRYPTO_OFFSETADDRESS  RTC_RRH_REQ_RST_OFFSETADDRESS
#define RTC_RRH_REQ_RST_FWCRYPTO_BITOFFSET      2
#define RTC_RRH_REQ_RST_FWCRYPTO_BITFIELDSIZE   1
#define RTC_RRH_REQ_RST_FWCRYPTO_BITMASK        0x00000004
#define RTC_RRH_REQ_RST_FWCRYPTO_INIT           0x0
/*
 *  RTC_RRH_REQ_RST_FWPOR bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_REQ_RST_FWPOR_OFFSETADDRESS     RTC_RRH_REQ_RST_OFFSETADDRESS
#define RTC_RRH_REQ_RST_FWPOR_BITOFFSET         3
#define RTC_RRH_REQ_RST_FWPOR_BITFIELDSIZE      1
#define RTC_RRH_REQ_RST_FWPOR_BITMASK           0x00000008
#define RTC_RRH_REQ_RST_FWPOR_INIT              0x0

/*
 *  RTC_RRH_FWAPP_STAT register defines
 ****************************************************************************************
 */
#define RTC_RRH_FWAPP_STAT_OFFSETADDRESS 0x00000168  /* RW */
#define RTC_RRH_FWAPP_STAT_BITOFFSET   0
#define RTC_RRH_FWAPP_STAT_BITFIELDSIZE 32
#define RTC_RRH_FWAPP_STAT_BITMASK     0xFFFFFFFF
#define RTC_RRH_FWAPP_STAT_INIT        0x00000000
/*
 *  RTC_RRH_FWAPP_STATUS bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_FWAPP_STATUS_OFFSETADDRESS      RTC_RRH_FWAPP_STAT_OFFSETADDRESS
#define RTC_RRH_FWAPP_STATUS_BITOFFSET          0
#define RTC_RRH_FWAPP_STATUS_BITFIELDSIZE       1
#define RTC_RRH_FWAPP_STATUS_BITMASK            0x00000001
#define RTC_RRH_FWAPP_STATUS_INIT               0x0

/*
 *  RTC_RRH_FWAPP_CTL register defines
 ****************************************************************************************
 */
#define RTC_RRH_FWAPP_CTL_OFFSETADDRESS 0x0000016c  /* RW */
#define RTC_RRH_FWAPP_CTL_BITOFFSET    0
#define RTC_RRH_FWAPP_CTL_BITFIELDSIZE 32
#define RTC_RRH_FWAPP_CTL_BITMASK      0xFFFFFFFF
#define RTC_RRH_FWAPP_CTL_INIT         0x00000000
/*
 *  RTC_RRH_FWAPP_CTL_REQ bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_FWAPP_CTL_REQ_OFFSETADDRESS     RTC_RRH_FWAPP_CTL_OFFSETADDRESS
#define RTC_RRH_FWAPP_CTL_REQ_BITOFFSET         0
#define RTC_RRH_FWAPP_CTL_REQ_BITFIELDSIZE      1
#define RTC_RRH_FWAPP_CTL_REQ_BITMASK           0x00000001
#define RTC_RRH_FWAPP_CTL_REQ_INIT              0x0
/*
 *  RTC_RRH_FWAPP_CTL_POR bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_FWAPP_CTL_COND_OFFSETADDRESS    RTC_RRH_FWAPP_CTL_OFFSETADDRESS
#define RTC_RRH_FWAPP_CTL_COND_BITOFFSET        1
#define RTC_RRH_FWAPP_CTL_COND_BITFIELDSIZE     1
#define RTC_RRH_FWAPP_CTL_COND_BITMASK          0x00000002
#define RTC_RRH_FWAPP_CTL_COND_INIT             0x0

/*
 *  RTC_RRH_FWWLAN_STAT register defines
 ****************************************************************************************
 */
#define RTC_RRH_FWWLAN_STAT_OFFSETADDRESS 0x00000170  /* RW */
#define RTC_RRH_FWWLAN_STAT_BITOFFSET  0
#define RTC_RRH_FWWLAN_STAT_BITFIELDSIZE 32
#define RTC_RRH_FWWLAN_STAT_BITMASK    0xFFFFFFFF
#define RTC_RRH_FWWLAN_STAT_INIT       0x00000000
/*
 *  RTC_RRH_FWWLAN_STATUS bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_FWWLAN_STATUS_OFFSETADDRESS     RTC_RRH_FWWLAN_STAT_OFFSETADDRESS
#define RTC_RRH_FWWLAN_STATUS_BITOFFSET         0
#define RTC_RRH_FWWLAN_STATUS_BITFIELDSIZE      1
#define RTC_RRH_FWWLAN_STATUS_BITMASK           0x00000001
#define RTC_RRH_FWWLAN_STATUS_INIT              0x0

/*
 *  RTC_RRH_FWWLAN_CTL register defines
 ****************************************************************************************
 */
#define RTC_RRH_FWWLAN_CTL_OFFSETADDRESS 0x00000174  /* RW */
#define RTC_RRH_FWWLAN_CTL_BITOFFSET   0
#define RTC_RRH_FWWLAN_CTL_BITFIELDSIZE 32
#define RTC_RRH_FWWLAN_CTL_BITMASK     0xFFFFFFFF
#define RTC_RRH_FWWLAN_CTL_INIT        0x00000000
/*
 *  RTC_RRH_FWWLAN_CTL_REQ bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_FWWLAN_CTL_REQ_OFFSETADDRESS    RTC_RRH_FWWLAN_CTL_OFFSETADDRESS
#define RTC_RRH_FWWLAN_CTL_REQ_BITOFFSET        0
#define RTC_RRH_FWWLAN_CTL_REQ_BITFIELDSIZE     1
#define RTC_RRH_FWWLAN_CTL_REQ_BITMASK          0x00000001
#define RTC_RRH_FWWLAN_CTL_REQ_INIT             0x0
/*
 *  RTC_RRH_FWWLAN_CTL_POR bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_FWWLAN_CTL_COND_OFFSETADDRESS   RTC_RRH_FWWLAN_CTL_OFFSETADDRESS
#define RTC_RRH_FWWLAN_CTL_COND_BITOFFSET       1
#define RTC_RRH_FWWLAN_CTL_COND_BITFIELDSIZE    1
#define RTC_RRH_FWWLAN_CTL_COND_BITMASK         0x00000002
#define RTC_RRH_FWWLAN_CTL_COND_INIT            0x0

/*
 *  RTC_RRH_FWCRYPTO_STAT register defines
 ****************************************************************************************
 */
#define RTC_RRH_FWCRYPTO_STAT_OFFSETADDRESS 0x00000178  /* RW */
#define RTC_RRH_FWCRYPTO_STAT_BITOFFSET 0
#define RTC_RRH_FWCRYPTO_STAT_BITFIELDSIZE 32
#define RTC_RRH_FWCRYPTO_STAT_BITMASK  0xFFFFFFFF
#define RTC_RRH_FWCRYPTO_STAT_INIT     0x00000000
/*
 *  RTC_RRH_FWCRYPTO_STATUS bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_FWCRYPTO_STATUS_OFFSETADDRESS   RTC_RRH_FWCRYPTO_STAT_OFFSETADDRESS
#define RTC_RRH_FWCRYPTO_STATUS_BITOFFSET       0
#define RTC_RRH_FWCRYPTO_STATUS_BITFIELDSIZE    1
#define RTC_RRH_FWCRYPTO_STATUS_BITMASK         0x00000001
#define RTC_RRH_FWCRYPTO_STATUS_INIT            0x0

/*
 *  RTC_RRH_FWCRYPTO_CTL register defines
 ****************************************************************************************
 */
#define RTC_RRH_FWCRYPTO_CTL_OFFSETADDRESS 0x0000017c  /* RW */
#define RTC_RRH_FWCRYPTO_CTL_BITOFFSET 0
#define RTC_RRH_FWCRYPTO_CTL_BITFIELDSIZE 32
#define RTC_RRH_FWCRYPTO_CTL_BITMASK   0xFFFFFFFF
#define RTC_RRH_FWCRYPTO_CTL_INIT      0x00000000
/*
 *  RTC_RRH_FWCRYPTO_CTL_REQ bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_FWCRYPTO_CTL_REQ_OFFSETADDRESS  RTC_RRH_FWCRYPTO_CTL_OFFSETADDRESS
#define RTC_RRH_FWCRYPTO_CTL_REQ_BITOFFSET      0
#define RTC_RRH_FWCRYPTO_CTL_REQ_BITFIELDSIZE   1
#define RTC_RRH_FWCRYPTO_CTL_REQ_BITMASK        0x00000001
#define RTC_RRH_FWCRYPTO_CTL_REQ_INIT           0x0
/*
 *  RTC_RRH_FWCRYPTO_CTL_POR bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_FWCRYPTO_CTL_COND_OFFSETADDRESS RTC_RRH_FWCRYPTO_CTL_OFFSETADDRESS
#define RTC_RRH_FWCRYPTO_CTL_COND_BITOFFSET     1
#define RTC_RRH_FWCRYPTO_CTL_COND_BITFIELDSIZE  1
#define RTC_RRH_FWCRYPTO_CTL_COND_BITMASK       0x00000002
#define RTC_RRH_FWCRYPTO_CTL_COND_INIT          0x0

/*
 *  RTC_RRH_FWPOR_STAT register defines
 ****************************************************************************************
 */
#define RTC_RRH_FWPOR_STAT_OFFSETADDRESS 0x00000180  /* RW */
#define RTC_RRH_FWPOR_STAT_BITOFFSET   0
#define RTC_RRH_FWPOR_STAT_BITFIELDSIZE 32
#define RTC_RRH_FWPOR_STAT_BITMASK     0xFFFFFFFF
#define RTC_RRH_FWPOR_STAT_INIT        0x00000000
/*
 *  RTC_RRH_FWPOR_STATUS bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_FWPOR_STATUS_OFFSETADDRESS      RTC_RRH_FWPOR_STAT_OFFSETADDRESS
#define RTC_RRH_FWPOR_STATUS_BITOFFSET          0
#define RTC_RRH_FWPOR_STATUS_BITFIELDSIZE       1
#define RTC_RRH_FWPOR_STATUS_BITMASK            0x00000001
#define RTC_RRH_FWPOR_STATUS_INIT               0x0

/*
 *  RTC_RRH_FWPOR_CTL register defines
 ****************************************************************************************
 */
#define RTC_RRH_FWPOR_CTL_OFFSETADDRESS 0x00000184  /* RW */
#define RTC_RRH_FWPOR_CTL_BITOFFSET    0
#define RTC_RRH_FWPOR_CTL_BITFIELDSIZE 32
#define RTC_RRH_FWPOR_CTL_BITMASK      0xFFFFFFFF
#define RTC_RRH_FWPOR_CTL_INIT         0x00000000
/*
 *  RTC_RRH_FWPOR_CTL_REQ bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_FWPOR_CTL_REQ_OFFSETADDRESS     RTC_RRH_FWPOR_CTL_OFFSETADDRESS
#define RTC_RRH_FWPOR_CTL_REQ_BITOFFSET         0
#define RTC_RRH_FWPOR_CTL_REQ_BITFIELDSIZE      1
#define RTC_RRH_FWPOR_CTL_REQ_BITMASK           0x00000001
#define RTC_RRH_FWPOR_CTL_REQ_INIT              0x0
/*
 *  RTC_RRH_FWPOR_CTL_POR bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_FWPOR_CTL_COND_OFFSETADDRESS    RTC_RRH_FWPOR_CTL_OFFSETADDRESS
#define RTC_RRH_FWPOR_CTL_COND_BITOFFSET        1
#define RTC_RRH_FWPOR_CTL_COND_BITFIELDSIZE     1
#define RTC_RRH_FWPOR_CTL_COND_BITMASK          0x00000002
#define RTC_RRH_FWPOR_CTL_COND_INIT             0x0

/*
 *  RTC_RRH_EXT_RST_STAT register defines
 ****************************************************************************************
 */
#define RTC_RRH_EXT_RST_STAT_OFFSETADDRESS 0x00000188  /* RW */
#define RTC_RRH_EXT_RST_STAT_BITOFFSET 0
#define RTC_RRH_EXT_RST_STAT_BITFIELDSIZE 32
#define RTC_RRH_EXT_RST_STAT_BITMASK   0xFFFFFFFF
#define RTC_RRH_EXT_RST_STAT_INIT      0x00000000
/*
 *  RTC_RRH_EXT_RST_STATUS bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_EXT_RST_STATUS_OFFSETADDRESS    RTC_RRH_EXT_RST_STAT_OFFSETADDRESS
#define RTC_RRH_EXT_RST_STATUS_BITOFFSET        0
#define RTC_RRH_EXT_RST_STATUS_BITFIELDSIZE     1
#define RTC_RRH_EXT_RST_STATUS_BITMASK          0x00000001
#define RTC_RRH_EXT_RST_STATUS_INIT             0x0

/*
 *  RTC_RRH_EXT_RST_CTL register defines
 ****************************************************************************************
 */
#define RTC_RRH_EXT_RST_CTL_OFFSETADDRESS 0x0000018c  /* RW */
#define RTC_RRH_EXT_RST_CTL_BITOFFSET  0
#define RTC_RRH_EXT_RST_CTL_BITFIELDSIZE 32
#define RTC_RRH_EXT_RST_CTL_BITMASK    0xFFFFFFFF
#define RTC_RRH_EXT_RST_CTL_INIT       0x00000000
/*
 *  RTC_RRH_EXT_RST_CTL_REQ bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_EXT_RST_CTL_REQ_OFFSETADDRESS   RTC_RRH_EXT_RST_CTL_OFFSETADDRESS
#define RTC_RRH_EXT_RST_CTL_REQ_BITOFFSET       0
#define RTC_RRH_EXT_RST_CTL_REQ_BITFIELDSIZE    1
#define RTC_RRH_EXT_RST_CTL_REQ_BITMASK         0x00000001
#define RTC_RRH_EXT_RST_CTL_REQ_INIT            0x0
/*
 *  RTC_RRH_EXT_RST_CTL_POR bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_EXT_RST_CTL_COND_OFFSETADDRESS  RTC_RRH_EXT_RST_CTL_OFFSETADDRESS
#define RTC_RRH_EXT_RST_CTL_COND_BITOFFSET      1
#define RTC_RRH_EXT_RST_CTL_COND_BITFIELDSIZE   1
#define RTC_RRH_EXT_RST_CTL_COND_BITMASK        0x00000002
#define RTC_RRH_EXT_RST_CTL_COND_INIT           0x0

/*
 *  RTC_RRH_ACM3AIRC_STAT register defines
 ****************************************************************************************
 */
#define RTC_RRH_ACM3AIRC_STAT_OFFSETADDRESS 0x00000190  /* RW */
#define RTC_RRH_ACM3AIRC_STAT_BITOFFSET 0
#define RTC_RRH_ACM3AIRC_STAT_BITFIELDSIZE 32
#define RTC_RRH_ACM3AIRC_STAT_BITMASK  0xFFFFFFFF
#define RTC_RRH_ACM3AIRC_STAT_INIT     0x00000000
/*
 *  RTC_RRH_ACM3AIRC_STATUS bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_ACM3AIRC_STATUS_OFFSETADDRESS   RTC_RRH_ACM3AIRC_STAT_OFFSETADDRESS
#define RTC_RRH_ACM3AIRC_STATUS_BITOFFSET       0
#define RTC_RRH_ACM3AIRC_STATUS_BITFIELDSIZE    1
#define RTC_RRH_ACM3AIRC_STATUS_BITMASK         0x00000001
#define RTC_RRH_ACM3AIRC_STATUS_INIT            0x0

/*
 *  RTC_RRH_ACM3AIRC_CTL register defines
 ****************************************************************************************
 */
#define RTC_RRH_ACM3AIRC_CTL_OFFSETADDRESS 0x00000194  /* RW */
#define RTC_RRH_ACM3AIRC_CTL_BITOFFSET 0
#define RTC_RRH_ACM3AIRC_CTL_BITFIELDSIZE 32
#define RTC_RRH_ACM3AIRC_CTL_BITMASK   0xFFFFFFFF
#define RTC_RRH_ACM3AIRC_CTL_INIT      0x00000000
/*
 *  RTC_RRH_ACM3AIRC_CTL_REQ bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_ACM3AIRC_CTL_REQ_OFFSETADDRESS  RTC_RRH_ACM3AIRC_CTL_OFFSETADDRESS
#define RTC_RRH_ACM3AIRC_CTL_REQ_BITOFFSET      0
#define RTC_RRH_ACM3AIRC_CTL_REQ_BITFIELDSIZE   1
#define RTC_RRH_ACM3AIRC_CTL_REQ_BITMASK        0x00000001
#define RTC_RRH_ACM3AIRC_CTL_REQ_INIT           0x0
/*
 *  RTC_RRH_ACM3AIRC_CTL_POR bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_ACM3AIRC_CTL_COND_OFFSETADDRESS RTC_RRH_ACM3AIRC_CTL_OFFSETADDRESS
#define RTC_RRH_ACM3AIRC_CTL_COND_BITOFFSET     1
#define RTC_RRH_ACM3AIRC_CTL_COND_BITFIELDSIZE  1
#define RTC_RRH_ACM3AIRC_CTL_COND_BITMASK       0x00000002
#define RTC_RRH_ACM3AIRC_CTL_COND_INIT          0x0

/*
 *  RTC_RRH_WCM3AIRC_STAT register defines
 ****************************************************************************************
 */
#define RTC_RRH_WCM3AIRC_STAT_OFFSETADDRESS 0x00000198  /* RW */
#define RTC_RRH_WCM3AIRC_STAT_BITOFFSET 0
#define RTC_RRH_WCM3AIRC_STAT_BITFIELDSIZE 32
#define RTC_RRH_WCM3AIRC_STAT_BITMASK  0xFFFFFFFF
#define RTC_RRH_WCM3AIRC_STAT_INIT     0x00000000
/*
 *  RTC_RRH_WCM3AIRC_STATUS bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_WCM3AIRC_STATUS_OFFSETADDRESS   RTC_RRH_WCM3AIRC_STAT_OFFSETADDRESS
#define RTC_RRH_WCM3AIRC_STATUS_BITOFFSET       0
#define RTC_RRH_WCM3AIRC_STATUS_BITFIELDSIZE    1
#define RTC_RRH_WCM3AIRC_STATUS_BITMASK         0x00000001
#define RTC_RRH_WCM3AIRC_STATUS_INIT            0x0

/*
 *  RTC_RRH_WCM3AIRC_CTL register defines
 ****************************************************************************************
 */
#define RTC_RRH_WCM3AIRC_CTL_OFFSETADDRESS 0x0000019c  /* RW */
#define RTC_RRH_WCM3AIRC_CTL_BITOFFSET 0
#define RTC_RRH_WCM3AIRC_CTL_BITFIELDSIZE 32
#define RTC_RRH_WCM3AIRC_CTL_BITMASK   0xFFFFFFFF
#define RTC_RRH_WCM3AIRC_CTL_INIT      0x00000000
/*
 *  RTC_RRH_WCM3AIRC_CTL_REQ bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_WCM3AIRC_CTL_REQ_OFFSETADDRESS  RTC_RRH_WCM3AIRC_CTL_OFFSETADDRESS
#define RTC_RRH_WCM3AIRC_CTL_REQ_BITOFFSET      0
#define RTC_RRH_WCM3AIRC_CTL_REQ_BITFIELDSIZE   1
#define RTC_RRH_WCM3AIRC_CTL_REQ_BITMASK        0x00000001
#define RTC_RRH_WCM3AIRC_CTL_REQ_INIT           0x0
/*
 *  RTC_RRH_WCM3AIRC_CTL_POR bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_WCM3AIRC_CTL_COND_OFFSETADDRESS RTC_RRH_WCM3AIRC_CTL_OFFSETADDRESS
#define RTC_RRH_WCM3AIRC_CTL_COND_BITOFFSET     1
#define RTC_RRH_WCM3AIRC_CTL_COND_BITFIELDSIZE  1
#define RTC_RRH_WCM3AIRC_CTL_COND_BITMASK       0x00000002
#define RTC_RRH_WCM3AIRC_CTL_COND_INIT          0x0

/*
 *  RTC_RRH_AWDOG_STAT register defines
 ****************************************************************************************
 */
#define RTC_RRH_AWDOG_STAT_OFFSETADDRESS 0x000001a0  /* RW */
#define RTC_RRH_AWDOG_STAT_BITOFFSET   0
#define RTC_RRH_AWDOG_STAT_BITFIELDSIZE 32
#define RTC_RRH_AWDOG_STAT_BITMASK     0xFFFFFFFF
#define RTC_RRH_AWDOG_STAT_INIT        0x00000000
/*
 *  RTC_RRH_AWDOG_STATUS bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_AWDOG_STATUS_OFFSETADDRESS      RTC_RRH_AWDOG_STAT_OFFSETADDRESS
#define RTC_RRH_AWDOG_STATUS_BITOFFSET          0
#define RTC_RRH_AWDOG_STATUS_BITFIELDSIZE       1
#define RTC_RRH_AWDOG_STATUS_BITMASK            0x00000001
#define RTC_RRH_AWDOG_STATUS_INIT               0x0

/*
 *  RTC_RRH_AWDOG_CTL register defines
 ****************************************************************************************
 */
#define RTC_RRH_AWDOG_CTL_OFFSETADDRESS 0x000001a4  /* RW */
#define RTC_RRH_AWDOG_CTL_BITOFFSET    0
#define RTC_RRH_AWDOG_CTL_BITFIELDSIZE 32
#define RTC_RRH_AWDOG_CTL_BITMASK      0xFFFFFFFF
#define RTC_RRH_AWDOG_CTL_INIT         0x00000000
/*
 *  RTC_RRH_AWDOG_CTL_REQ bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_AWDOG_CTL_REQ_OFFSETADDRESS     RTC_RRH_AWDOG_CTL_OFFSETADDRESS
#define RTC_RRH_AWDOG_CTL_REQ_BITOFFSET         0
#define RTC_RRH_AWDOG_CTL_REQ_BITFIELDSIZE      1
#define RTC_RRH_AWDOG_CTL_REQ_BITMASK           0x00000001
#define RTC_RRH_AWDOG_CTL_REQ_INIT              0x0
/*
 *  RTC_RRH_AWDOG_CTL_POR bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_AWDOG_CTL_COND_OFFSETADDRESS    RTC_RRH_AWDOG_CTL_OFFSETADDRESS
#define RTC_RRH_AWDOG_CTL_COND_BITOFFSET        1
#define RTC_RRH_AWDOG_CTL_COND_BITFIELDSIZE     1
#define RTC_RRH_AWDOG_CTL_COND_BITMASK          0x00000002
#define RTC_RRH_AWDOG_CTL_COND_INIT             0x0

/*
 *  RTC_RRH_CBO_STAT register defines
 ****************************************************************************************
 */
#define RTC_RRH_CBO_STAT_OFFSETADDRESS 0x000001a8  /* RW */
#define RTC_RRH_CBO_STAT_BITOFFSET     0
#define RTC_RRH_CBO_STAT_BITFIELDSIZE  32
#define RTC_RRH_CBO_STAT_BITMASK       0xFFFFFFFF
#define RTC_RRH_CBO_STAT_INIT          0x00000000
/*
 *  RTC_RRH_CBO_STATUS bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_CBO_STATUS_OFFSETADDRESS        RTC_RRH_CBO_STAT_OFFSETADDRESS
#define RTC_RRH_CBO_STATUS_BITOFFSET            0
#define RTC_RRH_CBO_STATUS_BITFIELDSIZE         1
#define RTC_RRH_CBO_STATUS_BITMASK              0x00000001
#define RTC_RRH_CBO_STATUS_INIT                 0x0

/*
 *  RTC_RRH_CBO_CTL register defines
 ****************************************************************************************
 */
#define RTC_RRH_CBO_CTL_OFFSETADDRESS  0x000001ac  /* RW */
#define RTC_RRH_CBO_CTL_BITOFFSET      0
#define RTC_RRH_CBO_CTL_BITFIELDSIZE   32
#define RTC_RRH_CBO_CTL_BITMASK        0xFFFFFFFF
#define RTC_RRH_CBO_CTL_INIT           0x00000000
/*
 *  RTC_RRH_CBO_CTL_REQ bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_CBO_CTL_REQ_OFFSETADDRESS       RTC_RRH_CBO_CTL_OFFSETADDRESS
#define RTC_RRH_CBO_CTL_REQ_BITOFFSET           0
#define RTC_RRH_CBO_CTL_REQ_BITFIELDSIZE        1
#define RTC_RRH_CBO_CTL_REQ_BITMASK             0x00000001
#define RTC_RRH_CBO_CTL_REQ_INIT                0x0
/*
 *  RTC_RRH_CBO_CTL_POR bit field defines
 ****************************************************************************************
 */
#define RTC_RRH_CBO_CTL_COND_OFFSETADDRESS      RTC_RRH_CBO_CTL_OFFSETADDRESS
#define RTC_RRH_CBO_CTL_COND_BITOFFSET          1
#define RTC_RRH_CBO_CTL_COND_BITFIELDSIZE       1
#define RTC_RRH_CBO_CTL_COND_BITMASK            0x00000002
#define RTC_RRH_CBO_CTL_COND_INIT               0x0

/*
 *  RTC_LDO_STBY_0 register defines
 ****************************************************************************************
 */
#define RTC_LDO_STBY_0_OFFSETADDRESS   0x00000200  /* RW */
#define RTC_LDO_STBY_0_BITOFFSET       0
#define RTC_LDO_STBY_0_BITFIELDSIZE    32
#define RTC_LDO_STBY_0_BITMASK         0xFFFFFFFF
#define RTC_LDO_STBY_0_INIT            0x00000000
/*
 *  RTC_LDO_STBY_0_IN_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_STBY_0_IN_DIG_OFFSETADDRESS     RTC_LDO_STBY_0_OFFSETADDRESS
#define RTC_LDO_STBY_0_IN_DIG_BITOFFSET         0
#define RTC_LDO_STBY_0_IN_DIG_BITFIELDSIZE      1
#define RTC_LDO_STBY_0_IN_DIG_BITMASK           0x00000001
#define RTC_LDO_STBY_0_IN_DIG_INIT              0x0

/*
 *  RTC_LDO_STBY_1 register defines
 ****************************************************************************************
 */
#define RTC_LDO_STBY_1_OFFSETADDRESS   0x00000240  /* RW */
#define RTC_LDO_STBY_1_BITOFFSET       0
#define RTC_LDO_STBY_1_BITFIELDSIZE    32
#define RTC_LDO_STBY_1_BITMASK         0xFFFFFFFF
#define RTC_LDO_STBY_1_INIT            0x00000000
/*
 *  RTC_LDO_STBY_1_IN_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_STBY_1_IN_DIG_OFFSETADDRESS     RTC_LDO_STBY_1_OFFSETADDRESS
#define RTC_LDO_STBY_1_IN_DIG_BITOFFSET         0
#define RTC_LDO_STBY_1_IN_DIG_BITFIELDSIZE      1
#define RTC_LDO_STBY_1_IN_DIG_BITMASK           0x00000001
#define RTC_LDO_STBY_1_IN_DIG_INIT              0x0

/*
 *  RTC_LDO_CTRL_18100_0 register defines
 ****************************************************************************************
 */
#define RTC_LDO_CTRL_18100_0_OFFSETADDRESS 0x00000204  /* RW */
#define RTC_LDO_CTRL_18100_0_BITOFFSET 0
#define RTC_LDO_CTRL_18100_0_BITFIELDSIZE 32
#define RTC_LDO_CTRL_18100_0_BITMASK   0xFFFFFFFF
#define RTC_LDO_CTRL_18100_0_INIT      0x00000000
/*
 *  RTC_LDO_CTRL_18100_0_OUT_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_CTRL_18100_0_OUT_DIG_OFFSETADDRESS RTC_LDO_CTRL_18100_0_OFFSETADDRESS
#define RTC_LDO_CTRL_18100_0_OUT_DIG_BITOFFSET  0
#define RTC_LDO_CTRL_18100_0_OUT_DIG_BITFIELDSIZE  1
#define RTC_LDO_CTRL_18100_0_OUT_DIG_BITMASK    0x00000001
#define RTC_LDO_CTRL_18100_0_OUT_DIG_INIT       0x0

/*
 *  RTC_LDO_CTRL_18100_1 register defines
 ****************************************************************************************
 */
#define RTC_LDO_CTRL_18100_1_OFFSETADDRESS 0x00000244  /* RW */
#define RTC_LDO_CTRL_18100_1_BITOFFSET 0
#define RTC_LDO_CTRL_18100_1_BITFIELDSIZE 32
#define RTC_LDO_CTRL_18100_1_BITMASK   0xFFFFFFFF
#define RTC_LDO_CTRL_18100_1_INIT      0x00000000
/*
 *  RTC_LDO_CTRL_18100_1_OUT_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_CTRL_18100_1_OUT_DIG_OFFSETADDRESS RTC_LDO_CTRL_18100_1_OFFSETADDRESS
#define RTC_LDO_CTRL_18100_1_OUT_DIG_BITOFFSET  0
#define RTC_LDO_CTRL_18100_1_OUT_DIG_BITFIELDSIZE  5
#define RTC_LDO_CTRL_18100_1_OUT_DIG_BITMASK    0x0000001f
#define RTC_LDO_CTRL_18100_1_OUT_DIG_INIT       0x0

/*
 *  RTC_LDO_SEL_CTRL__0 register defines
 ****************************************************************************************
 */
#define RTC_LDO_SEL_CTRL__0_OFFSETADDRESS 0x00000208  /* RW */
#define RTC_LDO_SEL_CTRL__0_BITOFFSET  0
#define RTC_LDO_SEL_CTRL__0_BITFIELDSIZE 32
#define RTC_LDO_SEL_CTRL__0_BITMASK    0xFFFFFFFF
#define RTC_LDO_SEL_CTRL__0_INIT       0x00000000
/*
 *  RTC_LDO_SEL_CTRL__0_OUT_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_SEL_CTRL__0_OUT_DIG_OFFSETADDRESS RTC_LDO_SEL_CTRL__0_OFFSETADDRESS
#define RTC_LDO_SEL_CTRL__0_OUT_DIG_BITOFFSET   0
#define RTC_LDO_SEL_CTRL__0_OUT_DIG_BITFIELDSIZE  1
#define RTC_LDO_SEL_CTRL__0_OUT_DIG_BITMASK     0x00000001
#define RTC_LDO_SEL_CTRL__0_OUT_DIG_INIT        0x0

/*
 *  RTC_LDO_SEL_CTRL__1 register defines
 ****************************************************************************************
 */
#define RTC_LDO_SEL_CTRL__1_OFFSETADDRESS 0x00000248  /* RW */
#define RTC_LDO_SEL_CTRL__1_BITOFFSET  0
#define RTC_LDO_SEL_CTRL__1_BITFIELDSIZE 32
#define RTC_LDO_SEL_CTRL__1_BITMASK    0xFFFFFFFF
#define RTC_LDO_SEL_CTRL__1_INIT       0x00000000
/*
 *  RTC_LDO_SEL_CTRL__1_OUT_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_SEL_CTRL__1_OUT_DIG_OFFSETADDRESS RTC_LDO_SEL_CTRL__1_OFFSETADDRESS
#define RTC_LDO_SEL_CTRL__1_OUT_DIG_BITOFFSET   0
#define RTC_LDO_SEL_CTRL__1_OUT_DIG_BITFIELDSIZE  1
#define RTC_LDO_SEL_CTRL__1_OUT_DIG_BITMASK     0x00000001
#define RTC_LDO_SEL_CTRL__1_OUT_DIG_INIT        0x0

/*
 *  RTC_LDO_FORCE_ON__0 register defines
 ****************************************************************************************
 */
#define RTC_LDO_FORCE_ON__0_OFFSETADDRESS 0x0000020c  /* RW */
#define RTC_LDO_FORCE_ON__0_BITOFFSET  0
#define RTC_LDO_FORCE_ON__0_BITFIELDSIZE 32
#define RTC_LDO_FORCE_ON__0_BITMASK    0xFFFFFFFF
#define RTC_LDO_FORCE_ON__0_INIT       0x00000000
/*
 *  RTC_LDO_FORCE_ON__0_ON_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_FORCE_ON__0_ON_DIG_OFFSETADDRESS RTC_LDO_FORCE_ON__0_OFFSETADDRESS
#define RTC_LDO_FORCE_ON__0_ON_DIG_BITOFFSET    0
#define RTC_LDO_FORCE_ON__0_ON_DIG_BITFIELDSIZE  1
#define RTC_LDO_FORCE_ON__0_ON_DIG_BITMASK      0x00000001
#define RTC_LDO_FORCE_ON__0_ON_DIG_INIT         0x0

/*
 *  RTC_LDO_FORCE_ON__1 register defines
 ****************************************************************************************
 */
#define RTC_LDO_FORCE_ON__1_OFFSETADDRESS 0x0000024c  /* RW */
#define RTC_LDO_FORCE_ON__1_BITOFFSET  0
#define RTC_LDO_FORCE_ON__1_BITFIELDSIZE 32
#define RTC_LDO_FORCE_ON__1_BITMASK    0xFFFFFFFF
#define RTC_LDO_FORCE_ON__1_INIT       0x00000000
/*
 *  RTC_LDO_FORCE_ON__1_ON_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_FORCE_ON__1_ON_DIG_OFFSETADDRESS RTC_LDO_FORCE_ON__1_OFFSETADDRESS
#define RTC_LDO_FORCE_ON__1_ON_DIG_BITOFFSET    0
#define RTC_LDO_FORCE_ON__1_ON_DIG_BITFIELDSIZE  1
#define RTC_LDO_FORCE_ON__1_ON_DIG_BITMASK      0x00000001
#define RTC_LDO_FORCE_ON__1_ON_DIG_INIT         0x0

/*
 *  RTC_LDO_TEST_CTRL_18100__0 register defines
 ****************************************************************************************
 */
#define RTC_LDO_TEST_CTRL_18100__0_OFFSETADDRESS 0x00000210  /* RW */
#define RTC_LDO_TEST_CTRL_18100__0_BITOFFSET 0
#define RTC_LDO_TEST_CTRL_18100__0_BITFIELDSIZE 32
#define RTC_LDO_TEST_CTRL_18100__0_BITMASK 0xFFFFFFFF
#define RTC_LDO_TEST_CTRL_18100__0_INIT 0x00000000
/*
 *  RTC_LDO_TEST_CTRL_18100__0_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_TEST_CTRL_18100__0_DIG_OFFSETADDRESS RTC_LDO_TEST_CTRL_18100__0_OFFSETADDRESS
#define RTC_LDO_TEST_CTRL_18100__0_DIG_BITOFFSET  0
#define RTC_LDO_TEST_CTRL_18100__0_DIG_BITFIELDSIZE  5
#define RTC_LDO_TEST_CTRL_18100__0_DIG_BITMASK  0x0000001f
#define RTC_LDO_TEST_CTRL_18100__0_DIG_INIT     0x0

/*
 *  RTC_LDO_TEST_CTRL_18100__1 register defines
 ****************************************************************************************
 */
#define RTC_LDO_TEST_CTRL_18100__1_OFFSETADDRESS 0x00000250  /* RW */
#define RTC_LDO_TEST_CTRL_18100__1_BITOFFSET 0
#define RTC_LDO_TEST_CTRL_18100__1_BITFIELDSIZE 32
#define RTC_LDO_TEST_CTRL_18100__1_BITMASK 0xFFFFFFFF
#define RTC_LDO_TEST_CTRL_18100__1_INIT 0x00000000
/*
 *  RTC_LDO_TEST_CTRL_18100__1_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_TEST_CTRL_18100__1_DIG_OFFSETADDRESS RTC_LDO_TEST_CTRL_18100__1_OFFSETADDRESS
#define RTC_LDO_TEST_CTRL_18100__1_DIG_BITOFFSET  0
#define RTC_LDO_TEST_CTRL_18100__1_DIG_BITFIELDSIZE  5
#define RTC_LDO_TEST_CTRL_18100__1_DIG_BITMASK  0x0000001f
#define RTC_LDO_TEST_CTRL_18100__1_DIG_INIT     0x0

/*
 *  RTC_LDO_SEL_2P5V__0 register defines
 ****************************************************************************************
 */
#define RTC_LDO_SEL_2P5V__0_OFFSETADDRESS 0x00000214  /* RW */
#define RTC_LDO_SEL_2P5V__0_BITOFFSET  0
#define RTC_LDO_SEL_2P5V__0_BITFIELDSIZE 32
#define RTC_LDO_SEL_2P5V__0_BITMASK    0xFFFFFFFF
#define RTC_LDO_SEL_2P5V__0_INIT       0x00000000
/*
 *  RTC_LDO_SEL_2P5V__0_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_SEL_2P5V__0_DIG_OFFSETADDRESS   RTC_LDO_SEL_2P5V__0_OFFSETADDRESS
#define RTC_LDO_SEL_2P5V__0_DIG_BITOFFSET       0
#define RTC_LDO_SEL_2P5V__0_DIG_BITFIELDSIZE    1
#define RTC_LDO_SEL_2P5V__0_DIG_BITMASK         0x00000001
#define RTC_LDO_SEL_2P5V__0_DIG_INIT            0x0

/*
 *  RTC_LDO_SEL_2P5V__1 register defines
 ****************************************************************************************
 */
#define RTC_LDO_SEL_2P5V__1_OFFSETADDRESS 0x00000254  /* RW */
#define RTC_LDO_SEL_2P5V__1_BITOFFSET  0
#define RTC_LDO_SEL_2P5V__1_BITFIELDSIZE 32
#define RTC_LDO_SEL_2P5V__1_BITMASK    0xFFFFFFFF
#define RTC_LDO_SEL_2P5V__1_INIT       0x00000000
/*
 *  RTC_LDO_SEL_2P5V__1_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_SEL_2P5V__1_DIG_OFFSETADDRESS   RTC_LDO_SEL_2P5V__1_OFFSETADDRESS
#define RTC_LDO_SEL_2P5V__1_DIG_BITOFFSET       0
#define RTC_LDO_SEL_2P5V__1_DIG_BITFIELDSIZE    1
#define RTC_LDO_SEL_2P5V__1_DIG_BITMASK         0x00000001
#define RTC_LDO_SEL_2P5V__1_DIG_INIT            0x0

/*
 *  RTC_LDO_POWERGOOD__0 register defines
 ****************************************************************************************
 */
#define RTC_LDO_POWERGOOD__0_OFFSETADDRESS 0x0000021c  /* R */
#define RTC_LDO_POWERGOOD__0_BITOFFSET 0
#define RTC_LDO_POWERGOOD__0_BITFIELDSIZE 32
#define RTC_LDO_POWERGOOD__0_BITMASK   0xFFFFFFFF
#define RTC_LDO_POWERGOOD__0_INIT      0x00000000
/*
 *  RTC_LDO_POWERGOOD__0_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_POWERGOOD__0_DIG_OFFSETADDRESS  RTC_LDO_POWERGOOD__0_OFFSETADDRESS
#define RTC_LDO_POWERGOOD__0_DIG_BITOFFSET      0
#define RTC_LDO_POWERGOOD__0_DIG_BITFIELDSIZE   1
#define RTC_LDO_POWERGOOD__0_DIG_BITMASK        0x00000001
#define RTC_LDO_POWERGOOD__0_DIG_INIT           0x0

/*
 *  RTC_LDO_POWERGOOD__1 register defines
 ****************************************************************************************
 */
#define RTC_LDO_POWERGOOD__1_OFFSETADDRESS 0x0000025c  /* R */
#define RTC_LDO_POWERGOOD__1_BITOFFSET 0
#define RTC_LDO_POWERGOOD__1_BITFIELDSIZE 32
#define RTC_LDO_POWERGOOD__1_BITMASK   0xFFFFFFFF
#define RTC_LDO_POWERGOOD__1_INIT      0x00000000
/*
 *  RTC_LDO_POWERGOOD__1_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_POWERGOOD__1_DIG_OFFSETADDRESS  RTC_LDO_POWERGOOD__1_OFFSETADDRESS
#define RTC_LDO_POWERGOOD__1_DIG_BITOFFSET      0
#define RTC_LDO_POWERGOOD__1_DIG_BITFIELDSIZE   1
#define RTC_LDO_POWERGOOD__1_DIG_BITMASK        0x00000001
#define RTC_LDO_POWERGOOD__1_DIG_INIT           0x0

/*
 *  RTC_LDO_STBY_IND__0 register defines
 ****************************************************************************************
 */
#define RTC_LDO_STBY_IND__0_OFFSETADDRESS 0x00000220  /* R */
#define RTC_LDO_STBY_IND__0_BITOFFSET  0
#define RTC_LDO_STBY_IND__0_BITFIELDSIZE 32
#define RTC_LDO_STBY_IND__0_BITMASK    0xFFFFFFFF
#define RTC_LDO_STBY_IND__0_INIT       0x00000000
/*
 *  RTC_LDO_STBY_IND__0_OUT_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_STBY_IND__0_OUT_DIG_OFFSETADDRESS RTC_LDO_STBY_IND__0_OFFSETADDRESS
#define RTC_LDO_STBY_IND__0_OUT_DIG_BITOFFSET   0
#define RTC_LDO_STBY_IND__0_OUT_DIG_BITFIELDSIZE  1
#define RTC_LDO_STBY_IND__0_OUT_DIG_BITMASK     0x00000001
#define RTC_LDO_STBY_IND__0_OUT_DIG_INIT        0x0

/*
 *  RTC_LDO_STBY_IND__1 register defines
 ****************************************************************************************
 */
#define RTC_LDO_STBY_IND__1_OFFSETADDRESS 0x00000260  /* R */
#define RTC_LDO_STBY_IND__1_BITOFFSET  0
#define RTC_LDO_STBY_IND__1_BITFIELDSIZE 32
#define RTC_LDO_STBY_IND__1_BITMASK    0xFFFFFFFF
#define RTC_LDO_STBY_IND__1_INIT       0x00000000
/*
 *  RTC_LDO_STBY_IND__1_OUT_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_STBY_IND__1_OUT_DIG_OFFSETADDRESS RTC_LDO_STBY_IND__1_OFFSETADDRESS
#define RTC_LDO_STBY_IND__1_OUT_DIG_BITOFFSET   0
#define RTC_LDO_STBY_IND__1_OUT_DIG_BITFIELDSIZE  1
#define RTC_LDO_STBY_IND__1_OUT_DIG_BITMASK     0x00000001
#define RTC_LDO_STBY_IND__1_OUT_DIG_INIT        0x0

/*
 *  RTC_LDO_TEST_OUT__0 register defines
 ****************************************************************************************
 */
#define RTC_LDO_TEST_OUT__0_OFFSETADDRESS 0x00000224  /* R */
#define RTC_LDO_TEST_OUT__0_BITOFFSET  0
#define RTC_LDO_TEST_OUT__0_BITFIELDSIZE 32
#define RTC_LDO_TEST_OUT__0_BITMASK    0xFFFFFFFF
#define RTC_LDO_TEST_OUT__0_INIT       0x00000000
/*
 *  RTC_LDO_TEST_OUT__0_OUT_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_TEST_OUT__0_OUT_DIG_OFFSETADDRESS RTC_LDO_TEST_OUT__0_OFFSETADDRESS
#define RTC_LDO_TEST_OUT__0_OUT_DIG_BITOFFSET   0
#define RTC_LDO_TEST_OUT__0_OUT_DIG_BITFIELDSIZE  3
#define RTC_LDO_TEST_OUT__0_OUT_DIG_BITMASK     0x00000007
#define RTC_LDO_TEST_OUT__0_OUT_DIG_INIT        0x0

/*
 *  RTC_LDO_TEST_OUT__1 register defines
 ****************************************************************************************
 */
#define RTC_LDO_TEST_OUT__1_OFFSETADDRESS 0x00000264  /* R */
#define RTC_LDO_TEST_OUT__1_BITOFFSET  0
#define RTC_LDO_TEST_OUT__1_BITFIELDSIZE 32
#define RTC_LDO_TEST_OUT__1_BITMASK    0xFFFFFFFF
#define RTC_LDO_TEST_OUT__1_INIT       0x00000000
/*
 *  RTC_LDO_TEST_OUT__1_OUT_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_TEST_OUT__1_OUT_DIG_OFFSETADDRESS RTC_LDO_TEST_OUT__1_OFFSETADDRESS
#define RTC_LDO_TEST_OUT__1_OUT_DIG_BITOFFSET   0
#define RTC_LDO_TEST_OUT__1_OUT_DIG_BITFIELDSIZE  3
#define RTC_LDO_TEST_OUT__1_OUT_DIG_BITMASK     0x00000007
#define RTC_LDO_TEST_OUT__1_OUT_DIG_INIT        0x0

/*
 *  RTC_LDO_STBY_30300 register defines
 ****************************************************************************************
 */
#define RTC_LDO_STBY_30300_OFFSETADDRESS 0x00000280  /* RW */
#define RTC_LDO_STBY_30300_BITOFFSET   0
#define RTC_LDO_STBY_30300_BITFIELDSIZE 32
#define RTC_LDO_STBY_30300_BITMASK     0xFFFFFFFF
#define RTC_LDO_STBY_30300_INIT        0x00000000
/*
 *  RTC_LDO_STBY_30300_IN_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_STBY_30300_IN_DIG_OFFSETADDRESS RTC_LDO_STBY_30300_OFFSETADDRESS
#define RTC_LDO_STBY_30300_IN_DIG_BITOFFSET     0
#define RTC_LDO_STBY_30300_IN_DIG_BITFIELDSIZE  1
#define RTC_LDO_STBY_30300_IN_DIG_BITMASK       0x00000001
#define RTC_LDO_STBY_30300_IN_DIG_INIT          0x0

/*
 *  RTC_LDO_CTRL_30300 register defines
 ****************************************************************************************
 */
#define RTC_LDO_CTRL_30300_OFFSETADDRESS 0x00000284  /* RW */
#define RTC_LDO_CTRL_30300_BITOFFSET   0
#define RTC_LDO_CTRL_30300_BITFIELDSIZE 32
#define RTC_LDO_CTRL_30300_BITMASK     0xFFFFFFFF
#define RTC_LDO_CTRL_30300_INIT        0x00000000
/*
 *  RTC_LDO_CTRL_30300_OUT_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_CTRL_30300_OUT_DIG_OFFSETADDRESS RTC_LDO_CTRL_30300_OFFSETADDRESS
#define RTC_LDO_CTRL_30300_OUT_DIG_BITOFFSET    0
#define RTC_LDO_CTRL_30300_OUT_DIG_BITFIELDSIZE  3
#define RTC_LDO_CTRL_30300_OUT_DIG_BITMASK      0x00000007
#define RTC_LDO_CTRL_30300_OUT_DIG_INIT         0x0

/*
 *  RTC_LDO_SEL_CTRL_30300 register defines
 ****************************************************************************************
 */
#define RTC_LDO_SEL_CTRL_30300_OFFSETADDRESS 0x00000288  /* RW */
#define RTC_LDO_SEL_CTRL_30300_BITOFFSET 0
#define RTC_LDO_SEL_CTRL_30300_BITFIELDSIZE 32
#define RTC_LDO_SEL_CTRL_30300_BITMASK 0xFFFFFFFF
#define RTC_LDO_SEL_CTRL_30300_INIT    0x00000000
/*
 *  RTC_LDO_SEL_CTRL_30300_OUT_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_SEL_CTRL_30300_OUT_DIG_OFFSETADDRESS RTC_LDO_SEL_CTRL_30300_OFFSETADDRESS
#define RTC_LDO_SEL_CTRL_30300_OUT_DIG_BITOFFSET  0
#define RTC_LDO_SEL_CTRL_30300_OUT_DIG_BITFIELDSIZE  1
#define RTC_LDO_SEL_CTRL_30300_OUT_DIG_BITMASK  0x00000001
#define RTC_LDO_SEL_CTRL_30300_OUT_DIG_INIT     0x0

/*
 *  RTC_LDO_FORCE_ON_30300 register defines
 ****************************************************************************************
 */
#define RTC_LDO_FORCE_ON_30300_OFFSETADDRESS 0x0000028c  /* RW */
#define RTC_LDO_FORCE_ON_30300_BITOFFSET 0
#define RTC_LDO_FORCE_ON_30300_BITFIELDSIZE 32
#define RTC_LDO_FORCE_ON_30300_BITMASK 0xFFFFFFFF
#define RTC_LDO_FORCE_ON_30300_INIT    0x00000000
/*
 *  RTC_LDO_FORCE_ON_30300_ON_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_FORCE_ON_30300_ON_DIG_OFFSETADDRESS RTC_LDO_FORCE_ON_30300_OFFSETADDRESS
#define RTC_LDO_FORCE_ON_30300_ON_DIG_BITOFFSET  0
#define RTC_LDO_FORCE_ON_30300_ON_DIG_BITFIELDSIZE  1
#define RTC_LDO_FORCE_ON_30300_ON_DIG_BITMASK   0x00000001
#define RTC_LDO_FORCE_ON_30300_ON_DIG_INIT      0x0

/*
 *  RTC_LDO_TEST_CTRL_30300 register defines
 ****************************************************************************************
 */
#define RTC_LDO_TEST_CTRL_30300_OFFSETADDRESS 0x00000290  /* RW */
#define RTC_LDO_TEST_CTRL_30300_BITOFFSET 0
#define RTC_LDO_TEST_CTRL_30300_BITFIELDSIZE 32
#define RTC_LDO_TEST_CTRL_30300_BITMASK 0xFFFFFFFF
#define RTC_LDO_TEST_CTRL_30300_INIT   0x00000000
/*
 *  RTC_LDO_TEST_CTRL_30300_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_TEST_CTRL_30300_DIG_OFFSETADDRESS RTC_LDO_TEST_CTRL_30300_OFFSETADDRESS
#define RTC_LDO_TEST_CTRL_30300_DIG_BITOFFSET   0
#define RTC_LDO_TEST_CTRL_30300_DIG_BITFIELDSIZE  3
#define RTC_LDO_TEST_CTRL_30300_DIG_BITMASK     0x00000007
#define RTC_LDO_TEST_CTRL_30300_DIG_INIT        0x0

/*
 *  RTC_LDO_SEL_2P5V_30300 register defines
 ****************************************************************************************
 */
#define RTC_LDO_SEL_2P5V_30300_OFFSETADDRESS 0x00000294  /* RW */
#define RTC_LDO_SEL_2P5V_30300_BITOFFSET 0
#define RTC_LDO_SEL_2P5V_30300_BITFIELDSIZE 32
#define RTC_LDO_SEL_2P5V_30300_BITMASK 0xFFFFFFFF
#define RTC_LDO_SEL_2P5V_30300_INIT    0x00000000
/*
 *  RTC_LDO_SEL_2P5V_30300_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_SEL_2P5V_30300_DIG_OFFSETADDRESS RTC_LDO_SEL_2P5V_30300_OFFSETADDRESS
#define RTC_LDO_SEL_2P5V_30300_DIG_BITOFFSET    0
#define RTC_LDO_SEL_2P5V_30300_DIG_BITFIELDSIZE  1
#define RTC_LDO_SEL_2P5V_30300_DIG_BITMASK      0x00000001
#define RTC_LDO_SEL_2P5V_30300_DIG_INIT         0x0

/*
 *  RTC_LDO_PG_VDD_30300 register defines
 ****************************************************************************************
 */
#define RTC_LDO_PG_VDD_30300_OFFSETADDRESS 0x00000298  /* RW */
#define RTC_LDO_PG_VDD_30300_BITOFFSET 0
#define RTC_LDO_PG_VDD_30300_BITFIELDSIZE 32
#define RTC_LDO_PG_VDD_30300_BITMASK   0xFFFFFFFF
#define RTC_LDO_PG_VDD_30300_INIT      0x00000000
/*
 *  RTC_LDO_PG_VDD_30300_PG_VDD bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_PG_VDD_30300_PG_VDD_OFFSETADDRESS RTC_LDO_PG_VDD_30300_OFFSETADDRESS
#define RTC_LDO_PG_VDD_30300_PG_VDD_BITOFFSET   0
#define RTC_LDO_PG_VDD_30300_PG_VDD_BITFIELDSIZE  1
#define RTC_LDO_PG_VDD_30300_PG_VDD_BITMASK     0x00000001
#define RTC_LDO_PG_VDD_30300_PG_VDD_INIT        0x0

/*
 *  RTC_LDO_POWERGOOD_30300 register defines
 ****************************************************************************************
 */
#define RTC_LDO_POWERGOOD_30300_OFFSETADDRESS 0x0000029c  /* R */
#define RTC_LDO_POWERGOOD_30300_BITOFFSET 0
#define RTC_LDO_POWERGOOD_30300_BITFIELDSIZE 32
#define RTC_LDO_POWERGOOD_30300_BITMASK 0xFFFFFFFF
#define RTC_LDO_POWERGOOD_30300_INIT   0x00000000
/*
 *  RTC_LDO_POWERGOOD_30300_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_POWERGOOD_30300_DIG_OFFSETADDRESS RTC_LDO_POWERGOOD_30300_OFFSETADDRESS
#define RTC_LDO_POWERGOOD_30300_DIG_BITOFFSET   0
#define RTC_LDO_POWERGOOD_30300_DIG_BITFIELDSIZE  1
#define RTC_LDO_POWERGOOD_30300_DIG_BITMASK     0x00000001
#define RTC_LDO_POWERGOOD_30300_DIG_INIT        0x0

/*
 *  RTC_LDO_STBY_IND_30300 register defines
 ****************************************************************************************
 */
#define RTC_LDO_STBY_IND_30300_OFFSETADDRESS 0x000002a0  /* R */
#define RTC_LDO_STBY_IND_30300_BITOFFSET 0
#define RTC_LDO_STBY_IND_30300_BITFIELDSIZE 32
#define RTC_LDO_STBY_IND_30300_BITMASK 0xFFFFFFFF
#define RTC_LDO_STBY_IND_30300_INIT    0x00000000
/*
 *  RTC_LDO_STBY_IND_30300_OUT_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_STBY_IND_30300_OUT_DIG_OFFSETADDRESS RTC_LDO_STBY_IND_30300_OFFSETADDRESS
#define RTC_LDO_STBY_IND_30300_OUT_DIG_BITOFFSET  0
#define RTC_LDO_STBY_IND_30300_OUT_DIG_BITFIELDSIZE  1
#define RTC_LDO_STBY_IND_30300_OUT_DIG_BITMASK  0x00000001
#define RTC_LDO_STBY_IND_30300_OUT_DIG_INIT     0x0

/*
 *  RTC_LDO_TEST_OUT_30300 register defines
 ****************************************************************************************
 */
#define RTC_LDO_TEST_OUT_30300_OFFSETADDRESS 0x000002a0  /* R */
#define RTC_LDO_TEST_OUT_30300_BITOFFSET 0
#define RTC_LDO_TEST_OUT_30300_BITFIELDSIZE 32
#define RTC_LDO_TEST_OUT_30300_BITMASK 0xFFFFFFFF
#define RTC_LDO_TEST_OUT_30300_INIT    0x00000000
/*
 *  RTC_LDO_TEST_OUT_30300_OUT_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_LDO_TEST_OUT_30300_OUT_DIG_OFFSETADDRESS RTC_LDO_TEST_OUT_30300_OFFSETADDRESS
#define RTC_LDO_TEST_OUT_30300_OUT_DIG_BITOFFSET  0
#define RTC_LDO_TEST_OUT_30300_OUT_DIG_BITFIELDSIZE  3
#define RTC_LDO_TEST_OUT_30300_OUT_DIG_BITMASK  0x00000007
#define RTC_LDO_TEST_OUT_30300_OUT_DIG_INIT     0x0

/*
 *  RTC_BG_OK register defines
 ****************************************************************************************
 */
#define RTC_BG_OK_OFFSETADDRESS        0x000002c0  /* R */
#define RTC_BG_OK_BITOFFSET            0
#define RTC_BG_OK_BITFIELDSIZE         32
#define RTC_BG_OK_BITMASK              0xFFFFFFFF
#define RTC_BG_OK_INIT                 0x00000000
/*
 *  RTC_BG_OK_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_BG_OK_DIG_OFFSETADDRESS             RTC_BG_OK_OFFSETADDRESS
#define RTC_BG_OK_DIG_BITOFFSET                 0
#define RTC_BG_OK_DIG_BITFIELDSIZE              1
#define RTC_BG_OK_DIG_BITMASK                   0x00000001
#define RTC_BG_OK_DIG_INIT                      0x0

/*
 *  RTC_BG_TEST_DATA register defines
 ****************************************************************************************
 */
#define RTC_BG_TEST_DATA_OFFSETADDRESS 0x000002c4  /* R */
#define RTC_BG_TEST_DATA_BITOFFSET     0
#define RTC_BG_TEST_DATA_BITFIELDSIZE  32
#define RTC_BG_TEST_DATA_BITMASK       0xFFFFFFFF
#define RTC_BG_TEST_DATA_INIT          0x00000000
/*
 *  RTC_BG_TEST_DATA_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_BG_TEST_DATA_VAL_OFFSETADDRESS      RTC_BG_TEST_DATA_OFFSETADDRESS
#define RTC_BG_TEST_DATA_VAL_BITOFFSET          0
#define RTC_BG_TEST_DATA_VAL_BITFIELDSIZE       6
#define RTC_BG_TEST_DATA_VAL_BITMASK            0x0000003f
#define RTC_BG_TEST_DATA_VAL_INIT               0x0

/*
 *  RTC_BG_TEST_CTRL register defines
 ****************************************************************************************
 */
#define RTC_BG_TEST_CTRL_OFFSETADDRESS 0x000002c8  /* RW */
#define RTC_BG_TEST_CTRL_BITOFFSET     0
#define RTC_BG_TEST_CTRL_BITFIELDSIZE  32
#define RTC_BG_TEST_CTRL_BITMASK       0xFFFFFFFF
#define RTC_BG_TEST_CTRL_INIT          0x00000000
/*
 *  RTC_BG_TEST_CTRL_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_BG_TEST_CTRL_DIG_OFFSETADDRESS      RTC_BG_TEST_CTRL_OFFSETADDRESS
#define RTC_BG_TEST_CTRL_DIG_BITOFFSET          0
#define RTC_BG_TEST_CTRL_DIG_BITFIELDSIZE      10
#define RTC_BG_TEST_CTRL_DIG_BITMASK            0x000003ff
#define RTC_BG_TEST_CTRL_DIG_INIT               0x0

/*
 *  RTC_BG_TRIM register defines
 ****************************************************************************************
 */
#define RTC_BG_TRIM_OFFSETADDRESS      0x000002cc  /* RW */
#define RTC_BG_TRIM_BITOFFSET          0
#define RTC_BG_TRIM_BITFIELDSIZE       32
#define RTC_BG_TRIM_BITMASK            0xFFFFFFFF
#define RTC_BG_TRIM_INIT               0x00000000
/*
 *  RTC_BG_TRIM_DIG bit field defines
 ****************************************************************************************
 */
#define RTC_BG_TRIM_DIG_OFFSETADDRESS           RTC_BG_TRIM_OFFSETADDRESS
#define RTC_BG_TRIM_DIG_BITOFFSET               0
#define RTC_BG_TRIM_DIG_BITFIELDSIZE            4
#define RTC_BG_TRIM_DIG_BITMASK                 0x0000000f
#define RTC_BG_TRIM_DIG_INIT                    0x0

/*
 *  RTC_CX_BG_CTRL register defines
 ****************************************************************************************
 */
#define RTC_CX_BG_CTRL_OFFSETADDRESS   0x000002d0  /* RW */
#define RTC_CX_BG_CTRL_BITOFFSET       0
#define RTC_CX_BG_CTRL_BITFIELDSIZE    32
#define RTC_CX_BG_CTRL_BITMASK         0xFFFFFFFF
#define RTC_CX_BG_CTRL_INIT            0x00000000
/*
 *  RTC_CX_BG_CTRL_F bit field defines
 ****************************************************************************************
 */
#define RTC_CX_BG_CTRL_F_OFFSETADDRESS          RTC_CX_BG_CTRL_OFFSETADDRESS
#define RTC_CX_BG_CTRL_F_BITOFFSET              0
#define RTC_CX_BG_CTRL_F_BITFIELDSIZE           2
#define RTC_CX_BG_CTRL_F_BITMASK                0x00000003
#define RTC_CX_BG_CTRL_F_INIT                   0x0

/*
 *  RTC_CX_C1_CTRL register defines
 ****************************************************************************************
 */
#define RTC_CX_C1_CTRL_OFFSETADDRESS   0x000002d4  /* RW */
#define RTC_CX_C1_CTRL_BITOFFSET       0
#define RTC_CX_C1_CTRL_BITFIELDSIZE    32
#define RTC_CX_C1_CTRL_BITMASK         0xFFFFFFFF
#define RTC_CX_C1_CTRL_INIT            0x00000000
/*
 *  RTC_CX_C1_CTRL_F bit field defines
 ****************************************************************************************
 */
#define RTC_CX_C1_CTRL_F_OFFSETADDRESS          RTC_CX_C1_CTRL_OFFSETADDRESS
#define RTC_CX_C1_CTRL_F_BITOFFSET              0
#define RTC_CX_C1_CTRL_F_BITFIELDSIZE           8
#define RTC_CX_C1_CTRL_F_BITMASK                0x000000ff
#define RTC_CX_C1_CTRL_F_INIT                   0x0

/*
 *  RTC_CX_C2_CTRL register defines
 ****************************************************************************************
 */
#define RTC_CX_C2_CTRL_OFFSETADDRESS   0x000002d8  /* RW */
#define RTC_CX_C2_CTRL_BITOFFSET       0
#define RTC_CX_C2_CTRL_BITFIELDSIZE    32
#define RTC_CX_C2_CTRL_BITMASK         0xFFFFFFFF
#define RTC_CX_C2_CTRL_INIT            0x00000000
/*
 *  RTC_CX_C2_CTRL_F bit field defines
 ****************************************************************************************
 */
#define RTC_CX_C2_CTRL_F_OFFSETADDRESS          RTC_CX_C2_CTRL_OFFSETADDRESS
#define RTC_CX_C2_CTRL_F_BITOFFSET              0
#define RTC_CX_C2_CTRL_F_BITFIELDSIZE           8
#define RTC_CX_C2_CTRL_F_BITMASK                0x000000ff
#define RTC_CX_C2_CTRL_F_INIT                   0x0

/*
 *  RTC_CX_CAL_CTL register defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_CTL_OFFSETADDRESS   0x000002dc  /* RW */
#define RTC_CX_CAL_CTL_BITOFFSET       0
#define RTC_CX_CAL_CTL_BITFIELDSIZE    32
#define RTC_CX_CAL_CTL_BITMASK         0xFFFFFFFF
#define RTC_CX_CAL_CTL_INIT            0x00000000
/*
 *  RTC_CX_CAL_CLK_ENA bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_CLK_ENA_OFFSETADDRESS        RTC_CX_CAL_CTL_OFFSETADDRESS
#define RTC_CX_CAL_CLK_ENA_BITOFFSET            0
#define RTC_CX_CAL_CLK_ENA_BITFIELDSIZE         1
#define RTC_CX_CAL_CLK_ENA_BITMASK              0x00000001
#define RTC_CX_CAL_CLK_ENA_INIT                 0x0
/*
 *  RTC_CX_OSC_IN_HOLD bit field defines
 ****************************************************************************************
 */
#define RTC_CX_OSC_IN_HOLD_OFFSETADDRESS        RTC_CX_CAL_CTL_OFFSETADDRESS
#define RTC_CX_OSC_IN_HOLD_BITOFFSET            1
#define RTC_CX_OSC_IN_HOLD_BITFIELDSIZE         1
#define RTC_CX_OSC_IN_HOLD_BITMASK              0x00000002
#define RTC_CX_OSC_IN_HOLD_INIT                 0x0
/*
 *  RTC_CX_RESET_CAL_N bit field defines
 ****************************************************************************************
 */
#define RTC_CX_RESET_CAL_N_OFFSETADDRESS        RTC_CX_CAL_CTL_OFFSETADDRESS
#define RTC_CX_RESET_CAL_N_BITOFFSET            2
#define RTC_CX_RESET_CAL_N_BITFIELDSIZE         1
#define RTC_CX_RESET_CAL_N_BITMASK              0x00000004
#define RTC_CX_RESET_CAL_N_INIT                 0x0

/*
 *  RTC_CX_CAL_ENA register defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_ENA_OFFSETADDRESS   0x000002e0  /* RW */
#define RTC_CX_CAL_ENA_BITOFFSET       0
#define RTC_CX_CAL_ENA_BITFIELDSIZE    32
#define RTC_CX_CAL_ENA_BITMASK         0xFFFFFFFF
#define RTC_CX_CAL_ENA_INIT            0x00000000
/*
 *  RTC_CX_CAL_ENABLE bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_ENABLE_OFFSETADDRESS         RTC_CX_CAL_ENA_OFFSETADDRESS
#define RTC_CX_CAL_ENABLE_BITOFFSET             0
#define RTC_CX_CAL_ENABLE_BITFIELDSIZE          1
#define RTC_CX_CAL_ENABLE_BITMASK               0x00000001
#define RTC_CX_CAL_ENABLE_INIT                  0x0

/*
 *  RTC_CX_CAL_EXT_IN register defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_EXT_IN_OFFSETADDRESS 0x000002e4  /* RW */
#define RTC_CX_CAL_EXT_IN_BITOFFSET    0
#define RTC_CX_CAL_EXT_IN_BITFIELDSIZE 32
#define RTC_CX_CAL_EXT_IN_BITMASK      0xFFFFFFFF
#define RTC_CX_CAL_EXT_IN_INIT         0x00000000
/*
 *  RTC_CX_CAL_EXT_INPUT bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_EXT_INPUT_OFFSETADDRESS      RTC_CX_CAL_EXT_IN_OFFSETADDRESS
#define RTC_CX_CAL_EXT_INPUT_BITOFFSET          0
#define RTC_CX_CAL_EXT_INPUT_BITFIELDSIZE      10
#define RTC_CX_CAL_EXT_INPUT_BITMASK            0x000003ff
#define RTC_CX_CAL_EXT_INPUT_INIT               0x0

/*
 *  RTC_CX_CAL_OFF_VAL register defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_OFF_VAL_OFFSETADDRESS 0x000002e8  /* RW */
#define RTC_CX_CAL_OFF_VAL_BITOFFSET   0
#define RTC_CX_CAL_OFF_VAL_BITFIELDSIZE 32
#define RTC_CX_CAL_OFF_VAL_BITMASK     0xFFFFFFFF
#define RTC_CX_CAL_OFF_VAL_INIT        0x00000000
/*
 *  RTC_CX_CAL_OFF_VALUE bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_OFF_VALUE_OFFSETADDRESS      RTC_CX_CAL_OFF_VAL_OFFSETADDRESS
#define RTC_CX_CAL_OFF_VALUE_BITOFFSET          0
#define RTC_CX_CAL_OFF_VALUE_BITFIELDSIZE      10
#define RTC_CX_CAL_OFF_VALUE_BITMASK            0x000003ff
#define RTC_CX_CAL_OFF_VALUE_INIT               0x0

/*
 *  RTC_CX_CAL_OVER_WRITE register defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_OVER_WRITE_OFFSETADDRESS 0x000002ec  /* RW */
#define RTC_CX_CAL_OVER_WRITE_BITOFFSET 0
#define RTC_CX_CAL_OVER_WRITE_BITFIELDSIZE 32
#define RTC_CX_CAL_OVER_WRITE_BITMASK  0xFFFFFFFF
#define RTC_CX_CAL_OVER_WRITE_INIT     0x00000000
/*
 *  RTC_CX_CAL_OVER_WRITE_F bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_OVER_WRITE_F_OFFSETADDRESS   RTC_CX_CAL_OVER_WRITE_OFFSETADDRESS
#define RTC_CX_CAL_OVER_WRITE_F_BITOFFSET       0
#define RTC_CX_CAL_OVER_WRITE_F_BITFIELDSIZE    1
#define RTC_CX_CAL_OVER_WRITE_F_BITMASK         0x00000001
#define RTC_CX_CAL_OVER_WRITE_F_INIT            0x0

/*
 *  RTC_CX_CAL_REG_OUT register defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_REG_OUT_OFFSETADDRESS 0x000002f0  /* RW */
#define RTC_CX_CAL_REG_OUT_BITOFFSET   0
#define RTC_CX_CAL_REG_OUT_BITFIELDSIZE 32
#define RTC_CX_CAL_REG_OUT_BITMASK     0xFFFFFFFF
#define RTC_CX_CAL_REG_OUT_INIT        0x00000000
/*
 *  RTC_CX_CAL_REG_OUT_F bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_REG_OUT_F_OFFSETADDRESS      RTC_CX_CAL_REG_OUT_OFFSETADDRESS
#define RTC_CX_CAL_REG_OUT_F_BITOFFSET          0
#define RTC_CX_CAL_REG_OUT_F_BITFIELDSIZE      10
#define RTC_CX_CAL_REG_OUT_F_BITMASK            0x000003ff
#define RTC_CX_CAL_REG_OUT_F_INIT               0x0

/*
 *  RTC_CX_CAL_ACC_ATTN register defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_ACC_ATTN_OFFSETADDRESS 0x000002f4  /* RW */
#define RTC_CX_CAL_ACC_ATTN_BITOFFSET  0
#define RTC_CX_CAL_ACC_ATTN_BITFIELDSIZE 32
#define RTC_CX_CAL_ACC_ATTN_BITMASK    0xFFFFFFFF
#define RTC_CX_CAL_ACC_ATTN_INIT       0x00000000
/*
 *  RTC_CX_CAL_ACCUM_ATTN bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_ACCUM_ATTN_OFFSETADDRESS     RTC_CX_CAL_ACC_ATTN_OFFSETADDRESS
#define RTC_CX_CAL_ACCUM_ATTN_BITOFFSET         0
#define RTC_CX_CAL_ACCUM_ATTN_BITFIELDSIZE      2
#define RTC_CX_CAL_ACCUM_ATTN_BITMASK           0x00000003
#define RTC_CX_CAL_ACCUM_ATTN_INIT              0x0

/*
 *  RTC_CX_CAL_ACC_INC register defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_ACC_INC_OFFSETADDRESS 0x000002f8  /* RW */
#define RTC_CX_CAL_ACC_INC_BITOFFSET   0
#define RTC_CX_CAL_ACC_INC_BITFIELDSIZE 32
#define RTC_CX_CAL_ACC_INC_BITMASK     0xFFFFFFFF
#define RTC_CX_CAL_ACC_INC_INIT        0x00000000
/*
 *  RTC_CX_CAL_ACCUM_INC bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_ACCUM_INC_OFFSETADDRESS      RTC_CX_CAL_ACC_INC_OFFSETADDRESS
#define RTC_CX_CAL_ACCUM_INC_BITOFFSET          0
#define RTC_CX_CAL_ACCUM_INC_BITFIELDSIZE       2
#define RTC_CX_CAL_ACCUM_INC_BITMASK            0x00000003
#define RTC_CX_CAL_ACCUM_INC_INIT               0x0

/*
 *  RTC_CX_CAL_FREQ_ACCU_INC register defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_FREQ_ACCU_INC_OFFSETADDRESS 0x000002fc  /* RW */
#define RTC_CX_CAL_FREQ_ACCU_INC_BITOFFSET 0
#define RTC_CX_CAL_FREQ_ACCU_INC_BITFIELDSIZE 32
#define RTC_CX_CAL_FREQ_ACCU_INC_BITMASK 0xFFFFFFFF
#define RTC_CX_CAL_FREQ_ACCU_INC_INIT  0x00000000
/*
 *  RTC_CX_CAL_FREQ_ACCU bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CAL_FREQ_ACCU_OFFSETADDRESS      RTC_CX_CAL_FREQ_ACCU_INC_OFFSETADDRESS
#define RTC_CX_CAL_FREQ_ACCU_BITOFFSET          0
#define RTC_CX_CAL_FREQ_ACCU_BITFIELDSIZE       2
#define RTC_CX_CAL_FREQ_ACCU_BITMASK            0x00000003
#define RTC_CX_CAL_FREQ_ACCU_INIT               0x0

/*
 *  RTC_CX_CLK_PLL_ENABLE register defines
 ****************************************************************************************
 */
#define RTC_CX_CLK_PLL_ENABLE_OFFSETADDRESS 0x00000300  /* RW */
#define RTC_CX_CLK_PLL_ENABLE_BITOFFSET 0
#define RTC_CX_CLK_PLL_ENABLE_BITFIELDSIZE 32
#define RTC_CX_CLK_PLL_ENABLE_BITMASK  0xFFFFFFFF
#define RTC_CX_CLK_PLL_ENABLE_INIT     0x00000000
/*
 *  RTC_CX_CLK_DIG1_ENA bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CLK_DIG1_ENA_OFFSETADDRESS       RTC_CX_CLK_PLL_ENABLE_OFFSETADDRESS
#define RTC_CX_CLK_DIG1_ENA_BITOFFSET           0
#define RTC_CX_CLK_DIG1_ENA_BITFIELDSIZE        1
#define RTC_CX_CLK_DIG1_ENA_BITMASK             0x00000001
#define RTC_CX_CLK_DIG1_ENA_INIT                0x0
/*
 *  RTC_CX_CLK_DIG2_ENA bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CLK_DIG2_ENA_OFFSETADDRESS       RTC_CX_CLK_PLL_ENABLE_OFFSETADDRESS
#define RTC_CX_CLK_DIG2_ENA_BITOFFSET           1
#define RTC_CX_CLK_DIG2_ENA_BITFIELDSIZE        1
#define RTC_CX_CLK_DIG2_ENA_BITMASK             0x00000002
#define RTC_CX_CLK_DIG2_ENA_INIT                0x0
/*
 *  RTC_CX_CLK_DIG3_ENA bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CLK_DIG3_ENA_OFFSETADDRESS       RTC_CX_CLK_PLL_ENABLE_OFFSETADDRESS
#define RTC_CX_CLK_DIG3_ENA_BITOFFSET           2
#define RTC_CX_CLK_DIG3_ENA_BITFIELDSIZE        1
#define RTC_CX_CLK_DIG3_ENA_BITMASK             0x00000004
#define RTC_CX_CLK_DIG3_ENA_INIT                0x0
/*
 *  RTC_CX_CLK_DIG4_ENA bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CLK_DIG4_ENA_OFFSETADDRESS       RTC_CX_CLK_PLL_ENABLE_OFFSETADDRESS
#define RTC_CX_CLK_DIG4_ENA_BITOFFSET           3
#define RTC_CX_CLK_DIG4_ENA_BITFIELDSIZE        1
#define RTC_CX_CLK_DIG4_ENA_BITMASK             0x00000008
#define RTC_CX_CLK_DIG4_ENA_INIT                0x0
/*
 *  RTC_CX_CLK_DIG5_ENA bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CLK_DIG5_ENA_OFFSETADDRESS       RTC_CX_CLK_PLL_ENABLE_OFFSETADDRESS
#define RTC_CX_CLK_DIG5_ENA_BITOFFSET           4
#define RTC_CX_CLK_DIG5_ENA_BITFIELDSIZE        1
#define RTC_CX_CLK_DIG5_ENA_BITMASK             0x00000010
#define RTC_CX_CLK_DIG5_ENA_INIT                0x0
/*
 *  RTC_CX_CLK_DIG6_ENA bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CLK_DIG6_ENA_OFFSETADDRESS       RTC_CX_CLK_PLL_ENABLE_OFFSETADDRESS
#define RTC_CX_CLK_DIG6_ENA_BITOFFSET           5
#define RTC_CX_CLK_DIG6_ENA_BITFIELDSIZE        1
#define RTC_CX_CLK_DIG6_ENA_BITMASK             0x00000020
#define RTC_CX_CLK_DIG6_ENA_INIT                0x0
/*
 *  RTC_CX_CLK_ADC_ENA bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CLK_ADC_ENA_OFFSETADDRESS        RTC_CX_CLK_PLL_ENABLE_OFFSETADDRESS
#define RTC_CX_CLK_ADC_ENA_BITOFFSET            6
#define RTC_CX_CLK_ADC_ENA_BITFIELDSIZE         1
#define RTC_CX_CLK_ADC_ENA_BITMASK              0x00000040
#define RTC_CX_CLK_ADC_ENA_INIT                 0x0
/*
 *  RTC_CX_CLK_DAC_ENA bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CLK_DAC_ENA_OFFSETADDRESS        RTC_CX_CLK_PLL_ENABLE_OFFSETADDRESS
#define RTC_CX_CLK_DAC_ENA_BITOFFSET            7
#define RTC_CX_CLK_DAC_ENA_BITFIELDSIZE         1
#define RTC_CX_CLK_DAC_ENA_BITMASK              0x00000080
#define RTC_CX_CLK_DAC_ENA_INIT                 0x0

/*
 *  RTC_CX_FB_DIV_SEL register defines
 ****************************************************************************************
 */
#define RTC_CX_FB_DIV_SEL_OFFSETADDRESS 0x00000308  /* RW */
#define RTC_CX_FB_DIV_SEL_BITOFFSET    0
#define RTC_CX_FB_DIV_SEL_BITFIELDSIZE 32
#define RTC_CX_FB_DIV_SEL_BITMASK      0xFFFFFFFF
#define RTC_CX_FB_DIV_SEL_INIT         0x00000000
/*
 *  RTC_CX_FB_DIV_SEL_PLL bit field defines
 ****************************************************************************************
 */
#define RTC_CX_FB_DIV_SEL_PLL_OFFSETADDRESS     RTC_CX_FB_DIV_SEL_OFFSETADDRESS
#define RTC_CX_FB_DIV_SEL_PLL_BITOFFSET         0
#define RTC_CX_FB_DIV_SEL_PLL_BITFIELDSIZE      5
#define RTC_CX_FB_DIV_SEL_PLL_BITMASK           0x0000001f
#define RTC_CX_FB_DIV_SEL_PLL_INIT              0x0

/*
 *  RTC_CX_LPF_MON_ENA register defines
 ****************************************************************************************
 */
#define RTC_CX_LPF_MON_ENA_OFFSETADDRESS 0x0000030c  /* RW */
#define RTC_CX_LPF_MON_ENA_BITOFFSET   0
#define RTC_CX_LPF_MON_ENA_BITFIELDSIZE 32
#define RTC_CX_LPF_MON_ENA_BITMASK     0xFFFFFFFF
#define RTC_CX_LPF_MON_ENA_INIT        0x00000000
/*
 *  RTC_CX_LPF_MON_EN bit field defines
 ****************************************************************************************
 */
#define RTC_CX_LPF_MON_EN_OFFSETADDRESS         RTC_CX_LPF_MON_ENA_OFFSETADDRESS
#define RTC_CX_LPF_MON_EN_BITOFFSET             0
#define RTC_CX_LPF_MON_EN_BITFIELDSIZE          1
#define RTC_CX_LPF_MON_EN_BITMASK               0x00000001
#define RTC_CX_LPF_MON_EN_INIT                  0x0

/*
 *  RTC_CX_OSC_OPT_BIT register defines
 ****************************************************************************************
 */
#define RTC_CX_OSC_OPT_BIT_OFFSETADDRESS 0x00000310  /* RW */
#define RTC_CX_OSC_OPT_BIT_BITOFFSET   0
#define RTC_CX_OSC_OPT_BIT_BITFIELDSIZE 32
#define RTC_CX_OSC_OPT_BIT_BITMASK     0xFFFFFFFF
#define RTC_CX_OSC_OPT_BIT_INIT        0x00000000
/*
 *  RTC_CX_OSC_OPT_BIT_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_CX_OSC_OPT_BIT_VAL_OFFSETADDRESS    RTC_CX_OSC_OPT_BIT_OFFSETADDRESS
#define RTC_CX_OSC_OPT_BIT_VAL_BITOFFSET        0
#define RTC_CX_OSC_OPT_BIT_VAL_BITFIELDSIZE     3
#define RTC_CX_OSC_OPT_BIT_VAL_BITMASK          0x00000007
#define RTC_CX_OSC_OPT_BIT_VAL_INIT             0x0

/*
 *  RTC_CX_PLL_OPT_BIT register defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_OPT_BIT_OFFSETADDRESS 0x00000314  /* RW */
#define RTC_CX_PLL_OPT_BIT_BITOFFSET   0
#define RTC_CX_PLL_OPT_BIT_BITFIELDSIZE 32
#define RTC_CX_PLL_OPT_BIT_BITMASK     0xFFFFFFFF
#define RTC_CX_PLL_OPT_BIT_INIT        0x00000000
/*
 *  RTC_CX_PLL_OPT_BIT_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_OPT_BIT_VAL_OFFSETADDRESS    RTC_CX_PLL_OPT_BIT_OFFSETADDRESS
#define RTC_CX_PLL_OPT_BIT_VAL_BITOFFSET        0
#define RTC_CX_PLL_OPT_BIT_VAL_BITFIELDSIZE     3
#define RTC_CX_PLL_OPT_BIT_VAL_BITMASK          0x00000007
#define RTC_CX_PLL_OPT_BIT_VAL_INIT             0x0

/*
 *  RTC_CX_DCOP register defines
 ****************************************************************************************
 */
#define RTC_CX_DCOP_OFFSETADDRESS      0x00000318  /* RW */
#define RTC_CX_DCOP_BITOFFSET          0
#define RTC_CX_DCOP_BITFIELDSIZE       32
#define RTC_CX_DCOP_BITMASK            0xFFFFFFFF
#define RTC_CX_DCOP_INIT               0x00000000
/*
 *  RTC_CX_DCOP_F bit field defines
 ****************************************************************************************
 */
#define RTC_CX_DCOP_F_OFFSETADDRESS             RTC_CX_DCOP_OFFSETADDRESS
#define RTC_CX_DCOP_F_BITOFFSET                 0
#define RTC_CX_DCOP_F_BITFIELDSIZE              1
#define RTC_CX_DCOP_F_BITMASK                   0x00000001
#define RTC_CX_DCOP_F_INIT                      0x0

/*
 *  RTC_CX_EN_GSHIFT register defines
 ****************************************************************************************
 */
#define RTC_CX_EN_GSHIFT_OFFSETADDRESS 0x0000031c  /* RW */
#define RTC_CX_EN_GSHIFT_BITOFFSET     0
#define RTC_CX_EN_GSHIFT_BITFIELDSIZE  32
#define RTC_CX_EN_GSHIFT_BITMASK       0xFFFFFFFF
#define RTC_CX_EN_GSHIFT_INIT          0x00000000
/*
 *  RTC_CX_EN_G_SHIFT bit field defines
 ****************************************************************************************
 */
#define RTC_CX_EN_G_SHIFT_OFFSETADDRESS         RTC_CX_EN_GSHIFT_OFFSETADDRESS
#define RTC_CX_EN_G_SHIFT_BITOFFSET             0
#define RTC_CX_EN_G_SHIFT_BITFIELDSIZE          1
#define RTC_CX_EN_G_SHIFT_BITMASK               0x00000001
#define RTC_CX_EN_G_SHIFT_INIT                  0x0

/*
 *  RTC_CX_GM register defines
 ****************************************************************************************
 */
#define RTC_CX_GM_OFFSETADDRESS        0x00000320  /* RW */
#define RTC_CX_GM_BITOFFSET            0
#define RTC_CX_GM_BITFIELDSIZE         32
#define RTC_CX_GM_BITMASK              0xFFFFFFFF
#define RTC_CX_GM_INIT                 0x00000000
/*
 *  RTC_CX_GM_F bit field defines
 ****************************************************************************************
 */
#define RTC_CX_GM_F_OFFSETADDRESS               RTC_CX_GM_OFFSETADDRESS
#define RTC_CX_GM_F_BITOFFSET                   0
#define RTC_CX_GM_F_BITFIELDSIZE                2
#define RTC_CX_GM_F_BITMASK                     0x00000003
#define RTC_CX_GM_F_INIT                        0x0

/*
 *  RTC_CX_PLL_SEL_DIG1 register defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG1_OFFSETADDRESS 0x00000324  /* RW */
#define RTC_CX_PLL_SEL_DIG1_BITOFFSET  0
#define RTC_CX_PLL_SEL_DIG1_BITFIELDSIZE 32
#define RTC_CX_PLL_SEL_DIG1_BITMASK    0xFFFFFFFF
#define RTC_CX_PLL_SEL_DIG1_INIT       0x00000000
/*
 *  RTC_CX_PLL_SEL_DIG1_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG1_VAL_OFFSETADDRESS   RTC_CX_PLL_SEL_DIG1_OFFSETADDRESS
#define RTC_CX_PLL_SEL_DIG1_VAL_BITOFFSET       0
#define RTC_CX_PLL_SEL_DIG1_VAL_BITFIELDSIZE    4
#define RTC_CX_PLL_SEL_DIG1_VAL_BITMASK         0x0000000f
#define RTC_CX_PLL_SEL_DIG1_VAL_INIT            0x0

/*
 *  RTC_CX_PLL_SEL_DIG2 register defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG2_OFFSETADDRESS 0x00000328  /* RW */
#define RTC_CX_PLL_SEL_DIG2_BITOFFSET  0
#define RTC_CX_PLL_SEL_DIG2_BITFIELDSIZE 32
#define RTC_CX_PLL_SEL_DIG2_BITMASK    0xFFFFFFFF
#define RTC_CX_PLL_SEL_DIG2_INIT       0x00000000
/*
 *  RTC_CX_PLL_SEL_DIG2_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG2_VAL_OFFSETADDRESS   RTC_CX_PLL_SEL_DIG2_OFFSETADDRESS
#define RTC_CX_PLL_SEL_DIG2_VAL_BITOFFSET       0
#define RTC_CX_PLL_SEL_DIG2_VAL_BITFIELDSIZE    4
#define RTC_CX_PLL_SEL_DIG2_VAL_BITMASK         0x0000000f
#define RTC_CX_PLL_SEL_DIG2_VAL_INIT            0x0

/*
 *  RTC_CX_PLL_SEL_DIG3 register defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG3_OFFSETADDRESS 0x0000032c  /* RW */
#define RTC_CX_PLL_SEL_DIG3_BITOFFSET  0
#define RTC_CX_PLL_SEL_DIG3_BITFIELDSIZE 32
#define RTC_CX_PLL_SEL_DIG3_BITMASK    0xFFFFFFFF
#define RTC_CX_PLL_SEL_DIG3_INIT       0x00000000
/*
 *  RTC_CX_PLL_SEL_DIG3_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG3_VAL_OFFSETADDRESS   RTC_CX_PLL_SEL_DIG3_OFFSETADDRESS
#define RTC_CX_PLL_SEL_DIG3_VAL_BITOFFSET       0
#define RTC_CX_PLL_SEL_DIG3_VAL_BITFIELDSIZE    4
#define RTC_CX_PLL_SEL_DIG3_VAL_BITMASK         0x0000000f
#define RTC_CX_PLL_SEL_DIG3_VAL_INIT            0x0

/*
 *  RTC_CX_PLL_SEL_DIG4 register defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG4_OFFSETADDRESS 0x00000330  /* RW */
#define RTC_CX_PLL_SEL_DIG4_BITOFFSET  0
#define RTC_CX_PLL_SEL_DIG4_BITFIELDSIZE 32
#define RTC_CX_PLL_SEL_DIG4_BITMASK    0xFFFFFFFF
#define RTC_CX_PLL_SEL_DIG4_INIT       0x00000000
/*
 *  RTC_CX_PLL_SEL_DIG4_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG4_VAL_OFFSETADDRESS   RTC_CX_PLL_SEL_DIG4_OFFSETADDRESS
#define RTC_CX_PLL_SEL_DIG4_VAL_BITOFFSET       0
#define RTC_CX_PLL_SEL_DIG4_VAL_BITFIELDSIZE    4
#define RTC_CX_PLL_SEL_DIG4_VAL_BITMASK         0x0000000f
#define RTC_CX_PLL_SEL_DIG4_VAL_INIT            0x0

/*
 *  RTC_CX_PLL_SEL_DIG5 register defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG5_OFFSETADDRESS 0x00000334  /* RW */
#define RTC_CX_PLL_SEL_DIG5_BITOFFSET  0
#define RTC_CX_PLL_SEL_DIG5_BITFIELDSIZE 32
#define RTC_CX_PLL_SEL_DIG5_BITMASK    0xFFFFFFFF
#define RTC_CX_PLL_SEL_DIG5_INIT       0x00000000
/*
 *  RTC_CX_PLL_SEL_DIG5_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG5_VAL_OFFSETADDRESS   RTC_CX_PLL_SEL_DIG5_OFFSETADDRESS
#define RTC_CX_PLL_SEL_DIG5_VAL_BITOFFSET       0
#define RTC_CX_PLL_SEL_DIG5_VAL_BITFIELDSIZE    4
#define RTC_CX_PLL_SEL_DIG5_VAL_BITMASK         0x0000000f
#define RTC_CX_PLL_SEL_DIG5_VAL_INIT            0x0

/*
 *  RTC_CX_PLL_SEL_DIG6 register defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG6_OFFSETADDRESS 0x00000338  /* RW */
#define RTC_CX_PLL_SEL_DIG6_BITOFFSET  0
#define RTC_CX_PLL_SEL_DIG6_BITFIELDSIZE 32
#define RTC_CX_PLL_SEL_DIG6_BITMASK    0xFFFFFFFF
#define RTC_CX_PLL_SEL_DIG6_INIT       0x00000000
/*
 *  RTC_CX_PLL_SEL_DIG6_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DIG6_VAL_OFFSETADDRESS   RTC_CX_PLL_SEL_DIG6_OFFSETADDRESS
#define RTC_CX_PLL_SEL_DIG6_VAL_BITOFFSET       0
#define RTC_CX_PLL_SEL_DIG6_VAL_BITFIELDSIZE    4
#define RTC_CX_PLL_SEL_DIG6_VAL_BITMASK         0x0000000f
#define RTC_CX_PLL_SEL_DIG6_VAL_INIT            0x0

/*
 *  RTC_CX_PLL_SEL_ADC register defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_ADC_OFFSETADDRESS 0x0000033c  /* RW */
#define RTC_CX_PLL_SEL_ADC_BITOFFSET   0
#define RTC_CX_PLL_SEL_ADC_BITFIELDSIZE 32
#define RTC_CX_PLL_SEL_ADC_BITMASK     0xFFFFFFFF
#define RTC_CX_PLL_SEL_ADC_INIT        0x00000000
/*
 *  RTC_CX_PLL_SEL_ADC_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_ADC_VAL_OFFSETADDRESS    RTC_CX_PLL_SEL_ADC_OFFSETADDRESS
#define RTC_CX_PLL_SEL_ADC_VAL_BITOFFSET        0
#define RTC_CX_PLL_SEL_ADC_VAL_BITFIELDSIZE     4
#define RTC_CX_PLL_SEL_ADC_VAL_BITMASK          0x0000000f
#define RTC_CX_PLL_SEL_ADC_VAL_INIT             0x0

/*
 *  RTC_CX_PLL_SEL_DAC register defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DAC_OFFSETADDRESS 0x00000340  /* RW */
#define RTC_CX_PLL_SEL_DAC_BITOFFSET   0
#define RTC_CX_PLL_SEL_DAC_BITFIELDSIZE 32
#define RTC_CX_PLL_SEL_DAC_BITMASK     0xFFFFFFFF
#define RTC_CX_PLL_SEL_DAC_INIT        0x00000000
/*
 *  RTC_CX_PLL_SEL_DAC_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_CX_PLL_SEL_DAC_VAL_OFFSETADDRESS    RTC_CX_PLL_SEL_DAC_OFFSETADDRESS
#define RTC_CX_PLL_SEL_DAC_VAL_BITOFFSET        0
#define RTC_CX_PLL_SEL_DAC_VAL_BITFIELDSIZE     4
#define RTC_CX_PLL_SEL_DAC_VAL_BITMASK          0x0000000f
#define RTC_CX_PLL_SEL_DAC_VAL_INIT             0x0

/*
 *  RTC_CX_CLK_SRC_SEL register defines
 ****************************************************************************************
 */
#define RTC_CX_CLK_SRC_SEL_OFFSETADDRESS 0x00000344  /* RW */
#define RTC_CX_CLK_SRC_SEL_BITOFFSET   0
#define RTC_CX_CLK_SRC_SEL_BITFIELDSIZE 32
#define RTC_CX_CLK_SRC_SEL_BITMASK     0xFFFFFFFF
#define RTC_CX_CLK_SRC_SEL_INIT        0x00000000
/*
 *  RTC_CX_CLK_SRC_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_CX_CLK_SRC_SEL_VAL_OFFSETADDRESS    RTC_CX_CLK_SRC_SEL_OFFSETADDRESS
#define RTC_CX_CLK_SRC_SEL_VAL_BITOFFSET        0
#define RTC_CX_CLK_SRC_SEL_VAL_BITFIELDSIZE     2
#define RTC_CX_CLK_SRC_SEL_VAL_BITMASK          0x00000003
#define RTC_CX_CLK_SRC_SEL_VAL_INIT             0x0

/*
 *  RTC_CX_EN_BB register defines
 ****************************************************************************************
 */
#define RTC_CX_EN_BB_OFFSETADDRESS     0x00000348  /* RW */
#define RTC_CX_EN_BB_BITOFFSET         0
#define RTC_CX_EN_BB_BITFIELDSIZE      32
#define RTC_CX_EN_BB_BITMASK           0xFFFFFFFF
#define RTC_CX_EN_BB_INIT              0x00000000
/*
 *  RTC_CX_EN_BB_F bit field defines
 ****************************************************************************************
 */
#define RTC_CX_EN_BB_F_OFFSETADDRESS            RTC_CX_EN_BB_OFFSETADDRESS
#define RTC_CX_EN_BB_F_BITOFFSET                0
#define RTC_CX_EN_BB_F_BITFIELDSIZE             1
#define RTC_CX_EN_BB_F_BITMASK                  0x00000001
#define RTC_CX_EN_BB_F_INIT                     0x0

/*
 *  RTC_CX_EN_RF register defines
 ****************************************************************************************
 */
#define RTC_CX_EN_RF_OFFSETADDRESS     0x0000034c  /* RW */
#define RTC_CX_EN_RF_BITOFFSET         0
#define RTC_CX_EN_RF_BITFIELDSIZE      32
#define RTC_CX_EN_RF_BITMASK           0xFFFFFFFF
#define RTC_CX_EN_RF_INIT              0x00000000
/*
 *  RTC_CX_EN_RF_F bit field defines
 ****************************************************************************************
 */
#define RTC_CX_EN_RF_F_OFFSETADDRESS            RTC_CX_EN_RF_OFFSETADDRESS
#define RTC_CX_EN_RF_F_BITOFFSET                0
#define RTC_CX_EN_RF_F_BITFIELDSIZE             1
#define RTC_CX_EN_RF_F_BITMASK                  0x00000001
#define RTC_CX_EN_RF_F_INIT                     0x0

/*
 *  RTC_CX_BYPASS register defines
 ****************************************************************************************
 */
#define RTC_CX_BYPASS_OFFSETADDRESS    0x00000350  /* RW */
#define RTC_CX_BYPASS_BITOFFSET        0
#define RTC_CX_BYPASS_BITFIELDSIZE     32
#define RTC_CX_BYPASS_BITMASK          0xFFFFFFFF
#define RTC_CX_BYPASS_INIT             0x00000000
/*
 *  RTC_CX_BYPASS_F bit field defines
 ****************************************************************************************
 */
#define RTC_CX_BYPASS_F_OFFSETADDRESS           RTC_CX_BYPASS_OFFSETADDRESS
#define RTC_CX_BYPASS_F_BITOFFSET               0
#define RTC_CX_BYPASS_F_BITFIELDSIZE            1
#define RTC_CX_BYPASS_F_BITMASK                 0x00000001
#define RTC_CX_BYPASS_F_INIT                    0x0

/*
 *  RTC_EN_PWR register defines
 ****************************************************************************************
 */
#define RTC_EN_PWR_OFFSETADDRESS       0x00000354  /* RW */
#define RTC_EN_PWR_BITOFFSET           0
#define RTC_EN_PWR_BITFIELDSIZE        32
#define RTC_EN_PWR_BITMASK             0xFFFFFFFF
#define RTC_EN_PWR_INIT                0x00000000
/*
 *  RTC_EN_PWR_RTC_SARM bit field defines
 ****************************************************************************************
 */
#define RTC_EN_PWR_RTC_SARM_OFFSETADDRESS       RTC_EN_PWR_OFFSETADDRESS
#define RTC_EN_PWR_RTC_SARM_BITOFFSET           0
#define RTC_EN_PWR_RTC_SARM_BITFIELDSIZE        4
#define RTC_EN_PWR_RTC_SARM_BITMASK             0x0000000f
#define RTC_EN_PWR_RTC_SARM_INIT                0x0
/*
 *  RTC_EN_PWR_WLAN_SRAM bit field defines
 ****************************************************************************************
 */
#define RTC_EN_PWR_WLAN_SRAM_OFFSETADDRESS      RTC_EN_PWR_OFFSETADDRESS
#define RTC_EN_PWR_WLAN_SRAM_BITOFFSET          6
#define RTC_EN_PWR_WLAN_SRAM_BITFIELDSIZE       1
#define RTC_EN_PWR_WLAN_SRAM_BITMASK            0x00000040
#define RTC_EN_PWR_WLAN_SRAM_INIT               0x0
/*
 *  RTC_EN_PWR_APP_SRAM bit field defines
 ****************************************************************************************
 */
#define RTC_EN_PWR_APP_SRAM_OFFSETADDRESS       RTC_EN_PWR_OFFSETADDRESS
#define RTC_EN_PWR_APP_SRAM_BITOFFSET           4
#define RTC_EN_PWR_APP_SRAM_BITFIELDSIZE        1
#define RTC_EN_PWR_APP_SRAM_BITMASK             0x00000010
#define RTC_EN_PWR_APP_SRAM_INIT                0x0
/*
 *  RTC_EN_PWR_SHARE_MEM bit field defines
 ****************************************************************************************
 */
#define RTC_EN_PWR_SHARE_MEM_OFFSETADDRESS      RTC_EN_PWR_OFFSETADDRESS
#define RTC_EN_PWR_SHARE_MEM_BITOFFSET          5
#define RTC_EN_PWR_SHARE_MEM_BITFIELDSIZE       1
#define RTC_EN_PWR_SHARE_MEM_BITMASK            0x00000020
#define RTC_EN_PWR_SHARE_MEM_INIT               0x0
/*
 *  RTC_EN_PWR_WLAN_CORE bit field defines
 ****************************************************************************************
 */
#define RTC_EN_PWR_WLAN_CORE_OFFSETADDRESS      RTC_EN_PWR_OFFSETADDRESS
#define RTC_EN_PWR_WLAN_CORE_BITOFFSET          7
#define RTC_EN_PWR_WLAN_CORE_BITFIELDSIZE       1
#define RTC_EN_PWR_WLAN_CORE_BITMASK            0x00000080
#define RTC_EN_PWR_WLAN_CORE_INIT               0x0
/*
 *  RTC_EN_PWR_CRYPTO bit field defines
 ****************************************************************************************
 */
#define RTC_EN_PWR_CRYPTO_OFFSETADDRESS         RTC_EN_PWR_OFFSETADDRESS
#define RTC_EN_PWR_CRYPTO_BITOFFSET             8
#define RTC_EN_PWR_CRYPTO_BITFIELDSIZE          1
#define RTC_EN_PWR_CRYPTO_BITMASK               0x00000100
#define RTC_EN_PWR_CRYPTO_INIT                  0x0

/*
 *  RTC_ISO_CTL register defines
 ****************************************************************************************
 */
#define RTC_ISO_CTL_OFFSETADDRESS      0x00000358  /* RW */
#define RTC_ISO_CTL_BITOFFSET          0
#define RTC_ISO_CTL_BITFIELDSIZE       32
#define RTC_ISO_CTL_BITMASK            0xFFFFFFFF
#define RTC_ISO_CTL_INIT               0x00000000
/*
 *  RTC_ISO_CTL_RTC_SARM bit field defines
 ****************************************************************************************
 */
#define RTC_ISO_CTL_RTC_SARM_OFFSETADDRESS      RTC_ISO_CTL_OFFSETADDRESS
#define RTC_ISO_CTL_RTC_SARM_BITOFFSET          0
#define RTC_ISO_CTL_RTC_SARM_BITFIELDSIZE       4
#define RTC_ISO_CTL_RTC_SARM_BITMASK            0x0000000f
#define RTC_ISO_CTL_RTC_SARM_INIT               0x0
/*
 *  RTC_ISO_CTL_WLAN_SRAM bit field defines
 ****************************************************************************************
 */
#define RTC_ISO_CTL_WLAN_SRAM_OFFSETADDRESS     RTC_ISO_CTL_OFFSETADDRESS
#define RTC_ISO_CTL_WLAN_SRAM_BITOFFSET         6
#define RTC_ISO_CTL_WLAN_SRAM_BITFIELDSIZE      1
#define RTC_ISO_CTL_WLAN_SRAM_BITMASK           0x00000040
#define RTC_ISO_CTL_WLAN_SRAM_INIT              0x0
/*
 *  RTC_ISO_CTL_APP_SRAM bit field defines
 ****************************************************************************************
 */
#define RTC_ISO_CTL_APP_SRAM_OFFSETADDRESS      RTC_ISO_CTL_OFFSETADDRESS
#define RTC_ISO_CTL_APP_SRAM_BITOFFSET          4
#define RTC_ISO_CTL_APP_SRAM_BITFIELDSIZE       1
#define RTC_ISO_CTL_APP_SRAM_BITMASK            0x00000010
#define RTC_ISO_CTL_APP_SRAM_INIT               0x0
/*
 *  RTC_ISO_CTL_SHARE_MEM bit field defines
 ****************************************************************************************
 */
#define RTC_ISO_CTL_SHARE_MEM_OFFSETADDRESS     RTC_ISO_CTL_OFFSETADDRESS
#define RTC_ISO_CTL_SHARE_MEM_BITOFFSET         5
#define RTC_ISO_CTL_SHARE_MEM_BITFIELDSIZE      1
#define RTC_ISO_CTL_SHARE_MEM_BITMASK           0x00000020
#define RTC_ISO_CTL_SHARE_MEM_INIT              0x0
/*
 *  RTC_ISO_CTL_WLAN_CORE bit field defines
 ****************************************************************************************
 */
#define RTC_ISO_CTL_WLAN_CORE_OFFSETADDRESS     RTC_ISO_CTL_OFFSETADDRESS
#define RTC_ISO_CTL_WLAN_CORE_BITOFFSET         7
#define RTC_ISO_CTL_WLAN_CORE_BITFIELDSIZE      1
#define RTC_ISO_CTL_WLAN_CORE_BITMASK           0x00000080
#define RTC_ISO_CTL_WLAN_CORE_INIT              0x0
/*
 *  RTC_ISO_CTL_CRYPTO bit field defines
 ****************************************************************************************
 */
#define RTC_ISO_CTL_CRYPTO_OFFSETADDRESS        RTC_ISO_CTL_OFFSETADDRESS
#define RTC_ISO_CTL_CRYPTO_BITOFFSET            8
#define RTC_ISO_CTL_CRYPTO_BITFIELDSIZE         1
#define RTC_ISO_CTL_CRYPTO_BITMASK              0x00000100
#define RTC_ISO_CTL_CRYPTO_INIT                 0x0

/*
 *  RTC_SX_EN_BIAS register defines
 ****************************************************************************************
 */
#define RTC_SX_EN_BIAS_OFFSETADDRESS   0x0000035c  /* RW */
#define RTC_SX_EN_BIAS_BITOFFSET       0
#define RTC_SX_EN_BIAS_BITFIELDSIZE    32
#define RTC_SX_EN_BIAS_BITMASK         0xFFFFFFFF
#define RTC_SX_EN_BIAS_INIT            0x00000000
/*
 *  RTC_SX_EN_BIAS_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_EN_BIAS_F_OFFSETADDRESS          RTC_SX_EN_BIAS_OFFSETADDRESS
#define RTC_SX_EN_BIAS_F_BITOFFSET              0
#define RTC_SX_EN_BIAS_F_BITFIELDSIZE           1
#define RTC_SX_EN_BIAS_F_BITMASK                0x00000001
#define RTC_SX_EN_BIAS_F_INIT                   0x0

/*
 *  RTC_SX_EN_U_LDO register defines
 ****************************************************************************************
 */
#define RTC_SX_EN_U_LDO_OFFSETADDRESS  0x00000360  /* RW */
#define RTC_SX_EN_U_LDO_BITOFFSET      0
#define RTC_SX_EN_U_LDO_BITFIELDSIZE   32
#define RTC_SX_EN_U_LDO_BITMASK        0xFFFFFFFF
#define RTC_SX_EN_U_LDO_INIT           0x00000000
/*
 *  RTC_SX_EN_U_LDO_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_EN_U_LDO_F_OFFSETADDRESS         RTC_SX_EN_U_LDO_OFFSETADDRESS
#define RTC_SX_EN_U_LDO_F_BITOFFSET             0
#define RTC_SX_EN_U_LDO_F_BITFIELDSIZE          1
#define RTC_SX_EN_U_LDO_F_BITMASK               0x00000001
#define RTC_SX_EN_U_LDO_F_INIT                  0x0

/*
 *  RTC_SX_SWT2LDO register defines
 ****************************************************************************************
 */
#define RTC_SX_SWT2LDO_OFFSETADDRESS   0x00000364  /* RW */
#define RTC_SX_SWT2LDO_BITOFFSET       0
#define RTC_SX_SWT2LDO_BITFIELDSIZE    32
#define RTC_SX_SWT2LDO_BITMASK         0xFFFFFFFF
#define RTC_SX_SWT2LDO_INIT            0x00000000
/*
 *  RTC_SX_SWT2LDO_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_SWT2LDO_F_OFFSETADDRESS          RTC_SX_SWT2LDO_OFFSETADDRESS
#define RTC_SX_SWT2LDO_F_BITOFFSET              0
#define RTC_SX_SWT2LDO_F_BITFIELDSIZE           1
#define RTC_SX_SWT2LDO_F_BITMASK                0x00000001
#define RTC_SX_SWT2LDO_F_INIT                   0x0

/*
 *  RTC_SX_TS_GAIN register defines
 ****************************************************************************************
 */
#define RTC_SX_TS_GAIN_OFFSETADDRESS   0x00000368  /* RW */
#define RTC_SX_TS_GAIN_BITOFFSET       0
#define RTC_SX_TS_GAIN_BITFIELDSIZE    32
#define RTC_SX_TS_GAIN_BITMASK         0xFFFFFFFF
#define RTC_SX_TS_GAIN_INIT            0x00000000
/*
 *  RTC_SX_TS_GAIN_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_TS_GAIN_F_OFFSETADDRESS          RTC_SX_TS_GAIN_OFFSETADDRESS
#define RTC_SX_TS_GAIN_F_BITOFFSET              0
#define RTC_SX_TS_GAIN_F_BITFIELDSIZE           1
#define RTC_SX_TS_GAIN_F_BITMASK                0x00000001
#define RTC_SX_TS_GAIN_F_INIT                   0x0

/*
 *  RTC_SX_EN_BO register defines
 ****************************************************************************************
 */
#define RTC_SX_EN_BO_OFFSETADDRESS     0x0000036c  /* RW */
#define RTC_SX_EN_BO_BITOFFSET         0
#define RTC_SX_EN_BO_BITFIELDSIZE      32
#define RTC_SX_EN_BO_BITMASK           0xFFFFFFFF
#define RTC_SX_EN_BO_INIT              0x00000000
/*
 *  RTC_SX_SX_EN_BO bit field defines
 ****************************************************************************************
 */
#define RTC_SX_SX_EN_BO_OFFSETADDRESS           RTC_SX_EN_BO_OFFSETADDRESS
#define RTC_SX_SX_EN_BO_BITOFFSET               0
#define RTC_SX_SX_EN_BO_BITFIELDSIZE            1
#define RTC_SX_SX_EN_BO_BITMASK                 0x00000001
#define RTC_SX_SX_EN_BO_INIT                    0x0

/*
 *  RTC_SX_EN_BO_FLASH register defines
 ****************************************************************************************
 */
#define RTC_SX_EN_BO_FLASH_OFFSETADDRESS 0x00000370  /* RW */
#define RTC_SX_EN_BO_FLASH_BITOFFSET   0
#define RTC_SX_EN_BO_FLASH_BITFIELDSIZE 32
#define RTC_SX_EN_BO_FLASH_BITMASK     0xFFFFFFFF
#define RTC_SX_EN_BO_FLASH_INIT        0x00000000
/*
 *  RTC_SX_SX_EN_BO_FLASH bit field defines
 ****************************************************************************************
 */
#define RTC_SX_SX_EN_BO_FLASH_OFFSETADDRESS     RTC_SX_EN_BO_FLASH_OFFSETADDRESS
#define RTC_SX_SX_EN_BO_FLASH_BITOFFSET         0
#define RTC_SX_SX_EN_BO_FLASH_BITFIELDSIZE      1
#define RTC_SX_SX_EN_BO_FLASH_BITMASK           0x00000001
#define RTC_SX_SX_EN_BO_FLASH_INIT              0x0

/*
 *  RTC_SX_EN_BO_SAR register defines
 ****************************************************************************************
 */
#define RTC_SX_EN_BO_SAR_OFFSETADDRESS 0x00000374  /* RW */
#define RTC_SX_EN_BO_SAR_BITOFFSET     0
#define RTC_SX_EN_BO_SAR_BITFIELDSIZE  32
#define RTC_SX_EN_BO_SAR_BITMASK       0xFFFFFFFF
#define RTC_SX_EN_BO_SAR_INIT          0x00000000
/*
 *  RTC_SX_SX_EN_BO_SAR bit field defines
 ****************************************************************************************
 */
#define RTC_SX_SX_EN_BO_SAR_OFFSETADDRESS       RTC_SX_EN_BO_SAR_OFFSETADDRESS
#define RTC_SX_SX_EN_BO_SAR_BITOFFSET           0
#define RTC_SX_SX_EN_BO_SAR_BITFIELDSIZE        1
#define RTC_SX_SX_EN_BO_SAR_BITMASK             0x00000001
#define RTC_SX_SX_EN_BO_SAR_INIT                0x0

/*
 *  RTC_SX_OFF_SEN_FLASH register defines
 ****************************************************************************************
 */
#define RTC_SX_OFF_SEN_FLASH_OFFSETADDRESS 0x00000378  /* RW */
#define RTC_SX_OFF_SEN_FLASH_BITOFFSET 0
#define RTC_SX_OFF_SEN_FLASH_BITFIELDSIZE 32
#define RTC_SX_OFF_SEN_FLASH_BITMASK   0xFFFFFFFF
#define RTC_SX_OFF_SEN_FLASH_INIT      0x00000000
/*
 *  RTC_SX_OFF_SEN_FLASH_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_OFF_SEN_FLASH_F_OFFSETADDRESS    RTC_SX_OFF_SEN_FLASH_OFFSETADDRESS
#define RTC_SX_OFF_SEN_FLASH_F_BITOFFSET        0
#define RTC_SX_OFF_SEN_FLASH_F_BITFIELDSIZE     1
#define RTC_SX_OFF_SEN_FLASH_F_BITMASK          0x00000001
#define RTC_SX_OFF_SEN_FLASH_F_INIT             0x0

/*
 *  RTC_SX_OFF_SEN_SAR register defines
 ****************************************************************************************
 */
#define RTC_SX_OFF_SEN_SAR_OFFSETADDRESS 0x0000037c  /* RW */
#define RTC_SX_OFF_SEN_SAR_BITOFFSET   0
#define RTC_SX_OFF_SEN_SAR_BITFIELDSIZE 32
#define RTC_SX_OFF_SEN_SAR_BITMASK     0xFFFFFFFF
#define RTC_SX_OFF_SEN_SAR_INIT        0x00000000
/*
 *  RTC_SX_OFF_SEN_SAR_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_OFF_SEN_SAR_F_OFFSETADDRESS      RTC_SX_OFF_SEN_SAR_OFFSETADDRESS
#define RTC_SX_OFF_SEN_SAR_F_BITOFFSET          0
#define RTC_SX_OFF_SEN_SAR_F_BITFIELDSIZE       1
#define RTC_SX_OFF_SEN_SAR_F_BITMASK            0x00000001
#define RTC_SX_OFF_SEN_SAR_F_INIT               0x0

/*
 *  RTC_SX_BO_TH_CTRL register defines
 ****************************************************************************************
 */
#define RTC_SX_BO_TH_CTRL_OFFSETADDRESS 0x00000380  /* RW */
#define RTC_SX_BO_TH_CTRL_BITOFFSET    0
#define RTC_SX_BO_TH_CTRL_BITFIELDSIZE 32
#define RTC_SX_BO_TH_CTRL_BITMASK      0xFFFFFFFF
#define RTC_SX_BO_TH_CTRL_INIT         0x00000000
/*
 *  RTC_SX_BO_TH_CTRL_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_BO_TH_CTRL_F_OFFSETADDRESS       RTC_SX_BO_TH_CTRL_OFFSETADDRESS
#define RTC_SX_BO_TH_CTRL_F_BITOFFSET           0
#define RTC_SX_BO_TH_CTRL_F_BITFIELDSIZE        2
#define RTC_SX_BO_TH_CTRL_F_BITMASK             0x00000003
#define RTC_SX_BO_TH_CTRL_F_INIT                0x0

/*
 *  RTC_SX_BO_DS register defines
 ****************************************************************************************
 */
#define RTC_SX_BO_DS_OFFSETADDRESS     0x00000384  /* RW */
#define RTC_SX_BO_DS_BITOFFSET         0
#define RTC_SX_BO_DS_BITFIELDSIZE      32
#define RTC_SX_BO_DS_BITMASK           0xFFFFFFFF
#define RTC_SX_BO_DS_INIT              0x00000000
/*
 *  RTC_SX_BO_DS_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_BO_DS_F_OFFSETADDRESS            RTC_SX_BO_DS_OFFSETADDRESS
#define RTC_SX_BO_DS_F_BITOFFSET                0
#define RTC_SX_BO_DS_F_BITFIELDSIZE             1
#define RTC_SX_BO_DS_F_BITMASK                  0x00000001
#define RTC_SX_BO_DS_F_INIT                     0x0

/*
 *  RTC_SX_CX_1_CTRL register defines
 ****************************************************************************************
 */
#define RTC_SX_CX_1_CTRL_OFFSETADDRESS 0x00000388  /* RW */
#define RTC_SX_CX_1_CTRL_BITOFFSET     0
#define RTC_SX_CX_1_CTRL_BITFIELDSIZE  32
#define RTC_SX_CX_1_CTRL_BITMASK       0xFFFFFFFF
#define RTC_SX_CX_1_CTRL_INIT          0x00000000
/*
 *  RTC_SX_CX_1_CTRL_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_CX_1_CTRL_F_OFFSETADDRESS        RTC_SX_CX_1_CTRL_OFFSETADDRESS
#define RTC_SX_CX_1_CTRL_F_BITOFFSET            0
#define RTC_SX_CX_1_CTRL_F_BITFIELDSIZE         8
#define RTC_SX_CX_1_CTRL_F_BITMASK              0x000000ff
#define RTC_SX_CX_1_CTRL_F_INIT                 0x0

/*
 *  RTC_SX_CX_2_CTRL register defines
 ****************************************************************************************
 */
#define RTC_SX_CX_2_CTRL_OFFSETADDRESS 0x0000038c  /* RW */
#define RTC_SX_CX_2_CTRL_BITOFFSET     0
#define RTC_SX_CX_2_CTRL_BITFIELDSIZE  32
#define RTC_SX_CX_2_CTRL_BITMASK       0xFFFFFFFF
#define RTC_SX_CX_2_CTRL_INIT          0x00000000
/*
 *  RTC_SX_CX_2_CTRL_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_CX_2_CTRL_F_OFFSETADDRESS        RTC_SX_CX_2_CTRL_OFFSETADDRESS
#define RTC_SX_CX_2_CTRL_F_BITOFFSET            0
#define RTC_SX_CX_2_CTRL_F_BITFIELDSIZE         8
#define RTC_SX_CX_2_CTRL_F_BITMASK              0x000000ff
#define RTC_SX_CX_2_CTRL_F_INIT                 0x0

/*
 *  RTC_SX_CL_CTRL register defines
 ****************************************************************************************
 */
#define RTC_SX_CL_CTRL_OFFSETADDRESS   0x00000390  /* RW */
#define RTC_SX_CL_CTRL_BITOFFSET       0
#define RTC_SX_CL_CTRL_BITFIELDSIZE    32
#define RTC_SX_CL_CTRL_BITMASK         0xFFFFFFFF
#define RTC_SX_CL_CTRL_INIT            0x00000000
/*
 *  RTC_SX_CL_CTRL_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_CL_CTRL_F_OFFSETADDRESS          RTC_SX_CL_CTRL_OFFSETADDRESS
#define RTC_SX_CL_CTRL_F_BITOFFSET              0
#define RTC_SX_CL_CTRL_F_BITFIELDSIZE           8
#define RTC_SX_CL_CTRL_F_BITMASK                0x000000ff
#define RTC_SX_CL_CTRL_F_INIT                   0x0

/*
 *  RTC_SX_RL_CTRL register defines
 ****************************************************************************************
 */
#define RTC_SX_RL_CTRL_OFFSETADDRESS   0x00000394  /* RW */
#define RTC_SX_RL_CTRL_BITOFFSET       0
#define RTC_SX_RL_CTRL_BITFIELDSIZE    32
#define RTC_SX_RL_CTRL_BITMASK         0xFFFFFFFF
#define RTC_SX_RL_CTRL_INIT            0x00000000
/*
 *  RTC_SX_RL_CTRL_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_RL_CTRL_F_OFFSETADDRESS          RTC_SX_RL_CTRL_OFFSETADDRESS
#define RTC_SX_RL_CTRL_F_BITOFFSET              0
#define RTC_SX_RL_CTRL_F_BITFIELDSIZE           8
#define RTC_SX_RL_CTRL_F_BITMASK                0x000000ff
#define RTC_SX_RL_CTRL_F_INIT                   0x0

/*
 *  RTC_SX_GM_CTRL register defines
 ****************************************************************************************
 */
#define RTC_SX_GM_CTRL_OFFSETADDRESS   0x00000398  /* RW */
#define RTC_SX_GM_CTRL_BITOFFSET       0
#define RTC_SX_GM_CTRL_BITFIELDSIZE    32
#define RTC_SX_GM_CTRL_BITMASK         0xFFFFFFFF
#define RTC_SX_GM_CTRL_INIT            0x00000000
/*
 *  RTC_SX_GM_CTRL_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_GM_CTRL_F_OFFSETADDRESS          RTC_SX_GM_CTRL_OFFSETADDRESS
#define RTC_SX_GM_CTRL_F_BITOFFSET              0
#define RTC_SX_GM_CTRL_F_BITFIELDSIZE           2
#define RTC_SX_GM_CTRL_F_BITMASK                0x00000003
#define RTC_SX_GM_CTRL_F_INIT                   0x0

/*
 *  RTC_SX_EN_TS register defines
 ****************************************************************************************
 */
#define RTC_SX_EN_TS_OFFSETADDRESS     0x0000039c  /* RW */
#define RTC_SX_EN_TS_BITOFFSET         0
#define RTC_SX_EN_TS_BITFIELDSIZE      32
#define RTC_SX_EN_TS_BITMASK           0xFFFFFFFF
#define RTC_SX_EN_TS_INIT              0x00000000
/*
 *  RTC_SX_EN_TS_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_EN_TS_F_OFFSETADDRESS            RTC_SX_EN_TS_OFFSETADDRESS
#define RTC_SX_EN_TS_F_BITOFFSET                0
#define RTC_SX_EN_TS_F_BITFIELDSIZE             1
#define RTC_SX_EN_TS_F_BITMASK                  0x00000001
#define RTC_SX_EN_TS_F_INIT                     0x0

/*
 *  RTC_SX_OFF_SNS register defines
 ****************************************************************************************
 */
#define RTC_SX_OFF_SNS_OFFSETADDRESS   0x000003a0  /* RW */
#define RTC_SX_OFF_SNS_BITOFFSET       0
#define RTC_SX_OFF_SNS_BITFIELDSIZE    32
#define RTC_SX_OFF_SNS_BITMASK         0xFFFFFFFF
#define RTC_SX_OFF_SNS_INIT            0x00000000
/*
 *  RTC_SX_OFFSET_SNS bit field defines
 ****************************************************************************************
 */
#define RTC_SX_OFFSET_SNS_OFFSETADDRESS         RTC_SX_OFF_SNS_OFFSETADDRESS
#define RTC_SX_OFFSET_SNS_BITOFFSET             0
#define RTC_SX_OFFSET_SNS_BITFIELDSIZE          1
#define RTC_SX_OFFSET_SNS_BITMASK               0x00000001
#define RTC_SX_OFFSET_SNS_INIT                  0x0

/*
 *  RTC_SX_TEST register defines
 ****************************************************************************************
 */
#define RTC_SX_TEST_OFFSETADDRESS      0x000003a4  /* RW */
#define RTC_SX_TEST_BITOFFSET          0
#define RTC_SX_TEST_BITFIELDSIZE       32
#define RTC_SX_TEST_BITMASK            0xFFFFFFFF
#define RTC_SX_TEST_INIT               0x00000000
/*
 *  RTC_SX_TEST_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_SX_TEST_VAL_OFFSETADDRESS           RTC_SX_TEST_OFFSETADDRESS
#define RTC_SX_TEST_VAL_BITOFFSET               0
#define RTC_SX_TEST_VAL_BITFIELDSIZE            4
#define RTC_SX_TEST_VAL_BITMASK                 0x0000000f
#define RTC_SX_TEST_VAL_INIT                    0x0

/*
 *  RTC_SX_TSADJ register defines
 ****************************************************************************************
 */
#define RTC_SX_TSADJ_OFFSETADDRESS     0x000003a8  /* RW */
#define RTC_SX_TSADJ_BITOFFSET         0
#define RTC_SX_TSADJ_BITFIELDSIZE      32
#define RTC_SX_TSADJ_BITMASK           0xFFFFFFFF
#define RTC_SX_TSADJ_INIT              0x00000000
/*
 *  RTC_SX_TSADJ_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_SX_TSADJ_VAL_OFFSETADDRESS          RTC_SX_TSADJ_OFFSETADDRESS
#define RTC_SX_TSADJ_VAL_BITOFFSET              0
#define RTC_SX_TSADJ_VAL_BITFIELDSIZE           8
#define RTC_SX_TSADJ_VAL_BITMASK                0x000000ff
#define RTC_SX_TSADJ_VAL_INIT                   0x0

/*
 *  RTC_SX_DC_OP register defines
 ****************************************************************************************
 */
#define RTC_SX_DC_OP_OFFSETADDRESS     0x000003ac  /* RW */
#define RTC_SX_DC_OP_BITOFFSET         0
#define RTC_SX_DC_OP_BITFIELDSIZE      32
#define RTC_SX_DC_OP_BITMASK           0xFFFFFFFF
#define RTC_SX_DC_OP_INIT              0x00000000
/*
 *  RTC_SX_DC_OP_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_DC_OP_F_OFFSETADDRESS            RTC_SX_DC_OP_OFFSETADDRESS
#define RTC_SX_DC_OP_F_BITOFFSET                0
#define RTC_SX_DC_OP_F_BITFIELDSIZE             1
#define RTC_SX_DC_OP_F_BITMASK                  0x00000001
#define RTC_SX_DC_OP_F_INIT                     0x0

/*
 *  RTC_SX_LOAD register defines
 ****************************************************************************************
 */
#define RTC_SX_LOAD_OFFSETADDRESS      0x000003b0  /* RW */
#define RTC_SX_LOAD_BITOFFSET          0
#define RTC_SX_LOAD_BITFIELDSIZE       32
#define RTC_SX_LOAD_BITMASK            0xFFFFFFFF
#define RTC_SX_LOAD_INIT               0x00000000
/*
 *  RTC_SX_LOAD_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_LOAD_F_OFFSETADDRESS             RTC_SX_LOAD_OFFSETADDRESS
#define RTC_SX_LOAD_F_BITOFFSET                 0
#define RTC_SX_LOAD_F_BITFIELDSIZE              1
#define RTC_SX_LOAD_F_BITMASK                   0x00000001
#define RTC_SX_LOAD_F_INIT                      0x0

/*
 *  RTC_SX_DS register defines
 ****************************************************************************************
 */
#define RTC_SX_DS_OFFSETADDRESS        0x000003b4  /* RW */
#define RTC_SX_DS_BITOFFSET            0
#define RTC_SX_DS_BITFIELDSIZE         32
#define RTC_SX_DS_BITMASK              0xFFFFFFFF
#define RTC_SX_DS_INIT                 0x00000000
/*
 *  RTC_SX_DS_VAL bit field defines
 ****************************************************************************************
 */
#define RTC_SX_DS_VAL_OFFSETADDRESS             RTC_SX_DS_OFFSETADDRESS
#define RTC_SX_DS_VAL_BITOFFSET                 0
#define RTC_SX_DS_VAL_BITFIELDSIZE              6
#define RTC_SX_DS_VAL_BITMASK                   0x0000003f
#define RTC_SX_DS_VAL_INIT                      0x0

/*
 *  RTC_SX_PDEN register defines
 ****************************************************************************************
 */
#define RTC_SX_PDEN_OFFSETADDRESS      0x000003b8  /* RW */
#define RTC_SX_PDEN_BITOFFSET          0
#define RTC_SX_PDEN_BITFIELDSIZE       32
#define RTC_SX_PDEN_BITMASK            0xFFFFFFFF
#define RTC_SX_PDEN_INIT               0x00000000
/*
 *  RTC_SX_PDEN_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_PDEN_F_OFFSETADDRESS             RTC_SX_PDEN_OFFSETADDRESS
#define RTC_SX_PDEN_F_BITOFFSET                 0
#define RTC_SX_PDEN_F_BITFIELDSIZE              6
#define RTC_SX_PDEN_F_BITMASK                   0x0000003f
#define RTC_SX_PDEN_F_INIT                      0x0

/*
 *  RTC_SX_PUEN register defines
 ****************************************************************************************
 */
#define RTC_SX_PUEN_OFFSETADDRESS      0x000003bc  /* RW */
#define RTC_SX_PUEN_BITOFFSET          0
#define RTC_SX_PUEN_BITFIELDSIZE       32
#define RTC_SX_PUEN_BITMASK            0xFFFFFFFF
#define RTC_SX_PUEN_INIT               0x00000000
/*
 *  RTC_SX_PUEN_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_PUEN_F_OFFSETADDRESS             RTC_SX_PUEN_OFFSETADDRESS
#define RTC_SX_PUEN_F_BITOFFSET                 0
#define RTC_SX_PUEN_F_BITFIELDSIZE              6
#define RTC_SX_PUEN_F_BITMASK                   0x0000003f
#define RTC_SX_PUEN_F_INIT                      0x0

/*
 *  RTC_SX_REGDS register defines
 ****************************************************************************************
 */
#define RTC_SX_REGDS_OFFSETADDRESS     0x000003c0  /* RW */
#define RTC_SX_REGDS_BITOFFSET         0
#define RTC_SX_REGDS_BITFIELDSIZE      32
#define RTC_SX_REGDS_BITMASK           0xFFFFFFFF
#define RTC_SX_REGDS_INIT              0x00000000
/*
 *  RTC_SX_REGDS_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_REGDS_F_OFFSETADDRESS            RTC_SX_REGDS_OFFSETADDRESS
#define RTC_SX_REGDS_F_BITOFFSET                0
#define RTC_SX_REGDS_F_BITFIELDSIZE             2
#define RTC_SX_REGDS_F_BITMASK                  0x00000003
#define RTC_SX_REGDS_F_INIT                     0x0

/*
 *  RTC_SX_REGPDEN register defines
 ****************************************************************************************
 */
#define RTC_SX_REGPDEN_OFFSETADDRESS   0x000003c4  /* RW */
#define RTC_SX_REGPDEN_BITOFFSET       0
#define RTC_SX_REGPDEN_BITFIELDSIZE    32
#define RTC_SX_REGPDEN_BITMASK         0xFFFFFFFF
#define RTC_SX_REGPDEN_INIT            0x00000000
/*
 *  RTC_SX_REGPDEN_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_REGPDEN_F_OFFSETADDRESS          RTC_SX_REGPDEN_OFFSETADDRESS
#define RTC_SX_REGPDEN_F_BITOFFSET              0
#define RTC_SX_REGPDEN_F_BITFIELDSIZE           2
#define RTC_SX_REGPDEN_F_BITMASK                0x00000003
#define RTC_SX_REGPDEN_F_INIT                   0x0

/*
 *  RTC_SX_REGPUEN register defines
 ****************************************************************************************
 */
#define RTC_SX_REGPUEN_OFFSETADDRESS   0x000003c8  /* RW */
#define RTC_SX_REGPUEN_BITOFFSET       0
#define RTC_SX_REGPUEN_BITFIELDSIZE    32
#define RTC_SX_REGPUEN_BITMASK         0xFFFFFFFF
#define RTC_SX_REGPUEN_INIT            0x00000000
/*
 *  RTC_SX_REGPUEN_F bit field defines
 ****************************************************************************************
 */
#define RTC_SX_REGPUEN_F_OFFSETADDRESS          RTC_SX_REGPUEN_OFFSETADDRESS
#define RTC_SX_REGPUEN_F_BITOFFSET              0
#define RTC_SX_REGPUEN_F_BITFIELDSIZE           2
#define RTC_SX_REGPUEN_F_BITMASK                0x00000003
#define RTC_SX_REGPUEN_F_INIT                   0x0

/*
 *  RTC_REG_RF_IO_CNTRL register defines
 ****************************************************************************************
 */
#define RTC_REG_RF_IO_CNTRL_OFFSETADDRESS 0x000003cc  /* RW */
#define RTC_REG_RF_IO_CNTRL_BITOFFSET  0
#define RTC_REG_RF_IO_CNTRL_BITFIELDSIZE 32
#define RTC_REG_RF_IO_CNTRL_BITMASK    0xFFFFFFFF
#define RTC_REG_RF_IO_CNTRL_INIT       0x00000000
/*
 *  RTC_RF_IO_RTC_READY bit field defines
 ****************************************************************************************
 */
#define RTC_RF_IO_RTC_READY_OFFSETADDRESS       RTC_REG_RF_IO_CNTRL_OFFSETADDRESS
#define RTC_RF_IO_RTC_READY_BITOFFSET           0
#define RTC_RF_IO_RTC_READY_BITFIELDSIZE        1
#define RTC_RF_IO_RTC_READY_BITMASK             0x00000001
#define RTC_RF_IO_RTC_READY_INIT                0x0
/*
 *  RTC_RF_IO_RTC_IO_I bit field defines
 ****************************************************************************************
 */
#define RTC_RF_IO_RTC_IO_I_OFFSETADDRESS        RTC_REG_RF_IO_CNTRL_OFFSETADDRESS
#define RTC_RF_IO_RTC_IO_I_BITOFFSET            1
#define RTC_RF_IO_RTC_IO_I_BITFIELDSIZE         5
#define RTC_RF_IO_RTC_IO_I_BITMASK              0x0000003e
#define RTC_RF_IO_RTC_IO_I_INIT                 0x0
/*
 *  RTC_RF_IO_RTC_IO_OE bit field defines
 ****************************************************************************************
 */
#define RTC_RF_IO_RTC_IO_OE_OFFSETADDRESS       RTC_REG_RF_IO_CNTRL_OFFSETADDRESS
#define RTC_RF_IO_RTC_IO_OE_BITOFFSET           6
#define RTC_RF_IO_RTC_IO_OE_BITFIELDSIZE        5
#define RTC_RF_IO_RTC_IO_OE_BITMASK             0x000007c0
#define RTC_RF_IO_RTC_IO_OE_INIT                0x0

/*
 *  RTC_REG_RF_PWR_CNTRL register defines
 ****************************************************************************************
 */
#define RTC_REG_RF_PWR_CNTRL_OFFSETADDRESS 0x000003d0  /* RW */
#define RTC_REG_RF_PWR_CNTRL_BITOFFSET 0
#define RTC_REG_RF_PWR_CNTRL_BITFIELDSIZE 32
#define RTC_REG_RF_PWR_CNTRL_BITMASK   0xFFFFFFFF
#define RTC_REG_RF_PWR_CNTRL_INIT      0x00000000
/*
 *  RTC_AX_RTC_READY bit field defines
 ****************************************************************************************
 */
#define RTC_AX_RTC_READY_OFFSETADDRESS          RTC_REG_RF_PWR_CNTRL_OFFSETADDRESS
#define RTC_AX_RTC_READY_BITOFFSET              0
#define RTC_AX_RTC_READY_BITFIELDSIZE           1
#define RTC_AX_RTC_READY_BITMASK                0x00000001
#define RTC_AX_RTC_READY_INIT                   0x0
/*
 *  RTC_AX_AVDD_EN bit field defines
 ****************************************************************************************
 */
#define RTC_AX_AVDD_EN_OFFSETADDRESS            RTC_REG_RF_PWR_CNTRL_OFFSETADDRESS
#define RTC_AX_AVDD_EN_BITOFFSET                1
#define RTC_AX_AVDD_EN_BITFIELDSIZE             1
#define RTC_AX_AVDD_EN_BITMASK                  0x00000002
#define RTC_AX_AVDD_EN_INIT                     0x0
/*
 *  RTC_TX_PA_RTC_READY bit field defines
 ****************************************************************************************
 */
#define RTC_TX_PA_RTC_READY_OFFSETADDRESS       RTC_REG_RF_PWR_CNTRL_OFFSETADDRESS
#define RTC_TX_PA_RTC_READY_BITOFFSET           2
#define RTC_TX_PA_RTC_READY_BITFIELDSIZE        1
#define RTC_TX_PA_RTC_READY_BITMASK             0x00000004
#define RTC_TX_PA_RTC_READY_INIT                0x0


/*
 *  SX_EN_ULDO  register defines
 ****************************************************************************************
 */
#define SX_EN_ULDO_OFFSETADDRESS  0x0360  /* RW */
#define SX_EN_ULDO_BITOFFSET      0
#define SX_EN_ULDO_BITFIELDSIZE   1
#define SX_EN_ULDO_BITMASK        0x00000001
#define SX_EN_ULDO_INIT           0x00000000

#endif
