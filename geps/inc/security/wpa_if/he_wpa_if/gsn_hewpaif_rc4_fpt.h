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
* $RCSfile: gsn_hewpaif_rc4_fpt.h,v $
*
* Description : This file contains function pointer variables for 
* gsn_hewpaif_rc4.c.
*******************************************************************************/

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include "security/hw_engine_if/gsn_hw_engine_if.h"

#include "supplicant/utils/includes.h"
#include "supplicant/utils/common.h"
#include "supplicant/crypto/aes.h"
#include "supplicant/crypto/crypto.h"
#include "supplicant/eap_common/eap_defs.h"
#include "supplicant/common/defs.h"
#include "supplicant/rsn_supp/wpa.h"
/**
 *******************************************************************************
 * @file gsn_wpaif.h
 * @brief GSN WPAIF module.
 *      This file contains the WPAIF specific definitions.
 ******************************************************************************/

typedef int (*rc4_skip_FP_T)(const u8 *key, size_t keylen, size_t skip,
	     u8 *data, size_t data_len);

extern _RPST_ rc4_skip_FP_T rc4_skip_FP;
