/******************************************************************************
*
*               COPYRIGHT (c) 20012-2014 GainSpan Corporation
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
* $RCSfile: gsn_reg_otp_op.h,v $
*
* Description : This file contains OTP register operation macros.
******************************************************************************/


#ifndef _REG_OTP_OP_H
#define _REG_OTP_OP_H

/***************************************************
 *
 *             OTP
 *
 ***************************************************/


/*
 *  OTP_OTP_SM_PAGE_RD register macros
 ****************************************************************************************
 */
#define OTP_OTP_SM_PAGE_RD_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_PAGE_RD))
#define OTP_OTP_SM_PAGE_RD_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_PAGE_RD, (value))
#define OTP_OTP_SM_PAGE_RD_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_PAGE_RD, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_PAGE_RD) | (value))
#define OTP_OTP_SM_PAGE_RD_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_PAGE_RD, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_PAGE_RD) & (~(value)))

/*
 *  OTP_PAGE_RD_REQ bit field macros
 ****************************************************************************************
 */
#define OTP_PAGE_RD_REQ_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_PAGE_RD_REQ)
#define OTP_PAGE_RD_REQ_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_PAGE_RD_REQ, 1)
#define OTP_PAGE_RD_REQ_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_PAGE_RD_REQ, 0)


/*
 *  OTP_OTP_SM_PAGE_WR register macros
 ****************************************************************************************
 */
#define OTP_OTP_SM_PAGE_WR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_PAGE_WR))
#define OTP_OTP_SM_PAGE_WR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_PAGE_WR, (value))
#define OTP_OTP_SM_PAGE_WR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_PAGE_WR, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_PAGE_WR) | (value))
#define OTP_OTP_SM_PAGE_WR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_PAGE_WR, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_PAGE_WR) & (~(value)))

/*
 *  OTP_PAGE_WR_REQ bit field macros
 ****************************************************************************************
 */
#define OTP_PAGE_WR_REQ_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_PAGE_WR_REQ)
#define OTP_PAGE_WR_REQ_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_PAGE_WR_REQ, 1)
#define OTP_PAGE_WR_REQ_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_PAGE_WR_REQ, 0)


/*
 *  OTP_OTP_SM_NV_STORE register macros
 ****************************************************************************************
 */
#define OTP_OTP_SM_NV_STORE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_STORE))
#define OTP_OTP_SM_NV_STORE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_STORE, (value))
#define OTP_OTP_SM_NV_STORE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_STORE, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_STORE) | (value))
#define OTP_OTP_SM_NV_STORE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_STORE, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_STORE) & (~(value)))

/*
 *  OTP_NV_STORE_REQ bit field macros
 ****************************************************************************************
 */
#define OTP_NV_STORE_REQ_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_NV_STORE_REQ)
#define OTP_NV_STORE_REQ_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_NV_STORE_REQ, 1)
#define OTP_NV_STORE_REQ_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_NV_STORE_REQ, 0)


/*
 *  OTP_OTP_SM_NV_RCALL register macros
 ****************************************************************************************
 */
#define OTP_OTP_SM_NV_RCALL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_RCALL))
#define OTP_OTP_SM_NV_RCALL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_RCALL, (value))
#define OTP_OTP_SM_NV_RCALL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_RCALL, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_RCALL) | (value))
#define OTP_OTP_SM_NV_RCALL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_RCALL, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_RCALL) & (~(value)))

/*
 *  OTP_NV_RCALL_REQ bit field macros
 ****************************************************************************************
 */
#define OTP_NV_RCALL_REQ_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_NV_RCALL_REQ)
#define OTP_NV_RCALL_REQ_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_NV_RCALL_REQ, 1)
#define OTP_NV_RCALL_REQ_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_NV_RCALL_REQ, 0)


/*
 *  OTP_OTP_SM_RD_DATA_LSB register macros
 ****************************************************************************************
 */
#define OTP_OTP_SM_RD_DATA_LSB_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_RD_DATA_LSB))

/*
 *  OTP_RD_BUFFER_31_0 bit field macros
 ****************************************************************************************
 */
