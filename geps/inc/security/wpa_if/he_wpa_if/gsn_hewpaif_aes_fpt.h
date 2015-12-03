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
* $RCSfile: gsn_hewpaif_aes_fpt.h,v $
*
* Description : This file contains function pointer variables for 
* gsn_hewpaif_aes.c.
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
#include "supplicant/crypto/aes.h"

typedef int (*aes_128_cbc_encrypt_FP_T)(const uint8_t *key, const uint8_t *iv, uint8_t *data, 
                        size_t data_len);
extern _RPST_ aes_128_cbc_encrypt_FP_T aes_128_cbc_encrypt_FP;

typedef int (*aes_128_cbc_decrypt_FP_T)(const uint8_t *key, const uint8_t *iv, uint8_t *data, 
                        size_t data_len);
extern _RPST_ aes_128_cbc_decrypt_FP_T aes_128_cbc_decrypt_FP;

typedef int (*aes_wrap_FP_T)(const uint8_t *kek, int n, const uint8_t *plain, uint8_t *cipher);
extern _RPST_ aes_wrap_FP_T aes_wrap_FP;

typedef int (*aes_unwrap_FP_T)(const uint8_t *kek, int n, const uint8_t *cipher, uint8_t *plain);
extern _RPST_ aes_unwrap_FP_T aes_unwrap_FP;

typedef int (*omac1_aes_128_vector_FP_T)(const uint8_t *key, size_t num_elem,
			 const uint8_t *addr[], const size_t *len, uint8_t *mac);
extern _RPST_ omac1_aes_128_vector_FP_T omac1_aes_128_vector_FP;

typedef int (*omac1_aes_128_FP_T)(const uint8_t *key, const uint8_t *data, size_t data_len, uint8_t *mac);
extern _RPST_ omac1_aes_128_FP_T omac1_aes_128_FP;

typedef int (*aes_128_ctr_encrypt_FP_T)(const uint8_t *key, const uint8_t *nonce,
			uint8_t *data, size_t data_len);
extern _RPST_ aes_128_ctr_encrypt_FP_T aes_128_ctr_encrypt_FP;

typedef int (*aes_128_eax_encrypt_FP_T)(const uint8_t *key, const uint8_t *nonce, size_t nonce_len,
			const uint8_t *hdr, size_t hdr_len,
			uint8_t *data, size_t data_len, uint8_t *tag);
extern _RPST_ aes_128_eax_encrypt_FP_T aes_128_eax_encrypt_FP;

typedef int (*aes_128_eax_decrypt_FP_T)(const uint8_t *key, const uint8_t *nonce, size_t nonce_len,
			const uint8_t *hdr, size_t hdr_len,
			uint8_t *data, size_t data_len, const uint8_t *tag);
extern _RPST_ aes_128_eax_decrypt_FP_T aes_128_eax_decrypt_FP;

typedef int (*aes_128_encrypt_block_FP_T)(const uint8_t *key, const uint8_t *in, uint8_t *out);
extern _RPST_ aes_128_encrypt_block_FP_T aes_128_encrypt_block_FP;

