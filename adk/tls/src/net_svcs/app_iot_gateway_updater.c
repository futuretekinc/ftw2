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
* $RCSfile: app_iot_gateway_updater.c,v
*
*  Created on: 04-Oct-2013
*      Author: Dhanya Lakshmi
*/

#include "app_net_svcs_priv.h"
#include "app_iot_gateway_updater.h"
#include "modules/coap/gsn_coap.h"
#include "app_debug.h"
#include "app_tls.h"


#define DEVICE_API "/deviceapi"
#define ADD_DEVICE_PATH "/deviceapi/devices/"
#define READING "/readings/"
#define READING_PATH "/deviceapi/devices/1/readings/"
#define CONFIG "/config/"
#define CONFIG_PATH "/deviceapi/devices/1/config/"
#define UPDATE_INTERVAL_OPENING_TAG "<updt_int>"
#define UPDATE_INTERVAL_CLOSING_TAG "</updt_int>"
#define ONE 1
#define ZERO 0
#define STACK_5K 5120
#define STACK_3K 3072
#define DEFAULT_UPDATE_INTERVAL 5000
#define HTTP_RESPONSE_200 "200"
#define HTTP_RESPONSE_201 "201"
#define HTTP_CONN_TIMEOUT 5
#define HTTP_SEND_TIMEOUT 10
#define CONTENT_TYPE_XML COAP_MEDIATYPE_APPLICATION_XML
#define COAP_READ_TIMEOUT 5
#define RESPONSE_BUFFER_LEN 100

PRIVATE GSN_OSAL_THREAD_TCB_T httpClientTask;

PROXY_UPDATER_DATA proxy_updater;
UINT32 postCount;
BOOL deviceAdded = FALSE;

extern void App_StartServiceDiscovery(PROXY_UPDATER_DATA *proxyUpdater,GSN_MDNS_T *mdns);


INT8 *headerValues1[GSN_HTTP_HEADER_ALL] = {
    NULL,//192.168.7.104 // IP of proxy server 
	"application/xml",
    NULL
};

/*  Http header Types */
/* Note: Header types should be in the same oreder as Header values */
GSN_HTTP_USER_HEADER_TYPE_T headerFields[GSN_HTTP_HEADER_ALL] = {
    GSN_HTTP_HEADER_HOST,
    GSN_HTTP_HEADER_CONTENT_TYPE,
    GSN_HTTP_HEADER_CONTENT_LENGTH,
};

INT8 *headerValues2[GSN_HTTP_HEADER_ALL] = {
    NULL,//192.168.7.104 // IP of proxy server
};

/*  Http header Types */
/* Note: Header types should be in the same oreder as Header values */
GSN_HTTP_USER_HEADER_TYPE_T headerFields2[GSN_HTTP_HEADER_ALL] = {
    GSN_HTTP_HEADER_HOST,
};

typedef enum APP_TLS_HTTP_HEADER
{
	HOST,
    CONTENT_TYPE,
    CONTENT_LENGTH,
    HEADER_COUNT
}APP_TLS_HTTP_HEADER_T;

/* 
Method to get the update time interval
Parses the HTTP Response buffer for
<updt_int> tag
*/
PRIVATE UINT32
Get_UpdateInterval(INT8* pHttpRxDataBuf)
{
	UINT32 interval = 0;
	INT8* a;
    INT8* b;
	INT8 len;
	a = tm_strstr(pHttpRxDataBuf,UPDATE_INTERVAL_OPENING_TAG);
		if(a != NULL)
		{
			b = tm_strstr(a,UPDATE_INTERVAL_CLOSING_TAG);
			if(b != NULL)
			{
				a = a + 10;
				AppDbg_Printf("a = %s\r\n",a);
				AppDbg_Printf("b = %s\r\n",b);
				len = b - a;
				AppDbg_Printf("len of updt interval = %d\r\n",len);
				//proxy_updater.updtInterval = (INT8*) malloc((len)*sizeof(INT8)+1);
				
				strncpy(proxy_updater.updtInterval,a,len);
				proxy_updater.updtInterval[len] = '\0';
				printf("proxy_updater.updtInterval = %s\r\n",proxy_updater.updtInterval);
				interval = atoi(proxy_updater.updtInterval);
				AppDbg_Printf("proxy_updater.updateInterval = %d\r\n",proxy_updater.updateInterval);
				//free(proxy_updater.updtInterval);
				//proxy_updater.updtInterval = NULL;
			}
		}
	return interval;
}