#define OTP_RD_BUFFER_31_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_RD_BUFFER_31_0)


/*
 *  OTP_OTP_SM_RD_DATA_MSB register macros
 ****************************************************************************************
 */
#define OTP_OTP_SM_RD_DATA_MSB_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_RD_DATA_MSB))

/*
 *  OTP_RD_BUFFER_63_32 bit field macros
 ****************************************************************************************
 */
#define OTP_RD_BUFFER_63_32_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_RD_BUFFER_63_32)


/*
 *  OTP_OTP_SM_WR_DATA_LSB register macros
 ****************************************************************************************
 */
#define OTP_OTP_SM_WR_DATA_LSB_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_WR_DATA_LSB))
#define OTP_OTP_SM_WR_DATA_LSB_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_WR_DATA_LSB, (value))
#define OTP_OTP_SM_WR_DATA_LSB_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_WR_DATA_LSB, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_WR_DATA_LSB) | (value))
#define OTP_OTP_SM_WR_DATA_LSB_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_WR_DATA_LSB, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_WR_DATA_LSB) & (~(value)))

/*
 *  OTP_WR_BUFFER_31_0 bit field macros
 ****************************************************************************************
 */
#define OTP_WR_BUFFER_31_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_WR_BUFFER_31_0)
#define OTP_WR_BUFFER_31_0_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, OTP_WR_BUFFER_31_0, (value))


/*
 *  OTP_OTP_SM_WR_DATA_MSB register macros
 ****************************************************************************************
 */
#define OTP_OTP_SM_WR_DATA_MSB_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_WR_DATA_MSB))
#define OTP_OTP_SM_WR_DATA_MSB_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_WR_DATA_MSB, (value))
#define OTP_OTP_SM_WR_DATA_MSB_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_WR_DATA_MSB, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_WR_DATA_MSB) | (value))
#define OTP_OTP_SM_WR_DATA_MSB_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_WR_DATA_MSB, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_WR_DATA_MSB) & (~(value)))

/*
 *  OTP_WR_BUFFER_63_32 bit field macros
 ****************************************************************************************
 */
#define OTP_WR_BUFFER_63_32_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_WR_BUFFER_63_32)
#define OTP_WR_BUFFER_63_32_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, OTP_WR_BUFFER_63_32, (value))


/*
 *  OTP_OTP_SM_NV_ADDR register macros
 ****************************************************************************************
 */
#define OTP_OTP_SM_NV_ADDR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_ADDR))
#define OTP_OTP_SM_NV_ADDR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_ADDR, (value))
#define OTP_OTP_SM_NV_ADDR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_ADDR, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_ADDR) | (value))
#define OTP_OTP_SM_NV_ADDR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_ADDR, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_NV_ADDR) & (~(value)))

/*
 *  OTP_NVA_BUFFER bit field macros
 ****************************************************************************************
 */
#define OTP_NVA_BUFFER_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_NVA_BUFFER)
#define OTP_NVA_BUFFER_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, OTP_NVA_BUFFER, (value))


/*
 *  OTP_OTP_CVAL_STORE_WAIT register macros
 ****************************************************************************************
 */
#define OTP_OTP_CVAL_STORE_WAIT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_STORE_WAIT))
#define OTP_OTP_CVAL_STORE_WAIT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_STORE_WAIT, (value))
#define OTP_OTP_CVAL_STORE_WAIT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_STORE_WAIT, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_STORE_WAIT) | (value))
#define OTP_OTP_CVAL_STORE_WAIT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_STORE_WAIT, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_STORE_WAIT) & (~(value)))

/*
 *  OTP_CVAL_STORE_WAIT bit field macros
 ****************************************************************************************
 */
#define OTP_CVAL_STORE_WAIT_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_CVAL_STORE_WAIT)
#define OTP_CVAL_STORE_WAIT_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, OTP_CVAL_STORE_WAIT, (value))


/*
 *  OTP_OTP_CVAL_STORE_END register macros
 ****************************************************************************************
 */
