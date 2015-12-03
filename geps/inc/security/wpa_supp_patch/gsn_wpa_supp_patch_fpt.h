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
* $RCSfile: gsn_wpa_supp_patch_fpt.h,v $
*
* Description : This file contains the interfacing APIs and declaration that is
* used to interface with the WPA opwn source code.
*******************************************************************************/
#ifndef _GSN_WPA_SUPP_PATCH_FPT_
#define _GSN_WPA_SUPP_PATCH_FPT_
/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"

#include "supplicant/utils/includes.h"
#include "supplicant/utils/common.h"
#include "supplicant/common/defs.h"

/**
 *******************************************************************************
 * @file gsn_wpaif.h
 * @brief GSN WPAIF module.
 *      This file contains the WPAIF specific definitions.
 ******************************************************************************/
typedef struct rsn_pmksa_cache *
(*pmksa_cache_auth_init_FP_T)(void (*free_cb)(struct rsn_pmksa_cache_entry *entry,
				      void *ctx), void *ctx);
extern _RPST_ pmksa_cache_auth_init_FP_T pmksa_cache_auth_init_FP;

typedef void (*pmksa_cache_auth_deinit_FP_T)(struct rsn_pmksa_cache *pmksa);
extern _RPST_ pmksa_cache_auth_deinit_FP_T pmksa_cache_auth_deinit_FP;

typedef struct rsn_pmksa_cache_entry *
(*pmksa_cache_auth_get_FP_T)(struct rsn_pmksa_cache *pmksa,
		     const u8 *spa, const u8 *pmkid);
extern _RPST_ pmksa_cache_auth_get_FP_T pmksa_cache_auth_get_FP;

typedef struct rsn_pmksa_cache_entry * (*pmksa_cache_get_okc_FP_T)(
	struct rsn_pmksa_cache *pmksa, const u8 *spa, const u8 *aa,
	const u8 *pmkid);
extern _RPST_ pmksa_cache_get_okc_FP_T pmksa_cache_get_okc_FP;

typedef struct rsn_pmksa_cache_entry *
(*pmksa_cache_auth_add_FP_T)(struct rsn_pmksa_cache *pmksa,
		     const u8 *pmk, size_t pmk_len,
		     const u8 *aa, const u8 *spa, int session_timeout,
		     struct eapol_state_machine *eapol, int akmp);
extern _RPST_ pmksa_cache_auth_add_FP_T pmksa_cache_auth_add_FP;

typedef struct rsn_pmksa_cache_entry *
(*pmksa_cache_add_okc_FP_T)(struct rsn_pmksa_cache *pmksa,
		    const struct rsn_pmksa_cache_entry *old_entry,
		    const u8 *aa, const u8 *pmkid);
extern _RPST_ pmksa_cache_add_okc_FP_T pmksa_cache_add_okc_FP;

typedef void (*pmksa_cache_to_eapol_data_FP_T)(struct rsn_pmksa_cache_entry *entry,
			       struct eapol_state_machine *eapol);
extern _RPST_ pmksa_cache_to_eapol_data_FP_T pmksa_cache_to_eapol_data_FP;

/****************************/
typedef int (*wpa_validate_wpa_ie_FP_T)(struct wpa_authenticator *wpa_auth,
			struct wpa_state_machine *sm,
			const u8 *wpa_ie, size_t wpa_ie_len,
			const u8 *mdie, size_t mdie_len);
extern _RPST_ wpa_validate_wpa_ie_FP_T wpa_validate_wpa_ie_FP;

typedef int (*wpa_auth_uses_mfp_FP_T)(struct wpa_state_machine *sm);
extern _RPST_ wpa_auth_uses_mfp_FP_T wpa_auth_uses_mfp_FP;

typedef struct wpa_state_machine *
(*wpa_auth_sta_init_FP_T)(struct wpa_authenticator *wpa_auth, const u8 *addr);
extern _RPST_ wpa_auth_sta_init_FP_T wpa_auth_sta_init_FP;

typedef int (*wpa_auth_sta_associated_FP_T)(struct wpa_authenticator *wpa_auth,
			    struct wpa_state_machine *sm);
extern _RPST_ wpa_auth_sta_associated_FP_T wpa_auth_sta_associated_FP;

typedef void (*wpa_auth_sta_no_wpa_FP_T)(struct wpa_state_machine *sm);
extern _RPST_ wpa_auth_sta_no_wpa_FP_T wpa_auth_sta_no_wpa_FP;

typedef void (*wpa_auth_sta_deinit_FP_T)(struct wpa_state_machine *sm);
extern _RPST_ wpa_auth_sta_deinit_FP_T wpa_auth_sta_deinit_FP;

typedef void (*wpa_receive_FP_T)(struct wpa_authenticator *wpa_auth,
		 struct wpa_state_machine *sm,
		 u8 *data, size_t data_len);
extern _RPST_ wpa_receive_FP_T wpa_receive_FP;

typedef void (*wpa_remove_ptk_FP_T)(struct wpa_state_machine *sm);
extern _RPST_ wpa_remove_ptk_FP_T wpa_remove_ptk_FP;

typedef int (*wpa_auth_sm_event_FP_T)(struct wpa_state_machine *sm, int event);
extern _RPST_ wpa_auth_sm_event_FP_T wpa_auth_sm_event_FP;

typedef void (*wpa_auth_sm_notify_FP_T)(struct wpa_state_machine *sm);
extern _RPST_ wpa_auth_sm_notify_FP_T wpa_auth_sm_notify_FP;

typedef void (*wpa_gtk_rekey_FP_T)(struct wpa_authenticator *wpa_auth);
extern _RPST_ wpa_gtk_rekey_FP_T wpa_gtk_rekey_FP;

typedef int (*wpa_get_mib_FP_T)(struct wpa_authenticator *wpa_auth, char *buf, size_t buflen);
extern _RPST_ wpa_get_mib_FP_T wpa_get_mib_FP;

typedef int (*wpa_get_mib_sta_FP_T)(struct wpa_state_machine *sm, char *buf, size_t buflen);
extern _RPST_ wpa_get_mib_sta_FP_T wpa_get_mib_sta_FP;

typedef u8 *(* wpa_sm_write_assoc_resp_ies_FP_T)(struct wpa_state_machine *sm, u8 *pos,
				 size_t max_len, int auth_alg,
				 const u8 *req_ies, size_t req_ies_len);
extern _RPST_ wpa_sm_write_assoc_resp_ies_FP_T wpa_sm_write_assoc_resp_ies_FP;

