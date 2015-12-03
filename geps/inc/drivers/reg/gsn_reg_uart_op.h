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
 * $RCSfile: gsn_reg_uart_op.h,v $
 *
 * Description:
 *      This file contains register macros for UART Driver
 *
 ******************************************************************************
 */

#ifndef _REG_UART_MAC_H
#define _REG_UART_MAC_H

/***************************************************
 *
 *             UART
 *
 ***************************************************/


/*
 *  UART_DR register macros
 ****************************************************************************************
 */
#define UART_DR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_DR))
#define UART_DR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_DR, (value))
#define UART_DR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_DR, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_DR) | (value))
#define UART_DR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_DR, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_DR) & (~(value)))

/*
 *  UART_DATA bit field macros
 ****************************************************************************************
 */
#define UART_DATA_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_DATA)
#define UART_DATA_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, UART_DATA, (value))


/*
 *  UART_RSR register macros
 ****************************************************************************************
 */
#define UART_RSR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_RSR))
#define UART_RSR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_RSR, (value))
#define UART_RSR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_RSR, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_RSR) | (value))
#define UART_RSR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_RSR, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_RSR) & (~(value)))

/*
 *  UART_OE bit field macros
 ****************************************************************************************
 */
#define UART_OE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_OE)
#define UART_OE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_OE, 1)
#define UART_OE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_OE, 0)

/*
 *  UART_BE bit field macros
 ****************************************************************************************
 */
#define UART_BE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_BE)
#define UART_BE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_BE, 1)
#define UART_BE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_BE, 0)

/*
 *  UART_PE bit field macros
 ****************************************************************************************
 */
#define UART_PE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_PE)
#define UART_PE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_PE, 1)
#define UART_PE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_PE, 0)

/*
 *  UART_FE bit field macros
 ****************************************************************************************
 */
#define UART_FE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_FE)
#define UART_FE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_FE, 1)
#define UART_FE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_FE, 0)


/*
 *  UART_ECR register macros
 ****************************************************************************************
 */
#define UART_ECR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_ECR))
#define UART_ECR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_ECR, (value))
#define UART_ECR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_ECR, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_ECR) | (value))
#define UART_ECR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_ECR, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_ECR) & (~(value)))

/*
 *  UART_ECRVAL bit field macros
 ****************************************************************************************
 */
#define UART_ECRVAL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_ECRVAL)
#define UART_ECRVAL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, UART_ECRVAL, (value))


/*
 *  UART_FR register macros
 ****************************************************************************************
 */
#define UART_FR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_FR))

/*
 *  UART_RI bit field macros
 ****************************************************************************************
 */
#define UART_RI_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_RI)

/*
 *  UART_TXFE bit field macros
 ****************************************************************************************
 */
#define UART_TXFE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_TXFE)

/*
 *  UART_RXFF bit field macros
 ****************************************************************************************
 */
#define UART_RXFF_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_RXFF)

/*
 *  UART_TXFF bit field macros
 ****************************************************************************************
 */
#define UART_TXFF_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_TXFF)

/*
 *  UART_RXFE bit field macros
 ****************************************************************************************
 */
#define UART_RXFE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_RXFE)

/*
 *  UART_BUSY bit field macros
 ****************************************************************************************
 */
#define UART_BUSY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_BUSY)

/*
 *  UART_DCD bit field macros
 ****************************************************************************************
 */
#define UART_DCD_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_DCD)

/*
 *  UART_DSR bit field macros
 ****************************************************************************************
 */
#define UART_DSR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_DSR)

/*
 *  UART_CTS bit field macros
 ****************************************************************************************
 */
#define UART_CTS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_CTS)


/*
 *  UART_IBRD register macros
 ****************************************************************************************
 */
#define UART_IBRD_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IBRD))
#define UART_IBRD_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IBRD, (value))
#define UART_IBRD_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IBRD, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IBRD) | (value))
#define UART_IBRD_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IBRD, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IBRD) & (~(value)))

/*
 *  UART_BAUD_DIVINT bit field macros
 ****************************************************************************************
 */
