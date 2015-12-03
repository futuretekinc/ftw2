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
* gsn_cloud_private.h
*
*  Created on: 29-May-2013
*      Author: Dhanya Lakshmi
*/

#ifndef GSN_CLOUD_PRIVATE_H_
#define GSN_CLOUD_PRIVATE_H_

/**
 ******************************************************************************
 * @file gsn_cloud_private.h
 * @brief Cloud private Apis.
 *     This file contains declaration for cloud connectivity.
 *     These apis are internal to the cloud_connect
 ******************************************************************************/

#include "gsn_includes.h"
#include "gsn_httpc.h"

#include "gsn_cloud_api.h"

#define BUF_SIZE 1024
#define STACK_5K 5120
#define STACK_3K 3072
#define STR_LEN 256
#define CLOUD_TYPE_LEN 30
#define ADK_TYPE_LEN 20
#define IPADDRESS_LEN 32
/**
 *******************************************************************************
 * @ingroup GsnCloudApis
 * @brief stores the cloud context required to HTTP connection,  cloud authentication key
 * and other information required to talk to the cloud
 ******************************************************************************/
typedef struct CLOUD_CONTEXT_DATA
{
	GSN_HTTPC_CONF_INFO_T httpConfInfo;
	INT8 httpRxBuf[BUF_SIZE];
	INT8 httpRequestBuf[BUF_SIZE];
	INT8 httpResHeaderBuf[BUF_SIZE];
	INT8 readingPath[STR_LEN];
	INT8 configPath[STR_LEN];
	void *httpConn;
	BOOL bConnReady;
	UINT16 portNo;
	INT8 CIK[CLOUD_KEY_LEN];
	INT8 serverName[STR_LEN];
	UINT32 updateInterval;
	INT8 ipAddressString[IPADDRESS_LEN];
	INT8 devicePath[STR_LEN];
	BOOL continueRunning;
	INT8 uid[UID_LEN];
	UINT32 requestBufLen;
	enum GSN_ADK_TYPE adkType;
	enum GSN_CLOUD_TYPE cloudType;
	INT16 loadStatus;
	GSN_APP_CLOUD_CB_FN cbFn;
	GSN_CLOUD_CALLBACK_DATA_T cloudCallbackData;
}CLOUD_CONTEXT_DATA_T;

/**
 *******************************************************************************
 * @ingroup GsnCloudApis
 * @brief function pointer for app specific formatting data
 * each ADK posts different sensor data to the cloud
 * @param cloudUpdater - cloud Context;
 ******************************************************************************/
typedef void(*GSN_CLOUD_DATA_FORMAT_FN)(CLOUD_CONTEXT_DATA_T* cloudUpdater);

#endif /* GSN_CLOUD_PRIVATE_H_ */