typedef void (*wpa_ft_process_auth_FP_T)(struct wpa_state_machine *sm, const u8 *bssid,
			 u16 auth_transaction, const u8 *ies, size_t ies_len,
			 void (*cb)(void *ctx, const u8 *dst, const u8 *bssid,
				    u16 auth_transaction, u16 resp,
				    const u8 *ies, size_t ies_len),
			 void *ctx);
extern _RPST_ wpa_ft_process_auth_FP_T wpa_ft_process_auth_FP;

typedef u16 (*wpa_ft_validate_reassoc_FP_T)(struct wpa_state_machine *sm, const u8 *ies,
			    size_t ies_len);
extern _RPST_ wpa_ft_validate_reassoc_FP_T wpa_ft_validate_reassoc_FP;

typedef int (*wpa_ft_action_rx_FP_T)(struct wpa_state_machine *sm, const u8 *data, size_t len);
extern _RPST_ wpa_ft_action_rx_FP_T wpa_ft_action_rx_FP;

typedef int (*wpa_ft_rrb_rx_FP_T)(struct wpa_authenticator *wpa_auth, const u8 *src_addr,
		  const u8 *data, size_t data_len);
extern _RPST_ wpa_ft_rrb_rx_FP_T wpa_ft_rrb_rx_FP; 

typedef void (*wpa_ft_push_pmk_r1_FP_T)(struct wpa_authenticator *wpa_auth, const u8 *addr);
extern _RPST_ wpa_ft_push_pmk_r1_FP_T wpa_ft_push_pmk_r1_FP;


/***********************/

typedef const u8 * (*eap_hdr_validate_FP_T)(int vendor, int eap_type,
			    const struct wpabuf *msg, size_t *plen);
extern _RPST_ eap_hdr_validate_FP_T eap_hdr_validate_FP;

typedef struct wpabuf * (*eap_msg_alloc_FP_T)(int vendor, int type, size_t payload_len,
			      u8 code, u8 identifier);
extern _RPST_ eap_msg_alloc_FP_T eap_msg_alloc_FP;

typedef void (*eap_update_len_FP_T)(struct wpabuf *msg);
extern _RPST_ eap_update_len_FP_T eap_update_len_FP;

typedef u8 (*eap_get_id_FP_T)(const struct wpabuf *msg);
extern _RPST_ eap_get_id_FP_T eap_get_id_FP;

typedef int (*eap_get_type_FP_T)(const struct wpabuf *msg);
extern _RPST_ eap_get_type_FP_T eap_get_type_FP;

typedef int (*eap_peer_fast_register_FP_T)(void);
extern _RPST_ eap_peer_fast_register_FP_T eap_peer_fast_register_FP;



typedef void (*eap_fast_free_pac_FP_T)(struct eap_fast_pac *pac);
extern _RPST_ eap_fast_free_pac_FP_T eap_fast_free_pac_FP;

typedef struct eap_fast_pac * (*eap_fast_get_pac_FP_T)(struct eap_fast_pac *pac_root,
				       const u8 *a_id, size_t a_id_len,
				       u16 pac_type);
extern _RPST_ eap_fast_get_pac_FP_T eap_fast_get_pac_FP;

typedef int (*eap_fast_add_pac_FP_T)(struct eap_fast_pac **pac_root,
		     struct eap_fast_pac **pac_current,
		     struct eap_fast_pac *entry);
extern _RPST_ eap_fast_add_pac_FP_T eap_fast_add_pac_FP;

typedef int (*eap_fast_load_pac_FP_T)(struct eap_sm *sm, struct eap_fast_pac **pac_root,
		      const char *pac_file);
extern _RPST_ eap_fast_load_pac_FP_T eap_fast_load_pac_FP;

typedef int (*eap_fast_save_pac_FP_T)(struct eap_sm *sm, struct eap_fast_pac *pac_root,
		      const char *pac_file);
extern _RPST_ eap_fast_save_pac_FP_T eap_fast_save_pac_FP;

typedef size_t (*eap_fast_pac_list_truncate_FP_T)(struct eap_fast_pac *pac_root,
				  size_t max_len);
extern _RPST_ eap_fast_pac_list_truncate_FP_T eap_fast_pac_list_truncate_FP;

typedef int (*eap_fast_load_pac_bin_FP_T)(struct eap_sm *sm, struct eap_fast_pac **pac_root,
			  const char *pac_file);
extern _RPST_ eap_fast_load_pac_bin_FP_T eap_fast_load_pac_bin_FP;

typedef int (*eap_fast_save_pac_bin_FP_T)(struct eap_sm *sm, struct eap_fast_pac *pac_root,
			  const char *pac_file);
extern _RPST_ eap_fast_save_pac_bin_FP_T eap_fast_save_pac_bin_FP;


typedef int (*eap_peer_gpsk_register_FP_T)(void);
extern _RPST_ eap_peer_gpsk_register_FP_T eap_peer_gpsk_register_FP;

typedef int (*eap_peer_gtc_register_FP_T)(void);
extern _RPST_ eap_peer_gtc_register_FP_T eap_peer_gtc_register_FP;

typedef int (*eap_peer_ikev2_register_FP_T)(void);
extern _RPST_ eap_peer_ikev2_register_FP_T eap_peer_ikev2_register_FP;

typedef int (*eap_peer_leap_register_FP_T)(void);
extern _RPST_ eap_peer_leap_register_FP_T eap_peer_leap_register_FP;

typedef int (*eap_peer_md5_register_FP_T)(void);
extern _RPST_ eap_peer_md5_register_FP_T eap_peer_md5_register_FP;

typedef int (*eap_peer_mschapv2_register_FP_T)(void);
extern _RPST_ eap_peer_mschapv2_register_FP_T eap_peer_mschapv2_register_FP;

typedef int (*eap_peer_otp_register_FP_T)(void);
extern _RPST_ eap_peer_otp_register_FP_T eap_peer_otp_register_FP;

typedef int (*eap_peer_pax_register_FP_T)(void);
extern _RPST_ eap_peer_pax_register_FP_T eap_peer_pax_register_FP;

typedef int (*eap_peer_peap_register_FP_T)(void);
extern _RPST_ eap_peer_peap_register_FP_T eap_peer_peap_register_FP;

typedef int (*eap_peer_psk_register_FP_T)(void);
extern _RPST_ eap_peer_psk_register_FP_T eap_peer_psk_register_FP;

typedef int (*eap_peer_sake_register_FP_T)(void);
extern _RPST_ eap_peer_sake_register_FP_T eap_peer_sake_register_FP;

