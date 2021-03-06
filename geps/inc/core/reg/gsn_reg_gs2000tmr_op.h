/*
 ****************************************************************************************
 * reg_gs2000tmr_mac.h
 *
 * Copyright (C) NewLogic 2003-2005
 *
 * Project: LPX Software
 *
 * Description:
 *    File generated by reg_build.py from ..\HWdriver\header\xml\GS2000TMR.xml
 *
 *
 * Attention : This file must be used with precaution. Somes of its macros can be
 *             non-pertinent. But the original XML file doesn't allow to be pertinent.
 *             So don't include this file as header file. Copy/Paste is preferable.
 *
 ****************************************************************************************
 */

#ifndef _REG_GS2000TMR_MAC_H
#define _REG_GS2000TMR_MAC_H

/***************************************************
 *
 *             GS2000TMR
 *
 ***************************************************/


/*
 *  GS2000TMR_PCOUNT_LSB register macros
 ****************************************************************************************
 */
#define GS2000TMR_PCOUNT_LSB_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_PCOUNT_LSB))

/*
 *  GS2000TMR_COUNT_LSB bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_COUNT_LSB_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_COUNT_LSB)
#define GS2000TMR_COUNT_LSB_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_COUNT_LSB, (value))


/*
 *  GS2000TMR_PCOUNT_MSB register macros
 ****************************************************************************************
 */
#define GS2000TMR_PCOUNT_MSB_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_PCOUNT_MSB))

/*
 *  GS2000TMR_COUNT_MSB bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_COUNT_MSB_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_COUNT_MSB)


/*
 *  GS2000TMR_VALID register macros
 ****************************************************************************************
 */
#define GS2000TMR_VALID_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_VALID))
#define GS2000TMR_VALID_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_VALID, (value))
#define GS2000TMR_VALID_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_VALID, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_VALID) | (value))
#define GS2000TMR_VALID_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_VALID, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_VALID) & (~(value)))

/*
 *  GS2000TMR_COUNT_VALID bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_COUNT_VALID_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_COUNT_VALID, 1)


/*
 *  GS2000TMR_COMPARE_LSB register macros
 ****************************************************************************************
 */
#define GS2000TMR_COMPARE_LSB_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_LSB))
#define GS2000TMR_COMPARE_LSB_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_LSB, (value))
#define GS2000TMR_COMPARE_LSB_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_LSB, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_LSB) | (value))
#define GS2000TMR_COMPARE_LSB_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_LSB, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_LSB) & (~(value)))

/*
 *  GS2000TMR_COMP_LSB bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_COMP_LSB_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_COMP_LSB)
#define GS2000TMR_COMP_LSB_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_COMP_LSB, (value))


/*
 *  GS2000TMR_COMPARE_MSB register macros
 ****************************************************************************************
 */
#define GS2000TMR_COMPARE_MSB_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_MSB))
#define GS2000TMR_COMPARE_MSB_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_MSB, (value))
#define GS2000TMR_COMPARE_MSB_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_MSB, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_MSB) | (value))
#define GS2000TMR_COMPARE_MSB_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_MSB, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_MSB) & (~(value)))

/*
 *  GS2000TMR_COMP_MSB bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_COMP_MSB_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_COMP_MSB)
#define GS2000TMR_COMP_MSB_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_COMP_MSB, (value))


/*
 *  GS2000TMR_COMPARE_IRQ_STATUS register macros
 ****************************************************************************************
 */
#define GS2000TMR_COMPARE_IRQ_STATUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_STATUS))

/*
 *  GS2000TMR_COMP_IRQ_STATUS bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_COMP_IRQ_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_COMP_IRQ_STATUS)


/*
 *  GS2000TMR_COMPARE_IRQ_MASK register macros
 ****************************************************************************************
 */
#define GS2000TMR_COMPARE_IRQ_MASK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_MASK))
#define GS2000TMR_COMPARE_IRQ_MASK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_MASK, (value))
#define GS2000TMR_COMPARE_IRQ_MASK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_MASK) | (value))
#define GS2000TMR_COMPARE_IRQ_MASK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_MASK) & (~(value)))

