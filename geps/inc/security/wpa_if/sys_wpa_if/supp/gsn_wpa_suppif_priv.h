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
* $RCSfile: gsn_wpa_suppif_priv.h,v $
*
* Description : This file contains the private declaration used for supplicant
* modules.
*******************************************************************************/
#ifndef _GSN_WPA_SUPPIF_PRIV_H_
#define _GSN_WPA_SUPPIF_PRIV_H_

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
typedef struct GSN_WPA_SUPPIF
{
    GSN_WPAIF_T wpaIf;

    GSN_WPAIF_MODE_T mode;
    UINT32 eapol_received;


    GSN_WPAIF_CFG_T cfg;
    UINT8 bssid[ETH_ALEN];
    struct wpa_sm_ctx ctx;
    struct wpa_sm *wpa; /* WPA */
    struct wps_context *wps;
    struct eapol_sm *eapol;
    struct wpa_authenticator *auth_group;
    struct eap_peer_config *pEap_cfg;
    unsigned char last_eapol_src[ETH_ALEN];

    UINT8 secondPhase;
#ifdef GSN_SECURITY_ENTERPRISE_AVAILABLE
    GSN_BLOB_T *pBlobList;

    GSN_BLOB_T caBlob;
    GSN_BLOB_T certBlob;
    GSN_BLOB_T keyBlob ;
#endif
#ifdef GSN_SECURITY_WPS_ENABLE
    UINT8 wps_method;
    UINT8 wpsRegistrarFound;
    UINT8 channel;
    GSN_SOFT_TMR_T wpsPbcWalkTmr;
    UINT8 wps_state;
    UINT8 *pScanBuf;
    UINT8 *pScanBuf1;
    UINT8 maxChannel;
    UINT8 assoRetry;
    UINT8 phase1_cfg[32];
    UINT32 wpsCertification;
#endif
}GSN_WPA_SUPPIF_T;

enum GSN_WPSIF_METHOD
{
    GSN_WPSIF_METHOD_NONE,
    GSN_WPSIF_METHOD_PBC,
    GSN_WPSIF_METHOD_PIN_ENROLLEE_FIRST,
    GSN_WPSIF_METHOD_PIN_REGISTRAR_FIRST,
    GSN_WPSIF_METHOD_DFLT_PIN,
};

int GsnWpaSuppIf_PMKIDAdd(void *ctx, const u8 *bssid, const u8 *pmkid);
void GsnWpaSuppIf_Deauth(void * ctx, int reason_code);
void * GsnWpaSuppIf_GetNetworkCtx(void *ctx);
int GsnWpaSuppIf_GetBssid(void *ctx, u8 *bssid);
void GsnWpaSuppIf_SetState(void *ctx, enum wpa_states state);
enum wpa_states GsnWpaSuppIf_GetState(void *ctx );
void GsnWpaSuppIf_EapolRx(void *ctx, uint8_t *pData, uint32_t size );
int GsnWpaSuppIf_EthSend(void *ctx, const u8 *dest, u16 proto, const u8 *buf,
               size_t len);
void GsnWpaSuppIf_FreeEapol( UINT8 * pFrame );
u8 * GsnWpaSuppIf_AllocEapol(void *ctx, u8 type, const void *data,
                 u16 data_len, size_t *msg_len, void **data_pos);
int GsnWpaSuppIf_GetBeaconIE(void *ctx);
int GsnWpaSuppIf_SetKey(void *ctx, enum wpa_alg alg,
            const u8 *addr, int key_idx, int set_tx,
            const u8 *seq, size_t seq_len,
            const u8 *key, size_t key_len);
int GsnWpaSuppIf_MLMESetProtection(void *ctx, const u8 *addr,
                   int protection_type, int key_type);
void GsnWpaSuppIf_ReqAuthTimeout(void *ctx,
                         int sec, int usec);
void GsnWpaSuppIf_CancelAuthTimeout(void *ctx);

PUBLIC VOID 
GsnWpaAuthIf_EapolRx(VOID *ctx, UINT8 *pData, UINT32 size );


struct eap_peer_config * GsnEapIf_ConfigSet(GSN_WPA_SUPPIF_T *pWpaIf );

int GsnEapIf_RegisterMethods(void);

void GsnWpsIf_Start( GSN_WPA_SUPPIF_T *pWpaIf );

int GsnWpsIf_Init( void *pWpaCtx );

PUBLIC VOID
GsnEapIf_ConfigDelete(GSN_WPA_SUPPIF_T *pWpaIf );

void GsnWpsIf_Deinit( GSN_WPA_SUPPIF_T *pWpaIf );

int GsnWpsIf_PreconfigureDhKey( GSN_WPA_SUPPIF_T *pWpaIf );

void *GsnSuppif_WpaInit(struct wpa_sm_ctx *pWpaSmCtx);

GSN_STATUS
GsnWpaSuppIf_Cb( void *pCtx, UINT32 event, UINT8 *pData, UINT32 length );


#ifdef __cplusplus
}
#endif
#endif /*  _GSN_WPA_SUPPIF_PRIV_H_ */