typedef int (*eap_peer_sim_register_FP_T)(void);
extern _RPST_ eap_peer_sim_register_FP_T eap_peer_sim_register_FP;

typedef int (*eap_peer_tls_register_FP_T)(void);
extern _RPST_ eap_peer_tls_register_FP_T eap_peer_tls_register_FP;

typedef int (*eap_peer_ttls_register_FP_T)(void);
extern _RPST_ eap_peer_ttls_register_FP_T eap_peer_ttls_register_FP;

typedef int (*eap_peer_vendor_test_register_FP_T)(void);
extern _RPST_ eap_peer_vendor_test_register_FP_T eap_peer_vendor_test_register_FP;

typedef int (*eap_peer_wsc_register_FP_T)(void);
extern _RPST_ eap_peer_wsc_register_FP_T eap_peer_wsc_register_FP;
/***************/
typedef const struct eap_method * (*eap_peer_get_eap_method_FP_T)(int vendor, int method);
extern _RPST_ eap_peer_get_eap_method_FP_T eap_peer_get_eap_method_FP;

typedef const struct eap_method * (*eap_peer_get_methods_FP_T)(size_t *count);
extern _RPST_ eap_peer_get_methods_FP_T eap_peer_get_methods_FP;

typedef struct eap_method * (*eap_peer_method_alloc_FP_T)(int version, int vendor,
					  int method, const char *name);
extern _RPST_ eap_peer_method_alloc_FP_T eap_peer_method_alloc_FP;

typedef void (*eap_peer_method_free_FP_T)(struct eap_method *method);
extern _RPST_ eap_peer_method_free_FP_T eap_peer_method_free_FP;

typedef int (*eap_peer_method_register_FP_T)(struct eap_method *method);
extern _RPST_ eap_peer_method_register_FP_T eap_peer_method_register_FP;

typedef int (*eap_peer_get_type_FP_T)(const char *name, int *vendor);
extern _RPST_ eap_peer_get_type_FP_T eap_peer_get_type_FP;

typedef const char * (*eap_get_name_FP_T)(int vendor, int type);
extern _RPST_ eap_get_name_FP_T eap_get_name_FP;

typedef size_t (*eap_get_names_FP_T)(char *buf, size_t buflen);
extern _RPST_ eap_get_names_FP_T eap_get_names_FP;

typedef char ** (*eap_get_names_as_string_array_FP_T)(size_t *num);
extern _RPST_ eap_get_names_as_string_array_FP_T eap_get_names_as_string_array_FP;

typedef void (*eap_peer_unregister_methods_FP_T)(void);
extern _RPST_ eap_peer_unregister_methods_FP_T eap_peer_unregister_methods_FP;


/***********/
typedef int (*eap_peer_tls_ssl_init_FP_T)(struct eap_sm *sm, struct eap_ssl_data *data,
			  struct eap_peer_config *config);
extern _RPST_ eap_peer_tls_ssl_init_FP_T eap_peer_tls_ssl_init_FP;

typedef void (*eap_peer_tls_ssl_deinit_FP_T)(struct eap_sm *sm, struct eap_ssl_data *data);
extern _RPST_ eap_peer_tls_ssl_deinit_FP_T eap_peer_tls_ssl_deinit_FP;

typedef u8 * (*eap_peer_tls_derive_key_FP_T)(struct eap_sm *sm, struct eap_ssl_data *data,
			     const char *label, size_t len);
extern _RPST_ eap_peer_tls_derive_key_FP_T eap_peer_tls_derive_key_FP;

typedef int (*eap_peer_tls_process_helper_FP_T)(struct eap_sm *sm, struct eap_ssl_data *data,
				int eap_type, int peap_version,
				u8 id, const u8 *in_data, size_t in_len,
				struct wpabuf **out_data);
extern _RPST_ eap_peer_tls_process_helper_FP_T eap_peer_tls_process_helper_FP;

typedef struct wpabuf * (*eap_peer_tls_build_ack_FP_T)(u8 id, int eap_type,
				       int peap_version);
extern _RPST_ eap_peer_tls_build_ack_FP_T eap_peer_tls_build_ack_FP;

typedef int (*eap_peer_tls_reauth_init_FP_T)(struct eap_sm *sm, struct eap_ssl_data *data);
extern _RPST_ eap_peer_tls_reauth_init_FP_T eap_peer_tls_reauth_init_FP;

typedef int (*eap_peer_tls_status_FP_T)(struct eap_sm *sm, struct eap_ssl_data *data,
			char *buf, size_t buflen, int verbose);
extern _RPST_ eap_peer_tls_status_FP_T eap_peer_tls_status_FP;

typedef const u8 * (*eap_peer_tls_process_init_FP_T)(struct eap_sm *sm,
				     struct eap_ssl_data *data,
				     int eap_type,
				     struct eap_method_ret *ret,
				     const struct wpabuf *reqData,
				     size_t *len, u8 *flags);
extern _RPST_ eap_peer_tls_process_init_FP_T eap_peer_tls_process_init_FP;

typedef void (*eap_peer_tls_reset_input_FP_T)(struct eap_ssl_data *data);
extern _RPST_ eap_peer_tls_reset_input_FP_T eap_peer_tls_reset_input_FP;

typedef void (*eap_peer_tls_reset_output_FP_T)(struct eap_ssl_data *data);
extern _RPST_ eap_peer_tls_reset_output_FP_T eap_peer_tls_reset_output_FP;

typedef int (*eap_peer_tls_decrypt_FP_T)(struct eap_sm *sm, struct eap_ssl_data *data,
			 const struct wpabuf *in_data,
			 struct wpabuf **in_decrypted);
extern _RPST_ eap_peer_tls_decrypt_FP_T eap_peer_tls_decrypt_FP;

typedef int (*eap_peer_tls_encrypt_FP_T)(struct eap_sm *sm, struct eap_ssl_data *data,
			 int eap_type, int peap_version, u8 id,
			 const struct wpabuf *in_data,
			 struct wpabuf **out_data);
extern _RPST_ eap_peer_tls_encrypt_FP_T eap_peer_tls_encrypt_FP;

typedef int (*eap_peer_select_phase2_methods_FP_T)(struct eap_peer_config *config,
				   const char *prefix,
				   struct eap_method_type **types,
				   size_t *num_types);
extern _RPST_ eap_peer_select_phase2_methods_FP_T eap_peer_select_phase2_methods_FP;

typedef int (*eap_peer_tls_phase2_nak_FP_T)(struct eap_method_type *types, size_t num_types,
			    struct eap_hdr *hdr, struct wpabuf **resp);
