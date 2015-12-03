/******************************************************************************
 *
 *               COPYRIGHT (c) 2012-2013 GainSpan Corporation
 *                         All Rights Reserved
 *
 * The source code contained or described herein and all documents
 * related to the source code ("Material") are owned by Gainspan
 * Corporation or its licensors.  Title to the Material remains
 * with Gainspan Corporation or its suppliers and licensors.
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
 * Unless otherwise agreed by Gainspan in writing, you may not remove or
 * alter this notice or any other notice embedded in Materials by Gainspan
 * or Gainspan's suppliers or licensors in any way.
 *
 * $RCSfile: gsn_reg_gpio_spec.h,v $
 *
 * Description:
 *      This file contains register specification for GPIO Driver
 *
 ******************************************************************************
 */

#ifndef _REG_GPIO_MAC_H
#define _REG_GPIO_MAC_H

/***************************************************
 *
 *             GPIO
 *
 ***************************************************/


/*
 *  GPIO_GPIO_IN_0 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_IN_0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_IN_0))
#define GPIO_GPIO_IN_0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_IN_0, (value))
#define GPIO_GPIO_IN_0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_IN_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_IN_0) | (value))
#define GPIO_GPIO_IN_0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_IN_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_IN_0) & (~(value)))

/*
 *  GPIO_IN_0 bit field macros
 ****************************************************************************************
 */
#define GPIO_IN_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_IN_0)


/*
 *  GPIO_GPIO_OUT_0 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_OUT_0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_OUT_0))
#define GPIO_GPIO_OUT_0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_OUT_0, (value))
#define GPIO_GPIO_OUT_0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_OUT_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_OUT_0) | (value))
#define GPIO_GPIO_OUT_0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_OUT_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_OUT_0) & (~(value)))

/*
 *  GPIO_OUT_0 bit field macros
 ****************************************************************************************
 */
#define GPIO_OUT_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_OUT_0)
#define GPIO_OUT_0_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GPIO_OUT_0, (value))


/*
 *  GPIO_GPIO_CTL_0 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_CTL_0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_CTL_0))
#define GPIO_GPIO_CTL_0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_CTL_0, (value))
#define GPIO_GPIO_CTL_0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_CTL_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_CTL_0) | (value))
#define GPIO_GPIO_CTL_0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_CTL_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_CTL_0) & (~(value)))

/*
 *  GPIO_CTL_0 bit field macros
 ****************************************************************************************
 */
#define GPIO_CTL_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_CTL_0)
#define GPIO_CTL_0_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GPIO_CTL_0, (value))


/*
 *  GPIO_GPIO_IN_1 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_IN_1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_IN_1))
#define GPIO_GPIO_IN_1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_IN_1, (value))
#define GPIO_GPIO_IN_1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_IN_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_IN_1) | (value))
#define GPIO_GPIO_IN_1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_IN_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_IN_1) & (~(value)))

/*
 *  GPIO_IN_1 bit field macros
 ****************************************************************************************
 */
#define GPIO_IN_1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_IN_1)


/*
 *  GPIO_GPIO_OUT_1 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_OUT_1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_OUT_1))
#define GPIO_GPIO_OUT_1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_OUT_1, (value))
#define GPIO_GPIO_OUT_1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_OUT_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_OUT_1) | (value))
#define GPIO_GPIO_OUT_1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_OUT_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_OUT_1) & (~(value)))

/*
 *  GPIO_OUT_1 bit field macros
 ****************************************************************************************
 */
#define GPIO_OUT_1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_OUT_1)
#define GPIO_OUT_1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GPIO_OUT_1, (value))


/*
 *  GPIO_GPIO_CTL_1 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_CTL_1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_CTL_1))
#define GPIO_GPIO_CTL_1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_CTL_1, (value))
#define GPIO_GPIO_CTL_1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_CTL_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_CTL_1) | (value))
#define GPIO_GPIO_CTL_1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_CTL_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_CTL_1) & (~(value)))

/*
 *  GPIO_CTL_1 bit field macros
 ****************************************************************************************
 */
#define GPIO_CTL_1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_CTL_1)
#define GPIO_CTL_1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GPIO_CTL_1, (value))


