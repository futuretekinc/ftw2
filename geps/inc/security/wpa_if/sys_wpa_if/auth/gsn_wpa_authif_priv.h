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
* $RCSfile: gsn_wpa_authif_priv.h,v $
*
* Description : This file contains the private declaration used for supplicant
* modules.
*******************************************************************************/
#ifndef _GSN_WPA_AUTHIF_PRIV_H_
#define _GSN_WPA_AUTHIF_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "gsn_includes.h"
#include "supplicant/utils/includes.h"
#include "supplicant/utils/common.h"
#include "supplicant/utils/wpabuf.h"
#include "supplicant/common/defs.h"
#include "supplicant/rsn_supp/wpa.h"

#include "security/wpa_if/gsn_wpaif.h"
#include "security/wpa_if/sys_wpa_if/inc/gsn_blobif.h"

/**
 *******************************************************************************
 * @file gsn_wpaif_i.h
 * @brief GSN WPAIF module.
 *      This file contains the WPAIF specific definitions.
 ******************************************************************************/

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF mode.
 *     This enum defines the WPAIF operation mode. This mode specifies the Wi-Fi
 * operating mode.
 *******************************************************************************/


#define GSN_WPAIF_WPS_STATE_NONE        0
#define GSN_WPAIF_WPS_STATE_SRCH_REG    1
#define GSN_WPAIF_WPS_STATE_REG_IN_PROG 2

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF context declaration.
 *
 *     This structure defines the WPAIF context. It stores all the information
 * needed to operate on an Wi-Fi interface.
 ******************************************************************************/
typedef struct GSN_WPA_STA_INFO {
    struct sta_info *next; /* next entry in sta list */
    struct sta_info *hnext; /* next entry in hash table list */
    u8 addr[6];
       struct wpa_state_machine *wpa_sm;
       struct eapol_state_machine *eapol_sm;
    struct wpabuf *wps_ie; /* WPS IE from (Re)Association Request */
}GSN_WPA_STA_INFO_T;

typedef struct GSN_WPA_AUTHIF
{
    GSN_WPAIF_T wpaIf;


    UINT8 state;



    UINT8 maxNumSta;
    UINT8 numSta; /* number of entries in sta_list */
    GSN_WPA_STA_INFO_T *pStaList; /* STA info list head */

    GSN_WPAIF_BASIC_CFG_T basicCfg;
    GSN_WPAIF_PSK_CFG_T    pskCfg;

    struct wpa_authenticator *wpa_auth;
    struct eapol_authenticator *eapol_auth;
    struct wps_context *wps;

    struct wpabuf *wps_beacon_ie;
    struct wpabuf *wps_probe_resp_ie;
#ifdef CONFIG_WPS
    GSN_WPAIF_WPS_CFG_T wpsCfg;
    unsigned int ap_pin_failures;
    struct upnp_wps_device_sm *wps_upnp;
    unsigned int ap_pin_lockout_time;
#endif /* CONFIG_WPS */
}GSN_WPA_AUTHIF_T;


PUBLIC GSN_WPA_STA_INFO_T *
GsnWpaAuthIf_AddSta( GSN_WPA_AUTHIF_T *pAuthIf, const UINT8 *addr );

PUBLIC VOID
GsnWpaAuthIf_RemoveSta( GSN_WPA_AUTHIF_T *pAuthIf, const UINT8 *addr );

PUBLIC GSN_WPA_STA_INFO_T *
GsnWpaAuthIf_FindSta( GSN_WPA_AUTHIF_T *pAuthIf, const UINT8 *addr );

PUBLIC void GsnWapAuthIf_AuthConf( GSN_WPA_AUTHIF_T *pWpaAuthIf,
    GSN_WPAIF_BASIC_CFG_T *pCfg, struct wpa_auth_config *wconf);

PUBLIC VOID
GsnWpaAuthIf_Disconnect( VOID *pWpaAuthIf,
    UINT8 const*pMac, UINT16 reason );

PUBLIC VOID
GsnWpaAuthIf_MicFail(void *ctx, const u8 *addr);

PUBLIC VOID
GsnWpaAuthIf_SetEapol(void *ctx, const u8 *addr,
                       wpa_eapol_variable var, int value);

PUBLIC INT32
GsnWpaAuthIf_GetEapol(void *ctx, const u8 *addr,
                      wpa_eapol_variable var);

PUBLIC const u8*
GsnWpaAuthIf_GetPsk(void *ctx, const u8 *addr,
                       const u8 *prev_psk);
PUBLIC INT32
GsnWpaAuthIf_GetMsk(void *ctx, const u8 *addr, u8 *msk,
                    size_t *len);
PUBLIC int
GsnWpaAuthIf_SetKey(void *ctx, int vlan_id, enum wpa_alg alg,
                    const u8 *addr, int idx, u8 *key,
                    size_t key_len);
PUBLIC int
GsnWpaAuthIf_GetSeqnum(void *ctx, const u8 *addr, int idx,
                       u8 *seq);
PUBLIC INT32
GsnWpaAuthIf_SendEapol(void *ctx, const u8 *addr,
                       const u8 *data, size_t data_len,
                       int encrypt);
PUBLIC INT32
GsnWpaAuthIf_SendEther(void *ctx, const u8 *addr,u16 proto, const u8 *data,
    size_t data_len );

PUBLIC int
GsnWpaAuthIf_ForEachSta(
    void *ctx, int (*cb)(struct wpa_state_machine *sm, void *ctx),
    void *cb_ctx);
PUBLIC INT32
GsnWpaAuthIf_IfaceIter(VOID *iface, void *ctx);
PUBLIC INT32
GsnWpaAuthIf_ForEachAuth(
    void *ctx, int (*cb)(struct wpa_authenticator *sm, void *ctx),
    void *cb_ctx);
#if 0
PUBLIC INT32
GsnWpaAuthIf_Ft_Iter(struct hostapd_iface *iface, void *ctx);
#endif

#ifdef CONFIG_IEEE80211R

PUBLIC INT32
GsnWpaAuthIf_SendFtAction(void *ctx, const u8 *dst,
                       const u8 *data, size_t data_len);
PUBLIC struct wpa_state_machine *
GsnWpaAuthIf_AddSta(void *ctx, const u8 *sta_addr);


#endif


#ifdef __cplusplus
}
#endif
#endif /*  _GSN_WPA_AUTHIF_PRIV_H_ */
