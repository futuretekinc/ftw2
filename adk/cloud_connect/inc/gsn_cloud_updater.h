/*******************************************************************************
*
*               COPYRIGHT (c) 2013-2014 GainSpan Corporation
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
* gsn_cloud_updater.h
*
*  Created on: 16-May-2013
*      Author: Dhanya Lakshmi
*/
#ifndef APP_CLOUD_UPDATER_H_
#define APP_CLOUD_UPDATER_H_

#include "gsn_includes.h"
#include "gsn_cloud_api.h"
#include "gsn_cloud_private.h"


/**
 ******************************************************************************
 * @file gsn_cloud_updater.h
 * @brief Posting sensor data to cloud in a loop .
 *     This file contains declarations for starting and stopping the cloud
 *     updation
 ******************************************************************************/
#define CLOUD_UPDATER_THREAD_PRIORITY 12

/**
 *******************************************************************************
 * @ingroup GsnCloudApis
 * @brief function to start posting data to cloud continously, with a time interval
 * @param appContext - application context
 ******************************************************************************/
GSN_STATUS_T Gsn_CloudUpdaterStart( GSN_APP_CLOUD_CONTEXT_T* appContext,BOOL separateThread);


/**
 *******************************************************************************
 * @ingroup GsnCloudApis
 * @brief function to to stop posting data to cloud
 * @param appContext - application context
 ******************************************************************************/
VOID Gsn_CloudUpdaterStop();

VOID Gsn_CloudUpdaterResume();

#endif /* APP_CLOUD_UPDATER_H_ */
