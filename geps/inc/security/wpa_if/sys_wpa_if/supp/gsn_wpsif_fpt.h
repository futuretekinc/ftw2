
#ifndef _GSN_WPSIF_FPT_
#define _GSN_WPSIF_FPT_

#include <stdint.h>
#include "supplicant/utils/includes.h"
#include "supplicant/utils/common.h"
#include "supplicant/utils/wpabuf.h"
#include "supplicant/utils/eloop.h"


#include "supplicant/rsn_supp/wpa.h"
#include "supplicant/ap/wpa_auth.h"
#include "supplicant/ap/wpa_auth_i.h"
#include "supplicant/eap_peer/eap_config.h"

#include "gsn_includes.h"
#include "security/wpa_if/gsn_wpaif.h"
#include "security/wpa_if/sys_wpa_if/supp/gsn_eapolif.h"
#include "security/wpa_if/sys_wpa_if/gsn_wpaif_priv.h"
#include "supplicant/wps/wps.h"
#include "supplicant/wps/wps_defs.h"
#include "security/wpa_if/sys_wpa_if/supp/gsn_wpa_suppif_priv.h"

typedef int 
(*GsnWpsIf_ExtractCred_FP_T)(void *ctx,
    const struct wps_credential *cred);
extern _RPST_ GsnWpsIf_ExtractCred_FP_T GsnWpsIf_ExtractCred_FP;

typedef VOID 
(*GsnWpsIf_Event_FP_T)( VOID *ctx, enum wps_event event,
				     union wps_event_data *data);
extern _RPST_ GsnWpsIf_Event_FP_T GsnWpsIf_Event_FP;

typedef int (*GsnWpsIf_Init_FP_T)( void *pWpaCtx );
extern _RPST_ GsnWpsIf_Init_FP_T GsnWpsIf_Init_FP;

typedef void (*GsnWpsIf_Deinit_FP_T)( GSN_WPA_SUPPIF_T *pWpaIf );
extern _RPST_ GsnWpsIf_Deinit_FP_T GsnWpsIf_Deinit_FP;

typedef VOID
(*GsnWpsIf_PbcWalkTmrCb_FP_T)( VOID *pEloop_ctx, VOID *pCtx );
extern _RPST_ GsnWpsIf_PbcWalkTmrCb_FP_T GsnWpsIf_PbcWalkTmrCb_FP;

typedef void (*GsnWpsIf_Start_FP_T)( GSN_WPA_SUPPIF_T *pWpaIf );
extern _RPST_ GsnWpsIf_Start_FP_T GsnWpsIf_Start_FP;

typedef int (*GsnWpsIf_ProcessScanEntry_FP_T)(GSN_WPA_SUPPIF_T *pWpaIf, 
    GSN_WIF_WLAN_SCAN_IND_T *pFrame );
extern _RPST_ GsnWpsIf_ProcessScanEntry_FP_T GsnWpsIf_ProcessScanEntry_FP;

typedef void (*GsnWpsIf_PreAssocCb_FP_T)( GSN_WPA_SUPPIF_T *pWpaIf );
extern _RPST_ GsnWpsIf_PreAssocCb_FP_T GsnWpsIf_PreAssocCb_FP;

typedef int (*GsnWpsIf_ScanComplete_FP_T)( GSN_WPA_SUPPIF_T *pWpaIf );
extern _RPST_ GsnWpsIf_ScanComplete_FP_T GsnWpsIf_ScanComplete_FP;

typedef void (*GsnWpsIf_ScanCfmCb_FP_T)(VOID *ctx, GSN_STATUS status, 
    UINT8 *resultBuf, UINT32 numResults);
extern _RPST_ GsnWpsIf_ScanCfmCb_FP_T GsnWpsIf_ScanCfmCb_FP;

typedef int (*GsnWpsIf_PreconfigureDhKey_FP_T)( GSN_WPA_SUPPIF_T *pWpaIf );
extern _RPST_ GsnWpsIf_PreconfigureDhKey_FP_T GsnWpsIf_PreconfigureDhKey_FP;

typedef int (*GsnWpsIf_NewPskCb_FP_T)(void *ctx, const UINT8 *mac_addr, const UINT8 *psk,
    size_t psk_len);
extern _RPST_ GsnWpsIf_NewPskCb_FP_T GsnWpsIf_NewPskCb_FP;

typedef void (*GsnWpsIf_PinNeededCb_FP_T)(void *ctx, const UINT8 *uuid_e,
	const struct wps_device_data *dev);
extern _RPST_ GsnWpsIf_PinNeededCb_FP_T GsnWpsIf_PinNeededCb_FP;

typedef void (*GsnWpsIf_SetSelRegCb_FP_T)(void *ctx, int sel_reg, UINT16 dev_passwd_id,
	UINT16 sel_reg_config_methods);
extern _RPST_ GsnWpsIf_SetSelRegCb_FP_T GsnWpsIf_SetSelRegCb_FP;

typedef VOID (*GsnWpsIf_ConnectIndCb_FP_T)(VOID *ctx, GSN_STATUS status);
extern _RPST_ GsnWpsIf_ConnectIndCb_FP_T GsnWpsIf_ConnectIndCb_FP;

typedef void (*GsnWpsIf_DeAuthTimeoutCb_FP_T)( void* ctx,void *ctx1 );
extern _RPST_ GsnWpsIf_DeAuthTimeoutCb_FP_T GsnWpsIf_DeAuthTimeoutCb_FP;

typedef void (*GsnWpsIf_StartSecondPhase_FP_T)( GSN_WPA_SUPPIF_T *pWpaIf );
extern _RPST_ GsnWpsIf_StartSecondPhase_FP_T GsnWpsIf_StartSecondPhase_FP;
#endif /* _GSN_WPSIF_FPT_ */
