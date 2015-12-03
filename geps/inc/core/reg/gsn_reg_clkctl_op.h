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
* $RCSfile: gsn_reg_clkctl_op.h,v $
*
* Description : clock control
******************************************************************************/

#ifndef _REG_CLKCTL_MAC_H
#define _REG_CLKCTL_MAC_H

/***************************************************
 *
 *             CLKCTL
 *
 ***************************************************/


/*
 *  CLKCTL_ACM3_GATE_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_ACM3_GATE_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_GATE_EN))
#define CLKCTL_ACM3_GATE_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_GATE_EN, (value))
#define CLKCTL_ACM3_GATE_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_GATE_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_GATE_EN) | (value))
#define CLKCTL_ACM3_GATE_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_GATE_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_GATE_EN) & (~(value)))

/*
 *  CLKCTL_AFC_BUSCLK_EN bit field macros
 ****************************************************************************************
 */
#define CLKCTL_AFC_BUSCLK_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_AFC_BUSCLK_EN)
#define CLKCTL_AFC_BUSCLK_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_AFC_BUSCLK_EN, 1)
#define CLKCTL_AFC_BUSCLK_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_AFC_BUSCLK_EN, 0)

/*
 *  CLKCTL_SMEM_BUSCLK_EN bit field macros
 ****************************************************************************************
 */
#define CLKCTL_SMEM_BUSCLK_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_SMEM_BUSCLK_EN)
#define CLKCTL_SMEM_BUSCLK_EN_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SMEM_BUSCLK_EN, (value))

/*
 *  CLKCTL_AGSPI_BUSCLK_EN bit field macros
 ****************************************************************************************
 */
#define CLKCTL_AGSPI_BUSCLK_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_AGSPI_BUSCLK_EN)
#define CLKCTL_AGSPI_BUSCLK_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_AGSPI_BUSCLK_EN, 1)
#define CLKCTL_AGSPI_BUSCLK_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_AGSPI_BUSCLK_EN, 0)

/*
 *  CLKCTL_SDIO_BUSCLK_EN bit field macros
 ****************************************************************************************
 */
#define CLKCTL_SDIO_BUSCLK_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_SDIO_BUSCLK_EN)
#define CLKCTL_SDIO_BUSCLK_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SDIO_BUSCLK_EN, 1)
#define CLKCTL_SDIO_BUSCLK_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SDIO_BUSCLK_EN, 0)

/*
 *  CLKCTL_AGTMU_BUSCLK_EN bit field macros
 ****************************************************************************************
 */
#define CLKCTL_AGTMU_BUSCLK_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_AGTMU_BUSCLK_EN)
#define CLKCTL_AGTMU_BUSCLK_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_AGTMU_BUSCLK_EN, 1)
#define CLKCTL_AGTMU_BUSCLK_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_AGTMU_BUSCLK_EN, 0)

/*
 *  CLKCTL_ACM3_BUS_FORCE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_ACM3_BUS_FORCE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_BUS_FORCE)
#define CLKCTL_ACM3_BUS_FORCE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_BUS_FORCE, 1)
#define CLKCTL_ACM3_BUS_FORCE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_BUS_FORCE, 0)

/*
 *  CLKCTL_SDIO_GATE_FORCE_EN bit field macros
 ****************************************************************************************
 */
#define CLKCTL_SDIO_GATE_FORCE_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_SDIO_GATE_FORCE_EN)
#define CLKCTL_SDIO_GATE_FORCE_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SDIO_GATE_FORCE_EN, 1)
#define CLKCTL_SDIO_GATE_FORCE_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SDIO_GATE_FORCE_EN, 0)

/*
 *  CLKCTL_ADMA_GATE_FORCE_EN bit field macros
 ****************************************************************************************
 */
#define CLKCTL_ADMA_GATE_FORCE_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_ADMA_GATE_FORCE_EN)
#define CLKCTL_ADMA_GATE_FORCE_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ADMA_GATE_FORCE_EN, 1)
#define CLKCTL_ADMA_GATE_FORCE_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ADMA_GATE_FORCE_EN, 0)

/*
 *  CLKCTL_ACM3_GATE_CTL_EN bit field macros
 ****************************************************************************************
 */
#define CLKCTL_ACM3_GATE_CTL_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_GATE_CTL_EN)
#define CLKCTL_ACM3_GATE_CTL_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_GATE_CTL_EN, 1)
#define CLKCTL_ACM3_GATE_CTL_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_GATE_CTL_EN, 0)

/*
 *  CLKCTL_AFREE_GATE_CTL_EN bit field macros
 ****************************************************************************************
 */
#define CLKCTL_AFREE_GATE_CTL_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_AFREE_GATE_CTL_EN)
#define CLKCTL_AFREE_GATE_CTL_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_AFREE_GATE_CTL_EN, 1)
#define CLKCTL_AFREE_GATE_CTL_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_AFREE_GATE_CTL_EN, 0)


/*
 *  CLKCTL_CREQ_SDIO_IDLE register macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_SDIO_IDLE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_SDIO_IDLE))
#define CLKCTL_CREQ_SDIO_IDLE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_SDIO_IDLE, (value))
#define CLKCTL_CREQ_SDIO_IDLE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_SDIO_IDLE, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_SDIO_IDLE) | (value))
#define CLKCTL_CREQ_SDIO_IDLE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_SDIO_IDLE, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_SDIO_IDLE) & (~(value)))

/*
 *  CLKCTL_REQ_SDIO_IDLE_CLK_LP bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_SDIO_IDLE_CLK_LP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_IDLE_CLK_LP)
#define CLKCTL_REQ_SDIO_IDLE_CLK_LP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_IDLE_CLK_LP, 1)
#define CLKCTL_REQ_SDIO_IDLE_CLK_LP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_IDLE_CLK_LP, 0)

/*
 *  CLKCTL_REQ_SDIO_IDLE_CLK_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_SDIO_IDLE_CLK_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_IDLE_CLK_PLL)
#define CLKCTL_REQ_SDIO_IDLE_CLK_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_IDLE_CLK_PLL, 1)
#define CLKCTL_REQ_SDIO_IDLE_CLK_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_IDLE_CLK_PLL, 0)

/*
 *  CLKCTL_REQ_SDIO_IDLE_CLK_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_SDIO_IDLE_CLK_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_IDLE_CLK_HS_XTAL)
#define CLKCTL_REQ_SDIO_IDLE_CLK_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_IDLE_CLK_HS_XTAL, 1)
#define CLKCTL_REQ_SDIO_IDLE_CLK_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_IDLE_CLK_HS_XTAL, 0)

/*
 *  CLKCTL_REQ_SDIO_IDLE_CLK_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_SDIO_IDLE_CLK_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_IDLE_CLK_HS_RC)
#define CLKCTL_REQ_SDIO_IDLE_CLK_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_IDLE_CLK_HS_RC, 1)
#define CLKCTL_REQ_SDIO_IDLE_CLK_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_IDLE_CLK_HS_RC, 0)


/*
 *  CLKCTL_CREQ_SDIO_ACTIVE register macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_SDIO_ACTIVE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_SDIO_ACTIVE))
#define CLKCTL_CREQ_SDIO_ACTIVE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_SDIO_ACTIVE, (value))
#define CLKCTL_CREQ_SDIO_ACTIVE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_SDIO_ACTIVE, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_SDIO_ACTIVE) | (value))
#define CLKCTL_CREQ_SDIO_ACTIVE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_SDIO_ACTIVE, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_SDIO_ACTIVE) & (~(value)))

/*
 *  CLKCTL_REQ_SDIO_ACTIVE_CLK_LP bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_LP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_ACTIVE_CLK_LP)
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_LP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_ACTIVE_CLK_LP, 1)
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_LP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_ACTIVE_CLK_LP, 0)

/*
 *  CLKCTL_REQ_SDIO_ACTIVE_CLK_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_ACTIVE_CLK_PLL)
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_ACTIVE_CLK_PLL, 1)
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_ACTIVE_CLK_PLL, 0)

/*
 *  CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_XTAL)
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_XTAL, 1)
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_XTAL, 0)

/*
 *  CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_RC)
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_RC, 1)
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_RC, 0)


/*
 *  CLKCTL_CREQ_ACM3_DSLEEP register macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_ACM3_DSLEEP_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_DSLEEP))
#define CLKCTL_CREQ_ACM3_DSLEEP_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_DSLEEP, (value))
#define CLKCTL_CREQ_ACM3_DSLEEP_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_DSLEEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_DSLEEP) | (value))
#define CLKCTL_CREQ_ACM3_DSLEEP_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_DSLEEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_DSLEEP) & (~(value)))

/*
 *  CLKCTL_REQ_ACM3_DSLEEP_CLK_LP bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_LP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_DSLEEP_CLK_LP)
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_LP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_DSLEEP_CLK_LP, 1)
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_LP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_DSLEEP_CLK_LP, 0)

/*
 *  CLKCTL_REQ_ACM3_DSLEEP_CLK_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_DSLEEP_CLK_PLL)
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_DSLEEP_CLK_PLL, 1)
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_DSLEEP_CLK_PLL, 0)

/*
 *  CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_XTAL)
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_XTAL, 1)
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_XTAL, 0)

/*
 *  CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_RC)
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_RC, 1)
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_RC, 0)


/*
 *  CLKCTL_CREQ_ACM3_SLEEP register macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_ACM3_SLEEP_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_SLEEP))
#define CLKCTL_CREQ_ACM3_SLEEP_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_SLEEP, (value))
#define CLKCTL_CREQ_ACM3_SLEEP_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_SLEEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_SLEEP) | (value))
#define CLKCTL_CREQ_ACM3_SLEEP_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_SLEEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_SLEEP) & (~(value)))

/*
 *  CLKCTL_REQ_ACM3_SLEEP_CLK_LP bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_SLEEP_CLK_LP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_SLEEP_CLK_LP)
#define CLKCTL_REQ_ACM3_SLEEP_CLK_LP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_SLEEP_CLK_LP, 1)
#define CLKCTL_REQ_ACM3_SLEEP_CLK_LP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_SLEEP_CLK_LP, 0)

/*
 *  CLKCTL_REQ_ACM3_SLEEP_CLK_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_SLEEP_CLK_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_SLEEP_CLK_PLL)
#define CLKCTL_REQ_ACM3_SLEEP_CLK_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_SLEEP_CLK_PLL, 1)
#define CLKCTL_REQ_ACM3_SLEEP_CLK_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_SLEEP_CLK_PLL, 0)

/*
 *  CLKCTL_REQ_ACM3_SLEEP_CLK_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_SLEEP_CLK_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_SLEEP_CLK_HS_XTAL)
#define CLKCTL_REQ_ACM3_SLEEP_CLK_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_SLEEP_CLK_HS_XTAL, 1)
#define CLKCTL_REQ_ACM3_SLEEP_CLK_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_SLEEP_CLK_HS_XTAL, 0)

/*
 *  CLKCTL_REQ_ACM3_SLEEP_CLK_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_SLEEP_CLK_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_SLEEP_CLK_HS_RC)
#define CLKCTL_REQ_ACM3_SLEEP_CLK_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_SLEEP_CLK_HS_RC, 1)
#define CLKCTL_REQ_ACM3_SLEEP_CLK_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_SLEEP_CLK_HS_RC, 0)


/*
 *  CLKCTL_CREQ_ACM3_ACTIVE register macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_ACM3_ACTIVE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_ACTIVE))
#define CLKCTL_CREQ_ACM3_ACTIVE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_ACTIVE, (value))
#define CLKCTL_CREQ_ACM3_ACTIVE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_ACTIVE, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_ACTIVE) | (value))
#define CLKCTL_CREQ_ACM3_ACTIVE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_ACTIVE, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_ACM3_ACTIVE) & (~(value)))

/*
 *  CLKCTL_REQ_ACM3_ACTIVE_CLK_LP bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_LP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_ACTIVE_CLK_LP)
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_LP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_ACTIVE_CLK_LP, 1)
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_LP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_ACTIVE_CLK_LP, 0)

/*
 *  CLKCTL_REQ_ACM3_ACTIVE_CLK_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_ACTIVE_CLK_PLL)
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_ACTIVE_CLK_PLL, 1)
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_ACTIVE_CLK_PLL, 0)

/*
 *  CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_XTAL)
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_XTAL, 1)
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_XTAL, 0)

/*
 *  CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_RC)
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_RC, 1)
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_RC, 0)


/*
 *  CLKCTL_ACM3_CLK_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_ACM3_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_CLK_SEL))
#define CLKCTL_ACM3_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_CLK_SEL, (value))
#define CLKCTL_ACM3_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_CLK_SEL) | (value))
#define CLKCTL_ACM3_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_CLK_SEL) & (~(value)))

/*
 *  CLKCTL_ACM3_CLK_SEL_CORE_CNTL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_ACM3_CLK_SEL_CORE_CNTL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_CLK_SEL_CORE_CNTL)
#define CLKCTL_ACM3_CLK_SEL_CORE_CNTL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_CLK_SEL_CORE_CNTL, 1)
#define CLKCTL_ACM3_CLK_SEL_CORE_CNTL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_CLK_SEL_CORE_CNTL, 0)

/*
 *  CLKCTL_ACM3_CLK_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_ACM3_CLK_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_CLK_SEL_VAL)
#define CLKCTL_ACM3_CLK_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_CLK_SEL_VAL, (value))


/*
 *  CLKCTL_ACM3_CLK_ACTUAL register macros
 ****************************************************************************************
 */
