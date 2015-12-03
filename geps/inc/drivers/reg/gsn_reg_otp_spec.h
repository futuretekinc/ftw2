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
* $RCSfile: gsn_reg_otp_spec.h,v $
*
* Description : This file contains OTP register specifications.
******************************************************************************/

#ifndef _REG_OTP_SPEC_H
#define _REG_OTP_SPEC_H

/***************************************************
 *
 *             OTP
 *
 ***************************************************/


/*
 *  OTP0 instance offsets
 ****************************************************************************************
 */
#define OTP0 0x400D0000

/*
 *  OTP1 instance offsets
 ****************************************************************************************
 */
#define OTP1 0x40150000

/*
 *  OTP_OTP_SM_PAGE_RD register defines
 ****************************************************************************************
 */
#define OTP_OTP_SM_PAGE_RD_OFFSETADDRESS 0x00000000  /* RW */
#define OTP_OTP_SM_PAGE_RD_BITOFFSET   0
#define OTP_OTP_SM_PAGE_RD_BITFIELDSIZE 32
#define OTP_OTP_SM_PAGE_RD_BITMASK     0xFFFFFFFF
#define OTP_OTP_SM_PAGE_RD_INIT        0x00000000
/*
 *  OTP_PAGE_RD_REQ bit field defines
 ****************************************************************************************
 */
#define OTP_PAGE_RD_REQ_OFFSETADDRESS           OTP_OTP_SM_PAGE_RD_OFFSETADDRESS
#define OTP_PAGE_RD_REQ_BITOFFSET               0
#define OTP_PAGE_RD_REQ_BITFIELDSIZE            1
#define OTP_PAGE_RD_REQ_BITMASK                 0x00000001
#define OTP_PAGE_RD_REQ_INIT                    0x0

/*
 *  OTP_OTP_SM_PAGE_WR register defines
 ****************************************************************************************
 */
#define OTP_OTP_SM_PAGE_WR_OFFSETADDRESS 0x00000004  /* RW */
#define OTP_OTP_SM_PAGE_WR_BITOFFSET   0
#define OTP_OTP_SM_PAGE_WR_BITFIELDSIZE 32
#define OTP_OTP_SM_PAGE_WR_BITMASK     0xFFFFFFFF
#define OTP_OTP_SM_PAGE_WR_INIT        0x00000000
/*
 *  OTP_PAGE_WR_REQ bit field defines
 ****************************************************************************************
 */
#define OTP_PAGE_WR_REQ_OFFSETADDRESS           OTP_OTP_SM_PAGE_WR_OFFSETADDRESS
#define OTP_PAGE_WR_REQ_BITOFFSET               0
#define OTP_PAGE_WR_REQ_BITFIELDSIZE            1
#define OTP_PAGE_WR_REQ_BITMASK                 0x00000001
#define OTP_PAGE_WR_REQ_INIT                    0x0

/*
 *  OTP_OTP_SM_NV_STORE register defines
 ****************************************************************************************
 */
#define OTP_OTP_SM_NV_STORE_OFFSETADDRESS 0x00000008  /* RW */
#define OTP_OTP_SM_NV_STORE_BITOFFSET  0
#define OTP_OTP_SM_NV_STORE_BITFIELDSIZE 32
#define OTP_OTP_SM_NV_STORE_BITMASK    0xFFFFFFFF
#define OTP_OTP_SM_NV_STORE_INIT       0x00000000
/*
 *  OTP_NV_STORE_REQ bit field defines
 ****************************************************************************************
 */
#define OTP_NV_STORE_REQ_OFFSETADDRESS          OTP_OTP_SM_NV_STORE_OFFSETADDRESS
#define OTP_NV_STORE_REQ_BITOFFSET              0
#define OTP_NV_STORE_REQ_BITFIELDSIZE           1
#define OTP_NV_STORE_REQ_BITMASK                0x00000001
#define OTP_NV_STORE_REQ_INIT                   0x0

/*
 *  OTP_OTP_SM_NV_RCALL register defines
 ****************************************************************************************
 */
#define OTP_OTP_SM_NV_RCALL_OFFSETADDRESS 0x0000000c  /* RW */
#define OTP_OTP_SM_NV_RCALL_BITOFFSET  0
#define OTP_OTP_SM_NV_RCALL_BITFIELDSIZE 32
#define OTP_OTP_SM_NV_RCALL_BITMASK    0xFFFFFFFF
#define OTP_OTP_SM_NV_RCALL_INIT       0x00000000
/*
 *  OTP_NV_RCALL_REQ bit field defines
 ****************************************************************************************
 */
#define OTP_NV_RCALL_REQ_OFFSETADDRESS          OTP_OTP_SM_NV_RCALL_OFFSETADDRESS
#define OTP_NV_RCALL_REQ_BITOFFSET              0
#define OTP_NV_RCALL_REQ_BITFIELDSIZE           1
#define OTP_NV_RCALL_REQ_BITMASK                0x00000001
#define OTP_NV_RCALL_REQ_INIT                   0x0

/*
 *  OTP_OTP_SM_RD_DATA_LSB register defines
 ****************************************************************************************
 */
#define OTP_OTP_SM_RD_DATA_LSB_OFFSETADDRESS 0x00000010  /* RO */
#define OTP_OTP_SM_RD_DATA_LSB_BITOFFSET 0
#define OTP_OTP_SM_RD_DATA_LSB_BITFIELDSIZE 32
#define OTP_OTP_SM_RD_DATA_LSB_BITMASK 0xFFFFFFFF
#define OTP_OTP_SM_RD_DATA_LSB_INIT    0x00000000
/*
 *  OTP_RD_BUFFER_31_0 bit field defines
 ****************************************************************************************
 */
#define OTP_RD_BUFFER_31_0_OFFSETADDRESS        OTP_OTP_SM_RD_DATA_LSB_OFFSETADDRESS
#define OTP_RD_BUFFER_31_0_BITOFFSET            0
#define OTP_RD_BUFFER_31_0_BITFIELDSIZE        32
#define OTP_RD_BUFFER_31_0_BITMASK              0xffffffff
#define OTP_RD_BUFFER_31_0_INIT                 0x0

/*
 *  OTP_OTP_SM_RD_DATA_MSB register defines
 ****************************************************************************************
 */