PRIVATE VOID App_LowPPGetConfigProcessResponse(INT8* pHttpRxDataBuf)
{
	UINT32 interval;

    if(NULL != pHttpRxDataBuf)
    {

        if(!(strncmp((const INT8 *)pHttpRxDataBuf,HTTP_RESPONSE_200,3)))
        {
            AppDbg_Printf("[App_LowPProxyProcessResp] Response Message is 200 OK and Status is ");
			// Get the update interval that is configured in the server from the response body
			interval = Get_UpdateInterval(pHttpRxDataBuf);
			if(interval != ZERO)
				proxy_updater.updateInterval = interval;
        }
	}
}

PRIVATE VOID App_LowPPAddDeviceResponse(INT8* pHttpRxDataBuf)
{
        INT8* a;
	INT8* b;
	char** responseHeader;
	responseHeader= proxy_updater.httpConfInfo.resHeadersPtr;

	// case : device is added. response will be 201 if succesfull along with
	// location header containing the device ID
	// if device with supplied UID is already present in the server, still 201 along with location header is returned
    if(NULL != pHttpRxDataBuf)
    {
    	 if(!(strncmp((const INT8 *)pHttpRxDataBuf,HTTP_RESPONSE_201,3)))
    	 {
    		 AppDbg_Printf("[App_LowPPAddDeviceResponse] Response Message is 201 OK");
 			if(responseHeader[TM_HTTP_HEADER_LOCATION] != NULL)
 			{
 				printf("location header = %s\n",responseHeader[TM_HTTP_HEADER_LOCATION]);
 				a = tm_strstr(responseHeader[TM_HTTP_HEADER_LOCATION],DEVICE_API);
 				b = tm_strstr(a,DEVICE_API);
 				strcpy(proxy_updater.devicePath,b);
 				printf("proxy_updater.devicePath = %s",proxy_updater.devicePath);
 				deviceAdded = TRUE;
 			}
    	 }
    }
}


/*
Parses the http response
*/
PRIVATE VOID
App_LowPPPostReadingsResponse(INT8* pHttpRxDataBuf)
{
 	UINT32 interval;

    if(NULL != pHttpRxDataBuf)
    {

        if(!(strncmp((const INT8 *)pHttpRxDataBuf,HTTP_RESPONSE_201,3)))
        {
        	AppDbg_Printf("[App_LowPPPostReadingsResponse] Response Message is 201 OK");
			interval = Get_UpdateInterval(pHttpRxDataBuf);
			if(interval != ZERO)
				proxy_updater.updateInterval = interval;
			printf("App_LowPPPostReadingsResponse upd interval = %d\r\n",proxy_updater.updateInterval);
        }
    }
}

PUBLIC GSN_STATUS
GsnHttp_StartIPAndPort(GSN_HTTPC_CONN_HANDLE *pHttpConnHandle, INT8 *serverIpAddr,
			  UINT16 serverPortNo, GSN_HTTPC_CONN_PARAMS_T *pHttpcConnParams,
			  GSN_HTTPC_CONF_INFO_T * pHttpConfInfo)
{
	struct sockaddr_storage sockAddr;
	if(inet_pton(AF_INET, (char const*)serverIpAddr, &sockAddr.addr.ipv4.sin_addr.s_addr) == 1)
	{
		sockAddr.addr.ipv4.sin_family = AF_INET;
	}
	else if(inet_pton(AF_INET6, (char const*)serverIpAddr, &sockAddr.addr.ipv6.sin6_addr.s6_addr32) == 1)
	{
		sockAddr.addr.ipv6.sin6_family = AF_INET6;
	}
	sockAddr.ss_port = serverPortNo;

	return GsnHttp_Start(pHttpConnHandle, &sockAddr, pHttpcConnParams, pHttpConfInfo);

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

    memset((INT8 *)&connParams, ZERO, sizeof(connParams));
    connParams.ConTimeout = HTTP_CONN_TIMEOUT; /* maximum time to wait for the connection to happen */
    connParams.proxyPresent = ZERO;
   
    connParams.sslParams.caCert = httpsCACert;
    connParams.sslParams.caCertLen = httpsCACertLen;
    connParams.sslParams.caCertName = NULL;
    printf("\r\n[AppTls_HttpConnOpen] before GsnHttp_Start connecting to ip address = %s",httpServerIPAddr);
    printf("\r\n[AppTls_HttpConnOpen] before GsnHttp_Start connecting to port = %d",portNo);
    // Open Http/Https connection 
    status = GsnHttp_StartIPAndPort(&pHttpHandle, (INT8 *)httpServerIPAddr,
        portNo, &connParams, &(proxy_updater.httpConfInfo));
    AppDbg_Printf("\r\n[AppTls_HttpConnOpen] GsnHttp_Start status = %d\r\n", status);
    if(status == GSN_SUCCESS)
    {
        proxy_updater.bConnReady = TRUE;
        return pHttpHandle;
    }
    else
    {
        proxy_updater.bConnReady = FALSE;
        return NULL;
    }
}

