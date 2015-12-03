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
* $RCSfile: gsn_reg_clkctl_spec.h,v $
*
* Description : clock control
******************************************************************************/

#ifndef _REG_CLKCTL_H
#define _REG_CLKCTL_H

/***************************************************
 *
 *             CLKCTL
 *
 ***************************************************/


/*
 *  CLKCTL instance offsets
 ****************************************************************************************
 */
#define CLKCTL 0x40070000

/*
 *  CLKCTL_ACM3_GATE_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_ACM3_GATE_EN_OFFSETADDRESS 0x00000000  /* RW */
#define CLKCTL_ACM3_GATE_EN_BITOFFSET  0
#define CLKCTL_ACM3_GATE_EN_BITFIELDSIZE 32
#define CLKCTL_ACM3_GATE_EN_BITMASK    0xFFFFFFFF
#define CLKCTL_ACM3_GATE_EN_INIT       0x00000000
/*
 *  CLKCTL_AFC_BUSCLK_EN bit field defines
 ****************************************************************************************
 */
#define CLKCTL_AFC_BUSCLK_EN_OFFSETADDRESS      CLKCTL_ACM3_GATE_EN_OFFSETADDRESS
#define CLKCTL_AFC_BUSCLK_EN_BITOFFSET         13
#define CLKCTL_AFC_BUSCLK_EN_BITFIELDSIZE       1
#define CLKCTL_AFC_BUSCLK_EN_BITMASK            0x00002000
#define CLKCTL_AFC_BUSCLK_EN_INIT               0x0
/*
 *  CLKCTL_SMEM_BUSCLK_EN bit field defines
 ****************************************************************************************
 */
#define CLKCTL_SMEM_BUSCLK_EN_OFFSETADDRESS     CLKCTL_ACM3_GATE_EN_OFFSETADDRESS
#define CLKCTL_SMEM_BUSCLK_EN_BITOFFSET         8
#define CLKCTL_SMEM_BUSCLK_EN_BITFIELDSIZE      5
#define CLKCTL_SMEM_BUSCLK_EN_BITMASK           0x00001f00
#define CLKCTL_SMEM_BUSCLK_EN_INIT              0x0
/*
 *  CLKCTL_AGSPI_BUSCLK_EN bit field defines
 ****************************************************************************************
 */
#define CLKCTL_AGSPI_BUSCLK_EN_OFFSETADDRESS    CLKCTL_ACM3_GATE_EN_OFFSETADDRESS
#define CLKCTL_AGSPI_BUSCLK_EN_BITOFFSET        7
#define CLKCTL_AGSPI_BUSCLK_EN_BITFIELDSIZE     1
#define CLKCTL_AGSPI_BUSCLK_EN_BITMASK          0x00000080
#define CLKCTL_AGSPI_BUSCLK_EN_INIT             0x0
/*
 *  CLKCTL_SDIO_BUSCLK_EN bit field defines
 ****************************************************************************************
 */
#define CLKCTL_SDIO_BUSCLK_EN_OFFSETADDRESS     CLKCTL_ACM3_GATE_EN_OFFSETADDRESS
#define CLKCTL_SDIO_BUSCLK_EN_BITOFFSET         6
#define CLKCTL_SDIO_BUSCLK_EN_BITFIELDSIZE      1
#define CLKCTL_SDIO_BUSCLK_EN_BITMASK           0x00000040
#define CLKCTL_SDIO_BUSCLK_EN_INIT              0x0
/*
 *  CLKCTL_AGTMU_BUSCLK_EN bit field defines
 ****************************************************************************************
 */
#define CLKCTL_AGTMU_BUSCLK_EN_OFFSETADDRESS    CLKCTL_ACM3_GATE_EN_OFFSETADDRESS
#define CLKCTL_AGTMU_BUSCLK_EN_BITOFFSET        5
#define CLKCTL_AGTMU_BUSCLK_EN_BITFIELDSIZE     1
#define CLKCTL_AGTMU_BUSCLK_EN_BITMASK          0x00000020
#define CLKCTL_AGTMU_BUSCLK_EN_INIT             0x0
/*
 *  CLKCTL_ACM3_BUS_FORCE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_ACM3_BUS_FORCE_OFFSETADDRESS     CLKCTL_ACM3_GATE_EN_OFFSETADDRESS
#define CLKCTL_ACM3_BUS_FORCE_BITOFFSET         4
#define CLKCTL_ACM3_BUS_FORCE_BITFIELDSIZE      1
#define CLKCTL_ACM3_BUS_FORCE_BITMASK           0x00000010
#define CLKCTL_ACM3_BUS_FORCE_INIT              0x0
/*
 *  CLKCTL_SDIO_GATE_FORCE_EN bit field defines
 ****************************************************************************************
 */
#define CLKCTL_SDIO_GATE_FORCE_EN_OFFSETADDRESS CLKCTL_ACM3_GATE_EN_OFFSETADDRESS
#define CLKCTL_SDIO_GATE_FORCE_EN_BITOFFSET     3
#define CLKCTL_SDIO_GATE_FORCE_EN_BITFIELDSIZE  1
#define CLKCTL_SDIO_GATE_FORCE_EN_BITMASK       0x00000008
#define CLKCTL_SDIO_GATE_FORCE_EN_INIT          0x0
/*
 *  CLKCTL_ADMA_GATE_FORCE_EN bit field defines
 ****************************************************************************************
 */
#define CLKCTL_ADMA_GATE_FORCE_EN_OFFSETADDRESS CLKCTL_ACM3_GATE_EN_OFFSETADDRESS
#define CLKCTL_ADMA_GATE_FORCE_EN_BITOFFSET     2
#define CLKCTL_ADMA_GATE_FORCE_EN_BITFIELDSIZE  1
#define CLKCTL_ADMA_GATE_FORCE_EN_BITMASK       0x00000004
#define CLKCTL_ADMA_GATE_FORCE_EN_INIT          0x0
/*
 *  CLKCTL_ACM3_GATE_CTL_EN bit field defines
 ****************************************************************************************
 */
#define CLKCTL_ACM3_GATE_CTL_EN_OFFSETADDRESS   CLKCTL_ACM3_GATE_EN_OFFSETADDRESS
#define CLKCTL_ACM3_GATE_CTL_EN_BITOFFSET       1
#define CLKCTL_ACM3_GATE_CTL_EN_BITFIELDSIZE    1
#define CLKCTL_ACM3_GATE_CTL_EN_BITMASK         0x00000002
#define CLKCTL_ACM3_GATE_CTL_EN_INIT            0x0
/*
 *  CLKCTL_AFREE_GATE_CTL_EN bit field defines
 ****************************************************************************************
 */
#define CLKCTL_AFREE_GATE_CTL_EN_OFFSETADDRESS  CLKCTL_ACM3_GATE_EN_OFFSETADDRESS
#define CLKCTL_AFREE_GATE_CTL_EN_BITOFFSET      0
#define CLKCTL_AFREE_GATE_CTL_EN_BITFIELDSIZE   1
#define CLKCTL_AFREE_GATE_CTL_EN_BITMASK        0x00000001
#define CLKCTL_AFREE_GATE_CTL_EN_INIT           0x0

/*
 *  CLKCTL_CREQ_SDIO_IDLE register defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_SDIO_IDLE_OFFSETADDRESS 0x0000000c  /* RW */
#define CLKCTL_CREQ_SDIO_IDLE_BITOFFSET 0
#define CLKCTL_CREQ_SDIO_IDLE_BITFIELDSIZE 32
#define CLKCTL_CREQ_SDIO_IDLE_BITMASK  0xFFFFFFFF
#define CLKCTL_CREQ_SDIO_IDLE_INIT     0x00000000
/*
 *  CLKCTL_REQ_SDIO_IDLE_CLK_LP bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_SDIO_IDLE_CLK_LP_OFFSETADDRESS CLKCTL_CREQ_SDIO_IDLE_OFFSETADDRESS
#define CLKCTL_REQ_SDIO_IDLE_CLK_LP_BITOFFSET   3
#define CLKCTL_REQ_SDIO_IDLE_CLK_LP_BITFIELDSIZE  1
#define CLKCTL_REQ_SDIO_IDLE_CLK_LP_BITMASK     0x00000008
#define CLKCTL_REQ_SDIO_IDLE_CLK_LP_INIT        0x0
/*
 *  CLKCTL_REQ_SDIO_IDLE_CLK_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_SDIO_IDLE_CLK_PLL_OFFSETADDRESS CLKCTL_CREQ_SDIO_IDLE_OFFSETADDRESS
#define CLKCTL_REQ_SDIO_IDLE_CLK_PLL_BITOFFSET  2
#define CLKCTL_REQ_SDIO_IDLE_CLK_PLL_BITFIELDSIZE  1
#define CLKCTL_REQ_SDIO_IDLE_CLK_PLL_BITMASK    0x00000004
#define CLKCTL_REQ_SDIO_IDLE_CLK_PLL_INIT       0x0
/*
 *  CLKCTL_REQ_SDIO_IDLE_CLK_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_SDIO_IDLE_CLK_HS_XTAL_OFFSETADDRESS CLKCTL_CREQ_SDIO_IDLE_OFFSETADDRESS
#define CLKCTL_REQ_SDIO_IDLE_CLK_HS_XTAL_BITOFFSET  1
#define CLKCTL_REQ_SDIO_IDLE_CLK_HS_XTAL_BITFIELDSIZE  1
#define CLKCTL_REQ_SDIO_IDLE_CLK_HS_XTAL_BITMASK 0x00000002
#define CLKCTL_REQ_SDIO_IDLE_CLK_HS_XTAL_INIT   0x0
/*
 *  CLKCTL_REQ_SDIO_IDLE_CLK_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_SDIO_IDLE_CLK_HS_RC_OFFSETADDRESS CLKCTL_CREQ_SDIO_IDLE_OFFSETADDRESS
#define CLKCTL_REQ_SDIO_IDLE_CLK_HS_RC_BITOFFSET  0
#define CLKCTL_REQ_SDIO_IDLE_CLK_HS_RC_BITFIELDSIZE  1
#define CLKCTL_REQ_SDIO_IDLE_CLK_HS_RC_BITMASK  0x00000001
#define CLKCTL_REQ_SDIO_IDLE_CLK_HS_RC_INIT     0x0

/*
 *  CLKCTL_CREQ_SDIO_ACTIVE register defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_SDIO_ACTIVE_OFFSETADDRESS 0x00000010  /* RW */
#define CLKCTL_CREQ_SDIO_ACTIVE_BITOFFSET 0
#define CLKCTL_CREQ_SDIO_ACTIVE_BITFIELDSIZE 32
#define CLKCTL_CREQ_SDIO_ACTIVE_BITMASK 0xFFFFFFFF
#define CLKCTL_CREQ_SDIO_ACTIVE_INIT   0x00000000
/*
 *  CLKCTL_REQ_SDIO_ACTIVE_CLK_LP bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_LP_OFFSETADDRESS CLKCTL_CREQ_SDIO_ACTIVE_OFFSETADDRESS
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_LP_BITOFFSET  3
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_LP_BITFIELDSIZE  1
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_LP_BITMASK   0x00000008
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_LP_INIT      0x0
/*
 *  CLKCTL_REQ_SDIO_ACTIVE_CLK_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_PLL_OFFSETADDRESS CLKCTL_CREQ_SDIO_ACTIVE_OFFSETADDRESS
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_PLL_BITOFFSET  2
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_PLL_BITFIELDSIZE  1
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_PLL_BITMASK  0x00000004
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_PLL_INIT     0x0
/*
 *  CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_XTAL_OFFSETADDRESS CLKCTL_CREQ_SDIO_ACTIVE_OFFSETADDRESS
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_XTAL_BITOFFSET  1
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_XTAL_BITFIELDSIZE  1
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_XTAL_BITMASK 0x00000002
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_XTAL_INIT 0x0
/*
 *  CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_RC_OFFSETADDRESS CLKCTL_CREQ_SDIO_ACTIVE_OFFSETADDRESS
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_RC_BITOFFSET  0
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_RC_BITFIELDSIZE  1
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_RC_BITMASK 0x00000001
#define CLKCTL_REQ_SDIO_ACTIVE_CLK_HS_RC_INIT   0x0

/*
 *  CLKCTL_CREQ_ACM3_DSLEEP register defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_ACM3_DSLEEP_OFFSETADDRESS 0x00000014  /* RW */
#define CLKCTL_CREQ_ACM3_DSLEEP_BITOFFSET 0
#define CLKCTL_CREQ_ACM3_DSLEEP_BITFIELDSIZE 32
#define CLKCTL_CREQ_ACM3_DSLEEP_BITMASK 0xFFFFFFFF
#define CLKCTL_CREQ_ACM3_DSLEEP_INIT   0x00000000
/*
 *  CLKCTL_REQ_ACM3_DSLEEP_CLK_LP bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_LP_OFFSETADDRESS CLKCTL_CREQ_ACM3_DSLEEP_OFFSETADDRESS
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_LP_BITOFFSET  3
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_LP_BITFIELDSIZE  1
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_LP_BITMASK   0x00000008
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_LP_INIT      0x0
/*
 *  CLKCTL_REQ_ACM3_DSLEEP_CLK_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_PLL_OFFSETADDRESS CLKCTL_CREQ_ACM3_DSLEEP_OFFSETADDRESS
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_PLL_BITOFFSET  2
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_PLL_BITFIELDSIZE  1
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_PLL_BITMASK  0x00000004
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_PLL_INIT     0x0
/*
 *  CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_XTAL_OFFSETADDRESS CLKCTL_CREQ_ACM3_DSLEEP_OFFSETADDRESS
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_XTAL_BITOFFSET  1
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_XTAL_BITFIELDSIZE  1
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_XTAL_BITMASK 0x00000002
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_XTAL_INIT 0x0
/*
 *  CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_RC_OFFSETADDRESS CLKCTL_CREQ_ACM3_DSLEEP_OFFSETADDRESS
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_RC_BITOFFSET  0
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_RC_BITFIELDSIZE  1
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_RC_BITMASK 0x00000001
#define CLKCTL_REQ_ACM3_DSLEEP_CLK_HS_RC_INIT   0x0

/*
 *  CLKCTL_CREQ_ACM3_SLEEP register defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_ACM3_SLEEP_OFFSETADDRESS 0x00000018  /* RW */
#define CLKCTL_CREQ_ACM3_SLEEP_BITOFFSET 0
#define CLKCTL_CREQ_ACM3_SLEEP_BITFIELDSIZE 32
#define CLKCTL_CREQ_ACM3_SLEEP_BITMASK 0xFFFFFFFF
#define CLKCTL_CREQ_ACM3_SLEEP_INIT    0x00000000
/*
 *  CLKCTL_REQ_ACM3_SLEEP_CLK_LP bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_SLEEP_CLK_LP_OFFSETADDRESS CLKCTL_CREQ_ACM3_SLEEP_OFFSETADDRESS
#define CLKCTL_REQ_ACM3_SLEEP_CLK_LP_BITOFFSET  3
#define CLKCTL_REQ_ACM3_SLEEP_CLK_LP_BITFIELDSIZE  1
#define CLKCTL_REQ_ACM3_SLEEP_CLK_LP_BITMASK    0x00000008
#define CLKCTL_REQ_ACM3_SLEEP_CLK_LP_INIT       0x0
/*
 *  CLKCTL_REQ_ACM3_SLEEP_CLK_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_SLEEP_CLK_PLL_OFFSETADDRESS CLKCTL_CREQ_ACM3_SLEEP_OFFSETADDRESS
#define CLKCTL_REQ_ACM3_SLEEP_CLK_PLL_BITOFFSET  2
#define CLKCTL_REQ_ACM3_SLEEP_CLK_PLL_BITFIELDSIZE  1
#define CLKCTL_REQ_ACM3_SLEEP_CLK_PLL_BITMASK   0x00000004
#define CLKCTL_REQ_ACM3_SLEEP_CLK_PLL_INIT      0x0
/*
 *  CLKCTL_REQ_ACM3_SLEEP_CLK_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_SLEEP_CLK_HS_XTAL_OFFSETADDRESS CLKCTL_CREQ_ACM3_SLEEP_OFFSETADDRESS
#define CLKCTL_REQ_ACM3_SLEEP_CLK_HS_XTAL_BITOFFSET  1
#define CLKCTL_REQ_ACM3_SLEEP_CLK_HS_XTAL_BITFIELDSIZE  1
#define CLKCTL_REQ_ACM3_SLEEP_CLK_HS_XTAL_BITMASK 0x00000002
#define CLKCTL_REQ_ACM3_SLEEP_CLK_HS_XTAL_INIT  0x0
/*
 *  CLKCTL_REQ_ACM3_SLEEP_CLK_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_SLEEP_CLK_HS_RC_OFFSETADDRESS CLKCTL_CREQ_ACM3_SLEEP_OFFSETADDRESS
#define CLKCTL_REQ_ACM3_SLEEP_CLK_HS_RC_BITOFFSET  0
#define CLKCTL_REQ_ACM3_SLEEP_CLK_HS_RC_BITFIELDSIZE  1
#define CLKCTL_REQ_ACM3_SLEEP_CLK_HS_RC_BITMASK 0x00000001
#define CLKCTL_REQ_ACM3_SLEEP_CLK_HS_RC_INIT    0x0

/*
 *  CLKCTL_CREQ_ACM3_ACTIVE register defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_ACM3_ACTIVE_OFFSETADDRESS 0x0000001c  /* RW */
