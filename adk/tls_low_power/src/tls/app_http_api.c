/*******************************************************************************
*
*               COPYRIGHT (c) 2009-2010 GainSpan Corporation
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
* $RCSfile: tls_http_api.c,v
*/

/*
 * tls_http_api.c
 *
 *  Created on: Jun 23, 2011
 *      Author: PViswanathan
 */
/*******************************************************************************
 * File Inclusions
 ******************************************************************************/

#include <stddef.h>
#include "gsn_includes.h"
#include "modules/http/gsn_httpd.h"
#include "modules/http/gsn_httpd_util.h"
#include "modules/http/gsn_httpd_debug.h"

#include "app_events.h"
#include "config/app_resource_config.h"
#include "config/app_cfg.h"
#include "fs_if/app_fsIf.h"
#include "gsn_ncm.h"
#include "config/app_cfg.h"
#include "app_main_ctx.h"
#include "app_sm.h"
#include "app_ncm.h"
#include "app_resource_config.h"
#include "app_events.h"
#include "app_debug.h"
#include "app_tls.h"
#include "tls/app_http_api.h"


#define APP_API_XML
/*
#define APP_API_JSON
*/
UINT32 updateCnt = 0;

UINT8 ledStatus = 0;

UINT8
App_GetLedStatus(VOID)
{
	return ledStatus;
}

VOID
App_LedStatusSet(UINT8 status)
{
	ledStatus = status;
	if(status)
	{
		GsnGpio_OutIndvidualSet(LED_GPIO_9);   // gpio become high
	}
	else
	{
		GsnGpio_OutClear(LED_GPIO_9);
	}
}
PRIVATE INT32
AppTls_CreateXmlResp(APP_MAIN_CTX_T *pAppCtx, INT8* buffer, ttHttpdUserConHandle conHandle)
{
    int errorCode;
    UINT32 battery = 0, TLSdata[2] = {0,0};
    GSN_WIF_WLAN_RSSI_T    wRssi;

	UINT8 LEDStatus;
    INT8 *LEDstsPtr;

    AppTls_TempOrLightGet( TLSdata );
    GsnWdd_RSSIGet(&pAppCtx->if0.wddCtx, (INT8*) &wRssi, sizeof(wRssi));
    AppDbg_Printf("### Get ## adc data temp : %d , lux : %d RSSI %d \r\n", TLSdata[0], TLSdata[1], (signed char)wRssi.rssi);
#if 0
    AppTls_TempSensorDataGet(pAppCtx, &temp);
    AppTls_LightSensorDataGet(pAppCtx, &light);
    AppTls_BatteryValueGet(pAppCtx, &battery);
	
    rssi1 = AppNcm_RSSIValueGet(&pTlsAppSmCtx->ncm);
    rssi2 = ~rssi1 + 1;
    rssiInt = -rssi2;
    battery = battery;
#endif
#ifdef APP_API_JSON
    sprintf(buffer, "{\"version\":\"%s\",\"lux\":%d,\"temp\":%d,"
            "\"battery\":%d,\"rssi\":%d}",
            TLS_HTTP_API_VERSION, light, temp, battery, rssiInt);
#else
	LEDStatus = App_GetLedStatus();
	LEDstsPtr = LEDStatus==1?"on":"off";
	
sprintf(buffer, "<tls><version>%s</version><lux>%d</lux><temp>%d</temp>"
            "<battery>%d</battery><rssi>%d</rssi><leds>%s</leds></tls>",
            TLS_HTTP_API_VERSION, TLSdata[1], TLSdata[0], battery, (signed char)wRssi.rssi, LEDstsPtr );
#endif
    GsnHttpd_SendBufferAndLastChunk(conHandle, buffer, strlen(buffer), TM_BLOCKING_ON, &errorCode);
    return 0;
}

GSN_HTTPD_STATUS_T
AppTls_HttpApiCb(ttHttpdUserEvent event, const char* uri, ttHttpdUserConHandle conHandle)
{
    INT32 respLen;
    int errorCode = TM_ENOERROR;
    UINT32 bufferLen;
	APP_MAIN_CTX_T *pAppCtx = globalAppCtxPtr;
    INT8  *buffer = GsnHttpd_GetBuffer();
	INT8 *pPostBody;
    HTTPD_DEBUG_PRINT(("[TLSApp:HTTPApi] Got callback\r\n"));

    if (GsnHttpd_GetHttpMethod(conHandle) == TM_HTTP_METHOD_POST)
    {
        //sprintf(buffer, "<error>POST not allowed</error>");
        //GsnHttpd_SendBufferAndLastChunk(conHandle, buffer, strlen(buffer), TM_BLOCKING_ON, &errorCode);
        //return GSN_HTTPD_SUCCESS;
    }

    switch (event)
    {
        case TM_HTTPD_EVENT_BODY_RECV:
			bufferLen = GSN_HTTPD_BUF_SIZE;
			tfHttpdUserGetRequestBody(conHandle,buffer,(INT32 *)&bufferLen,0);
			pPostBody = buffer; 
			pPostBody[bufferLen]=0;
			pPostBody = strstr(buffer, "<leds>");
			pPostBody += strlen("<leds>");
			if('o'== pPostBody[0] && 'n'== pPostBody[1])
			{
				App_LedStatusSet(1);
			}
			else
			{
				App_LedStatusSet(0);
			}
            break;
        case TM_HTTPD_EVENT_SEND_READY:
            respLen = AppTls_CreateXmlResp(pAppCtx, buffer, conHandle);
            GsnHttpd_SendBufferAndLastChunk(conHandle, buffer, respLen, TM_BLOCKING_ON,
                    &errorCode);
            break;
    }
    if(NULL != buffer)
    {
        GsnHttpd_ReleaseBuffer(buffer);
    }
    return GSN_HTTPD_SUCCESS;
}


UINT8
AppTls_HttpApiInit(VOID)
{
#ifdef APP_API_JSON
    GsnHttpd_UriHandlerConfig(TLS_HTTP_API_PATH,
            GSN_HTTPD_URI_METHOD_GET_POST, "HTTP API's", AppTls_HttpApiCb, GSN_HTTPD_CONTENT_APP_JSON  );
#else
    GsnHttpd_UriHandlerConfig(TLS_HTTP_API_PATH,
            GSN_HTTPD_URI_METHOD_GET_POST, "HTTP API's", AppTls_HttpApiCb, GSN_HTTPD_CONTENT_APP_XML );
#endif

    return 0;
}

UINT8
AppHttp_ApiInit(VOID)
{
    return AppTls_HttpApiInit();
}

VOID
AppTls_HttpApiDeInit()
{

#ifdef APP_API_JSON
    GsnHttpd_UriHandlerConfig(TLS_HTTP_API_PATH, 0, NULL, NULL, 0);
#else
    GsnHttpd_UriHandlerConfig(TLS_HTTP_API_PATH, 0, NULL, NULL, 0);
#endif

}




