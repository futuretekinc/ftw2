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
* $RCSfile: gsn_wpa_authif_priv_fpt.h,v $
*
* Description : This file contains the API implementation to interface with WPA
*   AUTH module.
*******************************************************************************/
#ifndef _GSN_WPA_AUTHIF_PRIV_FPT_H_
#define _GSN_WPA_AUTHIF_PRIV_FPT_H_

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "supplicant/utils/includes.h"
#include "supplicant/utils/common.h"
#include "supplicant/rsn_supp/wpa.h"
#include "supplicant/rsn_supp/wpa_i.h"
#include "supplicant/ap/wpa_auth.h"
#include "supplicant/ap/wpa_auth_i.h"
#include "supplicant/eap_peer/eap_config.h"

#include "supplicant/eap_server/eap.h"
#include "supplicant/eapol_auth/eapol_auth_sm.h"
//#include "eapol_auth/eapol_auth_sm_i.h"

#include "gsn_includes.h"
#include "security/wpa_if/sys_wpa_if/gsn_wpaif_priv.h"
#include "security/wpa_if/sys_wpa_if/auth/gsn_wpa_authif_priv.h"

/**
 *******************************************************************************
 * @file gsn_security.c
 * @brief GSN SEC module.
 *      This file contains the Security specific definitions.
 ******************************************************************************/

typedef GSN_WPA_STA_INFO_T *
(*GsnWpaAuthIf_AddSta_FP_T)( GSN_WPA_AUTHIF_T *pAuthIf, const UINT8 *addr );
extern _RPST_ GsnWpaAuthIf_AddSta_FP_T GsnWpaAuthIf_AddSta_FP;

typedef VOID
(*GsnWpaAuthIf_RemoveSta_FP_T)( GSN_WPA_AUTHIF_T *pAuthIf, const UINT8 *addr );
extern _RPST_ GsnWpaAuthIf_RemoveSta_FP_T GsnWpaAuthIf_RemoveSta_FP;

typedef GSN_WPA_STA_INFO_T *
(*GsnWpaAuthIf_FindSta_FP_T)( GSN_WPA_AUTHIF_T *pAuthIf, const UINT8 *addr );
extern _RPST_ GsnWpaAuthIf_FindSta_FP_T GsnWpaAuthIf_FindSta_FP;

typedef PUBLIC void
(*GsnWapAuthIf_AuthConf_FP_T)( GSN_WPA_AUTHIF_T *pWpaAuthIf,
    GSN_WPAIF_BASIC_CFG_T *pCfg, struct wpa_auth_config *wconf);
extern _RPST_ GsnWapAuthIf_AuthConf_FP_T GsnWapAuthIf_AuthConf_FP;

typedef VOID
(*GsnWpaAuthIf_Disconnect_FP_T)( VOID *pCtx,
    const UINT8 *pMac, UINT16 reason );
extern _RPST_ GsnWpaAuthIf_Disconnect_FP_T GsnWpaAuthIf_Disconnect_FP;

typedef VOID
(*GsnWpaAuthIf_MicFail_FP_T)(void *ctx, const u8 *addr);
extern _RPST_ GsnWpaAuthIf_MicFail_FP_T GsnWpaAuthIf_MicFail_FP;

typedef VOID
(*GsnWpaAuthIf_SetEapol_FP_T)(void *ctx, const u8 *addr,
                       wpa_eapol_variable var, int value);
extern _RPST_ GsnWpaAuthIf_SetEapol_FP_T GsnWpaAuthIf_SetEapol_FP;

typedef INT32
(*GsnWpaAuthIf_GetEapol_FP_T)(void *ctx, const u8 *addr,
                      wpa_eapol_variable var);
extern _RPST_ GsnWpaAuthIf_GetEapol_FP_T GsnWpaAuthIf_GetEapol_FP;

typedef const UINT8*
(*GsnWpaAuthIf_GetPsk_FP_T)(void *ctx, const u8 *addr,
                       const u8 *prev_psk);
extern _RPST_ GsnWpaAuthIf_GetPsk_FP_T GsnWpaAuthIf_GetPsk_FP;

typedef INT32
(*GsnWpaAuthIf_GetMsk_FP_T)(void *ctx, const u8 *addr, u8 *msk,
                    size_t *len);
extern _RPST_ GsnWpaAuthIf_GetMsk_FP_T GsnWpaAuthIf_GetMsk_FP;

typedef int
(*GsnWpaAuthIf_SetKey_FP_T)(void *ctx, int vlan_id, enum wpa_alg alg,
                    const u8 *addr, int idx, u8 *key,
                    size_t key_len);
extern _RPST_ GsnWpaAuthIf_SetKey_FP_T GsnWpaAuthIf_SetKey_FP;

typedef int
(*GsnWpaAuthIf_GetSeqnum_FP_T)(void *ctx, const u8 *addr, int idx,
                       u8 *seq);
extern _RPST_ GsnWpaAuthIf_GetSeqnum_FP_T GsnWpaAuthIf_GetSeqnum_FP;

typedef INT32 
(*GsnWpaAuthIf_SendEther_FP_T)(void *ctx, const u8 *dst, u16 proto, const u8 *data,
			  size_t data_len);
extern _RPST_ GsnWpaAuthIf_SendEther_FP_T GsnWpaAuthIf_SendEther_FP;

typedef INT32
(*GsnWpaAuthIf_SendEapol_FP_T)(void *ctx, const u8 *addr,
                       const u8 *data, size_t data_len,
                       int encrypt);
extern _RPST_ GsnWpaAuthIf_SendEapol_FP_T GsnWpaAuthIf_SendEapol_FP;

typedef int
(*GsnWpaAuthIf_ForEachSta_FP_T)(
    void *ctx, int (*cb)(struct wpa_state_machine *sm, void *ctx),
    void *cb_ctx);
extern _RPST_ GsnWpaAuthIf_ForEachSta_FP_T GsnWpaAuthIf_ForEachSta_FP;
 

typedef INT32
(*GsnWpaAuthIf_IfaceIter_FP_T)(VOID *iface, void *ctx);
extern _RPST_ GsnWpaAuthIf_IfaceIter_FP_T GsnWpaAuthIf_IfaceIter_FP;

typedef INT32
(*GsnWpaAuthIf_ForEachAuth_FP_T)(
    void *ctx, int (*cb)(struct wpa_authenticator *sm, void *ctx),
    void *cb_ctx);
extern _RPST_ GsnWpaAuthIf_ForEachAuth_FP_T GsnWpaAuthIf_ForEachAuth_FP;

typedef VOID 
(*GsnWpaAuthIf_EapolRx_FP_T)(void *ctx, uint8_t *pData, uint32_t size );
extern _RPST_ GsnWpaAuthIf_EapolRx_FP_T GsnWpaAuthIf_EapolRx_FP;

#endif /* _GSN_WPA_AUTHIF_PRIV_FPT_H_ */