#define OTP_OTP_SM_RD_DATA_MSB_OFFSETADDRESS 0x00000014  /* RO */
#define OTP_OTP_SM_RD_DATA_MSB_BITOFFSET 0
#define OTP_OTP_SM_RD_DATA_MSB_BITFIELDSIZE 32
#define OTP_OTP_SM_RD_DATA_MSB_BITMASK 0xFFFFFFFF
#define OTP_OTP_SM_RD_DATA_MSB_INIT    0x00000000
/*
 *  OTP_RD_BUFFER_63_32 bit field defines
 ****************************************************************************************
 */
#define OTP_RD_BUFFER_63_32_OFFSETADDRESS       OTP_OTP_SM_RD_DATA_MSB_OFFSETADDRESS
#define OTP_RD_BUFFER_63_32_BITOFFSET           0
#define OTP_RD_BUFFER_63_32_BITFIELDSIZE       32
#define OTP_RD_BUFFER_63_32_BITMASK             0xffffffff
#define OTP_RD_BUFFER_63_32_INIT                0x0

/*
 *  OTP_OTP_SM_WR_DATA_LSB register defines
 ****************************************************************************************
 */
#define OTP_OTP_SM_WR_DATA_LSB_OFFSETADDRESS 0x00000018  /* RW */
#define OTP_OTP_SM_WR_DATA_LSB_BITOFFSET 0
#define OTP_OTP_SM_WR_DATA_LSB_BITFIELDSIZE 32
#define OTP_OTP_SM_WR_DATA_LSB_BITMASK 0xFFFFFFFF
#define OTP_OTP_SM_WR_DATA_LSB_INIT    0x00000000
/*
 *  OTP_WR_BUFFER_31_0 bit field defines
 ****************************************************************************************
 */
#define OTP_WR_BUFFER_31_0_OFFSETADDRESS        OTP_OTP_SM_WR_DATA_LSB_OFFSETADDRESS
#define OTP_WR_BUFFER_31_0_BITOFFSET            0
#define OTP_WR_BUFFER_31_0_BITFIELDSIZE        32
#define OTP_WR_BUFFER_31_0_BITMASK              0xffffffff
#define OTP_WR_BUFFER_31_0_INIT                 0x0

/*
 *  OTP_OTP_SM_WR_DATA_MSB register defines
 ****************************************************************************************
 */
#define OTP_OTP_SM_WR_DATA_MSB_OFFSETADDRESS 0x0000001c  /* RW */
#define OTP_OTP_SM_WR_DATA_MSB_BITOFFSET 0
#define OTP_OTP_SM_WR_DATA_MSB_BITFIELDSIZE 32
#define OTP_OTP_SM_WR_DATA_MSB_BITMASK 0xFFFFFFFF
#define OTP_OTP_SM_WR_DATA_MSB_INIT    0x00000000
/*
 *  OTP_WR_BUFFER_63_32 bit field defines
 ****************************************************************************************
 */
#define OTP_WR_BUFFER_63_32_OFFSETADDRESS       OTP_OTP_SM_WR_DATA_MSB_OFFSETADDRESS
#define OTP_WR_BUFFER_63_32_BITOFFSET           0
#define OTP_WR_BUFFER_63_32_BITFIELDSIZE       32
#define OTP_WR_BUFFER_63_32_BITMASK             0xffffffff
#define OTP_WR_BUFFER_63_32_INIT                0x0

/*
 *  OTP_OTP_SM_NV_ADDR register defines
 ****************************************************************************************
 */
#define OTP_OTP_SM_NV_ADDR_OFFSETADDRESS 0x00000020  /* RW */
#define OTP_OTP_SM_NV_ADDR_BITOFFSET   0
#define OTP_OTP_SM_NV_ADDR_BITFIELDSIZE 32
#define OTP_OTP_SM_NV_ADDR_BITMASK     0xFFFFFFFF
#define OTP_OTP_SM_NV_ADDR_INIT        0x00000000
/*
 *  OTP_NVA_BUFFER bit field defines
 ****************************************************************************************
 */
#define OTP_NVA_BUFFER_OFFSETADDRESS            OTP_OTP_SM_NV_ADDR_OFFSETADDRESS
#define OTP_NVA_BUFFER_BITOFFSET                0
#define OTP_NVA_BUFFER_BITFIELDSIZE             9
#define OTP_NVA_BUFFER_BITMASK                  0x000001ff
#define OTP_NVA_BUFFER_INIT                     0x0

/*
 *  OTP_OTP_CVAL_STORE_WAIT register defines
 ****************************************************************************************
 */
#define OTP_OTP_CVAL_STORE_WAIT_OFFSETADDRESS 0x00000024  /* RW */
#define OTP_OTP_CVAL_STORE_WAIT_BITOFFSET 0
#define OTP_OTP_CVAL_STORE_WAIT_BITFIELDSIZE 32
#define OTP_OTP_CVAL_STORE_WAIT_BITMASK 0xFFFFFFFF
#define OTP_OTP_CVAL_STORE_WAIT_INIT   0x00001f40
/*
 *  OTP_CVAL_STORE_WAIT bit field defines
 ****************************************************************************************
 */
#define OTP_CVAL_STORE_WAIT_OFFSETADDRESS       OTP_OTP_CVAL_STORE_WAIT_OFFSETADDRESS
#define OTP_CVAL_STORE_WAIT_BITOFFSET           0
#define OTP_CVAL_STORE_WAIT_BITFIELDSIZE       24
#define OTP_CVAL_STORE_WAIT_BITMASK             0x00ffffff
#define OTP_CVAL_STORE_WAIT_INIT                0x1f40

/*
 *  OTP_OTP_CVAL_STORE_END register defines
 ****************************************************************************************
 */
#define OTP_OTP_CVAL_STORE_END_OFFSETADDRESS 0x00000028  /* RW */
#define OTP_OTP_CVAL_STORE_END_BITOFFSET 0
#define OTP_OTP_CVAL_STORE_END_BITFIELDSIZE 32
#define OTP_OTP_CVAL_STORE_END_BITMASK 0xFFFFFFFF
#define OTP_OTP_CVAL_STORE_END_INIT    0x00000005
/*
 *  OTP_CVAL_STORE_END bit field defines
 ****************************************************************************************
 */
