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
* $RCSfile: gsn_reg_flashif_op.h,v $
*
* Description : This file contains flash if operation macros.
******************************************************************************/

#ifndef _REG_FLASHIF_OP_H
#define _REG_FLASHIF_OP_H

/***************************************************
 *
 *             FLASHIF
 *
 ***************************************************/


/*
 *  FLASHIF_CTL register macros
 ****************************************************************************************
 */
#define FLASHIF_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_CTL))
#define FLASHIF_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_CTL, (value))
#define FLASHIF_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_CTL) | (value))
#define FLASHIF_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_CTL) & (~(value)))

/*
 *  FLASHIF_WLAN_DMA_EN bit field macros
 ****************************************************************************************
 */
#define FLASHIF_WLAN_DMA_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_WLAN_DMA_EN)
#define FLASHIF_WLAN_DMA_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_WLAN_DMA_EN, 1)
#define FLASHIF_WLAN_DMA_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_WLAN_DMA_EN, 0)

/*
 *  FLASHIF_APP_DMA_EN bit field macros
 ****************************************************************************************
 */
#define FLASHIF_APP_DMA_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_APP_DMA_EN)
#define FLASHIF_APP_DMA_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_APP_DMA_EN, 1)
#define FLASHIF_APP_DMA_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_APP_DMA_EN, 0)

/*
 *  FLASHIF_EN bit field macros
 ****************************************************************************************
 */
#define FLASHIF_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_EN)
#define FLASHIF_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_EN, 1)
#define FLASHIF_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_EN, 0)


/*
 *  FLASHIF_STATUS register macros
 ****************************************************************************************
 */
#define FLASHIF_STATUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_STATUS))
#define FLASHIF_STATUS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_STATUS, (value))
#define FLASHIF_STATUS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_STATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_STATUS) | (value))
#define FLASHIF_STATUS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_STATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_STATUS) & (~(value)))

/*
 *  FLASHIF_DMA_STATUS bit field macros
 ****************************************************************************************
 */
#define FLASHIF_DMA_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_DMA_STATUS)
#define FLASHIF_DMA_STATUS_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_DMA_STATUS, (value))

/*
 *  FLASHIF_ACTIVE bit field macros
 ****************************************************************************************
 */
#define FLASHIF_ACTIVE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_ACTIVE)
#define FLASHIF_ACTIVE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_ACTIVE, 1)
#define FLASHIF_ACTIVE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_ACTIVE, 0)

/*
 *  FLASHIF_PIO_RXFIFO_FULL bit field macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_RXFIFO_FULL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_PIO_RXFIFO_FULL)
#define FLASHIF_PIO_RXFIFO_FULL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_RXFIFO_FULL, 1)
#define FLASHIF_PIO_RXFIFO_FULL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_RXFIFO_FULL, 0)

/*
 *  FLASHIF_PIO_RXFIFO_EMPTY bit field macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_RXFIFO_EMPTY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_PIO_RXFIFO_EMPTY)
#define FLASHIF_PIO_RXFIFO_EMPTY_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_RXFIFO_EMPTY, 1)
#define FLASHIF_PIO_RXFIFO_EMPTY_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_RXFIFO_EMPTY, 0)

/*
 *  FLASHIF_PIO_TXFIFO_FULL bit field macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_TXFIFO_FULL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_PIO_TXFIFO_FULL)
#define FLASHIF_PIO_TXFIFO_FULL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_TXFIFO_FULL, 1)
#define FLASHIF_PIO_TXFIFO_FULL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_TXFIFO_FULL, 0)

/*
 *  FLASHIF_PIO_TXFIFO_EMPTY bit field macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_TXFIFO_EMPTY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_PIO_TXFIFO_EMPTY)
#define FLASHIF_PIO_TXFIFO_EMPTY_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_TXFIFO_EMPTY, 1)
#define FLASHIF_PIO_TXFIFO_EMPTY_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_TXFIFO_EMPTY, 0)


/*
 *  FLASHIF_DMACTL register macros
 ****************************************************************************************
 */
#define FLASHIF_DMACTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_DMACTL))
#define FLASHIF_DMACTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_DMACTL, (value))
#define FLASHIF_DMACTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_DMACTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_DMACTL) | (value))
#define FLASHIF_DMACTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_DMACTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_DMACTL) & (~(value)))

/*
 *  FLASHIF_DMA_DUMMY_BYTECOUNT bit field macros
 ****************************************************************************************
 */
#define FLASHIF_DMA_DUMMY_BYTECOUNT_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_DMA_DUMMY_BYTECOUNT)
#define FLASHIF_DMA_DUMMY_BYTECOUNT_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_DMA_DUMMY_BYTECOUNT, (value))

