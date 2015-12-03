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
 * $RCSfile: gsn_reg_uart_spec.h,v $
 *
 * Description:
 *      This file contains register specification for UART Driver
 *
 ******************************************************************************
 */

#ifndef _REG_UART_H
#define _REG_UART_H

/***************************************************
 *
 *             UART
 *
 ***************************************************/


/*
 *  COMMON_UART0 instance offsets
 ****************************************************************************************
 */
#define GSN_UART0_REG_BASE 0x40010000
#define GSN_UART1_REG_BASE 0x40020000


/*
 *  UART_DR register defines
 ****************************************************************************************
 */
#define UART_DR_OFFSETADDRESS          0x00000000  /* RW */
#define UART_DR_BITOFFSET              0
#define UART_DR_BITFIELDSIZE           32
#define UART_DR_BITMASK                0xFFFFFFFF
#define UART_DR_INIT                   0x00000000
/*
 *  UART_DATA bit field defines
 ****************************************************************************************
 */
#define UART_DATA_OFFSETADDRESS                 UART_DR_OFFSETADDRESS
#define UART_DATA_BITOFFSET                     0
#define UART_DATA_BITFIELDSIZE                  8
#define UART_DATA_BITMASK                       0x000000ff
#define UART_DATA_INIT                          0x0

/*
 *  UART_RSR register defines
 ****************************************************************************************
 */
#define UART_RSR_OFFSETADDRESS         0x00000004  /* RW */
#define UART_RSR_BITOFFSET             0
#define UART_RSR_BITFIELDSIZE          32
#define UART_RSR_BITMASK               0xFFFFFFFF
#define UART_RSR_INIT                  0x00000000
/*
 *  UART_OE bit field defines
 ****************************************************************************************
 */
#define UART_OE_OFFSETADDRESS                   UART_RSR_OFFSETADDRESS
#define UART_OE_BITOFFSET                       3
#define UART_OE_BITFIELDSIZE                    1
#define UART_OE_BITMASK                         0x00000008
#define UART_OE_INIT                            0x0
/*
 *  UART_BE bit field defines
 ****************************************************************************************
 */
#define UART_BE_OFFSETADDRESS                   UART_RSR_OFFSETADDRESS
#define UART_BE_BITOFFSET                       2
#define UART_BE_BITFIELDSIZE                    1
#define UART_BE_BITMASK                         0x00000004
#define UART_BE_INIT                            0x0
/*
 *  UART_PE bit field defines
 ****************************************************************************************
 */
#define UART_PE_OFFSETADDRESS                   UART_RSR_OFFSETADDRESS
#define UART_PE_BITOFFSET                       1
#define UART_PE_BITFIELDSIZE                    1
#define UART_PE_BITMASK                         0x00000002
#define UART_PE_INIT                            0x0
/*
 *  UART_FE bit field defines
 ****************************************************************************************
 */
#define UART_FE_OFFSETADDRESS                   UART_RSR_OFFSETADDRESS
#define UART_FE_BITOFFSET                       0
#define UART_FE_BITFIELDSIZE                    1
#define UART_FE_BITMASK                         0x00000001
#define UART_FE_INIT                            0x0

/*
 *  UART_ECR register defines
 ****************************************************************************************
 */
#define UART_ECR_OFFSETADDRESS         0x00000004  /* RW */
#define UART_ECR_BITOFFSET             0
#define UART_ECR_BITFIELDSIZE          32
#define UART_ECR_BITMASK               0xFFFFFFFF
#define UART_ECR_INIT                  0x00000000
/*
 *  UART_ECRVAL bit field defines
 ****************************************************************************************
 */
#define UART_ECRVAL_OFFSETADDRESS               UART_ECR_OFFSETADDRESS
#define UART_ECRVAL_BITOFFSET                   0
#define UART_ECRVAL_BITFIELDSIZE                8
#define UART_ECRVAL_BITMASK                     0x000000ff
#define UART_ECRVAL_INIT                        0x0

/*
 *  UART_FR register defines
 ****************************************************************************************
 */
#define UART_FR_OFFSETADDRESS          0x00000018  /* R */
#define UART_FR_BITOFFSET              0
#define UART_FR_BITFIELDSIZE           32
#define UART_FR_BITMASK                0xFFFFFFFF
#define UART_FR_INIT                   0x00000090
/*
 *  UART_RI bit field defines
 ****************************************************************************************
 */
#define UART_RI_OFFSETADDRESS                   UART_FR_OFFSETADDRESS
#define UART_RI_BITOFFSET                       8
#define UART_RI_BITFIELDSIZE                    1
#define UART_RI_BITMASK                         0x00000100
#define UART_RI_INIT                            0x0
/*
 *  UART_TXFE bit field defines
 ****************************************************************************************
 */
#define UART_TXFE_OFFSETADDRESS                 UART_FR_OFFSETADDRESS
#define UART_TXFE_BITOFFSET                     7
#define UART_TXFE_BITFIELDSIZE                  1
#define UART_TXFE_BITMASK                       0x00000080
#define UART_TXFE_INIT                          0x1
/*
 *  UART_RXFF bit field defines
 ****************************************************************************************
 */
