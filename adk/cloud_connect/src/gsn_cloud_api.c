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
* gsn_cloud_api.c
*
*  Created on: 21-May-2013
*      Author: Dhanya Lakshmi
*/

#include "gsn_includes.h"
#include "gsn_cloud_exosite.h"
#include "gsn_cloud_private.h"


enum GSN_CLOUD_TYPE cldType;

GSN_STATUS Gsn_CreateCloudStack(UINT8** pStack, UINT16 pStackSize, UINT16 *allocatedStackSize)
{
	GSN_STATUS retVal = GSN_FAILURE;
	if(cldType == EXOSITE)
		retVal = Gsn_CloudStackAlloc(pStack,pStackSize,allocatedStackSize);
	return retVal;
}



GSN_STATUS Gsn_CloudActivateDevice()
{
	GSN_STATUS retVal = GSN_FAILURE;
	if(cldType == EXOSITE)
		retVal = Gsn_ActivateExositeDevice();
	return retVal;
}



/*
retrieve the sensor updates the respective ADK
format the data as required by the cloud
*/
GSN_STATUS Gsn_cloudPostUdpates()
{
	GSN_STATUS retVal = GSN_FAILURE;
	if(cldType == EXOSITE)
		retVal = Gsn_GetSensorUpdatesandPost();
	return retVal;
}

void Gsn_CloudApiInit(GSN_APP_CLOUD_CONTEXT_T* appContext)
{
	cldType = appContext->cloudType;
	if(appContext->cloudType == EXOSITE)
		Gsn_ExositeInit(appContext);
}

VOID GsnCloud_GetConfig(UINT32 updateInterval)
{
	GsnExosite_GetConfig(updateInterval);
}

