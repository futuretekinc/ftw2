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
* $RCSfile: gsn_reg_mb_spec.h,v $
*
* Description : This file contains mailbox register specification.
******************************************************************************/

#ifndef _REG_MB_H
#define _REG_MB_H

/***************************************************
 *
 *             MB
 *
 ***************************************************/


/*
 *  MAILBOX instance offsets
 ****************************************************************************************
 */
#define MAILBOX 0x40050000

/*
 *  MB_MB_RB_STATUS register defines
 ****************************************************************************************
 */
#define MB_MB_RB_STATUS_OFFSETADDRESS 0x00000000  /* R */
#define MB_MB_RB_STATUS_BITOFFSET  0
#define MB_MB_RB_STATUS_BITFIELDSIZE 32
#define MB_MB_RB_STATUS_BITMASK    0xFFFFFFFF
#define MB_MB_RB_STATUS_INIT       0x00000000
/*
 *  MB_RB_INT bit field defines
 ****************************************************************************************
 */
#define MB_RB_INT_OFFSETADDRESS             MB_MB_RB_STATUS_OFFSETADDRESS
#define MB_RB_INT_BITOFFSET                 0
#define MB_RB_INT_BITFIELDSIZE              4
#define MB_RB_INT_BITMASK                   0x0000000f
#define MB_RB_INT_INIT                      0x0

/*
 *  MB_MB_RB_MASK register defines
 ****************************************************************************************
 */
#define MB_MB_RB_MASK_OFFSETADDRESS 0x00000004  /* RW */
#define MB_MB_RB_MASK_BITOFFSET    0
#define MB_MB_RB_MASK_BITFIELDSIZE 32
#define MB_MB_RB_MASK_BITMASK      0xFFFFFFFF
#define MB_MB_RB_MASK_INIT         0x00000000
/*
 *  MB_RB_MASK bit field defines
 ****************************************************************************************
 */
#define MB_RB_MASK_OFFSETADDRESS            MB_MB_RB_MASK_OFFSETADDRESS
#define MB_RB_MASK_BITOFFSET                0
#define MB_RB_MASK_BITFIELDSIZE             4
#define MB_RB_MASK_BITMASK                  0x0000000f
#define MB_RB_MASK_INIT                     0x0

/*
 *  MB_MB_RB_CLEAR register defines
 ****************************************************************************************
 */
#define MB_MB_RB_CLEAR_OFFSETADDRESS 0x00000008  /* RW */
#define MB_MB_RB_CLEAR_BITOFFSET   0
#define MB_MB_RB_CLEAR_BITFIELDSIZE 32
#define MB_MB_RB_CLEAR_BITMASK     0xFFFFFFFF
#define MB_MB_RB_CLEAR_INIT        0x00000000
/*
 *  MB_RB_CLEAR bit field defines
 ****************************************************************************************
 */
#define MB_RB_CLEAR_OFFSETADDRESS           MB_MB_RB_CLEAR_OFFSETADDRESS
#define MB_RB_CLEAR_BITOFFSET               0
#define MB_RB_CLEAR_BITFIELDSIZE            4
#define MB_RB_CLEAR_BITMASK                 0x0000000f
#define MB_RB_CLEAR_INIT                    0x0

/*
 *  MB_MB_RB_SET register defines
 ****************************************************************************************
 */
#define MB_MB_RB_SET_OFFSETADDRESS 0x0000000c  /* RW */
#define MB_MB_RB_SET_BITOFFSET     0
#define MB_MB_RB_SET_BITFIELDSIZE  32
#define MB_MB_RB_SET_BITMASK       0xFFFFFFFF
#define MB_MB_RB_SET_INIT          0x00000000
/*
 *  MB_RB_SET bit field defines
 ****************************************************************************************
 */
#define MB_RB_SET_OFFSETADDRESS             MB_MB_RB_SET_OFFSETADDRESS
#define MB_RB_SET_BITOFFSET                 0
#define MB_RB_SET_BITFIELDSIZE              4
#define MB_RB_SET_BITMASK                   0x0000000f
#define MB_RB_SET_INIT                      0x0

/*
 *  MB_MB_SB_CONF register defines
 ****************************************************************************************
 */
#define MB_MB_SB_CONF_OFFSETADDRESS 0x00000040  /* RW */
#define MB_MB_SB_CONF_BITOFFSET    0
#define MB_MB_SB_CONF_BITFIELDSIZE 32
#define MB_MB_SB_CONF_BITMASK      0xFFFFFFFF
#define MB_MB_SB_CONF_INIT         0x00000000
/*
 *  MB_SB_CONF bit field defines
 ****************************************************************************************
 */
