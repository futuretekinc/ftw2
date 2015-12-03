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
 * $RCSfile: gsn_httpd_prov.c,v $
 *
 * Description : GSN Provision  file
 *******************************************************************************/

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include <string.h>
#include "gsn_includes.h"
#include "modules/http/include/trhttpd.h"

#include "modules/http/gsn_httpd.h"
#include "modules/http/gsn_httpd_util.h"
#include "modules/http/gsn_httpd_debug.h"
#include "modules/xml_parser/test/modules/gsn_xml.h"

/* ADK  includes */
#include "gsn_wlan_scan.h"
#include "gsn_httpd_prov.h"

#include "gsn_prov_xml_schema.c"
#include "gsn_httpd_prov_fpt.h"


/*******************************************************************************
 *  Private Definitions
 ******************************************************************************/


#define GSN_HTTPD_SCAN_DELAY
#undef GSN_HTTPD_SCAN_TIMESTAMP
#undef GSN_HTTPD_ENABLE_SCAN_SOCK_OPT

/*******************************************************************************
 *  Public Functions
 ******************************************************************************/

#define GSN_SSID_DEFAULT_FILTER "*"
#define GSN_HTTPD_MAX_SCAN_ELEMENTS 10

PRIVATE UINT8 s_ssidFilter[32];
PRIVATE GSN_WLAN_SCAN_PARAM_T s_wlanParam;
PRIVATE GSN_WLAN_SCAN_RESULT_T* scanInfo = NULL;

PRIVATE INT8 s_wpsEnabled[32];
PRIVATE INT8 s_wpsMode[32];
PRIVATE INT8 s_wpsPin[32];

/* XML Representations */
PRIVATE scan_params_xml_t scan_params_xml;
PRIVATE wps_xml_t wps_xml;

GSN_HTTPD_STATUS_T GsnHttpd_ScanParamsCb(ttHttpdUserEvent event, const char* uri,
        ttHttpdUserConHandle conHandle)
{
    {
        if(GsnHttpd_ScanParamsCb_FP)
        {
            return GsnHttpd_ScanParamsCb_FP(event,uri,conHandle);
        }
    }
    int i;
    INT32 respLen;
    int errorCode;
    UINT32 bufferLen;
    UINT32 encodedSize = 0;
    UINT32 maxSize = GSN_HTTPD_BUF_SIZE;
    INT8* buffer = GsnHttpd_GetBuffer();
	if(buffer == NULL)
		return GSN_HTTPD_FAILURE;

    switch (event)
    {
        case TM_HTTPD_EVENT_BODY_RECV:
        {
            UINT8 *ParentNodeStart, *ParentNodeEnd;
            // Read body
            bufferLen = TM_BODY_BUFFER_LEN;

            /* Do not copy the body message. Let the HTTPD server process CGI Args in body */
            tfHttpdUserGetRequestBody(conHandle, buffer,
                    (ttUserIntPtr) &bufferLen, 0/*  TM_HTTPD_NO_COPY*/);

            ParentNodeStart = (UINT8*) buffer; //Parent Node start address
            ParentNodeEnd = (UINT8*) buffer + bufferLen - 1; //Parent Node End adress
            buffer[bufferLen] = 0;

            GsnXml_Decode(ParentNodeStart, ParentNodeEnd,
                    (GSN_XML_COMPLEX_OBJ_T *) &Scan_Params_Schema_Start,
                    (UINT8 *) &scan_params_xml); 
            scan_params_xml.scan_elem.ssid_filter.ptr[scan_params_xml.scan_elem.ssid_filter.len]
                    = 0;
            memcpy(s_ssidFilter, scan_params_xml.scan_elem.ssid_filter.ptr,
                    scan_params_xml.scan_elem.ssid_filter.len);
            s_ssidFilter[scan_params_xml.scan_elem.ssid_filter.len] = 0;
            scan_params_xml.scan_elem.ssid_filter.ptr = s_ssidFilter;
            HTTPD_DEBUG_PRINT((
                    "[httpd_prov] Got ssid filter %s, channel %d, scan time %d\r\n",
                    scan_params_xml.scan_elem.ssid_filter.ptr,
                    scan_params_xml.scan_elem.scan_channel,
                    scan_params_xml.scan_elem.scan_time));
            s_wlanParam.channel = scan_params_xml.scan_elem.scan_channel;
            s_wlanParam.scanTime = scan_params_xml.scan_elem.scan_time;
            s_wlanParam.scanDelay = scan_params_xml.scan_elem.scan_delay;
        }
            break;
        case TM_HTTPD_EVENT_SEND_READY:

            if (GsnHttpd_GetHttpMethod(conHandle) ==  TM_HTTP_METHOD_GET)
            {
                GsnXml_Encode((GSN_XML_COMPLEX_OBJ_T *) &Scan_Params_Schema_Start,
                        (UINT8*) &scan_params_xml, (UINT8*) buffer, maxSize,
                        &encodedSize);

                GsnHttpd_SendBufferAndLastChunk(conHandle, buffer, encodedSize,
                        TM_BLOCKING_ON, &errorCode);
            }
            else
            {
                sprintf(buffer, "<status>ok</status>");
                GsnHttpd_SendBufferAndLastChunk(conHandle, buffer, strlen(buffer), TM_BLOCKING_ON, &errorCode);
            }

            break;
    }

	if(NULL != buffer)
		GsnHttpd_ReleaseBuffer(buffer);
    return GSN_HTTPD_SUCCESS;
}