#define UART_BAUD_DIVINT_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_BAUD_DIVINT)
#define UART_BAUD_DIVINT_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, UART_BAUD_DIVINT, (value))


/*
 *  UART_FBRD register macros
 ****************************************************************************************
 */
#define UART_FBRD_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_FBRD))
#define UART_FBRD_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_FBRD, (value))
#define UART_FBRD_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_FBRD, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_FBRD) | (value))
#define UART_FBRD_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_FBRD, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_FBRD) & (~(value)))

/*
 *  UART_BAUD_DIVFRAC bit field macros
 ****************************************************************************************
 */
#define UART_BAUD_DIVFRAC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_BAUD_DIVFRAC)
#define UART_BAUD_DIVFRAC_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, UART_BAUD_DIVFRAC, (value))


/*
 *  UART_LCR register macros
 ****************************************************************************************
 */
#define UART_LCR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_LCR))
#define UART_LCR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_LCR, (value))
#define UART_LCR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_LCR, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_LCR) | (value))
#define UART_LCR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_LCR, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_LCR) & (~(value)))

/*
 *  UART_SPS bit field macros
 ****************************************************************************************
 */
#define UART_SPS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_SPS)
#define UART_SPS_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_SPS, 1)
#define UART_SPS_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_SPS, 0)

/*
 *  UART_WLEN bit field macros
 ****************************************************************************************
 */
#define UART_WLEN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_WLEN)
#define UART_WLEN_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, UART_WLEN, (value))

/*
 *  UART_FEN bit field macros
 ****************************************************************************************
 */
#define UART_FEN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_FEN)
#define UART_FEN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_FEN, 1)
#define UART_FEN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_FEN, 0)

/*
 *  UART_STP2 bit field macros
 ****************************************************************************************
 */
#define UART_STP2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_STP2)
#define UART_STP2_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_STP2, 1)
#define UART_STP2_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_STP2, 0)

/*
 *  UART_EPS bit field macros
 ****************************************************************************************
 */
#define UART_EPS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_EPS)
#define UART_EPS_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_EPS, 1)
#define UART_EPS_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_EPS, 0)

/*
 *  UART_PEN bit field macros
 ****************************************************************************************
 */
#define UART_PEN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_PEN)
#define UART_PEN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_PEN, 1)
#define UART_PEN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_PEN, 0)

/*
 *  UART_BRK bit field macros
 ****************************************************************************************
 */
#define UART_BRK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_BRK)
#define UART_BRK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_BRK, 1)
#define UART_BRK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_BRK, 0)


/*
 *  UART_CR register macros
 ****************************************************************************************
 */
#define UART_CR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_CR))
#define UART_CR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_CR, (value))
#define UART_CR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_CR, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_CR) | (value))
#define UART_CR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_CR, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_CR) & (~(value)))

/*
 *  UART_CTSEN bit field macros
 ****************************************************************************************
 */
#define UART_CTSEN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_CTSEN)
#define UART_CTSEN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_CTSEN, 1)
#define UART_CTSEN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_CTSEN, 0)

/*
 *  UART_RTSEN bit field macros
 ****************************************************************************************
 */
#define UART_RTSEN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_RTSEN)
#define UART_RTSEN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RTSEN, 1)
#define UART_RTSEN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RTSEN, 0)

/*
 *  UART_OUT2 bit field macros
 ****************************************************************************************
 */
#define UART_OUT2_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_OUT2)
#define UART_OUT2_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_OUT2, 1)
#define UART_OUT2_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_OUT2, 0)

/*
 *  UART_OUT1 bit field macros
 ****************************************************************************************
 */
#define UART_OUT1_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_OUT1)
#define UART_OUT1_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_OUT1, 1)
#define UART_OUT1_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_OUT1, 0)

/*
 *  UART_RTS bit field macros
 ****************************************************************************************
 */
#define UART_RTS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_RTS)
#define UART_RTS_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RTS, 1)
#define UART_RTS_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RTS, 0)

/*
 *  UART_DTR bit field macros
 ****************************************************************************************
 */