#define OTP_CVAL_STORE_END_OFFSETADDRESS        OTP_OTP_CVAL_STORE_END_OFFSETADDRESS
#define OTP_CVAL_STORE_END_BITOFFSET            0
#define OTP_CVAL_STORE_END_BITFIELDSIZE         8
#define OTP_CVAL_STORE_END_BITMASK              0x000000ff
#define OTP_CVAL_STORE_END_INIT                 0x5

/*
 *  OTP_OTP_CVAL_RCALL_END register defines
 ****************************************************************************************
 */
#define OTP_OTP_CVAL_RCALL_END_OFFSETADDRESS 0x0000002c  /* RW */
#define OTP_OTP_CVAL_RCALL_END_BITOFFSET 0
#define OTP_OTP_CVAL_RCALL_END_BITFIELDSIZE 32
#define OTP_OTP_CVAL_RCALL_END_BITMASK 0xFFFFFFFF
#define OTP_OTP_CVAL_RCALL_END_INIT    0x00000005
/*
 *  OTP_CVAL_RCALL_END bit field defines
 ****************************************************************************************
 */
#define OTP_CVAL_RCALL_END_OFFSETADDRESS        OTP_OTP_CVAL_RCALL_END_OFFSETADDRESS
#define OTP_CVAL_RCALL_END_BITOFFSET            0
#define OTP_CVAL_RCALL_END_BITFIELDSIZE         8
#define OTP_CVAL_RCALL_END_BITMASK              0x000000ff
#define OTP_CVAL_RCALL_END_INIT                 0x5

/*
 *  OTP_OTP_CVAL_TEST_END register defines
 ****************************************************************************************
 */
#define OTP_OTP_CVAL_TEST_END_OFFSETADDRESS 0x00000030  /* RW */
#define OTP_OTP_CVAL_TEST_END_BITOFFSET 0
#define OTP_OTP_CVAL_TEST_END_BITFIELDSIZE 32
#define OTP_OTP_CVAL_TEST_END_BITMASK  0xFFFFFFFF
#define OTP_OTP_CVAL_TEST_END_INIT     0x00000012
/*
 *  OTP_CVAL_TEST_END_NEWBITFIELD1 bit field defines
 ****************************************************************************************
 */
#define OTP_CVAL_TEST_END_NEWBITFIELD1_OFFSETADDRESS OTP_OTP_CVAL_TEST_END_OFFSETADDRESS
#define OTP_CVAL_TEST_END_NEWBITFIELD1_BITOFFSET  0
#define OTP_CVAL_TEST_END_NEWBITFIELD1_BITFIELDSIZE  8
#define OTP_CVAL_TEST_END_NEWBITFIELD1_BITMASK  0x000000ff
#define OTP_CVAL_TEST_END_NEWBITFIELD1_INIT     0x12

/*
 *  OTP_OTP_CVAL_TEST_WAIT register defines
 ****************************************************************************************
 */
#define OTP_OTP_CVAL_TEST_WAIT_OFFSETADDRESS 0x00000034  /* RW */
#define OTP_OTP_CVAL_TEST_WAIT_BITOFFSET 0
#define OTP_OTP_CVAL_TEST_WAIT_BITFIELDSIZE 32
#define OTP_OTP_CVAL_TEST_WAIT_BITMASK 0xFFFFFFFF
#define OTP_OTP_CVAL_TEST_WAIT_INIT    0x00000000
/*
 *  OTP_CVAL_TEST_WAIT_NEWBITFIELD1 bit field defines
 ****************************************************************************************
 */
#define OTP_CVAL_TEST_WAIT_NEWBITFIELD1_OFFSETADDRESS OTP_OTP_CVAL_TEST_WAIT_OFFSETADDRESS
#define OTP_CVAL_TEST_WAIT_NEWBITFIELD1_BITOFFSET  0
#define OTP_CVAL_TEST_WAIT_NEWBITFIELD1_BITFIELDSIZE  8
#define OTP_CVAL_TEST_WAIT_NEWBITFIELD1_BITMASK 0x000000ff
#define OTP_CVAL_TEST_WAIT_NEWBITFIELD1_INIT    0x0

/*
 *  OTP_OTP_SM_TEST_TEFAIL register defines
 ****************************************************************************************
 */
#define OTP_OTP_SM_TEST_TEFAIL_OFFSETADDRESS 0x00000038  /* RO */
#define OTP_OTP_SM_TEST_TEFAIL_BITOFFSET 0
#define OTP_OTP_SM_TEST_TEFAIL_BITFIELDSIZE 32
#define OTP_OTP_SM_TEST_TEFAIL_BITMASK 0xFFFFFFFF
#define OTP_OTP_SM_TEST_TEFAIL_INIT    0x00000000
/*
 *  OTP_TEST_TEFAIL bit field defines
 ****************************************************************************************
 */
#define OTP_TEST_TEFAIL_OFFSETADDRESS           OTP_OTP_SM_TEST_TEFAIL_OFFSETADDRESS
#define OTP_TEST_TEFAIL_BITOFFSET               0
#define OTP_TEST_TEFAIL_BITFIELDSIZE            1
#define OTP_TEST_TEFAIL_BITMASK                 0x00000001
#define OTP_TEST_TEFAIL_INIT                    0x0

/*
 *  OTP_OTP_SM_TEST_DIAG register defines
 ****************************************************************************************
 */
#define OTP_OTP_SM_TEST_DIAG_OFFSETADDRESS 0x0000003c  /* RW */
#define OTP_OTP_SM_TEST_DIAG_BITOFFSET 0
#define OTP_OTP_SM_TEST_DIAG_BITFIELDSIZE 32
#define OTP_OTP_SM_TEST_DIAG_BITMASK   0xFFFFFFFF
#define OTP_OTP_SM_TEST_DIAG_INIT      0x00000000
/*
 *  OTP_TEST_DIAG_REQ bit field defines
 ****************************************************************************************
 */
