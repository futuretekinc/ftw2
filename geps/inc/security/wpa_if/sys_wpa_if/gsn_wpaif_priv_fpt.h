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
* $RCSfile: gsn_wpaif_priv_fpt.h,v $
*
* Description : This file contains the API implementation to interface with Security module.
*******************************************************************************/
#ifndef _GSN_WPAIF_PRIV_FPT_
#define _GSN_WPAIF_PRIV_FPT_
/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "gsn_includes.h"
#include "security/wpa_if/sys_wpa_if/gsn_wpaif_priv.h"


typedef GSN_WPAIF_T *
(*GsnWpa_FindIf_FP_T)( VOID *pDrvIf );
extern _RPST_ GsnWpa_FindIf_FP_T GsnWpa_FindIf_FP;

typedef VOID
(*GsnWpa_AddIf_FP_T)( GSN_WPAIF_T *pIf );
extern _RPST_ GsnWpa_AddIf_FP_T GsnWpa_AddIf_FP;

typedef VOID
(*GsnWpa_RemoveIf_FP_T)( GSN_WPAIF_T *pIf );
extern _RPST_ GsnWpa_RemoveIf_FP_T GsnWpa_RemoveIf_FP;

#endif /* _GSN_WPAIF_PRIV_FPT_ */