extern _RPST_ eap_peer_tls_phase2_nak_FP_T eap_peer_tls_phase2_nak_FP;

/************/
typedef int (*tlsv12_prf_FP_T)(const u8 *secret, size_t secret_len, const char *label,
	    const u8 *seed, size_t seed_len, u8 *out, size_t outlen);
extern _RPST_ tlsv12_prf_FP_T tlsv12_prf_FP;

typedef u8 * (*tls_send_client_hello_FP_T)(struct tlsv1_client *conn, size_t *out_len);
extern _RPST_ tls_send_client_hello_FP_T tls_send_client_hello_FP;

typedef int (*tls_derive_keys_FP_T)(struct tlsv1_client *conn,
		    const u8 *pre_master_secret, size_t pre_master_secret_len);
extern _RPST_ tls_derive_keys_FP_T tls_derive_keys_FP;

typedef int (*tls_derive_pre_master_secret_FP_T)(u8 *pre_master_secret);
extern _RPST_ tls_derive_pre_master_secret_FP_T tls_derive_pre_master_secret_FP;

typedef void (*tlsv1_client_free_dh_FP_T)(struct tlsv1_client *conn);
extern _RPST_ tlsv1_client_free_dh_FP_T tlsv1_client_free_dh_FP;

typedef int (*tls_process_server_hello_FP_T)(struct tlsv1_client *conn, u8 ct,
				    const u8 *in_data, size_t *in_len);
extern _RPST_ tls_process_server_hello_FP_T tls_process_server_hello_FP;

typedef int (*tls_client_process_certificate_FP_T)(struct tlsv1_client *conn, u8 ct,
				   const u8 *in_data, size_t *in_len);
extern _RPST_ tls_client_process_certificate_FP_T tls_client_process_certificate_FP;

typedef int (*tls_process_server_hello_done_FP_T)(struct tlsv1_client *conn, u8 ct,
					 const u8 *in_data, size_t *in_len);
extern _RPST_ tls_process_server_hello_done_FP_T tls_process_server_hello_done_FP;

typedef int (*tls_process_server_change_cipher_spec_FP_T)(struct tlsv1_client *conn,
						 u8 ct, const u8 *in_data,
						 size_t *in_len);
extern _RPST_ tls_process_server_change_cipher_spec_FP_T tls_process_server_change_cipher_spec_FP;

typedef int (*tlsv1_process_diffie_hellman_FP_T)(struct tlsv1_client *conn,
					const u8 *buf, size_t len);
extern _RPST_ tlsv1_process_diffie_hellman_FP_T tlsv1_process_diffie_hellman_FP;


typedef int (*tls_process_server_finished_FP_T)(struct tlsv1_client *conn, u8 ct,
				       const u8 *in_data, size_t *in_len);
extern _RPST_ tls_process_server_finished_FP_T tls_process_server_finished_FP;

typedef int (*tls_process_application_data_FP_T)(struct tlsv1_client *conn, u8 ct,
					const u8 *in_data, size_t *in_len,
					u8 **out_data, size_t *out_len);
extern _RPST_ tls_process_application_data_FP_T tls_process_application_data_FP;

typedef int (*tlsv1_client_process_handshake_FP_T)(struct tlsv1_client *conn, u8 ct,
				   const u8 *buf, size_t *len,
				   u8 **out_data, size_t *out_len);
extern _RPST_ tlsv1_client_process_handshake_FP_T tlsv1_client_process_handshake_FP;

typedef int (*tls_process_server_key_exchange_FP_T)(struct tlsv1_client *conn, u8 ct,
					   const u8 *in_data, size_t *in_len);
extern _RPST_ tls_process_server_key_exchange_FP_T tls_process_server_key_exchange_FP;

typedef int (*tls_process_certificate_request_FP_T)(struct tlsv1_client *conn, u8 ct,
					   const u8 *in_data, size_t *in_len);
extern _RPST_ tls_process_certificate_request_FP_T tls_process_certificate_request_FP;

typedef int (*tls_write_client_certificate_FP_T)(struct tlsv1_client *conn,u8 **msgpos, u8 *end);
extern _RPST_ tls_write_client_certificate_FP_T tls_write_client_certificate_FP;

typedef int (*tlsv1_key_x_anon_dh_FP_T)(struct tlsv1_client *conn, u8 **pos, u8 *end);
extern _RPST_ tlsv1_key_x_anon_dh_FP_T tlsv1_key_x_anon_dh_FP;

typedef int (*tlsv1_key_x_rsa_FP_T)(struct tlsv1_client *conn, u8 **pos, u8 *end);
extern _RPST_ tlsv1_key_x_rsa_FP_T tlsv1_key_x_rsa_FP;

typedef int (*tls_write_client_key_exchange_FP_T)(struct tlsv1_client *conn,u8 **msgpos, u8 *end);
extern _RPST_ tls_write_client_key_exchange_FP_T tls_write_client_key_exchange_FP;

typedef int (*tls_write_client_certificate_verify_FP_T)(struct tlsv1_client *conn,u8 **msgpos, u8 *end);
extern _RPST_ tls_write_client_certificate_verify_FP_T tls_write_client_certificate_verify_FP;

typedef int (*tls_write_client_change_cipher_spec_FP_T)(struct tlsv1_client *conn,u8 **msgpos, u8 *end);
extern _RPST_ tls_write_client_change_cipher_spec_FP_T tls_write_client_change_cipher_spec_FP;

typedef int (*tls_write_client_finished_FP_T)(struct tlsv1_client *conn,u8 **msgpos, u8 *end);
extern _RPST_ tls_write_client_finished_FP_T tls_write_client_finished_FP;

typedef u8 * (*tls_send_client_key_exchange_FP_T)(struct tlsv1_client *conn,size_t *out_len);
extern _RPST_ tls_send_client_key_exchange_FP_T tls_send_client_key_exchange_FP;

typedef u8 * (*tls_client_send_change_cipher_spec_FP_T)(struct tlsv1_client *conn,size_t *out_len);
extern _RPST_ tls_client_send_change_cipher_spec_FP_T tls_client_send_change_cipher_spec_FP;

typedef u8 * (*tlsv1_client_handshake_write_FP_T)(struct tlsv1_client *conn, size_t *out_len,int no_appl_data);
extern _RPST_ tlsv1_client_handshake_write_FP_T tlsv1_client_handshake_write_FP;

typedef u8 * (*tlsv1_client_send_alert_FP_T)(struct tlsv1_client *conn, u8 level,u8 description, size_t *out_len);
extern _RPST_ tlsv1_client_send_alert_FP_T tlsv1_client_send_alert_FP;