#define CLKCTL_ACM3_CLK_ACTUAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_CLK_ACTUAL))
#define CLKCTL_ACM3_CLK_ACTUAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_CLK_ACTUAL, (value))
#define CLKCTL_ACM3_CLK_ACTUAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_CLK_ACTUAL) | (value))
#define CLKCTL_ACM3_CLK_ACTUAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_CLK_ACTUAL) & (~(value)))

/*
 *  CLKCTL_ACM3_CLK_ACTUAL_CLK_LP bit field macros
 ****************************************************************************************
 */
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_LP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_CLK_ACTUAL_CLK_LP)
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_LP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_CLK_ACTUAL_CLK_LP, 1)
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_LP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_CLK_ACTUAL_CLK_LP, 0)

/*
 *  CLKCTL_ACM3_CLK_ACTUAL_CLK_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_CLK_ACTUAL_CLK_PLL)
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_CLK_ACTUAL_CLK_PLL, 1)
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_CLK_ACTUAL_CLK_PLL, 0)

/*
 *  CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_XTAL)
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_XTAL, 1)
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_XTAL, 0)

/*
 *  CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_RC)
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_RC, 1)
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_RC, 0)


/*
 *  CLKCTL_ACM3_DIV_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_ACM3_DIV_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_DIV_SEL))
#define CLKCTL_ACM3_DIV_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_DIV_SEL, (value))
#define CLKCTL_ACM3_DIV_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_DIV_SEL) | (value))
#define CLKCTL_ACM3_DIV_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ACM3_DIV_SEL) & (~(value)))

/*
 *  CLKCTL_ACM3_DIV_SEL_VALUE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_ACM3_DIV_SEL_VALUE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_DIV_SEL_VALUE)
#define CLKCTL_ACM3_DIV_SEL_VALUE_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ACM3_DIV_SEL_VALUE, (value))


/*
 *  CLKCTL_UART0_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_UART0_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_EN))
#define CLKCTL_UART0_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_EN, (value))
#define CLKCTL_UART0_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_EN) | (value))
#define CLKCTL_UART0_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_EN) & (~(value)))

/*
 *  CLKCTL_UART0_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_UART0_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_UART0_CLK_ENABLE)
#define CLKCTL_UART0_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_UART0_CLK_ENABLE, 1)
#define CLKCTL_UART0_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_UART0_CLK_ENABLE, 0)


/*
 *  CLKCTL_UART0_CLK_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_UART0_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_SEL))
#define CLKCTL_UART0_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_SEL, (value))
#define CLKCTL_UART0_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_SEL) | (value))
#define CLKCTL_UART0_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_SEL) & (~(value)))

/*
 *  CLKCTL_UART0_CLK_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_UART0_CLK_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_UART0_CLK_SEL_VAL)
#define CLKCTL_UART0_CLK_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_UART0_CLK_SEL_VAL, (value))


/*
 *  CLKCTL_UART0_CLK_ACTUAL register macros
 ****************************************************************************************
 */
#define CLKCTL_UART0_CLK_ACTUAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_ACTUAL))
#define CLKCTL_UART0_CLK_ACTUAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_ACTUAL, (value))
#define CLKCTL_UART0_CLK_ACTUAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_ACTUAL) | (value))
#define CLKCTL_UART0_CLK_ACTUAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_CLK_ACTUAL) & (~(value)))

/*
 *  CLKCTL_UART0_CLK_ACTUAL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_UART0_CLK_ACTUAL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_UART0_CLK_ACTUAL_VAL)
#define CLKCTL_UART0_CLK_ACTUAL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_UART0_CLK_ACTUAL_VAL, (value))


/*
 *  CLKCTL_UART0_DIV_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_UART0_DIV_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_DIV_SEL))
#define CLKCTL_UART0_DIV_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_DIV_SEL, (value))
#define CLKCTL_UART0_DIV_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_DIV_SEL) | (value))
#define CLKCTL_UART0_DIV_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART0_DIV_SEL) & (~(value)))

/*
 *  CLKCTL_UART0_DIV_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_UART0_DIV_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_UART0_DIV_SEL_VAL)
#define CLKCTL_UART0_DIV_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_UART0_DIV_SEL_VAL, (value))


/*
 *  CLKCTL_UART1_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_UART1_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_EN))
#define CLKCTL_UART1_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_EN, (value))
#define CLKCTL_UART1_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_EN) | (value))
#define CLKCTL_UART1_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_EN) & (~(value)))

/*
 *  CLKCTL_UART1_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_UART1_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_UART1_CLK_ENABLE)
#define CLKCTL_UART1_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_UART1_CLK_ENABLE, 1)
#define CLKCTL_UART1_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_UART1_CLK_ENABLE, 0)


/*
 *  CLKCTL_UART1_CLK_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_UART1_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_SEL))
#define CLKCTL_UART1_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_SEL, (value))
#define CLKCTL_UART1_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_SEL) | (value))
#define CLKCTL_UART1_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_SEL) & (~(value)))

/*
 *  CLKCTL_UART1_CLK_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_UART1_CLK_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_UART1_CLK_SEL_VAL)
#define CLKCTL_UART1_CLK_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_UART1_CLK_SEL_VAL, (value))


/*
 *  CLKCTL_UART1_CLK_ACTUAL register macros
 ****************************************************************************************
 */
#define CLKCTL_UART1_CLK_ACTUAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_ACTUAL))
#define CLKCTL_UART1_CLK_ACTUAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_ACTUAL, (value))
#define CLKCTL_UART1_CLK_ACTUAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_ACTUAL) | (value))
#define CLKCTL_UART1_CLK_ACTUAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_CLK_ACTUAL) & (~(value)))

/*
 *  CLKCTL_UART1_CLK_ACTUAL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_UART1_CLK_ACTUAL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_UART1_CLK_ACTUAL_VAL)
#define CLKCTL_UART1_CLK_ACTUAL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_UART1_CLK_ACTUAL_VAL, (value))


/*
 *  CLKCTL_UART1_DIV_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_UART1_DIV_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_DIV_SEL))
#define CLKCTL_UART1_DIV_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_DIV_SEL, (value))
#define CLKCTL_UART1_DIV_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_DIV_SEL) | (value))
#define CLKCTL_UART1_DIV_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_UART1_DIV_SEL) & (~(value)))

/*
 *  CLKCTL_UART1_DIV_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_UART1_DIV_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_UART1_DIV_SEL_VAL)
#define CLKCTL_UART1_DIV_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_UART1_DIV_SEL_VAL, (value))


/*
 *  CLKCTL_SSP0_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_SSP0_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_EN))
#define CLKCTL_SSP0_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_EN, (value))
#define CLKCTL_SSP0_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_EN) | (value))
#define CLKCTL_SSP0_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_EN) & (~(value)))

/*
 *  CLKCTL_SSP0_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_SSP0_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_SSP0_CLK_ENABLE)
#define CLKCTL_SSP0_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SSP0_CLK_ENABLE, 1)
#define CLKCTL_SSP0_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SSP0_CLK_ENABLE, 0)


/*
 *  CLKCTL_SSP0_CLK_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_SSP0_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_SEL))
#define CLKCTL_SSP0_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_SEL, (value))
#define CLKCTL_SSP0_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_SEL) | (value))
#define CLKCTL_SSP0_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_SEL) & (~(value)))

/*
 *  CLKCTL_SSP0_CLK_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_SSP0_CLK_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_SSP0_CLK_SEL_VAL)
#define CLKCTL_SSP0_CLK_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SSP0_CLK_SEL_VAL, (value))


/*
 *  CLKCTL_SSP0_CLK_ACTUAL register macros
 ****************************************************************************************
 */
#define CLKCTL_SSP0_CLK_ACTUAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_ACTUAL))
#define CLKCTL_SSP0_CLK_ACTUAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_ACTUAL, (value))
#define CLKCTL_SSP0_CLK_ACTUAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_ACTUAL) | (value))
#define CLKCTL_SSP0_CLK_ACTUAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_CLK_ACTUAL) & (~(value)))