#define MB_SB_CONF_OFFSETADDRESS            MB_MB_SB_CONF_OFFSETADDRESS
#define MB_SB_CONF_BITOFFSET                0
#define MB_SB_CONF_BITFIELDSIZE             4
#define MB_SB_CONF_BITMASK                  0x0000000f
#define MB_SB_CONF_INIT                     0x0

/*
 *  MB_MB_SB_INT register defines
 ****************************************************************************************
 */
#define MB_MB_SB_INT_OFFSETADDRESS 0x00000044  /* RW */
#define MB_MB_SB_INT_BITOFFSET     0
#define MB_MB_SB_INT_BITFIELDSIZE  32
#define MB_MB_SB_INT_BITMASK       0xFFFFFFFF
#define MB_MB_SB_INT_INIT          0x00000000
/*
 *  MB_SB_INT bit field defines
 ****************************************************************************************
 */
#define MB_SB_INT_OFFSETADDRESS             MB_MB_SB_INT_OFFSETADDRESS
#define MB_SB_INT_BITOFFSET                 0
#define MB_SB_INT_BITFIELDSIZE              4
#define MB_SB_INT_BITMASK                   0x0000000f
#define MB_SB_INT_INIT                      0x0

/*
 *  MB_MB_SB_0 register defines
 ****************************************************************************************
 */
#define MB_MB_SB_0_OFFSETADDRESS   0x00000080  /* W */
#define MB_MB_SB_0_BITOFFSET       0
#define MB_MB_SB_0_BITFIELDSIZE    32
#define MB_MB_SB_0_BITMASK         0xFFFFFFFF
#define MB_MB_SB_0_INIT            0x00000000
/*
 *  MB_SB_0 bit field defines
 ****************************************************************************************
 */
#define MB_SB_0_OFFSETADDRESS               MB_MB_SB_0_OFFSETADDRESS
#define MB_SB_0_BITOFFSET                   0
#define MB_SB_0_BITFIELDSIZE               32
#define MB_SB_0_BITMASK                     0xffffffff
#define MB_SB_0_INIT                        0x0

/*
 *  MB_MB_SB_1 register defines
 ****************************************************************************************
 */
#define MB_MB_SB_1_OFFSETADDRESS   0x00000084  /* W */
#define MB_MB_SB_1_BITOFFSET       0
#define MB_MB_SB_1_BITFIELDSIZE    32
#define MB_MB_SB_1_BITMASK         0xFFFFFFFF
#define MB_MB_SB_1_INIT            0x00000000
/*
 *  MB_SB_1 bit field defines
 ****************************************************************************************
 */
#define MB_SB_1_OFFSETADDRESS               MB_MB_SB_1_OFFSETADDRESS
#define MB_SB_1_BITOFFSET                   0
#define MB_SB_1_BITFIELDSIZE               32
#define MB_SB_1_BITMASK                     0xffffffff
#define MB_SB_1_INIT                        0x0

/*
 *  MB_MB_RB_0 register defines
 ****************************************************************************************
 */
#define MB_MB_RB_0_OFFSETADDRESS   0x00000100  /* R */
#define MB_MB_RB_0_BITOFFSET       0
#define MB_MB_RB_0_BITFIELDSIZE    32
#define MB_MB_RB_0_BITMASK         0xFFFFFFFF
#define MB_MB_RB_0_INIT            0x00000000
/*
 *  MB_RB_0 bit field defines
 ****************************************************************************************
 */
#define MB_RB_0_OFFSETADDRESS               MB_MB_RB_0_OFFSETADDRESS
#define MB_RB_0_BITOFFSET                   0
#define MB_RB_0_BITFIELDSIZE               32
#define MB_RB_0_BITMASK                     0xffffffff
#define MB_RB_0_INIT                        0x0

/*
 *  MB_MB_RB_1 register defines
 ****************************************************************************************
 */
#define MB_MB_RB_1_OFFSETADDRESS   0x00000104  /* R */
#define MB_MB_RB_1_BITOFFSET       0
#define MB_MB_RB_1_BITFIELDSIZE    32
#define MB_MB_RB_1_BITMASK         0xFFFFFFFF
#define MB_MB_RB_1_INIT            0x00000000
/*
 *  MB_RB_1 bit field defines
 ****************************************************************************************
 */
#define MB_RB_1_OFFSETADDRESS               MB_MB_RB_1_OFFSETADDRESS
#define MB_RB_1_BITOFFSET                   0
#define MB_RB_1_BITFIELDSIZE               32
#define MB_RB_1_BITMASK                     0xffffffff
#define MB_RB_1_INIT                        0x0
#endif