VOID App_LowPProxy_RespCb(VOID *ctx,
    GSN_HTTPC_CONN_HANDLE conHandle,
    INT8 *httpRxDataBuf,
    INT32 httpRxDataLen,
    INT32 *rxBufferMgmtstatus)
{
	printf("[App_LowPProxy_RespCb] callback called with data length %d\r\n", httpRxDataLen);
    //App_LowPProxyProcessResp(httpRxDataBuf, httpRxDataLen);
    *rxBufferMgmtstatus = GSN_SUCCESS;
    return;
}
/*
Add the node as a device to the proxy server
response: 201 created if adding first time or 201 created if already added
along with location header containing the device ID
POST Request:

"POST /deviceapi/devices/ HTTP/1.1
Host: 192.168.7.104
Content-Type: application/xml
Content-Length: 73

<device><type>tls</type><uuid>abcd22221</uuid><name>test2</name></device>"
*/
PRIVATE GSN_STATUS
App_IotGatewayAddDevice( BOOL bSSL, APP_MAIN_CTX_T * pAppCtx)
{
	//UINT32 serverPort = 8182; //hardcoding for now since service discover is not checked in
	 // uncomment when MDNS is checked in
    UINT32 serverPort = proxy_updater.portNo;
    UINT32 httpRxDataLen;
    GSN_STATUS retVal = GSN_SUCCESS;
   
    INT8* reqBuf;
	UINT32 httpBufLen;
	INT8 *pHttpRxDataBuf;
	INT8 BufferLen[10];
	printf("App_IotGatewayAddDevice +\n");

	
	 //sprintf(proxy_updater.IpAddressString,"%d.%d.%d.%d", 192, 168, 27, 132);
	 // uncomment when MDNS is checked in

    printf("App_IotGatewayAddDevice ipaddress = %s\r\n",proxy_updater.IpAddressString);

    headerValues1[HOST] = proxy_updater.IpAddressString;
    proxy_updater.httpConfInfo.reqVersion = GSN_HTTP_VERSION_1_1;
    proxy_updater.httpConfInfo.reqHeaderTypes = headerFields;
    proxy_updater.httpConfInfo.reqHeaderValues = headerValues1;
    proxy_updater.httpConfInfo.reqHeaderCount = HEADER_COUNT;
    /* Reset the Connection Connection Ready Flag */
    proxy_updater.bConnReady = FALSE ;

    /*Open the HTTP COnnection */
    printf(" before AppTls_HttpConnOpen\r\n");
    proxy_updater.httpConn= AppTls_HttpConnOpen(proxy_updater.IpAddressString,serverPort,bSSL,NULL,NULL,0);
    printf(" After AppTls_HttpConnOpen\r\n");
	if(NULL == proxy_updater.httpConn)
    {
	AppDbg_Printf("proxy_updater.httpConn is NULL\n");
	return GSN_FAILURE;
	}
	
	
    reqBuf = proxy_updater.HttpRequestBuf;
    printf("UUID = %s\r\n",&pAppCtx->config.sysIdConfig.uid);

    httpBufLen =sprintf(reqBuf,"<device><type>tls</type><uuid>%s</uuid><name>TLSDiningRoom</name></device>",(char*)&pAppCtx->config.sysIdConfig.uid);
    printf("httpBufLen = %d\n",httpBufLen);
	
	sprintf(&BufferLen[0],"%d", httpBufLen);
    headerValues1[CONTENT_LENGTH] = BufferLen;
	
	proxy_updater.httpConfInfo.reqPathPtr = ADD_DEVICE_PATH;       //page to be opened
    proxy_updater.httpConfInfo.reqMethod = GSN_HTTP_METHOD_POST;  //Request method
    proxy_updater.httpConfInfo.reqBodyLen = httpBufLen;           //Request body len
    proxy_updater.httpConfInfo.reqBodyTotalLen = httpBufLen;      //Request body total len
    proxy_updater.httpConfInfo.rxBufferMgmtCbCtx = NULL;
    proxy_updater.httpConfInfo.reqBodyPtr = reqBuf;              //Request body pointer
	
	pHttpRxDataBuf = &proxy_updater.HttpRxBuf[0];
    httpRxDataLen = BUF_SIZE;
    memset(pHttpRxDataBuf, 0, BUF_SIZE);

    if( proxy_updater.bConnReady == TRUE )
    {
        /* Send Data */
    	printf("[App_IotGatewayAddDevice] Sending GET request to Server\r\n");
        retVal = GsnHttp_Send(proxy_updater.httpConn, (INT8 *)pHttpRxDataBuf,
                       &httpRxDataLen, HTTP_SEND_TIMEOUT, &(proxy_updater.httpConfInfo));
    }
	 if(retVal == GSN_SUCCESS)
    {
		 if (httpRxDataLen)
		 		App_LowPPAddDeviceResponse(pHttpRxDataBuf);
    }
	 else
	 {
		 AppDbg_Printf("[App_IotGatewayAddDevice] GsnHttp_Send failed error = %d\r\n",retVal);
	 }

    /* Close the Http conn */
    if(proxy_updater.httpConn != NULL)
    {
		printf("closing the connection\r\n");
        GsnHttp_Close(proxy_updater.httpConn);
        proxy_updater.httpConn = NULL;
    }
    printf("[App_IotGatewayAddDevice] -\r\n");
	return retVal;
}