/*
 *  CLKCTL_SSP0_CLK_ACTUAL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_SSP0_CLK_ACTUAL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_SSP0_CLK_ACTUAL_VAL)
#define CLKCTL_SSP0_CLK_ACTUAL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SSP0_CLK_ACTUAL_VAL, (value))


/*
 *  CLKCTL_SSP0_DIV_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_SSP0_DIV_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_DIV_SEL))
#define CLKCTL_SSP0_DIV_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_DIV_SEL, (value))
#define CLKCTL_SSP0_DIV_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_DIV_SEL) | (value))
#define CLKCTL_SSP0_DIV_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP0_DIV_SEL) & (~(value)))

/*
 *  CLKCTL_SSP0_DIV_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_SSP0_DIV_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_SSP0_DIV_SEL_VAL)
#define CLKCTL_SSP0_DIV_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SSP0_DIV_SEL_VAL, (value))


/*
 *  CLKCTL_SSP1_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_SSP1_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_EN))
#define CLKCTL_SSP1_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_EN, (value))
#define CLKCTL_SSP1_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_EN) | (value))
#define CLKCTL_SSP1_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_EN) & (~(value)))

/*
 *  CLKCTL_SSP1_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_SSP1_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_SSP1_CLK_ENABLE)
#define CLKCTL_SSP1_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SSP1_CLK_ENABLE, 1)
#define CLKCTL_SSP1_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SSP1_CLK_ENABLE, 0)


/*
 *  CLKCTL_SSP1_CLK_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_SSP1_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_SEL))
#define CLKCTL_SSP1_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_SEL, (value))
#define CLKCTL_SSP1_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_SEL) | (value))
#define CLKCTL_SSP1_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_SEL) & (~(value)))

/*
 *  CLKCTL_SSP1_CLK_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_SSP1_CLK_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_SSP1_CLK_SEL_VAL)
#define CLKCTL_SSP1_CLK_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SSP1_CLK_SEL_VAL, (value))


/*
 *  CLKCTL_SSP1_CLK_ACTUAL register macros
 ****************************************************************************************
 */
#define CLKCTL_SSP1_CLK_ACTUAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_ACTUAL))
#define CLKCTL_SSP1_CLK_ACTUAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_ACTUAL, (value))
#define CLKCTL_SSP1_CLK_ACTUAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_ACTUAL) | (value))
#define CLKCTL_SSP1_CLK_ACTUAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_CLK_ACTUAL) & (~(value)))

/*
 *  CLKCTL_SSP1_CLK_ACTUAL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_SSP1_CLK_ACTUAL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_SSP1_CLK_ACTUAL_VAL)
#define CLKCTL_SSP1_CLK_ACTUAL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SSP1_CLK_ACTUAL_VAL, (value))


/*
 *  CLKCTL_SSP1_DIV_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_SSP1_DIV_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_DIV_SEL))
#define CLKCTL_SSP1_DIV_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_DIV_SEL, (value))
#define CLKCTL_SSP1_DIV_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_DIV_SEL) | (value))
#define CLKCTL_SSP1_DIV_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SSP1_DIV_SEL) & (~(value)))

/*
 *  CLKCTL_SSP1_DIV_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_SSP1_DIV_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_SSP1_DIV_SEL_VAL)
#define CLKCTL_SSP1_DIV_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SSP1_DIV_SEL_VAL, (value))


/*
 *  CLKCTL_I2C_NCO_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_I2C_NCO_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_NCO_EN))
#define CLKCTL_I2C_NCO_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_NCO_EN, (value))
#define CLKCTL_I2C_NCO_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_NCO_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_NCO_EN) | (value))
#define CLKCTL_I2C_NCO_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_NCO_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_NCO_EN) & (~(value)))

/*
 *  CLKCTL_I2C_NCO_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_I2C_NCO_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_I2C_NCO_ENABLE)
#define CLKCTL_I2C_NCO_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_I2C_NCO_ENABLE, 1)
#define CLKCTL_I2C_NCO_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_I2C_NCO_ENABLE, 0)


/*
 *  CLKCTL_I2C_CLK_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_I2C_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_CLK_SEL))
#define CLKCTL_I2C_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_CLK_SEL, (value))
#define CLKCTL_I2C_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_CLK_SEL) | (value))
#define CLKCTL_I2C_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_CLK_SEL) & (~(value)))

/*
 *  CLKCTL_I2C_CLK_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_I2C_CLK_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_I2C_CLK_SEL_VAL)
#define CLKCTL_I2C_CLK_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_I2C_CLK_SEL_VAL, (value))


/*
 *  CLKCTL_I2C_CLK_ACTUAL register macros
 ****************************************************************************************
 */
#define CLKCTL_I2C_CLK_ACTUAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_CLK_ACTUAL))
#define CLKCTL_I2C_CLK_ACTUAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_CLK_ACTUAL, (value))
#define CLKCTL_I2C_CLK_ACTUAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_CLK_ACTUAL) | (value))
#define CLKCTL_I2C_CLK_ACTUAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_CLK_ACTUAL) & (~(value)))

/*
 *  CLKCTL_I2C_CLK_ACTUAL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_I2C_CLK_ACTUAL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_I2C_CLK_ACTUAL_VAL)
#define CLKCTL_I2C_CLK_ACTUAL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_I2C_CLK_ACTUAL_VAL, (value))


/*
 *  CLKCTL_I2C_STEP register macros
 ****************************************************************************************
 */
#define CLKCTL_I2C_STEP_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_STEP))
#define CLKCTL_I2C_STEP_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_STEP, (value))
#define CLKCTL_I2C_STEP_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_STEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_STEP) | (value))
#define CLKCTL_I2C_STEP_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_STEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2C_STEP) & (~(value)))

/*
 *  CLKCTL_I2C_STEP_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_I2C_STEP_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_I2C_STEP_VAL)
#define CLKCTL_I2C_STEP_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_I2C_STEP_VAL, (value))


/*
 *  CLKCTL_I2S_NCO_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_I2S_NCO_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_NCO_EN))
#define CLKCTL_I2S_NCO_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_NCO_EN, (value))
#define CLKCTL_I2S_NCO_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_NCO_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_NCO_EN) | (value))
#define CLKCTL_I2S_NCO_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_NCO_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_NCO_EN) & (~(value)))

/*
 *  CLKCTL_I2S_NCO_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_I2S_NCO_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_I2S_NCO_ENABLE)
#define CLKCTL_I2S_NCO_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_I2S_NCO_ENABLE, 1)
#define CLKCTL_I2S_NCO_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_I2S_NCO_ENABLE, 0)


/*
 *  CLKCTL_I2S_CLK_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_I2S_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_CLK_SEL))
#define CLKCTL_I2S_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_CLK_SEL, (value))
#define CLKCTL_I2S_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_CLK_SEL) | (value))
#define CLKCTL_I2S_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_CLK_SEL) & (~(value)))

/*
 *  CLKCTL_I2S_CLK_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_I2S_CLK_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_I2S_CLK_SEL_VAL)
#define CLKCTL_I2S_CLK_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_I2S_CLK_SEL_VAL, (value))


/*
 *  CLKCTL_I2S_CLK_ACTUAL register macros
 ****************************************************************************************
 */
#define CLKCTL_I2S_CLK_ACTUAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_CLK_ACTUAL))
#define CLKCTL_I2S_CLK_ACTUAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_CLK_ACTUAL, (value))
#define CLKCTL_I2S_CLK_ACTUAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_CLK_ACTUAL) | (value))
#define CLKCTL_I2S_CLK_ACTUAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_CLK_ACTUAL) & (~(value)))

/*
 *  CLKCTL_I2S_CLK_ACTUAL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_I2S_CLK_ACTUAL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_I2S_CLK_ACTUAL_VAL)
#define CLKCTL_I2S_CLK_ACTUAL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_I2S_CLK_ACTUAL_VAL, (value))


/*
 *  CLKCTL_I2S_STEP register macros
 ****************************************************************************************
 */
#define CLKCTL_I2S_STEP_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_STEP))
#define CLKCTL_I2S_STEP_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_STEP, (value))
#define CLKCTL_I2S_STEP_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_STEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_STEP) | (value))
#define CLKCTL_I2S_STEP_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_STEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2S_STEP) & (~(value)))

/*
 *  CLKCTL_I2S_STEP_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_I2S_STEP_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_I2S_STEP_VAL)
#define CLKCTL_I2S_STEP_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_I2S_STEP_VAL, (value))


/*
 *  CLKCTL_OTP0_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_OTP0_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_EN))
#define CLKCTL_OTP0_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_EN, (value))
#define CLKCTL_OTP0_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_EN) | (value))
#define CLKCTL_OTP0_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_EN) & (~(value)))

/*
 *  CLKCTL_OTP0_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_OTP0_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_OTP0_CLK_ENABLE)
#define CLKCTL_OTP0_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_OTP0_CLK_ENABLE, 1)
#define CLKCTL_OTP0_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_OTP0_CLK_ENABLE, 0)


/*
 *  CLKCTL_OTP0_CLK_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_OTP0_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_SEL))
#define CLKCTL_OTP0_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_SEL, (value))
#define CLKCTL_OTP0_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_SEL) | (value))
#define CLKCTL_OTP0_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_SEL) & (~(value)))

/*
 *  CLKCTL_OTP0_CLK_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_OTP0_CLK_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_OTP0_CLK_SEL_VAL)
#define CLKCTL_OTP0_CLK_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_OTP0_CLK_SEL_VAL, (value))


/*
 *  CLKCTL_OTP0_CLK_ACTUAL register macros
 ****************************************************************************************
 */
#define CLKCTL_OTP0_CLK_ACTUAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_ACTUAL))
#define CLKCTL_OTP0_CLK_ACTUAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_ACTUAL, (value))
#define CLKCTL_OTP0_CLK_ACTUAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_ACTUAL) | (value))
#define CLKCTL_OTP0_CLK_ACTUAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_CLK_ACTUAL) & (~(value)))