#define CLKCTL_CREQ_ACM3_ACTIVE_BITOFFSET 0
#define CLKCTL_CREQ_ACM3_ACTIVE_BITFIELDSIZE 32
#define CLKCTL_CREQ_ACM3_ACTIVE_BITMASK 0xFFFFFFFF
#define CLKCTL_CREQ_ACM3_ACTIVE_INIT   0x00000000
/*
 *  CLKCTL_REQ_ACM3_ACTIVE_CLK_LP bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_LP_OFFSETADDRESS CLKCTL_CREQ_ACM3_ACTIVE_OFFSETADDRESS
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_LP_BITOFFSET  3
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_LP_BITFIELDSIZE  1
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_LP_BITMASK   0x00000008
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_LP_INIT      0x0
/*
 *  CLKCTL_REQ_ACM3_ACTIVE_CLK_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_PLL_OFFSETADDRESS CLKCTL_CREQ_ACM3_ACTIVE_OFFSETADDRESS
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_PLL_BITOFFSET  2
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_PLL_BITFIELDSIZE  1
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_PLL_BITMASK  0x00000004
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_PLL_INIT     0x0
/*
 *  CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_XTAL_OFFSETADDRESS CLKCTL_CREQ_ACM3_ACTIVE_OFFSETADDRESS
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_XTAL_BITOFFSET  1
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_XTAL_BITFIELDSIZE  1
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_XTAL_BITMASK 0x00000002
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_XTAL_INIT 0x0
/*
 *  CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_RC_OFFSETADDRESS CLKCTL_CREQ_ACM3_ACTIVE_OFFSETADDRESS
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_RC_BITOFFSET  0
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_RC_BITFIELDSIZE  1
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_RC_BITMASK 0x00000001
#define CLKCTL_REQ_ACM3_ACTIVE_CLK_HS_RC_INIT   0x0

/*
 *  CLKCTL_ACM3_CLK_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_ACM3_CLK_SEL_OFFSETADDRESS 0x00000020  /* RW */
#define CLKCTL_ACM3_CLK_SEL_BITOFFSET  0
#define CLKCTL_ACM3_CLK_SEL_BITFIELDSIZE 32
#define CLKCTL_ACM3_CLK_SEL_BITMASK    0xFFFFFFFF
#define CLKCTL_ACM3_CLK_SEL_INIT       0x00000000
/*
 *  CLKCTL_ACM3_CLK_SEL_CORE_CNTL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_ACM3_CLK_SEL_CORE_CNTL_OFFSETADDRESS CLKCTL_ACM3_CLK_SEL_OFFSETADDRESS
#define CLKCTL_ACM3_CLK_SEL_CORE_CNTL_BITOFFSET  2
#define CLKCTL_ACM3_CLK_SEL_CORE_CNTL_BITFIELDSIZE  1
#define CLKCTL_ACM3_CLK_SEL_CORE_CNTL_BITMASK   0x00000004
#define CLKCTL_ACM3_CLK_SEL_CORE_CNTL_INIT      0x0
/*
 *  CLKCTL_ACM3_CLK_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_ACM3_CLK_SEL_VAL_OFFSETADDRESS   CLKCTL_ACM3_CLK_SEL_OFFSETADDRESS
#define CLKCTL_ACM3_CLK_SEL_VAL_BITOFFSET       0
#define CLKCTL_ACM3_CLK_SEL_VAL_BITFIELDSIZE    2
#define CLKCTL_ACM3_CLK_SEL_VAL_BITMASK         0x00000003
#define CLKCTL_ACM3_CLK_SEL_VAL_INIT            0x0

/*
 *  CLKCTL_ACM3_CLK_ACTUAL register defines
 ****************************************************************************************
 */
#define CLKCTL_ACM3_CLK_ACTUAL_OFFSETADDRESS 0x00000024  /* RW */
#define CLKCTL_ACM3_CLK_ACTUAL_BITOFFSET 0
#define CLKCTL_ACM3_CLK_ACTUAL_BITFIELDSIZE 32
#define CLKCTL_ACM3_CLK_ACTUAL_BITMASK 0xFFFFFFFF
#define CLKCTL_ACM3_CLK_ACTUAL_INIT    0x00000000
/*
 *  CLKCTL_ACM3_CLK_ACTUAL_CLK_LP bit field defines
 ****************************************************************************************
 */
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_LP_OFFSETADDRESS CLKCTL_ACM3_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_LP_BITOFFSET  3
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_LP_BITFIELDSIZE  1
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_LP_BITMASK   0x00000008
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_LP_INIT      0x0
/*
 *  CLKCTL_ACM3_CLK_ACTUAL_CLK_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_PLL_OFFSETADDRESS CLKCTL_ACM3_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_PLL_BITOFFSET  2
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_PLL_BITFIELDSIZE  1
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_PLL_BITMASK  0x00000004
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_PLL_INIT     0x0
/*
 *  CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_XTAL_OFFSETADDRESS CLKCTL_ACM3_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_XTAL_BITOFFSET  1
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_XTAL_BITFIELDSIZE  1
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_XTAL_BITMASK 0x00000002
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_XTAL_INIT 0x0
/*
 *  CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_RC_OFFSETADDRESS CLKCTL_ACM3_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_RC_BITOFFSET  0
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_RC_BITFIELDSIZE  1
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_RC_BITMASK 0x00000001
#define CLKCTL_ACM3_CLK_ACTUAL_CLK_HS_RC_INIT   0x0

/*
 *  CLKCTL_ACM3_DIV_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_ACM3_DIV_SEL_OFFSETADDRESS 0x00000028  /* RW */
#define CLKCTL_ACM3_DIV_SEL_BITOFFSET  0
#define CLKCTL_ACM3_DIV_SEL_BITFIELDSIZE 32
#define CLKCTL_ACM3_DIV_SEL_BITMASK    0xFFFFFFFF
#define CLKCTL_ACM3_DIV_SEL_INIT       0x00000000
/*
 *  CLKCTL_ACM3_DIV_SEL_VALUE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_ACM3_DIV_SEL_VALUE_OFFSETADDRESS CLKCTL_ACM3_DIV_SEL_OFFSETADDRESS
#define CLKCTL_ACM3_DIV_SEL_VALUE_BITOFFSET     0
#define CLKCTL_ACM3_DIV_SEL_VALUE_BITFIELDSIZE  3
#define CLKCTL_ACM3_DIV_SEL_VALUE_BITMASK       0x00000007
#define CLKCTL_ACM3_DIV_SEL_VALUE_INIT          0x0

/*
 *  CLKCTL_UART0_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_UART0_CLK_EN_OFFSETADDRESS 0x0000002c  /* RW */
#define CLKCTL_UART0_CLK_EN_BITOFFSET  0
#define CLKCTL_UART0_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_UART0_CLK_EN_BITMASK    0xFFFFFFFF
#define CLKCTL_UART0_CLK_EN_INIT       0x00000000
/*
 *  CLKCTL_UART0_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_UART0_CLK_ENABLE_OFFSETADDRESS   CLKCTL_UART0_CLK_EN_OFFSETADDRESS
#define CLKCTL_UART0_CLK_ENABLE_BITOFFSET       0
#define CLKCTL_UART0_CLK_ENABLE_BITFIELDSIZE    1
#define CLKCTL_UART0_CLK_ENABLE_BITMASK         0x00000001
#define CLKCTL_UART0_CLK_ENABLE_INIT            0x0

/*
 *  CLKCTL_UART0_CLK_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_UART0_CLK_SEL_OFFSETADDRESS 0x00000030  /* RW */
#define CLKCTL_UART0_CLK_SEL_BITOFFSET 0
#define CLKCTL_UART0_CLK_SEL_BITFIELDSIZE 32
#define CLKCTL_UART0_CLK_SEL_BITMASK   0xFFFFFFFF
#define CLKCTL_UART0_CLK_SEL_INIT      0x00000000
/*
 *  CLKCTL_UART0_CLK_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_UART0_CLK_SEL_VAL_OFFSETADDRESS  CLKCTL_UART0_CLK_SEL_OFFSETADDRESS
#define CLKCTL_UART0_CLK_SEL_VAL_BITOFFSET      0
#define CLKCTL_UART0_CLK_SEL_VAL_BITFIELDSIZE   2
#define CLKCTL_UART0_CLK_SEL_VAL_BITMASK        0x00000003
#define CLKCTL_UART0_CLK_SEL_VAL_INIT           0x0

/*
 *  CLKCTL_UART0_CLK_ACTUAL register defines
 ****************************************************************************************
 */
#define CLKCTL_UART0_CLK_ACTUAL_OFFSETADDRESS 0x00000034  /* RW */
#define CLKCTL_UART0_CLK_ACTUAL_BITOFFSET 0
#define CLKCTL_UART0_CLK_ACTUAL_BITFIELDSIZE 32
#define CLKCTL_UART0_CLK_ACTUAL_BITMASK 0xFFFFFFFF
#define CLKCTL_UART0_CLK_ACTUAL_INIT   0x00000000
/*
 *  CLKCTL_UART0_CLK_ACTUAL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_UART0_CLK_ACTUAL_VAL_OFFSETADDRESS CLKCTL_UART0_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_UART0_CLK_ACTUAL_VAL_BITOFFSET   0
#define CLKCTL_UART0_CLK_ACTUAL_VAL_BITFIELDSIZE  3
#define CLKCTL_UART0_CLK_ACTUAL_VAL_BITMASK     0x00000007
#define CLKCTL_UART0_CLK_ACTUAL_VAL_INIT        0x0

/*
 *  CLKCTL_UART0_DIV_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_UART0_DIV_SEL_OFFSETADDRESS 0x00000038  /* RW */
#define CLKCTL_UART0_DIV_SEL_BITOFFSET 0
#define CLKCTL_UART0_DIV_SEL_BITFIELDSIZE 32
#define CLKCTL_UART0_DIV_SEL_BITMASK   0xFFFFFFFF
#define CLKCTL_UART0_DIV_SEL_INIT      0x00000000
/*
 *  CLKCTL_UART0_DIV_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_UART0_DIV_SEL_VAL_OFFSETADDRESS  CLKCTL_UART0_DIV_SEL_OFFSETADDRESS
#define CLKCTL_UART0_DIV_SEL_VAL_BITOFFSET      0
#define CLKCTL_UART0_DIV_SEL_VAL_BITFIELDSIZE   3
#define CLKCTL_UART0_DIV_SEL_VAL_BITMASK        0x00000007
#define CLKCTL_UART0_DIV_SEL_VAL_INIT           0x0

/*
 *  CLKCTL_UART1_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_UART1_CLK_EN_OFFSETADDRESS 0x0000003c  /* RW */
#define CLKCTL_UART1_CLK_EN_BITOFFSET  0
#define CLKCTL_UART1_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_UART1_CLK_EN_BITMASK    0xFFFFFFFF
#define CLKCTL_UART1_CLK_EN_INIT       0x00000000
/*
 *  CLKCTL_UART1_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_UART1_CLK_ENABLE_OFFSETADDRESS   CLKCTL_UART1_CLK_EN_OFFSETADDRESS
#define CLKCTL_UART1_CLK_ENABLE_BITOFFSET       0
#define CLKCTL_UART1_CLK_ENABLE_BITFIELDSIZE    1
#define CLKCTL_UART1_CLK_ENABLE_BITMASK         0x00000001
#define CLKCTL_UART1_CLK_ENABLE_INIT            0x0

/*
 *  CLKCTL_UART1_CLK_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_UART1_CLK_SEL_OFFSETADDRESS 0x00000040  /* RW */
#define CLKCTL_UART1_CLK_SEL_BITOFFSET 0
#define CLKCTL_UART1_CLK_SEL_BITFIELDSIZE 32
#define CLKCTL_UART1_CLK_SEL_BITMASK   0xFFFFFFFF
#define CLKCTL_UART1_CLK_SEL_INIT      0x00000000
/*
 *  CLKCTL_UART1_CLK_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_UART1_CLK_SEL_VAL_OFFSETADDRESS  CLKCTL_UART1_CLK_SEL_OFFSETADDRESS
#define CLKCTL_UART1_CLK_SEL_VAL_BITOFFSET      0
#define CLKCTL_UART1_CLK_SEL_VAL_BITFIELDSIZE   2
#define CLKCTL_UART1_CLK_SEL_VAL_BITMASK        0x00000003
#define CLKCTL_UART1_CLK_SEL_VAL_INIT           0x0

/*
 *  CLKCTL_UART1_CLK_ACTUAL register defines
 ****************************************************************************************
 */
#define CLKCTL_UART1_CLK_ACTUAL_OFFSETADDRESS 0x00000044  /* RW */
#define CLKCTL_UART1_CLK_ACTUAL_BITOFFSET 0
#define CLKCTL_UART1_CLK_ACTUAL_BITFIELDSIZE 32
#define CLKCTL_UART1_CLK_ACTUAL_BITMASK 0xFFFFFFFF
#define CLKCTL_UART1_CLK_ACTUAL_INIT   0x00000000
/*
 *  CLKCTL_UART1_CLK_ACTUAL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_UART1_CLK_ACTUAL_VAL_OFFSETADDRESS CLKCTL_UART1_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_UART1_CLK_ACTUAL_VAL_BITOFFSET   0
#define CLKCTL_UART1_CLK_ACTUAL_VAL_BITFIELDSIZE  3
#define CLKCTL_UART1_CLK_ACTUAL_VAL_BITMASK     0x00000007
#define CLKCTL_UART1_CLK_ACTUAL_VAL_INIT        0x0

/*
 *  CLKCTL_UART1_DIV_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_UART1_DIV_SEL_OFFSETADDRESS 0x00000048  /* RW */
#define CLKCTL_UART1_DIV_SEL_BITOFFSET 0
#define CLKCTL_UART1_DIV_SEL_BITFIELDSIZE 32
#define CLKCTL_UART1_DIV_SEL_BITMASK   0xFFFFFFFF
#define CLKCTL_UART1_DIV_SEL_INIT      0x00000000
/*
 *  CLKCTL_UART1_DIV_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_UART1_DIV_SEL_VAL_OFFSETADDRESS  CLKCTL_UART1_DIV_SEL_OFFSETADDRESS
#define CLKCTL_UART1_DIV_SEL_VAL_BITOFFSET      0
#define CLKCTL_UART1_DIV_SEL_VAL_BITFIELDSIZE   3
#define CLKCTL_UART1_DIV_SEL_VAL_BITMASK        0x00000007
#define CLKCTL_UART1_DIV_SEL_VAL_INIT           0x0

/*
 *  CLKCTL_SSP0_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_SSP0_CLK_EN_OFFSETADDRESS 0x0000004c  /* RW */
#define CLKCTL_SSP0_CLK_EN_BITOFFSET   0
#define CLKCTL_SSP0_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_SSP0_CLK_EN_BITMASK     0xFFFFFFFF
#define CLKCTL_SSP0_CLK_EN_INIT        0x00000000
/*
 *  CLKCTL_SSP0_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_SSP0_CLK_ENABLE_OFFSETADDRESS    CLKCTL_SSP0_CLK_EN_OFFSETADDRESS
#define CLKCTL_SSP0_CLK_ENABLE_BITOFFSET        0
#define CLKCTL_SSP0_CLK_ENABLE_BITFIELDSIZE     1
#define CLKCTL_SSP0_CLK_ENABLE_BITMASK          0x00000001
#define CLKCTL_SSP0_CLK_ENABLE_INIT             0x0

/*
 *  CLKCTL_SSP0_CLK_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_SSP0_CLK_SEL_OFFSETADDRESS 0x00000050  /* RW */
#define CLKCTL_SSP0_CLK_SEL_BITOFFSET  0
#define CLKCTL_SSP0_CLK_SEL_BITFIELDSIZE 32
#define CLKCTL_SSP0_CLK_SEL_BITMASK    0xFFFFFFFF
#define CLKCTL_SSP0_CLK_SEL_INIT       0x00000000
/*
 *  CLKCTL_SSP0_CLK_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_SSP0_CLK_SEL_VAL_OFFSETADDRESS   CLKCTL_SSP0_CLK_SEL_OFFSETADDRESS
#define CLKCTL_SSP0_CLK_SEL_VAL_BITOFFSET       0
#define CLKCTL_SSP0_CLK_SEL_VAL_BITFIELDSIZE    2
#define CLKCTL_SSP0_CLK_SEL_VAL_BITMASK         0x00000003
#define CLKCTL_SSP0_CLK_SEL_VAL_INIT            0x0

/*
 *  CLKCTL_SSP0_CLK_ACTUAL register defines
 ****************************************************************************************
 */
#define CLKCTL_SSP0_CLK_ACTUAL_OFFSETADDRESS 0x00000054  /* RW */
#define CLKCTL_SSP0_CLK_ACTUAL_BITOFFSET 0
#define CLKCTL_SSP0_CLK_ACTUAL_BITFIELDSIZE 32
#define CLKCTL_SSP0_CLK_ACTUAL_BITMASK 0xFFFFFFFF
#define CLKCTL_SSP0_CLK_ACTUAL_INIT    0x00000000
/*
 *  CLKCTL_SSP0_CLK_ACTUAL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_SSP0_CLK_ACTUAL_VAL_OFFSETADDRESS CLKCTL_SSP0_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_SSP0_CLK_ACTUAL_VAL_BITOFFSET    0
#define CLKCTL_SSP0_CLK_ACTUAL_VAL_BITFIELDSIZE  3
#define CLKCTL_SSP0_CLK_ACTUAL_VAL_BITMASK      0x00000007
#define CLKCTL_SSP0_CLK_ACTUAL_VAL_INIT         0x0

/*
 *  CLKCTL_SSP0_DIV_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_SSP0_DIV_SEL_OFFSETADDRESS 0x00000058  /* RW */