PRIVATE GSN_HTTPD_PROV_WPS_CB_FN_T GsnHttpd_WpsCbFn = NULL;

GSN_HTTPD_STATUS_T GsnHttpd_WpsCb(ttHttpdUserEvent event, const char* uri,
        ttHttpdUserConHandle conHandle)
{
    if(GsnHttpd_WpsCb_FP)
        {
            return GsnHttpd_WpsCb_FP(event,uri,conHandle);
        }
    int i;
    INT32 respLen;
    int errorCode;
    UINT32 bufferLen;
    UINT32 encodedSize = 0;
    UINT32 maxSize = GSN_HTTPD_BUF_SIZE;
    INT8* buffer = GsnHttpd_GetBuffer();
	if(buffer == NULL)
		return GSN_HTTPD_FAILURE;

    switch (event)
    {
        case TM_HTTPD_EVENT_BODY_RECV:
        {
            UINT8 *ParentNodeStart, *ParentNodeEnd;
            // Read body
            bufferLen = TM_BODY_BUFFER_LEN;

            /* Do not copy the body message. Let the HTTPD server process CGI Args in body */
            tfHttpdUserGetRequestBody(conHandle, buffer,
                    (ttUserIntPtr) &bufferLen, 0/*  TM_HTTPD_NO_COPY*/);

            ParentNodeStart = (UINT8*) buffer; //Parent Node start address
            ParentNodeEnd = (UINT8*) buffer + bufferLen - 1; //Parent Node End adress
            buffer[bufferLen] = 0;

            GsnXml_Decode(ParentNodeStart, ParentNodeEnd,
                    (GSN_XML_COMPLEX_OBJ_T *) &Wps_Schema_Start,
                    (UINT8 *) &wps_xml);
            GsnHttpd_SetStrFromXmlStr((UINT8*)s_wpsEnabled, wps_xml.wps_elem.enabled, sizeof(s_wpsEnabled));
            GsnHttpd_SetStrFromXmlStr((UINT8*)s_wpsMode, wps_xml.wps_elem.mode, sizeof(s_wpsMode));
            GsnHttpd_SetStrFromXmlStr((UINT8*)s_wpsPin, wps_xml.wps_elem.pin, sizeof(s_wpsPin));

            wps_xml.wps_elem.enabled.ptr = (UINT8*)s_wpsEnabled;
            wps_xml.wps_elem.mode.ptr = (UINT8*)s_wpsMode;
            wps_xml.wps_elem.pin.ptr = (UINT8*)s_wpsPin;

        }
            break;
        case TM_HTTPD_EVENT_SEND_READY:

            if (GsnHttpd_GetHttpMethod(conHandle) ==  TM_HTTP_METHOD_GET)
            {
                GsnXml_Encode((GSN_XML_COMPLEX_OBJ_T *) &Wps_Schema_Start,
                        (UINT8*) &wps_xml, (UINT8*) buffer, maxSize,
                        &encodedSize);

                GsnHttpd_SendBufferAndLastChunk(conHandle, buffer, encodedSize,
                        TM_BLOCKING_ON, &errorCode);
            }
            else
            {
                sprintf(buffer, "<status>ok</status>");
                GsnHttpd_SendBufferAndLastChunk(conHandle, buffer, strlen(buffer), TM_BLOCKING_ON, &errorCode);
                    HTTPD_DEBUG_PRINT((
                            "[httpd_prov] Got wps enabled %s, mode %s, pin %s\r\n",
                            s_wpsEnabled,
                            s_wpsMode,
                            s_wpsPin));
                if (!strcmp(s_wpsEnabled, "true") && GsnHttpd_WpsCbFn)
                {
                    (*GsnHttpd_WpsCbFn)(s_wpsMode, s_wpsPin);
                }
            }

            break;

        case TM_HTTPD_EVENT_CON_CLOSE:
            break;

    }
	if(NULL != buffer)
		GsnHttpd_ReleaseBuffer(buffer);

    return GSN_HTTPD_SUCCESS;
}


