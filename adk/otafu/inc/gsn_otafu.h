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
* $RCSfile: gsn_otafu.h,v
*/

#ifndef GSN_OTAFU_H_
#define GSN_OTAFU_H_

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
 * @defgroup GsnOtafuApi ADK OTAFU API
 * @brief  API's for OTAFU
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
#include "gsn_otafu_dsv.h"

#define GSN_HTTP_OTAFU_API_NAME "gs_sys_otafu"
#define GSN_HTTP_OTAFU_API_VERSION "0.1.0"
#define GSN_HTTP_OTAFU_API_PATH "/gainspan/system/fwuploc"
#define GSN_FLASH_OTAFU_FW     1
#define GSN_FLASH_OTAFU_SIGN   2

#define GSN_OTAFU_FW_TAG_LEN     8
#define GSN_OTAFU_SIGN_TAG_LEN   12

#define GSN_OTAFU_SUCCESS			0
#define GSN_OTAFU_INIT_FAIL			1
#define GSN_OTAFU_INVALID_TAG		2
#define GSN_OTAFU_WRITE_FAIL		3
#define GSN_OTAFU_CB_UPDATE_FAIL	4

/**
 ******************************************************************************
 * @ingroup GsnOtafuApi
 * @brief Definition of callback function for Notifying app of events
 ******************************************************************************/
typedef VOID (*GSN_OTAFU_CB_FN)(VOID* ctx, UINT8 event);

/**
 ******************************************************************************
 * @ingroup GsnOtafuApi
 * @brief Definition of context needed for OTAFU.
 ******************************************************************************/
typedef struct GSN_OTAFU_CTX
{
    GSN_OTAFU_CB_FN cbFn;           /**< Callback funciton for notifying app */
    VOID* cbFnCtx;
    GSN_FWUP_CTX_T fwupCtx;
	
	INT32 status;

#ifdef ADK_OTAFU_DSV	
	GSN_OTAFU_DSV_CTX_T otafuDsvCtx;
#endif

} GSN_OTAFU_CTX_T;

/**
 ******************************************************************************
 * @ingroup GsnOtafuApi
 * @brief Definition of events sent to app
 ******************************************************************************/
typedef enum
{
    GSN_OTAFU_EVENT_INIT_FAIL,                /**< Initialization failed */
    GSN_OTAFU_EVENT_FWUP_FAIL,   /**< Copying to ext flash failed*/
    GSN_OTAFU_EVENT_FWUP_SUCCESS,/**< Copying from ext flash to int flash started */
    GSN_OTAFU_EVENT_DEINIT                    /**< Deinitialization */
} GSN_OTAFU_EVENTS_T;

/**
 *******************************************************************************
 * @ingroup GsnOtafuApi
 * @brief Initialize ADK OTAFU module
 *    This function initializes the OTAFU module by registering the system
 *    default URI for firmware update and sets up callback functions to
 *    handle events from http server.
 * @param pOtafuCtx - IN Pointer to OTAFU context
 ******************************************************************************/
PUBLIC VOID GsnOtafu_Init(GSN_OTAFU_CTX_T *pOtafuCtx);

/**
 *******************************************************************************
 * @ingroup GsnOtafuApi
 * @brief Copy from External flash to Internal flash
 *    This function copies the images from External flash to internal flash.
 *    This should be invoked after the images are copied successfully into
 *    external flash and a response is sent to the HTTP client sending
 *    the firmware images.
 * @param pOtafuCtx - IN Pointer to OTAFU context
 ******************************************************************************/
GSN_STATUS GsnOtafu_IntFlashCopy(GSN_OTAFU_CTX_T *pCtx);

#endif /* GSN_OTAFU_H_ */