#define CLKCTL_SSP0_DIV_SEL_BITOFFSET  0
#define CLKCTL_SSP0_DIV_SEL_BITFIELDSIZE 32
#define CLKCTL_SSP0_DIV_SEL_BITMASK    0xFFFFFFFF
#define CLKCTL_SSP0_DIV_SEL_INIT       0x00000000
/*
 *  CLKCTL_SSP0_DIV_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_SSP0_DIV_SEL_VAL_OFFSETADDRESS   CLKCTL_SSP0_DIV_SEL_OFFSETADDRESS
#define CLKCTL_SSP0_DIV_SEL_VAL_BITOFFSET       0
#define CLKCTL_SSP0_DIV_SEL_VAL_BITFIELDSIZE    3
#define CLKCTL_SSP0_DIV_SEL_VAL_BITMASK         0x00000007
#define CLKCTL_SSP0_DIV_SEL_VAL_INIT            0x0

/*
 *  CLKCTL_SSP1_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_SSP1_CLK_EN_OFFSETADDRESS 0x0000005c  /* RW */
#define CLKCTL_SSP1_CLK_EN_BITOFFSET   0
#define CLKCTL_SSP1_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_SSP1_CLK_EN_BITMASK     0xFFFFFFFF
#define CLKCTL_SSP1_CLK_EN_INIT        0x00000000
/*
 *  CLKCTL_SSP1_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_SSP1_CLK_ENABLE_OFFSETADDRESS    CLKCTL_SSP1_CLK_EN_OFFSETADDRESS
#define CLKCTL_SSP1_CLK_ENABLE_BITOFFSET        0
#define CLKCTL_SSP1_CLK_ENABLE_BITFIELDSIZE     1
#define CLKCTL_SSP1_CLK_ENABLE_BITMASK          0x00000001
#define CLKCTL_SSP1_CLK_ENABLE_INIT             0x0

/*
 *  CLKCTL_SSP1_CLK_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_SSP1_CLK_SEL_OFFSETADDRESS 0x00000060  /* RW */
#define CLKCTL_SSP1_CLK_SEL_BITOFFSET  0
#define CLKCTL_SSP1_CLK_SEL_BITFIELDSIZE 32
#define CLKCTL_SSP1_CLK_SEL_BITMASK    0xFFFFFFFF
#define CLKCTL_SSP1_CLK_SEL_INIT       0x00000000
/*
 *  CLKCTL_SSP1_CLK_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_SSP1_CLK_SEL_VAL_OFFSETADDRESS   CLKCTL_SSP1_CLK_SEL_OFFSETADDRESS
#define CLKCTL_SSP1_CLK_SEL_VAL_BITOFFSET       0
#define CLKCTL_SSP1_CLK_SEL_VAL_BITFIELDSIZE    2
#define CLKCTL_SSP1_CLK_SEL_VAL_BITMASK         0x00000003
#define CLKCTL_SSP1_CLK_SEL_VAL_INIT            0x0

/*
 *  CLKCTL_SSP1_CLK_ACTUAL register defines
 ****************************************************************************************
 */
#define CLKCTL_SSP1_CLK_ACTUAL_OFFSETADDRESS 0x00000064  /* RW */
#define CLKCTL_SSP1_CLK_ACTUAL_BITOFFSET 0
#define CLKCTL_SSP1_CLK_ACTUAL_BITFIELDSIZE 32
#define CLKCTL_SSP1_CLK_ACTUAL_BITMASK 0xFFFFFFFF
#define CLKCTL_SSP1_CLK_ACTUAL_INIT    0x00000000
/*
 *  CLKCTL_SSP1_CLK_ACTUAL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_SSP1_CLK_ACTUAL_VAL_OFFSETADDRESS CLKCTL_SSP1_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_SSP1_CLK_ACTUAL_VAL_BITOFFSET    0
#define CLKCTL_SSP1_CLK_ACTUAL_VAL_BITFIELDSIZE  3
#define CLKCTL_SSP1_CLK_ACTUAL_VAL_BITMASK      0x00000007
#define CLKCTL_SSP1_CLK_ACTUAL_VAL_INIT         0x0

/*
 *  CLKCTL_SSP1_DIV_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_SSP1_DIV_SEL_OFFSETADDRESS 0x00000068  /* RW */
#define CLKCTL_SSP1_DIV_SEL_BITOFFSET  0
#define CLKCTL_SSP1_DIV_SEL_BITFIELDSIZE 32
#define CLKCTL_SSP1_DIV_SEL_BITMASK    0xFFFFFFFF
#define CLKCTL_SSP1_DIV_SEL_INIT       0x00000000
/*
 *  CLKCTL_SSP1_DIV_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_SSP1_DIV_SEL_VAL_OFFSETADDRESS   CLKCTL_SSP1_DIV_SEL_OFFSETADDRESS
#define CLKCTL_SSP1_DIV_SEL_VAL_BITOFFSET       0
#define CLKCTL_SSP1_DIV_SEL_VAL_BITFIELDSIZE    3
#define CLKCTL_SSP1_DIV_SEL_VAL_BITMASK         0x00000007
#define CLKCTL_SSP1_DIV_SEL_VAL_INIT            0x0

/*
 *  CLKCTL_I2C_NCO_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_I2C_NCO_EN_OFFSETADDRESS 0x0000006c  /* RW */
#define CLKCTL_I2C_NCO_EN_BITOFFSET    0
#define CLKCTL_I2C_NCO_EN_BITFIELDSIZE 32
#define CLKCTL_I2C_NCO_EN_BITMASK      0xFFFFFFFF
#define CLKCTL_I2C_NCO_EN_INIT         0x00000000
/*
 *  CLKCTL_I2C_NCO_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_I2C_NCO_ENABLE_OFFSETADDRESS     CLKCTL_I2C_NCO_EN_OFFSETADDRESS
#define CLKCTL_I2C_NCO_ENABLE_BITOFFSET         0
#define CLKCTL_I2C_NCO_ENABLE_BITFIELDSIZE      1
#define CLKCTL_I2C_NCO_ENABLE_BITMASK           0x00000001
#define CLKCTL_I2C_NCO_ENABLE_INIT              0x0

/*
 *  CLKCTL_I2C_CLK_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_I2C_CLK_SEL_OFFSETADDRESS 0x00000070  /* RW */
#define CLKCTL_I2C_CLK_SEL_BITOFFSET   0
#define CLKCTL_I2C_CLK_SEL_BITFIELDSIZE 32
#define CLKCTL_I2C_CLK_SEL_BITMASK     0xFFFFFFFF
#define CLKCTL_I2C_CLK_SEL_INIT        0x00000000
/*
 *  CLKCTL_I2C_CLK_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_I2C_CLK_SEL_VAL_OFFSETADDRESS    CLKCTL_I2C_CLK_SEL_OFFSETADDRESS
#define CLKCTL_I2C_CLK_SEL_VAL_BITOFFSET        0
#define CLKCTL_I2C_CLK_SEL_VAL_BITFIELDSIZE     2
#define CLKCTL_I2C_CLK_SEL_VAL_BITMASK          0x00000003
#define CLKCTL_I2C_CLK_SEL_VAL_INIT             0x0

/*
 *  CLKCTL_I2C_CLK_ACTUAL register defines
 ****************************************************************************************
 */
#define CLKCTL_I2C_CLK_ACTUAL_OFFSETADDRESS 0x00000074  /* RW */
#define CLKCTL_I2C_CLK_ACTUAL_BITOFFSET 0
#define CLKCTL_I2C_CLK_ACTUAL_BITFIELDSIZE 32
#define CLKCTL_I2C_CLK_ACTUAL_BITMASK  0xFFFFFFFF
#define CLKCTL_I2C_CLK_ACTUAL_INIT     0x00000000
/*
 *  CLKCTL_I2C_CLK_ACTUAL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_I2C_CLK_ACTUAL_VAL_OFFSETADDRESS CLKCTL_I2C_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_I2C_CLK_ACTUAL_VAL_BITOFFSET     0
#define CLKCTL_I2C_CLK_ACTUAL_VAL_BITFIELDSIZE  3
#define CLKCTL_I2C_CLK_ACTUAL_VAL_BITMASK       0x00000007
#define CLKCTL_I2C_CLK_ACTUAL_VAL_INIT          0x0

/*
 *  CLKCTL_I2C_STEP register defines
 ****************************************************************************************
 */
#define CLKCTL_I2C_STEP_OFFSETADDRESS  0x00000078  /* RW */
#define CLKCTL_I2C_STEP_BITOFFSET      0
#define CLKCTL_I2C_STEP_BITFIELDSIZE   32
#define CLKCTL_I2C_STEP_BITMASK        0xFFFFFFFF
#define CLKCTL_I2C_STEP_INIT           0x00000000
/*
 *  CLKCTL_I2C_STEP_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_I2C_STEP_VAL_OFFSETADDRESS       CLKCTL_I2C_STEP_OFFSETADDRESS
#define CLKCTL_I2C_STEP_VAL_BITOFFSET           0
#define CLKCTL_I2C_STEP_VAL_BITFIELDSIZE       26
#define CLKCTL_I2C_STEP_VAL_BITMASK             0x03ffffff
#define CLKCTL_I2C_STEP_VAL_INIT                0x0

/*
 *  CLKCTL_I2S_NCO_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_I2S_NCO_EN_OFFSETADDRESS 0x0000007c  /* RW */
#define CLKCTL_I2S_NCO_EN_BITOFFSET    0
#define CLKCTL_I2S_NCO_EN_BITFIELDSIZE 32
#define CLKCTL_I2S_NCO_EN_BITMASK      0xFFFFFFFF
#define CLKCTL_I2S_NCO_EN_INIT         0x00000000
/*
 *  CLKCTL_I2S_NCO_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_I2S_NCO_ENABLE_OFFSETADDRESS     CLKCTL_I2S_NCO_EN_OFFSETADDRESS
#define CLKCTL_I2S_NCO_ENABLE_BITOFFSET         0
#define CLKCTL_I2S_NCO_ENABLE_BITFIELDSIZE      1
#define CLKCTL_I2S_NCO_ENABLE_BITMASK           0x00000001
#define CLKCTL_I2S_NCO_ENABLE_INIT              0x0

/*
 *  CLKCTL_I2S_CLK_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_I2S_CLK_SEL_OFFSETADDRESS 0x00000080  /* RW */
#define CLKCTL_I2S_CLK_SEL_BITOFFSET   0
#define CLKCTL_I2S_CLK_SEL_BITFIELDSIZE 32
#define CLKCTL_I2S_CLK_SEL_BITMASK     0xFFFFFFFF
#define CLKCTL_I2S_CLK_SEL_INIT        0x00000000
/*
 *  CLKCTL_I2S_CLK_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_I2S_CLK_SEL_VAL_OFFSETADDRESS    CLKCTL_I2S_CLK_SEL_OFFSETADDRESS
#define CLKCTL_I2S_CLK_SEL_VAL_BITOFFSET        0
#define CLKCTL_I2S_CLK_SEL_VAL_BITFIELDSIZE     2
#define CLKCTL_I2S_CLK_SEL_VAL_BITMASK          0x00000003
#define CLKCTL_I2S_CLK_SEL_VAL_INIT             0x0

/*
 *  CLKCTL_I2S_CLK_ACTUAL register defines
 ****************************************************************************************
 */
#define CLKCTL_I2S_CLK_ACTUAL_OFFSETADDRESS 0x00000084  /* RW */
#define CLKCTL_I2S_CLK_ACTUAL_BITOFFSET 0
#define CLKCTL_I2S_CLK_ACTUAL_BITFIELDSIZE 32
#define CLKCTL_I2S_CLK_ACTUAL_BITMASK  0xFFFFFFFF
#define CLKCTL_I2S_CLK_ACTUAL_INIT     0x00000000
/*
 *  CLKCTL_I2S_CLK_ACTUAL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_I2S_CLK_ACTUAL_VAL_OFFSETADDRESS CLKCTL_I2S_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_I2S_CLK_ACTUAL_VAL_BITOFFSET     0
#define CLKCTL_I2S_CLK_ACTUAL_VAL_BITFIELDSIZE  3
#define CLKCTL_I2S_CLK_ACTUAL_VAL_BITMASK       0x00000007
#define CLKCTL_I2S_CLK_ACTUAL_VAL_INIT          0x0

/*
 *  CLKCTL_I2S_STEP register defines
 ****************************************************************************************
 */
#define CLKCTL_I2S_STEP_OFFSETADDRESS  0x00000088  /* RW */
#define CLKCTL_I2S_STEP_BITOFFSET      0
#define CLKCTL_I2S_STEP_BITFIELDSIZE   32
#define CLKCTL_I2S_STEP_BITMASK        0xFFFFFFFF
#define CLKCTL_I2S_STEP_INIT           0x00000000
/*
 *  CLKCTL_I2S_STEP_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_I2S_STEP_VAL_OFFSETADDRESS       CLKCTL_I2S_STEP_OFFSETADDRESS
#define CLKCTL_I2S_STEP_VAL_BITOFFSET           0
#define CLKCTL_I2S_STEP_VAL_BITFIELDSIZE       26
#define CLKCTL_I2S_STEP_VAL_BITMASK             0x03ffffff
#define CLKCTL_I2S_STEP_VAL_INIT                0x0

/*
 *  CLKCTL_OTP0_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_OTP0_CLK_EN_OFFSETADDRESS 0x0000008c  /* RW */
#define CLKCTL_OTP0_CLK_EN_BITOFFSET   0
#define CLKCTL_OTP0_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_OTP0_CLK_EN_BITMASK     0xFFFFFFFF
#define CLKCTL_OTP0_CLK_EN_INIT        0x00000000
/*
 *  CLKCTL_OTP0_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_OTP0_CLK_ENABLE_OFFSETADDRESS    CLKCTL_OTP0_CLK_EN_OFFSETADDRESS
#define CLKCTL_OTP0_CLK_ENABLE_BITOFFSET        0
#define CLKCTL_OTP0_CLK_ENABLE_BITFIELDSIZE     1
#define CLKCTL_OTP0_CLK_ENABLE_BITMASK          0x00000001
#define CLKCTL_OTP0_CLK_ENABLE_INIT             0x0

/*
 *  CLKCTL_OTP0_CLK_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_OTP0_CLK_SEL_OFFSETADDRESS 0x00000090  /* RW */
#define CLKCTL_OTP0_CLK_SEL_BITOFFSET  0
#define CLKCTL_OTP0_CLK_SEL_BITFIELDSIZE 32
#define CLKCTL_OTP0_CLK_SEL_BITMASK    0xFFFFFFFF
#define CLKCTL_OTP0_CLK_SEL_INIT       0x00000000
/*
 *  CLKCTL_OTP0_CLK_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_OTP0_CLK_SEL_VAL_OFFSETADDRESS   CLKCTL_OTP0_CLK_SEL_OFFSETADDRESS
#define CLKCTL_OTP0_CLK_SEL_VAL_BITOFFSET       0
#define CLKCTL_OTP0_CLK_SEL_VAL_BITFIELDSIZE    2
#define CLKCTL_OTP0_CLK_SEL_VAL_BITMASK         0x00000003
#define CLKCTL_OTP0_CLK_SEL_VAL_INIT            0x0

/*
 *  CLKCTL_OTP0_CLK_ACTUAL register defines
 ****************************************************************************************
 */
#define CLKCTL_OTP0_CLK_ACTUAL_OFFSETADDRESS 0x00000094  /* RW */
#define CLKCTL_OTP0_CLK_ACTUAL_BITOFFSET 0
#define CLKCTL_OTP0_CLK_ACTUAL_BITFIELDSIZE 32
#define CLKCTL_OTP0_CLK_ACTUAL_BITMASK 0xFFFFFFFF
#define CLKCTL_OTP0_CLK_ACTUAL_INIT    0x00000000
/*
 *  CLKCTL_OTP0_CLK_ACTUAL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_OTP0_CLK_ACTUAL_VAL_OFFSETADDRESS CLKCTL_OTP0_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_OTP0_CLK_ACTUAL_VAL_BITOFFSET    0
#define CLKCTL_OTP0_CLK_ACTUAL_VAL_BITFIELDSIZE  3
#define CLKCTL_OTP0_CLK_ACTUAL_VAL_BITMASK      0x00000007
#define CLKCTL_OTP0_CLK_ACTUAL_VAL_INIT         0x0

/*
 *  CLKCTL_OTP0_DIV_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_OTP0_DIV_SEL_OFFSETADDRESS 0x00000098  /* RW */
#define CLKCTL_OTP0_DIV_SEL_BITOFFSET  0
#define CLKCTL_OTP0_DIV_SEL_BITFIELDSIZE 32
#define CLKCTL_OTP0_DIV_SEL_BITMASK    0xFFFFFFFF
#define CLKCTL_OTP0_DIV_SEL_INIT       0x00000000
/*
 *  CLKCTL_OTP0_DIV_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_OTP0_DIV_SEL_VAL_OFFSETADDRESS   CLKCTL_OTP0_DIV_SEL_OFFSETADDRESS
#define CLKCTL_OTP0_DIV_SEL_VAL_BITOFFSET       0
#define CLKCTL_OTP0_DIV_SEL_VAL_BITFIELDSIZE    3
#define CLKCTL_OTP0_DIV_SEL_VAL_BITMASK         0x00000007
#define CLKCTL_OTP0_DIV_SEL_VAL_INIT            0x0

/*
 *  CLKCTL_OTP1_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_OTP1_CLK_EN_OFFSETADDRESS 0x0000009c  /* RW */