typedef const struct tls_cipher_suite * (*tls_get_cipher_suite_FP_T)(u16 suite);
extern _RPST_ tls_get_cipher_suite_FP_T tls_get_cipher_suite_FP;

typedef struct tlsv1_credentials * (*tlsv1_cred_alloc_FP_T)(void);
extern _RPST_ tlsv1_cred_alloc_FP_T tlsv1_cred_alloc_FP;

typedef void (*tlsv1_cred_free_FP_T)(struct tlsv1_credentials *cred);
extern _RPST_ tlsv1_cred_free_FP_T tlsv1_cred_free_FP;

typedef int (*tlsv1_add_cert_der_FP_T)(struct x509_certificate **chain,const u8 *buf, size_t len);
extern _RPST_ tlsv1_add_cert_der_FP_T tlsv1_add_cert_der_FP;

typedef const u8 * (*search_tag_FP_T)(const char *tag, const u8 *buf, size_t len);
extern _RPST_ search_tag_FP_T search_tag_FP;

typedef int (*tlsv1_add_cert_FP_T)(struct x509_certificate **chain,const u8 *buf, size_t len);
extern _RPST_ tlsv1_add_cert_FP_T tlsv1_add_cert_FP;

typedef int (*tlsv1_set_cert_chain_FP_T)(struct x509_certificate **chain,const char *cert, const u8 *cert_blob,size_t cert_blob_len);
extern _RPST_ tlsv1_set_cert_chain_FP_T tlsv1_set_cert_chain_FP;

typedef int (*tlsv1_set_ca_cert_FP_T)(struct tlsv1_credentials *cred, const char *cert,
		      const u8 *cert_blob, size_t cert_blob_len,
		      const char *path);
extern _RPST_ tlsv1_set_ca_cert_FP_T tlsv1_set_ca_cert_FP;

typedef struct crypto_private_key * (*tlsv1_set_key_pem_FP_T)(const u8 *key, size_t len);
extern _RPST_ tlsv1_set_key_pem_FP_T tlsv1_set_key_pem_FP;

typedef struct crypto_private_key * (*tlsv1_set_key_enc_pem_FP_T)(const u8 *key,
							 size_t len,
							 const char *passwd);
extern _RPST_ tlsv1_set_key_enc_pem_FP_T tlsv1_set_key_enc_pem_FP;

typedef int (*tlsv1_set_key_FP_T)(struct tlsv1_credentials *cred,
			 const u8 *key, size_t len, const char *passwd);
extern _RPST_ tlsv1_set_key_FP_T tlsv1_set_key_FP;

typedef int (*tlsv1_set_private_key_FP_T)(struct tlsv1_credentials *cred,
			  const char *private_key,
			  const char *private_key_passwd,
			  const u8 *private_key_blob,
			  size_t private_key_blob_len);
extern _RPST_ tlsv1_set_private_key_FP_T tlsv1_set_private_key_FP;

typedef int (*tlsv1_set_dhparams_der_FP_T)(struct tlsv1_credentials *cred,
				  const u8 *dh, size_t len);
extern _RPST_ tlsv1_set_dhparams_der_FP_T tlsv1_set_dhparams_der_FP;

typedef int (*tlsv1_set_dhparams_blob_FP_T)(struct tlsv1_credentials *cred,
				   const u8 *buf, size_t len);
extern _RPST_ tlsv1_set_dhparams_blob_FP_T tlsv1_set_dhparams_blob_FP;

typedef int (*tlsv1_set_dhparams_FP_T)(struct tlsv1_credentials *cred, const char *dh_file,
		       const u8 *dh_blob, size_t dh_blob_len);
extern _RPST_ tlsv1_set_dhparams_FP_T tlsv1_set_dhparams_FP;

typedef int (*tlsv1_record_set_cipher_suite_FP_T)(struct tlsv1_record_layer *rl,
				  u16 cipher_suite);
extern _RPST_ tlsv1_record_set_cipher_suite_FP_T tlsv1_record_set_cipher_suite_FP;

typedef int (*tlsv1_record_change_write_cipher_FP_T)(struct tlsv1_record_layer *rl);
extern _RPST_ tlsv1_record_change_write_cipher_FP_T tlsv1_record_change_write_cipher_FP;

typedef int (*tlsv1_record_change_read_cipher_FP_T)(struct tlsv1_record_layer *rl);
extern _RPST_ tlsv1_record_change_read_cipher_FP_T tlsv1_record_change_read_cipher_FP;

typedef int (*tlsv1_record_send_FP_T)(struct tlsv1_record_layer *rl, u8 content_type, u8 *buf,
		      size_t buf_size, const u8 *payload, size_t payload_len,
		      size_t *out_len);
extern _RPST_ tlsv1_record_send_FP_T tlsv1_record_send_FP;

typedef int (*tlsv1_record_receive_FP_T)(struct tlsv1_record_layer *rl,
			 const u8 *in_data, size_t in_len,
			 u8 *out_data, size_t *out_len, u8 *alert);
extern _RPST_ tlsv1_record_receive_FP_T tlsv1_record_receive_FP;

typedef int (*tlsv1_server_derive_keys_FP_T)(struct tlsv1_server *conn,
			     const u8 *pre_master_secret,
			     size_t pre_master_secret_len);
extern _RPST_ tlsv1_server_derive_keys_FP_T tlsv1_server_derive_keys_FP;

typedef void (*tlsv1_server_clear_data_FP_T)(struct tlsv1_server *conn);
extern _RPST_ tlsv1_server_clear_data_FP_T tlsv1_server_clear_data_FP;

typedef int (*tlsv1_server_prf_FP_T)(struct tlsv1_server *conn, const char *label,
		     int server_random_first, u8 *out, size_t out_len);
extern _RPST_ tlsv1_server_prf_FP_T tlsv1_server_prf_FP;

typedef int (*tls_process_client_hello_FP_T)(struct tlsv1_server *conn, u8 ct,
				    const u8 *in_data, size_t *in_len);
extern _RPST_ tls_process_client_hello_FP_T tls_process_client_hello_FP;

typedef int (*tls_process_certificate_FP_T)(struct tlsv1_server *conn, u8 ct,
				   const u8 *in_data, size_t *in_len);
extern _RPST_ tls_process_certificate_FP_T tls_process_certificate_FP;

typedef int (*tls_process_client_key_exchange_rsa_FP_T)(
	struct tlsv1_server *conn, const u8 *pos, const u8 *end);
extern _RPST_ tls_process_client_key_exchange_rsa_FP_T tls_process_client_key_exchange_rsa_FP;