/*
Send the Node readings to the proxy server
POST /deviceapi/devices/1/readings
Host: 192.168.7.104
Content-Type: application/xml
Content-Length: 144

<reading><sys></sys><profile type=\"tls\"><temp>30</temp><lux>500</lux><rssi>-40</rssi><batt>1.4</batt></profile></reading>

*/
PRIVATE GSN_STATUS
App_LowPProxyPostReadings( BOOL bSSL,INT8* reqBuf, UINT32 httpBufLen)
{
	UINT32 serverPort = proxy_updater.portNo;
    UINT32 httpRxDataLen;
    GSN_STATUS retVal = GSN_SUCCESS;
	INT8 *pHttpRxDataBuf;
	INT8 BufferLen[10];
	
	printf("App_IotGatewayUpdatereadings +\n");
	
    /* Reset the Connection Connection Ready Flag */
    proxy_updater.bConnReady = FALSE ;
    headerValues1[HOST] = proxy_updater.IpAddressString;
    proxy_updater.httpConfInfo.reqVersion = GSN_HTTP_VERSION_1_1;
    proxy_updater.httpConfInfo.reqHeaderTypes = headerFields;
    proxy_updater.httpConfInfo.reqHeaderValues = headerValues1;
    proxy_updater.httpConfInfo.reqHeaderCount = HEADER_COUNT;

    /*Open the HTTP COnnection */
    printf(" before AppTls_HttpConnOpen\r\n");
    proxy_updater.httpConn= AppTls_HttpConnOpen(proxy_updater.IpAddressString,serverPort,bSSL,NULL,NULL,0);
    printf(" After AppTls_HttpConnOpen\r\n");
	if(NULL == proxy_updater.httpConn)
    {
	AppDbg_Printf("proxy_updater.httpConn is NULL\n");
	return GSN_FAILURE;
	}
	
	printf("httpBufLen = %d\n",httpBufLen);
	
	sprintf(&BufferLen[0],"%d", httpBufLen);
    headerValues1[CONTENT_LENGTH] = BufferLen;
	if(proxy_updater.devicePath != NULL && proxy_updater.postingFirstTime)
	{
		strcpy(proxy_updater.readingPath,proxy_updater.devicePath);
		strcat(proxy_updater.readingPath,READING);
		printf("proxy_updater.readingPath = %s\r\n",proxy_updater.readingPath);
		proxy_updater.postingFirstTime = FALSE;
	}
		proxy_updater.httpConfInfo.reqPathPtr = proxy_updater.readingPath;


	//else
		//proxy_updater.httpConfInfo.reqPathPtr = READING_PATH;       //page to be opened
		

    proxy_updater.httpConfInfo.reqMethod = GSN_HTTP_METHOD_POST;  //Request method
    proxy_updater.httpConfInfo.reqBodyLen = httpBufLen;           //Request body len
    proxy_updater.httpConfInfo.reqBodyTotalLen = httpBufLen;      //Request body total len
    proxy_updater.httpConfInfo.rxBufferMgmtCbCtx = NULL;
    proxy_updater.httpConfInfo.reqBodyPtr = reqBuf;              //Request body pointer
	
	pHttpRxDataBuf = &proxy_updater.HttpRxBuf[0];

    httpRxDataLen = BUF_SIZE;
    memset(pHttpRxDataBuf, 0, BUF_SIZE);

    if( proxy_updater.bConnReady == TRUE )
    {
        /* Send Data */
    	printf("[App_IotGatewayUpdatereadings] Sending GET request to Server\r\n");
        retVal = GsnHttp_Send(proxy_updater.httpConn, (INT8 *)pHttpRxDataBuf,
                       &httpRxDataLen, HTTP_SEND_TIMEOUT, &(proxy_updater.httpConfInfo));
    }
	 if(retVal == GSN_SUCCESS)
    {
		 if (httpRxDataLen)
			 App_LowPPPostReadingsResponse(pHttpRxDataBuf);
    }
	else
		 AppDbg_Printf("App_LowPProxyPostReadings send failed with error\r\n;");

	
    /* Close the Http conn */
    if(proxy_updater.httpConn != NULL)
    {
	    printf("closing the connection\r\n");
        GsnHttp_Close(proxy_updater.httpConn);
        proxy_updater.httpConn = NULL;
    }

	return retVal;
}
/*
Update the temp,light,battery details to the proxy server
*/
PRIVATE GSN_STATUS
APP_LowPProxyUpdateReadingsWithCoap(APP_MAIN_CTX_T *pAppCtx)
{
    UINT32 battery = 0, temp = 0, light = 0,TLSdata[2] = {0,0};
    GSN_WIF_WLAN_RSSI_T    wRssi;
    INT8 signalstrength = 0;
	UINT32 bufLen;
	char reqBuf[256];
	unsigned char coapUri[256];
	GSN_STATUS retVal = GSN_SUCCESS;
	char * respBuf;
	GSN_COAP_CONTEXT_T *ctx;
	int numBytes = 0;
	GSN_COAP_CONN_PARAMS_T coapConnParams;

	AppTls_TempOrLightGet( TLSdata );
	GsnWdd_RSSIGet(&pAppCtx->if0.wddCtx, (INT8*) &wRssi, sizeof(wRssi));
	temp = TLSdata[0];
	light = TLSdata[1];
	battery = battery;
	signalstrength = wRssi.rssi;
	AppDbg_Printf("### Get ## adc data temp : %d , lux : %d RSSI %d \r\n", TLSdata[0], TLSdata[1], (signed char)wRssi.rssi);
    battery = 0;

	bufLen = sprintf(reqBuf,"<reading><sys></sys><profile type=\"tls\"><temp>%d</temp><lux>%d</lux><rssi>%d</rssi><batt>%d</batt></profile></reading>",temp,light,(signed char)signalstrength,battery);

	coapConnParams.uriLength = sprintf((char*)coapUri,"coap://%s:%d%s%s",proxy_updater.IpAddressString,COAP_DEFAULT_PORT,proxy_updater.devicePath,READING);
	AppDbg_Printf("coap uri = %s\r\n",coapUri);
	ctx = GsnCoap_Init(NULL);
	respBuf = (char*) gsn_malloc(RESPONSE_BUFFER_LEN);
	coapConnParams.uri = coapUri;
	coapConnParams.payload = reqBuf;
	coapConnParams.payloadSize = bufLen;
	coapConnParams.payloadType = gsn_malloc(sizeof(unsigned char *)* 4);
    sprintf((char*)coapConnParams.payloadType,"%d", CONTENT_TYPE_XML);
	coapConnParams.responseBufLen = RESPONSE_BUFFER_LEN;
	coapConnParams.responseBuffer = respBuf;
	coapConnParams.type = GSN_COAP_MESSAGE_NON;
	coapConnParams.method = GSN_COAP_REQUEST_POST;
	coapConnParams.responseTimeout = COAP_READ_TIMEOUT;

	numBytes = GsnCoap_Send_And_Recieve(ctx,&coapConnParams);
	AppDbg_Printf("GsnCoap_Send_And_Recieve returned %d\r\n",numBytes);
	gsn_free(respBuf);
	respBuf = NULL;
	GsnCoap_DeInit(ctx);
	if(retVal != GSN_SUCCESS)
	{
		AppDbg_Printf("App_LowPProxyPostReadings returned error %d",retVal);
	}
	return retVal;
}

