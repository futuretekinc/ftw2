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
* $RCSfile: gsn_hewpaif_sha_fpt.h,v $
*
* Description : This file contains function pointer variables for 
* gsn_hewpaif_sha.c.
*******************************************************************************/

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include "security/hw_engine_if/gsn_hw_engine_if.h"

#include "supplicant/utils/includes.h"
#include "supplicant/utils/common.h"
#include "supplicant/crypto/crypto.h"
#include "supplicant/crypto/sha1.h"
#include "supplicant/crypto/sha1_i.h"

#include "supplicant/crypto/sha256.h"
#include "supplicant/eap_common/eap_defs.h"
#include "supplicant/common/defs.h"
#include "supplicant/rsn_supp/wpa.h"

typedef int (*hmac_sha1_vector_FP_T)(const u8 *key, size_t key_len, size_t num_elem,
		     const u8 *addr[], const size_t *len, u8 *mac);
extern _RPST_ hmac_sha1_vector_FP_T hmac_sha1_vector_FP;

typedef int (*hmac_sha1_FP_T)(const u8 *key, size_t key_len, const u8 *data, size_t data_len,
	       u8 *mac);
extern _RPST_ hmac_sha1_FP_T hmac_sha1_FP;

typedef int (*sha1_prf_FP_T)(const u8 *key, size_t key_len, const char *label,
	     const u8 *data, size_t data_len, u8 *buf, size_t buf_len);
extern _RPST_ sha1_prf_FP_T sha1_prf_FP;

typedef int (*pbkdf2_sha1_f_FP_T)(const char *passphrase, const char *ssid,
			 size_t ssid_len, int iterations, unsigned int count,
			 u8 *digest);
extern _RPST_ pbkdf2_sha1_f_FP_T pbkdf2_sha1_f_FP;

typedef void (*generate_sha1_keys_FP_T)(const u8 *key, size_t key_len, void *keys);
extern _RPST_ generate_sha1_keys_FP_T generate_sha1_keys_FP;

typedef void (*hmac_sha1_vector_quick_FP_T)(void *keys, size_t num_elem,
		      const u8 *addr[], const size_t *len, u8 *mac);
extern _RPST_ hmac_sha1_vector_quick_FP_T hmac_sha1_vector_quick_FP;

typedef void (*hmac_sha1_quick_FP_T)(void *keys, const u8 *data, size_t data_len, u8 *mac);
extern _RPST_ hmac_sha1_quick_FP_T hmac_sha1_quick_FP;

typedef int (*pbkdf2_sha1_FP_T)(const char *passphrase, const char *ssid, size_t ssid_len,
		int iterations, u8 *buf, size_t buflen);
extern _RPST_ pbkdf2_sha1_FP_T pbkdf2_sha1_FP;

typedef void (*hmac_sha256_vector_FP_T)(const u8 *key, size_t key_len, size_t num_elem,
			const u8 *addr[], const size_t *len, u8 *mac);
extern _RPST_ hmac_sha256_vector_FP_T hmac_sha256_vector_FP;


typedef void (*hmac_sha256_FP_T)(const u8 *key, size_t key_len, const u8 *data,
		 size_t data_len, u8 *mac);
extern _RPST_ hmac_sha256_FP_T hmac_sha256_FP;


typedef void (*sha256_prf_FP_T)(const u8 *key, size_t key_len, const char *label,
		const u8 *data, size_t data_len, u8 *buf, size_t buf_len);
extern _RPST_ sha256_prf_FP_T sha256_prf_FP;

typedef int (*sha256_vector_FP_T)(size_t num_elem, const u8 *addr[], const size_t *len,
		  u8 *mac);
extern _RPST_ sha256_vector_FP_T sha256_vector_FP;


typedef int (*sha1_vector_FP_T)(size_t num_elem, const u8 *addr[], const size_t *len, u8 *mac);
extern _RPST_ sha1_vector_FP_T sha1_vector_FP;

typedef int (*sha1_t_prf_FP_T)(const u8 *key, size_t key_len, const char *label,
	       const u8 *seed, size_t seed_len, u8 *buf, size_t buf_len);
extern _RPST_ sha1_t_prf_FP_T sha1_t_prf_FP;

typedef int (*fips186_2_prf_FP_T)(const u8 *seed, size_t seed_len, u8 *x, size_t xlen);
extern _RPST_ fips186_2_prf_FP_T fips186_2_prf_FP;