/*
 *  GPIO_GPIO_PE_IRQ_STATUS_0 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_PE_IRQ_STATUS_0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_STATUS_0))
#define GPIO_GPIO_PE_IRQ_STATUS_0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_STATUS_0, (value))
#define GPIO_GPIO_PE_IRQ_STATUS_0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_STATUS_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_STATUS_0) | (value))
#define GPIO_GPIO_PE_IRQ_STATUS_0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_STATUS_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_STATUS_0) & (~(value)))

/*
 *  GPIO_PE_IRQ_STATUS_0 bit field macros
 ****************************************************************************************
 */
#define GPIO_PE_IRQ_STATUS_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_PE_IRQ_STATUS_0)


/*
 *  GPIO_GPIO_PE_IRQ_MASK_0 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_PE_IRQ_MASK_0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_MASK_0))
#define GPIO_GPIO_PE_IRQ_MASK_0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_MASK_0, (value))
#define GPIO_GPIO_PE_IRQ_MASK_0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_MASK_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_MASK_0) | (value))
#define GPIO_GPIO_PE_IRQ_MASK_0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_MASK_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_MASK_0) & (~(value)))

/*
 *  GPIO_PE_IRQ_MASK_0 bit field macros
 ****************************************************************************************
 */
#define GPIO_PE_IRQ_MASK_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_PE_IRQ_MASK_0)
#define GPIO_PE_IRQ_MASK_0_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GPIO_PE_IRQ_MASK_0, (value))


/*
 *  GPIO_GPIO_PE_IRQ_CLEAR_0 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_PE_IRQ_CLEAR_0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_CLEAR_0))
#define GPIO_GPIO_PE_IRQ_CLEAR_0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_CLEAR_0, (value))
#define GPIO_GPIO_PE_IRQ_CLEAR_0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_CLEAR_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_CLEAR_0) | (value))
#define GPIO_GPIO_PE_IRQ_CLEAR_0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_CLEAR_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_CLEAR_0) & (~(value)))

/*
 *  GPIO_PE_IRQ_CLEAR_0 bit field macros
 ****************************************************************************************
 */
#define GPIO_PE_IRQ_CLEAR_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_PE_IRQ_CLEAR_0)
#define GPIO_PE_IRQ_CLEAR_0_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GPIO_PE_IRQ_CLEAR_0, (value))


/*
 *  GPIO_GPIO_PE_IRQ_SET_0 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_PE_IRQ_SET_0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_SET_0))
#define GPIO_GPIO_PE_IRQ_SET_0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_SET_0, (value))
#define GPIO_GPIO_PE_IRQ_SET_0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_SET_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_SET_0) | (value))
#define GPIO_GPIO_PE_IRQ_SET_0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_SET_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_SET_0) & (~(value)))

/*
 *  GPIO_PE_IRQ_SET_0 bit field macros
 ****************************************************************************************
 */
#define GPIO_PE_IRQ_SET_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_PE_IRQ_SET_0)
#define GPIO_PE_IRQ_SET_0_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GPIO_PE_IRQ_SET_0, (value))


/*
 *  GPIO_GPIO_PE_IRQ_STATUS_1 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_PE_IRQ_STATUS_1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_STATUS_1))
#define GPIO_GPIO_PE_IRQ_STATUS_1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_STATUS_1, (value))
#define GPIO_GPIO_PE_IRQ_STATUS_1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_STATUS_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_STATUS_1) | (value))
#define GPIO_GPIO_PE_IRQ_STATUS_1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_STATUS_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_STATUS_1) & (~(value)))

/*
 *  GPIO_PE_IRQ_STATUS_1 bit field macros
 ****************************************************************************************
 */
#define GPIO_PE_IRQ_STATUS_1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_PE_IRQ_STATUS_1)


/*
 *  GPIO_GPIO_PE_IRQ_MASK_1 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_PE_IRQ_MASK_1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_MASK_1))
#define GPIO_GPIO_PE_IRQ_MASK_1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_MASK_1, (value))
#define GPIO_GPIO_PE_IRQ_MASK_1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_MASK_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_MASK_1) | (value))
#define GPIO_GPIO_PE_IRQ_MASK_1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_MASK_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_MASK_1) & (~(value)))

/*
 *  GPIO_PE_IRQ_MASK_1 bit field macros
 ****************************************************************************************
 */
