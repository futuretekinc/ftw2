/*******************************************************************************
*
*               COPYRIGHT (c) 2009-2010 GainSpan Corporation
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
* $RCSfile: gsn_otafu_dsv.h,v
*/

#ifndef GSN_OTAFU_DSV_H_
#define GSN_OTAFU_DSV_H_

/**
 *******************************************************************************
 * @file gsn_otafu_dsv.h
 * @brief GSN OTAFU DSV implementation of multipart/form-data upload.
 *    This file contains declarations of Functions providing the OTAFU
 *    interface for applications
 ******************************************************************************/

/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/


/**
 *******************************************************************************
 * @defgroup GsnOtafuDsv Api 
 * @brief  API's for DSV OTAFU
 *
 *  OTAFU API's provide applications a way to register handler for handling
 *  firmware update posted using multipart/form-data
 ******************************************************************************/

/**
 *****************************************************************************
 *
 * @}
 *****************************************************************************/
#ifdef ADK_OTAFU_DSV	

#include <stddef.h>
#include "gsn_includes.h"
#include "modules/xml_parser/test/modules/gsn_xml.h"
#include "modules/http/gsn_httpd.h"
#include "modules/http/gsn_httpd_util.h"
#include "modules/http/gsn_httpd_debug.h"
#include "modules/http/gsn_httpd_file_api.h"
#include "main/gsn_br_flashldr.h"
#include "modules/fwup/gsn_fwup.h"
#include "modules/fwup/gsn_ext_fwup.h"
#include "../inc/gsn_otafu.h"

#define GSN_OTAFU_DSV_SIGN_LEN 512

#define GSN_OTAFU_DSV_HASH_LEN 20
/**
 ******************************************************************************
 * @ingroup GsnOtafuDsv
 * @brief Definition of context needed for OTAFU.
 ******************************************************************************/
typedef struct GSN_OTAFU_DSV_CTX
{
	struct crypto_hash *sha1Ctx;

	UINT8 *rootCertName;	
	UINT8 *serverCertName;

	UINT8 *signatureBuf;
	UINT32 signatureLen;
	UINT8 dataHash[GSN_OTAFU_DSV_HASH_LEN];
	
} GSN_OTAFU_DSV_CTX_T;

/**
 *******************************************************************************
 * @ingroup GsnExtOtafu Api
 * @brief Initialize ADK OTAFU module
 *    This function initializes the OTAFU module by registering the system
 *    default URI for firmware update and sets up callback functions to
 *    handle events from http server.
 * @param pOtafuCtx - IN Pointer to OTAFU context
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnOtafuDsv_Init (GSN_OTAFU_DSV_CTX_T *otafuDsvCtx);

PUBLIC VOID
GsnOtafuDsv_DeInit (GSN_OTAFU_DSV_CTX_T *otafuDsvCtx);

PUBLIC VOID
GsnOtafuDsv_Sha1Init(GSN_OTAFU_DSV_CTX_T *otafuDsvCtx);


PUBLIC VOID
GsnOtafuDsv_Sha1Update(GSN_OTAFU_DSV_CTX_T *otafuDsvCtx, INT8 *buffer, UINT32 dataLen);

PUBLIC VOID
GsnOtafuDsv_Sha1Finish(GSN_OTAFU_DSV_CTX_T *otafuDsvCtx);

PUBLIC GSN_STATUS_T
GsnOtafuDsv_SignUpdate(GSN_OTAFU_DSV_CTX_T *otafuDsvCtx, INT8 *buffer, UINT32 bufferLen);

PUBLIC GSN_STATUS_T
GsnOtafuDsv_Verify(GSN_OTAFU_DSV_CTX_T *otafuDsvCtx);

#endif
#endif /* GSN_OTAFU_DSV_H_ */