#define CLKCTL_OTP1_CLK_EN_BITOFFSET   0
#define CLKCTL_OTP1_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_OTP1_CLK_EN_BITMASK     0xFFFFFFFF
#define CLKCTL_OTP1_CLK_EN_INIT        0x00000000
/*
 *  CLKCTL_OTP1_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_OTP1_CLK_ENABLE_OFFSETADDRESS    CLKCTL_OTP1_CLK_EN_OFFSETADDRESS
#define CLKCTL_OTP1_CLK_ENABLE_BITOFFSET        0
#define CLKCTL_OTP1_CLK_ENABLE_BITFIELDSIZE     1
#define CLKCTL_OTP1_CLK_ENABLE_BITMASK          0x00000001
#define CLKCTL_OTP1_CLK_ENABLE_INIT             0x0

/*
 *  CLKCTL_OTP1_CLK_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_OTP1_CLK_SEL_OFFSETADDRESS 0x000000a0  /* RW */
#define CLKCTL_OTP1_CLK_SEL_BITOFFSET  0
#define CLKCTL_OTP1_CLK_SEL_BITFIELDSIZE 32
#define CLKCTL_OTP1_CLK_SEL_BITMASK    0xFFFFFFFF
#define CLKCTL_OTP1_CLK_SEL_INIT       0x00000000
/*
 *  CLKCTL_OTP1_CLK_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_OTP1_CLK_SEL_VAL_OFFSETADDRESS   CLKCTL_OTP1_CLK_SEL_OFFSETADDRESS
#define CLKCTL_OTP1_CLK_SEL_VAL_BITOFFSET       0
#define CLKCTL_OTP1_CLK_SEL_VAL_BITFIELDSIZE    2
#define CLKCTL_OTP1_CLK_SEL_VAL_BITMASK         0x00000003
#define CLKCTL_OTP1_CLK_SEL_VAL_INIT            0x0

/*
 *  CLKCTL_OTP1_CLK_ACTUAL register defines
 ****************************************************************************************
 */
#define CLKCTL_OTP1_CLK_ACTUAL_OFFSETADDRESS 0x000000a4  /* RW */
#define CLKCTL_OTP1_CLK_ACTUAL_BITOFFSET 0
#define CLKCTL_OTP1_CLK_ACTUAL_BITFIELDSIZE 32
#define CLKCTL_OTP1_CLK_ACTUAL_BITMASK 0xFFFFFFFF
#define CLKCTL_OTP1_CLK_ACTUAL_INIT    0x00000000
/*
 *  CLKCTL_OTP1_CLK_ACTUAL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_OTP1_CLK_ACTUAL_VAL_OFFSETADDRESS CLKCTL_OTP1_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_OTP1_CLK_ACTUAL_VAL_BITOFFSET    0
#define CLKCTL_OTP1_CLK_ACTUAL_VAL_BITFIELDSIZE  3
#define CLKCTL_OTP1_CLK_ACTUAL_VAL_BITMASK      0x00000007
#define CLKCTL_OTP1_CLK_ACTUAL_VAL_INIT         0x0

/*
 *  CLKCTL_OTP1_DIV_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_OTP1_DIV_SEL_OFFSETADDRESS 0x000000a8  /* RW */
#define CLKCTL_OTP1_DIV_SEL_BITOFFSET  0
#define CLKCTL_OTP1_DIV_SEL_BITFIELDSIZE 32
#define CLKCTL_OTP1_DIV_SEL_BITMASK    0xFFFFFFFF
#define CLKCTL_OTP1_DIV_SEL_INIT       0x00000000
/*
 *  CLKCTL_OTP1_DIV_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_OTP1_DIV_SEL_VAL_OFFSETADDRESS   CLKCTL_OTP1_DIV_SEL_OFFSETADDRESS
#define CLKCTL_OTP1_DIV_SEL_VAL_BITOFFSET       0
#define CLKCTL_OTP1_DIV_SEL_VAL_BITFIELDSIZE    3
#define CLKCTL_OTP1_DIV_SEL_VAL_BITMASK         0x00000007
#define CLKCTL_OTP1_DIV_SEL_VAL_INIT            0x0

/*
 *  CLKCTL_FIF_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_FIF_CLK_EN_OFFSETADDRESS 0x000000ac  /* RW */
#define CLKCTL_FIF_CLK_EN_BITOFFSET    0
#define CLKCTL_FIF_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_FIF_CLK_EN_BITMASK      0xFFFFFFFF
#define CLKCTL_FIF_CLK_EN_INIT         0x00000000
/*
 *  CLKCTL_FIF_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_FIF_CLK_ENABLE_OFFSETADDRESS     CLKCTL_FIF_CLK_EN_OFFSETADDRESS
#define CLKCTL_FIF_CLK_ENABLE_BITOFFSET         0
#define CLKCTL_FIF_CLK_ENABLE_BITFIELDSIZE      1
#define CLKCTL_FIF_CLK_ENABLE_BITMASK           0x00000001
#define CLKCTL_FIF_CLK_ENABLE_INIT              0x0

/*
 *  CLKCTL_FIF_CLK_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_FIF_CLK_SEL_OFFSETADDRESS 0x000000b0  /* RW */
#define CLKCTL_FIF_CLK_SEL_BITOFFSET   0
#define CLKCTL_FIF_CLK_SEL_BITFIELDSIZE 32
#define CLKCTL_FIF_CLK_SEL_BITMASK     0xFFFFFFFF
#define CLKCTL_FIF_CLK_SEL_INIT        0x00000000
/*
 *  CLKCTL_FIF_CLK_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_FIF_CLK_SEL_VAL_OFFSETADDRESS    CLKCTL_FIF_CLK_SEL_OFFSETADDRESS
#define CLKCTL_FIF_CLK_SEL_VAL_BITOFFSET        0
#define CLKCTL_FIF_CLK_SEL_VAL_BITFIELDSIZE     2
#define CLKCTL_FIF_CLK_SEL_VAL_BITMASK          0x00000003
#define CLKCTL_FIF_CLK_SEL_VAL_INIT             0x0

/*
 *  CLKCTL_FIF_CLK_ACTUAL register defines
 ****************************************************************************************
 */
#define CLKCTL_FIF_CLK_ACTUAL_OFFSETADDRESS 0x000000b4  /* RW */
#define CLKCTL_FIF_CLK_ACTUAL_BITOFFSET 0
#define CLKCTL_FIF_CLK_ACTUAL_BITFIELDSIZE 32
#define CLKCTL_FIF_CLK_ACTUAL_BITMASK  0xFFFFFFFF
#define CLKCTL_FIF_CLK_ACTUAL_INIT     0x00000000
/*
 *  CLKCTL_FIF_CLK_ACTUAL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_FIF_CLK_ACTUAL_VAL_OFFSETADDRESS CLKCTL_FIF_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_FIF_CLK_ACTUAL_VAL_BITOFFSET     0
#define CLKCTL_FIF_CLK_ACTUAL_VAL_BITFIELDSIZE  3
#define CLKCTL_FIF_CLK_ACTUAL_VAL_BITMASK       0x00000007
#define CLKCTL_FIF_CLK_ACTUAL_VAL_INIT          0x0

/*
 *  CLKCTL_FIF_DIV_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_FIF_DIV_SEL_OFFSETADDRESS 0x000000b8  /* RW */
#define CLKCTL_FIF_DIV_SEL_BITOFFSET   0
#define CLKCTL_FIF_DIV_SEL_BITFIELDSIZE 32
#define CLKCTL_FIF_DIV_SEL_BITMASK     0xFFFFFFFF
#define CLKCTL_FIF_DIV_SEL_INIT        0x00000000
/*
 *  CLKCTL_FIF_DIV_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_FIF_DIV_SEL_VAL_OFFSETADDRESS    CLKCTL_FIF_DIV_SEL_OFFSETADDRESS
#define CLKCTL_FIF_DIV_SEL_VAL_BITOFFSET        0
#define CLKCTL_FIF_DIV_SEL_VAL_BITFIELDSIZE     3
#define CLKCTL_FIF_DIV_SEL_VAL_BITMASK          0x00000007
#define CLKCTL_FIF_DIV_SEL_VAL_INIT             0x0

/*
 *  CLKCTL_PWM_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_PWM_CLK_EN_OFFSETADDRESS 0x000000bc  /* RW */
#define CLKCTL_PWM_CLK_EN_BITOFFSET    0
#define CLKCTL_PWM_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_PWM_CLK_EN_BITMASK      0xFFFFFFFF
#define CLKCTL_PWM_CLK_EN_INIT         0x00000000
/*
 *  CLKCTL_PWM_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_PWM_CLK_ENABLE_OFFSETADDRESS     CLKCTL_PWM_CLK_EN_OFFSETADDRESS
#define CLKCTL_PWM_CLK_ENABLE_BITOFFSET         0
#define CLKCTL_PWM_CLK_ENABLE_BITFIELDSIZE      1
#define CLKCTL_PWM_CLK_ENABLE_BITMASK           0x00000001
#define CLKCTL_PWM_CLK_ENABLE_INIT              0x0

/*
 *  CLKCTL_PWM_CLK_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_PWM_CLK_SEL_OFFSETADDRESS 0x000000c0  /* RW */
#define CLKCTL_PWM_CLK_SEL_BITOFFSET   0
#define CLKCTL_PWM_CLK_SEL_BITFIELDSIZE 32
#define CLKCTL_PWM_CLK_SEL_BITMASK     0xFFFFFFFF
#define CLKCTL_PWM_CLK_SEL_INIT        0x00000000
/*
 *  CLKCTL_PWM_CLK_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_PWM_CLK_SEL_VAL_OFFSETADDRESS    CLKCTL_PWM_CLK_SEL_OFFSETADDRESS
#define CLKCTL_PWM_CLK_SEL_VAL_BITOFFSET        0
#define CLKCTL_PWM_CLK_SEL_VAL_BITFIELDSIZE     2
#define CLKCTL_PWM_CLK_SEL_VAL_BITMASK          0x00000003
#define CLKCTL_PWM_CLK_SEL_VAL_INIT             0x0

/*
 *  CLKCTL_PWM_CLK_ACTUAL register defines
 ****************************************************************************************
 */
#define CLKCTL_PWM_CLK_ACTUAL_OFFSETADDRESS 0x000000c4  /* RW */
#define CLKCTL_PWM_CLK_ACTUAL_BITOFFSET 0
#define CLKCTL_PWM_CLK_ACTUAL_BITFIELDSIZE 32
#define CLKCTL_PWM_CLK_ACTUAL_BITMASK  0xFFFFFFFF
#define CLKCTL_PWM_CLK_ACTUAL_INIT     0x00000000
/*
 *  CLKCTL_PWM_CLK_ACTUAL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_PWM_CLK_ACTUAL_VAL_OFFSETADDRESS CLKCTL_PWM_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_PWM_CLK_ACTUAL_VAL_BITOFFSET     0
#define CLKCTL_PWM_CLK_ACTUAL_VAL_BITFIELDSIZE  3
#define CLKCTL_PWM_CLK_ACTUAL_VAL_BITMASK       0x00000007
#define CLKCTL_PWM_CLK_ACTUAL_VAL_INIT          0x0

/*
 *  CLKCTL_PWM_DIV_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_PWM_DIV_SEL_OFFSETADDRESS 0x000000c8  /* RW */
#define CLKCTL_PWM_DIV_SEL_BITOFFSET   0
#define CLKCTL_PWM_DIV_SEL_BITFIELDSIZE 32
#define CLKCTL_PWM_DIV_SEL_BITMASK     0xFFFFFFFF
#define CLKCTL_PWM_DIV_SEL_INIT        0x00000000
/*
 *  CLKCTL_PWM_DIV_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_PWM_DIV_SEL_VAL_OFFSETADDRESS    CLKCTL_PWM_DIV_SEL_OFFSETADDRESS
#define CLKCTL_PWM_DIV_SEL_VAL_BITOFFSET        0
#define CLKCTL_PWM_DIV_SEL_VAL_BITFIELDSIZE     3
#define CLKCTL_PWM_DIV_SEL_VAL_BITMASK          0x00000007
#define CLKCTL_PWM_DIV_SEL_VAL_INIT             0x0

/*
 *  CLKCTL_SDADCDAC_NCO_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_SDADCDAC_NCO_EN_OFFSETADDRESS 0x000000cc  /* RW */
#define CLKCTL_SDADCDAC_NCO_EN_BITOFFSET 0
#define CLKCTL_SDADCDAC_NCO_EN_BITFIELDSIZE 32
#define CLKCTL_SDADCDAC_NCO_EN_BITMASK 0xFFFFFFFF
#define CLKCTL_SDADCDAC_NCO_EN_INIT    0x00000000
/*
 *  CLKCTL_SDADCDAC_NCO_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_SDADCDAC_NCO_ENABLE_OFFSETADDRESS CLKCTL_SDADCDAC_NCO_EN_OFFSETADDRESS
#define CLKCTL_SDADCDAC_NCO_ENABLE_BITOFFSET    0
#define CLKCTL_SDADCDAC_NCO_ENABLE_BITFIELDSIZE  1
#define CLKCTL_SDADCDAC_NCO_ENABLE_BITMASK      0x00000001
#define CLKCTL_SDADCDAC_NCO_ENABLE_INIT         0x0

/*
 *  CLKCTL_SDADCDAC_CLK_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_SDADCDAC_CLK_SEL_OFFSETADDRESS 0x000000d0  /* RW */
#define CLKCTL_SDADCDAC_CLK_SEL_BITOFFSET 0
#define CLKCTL_SDADCDAC_CLK_SEL_BITFIELDSIZE 32
#define CLKCTL_SDADCDAC_CLK_SEL_BITMASK 0xFFFFFFFF
#define CLKCTL_SDADCDAC_CLK_SEL_INIT   0x00000000
/*
 *  CLKCTL_SDADCDAC_CLK_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_SDADCDAC_CLK_SEL_VAL_OFFSETADDRESS CLKCTL_SDADCDAC_CLK_SEL_OFFSETADDRESS
#define CLKCTL_SDADCDAC_CLK_SEL_VAL_BITOFFSET   0
#define CLKCTL_SDADCDAC_CLK_SEL_VAL_BITFIELDSIZE  2
#define CLKCTL_SDADCDAC_CLK_SEL_VAL_BITMASK     0x00000003
#define CLKCTL_SDADCDAC_CLK_SEL_VAL_INIT        0x0

/*
 *  CLKCTL_SDADCDAC_CLK_ACTUAL register defines
 ****************************************************************************************
 */
#define CLKCTL_SDADCDAC_CLK_ACTUAL_OFFSETADDRESS 0x000000d4  /* RW */
#define CLKCTL_SDADCDAC_CLK_ACTUAL_BITOFFSET 0
#define CLKCTL_SDADCDAC_CLK_ACTUAL_BITFIELDSIZE 32
#define CLKCTL_SDADCDAC_CLK_ACTUAL_BITMASK 0xFFFFFFFF
#define CLKCTL_SDADCDAC_CLK_ACTUAL_INIT 0x00000000
/*
 *  CLKCTL_SDADCDAC_CLK_ACTUAL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_SDADCDAC_CLK_ACTUAL_VAL_OFFSETADDRESS CLKCTL_SDADCDAC_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_SDADCDAC_CLK_ACTUAL_VAL_BITOFFSET  0
#define CLKCTL_SDADCDAC_CLK_ACTUAL_VAL_BITFIELDSIZE  3
#define CLKCTL_SDADCDAC_CLK_ACTUAL_VAL_BITMASK  0x00000007
#define CLKCTL_SDADCDAC_CLK_ACTUAL_VAL_INIT     0x0

/*
 *  CLKCTL_SDADCDAC_STEP register defines
 ****************************************************************************************
 */
#define CLKCTL_SDADCDAC_STEP_OFFSETADDRESS 0x000000d8  /* RW */
#define CLKCTL_SDADCDAC_STEP_BITOFFSET 0
#define CLKCTL_SDADCDAC_STEP_BITFIELDSIZE 32
#define CLKCTL_SDADCDAC_STEP_BITMASK   0xFFFFFFFF
#define CLKCTL_SDADCDAC_STEP_INIT      0x00000000
/*
 *  CLKCTL_SDADCDAC_STEP_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_SDADCDAC_STEP_VAL_OFFSETADDRESS  CLKCTL_SDADCDAC_STEP_OFFSETADDRESS
#define CLKCTL_SDADCDAC_STEP_VAL_BITOFFSET      0
#define CLKCTL_SDADCDAC_STEP_VAL_BITFIELDSIZE  26
#define CLKCTL_SDADCDAC_STEP_VAL_BITMASK        0x03ffffff
#define CLKCTL_SDADCDAC_STEP_VAL_INIT           0x0

/*
 *  CLKCTL_CREQ_AADC_ACTIVE register defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AADC_ACTIVE_OFFSETADDRESS 0x000000dc  /* RW */