#define GPIO_PE_IRQ_MASK_1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_PE_IRQ_MASK_1)
#define GPIO_PE_IRQ_MASK_1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GPIO_PE_IRQ_MASK_1, (value))


/*
 *  GPIO_GPIO_PE_IRQ_CLEAR_1 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_PE_IRQ_CLEAR_1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_CLEAR_1))
#define GPIO_GPIO_PE_IRQ_CLEAR_1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_CLEAR_1, (value))
#define GPIO_GPIO_PE_IRQ_CLEAR_1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_CLEAR_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_CLEAR_1) | (value))
#define GPIO_GPIO_PE_IRQ_CLEAR_1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_CLEAR_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_CLEAR_1) & (~(value)))

/*
 *  GPIO_PE_IRQ_CLEAR_1 bit field macros
 ****************************************************************************************
 */
#define GPIO_PE_IRQ_CLEAR_1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_PE_IRQ_CLEAR_1)
#define GPIO_PE_IRQ_CLEAR_1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GPIO_PE_IRQ_CLEAR_1, (value))


/*
 *  GPIO_GPIO_PE_IRQ_SET_1 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_PE_IRQ_SET_1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_SET_1))
#define GPIO_GPIO_PE_IRQ_SET_1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_SET_1, (value))
#define GPIO_GPIO_PE_IRQ_SET_1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_SET_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_SET_1) | (value))
#define GPIO_GPIO_PE_IRQ_SET_1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_SET_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_PE_IRQ_SET_1) & (~(value)))

/*
 *  GPIO_PE_IRQ_SET_1 bit field macros
 ****************************************************************************************
 */
#define GPIO_PE_IRQ_SET_1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_PE_IRQ_SET_1)
#define GPIO_PE_IRQ_SET_1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GPIO_PE_IRQ_SET_1, (value))


/*
 *  GPIO_GPIO_NE_IRQ_STATUS_0 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_NE_IRQ_STATUS_0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_STATUS_0))
#define GPIO_GPIO_NE_IRQ_STATUS_0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_STATUS_0, (value))
#define GPIO_GPIO_NE_IRQ_STATUS_0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_STATUS_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_STATUS_0) | (value))
#define GPIO_GPIO_NE_IRQ_STATUS_0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_STATUS_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_STATUS_0) & (~(value)))

/*
 *  GPIO_NE_IRQ_STATUS_0 bit field macros
 ****************************************************************************************
 */
#define GPIO_NE_IRQ_STATUS_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_NE_IRQ_STATUS_0)


/*
 *  GPIO_GPIO_NE_IRQ_MASK_0 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_NE_IRQ_MASK_0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_MASK_0))
#define GPIO_GPIO_NE_IRQ_MASK_0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_MASK_0, (value))
#define GPIO_GPIO_NE_IRQ_MASK_0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_MASK_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_MASK_0) | (value))
#define GPIO_GPIO_NE_IRQ_MASK_0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_MASK_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_MASK_0) & (~(value)))

/*
 *  GPIO_NE_IRQ_MASK_0 bit field macros
 ****************************************************************************************
 */
#define GPIO_NE_IRQ_MASK_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_NE_IRQ_MASK_0)
#define GPIO_NE_IRQ_MASK_0_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GPIO_NE_IRQ_MASK_0, (value))


/*
 *  GPIO_GPIO_NE_IRQ_CLEAR_0 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_NE_IRQ_CLEAR_0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_CLEAR_0))
#define GPIO_GPIO_NE_IRQ_CLEAR_0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_CLEAR_0, (value))
#define GPIO_GPIO_NE_IRQ_CLEAR_0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_CLEAR_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_CLEAR_0) | (value))
#define GPIO_GPIO_NE_IRQ_CLEAR_0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_CLEAR_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_CLEAR_0) & (~(value)))

/*
 *  GPIO_NE_IRQ_CLEAR_0 bit field macros
 ****************************************************************************************
 */
