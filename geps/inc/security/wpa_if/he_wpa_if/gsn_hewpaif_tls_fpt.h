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
* $RCSfile: gsn_hewpaif_tls_fpt.h,v $
*
* Description : This file contains function pointer variables for 
* gsn_hewpaif_tls.c.
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
#include "supplicant/crypto/md5_i.h"
#include "supplicant/crypto/md5.h"
#include "supplicant/crypto/sha1.h"
#include "supplicant/crypto/sha1_i.h"

#include "supplicant/crypto/sha256.h"
#include "supplicant/eap_common/eap_defs.h"
#include "supplicant/common/defs.h"
#include "supplicant/rsn_supp/wpa.h"
#include "supplicant/crypto/tls.h"
#include "supplicant/tls/tlsv1_client.h"
#include "supplicant/tls/tlsv1_server.h"

typedef void * (*tls_init_FP_T)(const struct tls_config *conf);
extern _RPST_ tls_init_FP_T tls_init_FP;

typedef void (*tls_deinit_FP_T)(void *ssl_ctx);
extern _RPST_ tls_deinit_FP_T tls_deinit_FP;

typedef struct tls_connection * (*tls_connection_init_FP_T)(void *tls_ctx);
extern _RPST_ tls_connection_init_FP_T tls_connection_init_FP;

typedef void (*tls_connection_deinit_FP_T)(void *tls_ctx, struct tls_connection *conn);
extern _RPST_ tls_connection_deinit_FP_T tls_connection_deinit_FP;

typedef int (*tls_connection_established_FP_T)(void *tls_ctx, struct tls_connection *conn);
extern _RPST_ tls_connection_established_FP_T tls_connection_established_FP;

typedef int (*tls_connection_resumed_FP_T)(void *tls_ctx, struct tls_connection *conn);
extern _RPST_ tls_connection_resumed_FP_T tls_connection_resumed_FP;

typedef int (*tls_connection_set_params_FP_T)(void *tls_ctx, struct tls_connection *conn,
			      const struct tls_connection_params *params);
extern _RPST_ tls_connection_set_params_FP_T tls_connection_set_params_FP;

typedef int (*tls_connection_prf_FP_T)(void *tls_ctx, struct tls_connection *conn,
		       const char *label, int server_random_first,
		       u8 *out, size_t out_len);
extern _RPST_ tls_connection_prf_FP_T tls_connection_prf_FP;

typedef int (*tls_connection_get_keys_FP_T)(void *tls_ctx, struct tls_connection *conn,
			    struct tls_keys *keys);
extern _RPST_ tls_connection_get_keys_FP_T tls_connection_get_keys_FP;

typedef int (*tls_prf_FP_T)(const u8 *secret, size_t secret_len, const char *label,
	    const u8 *seed, size_t seed_len, u8 *out, size_t outlen);
extern _RPST_ tls_prf_FP_T tls_prf_FP;

typedef struct wpabuf * (*tls_connection_handshake_FP_T)(void *tls_ctx,
					 struct tls_connection *conn,
					 const struct wpabuf *in_data,
					 struct wpabuf **appl_data);
extern _RPST_ tls_connection_handshake_FP_T tls_connection_handshake_FP;

typedef int (*tls_connection_get_failed_FP_T)(void *tls_ctx, struct tls_connection *conn);
extern _RPST_ tls_connection_get_failed_FP_T tls_connection_get_failed_FP;

typedef int (*tls_connection_shutdown_FP_T)(void *tls_ctx, struct tls_connection *conn);
extern _RPST_ tls_connection_shutdown_FP_T tls_connection_shutdown_FP;

typedef int (*tls_get_cipher_FP_T)(void *tls_ctx, struct tls_connection *conn,
		   char *buf, size_t buflen);
extern _RPST_ tls_get_cipher_FP_T tls_get_cipher_FP;
/*
typedef int (*tls_get_errors_FP_T)(void *tls_ctx);
extern _RPST_ tls_get_errors_FP_T tls_get_errors_FP;
*/
typedef struct wpabuf * (*tls_connection_encrypt_FP_T)(void *tls_ctx,
				       struct tls_connection *conn,
				       const struct wpabuf *in_data);
extern _RPST_ tls_connection_encrypt_FP_T tls_connection_encrypt_FP;

typedef struct wpabuf * (*tls_connection_decrypt_FP_T)(void *tls_ctx,
				       struct tls_connection *conn,
				       const struct wpabuf *in_data);
extern _RPST_ tls_connection_decrypt_FP_T tls_connection_decrypt_FP;

typedef int (*tls_connection_set_session_ticket_cb_FP_T)(void *tls_ctx,
					 struct tls_connection *conn,
					 tls_session_ticket_cb cb,
					 void *ctx);
extern _RPST_ tls_connection_set_session_ticket_cb_FP_T tls_connection_set_session_ticket_cb_FP;

typedef int (*tls_connection_enable_workaround_FP_T)(void *tls_ctx,
				     struct tls_connection *conn);
extern _RPST_ tls_connection_enable_workaround_FP_T tls_connection_enable_workaround_FP;

typedef int (*tls_connection_client_hello_ext_FP_T)(void *tls_ctx, struct tls_connection *conn,
				    int ext_type, const u8 *data,
				    size_t data_len);
extern _RPST_ tls_connection_client_hello_ext_FP_T tls_connection_client_hello_ext_FP;

typedef int (*tls_connection_set_cipher_list_FP_T)(void *tls_ctx, struct tls_connection *conn,
				   u8 *ciphers);
extern _RPST_ tls_connection_set_cipher_list_FP_T tls_connection_set_cipher_list_FP;

typedef int (*tls_connection_get_keyblock_size_FP_T)(void *tls_ctx,
				     struct tls_connection *conn);
extern _RPST_ tls_connection_get_keyblock_size_FP_T tls_connection_get_keyblock_size_FP;

