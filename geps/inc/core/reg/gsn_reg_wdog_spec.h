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
* $RCSfile: gsn_reg_wdog_spec.h,v $
*
* Description : This file contains watch dog register specifications.
*****************************************************************************/


#ifndef _REG_WDOG_H
#define _REG_WDOG_H

/***************************************************
 *
 *             WDOG
 *
 ***************************************************/


/*
 *  WDOG instance offsets
 ****************************************************************************************
 */
#define WDOG 0x40110000

/*
 *  WDOG_LOAD register defines
 ****************************************************************************************
 */
#define WDOG_LOAD_OFFSETADDRESS        0x00000000  /* RW */
#define WDOG_LOAD_BITOFFSET            0
#define WDOG_LOAD_BITFIELDSIZE         32
#define WDOG_LOAD_BITMASK              0xFFFFFFFF
#define WDOG_LOAD_INIT                 0x00000000
/*
 *  WDOG_LOAD_VAL bit field defines
 ****************************************************************************************
 */
#define WDOG_LOAD_VAL_OFFSETADDRESS             WDOG_LOAD_OFFSETADDRESS
#define WDOG_LOAD_VAL_BITOFFSET                 0
#define WDOG_LOAD_VAL_BITFIELDSIZE             32
#define WDOG_LOAD_VAL_BITMASK                   0xffffffff
#define WDOG_LOAD_VAL_INIT                      0x0

/*
 *  WDOG_COUNTER register defines
 ****************************************************************************************
 */
#define WDOG_COUNTER_OFFSETADDRESS     0x00000004  /* R */
#define WDOG_COUNTER_BITOFFSET         0
#define WDOG_COUNTER_BITFIELDSIZE      32
#define WDOG_COUNTER_BITMASK           0xFFFFFFFF
#define WDOG_COUNTER_INIT              0x00000000
/*
 *  WDOG_COUNTER_VAL bit field defines
 ****************************************************************************************
 */
#define WDOG_COUNTER_VAL_OFFSETADDRESS          WDOG_COUNTER_OFFSETADDRESS
#define WDOG_COUNTER_VAL_BITOFFSET              0
#define WDOG_COUNTER_VAL_BITFIELDSIZE          32
#define WDOG_COUNTER_VAL_BITMASK                0xffffffff
#define WDOG_COUNTER_VAL_INIT                   0x0

/*
 *  WDOG_CONTROL register defines
 ****************************************************************************************
 */
#define WDOG_CONTROL_OFFSETADDRESS     0x00000008  /* R */
#define WDOG_CONTROL_BITOFFSET         0
#define WDOG_CONTROL_BITFIELDSIZE      32
#define WDOG_CONTROL_BITMASK           0xFFFFFFFF
#define WDOG_CONTROL_INIT              0x00000000
/*
 *  WDOG_INT_EN bit field defines
 ****************************************************************************************
 */
#define WDOG_INT_EN_OFFSETADDRESS               WDOG_CONTROL_OFFSETADDRESS
#define WDOG_INT_EN_BITOFFSET                   0
#define WDOG_INT_EN_BITFIELDSIZE                1
#define WDOG_INT_EN_BITMASK                     0x00000001
#define WDOG_INT_EN_INIT                        0x0
/*
 *  WDOG_RESET_EN bit field defines
 ****************************************************************************************
 */
#define WDOG_RESET_EN_OFFSETADDRESS             WDOG_CONTROL_OFFSETADDRESS
#define WDOG_RESET_EN_BITOFFSET                 1
#define WDOG_RESET_EN_BITFIELDSIZE              1
#define WDOG_RESET_EN_BITMASK                   0x00000002
#define WDOG_RESET_EN_INIT                      0x0

/*
 *  WDOG_INT_CLR register defines
 ****************************************************************************************
 */
#define WDOG_INT_CLR_OFFSETADDRESS     0x0000000c  /* R */
#define WDOG_INT_CLR_BITOFFSET         0
#define WDOG_INT_CLR_BITFIELDSIZE      32
#define WDOG_INT_CLR_BITMASK           0xFFFFFFFF
#define WDOG_INT_CLR_INIT              0x00000000
/*
 *  WDOG_INT_CLEAR bit field defines
 ****************************************************************************************
 */
#define WDOG_INT_CLEAR_OFFSETADDRESS            WDOG_INT_CLR_OFFSETADDRESS
#define WDOG_INT_CLEAR_BITOFFSET                0
#define WDOG_INT_CLEAR_BITFIELDSIZE            32
#define WDOG_INT_CLEAR_BITMASK                  0xffffffff
#define WDOG_INT_CLEAR_INIT                     0x0

/*
 *  WDOG_RAW_INT_STAT register defines
 ****************************************************************************************
 */
#define WDOG_RAW_INT_STAT_OFFSETADDRESS 0x00000010  /* R */
#define WDOG_RAW_INT_STAT_BITOFFSET    0
#define WDOG_RAW_INT_STAT_BITFIELDSIZE 32
#define WDOG_RAW_INT_STAT_BITMASK      0xFFFFFFFF
#define WDOG_RAW_INT_STAT_INIT         0x00000000
/*
 *  WDOG_RAW_INT_STATUS bit field defines
 ****************************************************************************************
 */
#define WDOG_RAW_INT_STATUS_OFFSETADDRESS       WDOG_RAW_INT_STAT_OFFSETADDRESS
#define WDOG_RAW_INT_STATUS_BITOFFSET           0
#define WDOG_RAW_INT_STATUS_BITFIELDSIZE        1
#define WDOG_RAW_INT_STATUS_BITMASK             0x00000001
#define WDOG_RAW_INT_STATUS_INIT                0x0

/*
 *  WDOG_MASKED_INT_STAT register defines
 ****************************************************************************************
 */
#define WDOG_MASKED_INT_STAT_OFFSETADDRESS 0x00000014  /* R */
#define WDOG_MASKED_INT_STAT_BITOFFSET 0
#define WDOG_MASKED_INT_STAT_BITFIELDSIZE 32
#define WDOG_MASKED_INT_STAT_BITMASK   0xFFFFFFFF
#define WDOG_MASKED_INT_STAT_INIT      0x00000000
/*
 *  WDOG_MASKED_INT_STATUS bit field defines
 ****************************************************************************************
 */
#define WDOG_MASKED_INT_STATUS_OFFSETADDRESS    WDOG_MASKED_INT_STAT_OFFSETADDRESS
#define WDOG_MASKED_INT_STATUS_BITOFFSET        0
#define WDOG_MASKED_INT_STATUS_BITFIELDSIZE     1
#define WDOG_MASKED_INT_STATUS_BITMASK          0x00000001
#define WDOG_MASKED_INT_STATUS_INIT             0x0

/*
 *  WDOG_LOCK register defines
 ****************************************************************************************
 */
#define WDOG_LOCK_OFFSETADDRESS        0x00000c00  /* RW */
#define WDOG_LOCK_BITOFFSET            0
#define WDOG_LOCK_BITFIELDSIZE         32
#define WDOG_LOCK_BITMASK              0xFFFFFFFF
#define WDOG_LOCK_INIT                 0x00000000
/*
 *  WDOG_LOCK_VAL bit field defines
 ****************************************************************************************
 */
#define WDOG_LOCK_VAL_OFFSETADDRESS             WDOG_LOCK_OFFSETADDRESS
#define WDOG_LOCK_VAL_BITOFFSET                 0
#define WDOG_LOCK_VAL_BITFIELDSIZE             32
#define WDOG_LOCK_VAL_BITMASK                   0xffffffff
#define WDOG_LOCK_VAL_INIT                      0x0
#endif