#define GPIO_NE_IRQ_CLEAR_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_NE_IRQ_CLEAR_0)
#define GPIO_NE_IRQ_CLEAR_0_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GPIO_NE_IRQ_CLEAR_0, (value))


/*
 *  GPIO_GPIO_NE_IRQ_SET_0 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_NE_IRQ_SET_0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_SET_0))
#define GPIO_GPIO_NE_IRQ_SET_0_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_SET_0, (value))
#define GPIO_GPIO_NE_IRQ_SET_0_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_SET_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_SET_0) | (value))
#define GPIO_GPIO_NE_IRQ_SET_0_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_SET_0, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_SET_0) & (~(value)))

/*
 *  GPIO_NE_IRQ_SET_0 bit field macros
 ****************************************************************************************
 */
#define GPIO_NE_IRQ_SET_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_NE_IRQ_SET_0)
#define GPIO_NE_IRQ_SET_0_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GPIO_NE_IRQ_SET_0, (value))


/*
 *  GPIO_GPIO_NE_IRQ_STATUS_1 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_NE_IRQ_STATUS_1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_STATUS_1))
#define GPIO_GPIO_NE_IRQ_STATUS_1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_STATUS_1, (value))
#define GPIO_GPIO_NE_IRQ_STATUS_1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_STATUS_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_STATUS_1) | (value))
#define GPIO_GPIO_NE_IRQ_STATUS_1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_STATUS_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_STATUS_1) & (~(value)))

/*
 *  GPIO_NE_IRQ_STATUS_1 bit field macros
 ****************************************************************************************
 */
#define GPIO_NE_IRQ_STATUS_1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_NE_IRQ_STATUS_1)


/*
 *  GPIO_GPIO_NE_IRQ_MASK_1 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_NE_IRQ_MASK_1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_MASK_1))
#define GPIO_GPIO_NE_IRQ_MASK_1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_MASK_1, (value))
#define GPIO_GPIO_NE_IRQ_MASK_1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_MASK_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_MASK_1) | (value))
#define GPIO_GPIO_NE_IRQ_MASK_1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_MASK_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_MASK_1) & (~(value)))

/*
 *  GPIO_NE_IRQ_MASK_1 bit field macros
 ****************************************************************************************
 */
#define GPIO_NE_IRQ_MASK_1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_NE_IRQ_MASK_1)
#define GPIO_NE_IRQ_MASK_1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GPIO_NE_IRQ_MASK_1, (value))


/*
 *  GPIO_GPIO_NE_IRQ_CLEAR_1 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_NE_IRQ_CLEAR_1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_CLEAR_1))
#define GPIO_GPIO_NE_IRQ_CLEAR_1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_CLEAR_1, (value))
#define GPIO_GPIO_NE_IRQ_CLEAR_1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_CLEAR_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_CLEAR_1) | (value))
#define GPIO_GPIO_NE_IRQ_CLEAR_1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_CLEAR_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_CLEAR_1) & (~(value)))

/*
 *  GPIO_NE_IRQ_CLEAR_1 bit field macros
 ****************************************************************************************
 */
#define GPIO_NE_IRQ_CLEAR_1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_NE_IRQ_CLEAR_1)
#define GPIO_NE_IRQ_CLEAR_1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GPIO_NE_IRQ_CLEAR_1, (value))


/*
 *  GPIO_GPIO_NE_IRQ_SET_1 register macros
 ****************************************************************************************
 */
#define GPIO_GPIO_NE_IRQ_SET_1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_SET_1))
#define GPIO_GPIO_NE_IRQ_SET_1_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_SET_1, (value))
#define GPIO_GPIO_NE_IRQ_SET_1_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_SET_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_SET_1) | (value))
#define GPIO_GPIO_NE_IRQ_SET_1_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_SET_1, GET_WORD_EXCLUSIVE_BITFIELD(addr, GPIO_GPIO_NE_IRQ_SET_1) & (~(value)))

/*
 *  GPIO_NE_IRQ_SET_1 bit field macros
 ****************************************************************************************
 */
#define GPIO_NE_IRQ_SET_1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, GPIO_NE_IRQ_SET_1)
#define GPIO_NE_IRQ_SET_1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, GPIO_NE_IRQ_SET_1, (value))

#endif
