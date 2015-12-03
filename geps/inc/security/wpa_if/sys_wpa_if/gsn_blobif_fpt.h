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
* $RCSfile: gsn_blobif_fpt.h,v $
*
* Description : This file contains the API implementation to interface with Security module.
*******************************************************************************/

#ifndef _GSN_BLOBIF_FPT_
#define _GSN_BLOBIF_FPT_

#include <stdint.h> 
#include "supplicant/utils/includes.h"
#include "supplicant/utils/common.h"

#include "gsn_includes.h"

#include "security/wpa_if/sys_wpa_if/inc/gsn_blobif.h"

typedef const GSN_BLOB_T *
(*GsnBlobIf_Get_FP_T)( GSN_BLOB_T **pBlobList, const char *pName);
extern _RPST_ GsnBlobIf_Get_FP_T GsnBlobIf_Get_FP;

typedef VOID (*GsnBlobIf_Add_FP_T)( GSN_BLOB_T **pBlobList, GSN_BLOB_T *pBlob);
extern _RPST_ GsnBlobIf_Add_FP_T GsnBlobIf_Add_FP;

typedef GSN_STATUS
(*GsnBlobIf_DeleteAll_FP_T)( GSN_BLOB_T **pBlobList );
extern _RPST_ GsnBlobIf_DeleteAll_FP_T GsnBlobIf_DeleteAll_FP;


#endif /* _GSN_BLOBIF_FPT_ */