#define OTP_TEST_DIAG_REQ_OFFSETADDRESS         OTP_OTP_SM_TEST_DIAG_OFFSETADDRESS
#define OTP_TEST_DIAG_REQ_BITOFFSET             0
#define OTP_TEST_DIAG_REQ_BITFIELDSIZE          1
#define OTP_TEST_DIAG_REQ_BITMASK               0x00000001
#define OTP_TEST_DIAG_REQ_INIT                  0x0

/*
 *  OTP_OTP_SM_TEST_STORE register defines
 ****************************************************************************************
 */
#define OTP_OTP_SM_TEST_STORE_OFFSETADDRESS 0x00000040  /* RW */
#define OTP_OTP_SM_TEST_STORE_BITOFFSET 0
#define OTP_OTP_SM_TEST_STORE_BITFIELDSIZE 32
#define OTP_OTP_SM_TEST_STORE_BITMASK  0xFFFFFFFF
#define OTP_OTP_SM_TEST_STORE_INIT     0x00000000
/*
 *  OTP_TEST_STORE_REQ bit field defines
 ****************************************************************************************
 */
#define OTP_TEST_STORE_REQ_OFFSETADDRESS        OTP_OTP_SM_TEST_STORE_OFFSETADDRESS
#define OTP_TEST_STORE_REQ_BITOFFSET            0
#define OTP_TEST_STORE_REQ_BITFIELDSIZE         1
#define OTP_TEST_STORE_REQ_BITMASK              0x00000001
#define OTP_TEST_STORE_REQ_INIT                 0x0

/*
 *  OTP_OTP_TEST_TESTSEL register defines
 ****************************************************************************************
 */
#define OTP_OTP_TEST_TESTSEL_OFFSETADDRESS 0x00000044  /* RW */
#define OTP_OTP_TEST_TESTSEL_BITOFFSET 0
#define OTP_OTP_TEST_TESTSEL_BITFIELDSIZE 32
#define OTP_OTP_TEST_TESTSEL_BITMASK   0xFFFFFFFF
#define OTP_OTP_TEST_TESTSEL_INIT      0x00000000
/*
 *  OTP_TESTSEL bit field defines
 ****************************************************************************************
 */
#define OTP_TESTSEL_OFFSETADDRESS               OTP_OTP_TEST_TESTSEL_OFFSETADDRESS
#define OTP_TESTSEL_BITOFFSET                   0
#define OTP_TESTSEL_BITFIELDSIZE                2
#define OTP_TESTSEL_BITMASK                     0x00000003
#define OTP_TESTSEL_INIT                        0x0

/*
 *  OTP_OTP_SM_TEST_SDTA register defines
 ****************************************************************************************
 */
#define OTP_OTP_SM_TEST_SDTA_OFFSETADDRESS 0x00000048  /* RW */
#define OTP_OTP_SM_TEST_SDTA_BITOFFSET 0
#define OTP_OTP_SM_TEST_SDTA_BITFIELDSIZE 32
#define OTP_OTP_SM_TEST_SDTA_BITMASK   0xFFFFFFFF
#define OTP_OTP_SM_TEST_SDTA_INIT      0x00000000
/*
 *  OTP_TEST_SDTA bit field defines
 ****************************************************************************************
 */
#define OTP_TEST_SDTA_OFFSETADDRESS             OTP_OTP_SM_TEST_SDTA_OFFSETADDRESS
#define OTP_TEST_SDTA_BITOFFSET                 0
#define OTP_TEST_SDTA_BITFIELDSIZE              6
#define OTP_TEST_SDTA_BITMASK                   0x0000003f
#define OTP_TEST_SDTA_INIT                      0x0

/*
 *  OTP_OTP_SM_TEST_SDTO_0 register defines
 ****************************************************************************************
 */
#define OTP_OTP_SM_TEST_SDTO_0_OFFSETADDRESS 0x0000004c  /* RO */
#define OTP_OTP_SM_TEST_SDTO_0_BITOFFSET 0
#define OTP_OTP_SM_TEST_SDTO_0_BITFIELDSIZE 32
#define OTP_OTP_SM_TEST_SDTO_0_BITMASK 0xFFFFFFFF
#define OTP_OTP_SM_TEST_SDTO_0_INIT    0x00000000
/*
 *  OTP_SDTO0_BUFFER bit field defines
 ****************************************************************************************
 */
#define OTP_SDTO0_BUFFER_OFFSETADDRESS          OTP_OTP_SM_TEST_SDTO_0_OFFSETADDRESS
#define OTP_SDTO0_BUFFER_BITOFFSET              0
#define OTP_SDTO0_BUFFER_BITFIELDSIZE           5
#define OTP_SDTO0_BUFFER_BITMASK                0x0000001f
#define OTP_SDTO0_BUFFER_INIT                   0x0

/*
 *  OTP_OTP_SM_TEST_SDTO_1 register defines
 ****************************************************************************************
 */
#define OTP_OTP_SM_TEST_SDTO_1_OFFSETADDRESS 0x00000050  /* RO */
#define OTP_OTP_SM_TEST_SDTO_1_BITOFFSET 0
#define OTP_OTP_SM_TEST_SDTO_1_BITFIELDSIZE 32
#define OTP_OTP_SM_TEST_SDTO_1_BITMASK 0xFFFFFFFF
#define OTP_OTP_SM_TEST_SDTO_1_INIT    0x00000000
/*
 *  OTP_SDTO1_BUFFER bit field defines
 ****************************************************************************************
 */
#define OTP_SDTO1_BUFFER_OFFSETADDRESS          OTP_OTP_SM_TEST_SDTO_1_OFFSETADDRESS
#define OTP_SDTO1_BUFFER_BITOFFSET              0
#define OTP_SDTO1_BUFFER_BITFIELDSIZE           5
#define OTP_SDTO1_BUFFER_BITMASK                0x0000001f
#define OTP_SDTO1_BUFFER_INIT                   0x0

/*
 *  OTP_OTP_SIG_VWL register defines
 ****************************************************************************************
 */
#define OTP_OTP_SIG_VWL_OFFSETADDRESS  0x00000054  /* RW */
#define OTP_OTP_SIG_VWL_BITOFFSET      0
#define OTP_OTP_SIG_VWL_BITFIELDSIZE   32
#define OTP_OTP_SIG_VWL_BITMASK        0xFFFFFFFF
#define OTP_OTP_SIG_VWL_INIT           0x00000000
/*
 *  OTP_VWLIN bit field defines
 ****************************************************************************************
 */
