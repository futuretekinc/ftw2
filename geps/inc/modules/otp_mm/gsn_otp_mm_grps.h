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
* $RCSfile: gsn_otp_mm_grps.h,v $
*
* Description : This file contains public definitions of OTP MM groups.
******************************************************************************/
#ifndef _GSN_OTP_MM_GRPS_H_
#define _GSN_OTP_MM_GRPS_H_
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
 * @file gsn_otp_mm_grps.h
 * @brief GSN OTP Memory Management special groups public header.
 *    This file contains defintions of OTP memory management module special
 *    groups.
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup GsnOtpMm GSN OTP Memory Management API.
 *    This group defines OTP MM special .
*****************************************************************************/

/*****************************************************************************
 * MACROS 
 ****************************************************************************/
#define GSN_OTP_MM_SP_GRPS_BMAP_GRP_OFFSET      (UINT32)0  /* byte offset in otp mem */
#define GSN_OTP_MM_SKIP_N_BYTES_GRP_OFFSET      (UINT32)16 /* byte offset in otp mem */
#define GSN_OTP_MM_FIRST_FREE_LOC               (UINT32)32 /* byte offset in otp mem */


/*****************************************************************************
 * Public definitions
 ****************************************************************************/

/* Special group IDs are defined here */
typedef enum GSN_OTP_MM_ID_E
{
    /* Special Groups indication bitmap group ID, always placed
       at offset 0 in OTP. */
    GSN_OTP_MM_ID_SP_GRPS_BMAP = 0,

    /* Skip N bytes group is always placed at offset 16 in OTP */
    GSN_OTP_MM_ID_SKIP_N_BYTES = 1,

    /* IDs of special groups */
    GSN_OTP_MM_ID_JUMP_ADDR = 2,
    GSN_OTP_MM_ID_ROM_PATCH_FPT = 3,
    GSN_OTP_MM_ID_ROM_PATCH_CODE = 4,

    /* Other groups */
    GSN_OTP_MM_ID_MFG_DATA = 8,
    GSN_OTP_MM_ID_ATE_CAL_DATA =9,
    GSN_OTP_MM_ID_MODULE_CAL_DATA=10,
    GSN_OTP_MM_ID_MODULE_EXT_INFO=14,
    GSN_OTP_MM_ID_REG_INFO = 15,
    GSN_OTP_MM_ID_MAC_ID0 = 0xF8,
    GSN_OTP_MM_ID_MAC_ID1 = 0xF9,
    GSN_OTP_MM_ID_MAC_ID2 = 0xFA,


    /* If ID is 255, then next byte again contains ID */
    GSN_OTP_MM_ID_EXTENDER = 255

} GSN_OTP_MM_ID_T;

/* All special groups structures are defined here */
typedef struct GSN_OTP_MM_SP_GRPS_BMAP_GRP_S
{
    UINT32 bitmap; /* indicates special groups presence */
    UINT32 featureBitmap; /* indicates which features are enabled/disabled */
} GSN_OTP_MM_SP_GRPS_BMAP_GRP_T;
#define GSN_OTP_MM_SP_GRPS_BMAP_JUMP_ADDR_MASK  (1 << GSN_OTP_MM_ID_JUMP_ADDR)
#define GSN_OTP_MM_SP_GRPS_BMAP_ROM_FPT_MASK    (1 << GSN_OTP_MM_ID_ROM_PATCH_FPT)
#define GSN_OTP_MM_SP_GRPS_BMAP_ROM_CODE_MASK   (1 << GSN_OTP_MM_ID_ROM_PATCH_CODE)


typedef struct GSN_OTP_MM_SKIP_N_BYTES_GRP_S
{
    UINT32 numBytes;
    UINT32 unused;
} GSN_OTP_MM_SKIP_N_BYTES_GRP_T;

typedef struct GSN_OTP_MM_JUMP_ADDR_GRP_S
{
    UINT32 appJumpAddr;
    UINT32 wlanJumpAddr;
} GSN_OTP_MM_JUMP_ADDR_GRP_T;


