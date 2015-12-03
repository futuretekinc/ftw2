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
* gsn_cloud_exosite.h
*
*  Created on: 28-May-2013
*      Author: Dhanya Lakshmi
*/

#ifndef GSN_CLOUD_EXOSITE_H_
#define GSN_CLOUD_EXOSITE_H_

#include "gsn_cloud_private.h"
#include "gsn_cloud_api.h"

#define HTTP_RESPONSE_200 "200"
#define HTTP_RESPONSE_204 "204"
#define HTTP_RESPONSE_409 "409"

/**
 ******************************************************************************
 * @file gsn_cloud_api.h
 * @brief Exosite Apis.
 *     This file contains declarations for exosite specific functionality
 ******************************************************************************/

/**
 *******************************************************************************
 * @ingroup GsnCloudApis
 * @brief function to get the exosite server address
 * @param appContext - application context
 ******************************************************************************/

void Gsn_ExositeGetCloudAddress(CLOUD_CONTEXT_DATA_T* cloudUpdater);

/**
 ******************************************************************************
 * @defgroup GsnCloudApis
 * @brief formats the request for exosite device activation
 ******************************************************************************/

void Gsn_ExositeFormatActivationRequest(CLOUD_CONTEXT_DATA_T* cloudUpdater);

PUBLIC GSN_STATUS Gsn_ActivateExositeDevice();

PUBLIC GSN_STATUS_T Gsn_CloudStackAlloc(UINT8** pStack, UINT16 pStackSize, UINT16 *allocatedStackSize);

PUBLIC VOID Gsn_ExositeInit(GSN_APP_CLOUD_CONTEXT_T* appContext);

PUBLIC GSN_STATUS Gsn_GetSensorUpdatesandPost();

GSN_STATUS GsnExosite_GetLoadControl();

VOID GsnExosite_GetConfig(UINT32 updateInterval);

GSN_STATUS Gsn_ExositeSetLoadControl();

#endif /* GSN_CLOUD_EXOSITE_H_ */
