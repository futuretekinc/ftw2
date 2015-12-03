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
* $RCSfile: gsn_hewpaif_dh_fpt.h,v $
*
* Description : This file contains function pointer variables for 
* gsn_hewpaif_dh.c.
*******************************************************************************/

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "supplicant/utils/includes.h"
#include "supplicant/utils/common.h"
#include "supplicant/crypto/aes.h"
#include "supplicant/crypto/crypto.h"
#include "supplicant/crypto/dh_groups.h"
#include "supplicant/eap_common/eap_defs.h"
#include "supplicant/common/defs.h"
#include "supplicant/rsn_supp/wpa.h"
/**
 *******************************************************************************
 * @file gsn_wpaif.h
 * @brief GSN WPAIF module.
 *      This file contains the WPAIF specific definitions.
 ******************************************************************************/

typedef void * (*dh5_init_FP_T)(struct wpabuf **priv, struct wpabuf **publ);
extern _RPST_ dh5_init_FP_T dh5_init_FP;

typedef struct wpabuf * (*dh5_derive_shared_FP_T)(void *ctx, const struct wpabuf *peer_public,
				  const struct wpabuf *own_private);
extern _RPST_ dh5_derive_shared_FP_T dh5_derive_shared_FP;

typedef void (*dh5_free_FP_T)(void *ctx);
extern _RPST_ dh5_free_FP_T dh5_free_FP;

typedef const struct dh_group * (*dh_groups_get_FP_T)(int id);
extern _RPST_ dh_groups_get_FP_T dh_groups_get_FP;

typedef struct wpabuf * (*dh_init_FP_T)(const struct dh_group *dh, struct wpabuf **priv);
extern _RPST_ dh_init_FP_T dh_init_FP;

typedef struct wpabuf * (*dh_derive_shared_FP_T)(const struct wpabuf *peer_public,
				 const struct wpabuf *own_private,
				 const struct dh_group *dh);
extern _RPST_ dh_derive_shared_FP_T dh_derive_shared_FP; 