#define OTP_OTP_CVAL_STORE_END_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_STORE_END))
#define OTP_OTP_CVAL_STORE_END_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_STORE_END, (value))
#define OTP_OTP_CVAL_STORE_END_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_STORE_END, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_STORE_END) | (value))
#define OTP_OTP_CVAL_STORE_END_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_STORE_END, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_STORE_END) & (~(value)))

/*
 *  OTP_CVAL_STORE_END bit field macros
 ****************************************************************************************
 */
#define OTP_CVAL_STORE_END_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_CVAL_STORE_END)
#define OTP_CVAL_STORE_END_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, OTP_CVAL_STORE_END, (value))


/*
 *  OTP_OTP_CVAL_RCALL_END register macros
 ****************************************************************************************
 */
#define OTP_OTP_CVAL_RCALL_END_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_RCALL_END))
#define OTP_OTP_CVAL_RCALL_END_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_RCALL_END, (value))
#define OTP_OTP_CVAL_RCALL_END_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_RCALL_END, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_RCALL_END) | (value))
#define OTP_OTP_CVAL_RCALL_END_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_RCALL_END, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_RCALL_END) & (~(value)))

/*
 *  OTP_CVAL_RCALL_END bit field macros
 ****************************************************************************************
 */
#define OTP_CVAL_RCALL_END_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_CVAL_RCALL_END)
#define OTP_CVAL_RCALL_END_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, OTP_CVAL_RCALL_END, (value))


/*
 *  OTP_OTP_CVAL_TEST_END register macros
 ****************************************************************************************
 */
#define OTP_OTP_CVAL_TEST_END_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_TEST_END))
#define OTP_OTP_CVAL_TEST_END_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_TEST_END, (value))
#define OTP_OTP_CVAL_TEST_END_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_TEST_END, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_TEST_END) | (value))
#define OTP_OTP_CVAL_TEST_END_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_TEST_END, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_TEST_END) & (~(value)))

/*
 *  OTP_CVAL_TEST_END_NEWBITFIELD1 bit field macros
 ****************************************************************************************
 */
#define OTP_CVAL_TEST_END_NEWBITFIELD1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_CVAL_TEST_END_NEWBITFIELD1)
#define OTP_CVAL_TEST_END_NEWBITFIELD1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, OTP_CVAL_TEST_END_NEWBITFIELD1, (value))


/*
 *  OTP_OTP_CVAL_TEST_WAIT register macros
 ****************************************************************************************
 */
#define OTP_OTP_CVAL_TEST_WAIT_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_TEST_WAIT))
#define OTP_OTP_CVAL_TEST_WAIT_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_TEST_WAIT, (value))
#define OTP_OTP_CVAL_TEST_WAIT_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_TEST_WAIT, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_TEST_WAIT) | (value))
#define OTP_OTP_CVAL_TEST_WAIT_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_TEST_WAIT, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_CVAL_TEST_WAIT) & (~(value)))

/*
 *  OTP_CVAL_TEST_WAIT_NEWBITFIELD1 bit field macros
 ****************************************************************************************
 */
#define OTP_CVAL_TEST_WAIT_NEWBITFIELD1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_CVAL_TEST_WAIT_NEWBITFIELD1)
#define OTP_CVAL_TEST_WAIT_NEWBITFIELD1_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, OTP_CVAL_TEST_WAIT_NEWBITFIELD1, (value))


/*
 *  OTP_OTP_SM_TEST_TEFAIL register macros
 ****************************************************************************************
 */
#define OTP_OTP_SM_TEST_TEFAIL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_TEFAIL))

/*
 *  OTP_TEST_TEFAIL bit field macros
 ****************************************************************************************
 */
#define OTP_TEST_TEFAIL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_TEST_TEFAIL)


/*
 *  OTP_OTP_SM_TEST_DIAG register macros
 ****************************************************************************************
 */
#define OTP_OTP_SM_TEST_DIAG_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_DIAG))
#define OTP_OTP_SM_TEST_DIAG_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_DIAG, (value))
#define OTP_OTP_SM_TEST_DIAG_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_DIAG, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_DIAG) | (value))
#define OTP_OTP_SM_TEST_DIAG_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_DIAG, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_DIAG) & (~(value)))