/*
 *  FLASHIF_DMA_DATA_BITLANES bit field macros
 ****************************************************************************************
 */
#define FLASHIF_DMA_DATA_BITLANES_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_DMA_DATA_BITLANES)
#define FLASHIF_DMA_DATA_BITLANES_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_DMA_DATA_BITLANES, (value))

/*
 *  FLASHIF_DMA_DUMMY_BITLANES bit field macros
 ****************************************************************************************
 */
#define FLASHIF_DMA_DUMMY_BITLANES_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_DMA_DUMMY_BITLANES)
#define FLASHIF_DMA_DUMMY_BITLANES_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_DMA_DUMMY_BITLANES, (value))

/*
 *  FLASHIF_DMA_ADDR_BITLANES bit field macros
 ****************************************************************************************
 */
#define FLASHIF_DMA_ADDR_BITLANES_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_DMA_ADDR_BITLANES)
#define FLASHIF_DMA_ADDR_BITLANES_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_DMA_ADDR_BITLANES, (value))

/*
 *  FLASHIF_DMA_CMD_BITLANES bit field macros
 ****************************************************************************************
 */
#define FLASHIF_DMA_CMD_BITLANES_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_DMA_CMD_BITLANES)
#define FLASHIF_DMA_CMD_BITLANES_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_DMA_CMD_BITLANES, (value))

/*
 *  FLASHIF_DMA_DUMMY_CYCLECOUNT bit field macros
 ****************************************************************************************
 */
#define FLASHIF_DMA_DUMMY_CYCLECOUNT_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_DMA_DUMMY_CYCLECOUNT)
#define FLASHIF_DMA_DUMMY_CYCLECOUNT_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_DMA_DUMMY_CYCLECOUNT, 1)
#define FLASHIF_DMA_DUMMY_CYCLECOUNT_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_DMA_DUMMY_CYCLECOUNT, 0)

/*
 *  FLASHIF_DMA_DUMMY_BYTESNONZERO bit field macros
 ****************************************************************************************
 */
#define FLASHIF_DMA_DUMMY_BYTESNONZERO_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_DMA_DUMMY_BYTESNONZERO)
#define FLASHIF_DMA_DUMMY_BYTESNONZERO_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_DMA_DUMMY_BYTESNONZERO, 1)
#define FLASHIF_DMA_DUMMY_BYTESNONZERO_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_DMA_DUMMY_BYTESNONZERO, 0)

/*
 *  FLASHIF_DMA_ADDR_BYTECOUNT bit field macros
 ****************************************************************************************
 */
#define FLASHIF_DMA_ADDR_BYTECOUNT_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_DMA_ADDR_BYTECOUNT)
#define FLASHIF_DMA_ADDR_BYTECOUNT_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_DMA_ADDR_BYTECOUNT, (value))

/*
 *  FLASHIF_DMA_CMD_BYTECOUNT bit field macros
 ****************************************************************************************
 */
#define FLASHIF_DMA_CMD_BYTECOUNT_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_DMA_CMD_BYTECOUNT)
#define FLASHIF_DMA_CMD_BYTECOUNT_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_DMA_CMD_BYTECOUNT, (value))

/*
 *  FLASHIF_DMA_DIRECTION bit field macros
 ****************************************************************************************
 */
#define FLASHIF_DMA_DIRECTION_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_DMA_DIRECTION)
#define FLASHIF_DMA_DIRECTION_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_DMA_DIRECTION, 1)
#define FLASHIF_DMA_DIRECTION_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_DMA_DIRECTION, 0)


/*
 *  FLASHIF_DMACMD register macros
 ****************************************************************************************
 */
#define FLASHIF_DMACMD_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_DMACMD))
#define FLASHIF_DMACMD_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_DMACMD, (value))
#define FLASHIF_DMACMD_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_DMACMD, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_DMACMD) | (value))
#define FLASHIF_DMACMD_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_DMACMD, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_DMACMD) & (~(value)))

/*
 *  FLASHIF_DMACMD_WORD bit field macros
 ****************************************************************************************
 */
#define FLASHIF_DMACMD_WORD_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_DMACMD_WORD)
#define FLASHIF_DMACMD_WORD_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_DMACMD_WORD, (value))