/*
 *  CLKCTL_OTP0_CLK_ACTUAL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_OTP0_CLK_ACTUAL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_OTP0_CLK_ACTUAL_VAL)
#define CLKCTL_OTP0_CLK_ACTUAL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_OTP0_CLK_ACTUAL_VAL, (value))


/*
 *  CLKCTL_OTP0_DIV_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_OTP0_DIV_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_DIV_SEL))
#define CLKCTL_OTP0_DIV_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_DIV_SEL, (value))
#define CLKCTL_OTP0_DIV_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_DIV_SEL) | (value))
#define CLKCTL_OTP0_DIV_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP0_DIV_SEL) & (~(value)))

/*
 *  CLKCTL_OTP0_DIV_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_OTP0_DIV_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_OTP0_DIV_SEL_VAL)
#define CLKCTL_OTP0_DIV_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_OTP0_DIV_SEL_VAL, (value))


/*
 *  CLKCTL_OTP1_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_OTP1_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_EN))
#define CLKCTL_OTP1_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_EN, (value))
#define CLKCTL_OTP1_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_EN) | (value))
#define CLKCTL_OTP1_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_EN) & (~(value)))

/*
 *  CLKCTL_OTP1_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_OTP1_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_OTP1_CLK_ENABLE)
#define CLKCTL_OTP1_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_OTP1_CLK_ENABLE, 1)
#define CLKCTL_OTP1_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_OTP1_CLK_ENABLE, 0)


/*
 *  CLKCTL_OTP1_CLK_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_OTP1_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_SEL))
#define CLKCTL_OTP1_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_SEL, (value))
#define CLKCTL_OTP1_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_SEL) | (value))
#define CLKCTL_OTP1_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_SEL) & (~(value)))

/*
 *  CLKCTL_OTP1_CLK_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_OTP1_CLK_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_OTP1_CLK_SEL_VAL)
#define CLKCTL_OTP1_CLK_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_OTP1_CLK_SEL_VAL, (value))


/*
 *  CLKCTL_OTP1_CLK_ACTUAL register macros
 ****************************************************************************************
 */
#define CLKCTL_OTP1_CLK_ACTUAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_ACTUAL))
#define CLKCTL_OTP1_CLK_ACTUAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_ACTUAL, (value))
#define CLKCTL_OTP1_CLK_ACTUAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_ACTUAL) | (value))
#define CLKCTL_OTP1_CLK_ACTUAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_CLK_ACTUAL) & (~(value)))

/*
 *  CLKCTL_OTP1_CLK_ACTUAL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_OTP1_CLK_ACTUAL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_OTP1_CLK_ACTUAL_VAL)
#define CLKCTL_OTP1_CLK_ACTUAL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_OTP1_CLK_ACTUAL_VAL, (value))


/*
 *  CLKCTL_OTP1_DIV_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_OTP1_DIV_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_DIV_SEL))
#define CLKCTL_OTP1_DIV_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_DIV_SEL, (value))
#define CLKCTL_OTP1_DIV_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_DIV_SEL) | (value))
#define CLKCTL_OTP1_DIV_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_OTP1_DIV_SEL) & (~(value)))

/*
 *  CLKCTL_OTP1_DIV_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_OTP1_DIV_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_OTP1_DIV_SEL_VAL)
#define CLKCTL_OTP1_DIV_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_OTP1_DIV_SEL_VAL, (value))


/*
 *  CLKCTL_FIF_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_FIF_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_EN))
#define CLKCTL_FIF_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_EN, (value))
#define CLKCTL_FIF_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_EN) | (value))
#define CLKCTL_FIF_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_EN) & (~(value)))

/*
 *  CLKCTL_FIF_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_FIF_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_FIF_CLK_ENABLE)
#define CLKCTL_FIF_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_FIF_CLK_ENABLE, 1)
#define CLKCTL_FIF_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_FIF_CLK_ENABLE, 0)


/*
 *  CLKCTL_FIF_CLK_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_FIF_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_SEL))
#define CLKCTL_FIF_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_SEL, (value))
#define CLKCTL_FIF_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_SEL) | (value))
#define CLKCTL_FIF_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_SEL) & (~(value)))

/*
 *  CLKCTL_FIF_CLK_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_FIF_CLK_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_FIF_CLK_SEL_VAL)
#define CLKCTL_FIF_CLK_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_FIF_CLK_SEL_VAL, (value))


/*
 *  CLKCTL_FIF_CLK_ACTUAL register macros
 ****************************************************************************************
 */
#define CLKCTL_FIF_CLK_ACTUAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_ACTUAL))
#define CLKCTL_FIF_CLK_ACTUAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_ACTUAL, (value))
#define CLKCTL_FIF_CLK_ACTUAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_ACTUAL) | (value))
#define CLKCTL_FIF_CLK_ACTUAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_CLK_ACTUAL) & (~(value)))

/*
 *  CLKCTL_FIF_CLK_ACTUAL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_FIF_CLK_ACTUAL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_FIF_CLK_ACTUAL_VAL)
#define CLKCTL_FIF_CLK_ACTUAL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_FIF_CLK_ACTUAL_VAL, (value))


/*
 *  CLKCTL_FIF_DIV_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_FIF_DIV_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_DIV_SEL))
#define CLKCTL_FIF_DIV_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_DIV_SEL, (value))
#define CLKCTL_FIF_DIV_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_DIV_SEL) | (value))
#define CLKCTL_FIF_DIV_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_FIF_DIV_SEL) & (~(value)))

/*
 *  CLKCTL_FIF_DIV_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_FIF_DIV_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_FIF_DIV_SEL_VAL)
#define CLKCTL_FIF_DIV_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_FIF_DIV_SEL_VAL, (value))


/*
 *  CLKCTL_PWM_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_PWM_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_EN))
#define CLKCTL_PWM_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_EN, (value))
#define CLKCTL_PWM_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_EN) | (value))
#define CLKCTL_PWM_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_EN) & (~(value)))

/*
 *  CLKCTL_PWM_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_PWM_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_PWM_CLK_ENABLE)
#define CLKCTL_PWM_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_PWM_CLK_ENABLE, 1)
#define CLKCTL_PWM_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_PWM_CLK_ENABLE, 0)


/*
 *  CLKCTL_PWM_CLK_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_PWM_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_SEL))
#define CLKCTL_PWM_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_SEL, (value))
#define CLKCTL_PWM_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_SEL) | (value))
#define CLKCTL_PWM_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_SEL) & (~(value)))

/*
 *  CLKCTL_PWM_CLK_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_PWM_CLK_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_PWM_CLK_SEL_VAL)
#define CLKCTL_PWM_CLK_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_PWM_CLK_SEL_VAL, (value))


/*
 *  CLKCTL_PWM_CLK_ACTUAL register macros
 ****************************************************************************************
 */
#define CLKCTL_PWM_CLK_ACTUAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_ACTUAL))
#define CLKCTL_PWM_CLK_ACTUAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_ACTUAL, (value))
#define CLKCTL_PWM_CLK_ACTUAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_ACTUAL) | (value))
#define CLKCTL_PWM_CLK_ACTUAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_CLK_ACTUAL) & (~(value)))

/*
 *  CLKCTL_PWM_CLK_ACTUAL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_PWM_CLK_ACTUAL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_PWM_CLK_ACTUAL_VAL)
#define CLKCTL_PWM_CLK_ACTUAL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_PWM_CLK_ACTUAL_VAL, (value))


/*
 *  CLKCTL_PWM_DIV_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_PWM_DIV_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_DIV_SEL))
#define CLKCTL_PWM_DIV_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_DIV_SEL, (value))
#define CLKCTL_PWM_DIV_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_DIV_SEL) | (value))
#define CLKCTL_PWM_DIV_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_PWM_DIV_SEL) & (~(value)))

/*
 *  CLKCTL_PWM_DIV_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_PWM_DIV_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_PWM_DIV_SEL_VAL)
#define CLKCTL_PWM_DIV_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_PWM_DIV_SEL_VAL, (value))


/*
 *  CLKCTL_SDADCDAC_NCO_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_SDADCDAC_NCO_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_NCO_EN))
#define CLKCTL_SDADCDAC_NCO_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_NCO_EN, (value))
#define CLKCTL_SDADCDAC_NCO_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_NCO_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_NCO_EN) | (value))
#define CLKCTL_SDADCDAC_NCO_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_NCO_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_NCO_EN) & (~(value)))

/*
 *  CLKCTL_SDADCDAC_NCO_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_SDADCDAC_NCO_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_SDADCDAC_NCO_ENABLE)
#define CLKCTL_SDADCDAC_NCO_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SDADCDAC_NCO_ENABLE, 1)
#define CLKCTL_SDADCDAC_NCO_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SDADCDAC_NCO_ENABLE, 0)


/*
 *  CLKCTL_SDADCDAC_CLK_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_SDADCDAC_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_CLK_SEL))
#define CLKCTL_SDADCDAC_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_CLK_SEL, (value))
#define CLKCTL_SDADCDAC_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_CLK_SEL) | (value))
#define CLKCTL_SDADCDAC_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_CLK_SEL) & (~(value)))

/*
 *  CLKCTL_SDADCDAC_CLK_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_SDADCDAC_CLK_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_SDADCDAC_CLK_SEL_VAL)
#define CLKCTL_SDADCDAC_CLK_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SDADCDAC_CLK_SEL_VAL, (value))


/*
 *  CLKCTL_SDADCDAC_CLK_ACTUAL register macros
 ****************************************************************************************
 */
#define CLKCTL_SDADCDAC_CLK_ACTUAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_CLK_ACTUAL))
#define CLKCTL_SDADCDAC_CLK_ACTUAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_CLK_ACTUAL, (value))
#define CLKCTL_SDADCDAC_CLK_ACTUAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_CLK_ACTUAL) | (value))
#define CLKCTL_SDADCDAC_CLK_ACTUAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_CLK_ACTUAL) & (~(value)))

/*
 *  CLKCTL_SDADCDAC_CLK_ACTUAL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_SDADCDAC_CLK_ACTUAL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_SDADCDAC_CLK_ACTUAL_VAL)
#define CLKCTL_SDADCDAC_CLK_ACTUAL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SDADCDAC_CLK_ACTUAL_VAL, (value))


/*
 *  CLKCTL_SDADCDAC_STEP register macros
 ****************************************************************************************
 */
#define CLKCTL_SDADCDAC_STEP_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_STEP))
#define CLKCTL_SDADCDAC_STEP_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_STEP, (value))
#define CLKCTL_SDADCDAC_STEP_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_STEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_STEP) | (value))
#define CLKCTL_SDADCDAC_STEP_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_STEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_SDADCDAC_STEP) & (~(value)))