#define UART_RXFF_OFFSETADDRESS                 UART_FR_OFFSETADDRESS
#define UART_RXFF_BITOFFSET                     6
#define UART_RXFF_BITFIELDSIZE                  1
#define UART_RXFF_BITMASK                       0x00000040
#define UART_RXFF_INIT                          0x0
/*
 *  UART_TXFF bit field defines
 ****************************************************************************************
 */
#define UART_TXFF_OFFSETADDRESS                 UART_FR_OFFSETADDRESS
#define UART_TXFF_BITOFFSET                     5
#define UART_TXFF_BITFIELDSIZE                  1
#define UART_TXFF_BITMASK                       0x00000020
#define UART_TXFF_INIT                          0x0
/*
 *  UART_RXFE bit field defines
 ****************************************************************************************
 */
#define UART_RXFE_OFFSETADDRESS                 UART_FR_OFFSETADDRESS
#define UART_RXFE_BITOFFSET                     4
#define UART_RXFE_BITFIELDSIZE                  1
#define UART_RXFE_BITMASK                       0x00000010
#define UART_RXFE_INIT                          0x1
/*
 *  UART_BUSY bit field defines
 ****************************************************************************************
 */
#define UART_BUSY_OFFSETADDRESS                 UART_FR_OFFSETADDRESS
#define UART_BUSY_BITOFFSET                     3
#define UART_BUSY_BITFIELDSIZE                  1
#define UART_BUSY_BITMASK                       0x00000008
#define UART_BUSY_INIT                          0x0
/*
 *  UART_DCD bit field defines
 ****************************************************************************************
 */
#define UART_DCD_OFFSETADDRESS                  UART_FR_OFFSETADDRESS
#define UART_DCD_BITOFFSET                      2
#define UART_DCD_BITFIELDSIZE                   1
#define UART_DCD_BITMASK                        0x00000004
#define UART_DCD_INIT                           0x0
/*
 *  UART_DSR bit field defines
 ****************************************************************************************
 */
#define UART_DSR_OFFSETADDRESS                  UART_FR_OFFSETADDRESS
#define UART_DSR_BITOFFSET                      1
#define UART_DSR_BITFIELDSIZE                   1
#define UART_DSR_BITMASK                        0x00000002
#define UART_DSR_INIT                           0x0
/*
 *  UART_CTS bit field defines
 ****************************************************************************************
 */
#define UART_CTS_OFFSETADDRESS                  UART_FR_OFFSETADDRESS
#define UART_CTS_BITOFFSET                      0
#define UART_CTS_BITFIELDSIZE                   1
#define UART_CTS_BITMASK                        0x00000001
#define UART_CTS_INIT                           0x0

/*
 *  UART_IBRD register defines
 ****************************************************************************************
 */
#define UART_IBRD_OFFSETADDRESS        0x00000024  /* RW */
#define UART_IBRD_BITOFFSET            0
#define UART_IBRD_BITFIELDSIZE         32
#define UART_IBRD_BITMASK              0xFFFFFFFF
#define UART_IBRD_INIT                 0x00000000
/*
 *  UART_BAUD_DIVINT bit field defines
 ****************************************************************************************
 */
#define UART_BAUD_DIVINT_OFFSETADDRESS          UART_IBRD_OFFSETADDRESS
#define UART_BAUD_DIVINT_BITOFFSET              0
#define UART_BAUD_DIVINT_BITFIELDSIZE          16
#define UART_BAUD_DIVINT_BITMASK                0x0000ffff
#define UART_BAUD_DIVINT_INIT                   0x0

/*
 *  UART_FBRD register defines
 ****************************************************************************************
 */
#define UART_FBRD_OFFSETADDRESS        0x00000028  /* RW */
#define UART_FBRD_BITOFFSET            0
#define UART_FBRD_BITFIELDSIZE         32
#define UART_FBRD_BITMASK              0xFFFFFFFF
#define UART_FBRD_INIT                 0x00000000
/*
 *  UART_BAUD_DIVFRAC bit field defines
 ****************************************************************************************
 */
#define UART_BAUD_DIVFRAC_OFFSETADDRESS         UART_FBRD_OFFSETADDRESS
#define UART_BAUD_DIVFRAC_BITOFFSET             0
#define UART_BAUD_DIVFRAC_BITFIELDSIZE          6
#define UART_BAUD_DIVFRAC_BITMASK               0x0000003f
#define UART_BAUD_DIVFRAC_INIT                  0x0

/*
 *  UART_LCR register defines
 ****************************************************************************************
 */
#define UART_LCR_OFFSETADDRESS         0x0000002c  /* RW */
#define UART_LCR_BITOFFSET             0
#define UART_LCR_BITFIELDSIZE          32
#define UART_LCR_BITMASK               0xFFFFFFFF
#define UART_LCR_INIT                  0x00000000
/*
 *  UART_SPS bit field defines
 ****************************************************************************************
 */
#define UART_SPS_OFFSETADDRESS                  UART_LCR_OFFSETADDRESS
#define UART_SPS_BITOFFSET                      7
#define UART_SPS_BITFIELDSIZE                   1
#define UART_SPS_BITMASK                        0x00000080
#define UART_SPS_INIT                           0x0
/*
 *  UART_WLEN bit field defines
 ****************************************************************************************
 */