#define OTP_VWLIN_OFFSETADDRESS                 OTP_OTP_SIG_VWL_OFFSETADDRESS
#define OTP_VWLIN_BITOFFSET                     2
#define OTP_VWLIN_BITFIELDSIZE                  1
#define OTP_VWLIN_BITMASK                       0x00000004
#define OTP_VWLIN_INIT                          0x0
/*
 *  OTP_VWLSEL bit field defines
 ****************************************************************************************
 */
#define OTP_VWLSEL_OFFSETADDRESS                OTP_OTP_SIG_VWL_OFFSETADDRESS
#define OTP_VWLSEL_BITOFFSET                    0
#define OTP_VWLSEL_BITFIELDSIZE                 2
#define OTP_VWLSEL_BITMASK                      0x00000003
#define OTP_VWLSEL_INIT                         0x0

/*
 *  OTP_OTP_SIG_CTL register defines
 ****************************************************************************************
 */
#define OTP_OTP_SIG_CTL_OFFSETADDRESS  0x00000058  /* RW */
#define OTP_OTP_SIG_CTL_BITOFFSET      0
#define OTP_OTP_SIG_CTL_BITFIELDSIZE   32
#define OTP_OTP_SIG_CTL_BITMASK        0xFFFFFFFF
#define OTP_OTP_SIG_CTL_INIT           0x00000000
/*
 *  OTP_SIG_CTL bit field defines
 ****************************************************************************************
 */
#define OTP_SIG_CTL_OFFSETADDRESS               OTP_OTP_SIG_CTL_OFFSETADDRESS
#define OTP_SIG_CTL_BITOFFSET                   0
#define OTP_SIG_CTL_BITFIELDSIZE               10
#define OTP_SIG_CTL_BITMASK                     0x000003ff
#define OTP_SIG_CTL_INIT                        0x0

/*
 *  OTP_OTP_SIG_VAL register defines
 ****************************************************************************************
 */
#define OTP_OTP_SIG_VAL_OFFSETADDRESS  0x0000005c  /* RW */
#define OTP_OTP_SIG_VAL_BITOFFSET      0
#define OTP_OTP_SIG_VAL_BITFIELDSIZE   32
#define OTP_OTP_SIG_VAL_BITMASK        0xFFFFFFFF
#define OTP_OTP_SIG_VAL_INIT           0x0000007f
/*
 *  OTP_SIG_VAL bit field defines
 ****************************************************************************************
 */
#define OTP_SIG_VAL_OFFSETADDRESS               OTP_OTP_SIG_VAL_OFFSETADDRESS
#define OTP_SIG_VAL_BITOFFSET                   0
#define OTP_SIG_VAL_BITFIELDSIZE                7
#define OTP_SIG_VAL_BITMASK                     0x0000007f
#define OTP_SIG_VAL_INIT                        0x7f

/*
 *  OTP_OTP_SIG_SDTO_0 register defines
 ****************************************************************************************
 */
#define OTP_OTP_SIG_SDTO_0_OFFSETADDRESS 0x00000060  /* RO */
#define OTP_OTP_SIG_SDTO_0_BITOFFSET   0
#define OTP_OTP_SIG_SDTO_0_BITFIELDSIZE 32
#define OTP_OTP_SIG_SDTO_0_BITMASK     0xFFFFFFFF
#define OTP_OTP_SIG_SDTO_0_INIT        0x00000000
/*
 *  OTP_OTP_SDTO0 bit field defines
 ****************************************************************************************
 */
#define OTP_OTP_SDTO0_OFFSETADDRESS             OTP_OTP_SIG_SDTO_0_OFFSETADDRESS
#define OTP_OTP_SDTO0_BITOFFSET                 0
#define OTP_OTP_SDTO0_BITFIELDSIZE              5
#define OTP_OTP_SDTO0_BITMASK                   0x0000001f
#define OTP_OTP_SDTO0_INIT                      0x0

/*
 *  OTP_OTP_SIG_SDTO_1 register defines
 ****************************************************************************************
 */
#define OTP_OTP_SIG_SDTO_1_OFFSETADDRESS 0x00000064  /* RO */
#define OTP_OTP_SIG_SDTO_1_BITOFFSET   0
#define OTP_OTP_SIG_SDTO_1_BITFIELDSIZE 32
#define OTP_OTP_SIG_SDTO_1_BITMASK     0xFFFFFFFF
#define OTP_OTP_SIG_SDTO_1_INIT        0x00000000
/*
 *  OTP_OTP_SDTO1 bit field defines
 ****************************************************************************************
 */
#define OTP_OTP_SDTO1_OFFSETADDRESS             OTP_OTP_SIG_SDTO_1_OFFSETADDRESS
#define OTP_OTP_SDTO1_BITOFFSET                 0
#define OTP_OTP_SDTO1_BITFIELDSIZE              5
#define OTP_OTP_SDTO1_BITMASK                   0x0000001f
#define OTP_OTP_SDTO1_INIT                      0x0

/*
 *  OTP_OTP_SIG_DOUT_LSB register defines
 ****************************************************************************************
 */
#define OTP_OTP_SIG_DOUT_LSB_OFFSETADDRESS 0x00000068  /* RO */
#define OTP_OTP_SIG_DOUT_LSB_BITOFFSET 0
#define OTP_OTP_SIG_DOUT_LSB_BITFIELDSIZE 32
#define OTP_OTP_SIG_DOUT_LSB_BITMASK   0xFFFFFFFF
#define OTP_OTP_SIG_DOUT_LSB_INIT      0x00000000
/*
 *  OTP_OTP_DOUT_31_0 bit field defines
 ****************************************************************************************
 */
#define OTP_OTP_DOUT_31_0_OFFSETADDRESS         OTP_OTP_SIG_DOUT_LSB_OFFSETADDRESS
#define OTP_OTP_DOUT_31_0_BITOFFSET             0
#define OTP_OTP_DOUT_31_0_BITFIELDSIZE         32
#define OTP_OTP_DOUT_31_0_BITMASK               0xffffffff
#define OTP_OTP_DOUT_31_0_INIT                  0x0

