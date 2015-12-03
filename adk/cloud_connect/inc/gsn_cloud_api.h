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
* gsn_cloud_api.h
*
*  Created on: 21-May-2013
*      Author: Dhanya Lakshmi
*/

#ifndef GSN_CLOUD_API_H_
#define GSN_CLOUD_API_H_


/**
 ******************************************************************************
 * @file gsn_cloud_api.h
 * @brief Cloud Public Apis.
 *     This file contains declaration for cloud connectivity.
 *     These apis are exposed to the application
 ******************************************************************************/

#include "gsn_includes.h"

#define CLOUD_KEY_LEN 41
#define UID_LEN 13

enum GSN_CALLBACK_METHOD
{
	GET_DATA = 1,
	GET_KEY,
	STORE_KEY,
	GET_LOAD_STATUS,
	SET_LOAD_STATUS
};


/**
 *******************************************************************************
 * @ingroup GsnCloudApis
 * @brief stores the cloud callback data - sensor data and cloud authentication key
 ******************************************************************************/

typedef struct GSN_CLOUD_CALLBACK_DATA
{
	INT8 cloudKey[CLOUD_KEY_LEN];
	void * adkData;

}GSN_CLOUD_CALLBACK_DATA_T;


enum GSN_ADK_TYPE
{
	TLS_ADK = 1,
	SP_ADK = 2
};

enum GSN_CLOUD_TYPE
{
	EXOSITE = 1
};

/**
 *******************************************************************************
 * @ingroup GsnCloudApis
 * @brief retrieve sensor data or write NVDS based on @param method
 *    This function initializes the Configuration API module based on the
 *    callback function provided
 * @param method - method decides whether sensor data is retrieved or the
 * 	  cloud authentication key is stored/retrieved from flash memory
 * @param cloudCallbackData - structure which holds the retrieved data
 ******************************************************************************/

typedef void(*GSN_APP_CLOUD_CB_FN)(enum GSN_CALLBACK_METHOD method, GSN_CLOUD_CALLBACK_DATA_T*  cloudCallbackData);

/**
 *******************************************************************************
 * @ingroup GsnCloudApis
 * @brief stores the app specific context passed from the application
 * including the callback function, adktype, cloud type.
 ******************************************************************************/
typedef struct GSN_APP_CLOUD_CONTEXT
{
	GSN_APP_CLOUD_CB_FN cloudCallbackFn;
	INT8 uid[UID_LEN];
	UINT32 updateInterval;
	enum GSN_ADK_TYPE adkType;
	enum GSN_CLOUD_TYPE cloudType;

}GSN_APP_CLOUD_CONTEXT_T;


/**
 *******************************************************************************
 * @ingroup GsnCloudApis
 * @brief function to initialise the cloud context passed with info from app context
 * @param appContext - application context
 ******************************************************************************/
void Gsn_CloudApiInit(GSN_APP_CLOUD_CONTEXT_T* appContext);


/**
 *******************************************************************************
 * @ingroup GsnCloudApis
 * @brief function to activate the device on cloud
 * @return - success or failure
 ******************************************************************************/
GSN_STATUS Gsn_CloudActivateDevice();

/**
 *******************************************************************************
 * @ingroup GsnCloudApis
 * @brief function to post sensor data to the cloud
 * @return - success or failure
 ******************************************************************************/
GSN_STATUS Gsn_cloudPostUdpates();

/**
 *******************************************************************************
 * @ingroup GsnCloudApis
 * @brief function to get config data from the cloud
 * @return - none
 ******************************************************************************/
VOID GsnCloud_GetConfig(UINT32 updateInterval);

#endif /* GSN_CLOUD_API_H_ */