#define UART_WLEN_OFFSETADDRESS                 UART_LCR_OFFSETADDRESS
#define UART_WLEN_BITOFFSET                     5
#define UART_WLEN_BITFIELDSIZE                  2
#define UART_WLEN_BITMASK                       0x00000060
#define UART_WLEN_INIT                          0x0
/*
 *  UART_FEN bit field defines
 ****************************************************************************************
 */
#define UART_FEN_OFFSETADDRESS                  UART_LCR_OFFSETADDRESS
#define UART_FEN_BITOFFSET                      4
#define UART_FEN_BITFIELDSIZE                   1
#define UART_FEN_BITMASK                        0x00000010
#define UART_FEN_INIT                           0x0
/*
 *  UART_STP2 bit field defines
 ****************************************************************************************
 */
#define UART_STP2_OFFSETADDRESS                 UART_LCR_OFFSETADDRESS
#define UART_STP2_BITOFFSET                     3
#define UART_STP2_BITFIELDSIZE                  1
#define UART_STP2_BITMASK                       0x00000008
#define UART_STP2_INIT                          0x0
/*
 *  UART_EPS bit field defines
 ****************************************************************************************
 */
#define UART_EPS_OFFSETADDRESS                  UART_LCR_OFFSETADDRESS
#define UART_EPS_BITOFFSET                      2
#define UART_EPS_BITFIELDSIZE                   1
#define UART_EPS_BITMASK                        0x00000004
#define UART_EPS_INIT                           0x0
/*
 *  UART_PEN bit field defines
 ****************************************************************************************
 */
#define UART_PEN_OFFSETADDRESS                  UART_LCR_OFFSETADDRESS
#define UART_PEN_BITOFFSET                      1
#define UART_PEN_BITFIELDSIZE                   1
#define UART_PEN_BITMASK                        0x00000002
#define UART_PEN_INIT                           0x0
/*
 *  UART_BRK bit field defines
 ****************************************************************************************
 */
#define UART_BRK_OFFSETADDRESS                  UART_LCR_OFFSETADDRESS
#define UART_BRK_BITOFFSET                      0
#define UART_BRK_BITFIELDSIZE                   1
#define UART_BRK_BITMASK                        0x00000001
#define UART_BRK_INIT                           0x0

/*
 *  UART_CR register defines
 ****************************************************************************************
 */
#define UART_CR_OFFSETADDRESS          0x00000030  /* RW */
#define UART_CR_BITOFFSET              0
#define UART_CR_BITFIELDSIZE           32
#define UART_CR_BITMASK                0xFFFFFFFF
#define UART_CR_INIT                   0x00000300
/*
 *  UART_CTSEN bit field defines
 ****************************************************************************************
 */
#define UART_CTSEN_OFFSETADDRESS                UART_CR_OFFSETADDRESS
#define UART_CTSEN_BITOFFSET                   15
#define UART_CTSEN_BITFIELDSIZE                 1
#define UART_CTSEN_BITMASK                      0x00008000
#define UART_CTSEN_INIT                         0x0
/*
 *  UART_RTSEN bit field defines
 ****************************************************************************************
 */
#define UART_RTSEN_OFFSETADDRESS                UART_CR_OFFSETADDRESS
#define UART_RTSEN_BITOFFSET                   14
#define UART_RTSEN_BITFIELDSIZE                 1
#define UART_RTSEN_BITMASK                      0x00004000
#define UART_RTSEN_INIT                         0x0
/*
 *  UART_OUT2 bit field defines
 ****************************************************************************************
 */
#define UART_OUT2_OFFSETADDRESS                 UART_CR_OFFSETADDRESS
#define UART_OUT2_BITOFFSET                    13
#define UART_OUT2_BITFIELDSIZE                  1
#define UART_OUT2_BITMASK                       0x00002000
#define UART_OUT2_INIT                          0x0
/*
 *  UART_OUT1 bit field defines
 ****************************************************************************************
 */
#define UART_OUT1_OFFSETADDRESS                 UART_CR_OFFSETADDRESS
#define UART_OUT1_BITOFFSET                    12
#define UART_OUT1_BITFIELDSIZE                  1
#define UART_OUT1_BITMASK                       0x00001000
#define UART_OUT1_INIT                          0x0
/*
 *  UART_RTS bit field defines
 ****************************************************************************************
 */
#define UART_RTS_OFFSETADDRESS                  UART_CR_OFFSETADDRESS
#define UART_RTS_BITOFFSET                     11
#define UART_RTS_BITFIELDSIZE                   1
#define UART_RTS_BITMASK                        0x00000800
#define UART_RTS_INIT                           0x0
/*
 *  UART_DTR bit field defines
 ****************************************************************************************
 */
#define UART_DTR_OFFSETADDRESS                  UART_CR_OFFSETADDRESS
#define UART_DTR_BITOFFSET                     10
#define UART_DTR_BITFIELDSIZE                   1
#define UART_DTR_BITMASK                        0x00000400
#define UART_DTR_INIT                           0x0
/*
 *  UART_RXE bit field defines
 ****************************************************************************************
 */
