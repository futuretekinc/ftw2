/******************************************************************************
*
*               COPYRIGHT (c) 2012-2014 GainSpan Corporation
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
* $RCSfile: gsn_otp.h,v $
*
* Description : This file contains public definitions for OTP driver.
******************************************************************************/
#ifndef _GSN_OTP_H_
#define _GSN_OTP_H_
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
* File Inclusion
*****************************************************************************/
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
    
#include "core/reg/gsn_reg_op.h"
  
#include "drivers/reg/gsn_reg_otp_spec.h"
#include "drivers/reg/gsn_reg_otp_op.h"


/**
 *****************************************************************************
 * @file gsn_otp.h
 * @brief GSN OTP driver public header.
 *    This file contains the public APIs and structures of OTP
 *    driver module.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup driversdoc
 *
 * @{
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup GsnOtp GSN OTP driver API.
 *    This group of APIs implements the OTP driver features.
*****************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/

/*****************************************************************************
 * MACROS 
 ****************************************************************************/
//#define GSN_OTP_RAM_EMULATION

#define GSN_OTP_NUM_BYTES_PER_WORD          8
#define GSN_OTP_NUM_BYTES_PER_WORD_MASK_VAL (GSN_OTP_NUM_BYTES_PER_WORD-1)
#define GSN_OTP_NUM_BYTES_PER_WORD_SHIFT_VAL 3
#define GSN_OTP_NUM_WORDS_PER_BLK           256
#define GSN_OTP_NUM_WORDS_PER_BLK_MASK_VAL  (GSN_OTP_NUM_WORDS_PER_BLK-1)
#define GSN_OTP_NUM_WORDS_PER_BLK_SHIFT_VAL 8     /* 2^8 */
#define GSN_OTP_NUM_BYTES_PER_BLK           \
            (GSN_OTP_NUM_BYTES_PER_WORD * GSN_OTP_NUM_WORDS_PER_BLK)

#define GSN_OTP_START_ADDR                  0
#define GSN_OTP_SIZE_IN_BYTES               \
    (GSN_OTP_NUM_BYTES_PER_WORD * GSN_OTP_NUM_WORDS_PER_BLK \
    * GSN_OTP_NUM_BLKS)

#define GSN_OTP_NUM_TEST_WORDS_PER_BLK      4
#define GSN_OTP_NUM_BLKS                    2

#define GSN_OTP_BLK_TEST_WORD_START_ADDR    0x100

#define GSN_OTP_LENBYTES_TO_LENWORDS(len)      \
    (((len) & GSN_OTP_NUM_BYTES_PER_WORD_MASK_VAL) == 0) ? \
    ((len) >> GSN_OTP_NUM_BYTES_PER_WORD_SHIFT_VAL) : \
    (((len) + (GSN_OTP_NUM_BYTES_PER_WORD - ((len) & GSN_OTP_NUM_BYTES_PER_WORD_MASK_VAL))) >> GSN_OTP_NUM_BYTES_PER_WORD_SHIFT_VAL)

/* This macro converts a given byte address to block number. For example,
 * it returns block 0 for byte address 8 and block 1 for byte address
 * 2048.
 */
#define GSN_OTP_BYTEADDR_TO_BLKNUM(addr)      \
    ((((UINT32)addr) >> GSN_OTP_NUM_BYTES_PER_WORD_SHIFT_VAL) >> GSN_OTP_NUM_WORDS_PER_BLK_SHIFT_VAL)

/* This macro converts a given byte address to block adjusted word
 * address ie., relative word address. For example, it returns 1 for
 * byte address 8 and 2056.
 */
#define GSN_OTP_BYTEADDR_TO_WORDADDR(addr)     \
    ((((UINT32)addr) >> GSN_OTP_NUM_BYTES_PER_WORD_SHIFT_VAL) & GSN_OTP_NUM_WORDS_PER_BLK_MASK_VAL)

#define GSN_OTP_WORDADDR_TO_BYTEADDR(addr)     \
    ((UINT32)(addr) * GSN_OTP_NUM_BYTES_PER_WORD)

#define GSN_OTP_BYTEADDR_NEXT_WORD_ALIGN(addr)  \
    ((((UINT32)addr) & GSN_OTP_NUM_BYTES_PER_WORD_MASK_VAL) == 0) ? \
    ((UINT32)addr) : \
    (((UINT32)addr) + (GSN_OTP_NUM_BYTES_PER_WORD - (((UINT32)addr) & GSN_OTP_NUM_BYTES_PER_WORD_MASK_VAL)))
/*
*/

/*****************************************************************************
  * Public definitions
  ****************************************************************************/

typedef struct GSN_OTP_S
{
    #ifdef GSN_OTP_RAM_EMULATION
    /* For testing, we use ram */
    ULONG64 otpStore[2][256];
    #endif

    ULONG64 lastWord;
    UINT32 lastWordAddr;
    UINT32 lastWordBlk;
    BOOL lastWordValid;

    UINT32 nextFreeAddr; /**< maintains next free address */
    UINT32 otpBlkBase[2]; /**< maintains OTP block register base addresses */

    /* other context ptrs */
    void *pDbg;
    void *pClkCtl;

    GSN_OSAL_SEM_T otpSem;
    GSN_OSAL_MUTEX_T otpAccessMutex; // to protect for re-entrant scenario
} GSN_OTP_T;

typedef struct GSN_OTP_CTX_USES_OBJS_S
{
    void *pDbg;
    void *pClkCtl;
}GSN_OTP_CTX_USES_OBJS_S;


#define GSN_OTP_CTX_USES_INFO_T void

/*****************************************************************************
  * Public Variables
  ****************************************************************************/



/*****************************************************************************
  * Public functions
  ****************************************************************************/


PUBLIC GSN_STATUS
GsnOtp_Init(GSN_OTP_T *pOtp, GSN_OTP_CTX_USES_OBJS_S *pUsesObjs, GSN_OTP_CTX_USES_INFO_T *pUsesInfo);

PUBLIC GSN_STATUS
GsnOtp_Write(GSN_OTP_T *pOtp, UINT8 *addr, UINT32 len, UINT8 *data);

PUBLIC GSN_STATUS
GsnOtp_Read(GSN_OTP_T *pOtp, UINT8 *addr, UINT32 len, UINT8 *data);

PUBLIC VOID
GsnOtp_Isr(void);

#ifdef __cplusplus
}
#endif
#endif /* _GSN_OTP_H_ */
