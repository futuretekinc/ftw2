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
* $RCSfile: gsn_wpa_suppif.h,v $
*
* Description : This file contains the private declaration used for supplicant
* modules.
*******************************************************************************/
#ifndef _GSN_WPA_SUPPIF_H_
#define _GSN_WPA_SUPPIF_H_

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
 * @brief Initialize the WPAIF.
 *
 *    This function is called to initialize the WPAIF module. This API has to be
 * called before callignany other APIs of WPAIF. This API is called once the
 * user has decided to join/create a network. At this point user will have the
 * basic configuration of the network.
 * To derive the basic configuration from the scan response user can call
 * wpa_parse_wpa_ie API provided by WPA open source code (refer wpa.h in rsn_supp
 * folder).
 *     In case of WPS connection, the user has to set the "proto" to
 * "WPA_PROTO_WPS" (defined in defs.h) and has to provide the WPS configuration
 * in pSpecCfg to initiate WPS joining procedure.
 *
 * @param mode - IN WiFi operation mode.
 * @param pDrvIf - IN Pointer to the WiFi driver interface (WDD).
 * @param pCfg - IN Pointer to basic configuration. This API copies the content
 *               of this pointer to its context memory.
 * @param pSpecCfg - IN Pointer to the specific configuration. This field is used
 *                             if user wants to provide WPA, EAP or WPS configuartion. In
 *                             case of WPS, this field is mandatory.
 *******************************************************************************/
PUBLIC VOID* 
GsnWpaSuppIf_Init( VOID *pCtx, GSN_WPAIF_MODE_T mode, VOID *pDrvIf, 
    GSN_WPAIF_BASIC_CFG_T *pCfg, GSN_WPAIF_SPECFIC_CFG_T *pSpecCfg );


#ifdef __cplusplus
}
#endif
#endif /*  _GSN_WPA_SUPPIF_H_ */