#define UART_RXE_OFFSETADDRESS                  UART_CR_OFFSETADDRESS
#define UART_RXE_BITOFFSET                      9
#define UART_RXE_BITFIELDSIZE                   1
#define UART_RXE_BITMASK                        0x00000200
#define UART_RXE_INIT                           0x1
/*
 *  UART_TXE bit field defines
 ****************************************************************************************
 */
#define UART_TXE_OFFSETADDRESS                  UART_CR_OFFSETADDRESS
#define UART_TXE_BITOFFSET                      8
#define UART_TXE_BITFIELDSIZE                   1
#define UART_TXE_BITMASK                        0x00000100
#define UART_TXE_INIT                           0x1
/*
 *  UART_LBE bit field defines
 ****************************************************************************************
 */
#define UART_LBE_OFFSETADDRESS                  UART_CR_OFFSETADDRESS
#define UART_LBE_BITOFFSET                      7
#define UART_LBE_BITFIELDSIZE                   1
#define UART_LBE_BITMASK                        0x00000080
#define UART_LBE_INIT                           0x0
/*
 *  UART_SIRLP bit field defines
 ****************************************************************************************
 */
#define UART_SIRLP_OFFSETADDRESS                UART_CR_OFFSETADDRESS
#define UART_SIRLP_BITOFFSET                    2
#define UART_SIRLP_BITFIELDSIZE                 1
#define UART_SIRLP_BITMASK                      0x00000004
#define UART_SIRLP_INIT                         0x0
/*
 *  UART_SIREN bit field defines
 ****************************************************************************************
 */
#define UART_SIREN_OFFSETADDRESS                UART_CR_OFFSETADDRESS
#define UART_SIREN_BITOFFSET                    1
#define UART_SIREN_BITFIELDSIZE                 1
#define UART_SIREN_BITMASK                      0x00000002
#define UART_SIREN_INIT                         0x0
/*
 *  UART_UARTEN bit field defines
 ****************************************************************************************
 */
#define UART_UARTEN_OFFSETADDRESS               UART_CR_OFFSETADDRESS
#define UART_UARTEN_BITOFFSET                   0
#define UART_UARTEN_BITFIELDSIZE                1
#define UART_UARTEN_BITMASK                     0x00000001
#define UART_UARTEN_INIT                        0x0

/*
 *  UART_IFLS register defines
 ****************************************************************************************
 */
#define UART_IFLS_OFFSETADDRESS        0x00000034  /* RW */
#define UART_IFLS_BITOFFSET            0
#define UART_IFLS_BITFIELDSIZE         32
#define UART_IFLS_BITMASK              0xFFFFFFFF
#define UART_IFLS_INIT                 0x00000012
/*
 *  UART_RXIFLSEL bit field defines
 ****************************************************************************************
 */
#define UART_RXIFLSEL_OFFSETADDRESS             UART_IFLS_OFFSETADDRESS
#define UART_RXIFLSEL_BITOFFSET                 3
#define UART_RXIFLSEL_BITFIELDSIZE              3
#define UART_RXIFLSEL_BITMASK                   0x00000038
#define UART_RXIFLSEL_INIT                      0x2
/*
 *  UART_TXIFLSEL bit field defines
 ****************************************************************************************
 */
#define UART_TXIFLSEL_OFFSETADDRESS             UART_IFLS_OFFSETADDRESS
#define UART_TXIFLSEL_BITOFFSET                 0
#define UART_TXIFLSEL_BITFIELDSIZE              3
#define UART_TXIFLSEL_BITMASK                   0x00000007
#define UART_TXIFLSEL_INIT                      0x2

/*
 *  UART_IMSC register defines
 ****************************************************************************************
 */
#define UART_IMSC_OFFSETADDRESS        0x00000038  /* RW */
#define UART_IMSC_BITOFFSET            0
#define UART_IMSC_BITFIELDSIZE         32
#define UART_IMSC_BITMASK              0xFFFFFFFF
#define UART_IMSC_INIT                 0x00000000
/*
 *  UART_IM bit field defines
 ****************************************************************************************
 */
#define UART_IM_OFFSETADDRESS                   UART_IMSC_OFFSETADDRESS
#define UART_IM_BITOFFSET                       0
#define UART_IM_BITFIELDSIZE                   11
#define UART_IM_BITMASK                         0x000007ff
#define UART_IM_INIT                            0x0
/*
 *  UART_OEIM bit field defines
 ****************************************************************************************
 */
#define UART_OEIM_OFFSETADDRESS                 UART_IMSC_OFFSETADDRESS
#define UART_OEIM_BITOFFSET                    10
#define UART_OEIM_BITFIELDSIZE                  1
#define UART_OEIM_BITMASK                       0x00000400
#define UART_OEIM_INIT                          0x0
/*
 *  UART_BEIM bit field defines
 ****************************************************************************************
 */
#define UART_BEIM_OFFSETADDRESS                 UART_IMSC_OFFSETADDRESS
#define UART_BEIM_BITOFFSET                     9
#define UART_BEIM_BITFIELDSIZE                  1
#define UART_BEIM_BITMASK                       0x00000200
#define UART_BEIM_INIT                          0x0
/*
 *  UART_PEIM bit field defines
 ****************************************************************************************
 */