/*
 *  CLKCTL_SDADCDAC_STEP_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_SDADCDAC_STEP_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_SDADCDAC_STEP_VAL)
#define CLKCTL_SDADCDAC_STEP_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_SDADCDAC_STEP_VAL, (value))


/*
 *  CLKCTL_CREQ_AADC_ACTIVE register macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AADC_ACTIVE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AADC_ACTIVE))
#define CLKCTL_CREQ_AADC_ACTIVE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AADC_ACTIVE, (value))
#define CLKCTL_CREQ_AADC_ACTIVE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AADC_ACTIVE, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AADC_ACTIVE) | (value))
#define CLKCTL_CREQ_AADC_ACTIVE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AADC_ACTIVE, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AADC_ACTIVE) & (~(value)))

/*
 *  CLKCTL_REQ_AADC_ACTIVE_CLK_LP bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_AADC_ACTIVE_CLK_LP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_AADC_ACTIVE_CLK_LP)
#define CLKCTL_REQ_AADC_ACTIVE_CLK_LP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_AADC_ACTIVE_CLK_LP, 1)
#define CLKCTL_REQ_AADC_ACTIVE_CLK_LP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_AADC_ACTIVE_CLK_LP, 0)

/*
 *  CLKCTL_REQ_AADC_ACTIVE_CLK_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_AADC_ACTIVE_CLK_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_AADC_ACTIVE_CLK_PLL)
#define CLKCTL_REQ_AADC_ACTIVE_CLK_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_AADC_ACTIVE_CLK_PLL, 1)
#define CLKCTL_REQ_AADC_ACTIVE_CLK_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_AADC_ACTIVE_CLK_PLL, 0)

/*
 *  CLKCTL_REQ_AADC_ACTIVE_CLK_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_AADC_ACTIVE_CLK_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_AADC_ACTIVE_CLK_HS_XTAL)
#define CLKCTL_REQ_AADC_ACTIVE_CLK_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_AADC_ACTIVE_CLK_HS_XTAL, 1)
#define CLKCTL_REQ_AADC_ACTIVE_CLK_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_AADC_ACTIVE_CLK_HS_XTAL, 0)

/*
 *  CLKCTL_REQ_AADC_ACTIVE_CLK_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_REQ_AADC_ACTIVE_CLK_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_REQ_AADC_ACTIVE_CLK_HS_RC)
#define CLKCTL_REQ_AADC_ACTIVE_CLK_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_AADC_ACTIVE_CLK_HS_RC, 1)
#define CLKCTL_REQ_AADC_ACTIVE_CLK_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_REQ_AADC_ACTIVE_CLK_HS_RC, 0)


/*
 *  CLKCTL_ADC_NCO_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_ADC_NCO_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_NCO_EN))
#define CLKCTL_ADC_NCO_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_NCO_EN, (value))
#define CLKCTL_ADC_NCO_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_NCO_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_NCO_EN) | (value))
#define CLKCTL_ADC_NCO_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_NCO_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_NCO_EN) & (~(value)))

/*
 *  CLKCTL_AADC_NCO_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_AADC_NCO_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_AADC_NCO_ENABLE)
#define CLKCTL_AADC_NCO_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_AADC_NCO_ENABLE, 1)
#define CLKCTL_AADC_NCO_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_AADC_NCO_ENABLE, 0)


/*
 *  CLKCTL_ADC_CLK_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_ADC_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_CLK_SEL))
#define CLKCTL_ADC_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_CLK_SEL, (value))
#define CLKCTL_ADC_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_CLK_SEL) | (value))
#define CLKCTL_ADC_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_CLK_SEL) & (~(value)))

/*
 *  CLKCTL_ADC_CLK_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_ADC_CLK_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_ADC_CLK_SEL_VAL)
#define CLKCTL_ADC_CLK_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ADC_CLK_SEL_VAL, (value))


/*
 *  CLKCTL_ADC_CLK_ACTUAL register macros
 ****************************************************************************************
 */
#define CLKCTL_ADC_CLK_ACTUAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_CLK_ACTUAL))
#define CLKCTL_ADC_CLK_ACTUAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_CLK_ACTUAL, (value))
#define CLKCTL_ADC_CLK_ACTUAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_CLK_ACTUAL) | (value))
#define CLKCTL_ADC_CLK_ACTUAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_CLK_ACTUAL) & (~(value)))

/*
 *  CLKCTL_ADC_CLK_ACTUAL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_ADC_CLK_ACTUAL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_ADC_CLK_ACTUAL_VAL)
#define CLKCTL_ADC_CLK_ACTUAL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ADC_CLK_ACTUAL_VAL, (value))


/*
 *  CLKCTL_ADC_STEP register macros
 ****************************************************************************************
 */
#define CLKCTL_ADC_STEP_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_STEP))
#define CLKCTL_ADC_STEP_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_STEP, (value))
#define CLKCTL_ADC_STEP_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_STEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_STEP) | (value))
#define CLKCTL_ADC_STEP_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_STEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_ADC_STEP) & (~(value)))

/*
 *  CLKCTL_ADC_STEP_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_ADC_STEP_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_ADC_STEP_VAL)
#define CLKCTL_ADC_STEP_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_ADC_STEP_VAL, (value))


/*
 *  CLKCTL_GTMU_NCO_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_NCO_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_NCO_EN))
#define CLKCTL_GTMU_NCO_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_NCO_EN, (value))
#define CLKCTL_GTMU_NCO_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_NCO_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_NCO_EN) | (value))
#define CLKCTL_GTMU_NCO_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_NCO_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_NCO_EN) & (~(value)))

/*
 *  CLKCTL_GTMU_AUX_NCO_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_AUX_NCO_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_AUX_NCO_ENABLE)
#define CLKCTL_GTMU_AUX_NCO_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_AUX_NCO_ENABLE, 1)
#define CLKCTL_GTMU_AUX_NCO_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_AUX_NCO_ENABLE, 0)

/*
 *  CLKCTL_GTMU_NCO_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_NCO_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_NCO_ENABLE)
#define CLKCTL_GTMU_NCO_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_NCO_ENABLE, 1)
#define CLKCTL_GTMU_NCO_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_NCO_ENABLE, 0)


/*
 *  CLKCTL_GTMU_CLK_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_SEL))
#define CLKCTL_GTMU_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_SEL, (value))
#define CLKCTL_GTMU_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_SEL) | (value))
#define CLKCTL_GTMU_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_SEL) & (~(value)))

/*
 *  CLKCTL_GTMU_GPIO_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_GPIO_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_GPIO_SEL_VAL)
#define CLKCTL_GTMU_GPIO_SEL_VAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_GPIO_SEL_VAL, 1)
#define CLKCTL_GTMU_GPIO_SEL_VAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_GPIO_SEL_VAL, 0)

/*
 *  CLKCTL_GTMU_CLK_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_CLK_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_CLK_SEL_VAL)
#define CLKCTL_GTMU_CLK_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_CLK_SEL_VAL, (value))


/*
 *  CLKCTL_GTMU_CLK_ACTUAL register macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_CLK_ACTUAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_ACTUAL))
#define CLKCTL_GTMU_CLK_ACTUAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_ACTUAL, (value))
#define CLKCTL_GTMU_CLK_ACTUAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_ACTUAL) | (value))
#define CLKCTL_GTMU_CLK_ACTUAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_ACTUAL) & (~(value)))

/*
 *  CLKCTL_GTMU_CLK_ACTUAL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_CLK_ACTUAL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_CLK_ACTUAL_VAL)
#define CLKCTL_GTMU_CLK_ACTUAL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_CLK_ACTUAL_VAL, (value))


/*
 *  CLKCTL_GTMU_STEP register macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_STEP_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_STEP))
#define CLKCTL_GTMU_STEP_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_STEP, (value))
#define CLKCTL_GTMU_STEP_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_STEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_STEP) | (value))
#define CLKCTL_GTMU_STEP_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_STEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_STEP) & (~(value)))

/*
 *  CLKCTL_GTMU_STEP_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_STEP_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_STEP_VAL)
#define CLKCTL_GTMU_STEP_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_STEP_VAL, (value))


/*
 *  CLKCTL_GTMU_SELECT0 register macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_SELECT0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_SELECT0))
#define CLKCTL_GTMU_SELECT0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_SELECT0, (value))
#define CLKCTL_GTMU_SELECT0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_SELECT0, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_SELECT0) | (value))
#define CLKCTL_GTMU_SELECT0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_SELECT0, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_SELECT0) & (~(value)))

/*
 *  CLKCTL_GTMU_SELECT0_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_SELECT0_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_SELECT0_VAL)
#define CLKCTL_GTMU_SELECT0_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_SELECT0_VAL, (value))


/*
 *  CLKCTL_GTMU_CLK_SEL1 register macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_CLK_SEL1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_SEL1))
#define CLKCTL_GTMU_CLK_SEL1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_SEL1, (value))
#define CLKCTL_GTMU_CLK_SEL1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_SEL1, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_SEL1) | (value))
#define CLKCTL_GTMU_CLK_SEL1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_SEL1, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_SEL1) & (~(value)))

/*
 *  CLKCTL_GTMU_GPIO_SEL1_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_GPIO_SEL1_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_GPIO_SEL1_VAL)
#define CLKCTL_GTMU_GPIO_SEL1_VAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_GPIO_SEL1_VAL, 1)
#define CLKCTL_GTMU_GPIO_SEL1_VAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_GPIO_SEL1_VAL, 0)

/*
 *  CLKCTL_GTMU_CLK_SEL1_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_CLK_SEL1_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_CLK_SEL1_VAL)
#define CLKCTL_GTMU_CLK_SEL1_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_CLK_SEL1_VAL, (value))


/*
 *  CLKCTL_GTMU_CLK_ACTUAL1 register macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_CLK_ACTUAL1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_ACTUAL1))
#define CLKCTL_GTMU_CLK_ACTUAL1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_ACTUAL1, (value))
#define CLKCTL_GTMU_CLK_ACTUAL1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_ACTUAL1, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_ACTUAL1) | (value))
#define CLKCTL_GTMU_CLK_ACTUAL1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_ACTUAL1, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_CLK_ACTUAL1) & (~(value)))

/*
 *  CLKCTL_GTMU_CLK_ACTUAL1_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_CLK_ACTUAL1_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_CLK_ACTUAL1_VAL)
#define CLKCTL_GTMU_CLK_ACTUAL1_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_CLK_ACTUAL1_VAL, (value))


/*
 *  CLKCTL_GTMU_STEP1 register macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_STEP1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_STEP1))
#define CLKCTL_GTMU_STEP1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_STEP1, (value))
#define CLKCTL_GTMU_STEP1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_STEP1, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_STEP1) | (value))
#define CLKCTL_GTMU_STEP1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_STEP1, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_STEP1) & (~(value)))

/*
 *  CLKCTL_GTMU_STEP1_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_STEP1_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_STEP1_VAL)
#define CLKCTL_GTMU_STEP1_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_STEP1_VAL, (value))


/*
 *  CLKCTL_GTMU_SELECT1 register macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_SELECT1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_SELECT1))
#define CLKCTL_GTMU_SELECT1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_SELECT1, (value))
#define CLKCTL_GTMU_SELECT1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_SELECT1, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_SELECT1) | (value))
#define CLKCTL_GTMU_SELECT1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_SELECT1, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMU_SELECT1) & (~(value)))

/*
 *  CLKCTL_GTMU_SELECT1_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_GTMU_SELECT1_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_SELECT1_VAL)
#define CLKCTL_GTMU_SELECT1_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMU_SELECT1_VAL, (value))


/*
 *  CLKCTL_BUS_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_BUS_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_BUS_CLK_EN))
#define CLKCTL_BUS_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_BUS_CLK_EN, (value))
#define CLKCTL_BUS_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_BUS_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_BUS_CLK_EN) | (value))
#define CLKCTL_BUS_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_BUS_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_BUS_CLK_EN) & (~(value)))

/*
 *  CLKCTL_BUS_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_BUS_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_BUS_CLK_ENABLE)
#define CLKCTL_BUS_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_BUS_CLK_ENABLE, 1)
#define CLKCTL_BUS_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_BUS_CLK_ENABLE, 0)


/*
 *  CLKCTL_GPIO_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_GPIO_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GPIO_CLK_EN))
#define CLKCTL_GPIO_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GPIO_CLK_EN, (value))
#define CLKCTL_GPIO_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GPIO_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GPIO_CLK_EN) | (value))
#define CLKCTL_GPIO_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GPIO_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GPIO_CLK_EN) & (~(value)))

/*
 *  CLKCTL_GPIO_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_GPIO_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_GPIO_CLK_ENABLE)
#define CLKCTL_GPIO_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GPIO_CLK_ENABLE, 1)
#define CLKCTL_GPIO_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GPIO_CLK_ENABLE, 0)


/*
 *  CLKCTL_TMRS_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_TMRS_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_TMRS_CLK_EN))
#define CLKCTL_TMRS_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_TMRS_CLK_EN, (value))
#define CLKCTL_TMRS_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_TMRS_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_TMRS_CLK_EN) | (value))
#define CLKCTL_TMRS_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_TMRS_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_TMRS_CLK_EN) & (~(value)))

/*
 *  CLKCTL_TMRS_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_TMRS_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_TMRS_CLK_ENABLE)
#define CLKCTL_TMRS_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_TMRS_CLK_ENABLE, 1)
#define CLKCTL_TMRS_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_TMRS_CLK_ENABLE, 0)


/*
 *  CLKCTL_AMB_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_AMB_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_AMB_CLK_EN))
#define CLKCTL_AMB_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_AMB_CLK_EN, (value))
#define CLKCTL_AMB_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_AMB_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_AMB_CLK_EN) | (value))
#define CLKCTL_AMB_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_AMB_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_AMB_CLK_EN) & (~(value)))

/*
 *  CLKCTL_AMB_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_AMB_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_AMB_CLK_ENABLE)
#define CLKCTL_AMB_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_AMB_CLK_ENABLE, 1)
#define CLKCTL_AMB_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_AMB_CLK_ENABLE, 0)


/*
 *  CLKCTL_DMA_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_DMA_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_DMA_CLK_EN))
#define CLKCTL_DMA_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_DMA_CLK_EN, (value))
#define CLKCTL_DMA_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_DMA_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_DMA_CLK_EN) | (value))
#define CLKCTL_DMA_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_DMA_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_DMA_CLK_EN) & (~(value)))

/*
 *  CLKCTL_DMA_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_DMA_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_DMA_CLK_ENABLE)
#define CLKCTL_DMA_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_DMA_CLK_ENABLE, 1)
#define CLKCTL_DMA_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_DMA_CLK_ENABLE, 0)


/*
 *  CLKCTL_I2STXFIFO_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_I2STXFIFO_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2STXFIFO_CLK_EN))
#define CLKCTL_I2STXFIFO_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2STXFIFO_CLK_EN, (value))
#define CLKCTL_I2STXFIFO_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2STXFIFO_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2STXFIFO_CLK_EN) | (value))
#define CLKCTL_I2STXFIFO_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2STXFIFO_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2STXFIFO_CLK_EN) & (~(value)))

/*
 *  CLKCTL_I2STXFIFO_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_I2STXFIFO_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_I2STXFIFO_CLK_ENABLE)
#define CLKCTL_I2STXFIFO_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_I2STXFIFO_CLK_ENABLE, 1)
#define CLKCTL_I2STXFIFO_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_I2STXFIFO_CLK_ENABLE, 0)


/*
 *  CLKCTL_I2SRXFIFO_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_I2SRXFIFO_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2SRXFIFO_CLK_EN))
#define CLKCTL_I2SRXFIFO_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2SRXFIFO_CLK_EN, (value))
#define CLKCTL_I2SRXFIFO_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2SRXFIFO_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2SRXFIFO_CLK_EN) | (value))
#define CLKCTL_I2SRXFIFO_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2SRXFIFO_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_I2SRXFIFO_CLK_EN) & (~(value)))

/*
 *  CLKCTL_I2SRXFIFO_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_I2SRXFIFO_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_I2SRXFIFO_CLK_ENABLE)
#define CLKCTL_I2SRXFIFO_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_I2SRXFIFO_CLK_ENABLE, 1)
#define CLKCTL_I2SRXFIFO_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_I2SRXFIFO_CLK_ENABLE, 0)


/*
 *  CLKCTL_GTMR_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_GTMR_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMR_CLK_EN))
#define CLKCTL_GTMR_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMR_CLK_EN, (value))
#define CLKCTL_GTMR_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMR_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMR_CLK_EN) | (value))
#define CLKCTL_GTMR_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMR_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_GTMR_CLK_EN) & (~(value)))

/*
 *  CLKCTL_GTMR_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_GTMR_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_GTMR_CLK_ENABLE)
#define CLKCTL_GTMR_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMR_CLK_ENABLE, 1)
#define CLKCTL_GTMR_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_GTMR_CLK_ENABLE, 0)


/*
 *  CLKCTL_WDOG_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_WDOG_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_WDOG_CLK_EN))
#define CLKCTL_WDOG_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_WDOG_CLK_EN, (value))
#define CLKCTL_WDOG_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_WDOG_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_WDOG_CLK_EN) | (value))
#define CLKCTL_WDOG_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_WDOG_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_WDOG_CLK_EN) & (~(value)))

/*
 *  CLKCTL_WDOG_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_WDOG_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_WDOG_CLK_ENABLE)
#define CLKCTL_WDOG_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_WDOG_CLK_ENABLE, 1)
#define CLKCTL_WDOG_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_WDOG_CLK_ENABLE, 0)


/*
 *  CLKCTL_AWDOG_DIV_VAL register macros
 ****************************************************************************************
 */
