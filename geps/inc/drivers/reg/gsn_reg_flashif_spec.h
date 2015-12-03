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
* $RCSfile: gsn_reg_flashif_spec.h,v $
*
* Description : This file contains flash if register specification.
******************************************************************************/

#ifndef _REG_FLASHIF_SPEC_H
#define _REG_FLASHIF_SPEC_H

/***************************************************
 *
 *             FLASHIF
 *
 ***************************************************/


/*
 *  FLASHIF instance offsets
 ****************************************************************************************
 */
#define FLASHIF 0x400E0000

/*
 *  FLASHIF_CTL register defines
 ****************************************************************************************
 */
#define FLASHIF_CTL_OFFSETADDRESS      0x00000000  /* RW */
#define FLASHIF_CTL_BITOFFSET          0
#define FLASHIF_CTL_BITFIELDSIZE       32
#define FLASHIF_CTL_BITMASK            0xFFFFFFFF
#define FLASHIF_CTL_INIT               0x00000000
/*
 *  FLASHIF_WLAN_DMA_EN bit field defines
 ****************************************************************************************
 */
#define FLASHIF_WLAN_DMA_EN_OFFSETADDRESS       FLASHIF_CTL_OFFSETADDRESS
#define FLASHIF_WLAN_DMA_EN_BITOFFSET           2
#define FLASHIF_WLAN_DMA_EN_BITFIELDSIZE        1
#define FLASHIF_WLAN_DMA_EN_BITMASK             0x00000004
#define FLASHIF_WLAN_DMA_EN_INIT                0x0
/*
 *  FLASHIF_APP_DMA_EN bit field defines
 ****************************************************************************************
 */
#define FLASHIF_APP_DMA_EN_OFFSETADDRESS        FLASHIF_CTL_OFFSETADDRESS
#define FLASHIF_APP_DMA_EN_BITOFFSET            1
#define FLASHIF_APP_DMA_EN_BITFIELDSIZE         1
#define FLASHIF_APP_DMA_EN_BITMASK              0x00000002
#define FLASHIF_APP_DMA_EN_INIT                 0x0
/*
 *  FLASHIF_EN bit field defines
 ****************************************************************************************
 */
#define FLASHIF_EN_OFFSETADDRESS                FLASHIF_CTL_OFFSETADDRESS
#define FLASHIF_EN_BITOFFSET                    0
#define FLASHIF_EN_BITFIELDSIZE                 1
#define FLASHIF_EN_BITMASK                      0x00000001
#define FLASHIF_EN_INIT                         0x0

/*
 *  FLASHIF_STATUS register defines
 ****************************************************************************************
 */
#define FLASHIF_STATUS_OFFSETADDRESS   0x00000004  /* RW */
#define FLASHIF_STATUS_BITOFFSET       0
#define FLASHIF_STATUS_BITFIELDSIZE    32
#define FLASHIF_STATUS_BITMASK         0xFFFFFFFF
#define FLASHIF_STATUS_INIT            0x00000000
/*
 *  FLASHIF_DMA_STATUS bit field defines
 ****************************************************************************************
 */
#define FLASHIF_DMA_STATUS_OFFSETADDRESS        FLASHIF_STATUS_OFFSETADDRESS
#define FLASHIF_DMA_STATUS_BITOFFSET            5
#define FLASHIF_DMA_STATUS_BITFIELDSIZE         2
#define FLASHIF_DMA_STATUS_BITMASK              0x00000060
#define FLASHIF_DMA_STATUS_INIT                 0x0
/*
 *  FLASHIF_ACTIVE bit field defines
 ****************************************************************************************
 */