/*
Update the temp,light,battery details to the proxy server
*/
PRIVATE GSN_STATUS
APP_LowPProxyUpdateReadings(APP_MAIN_CTX_T *pAppCtx, BOOL bSSL)
{
    UINT32 battery = 0, temp = 0, light = 0,TLSdata[2] = {0,0};
    GSN_WIF_WLAN_RSSI_T    wRssi;
    INT8 signalstrength = 0;
	UINT32 httpBufLen;
	INT8* reqBuf;
	GSN_STATUS retVal = GSN_SUCCESS;

	AppTls_TempOrLightGet( TLSdata );
	GsnWdd_RSSIGet(&pAppCtx->if0.wddCtx, (INT8*) &wRssi, sizeof(wRssi));
	temp = TLSdata[0];
	light = TLSdata[1];
	//battery = battery;
	signalstrength = wRssi.rssi;
	AppDbg_Printf("### Get ## adc data temp : %d , lux : %d RSSI %d \r\n", TLSdata[0], TLSdata[1], (signed char)wRssi.rssi);
    battery = 0;
	
	reqBuf = proxy_updater.HttpRequestBuf;
	httpBufLen = sprintf(reqBuf,"<reading><sys></sys><profile type=\"tls\"><temp>%d</temp><lux>%d</lux><rssi>%d</rssi><batt>%d</batt></profile></reading>",temp,light,(signed char)signalstrength,battery);
	
	retVal = App_LowPProxyPostReadings(bSSL, reqBuf, httpBufLen);
	if(retVal != GSN_SUCCESS)
	{
		AppDbg_Printf("App_LowPProxyPostReadings returned error %d",retVal);
	}
	return retVal;
}
	
