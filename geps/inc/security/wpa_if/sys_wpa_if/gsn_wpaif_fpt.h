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
* $RCSfile: gsn_wpaif_fpt.h,v $
*
* Description : This file contains the API implementation to interface with WDD.
*******************************************************************************/
#ifndef _GSN_WPAIF_FPT_
#define _GSN_WPAIF_FPT_

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
#include "supplicant/eapol_supp/eapol_supp_sm.h"

#include "gsn_includes.h"
#include "security/wpa_if/gsn_wpaif.h"

#include "security/wpa_if/sys_wpa_if/inc/gsn_wpa_authif.h"
#include "security/wpa_if/sys_wpa_if/inc/gsn_wpa_suppif.h"

#include "security/wpa_if/sys_wpa_if/gsn_wpaif_priv.h"

/**
 *******************************************************************************
 * @file gsn_wpaif.h
 * @brief GSN WPAIF module.
 *      This file contains the WPAIF specific definitions.
 ******************************************************************************/
typedef VOID
(*GsnWpa_Init_FP_T)( GSN_WPAIF_TMR_NITIF_CB_T cb, void *pCtx, 
    UINT32 seed[TRNG_NONCE_SIZE_WORDS] );
extern _RPST_ GsnWpa_Init_FP_T GsnWpa_Init_FP;

typedef VOID* 
(*GsnWpaIf_Init_FP_T)( GSN_WPAIF_MODE_T mode, VOID *pDrvIf, GSN_WPAIF_BASIC_CFG_T *pCfg, 
	GSN_WPAIF_SPECFIC_CFG_T *pSpecCfg );
extern _RPST_ GsnWpaIf_Init_FP_T GsnWpaIf_Init_FP;


typedef GSN_STATUS 
(*GsnWpaIf_Deinit_FP_T)( void *pCtx );
extern _RPST_ GsnWpaIf_Deinit_FP_T GsnWpaIf_Deinit_FP;

typedef GSN_STATUS 
(*GsnWpaIf_Notif_FP_T)( void *pCtx, GSN_WPAIF_EVENT_T event, UINT8 *pData, UINT32 length );
extern _RPST_ GsnWpaIf_Notif_FP_T GsnWpaIf_Notif_FP;

/**
wpa_cfg_get, wpa_cfg_set:-
**/
typedef GSN_STATUS 
(*GsnWpaIf_CfgGet_FP_T)( void *pCtx, GSN_WPAIF_CFG_OPT_T cfgOpt, UINT8 *pData, 
               UINT32* pLen );
extern _RPST_ GsnWpaIf_CfgGet_FP_T GsnWpaIf_CfgGet_FP;

typedef GSN_STATUS 
(*GsnWpaIf_CfgSet_FP_T)( VOID *pCtx,  GSN_WPAIF_CFG_OPT_T cfgOpt, UINT8 *pData, 
               UINT32 length );
extern _RPST_ GsnWpaIf_CfgSet_FP_T GsnWpaIf_CfgSet_FP;

typedef VOID*
(*GsnWpaIf_BasicStateInit_FP_T)( VOID *pCtx );
extern _RPST_ GsnWpaIf_BasicStateInit_FP_T GsnWpaIf_BasicStateInit_FP;

typedef GSN_STATUS
(*GsnWpaIf_ExtractCfg_FP_T)( GSN_MAC_FRAME_T* framePtr, UINT16 frameLen,
    GSN_WPAIF_BASIC_CFG_T *pCfg, INT8 *pIE, INT8 *pIElen);
extern _RPST_ GsnWpaIf_ExtractCfg_FP_T GsnWpaIf_ExtractCfg_FP;

#endif /* _GSN_WPAIF_FPT_ */