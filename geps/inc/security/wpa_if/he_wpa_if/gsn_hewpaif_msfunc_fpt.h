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
* $RCSfile: gsn_hewpaif_msfunc_fpt.h,v $
*
* Description : This file contains function pointer variables for 
* gsn_hewpaif_msfunc.c.
*******************************************************************************/

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "supplicant/utils/includes.h"
#include "supplicant/utils/common.h"
#include "supplicant/crypto/crypto.h"
#include "supplicant/crypto/sha1.h"
#include "supplicant/eap_common/eap_defs.h"
#include "supplicant/common/defs.h"
#include "supplicant/rsn_supp/wpa.h"

typedef int (*challenge_hash_FP_T)(const u8 *peer_challenge, const u8 *auth_challenge,
			  const u8 *username, size_t username_len,
			  u8 *challenge);
extern _RPST_ challenge_hash_FP_T challenge_hash_FP;

typedef int (*nt_password_hash_FP_T)(const u8 *password, size_t password_len,
		      u8 *password_hash);
extern _RPST_ nt_password_hash_FP_T nt_password_hash_FP;

typedef int (*hash_nt_password_hash_FP_T)(const u8 *password_hash, u8 *password_hash_hash);
extern _RPST_ hash_nt_password_hash_FP_T hash_nt_password_hash_FP;

typedef void (*challenge_response_FP_T)(const u8 *challenge, const u8 *password_hash,
			u8 *response);
extern _RPST_ challenge_response_FP_T challenge_response_FP;

typedef int (*generate_nt_response_FP_T)(const u8 *auth_challenge, const u8 *peer_challenge,
			 const u8 *username, size_t username_len,
			 const u8 *password, size_t password_len,
			 u8 *response);
extern _RPST_ generate_nt_response_FP_T generate_nt_response_FP;

typedef int (*generate_nt_response_pwhash_FP_T)(const u8 *auth_challenge,
				const u8 *peer_challenge,
				const u8 *username, size_t username_len,
				const u8 *password_hash,
				u8 *response);
extern _RPST_ generate_nt_response_pwhash_FP_T generate_nt_response_pwhash_FP;

typedef int (*generate_authenticator_response_pwhash_FP_T)(
	const u8 *password_hash,
	const u8 *peer_challenge, const u8 *auth_challenge,
	const u8 *username, size_t username_len,
	const u8 *nt_response, u8 *response);
extern _RPST_ generate_authenticator_response_pwhash_FP_T generate_authenticator_response_pwhash_FP;

typedef int (*generate_authenticator_response_FP_T)(const u8 *password, size_t password_len,
				    const u8 *peer_challenge,
				    const u8 *auth_challenge,
				    const u8 *username, size_t username_len,
				    const u8 *nt_response, u8 *response);
extern _RPST_ generate_authenticator_response_FP_T generate_authenticator_response_FP;

typedef int (*nt_challenge_response_FP_T)(const u8 *challenge, const u8 *password,
			  size_t password_len, u8 *response);
extern _RPST_ nt_challenge_response_FP_T nt_challenge_response_FP;

typedef int (*get_master_key_FP_T)(const u8 *password_hash_hash, const u8 *nt_response,
		   u8 *master_key);
extern _RPST_ get_master_key_FP_T get_master_key_FP;

typedef int (*get_asymetric_start_key_FP_T)(const u8 *master_key, u8 *session_key,
			    size_t session_key_len, int is_send,
			    int is_server);
extern _RPST_ get_asymetric_start_key_FP_T get_asymetric_start_key_FP;

typedef int (*encrypt_pw_block_with_password_hash_FP_T)(
	const u8 *password, size_t password_len,
	const u8 *password_hash, u8 *pw_block);
extern _RPST_ encrypt_pw_block_with_password_hash_FP_T encrypt_pw_block_with_password_hash_FP;

typedef int (*new_password_encrypted_with_old_nt_password_hash_FP_T)(
	const u8 *new_password, size_t new_password_len,
	const u8 *old_password, size_t old_password_len,
	u8 *encrypted_pw_block);
extern _RPST_ new_password_encrypted_with_old_nt_password_hash_FP_T new_password_encrypted_with_old_nt_password_hash_FP;

typedef void (*nt_password_hash_encrypted_with_block_FP_T)(const u8 *password_hash,
					   const u8 *block, u8 *cypher);
extern _RPST_ nt_password_hash_encrypted_with_block_FP_T nt_password_hash_encrypted_with_block_FP;

typedef int (*old_nt_password_hash_encrypted_with_new_nt_password_hash_FP_T)(
	const u8 *new_password, size_t new_password_len,
	const u8 *old_password, size_t old_password_len,
	u8 *encrypted_password_hash);
extern _RPST_ old_nt_password_hash_encrypted_with_new_nt_password_hash_FP_T old_nt_password_hash_encrypted_with_new_nt_password_hash_FP;
