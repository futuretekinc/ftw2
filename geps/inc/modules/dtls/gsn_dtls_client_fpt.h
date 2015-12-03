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
* $RCSfile: gsn_dtls_client_fpt.h,v $
*
* Description : 
*******************************************************************************/
#ifndef _GSN_DTLS_CLIENT_FPT_H_
#define _GSN_DTLS_CLIENT_FPT_H_
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
* File Inclusion
*****************************************************************************/


typedef DTLS_CORE_T *(*DTLS_CLIENT_INIT_FP_T)( void* ctx );


typedef int (*DTLS_CLIENT_SET_CRED_FP_T)( DTLS_CORE_T *conn, struct tlsv1_credentials *cred );


typedef int (*DTLS_CLIENT_ESTABLISHED_FP_T)( DTLS_CORE_T *conn);


typedef int (*DTLS_CLIENT_HELLO_EXT_FP_T)( DTLS_CORE_T *conn, int ext_type,
    const u8 *data, size_t data_len);

typedef UINT8 * (*DTLS_CLIENT_HANDSHAKE_FP_T)( DTLS_CORE_T *conn,
    const UINT8 *in_data, size_t in_len, size_t *out_len );

typedef void (*DTLS_CLIENT_DEINIT_FP_T)( DTLS_CORE_T *conn);

typedef UINT8 * (*DTLS_SEND_CLIENT_HELLO_FP_T)( DTLS_CORE_T *conn, size_t *out_len, 
    UINT8 *cookie, UINT16 cookieLen );

typedef int (*DTLS_CLIENT_PROCESS_HANDSHAKE_FP_T)(DTLS_CORE_T *conn, UINT8 ct,
    UINT8 *buf, size_t *len );

typedef int (*DTLS_PROCESS_SERVER_HELLO_VERIFY_FP_T)(DTLS_CORE_T *conn, UINT8 ct,
    const UINT8 *in_data, size_t *in_len );

typedef int (*DTLS_PROCESS_SERVER_HELLO_FP_T)(DTLS_CORE_T *conn, UINT8 ct,
                    const UINT8 *in_data, size_t *IN_LEN);

typedef int (*DTLS_PROCESS_CERTIFICATE_FP_T)(DTLS_CORE_T *conn, UINT8 ct,
    const UINT8 *in_data, size_t *in_len);

typedef int (*DTLS_PROCESS_SERVER_KEY_EXCHANGE_FP_T)(DTLS_CORE_T *conn, UINT8 ct,
    const UINT8 *in_data, size_t *in_len);

typedef int (*DTLS_PROCESS_CERTIFICATE_REQUEST_FP_T)(DTLS_CORE_T *conn, UINT8 ct,
    const UINT8 *in_data, size_t *in_len);

typedef int (*DTLS_PROCESS_SERVER_HELLO_DONE_FP_T)(DTLS_CORE_T *conn, UINT8 ct,
    const UINT8 *in_data, size_t *in_len);

typedef int (*DTLS_PROCESS_SERVER_CHANGE_CIPHER_SPEC_FP_T)(DTLS_CORE_T *conn,
    UINT8 ct, const UINT8 *in_data, size_t *in_len);

typedef int (*DTLS_PROCESS_SERVER_FINISHED_FP_T)(DTLS_CORE_T *conn, UINT8 ct,
    const UINT8 *in_data, size_t *in_len);

typedef int (*DTLS_PROCESS_APPLICATION_DATA_FP_T)(DTLS_CORE_T *conn, UINT8 ct,
                    const UINT8 *in_data, size_t *in_len,
                    UINT8 **out_data, size_t *out_len);

typedef UINT8 * (*DTLS_CLIENT_HANDSHAKE_WRITE_FP_T)(DTLS_CORE_T *conn, size_t *out_len,
    int no_appl_data);

typedef UINT8 * (*DTLS_SEND_CLIENT_KEY_EXCHANGE_FP_T)(DTLS_CORE_T *conn,
    size_t *out_len);

typedef UINT8 * (*DTLS_SEND_CHANGE_CIPHER_SPEC_FP_T)(DTLS_CORE_T *conn,
    size_t *out_len);

typedef int (*DTLS_WRITE_CLIENT_KEY_EXCHANGE_FP_T)(DTLS_CORE_T *conn,  pkt_info_t *info );

typedef int (*DTLS_WRITE_CLIENT_CERTIFICATE_VERIFY_FP_T)(DTLS_CORE_T *conn, pkt_info_t *info );

typedef int (*DTLS_WRITE_CLIENT_CHANGE_CIPHER_SPEC_FP_T)(DTLS_CORE_T *conn, 
        pkt_info_t *info );

typedef int (*DTLS_WRITE_CLIENT_FINISHED_FP_T)(DTLS_CORE_T *conn, pkt_info_t *info );

typedef int (*DTLS_WRITE_CLIENT_CERTIFICATE_FP_T)(DTLS_CORE_T *conn, pkt_info_t *info );

typedef int (*DTLS_KEY_X_ANON_DH_FP_T)(DTLS_CORE_T *conn, u8 **pos, u8 *end);

typedef int (*DTLS_DERIVE_PRE_MASTER_SECRET_FP_T)(u8 *pre_master_secret);

