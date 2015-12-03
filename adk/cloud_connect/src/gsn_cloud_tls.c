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
* gsn_cloud_tls.c
*
*  Created on: 21-May-2013
*      Author: Dhanya Lakshmi
*/
#include "gsn_cloud_tls.h"
#include "gsn_version.h"

void Gsn_TlsFormatData(CLOUD_CONTEXT_DATA_T* cloudUpdater)
{
	UINT8 led_control;
	INT8* reqBuf;
	GSN_TLS_ADK_DATA_T *data;
	printf("Gsn_TlsFormatData +\r\n");
	if (cloudUpdater->cbFn)
		        (*cloudUpdater->cbFn)(GET_DATA, &cloudUpdater->cloudCallbackData);

    led_control = 1;
    data = (GSN_TLS_ADK_DATA_T*)cloudUpdater->cloudCallbackData.adkData;
    printf("temp = %d,light = %d, rssi = %d\r\n",data->temp,data->light, (signed char)data->signalstrength);
    /* here call the callback function to retreive the TLS value */

    reqBuf = cloudUpdater->httpRequestBuf;
    if(strcmp(GSN_CHIP_VERSION,"gs2000") == 0)
    	cloudUpdater->requestBufLen = sprintf(reqBuf,"led_control=%d&temp=%d&light=%d&signal=%d&battery=%d&chip=%s",led_control,data->temp,data->light,(signed char)data->signalstrength,data->battery,GSN_CHIP_VERSION);
    else if(strcmp(GSN_CHIP_VERSION,"gs1011") == 0)
    	cloudUpdater->requestBufLen = sprintf(reqBuf,"led_control=%d&temp=%d&light=%d&signal=%d&battery=%d&chip=%s",led_control,data->temp,data->light,(signed char)data->signalstrength,data->battery,GSN_CHIP_VERSION);

	printf("Gsn_TlsFormatData -\r\n");
}