#define FLASHIF_ACTIVE_OFFSETADDRESS            FLASHIF_STATUS_OFFSETADDRESS
#define FLASHIF_ACTIVE_BITOFFSET                4
#define FLASHIF_ACTIVE_BITFIELDSIZE             1
#define FLASHIF_ACTIVE_BITMASK                  0x00000010
#define FLASHIF_ACTIVE_INIT                     0x0
/*
 *  FLASHIF_PIO_RXFIFO_FULL bit field defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_RXFIFO_FULL_OFFSETADDRESS   FLASHIF_STATUS_OFFSETADDRESS
#define FLASHIF_PIO_RXFIFO_FULL_BITOFFSET       3
#define FLASHIF_PIO_RXFIFO_FULL_BITFIELDSIZE    1
#define FLASHIF_PIO_RXFIFO_FULL_BITMASK         0x00000008
#define FLASHIF_PIO_RXFIFO_FULL_INIT            0x0
/*
 *  FLASHIF_PIO_RXFIFO_EMPTY bit field defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_RXFIFO_EMPTY_OFFSETADDRESS  FLASHIF_STATUS_OFFSETADDRESS
#define FLASHIF_PIO_RXFIFO_EMPTY_BITOFFSET      2
#define FLASHIF_PIO_RXFIFO_EMPTY_BITFIELDSIZE   1
#define FLASHIF_PIO_RXFIFO_EMPTY_BITMASK        0x00000004
#define FLASHIF_PIO_RXFIFO_EMPTY_INIT           0x0
/*
 *  FLASHIF_PIO_TXFIFO_FULL bit field defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_TXFIFO_FULL_OFFSETADDRESS   FLASHIF_STATUS_OFFSETADDRESS
#define FLASHIF_PIO_TXFIFO_FULL_BITOFFSET       1
#define FLASHIF_PIO_TXFIFO_FULL_BITFIELDSIZE    1
#define FLASHIF_PIO_TXFIFO_FULL_BITMASK         0x00000002
#define FLASHIF_PIO_TXFIFO_FULL_INIT            0x0
/*
 *  FLASHIF_PIO_TXFIFO_EMPTY bit field defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_TXFIFO_EMPTY_OFFSETADDRESS  FLASHIF_STATUS_OFFSETADDRESS
#define FLASHIF_PIO_TXFIFO_EMPTY_BITOFFSET      0
#define FLASHIF_PIO_TXFIFO_EMPTY_BITFIELDSIZE   1
#define FLASHIF_PIO_TXFIFO_EMPTY_BITMASK        0x00000001
#define FLASHIF_PIO_TXFIFO_EMPTY_INIT           0x0

/*
 *  FLASHIF_DMACTL register defines
 ****************************************************************************************
 */
#define FLASHIF_DMACTL_OFFSETADDRESS   0x00000008  /* RW */
#define FLASHIF_DMACTL_BITOFFSET       0
#define FLASHIF_DMACTL_BITFIELDSIZE    32
#define FLASHIF_DMACTL_BITMASK         0xFFFFFFFF
#define FLASHIF_DMACTL_INIT            0x00000000
/*
 *  FLASHIF_DMA_DUMMY_BYTECOUNT bit field defines
 ****************************************************************************************
 */
#define FLASHIF_DMA_DUMMY_BYTECOUNT_OFFSETADDRESS FLASHIF_DMACTL_OFFSETADDRESS
#define FLASHIF_DMA_DUMMY_BYTECOUNT_BITOFFSET  16
#define FLASHIF_DMA_DUMMY_BYTECOUNT_BITFIELDSIZE  8
#define FLASHIF_DMA_DUMMY_BYTECOUNT_BITMASK     0x00ff0000
#define FLASHIF_DMA_DUMMY_BYTECOUNT_INIT        0x0
/*
 *  FLASHIF_DMA_DATA_BITLANES bit field defines
 ****************************************************************************************
 */
#define FLASHIF_DMA_DATA_BITLANES_OFFSETADDRESS FLASHIF_DMACTL_OFFSETADDRESS
#define FLASHIF_DMA_DATA_BITLANES_BITOFFSET    14
#define FLASHIF_DMA_DATA_BITLANES_BITFIELDSIZE  2
#define FLASHIF_DMA_DATA_BITLANES_BITMASK       0x0000c000
#define FLASHIF_DMA_DATA_BITLANES_INIT          0x0
/*
 *  FLASHIF_DMA_DUMMY_BITLANES bit field defines
 ****************************************************************************************
 */
#define FLASHIF_DMA_DUMMY_BITLANES_OFFSETADDRESS FLASHIF_DMACTL_OFFSETADDRESS
#define FLASHIF_DMA_DUMMY_BITLANES_BITOFFSET   12
#define FLASHIF_DMA_DUMMY_BITLANES_BITFIELDSIZE  2
#define FLASHIF_DMA_DUMMY_BITLANES_BITMASK      0x00003000
#define FLASHIF_DMA_DUMMY_BITLANES_INIT         0x0
/*
 *  FLASHIF_DMA_ADDR_BITLANES bit field defines
 ****************************************************************************************
 */
