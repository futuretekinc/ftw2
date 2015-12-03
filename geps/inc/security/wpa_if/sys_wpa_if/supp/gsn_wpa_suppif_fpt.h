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
* $RCSfile: gsn_wpa_suppif_fpt.h,v $
*
* Description : This file contains the API implementation to interface with WDD.
*******************************************************************************/
#ifndef _GSN_WPA_SUPPIF_FPT_
#define _GSN_WPA_SUPPIF_FPT_
/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "supplicant/utils/includes.h"
#include "supplicant/utils/common.h"
#include "supplicant/rsn_supp/wpa.h"
#include "supplicant/rsn_supp/wpa_i.h"
#include "supplicant/rsn_supp/pmksa_cache.h"

#include "supplicant/ap/wpa_auth.h"
#include "supplicant/ap/wpa_auth_i.h"
#include "supplicant/eap_peer/eap_config.h"
#include "supplicant/eap_server/eap_methods.h"
#include "supplicant/eapol_supp/eapol_supp_sm.h"

#include "supplicant/crypto/sha1.h"

#include "gsn_includes.h"
#include "security/wpa_if/gsn_wpaif.h"
#include "security/wpa_if/sys_wpa_if/gsn_wpaif_priv.h"
#include "security/wpa_if/sys_wpa_if/supp/gsn_wpa_suppif_priv.h"

#include "security/wpa_if/sys_wpa_if/supp/gsn_eapolif.h"
/**
 *******************************************************************************
 * @file gsn_wpaif.h
 * @brief GSN WPAIF module.
 *      This file contains the WPAIF specific definitions.
 ******************************************************************************/
typedef VOID*
(*GsnWpaSuppIf_BasicStateInit_FP_T)( VOID *pWpaSuppIf );
extern _RPST_ GsnWpaSuppIf_BasicStateInit_FP_T GsnWpaSuppIf_BasicStateInit_FP;

typedef GSN_STATUS
(*GsnWpaSuppIf_CfgSet_FP_T)( VOID *pCtx,  GSN_WPAIF_CFG_OPT_T cfgOpt, UINT8 *pData,
            UINT32 length );
extern _RPST_ GsnWpaSuppIf_CfgSet_FP_T GsnWpaSuppIf_CfgSet_FP;

typedef GSN_STATUS
(*GsnWpaSuppIf_CfgGet_FP_T)( VOID *pCtx, GSN_WPAIF_CFG_OPT_T cfgOpt, UINT8 *pData,
            UINT32* pLen );
extern _RPST_ GsnWpaSuppIf_CfgGet_FP_T GsnWpaSuppIf_CfgGet_FP;

typedef GSN_STATUS
(*GsnWpaSuppIf_Cb_FP_T)( VOID *pCtx, UINT32 event, UINT8 *pData, UINT32 length );
extern _RPST_ GsnWpaSuppIf_Cb_FP_T GsnWpaSuppIf_Cb_FP;

typedef GSN_STATUS
(*GsnWpaSuppIf_Deinit_FP_T)( VOID *pCtx );
extern _RPST_ GsnWpaSuppIf_Deinit_FP_T GsnWpaSuppIf_Deinit_FP;

typedef VOID*
(*GsnWpaSuppIf_RestoreConn_FP_T)( GSN_WPA_SUPPIF_T *pWpaSuppIf, struct wpa_ptk *pPtk );
extern _RPST_ GsnWpaSuppIf_RestoreConn_FP_T GsnWpaSuppIf_RestoreConn_FP;

typedef GSN_STATUS
(*GsnWpaSuppIf_StoreSpecialCnf_FP_T)( GSN_WPA_SUPPIF_T *pWpaSuppIf, VOID *pSCfg );
extern _RPST_ GsnWpaSuppIf_StoreSpecialCnf_FP_T GsnWpaSuppIf_StoreSpecialCnf_FP;

typedef VOID*
(*GsnWpaSuppIf_Init_FP_T)( VOID *pCtx, GSN_WPAIF_MODE_T mode, VOID *pDrvIf,
    GSN_WPAIF_BASIC_CFG_T *pCfg, GSN_WPAIF_SPECFIC_CFG_T *pSpecCfg );
extern _RPST_ GsnWpaSuppIf_Init_FP_T GsnWpaSuppIf_Init_FP;

#endif /* _GSN_WPA_SUPPIF_PRIV_FPT_ */