/*
Get the device configuration from the proxy server
*/
PRIVATE GSN_STATUS
App_IotGatewayGetConfig(BOOL bSSL)
{
	UINT32 serverPort = proxy_updater.portNo;
    UINT32 httpRxDataLen;
    GSN_STATUS retVal = GSN_SUCCESS;
	
	INT8 *pHttpRxDataBuf;
	printf("App_IotGatewayGetConfig +\n");
	
    /* Reset the Connection Connection Ready Flag */
    proxy_updater.bConnReady = FALSE ;
    /*Open the HTTP COnnection */
    printf(" before AppTls_HttpConnOpen\r\n");
    headerValues2[HOST] = proxy_updater.IpAddressString;

    proxy_updater.httpConfInfo.reqVersion = GSN_HTTP_VERSION_1_1;
    proxy_updater.httpConfInfo.reqHeaderTypes = headerFields2;
    proxy_updater.httpConfInfo.reqHeaderValues = headerValues2;
    proxy_updater.httpConfInfo.reqHeaderCount = 1;
    proxy_updater.httpConn= AppTls_HttpConnOpen(proxy_updater.IpAddressString,serverPort,bSSL,NULL,NULL,0);
    printf(" After AppTls_HttpConnOpen\r\n");
	if(NULL == proxy_updater.httpConn)
    {
		AppDbg_Printf("proxy_updater.httpConn is NULL\n");
		return GSN_FAILURE;
	}

    if(proxy_updater.devicePath != NULL && proxy_updater.postingFirstTime)
    {
    		strcpy(proxy_updater.configPath,proxy_updater.devicePath);
    		strcat(proxy_updater.configPath,CONFIG);
    		printf("proxy_updater.configPath = %s\r\n",proxy_updater.configPath);
    		proxy_updater.httpConfInfo.reqPathPtr = proxy_updater.configPath;

    }
	else
		proxy_updater.httpConfInfo.reqPathPtr = CONFIG_PATH;
	 
    proxy_updater.httpConfInfo.reqMethod = GSN_HTTP_METHOD_GET;  //Request method
    proxy_updater.httpConfInfo.reqBodyLen = 0;           //Request body len
    proxy_updater.httpConfInfo.reqBodyTotalLen = 0;      //Request body total len

    proxy_updater.httpConfInfo.rxBufferMgmtCbCtx = NULL;
    proxy_updater.httpConfInfo.reqBodyPtr = NULL;              //Request body pointer
	
	pHttpRxDataBuf = &(proxy_updater.HttpRxBuf[0]);
    httpRxDataLen = BUF_SIZE;
    memset(pHttpRxDataBuf, 0, BUF_SIZE);
	
    if( proxy_updater.bConnReady == TRUE )
    {
        /* Send Data */
    	printf("[App_IotGatewayGetConfig] Sending GET request to Server\r\n");
        retVal = GsnHttp_Send(proxy_updater.httpConn, (INT8 *)pHttpRxDataBuf,
                       &httpRxDataLen, HTTP_SEND_TIMEOUT, &(proxy_updater.httpConfInfo));
    }
	if(retVal == GSN_SUCCESS)
    {
		if (httpRxDataLen)
			App_LowPPGetConfigProcessResponse(pHttpRxDataBuf);
    }
	else
		 AppDbg_Printf("App_LowPProxyPostReadings send failed with error\r\n;");
    /* Close the Http conn */
    if(proxy_updater.httpConn != NULL)
    {
    	printf("closing the connection\r\n");
        GsnHttp_Close(proxy_updater.httpConn);
        proxy_updater.httpConn = NULL;
    }

	return retVal;
}

