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
* $RCSfile: app_data_send.c,v $
*******************************************************************************/

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_includes.h"
#include "gsn_includes.h"
#include "config/app_cfg.h"
#include "fs_if/app_fsIf.h"
#include "gsn_ncm.h"
#include "app_main_ctx.h"
#include "app_sm.h"
#include "app_ncm.h"
#include "app_resource_config.h"
#include "app_events.h"
#include "app_debug.h"
#include "app_rtc_mem.h"
#include "gsn_httpd_config.h"
#include "app_fsIf.h"
#include "app_default_cfg.h"
#include "app_data_send.h"
#include <http\gsn_httpc.h>

/*****************************************************************************
 *Private variables
 ****************************************************************************/
GSN_HTTPC_CONF_INFO_T httpConfInfo;
PRIVATE void *httpConn = NULL ;
UINT8 HttpRxBuf[1204];
#define UDP_SERVER_ADDRESS IP_ADDRESS(192,168,50,1)

UINT32 UdpServerIp = UDP_SERVER_ADDRESS;

typedef enum APP_TLS_HTTP_HEADER
{
	HOST,
    CONTENT_TYPE,
    CONTENT_LENGTH,
    HEADER_COUNT
}APP_TLS_HTTP_HEADER_T;

INT8 *headerValue[HEADER_COUNT] = {
    NULL,//192.168.7.104 // IP of proxy server 
	"application/xml",
    NULL
};

/*  Http header Types */
/* Note: Header types should be in the same oreder as Header values */

GSN_HTTP_USER_HEADER_TYPE_T headerEnums[HEADER_COUNT] = {
    GSN_HTTP_HEADER_HOST,
    GSN_HTTP_HEADER_CONTENT_TYPE,
    GSN_HTTP_HEADER_CONTENT_LENGTH,
};

/*****************************************************************************
 *Private Functions
 ****************************************************************************/

INT32
App_DataSendOverUdp(APP_MAIN_CTX_T *pAppCtx)
{
	INT32 sockId;
	struct sockaddr_in destAddr = {0};
	UINT8 tlsData[256];	
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();

	
	sockId = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockId < 0)
	{
		return -1;
	}
#ifdef NO_SENSOR
	sprintf(tlsData, "<tls><seq>%d</seq><msg>Hello World</msg></tls>",
				pAppRtcLtchInfo->UdpSeqNo);
#else
#ifdef ULTRA_LOW_POWER
	sprintf(tlsData, "<tls><seq>%d</seq><lux>%d</lux><temp>%d</temp></tls>",
			    pAppRtcLtchInfo->UdpSeqNo,
				pAppRtcLtchInfo->TLSdata[0], 
				pAppRtcLtchInfo->TLSdata[1]);
#else
	sprintf(tlsData, "<tls><seq>%d</seq><lux>%d</lux><temp>%d</temp>""<lux>%d</lux><temp>%d</temp></tls>",
			    pAppRtcLtchInfo->UdpSeqNo,
				pAppRtcLtchInfo->TLSdata[0],
				pAppRtcLtchInfo->TLSdata[1],
				pAppRtcLtchInfo->TLSdata[2],
				pAppRtcLtchInfo->TLSdata[3]);
#endif
#endif

	destAddr.sin_family = PF_INET;
	destAddr.sin_port = htons(8080);
	//UdpServerIp = htonl(IP_ADDRESS(192,168,10,10));
	destAddr.sin_addr.s_addr = htonl(UDP_SERVER_ADDRESS);

	sendto(sockId, tlsData, (strlen(tlsData) + 1), 0, (struct sockaddr *)&destAddr, 
			sizeof(destAddr));
	soc_close(sockId);
}


/*
opens a HTTP/HTTPS connection to the specified IP Address and port
*/

PRIVATE VOID*
AppTls_HttpConnOpen(const INT8* httpServerIPAddr,
                                     UINT32 portNo,
                                     BOOL bSSL,
                                     char*httpsCACertName,
                                     UINT8*httpsCACert,
                                     UINT32 httpsCACertLen)
{
    GSN_STATUS status;
    UINT32 serverIp = inet_addr((INT8*)httpServerIPAddr);
    void *pHttpHandle = NULL;
    GSN_HTTPC_CONN_PARAMS_T connParams;
	struct sockaddr_storage sockAddr;


	inet_pton(AF_INET, (char const*)httpServerIPAddr, &sockAddr.addr.ipv4.sin_addr.s_addr);

	sockAddr.ss_port = portNo;
	sockAddr.addr.ipv4.sin_family = AF_INET;
    memset((INT8 *)&connParams, 0, sizeof(connParams));

	connParams.ConTimeout = 5;
    connParams.proxyPresent = 0;
   
    connParams.sslParams.caCert = httpsCACert;
    connParams.sslParams.caCertLen = httpsCACertLen;
    connParams.sslParams.caCertName = NULL;
	AppDbg_Printf("[AppTls_HttpConnOpen] before GsnHttp_Start\n");
    /*Open Http/Https connection */
    status = GsnHttp_Start(&pHttpHandle, &sockAddr, &connParams, &httpConfInfo);
    AppDbg_Printf("[AppTls_HttpConnOpen] GsnHttp_Start status = %d\r\n", status);
    if(status == GSN_SUCCESS)
    {
        return pHttpHandle;
    }
    else
    {
        return NULL;
    }
}