#define UART_DTR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_DTR)
#define UART_DTR_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_DTR, 1)
#define UART_DTR_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_DTR, 0)

/*
 *  UART_RXE bit field macros
 ****************************************************************************************
 */
#define UART_RXE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_RXE)
#define UART_RXE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RXE, 1)
#define UART_RXE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RXE, 0)

/*
 *  UART_TXE bit field macros
 ****************************************************************************************
 */
#define UART_TXE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_TXE)
#define UART_TXE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_TXE, 1)
#define UART_TXE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_TXE, 0)

/*
 *  UART_LBE bit field macros
 ****************************************************************************************
 */
#define UART_LBE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_LBE)
#define UART_LBE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_LBE, 1)
#define UART_LBE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_LBE, 0)

/*
 *  UART_SIRLP bit field macros
 ****************************************************************************************
 */
#define UART_SIRLP_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_SIRLP)
#define UART_SIRLP_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_SIRLP, 1)
#define UART_SIRLP_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_SIRLP, 0)

/*
 *  UART_SIREN bit field macros
 ****************************************************************************************
 */
#define UART_SIREN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_SIREN)
#define UART_SIREN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_SIREN, 1)
#define UART_SIREN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_SIREN, 0)

/*
 *  UART_UARTEN bit field macros
 ****************************************************************************************
 */
#define UART_UARTEN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_UARTEN)
#define UART_UARTEN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_UARTEN, 1)
#define UART_UARTEN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_UARTEN, 0)


/*
 *  UART_IFLS register macros
 ****************************************************************************************
 */
#define UART_IFLS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IFLS))
#define UART_IFLS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IFLS, (value))
#define UART_IFLS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IFLS, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IFLS) | (value))
#define UART_IFLS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IFLS, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IFLS) & (~(value)))

/*
 *  UART_RXIFLSEL bit field macros
 ****************************************************************************************
 */
#define UART_RXIFLSEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_RXIFLSEL)
#define UART_RXIFLSEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, UART_RXIFLSEL, (value))

/*
 *  UART_TXIFLSEL bit field macros
 ****************************************************************************************
 */
#define UART_TXIFLSEL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_TXIFLSEL)
#define UART_TXIFLSEL_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, UART_TXIFLSEL, (value))


/*
 *  UART_IMSC register macros
 ****************************************************************************************
 */
#define UART_IMSC_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IMSC))
#define UART_IMSC_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IMSC, (value))
#define UART_IMSC_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IMSC, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IMSC) | (value))
#define UART_IMSC_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IMSC, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_IMSC) & (~(value)))

/*
 *  UART_IM bit field macros
 ****************************************************************************************
 */
#define UART_IM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_IM)
#define UART_IM_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, UART_IM, (value))

/*
 *  UART_OEIM bit field macros
 ****************************************************************************************
 */
#define UART_OEIM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_OEIM)
#define UART_OEIM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_OEIM, 1)
#define UART_OEIM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_OEIM, 0)

/*
 *  UART_BEIM bit field macros
 ****************************************************************************************
 */
#define UART_BEIM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_BEIM)
#define UART_BEIM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_BEIM, 1)
#define UART_BEIM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_BEIM, 0)

/*
 *  UART_PEIM bit field macros
 ****************************************************************************************
 */
#define UART_PEIM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_PEIM)
#define UART_PEIM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_PEIM, 1)
#define UART_PEIM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_PEIM, 0)

/*
 *  UART_FEIM bit field macros
 ****************************************************************************************
 */
#define UART_FEIM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_FEIM)
#define UART_FEIM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_FEIM, 1)
#define UART_FEIM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_FEIM, 0)

/*
 *  UART_RTIM bit field macros
 ****************************************************************************************
 */
#define UART_RTIM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_RTIM)
#define UART_RTIM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RTIM, 1)
#define UART_RTIM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RTIM, 0)

/*
 *  UART_TXIM bit field macros
 ****************************************************************************************
 */
#define UART_TXIM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_TXIM)
#define UART_TXIM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_TXIM, 1)
#define UART_TXIM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_TXIM, 0)

