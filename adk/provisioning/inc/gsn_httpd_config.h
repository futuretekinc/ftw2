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
* $RCSfile: gsn_httpd_config.h,v
*/

#ifndef GSN_HTTPD_CONFIG_H_
#define GSN_HTTPD_CONFIG_H_

#include "gsn_includes.h"
#include "gsn_sys_config.h"

/**
 *******************************************************************************
 * @file gsn_httpd_config.h
 * @brief GSN HTTPD Configuration API Functions
 *    This file contains declarations of Functions providing the HTTP
 *    Configuration API.
 ******************************************************************************/

/**
 ******************************************************************************
 * @ingroup GsnHttpApis
 * @brief Definition of callback function for HTTP Configuraiton API
 ******************************************************************************/
typedef void(*GSN_HTTPD_API_CONFIG_CB_FN)(GSN_SYS_CONFIG_T *pConfig, UINT8 method);

/**
 *******************************************************************************
 * @ingroup GsnHttpApis
 * @brief Initialize HTTP Configuration API module
 *    This function initializes the Configuration API module based on the
 *    callback function provided
 * @param cbFn - IN Pointer to callback function
 ******************************************************************************/
UINT8 GsnHttpdApi_ConfigInit(GSN_HTTPD_API_CONFIG_CB_FN cbFn);

/**
 *******************************************************************************
 * @ingroup GsnHttpApis
 * @brief UnInitialize HTTP Configuration API module
 *    This function Uninitializes the Configuration API module 
 *    
 ******************************************************************************/
VOID GsnHttpdApi_ConfigDeInit();

UINT8 GsnHttpdApi_FwInit(UINT32 wlanVer, UINT8* appVersion);

#endif /* GSN_HTTPD_CONFIG_H_ */