/*
 *  OTP_TEST_DIAG_REQ bit field macros
 ****************************************************************************************
 */
#define OTP_TEST_DIAG_REQ_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_TEST_DIAG_REQ)
#define OTP_TEST_DIAG_REQ_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_TEST_DIAG_REQ, 1)
#define OTP_TEST_DIAG_REQ_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_TEST_DIAG_REQ, 0)


/*
 *  OTP_OTP_SM_TEST_STORE register macros
 ****************************************************************************************
 */
#define OTP_OTP_SM_TEST_STORE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_STORE))
#define OTP_OTP_SM_TEST_STORE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_STORE, (value))
#define OTP_OTP_SM_TEST_STORE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_STORE, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_STORE) | (value))
#define OTP_OTP_SM_TEST_STORE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_STORE, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_STORE) & (~(value)))

/*
 *  OTP_TEST_STORE_REQ bit field macros
 ****************************************************************************************
 */
#define OTP_TEST_STORE_REQ_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_TEST_STORE_REQ)
#define OTP_TEST_STORE_REQ_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_TEST_STORE_REQ, 1)
#define OTP_TEST_STORE_REQ_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_TEST_STORE_REQ, 0)


/*
 *  OTP_OTP_TEST_TESTSEL register macros
 ****************************************************************************************
 */
#define OTP_OTP_TEST_TESTSEL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_TEST_TESTSEL))
#define OTP_OTP_TEST_TESTSEL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_TEST_TESTSEL, (value))
#define OTP_OTP_TEST_TESTSEL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_TEST_TESTSEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_TEST_TESTSEL) | (value))
#define OTP_OTP_TEST_TESTSEL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_TEST_TESTSEL, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_TEST_TESTSEL) & (~(value)))

/*
 *  OTP_TESTSEL bit field macros
 ****************************************************************************************
 */
#define OTP_TESTSEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_TESTSEL)
#define OTP_TESTSEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, OTP_TESTSEL, (value))


/*
 *  OTP_OTP_SM_TEST_SDTA register macros
 ****************************************************************************************
 */
#define OTP_OTP_SM_TEST_SDTA_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_SDTA))
#define OTP_OTP_SM_TEST_SDTA_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_SDTA, (value))
#define OTP_OTP_SM_TEST_SDTA_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_SDTA, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_SDTA) | (value))
#define OTP_OTP_SM_TEST_SDTA_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_SDTA, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_SDTA) & (~(value)))

/*
 *  OTP_TEST_SDTA bit field macros
 ****************************************************************************************
 */
#define OTP_TEST_SDTA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_TEST_SDTA)
#define OTP_TEST_SDTA_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, OTP_TEST_SDTA, (value))


/*
 *  OTP_OTP_SM_TEST_SDTO_0 register macros
 ****************************************************************************************
 */
#define OTP_OTP_SM_TEST_SDTO_0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_SDTO_0))

/*
 *  OTP_SDTO0_BUFFER bit field macros
 ****************************************************************************************
 */
#define OTP_SDTO0_BUFFER_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_SDTO0_BUFFER)


/*
 *  OTP_OTP_SM_TEST_SDTO_1 register macros
 ****************************************************************************************
 */
#define OTP_OTP_SM_TEST_SDTO_1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SM_TEST_SDTO_1))

/*
 *  OTP_SDTO1_BUFFER bit field macros
 ****************************************************************************************
 */
#define OTP_SDTO1_BUFFER_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_SDTO1_BUFFER)


/*
 *  OTP_OTP_SIG_VWL register macros
 ****************************************************************************************
 */
#define OTP_OTP_SIG_VWL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_VWL))
#define OTP_OTP_SIG_VWL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_VWL, (value))
#define OTP_OTP_SIG_VWL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_VWL, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_VWL) | (value))
#define OTP_OTP_SIG_VWL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_VWL, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_VWL) & (~(value)))

/*
 *  OTP_VWLIN bit field macros
 ****************************************************************************************
 */
#define OTP_VWLIN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_VWLIN)
#define OTP_VWLIN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_VWLIN, 1)
#define OTP_VWLIN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_VWLIN, 0)