/*
 *  UART_RXIM bit field macros
 ****************************************************************************************
 */
#define UART_RXIM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_RXIM)
#define UART_RXIM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RXIM, 1)
#define UART_RXIM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RXIM, 0)

/*
 *  UART_DSRMIM bit field macros
 ****************************************************************************************
 */
#define UART_DSRMIM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_DSRMIM)
#define UART_DSRMIM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_DSRMIM, 1)
#define UART_DSRMIM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_DSRMIM, 0)

/*
 *  UART_DCDMIM bit field macros
 ****************************************************************************************
 */
#define UART_DCDMIM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_DCDMIM)
#define UART_DCDMIM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_DCDMIM, 1)
#define UART_DCDMIM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_DCDMIM, 0)

/*
 *  UART_CTSMIM bit field macros
 ****************************************************************************************
 */
#define UART_CTSMIM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_CTSMIM)
#define UART_CTSMIM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_CTSMIM, 1)
#define UART_CTSMIM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_CTSMIM, 0)

/*
 *  UART_RIMIM bit field macros
 ****************************************************************************************
 */
#define UART_RIMIM_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_RIMIM)
#define UART_RIMIM_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RIMIM, 1)
#define UART_RIMIM_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RIMIM, 0)


/*
 *  UART_RIS register macros
 ****************************************************************************************
 */
#define UART_RIS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_RIS))

/*
 *  UART_IS bit field macros
 ****************************************************************************************
 */
#define UART_IS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_IS)
#define UART_IS_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, UART_IS, (value))

/*
 *  UART_OERIS bit field macros
 ****************************************************************************************
 */
#define UART_OERIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_OERIS)

/*
 *  UART_BERIS bit field macros
 ****************************************************************************************
 */
#define UART_BERIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_BERIS)

/*
 *  UART_PERIS bit field macros
 ****************************************************************************************
 */
#define UART_PERIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_PERIS)

/*
 *  UART_FERIS bit field macros
 ****************************************************************************************
 */
#define UART_FERIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_FERIS)

/*
 *  UART_RTRIS bit field macros
 ****************************************************************************************
 */
#define UART_RTRIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_RTRIS)

/*
 *  UART_TXRIS bit field macros
 ****************************************************************************************
 */
#define UART_TXRIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_TXRIS)

/*
 *  UART_RXRIS bit field macros
 ****************************************************************************************
 */
#define UART_RXRIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_RXRIS)

/*
 *  UART_DSRRMIS bit field macros
 ****************************************************************************************
 */
#define UART_DSRRMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_DSRRMIS)

/*
 *  UART_DCDRMIS bit field macros
 ****************************************************************************************
 */
#define UART_DCDRMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_DCDRMIS)

/*
 *  UART_CTSRMIS bit field macros
 ****************************************************************************************
 */
#define UART_CTSRMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_CTSRMIS)

/*
 *  UART_RIRMIS bit field macros
 ****************************************************************************************
 */
#define UART_RIRMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_RIRMIS)


/*
 *  UART_MIS register macros
 ****************************************************************************************
 */
#define UART_MIS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_MIS))

/*
 *  UART_OEMIS bit field macros
 ****************************************************************************************
 */
#define UART_OEMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_OEMIS)

/*
 *  UART_BEMIS bit field macros
 ****************************************************************************************
 */
#define UART_BEMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_BEMIS)

/*
 *  UART_PEMIS bit field macros
 ****************************************************************************************
 */
#define UART_PEMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_PEMIS)

/*
 *  UART_FEMIS bit field macros
 ****************************************************************************************
 */
#define UART_FEMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_FEMIS)

/*
 *  UART_RTMIS bit field macros
 ****************************************************************************************
 */
#define UART_RTMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_RTMIS)

/*
 *  UART_TXMIS bit field macros
 ****************************************************************************************
 */
#define UART_TXMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_TXMIS)

/*
 *  UART_RXMIS bit field macros
 ****************************************************************************************
 */
#define UART_RXMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_RXMIS)

/*
 *  UART_DSRMMIS bit field macros
 ****************************************************************************************
 */
