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
* $RCSfile: gsn_reg_wdog_op.h,v $
*
* Description : This file contains watch dog register operations.
*****************************************************************************/


#ifndef _REG_WDOG_MAC_H
#define _REG_WDOG_MAC_H

/***************************************************
 *
 *             WDOG
 *
 ***************************************************/


/*
 *  WDOG_LOAD register macros
 ****************************************************************************************
 */
#define WDOG_LOAD_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, WDOG_LOAD))
#define WDOG_LOAD_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, WDOG_LOAD, (value))
#define WDOG_LOAD_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, WDOG_LOAD, GET_WORD_EXCLUSIVE_BITFIELD(addr, WDOG_LOAD) | (value))
#define WDOG_LOAD_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, WDOG_LOAD, GET_WORD_EXCLUSIVE_BITFIELD(addr, WDOG_LOAD) & (~(value)))

/*
 *  WDOG_LOAD_VAL bit field macros
 ****************************************************************************************
 */
#define WDOG_LOAD_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, WDOG_LOAD_VAL)
#define WDOG_LOAD_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, WDOG_LOAD_VAL, (value))


/*
 *  WDOG_COUNTER register macros
 ****************************************************************************************
 */
#define WDOG_COUNTER_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, WDOG_COUNTER))

/*
 *  WDOG_COUNTER_VAL bit field macros
 ****************************************************************************************
 */
#define WDOG_COUNTER_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, WDOG_COUNTER_VAL)


/*
 *  WDOG_CONTROL register macros
 ****************************************************************************************
 */
#define WDOG_CONTROL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, WDOG_CONTROL))

/*
 *  WDOG_INT_EN bit field macros
 ****************************************************************************************
 */
#define WDOG_INT_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, WDOG_INT_EN)
#define WDOG_INT_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, WDOG_INT_EN, 1)
#define WDOG_INT_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, WDOG_INT_EN, 0)

/*
 *  WDOG_RESET_EN bit field macros
 ****************************************************************************************
 */
#define WDOG_RESET_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, WDOG_RESET_EN)
#define WDOG_RESET_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, WDOG_RESET_EN, 1)
#define WDOG_RESET_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, WDOG_RESET_EN, 0)


/*
 *  WDOG_INT_CLR register macros
 ****************************************************************************************
 */
#define WDOG_INT_CLR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, WDOG_INT_CLR))

/*
 *  WDOG_INT_CLEAR bit field macros
 ****************************************************************************************
 */
#define WDOG_INT_CLEAR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, WDOG_INT_CLEAR)
#define WDOG_INT_CLEAR_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, WDOG_INT_CLEAR, (value))


/*
 *  WDOG_RAW_INT_STAT register macros
 ****************************************************************************************
 */
#define WDOG_RAW_INT_STAT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, WDOG_RAW_INT_STAT))

/*
 *  WDOG_RAW_INT_STATUS bit field macros
 ****************************************************************************************
 */
#define WDOG_RAW_INT_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, WDOG_RAW_INT_STATUS)


/*
 *  WDOG_MASKED_INT_STAT register macros
 ****************************************************************************************
 */
#define WDOG_MASKED_INT_STAT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, WDOG_MASKED_INT_STAT))

/*
 *  WDOG_MASKED_INT_STATUS bit field macros
 ****************************************************************************************
 */
#define WDOG_MASKED_INT_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, WDOG_MASKED_INT_STATUS)


/*
 *  WDOG_LOCK register macros
 ****************************************************************************************
 */
#define WDOG_LOCK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, WDOG_LOCK))
#define WDOG_LOCK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, WDOG_LOCK, (value))
#define WDOG_LOCK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, WDOG_LOCK, GET_WORD_EXCLUSIVE_BITFIELD(addr, WDOG_LOCK) | (value))
#define WDOG_LOCK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, WDOG_LOCK, GET_WORD_EXCLUSIVE_BITFIELD(addr, WDOG_LOCK) & (~(value)))

/*
 *  WDOG_LOCK_VAL bit field macros
 ****************************************************************************************
 */
#define WDOG_LOCK_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, WDOG_LOCK_VAL)
#define WDOG_LOCK_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, WDOG_LOCK_VAL, (value))

#endif
