#ifndef _GSN_WPA_SUPPIF_PRIV_FPT_
#define _GSN_WPA_SUPPIF_PRIV_FPT_

#include <stdint.h>
#include "supplicant/utils/includes.h"
#include "supplicant/utils/common.h"
#include "supplicant/utils/eloop.h"

#include "supplicant/rsn_supp/wpa.h"
#include "supplicant/rsn_supp/wpa_i.h"
#include "supplicant/rsn_supp/wpa_ie.h"
#include "supplicant/rsn_supp/pmksa_cache.h"
#include "supplicant/ap/wpa_auth.h"
#include "supplicant/ap/wpa_auth_i.h"
#include "supplicant/eap_peer/eap_config.h"
#include "supplicant/eapol_supp/eapol_supp_sm.h"
#include "supplicant/common/ieee802_11_defs.h"

#include "gsn_includes.h"
#ifdef OS_UVEL
#include "gsn_supplicant_private.h"
#endif

#include "security/wpa_if/gsn_wpaif.h"
#include "security/wpa_if/sys_wpa_if/gsn_wpaif_priv.h"
#include "security/wpa_if/sys_wpa_if/supp/gsn_wpa_suppif_priv.h"


typedef void *(*GsnSuppif_WpaInit_FP_T)(struct wpa_sm_ctx *pWpaSmCtx);
extern _RPST_ GsnSuppif_WpaInit_FP_T GsnSuppif_WpaInit_FP; 

#endif /* _GSN_WPA_SUPPIF_PRIV_FPT_ */