#define CLKCTL_AWDOG_DIV_VAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_AWDOG_DIV_VAL))
#define CLKCTL_AWDOG_DIV_VAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_AWDOG_DIV_VAL, (value))
#define CLKCTL_AWDOG_DIV_VAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_AWDOG_DIV_VAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_AWDOG_DIV_VAL) | (value))
#define CLKCTL_AWDOG_DIV_VAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_AWDOG_DIV_VAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_AWDOG_DIV_VAL) & (~(value)))

/*
 *  CLKCTL_AWDOG_DIV_VALUE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_AWDOG_DIV_VALUE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_AWDOG_DIV_VALUE)
#define CLKCTL_AWDOG_DIV_VALUE_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_AWDOG_DIV_VALUE, (value))


/*
 *  CLKCTL_RBUS_SYNC register macros
 ****************************************************************************************
 */
#define CLKCTL_RBUS_SYNC_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_SYNC))
#define CLKCTL_RBUS_SYNC_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_SYNC, (value))
#define CLKCTL_RBUS_SYNC_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_SYNC, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_SYNC) | (value))
#define CLKCTL_RBUS_SYNC_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_SYNC, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_SYNC) & (~(value)))

/*
 *  CLKCTL_RBUS_SYNC_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_RBUS_SYNC_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_RBUS_SYNC_VAL)
#define CLKCTL_RBUS_SYNC_VAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_RBUS_SYNC_VAL, 1)
#define CLKCTL_RBUS_SYNC_VAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_RBUS_SYNC_VAL, 0)


/*
 *  CLKCTL_RBUS_CLK_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_RBUS_CLK_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_CLK_SEL))
#define CLKCTL_RBUS_CLK_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_CLK_SEL, (value))
#define CLKCTL_RBUS_CLK_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_CLK_SEL) | (value))
#define CLKCTL_RBUS_CLK_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_CLK_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_CLK_SEL) & (~(value)))

/*
 *  CLKCTL_RBUS_CORE_CTL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_RBUS_CORE_CTL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_RBUS_CORE_CTL)
#define CLKCTL_RBUS_CORE_CTL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_RBUS_CORE_CTL, 1)
#define CLKCTL_RBUS_CORE_CTL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_RBUS_CORE_CTL, 0)

/*
 *  CLKCTL_RBUS_CLK_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_RBUS_CLK_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_RBUS_CLK_SEL_VAL)
#define CLKCTL_RBUS_CLK_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_RBUS_CLK_SEL_VAL, (value))


/*
 *  CLKCTL_RBUS_CLK_ACTUAL register macros
 ****************************************************************************************
 */
#define CLKCTL_RBUS_CLK_ACTUAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_CLK_ACTUAL))
#define CLKCTL_RBUS_CLK_ACTUAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_CLK_ACTUAL, (value))
#define CLKCTL_RBUS_CLK_ACTUAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_CLK_ACTUAL) | (value))
#define CLKCTL_RBUS_CLK_ACTUAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_CLK_ACTUAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_CLK_ACTUAL) & (~(value)))

/*
 *  CLKCTL_RBUS_CLK_ACTUAL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_RBUS_CLK_ACTUAL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_RBUS_CLK_ACTUAL_VAL)
#define CLKCTL_RBUS_CLK_ACTUAL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_RBUS_CLK_ACTUAL_VAL, (value))


/*
 *  CLKCTL_RBUS_DIV_SEL register macros
 ****************************************************************************************
 */
#define CLKCTL_RBUS_DIV_SEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_DIV_SEL))
#define CLKCTL_RBUS_DIV_SEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_DIV_SEL, (value))
#define CLKCTL_RBUS_DIV_SEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_DIV_SEL) | (value))
#define CLKCTL_RBUS_DIV_SEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_DIV_SEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_RBUS_DIV_SEL) & (~(value)))

/*
 *  CLKCTL_RBUS_DIV_SEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_RBUS_DIV_SEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_RBUS_DIV_SEL_VAL)
#define CLKCTL_RBUS_DIV_SEL_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_RBUS_DIV_SEL_VAL, (value))


/*
 *  CLKCTL_CRYPTO_CLK_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_CRYPTO_CLK_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CRYPTO_CLK_EN))
#define CLKCTL_CRYPTO_CLK_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CRYPTO_CLK_EN, (value))
#define CLKCTL_CRYPTO_CLK_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CRYPTO_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CRYPTO_CLK_EN) | (value))
#define CLKCTL_CRYPTO_CLK_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CRYPTO_CLK_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CRYPTO_CLK_EN) & (~(value)))

/*
 *  CLKCTL_CRYPTO_CLK_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CRYPTO_CLK_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CRYPTO_CLK_ENABLE)
#define CLKCTL_CRYPTO_CLK_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CRYPTO_CLK_ENABLE, 1)
#define CLKCTL_CRYPTO_CLK_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CRYPTO_CLK_ENABLE, 0)


/*
 *  CLKCTL_STCLKEN_NCO_EN register macros
 ****************************************************************************************
 */