/*
 *  OTP_OTP_SIG_DOUT_MSB register defines
 ****************************************************************************************
 */
#define OTP_OTP_SIG_DOUT_MSB_OFFSETADDRESS 0x0000006c  /* RO */
#define OTP_OTP_SIG_DOUT_MSB_BITOFFSET 0
#define OTP_OTP_SIG_DOUT_MSB_BITFIELDSIZE 32
#define OTP_OTP_SIG_DOUT_MSB_BITMASK   0xFFFFFFFF
#define OTP_OTP_SIG_DOUT_MSB_INIT      0x00000000
/*
 *  OTP_OTP_DOUT_63_32 bit field defines
 ****************************************************************************************
 */
#define OTP_OTP_DOUT_63_32_OFFSETADDRESS        OTP_OTP_SIG_DOUT_MSB_OFFSETADDRESS
#define OTP_OTP_DOUT_63_32_BITOFFSET            0
#define OTP_OTP_DOUT_63_32_BITFIELDSIZE        32
#define OTP_OTP_DOUT_63_32_BITMASK              0xffffffff
#define OTP_OTP_DOUT_63_32_INIT                 0x0

/*
 *  OTP_OTP_SIG_TEFAIL register defines
 ****************************************************************************************
 */
#define OTP_OTP_SIG_TEFAIL_OFFSETADDRESS 0x00000070  /* RO */
#define OTP_OTP_SIG_TEFAIL_BITOFFSET   0
#define OTP_OTP_SIG_TEFAIL_BITFIELDSIZE 32
#define OTP_OTP_SIG_TEFAIL_BITMASK     0xFFFFFFFF
#define OTP_OTP_SIG_TEFAIL_INIT        0x00000000
/*
 *  OTP_OTP_TEFAIL bit field defines
 ****************************************************************************************
 */
#define OTP_OTP_TEFAIL_OFFSETADDRESS            OTP_OTP_SIG_TEFAIL_OFFSETADDRESS
#define OTP_OTP_TEFAIL_BITOFFSET                0
#define OTP_OTP_TEFAIL_BITFIELDSIZE             1
#define OTP_OTP_TEFAIL_BITMASK                  0x00000001
#define OTP_OTP_TEFAIL_INIT                     0x0

/*
 *  OTP_OTP_IRQ_STATUS register defines
 ****************************************************************************************
 */
#define OTP_OTP_IRQ_STATUS_OFFSETADDRESS 0x00000080  /* R0 */
#define OTP_OTP_IRQ_STATUS_BITOFFSET   0
#define OTP_OTP_IRQ_STATUS_BITFIELDSIZE 32
#define OTP_OTP_IRQ_STATUS_BITMASK     0xFFFFFFFF
#define OTP_OTP_IRQ_STATUS_INIT        0x00000000
/*
 *  OTP_IRQ_STATUS_TEST_STORE_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_STATUS_TEST_STORE_ACK_OFFSETADDRESS OTP_OTP_IRQ_STATUS_OFFSETADDRESS
#define OTP_IRQ_STATUS_TEST_STORE_ACK_BITOFFSET  5
#define OTP_IRQ_STATUS_TEST_STORE_ACK_BITFIELDSIZE  1
#define OTP_IRQ_STATUS_TEST_STORE_ACK_BITMASK   0x00000020
#define OTP_IRQ_STATUS_TEST_STORE_ACK_INIT      0x0
/*
 *  OTP_IRQ_STATUS_TEST_DIAG_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_STATUS_TEST_DIAG_ACK_OFFSETADDRESS OTP_OTP_IRQ_STATUS_OFFSETADDRESS
#define OTP_IRQ_STATUS_TEST_DIAG_ACK_BITOFFSET  4
#define OTP_IRQ_STATUS_TEST_DIAG_ACK_BITFIELDSIZE  1
#define OTP_IRQ_STATUS_TEST_DIAG_ACK_BITMASK    0x00000010
#define OTP_IRQ_STATUS_TEST_DIAG_ACK_INIT       0x0
/*
 *  OTP_IRQ_STATUS_PAGE_RD_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_STATUS_PAGE_RD_ACK_OFFSETADDRESS OTP_OTP_IRQ_STATUS_OFFSETADDRESS
#define OTP_IRQ_STATUS_PAGE_RD_ACK_BITOFFSET    3
#define OTP_IRQ_STATUS_PAGE_RD_ACK_BITFIELDSIZE  1
#define OTP_IRQ_STATUS_PAGE_RD_ACK_BITMASK      0x00000008
#define OTP_IRQ_STATUS_PAGE_RD_ACK_INIT         0x0
/*
 *  OTP_IRQ_STATUS_PAGE_WR_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_STATUS_PAGE_WR_ACK_OFFSETADDRESS OTP_OTP_IRQ_STATUS_OFFSETADDRESS
#define OTP_IRQ_STATUS_PAGE_WR_ACK_BITOFFSET    2
#define OTP_IRQ_STATUS_PAGE_WR_ACK_BITFIELDSIZE  1
#define OTP_IRQ_STATUS_PAGE_WR_ACK_BITMASK      0x00000004
#define OTP_IRQ_STATUS_PAGE_WR_ACK_INIT         0x0
/*
 *  OTP_IRQ_STATUS_NV_STORE_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_STATUS_NV_STORE_ACK_OFFSETADDRESS OTP_OTP_IRQ_STATUS_OFFSETADDRESS
#define OTP_IRQ_STATUS_NV_STORE_ACK_BITOFFSET   1
#define OTP_IRQ_STATUS_NV_STORE_ACK_BITFIELDSIZE  1
#define OTP_IRQ_STATUS_NV_STORE_ACK_BITMASK     0x00000002
#define OTP_IRQ_STATUS_NV_STORE_ACK_INIT        0x0
/*
 *  OTP_IRQ_STATUS_NV_RCALL_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_STATUS_NV_RCALL_ACK_OFFSETADDRESS OTP_OTP_IRQ_STATUS_OFFSETADDRESS
#define OTP_IRQ_STATUS_NV_RCALL_ACK_BITOFFSET   0
#define OTP_IRQ_STATUS_NV_RCALL_ACK_BITFIELDSIZE  1
#define OTP_IRQ_STATUS_NV_RCALL_ACK_BITMASK     0x00000001
#define OTP_IRQ_STATUS_NV_RCALL_ACK_INIT        0x0

/*
 *  OTP_OTP_IRQ_MASK register defines
 ****************************************************************************************
 */