typedef int (*tls_process_client_key_exchange_dh_anon_FP_T)(
	struct tlsv1_server *conn, const u8 *pos, const u8 *end);
extern _RPST_ tls_process_client_key_exchange_dh_anon_FP_T tls_process_client_key_exchange_dh_anon_FP;

typedef int (*tls_process_client_key_exchange_FP_T)(struct tlsv1_server *conn, u8 ct,
					   const u8 *in_data, size_t *in_len);
extern _RPST_ tls_process_client_key_exchange_FP_T tls_process_client_key_exchange_FP;

typedef int (*tls_process_certificate_verify_FP_T)(struct tlsv1_server *conn, u8 ct,
					  const u8 *in_data, size_t *in_len);
extern _RPST_ tls_process_certificate_verify_FP_T tls_process_certificate_verify_FP;

typedef int (*tls_process_change_cipher_spec_FP_T)(struct tlsv1_server *conn,
					  u8 ct, const u8 *in_data,
					  size_t *in_len);
extern _RPST_ tls_process_change_cipher_spec_FP_T tls_process_change_cipher_spec_FP;

typedef int (*tls_process_client_finished_FP_T)(struct tlsv1_server *conn, u8 ct,
				       const u8 *in_data, size_t *in_len);
extern _RPST_ tls_process_client_finished_FP_T tls_process_client_finished_FP;

typedef int (*tlsv1_server_process_handshake_FP_T)(struct tlsv1_server *conn, u8 ct,
				   const u8 *buf, size_t *len);
extern _RPST_ tlsv1_server_process_handshake_FP_T tlsv1_server_process_handshake_FP;

typedef size_t (*tls_server_cert_chain_der_len_FP_T)(struct tlsv1_server *conn);
extern _RPST_ tls_server_cert_chain_der_len_FP_T tls_server_cert_chain_der_len_FP;

typedef int (*tls_write_server_hello_FP_T)(struct tlsv1_server *conn,
				  u8 **msgpos, u8 *end);
extern _RPST_ tls_write_server_hello_FP_T tls_write_server_hello_FP;

typedef int (*tls_write_server_certificate_FP_T)(struct tlsv1_server *conn,
					u8 **msgpos, u8 *end);
extern _RPST_ tls_write_server_certificate_FP_T tls_write_server_certificate_FP;

typedef int (*tls_write_server_key_exchange_FP_T)(struct tlsv1_server *conn,
					 u8 **msgpos, u8 *end);
extern _RPST_ tls_write_server_key_exchange_FP_T tls_write_server_key_exchange_FP;

typedef int (*tls_write_server_certificate_request_FP_T)(struct tlsv1_server *conn,
						u8 **msgpos, u8 *end);
extern _RPST_ tls_write_server_certificate_request_FP_T tls_write_server_certificate_request_FP;

typedef int (*tls_write_server_hello_done_FP_T)(struct tlsv1_server *conn,
				       u8 **msgpos, u8 *end);
extern _RPST_ tls_write_server_hello_done_FP_T tls_write_server_hello_done_FP;

typedef int (*tls_write_server_change_cipher_spec_FP_T)(struct tlsv1_server *conn,
					       u8 **msgpos, u8 *end);
extern _RPST_ tls_write_server_change_cipher_spec_FP_T tls_write_server_change_cipher_spec_FP;

typedef int (*tls_write_server_finished_FP_T)(struct tlsv1_server *conn,
				     u8 **msgpos, u8 *end);
extern _RPST_ tls_write_server_finished_FP_T tls_write_server_finished_FP;

typedef u8 * (*tls_send_server_hello_FP_T)(struct tlsv1_server *conn, size_t *out_len);
extern _RPST_ tls_send_server_hello_FP_T tls_send_server_hello_FP;

typedef u8 * (*tls_send_change_cipher_spec_FP_T)(struct tlsv1_server *conn,
					size_t *out_len);
extern _RPST_ tls_send_change_cipher_spec_FP_T tls_send_change_cipher_spec_FP;

typedef u8 * (*tlsv1_server_handshake_write_FP_T)(struct tlsv1_server *conn, size_t *out_len);
extern _RPST_ tlsv1_server_handshake_write_FP_T tlsv1_server_handshake_write_FP;

typedef u8 * (*tlsv1_server_send_alert_FP_T)(struct tlsv1_server *conn, u8 level,
			     u8 description, size_t *out_len);
extern _RPST_ tlsv1_server_send_alert_FP_T tlsv1_server_send_alert_FP;
/*********/

typedef const u8 * (*mschapv2_remove_domain_FP_T)(const u8 *username, size_t *len);
extern _RPST_ mschapv2_remove_domain_FP_T mschapv2_remove_domain_FP;

typedef int (*mschapv2_derive_response_FP_T)(const u8 *username, size_t username_len,
			     const u8 *password, size_t password_len,
			     int pwhash,
			     const u8 *auth_challenge,
			     const u8 *peer_challenge,
			     u8 *nt_response, u8 *auth_response,
			     u8 *master_key);
extern _RPST_ mschapv2_derive_response_FP_T mschapv2_derive_response_FP;

typedef int (*mschapv2_verify_auth_response_FP_T)(const u8 *auth_response,
				  const u8 *buf, size_t buf_len);
extern _RPST_ mschapv2_verify_auth_response_FP_T mschapv2_verify_auth_response_FP;

/***********/
typedef struct eapol_sm *(*eapol_sm_init_FP_T)(struct eapol_ctx *ctx);
extern _RPST_ eapol_sm_init_FP_T eapol_sm_init_FP;

typedef void (*eapol_sm_deinit_FP_T)(struct eapol_sm *sm);
extern _RPST_ eapol_sm_deinit_FP_T eapol_sm_deinit_FP;

typedef int (*eapol_sm_rx_eapol_FP_T)(struct eapol_sm *sm, const u8 *src, const u8 *buf,
		      size_t len);
extern _RPST_ eapol_sm_rx_eapol_FP_T eapol_sm_rx_eapol_FP;

typedef void (*eapol_sm_notify_eap_success_FP_T)(struct eapol_sm *sm, Boolean success);
extern _RPST_ eapol_sm_notify_eap_success_FP_T eapol_sm_notify_eap_success_FP;

typedef void (*eapol_sm_notify_eap_fail_FP_T)(struct eapol_sm *sm, Boolean fail);
extern _RPST_ eapol_sm_notify_eap_fail_FP_T eapol_sm_notify_eap_fail_FP;

typedef void (*eapol_sm_notify_config_FP_T)(struct eapol_sm *sm,
			    struct eap_peer_config *config,
			    const struct eapol_config *conf);
