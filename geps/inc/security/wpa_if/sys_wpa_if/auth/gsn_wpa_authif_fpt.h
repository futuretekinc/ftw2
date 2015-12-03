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
* $RCSfile: gsn_wpa_authif_fpt.h,v $
*
* Description : This file contains the API implementation to interface with WPA AUTH.
*******************************************************************************/
#ifndef _GSN_WPA_AUTHIF_FPT_H_
#define _GSN_WPA_AUTHIF_FPT_H_

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "supplicant/utils/includes.h"
#include "supplicant/utils/common.h"
#include "supplicant/ap/wpa_auth.h"
#include "supplicant/ap/wpa_auth_i.h"
#include "supplicant/eap_peer/eap_config.h"

#include "supplicant/eap_server/eap.h"
#include "supplicant/eapol_auth/eapol_auth_sm.h"
//#include "eapol_auth/eapol_auth_sm_i.h"

#include "gsn_includes.h"
#include "security/wpa_if/gsn_wpaif.h"

#include "security/wpa_if/sys_wpa_if/gsn_wpaif_priv.h"
#include "security/wpa_if/sys_wpa_if/auth/gsn_wpa_authif_priv.h"



/**
 *******************************************************************************
 * @file gsn_wpaif.h
 * @brief GSN WPAIF module.
 *      This file contains the WPAIF specific definitions.
 ******************************************************************************/
typedef VOID*
(*GsnWpaAuthIf_BasicStateInit_FP_T)( VOID *pCtx);
extern _RPST_ GsnWpaAuthIf_BasicStateInit_FP_T GsnWpaAuthIf_BasicStateInit_FP;

typedef GSN_STATUS
(*GsnWpaAuthIf_CfgSet_FP_T)( VOID *pCtx,  GSN_WPAIF_CFG_OPT_T cfgOpt, UINT8 *pData,
            UINT32 length );
extern _RPST_ GsnWpaAuthIf_CfgSet_FP_T GsnWpaAuthIf_CfgSet_FP;

typedef GSN_STATUS
(*GsnWpaAuthIf_CfgGet_FP_T)( VOID *pCtx, GSN_WPAIF_CFG_OPT_T cfgOpt, UINT8 *pData,
            UINT32* pLen );
extern _RPST_ GsnWpaAuthIf_CfgGet_FP_T GsnWpaAuthIf_CfgGet_FP;

typedef GSN_STATUS
(*GsnWpaAuthIf_Cb_FP_T)( VOID *pCtx, UINT32 event, UINT8 *pData, UINT32 length );
extern _RPST_ GsnWpaAuthIf_Cb_FP_T GsnWpaAuthIf_Cb_FP;

typedef GSN_STATUS
(*GsnWpaAuthIf_Deinit_FP_T)( VOID *pCtx );
extern _RPST_ GsnWpaAuthIf_Deinit_FP_T GsnWpaAuthIf_Deinit_FP;

typedef VOID* 
(*GsnWpaAuthIf_Init_FP_T)( VOID *pCtx, GSN_WPAIF_MODE_T mode, VOID *pDrvIf, 
    GSN_WPAIF_BASIC_CFG_T *pCfg, GSN_WPAIF_SPECFIC_CFG_T *pSpecCfg );
extern _RPST_ GsnWpaAuthIf_Init_FP_T GsnWpaAuthIf_Init_FP;

typedef int (*GsnWpsIf_AuthInit_FP_T)( void *pWpaCtx );
extern _RPST_ GsnWpsIf_AuthInit_FP_T GsnWpsIf_AuthInit_FP;

typedef void (*GsnWpsIf_AuthDeinit_FP_T)( VOID *pWpaCtx );
extern _RPST_ GsnWpsIf_AuthDeinit_FP_T GsnWpsIf_AuthDeinit_FP;

typedef GSN_STATUS (*GsnWpsIf_AuthTrigger_FP_T)( void *pWpaCtx, UINT8 *pin );
extern _RPST_ GsnWpsIf_AuthTrigger_FP_T GsnWpsIf_AuthTrigger_FP;

typedef  VOID* (*GsnWpsIf_InitCfg_FP_T)( GSN_WPAIF_WPS_CFG_T *pWpsCfg, 
    VOID *pWpaCtx );
extern _RPST_ GsnWpsIf_InitCfg_FP_T GsnWpsIf_InitCfg_FP;

typedef VOID (*GsnWpaAuthIf_GetIe_FP_T)( VOID *pCtx, UINT8* pIe, UINT32* pIeLen );
extern _RPST_ GsnWpaAuthIf_GetIe_FP_T GsnWpaAuthIf_GetIe_FP;
#endif /* _GSN_WPA_AUTHIF_FPT_H_ */