VOID App_IotGatewayDataSendAndRecv(void* ctx)
{
GSN_STATUS status;
UINT8 count = 1;
printf("App_IotGatewayDataSendAndRecv + \n");
    
    proxy_updater.postingFirstTime = TRUE;
	while(count < RETRIAL_COUNT && proxy_updater.continueRunning)
	{
		// retry for 5 times in case the server is down

		if(!deviceAdded)
		{
			status = App_IotGatewayAddDevice(FALSE,ctx);
			if(GSN_FAILURE == status)
			{
				count++;
				return;
			}


			status = App_IotGatewayGetConfig(FALSE);
			if(GSN_FAILURE == status)
			{
				count++;
				return;
			}
		}

		while(1)
		{
			if(proxy_updater.continueRunning == FALSE)
			return;
#ifdef ADK_IOT_COAP
			status = APP_LowPProxyUpdateReadingsWithCoap(ctx);
#else
			status = APP_LowPProxyUpdateReadings(ctx,FALSE);
#endif

			if(GSN_FAILURE == status)
				break;
			printf("posting after %d msecs\r\n",proxy_updater.updateInterval);
			// update readings after specified time interval
			GsnTaskSleep(proxy_updater.updateInterval);
		}
		
		printf("App_IotGatewayDataSendAndRecv \r\n");
		count++;
	}

	printf("App_IotGatewayDataSendAndRecv - \n");
}
GSN_STATUS_T App_HttpClientStackAlloc(UINT8** pStack, UINT16* pStackSize)
{
    GSN_STATUS_T retVal = GSN_FAILURE;
    UINT8* stack = NULL;
    UINT16 stackSize = STACK_5K;

    if ((stack = (UINT8*) malloc(stackSize)) == NULL)
    {
        stackSize = STACK_3K;
        if ((stack = (UINT8*) malloc((stackSize))) == NULL)
        {
			retVal = GSN_FAILURE;
        }
        else
        {
            *pStack = stack;
            *pStackSize = stackSize;
            retVal = GSN_SUCCESS;
		}					
    }
    else
    {
        *pStack = stack;
        *pStackSize = stackSize;
        retVal = GSN_SUCCESS;
    }

    AppDbg_Printf("[App_HttpClientStackAlloc] allocated %d bytes of stack\r\n",
            stackSize);

    return retVal;
}
VOID App_LowPowerDiscoverServices(APP_MAIN_CTX_T *pAppCtx)
{
	// start the mdns discovery
	//
	AppDbg_Printf("\r\nApp_LowPowerDiscoverServices +\r\n");
	GsnOsal_SemCreate ( &proxy_updater.appTlsServiceDiscoverWaitSem, 0 );
	App_StartServiceDiscovery(&proxy_updater,&pAppCtx->if0.mdns);

	AppDbg_Printf("IP address = %d.%d.%d.%d",proxy_updater.IPAddress[0],proxy_updater.IPAddress[1],proxy_updater.IPAddress[2],proxy_updater.IPAddress[3]);
	AppDbg_Printf("\r\nApp_LowPowerDiscoverServices Port no = %d",proxy_updater.portNo);
	sprintf(proxy_updater.IpAddressString,"%d.%d.%d.%d", proxy_updater.IPAddress[0], proxy_updater.IPAddress[1],proxy_updater.IPAddress[2], proxy_updater.IPAddress[3]);
	AppDbg_Printf("\r\nApp_LowPowerDiscoverServices -\r\n");
}
VOID App_IotGatewayDiscoverAndSend(APP_MAIN_CTX_T* ctx)
{
	postCount = 0;
	//App_GetUUID(ctx);
	while(proxy_updater.continueRunning)
	{
		App_LowPowerDiscoverServices(ctx);
		App_IotGatewayDataSendAndRecv(ctx);
		GsnOsal_SemDelete ( &proxy_updater.appTlsServiceDiscoverWaitSem );
	}

}
// note stop returns immediately,