/*
 *  OTP_VWLSEL bit field macros
 ****************************************************************************************
 */
#define OTP_VWLSEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_VWLSEL)
#define OTP_VWLSEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, OTP_VWLSEL, (value))


/*
 *  OTP_OTP_SIG_CTL register macros
 ****************************************************************************************
 */
#define OTP_OTP_SIG_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_CTL))
#define OTP_OTP_SIG_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_CTL, (value))
#define OTP_OTP_SIG_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_CTL) | (value))
#define OTP_OTP_SIG_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_CTL) & (~(value)))

/*
 *  OTP_SIG_CTL bit field macros
 ****************************************************************************************
 */
#define OTP_SIG_CTL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_SIG_CTL)
#define OTP_SIG_CTL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, OTP_SIG_CTL, (value))


/*
 *  OTP_OTP_SIG_VAL register macros
 ****************************************************************************************
 */
#define OTP_OTP_SIG_VAL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_VAL))
#define OTP_OTP_SIG_VAL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_VAL, (value))
#define OTP_OTP_SIG_VAL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_VAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_VAL) | (value))
#define OTP_OTP_SIG_VAL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_VAL, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_VAL) & (~(value)))

/*
 *  OTP_SIG_VAL bit field macros
 ****************************************************************************************
 */
#define OTP_SIG_VAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_SIG_VAL)
#define OTP_SIG_VAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, OTP_SIG_VAL, (value))


/*
 *  OTP_OTP_SIG_SDTO_0 register macros
 ****************************************************************************************
 */
#define OTP_OTP_SIG_SDTO_0_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_SDTO_0))

/*
 *  OTP_OTP_SDTO0 bit field macros
 ****************************************************************************************
 */
#define OTP_OTP_SDTO0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_OTP_SDTO0)


/*
 *  OTP_OTP_SIG_SDTO_1 register macros
 ****************************************************************************************
 */
#define OTP_OTP_SIG_SDTO_1_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_SDTO_1))

/*
 *  OTP_OTP_SDTO1 bit field macros
 ****************************************************************************************
 */
#define OTP_OTP_SDTO1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_OTP_SDTO1)


/*
 *  OTP_OTP_SIG_DOUT_LSB register macros
 ****************************************************************************************
 */
#define OTP_OTP_SIG_DOUT_LSB_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_DOUT_LSB))

/*
 *  OTP_OTP_DOUT_31_0 bit field macros
 ****************************************************************************************
 */
#define OTP_OTP_DOUT_31_0_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_OTP_DOUT_31_0)


/*
 *  OTP_OTP_SIG_DOUT_MSB register macros
 ****************************************************************************************
 */
#define OTP_OTP_SIG_DOUT_MSB_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_DOUT_MSB))

/*
 *  OTP_OTP_DOUT_63_32 bit field macros
 ****************************************************************************************
 */
#define OTP_OTP_DOUT_63_32_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_OTP_DOUT_63_32)


/*
 *  OTP_OTP_SIG_TEFAIL register macros
 ****************************************************************************************
 */
#define OTP_OTP_SIG_TEFAIL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_SIG_TEFAIL))

/*
 *  OTP_OTP_TEFAIL bit field macros
 ****************************************************************************************
 */
#define OTP_OTP_TEFAIL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_OTP_TEFAIL)


/*
 *  OTP_OTP_IRQ_STATUS register macros
 ****************************************************************************************
 */
#define OTP_OTP_IRQ_STATUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_STATUS))

/*
 *  OTP_IRQ_STATUS_TEST_STORE_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_STATUS_TEST_STORE_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_STATUS_TEST_STORE_ACK)

/*
 *  OTP_IRQ_STATUS_TEST_DIAG_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_STATUS_TEST_DIAG_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_STATUS_TEST_DIAG_ACK)

/*
 *  OTP_IRQ_STATUS_PAGE_RD_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_STATUS_PAGE_RD_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_STATUS_PAGE_RD_ACK)

/*
 *  OTP_IRQ_STATUS_PAGE_WR_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_STATUS_PAGE_WR_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_STATUS_PAGE_WR_ACK)

/*
 *  OTP_IRQ_STATUS_NV_STORE_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_STATUS_NV_STORE_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_STATUS_NV_STORE_ACK)

/*
 *  OTP_IRQ_STATUS_NV_RCALL_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_STATUS_NV_RCALL_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_STATUS_NV_RCALL_ACK)


/*
 *  OTP_OTP_IRQ_MASK register macros
 ****************************************************************************************
 */