#define CLKCTL_CREQ_AADC_ACTIVE_BITOFFSET 0
#define CLKCTL_CREQ_AADC_ACTIVE_BITFIELDSIZE 32
#define CLKCTL_CREQ_AADC_ACTIVE_BITMASK 0xFFFFFFFF
#define CLKCTL_CREQ_AADC_ACTIVE_INIT   0x00000000
/*
 *  CLKCTL_REQ_AADC_ACTIVE_CLK_LP bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_AADC_ACTIVE_CLK_LP_OFFSETADDRESS CLKCTL_CREQ_AADC_ACTIVE_OFFSETADDRESS
#define CLKCTL_REQ_AADC_ACTIVE_CLK_LP_BITOFFSET  3
#define CLKCTL_REQ_AADC_ACTIVE_CLK_LP_BITFIELDSIZE  1
#define CLKCTL_REQ_AADC_ACTIVE_CLK_LP_BITMASK   0x00000008
#define CLKCTL_REQ_AADC_ACTIVE_CLK_LP_INIT      0x0
/*
 *  CLKCTL_REQ_AADC_ACTIVE_CLK_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_AADC_ACTIVE_CLK_PLL_OFFSETADDRESS CLKCTL_CREQ_AADC_ACTIVE_OFFSETADDRESS
#define CLKCTL_REQ_AADC_ACTIVE_CLK_PLL_BITOFFSET  2
#define CLKCTL_REQ_AADC_ACTIVE_CLK_PLL_BITFIELDSIZE  1
#define CLKCTL_REQ_AADC_ACTIVE_CLK_PLL_BITMASK  0x00000004
#define CLKCTL_REQ_AADC_ACTIVE_CLK_PLL_INIT     0x0
/*
 *  CLKCTL_REQ_AADC_ACTIVE_CLK_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_AADC_ACTIVE_CLK_HS_XTAL_OFFSETADDRESS CLKCTL_CREQ_AADC_ACTIVE_OFFSETADDRESS
#define CLKCTL_REQ_AADC_ACTIVE_CLK_HS_XTAL_BITOFFSET  1
#define CLKCTL_REQ_AADC_ACTIVE_CLK_HS_XTAL_BITFIELDSIZE  1
#define CLKCTL_REQ_AADC_ACTIVE_CLK_HS_XTAL_BITMASK 0x00000002
#define CLKCTL_REQ_AADC_ACTIVE_CLK_HS_XTAL_INIT 0x0
/*
 *  CLKCTL_REQ_AADC_ACTIVE_CLK_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_REQ_AADC_ACTIVE_CLK_HS_RC_OFFSETADDRESS CLKCTL_CREQ_AADC_ACTIVE_OFFSETADDRESS
#define CLKCTL_REQ_AADC_ACTIVE_CLK_HS_RC_BITOFFSET  0
#define CLKCTL_REQ_AADC_ACTIVE_CLK_HS_RC_BITFIELDSIZE  1
#define CLKCTL_REQ_AADC_ACTIVE_CLK_HS_RC_BITMASK 0x00000001
#define CLKCTL_REQ_AADC_ACTIVE_CLK_HS_RC_INIT   0x0

/*
 *  CLKCTL_ADC_NCO_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_ADC_NCO_EN_OFFSETADDRESS 0x000000e0  /* RW */
#define CLKCTL_ADC_NCO_EN_BITOFFSET    0
#define CLKCTL_ADC_NCO_EN_BITFIELDSIZE 32
#define CLKCTL_ADC_NCO_EN_BITMASK      0xFFFFFFFF
#define CLKCTL_ADC_NCO_EN_INIT         0x00000000
/*
 *  CLKCTL_AADC_NCO_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_AADC_NCO_ENABLE_OFFSETADDRESS    CLKCTL_ADC_NCO_EN_OFFSETADDRESS
#define CLKCTL_AADC_NCO_ENABLE_BITOFFSET        0
#define CLKCTL_AADC_NCO_ENABLE_BITFIELDSIZE     1
#define CLKCTL_AADC_NCO_ENABLE_BITMASK          0x00000001
#define CLKCTL_AADC_NCO_ENABLE_INIT             0x0

/*
 *  CLKCTL_ADC_CLK_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_ADC_CLK_SEL_OFFSETADDRESS 0x000000e4  /* RW */
#define CLKCTL_ADC_CLK_SEL_BITOFFSET   0
#define CLKCTL_ADC_CLK_SEL_BITFIELDSIZE 32
#define CLKCTL_ADC_CLK_SEL_BITMASK     0xFFFFFFFF
#define CLKCTL_ADC_CLK_SEL_INIT        0x00000000
/*
 *  CLKCTL_ADC_CLK_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_ADC_CLK_SEL_VAL_OFFSETADDRESS    CLKCTL_ADC_CLK_SEL_OFFSETADDRESS
#define CLKCTL_ADC_CLK_SEL_VAL_BITOFFSET        0
#define CLKCTL_ADC_CLK_SEL_VAL_BITFIELDSIZE     2
#define CLKCTL_ADC_CLK_SEL_VAL_BITMASK          0x00000003
#define CLKCTL_ADC_CLK_SEL_VAL_INIT             0x0

/*
 *  CLKCTL_ADC_CLK_ACTUAL register defines
 ****************************************************************************************
 */
#define CLKCTL_ADC_CLK_ACTUAL_OFFSETADDRESS 0x000000e8  /* RW */
#define CLKCTL_ADC_CLK_ACTUAL_BITOFFSET 0
#define CLKCTL_ADC_CLK_ACTUAL_BITFIELDSIZE 32
#define CLKCTL_ADC_CLK_ACTUAL_BITMASK  0xFFFFFFFF
#define CLKCTL_ADC_CLK_ACTUAL_INIT     0x00000000
/*
 *  CLKCTL_ADC_CLK_ACTUAL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_ADC_CLK_ACTUAL_VAL_OFFSETADDRESS CLKCTL_ADC_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_ADC_CLK_ACTUAL_VAL_BITOFFSET     0
#define CLKCTL_ADC_CLK_ACTUAL_VAL_BITFIELDSIZE  3
#define CLKCTL_ADC_CLK_ACTUAL_VAL_BITMASK       0x00000007
#define CLKCTL_ADC_CLK_ACTUAL_VAL_INIT          0x0

/*
 *  CLKCTL_ADC_STEP register defines
 ****************************************************************************************
 */
#define CLKCTL_ADC_STEP_OFFSETADDRESS  0x000000ec  /* RW */
#define CLKCTL_ADC_STEP_BITOFFSET      0
#define CLKCTL_ADC_STEP_BITFIELDSIZE   32
#define CLKCTL_ADC_STEP_BITMASK        0xFFFFFFFF
#define CLKCTL_ADC_STEP_INIT           0x00000000
/*
 *  CLKCTL_ADC_STEP_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_ADC_STEP_VAL_OFFSETADDRESS       CLKCTL_ADC_STEP_OFFSETADDRESS
#define CLKCTL_ADC_STEP_VAL_BITOFFSET           0
#define CLKCTL_ADC_STEP_VAL_BITFIELDSIZE       26
#define CLKCTL_ADC_STEP_VAL_BITMASK             0x03ffffff
#define CLKCTL_ADC_STEP_VAL_INIT                0x0

/*
 *  CLKCTL_GTMU_NCO_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_NCO_EN_OFFSETADDRESS 0x000000f0  /* RW */
#define CLKCTL_GTMU_NCO_EN_BITOFFSET   0
#define CLKCTL_GTMU_NCO_EN_BITFIELDSIZE 32
#define CLKCTL_GTMU_NCO_EN_BITMASK     0xFFFFFFFF
#define CLKCTL_GTMU_NCO_EN_INIT        0x00000000
/*
 *  CLKCTL_GTMU_AUX_NCO_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_AUX_NCO_ENABLE_OFFSETADDRESS CLKCTL_GTMU_NCO_EN_OFFSETADDRESS
#define CLKCTL_GTMU_AUX_NCO_ENABLE_BITOFFSET    1
#define CLKCTL_GTMU_AUX_NCO_ENABLE_BITFIELDSIZE  1
#define CLKCTL_GTMU_AUX_NCO_ENABLE_BITMASK      0x00000002
#define CLKCTL_GTMU_AUX_NCO_ENABLE_INIT         0x0
/*
 *  CLKCTL_GTMU_NCO_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_NCO_ENABLE_OFFSETADDRESS    CLKCTL_GTMU_NCO_EN_OFFSETADDRESS
#define CLKCTL_GTMU_NCO_ENABLE_BITOFFSET        0
#define CLKCTL_GTMU_NCO_ENABLE_BITFIELDSIZE     1
#define CLKCTL_GTMU_NCO_ENABLE_BITMASK          0x00000001
#define CLKCTL_GTMU_NCO_ENABLE_INIT             0x0

/*
 *  CLKCTL_GTMU_CLK_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_CLK_SEL_OFFSETADDRESS 0x000000f4  /* RW */
#define CLKCTL_GTMU_CLK_SEL_BITOFFSET  0
#define CLKCTL_GTMU_CLK_SEL_BITFIELDSIZE 32
#define CLKCTL_GTMU_CLK_SEL_BITMASK    0xFFFFFFFF
#define CLKCTL_GTMU_CLK_SEL_INIT       0x00000000
/*
 *  CLKCTL_GTMU_GPIO_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_GPIO_SEL_VAL_OFFSETADDRESS  CLKCTL_GTMU_CLK_SEL_OFFSETADDRESS
#define CLKCTL_GTMU_GPIO_SEL_VAL_BITOFFSET      2
#define CLKCTL_GTMU_GPIO_SEL_VAL_BITFIELDSIZE   1
#define CLKCTL_GTMU_GPIO_SEL_VAL_BITMASK        0x00000004
#define CLKCTL_GTMU_GPIO_SEL_VAL_INIT           0x0
/*
 *  CLKCTL_GTMU_CLK_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_CLK_SEL_VAL_OFFSETADDRESS   CLKCTL_GTMU_CLK_SEL_OFFSETADDRESS
#define CLKCTL_GTMU_CLK_SEL_VAL_BITOFFSET       0
#define CLKCTL_GTMU_CLK_SEL_VAL_BITFIELDSIZE    2
#define CLKCTL_GTMU_CLK_SEL_VAL_BITMASK         0x00000003
#define CLKCTL_GTMU_CLK_SEL_VAL_INIT            0x0

/*
 *  CLKCTL_GTMU_CLK_ACTUAL register defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_CLK_ACTUAL_OFFSETADDRESS 0x000000f8  /* RW */
#define CLKCTL_GTMU_CLK_ACTUAL_BITOFFSET 0
#define CLKCTL_GTMU_CLK_ACTUAL_BITFIELDSIZE 32
#define CLKCTL_GTMU_CLK_ACTUAL_BITMASK 0xFFFFFFFF
#define CLKCTL_GTMU_CLK_ACTUAL_INIT    0x00000000
/*
 *  CLKCTL_GTMU_CLK_ACTUAL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_CLK_ACTUAL_VAL_OFFSETADDRESS CLKCTL_GTMU_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_GTMU_CLK_ACTUAL_VAL_BITOFFSET    0
#define CLKCTL_GTMU_CLK_ACTUAL_VAL_BITFIELDSIZE  4
#define CLKCTL_GTMU_CLK_ACTUAL_VAL_BITMASK      0x0000000f
#define CLKCTL_GTMU_CLK_ACTUAL_VAL_INIT         0x0

/*
 *  CLKCTL_GTMU_STEP register defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_STEP_OFFSETADDRESS 0x000000fc  /* RW */
#define CLKCTL_GTMU_STEP_BITOFFSET     0
#define CLKCTL_GTMU_STEP_BITFIELDSIZE  32
#define CLKCTL_GTMU_STEP_BITMASK       0xFFFFFFFF
#define CLKCTL_GTMU_STEP_INIT          0x00000000
/*
 *  CLKCTL_GTMU_STEP_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_STEP_VAL_OFFSETADDRESS      CLKCTL_GTMU_STEP_OFFSETADDRESS
#define CLKCTL_GTMU_STEP_VAL_BITOFFSET          0
#define CLKCTL_GTMU_STEP_VAL_BITFIELDSIZE      26
#define CLKCTL_GTMU_STEP_VAL_BITMASK            0x03ffffff
#define CLKCTL_GTMU_STEP_VAL_INIT               0x0

/*
 *  CLKCTL_GTMU_SELECT0 register defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_SELECT0_OFFSETADDRESS 0x00000100  /* RW */
#define CLKCTL_GTMU_SELECT0_BITOFFSET  0
#define CLKCTL_GTMU_SELECT0_BITFIELDSIZE 32
#define CLKCTL_GTMU_SELECT0_BITMASK    0xFFFFFFFF
#define CLKCTL_GTMU_SELECT0_INIT       0x00000000
/*
 *  CLKCTL_GTMU_SELECT0_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_SELECT0_VAL_OFFSETADDRESS   CLKCTL_GTMU_SELECT0_OFFSETADDRESS
#define CLKCTL_GTMU_SELECT0_VAL_BITOFFSET       0
#define CLKCTL_GTMU_SELECT0_VAL_BITFIELDSIZE    6
#define CLKCTL_GTMU_SELECT0_VAL_BITMASK         0x0000003f
#define CLKCTL_GTMU_SELECT0_VAL_INIT            0x0

/*
 *  CLKCTL_GTMU_CLK_SEL1 register defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_CLK_SEL1_OFFSETADDRESS 0x00000104  /* RW */
#define CLKCTL_GTMU_CLK_SEL1_BITOFFSET 0
#define CLKCTL_GTMU_CLK_SEL1_BITFIELDSIZE 32
#define CLKCTL_GTMU_CLK_SEL1_BITMASK   0xFFFFFFFF
#define CLKCTL_GTMU_CLK_SEL1_INIT      0x00000000
/*
 *  CLKCTL_GTMU_GPIO_SEL1_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_GPIO_SEL1_VAL_OFFSETADDRESS CLKCTL_GTMU_CLK_SEL1_OFFSETADDRESS
#define CLKCTL_GTMU_GPIO_SEL1_VAL_BITOFFSET     2
#define CLKCTL_GTMU_GPIO_SEL1_VAL_BITFIELDSIZE  1
#define CLKCTL_GTMU_GPIO_SEL1_VAL_BITMASK       0x00000004
#define CLKCTL_GTMU_GPIO_SEL1_VAL_INIT          0x0
/*
 *  CLKCTL_GTMU_CLK_SEL1_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_CLK_SEL1_VAL_OFFSETADDRESS  CLKCTL_GTMU_CLK_SEL1_OFFSETADDRESS
#define CLKCTL_GTMU_CLK_SEL1_VAL_BITOFFSET      0
#define CLKCTL_GTMU_CLK_SEL1_VAL_BITFIELDSIZE   2
#define CLKCTL_GTMU_CLK_SEL1_VAL_BITMASK        0x00000003
#define CLKCTL_GTMU_CLK_SEL1_VAL_INIT           0x0

/*
 *  CLKCTL_GTMU_CLK_ACTUAL1 register defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_CLK_ACTUAL1_OFFSETADDRESS 0x00000108  /* RW */
#define CLKCTL_GTMU_CLK_ACTUAL1_BITOFFSET 0
#define CLKCTL_GTMU_CLK_ACTUAL1_BITFIELDSIZE 32
#define CLKCTL_GTMU_CLK_ACTUAL1_BITMASK 0xFFFFFFFF
#define CLKCTL_GTMU_CLK_ACTUAL1_INIT   0x00000000
/*
 *  CLKCTL_GTMU_CLK_ACTUAL1_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_CLK_ACTUAL1_VAL_OFFSETADDRESS CLKCTL_GTMU_CLK_ACTUAL1_OFFSETADDRESS
#define CLKCTL_GTMU_CLK_ACTUAL1_VAL_BITOFFSET   0
#define CLKCTL_GTMU_CLK_ACTUAL1_VAL_BITFIELDSIZE  4
#define CLKCTL_GTMU_CLK_ACTUAL1_VAL_BITMASK     0x0000000f
#define CLKCTL_GTMU_CLK_ACTUAL1_VAL_INIT        0x0

/*
 *  CLKCTL_GTMU_STEP1 register defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_STEP1_OFFSETADDRESS 0x0000010c  /* RW */
#define CLKCTL_GTMU_STEP1_BITOFFSET    0
#define CLKCTL_GTMU_STEP1_BITFIELDSIZE 32
#define CLKCTL_GTMU_STEP1_BITMASK      0xFFFFFFFF
#define CLKCTL_GTMU_STEP1_INIT         0x00000000
/*
 *  CLKCTL_GTMU_STEP1_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_STEP1_VAL_OFFSETADDRESS     CLKCTL_GTMU_STEP1_OFFSETADDRESS
#define CLKCTL_GTMU_STEP1_VAL_BITOFFSET         0
#define CLKCTL_GTMU_STEP1_VAL_BITFIELDSIZE     26
#define CLKCTL_GTMU_STEP1_VAL_BITMASK           0x03ffffff
#define CLKCTL_GTMU_STEP1_VAL_INIT              0x0

/*
 *  CLKCTL_GTMU_SELECT1 register defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_SELECT1_OFFSETADDRESS 0x00000110  /* RW */
#define CLKCTL_GTMU_SELECT1_BITOFFSET  0
#define CLKCTL_GTMU_SELECT1_BITFIELDSIZE 32
#define CLKCTL_GTMU_SELECT1_BITMASK    0xFFFFFFFF
#define CLKCTL_GTMU_SELECT1_INIT       0x00000000
/*
 *  CLKCTL_GTMU_SELECT1_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_GTMU_SELECT1_VAL_OFFSETADDRESS   CLKCTL_GTMU_SELECT1_OFFSETADDRESS
#define CLKCTL_GTMU_SELECT1_VAL_BITOFFSET       0
#define CLKCTL_GTMU_SELECT1_VAL_BITFIELDSIZE    6
#define CLKCTL_GTMU_SELECT1_VAL_BITMASK         0x0000003f
#define CLKCTL_GTMU_SELECT1_VAL_INIT            0x0

/*
 *  CLKCTL_BUS_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_BUS_CLK_EN_OFFSETADDRESS 0x00000114  /* RW */
