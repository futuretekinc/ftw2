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
* $RCSfile: gsn_ext_otafu.h,v
*/

#ifndef GSN_EXT_OTAFU_H_
#define GSN_EXT_OTAFU_H_

/**
 *******************************************************************************
 * @file gsn_otafu.h
 * @brief GSN OTAFU implementation of multipart/form-data upload.
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
 * @defgroup GsnExtOtafuApi ADK EXT OTAFU API
 * @brief  API's for External Flash OTAFU
 *
 *  OTAFU API's provide applications a way to register handler for handling
 *  firmware update posted using multipart/form-data
 ******************************************************************************/

/**
 *****************************************************************************
 *
 * @}
 *****************************************************************************/


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


#define GSN_HTTP_EXT_OTAFU_API_PATH "/gainspan/system/extfwuploc"
#define GSN_EXT_FLASH_OTAFU_FW     1
#define GSN_EXT_FLASH_OTAFU_SIGN   2

/**
 ******************************************************************************
 * @ingroup GsnExtOtafuApi
 * @brief Definition of context needed for OTAFU.
 ******************************************************************************/
typedef struct GSN_EXTOTAFU_CTX
{
	GSN_OTAFU_CTX_T otafuCtx;
	GSN_EXTFWUP_CTX_T extFwupCtx;
	
#ifdef ADK_OTAFU_DSV	
	GSN_OTAFU_DSV_CTX_T otafuDsvCtx;
#endif

} GSN_EXTOTAFU_CTX_T;

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
GsnExtOtafu_FwupInit(GSN_EXTOTAFU_CTX_T *pCtx);

PUBLIC VOID
GsnExtOtafu_Init(GSN_EXTOTAFU_CTX_T* pCtx);


#endif /* GSN_EXT_OTAFU_H_ */