#define OTP_OTP_IRQ_MASK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_MASK))
#define OTP_OTP_IRQ_MASK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_MASK, (value))
#define OTP_OTP_IRQ_MASK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_MASK) | (value))
#define OTP_OTP_IRQ_MASK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_MASK) & (~(value)))

/*
 *  OTP_IRQ_MASK_TEST_STORE_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_MASK_TEST_STORE_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_TEST_STORE_ACK)
#define OTP_IRQ_MASK_TEST_STORE_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_TEST_STORE_ACK, 1)
#define OTP_IRQ_MASK_TEST_STORE_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_TEST_STORE_ACK, 0)

/*
 *  OTP_IRQ_MASK_TEST_DIAG_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_MASK_TEST_DIAG_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_TEST_DIAG_ACK)
#define OTP_IRQ_MASK_TEST_DIAG_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_TEST_DIAG_ACK, 1)
#define OTP_IRQ_MASK_TEST_DIAG_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_TEST_DIAG_ACK, 0)

/*
 *  OTP_IRQ_MASK_PAGE_RD_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_MASK_PAGE_RD_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_PAGE_RD_ACK)
#define OTP_IRQ_MASK_PAGE_RD_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_PAGE_RD_ACK, 1)
#define OTP_IRQ_MASK_PAGE_RD_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_PAGE_RD_ACK, 0)

/*
 *  OTP_IRQ_MASK_PAGE_WR_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_MASK_PAGE_WR_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_PAGE_WR_ACK)
#define OTP_IRQ_MASK_PAGE_WR_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_PAGE_WR_ACK, 1)
#define OTP_IRQ_MASK_PAGE_WR_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_PAGE_WR_ACK, 0)

/*
 *  OTP_IRQ_MASK_NV_STORE_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_MASK_NV_STORE_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_NV_STORE_ACK)
#define OTP_IRQ_MASK_NV_STORE_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_NV_STORE_ACK, 1)
#define OTP_IRQ_MASK_NV_STORE_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_NV_STORE_ACK, 0)

/*
 *  OTP_IRQ_MASK_NV_RCALL_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_MASK_NV_RCALL_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_NV_RCALL_ACK)
#define OTP_IRQ_MASK_NV_RCALL_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_NV_RCALL_ACK, 1)
#define OTP_IRQ_MASK_NV_RCALL_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_MASK_NV_RCALL_ACK, 0)


/*
 *  OTP_OTP_IRQ_CLEAR register macros
 ****************************************************************************************
 */
#define OTP_OTP_IRQ_CLEAR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_CLEAR))
#define OTP_OTP_IRQ_CLEAR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_CLEAR, (value))
#define OTP_OTP_IRQ_CLEAR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_CLEAR, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_CLEAR) | (value))
#define OTP_OTP_IRQ_CLEAR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_CLEAR, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_CLEAR) & (~(value)))