#define CLKCTL_BUS_CLK_EN_BITOFFSET    0
#define CLKCTL_BUS_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_BUS_CLK_EN_BITMASK      0xFFFFFFFF
#define CLKCTL_BUS_CLK_EN_INIT         0x00000000
/*
 *  CLKCTL_BUS_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_BUS_CLK_ENABLE_OFFSETADDRESS     CLKCTL_BUS_CLK_EN_OFFSETADDRESS
#define CLKCTL_BUS_CLK_ENABLE_BITOFFSET         0
#define CLKCTL_BUS_CLK_ENABLE_BITFIELDSIZE      1
#define CLKCTL_BUS_CLK_ENABLE_BITMASK           0x00000001
#define CLKCTL_BUS_CLK_ENABLE_INIT              0x0

/*
 *  CLKCTL_GPIO_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_GPIO_CLK_EN_OFFSETADDRESS 0x00000118  /* RW */
#define CLKCTL_GPIO_CLK_EN_BITOFFSET   0
#define CLKCTL_GPIO_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_GPIO_CLK_EN_BITMASK     0xFFFFFFFF
#define CLKCTL_GPIO_CLK_EN_INIT        0x00000000
/*
 *  CLKCTL_GPIO_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_GPIO_CLK_ENABLE_OFFSETADDRESS    CLKCTL_GPIO_CLK_EN_OFFSETADDRESS
#define CLKCTL_GPIO_CLK_ENABLE_BITOFFSET        0
#define CLKCTL_GPIO_CLK_ENABLE_BITFIELDSIZE     1
#define CLKCTL_GPIO_CLK_ENABLE_BITMASK          0x00000001
#define CLKCTL_GPIO_CLK_ENABLE_INIT             0x0

/*
 *  CLKCTL_TMRS_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_TMRS_CLK_EN_OFFSETADDRESS 0x0000011c  /* RW */
#define CLKCTL_TMRS_CLK_EN_BITOFFSET   0
#define CLKCTL_TMRS_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_TMRS_CLK_EN_BITMASK     0xFFFFFFFF
#define CLKCTL_TMRS_CLK_EN_INIT        0x00000000
/*
 *  CLKCTL_TMRS_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_TMRS_CLK_ENABLE_OFFSETADDRESS    CLKCTL_TMRS_CLK_EN_OFFSETADDRESS
#define CLKCTL_TMRS_CLK_ENABLE_BITOFFSET        0
#define CLKCTL_TMRS_CLK_ENABLE_BITFIELDSIZE     1
#define CLKCTL_TMRS_CLK_ENABLE_BITMASK          0x00000001
#define CLKCTL_TMRS_CLK_ENABLE_INIT             0x0

/*
 *  CLKCTL_AMB_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_AMB_CLK_EN_OFFSETADDRESS 0x00000120  /* RW */
#define CLKCTL_AMB_CLK_EN_BITOFFSET    0
#define CLKCTL_AMB_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_AMB_CLK_EN_BITMASK      0xFFFFFFFF
#define CLKCTL_AMB_CLK_EN_INIT         0x00000000
/*
 *  CLKCTL_AMB_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_AMB_CLK_ENABLE_OFFSETADDRESS     CLKCTL_AMB_CLK_EN_OFFSETADDRESS
#define CLKCTL_AMB_CLK_ENABLE_BITOFFSET         0
#define CLKCTL_AMB_CLK_ENABLE_BITFIELDSIZE      1
#define CLKCTL_AMB_CLK_ENABLE_BITMASK           0x00000001
#define CLKCTL_AMB_CLK_ENABLE_INIT              0x0

/*
 *  CLKCTL_DMA_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_DMA_CLK_EN_OFFSETADDRESS 0x00000124  /* RW */
#define CLKCTL_DMA_CLK_EN_BITOFFSET    0
#define CLKCTL_DMA_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_DMA_CLK_EN_BITMASK      0xFFFFFFFF
#define CLKCTL_DMA_CLK_EN_INIT         0x00000000
/*
 *  CLKCTL_DMA_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_DMA_CLK_ENABLE_OFFSETADDRESS     CLKCTL_DMA_CLK_EN_OFFSETADDRESS
#define CLKCTL_DMA_CLK_ENABLE_BITOFFSET         0
#define CLKCTL_DMA_CLK_ENABLE_BITFIELDSIZE      1
#define CLKCTL_DMA_CLK_ENABLE_BITMASK           0x00000001
#define CLKCTL_DMA_CLK_ENABLE_INIT              0x0

/*
 *  CLKCTL_I2STXFIFO_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_I2STXFIFO_CLK_EN_OFFSETADDRESS 0x00000128  /* RW */
#define CLKCTL_I2STXFIFO_CLK_EN_BITOFFSET 0
#define CLKCTL_I2STXFIFO_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_I2STXFIFO_CLK_EN_BITMASK 0xFFFFFFFF
#define CLKCTL_I2STXFIFO_CLK_EN_INIT   0x00000000
/*
 *  CLKCTL_I2STXFIFO_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_I2STXFIFO_CLK_ENABLE_OFFSETADDRESS CLKCTL_I2STXFIFO_CLK_EN_OFFSETADDRESS
#define CLKCTL_I2STXFIFO_CLK_ENABLE_BITOFFSET   0
#define CLKCTL_I2STXFIFO_CLK_ENABLE_BITFIELDSIZE  1
#define CLKCTL_I2STXFIFO_CLK_ENABLE_BITMASK     0x00000001
#define CLKCTL_I2STXFIFO_CLK_ENABLE_INIT        0x0

/*
 *  CLKCTL_I2SRXFIFO_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_I2SRXFIFO_CLK_EN_OFFSETADDRESS 0x0000012c  /* RW */
#define CLKCTL_I2SRXFIFO_CLK_EN_BITOFFSET 0
#define CLKCTL_I2SRXFIFO_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_I2SRXFIFO_CLK_EN_BITMASK 0xFFFFFFFF
#define CLKCTL_I2SRXFIFO_CLK_EN_INIT   0x00000000
/*
 *  CLKCTL_I2SRXFIFO_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_I2SRXFIFO_CLK_ENABLE_OFFSETADDRESS CLKCTL_I2SRXFIFO_CLK_EN_OFFSETADDRESS
#define CLKCTL_I2SRXFIFO_CLK_ENABLE_BITOFFSET   0
#define CLKCTL_I2SRXFIFO_CLK_ENABLE_BITFIELDSIZE  1
#define CLKCTL_I2SRXFIFO_CLK_ENABLE_BITMASK     0x00000001
#define CLKCTL_I2SRXFIFO_CLK_ENABLE_INIT        0x0

/*
 *  CLKCTL_GTMR_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_GTMR_CLK_EN_OFFSETADDRESS 0x00000130  /* RW */
#define CLKCTL_GTMR_CLK_EN_BITOFFSET   0
#define CLKCTL_GTMR_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_GTMR_CLK_EN_BITMASK     0xFFFFFFFF
#define CLKCTL_GTMR_CLK_EN_INIT        0x00000000
/*
 *  CLKCTL_GTMR_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_GTMR_CLK_ENABLE_OFFSETADDRESS    CLKCTL_GTMR_CLK_EN_OFFSETADDRESS
#define CLKCTL_GTMR_CLK_ENABLE_BITOFFSET        0
#define CLKCTL_GTMR_CLK_ENABLE_BITFIELDSIZE     1
#define CLKCTL_GTMR_CLK_ENABLE_BITMASK          0x00000001
#define CLKCTL_GTMR_CLK_ENABLE_INIT             0x0

/*
 *  CLKCTL_WDOG_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_WDOG_CLK_EN_OFFSETADDRESS 0x00000134  /* RW */
#define CLKCTL_WDOG_CLK_EN_BITOFFSET   0
#define CLKCTL_WDOG_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_WDOG_CLK_EN_BITMASK     0xFFFFFFFF
#define CLKCTL_WDOG_CLK_EN_INIT        0x00000000
/*
 *  CLKCTL_WDOG_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_WDOG_CLK_ENABLE_OFFSETADDRESS    CLKCTL_WDOG_CLK_EN_OFFSETADDRESS
#define CLKCTL_WDOG_CLK_ENABLE_BITOFFSET        0
#define CLKCTL_WDOG_CLK_ENABLE_BITFIELDSIZE     1
#define CLKCTL_WDOG_CLK_ENABLE_BITMASK          0x00000001
#define CLKCTL_WDOG_CLK_ENABLE_INIT             0x0

/*
 *  CLKCTL_AWDOG_DIV_VAL register defines
 ****************************************************************************************
 */
#define CLKCTL_AWDOG_DIV_VAL_OFFSETADDRESS 0x00000138  /* RW */
#define CLKCTL_AWDOG_DIV_VAL_BITOFFSET 0
#define CLKCTL_AWDOG_DIV_VAL_BITFIELDSIZE 32
#define CLKCTL_AWDOG_DIV_VAL_BITMASK   0xFFFFFFFF
#define CLKCTL_AWDOG_DIV_VAL_INIT      0x00000000
/*
 *  CLKCTL_AWDOG_DIV_VALUE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_AWDOG_DIV_VALUE_OFFSETADDRESS    CLKCTL_AWDOG_DIV_VAL_OFFSETADDRESS
#define CLKCTL_AWDOG_DIV_VALUE_BITOFFSET        0
#define CLKCTL_AWDOG_DIV_VALUE_BITFIELDSIZE    16
#define CLKCTL_AWDOG_DIV_VALUE_BITMASK          0x0000ffff
#define CLKCTL_AWDOG_DIV_VALUE_INIT             0x0

/*
 *  CLKCTL_RBUS_SYNC register defines
 ****************************************************************************************
 */
#define CLKCTL_RBUS_SYNC_OFFSETADDRESS 0x0000013c  /* RW */
#define CLKCTL_RBUS_SYNC_BITOFFSET     0
#define CLKCTL_RBUS_SYNC_BITFIELDSIZE  32
#define CLKCTL_RBUS_SYNC_BITMASK       0xFFFFFFFF
#define CLKCTL_RBUS_SYNC_INIT          0x00000000
/*
 *  CLKCTL_RBUS_SYNC_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_RBUS_SYNC_VAL_OFFSETADDRESS      CLKCTL_RBUS_SYNC_OFFSETADDRESS
#define CLKCTL_RBUS_SYNC_VAL_BITOFFSET          0
#define CLKCTL_RBUS_SYNC_VAL_BITFIELDSIZE       1
#define CLKCTL_RBUS_SYNC_VAL_BITMASK            0x00000001
#define CLKCTL_RBUS_SYNC_VAL_INIT               0x0

/*
 *  CLKCTL_RBUS_CLK_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_RBUS_CLK_SEL_OFFSETADDRESS 0x00000140  /* RW */
#define CLKCTL_RBUS_CLK_SEL_BITOFFSET  0
#define CLKCTL_RBUS_CLK_SEL_BITFIELDSIZE 32
#define CLKCTL_RBUS_CLK_SEL_BITMASK    0xFFFFFFFF
#define CLKCTL_RBUS_CLK_SEL_INIT       0x00000000
/*
 *  CLKCTL_RBUS_CORE_CTL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_RBUS_CORE_CTL_OFFSETADDRESS      CLKCTL_RBUS_CLK_SEL_OFFSETADDRESS
#define CLKCTL_RBUS_CORE_CTL_BITOFFSET          2
#define CLKCTL_RBUS_CORE_CTL_BITFIELDSIZE       1
#define CLKCTL_RBUS_CORE_CTL_BITMASK            0x00000004
#define CLKCTL_RBUS_CORE_CTL_INIT               0x0
/*
 *  CLKCTL_RBUS_CLK_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_RBUS_CLK_SEL_VAL_OFFSETADDRESS   CLKCTL_RBUS_CLK_SEL_OFFSETADDRESS
#define CLKCTL_RBUS_CLK_SEL_VAL_BITOFFSET       0
#define CLKCTL_RBUS_CLK_SEL_VAL_BITFIELDSIZE    2
#define CLKCTL_RBUS_CLK_SEL_VAL_BITMASK         0x00000003
#define CLKCTL_RBUS_CLK_SEL_VAL_INIT            0x0

/*
 *  CLKCTL_RBUS_CLK_ACTUAL register defines
 ****************************************************************************************
 */
#define CLKCTL_RBUS_CLK_ACTUAL_OFFSETADDRESS 0x00000144  /* RW */
#define CLKCTL_RBUS_CLK_ACTUAL_BITOFFSET 0
#define CLKCTL_RBUS_CLK_ACTUAL_BITFIELDSIZE 32
#define CLKCTL_RBUS_CLK_ACTUAL_BITMASK 0xFFFFFFFF
#define CLKCTL_RBUS_CLK_ACTUAL_INIT    0x00000000
/*
 *  CLKCTL_RBUS_CLK_ACTUAL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_RBUS_CLK_ACTUAL_VAL_OFFSETADDRESS CLKCTL_RBUS_CLK_ACTUAL_OFFSETADDRESS
#define CLKCTL_RBUS_CLK_ACTUAL_VAL_BITOFFSET    0
#define CLKCTL_RBUS_CLK_ACTUAL_VAL_BITFIELDSIZE  4
#define CLKCTL_RBUS_CLK_ACTUAL_VAL_BITMASK      0x0000000f
#define CLKCTL_RBUS_CLK_ACTUAL_VAL_INIT         0x0

/*
 *  CLKCTL_RBUS_DIV_SEL register defines
 ****************************************************************************************
 */
#define CLKCTL_RBUS_DIV_SEL_OFFSETADDRESS 0x00000148  /* RW */
#define CLKCTL_RBUS_DIV_SEL_BITOFFSET  0
#define CLKCTL_RBUS_DIV_SEL_BITFIELDSIZE 32
#define CLKCTL_RBUS_DIV_SEL_BITMASK    0xFFFFFFFF
#define CLKCTL_RBUS_DIV_SEL_INIT       0x00000000
/*
 *  CLKCTL_RBUS_DIV_SEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_RBUS_DIV_SEL_VAL_OFFSETADDRESS   CLKCTL_RBUS_DIV_SEL_OFFSETADDRESS
#define CLKCTL_RBUS_DIV_SEL_VAL_BITOFFSET       0
#define CLKCTL_RBUS_DIV_SEL_VAL_BITFIELDSIZE    2
#define CLKCTL_RBUS_DIV_SEL_VAL_BITMASK         0x00000003
#define CLKCTL_RBUS_DIV_SEL_VAL_INIT            0x0

/*
 *  CLKCTL_CRYPTO_CLK_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_CRYPTO_CLK_EN_OFFSETADDRESS 0x0000014c  /* RW */
#define CLKCTL_CRYPTO_CLK_EN_BITOFFSET 0
#define CLKCTL_CRYPTO_CLK_EN_BITFIELDSIZE 32
#define CLKCTL_CRYPTO_CLK_EN_BITMASK   0xFFFFFFFF
#define CLKCTL_CRYPTO_CLK_EN_INIT      0x00000000
/*
 *  CLKCTL_CRYPTO_CLK_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CRYPTO_CLK_ENABLE_OFFSETADDRESS  CLKCTL_CRYPTO_CLK_EN_OFFSETADDRESS
#define CLKCTL_CRYPTO_CLK_ENABLE_BITOFFSET      0
#define CLKCTL_CRYPTO_CLK_ENABLE_BITFIELDSIZE   1
#define CLKCTL_CRYPTO_CLK_ENABLE_BITMASK        0x00000001
#define CLKCTL_CRYPTO_CLK_ENABLE_INIT           0x0

/*
 *  CLKCTL_STCLKEN_NCO_EN register defines
 ****************************************************************************************
 */
#define CLKCTL_STCLKEN_NCO_EN_OFFSETADDRESS 0x00000150  /* RW */
#define CLKCTL_STCLKEN_NCO_EN_BITOFFSET 0
#define CLKCTL_STCLKEN_NCO_EN_BITFIELDSIZE 32
#define CLKCTL_STCLKEN_NCO_EN_BITMASK  0xFFFFFFFF
#define CLKCTL_STCLKEN_NCO_EN_INIT     0x00000000
/*
 *  CLKCTL_STCLKEN_NCO_ENABLE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_STCLKEN_NCO_ENABLE_OFFSETADDRESS CLKCTL_STCLKEN_NCO_EN_OFFSETADDRESS
#define CLKCTL_STCLKEN_NCO_ENABLE_BITOFFSET     0
#define CLKCTL_STCLKEN_NCO_ENABLE_BITFIELDSIZE  1
#define CLKCTL_STCLKEN_NCO_ENABLE_BITMASK       0x00000001
#define CLKCTL_STCLKEN_NCO_ENABLE_INIT          0x0

/*
 *  CLKCTL_STCLKEN_STEP register defines
 ****************************************************************************************
 */