/*
Send the Node readings to the proxy server
POST /deviceapi/devices/1/readings
Host: 192.168.7.104
Content-Type: application/xml
Content-Length: 144

<reading><sys></sys><profile type=\"tls\"><temp>30</temp><lux>500</lux><rssi>-40</rssi><batt>1.4</batt></profile></reading>

*/
PRIVATE GSN_STATUS_T
App_DataSendOverHttp(APP_MAIN_CTX_T *pAppCtx, BOOL bSSL)
{
	GSN_STATUS retVal;
	UINT8 tlsData[256];	
	APP_RTC_LATCH_MEM_INFO_T *pAppRtcLtchInfo = App_RtcLatchMemInfoPtrGet();
	UINT32 dataLen;
	UINT32 httpRxDataLen;
	INT8 contentLenStr[10];

	sprintf(tlsData, "<tls><lux>%d</lux><temp>%d</temp>""<lux>%d</lux><temp>%d</temp></tls>",
				pAppRtcLtchInfo->TLSdata[0], 
				pAppRtcLtchInfo->TLSdata[1],
				pAppRtcLtchInfo->TLSdata[2], 
				pAppRtcLtchInfo->TLSdata[3]);

	
    /*Open the HTTP COnnection */
	httpConn= AppTls_HttpConnOpen("192.168.1.120", 8182, bSSL, NULL, NULL, 0);

	if(NULL == httpConn)
    {
		AppDbg_Printf("Http Open Failed\n");
		return GSN_FAILURE;
	}
	
	dataLen = strlen(tlsData);

	sprintf(&contentLenStr[0],"%d", dataLen);
    headerValue[CONTENT_LENGTH] = &contentLenStr[0];


	httpConfInfo.reqMethod = GSN_HTTP_METHOD_POST;  //Request method
	httpConfInfo.reqPathPtr = "/deviceapi/devices/1/readings/";       //page to be opened
	httpConfInfo.reqVersion = GSN_HTTP_VERSION_1_1;	

	httpConfInfo.reqHeaderTypes = (GSN_HTTP_USER_HEADER_TYPE_T *)headerEnums;
	httpConfInfo.reqHeaderValues = headerValue;
	httpConfInfo.reqHeaderCount = HEADER_COUNT;

    httpConfInfo.reqBodyLen = dataLen;           //Request body len
    httpConfInfo.reqBodyTotalLen = dataLen;      //Request body total len
    httpConfInfo.rxBufferMgmtCbCtx = NULL;
    httpConfInfo.reqBodyPtr = tlsData;              //Request body pointer
	

    if( httpConn )
    {
    	httpRxDataLen = sizeof(HttpRxBuf);
        /* Send Data */
        AppDbg_Printf("[App_LowPowerProxyUpdatereadings] Sending GET request to Server\r\n");
        retVal = GsnHttp_Send(httpConn, (INT8 *)HttpRxBuf,
                       &httpRxDataLen, 1, &httpConfInfo);
    }

	if(retVal != GSN_SUCCESS)
    {
        /* Send failed */
        AppDbg_Printf("[App_LowPowerProxyUpdatereadings] GET FAILED\r\n");
    }
    else
    {
        AppDbg_Printf("[App_LowPowerProxyUpdatereadings] GET response size is %d\r\n", httpRxDataLen);
    }
	if(httpConn != NULL)
	{
		GsnHttp_Close(httpConn);
		httpConn = NULL;

	}
	
	return retVal;
}

/*************************************************************************************/
VOID
App_DataSend(APP_MAIN_CTX_T *pAppCtx)
{

#ifdef SEND_DATA_OVER_HTTP
	App_DataSendOverHttp(pAppCtx, 0);
#else 	
	App_DataSendOverUdp(pAppCtx);
#endif

}