extern _RPST_ eapol_sm_notify_config_FP_T eapol_sm_notify_config_FP;

/**********/
/*
typedef int (*peerkey_verify_eapol_key_mic_FP_T)(struct wpa_sm *sm,
				 struct wpa_peerkey *peerkey,
				 struct wpa_eapol_key *key, u16 ver,
				 const u8 *buf, size_t len);
extern _RPST_ peerkey_verify_eapol_key_mic_FP_T peerkey_verify_eapol_key_mic_FP;
*/
typedef void (*peerkey_rx_eapol_4way_FP_T)(struct wpa_sm *sm, struct wpa_peerkey *peerkey,
			   struct wpa_eapol_key *key, u16 key_info, u16 ver);
extern _RPST_ peerkey_rx_eapol_4way_FP_T peerkey_rx_eapol_4way_FP;

typedef void (*peerkey_rx_eapol_smk_FP_T)(struct wpa_sm *sm, const u8 *src_addr,
			  struct wpa_eapol_key *key, size_t extra_len,
			  u16 key_info, u16 ver);
extern _RPST_ peerkey_rx_eapol_smk_FP_T peerkey_rx_eapol_smk_FP;

typedef void (*peerkey_deinit_FP_T)(struct wpa_sm *sm);
extern _RPST_ peerkey_deinit_FP_T peerkey_deinit_FP;

/**************/
typedef struct rsn_pmksa_cache *
(*pmksa_cache_init_FP_T)(void (*free_cb)(struct rsn_pmksa_cache_entry *entry,
				 void *ctx, int replace),
		 void *ctx, struct wpa_sm *sm);
extern _RPST_ pmksa_cache_init_FP_T pmksa_cache_init_FP;

typedef void (*pmksa_cache_deinit_FP_T)(struct rsn_pmksa_cache *pmksa);
extern _RPST_ pmksa_cache_deinit_FP_T pmksa_cache_deinit_FP;

typedef struct rsn_pmksa_cache_entry * (*pmksa_cache_get_FP_T)(struct rsn_pmksa_cache *pmksa,
					       const u8 *aa, const u8 *pmkid);
extern _RPST_ pmksa_cache_get_FP_T pmksa_cache_get_FP;

typedef int (*pmksa_cache_list_FP_T)(struct rsn_pmksa_cache *pmksa, char *buf, size_t len);
extern _RPST_ pmksa_cache_list_FP_T pmksa_cache_list_FP;

typedef struct rsn_pmksa_cache_entry *
(*pmksa_cache_add_FP_T)(struct rsn_pmksa_cache *pmksa, const u8 *pmk, size_t pmk_len,
		const u8 *aa, const u8 *spa, void *network_ctx, int akmp);
extern _RPST_ pmksa_cache_add_FP_T pmksa_cache_add_FP;

typedef struct rsn_pmksa_cache_entry * (*pmksa_cache_get_current_FP_T)(struct wpa_sm *sm);
extern _RPST_ pmksa_cache_get_current_FP_T pmksa_cache_get_current_FP;

typedef void(* pmksa_cache_clear_current_FP_T)(struct wpa_sm *sm);
extern _RPST_ pmksa_cache_clear_current_FP_T pmksa_cache_clear_current_FP;

typedef int (*pmksa_cache_set_current_FP_T)(struct wpa_sm *sm, const u8 *pmkid,
			    const u8 *bssid, void *network_ctx,
			    int try_opportunistic);
extern _RPST_ pmksa_cache_set_current_FP_T pmksa_cache_set_current_FP;

typedef struct rsn_pmksa_cache_entry *
(*pmksa_cache_get_opportunistic_FP_T)(struct rsn_pmksa_cache *pmksa,
			      void *network_ctx, const u8 *aa);
extern _RPST_ pmksa_cache_get_opportunistic_FP_T pmksa_cache_get_opportunistic_FP;

typedef void (*pmksa_cache_flush_FP_T)(struct rsn_pmksa_cache *pmksa, void *network_ctx);
extern _RPST_ pmksa_cache_flush_FP_T pmksa_cache_flush_FP;

/****************/	
typedef struct wpa_sm * (*wpa_sm_init_FP_T)(struct wpa_sm_ctx *ctx);
extern _RPST_ wpa_sm_init_FP_T wpa_sm_init_FP;

typedef void (*wpa_sm_deinit_FP_T)(struct wpa_sm *sm);
extern _RPST_ wpa_sm_deinit_FP_T wpa_sm_deinit_FP;

typedef void (*wpa_sm_set_pmk_FP_T)(struct wpa_sm *sm, const u8 *pmk, size_t pmk_len);
extern _RPST_ wpa_sm_set_pmk_FP_T wpa_sm_set_pmk_FP;

typedef void (*wpa_sm_set_pmk_from_pmksa_FP_T)(struct wpa_sm *sm);
extern _RPST_ wpa_sm_set_pmk_from_pmksa_FP_T wpa_sm_set_pmk_from_pmksa_FP;

typedef int (*wpa_sm_rx_eapol_FP_T)(struct wpa_sm *sm, const u8 *src_addr,
		    const u8 *buf, size_t len);
extern _RPST_ wpa_sm_rx_eapol_FP_T wpa_sm_rx_eapol_FP;

/***************/
typedef int (*tlsv1_client_global_init_FP_T)(void);
extern _RPST_ tlsv1_client_global_init_FP_T tlsv1_client_global_init_FP;

typedef void (*tlsv1_client_global_deinit_FP_T)(void);
extern _RPST_ tlsv1_client_global_deinit_FP_T tlsv1_client_global_deinit_FP;

typedef struct tlsv1_client * (*tlsv1_client_init_FP_T)(void);
extern _RPST_ tlsv1_client_init_FP_T tlsv1_client_init_FP;

typedef void (*tlsv1_client_deinit_FP_T)(struct tlsv1_client *conn);
extern _RPST_ tlsv1_client_deinit_FP_T tlsv1_client_deinit_FP;

typedef u8 * (*tlsv1_client_handshake_FP_T)(struct tlsv1_client *conn,
			    const u8 *in_data, size_t in_len,
			    size_t *out_len, u8 **appl_data,
			    size_t *appl_data_len);
extern _RPST_ tlsv1_client_handshake_FP_T tlsv1_client_handshake_FP;

typedef int (*tlsv1_client_encrypt_FP_T)(struct tlsv1_client *conn,
			 const u8 *in_data, size_t in_len,
			 u8 *out_data, size_t out_len);