void GsnHttpd_WpsConfigInit()
{
	if(GsnHttpd_WpsConfigInit_FP)
	{
		GsnHttpd_WpsConfigInit_FP();
        return;
	}
    memset(&wps_xml, 0, sizeof(wps_xml_t));
    strcpy(s_wpsEnabled, "false");
    strcpy(s_wpsMode, "none");
    strcpy(s_wpsPin, "");
    wps_xml.wps_elem.enabled.ptr = (UINT8*)s_wpsEnabled;
    wps_xml.wps_elem.enabled.len = strlen(s_wpsEnabled);
    wps_xml.wps_elem.mode.ptr = (UINT8*)s_wpsMode;
    wps_xml.wps_elem.mode.len = strlen(s_wpsMode);
    wps_xml.wps_elem.pin.ptr = (UINT8*)s_wpsPin;
    wps_xml.wps_elem.pin.len = strlen(s_wpsPin);
}



void GsnHttpd_ScanSetSockOpt(ttHttpdUserConHandle conHandle)
{
	if(GsnHttpd_ScanSetSockOpt_FP)
	{
		GsnHttpd_ScanSetSockOpt_FP(conHandle);
        return;
	}
    //int maxRtValue, maxRexmits, errorCode;
    //unsigned long maxRtoValue, rtoDefValue;

    //maxRtValue = 30;
#if 0
    errorCode = tfHttpdPeerSetSockopt(conHandle,
                            IP_PROTOTCP,
                            TCP_MAXRT,
                            (const char TM_FAR *)&maxRtValue,
                            sizeof(int) );
    if (errorCode == -1)
    {
        HTTPD_DEBUG_PRINT(("[httpd] unable to set TCP_MAXRT to %d\r\n", maxRtValue));
    }

    maxRexmits = 30;
    errorCode = tfHttpdPeerSetSockopt(conHandle,
                            IP_PROTOTCP,
                            TM_TCP_MAX_REXMIT,
                            (const char TM_FAR *)&maxRexmits,
                            sizeof(int) );
    if (errorCode == -1)
    {
        printf("[httpd] unable to set TM_TCP_MAX_REXMIT to %d\r\n", maxRexmits);
    }

    maxRtoValue = 1000;
    errorCode = tfHttpdPeerSetSockopt(conHandle,
                            IP_PROTOTCP,
                            TM_TCP_RTO_MAX,
                            (const char TM_FAR *)&maxRtoValue,
                            sizeof(unsigned long) );
    if (errorCode == -1)
    {
        printf("[httpd] unable to set TM_TCP_RTO_MAX to %d\r\n",
                maxRtoValue);
    }

    rtoDefValue = 1000;
    errorCode = tfHttpdPeerSetSockopt(conHandle,
                            IP_PROTOTCP,
                            TM_TCP_RTO_DEF,
                            (const char TM_FAR *)&rtoDefValue,
                            sizeof(unsigned long) );
    if (errorCode == -1)
    {
        printf("[httpd] unable to set TM_TCP_RTO_DEF to %d\r\n",
                rtoDefValue);
    }
#endif
}

UINT8 GsnHttpd_IsPrintableStr(UINT8* str, UINT8 length)
{
	if(GsnHttpd_IsPrintableStr_FP)
	{
		return (GsnHttpd_IsPrintableStr_FP)(str,length);
	}
    int i;
    for (i = 0; i < length; i++)
    {
        if (!isprint(str[i]))
        {
            return 0;
        }
    }

    return 1;
}