#define UART_PEIM_OFFSETADDRESS                 UART_IMSC_OFFSETADDRESS
#define UART_PEIM_BITOFFSET                     8
#define UART_PEIM_BITFIELDSIZE                  1
#define UART_PEIM_BITMASK                       0x00000100
#define UART_PEIM_INIT                          0x0
/*
 *  UART_FEIM bit field defines
 ****************************************************************************************
 */
#define UART_FEIM_OFFSETADDRESS                 UART_IMSC_OFFSETADDRESS
#define UART_FEIM_BITOFFSET                     7
#define UART_FEIM_BITFIELDSIZE                  1
#define UART_FEIM_BITMASK                       0x00000080
#define UART_FEIM_INIT                          0x0
/*
 *  UART_RTIM bit field defines
 ****************************************************************************************
 */
#define UART_RTIM_OFFSETADDRESS                 UART_IMSC_OFFSETADDRESS
#define UART_RTIM_BITOFFSET                     6
#define UART_RTIM_BITFIELDSIZE                  1
#define UART_RTIM_BITMASK                       0x00000040
#define UART_RTIM_INIT                          0x0
/*
 *  UART_TXIM bit field defines
 ****************************************************************************************
 */
#define UART_TXIM_OFFSETADDRESS                 UART_IMSC_OFFSETADDRESS
#define UART_TXIM_BITOFFSET                     5
#define UART_TXIM_BITFIELDSIZE                  1
#define UART_TXIM_BITMASK                       0x00000020
#define UART_TXIM_INIT                          0x0
/*
 *  UART_RXIM bit field defines
 ****************************************************************************************
 */
#define UART_RXIM_OFFSETADDRESS                 UART_IMSC_OFFSETADDRESS
#define UART_RXIM_BITOFFSET                     4
#define UART_RXIM_BITFIELDSIZE                  1
#define UART_RXIM_BITMASK                       0x00000010
#define UART_RXIM_INIT                          0x0
/*
 *  UART_DSRMIM bit field defines
 ****************************************************************************************
 */
#define UART_DSRMIM_OFFSETADDRESS               UART_IMSC_OFFSETADDRESS
#define UART_DSRMIM_BITOFFSET                   3
#define UART_DSRMIM_BITFIELDSIZE                1
#define UART_DSRMIM_BITMASK                     0x00000008
#define UART_DSRMIM_INIT                        0x0
/*
 *  UART_DCDMIM bit field defines
 ****************************************************************************************
 */
#define UART_DCDMIM_OFFSETADDRESS               UART_IMSC_OFFSETADDRESS
#define UART_DCDMIM_BITOFFSET                   2
#define UART_DCDMIM_BITFIELDSIZE                1
#define UART_DCDMIM_BITMASK                     0x00000004
#define UART_DCDMIM_INIT                        0x0
/*
 *  UART_CTSMIM bit field defines
 ****************************************************************************************
 */
#define UART_CTSMIM_OFFSETADDRESS               UART_IMSC_OFFSETADDRESS
#define UART_CTSMIM_BITOFFSET                   1
#define UART_CTSMIM_BITFIELDSIZE                1
#define UART_CTSMIM_BITMASK                     0x00000002
#define UART_CTSMIM_INIT                        0x0
/*
 *  UART_RIMIM bit field defines
 ****************************************************************************************
 */
#define UART_RIMIM_OFFSETADDRESS                UART_IMSC_OFFSETADDRESS
#define UART_RIMIM_BITOFFSET                    0
#define UART_RIMIM_BITFIELDSIZE                 1
#define UART_RIMIM_BITMASK                      0x00000001
#define UART_RIMIM_INIT                         0x0

/*
 *  UART_RIS register defines
 ****************************************************************************************
 */
#define UART_RIS_OFFSETADDRESS         0x0000003c  /* R */
#define UART_RIS_BITOFFSET             0
#define UART_RIS_BITFIELDSIZE          32
#define UART_RIS_BITMASK               0xFFFFFFFF
#define UART_RIS_INIT                  0x00000000
/*
 *  UART_IS bit field defines
 ****************************************************************************************
 */
#define UART_IS_OFFSETADDRESS                   UART_RIS_OFFSETADDRESS
#define UART_IS_BITOFFSET                       0
#define UART_IS_BITFIELDSIZE                   11
#define UART_IS_BITMASK                         0x000007ff
#define UART_IS_INIT                            0x0
/*
 *  UART_OERIS bit field defines
 ****************************************************************************************
 */
#define UART_OERIS_OFFSETADDRESS                UART_RIS_OFFSETADDRESS
#define UART_OERIS_BITOFFSET                   10
#define UART_OERIS_BITFIELDSIZE                 1
#define UART_OERIS_BITMASK                      0x00000400
#define UART_OERIS_INIT                         0x0
/*
 *  UART_BERIS bit field defines
 ****************************************************************************************
 */
#define UART_BERIS_OFFSETADDRESS                UART_RIS_OFFSETADDRESS
#define UART_BERIS_BITOFFSET                    9
#define UART_BERIS_BITFIELDSIZE                 1
#define UART_BERIS_BITMASK                      0x00000200
#define UART_BERIS_INIT                         0x0
/*
 *  UART_PERIS bit field defines
 ****************************************************************************************
 */