VOID App_IotGatewayUpdaterStop()
{
	// set the proxy_updater.continueRunning flag to false
	// and wait until the updater has stopped
	GsnOsal_SemRelease( &proxy_updater.appTlsServiceDiscoverWaitSem);
	proxy_updater.continueRunning = FALSE;
	//App_waiting_for_updater_toStop();
}
VOID App_IotGatewayUpdaterStart(APP_MAIN_CTX_T *pAppCtx)
{
	
	GSN_STATUS_T retVal;
    UINT8* stack;
    UINT16 stackSize;

    proxy_updater.httpConn = NULL;
    proxy_updater.bConnReady = FALSE;
    proxy_updater.updateInterval = DEFAULT_UPDATE_INTERVAL;
	proxy_updater.continueRunning = TRUE;
    AppDbg_Printf("App_IotGatewayUpdaterStart +\n");

    

    if ((retVal = App_HttpClientStackAlloc(&stack, &stackSize)) == GSN_FAILURE)
    {
        AppDbg_Printf("[App_PPCloudUpdaterStart] Unable to allocate stack\r\n");
        // stack allocation failed return
    }
    else
    {
    	//IpAddress = IpAddr;
    	// create a new thread and start service discovery and posting data in
    	// the new thread context
    	retVal = GsnOsal_ThreadCreate((GSN_OSAL_THREAD_ENTRY_T)App_IotGatewayDiscoverAndSend,
                    pAppCtx /* This is the thread parameter */,
                    &httpClientTask,
                    "App_IotGatewayDiscoverAndSend",
                    PROXY_UPDATER_THREAD_PRIORITY,
                    stack,
                    stackSize ,
                    GSN_OSAL_THREAD_INITIAL_READY);

    	if(retVal != GSN_SUCCESS)
    	{
        	AppDbg_Printf("[App_IotGatewayUpdaterStart] Thread creation Failed\r\n");
        	if (stack)
        	{
            	gsn_free(stack);
        	}
    	}
    }
    AppDbg_Printf("App_IotGatewayUpdaterStart -\r\n");
}
