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
* $RCSfile: gsn_heif_crypto_fpt.h,v $
*
* Description : This file contains the interfacing APIs and declaration that is
* used to interface with the HW engine crypto part.
*******************************************************************************/
#ifndef _GSN_HEIF_CTYPRO_FPT_
#define _GSN_HEIF_CTYPRO_FPT_

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "security/hw_engine_if/gsn_hw_engine_if.h"

#define GSN_MAX_DDT_ENTRIES 3
/**
 *******************************************************************************
 * @file gsn_heif_crypto.c
 * @brief GSN HEIF Crypto module.
 *      This file contains the HEIF crypto specific definitions.
 ******************************************************************************/


typedef GSN_STATUS
(*GsnHeIf_DriverInit_FP_T)( UINT32 seed[TRNG_NONCE_SIZE_WORDS] );
extern _RPST_ GsnHeIf_DriverInit_FP_T GsnHeIf_DriverInit_FP;

typedef INT32
(*GsnHeIf_CryptoInit_FP_T)( GSN_CRYPTO_MODE_T cModes, GSN_CRYPTO_OP_T op, UINT8 *pKey, 
UINT32 keySize, UINT8 *pIv, UINT32 ivSize );
extern _RPST_ GsnHeIf_CryptoInit_FP_T GsnHeIf_CryptoInit_FP;

typedef void (*ddt_init_FP_T)( pdu_ddt *pDdt, UINT8 *pSrc, UINT32 len, UINT32 *pBuffer,UINT8 ** pBuf);
extern _RPST_ ddt_init_FP_T ddt_init_FP;

typedef GSN_STATUS
(*GsnHeIf_CryptoProcess_FP_T)( INT32 handle, UINT8 *pSrc, UINT32 len, UINT8 *pDst );
extern _RPST_ GsnHeIf_CryptoProcess_FP_T GsnHeIf_CryptoProcess_FP;

typedef GSN_STATUS
(*GsnHeIf_CryptoDeInit_FP_T)( INT32 handle );
extern _RPST_ GsnHeIf_CryptoDeInit_FP_T GsnHeIf_CryptoDeInit_FP;

typedef GSN_STATUS
		(*GsnHeIf_CryptoDeInitWithIv_FP_T)( INT32 handle, UINT8 *pKey, UINT32 keySize,
		                         UINT8 *pIv, UINT32 ivSize );
extern _RPST_ GsnHeIf_CryptoDeInitWithIv_FP_T GsnHeIf_CryptoDeInitWithIv_FP;

typedef INT32
(*GsnHeIf_HashInit_FP_T)( GSN_HASH_MODE_T hMode, GSN_CRYPTO_OP_T op, UINT8 *pKey, 
UINT32 keySize, UINT8 *pIv, UINT32 ivSize );
extern _RPST_ GsnHeIf_HashInit_FP_T GsnHeIf_HashInit_FP;

typedef void (*ddt_init_m_FP_T)( pdu_ddt *pDdt, UINT32 num_elem, UINT8 *pSrc[], UINT32* pLen, 
    UINT32 *pBuffer );
extern _RPST_ ddt_init_m_FP_T ddt_init_m_FP;

typedef GSN_STATUS
(*GsnHeIf_HashProcess_FP_T)( INT32 handle, UINT32 num_elem, const UINT8 *pSrc[], 
    UINT32 *pLen, UINT8 *pDst, UINT32 destBuflen );
extern _RPST_ GsnHeIf_HashProcess_FP_T GsnHeIf_HashProcess_FP;


typedef GSN_STATUS
(*GsnHeIf_HashDeInit_FP_T)( INT32 handle );
extern _RPST_ GsnHeIf_HashDeInit_FP_T GsnHeIf_HashDeInit_FP;


typedef GSN_STATUS (*GsnHeIf_HashDeInitWithIv_FP_T)( INT32 handle, UINT8 *pKey, UINT32 keySize,
                         UINT8 *pIv, UINT32 ivSize );
extern _RPST_ GsnHeIf_HashDeInitWithIv_FP_T GsnHeIf_HashDeInitWithIv_FP;

typedef VOID (*GsnHeIf_DriverDeinit_FP_T)();
extern _RPST_ GsnHeIf_DriverDeinit_FP_T GsnHeIf_DriverDeinit_FP;
#endif /*_GSN_HEIF_CTYPRO_FPT_*/