#define UART_PERIS_OFFSETADDRESS                UART_RIS_OFFSETADDRESS
#define UART_PERIS_BITOFFSET                    8
#define UART_PERIS_BITFIELDSIZE                 1
#define UART_PERIS_BITMASK                      0x00000100
#define UART_PERIS_INIT                         0x0
/*
 *  UART_FERIS bit field defines
 ****************************************************************************************
 */
#define UART_FERIS_OFFSETADDRESS                UART_RIS_OFFSETADDRESS
#define UART_FERIS_BITOFFSET                    7
#define UART_FERIS_BITFIELDSIZE                 1
#define UART_FERIS_BITMASK                      0x00000080
#define UART_FERIS_INIT                         0x0
/*
 *  UART_RTRIS bit field defines
 ****************************************************************************************
 */
#define UART_RTRIS_OFFSETADDRESS                UART_RIS_OFFSETADDRESS
#define UART_RTRIS_BITOFFSET                    6
#define UART_RTRIS_BITFIELDSIZE                 1
#define UART_RTRIS_BITMASK                      0x00000040
#define UART_RTRIS_INIT                         0x0
/*
 *  UART_TXRIS bit field defines
 ****************************************************************************************
 */
#define UART_TXRIS_OFFSETADDRESS                UART_RIS_OFFSETADDRESS
#define UART_TXRIS_BITOFFSET                    5
#define UART_TXRIS_BITFIELDSIZE                 1
#define UART_TXRIS_BITMASK                      0x00000020
#define UART_TXRIS_INIT                         0x0
/*
 *  UART_RXRIS bit field defines
 ****************************************************************************************
 */
#define UART_RXRIS_OFFSETADDRESS                UART_RIS_OFFSETADDRESS
#define UART_RXRIS_BITOFFSET                    4
#define UART_RXRIS_BITFIELDSIZE                 1
#define UART_RXRIS_BITMASK                      0x00000010
#define UART_RXRIS_INIT                         0x0
/*
 *  UART_DSRRMIS bit field defines
 ****************************************************************************************
 */
#define UART_DSRRMIS_OFFSETADDRESS              UART_RIS_OFFSETADDRESS
#define UART_DSRRMIS_BITOFFSET                  3
#define UART_DSRRMIS_BITFIELDSIZE               1
#define UART_DSRRMIS_BITMASK                    0x00000008
#define UART_DSRRMIS_INIT                       0x0
/*
 *  UART_DCDRMIS bit field defines
 ****************************************************************************************
 */
#define UART_DCDRMIS_OFFSETADDRESS              UART_RIS_OFFSETADDRESS
#define UART_DCDRMIS_BITOFFSET                  2
#define UART_DCDRMIS_BITFIELDSIZE               1
#define UART_DCDRMIS_BITMASK                    0x00000004
#define UART_DCDRMIS_INIT                       0x0
/*
 *  UART_CTSRMIS bit field defines
 ****************************************************************************************
 */
#define UART_CTSRMIS_OFFSETADDRESS              UART_RIS_OFFSETADDRESS
#define UART_CTSRMIS_BITOFFSET                  1
#define UART_CTSRMIS_BITFIELDSIZE               1
#define UART_CTSRMIS_BITMASK                    0x00000002
#define UART_CTSRMIS_INIT                       0x0
/*
 *  UART_RIRMIS bit field defines
 ****************************************************************************************
 */
#define UART_RIRMIS_OFFSETADDRESS               UART_RIS_OFFSETADDRESS
#define UART_RIRMIS_BITOFFSET                   0
#define UART_RIRMIS_BITFIELDSIZE                1
#define UART_RIRMIS_BITMASK                     0x00000001
#define UART_RIRMIS_INIT                        0x0

/*
 *  UART_MIS register defines
 ****************************************************************************************
 */
#define UART_MIS_OFFSETADDRESS         0x00000040  /* R */
#define UART_MIS_BITOFFSET             0
#define UART_MIS_BITFIELDSIZE          32
#define UART_MIS_BITMASK               0xFFFFFFFF
#define UART_MIS_INIT                  0x00000000
/*
 *  UART_OEMIS bit field defines
 ****************************************************************************************
 */
#define UART_OEMIS_OFFSETADDRESS                UART_MIS_OFFSETADDRESS
#define UART_OEMIS_BITOFFSET                   10
#define UART_OEMIS_BITFIELDSIZE                 1
#define UART_OEMIS_BITMASK                      0x00000400
#define UART_OEMIS_INIT                         0x0
/*
 *  UART_BEMIS bit field defines
 ****************************************************************************************
 */
#define UART_BEMIS_OFFSETADDRESS                UART_MIS_OFFSETADDRESS
#define UART_BEMIS_BITOFFSET                    9
#define UART_BEMIS_BITFIELDSIZE                 1
#define UART_BEMIS_BITMASK                      0x00000200
#define UART_BEMIS_INIT                         0x0
/*
 *  UART_PEMIS bit field defines
 ****************************************************************************************
 */
#define UART_PEMIS_OFFSETADDRESS                UART_MIS_OFFSETADDRESS
#define UART_PEMIS_BITOFFSET                    8
#define UART_PEMIS_BITFIELDSIZE                 1
#define UART_PEMIS_BITMASK                      0x00000100
#define UART_PEMIS_INIT                         0x0
/*
 *  UART_FEMIS bit field defines
 ****************************************************************************************
 */