/*
 *  GS2000TMR_COMP_IRQ_MASK bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_COMP_IRQ_MASK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_COMP_IRQ_MASK)
#define GS2000TMR_COMP_IRQ_MASK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_COMP_IRQ_MASK, 1)
#define GS2000TMR_COMP_IRQ_MASK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_COMP_IRQ_MASK, 0)


/*
 *  GS2000TMR_COMPARE_IRQ_CLEAR register macros
 ****************************************************************************************
 */
#define GS2000TMR_COMPARE_IRQ_CLEAR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_CLEAR))
#define GS2000TMR_COMPARE_IRQ_CLEAR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_CLEAR, (value))
#define GS2000TMR_COMPARE_IRQ_CLEAR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_CLEAR, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_CLEAR) | (value))
#define GS2000TMR_COMPARE_IRQ_CLEAR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_CLEAR, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_CLEAR) & (~(value)))

/*
 *  GS2000TMR_COMP_IRQ_CLEAR bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_COMP_IRQ_CLEAR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_COMP_IRQ_CLEAR)
#define GS2000TMR_COMP_IRQ_CLEAR_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_COMP_IRQ_CLEAR, 1)
#define GS2000TMR_COMP_IRQ_CLEAR_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_COMP_IRQ_CLEAR, 0)


/*
 *  GS2000TMR_COMPARE_IRQ_SET register macros
 ****************************************************************************************
 */
#define GS2000TMR_COMPARE_IRQ_SET_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_SET))
#define GS2000TMR_COMPARE_IRQ_SET_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_SET, (value))
#define GS2000TMR_COMPARE_IRQ_SET_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_SET, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_SET) | (value))
#define GS2000TMR_COMPARE_IRQ_SET_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_SET, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_COMPARE_IRQ_SET) & (~(value)))