typedef int (*DTLS_KEY_X_RSA_FP_T)(DTLS_CORE_T *conn, u8 **pos, u8 *end);

typedef u8 * (*DTLS_CLIENT_SEND_ALERT_FP_T)(DTLS_CORE_T *conn, u8 level,
                 u8 description, size_t *out_len);

typedef void (*DTLS_CLIENT_FREE_DH_FP_T)(DTLS_CORE_T *conn);

typedef int (*DTLS_DERIVE_KEYS_FP_T)(DTLS_CORE_T *conn,
			   const u8 *pre_master_secret,
			   size_t pre_master_secret_len);

typedef size_t (*DTLS_CLIENT_CERT_CHAIN_DER_LEN_FP_T)(DTLS_CORE_T *conn);

typedef int (*DTLS_PROCESS_DIFFIE_HELLMAN_FP_T)(DTLS_CORE_T *conn,
					const u8 *buf, size_t len);

extern _RPST_ DTLS_CLIENT_INIT_FP_T dtls_client_init_FP;


extern _RPST_ DTLS_CLIENT_SET_CRED_FP_T dtls_client_set_cred_FP;


extern _RPST_ DTLS_CLIENT_ESTABLISHED_FP_T dtls_client_established_FP;

extern _RPST_ DTLS_CLIENT_HELLO_EXT_FP_T dtls_client_hello_ext_FP;

extern _RPST_ DTLS_CLIENT_HANDSHAKE_FP_T dtls_client_handshake_FP;


extern _RPST_ DTLS_CLIENT_DEINIT_FP_T dtls_client_deinit_FP;

extern _RPST_ DTLS_SEND_CLIENT_HELLO_FP_T dtls_send_client_hello_FP;

extern _RPST_ DTLS_CLIENT_PROCESS_HANDSHAKE_FP_T dtls_client_process_handshake_FP;

extern _RPST_ DTLS_PROCESS_SERVER_HELLO_VERIFY_FP_T dtls_process_server_hello_verify_FP;

extern _RPST_ DTLS_PROCESS_SERVER_HELLO_FP_T dtls_process_server_hello_FP;

extern _RPST_ DTLS_PROCESS_CERTIFICATE_FP_T dtls_process_certificate_FP;

extern _RPST_ DTLS_PROCESS_SERVER_KEY_EXCHANGE_FP_T dtls_process_server_key_exchange_FP;

extern _RPST_ DTLS_PROCESS_CERTIFICATE_REQUEST_FP_T dtls_process_certificate_request_FP;

extern _RPST_ DTLS_PROCESS_SERVER_HELLO_DONE_FP_T dtls_process_server_hello_done_FP;

extern _RPST_ DTLS_PROCESS_SERVER_CHANGE_CIPHER_SPEC_FP_T dtls_process_server_change_cipher_spec_FP;

extern _RPST_ DTLS_PROCESS_SERVER_FINISHED_FP_T dtls_process_server_finished_FP;

extern _RPST_ DTLS_PROCESS_APPLICATION_DATA_FP_T dtls_process_application_data_FP;

extern _RPST_ DTLS_CLIENT_HANDSHAKE_WRITE_FP_T dtls_client_handshake_write_FP;

extern _RPST_ DTLS_SEND_CLIENT_KEY_EXCHANGE_FP_T dtls_send_client_key_exchange_FP;

extern _RPST_ DTLS_SEND_CHANGE_CIPHER_SPEC_FP_T dtls_send_change_cipher_spec_FP;

extern _RPST_ DTLS_WRITE_CLIENT_KEY_EXCHANGE_FP_T dtls_write_client_key_exchange_FP;

extern _RPST_ DTLS_WRITE_CLIENT_CERTIFICATE_VERIFY_FP_T dtls_write_client_certificate_verify_FP;

extern _RPST_ DTLS_WRITE_CLIENT_CHANGE_CIPHER_SPEC_FP_T dtls_write_client_change_cipher_spec_FP;

extern _RPST_ DTLS_WRITE_CLIENT_FINISHED_FP_T dtls_write_client_finished_FP;

extern _RPST_ DTLS_WRITE_CLIENT_CERTIFICATE_FP_T dtls_write_client_certificate_FP;

extern _RPST_ DTLS_KEY_X_ANON_DH_FP_T dtls_key_x_anon_dh_FP;

extern _RPST_ DTLS_DERIVE_PRE_MASTER_SECRET_FP_T dtls_derive_pre_master_secret_FP;

extern _RPST_ DTLS_KEY_X_RSA_FP_T dtls_key_x_rsa_FP;

extern _RPST_ DTLS_CLIENT_SEND_ALERT_FP_T dtls_client_send_alert_FP;

extern _RPST_ DTLS_CLIENT_FREE_DH_FP_T dtls_client_free_dh_FP;

extern _RPST_ DTLS_DERIVE_KEYS_FP_T dtls_derive_keys_FP;

extern _RPST_ DTLS_CLIENT_CERT_CHAIN_DER_LEN_FP_T dtls_client_cert_chain_der_len_FP;

extern _RPST_ DTLS_PROCESS_DIFFIE_HELLMAN_FP_T dtls_process_diffie_hellman_FP;

#ifdef __cplusplus
}
#endif        
#endif /* _GSN_DTLS_CLIENT_FPT_H_ */