#define UART_FEMIS_OFFSETADDRESS                UART_MIS_OFFSETADDRESS
#define UART_FEMIS_BITOFFSET                    7
#define UART_FEMIS_BITFIELDSIZE                 1
#define UART_FEMIS_BITMASK                      0x00000080
#define UART_FEMIS_INIT                         0x0
/*
 *  UART_RTMIS bit field defines
 ****************************************************************************************
 */
#define UART_RTMIS_OFFSETADDRESS                UART_MIS_OFFSETADDRESS
#define UART_RTMIS_BITOFFSET                    6
#define UART_RTMIS_BITFIELDSIZE                 1
#define UART_RTMIS_BITMASK                      0x00000040
#define UART_RTMIS_INIT                         0x0
/*
 *  UART_TXMIS bit field defines
 ****************************************************************************************
 */
#define UART_TXMIS_OFFSETADDRESS                UART_MIS_OFFSETADDRESS
#define UART_TXMIS_BITOFFSET                    5
#define UART_TXMIS_BITFIELDSIZE                 1
#define UART_TXMIS_BITMASK                      0x00000020
#define UART_TXMIS_INIT                         0x0
/*
 *  UART_RXMIS bit field defines
 ****************************************************************************************
 */
#define UART_RXMIS_OFFSETADDRESS                UART_MIS_OFFSETADDRESS
#define UART_RXMIS_BITOFFSET                    4
#define UART_RXMIS_BITFIELDSIZE                 1
#define UART_RXMIS_BITMASK                      0x00000010
#define UART_RXMIS_INIT                         0x0
/*
 *  UART_DSRMMIS bit field defines
 ****************************************************************************************
 */
#define UART_DSRMMIS_OFFSETADDRESS              UART_MIS_OFFSETADDRESS
#define UART_DSRMMIS_BITOFFSET                  3
#define UART_DSRMMIS_BITFIELDSIZE               1
#define UART_DSRMMIS_BITMASK                    0x00000008
#define UART_DSRMMIS_INIT                       0x0
/*
 *  UART_DCDMMIS bit field defines
 ****************************************************************************************
 */
#define UART_DCDMMIS_OFFSETADDRESS              UART_MIS_OFFSETADDRESS
#define UART_DCDMMIS_BITOFFSET                  2
#define UART_DCDMMIS_BITFIELDSIZE               1
#define UART_DCDMMIS_BITMASK                    0x00000004
#define UART_DCDMMIS_INIT                       0x0
/*
 *  UART_CTSMMIS bit field defines
 ****************************************************************************************
 */
#define UART_CTSMMIS_OFFSETADDRESS              UART_MIS_OFFSETADDRESS
#define UART_CTSMMIS_BITOFFSET                  1
#define UART_CTSMMIS_BITFIELDSIZE               1
#define UART_CTSMMIS_BITMASK                    0x00000002
#define UART_CTSMMIS_INIT                       0x0
/*
 *  UART_RIMMIS bit field defines
 ****************************************************************************************
 */
#define UART_RIMMIS_OFFSETADDRESS               UART_MIS_OFFSETADDRESS
#define UART_RIMMIS_BITOFFSET                   0
#define UART_RIMMIS_BITFIELDSIZE                1
#define UART_RIMMIS_BITMASK                     0x00000001
#define UART_RIMMIS_INIT                        0x0

/*
 *  UART_ICR register defines
 ****************************************************************************************
 */
#define UART_ICR_OFFSETADDRESS         0x00000044  /* W */
#define UART_ICR_BITOFFSET             0
#define UART_ICR_BITFIELDSIZE          32
#define UART_ICR_BITMASK               0xFFFFFFFF
#define UART_ICR_INIT                  0x00000000
/*
 *  UART_IC bit field defines
 ****************************************************************************************
 */
#define UART_IC_OFFSETADDRESS                   UART_ICR_OFFSETADDRESS
#define UART_IC_BITOFFSET                       0
#define UART_IC_BITFIELDSIZE                   11
#define UART_IC_BITMASK                         0x000007ff
#define UART_IC_INIT                            0x0
/*
 *  UART_OEIC bit field defines
 ****************************************************************************************
 */
#define UART_OEIC_OFFSETADDRESS                 UART_ICR_OFFSETADDRESS
#define UART_OEIC_BITOFFSET                    10
#define UART_OEIC_BITFIELDSIZE                  1
#define UART_OEIC_BITMASK                       0x00000400
#define UART_OEIC_INIT                          0x0
/*
 *  UART_BEIC bit field defines
 ****************************************************************************************
 */
#define UART_BEIC_OFFSETADDRESS                 UART_ICR_OFFSETADDRESS
#define UART_BEIC_BITOFFSET                     9
#define UART_BEIC_BITFIELDSIZE                  1
#define UART_BEIC_BITMASK                       0x00000200
#define UART_BEIC_INIT                          0x0
/*
 *  UART_PEIC bit field defines
 ****************************************************************************************
 */