#define CLKCTL_STCLKEN_STEP_OFFSETADDRESS 0x00000154  /* RW */
#define CLKCTL_STCLKEN_STEP_BITOFFSET  0
#define CLKCTL_STCLKEN_STEP_BITFIELDSIZE 32
#define CLKCTL_STCLKEN_STEP_BITMASK    0xFFFFFFFF
#define CLKCTL_STCLKEN_STEP_INIT       0x00000000
/*
 *  CLKCTL_STCLKEN_STEP_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_STCLKEN_STEP_VAL_OFFSETADDRESS   CLKCTL_STCLKEN_STEP_OFFSETADDRESS
#define CLKCTL_STCLKEN_STEP_VAL_BITOFFSET       0
#define CLKCTL_STCLKEN_STEP_VAL_BITFIELDSIZE   26
#define CLKCTL_STCLKEN_STEP_VAL_BITMASK         0x03ffffff
#define CLKCTL_STCLKEN_STEP_VAL_INIT            0x0

/*
 *  CLKCTL_CREQ_AIP_0 register defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP_0_OFFSETADDRESS 0x00000158  /* RW */
#define CLKCTL_CREQ_AIP_0_BITOFFSET    0
#define CLKCTL_CREQ_AIP_0_BITFIELDSIZE 32
#define CLKCTL_CREQ_AIP_0_BITMASK      0xFFFFFFFF
#define CLKCTL_CREQ_AIP_0_INIT         0x00000000
/*
 *  CLKCTL_CREQ_AIP0_CLK_LP bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP0_CLK_LP_OFFSETADDRESS   CLKCTL_CREQ_AIP_0_OFFSETADDRESS
#define CLKCTL_CREQ_AIP0_CLK_LP_BITOFFSET       3
#define CLKCTL_CREQ_AIP0_CLK_LP_BITFIELDSIZE    1
#define CLKCTL_CREQ_AIP0_CLK_LP_BITMASK         0x00000008
#define CLKCTL_CREQ_AIP0_CLK_LP_INIT            0x0
/*
 *  CLKCTL_CREQ_AIP0_CLK_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP0_CLK_PLL_OFFSETADDRESS  CLKCTL_CREQ_AIP_0_OFFSETADDRESS
#define CLKCTL_CREQ_AIP0_CLK_PLL_BITOFFSET      2
#define CLKCTL_CREQ_AIP0_CLK_PLL_BITFIELDSIZE   1
#define CLKCTL_CREQ_AIP0_CLK_PLL_BITMASK        0x00000004
#define CLKCTL_CREQ_AIP0_CLK_PLL_INIT           0x0
/*
 *  CLKCTL_CREQ_AIP0_CLK_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP0_CLK_HS_XTAL_OFFSETADDRESS CLKCTL_CREQ_AIP_0_OFFSETADDRESS
#define CLKCTL_CREQ_AIP0_CLK_HS_XTAL_BITOFFSET  1
#define CLKCTL_CREQ_AIP0_CLK_HS_XTAL_BITFIELDSIZE  1
#define CLKCTL_CREQ_AIP0_CLK_HS_XTAL_BITMASK    0x00000002
#define CLKCTL_CREQ_AIP0_CLK_HS_XTAL_INIT       0x0
/*
 *  CLKCTL_CREQ_AIP0_CLK_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP0_CLK_HS_RC_OFFSETADDRESS CLKCTL_CREQ_AIP_0_OFFSETADDRESS
#define CLKCTL_CREQ_AIP0_CLK_HS_RC_BITOFFSET    0
#define CLKCTL_CREQ_AIP0_CLK_HS_RC_BITFIELDSIZE  1
#define CLKCTL_CREQ_AIP0_CLK_HS_RC_BITMASK      0x00000001
#define CLKCTL_CREQ_AIP0_CLK_HS_RC_INIT         0x0

/*
 *  CLKCTL_CREQ_AIP_1 register defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP_1_OFFSETADDRESS 0x0000015c  /* RW */
#define CLKCTL_CREQ_AIP_1_BITOFFSET    0
#define CLKCTL_CREQ_AIP_1_BITFIELDSIZE 32
#define CLKCTL_CREQ_AIP_1_BITMASK      0xFFFFFFFF
#define CLKCTL_CREQ_AIP_1_INIT         0x00000000
/*
 *  CLKCTL_CREQ_AIP1_CLK_LP bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP1_CLK_LP_OFFSETADDRESS   CLKCTL_CREQ_AIP_1_OFFSETADDRESS
#define CLKCTL_CREQ_AIP1_CLK_LP_BITOFFSET       3
#define CLKCTL_CREQ_AIP1_CLK_LP_BITFIELDSIZE    1
#define CLKCTL_CREQ_AIP1_CLK_LP_BITMASK         0x00000008
#define CLKCTL_CREQ_AIP1_CLK_LP_INIT            0x0
/*
 *  CLKCTL_CREQ_AIP1_CLK_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP1_CLK_PLL_OFFSETADDRESS  CLKCTL_CREQ_AIP_1_OFFSETADDRESS
#define CLKCTL_CREQ_AIP1_CLK_PLL_BITOFFSET      2
#define CLKCTL_CREQ_AIP1_CLK_PLL_BITFIELDSIZE   1
#define CLKCTL_CREQ_AIP1_CLK_PLL_BITMASK        0x00000004
#define CLKCTL_CREQ_AIP1_CLK_PLL_INIT           0x0
/*
 *  CLKCTL_CREQ_AIP1_CLK_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP1_CLK_HS_XTAL_OFFSETADDRESS CLKCTL_CREQ_AIP_1_OFFSETADDRESS
#define CLKCTL_CREQ_AIP1_CLK_HS_XTAL_BITOFFSET  1
#define CLKCTL_CREQ_AIP1_CLK_HS_XTAL_BITFIELDSIZE  1
#define CLKCTL_CREQ_AIP1_CLK_HS_XTAL_BITMASK    0x00000002
#define CLKCTL_CREQ_AIP1_CLK_HS_XTAL_INIT       0x0
/*
 *  CLKCTL_CREQ_AIP1_CLK_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP1_CLK_HS_RC_OFFSETADDRESS CLKCTL_CREQ_AIP_1_OFFSETADDRESS
#define CLKCTL_CREQ_AIP1_CLK_HS_RC_BITOFFSET    0
#define CLKCTL_CREQ_AIP1_CLK_HS_RC_BITFIELDSIZE  1
#define CLKCTL_CREQ_AIP1_CLK_HS_RC_BITMASK      0x00000001
#define CLKCTL_CREQ_AIP1_CLK_HS_RC_INIT         0x0

/*
 *  CLKCTL_CREQ_AIP_2 register defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP_2_OFFSETADDRESS 0x00000160  /* RW */
#define CLKCTL_CREQ_AIP_2_BITOFFSET    0
#define CLKCTL_CREQ_AIP_2_BITFIELDSIZE 32
#define CLKCTL_CREQ_AIP_2_BITMASK      0xFFFFFFFF
#define CLKCTL_CREQ_AIP_2_INIT         0x00000000
/*
 *  CLKCTL_CREQ_AIP2_CLK_LP bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP2_CLK_LP_OFFSETADDRESS   CLKCTL_CREQ_AIP_2_OFFSETADDRESS
#define CLKCTL_CREQ_AIP2_CLK_LP_BITOFFSET       3
#define CLKCTL_CREQ_AIP2_CLK_LP_BITFIELDSIZE    1
#define CLKCTL_CREQ_AIP2_CLK_LP_BITMASK         0x00000008
#define CLKCTL_CREQ_AIP2_CLK_LP_INIT            0x0
/*
 *  CLKCTL_CREQ_AIP2_CLK_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP2_CLK_PLL_OFFSETADDRESS  CLKCTL_CREQ_AIP_2_OFFSETADDRESS
#define CLKCTL_CREQ_AIP2_CLK_PLL_BITOFFSET      2
#define CLKCTL_CREQ_AIP2_CLK_PLL_BITFIELDSIZE   1
#define CLKCTL_CREQ_AIP2_CLK_PLL_BITMASK        0x00000004
#define CLKCTL_CREQ_AIP2_CLK_PLL_INIT           0x0
/*
 *  CLKCTL_CREQ_AIP2_CLK_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP2_CLK_HS_XTAL_OFFSETADDRESS CLKCTL_CREQ_AIP_2_OFFSETADDRESS
#define CLKCTL_CREQ_AIP2_CLK_HS_XTAL_BITOFFSET  1
#define CLKCTL_CREQ_AIP2_CLK_HS_XTAL_BITFIELDSIZE  1
#define CLKCTL_CREQ_AIP2_CLK_HS_XTAL_BITMASK    0x00000002
#define CLKCTL_CREQ_AIP2_CLK_HS_XTAL_INIT       0x0
/*
 *  CLKCTL_CREQ_AIP2_CLK_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP2_CLK_HS_RC_OFFSETADDRESS CLKCTL_CREQ_AIP_2_OFFSETADDRESS
#define CLKCTL_CREQ_AIP2_CLK_HS_RC_BITOFFSET    0
#define CLKCTL_CREQ_AIP2_CLK_HS_RC_BITFIELDSIZE  1
#define CLKCTL_CREQ_AIP2_CLK_HS_RC_BITMASK      0x00000001
#define CLKCTL_CREQ_AIP2_CLK_HS_RC_INIT         0x0

/*
 *  CLKCTL_CREQ_AIP_3 register defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP_3_OFFSETADDRESS 0x00000164  /* RW */
#define CLKCTL_CREQ_AIP_3_BITOFFSET    0
#define CLKCTL_CREQ_AIP_3_BITFIELDSIZE 32
#define CLKCTL_CREQ_AIP_3_BITMASK      0xFFFFFFFF
#define CLKCTL_CREQ_AIP_3_INIT         0x00000000
/*
 *  CLKCTL_CREQ_AIP3_CLK_LP bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP3_CLK_LP_OFFSETADDRESS   CLKCTL_CREQ_AIP_3_OFFSETADDRESS
#define CLKCTL_CREQ_AIP3_CLK_LP_BITOFFSET       3
#define CLKCTL_CREQ_AIP3_CLK_LP_BITFIELDSIZE    1
#define CLKCTL_CREQ_AIP3_CLK_LP_BITMASK         0x00000008
#define CLKCTL_CREQ_AIP3_CLK_LP_INIT            0x0
/*
 *  CLKCTL_CREQ_AIP3_CLK_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP3_CLK_PLL_OFFSETADDRESS  CLKCTL_CREQ_AIP_3_OFFSETADDRESS
#define CLKCTL_CREQ_AIP3_CLK_PLL_BITOFFSET      2
#define CLKCTL_CREQ_AIP3_CLK_PLL_BITFIELDSIZE   1
#define CLKCTL_CREQ_AIP3_CLK_PLL_BITMASK        0x00000004
#define CLKCTL_CREQ_AIP3_CLK_PLL_INIT           0x0
/*
 *  CLKCTL_CREQ_AIP3_CLK_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP3_CLK_HS_XTAL_OFFSETADDRESS CLKCTL_CREQ_AIP_3_OFFSETADDRESS
#define CLKCTL_CREQ_AIP3_CLK_HS_XTAL_BITOFFSET  1
#define CLKCTL_CREQ_AIP3_CLK_HS_XTAL_BITFIELDSIZE  1
#define CLKCTL_CREQ_AIP3_CLK_HS_XTAL_BITMASK    0x00000002
#define CLKCTL_CREQ_AIP3_CLK_HS_XTAL_INIT       0x0
/*
 *  CLKCTL_CREQ_AIP3_CLK_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP3_CLK_HS_RC_OFFSETADDRESS CLKCTL_CREQ_AIP_3_OFFSETADDRESS
#define CLKCTL_CREQ_AIP3_CLK_HS_RC_BITOFFSET    0
#define CLKCTL_CREQ_AIP3_CLK_HS_RC_BITFIELDSIZE  1
#define CLKCTL_CREQ_AIP3_CLK_HS_RC_BITMASK      0x00000001
#define CLKCTL_CREQ_AIP3_CLK_HS_RC_INIT         0x0

/*
 *  CLKCTL_CREQ_AIP_4 register defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP_4_OFFSETADDRESS 0x00000168  /* RW */
#define CLKCTL_CREQ_AIP_4_BITOFFSET    0
#define CLKCTL_CREQ_AIP_4_BITFIELDSIZE 32
#define CLKCTL_CREQ_AIP_4_BITMASK      0xFFFFFFFF
#define CLKCTL_CREQ_AIP_4_INIT         0x00000000
/*
 *  CLKCTL_CREQ_AIP4_CLK_LP bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP4_CLK_LP_OFFSETADDRESS   CLKCTL_CREQ_AIP_4_OFFSETADDRESS
#define CLKCTL_CREQ_AIP4_CLK_LP_BITOFFSET       3
#define CLKCTL_CREQ_AIP4_CLK_LP_BITFIELDSIZE    1
#define CLKCTL_CREQ_AIP4_CLK_LP_BITMASK         0x00000008
#define CLKCTL_CREQ_AIP4_CLK_LP_INIT            0x0
/*
 *  CLKCTL_CREQ_AIP4_CLK_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP4_CLK_PLL_OFFSETADDRESS  CLKCTL_CREQ_AIP_4_OFFSETADDRESS
#define CLKCTL_CREQ_AIP4_CLK_PLL_BITOFFSET      2
#define CLKCTL_CREQ_AIP4_CLK_PLL_BITFIELDSIZE   1
#define CLKCTL_CREQ_AIP4_CLK_PLL_BITMASK        0x00000004
#define CLKCTL_CREQ_AIP4_CLK_PLL_INIT           0x0
/*
 *  CLKCTL_CREQ_AIP4_CLK_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP4_CLK_HS_XTAL_OFFSETADDRESS CLKCTL_CREQ_AIP_4_OFFSETADDRESS
#define CLKCTL_CREQ_AIP4_CLK_HS_XTAL_BITOFFSET  1
#define CLKCTL_CREQ_AIP4_CLK_HS_XTAL_BITFIELDSIZE  1
#define CLKCTL_CREQ_AIP4_CLK_HS_XTAL_BITMASK    0x00000002
#define CLKCTL_CREQ_AIP4_CLK_HS_XTAL_INIT       0x0
/*
 *  CLKCTL_CREQ_AIP4_CLK_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_AIP4_CLK_HS_RC_OFFSETADDRESS CLKCTL_CREQ_AIP_4_OFFSETADDRESS
#define CLKCTL_CREQ_AIP4_CLK_HS_RC_BITOFFSET    0
#define CLKCTL_CREQ_AIP4_CLK_HS_RC_BITFIELDSIZE  1
#define CLKCTL_CREQ_AIP4_CLK_HS_RC_BITMASK      0x00000001
#define CLKCTL_CREQ_AIP4_CLK_HS_RC_INIT         0x0

/*
 *  CLKCTL_CREQ_INVERT register defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_INVERT_OFFSETADDRESS 0x0000016c  /* RW */
#define CLKCTL_CREQ_INVERT_BITOFFSET   0
#define CLKCTL_CREQ_INVERT_BITFIELDSIZE 32
#define CLKCTL_CREQ_INVERT_BITMASK     0xFFFFFFFF
#define CLKCTL_CREQ_INVERT_INIT        0x00000000
/*
 *  CLKCTL_CREQ_INVERT_CLK_LP bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_INVERT_CLK_LP_OFFSETADDRESS CLKCTL_CREQ_INVERT_OFFSETADDRESS
#define CLKCTL_CREQ_INVERT_CLK_LP_BITOFFSET     3
#define CLKCTL_CREQ_INVERT_CLK_LP_BITFIELDSIZE  1
#define CLKCTL_CREQ_INVERT_CLK_LP_BITMASK       0x00000008
#define CLKCTL_CREQ_INVERT_CLK_LP_INIT          0x0
/*
 *  CLKCTL_CREQ_INVERT_CLK_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_INVERT_CLK_PLL_OFFSETADDRESS CLKCTL_CREQ_INVERT_OFFSETADDRESS
#define CLKCTL_CREQ_INVERT_CLK_PLL_BITOFFSET    2
#define CLKCTL_CREQ_INVERT_CLK_PLL_BITFIELDSIZE  1
#define CLKCTL_CREQ_INVERT_CLK_PLL_BITMASK      0x00000004
#define CLKCTL_CREQ_INVERT_CLK_PLL_INIT         0x0
/*
 *  CLKCTL_CREQ_INVERT_CLK_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_INVERT_CLK_HS_XTAL_OFFSETADDRESS CLKCTL_CREQ_INVERT_OFFSETADDRESS
#define CLKCTL_CREQ_INVERT_CLK_HS_XTAL_BITOFFSET  1
#define CLKCTL_CREQ_INVERT_CLK_HS_XTAL_BITFIELDSIZE  1
#define CLKCTL_CREQ_INVERT_CLK_HS_XTAL_BITMASK  0x00000002
#define CLKCTL_CREQ_INVERT_CLK_HS_XTAL_INIT     0x0
/*
 *  CLKCTL_CREQ_INVERT_CLK_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_INVERT_CLK_HS_RC_OFFSETADDRESS CLKCTL_CREQ_INVERT_OFFSETADDRESS
#define CLKCTL_CREQ_INVERT_CLK_HS_RC_BITOFFSET  0
#define CLKCTL_CREQ_INVERT_CLK_HS_RC_BITFIELDSIZE  1
#define CLKCTL_CREQ_INVERT_CLK_HS_RC_BITMASK    0x00000001
#define CLKCTL_CREQ_INVERT_CLK_HS_RC_INIT       0x0

/*
 *  CLKCTL_CREQ_WCM3_DSLEEP register defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_DSLEEP_OFFSETADDRESS 0x00000170  /* RW */