GSN_HTTPD_STATUS_T GsnHttpd_Scan_And_Send_Response(ttHttpdUserConHandle conHandle,INT8* buffer )
{
	if(GsnHttpd_Scan_And_Send_Response_FP)
	{
		return (GsnHttpd_Scan_And_Send_Response_FP)(conHandle,buffer);
	}
    UINT32 encodedSize = 0;
    UINT32 mallocSize;
    INT32 maxScanElements;
    UINT32 index,  numResults = 1;
    int i;
    int errorCode;
    ap_list_t ap_list;
    UINT8	channelList[GSN_WDD_WLAN_MAX_CHNLS+1];
#ifdef GSN_HTTPD_SCAN_TIMESTAMP
		GSN_SYSTEM_TIME_T time1, time2, timeDiff;
#endif

    sprintf(buffer, "<ap_list>");
    GsnHttpd_SendBuffer(conHandle, buffer, strlen(buffer),
            TM_BLOCKING_ON, &errorCode);
	mallocSize = GSN_HTTPD_MAX_SCAN_ELEMENTS * sizeof(GSN_WLAN_SCAN_RESULT_T);
    if (!scanInfo)
    {

	   scanInfo = (GSN_WLAN_SCAN_RESULT_T*) gsn_malloc(mallocSize);

	   if (!scanInfo)
	      return GSN_FAILURE;

	   memset(scanInfo, 0x0, mallocSize);
    }
	 /*
	 * Fill the channel to be scanned depending on regulatory
	 * domain
	 */

	if(s_wlanParam.channel)
	{
		channelList[0]= s_wlanParam.channel;
		channelList[1]= 0;
	}
	else
	{
		GsnWlanScan_ChannelFill(&channelList[0],s_wlanParam.domain,0);//Scan all possible channels
	}

    /*
     * NOTE: This is a workaround to use the GsnHttpdApi_ProvWscan API
     * to scan the desired channels with a scan delay (quiet time)
     * in between.
     * We invoke GsnHttpdApi_ProvWscan() repeatedly for each channel
     * that we are interested in and send the results out in chunks.
     */
#ifdef GSN_HTTPD_SCAN_TIMESTAMP
				time1 = GsnSoftTmr_CurrentSystemTime();
#endif
    index=0;
    while(channelList[index])
    {
		GSN_WLAN_SCAN_PARAM_T scanParam;
		memcpy(&scanParam, &s_wlanParam, sizeof(scanParam));

		scanParam.channel = channelList[index];

		memset(scanInfo, 0x0, mallocSize);
		maxScanElements = GSN_HTTPD_MAX_SCAN_ELEMENTS;
		if ((GsnWlanScan_ProvWscan(&scanParam,scanInfo,&maxScanElements) == GSN_FAILURE)
			|| (maxScanElements == 0))
		{
			HTTPD_DEBUG_PRINT(("[httpd_prov] Scan failure...Retrying after 5ms\r\n"));
			GsnTaskSleep(5);
			maxScanElements = GSN_HTTPD_MAX_SCAN_ELEMENTS;
			if ((GsnWlanScan_ProvWscan(&scanParam,scanInfo,&maxScanElements) == GSN_FAILURE)
				|| (maxScanElements == 0))
			{
				HTTPD_DEBUG_PRINT(("[httpd_prov] Scan failure...Giving up\r\n"));
				maxScanElements = 0;
			}
			else
			{
				HTTPD_DEBUG_PRINT(("[httpd_prov] Scan completed. Got %d AP's\r\n",
								   maxScanElements));
			}
		}
		else
		{
			HTTPD_DEBUG_PRINT(("[httpd_prov] Scan completed. Got %d AP's\r\n",
								maxScanElements));
		}
#ifdef GSN_HTTPD_SCAN_TIMESTAMP
            time2 = GsnSoftTmr_CurrentSystemTime();
            timeDiff = ((time2 - time1)* 1000)/33554432;
            HTTPD_DEBUG_PRINT(("[httpd_prov] Scan time taken by wdd %lu\r\n", timeDiff ));
#endif

		if (maxScanElements < 0)
			maxScanElements = 0;

        HTTPD_DEBUG_PRINT(("maxScanElements = %d\r\n",maxScanElements));
        for (i = 0; i < maxScanElements; i++)
        {
            UINT32 maxSize = GSN_HTTPD_BUF_SIZE;
            char* str, *pBuf = buffer;

            ap_list.app.index = numResults++;
            if (GsnHttpd_IsPrintableStr(scanInfo[i].ssid.array, scanInfo[i].ssid.length))
            {
                ap_list.app.ssid.ptr = scanInfo[i].ssid.array;
                ap_list.app.ssid.len = scanInfo[i].ssid.length;
                ap_list.app.ssid.ptr[ap_list.app.ssid.len] = 0;
            }
            else
            {
                HTTPD_DEBUG_PRINT(("Skipping entry because it is alphanumeric\r\n"));
                ap_list.app.ssid.ptr = 0;
                ap_list.app.ssid.len = 0;
            }
            if (scanInfo->nwType)
                str = "adhoc";
            else
                str = "infra";
            ap_list.app.nw_type.ptr = (UINT8*) str;
            ap_list.app.nw_type.len = strlen(str);
            if (scanInfo[i].securityType == GSN_WLAN_SECURITY_NONE)
            {
                ap_list.app.security.ptr = GSN_WLAN_SECURITY_NONE_STR;
                ap_list.app.security.len = strlen(
                        GSN_WLAN_SECURITY_NONE_STR);
            }
            else if (scanInfo[i].securityType == GSN_WLAN_WEP)
            {
                ap_list.app.security.ptr = GSN_WLAN_WEP_STR;
                ap_list.app.security.len = strlen(GSN_WLAN_WEP_STR);
            }
            else if (scanInfo[i].securityType == GSN_WLAN_WPA_PERSONAL)
            {
                ap_list.app.security.ptr = GSN_WLAN_WPA_PERSONAL_STR;
                ap_list.app.security.len = strlen(
                        GSN_WLAN_WPA_PERSONAL_STR);
            }
            else if (scanInfo[i].securityType
                    == GSN_WLAN_WPA_ENTERPRISE)
            {
                ap_list.app.security.ptr = GSN_WLAN_WPA_ENTERPRISE_STR;
                ap_list.app.security.len = strlen(
                        GSN_WLAN_WPA_ENTERPRISE_STR);
            }

		    scanInfo[i].rssi = (~scanInfo[i].rssi) + 1;
		    ap_list.app.rssi = scanInfo[i].rssi;


            ap_list.app.channel = scanInfo[i].channel;

			encodedSize = 0;
            GsnXml_Encode((GSN_XML_COMPLEX_OBJ_T *) &Schema_Start_1,
                    (UINT8*) &ap_list, (UINT8*) pBuf, maxSize,
                    &encodedSize);
            GsnHttpd_SendBuffer(conHandle, buffer, encodedSize,
                    TM_BLOCKING_ON, &errorCode);
             HTTPD_DEBUG_PRINT(("[httpd_prov] Sent partial response of size %d\r\n",
             encodedSize));
        }

        index++; //Move to next channel in the list

        // Scan delay (quiet time) before we proceed to next channel */
#ifdef GSN_HTTPD_SCAN_DELAY
            if (channelList[index])
                GsnTaskSleep(s_wlanParam.scanDelay);
#endif
    }/* end of for loop */

#ifndef GSN_HTTPD_SCAN_TIMESTAMP
    sprintf(buffer, "</ap_list>");
#else
    sprintf(buffer, "\n<time>%lu</time>\n</ap_list>", timeDiff);
#endif
    HTTPD_DEBUG_PRINT(("sending the last chunk\r\n"));
    GsnHttpd_SendBufferAndLastChunk(conHandle, buffer, strlen(buffer),
            TM_BLOCKING_ON, &errorCode);
    return GSN_HTTPD_SUCCESS;
}
GSN_HTTPD_STATUS_T GsnHttpd_ApListCb(ttHttpdUserEvent event, const char* uri,
        ttHttpdUserConHandle conHandle)
{
    if(GsnHttpd_ApListCb_FP)
	{
		return (GsnHttpd_ApListCb_FP)(event,uri,conHandle);
	}
    int i;
    int errorCode;

    ttHttpdUserConEntryPtr conEntryPtr;

    INT8* buffer = GsnHttpd_GetBuffer();
	if(buffer == NULL)
		return GSN_HTTPD_FAILURE;


    conEntryPtr = tfHttpdUserGetConInfo(conHandle);
    if (conEntryPtr->uconReqMethod == TM_HTTP_METHOD_POST)
    {
        sprintf(buffer, "<error>POST not allowed</error>");
        GsnHttpd_SendBufferAndLastChunk(conHandle, buffer, strlen(buffer),
                TM_BLOCKING_ON, &errorCode);
        return GSN_HTTPD_SUCCESS;
    }

    switch (event)
    {
        case TM_HTTPD_EVENT_BODY_RECV:
            break;
        case TM_HTTPD_EVENT_SEND_READY:

#ifdef GSN_HTTPD_ENABLE_SCAN_SOCK_OPT
            GsnHttpd_ScanSetSockOpt(conHandle);
#endif
            GsnHttpd_Scan_And_Send_Response(conHandle,buffer);
           break; // end of switch
        }
    if(scanInfo)
    {
    	gsn_free(scanInfo);
    }
    scanInfo = NULL;
	if(buffer !=  NULL)
		GsnHttpd_ReleaseBuffer(buffer);

    return GSN_HTTPD_SUCCESS;

}