#define UART_PEIC_OFFSETADDRESS                 UART_ICR_OFFSETADDRESS
#define UART_PEIC_BITOFFSET                     8
#define UART_PEIC_BITFIELDSIZE                  1
#define UART_PEIC_BITMASK                       0x00000100
#define UART_PEIC_INIT                          0x0
/*
 *  UART_FEIC bit field defines
 ****************************************************************************************
 */
#define UART_FEIC_OFFSETADDRESS                 UART_ICR_OFFSETADDRESS
#define UART_FEIC_BITOFFSET                     7
#define UART_FEIC_BITFIELDSIZE                  1
#define UART_FEIC_BITMASK                       0x00000080
#define UART_FEIC_INIT                          0x0
/*
 *  UART_RTIC bit field defines
 ****************************************************************************************
 */
#define UART_RTIC_OFFSETADDRESS                 UART_ICR_OFFSETADDRESS
#define UART_RTIC_BITOFFSET                     6
#define UART_RTIC_BITFIELDSIZE                  1
#define UART_RTIC_BITMASK                       0x00000040
#define UART_RTIC_INIT                          0x0
/*
 *  UART_TXIC bit field defines
 ****************************************************************************************
 */
#define UART_TXIC_OFFSETADDRESS                 UART_ICR_OFFSETADDRESS
#define UART_TXIC_BITOFFSET                     5
#define UART_TXIC_BITFIELDSIZE                  1
#define UART_TXIC_BITMASK                       0x00000020
#define UART_TXIC_INIT                          0x0
/*
 *  UART_RXIC bit field defines
 ****************************************************************************************
 */
#define UART_RXIC_OFFSETADDRESS                 UART_ICR_OFFSETADDRESS
#define UART_RXIC_BITOFFSET                     4
#define UART_RXIC_BITFIELDSIZE                  1
#define UART_RXIC_BITMASK                       0x00000010
#define UART_RXIC_INIT                          0x0
/*
 *  UART_DSRMIC bit field defines
 ****************************************************************************************
 */
#define UART_DSRMIC_OFFSETADDRESS               UART_ICR_OFFSETADDRESS
#define UART_DSRMIC_BITOFFSET                   3
#define UART_DSRMIC_BITFIELDSIZE                1
#define UART_DSRMIC_BITMASK                     0x00000008
#define UART_DSRMIC_INIT                        0x0
/*
 *  UART_DCDMIC bit field defines
 ****************************************************************************************
 */
#define UART_DCDMIC_OFFSETADDRESS               UART_ICR_OFFSETADDRESS
#define UART_DCDMIC_BITOFFSET                   2
#define UART_DCDMIC_BITFIELDSIZE                1
#define UART_DCDMIC_BITMASK                     0x00000004
#define UART_DCDMIC_INIT                        0x0
/*
 *  UART_CTSMIC bit field defines
 ****************************************************************************************
 */
#define UART_CTSMIC_OFFSETADDRESS               UART_ICR_OFFSETADDRESS
#define UART_CTSMIC_BITOFFSET                   1
#define UART_CTSMIC_BITFIELDSIZE                1
#define UART_CTSMIC_BITMASK                     0x00000002
#define UART_CTSMIC_INIT                        0x0
/*
 *  UART_RIMIC bit field defines
 ****************************************************************************************
 */
#define UART_RIMIC_OFFSETADDRESS                UART_ICR_OFFSETADDRESS
#define UART_RIMIC_BITOFFSET                    0
#define UART_RIMIC_BITFIELDSIZE                 1
#define UART_RIMIC_BITMASK                      0x00000001
#define UART_RIMIC_INIT                         0x0

/*
 *  UART_DMACR register defines
 ****************************************************************************************
 */
#define UART_DMACR_OFFSETADDRESS       0x00000048  /* RW */
#define UART_DMACR_BITOFFSET           0
#define UART_DMACR_BITFIELDSIZE        32
#define UART_DMACR_BITMASK             0xFFFFFFFF
#define UART_DMACR_INIT                0x00000000
/*
 *  UART_DMAONERR bit field defines
 ****************************************************************************************
 */
#define UART_DMAONERR_OFFSETADDRESS             UART_DMACR_OFFSETADDRESS
#define UART_DMAONERR_BITOFFSET                 2
#define UART_DMAONERR_BITFIELDSIZE              1
#define UART_DMAONERR_BITMASK                   0x00000004
#define UART_DMAONERR_INIT                      0x0
/*
 *  UART_TXDMAE bit field defines
 ****************************************************************************************
 */
#define UART_TXDMAE_OFFSETADDRESS               UART_DMACR_OFFSETADDRESS
#define UART_TXDMAE_BITOFFSET                   1
#define UART_TXDMAE_BITFIELDSIZE                1
#define UART_TXDMAE_BITMASK                     0x00000002
#define UART_TXDMAE_INIT                        0x0
/*
 *  UART_RXDMAE bit field defines
 ****************************************************************************************
 */
#define UART_RXDMAE_OFFSETADDRESS               UART_DMACR_OFFSETADDRESS
#define UART_RXDMAE_BITOFFSET                   0
#define UART_RXDMAE_BITFIELDSIZE                1
#define UART_RXDMAE_BITMASK                     0x00000001
#define UART_RXDMAE_INIT                        0x0
#endif