/*
 *  GS2000TMR_COMP_IRQ_SET bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_COMP_IRQ_SET_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_COMP_IRQ_SET)
#define GS2000TMR_COMP_IRQ_SET_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_COMP_IRQ_SET, 1)
#define GS2000TMR_COMP_IRQ_SET_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_COMP_IRQ_SET, 0)


/*
 *  GS2000TMR_ALARM_IRQ_STATUS register macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_IRQ_STATUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_STATUS))

/*
 *  GS2000TMR_ALARM_0_IRQ_STATUS bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_0_IRQ_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_0_IRQ_STATUS)

/*
 *  GS2000TMR_ALARM_1_IRQ_STATUS bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_1_IRQ_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_1_IRQ_STATUS)

/*
 *  GS2000TMR_ALARM_2_IRQ_STATUS bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_2_IRQ_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_2_IRQ_STATUS)

/*
 *  GS2000TMR_ALARM_3_IRQ_STATUS bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_3_IRQ_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_3_IRQ_STATUS)

/*
 *  GS2000TMR_ALARM_4_IRQ_STATUS bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_4_IRQ_STATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_4_IRQ_STATUS)


/*
 *  GS2000TMR_ALARM_IRQ_MASK register macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_IRQ_MASK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_MASK))
#define GS2000TMR_ALARM_IRQ_MASK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_MASK, (value))
#define GS2000TMR_ALARM_IRQ_MASK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_MASK) | (value))
#define GS2000TMR_ALARM_IRQ_MASK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_MASK) & (~(value)))

/*
 *  GS2000TMR_ALARM_0_IRQ_MASK bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_0_IRQ_MASK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_0_IRQ_MASK)
#define GS2000TMR_ALARM_0_IRQ_MASK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_0_IRQ_MASK, 1)
#define GS2000TMR_ALARM_0_IRQ_MASK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_0_IRQ_MASK, 0)

/*
 *  GS2000TMR_ALARM_1_IRQ_MASK bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_1_IRQ_MASK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_1_IRQ_MASK)
#define GS2000TMR_ALARM_1_IRQ_MASK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_1_IRQ_MASK, 1)
#define GS2000TMR_ALARM_1_IRQ_MASK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_1_IRQ_MASK, 0)

/*
 *  GS2000TMR_ALARM_2_IRQ_MASK bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_2_IRQ_MASK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_2_IRQ_MASK)
#define GS2000TMR_ALARM_2_IRQ_MASK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_2_IRQ_MASK, 1)
#define GS2000TMR_ALARM_2_IRQ_MASK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_2_IRQ_MASK, 0)

/*
 *  GS2000TMR_ALARM_3_IRQ_MASK bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_3_IRQ_MASK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_3_IRQ_MASK)
#define GS2000TMR_ALARM_3_IRQ_MASK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_3_IRQ_MASK, 1)
#define GS2000TMR_ALARM_3_IRQ_MASK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_3_IRQ_MASK, 0)

/*
 *  GS2000TMR_ALARM_4_IRQ_MASK bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_4_IRQ_MASK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_4_IRQ_MASK)
#define GS2000TMR_ALARM_4_IRQ_MASK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_4_IRQ_MASK, 1)
#define GS2000TMR_ALARM_4_IRQ_MASK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_4_IRQ_MASK, 0)


/*
 *  GS2000TMR_ALARM_IRQ_CLEAR register macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_IRQ_CLEAR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_CLEAR))
#define GS2000TMR_ALARM_IRQ_CLEAR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_CLEAR, (value))
#define GS2000TMR_ALARM_IRQ_CLEAR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_CLEAR, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_CLEAR) | (value))
#define GS2000TMR_ALARM_IRQ_CLEAR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_CLEAR, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_CLEAR) & (~(value)))

/*
 *  GS2000TMR_ALARM_0_IRQ_CLEAR bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_0_IRQ_CLEAR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_0_IRQ_CLEAR)
#define GS2000TMR_ALARM_0_IRQ_CLEAR_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_0_IRQ_CLEAR, 1)
#define GS2000TMR_ALARM_0_IRQ_CLEAR_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_0_IRQ_CLEAR, 0)

/*
 *  GS2000TMR_ALARM_1_IRQ_CLEAR bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_1_IRQ_CLEAR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_1_IRQ_CLEAR)
#define GS2000TMR_ALARM_1_IRQ_CLEAR_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_1_IRQ_CLEAR, 1)
#define GS2000TMR_ALARM_1_IRQ_CLEAR_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_1_IRQ_CLEAR, 0)

/*
 *  GS2000TMR_ALARM_2_IRQ_CLEAR bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_2_IRQ_CLEAR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_2_IRQ_CLEAR)
#define GS2000TMR_ALARM_2_IRQ_CLEAR_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_2_IRQ_CLEAR, 1)
#define GS2000TMR_ALARM_2_IRQ_CLEAR_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_2_IRQ_CLEAR, 0)

/*
 *  GS2000TMR_ALARM_3_IRQ_CLEAR bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_3_IRQ_CLEAR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_3_IRQ_CLEAR)
#define GS2000TMR_ALARM_3_IRQ_CLEAR_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_3_IRQ_CLEAR, 1)
#define GS2000TMR_ALARM_3_IRQ_CLEAR_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_3_IRQ_CLEAR, 0)

/*
 *  GS2000TMR_ALARM_4_IRQ_CLEAR bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_4_IRQ_CLEAR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_4_IRQ_CLEAR)
#define GS2000TMR_ALARM_4_IRQ_CLEAR_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_4_IRQ_CLEAR, 1)
#define GS2000TMR_ALARM_4_IRQ_CLEAR_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_4_IRQ_CLEAR, 0)


/*
 *  GS2000TMR_ALARM_IRQ_SET register macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_IRQ_SET_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_SET))
#define GS2000TMR_ALARM_IRQ_SET_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_SET, (value))
#define GS2000TMR_ALARM_IRQ_SET_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_SET, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_SET) | (value))
#define GS2000TMR_ALARM_IRQ_SET_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_SET, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_IRQ_SET) & (~(value)))

/*
 *  GS2000TMR_ALARM_0_IRQ_SET bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_0_IRQ_SET_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_0_IRQ_SET)
#define GS2000TMR_ALARM_0_IRQ_SET_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_0_IRQ_SET, 1)
#define GS2000TMR_ALARM_0_IRQ_SET_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_0_IRQ_SET, 0)

/*
 *  GS2000TMR_ALARM_1_IRQ_SET bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_1_IRQ_SET_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_1_IRQ_SET)
#define GS2000TMR_ALARM_1_IRQ_SET_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_1_IRQ_SET, 1)
#define GS2000TMR_ALARM_1_IRQ_SET_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_1_IRQ_SET, 0)

/*
 *  GS2000TMR_ALARM_2_IRQ_SET bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_2_IRQ_SET_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_2_IRQ_SET)
#define GS2000TMR_ALARM_2_IRQ_SET_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_2_IRQ_SET, 1)
#define GS2000TMR_ALARM_2_IRQ_SET_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_2_IRQ_SET, 0)

/*
 *  GS2000TMR_ALARM_3_IRQ_SET bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_3_IRQ_SET_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_3_IRQ_SET)
#define GS2000TMR_ALARM_3_IRQ_SET_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_3_IRQ_SET, 1)
#define GS2000TMR_ALARM_3_IRQ_SET_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_3_IRQ_SET, 0)

/*
 *  GS2000TMR_ALARM_4_IRQ_SET bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_4_IRQ_SET_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_4_IRQ_SET)
#define GS2000TMR_ALARM_4_IRQ_SET_SET(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_4_IRQ_SET, 1)
#define GS2000TMR_ALARM_4_IRQ_SET_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_4_IRQ_SET, 0)


/*
 *  GS2000TMR_ALARM_TS0 register macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_TS0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS0))
#define GS2000TMR_ALARM_TS0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS0, (value))
#define GS2000TMR_ALARM_TS0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS0) | (value))
#define GS2000TMR_ALARM_TS0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS0) & (~(value)))

/*
 *  GS2000TMR_ALARM_TS_0 bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_TS_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_TS_0)
#define GS2000TMR_ALARM_TS_0_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_TS_0, (value))


/*
 *  GS2000TMR_ALARM_TS1 register macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_TS1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS1))
#define GS2000TMR_ALARM_TS1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS1, (value))
#define GS2000TMR_ALARM_TS1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS1) | (value))
#define GS2000TMR_ALARM_TS1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS1) & (~(value)))

/*
 *  GS2000TMR_ALARM_TS_1 bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_TS_1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_TS_1)
#define GS2000TMR_ALARM_TS_1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_TS_1, (value))


/*
 *  GS2000TMR_ALARM_TS2 register macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_TS2_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS2))
#define GS2000TMR_ALARM_TS2_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS2, (value))
#define GS2000TMR_ALARM_TS2_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS2, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS2) | (value))
#define GS2000TMR_ALARM_TS2_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS2, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS2) & (~(value)))

/*
 *  GS2000TMR_ALARM_TS_2 bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_TS_2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_TS_2)
#define GS2000TMR_ALARM_TS_2_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_TS_2, (value))


/*
 *  GS2000TMR_ALARM_TS3 register macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_TS3_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS3))
#define GS2000TMR_ALARM_TS3_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS3, (value))
#define GS2000TMR_ALARM_TS3_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS3, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS3) | (value))
#define GS2000TMR_ALARM_TS3_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS3, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS3) & (~(value)))

/*
 *  GS2000TMR_ALARM_TS_3 bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_TS_3_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_TS_3)
#define GS2000TMR_ALARM_TS_3_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_TS_3, (value))


/*
 *  GS2000TMR_ALARM_TS4 register macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_TS4_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS4))
#define GS2000TMR_ALARM_TS4_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS4, (value))
#define GS2000TMR_ALARM_TS4_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS4, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS4) | (value))
#define GS2000TMR_ALARM_TS4_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS4, GET_WORD_EXCLUSIVE_BITFIELD(addr, GS2000TMR_ALARM_TS4) & (~(value)))

/*
 *  GS2000TMR_ALARM_TS_4 bit field macros
 ****************************************************************************************
 */
#define GS2000TMR_ALARM_TS_4_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_TS_4)
#define GS2000TMR_ALARM_TS_4_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GS2000TMR_ALARM_TS_4, (value))

#endif
