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
* $RCSfile: gsn_otp_mm.h,v $
*
* Description : This file contains public definitions for OTP MM module.
******************************************************************************/
#ifndef _GSN_OTP_MM_H_
#define _GSN_OTP_MM_H_
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
* File Inclusion
*****************************************************************************/
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
    

/**
 *****************************************************************************
 * @file gsn_otp_mm.h
 * @brief GSN OTP Memory Management public header.
 *    This file contains the public APIs and structures of OTP memory
 *    management module.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup syssvcdoc
 * @{
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup GsnOtpMm GSN OTP Memory Management API.
 *    This group of APIs implements the OTP MM functions.
*****************************************************************************/

/**
 ******************************************************************************
 * @} 
 *****************************************************************************/


/*****************************************************************************
 * MACROS 
 ****************************************************************************/

/* OTP Signature suggested by HW team */
#define GSN_OTP_MM_SIGNATURE 0xf0a5

#define GSN_OTP_MM_VER_MAX     0xF
#define GSN_OTP_MM_VER_UNKNOWN 0x10

/*****************************************************************************
 * Public definitions
 ****************************************************************************/
typedef struct GSN_OTP_MM_CTX_S
{
    UINT32 nextFreeLoc;
    BOOL nextFreeLocValid;

    void *pOtpDrv;
    
    GSN_OSAL_MUTEX_T mutex;

} GSN_OTP_MM_CTX_T;

typedef struct GSN_OTP_MM_USES_OBJS_S
{
    void *otpDrv;

} GSN_OTP_MM_USES_OBJS_T;

#define GSN_OTP_MM_USES_INFO_T void

/* OTP memory management structure */
typedef struct GSN_OTP_MM_DATA_S
{
    UINT32 SignatureAndIdVerLen0; /**< Signature:0-15, ver0:16-19, ID0:20-27, Len0:28-31*/
    UINT32 verIdLenChksum1; /**< Len0:0-3,  ver1:4-7, ID1:8-15, Len1:16-23, chksum: 24-31 */
    UINT8  data[0];  /**< data of len bytes */
} GSN_OTP_MM_DATA_T;


/*****************************************************************************
  * Public function
  ****************************************************************************/



PUBLIC GSN_STATUS
GsnOtpMm_Init(GSN_OTP_MM_CTX_T* otpMm,
                GSN_OTP_MM_USES_OBJS_T *usesObjs,
                GSN_OTP_MM_USES_INFO_T *usesInfo);

PUBLIC GSN_STATUS
GsnOtpMm_Write(UINT8 id, UINT8 ver, UINT16 len, UINT8 *data);

PUBLIC GSN_STATUS
GsnOtpMm_Read(UINT8 id, UINT8 ver, UINT16* len, UINT8 *data);

GSN_STATUS
GsnOtpMm_NextFreeLocFind(VOID);
BOOL
GsnOtpMm_HdrValid(GSN_OTP_MM_DATA_T *otpHdr);

#ifdef __cplusplus
}
#endif
#endif /* _GSN_OTP_MM_H_ */
