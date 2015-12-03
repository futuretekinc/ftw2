/******************************************************************************
*
*               COPYRIGHT (c) 20012-2013 GainSpan Corporation
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
* $RCSfile: gsn_reg_mb_op.h,v $
*
* Description : This file contains mailbox macro definitions.
******************************************************************************/

#ifndef _REG_MB_MAC_H
#define _REG_MB_MAC_H

/***************************************************
 *
 *             MB
 *
 ***************************************************/


/*
 *  MB_MB_RB_STATUS register macros
 ****************************************************************************************
 */
#define MB_MB_RB_STATUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_STATUS))

/*
 *  MB_RB_INT bit field macros
 ****************************************************************************************
 */
#define MB_RB_INT_GET(addr) \
        GET_WORD_BITFIELD_N(addr, MB_RB_INT)


/*
 *  MB_MB_RB_MASK register macros
 ****************************************************************************************
 */
#define MB_MB_RB_MASK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_MASK))
#define MB_MB_RB_MASK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_MASK, (value))
#define MB_MB_RB_MASK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_MASK) | (value))
#define MB_MB_RB_MASK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_MASK) & (~(value)))

/*
 *  MB_RB_MASK bit field macros
 ****************************************************************************************
 */
#define MB_RB_MASK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, MB_RB_MASK)
#define MB_RB_MASK_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, MB_RB_MASK, (value))


/*
 *  MB_MB_RB_CLEAR register macros
 ****************************************************************************************
 */
#define MB_MB_RB_CLEAR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_CLEAR))
#define MB_MB_RB_CLEAR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_CLEAR, (value))
#define MB_MB_RB_CLEAR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_CLEAR, GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_CLEAR) | (value))
#define MB_MB_RB_CLEAR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_CLEAR, GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_CLEAR) & (~(value)))

/*
 *  MB_RB_CLEAR bit field macros
 ****************************************************************************************
 */
#define MB_RB_CLEAR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, MB_RB_CLEAR)
#define MB_RB_CLEAR_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, MB_RB_CLEAR, (value))


/*
 *  MB_MB_RB_SET register macros
 ****************************************************************************************
 */
#define MB_MB_RB_SET_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_SET))
#define MB_MB_RB_SET_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_SET, (value))
#define MB_MB_RB_SET_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_SET, GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_SET) | (value))
#define MB_MB_RB_SET_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_SET, GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_SET) & (~(value)))

/*
 *  MB_RB_SET bit field macros
 ****************************************************************************************
 */
#define MB_RB_SET_GET(addr) \
        GET_WORD_BITFIELD_N(addr, MB_RB_SET)
#define MB_RB_SET_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, MB_RB_SET, (value))


/*
 *  MB_MB_SB_CONF register macros
 ****************************************************************************************
 */
#define MB_MB_SB_CONF_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_SB_CONF))
#define MB_MB_SB_CONF_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_SB_CONF, (value))
#define MB_MB_SB_CONF_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_SB_CONF, GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_SB_CONF) | (value))
#define MB_MB_SB_CONF_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_SB_CONF, GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_SB_CONF) & (~(value)))

/*
 *  MB_SB_CONF bit field macros
 ****************************************************************************************
 */
#define MB_SB_CONF_GET(addr) \
        GET_WORD_BITFIELD_N(addr, MB_SB_CONF)
#define MB_SB_CONF_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, MB_SB_CONF, (value))


/*
 *  MB_MB_SB_INT register macros
 ****************************************************************************************
 */
#define MB_MB_SB_INT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_SB_INT))
#define MB_MB_SB_INT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_SB_INT, (value))
#define MB_MB_SB_INT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_SB_INT, GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_SB_INT) | (value))
#define MB_MB_SB_INT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_SB_INT, GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_SB_INT) & (~(value)))

/*
 *  MB_SB_INT bit field macros
 ****************************************************************************************
 */
#define MB_SB_INT_GET(addr) \
        GET_WORD_BITFIELD_N(addr, MB_SB_INT)
#define MB_SB_INT_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, MB_SB_INT, (value))


/*
 *  MB_MB_SB_0 register macros
 ****************************************************************************************
 */
#define MB_MB_SB_0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_SB_0, (value))

/*
 *  MB_SB_0 bit field macros
 ****************************************************************************************
 */
#define MB_SB_0_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, MB_SB_0, (value))


/*
 *  MB_MB_SB_1 register macros
 ****************************************************************************************
 */
#define MB_MB_SB_1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_SB_1, (value))

/*
 *  MB_SB_1 bit field macros
 ****************************************************************************************
 */
#define MB_SB_1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, MB_SB_1, (value))


/*
 *  MB_MB_RB_0 register macros
 ****************************************************************************************
 */
#define MB_MB_RB_0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_0))

/*
 *  MB_RB_0 bit field macros
 ****************************************************************************************
 */
#define MB_RB_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, MB_RB_0)


/*
 *  MB_MB_RB_1 register macros
 ****************************************************************************************
 */
#define MB_MB_RB_1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, MB_MB_RB_1))

/*
 *  MB_RB_1 bit field macros
 ****************************************************************************************
 */
#define MB_RB_1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, MB_RB_1)

#endif
