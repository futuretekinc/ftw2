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
* gsn_cloud_sp.h
*
*  Created on: 21-May-2013
*      Author: Dhanya Lakshmi
*/

#ifndef APP_CLOUD_SP_H_
#define APP_CLOUD_SP_H_

#include "gsn_cloud_api.h"
#include "gsn_cloud_private.h"
#include "gsn_cloud_exosite.h"

/**
 ******************************************************************************
 * @file gsn_cloud_sp.h
 * @brief Cloud apis for smartplug .
 *     This file contains declarations for smartplug specific cloud functionality
 ******************************************************************************/

#define SP_DATA_LEN 16
#define LOAD_DATA_LEN 8
#define TYPE_LEN 32

/**
 *******************************************************************************
 * @ingroup GsnCloudApis
 * @brief contains the SP sensor data
 ******************************************************************************/
typedef struct GSN_SP_ADK_DATA
{
	UINT8 voltsStr[SP_DATA_LEN];
	UINT8 currentStr[SP_DATA_LEN];
	UINT8 freqStr[SP_DATA_LEN];
	UINT8 powerStr[SP_DATA_LEN];
	UINT8 powerFactorStr[SP_DATA_LEN];
	UINT8 eUnitStr[SP_DATA_LEN];
	UINT8 loadStateStr[LOAD_DATA_LEN];
	UINT8 typeStr[TYPE_LEN];
	UINT8 signalstrength;
	BOOL liveControl;
}GSN_SP_ADK_DATA_T;

/**
 *******************************************************************************
 * @ingroup GsnCloudApis
 * @brief function to format the request for connecting smartplug device
 * @param cloudUpdater - cloud context
 ******************************************************************************/
void Gsn_SpFormatData(CLOUD_CONTEXT_DATA_T* cloudUpdater);

void Gsn_SpCloudGetLoadStatus(CLOUD_CONTEXT_DATA_T* cloudUpdater);

void Gsn_SpCloudSetLoadStatus(CLOUD_CONTEXT_DATA_T* cloudUpdater);


GSN_STATUS
GsnSp_ProcessGetLoadResponse(INT8* pHttpResponseBuffer,CLOUD_CONTEXT_DATA_T *cloudUpdater);


#endif /* APP_CLOUD_SP_H_ */
