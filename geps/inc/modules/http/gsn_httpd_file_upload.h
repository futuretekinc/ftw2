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

#ifndef GSN_FILE_UPLOAD_H_
#define GSN_FILE_UPLOAD_H_

/**
 *******************************************************************************
 * @file gsn_httpd_file_upload.h
 * @brief GSN HTTP_FILE_UPLOAD implementation of HTTP based file upload.
 *    This API supports file upload to any partition in file system
 ******************************************************************************/

/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/


/**
 *******************************************************************************
 * @defgroup GsnFsUploadApi Gsn HTTP File Upload API
 * @brief  API's for HTTP_FILE_UPLOAD
 *
 *  HTTP_FILE_UPLOAD API's provide applications a way to support file upload
 *  to file system partitions via HTTP
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
#include "fs/api/api_safe.h"

#define GSN_HTTP_FILE_UPLOAD_API_PATH "/gainspan/system/fsupload"
#define GSN_HTTPD_PATHDELIMITER "/"

#define GSN_MOD_FLASH_DRIVE_NUM_0 0
#define GSN_MOD_FLASH_DRIVE_NUM_1 1
#define GSN_EXT_FLASH_DRIVE_NUM_2 2
#define GSN_EXT_FLASH_DRIVE_NUM_3 3



/**
 *******************************************************************************
 * @ingroup GsnFsUploadApi
 * @brief Initialize ADK FILE UPLOAD module
 *    This function initializes the FS_UPLOAD module by registering the system
 *    default URI for file upload and sets up callback functions to
 *    handle events from http server.
 *******************************************************************************/
PUBLIC VOID GsnFsUpload_Init();


#endif /* GSN_FILE_UPLOAD_H_ */
