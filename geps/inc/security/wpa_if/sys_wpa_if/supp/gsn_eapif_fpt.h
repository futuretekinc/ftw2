#ifndef _GSN_EAPIF_FPT_H_
#define _GSN_EAPIF_FPT_H_

#include <stdint.h> 
#include "supplicant/utils/includes.h"
#include "supplicant/utils/common.h"
#include "supplicant/rsn_supp/wpa.h"
#include "supplicant/rsn_supp/wpa_i.h"
#include "supplicant/ap/wpa_auth.h"
#include "supplicant/ap/wpa_auth_i.h"
#include "supplicant/eap_peer/eap_config.h"
#include "supplicant/eap_server/eap.h"
#include "supplicant/eapol_supp/eapol_supp_sm.h"
#include "supplicant/eap_common/eap_wsc_common.h"

#include "gsn_includes.h"
#include "security/wpa_if/gsn_wpaif.h"

#include "security/wpa_if/sys_wpa_if/gsn_wpaif_priv.h"

#include "security/wpa_if/sys_wpa_if/inc/gsn_blobif.h"
#include "security/wpa_if/sys_wpa_if/supp/gsn_wpa_suppif_priv.h"


typedef VOID (*GsnEapIf_CertSet_FP_T)( GSN_WPA_SUPPIF_T *pWpaIf );
extern _RPST_ GsnEapIf_CertSet_FP_T GsnEapIf_CertSet_FP;

typedef GSN_STATUS (*GsnEapIf_PacSet_FP_T)( GSN_WPA_SUPPIF_T *pWpaIf );
extern _RPST_ GsnEapIf_PacSet_FP_T GsnEapIf_PacSet_FP;

typedef struct eap_peer_config * (*GsnEapIf_ConfigSet_FP_T)(GSN_WPA_SUPPIF_T *pWpaIf );
extern _RPST_ GsnEapIf_ConfigSet_FP_T GsnEapIf_ConfigSet_FP;

typedef VOID
(*GsnEapIf_ConfigDelete_FP_T)(GSN_WPA_SUPPIF_T *pWpaIf );
extern _RPST_ GsnEapIf_ConfigDelete_FP_T GsnEapIf_ConfigDelete_FP;

typedef int (*GsnEapIf_RegisterMethods_FP_T)(void);
extern _RPST_ GsnEapIf_RegisterMethods_FP_T GsnEapIf_RegisterMethods_FP;

typedef UINT8* (*GsnEapIf_Phase2StrGet_FP_T)( UINT8 auth );
extern _RPST_ GsnEapIf_Phase2StrGet_FP_T GsnEapIf_Phase2StrGet_FP;
#endif /* #ifndef _GSN_EAPIF_FPT_H_ */
