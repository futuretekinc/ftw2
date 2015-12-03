/*******************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
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
* $RCSfile: gsn_heif_trang_fpt.h,v $
*
* Description : This file contains the interfacing APIs and declaration that is
* used to interface with the WPA opwn source code.
*******************************************************************************/
#ifndef _GSN_HEIF_TRANG_FPT_
#define _GSN_HEIF_TRANG_FPT_
/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
#include "security/hw_engine_if/gsn_hw_engine_if.h"
#include "security/hw_engine_if/driver/src/inc/elptrng.h"

/**
 *******************************************************************************
 * @file gsn_wpaif.h
 * @brief GSN WPAIF module.
 *      This file contains the WPAIF specific definitions.
 ******************************************************************************/

typedef INT32
(*GsnHeIf_TrangInit_FP_T)( UINT32 seed[TRNG_NONCE_SIZE_WORDS] ) ;

extern _RPST_ GsnHeIf_TrangInit_FP_T GsnHeIf_TrangInit_FP;

typedef INT32
(*GsnHeIf_TrangGenerate_FP_T)( UINT8* pBuf, UINT32 length ) ;
extern _RPST_ GsnHeIf_TrangGenerate_FP_T GsnHeIf_TrangGenerate_FP;

typedef VOID
(*GsnHeIf_TrangGetSeed_FP_T)( UINT8* pBuf ) ;
extern _RPST_ GsnHeIf_TrangGetSeed_FP_T GsnHeIf_TrangGetSeed_FP;

#endif /* _GSN_HEIF_TRANG_FPT_ */