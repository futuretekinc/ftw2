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
* $RCSfile: app_cloud_helper.c
*
*  Created on: 17-May-2013
*      Author: Dhanya Lakshmi
*/

#include "gsn_cloud_updater.h"
#include "app_cloud_helper.h"
#include "gsn_cloud_tls.h"

#include "app_tls.h"
#include "app_debug.h"
#include "app_rtc_mem.h"

#define ADK_TYPE "TLS"
#define DEFAULT_UPDATE_TIME 5000


APP_MAIN_CTX_T *s_pAppMainCntxt;


GSN_STATUS
App_LoadCIK(INT8* pCIK)
{
    F_FILE *fp;
    int ret = 0;

    fp = f_open("exosite.data","r");
    if (!fp)
    {
        return GSN_FAILURE;
    }
#if 0
    else
    {
        f_close(fp);
        return GSN_FAILURE;
    }
#endif

    long file_size = f_filelength("exosite.data");
    if(file_size != CLOUD_KEY_LEN)
    {
        f_close(fp);
        return GSN_FAILURE;
    }

    ret = f_read(pCIK, 1, CLOUD_KEY_LEN, fp);
    if(ret != file_size)
    {
        f_close(fp);
        return GSN_FAILURE;
    }

    f_close(fp);

    return GSN_SUCCESS;
}

GSN_STATUS
App_SaveCIK(INT8* pCIK)
{
    F_FILE *fp;

    f_delete("exosite.data");

    fp = f_open("exosite.data","w+");
    if (!fp)
    {
        return GSN_FAILURE;
    }

    if(f_write(pCIK, 1, CLOUD_KEY_LEN, fp) != CLOUD_KEY_LEN)
    {
        f_close(fp);
        return GSN_FAILURE;
    }

    f_close(fp);

    return GSN_SUCCESS;
}


void App_CloudUpdaterCb(enum GSN_CALLBACK_METHOD method, GSN_CLOUD_CALLBACK_DATA_T* cloudData)
{
    UINT32 battery = 0, TLSdata[2] = {0,0};
    GSN_WIF_WLAN_RSSI_T    wRssi;
    GSN_TLS_ADK_DATA_T * data;
    APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
    AppDbg_Printf("in callback function\r\n");
	
	if(method == GET_DATA)
	{
		AppDbg_Printf("+ App_CloudUpdaterCb method 1\r\n");

		data = (GSN_TLS_ADK_DATA_T*)cloudData->adkData;
		AppTls_TempOrLightGet( TLSdata );
		GsnWdd_RSSIGet(&s_pAppMainCntxt->if0.wddCtx, (INT8*) &wRssi, sizeof(wRssi));
		data->temp = TLSdata[0];
		data->light = TLSdata[1];
		data->battery = battery;
		data->signalstrength = wRssi.rssi;
		AppDbg_Printf("### Get ## adc data temp : %d , lux : %d RSSI %d \r\n", TLSdata[0], TLSdata[1], (signed char)wRssi.rssi);
		
		AppDbg_Printf("- App_CloudUpdaterCb method 1\r\n");
	}
	if(method == GET_KEY)
	{
    #if 0
	    f_enterFS();
	    f_chdrive(0);
        App_LoadCIK(cloudData->cloudKey);
    #endif
        // retrieve the CIK from RTC memory
        AppDbg_Printf("pAppRtcLtchInfo->cloudCIK.CIK = %s\r\n",pAppRtcLtchInfo->cloudCIK.CIK);
        strcpy(cloudData->cloudKey,pAppRtcLtchInfo->cloudCIK.CIK);
	}
	if(method == STORE_KEY)
	{
    #if 0
	    f_enterFS();
	    f_chdrive(0);
		// store the CIK in non volatile memory
	    App_SaveCIK(cloudData->cloudKey);
    #endif
    
        // store the CIK in RTC latchmemory
        strcpy(pAppRtcLtchInfo->cloudCIK.CIK,cloudData->cloudKey);
        AppDbg_Printf("pAppRtcLtchInfo->cloudCIK.CIK = %s\r\n",pAppRtcLtchInfo->cloudCIK.CIK);
	}
}



void App_CloudUpdaterInit(APP_MAIN_CTX_T *pAppCtx)
{
	GSN_APP_CLOUD_CONTEXT_T cloudContext;
	s_pAppMainCntxt = pAppCtx;
	cloudContext.cloudCallbackFn = App_CloudUpdaterCb;
	cloudContext.cloudType = EXOSITE;
	AppDbg_Printf("App_CloudUpdaterInit before copying adk type\r\n");
	cloudContext.adkType = TLS_ADK;
	strcpy(cloudContext.uid,(char*)pAppCtx->config.sysIdConfig.uid);

	AppDbg_Printf("pAppCtx->config.sysIdConfig.uid = %s\r\n",pAppCtx->config.sysIdConfig.uid);
	AppDbg_Printf("cloudContext.UID = %s\r\n",cloudContext.uid);

	cloudContext.updateInterval = DEFAULT_UPDATE_TIME;
	Gsn_CloudUpdaterStart(&cloudContext,FALSE);

}

void App_CloudUpdaterResume()
{
	Gsn_CloudUpdaterResume();
}


void App_CloudUpdaterDeInit()
{
	Gsn_CloudUpdaterStop();

}
