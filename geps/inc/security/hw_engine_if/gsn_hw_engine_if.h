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
* $RCSfile: gsn_hw_engine_if.h,v $
*
* Description : This file contains the interfacing APIs and declaration that is
* used to interface with the Crypto HW Engine block.
*******************************************************************************/
#ifndef _GSN_HW_ENGINE_IF_H_
#define _GSN_HW_ENGINE_IF_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include "security/hw_engine_if/driver/inc/elpspacc.h"
#include "security/hw_engine_if/driver/src/inc/elppka.h"
#include "security/hw_engine_if/driver/src/inc/elptrng.h"


#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"

/**
 *******************************************************************************
 * @file gsn_hw_engine_if.h
 * @brief GSN HEIF module.
 *      This file contains the HW Engine IF specific definitions.
 ******************************************************************************/

/**
 *****************************************************************************
 * @ingroup supplicantdoc
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnHEIf GSN Hardware Engine Interface
 *****************************************************************************/
	
	
/**
 *****************************************************************************
 * 
 * @}
 *****************************************************************************/


typedef enum GSN_CRYPTO_MODE
{
    GSN_CRYPTO_MODE_NULL = CRYPTO_MODE_NULL,
    GSN_CRYPTO_MODE_RC4_40 = CRYPTO_MODE_RC4_40,
    GSN_CRYPTO_MODE_RC4_128 = CRYPTO_MODE_RC4_128,
    GSN_CRYPTO_MODE_RC4_KS = CRYPTO_MODE_RC4_KS,
    GSN_CRYPTO_MODE_AES_ECB = CRYPTO_MODE_AES_ECB,
    GSN_CRYPTO_MODE_AES_CBC = CRYPTO_MODE_AES_CBC,
    GSN_CRYPTO_MODE_AES_CTR = CRYPTO_MODE_AES_CTR,
    GSN_CRYPTO_MODE_AES_CCM = CRYPTO_MODE_AES_CCM,
    GSN_CRYPTO_MODE_AES_GCM = CRYPTO_MODE_AES_GCM,

    GSN_CRYPTO_MODE_3DES_CBC = CRYPTO_MODE_3DES_CBC,
    GSN_CRYPTO_MODE_3DES_ECB = CRYPTO_MODE_3DES_ECB,
    GSN_CRYPTO_MODE_DES_CBC = CRYPTO_MODE_DES_CBC,
    GSN_CRYPTO_MODE_DES_ECB = CRYPTO_MODE_DES_ECB,
    GSN_CRYPTO_MODE_RC4_256 = CRYPTO_MODE_RC4_256

}GSN_CRYPTO_MODE_T;

typedef enum GSN_CRYPTO_OP
{
    GSN_CRYPTO_OP_ENCRYPT,
    GSN_CRYPTO_OP_DECRYPT
}GSN_CRYPTO_OP_T;

typedef enum GSN_HASH_MODE
{
    GSN_HASH_MODE_SHA1 = CRYPTO_MODE_HASH_SHA1,
    GSN_HASH_MODE_HMAC_SHA1 = CRYPTO_MODE_HMAC_SHA1,
    GSN_HASH_MODE_MD5 = CRYPTO_MODE_HASH_MD5,
    GSN_HASH_MODE_HMAC_MD5 = CRYPTO_MODE_HMAC_MD5,

    GSN_HASH_MODE_SHA256 = CRYPTO_MODE_HASH_SHA256,
    GSN_HASH_MODE_HMAC_SHA256 = CRYPTO_MODE_HMAC_SHA256,
    GSN_HASH_MODE_MAC_XCBC = CRYPTO_MODE_MAC_XCBC,
    GSN_HASE_MODE_MAC_CMAC = CRYPTO_MODE_MAC_CMAC
}GSN_HASH_MODE_T;


PUBLIC GSN_STATUS
GsnHeIf_DriverInit( UINT32      seed[TRNG_NONCE_SIZE_WORDS]);

PUBLIC INT32
GsnHeIf_CryptoInit( GSN_CRYPTO_MODE_T cModes, GSN_CRYPTO_OP_T op, UINT8 *pKey,
UINT32 keySize, UINT8 *pIv, UINT32 ivSize );
PUBLIC GSN_STATUS
GsnHeIf_CryptoProcess( INT32 handle, UINT8 *pSrc, UINT32 len, UINT8 *pDst );

PUBLIC GSN_STATUS
GsnHeIf_CryptoDeInit( INT32 handle );
PUBLIC INT32
GsnHeIf_HashInit( GSN_HASH_MODE_T hMode, GSN_CRYPTO_OP_T op, UINT8 *pKey,
UINT32 keySize, UINT8 *pIv, UINT32 ivSize );

PUBLIC GSN_STATUS
GsnHeIf_HashProcess( INT32 handle, UINT32 num_elem, const UINT8 *pSrc[],
    UINT32 *pLen, UINT8 *pDst, UINT32 destBuflen );
PUBLIC GSN_STATUS
GsnHeIf_HashDeInit( INT32 handle );

PUBLIC INT32
GsnHeIf_TrangGenerate( UINT8* pBuf, UINT32 length ) ;

PUBLIC VOID
GsnHeIf_DriverDeinit( VOID );


PUBLIC VOID
GsnHeIf_DriverSuspend(VOID);
#ifdef __cplusplus
}
#endif
#endif /*  _GSN_HW_ENGINE_IF_H_ */