GSN_HTTPD_STATUS_T  GsnHttpdApi_cb(ttHttpdUserEvent event, const char* uri,
        ttHttpdUserConHandle conHandle)
{

    if(GsnHttpdApi_cb_FP)
    {
        return GsnHttpdApi_cb_FP(event,uri,conHandle);
    }

    if (!strcmp(uri, "/gainspan/system/prov/ap_list"))
        return GsnHttpd_ApListCb(event, uri, conHandle);
    else if (!strcmp(uri, "/gainspan/system/prov/scan_params"))
        return GsnHttpd_ScanParamsCb(event, uri, conHandle);
    else if ((!strcmp(uri, "/gainspan/system/prov/wps")) && GsnHttpd_WpsCbFn)
        return GsnHttpd_WpsCb(event, uri, conHandle);
    else
        return GSN_HTTPD_URI_HANDLER_INVALID;
}


void GsnHttpd_ScanConfigInit(GSN_WLAN_REG_DOMAIN_T domain)
{
	if(GsnHttpd_ScanConfigInit_FP)
	{
		GsnHttpd_ScanConfigInit_FP(domain);
        return;
	}
    memset(&scan_params_xml, 0, sizeof(scan_params_xml_t));
    memset(&s_wlanParam, 0, sizeof(s_wlanParam));
    scan_params_xml.scan_elem.scan_time = s_wlanParam.scanTime = GSN_WLAN_SCAN_DWELL_TIME;
    scan_params_xml.scan_elem.scan_delay = s_wlanParam.scanDelay = GSN_WLAN_SCAN_DELAY_TIME;
    s_wlanParam.domain = domain;
    scan_params_xml.scan_elem.scan_channel = 0;
    strncpy((char*)s_ssidFilter, GSN_SSID_DEFAULT_FILTER,
            (strlen(GSN_SSID_DEFAULT_FILTER) + 1));
    scan_params_xml.scan_elem.ssid_filter.ptr = s_ssidFilter;
    scan_params_xml.scan_elem.ssid_filter.len = strlen("*");
}