#define UART_DSRMMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_DSRMMIS)

/*
 *  UART_DCDMMIS bit field macros
 ****************************************************************************************
 */
#define UART_DCDMMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_DCDMMIS)

/*
 *  UART_CTSMMIS bit field macros
 ****************************************************************************************
 */
#define UART_CTSMMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_CTSMMIS)

/*
 *  UART_RIMMIS bit field macros
 ****************************************************************************************
 */
#define UART_RIMMIS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_RIMMIS)


/*
 *  UART_ICR register macros
 ****************************************************************************************
 */
#define UART_ICR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_ICR, (value))

/*
 *  UART_IC bit field macros
 ****************************************************************************************
 */
#define UART_IC_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_IC)
#define UART_IC_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, UART_IC, (value))

/*
 *  UART_OEIC bit field macros
 ****************************************************************************************
 */
#define UART_OEIC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_OEIC, 1)
#define UART_OEIC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_OEIC, 0)

/*
 *  UART_BEIC bit field macros
 ****************************************************************************************
 */
#define UART_BEIC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_BEIC, 1)
#define UART_BEIC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_BEIC, 0)

/*
 *  UART_PEIC bit field macros
 ****************************************************************************************
 */
#define UART_PEIC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_PEIC, 1)
#define UART_PEIC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_PEIC, 0)

/*
 *  UART_FEIC bit field macros
 ****************************************************************************************
 */
#define UART_FEIC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_FEIC, 1)
#define UART_FEIC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_FEIC, 0)

/*
 *  UART_RTIC bit field macros
 ****************************************************************************************
 */
#define UART_RTIC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RTIC, 1)
#define UART_RTIC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RTIC, 0)

/*
 *  UART_TXIC bit field macros
 ****************************************************************************************
 */
#define UART_TXIC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_TXIC, 1)
#define UART_TXIC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_TXIC, 0)

/*
 *  UART_RXIC bit field macros
 ****************************************************************************************
 */
#define UART_RXIC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RXIC, 1)
#define UART_RXIC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RXIC, 0)

/*
 *  UART_DSRMIC bit field macros
 ****************************************************************************************
 */
#define UART_DSRMIC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_DSRMIC, 1)
#define UART_DSRMIC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_DSRMIC, 0)

/*
 *  UART_DCDMIC bit field macros
 ****************************************************************************************
 */
#define UART_DCDMIC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_DCDMIC, 1)
#define UART_DCDMIC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_DCDMIC, 0)

/*
 *  UART_CTSMIC bit field macros
 ****************************************************************************************
 */
#define UART_CTSMIC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_CTSMIC, 1)
#define UART_CTSMIC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_CTSMIC, 0)

/*
 *  UART_RIMIC bit field macros
 ****************************************************************************************
 */
#define UART_RIMIC_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RIMIC, 1)
#define UART_RIMIC_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RIMIC, 0)


/*
 *  UART_DMACR register macros
 ****************************************************************************************
 */
#define UART_DMACR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_DMACR))
#define UART_DMACR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_DMACR, (value))
#define UART_DMACR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_DMACR, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_DMACR) | (value))
#define UART_DMACR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, UART_DMACR, GET_WORD_EXCLUSIVE_BITFIELD(addr, UART_DMACR) & (~(value)))

/*
 *  UART_DMAONERR bit field macros
 ****************************************************************************************
 */
#define UART_DMAONERR_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_DMAONERR)
#define UART_DMAONERR_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_DMAONERR, 1)
#define UART_DMAONERR_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_DMAONERR, 0)

/*
 *  UART_TXDMAE bit field macros
 ****************************************************************************************
 */
#define UART_TXDMAE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_TXDMAE)
#define UART_TXDMAE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_TXDMAE, 1)
#define UART_TXDMAE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_TXDMAE, 0)

/*
 *  UART_RXDMAE bit field macros
 ****************************************************************************************
 */
#define UART_RXDMAE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, UART_RXDMAE)
#define UART_RXDMAE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RXDMAE, 1)
#define UART_RXDMAE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, UART_RXDMAE, 0)

#endif