extern _RPST_ tlsv1_client_encrypt_FP_T tlsv1_client_encrypt_FP;

typedef int (*tlsv1_client_decrypt_FP_T)(struct tlsv1_client *conn,
			 const u8 *in_data, size_t in_len,
			 u8 *out_data, size_t out_len);
extern _RPST_ tlsv1_client_decrypt_FP_T tlsv1_client_decrypt_FP;

typedef int (*tlsv1_client_get_cipher_FP_T)(struct tlsv1_client *conn, char *buf,
			    size_t buflen);
extern _RPST_ tlsv1_client_get_cipher_FP_T tlsv1_client_get_cipher_FP;

typedef int (*tlsv1_client_shutdown_FP_T)(struct tlsv1_client *conn);
extern _RPST_ tlsv1_client_shutdown_FP_T tlsv1_client_shutdown_FP;

typedef int (*tlsv1_client_set_cipher_list_FP_T)(struct tlsv1_client *conn, u8 *ciphers);
extern _RPST_ tlsv1_client_set_cipher_list_FP_T tlsv1_client_set_cipher_list_FP;

/*******/

typedef const struct tls_cipher_data * (*tls_get_cipher_data_FP_T)(int cipher);
extern _RPST_ tls_get_cipher_data_FP_T tls_get_cipher_data_FP;

typedef int (*tls_server_key_exchange_allowed_FP_T)(int cipher);
extern _RPST_ tls_server_key_exchange_allowed_FP_T tls_server_key_exchange_allowed_FP;

typedef int (*tls_parse_cert_FP_T)(const u8 *buf, size_t len, struct crypto_public_key **pk);
extern _RPST_ tls_parse_cert_FP_T tls_parse_cert_FP;

typedef int (*tls_verify_hash_init_FP_T)(struct tls_verify_hash *verify);
extern _RPST_ tls_verify_hash_init_FP_T tls_verify_hash_init_FP;

typedef void (*tls_verify_hash_add_FP_T)(struct tls_verify_hash *verify, const u8 *buf,
			 size_t len);
extern _RPST_ tls_verify_hash_add_FP_T tls_verify_hash_add_FP;

typedef void (*tls_verify_hash_free_FP_T)(struct tls_verify_hash *verify);
extern _RPST_ tls_verify_hash_free_FP_T tls_verify_hash_free_FP;

/*************/
typedef int (*tlsv1_server_global_init_FP_T)(void);
extern _RPST_ tlsv1_server_global_init_FP_T tlsv1_server_global_init_FP;

typedef void (*tlsv1_server_global_deinit_FP_T)(void);
extern _RPST_ tlsv1_server_global_deinit_FP_T tlsv1_server_global_deinit_FP;

typedef struct tlsv1_server * (*tlsv1_server_init_FP_T)(struct tlsv1_credentials *cred);
extern _RPST_ tlsv1_server_init_FP_T tlsv1_server_init_FP;

typedef void (*tlsv1_server_deinit_FP_T)(struct tlsv1_server *conn);
extern _RPST_ tlsv1_server_deinit_FP_T tlsv1_server_deinit_FP;

typedef u8 * (*tlsv1_server_handshake_FP_T)(struct tlsv1_server *conn,
			    const u8 *in_data, size_t in_len, size_t *out_len);
extern _RPST_ tlsv1_server_handshake_FP_T tlsv1_server_handshake_FP;

typedef int (*tlsv1_server_encrypt_FP_T)(struct tlsv1_server *conn,
			 const u8 *in_data, size_t in_len,
			 u8 *out_data, size_t out_len);
extern _RPST_ tlsv1_server_encrypt_FP_T tlsv1_server_encrypt_FP;

typedef int (*tlsv1_server_decrypt_FP_T)(struct tlsv1_server *conn,
			 const u8 *in_data, size_t in_len,
			 u8 *out_data, size_t out_len);
extern _RPST_ tlsv1_server_decrypt_FP_T tlsv1_server_decrypt_FP;

typedef int (*tlsv1_server_get_cipher_FP_T)(struct tlsv1_server *conn, char *buf,
			    size_t buflen);
extern _RPST_ tlsv1_server_get_cipher_FP_T tlsv1_server_get_cipher_FP;

typedef int (*tlsv1_server_shutdown_FP_T)(struct tlsv1_server *conn);
extern _RPST_ tlsv1_server_shutdown_FP_T tlsv1_server_shutdown_FP;

typedef int (*tlsv1_server_set_cipher_list_FP_T)(struct tlsv1_server *conn, u8 *ciphers);
extern _RPST_ tlsv1_server_set_cipher_list_FP_T tlsv1_server_set_cipher_list_FP;

/***************/
typedef void (*x509_certificate_free_FP_T)(struct x509_certificate *cert);
extern _RPST_ x509_certificate_free_FP_T x509_certificate_free_FP;

typedef struct x509_certificate * (*x509_certificate_parse_FP_T)(const u8 *buf, size_t len);
extern _RPST_ x509_certificate_parse_FP_T x509_certificate_parse_FP;

typedef void (*x509_name_string_FP_T)(struct x509_name *name, char *buf, size_t len);
extern _RPST_ x509_name_string_FP_T x509_name_string_FP;

typedef int (*x509_name_compare_FP_T)(struct x509_name *a, struct x509_name *b);
extern _RPST_ x509_name_compare_FP_T x509_name_compare_FP;

typedef void (*x509_certificate_chain_free_FP_T)(struct x509_certificate *cert);
extern _RPST_ x509_certificate_chain_free_FP_T x509_certificate_chain_free_FP;

typedef int (*x509_certificate_check_signature_FP_T)(struct x509_certificate *issuer,
				     struct x509_certificate *cert);
extern _RPST_ x509_certificate_check_signature_FP_T x509_certificate_check_signature_FP;

typedef int (*x509_certificate_chain_validate_FP_T)(struct x509_certificate *trusted,
				    struct x509_certificate *chain,
				    int *reason, int disable_time_checks);
extern _RPST_ x509_certificate_chain_validate_FP_T x509_certificate_chain_validate_FP;

typedef struct x509_certificate *
(*x509_certificate_get_subject_FP_T)(struct x509_certificate *chain,
			     struct x509_name *name);
extern _RPST_ x509_certificate_get_subject_FP_T x509_certificate_get_subject_FP;

typedef int (*x509_certificate_self_signed_FP_T)(struct x509_certificate *cert);
extern _RPST_ x509_certificate_self_signed_FP_T x509_certificate_self_signed_FP;

#endif /*_GSN_WPA_SUPP_PATCH_FPT_*/