#define CLKCTL_STCLKEN_NCO_EN_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STCLKEN_NCO_EN))
#define CLKCTL_STCLKEN_NCO_EN_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STCLKEN_NCO_EN, (value))
#define CLKCTL_STCLKEN_NCO_EN_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STCLKEN_NCO_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STCLKEN_NCO_EN) | (value))
#define CLKCTL_STCLKEN_NCO_EN_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STCLKEN_NCO_EN, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STCLKEN_NCO_EN) & (~(value)))

/*
 *  CLKCTL_STCLKEN_NCO_ENABLE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_STCLKEN_NCO_ENABLE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_STCLKEN_NCO_ENABLE)
#define CLKCTL_STCLKEN_NCO_ENABLE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_STCLKEN_NCO_ENABLE, 1)
#define CLKCTL_STCLKEN_NCO_ENABLE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_STCLKEN_NCO_ENABLE, 0)


/*
 *  CLKCTL_STCLKEN_STEP register macros
 ****************************************************************************************
 */
#define CLKCTL_STCLKEN_STEP_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STCLKEN_STEP))
#define CLKCTL_STCLKEN_STEP_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STCLKEN_STEP, (value))
#define CLKCTL_STCLKEN_STEP_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STCLKEN_STEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STCLKEN_STEP) | (value))
#define CLKCTL_STCLKEN_STEP_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STCLKEN_STEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STCLKEN_STEP) & (~(value)))

/*
 *  CLKCTL_STCLKEN_STEP_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_STCLKEN_STEP_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_STCLKEN_STEP_VAL)
#define CLKCTL_STCLKEN_STEP_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_STCLKEN_STEP_VAL, (value))


/*
 *  CLKCTL_CREQ_AIP_0 register macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP_0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_0))
#define CLKCTL_CREQ_AIP_0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_0, (value))
#define CLKCTL_CREQ_AIP_0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_0) | (value))
#define CLKCTL_CREQ_AIP_0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_0) & (~(value)))

/*
 *  CLKCTL_CREQ_AIP0_CLK_LP bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP0_CLK_LP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP0_CLK_LP)
#define CLKCTL_CREQ_AIP0_CLK_LP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP0_CLK_LP, 1)
#define CLKCTL_CREQ_AIP0_CLK_LP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP0_CLK_LP, 0)

/*
 *  CLKCTL_CREQ_AIP0_CLK_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP0_CLK_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP0_CLK_PLL)
#define CLKCTL_CREQ_AIP0_CLK_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP0_CLK_PLL, 1)
#define CLKCTL_CREQ_AIP0_CLK_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP0_CLK_PLL, 0)

/*
 *  CLKCTL_CREQ_AIP0_CLK_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP0_CLK_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP0_CLK_HS_XTAL)
#define CLKCTL_CREQ_AIP0_CLK_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP0_CLK_HS_XTAL, 1)
#define CLKCTL_CREQ_AIP0_CLK_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP0_CLK_HS_XTAL, 0)

/*
 *  CLKCTL_CREQ_AIP0_CLK_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP0_CLK_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP0_CLK_HS_RC)
#define CLKCTL_CREQ_AIP0_CLK_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP0_CLK_HS_RC, 1)
#define CLKCTL_CREQ_AIP0_CLK_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP0_CLK_HS_RC, 0)


/*
 *  CLKCTL_CREQ_AIP_1 register macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP_1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_1))
#define CLKCTL_CREQ_AIP_1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_1, (value))
#define CLKCTL_CREQ_AIP_1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_1) | (value))
#define CLKCTL_CREQ_AIP_1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_1) & (~(value)))

/*
 *  CLKCTL_CREQ_AIP1_CLK_LP bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP1_CLK_LP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP1_CLK_LP)
#define CLKCTL_CREQ_AIP1_CLK_LP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP1_CLK_LP, 1)
#define CLKCTL_CREQ_AIP1_CLK_LP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP1_CLK_LP, 0)

/*
 *  CLKCTL_CREQ_AIP1_CLK_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP1_CLK_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP1_CLK_PLL)
#define CLKCTL_CREQ_AIP1_CLK_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP1_CLK_PLL, 1)
#define CLKCTL_CREQ_AIP1_CLK_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP1_CLK_PLL, 0)

/*
 *  CLKCTL_CREQ_AIP1_CLK_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP1_CLK_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP1_CLK_HS_XTAL)
#define CLKCTL_CREQ_AIP1_CLK_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP1_CLK_HS_XTAL, 1)
#define CLKCTL_CREQ_AIP1_CLK_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP1_CLK_HS_XTAL, 0)

/*
 *  CLKCTL_CREQ_AIP1_CLK_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP1_CLK_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP1_CLK_HS_RC)
#define CLKCTL_CREQ_AIP1_CLK_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP1_CLK_HS_RC, 1)
#define CLKCTL_CREQ_AIP1_CLK_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP1_CLK_HS_RC, 0)


/*
 *  CLKCTL_CREQ_AIP_2 register macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP_2_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_2))
#define CLKCTL_CREQ_AIP_2_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_2, (value))
#define CLKCTL_CREQ_AIP_2_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_2, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_2) | (value))
#define CLKCTL_CREQ_AIP_2_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_2, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_2) & (~(value)))

/*
 *  CLKCTL_CREQ_AIP2_CLK_LP bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP2_CLK_LP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP2_CLK_LP)
#define CLKCTL_CREQ_AIP2_CLK_LP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP2_CLK_LP, 1)
#define CLKCTL_CREQ_AIP2_CLK_LP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP2_CLK_LP, 0)

/*
 *  CLKCTL_CREQ_AIP2_CLK_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP2_CLK_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP2_CLK_PLL)
#define CLKCTL_CREQ_AIP2_CLK_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP2_CLK_PLL, 1)
#define CLKCTL_CREQ_AIP2_CLK_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP2_CLK_PLL, 0)

/*
 *  CLKCTL_CREQ_AIP2_CLK_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP2_CLK_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP2_CLK_HS_XTAL)
#define CLKCTL_CREQ_AIP2_CLK_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP2_CLK_HS_XTAL, 1)
#define CLKCTL_CREQ_AIP2_CLK_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP2_CLK_HS_XTAL, 0)

/*
 *  CLKCTL_CREQ_AIP2_CLK_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP2_CLK_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP2_CLK_HS_RC)
#define CLKCTL_CREQ_AIP2_CLK_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP2_CLK_HS_RC, 1)
#define CLKCTL_CREQ_AIP2_CLK_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP2_CLK_HS_RC, 0)


/*
 *  CLKCTL_CREQ_AIP_3 register macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP_3_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_3))
#define CLKCTL_CREQ_AIP_3_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_3, (value))
#define CLKCTL_CREQ_AIP_3_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_3, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_3) | (value))
#define CLKCTL_CREQ_AIP_3_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_3, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_3) & (~(value)))

/*
 *  CLKCTL_CREQ_AIP3_CLK_LP bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP3_CLK_LP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP3_CLK_LP)
#define CLKCTL_CREQ_AIP3_CLK_LP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP3_CLK_LP, 1)
#define CLKCTL_CREQ_AIP3_CLK_LP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP3_CLK_LP, 0)

/*
 *  CLKCTL_CREQ_AIP3_CLK_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP3_CLK_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP3_CLK_PLL)
#define CLKCTL_CREQ_AIP3_CLK_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP3_CLK_PLL, 1)
#define CLKCTL_CREQ_AIP3_CLK_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP3_CLK_PLL, 0)

/*
 *  CLKCTL_CREQ_AIP3_CLK_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP3_CLK_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP3_CLK_HS_XTAL)
#define CLKCTL_CREQ_AIP3_CLK_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP3_CLK_HS_XTAL, 1)
#define CLKCTL_CREQ_AIP3_CLK_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP3_CLK_HS_XTAL, 0)

/*
 *  CLKCTL_CREQ_AIP3_CLK_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP3_CLK_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP3_CLK_HS_RC)
#define CLKCTL_CREQ_AIP3_CLK_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP3_CLK_HS_RC, 1)
#define CLKCTL_CREQ_AIP3_CLK_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP3_CLK_HS_RC, 0)


/*
 *  CLKCTL_CREQ_AIP_4 register macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP_4_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_4))
#define CLKCTL_CREQ_AIP_4_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_4, (value))
#define CLKCTL_CREQ_AIP_4_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_4, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_4) | (value))
#define CLKCTL_CREQ_AIP_4_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_4, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_AIP_4) & (~(value)))

/*
 *  CLKCTL_CREQ_AIP4_CLK_LP bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP4_CLK_LP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP4_CLK_LP)
#define CLKCTL_CREQ_AIP4_CLK_LP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP4_CLK_LP, 1)
#define CLKCTL_CREQ_AIP4_CLK_LP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP4_CLK_LP, 0)

/*
 *  CLKCTL_CREQ_AIP4_CLK_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP4_CLK_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP4_CLK_PLL)
#define CLKCTL_CREQ_AIP4_CLK_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP4_CLK_PLL, 1)
#define CLKCTL_CREQ_AIP4_CLK_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP4_CLK_PLL, 0)

/*
 *  CLKCTL_CREQ_AIP4_CLK_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP4_CLK_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP4_CLK_HS_XTAL)
#define CLKCTL_CREQ_AIP4_CLK_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP4_CLK_HS_XTAL, 1)
#define CLKCTL_CREQ_AIP4_CLK_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP4_CLK_HS_XTAL, 0)

/*
 *  CLKCTL_CREQ_AIP4_CLK_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP4_CLK_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP4_CLK_HS_RC)
#define CLKCTL_CREQ_AIP4_CLK_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP4_CLK_HS_RC, 1)
#define CLKCTL_CREQ_AIP4_CLK_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_AIP4_CLK_HS_RC, 0)


/*
 *  CLKCTL_CREQ_INVERT register macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_INVERT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_INVERT))
#define CLKCTL_CREQ_INVERT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_INVERT, (value))
#define CLKCTL_CREQ_INVERT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_INVERT, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_INVERT) | (value))
#define CLKCTL_CREQ_INVERT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_INVERT, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_INVERT) & (~(value)))

/*
 *  CLKCTL_CREQ_INVERT_CLK_LP bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_INVERT_CLK_LP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_INVERT_CLK_LP)
#define CLKCTL_CREQ_INVERT_CLK_LP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_INVERT_CLK_LP, 1)
#define CLKCTL_CREQ_INVERT_CLK_LP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_INVERT_CLK_LP, 0)

/*
 *  CLKCTL_CREQ_INVERT_CLK_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_INVERT_CLK_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_INVERT_CLK_PLL)
#define CLKCTL_CREQ_INVERT_CLK_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_INVERT_CLK_PLL, 1)
#define CLKCTL_CREQ_INVERT_CLK_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_INVERT_CLK_PLL, 0)

/*
 *  CLKCTL_CREQ_INVERT_CLK_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_INVERT_CLK_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_INVERT_CLK_HS_XTAL)
#define CLKCTL_CREQ_INVERT_CLK_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_INVERT_CLK_HS_XTAL, 1)
#define CLKCTL_CREQ_INVERT_CLK_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_INVERT_CLK_HS_XTAL, 0)

/*
 *  CLKCTL_CREQ_INVERT_CLK_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_INVERT_CLK_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_INVERT_CLK_HS_RC)
#define CLKCTL_CREQ_INVERT_CLK_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_INVERT_CLK_HS_RC, 1)
#define CLKCTL_CREQ_INVERT_CLK_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_INVERT_CLK_HS_RC, 0)


/*
 *  CLKCTL_CREQ_WCM3_DSLEEP register macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_DSLEEP_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_DSLEEP))
#define CLKCTL_CREQ_WCM3_DSLEEP_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_DSLEEP, (value))
#define CLKCTL_CREQ_WCM3_DSLEEP_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_DSLEEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_DSLEEP) | (value))
#define CLKCTL_CREQ_WCM3_DSLEEP_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_DSLEEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_DSLEEP) & (~(value)))

/*
 *  CLKCTL_CREQ_WCM3_DSLEEP_CLK_LP bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_LP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_DSLEEP_CLK_LP)
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_LP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_DSLEEP_CLK_LP, 1)
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_LP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_DSLEEP_CLK_LP, 0)

/*
 *  CLKCTL_CREQ_WCM3_DSLEEP_CLK_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_DSLEEP_CLK_PLL)
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_DSLEEP_CLK_PLL, 1)
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_DSLEEP_CLK_PLL, 0)

/*
 *  CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_XTAL)
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_XTAL, 1)
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_XTAL, 0)

/*
 *  CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_RC)
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_RC, 1)
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_RC, 0)


/*
 *  CLKCTL_CREQ_WCM3_SLEEP register macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_SLEEP_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_SLEEP))
#define CLKCTL_CREQ_WCM3_SLEEP_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_SLEEP, (value))
#define CLKCTL_CREQ_WCM3_SLEEP_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_SLEEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_SLEEP) | (value))
#define CLKCTL_CREQ_WCM3_SLEEP_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_SLEEP, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_SLEEP) & (~(value)))

/*
 *  CLKCTL_CREQ_WCM3_SLEEP_CLK_LP bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_LP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_SLEEP_CLK_LP)
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_LP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_SLEEP_CLK_LP, 1)
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_LP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_SLEEP_CLK_LP, 0)

/*
 *  CLKCTL_CREQ_WCM3_SLEEP_CLK_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_SLEEP_CLK_PLL)
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_SLEEP_CLK_PLL, 1)
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_SLEEP_CLK_PLL, 0)

/*
 *  CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_XTAL)
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_XTAL, 1)
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_XTAL, 0)

/*
 *  CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_RC)
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_RC, 1)
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_RC, 0)


/*
 *  CLKCTL_CREQ_WCM3_ACTIVE register macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_ACTIVE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_ACTIVE))
#define CLKCTL_CREQ_WCM3_ACTIVE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_ACTIVE, (value))
#define CLKCTL_CREQ_WCM3_ACTIVE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_ACTIVE, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_ACTIVE) | (value))
#define CLKCTL_CREQ_WCM3_ACTIVE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_ACTIVE, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREQ_WCM3_ACTIVE) & (~(value)))

/*
 *  CLKCTL_CREQ_WCM3_ACTIVE_CLK_LP bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_LP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_ACTIVE_CLK_LP)
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_LP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_ACTIVE_CLK_LP, 1)
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_LP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_ACTIVE_CLK_LP, 0)

/*
 *  CLKCTL_CREQ_WCM3_ACTIVE_CLK_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_ACTIVE_CLK_PLL)
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_ACTIVE_CLK_PLL, 1)
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_ACTIVE_CLK_PLL, 0)

/*
 *  CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_XTAL)
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_XTAL, 1)
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_XTAL, 0)

/*
 *  CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_RC)
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_RC, 1)
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_RC, 0)


/*
 *  CLKCTL_CSEL_CLKSEL register macros
 ****************************************************************************************
 */