/*
 *  FLASHIF_PIO_TXFIFO register macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_TXFIFO_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_TXFIFO))
#define FLASHIF_PIO_TXFIFO_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_TXFIFO, (value))
#define FLASHIF_PIO_TXFIFO_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_TXFIFO, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_TXFIFO) | (value))
#define FLASHIF_PIO_TXFIFO_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_TXFIFO, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_TXFIFO) & (~(value)))

/*
 *  FLASHIF_PIO_TXFIFO_DATA bit field macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_TXFIFO_DATA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_PIO_TXFIFO_DATA)
#define FLASHIF_PIO_TXFIFO_DATA_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_TXFIFO_DATA, (value))


/*
 *  FLASHIF_PIO_TXFIFO_STATUS register macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_TXFIFO_STATUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_TXFIFO_STATUS))
#define FLASHIF_PIO_TXFIFO_STATUS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_TXFIFO_STATUS, (value))
#define FLASHIF_PIO_TXFIFO_STATUS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_TXFIFO_STATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_TXFIFO_STATUS) | (value))
#define FLASHIF_PIO_TXFIFO_STATUS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_TXFIFO_STATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_TXFIFO_STATUS) & (~(value)))

#if 0
/*
 *  FLASHIF_PIO_TXFIFO_EMPTY bit field macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_TXFIFO_EMPTY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_PIO_TXFIFO_EMPTY)
#define FLASHIF_PIO_TXFIFO_EMPTY_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_TXFIFO_EMPTY, 1)
#define FLASHIF_PIO_TXFIFO_EMPTY_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_TXFIFO_EMPTY, 0)

/*
 *  FLASHIF_PIO_TXFIFO_FULL bit field macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_TXFIFO_FULL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_PIO_TXFIFO_FULL)
#define FLASHIF_PIO_TXFIFO_FULL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_TXFIFO_FULL, 1)
#define FLASHIF_PIO_TXFIFO_FULL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_TXFIFO_FULL, 0)
#endif

/*
 *  FLASHIF_PIO_RXFIFO register macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_RXFIFO_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_RXFIFO))
#define FLASHIF_PIO_RXFIFO_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_RXFIFO, (value))
#define FLASHIF_PIO_RXFIFO_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_RXFIFO, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_RXFIFO) | (value))
#define FLASHIF_PIO_RXFIFO_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_RXFIFO, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_RXFIFO) & (~(value)))

/*
 *  FLASHIF_PIO_RXFIFO_DATA bit field macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_RXFIFO_DATA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_PIO_RXFIFO_DATA)
#define FLASHIF_PIO_RXFIFO_DATA_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_RXFIFO_DATA, (value))


/*
 *  FLASHIF_PIO_RXFIFO_STATUS register macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_RXFIFO_STATUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_RXFIFO_STATUS))
#define FLASHIF_PIO_RXFIFO_STATUS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_RXFIFO_STATUS, (value))
#define FLASHIF_PIO_RXFIFO_STATUS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_RXFIFO_STATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_RXFIFO_STATUS) | (value))
#define FLASHIF_PIO_RXFIFO_STATUS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_RXFIFO_STATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_RXFIFO_STATUS) & (~(value)))

#if 0
/*
 *  FLASHIF_PIO_RXFIFO_EMPTY bit field macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_RXFIFO_EMPTY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_PIO_RXFIFO_EMPTY)
#define FLASHIF_PIO_RXFIFO_EMPTY_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_RXFIFO_EMPTY, 1)
#define FLASHIF_PIO_RXFIFO_EMPTY_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_RXFIFO_EMPTY, 0)

/*
 *  FLASHIF_PIO_RXFIFO_FULL bit field macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_RXFIFO_FULL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_PIO_RXFIFO_FULL)
#define FLASHIF_PIO_RXFIFO_FULL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_RXFIFO_FULL, 1)
#define FLASHIF_PIO_RXFIFO_FULL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_RXFIFO_FULL, 0)
#endif

/*
 *  FLASHIF_PIO_REQ register macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_REQ_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_REQ))
#define FLASHIF_PIO_REQ_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_REQ, (value))
#define FLASHIF_PIO_REQ_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_REQ, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_REQ) | (value))
#define FLASHIF_PIO_REQ_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_REQ, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_REQ) & (~(value)))

/*
 *  FLASHIF_PIO_REQ_F bit field macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_REQ_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_PIO_REQ_F)
#define FLASHIF_PIO_REQ_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_REQ_F, 1)
#define FLASHIF_PIO_REQ_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_REQ_F, 0)


/*
 *  FLASHIF_PIO_GNT register macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_GNT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_GNT))
#define FLASHIF_PIO_GNT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_GNT, (value))
#define FLASHIF_PIO_GNT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_GNT, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_GNT) | (value))
#define FLASHIF_PIO_GNT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_GNT, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHIF_PIO_GNT) & (~(value)))

/*
 *  FLASHIF_PIO_GNT_F bit field macros
 ****************************************************************************************
 */
#define FLASHIF_PIO_GNT_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHIF_PIO_GNT_F)
#define FLASHIF_PIO_GNT_F_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_GNT_F, 1)
#define FLASHIF_PIO_GNT_F_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHIF_PIO_GNT_F, 0)

#endif