typedef struct GSN_OTP_MM_ROM_PATCH_INFO_S
{
    UINT32 fptLocation;
    UINT32 patchAddr;
} GSN_OTP_MM_ROM_PATCH_INFO_T;


typedef struct GSN_OTP_MM_ROM_PATCH_FPT_GRP_S
{
    UINT8 flags; /* 0-copyToRtcForWarmBootUse, 1-wlanPatchFpt */
    UINT8 numPatches;
    UINT16 rtcAddr; /* address in RTC to store FPT for warm boot use */
    UINT32 unused; /* to make the patch info aligned to 8-byte boundary  */
    GSN_OTP_MM_ROM_PATCH_INFO_T patchInfo[0]; /* numPatches number of patchInfo */
} GSN_OTP_MM_ROM_PATCH_FPT_GRP_T;

#define GSN_OTP_MM_ROM_PATCH_GRP_FLAG_COPYTORTC 0x1
#define GSN_OTP_MM_ROM_PATCH_GRP_FLAG_WLAN      0x2

typedef struct GSN_OTP_MM_ROM_PATCH_CODE_GRP_S
{
    UINT8 flags; /* 0-copyToRtcForWarmBootUse, 1-wlanPatchCode */
    UINT8 unused1;
    UINT16 rtcAddr; /* address in RTC to store FPT for warm boot use */

    UINT8 remapRegSetIndex; /* 0-7 */
    UINT8 unused2;
    UINT16 codeSize; /* size to be set in remap register */

    UINT32 remapSrcAddr;
    UINT32 remapDstAddr;

    UINT8 patchCode[0]; /* patchCode */
} GSN_OTP_MM_ROM_PATCH_CODE_GRP_T;

typedef struct GSN_OTP_MM_MFG_DATA
{
    ULONG64 lotNumber:34;
    UINT8 waferId:6;
    UINT8 DieY;
    UINT8 DieeX;
} GSN_OTP_MM_MFG_DATA_T;

typedef struct GSN_OTP_MM_ATE_CAL_DATA
{
    UINT8 dx_reTrim:4;
    UINT8 rsvd:4;
    UINT8 Nfine:4;
    UINT8 Ncourse:4;
    UINT8 khz32Rc_cl;
    UINT8 kh32zRc_rl;
    UINT8 khz32Rc_c;
    UINT16 SADC_set0:12;
    UINT8 pkgType:4;
    UINT16 fwVersion;
} GSN_OTP_MM_ATE_CAL_DATA_T;

typedef struct GSN_OTP_MM_MODULE_CAL_DATA
{
    UINT8 khz32Xtal_c1;
    UINT8 khz32Xtal_c2;
    UINT8 mhz40Xtal_rcc1;
    UINT8 mhz40Xtal_c2;
    UINT16 moduleType;
    UINT8 moduleVersion;
    UINT8 calFwVersion;
} GSN_OTP_MM_MODULE_CAL_DATA_T;

typedef struct GSN_OTP_MM_MODULE_EXT_INFO
{
    UINT16 moduleDataCode;
    UINT8 moduleLot:4;
    UINT8 rsvd:4;
    UINT8 assmblyVendorCode;
    UINT16 rsvd1;
    UINT16 sellerId;
} GSN_OTP_MM_MODULE_EXT_INFO_T;

typedef struct GSN_OTP_MM_REG_INFO
{
    UINT16 regDomainId;
    UINT16 rsvd;
    UINT32 rsvd1;
} GSN_OTP_MM_REG_INFO_T;

typedef struct GSN_OTP_MM_MAC_ID
{
    UINT8 mac[6];
    UINT16 rsvd;
} GSN_OTP_MM_MAC_ID_T;


/*****************************************************************************
 * Public Variables
 ****************************************************************************/



/*****************************************************************************
  * Public function
  ****************************************************************************/


#ifdef __cplusplus
}
#endif
#endif /* _GSN_OTP_MM_GRPS_H_ */