#define OTP_OTP_IRQ_MASK_OFFSETADDRESS 0x00000084  /* RW */
#define OTP_OTP_IRQ_MASK_BITOFFSET     0
#define OTP_OTP_IRQ_MASK_BITFIELDSIZE  32
#define OTP_OTP_IRQ_MASK_BITMASK       0xFFFFFFFF
#define OTP_OTP_IRQ_MASK_INIT          0x00000000
/*
 *  OTP_IRQ_MASK_TEST_STORE_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_MASK_TEST_STORE_ACK_OFFSETADDRESS OTP_OTP_IRQ_MASK_OFFSETADDRESS
#define OTP_IRQ_MASK_TEST_STORE_ACK_BITOFFSET   5
#define OTP_IRQ_MASK_TEST_STORE_ACK_BITFIELDSIZE  1
#define OTP_IRQ_MASK_TEST_STORE_ACK_BITMASK     0x00000020
#define OTP_IRQ_MASK_TEST_STORE_ACK_INIT        0x0
/*
 *  OTP_IRQ_MASK_TEST_DIAG_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_MASK_TEST_DIAG_ACK_OFFSETADDRESS OTP_OTP_IRQ_MASK_OFFSETADDRESS
#define OTP_IRQ_MASK_TEST_DIAG_ACK_BITOFFSET    4
#define OTP_IRQ_MASK_TEST_DIAG_ACK_BITFIELDSIZE  1
#define OTP_IRQ_MASK_TEST_DIAG_ACK_BITMASK      0x00000010
#define OTP_IRQ_MASK_TEST_DIAG_ACK_INIT         0x0
/*
 *  OTP_IRQ_MASK_PAGE_RD_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_MASK_PAGE_RD_ACK_OFFSETADDRESS  OTP_OTP_IRQ_MASK_OFFSETADDRESS
#define OTP_IRQ_MASK_PAGE_RD_ACK_BITOFFSET      3
#define OTP_IRQ_MASK_PAGE_RD_ACK_BITFIELDSIZE   1
#define OTP_IRQ_MASK_PAGE_RD_ACK_BITMASK        0x00000008
#define OTP_IRQ_MASK_PAGE_RD_ACK_INIT           0x0
/*
 *  OTP_IRQ_MASK_PAGE_WR_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_MASK_PAGE_WR_ACK_OFFSETADDRESS  OTP_OTP_IRQ_MASK_OFFSETADDRESS
#define OTP_IRQ_MASK_PAGE_WR_ACK_BITOFFSET      2
#define OTP_IRQ_MASK_PAGE_WR_ACK_BITFIELDSIZE   1
#define OTP_IRQ_MASK_PAGE_WR_ACK_BITMASK        0x00000004
#define OTP_IRQ_MASK_PAGE_WR_ACK_INIT           0x0
/*
 *  OTP_IRQ_MASK_NV_STORE_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_MASK_NV_STORE_ACK_OFFSETADDRESS OTP_OTP_IRQ_MASK_OFFSETADDRESS
#define OTP_IRQ_MASK_NV_STORE_ACK_BITOFFSET     1
#define OTP_IRQ_MASK_NV_STORE_ACK_BITFIELDSIZE  1
#define OTP_IRQ_MASK_NV_STORE_ACK_BITMASK       0x00000002
#define OTP_IRQ_MASK_NV_STORE_ACK_INIT          0x0
/*
 *  OTP_IRQ_MASK_NV_RCALL_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_MASK_NV_RCALL_ACK_OFFSETADDRESS OTP_OTP_IRQ_MASK_OFFSETADDRESS
#define OTP_IRQ_MASK_NV_RCALL_ACK_BITOFFSET     0
#define OTP_IRQ_MASK_NV_RCALL_ACK_BITFIELDSIZE  1
#define OTP_IRQ_MASK_NV_RCALL_ACK_BITMASK       0x00000001
#define OTP_IRQ_MASK_NV_RCALL_ACK_INIT          0x0

/*
 *  OTP_OTP_IRQ_CLEAR register defines
 ****************************************************************************************
 */