#define CLKCTL_CSEL_CLKSEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CSEL_CLKSEL))
#define CLKCTL_CSEL_CLKSEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CSEL_CLKSEL, (value))
#define CLKCTL_CSEL_CLKSEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CSEL_CLKSEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CSEL_CLKSEL) | (value))
#define CLKCTL_CSEL_CLKSEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CSEL_CLKSEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CSEL_CLKSEL) & (~(value)))

/*
 *  CLKCTL_CSEL_CLKSEL_VAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CSEL_CLKSEL_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CSEL_CLKSEL_VAL)
#define CLKCTL_CSEL_CLKSEL_VAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CSEL_CLKSEL_VAL, 1)
#define CLKCTL_CSEL_CLKSEL_VAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CSEL_CLKSEL_VAL, 0)


/*
 *  CLKCTL_CREG_CLKSEL register macros
 ****************************************************************************************
 */
#define CLKCTL_CREG_CLKSEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREG_CLKSEL))
#define CLKCTL_CREG_CLKSEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREG_CLKSEL, (value))
#define CLKCTL_CREG_CLKSEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREG_CLKSEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREG_CLKSEL) | (value))
#define CLKCTL_CREG_CLKSEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREG_CLKSEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CREG_CLKSEL) & (~(value)))

/*
 *  CLKCTL_CREG_CLKSEL_WCM3CLK_EN bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREG_CLKSEL_WCM3CLK_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREG_CLKSEL_WCM3CLK_EN)
#define CLKCTL_CREG_CLKSEL_WCM3CLK_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREG_CLKSEL_WCM3CLK_EN, 1)
#define CLKCTL_CREG_CLKSEL_WCM3CLK_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREG_CLKSEL_WCM3CLK_EN, 0)

/*
 *  CLKCTL_CREG_CLKSEL_RBUS_CLK_SEL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREG_CLKSEL_RBUS_CLK_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREG_CLKSEL_RBUS_CLK_SEL)
#define CLKCTL_CREG_CLKSEL_RBUS_CLK_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREG_CLKSEL_RBUS_CLK_SEL, (value))

/*
 *  CLKCTL_CREG_CLKSEL_WCM3CLK_SEL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREG_CLKSEL_WCM3CLK_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREG_CLKSEL_WCM3CLK_SEL)
#define CLKCTL_CREG_CLKSEL_WCM3CLK_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREG_CLKSEL_WCM3CLK_SEL, (value))

/*
 *  CLKCTL_CREG_CLKSEL_ACM3CLK_SEL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CREG_CLKSEL_ACM3CLK_SEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CREG_CLKSEL_ACM3CLK_SEL)
#define CLKCTL_CREG_CLKSEL_ACM3CLK_SEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_CREG_CLKSEL_ACM3CLK_SEL, (value))


/*
 *  CLKCTL_CX_TEST register macros
 ****************************************************************************************
 */
#define CLKCTL_CX_TEST_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_CX_TEST))

/*
 *  CLKCTL_CX_CAL_LOCK_DET bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CX_CAL_LOCK_DET_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CX_CAL_LOCK_DET)

/*
 *  CLKCTL_CX_LOCK_DET bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CX_LOCK_DET_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CX_LOCK_DET)

/*
 *  CLKCTL_CX_CAL_DONE bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CX_CAL_DONE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CX_CAL_DONE)

/*
 *  CLKCTL_CX_CAL_IN_PRGS bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CX_CAL_IN_PRGS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CX_CAL_IN_PRGS)

/*
 *  CLKCTL_CX_CAL_REG_OUT bit field macros
 ****************************************************************************************
 */
#define CLKCTL_CX_CAL_REG_OUT_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_CX_CAL_REG_OUT)


/*
 *  CLKCTL_STABLE_IRQ_STATUS register macros
 ****************************************************************************************
 */
#define CLKCTL_STABLE_IRQ_STATUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STABLE_IRQ_STATUS))

/*
 *  CLKCTL_STABLE_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_STABLE_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_STABLE_HS_RC)

/*
 *  CLKCTL_STABLE_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_STABLE_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_STABLE_HS_XTAL)

/*
 *  CLKCTL_STABLE_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_STABLE_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_STABLE_PLL)


/*
 *  CLKCTL_STABLE_IRQ_MASK register macros
 ****************************************************************************************
 */
#define CLKCTL_STABLE_IRQ_MASK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STABLE_IRQ_MASK))
#define CLKCTL_STABLE_IRQ_MASK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STABLE_IRQ_MASK, (value))
#define CLKCTL_STABLE_IRQ_MASK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STABLE_IRQ_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STABLE_IRQ_MASK) | (value))
#define CLKCTL_STABLE_IRQ_MASK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STABLE_IRQ_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, CLKCTL_STABLE_IRQ_MASK) & (~(value)))

/*
 *  CLKCTL_STABLE_IRQ_MASK_HS_RC bit field macros
 ****************************************************************************************
 */
#define CLKCTL_STABLE_IRQ_MASK_HS_RC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_STABLE_IRQ_MASK_HS_RC)
#define CLKCTL_STABLE_IRQ_MASK_HS_RC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_STABLE_IRQ_MASK_HS_RC, 1)
#define CLKCTL_STABLE_IRQ_MASK_HS_RC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_STABLE_IRQ_MASK_HS_RC, 0)

/*
 *  CLKCTL_STABLE_IRQ_MASK_HS_XTAL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_STABLE_IRQ_MASK_HS_XTAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_STABLE_IRQ_MASK_HS_XTAL)
#define CLKCTL_STABLE_IRQ_MASK_HS_XTAL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_STABLE_IRQ_MASK_HS_XTAL, 1)
#define CLKCTL_STABLE_IRQ_MASK_HS_XTAL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_STABLE_IRQ_MASK_HS_XTAL, 0)

/*
 *  CLKCTL_STABLE_IRQ_MASK_PLL bit field macros
 ****************************************************************************************
 */
#define CLKCTL_STABLE_IRQ_MASK_PLL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, CLKCTL_STABLE_IRQ_MASK_PLL)
#define CLKCTL_STABLE_IRQ_MASK_PLL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_STABLE_IRQ_MASK_PLL, 1)
#define CLKCTL_STABLE_IRQ_MASK_PLL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, CLKCTL_STABLE_IRQ_MASK_PLL, 0)


#endif

