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
* gsn_cloud_sp.c
*
*  Created on: 21-May-2013
*      Author: Dhanya Lakshmi
*/
#include "gsn_cloud_sp.h"
#include "app_debug.h"

void Gsn_SpFormatData(CLOUD_CONTEXT_DATA_T* cloudUpdater)
{
    INT8* reqBuf;
    UINT8 rssi;
    int rssiInt;
    GSN_SP_ADK_DATA_T *data;

    printf("Gsn_SpFormatData +\r\n");
    if (cloudUpdater->cbFn)
	(*cloudUpdater->cbFn)(GET_DATA, &cloudUpdater->cloudCallbackData);

    data = (GSN_SP_ADK_DATA_T*)cloudUpdater->cloudCallbackData.adkData;
    rssi = ~data->signalstrength +1;
    rssiInt = -rssi;
    AppDbg_Printf(" current = %s,freq = %s, power = %s,powerfactor = %s,volts = %s,rssiInt = %d load = %s\r\n",data->currentStr,data->freqStr,data->powerStr,data->powerFactorStr,data->voltsStr,rssiInt,data->loadStateStr);
    reqBuf = cloudUpdater->httpRequestBuf;
    cloudUpdater->requestBufLen = sprintf(reqBuf,"freq=%s&power=%s&voltage=%s&current=%s&energy=%s&powerfactor=%s&sig=%d&load_control=%s",data->freqStr,data->powerStr,data->voltsStr,data->currentStr,data->eUnitStr,data->powerFactorStr,rssiInt, data->loadStateStr);

    printf("Gsn_SpFormatData -\r\n");
}

void Gsn_SpCloudGetLoadStatus(CLOUD_CONTEXT_DATA_T* cloudUpdater)
{
	(*cloudUpdater->cbFn)(GET_LOAD_STATUS, &cloudUpdater->cloudCallbackData);
}

void Gsn_SpCloudSetLoadStatus(CLOUD_CONTEXT_DATA_T* cloudUpdater)
{
	GSN_SP_ADK_DATA_T *data = (GSN_SP_ADK_DATA_T*)cloudUpdater->cloudCallbackData.adkData;
	// first get the load status from the hardware.
	// if it is different from the one on the exosite portal. then take action
	if(data->liveControl != cloudUpdater->loadStatus)
	{
		data->liveControl = cloudUpdater->loadStatus;
		(*cloudUpdater->cbFn)(SET_LOAD_STATUS, &cloudUpdater->cloudCallbackData);
	}
}

GSN_STATUS
GsnSp_ProcessGetLoadResponse(INT8* pHttpResponseBuffer,CLOUD_CONTEXT_DATA_T *cloudUpdater)
{
	INT8 *a;
	INT8 len = 1;
	INT8 loadStatus[2];
	INT8 loadState;
        char** responseHeader;
	AppDbg_Printf("Gsn_CloudProcessGetResponse response buf = %s\r\n",pHttpResponseBuffer);
    
    responseHeader= cloudUpdater->httpConfInfo.resHeadersPtr;

	if(NULL != pHttpResponseBuffer)
	   {
		if(!(strncmp((const INT8 *)pHttpResponseBuffer,HTTP_RESPONSE_200,3)))
		{
			AppDbg_Printf("[Gsn_CloudProcessGetResponse] Response Message is 200 OK\r\n");

				a = strstr(pHttpResponseBuffer,"lc_request=");
				a = a + 11;
				if(a != NULL)
				{
					AppDbg_Printf("a = %s\r\n",a);
					AppDbg_Printf("strlen(a) = %d \r\n",strlen(a));
					strncpy(loadStatus,a,len);

					AppDbg_Printf("loadStatus = %s\r\n",loadStatus);
					loadState = atoi(loadStatus);
					cloudUpdater->loadStatus = loadState;
					AppDbg_Printf("loadState = %d\r\n",loadState);
					return GSN_SUCCESS;
				}
         }
		if(!(strncmp((const INT8 *)pHttpResponseBuffer,HTTP_RESPONSE_204,3)))
		{
			AppDbg_Printf("[Gsn_CloudProcessGetResponse] Response Message is 204 NO Content\r\n");
			// check for content-length. if 0 then no data
			if(responseHeader[TM_HTTP_HEADER_CONTENT_LENGTH] != NULL)
			{
				AppDbg_Printf("content length = %s\r\n",responseHeader[TM_HTTP_HEADER_CONTENT_LENGTH]);
				if(!(strcmp(responseHeader[TM_HTTP_HEADER_CONTENT_LENGTH],"0")))
				{
					AppDbg_Printf("setting load to -1\r\n");
					cloudUpdater->loadStatus = -1;
					AppDbg_Printf("cloudUpdater->loadStatus = %d\r\n",cloudUpdater->loadStatus);
					return GSN_SUCCESS;
				}
			}
		}
	   }
	   return GSN_FAILURE;
}