#define FLASHIF_DMA_ADDR_BITLANES_OFFSETADDRESS FLASHIF_DMACTL_OFFSETADDRESS
#define FLASHIF_DMA_ADDR_BITLANES_BITOFFSET    10
#define FLASHIF_DMA_ADDR_BITLANES_BITFIELDSIZE  2
#define FLASHIF_DMA_ADDR_BITLANES_BITMASK       0x00000c00
#define FLASHIF_DMA_ADDR_BITLANES_INIT          0x0
/*
 *  FLASHIF_DMA_CMD_BITLANES bit field defines
 ****************************************************************************************
 */
#define FLASHIF_DMA_CMD_BITLANES_OFFSETADDRESS  FLASHIF_DMACTL_OFFSETADDRESS
#define FLASHIF_DMA_CMD_BITLANES_BITOFFSET      8
#define FLASHIF_DMA_CMD_BITLANES_BITFIELDSIZE   2
#define FLASHIF_DMA_CMD_BITLANES_BITMASK        0x00000300
#define FLASHIF_DMA_CMD_BITLANES_INIT           0x0
/*
 *  FLASHIF_DMA_DUMMY_CYCLECOUNT bit field defines
 ****************************************************************************************
 */
#define FLASHIF_DMA_DUMMY_CYCLECOUNT_OFFSETADDRESS FLASHIF_DMACTL_OFFSETADDRESS
#define FLASHIF_DMA_DUMMY_CYCLECOUNT_BITOFFSET  7
#define FLASHIF_DMA_DUMMY_CYCLECOUNT_BITFIELDSIZE  1
#define FLASHIF_DMA_DUMMY_CYCLECOUNT_BITMASK    0x00000080
#define FLASHIF_DMA_DUMMY_CYCLECOUNT_INIT       0x0
/*
 *  FLASHIF_DMA_DUMMY_BYTESNONZERO bit field defines
 ****************************************************************************************
 */
#define FLASHIF_DMA_DUMMY_BYTESNONZERO_OFFSETADDRESS FLASHIF_DMACTL_OFFSETADDRESS
#define FLASHIF_DMA_DUMMY_BYTESNONZERO_BITOFFSET  6
#define FLASHIF_DMA_DUMMY_BYTESNONZERO_BITFIELDSIZE  1
#define FLASHIF_DMA_DUMMY_BYTESNONZERO_BITMASK  0x00000040
#define FLASHIF_DMA_DUMMY_BYTESNONZERO_INIT     0x0
/*
 *  FLASHIF_DMA_ADDR_BYTECOUNT bit field defines
 ****************************************************************************************
 */
#define FLASHIF_DMA_ADDR_BYTECOUNT_OFFSETADDRESS FLASHIF_DMACTL_OFFSETADDRESS
#define FLASHIF_DMA_ADDR_BYTECOUNT_BITOFFSET    3
#define FLASHIF_DMA_ADDR_BYTECOUNT_BITFIELDSIZE  3
#define FLASHIF_DMA_ADDR_BYTECOUNT_BITMASK      0x00000038
#define FLASHIF_DMA_ADDR_BYTECOUNT_INIT         0x0
/*
 *  FLASHIF_DMA_CMD_BYTECOUNT bit field defines
 ****************************************************************************************
 */
#define FLASHIF_DMA_CMD_BYTECOUNT_OFFSETADDRESS FLASHIF_DMACTL_OFFSETADDRESS
#define FLASHIF_DMA_CMD_BYTECOUNT_BITOFFSET     1
#define FLASHIF_DMA_CMD_BYTECOUNT_BITFIELDSIZE  2
#define FLASHIF_DMA_CMD_BYTECOUNT_BITMASK       0x00000006
#define FLASHIF_DMA_CMD_BYTECOUNT_INIT          0x0
/*
 *  FLASHIF_DMA_DIRECTION bit field defines
 ****************************************************************************************
 */
#define FLASHIF_DMA_DIRECTION_OFFSETADDRESS     FLASHIF_DMACTL_OFFSETADDRESS
#define FLASHIF_DMA_DIRECTION_BITOFFSET         0
#define FLASHIF_DMA_DIRECTION_BITFIELDSIZE      1
#define FLASHIF_DMA_DIRECTION_BITMASK           0x00000001
#define FLASHIF_DMA_DIRECTION_INIT              0x0

