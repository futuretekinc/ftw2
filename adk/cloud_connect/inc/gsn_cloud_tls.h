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
* gsn_cloud_tls.h
*
*  Created on: 21-May-2013
*      Author: Dhanya Lakshmi
*/


#ifndef APP_CLOUD_TLS_H_
#define APP_CLOUD_TLS_H_

#include "gsn_includes.h"
#include "gsn_cloud_api.h"
#include "gsn_cloud_private.h"

/**
 ******************************************************************************
 * @file gsn_cloud_sp.h
 * @brief Cloud apis for TLS .
 *     This file contains declarations for TLS specific cloud functionality
 ******************************************************************************/

/**
 *******************************************************************************
 * @ingroup GsnCloudApis
 * @brief contains the TLS sensor data
 ******************************************************************************/
typedef struct GSN_TLS_ADK_DATA
{
	UINT32 temp;
	UINT32 light;
	UINT32 battery;
	UINT8 signalstrength; /**<  Flag indicating whether change should be applied */

}GSN_TLS_ADK_DATA_T;

/**
 *******************************************************************************
 * @ingroup GsnCloudApis
 * @brief function to format the request for connecting TLS device
 * @param cloudUpdater - cloud context
 ******************************************************************************/
void Gsn_TlsFormatData(CLOUD_CONTEXT_DATA_T* cloudUpdater);

#endif /* APP_CLOUD_TLS_H_ */