#define CLKCTL_CREQ_WCM3_DSLEEP_BITOFFSET 0
#define CLKCTL_CREQ_WCM3_DSLEEP_BITFIELDSIZE 32
#define CLKCTL_CREQ_WCM3_DSLEEP_BITMASK 0xFFFFFFFF
#define CLKCTL_CREQ_WCM3_DSLEEP_INIT   0x00000000
/*
 *  CLKCTL_CREQ_WCM3_DSLEEP_CLK_LP bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_LP_OFFSETADDRESS CLKCTL_CREQ_WCM3_DSLEEP_OFFSETADDRESS
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_LP_BITOFFSET  3
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_LP_BITFIELDSIZE  1
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_LP_BITMASK  0x00000008
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_LP_INIT     0x0
/*
 *  CLKCTL_CREQ_WCM3_DSLEEP_CLK_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_PLL_OFFSETADDRESS CLKCTL_CREQ_WCM3_DSLEEP_OFFSETADDRESS
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_PLL_BITOFFSET  2
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_PLL_BITFIELDSIZE  1
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_PLL_BITMASK 0x00000004
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_PLL_INIT    0x0
/*
 *  CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_XTAL_OFFSETADDRESS CLKCTL_CREQ_WCM3_DSLEEP_OFFSETADDRESS
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_XTAL_BITOFFSET  1
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_XTAL_BITFIELDSIZE  1
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_XTAL_BITMASK 0x00000002
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_XTAL_INIT 0x0
/*
 *  CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_RC_OFFSETADDRESS CLKCTL_CREQ_WCM3_DSLEEP_OFFSETADDRESS
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_RC_BITOFFSET  0
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_RC_BITFIELDSIZE  1
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_RC_BITMASK 0x00000001
#define CLKCTL_CREQ_WCM3_DSLEEP_CLK_HS_RC_INIT  0x0

/*
 *  CLKCTL_CREQ_WCM3_SLEEP register defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_SLEEP_OFFSETADDRESS 0x00000174  /* RW */
#define CLKCTL_CREQ_WCM3_SLEEP_BITOFFSET 0
#define CLKCTL_CREQ_WCM3_SLEEP_BITFIELDSIZE 32
#define CLKCTL_CREQ_WCM3_SLEEP_BITMASK 0xFFFFFFFF
#define CLKCTL_CREQ_WCM3_SLEEP_INIT    0x00000000
/*
 *  CLKCTL_CREQ_WCM3_SLEEP_CLK_LP bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_LP_OFFSETADDRESS CLKCTL_CREQ_WCM3_SLEEP_OFFSETADDRESS
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_LP_BITOFFSET  3
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_LP_BITFIELDSIZE  1
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_LP_BITMASK   0x00000008
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_LP_INIT      0x0
/*
 *  CLKCTL_CREQ_WCM3_SLEEP_CLK_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_PLL_OFFSETADDRESS CLKCTL_CREQ_WCM3_SLEEP_OFFSETADDRESS
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_PLL_BITOFFSET  2
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_PLL_BITFIELDSIZE  1
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_PLL_BITMASK  0x00000004
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_PLL_INIT     0x0
/*
 *  CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_XTAL_OFFSETADDRESS CLKCTL_CREQ_WCM3_SLEEP_OFFSETADDRESS
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_XTAL_BITOFFSET  1
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_XTAL_BITFIELDSIZE  1
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_XTAL_BITMASK 0x00000002
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_XTAL_INIT 0x0
/*
 *  CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_RC_OFFSETADDRESS CLKCTL_CREQ_WCM3_SLEEP_OFFSETADDRESS
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_RC_BITOFFSET  0
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_RC_BITFIELDSIZE  1
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_RC_BITMASK 0x00000001
#define CLKCTL_CREQ_WCM3_SLEEP_CLK_HS_RC_INIT   0x0

/*
 *  CLKCTL_CREQ_WCM3_ACTIVE register defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_ACTIVE_OFFSETADDRESS 0x00000178  /* RW */
#define CLKCTL_CREQ_WCM3_ACTIVE_BITOFFSET 0
#define CLKCTL_CREQ_WCM3_ACTIVE_BITFIELDSIZE 32
#define CLKCTL_CREQ_WCM3_ACTIVE_BITMASK 0xFFFFFFFF
#define CLKCTL_CREQ_WCM3_ACTIVE_INIT   0x00000000
/*
 *  CLKCTL_CREQ_WCM3_ACTIVE_CLK_LP bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_LP_OFFSETADDRESS CLKCTL_CREQ_WCM3_ACTIVE_OFFSETADDRESS
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_LP_BITOFFSET  3
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_LP_BITFIELDSIZE  1
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_LP_BITMASK  0x00000008
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_LP_INIT     0x0
/*
 *  CLKCTL_CREQ_WCM3_ACTIVE_CLK_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_PLL_OFFSETADDRESS CLKCTL_CREQ_WCM3_ACTIVE_OFFSETADDRESS
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_PLL_BITOFFSET  2
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_PLL_BITFIELDSIZE  1
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_PLL_BITMASK 0x00000004
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_PLL_INIT    0x0
/*
 *  CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_XTAL_OFFSETADDRESS CLKCTL_CREQ_WCM3_ACTIVE_OFFSETADDRESS
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_XTAL_BITOFFSET  1
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_XTAL_BITFIELDSIZE  1
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_XTAL_BITMASK 0x00000002
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_XTAL_INIT 0x0
/*
 *  CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_RC_OFFSETADDRESS CLKCTL_CREQ_WCM3_ACTIVE_OFFSETADDRESS
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_RC_BITOFFSET  0
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_RC_BITFIELDSIZE  1
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_RC_BITMASK 0x00000001
#define CLKCTL_CREQ_WCM3_ACTIVE_CLK_HS_RC_INIT  0x0

/*
 *  CLKCTL_CSEL_CLKSEL register defines
 ****************************************************************************************
 */
#define CLKCTL_CSEL_CLKSEL_OFFSETADDRESS 0x0000017c  /* RW */
#define CLKCTL_CSEL_CLKSEL_BITOFFSET   0
#define CLKCTL_CSEL_CLKSEL_BITFIELDSIZE 32
#define CLKCTL_CSEL_CLKSEL_BITMASK     0xFFFFFFFF
#define CLKCTL_CSEL_CLKSEL_INIT        0x00000000
/*
 *  CLKCTL_CSEL_CLKSEL_VAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CSEL_CLKSEL_VAL_OFFSETADDRESS    CLKCTL_CSEL_CLKSEL_OFFSETADDRESS
#define CLKCTL_CSEL_CLKSEL_VAL_BITOFFSET        0
#define CLKCTL_CSEL_CLKSEL_VAL_BITFIELDSIZE     1
#define CLKCTL_CSEL_CLKSEL_VAL_BITMASK          0x00000001
#define CLKCTL_CSEL_CLKSEL_VAL_INIT             0x0

/*
 *  CLKCTL_CREG_CLKSEL register defines
 ****************************************************************************************
 */
#define CLKCTL_CREG_CLKSEL_OFFSETADDRESS 0x00000180  /* RW */
#define CLKCTL_CREG_CLKSEL_BITOFFSET   0
#define CLKCTL_CREG_CLKSEL_BITFIELDSIZE 32
#define CLKCTL_CREG_CLKSEL_BITMASK     0xFFFFFFFF
#define CLKCTL_CREG_CLKSEL_INIT        0x00000000
/*
 *  CLKCTL_CREG_CLKSEL_WCM3CLK_EN bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREG_CLKSEL_WCM3CLK_EN_OFFSETADDRESS CLKCTL_CREG_CLKSEL_OFFSETADDRESS
#define CLKCTL_CREG_CLKSEL_WCM3CLK_EN_BITOFFSET  6
#define CLKCTL_CREG_CLKSEL_WCM3CLK_EN_BITFIELDSIZE  1
#define CLKCTL_CREG_CLKSEL_WCM3CLK_EN_BITMASK   0x00000040
#define CLKCTL_CREG_CLKSEL_WCM3CLK_EN_INIT      0x0
/*
 *  CLKCTL_CREG_CLKSEL_RBUS_CLK_SEL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREG_CLKSEL_RBUS_CLK_SEL_OFFSETADDRESS CLKCTL_CREG_CLKSEL_OFFSETADDRESS
#define CLKCTL_CREG_CLKSEL_RBUS_CLK_SEL_BITOFFSET  4
#define CLKCTL_CREG_CLKSEL_RBUS_CLK_SEL_BITFIELDSIZE  2
#define CLKCTL_CREG_CLKSEL_RBUS_CLK_SEL_BITMASK 0x00000030
#define CLKCTL_CREG_CLKSEL_RBUS_CLK_SEL_INIT    0x0
/*
 *  CLKCTL_CREG_CLKSEL_WCM3CLK_SEL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREG_CLKSEL_WCM3CLK_SEL_OFFSETADDRESS CLKCTL_CREG_CLKSEL_OFFSETADDRESS
#define CLKCTL_CREG_CLKSEL_WCM3CLK_SEL_BITOFFSET  2
#define CLKCTL_CREG_CLKSEL_WCM3CLK_SEL_BITFIELDSIZE  2
#define CLKCTL_CREG_CLKSEL_WCM3CLK_SEL_BITMASK  0x0000000c
#define CLKCTL_CREG_CLKSEL_WCM3CLK_SEL_INIT     0x0
/*
 *  CLKCTL_CREG_CLKSEL_ACM3CLK_SEL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CREG_CLKSEL_ACM3CLK_SEL_OFFSETADDRESS CLKCTL_CREG_CLKSEL_OFFSETADDRESS
#define CLKCTL_CREG_CLKSEL_ACM3CLK_SEL_BITOFFSET  0
#define CLKCTL_CREG_CLKSEL_ACM3CLK_SEL_BITFIELDSIZE  2
#define CLKCTL_CREG_CLKSEL_ACM3CLK_SEL_BITMASK  0x00000003
#define CLKCTL_CREG_CLKSEL_ACM3CLK_SEL_INIT     0x0

/*
 *  CLKCTL_CX_TEST register defines
 ****************************************************************************************
 */
#define CLKCTL_CX_TEST_OFFSETADDRESS   0x00000184  /* R */
#define CLKCTL_CX_TEST_BITOFFSET       0
#define CLKCTL_CX_TEST_BITFIELDSIZE    32
#define CLKCTL_CX_TEST_BITMASK         0xFFFFFFFF
#define CLKCTL_CX_TEST_INIT            0x00000000
/*
 *  CLKCTL_CX_CAL_LOCK_DET bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CX_CAL_LOCK_DET_OFFSETADDRESS    CLKCTL_CX_TEST_OFFSETADDRESS
#define CLKCTL_CX_CAL_LOCK_DET_BITOFFSET       13
#define CLKCTL_CX_CAL_LOCK_DET_BITFIELDSIZE     1
#define CLKCTL_CX_CAL_LOCK_DET_BITMASK          0x00002000
#define CLKCTL_CX_CAL_LOCK_DET_INIT             0x0
/*
 *  CLKCTL_CX_LOCK_DET bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CX_LOCK_DET_OFFSETADDRESS        CLKCTL_CX_TEST_OFFSETADDRESS
#define CLKCTL_CX_LOCK_DET_BITOFFSET           12
#define CLKCTL_CX_LOCK_DET_BITFIELDSIZE         1
#define CLKCTL_CX_LOCK_DET_BITMASK              0x00001000
#define CLKCTL_CX_LOCK_DET_INIT                 0x0
/*
 *  CLKCTL_CX_CAL_DONE bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CX_CAL_DONE_OFFSETADDRESS        CLKCTL_CX_TEST_OFFSETADDRESS
#define CLKCTL_CX_CAL_DONE_BITOFFSET           11
#define CLKCTL_CX_CAL_DONE_BITFIELDSIZE         1
#define CLKCTL_CX_CAL_DONE_BITMASK              0x00000800
#define CLKCTL_CX_CAL_DONE_INIT                 0x0
/*
 *  CLKCTL_CX_CAL_IN_PRGS bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CX_CAL_IN_PRGS_OFFSETADDRESS     CLKCTL_CX_TEST_OFFSETADDRESS
#define CLKCTL_CX_CAL_IN_PRGS_BITOFFSET        10
#define CLKCTL_CX_CAL_IN_PRGS_BITFIELDSIZE      1
#define CLKCTL_CX_CAL_IN_PRGS_BITMASK           0x00000400
#define CLKCTL_CX_CAL_IN_PRGS_INIT              0x0
/*
 *  CLKCTL_CX_CAL_REG_OUT bit field defines
 ****************************************************************************************
 */
#define CLKCTL_CX_CAL_REG_OUT_OFFSETADDRESS     CLKCTL_CX_TEST_OFFSETADDRESS
#define CLKCTL_CX_CAL_REG_OUT_BITOFFSET         0
#define CLKCTL_CX_CAL_REG_OUT_BITFIELDSIZE     10
#define CLKCTL_CX_CAL_REG_OUT_BITMASK           0x000003ff
#define CLKCTL_CX_CAL_REG_OUT_INIT              0x0

/*
 *  CLKCTL_STABLE_IRQ_STATUS register defines
 ****************************************************************************************
 */
#define CLKCTL_STABLE_IRQ_STATUS_OFFSETADDRESS 0x00000188  /* R */
#define CLKCTL_STABLE_IRQ_STATUS_BITOFFSET 0
#define CLKCTL_STABLE_IRQ_STATUS_BITFIELDSIZE 32
#define CLKCTL_STABLE_IRQ_STATUS_BITMASK 0xFFFFFFFF
#define CLKCTL_STABLE_IRQ_STATUS_INIT  0x00000000
/*
 *  CLKCTL_STABLE_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_STABLE_HS_RC_OFFSETADDRESS       CLKCTL_STABLE_IRQ_STATUS_OFFSETADDRESS
#define CLKCTL_STABLE_HS_RC_BITOFFSET           2
#define CLKCTL_STABLE_HS_RC_BITFIELDSIZE        1
#define CLKCTL_STABLE_HS_RC_BITMASK             0x00000004
#define CLKCTL_STABLE_HS_RC_INIT                0x0
/*
 *  CLKCTL_STABLE_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_STABLE_HS_XTAL_OFFSETADDRESS     CLKCTL_STABLE_IRQ_STATUS_OFFSETADDRESS
#define CLKCTL_STABLE_HS_XTAL_BITOFFSET         1
#define CLKCTL_STABLE_HS_XTAL_BITFIELDSIZE      1
#define CLKCTL_STABLE_HS_XTAL_BITMASK           0x00000002
#define CLKCTL_STABLE_HS_XTAL_INIT              0x0
/*
 *  CLKCTL_STABLE_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_STABLE_PLL_OFFSETADDRESS         CLKCTL_STABLE_IRQ_STATUS_OFFSETADDRESS
#define CLKCTL_STABLE_PLL_BITOFFSET             0
#define CLKCTL_STABLE_PLL_BITFIELDSIZE          1
#define CLKCTL_STABLE_PLL_BITMASK               0x00000001
#define CLKCTL_STABLE_PLL_INIT                  0x0

/*
 *  CLKCTL_STABLE_IRQ_MASK register defines
 ****************************************************************************************
 */
#define CLKCTL_STABLE_IRQ_MASK_OFFSETADDRESS 0x0000018c  /* RW */
#define CLKCTL_STABLE_IRQ_MASK_BITOFFSET 0
#define CLKCTL_STABLE_IRQ_MASK_BITFIELDSIZE 32
#define CLKCTL_STABLE_IRQ_MASK_BITMASK 0xFFFFFFFF
#define CLKCTL_STABLE_IRQ_MASK_INIT    0x00000000
/*
 *  CLKCTL_STABLE_IRQ_MASK_HS_RC bit field defines
 ****************************************************************************************
 */
#define CLKCTL_STABLE_IRQ_MASK_HS_RC_OFFSETADDRESS CLKCTL_STABLE_IRQ_MASK_OFFSETADDRESS
#define CLKCTL_STABLE_IRQ_MASK_HS_RC_BITOFFSET  2
#define CLKCTL_STABLE_IRQ_MASK_HS_RC_BITFIELDSIZE  1
#define CLKCTL_STABLE_IRQ_MASK_HS_RC_BITMASK    0x00000004
#define CLKCTL_STABLE_IRQ_MASK_HS_RC_INIT       0x0
/*
 *  CLKCTL_STABLE_IRQ_MASK_HS_XTAL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_STABLE_IRQ_MASK_HS_XTAL_OFFSETADDRESS CLKCTL_STABLE_IRQ_MASK_OFFSETADDRESS
#define CLKCTL_STABLE_IRQ_MASK_HS_XTAL_BITOFFSET  1
#define CLKCTL_STABLE_IRQ_MASK_HS_XTAL_BITFIELDSIZE  1
#define CLKCTL_STABLE_IRQ_MASK_HS_XTAL_BITMASK  0x00000002
#define CLKCTL_STABLE_IRQ_MASK_HS_XTAL_INIT     0x0
/*
 *  CLKCTL_STABLE_IRQ_MASK_PLL bit field defines
 ****************************************************************************************
 */
#define CLKCTL_STABLE_IRQ_MASK_PLL_OFFSETADDRESS CLKCTL_STABLE_IRQ_MASK_OFFSETADDRESS
#define CLKCTL_STABLE_IRQ_MASK_PLL_BITOFFSET    0
#define CLKCTL_STABLE_IRQ_MASK_PLL_BITFIELDSIZE  1
#define CLKCTL_STABLE_IRQ_MASK_PLL_BITMASK      0x00000001
#define CLKCTL_STABLE_IRQ_MASK_PLL_INIT         0x0

#endif

