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
* $RCSfile: gsn_blobif.h,v $
*
* Description : This file contains the interfacing APIs and declaration that is
* used to interface with the WPA open source code.
*******************************************************************************/
#ifndef _GSN_BLOB_IF_H_
#define _GSN_BLOB_IF_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/


#include "supplicant/eap_peer/eap_config.h"

typedef struct wpa_config_blob GSN_BLOB_T;


/**
 *******************************************************************************
 * @ingroup GsnBlobIf
 * @brief Get a named configuration blob.
 *
 *    This function gets the named configuration blob.
 * @param pBlobList - IN pointer to blob list.
 * @param pName - IN pointer to the name of the blob.
 * @return Pointer to blob data or %NULL if not found. 
 ******************************************************************************/
const GSN_BLOB_T *
GsnBlobIf_Get( GSN_BLOB_T **pBlobList, const char *pName);

/**
 *******************************************************************************
 * @ingroup GsnBlobIf
 * @brief Add a named configuration blob.
 *
 *    This function adds the named configuration blob.
 * @param pBlobList - IN pointer to blob list.
 * @param pBlob - IN pointer to the blob to be added to the list.
 ******************************************************************************/
VOID GsnBlobIf_Add( GSN_BLOB_T **pBlobList, GSN_BLOB_T *pBlob);


#ifdef __cplusplus
 }
#endif
#endif  /* _GSN_BLOB_IF_H_ */ 
