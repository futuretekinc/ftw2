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
* $RCSfile: gsn_hewpaif_crypto_fpt.h,v $
*
* Description : This file contains function pointer variables for 
* gsn_hewpaif_crypto.c.
*******************************************************************************/

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "supplicant/utils/includes.h"
#include "supplicant/utils/common.h"
#include "supplicant/crypto/aes.h"
#include "supplicant/crypto/crypto.h"
#include "supplicant/crypto/md5.h"
#include "supplicant/crypto/sha1.h"
#include "supplicant/eap_common/eap_defs.h"
#include "supplicant/common/defs.h"
#include "supplicant/rsn_supp/wpa.h"

#include "security/hw_engine_if/gsn_hw_engine_if.h"

#include "supplicant/tls/bignum.h"
typedef struct crypto_cipher * (*crypto_cipher_init_FP_T)(enum crypto_cipher_alg alg,
					  const u8 *iv, const u8 *key,
					  size_t key_len);
extern _RPST_ crypto_cipher_init_FP_T crypto_cipher_init_FP;

typedef int (*crypto_cipher_encrypt_FP_T)(struct crypto_cipher *ctx, const u8 *plain,
			  u8 *crypt, size_t len);
extern _RPST_ crypto_cipher_encrypt_FP_T crypto_cipher_encrypt_FP;

typedef int (*crypto_cipher_decrypt_FP_T)(struct crypto_cipher *ctx, const u8 *crypt,
			  u8 *plain, size_t len);
extern _RPST_ crypto_cipher_decrypt_FP_T crypto_cipher_decrypt_FP;

typedef void (*crypto_cipher_deinit_FP_T)(struct crypto_cipher *ctx);
extern _RPST_ crypto_cipher_deinit_FP_T crypto_cipher_deinit_FP;

typedef struct crypto_hash * (*crypto_hash_init_FP_T)(enum crypto_hash_alg alg, 
    const u8 *key, u32 key_len);
extern _RPST_ crypto_hash_init_FP_T crypto_hash_init_FP;

typedef void (*crypto_hash_update_FP_T)(struct crypto_hash *ctx, const u8 *data, size_t len);
extern _RPST_ crypto_hash_update_FP_T crypto_hash_update_FP;

typedef int (*crypto_hash_finish_FP_T)(struct crypto_hash *ctx, u8 *mac, size_t *len);
extern _RPST_ crypto_hash_finish_FP_T crypto_hash_finish_FP;

typedef int (*crypto_global_init_FP_T)(void);
extern _RPST_ crypto_global_init_FP_T crypto_global_init_FP;

typedef void (*crypto_global_deinit_FP_T)(void);
extern _RPST_ crypto_global_deinit_FP_T crypto_global_deinit_FP;

typedef int (*crypto_mod_exp_FP_T)(const u8 *base, size_t base_len,
		   const u8 *power, size_t power_len,
		   const u8 *modulus, size_t modulus_len,
		   u8 *result, size_t *result_len);
extern _RPST_ crypto_mod_exp_FP_T crypto_mod_exp_FP;

typedef void (*des_encrypt_FP_T)(const u8 *clear, const u8 *key, u8 *cypher);
extern _RPST_ des_encrypt_FP_T des_encrypt_FP;