/*
 *  FLASHIF_DMACMD register defines
 ****************************************************************************************
 */
#define FLASHIF_DMACMD_OFFSETADDRESS   0x0000000c  /* RW */
#define FLASHIF_DMACMD_BITOFFSET       0
#define FLASHIF_DMACMD_BITFIELDSIZE    32
#define FLASHIF_DMACMD_BITMASK         0xFFFFFFFF
#define FLASHIF_DMACMD_INIT            0x00000000
/*
 *  FLASHIF_DMACMD_WORD bit field defines
 ****************************************************************************************
 */
#define FLASHIF_DMACMD_WORD_OFFSETADDRESS       FLASHIF_DMACMD_OFFSETADDRESS
#define FLASHIF_DMACMD_WORD_BITOFFSET           0
#define FLASHIF_DMACMD_WORD_BITFIELDSIZE       32
#define FLASHIF_DMACMD_WORD_BITMASK             0xffffffff
#define FLASHIF_DMACMD_WORD_INIT                0x0

/*
 *  FLASHIF_PIO_TXFIFO register defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_TXFIFO_OFFSETADDRESS 0x00000400  /* RW */
#define FLASHIF_PIO_TXFIFO_BITOFFSET   0
#define FLASHIF_PIO_TXFIFO_BITFIELDSIZE 32
#define FLASHIF_PIO_TXFIFO_BITMASK     0xFFFFFFFF
#define FLASHIF_PIO_TXFIFO_INIT        0x00000000
/*
 *  FLASHIF_PIO_TXFIFO_DATA bit field defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_TXFIFO_DATA_OFFSETADDRESS   FLASHIF_PIO_TXFIFO_OFFSETADDRESS
#define FLASHIF_PIO_TXFIFO_DATA_BITOFFSET       0
#define FLASHIF_PIO_TXFIFO_DATA_BITFIELDSIZE   32
#define FLASHIF_PIO_TXFIFO_DATA_BITMASK         0xffffffff
#define FLASHIF_PIO_TXFIFO_DATA_INIT            0x0

#if 0
/*
 *  FLASHIF_PIO_TXFIFO_STATUS register defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_TXFIFO_STATUS_OFFSETADDRESS 0x00000404  /* RW */
#define FLASHIF_PIO_TXFIFO_STATUS_BITOFFSET 0
#define FLASHIF_PIO_TXFIFO_STATUS_BITFIELDSIZE 32
#define FLASHIF_PIO_TXFIFO_STATUS_BITMASK 0xFFFFFFFF
#define FLASHIF_PIO_TXFIFO_STATUS_INIT 0x00000000
/*
 *  FLASHIF_PIO_TXFIFO_EMPTY bit field defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_TXFIFO_EMPTY_OFFSETADDRESS  FLASHIF_PIO_TXFIFO_STATUS_OFFSETADDRESS
#define FLASHIF_PIO_TXFIFO_EMPTY_BITOFFSET      1
#define FLASHIF_PIO_TXFIFO_EMPTY_BITFIELDSIZE   1
#define FLASHIF_PIO_TXFIFO_EMPTY_BITMASK        0x00000002
#define FLASHIF_PIO_TXFIFO_EMPTY_INIT           0x0
/*
 *  FLASHIF_PIO_TXFIFO_FULL bit field defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_TXFIFO_FULL_OFFSETADDRESS   FLASHIF_PIO_TXFIFO_STATUS_OFFSETADDRESS
#define FLASHIF_PIO_TXFIFO_FULL_BITOFFSET       0
#define FLASHIF_PIO_TXFIFO_FULL_BITFIELDSIZE    1
#define FLASHIF_PIO_TXFIFO_FULL_BITMASK         0x00000001
#define FLASHIF_PIO_TXFIFO_FULL_INIT            0x0
#endif

/*
 *  FLASHIF_PIO_RXFIFO register defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_RXFIFO_OFFSETADDRESS 0x00000408  /* RW */