void GsnHttpd_WpsInit(GSN_HTTPD_PROV_WPS_CB_FN_T pFn)
{
	if(GsnHttpd_WpsInit_FP)
	{
		GsnHttpd_WpsInit_FP(pFn);
        return;
	}
    GsnHttpd_WpsCbFn = pFn;
    GsnHttpd_WpsConfigInit();
}


void GsnHttpdApi_ProvInit(GSN_HTTPD_PROV_CONFIG_T *pConfig)
{
	if(GsnHttpdApi_ProvInit_FP)
	{
		GsnHttpdApi_ProvInit_FP(pConfig);
        return;
	}
    GsnWlanScan_Init(pConfig->pWdd);
    GsnHttpd_ScanConfigInit(pConfig->domain);

    GsnHttpd_WpsInit(pConfig->pWpsCbFn);

    GsnHttpd_UriHandlerConfig("/gainspan/system/prov",
            GSN_HTTPD_URI_METHOD_GET_POST, "Provisioning API",
            GsnHttpdApi_cb, GSN_HTTPD_CONTENT_APP_XML);
}

void GsnHttpdApi_ProvDeInit()
{
	if(GsnHttpdApi_ProvDeInit_FP)
	{
		GsnHttpdApi_ProvDeInit_FP();
        return;
	}
	GsnWlanScan_DeInit();
	if (scanInfo)
	{
		gsn_free(scanInfo);
		scanInfo = NULL;
	}
    GsnHttpd_UriHandlerConfig("/gainspan/system/prov", 0, NULL, NULL, 0);
}