#define OTP_OTP_IRQ_CLEAR_OFFSETADDRESS 0x00000088  /* RW */
#define OTP_OTP_IRQ_CLEAR_BITOFFSET    0
#define OTP_OTP_IRQ_CLEAR_BITFIELDSIZE 32
#define OTP_OTP_IRQ_CLEAR_BITMASK      0xFFFFFFFF
#define OTP_OTP_IRQ_CLEAR_INIT         0x00000000
/*
 *  OTP_IRQ_CLEAR_TEST_STORE_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_CLEAR_TEST_STORE_ACK_OFFSETADDRESS OTP_OTP_IRQ_CLEAR_OFFSETADDRESS
#define OTP_IRQ_CLEAR_TEST_STORE_ACK_BITOFFSET  5
#define OTP_IRQ_CLEAR_TEST_STORE_ACK_BITFIELDSIZE  1
#define OTP_IRQ_CLEAR_TEST_STORE_ACK_BITMASK    0x00000020
#define OTP_IRQ_CLEAR_TEST_STORE_ACK_INIT       0x0
/*
 *  OTP_IRQ_CLEAR_TEST_DIAG_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_CLEAR_TEST_DIAG_ACK_OFFSETADDRESS OTP_OTP_IRQ_CLEAR_OFFSETADDRESS
#define OTP_IRQ_CLEAR_TEST_DIAG_ACK_BITOFFSET   4
#define OTP_IRQ_CLEAR_TEST_DIAG_ACK_BITFIELDSIZE  1
#define OTP_IRQ_CLEAR_TEST_DIAG_ACK_BITMASK     0x00000010
#define OTP_IRQ_CLEAR_TEST_DIAG_ACK_INIT        0x0
/*
 *  OTP_IRQ_CLEAR_PAGE_RD_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_CLEAR_PAGE_RD_ACK_OFFSETADDRESS OTP_OTP_IRQ_CLEAR_OFFSETADDRESS
#define OTP_IRQ_CLEAR_PAGE_RD_ACK_BITOFFSET     3
#define OTP_IRQ_CLEAR_PAGE_RD_ACK_BITFIELDSIZE  1
#define OTP_IRQ_CLEAR_PAGE_RD_ACK_BITMASK       0x00000008
#define OTP_IRQ_CLEAR_PAGE_RD_ACK_INIT          0x0
/*
 *  OTP_IRQ_CLEAR_PAGE_WR_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_CLEAR_PAGE_WR_ACK_OFFSETADDRESS OTP_OTP_IRQ_CLEAR_OFFSETADDRESS
#define OTP_IRQ_CLEAR_PAGE_WR_ACK_BITOFFSET     2
#define OTP_IRQ_CLEAR_PAGE_WR_ACK_BITFIELDSIZE  1
#define OTP_IRQ_CLEAR_PAGE_WR_ACK_BITMASK       0x00000004
#define OTP_IRQ_CLEAR_PAGE_WR_ACK_INIT          0x0
/*
 *  OTP_IRQ_CLEAR_NV_STORE_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_CLEAR_NV_STORE_ACK_OFFSETADDRESS OTP_OTP_IRQ_CLEAR_OFFSETADDRESS
#define OTP_IRQ_CLEAR_NV_STORE_ACK_BITOFFSET    1
#define OTP_IRQ_CLEAR_NV_STORE_ACK_BITFIELDSIZE  1
#define OTP_IRQ_CLEAR_NV_STORE_ACK_BITMASK      0x00000002
#define OTP_IRQ_CLEAR_NV_STORE_ACK_INIT         0x0
/*
 *  OTP_IRQ_CLEAR_NV_RCALL_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_CLEAR_NV_RCALL_ACK_OFFSETADDRESS OTP_OTP_IRQ_CLEAR_OFFSETADDRESS
#define OTP_IRQ_CLEAR_NV_RCALL_ACK_BITOFFSET    0
#define OTP_IRQ_CLEAR_NV_RCALL_ACK_BITFIELDSIZE  1
#define OTP_IRQ_CLEAR_NV_RCALL_ACK_BITMASK      0x00000001
#define OTP_IRQ_CLEAR_NV_RCALL_ACK_INIT         0x0

/*
 *  OTP_OTP_IRQ_SET register defines
 ****************************************************************************************
 */
#define OTP_OTP_IRQ_SET_OFFSETADDRESS  0x0000008c  /* RW */
#define OTP_OTP_IRQ_SET_BITOFFSET      0
#define OTP_OTP_IRQ_SET_BITFIELDSIZE   32
#define OTP_OTP_IRQ_SET_BITMASK        0xFFFFFFFF
#define OTP_OTP_IRQ_SET_INIT           0x00000000
/*
 *  OTP_IRQ_SET_TEST_STORE_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_SET_TEST_STORE_ACK_OFFSETADDRESS OTP_OTP_IRQ_SET_OFFSETADDRESS
#define OTP_IRQ_SET_TEST_STORE_ACK_BITOFFSET    5
#define OTP_IRQ_SET_TEST_STORE_ACK_BITFIELDSIZE  1
#define OTP_IRQ_SET_TEST_STORE_ACK_BITMASK      0x00000020
#define OTP_IRQ_SET_TEST_STORE_ACK_INIT         0x0
/*
 *  OTP_IRQ_SET_TEST_DIAG_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_SET_TEST_DIAG_ACK_OFFSETADDRESS OTP_OTP_IRQ_SET_OFFSETADDRESS
#define OTP_IRQ_SET_TEST_DIAG_ACK_BITOFFSET     4
#define OTP_IRQ_SET_TEST_DIAG_ACK_BITFIELDSIZE  1
#define OTP_IRQ_SET_TEST_DIAG_ACK_BITMASK       0x00000010
#define OTP_IRQ_SET_TEST_DIAG_ACK_INIT          0x0
/*
 *  OTP_IRQ_SET_PAGE_RD_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_SET_PAGE_RD_ACK_OFFSETADDRESS   OTP_OTP_IRQ_SET_OFFSETADDRESS
#define OTP_IRQ_SET_PAGE_RD_ACK_BITOFFSET       3
#define OTP_IRQ_SET_PAGE_RD_ACK_BITFIELDSIZE    1
#define OTP_IRQ_SET_PAGE_RD_ACK_BITMASK         0x00000008
#define OTP_IRQ_SET_PAGE_RD_ACK_INIT            0x0
/*
 *  OTP_IRQ_SET_PAGE_WR_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_SET_PAGE_WR_ACK_OFFSETADDRESS   OTP_OTP_IRQ_SET_OFFSETADDRESS
#define OTP_IRQ_SET_PAGE_WR_ACK_BITOFFSET       2
#define OTP_IRQ_SET_PAGE_WR_ACK_BITFIELDSIZE    1
#define OTP_IRQ_SET_PAGE_WR_ACK_BITMASK         0x00000004
#define OTP_IRQ_SET_PAGE_WR_ACK_INIT            0x0
/*
 *  OTP_IRQ_SET_NV_STORE_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_SET_NV_STORE_ACK_OFFSETADDRESS  OTP_OTP_IRQ_SET_OFFSETADDRESS
#define OTP_IRQ_SET_NV_STORE_ACK_BITOFFSET      1
#define OTP_IRQ_SET_NV_STORE_ACK_BITFIELDSIZE   1
#define OTP_IRQ_SET_NV_STORE_ACK_BITMASK        0x00000002
#define OTP_IRQ_SET_NV_STORE_ACK_INIT           0x0
/*
 *  OTP_IRQ_SET_NV_RCALL_ACK bit field defines
 ****************************************************************************************
 */
#define OTP_IRQ_SET_NV_RCALL_ACK_OFFSETADDRESS  OTP_OTP_IRQ_SET_OFFSETADDRESS
#define OTP_IRQ_SET_NV_RCALL_ACK_BITOFFSET      0
#define OTP_IRQ_SET_NV_RCALL_ACK_BITFIELDSIZE   1
#define OTP_IRQ_SET_NV_RCALL_ACK_BITMASK        0x00000001
#define OTP_IRQ_SET_NV_RCALL_ACK_INIT           0x0
#endif