/*
 *  OTP_IRQ_CLEAR_TEST_STORE_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_CLEAR_TEST_STORE_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_TEST_STORE_ACK)
#define OTP_IRQ_CLEAR_TEST_STORE_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_TEST_STORE_ACK, 1)
#define OTP_IRQ_CLEAR_TEST_STORE_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_TEST_STORE_ACK, 0)

/*
 *  OTP_IRQ_CLEAR_TEST_DIAG_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_CLEAR_TEST_DIAG_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_TEST_DIAG_ACK)
#define OTP_IRQ_CLEAR_TEST_DIAG_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_TEST_DIAG_ACK, 1)
#define OTP_IRQ_CLEAR_TEST_DIAG_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_TEST_DIAG_ACK, 0)

/*
 *  OTP_IRQ_CLEAR_PAGE_RD_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_CLEAR_PAGE_RD_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_PAGE_RD_ACK)
#define OTP_IRQ_CLEAR_PAGE_RD_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_PAGE_RD_ACK, 1)
#define OTP_IRQ_CLEAR_PAGE_RD_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_PAGE_RD_ACK, 0)

/*
 *  OTP_IRQ_CLEAR_PAGE_WR_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_CLEAR_PAGE_WR_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_PAGE_WR_ACK)
#define OTP_IRQ_CLEAR_PAGE_WR_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_PAGE_WR_ACK, 1)
#define OTP_IRQ_CLEAR_PAGE_WR_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_PAGE_WR_ACK, 0)

/*
 *  OTP_IRQ_CLEAR_NV_STORE_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_CLEAR_NV_STORE_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_NV_STORE_ACK)
#define OTP_IRQ_CLEAR_NV_STORE_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_NV_STORE_ACK, 1)
#define OTP_IRQ_CLEAR_NV_STORE_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_NV_STORE_ACK, 0)

/*
 *  OTP_IRQ_CLEAR_NV_RCALL_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_CLEAR_NV_RCALL_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_NV_RCALL_ACK)
#define OTP_IRQ_CLEAR_NV_RCALL_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_NV_RCALL_ACK, 1)
#define OTP_IRQ_CLEAR_NV_RCALL_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_CLEAR_NV_RCALL_ACK, 0)


/*
 *  OTP_OTP_IRQ_SET register macros
 ****************************************************************************************
 */
#define OTP_OTP_IRQ_SET_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_SET))
#define OTP_OTP_IRQ_SET_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_SET, (value))
#define OTP_OTP_IRQ_SET_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_SET, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_SET) | (value))
#define OTP_OTP_IRQ_SET_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_SET, GET_WORD_EXCLUSIVE_BITFIELD(addr, OTP_OTP_IRQ_SET) & (~(value)))

/*
 *  OTP_IRQ_SET_TEST_STORE_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_SET_TEST_STORE_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_TEST_STORE_ACK)
#define OTP_IRQ_SET_TEST_STORE_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_TEST_STORE_ACK, 1)
#define OTP_IRQ_SET_TEST_STORE_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_TEST_STORE_ACK, 0)

/*
 *  OTP_IRQ_SET_TEST_DIAG_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_SET_TEST_DIAG_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_TEST_DIAG_ACK)
#define OTP_IRQ_SET_TEST_DIAG_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_TEST_DIAG_ACK, 1)
#define OTP_IRQ_SET_TEST_DIAG_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_TEST_DIAG_ACK, 0)

/*
 *  OTP_IRQ_SET_PAGE_RD_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_SET_PAGE_RD_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_PAGE_RD_ACK)
#define OTP_IRQ_SET_PAGE_RD_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_PAGE_RD_ACK, 1)
#define OTP_IRQ_SET_PAGE_RD_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_PAGE_RD_ACK, 0)

/*
 *  OTP_IRQ_SET_PAGE_WR_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_SET_PAGE_WR_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_PAGE_WR_ACK)
#define OTP_IRQ_SET_PAGE_WR_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_PAGE_WR_ACK, 1)
#define OTP_IRQ_SET_PAGE_WR_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_PAGE_WR_ACK, 0)

/*
 *  OTP_IRQ_SET_NV_STORE_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_SET_NV_STORE_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_NV_STORE_ACK)
#define OTP_IRQ_SET_NV_STORE_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_NV_STORE_ACK, 1)
#define OTP_IRQ_SET_NV_STORE_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_NV_STORE_ACK, 0)

/*
 *  OTP_IRQ_SET_NV_RCALL_ACK bit field macros
 ****************************************************************************************
 */
#define OTP_IRQ_SET_NV_RCALL_ACK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_NV_RCALL_ACK)
#define OTP_IRQ_SET_NV_RCALL_ACK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_NV_RCALL_ACK, 1)
#define OTP_IRQ_SET_NV_RCALL_ACK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, OTP_IRQ_SET_NV_RCALL_ACK, 0)

#endif