#define FLASHIF_PIO_RXFIFO_BITOFFSET   0
#define FLASHIF_PIO_RXFIFO_BITFIELDSIZE 32
#define FLASHIF_PIO_RXFIFO_BITMASK     0xFFFFFFFF
#define FLASHIF_PIO_RXFIFO_INIT        0x00000000
/*
 *  FLASHIF_PIO_RXFIFO_DATA bit field defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_RXFIFO_DATA_OFFSETADDRESS   FLASHIF_PIO_RXFIFO_OFFSETADDRESS
#define FLASHIF_PIO_RXFIFO_DATA_BITOFFSET       0
#define FLASHIF_PIO_RXFIFO_DATA_BITFIELDSIZE   32
#define FLASHIF_PIO_RXFIFO_DATA_BITMASK         0xffffffff
#define FLASHIF_PIO_RXFIFO_DATA_INIT            0x0

#if 0
/*
 *  FLASHIF_PIO_RXFIFO_STATUS register defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_RXFIFO_STATUS_OFFSETADDRESS 0x0000040c  /* RW */
#define FLASHIF_PIO_RXFIFO_STATUS_BITOFFSET 0
#define FLASHIF_PIO_RXFIFO_STATUS_BITFIELDSIZE 32
#define FLASHIF_PIO_RXFIFO_STATUS_BITMASK 0xFFFFFFFF
#define FLASHIF_PIO_RXFIFO_STATUS_INIT 0x00000000
/*
 *  FLASHIF_PIO_RXFIFO_EMPTY bit field defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_RXFIFO_EMPTY_OFFSETADDRESS  FLASHIF_PIO_RXFIFO_STATUS_OFFSETADDRESS
#define FLASHIF_PIO_RXFIFO_EMPTY_BITOFFSET      1
#define FLASHIF_PIO_RXFIFO_EMPTY_BITFIELDSIZE   1
#define FLASHIF_PIO_RXFIFO_EMPTY_BITMASK        0x00000002
#define FLASHIF_PIO_RXFIFO_EMPTY_INIT           0x0
/*
 *  FLASHIF_PIO_RXFIFO_FULL bit field defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_RXFIFO_FULL_OFFSETADDRESS   FLASHIF_PIO_RXFIFO_STATUS_OFFSETADDRESS
#define FLASHIF_PIO_RXFIFO_FULL_BITOFFSET       0
#define FLASHIF_PIO_RXFIFO_FULL_BITFIELDSIZE    1
#define FLASHIF_PIO_RXFIFO_FULL_BITMASK         0x00000001
#define FLASHIF_PIO_RXFIFO_FULL_INIT            0x0
#endif

/*
 *  FLASHIF_PIO_REQ register defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_REQ_OFFSETADDRESS  0x00000410  /* RW */
#define FLASHIF_PIO_REQ_BITOFFSET      0
#define FLASHIF_PIO_REQ_BITFIELDSIZE   32
#define FLASHIF_PIO_REQ_BITMASK        0xFFFFFFFF
#define FLASHIF_PIO_REQ_INIT           0x00000000
/*
 *  FLASHIF_PIO_REQ_F bit field defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_REQ_F_OFFSETADDRESS         FLASHIF_PIO_REQ_OFFSETADDRESS
#define FLASHIF_PIO_REQ_F_BITOFFSET             0
#define FLASHIF_PIO_REQ_F_BITFIELDSIZE          1
#define FLASHIF_PIO_REQ_F_BITMASK               0x00000001
#define FLASHIF_PIO_REQ_F_INIT                  0x0

/*
 *  FLASHIF_PIO_GNT register defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_GNT_OFFSETADDRESS  0x00000414  /* RW */
#define FLASHIF_PIO_GNT_BITOFFSET      0
#define FLASHIF_PIO_GNT_BITFIELDSIZE   32
#define FLASHIF_PIO_GNT_BITMASK        0xFFFFFFFF
#define FLASHIF_PIO_GNT_INIT           0x00000000
/*
 *  FLASHIF_PIO_GNT_F bit field defines
 ****************************************************************************************
 */
#define FLASHIF_PIO_GNT_F_OFFSETADDRESS         FLASHIF_PIO_GNT_OFFSETADDRESS
#define FLASHIF_PIO_GNT_F_BITOFFSET             0
#define FLASHIF_PIO_GNT_F_BITFIELDSIZE          1
#define FLASHIF_PIO_GNT_F_BITMASK               0x00000001
#define FLASHIF_PIO_GNT_F_INIT                  0x0
#endif
