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
* $RCSfile: gsn_httpd_prov.h,v
*/

#ifndef GSN_HTTPD_PROV_H_
#define GSN_HTTPD_PROV_H_

#include "gsn_wlan_scan.h"

/**
 *******************************************************************************
 * @file gsn_httpd_prov.h
 * @brief ADK Provisioning API Functions
 *    This file contains declarations of Functions providing the HTTP
 *    Provisioning API.
 ******************************************************************************/

/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/


/**
 *******************************************************************************
 * @defgroup GsnHttpApis Provisioning and Configuration ADK HTTP REST Style APIs
 * @brief  HTTP REST Style API's for System Configuration and Provisioning
 *
 *    The HTTP API's provide a REST style API for system configuration
 *    and provisioning. These include API's for configuring client and AP
 *    settings.
 ******************************************************************************/

/**
 *****************************************************************************
 *
 * @}
 *****************************************************************************/

/**
 ******************************************************************************
 * @ingroup GsnHttpApis
 * @brief Definition of callback function for WPS Provisioning
 ******************************************************************************/
typedef void (*GSN_HTTPD_PROV_WPS_CB_FN_T)(char*, char*);

/**
 ******************************************************************************
 * @ingroup GsnHttpApis
 * @brief Definition of context needed for provisioning.
 ******************************************************************************/
typedef struct GSN_HTTPD_PROV_CONFIG
{
    GSN_WDD_CTX_T* pWdd; /**< Pointer to WDD L2 context */
    GSN_HTTPD_PROV_WPS_CB_FN_T pWpsCbFn; /**< Pointer to WPS callback function*/
    GSN_WLAN_REG_DOMAIN_T domain; /**< Regulatory domain */
} GSN_HTTPD_PROV_CONFIG_T;


/**
 *******************************************************************************
 * @ingroup GsnHttpApis
 * @brief Initialize HTTP Provisioning API module
 *    This function initializes the Provisioning API module based on the
 *    configuration parameter provided
 * @param pConfig - IN Pointer to Provisioning configuraiton structure
 ******************************************************************************/
void GsnHttpdApi_ProvInit(GSN_HTTPD_PROV_CONFIG_T *pConfig);

/**
 *******************************************************************************
 * @ingroup GsnHttpApis
 * @brief Un-Initialize HTTP Provisioning API module
 *    This function un-initializes the Provisioning API module.
 ******************************************************************************/
void GsnHttpdApi_ProvDeInit();

#endif /* GSN_HTTPD_PROV_H_ */
