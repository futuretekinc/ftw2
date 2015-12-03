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
* $RCSfile: gsn_br_otprtc.h,v $
*
* Description : This file contains boot rom's flash booter.
*****************************************************************************/
#ifndef _GSN_BR_OTPRTC_H_
#define _GSN_BR_OTPRTC_H_

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_includes.h"
#include "gsn_types.h"


/**
 *****************************************************************************
 * @file gsn_br_otprtc.h
 * @brief GSN boot rom OTP RTC functionality.
 *    This file contains boot rom's functionality of storing and loading
 *    ROM patches from OTP and RTC.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GEPSSupport
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnBrOtpRtc GSN Bootrom OTP RTC functionality
 * @brief This module Contains boot rom's functionality of storing and loading
 *    ROM patches from OTP and RTC.
 *
 * \verbatim
 * PUBLIC is actually defined as blank.
 * PRIVATE is replaced with the "static" descriptor.
 * TRUE is replaced with 1, FALSE with 0
 * Compile-dependent definitions are provided for INLINE
 * BIT(n) provides n-bit offsets
 * A UINT32 with all bits = 1 is defined.
 *
 *\endverbatim
 *****************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/


/*****************************************************************************
  *  Definitions
  ****************************************************************************/
#define GSN_BR_OTPRTC_ROM_PATCH_CTL_SIGNATURE  (UINT16)0x95CD
#define GSN_BR_OTPRTC_ROM_PATCH_FPT_SIGNATURE  (UINT32)0x95950F97
#define GSN_BR_OTPRTC_ROM_PATCH_CODE_SIGNATURE (UINT32)0x9595C0DE

#define GSN_BR_OTPRTC_ROM_PATCH_CTL_JUMP_ADDR_PRESENT   0x1

typedef struct GSN_BR_OTPRTC_ROM_PATCH_CTL_S
{
    UINT16 signature;
    UINT16 flags;   /* bit#0 1 indicates if jump addresses are present */
    UINT16 appFptOffset;
    UINT16 appCodeOffset;
    UINT16 wlanFptOffset;
    UINT16 wlanCodeOffset;
    UINT32 appRomJumpAddr;
    UINT32 wlanRomJumpAddr;
} GSN_BR_OTPRTC_ROM_PATCH_CTL_T;

typedef struct GSN_BR_OTPRTC_ROM_PATCH_INFO_S
{
    UINT32 fptLocation;
    UINT32 patchFnAddr;
} GSN_BR_OTPRTC_ROM_PATCH_INFO_T;

typedef struct GSN_BR_OTPRTC_RTC_ROM_PATCH_FPT_S
{
    UINT32 signature;
    UINT8  wlanCode; /* indicates if this patch if for WLAN */
    UINT8  unused;
    UINT16 numPatches;
    GSN_BR_OTPRTC_ROM_PATCH_INFO_T patchInfo[0];
} GSN_BR_OTPRTC_RTC_ROM_PATCH_FPT_T;

typedef struct GSN_BR_OTPRTC_RTC_ROM_PATCH_CODE_S
{
    UINT32 signature;
    UINT8  wlanCode;
    UINT8  remapRegSetIndex;
    UINT16 codeSize;
    UINT32 remapSrcAddr;
    UINT32 remapDstAddr;
    UINT8  code[0];
} GSN_BR_OTPRTC_RTC_ROM_PATCH_CODE_T;


PUBLIC VOID
GsnBrOtpRtc_RomPatchRtcCheck();

PUBLIC VOID
GsnBrOtpRtc_RomPatchOtpCheck();


#ifdef __cplusplus
}
#endif

#endif /* _GSN_BR_OTPRTC_H_ */


