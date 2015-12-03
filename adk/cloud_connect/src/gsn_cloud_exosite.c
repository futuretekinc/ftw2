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
* gsn_cloud_exosite.c
*
*  Created on: 27-May-2013
*      Author: Dhanya Lakshmi
*/

#include "gsn_httpc.h"

#include "gsn_cloud_exosite.h"
#include "gsn_cloud_tls.h"
#include "gsn_cloud_sp.h"
#include "app_debug.h"

CLOUD_CONTEXT_DATA_T cloud_updater;

GSN_CLOUD_DATA_FORMAT_FN appFormatFn = NULL;

#define READING_PATH "/onep:v1/stack/alias"
#define FLUSH_DATA_PATH "/api:v1/rpc/process"
#define READING_PATH_LOAD_CONTROL "/onep:v1/stack/alias?lc_request"
#define PROVISION_PATH "/provision/activate"
#define LOAD_REQUEST_ALIAS "lc_request"
#define ONE 1
#define ZERO 0
//#define EXOSITE_ADDRESS "m2.exosite.com"
#define EXOSITE_ADDRESS "173.255.209.28"
#define TLS_MODEL "gs-tls-adk"
#define SP_MODEL "gs-sp-adk"
#define VENDOR_NAME "gainspan"

#define DEFAULT_UPDATE_INTERVAL 5000
#define HTTP_CONN_TIMEOUT 5
#define HTTP_SEND_TIMEOUT 10
#define NEW_LINE "\n"
#define CARRIAGE_RETURN "\r"

#define printf AppDbg_Printf


/*  Http header Types */
/* Note: Header types should be in the same order as Header values */
/* set of headers to send for activating the device */
GSN_HTTP_USER_HEADER_TYPE_T headerTypes[GSN_HTTP_HEADER_ALL] = {
    GSN_HTTP_HEADER_HOST,
    GSN_HTTP_HEADER_CONTENT_TYPE,
    GSN_HTTP_HEADER_CONTENT_LENGTH,
    };

INT8 *headerValues[GSN_HTTP_HEADER_ALL] = {
    "m2.exosite.com" ,// IP of cloud server
	"application/x-www-form-urlencoded; charset=utf-8",
    NULL,
};

/*  Http header Types */
/* Note: Header types should be in the same order as Header values */
/* set of headers to send for posting updates to cloud */
GSN_HTTP_USER_HEADER_TYPE_T headerTypes2[GSN_HTTP_HEADER_ALL] = {
    GSN_HTTP_HEADER_HOST,
    GSN_HTTP_HEADER_CONTENT_TYPE,
    GSN_HTTP_HEADER_CONTENT_LENGTH,
    GSN_HTTP_HEADER_CUSTOM,
    };


INT8 *headerValues2[GSN_HTTP_HEADER_ALL] = {
    "m2.exosite.com" ,// IP of cloud server
	"application/x-www-form-urlencoded; charset=utf-8", // content-type
    NULL,
    NULL,
};

INT8 *headerValues3[GSN_HTTP_HEADER_ALL] = {
    "m2.exosite.com" ,// IP of cloud server
	"application/json; charset=utf-8", // content-type
    NULL,
};

GSN_HTTP_USER_HEADER_TYPE_T headerTypesForGet[GSN_HTTP_HEADER_ALL] = {
    GSN_HTTP_HEADER_HOST,
    GSN_HTTP_HEADER_CUSTOM,
    GSN_HTTP_HEADER_CUSTOM,
    };
INT8 *headerValuesForGet[GSN_HTTP_HEADER_ALL] = {
    "m2.exosite.com" ,// IP of cloud server
	"Accept: application/x-www-form-urlencoded; charset=utf-8", // content-type
    NULL,
};
typedef enum APP_TLS_HTTP_HEADER2
{
    HOST,
    CONTENT_TYPE,
    CONTENT_LENGTH,
    CIK,
    HEADER_COUNT2,
}APP_TLS_HTTP_HEADER_T;



void Gsn_ExositeFormatActivationRequest(CLOUD_CONTEXT_DATA_T* cloudUpdater)
{
	INT8* reqBuf;
	reqBuf = cloudUpdater->httpRequestBuf;
	printf("UID = %s\r\n",cloudUpdater->uid);
	if(cloudUpdater->adkType == TLS_ADK)
	{
		cloudUpdater->requestBufLen = sprintf(reqBuf,"vendor=%s&model=%s&sn=%s",VENDOR_NAME,TLS_MODEL,cloudUpdater->uid);
		printf("reqBuf = %s\r\n",reqBuf);
	}

	if(cloudUpdater->adkType == SP_ADK)
	{
		cloudUpdater->requestBufLen = sprintf(reqBuf,"vendor=%s&model=%s&sn=%s",VENDOR_NAME,SP_MODEL,cloudUpdater->uid);
		printf("reqBuf = %s\r\n",reqBuf);
	}

}

void Gsn_ExositeGetCloudAddress(CLOUD_CONTEXT_DATA_T* cloudUpdater)
{
    printf("Gsn_ExositeGetCloudAddress +\r\n");
	strncpy(cloudUpdater->serverName,EXOSITE_ADDRESS,sizeof(cloudUpdater->serverName));
	printf("Gsn_ExositeGetCloudAddress -\r\n");
}
/*
Parses the http response
*/
PRIVATE GSN_STATUS
Gsn_CloudProcessResponse(INT8* pHttpRxDataBuf)
{
 	printf("response buf = %s\r\n",pHttpRxDataBuf);
    if(NULL != pHttpRxDataBuf)
    {

        if(!(strncmp((const INT8 *)pHttpRxDataBuf,HTTP_RESPONSE_204,3)))
        {
        	printf("[Gsn_CloudProcessResponse] Response Message is 204 No Content\r\n");
        	return GSN_SUCCESS;
        }
    }
    return GSN_FAILURE;

}

/*Parses the http response
*/
PRIVATE GSN_STATUS
Gsn_CloudProcessFlushResponse(INT8* pHttpRxDataBuf)
{
 	printf("response buf = %s\r\n",pHttpRxDataBuf);
    if(NULL != pHttpRxDataBuf)
    {

        if(!(strncmp((const INT8 *)pHttpRxDataBuf,HTTP_RESPONSE_200,3)))
        {
        	printf("[Gsn_CloudProcessResponse] Response Message is 204 No Content\r\n");
        	return GSN_SUCCESS;
        }
    }
    return GSN_FAILURE;

}


PRIVATE GSN_STATUS
Gsn_DeviceActivationProcessResponse(INT8* pHttpRxDataBuf)
{
	INT8* a;
	INT8 len = 40;
	printf("response buf = %s\r\n",pHttpRxDataBuf);
	if(NULL != pHttpRxDataBuf)
	{

		if(!(strncmp((const INT8 *)pHttpRxDataBuf,HTTP_RESPONSE_200,3)))
		{
			printf("[Gsn_ExositeActivateResponse] Response Message is 200 OK\r\n");
			a = strstr(pHttpRxDataBuf,"OK\r\n");
			a = a + 4;
			if(a != NULL)
			{

				printf("a = %s\r\n",a);
				printf("strlen(a) = %d \r\n",strlen(a));
				strncpy(cloud_updater.CIK,a,len);
				strcat(cloud_updater.CIK,"\0");
				printf("CIK = %s\r\n",cloud_updater.CIK);
				strncpy(cloud_updater.cloudCallbackData.cloudKey,a,len);
				strcat(cloud_updater.cloudCallbackData.cloudKey,"\0");
				AppDbg_Printf("CIK = %s\r\n",cloud_updater.cloudCallbackData.cloudKey);

				return GSN_SUCCESS;
			}
		}
		else
		{
			if(!(strncmp((const INT8 *)pHttpRxDataBuf,HTTP_RESPONSE_409,3)))
			{
				printf("[Gsn_ExositeActivateResponse] Response Message is 409\r\n ");
			}
			else
			{
				printf("[Gsn_ExositeActivateResponse] response is error\r\n");
			}
		}
	}
	return GSN_FAILURE;
}

PUBLIC GSN_STATUS_T Gsn_CloudStackAlloc(UINT8** pStack, UINT16 pStackSize, UINT16 *allocatedStackSize)
{
    GSN_STATUS_T retVal = GSN_FAILURE;
    UINT8* stack = NULL;
    UINT16 stackSize = pStackSize;

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
            *allocatedStackSize = stackSize;
            retVal = GSN_SUCCESS;
		}
    }
    else
    {
        *pStack = stack;
        // TODO - this fix needs to go into 1011
        *allocatedStackSize = stackSize;
        retVal = GSN_SUCCESS;
    }

    printf("[Gsn_HttpClientStackAlloc] allocated %d bytes of stack\r\n",
    		*allocatedStackSize);

    return retVal;
}

PUBLIC GSN_STATUS
GsnHttp_StartWithIPAndPort(GSN_HTTPC_CONN_HANDLE *pHttpConnHandle, INT8 *serverIpAddr,
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
Gsn_CloudHttpConnOpen(const INT8* httpServerIPAddr,
                                     UINT32 portNo,
                                     char* httpsCACertName,
                                     UINT8* httpsCACert,
                                     UINT32 httpsCACertLen)
{
    GSN_STATUS status;
    UINT32 serverIp = inet_addr((INT8*)httpServerIPAddr);
    void *pHttpHandle = NULL;
    GSN_HTTPC_CONN_PARAMS_T connParams;

    cloud_updater.httpConfInfo.reqVersion = GSN_HTTP_VERSION_1_1;

    memset((INT8 *)&connParams, ZERO, sizeof(connParams));
    connParams.ConTimeout = HTTP_CONN_TIMEOUT; /* maximum time to wait for the connection to happen */
    connParams.proxyPresent = ZERO;
    connParams.sslParams.caCert = httpsCACert;
    connParams.sslParams.caCertLen = httpsCACertLen;
    connParams.sslParams.caCertName = NULL;
	printf("[Gsn_CloudHttpConnOpen] before GsnHttp_Start connecting to ip address = %s\r\n",httpServerIPAddr);
	printf("[Gsn_CloudHttpConnOpen] before GsnHttp_Start connecting to port = %d\r\n",portNo);

    // Open Http/Https connection
    status = GsnHttp_StartWithIPAndPort(&pHttpHandle, (INT8 *)httpServerIPAddr,
        portNo, &connParams, &(cloud_updater.httpConfInfo));
    printf("[Gsn_CloudHttpConnOpen] GsnHttp_Start status = %d\r\n", status);
    if(status == GSN_SUCCESS)
    {
        cloud_updater.bConnReady = TRUE;
        return pHttpHandle;
    }
    else
    {
        cloud_updater.bConnReady = FALSE;
        return NULL;
    }
}


PRIVATE
void Gsn_ResolveHostName()
{
	//unsigned char octet[4] = {0,0,0,0};

	if(cloud_updater.cloudType == EXOSITE)
		Gsn_ExositeGetCloudAddress(&cloud_updater);

#if 0
	printf(" before dns lookup cloud_updater.serverName = %s\r\n",cloud_updater.serverName);
	while(1)
	{
		ret = tfDnsGetHostByName(( const char* ) cloud_updater.serverName, (ttUserIpAddressPtr)&serverAddr);
		if(ret != TM_EWOULDBLOCK)
			break;
	}
	printf("ret = %d\r\n",ret);
	// convert IP stored serverAddr in integer form to dotted form
	for(i = 0;i< 4 ;i++)
	{
		octet[i] = (serverAddr >> (i*8) ) & 0xFF;
	}
	sprintf(cloud_updater.ipAddressString , "%d.%d.%d.%d",octet[0],octet[1],octet[2],octet[3]);
#else
	strcpy(cloud_updater.ipAddressString, cloud_updater.serverName);
#endif
	printf("cloud_updater.ipAddressString = %s\r\n",cloud_updater.ipAddressString);

}

/*
* POST /provision/activate HTTP/1.1
* Host: m2.exosite.com
* Content-Type: application/x-www-form-urlencoded; charset=utf-8
* Content-Length: <length>
* <blankline>
* vendor=<vendor>&model=<model>&sn=<sn>
*/
PUBLIC GSN_STATUS Gsn_ActivateExositeDevice()
{
	UINT32 serverPort = 80;
	UINT32 httpRxDataLen;

	GSN_STATUS retVal = GSN_SUCCESS;
	INT8 *pHttpRxDataBuf;
	INT8 BufferLen[10];
	UINT32 httpBufLen;
	INT8* reqBuf;

	printf("Gsn_CloudActivateDevice +\r\n");

	Gsn_ResolveHostName();


	/* Reset the Connection Connection Ready Flag */
	cloud_updater.bConnReady = FALSE ;

	/*Open the HTTP COnnection */
	printf(" before Gsn_CloudHttpConnOpen\r\n");

	cloud_updater.httpConfInfo.reqHeaderTypes = headerTypes;
	cloud_updater.httpConfInfo.reqHeaderValues = headerValues;
	cloud_updater.httpConfInfo.reqHeaderCount = 3;

	cloud_updater.httpConn= Gsn_CloudHttpConnOpen(cloud_updater.ipAddressString,serverPort,NULL,NULL,0);
	printf(" After Gsn_CloudHttpConnOpen\r\n");
	if(NULL == cloud_updater.httpConn)
	{
		printf("cloud_updater.httpConn is NULL\r\n");
		return GSN_FAILURE;
	}


	if(cloud_updater.cloudType == EXOSITE)
	{
		Gsn_ExositeFormatActivationRequest(&cloud_updater);
	}

	reqBuf = cloud_updater.httpRequestBuf;
	httpBufLen = cloud_updater.requestBufLen;
	printf("httpBufLen = %d\r\n",httpBufLen);

	sprintf(&BufferLen[0],"%d", httpBufLen);
	headerValues[CONTENT_LENGTH] = BufferLen;
	cloud_updater.httpConfInfo.reqPathPtr = PROVISION_PATH;       //page to be opened


	cloud_updater.httpConfInfo.reqMethod = GSN_HTTP_METHOD_POST;  //Request method
	cloud_updater.httpConfInfo.reqBodyLen = httpBufLen;           //Request body len
	cloud_updater.httpConfInfo.reqBodyTotalLen = httpBufLen;      //Request body total len
	cloud_updater.httpConfInfo.rxBufferMgmtCbCtx = NULL;
	cloud_updater.httpConfInfo.reqBodyPtr = reqBuf;              //Request body pointer

	pHttpRxDataBuf = &cloud_updater.httpRxBuf[0];

	httpRxDataLen = BUF_SIZE;
	memset(pHttpRxDataBuf, 0, BUF_SIZE);

	if( cloud_updater.bConnReady == TRUE )
	{
		/* Send Data */
		printf("[Gsn_CloudActivateDevice] Sending POST request to Server\r\n");
		retVal = GsnHttp_Send(cloud_updater.httpConn, (INT8 *)pHttpRxDataBuf,
					   &httpRxDataLen, HTTP_SEND_TIMEOUT, &(cloud_updater.httpConfInfo));
		printf("after GsnHttp_send\r\n");
	}
	/* Close the Http conn */
	if(cloud_updater.httpConn != NULL)
	{
		printf("Gsn_CloudActivateDevice closing the connection\r\n");
		GsnHttp_Close(cloud_updater.httpConn);
		cloud_updater.httpConn = NULL;
	}

	if(retVal == GSN_SUCCESS)
	{
		 if (httpRxDataLen)
		 {
			retVal = Gsn_DeviceActivationProcessResponse(pHttpRxDataBuf);
			// store the CIK in flash memory
			if(retVal == GSN_FAILURE)
			{
				// query the non volatile memory
				(*cloud_updater.cbFn)(GET_KEY, &cloud_updater.cloudCallbackData);
				//if(cloud_updater.cloudCallbackData->cloudKey != NULL)
				//{
						printf("AppNcmCfg_Get returned %s \r\n",cloud_updater.cloudCallbackData.cloudKey);
						if(strcmp(cloud_updater.cloudCallbackData.cloudKey,"") != 0)
						{
							printf("CIK found in NVDS\r\n");
							retVal = GSN_SUCCESS;
							strcpy(cloud_updater.CIK, cloud_updater.cloudCallbackData.cloudKey);
						}

				//}
			}
			else
			{
				// store the CIK in non volatile memory
				(*cloud_updater.cbFn)(STORE_KEY, &cloud_updater.cloudCallbackData);

			}
		 }
	}


	return retVal;
}
/*
Send the Node readings to the cloud server
POST https://m2.exosite.com/onep:v1/stack/alias
X-Exosite-CIK: e3aa43b1bb4c33f039f2f78317401e173095618b
Content-Length: 29
Content-Type: application/x-www-form-urlencoded; charset=utf-8

led_control=%d&temp=%d&light=%d
*/
PRIVATE GSN_STATUS
Gsn_SendCloudUpdates( INT8* reqBuf, UINT32 httpBufLen)
{
	UINT32 serverPort = 80;
    UINT32 httpRxDataLen;

    GSN_STATUS retVal = GSN_SUCCESS;
	INT8 *pHttpRxDataBuf;
	INT8 BufferLen[10];
	INT8 CIKheader[120];


	printf("Gsn_SendCloudUpdates +\r\n");
    Gsn_ResolveHostName();

    /* Reset the Connection Connection Ready Flag */
    cloud_updater.bConnReady = FALSE ;

    /*Open the HTTP COnnection */
	printf(" before Gsn_CloudHttpConnOpen\r\n");

	cloud_updater.httpConfInfo.reqHeaderTypes = headerTypes2;
	cloud_updater.httpConfInfo.reqHeaderValues = headerValues2;
	cloud_updater.httpConfInfo.reqHeaderCount = HEADER_COUNT2;

    cloud_updater.httpConn= Gsn_CloudHttpConnOpen(cloud_updater.ipAddressString,serverPort,NULL,NULL,0);
    printf(" After Gsn_CloudHttpConnOpen\r\n");
	if(NULL == cloud_updater.httpConn)
    {
		printf("cloud_updater.httpConn is NULL\r\n");
		return GSN_FAILURE;
    }


	printf("httpBufLen = %d\r\n",httpBufLen);

	sprintf(&BufferLen[0],"%d", httpBufLen);
    headerValues2[CONTENT_LENGTH] = &BufferLen[0];
    //headerValues2[CIK] = "X-Exosite-CIK: 995c5a03d96db440ef8fabc8756dfa8e271aaa56";
	
	// case for TLS Low POwer
    // query the non volatile memory
    (*cloud_updater.cbFn)(GET_KEY, &cloud_updater.cloudCallbackData);
				
    printf("AppNcmCfg_Get returned %s \r\n",cloud_updater.cloudCallbackData.cloudKey);
    if(strcmp(cloud_updater.cloudCallbackData.cloudKey,"") != 0)
    {
        AppDbg_Printf("CIK found in NVDS\r\n");
        retVal = GSN_SUCCESS;
        strcpy(cloud_updater.CIK, cloud_updater.cloudCallbackData.cloudKey);
    }

				

    strcpy(CIKheader,"");
    strcat(CIKheader,"X-Exosite-CIK: ");
    cloud_updater.CIK[CLOUD_KEY_LEN-1] = 0;
    strcat(CIKheader,cloud_updater.CIK);
    headerValues2[CIK] = CIKheader;

    printf("headerValues2[content-length] = %s\r\n",headerValues2[CONTENT_LENGTH]);
    printf("headerValues2[CIK] = %s\r\n",headerValues2[CIK]);
	cloud_updater.httpConfInfo.reqPathPtr = READING_PATH;       //page to be opened


    cloud_updater.httpConfInfo.reqMethod = GSN_HTTP_METHOD_POST;  //Request method
    cloud_updater.httpConfInfo.reqBodyLen = httpBufLen;           //Request body len
    cloud_updater.httpConfInfo.reqBodyTotalLen = httpBufLen;      //Request body total len
    cloud_updater.httpConfInfo.rxBufferMgmtCbCtx = NULL;
    cloud_updater.httpConfInfo.reqBodyPtr = reqBuf;              //Request body pointer

	pHttpRxDataBuf = &cloud_updater.httpRxBuf[0];

    httpRxDataLen = BUF_SIZE;
    memset(pHttpRxDataBuf, ZERO, BUF_SIZE);

    if( cloud_updater.bConnReady == TRUE )
    {
        /* Send Data */
        printf("[Gsn_SendCloudUpdates] Sending POST request to Server\r\n");
        retVal = GsnHttp_Send(cloud_updater.httpConn, (INT8 *)pHttpRxDataBuf,
                       &httpRxDataLen, HTTP_SEND_TIMEOUT, &(cloud_updater.httpConfInfo));
    }
	 if(retVal == GSN_SUCCESS)
    {
		 if (httpRxDataLen)
			 retVal = Gsn_CloudProcessResponse(pHttpRxDataBuf);
    }


    /* Close the Http conn */
    if(cloud_updater.httpConn != NULL)
    {
	    printf("Gsn_SendCloudUpdates closing the connection\r\n");
        GsnHttp_Close(cloud_updater.httpConn);
        cloud_updater.httpConn = NULL;
    }

	return retVal;
}

PUBLIC GSN_STATUS Gsn_GetSensorUpdatesandPost()
{
	UINT32 httpBufLen;
	INT8* reqBuf;

	GSN_STATUS retVal = GSN_SUCCESS;


	if(appFormatFn)
	{
		 (*appFormatFn)(&cloud_updater);
		 reqBuf = cloud_updater.httpRequestBuf;
		 httpBufLen = cloud_updater.requestBufLen;
		 printf("requestBufLen = %d\r\n",httpBufLen);
	}
	retVal = Gsn_SendCloudUpdates( reqBuf, httpBufLen);
	if(retVal != GSN_SUCCESS)
	{
		printf("Gsn_SendCloudUpdates returned error %d\r\n",retVal);
	}
	return retVal;
}

PUBLIC VOID Gsn_ExositeInit(GSN_APP_CLOUD_CONTEXT_T* appContext)
{
    cloud_updater.cbFn = appContext->cloudCallbackFn;

    cloud_updater.httpConn = NULL;
    cloud_updater.bConnReady = FALSE;

	/* if adkType is tls, assign the fn pointer to tlsformatting
	 * else to sp formatting
	 */
	cloud_updater.updateInterval = appContext->updateInterval;
	cloud_updater.cloudType = appContext->cloudType;
	cloud_updater.adkType = appContext->adkType;
	printf("appContext->uid = %s\r\n",appContext->uid);
	strcpy(cloud_updater.uid,appContext->uid);
	printf("passed uid = %s\r\n",cloud_updater.uid);
	printf("appContext->adkType = %d\r\n",appContext->adkType);
	if(cloud_updater.adkType == TLS_ADK)
	{
		printf("TLS adk type\r\n");
		appFormatFn = Gsn_TlsFormatData;
		/* depending on adktype, malloc of the correct structure */
		cloud_updater.cloudCallbackData.adkData = (GSN_TLS_ADK_DATA_T*)malloc(sizeof(GSN_TLS_ADK_DATA_T));

	}

	if(cloud_updater.adkType == SP_ADK)
	{
		printf("SP adk type\r\n");
		appFormatFn = Gsn_SpFormatData;
		/* depending on adktype, malloc of the correct structure */
		cloud_updater.cloudCallbackData.adkData = (GSN_SP_ADK_DATA_T*)malloc(sizeof(GSN_SP_ADK_DATA_T));
	}
}
PUBLIC GSN_STATUS GsnExosite_FlushLoadRequest()
{
	UINT32 serverPort = 80;
	UINT32 httpRxDataLen;

	GSN_STATUS retVal = GSN_SUCCESS;
	INT8 *pHttpRxDataBuf;
	INT8 BufferLen[10];
	INT8* reqBuf;
	UINT8 httpreqBufLen = 0;


	printf("Gsn_FlushExositeLoadRequest +\r\n");

	/* Reset the Connection Connection Ready Flag */
	cloud_updater.bConnReady = FALSE ;

	/*Open the HTTP COnnection */
	printf(" before Gsn_CloudHttpConnOpen\r\n");

	reqBuf = &cloud_updater.httpRequestBuf[0];

	cloud_updater.httpConfInfo.reqHeaderTypes = headerTypes;
	cloud_updater.httpConfInfo.reqHeaderValues = headerValues3;
	cloud_updater.httpConfInfo.reqHeaderCount = 3;

	cloud_updater.httpConn= Gsn_CloudHttpConnOpen(cloud_updater.ipAddressString,serverPort,NULL,NULL,0);
	printf(" After Gsn_CloudHttpConnOpen\r\n");
	if(NULL == cloud_updater.httpConn)
	{
		printf("cloud_updater.httpConn is NULL\r\n");
		return GSN_FAILURE;
	}

	httpreqBufLen = sprintf(reqBuf,"{\"auth\":{\"cik\":\"%s\"},\"calls\":[{\"id\":1,\"procedure\":\"flush\",\"arguments\":[{\"alias\":\"%s\"},{}]}]}",cloud_updater.CIK,LOAD_REQUEST_ALIAS);

	sprintf(&BufferLen[0],"%d", httpreqBufLen);
	headerValues3[CONTENT_LENGTH] = &BufferLen[0];

	cloud_updater.httpConfInfo.reqPathPtr = FLUSH_DATA_PATH;       //page to be opened


	cloud_updater.httpConfInfo.reqMethod = GSN_HTTP_METHOD_POST;  //Request method
	cloud_updater.httpConfInfo.reqBodyLen = httpreqBufLen;           //Request body len
	cloud_updater.httpConfInfo.reqBodyTotalLen = httpreqBufLen;      //Request body total len
	cloud_updater.httpConfInfo.rxBufferMgmtCbCtx = NULL;
	cloud_updater.httpConfInfo.reqBodyPtr = reqBuf;              //Request body pointer

	pHttpRxDataBuf = &cloud_updater.httpRxBuf[0];

	httpRxDataLen = BUF_SIZE;
	memset(pHttpRxDataBuf, ZERO, BUF_SIZE);


	if( cloud_updater.bConnReady == TRUE )
	{
		/* Send Data */
		printf("[Gsn_SendCloudUpdates] Sending POST request to Server\r\n");
		retVal = GsnHttp_Send(cloud_updater.httpConn, (INT8 *)pHttpRxDataBuf,
					   &httpRxDataLen, HTTP_SEND_TIMEOUT, &(cloud_updater.httpConfInfo));
	}
	 if(retVal == GSN_SUCCESS)
	{
		 if (httpRxDataLen)
			 retVal = Gsn_CloudProcessFlushResponse(pHttpRxDataBuf);
	}


	/* Close the Http conn */
	if(cloud_updater.httpConn != NULL)
	{
		printf("Gsn_SendCloudUpdates closing the connection\r\n");
		GsnHttp_Close(cloud_updater.httpConn);
		cloud_updater.httpConn = NULL;
	}

		return retVal;
}
GSN_STATUS Gsn_ExositeSetLoadControl()
{
	// first get the load status from the hardware.

	//Gsn_SpCloudGetLoadStatus(&cloud_updater);
	if(cloud_updater.loadStatus >= 0)
	{
		Gsn_SpCloudSetLoadStatus(&cloud_updater);
		// flush the data from cloud
		GsnExosite_FlushLoadRequest();
		return GSN_SUCCESS;
	}
	return GSN_FAILURE;
}

VOID GsnExosite_GetConfig(UINT32 updateInterval)
{
    UINT8 i =0,count = 0;
	if(cloud_updater.adkType  == TLS_ADK)
	{
		// update readings after specified time interval
		GsnTaskSleep(updateInterval);
	}
	else if(cloud_updater.adkType  == SP_ADK)
	{
		// read load control from the cloud
		count = updateInterval/1000;
		for(i = 0;i<count;i++)
		{
			GsnExosite_GetLoadControl();
			if(Gsn_ExositeSetLoadControl() == GSN_SUCCESS) break;
			GsnTaskSleep(1000);
		}
	}
}

GSN_STATUS GsnExosite_GetLoadControl()
{
	// get load control state from the cloud
	// check if it has changed. compare with the load status
	// if it has changed, turn on/off the load and post the changed status to the cloud
	UINT32 serverPort = 80;
	INT8* pHttpRxDataBuf;
	INT8 CIKheader[120];        
    GSN_STATUS retVal = GSN_SUCCESS;
    UINT32 httpRxDataLen;
	AppDbg_Printf("Gsn_ExositeGetLoadControl\r\n");

    /* Reset the Connection Ready Flag */
    cloud_updater.bConnReady = FALSE ;

    /*Open the HTTP COnnection */
	AppDbg_Printf("Gsn_ExositeGetLoadControl before connection open\r\n");

	cloud_updater.httpConfInfo.reqHeaderTypes = headerTypesForGet;
	cloud_updater.httpConfInfo.reqHeaderValues = headerValuesForGet;
	cloud_updater.httpConfInfo.reqHeaderCount = 3;
    cloud_updater.httpConn= Gsn_CloudHttpConnOpen(cloud_updater.ipAddressString,serverPort,NULL,NULL,0);
    AppDbg_Printf("Gsn_ExositeGetLoadControl before connection open\r\n");

	if(NULL == cloud_updater.httpConn)
	{
		AppDbg_Printf("Gsn_ExositeGetLoadControl cloud_updater.httpConn is NULL\r\n");
		return GSN_FAILURE;
	}

	strcpy(CIKheader,"");
	strcat(CIKheader,"X-Exosite-CIK: ");
	cloud_updater.CIK[CLOUD_KEY_LEN-1] = 0;
	strcat(CIKheader,cloud_updater.CIK);
	headerValuesForGet[2] = CIKheader;

	AppDbg_Printf("headerValuesForGet[CIK] = %s\r\n",headerValuesForGet[2]);
	cloud_updater.httpConfInfo.reqPathPtr = READING_PATH_LOAD_CONTROL;       //page to be opened
	cloud_updater.httpConfInfo.reqMethod = GSN_HTTP_METHOD_GET;  //Request method
	cloud_updater.httpConfInfo.reqBodyLen = 0;           //Request body len
	cloud_updater.httpConfInfo.reqBodyTotalLen = 0;      //Request body total len
	cloud_updater.httpConfInfo.rxBufferMgmtCbCtx = NULL;
	cloud_updater.httpConfInfo.reqBodyPtr = NULL;              //Request body pointer

	pHttpRxDataBuf = &cloud_updater.httpRxBuf[0];

	httpRxDataLen = BUF_SIZE;
	memset(pHttpRxDataBuf, ZERO, BUF_SIZE);

	if( cloud_updater.bConnReady == TRUE )
	{
		/* Send Data */
		AppDbg_Printf("[Gsn_ExositeGetLoadControl] Sending POST request to Server\r\n");
		retVal = GsnHttp_Send(cloud_updater.httpConn, (INT8 *)pHttpRxDataBuf,
					   &httpRxDataLen, HTTP_SEND_TIMEOUT, &(cloud_updater.httpConfInfo));
	}
	 if(retVal == GSN_SUCCESS)
	{
		 if (httpRxDataLen)
			 retVal = GsnSp_ProcessGetLoadResponse(pHttpRxDataBuf, &cloud_updater);
	}

	/* Close the Http conn */
	if(cloud_updater.httpConn != NULL)
	{
		AppDbg_Printf("Gsn_SendCloudUpdates closing the connection\r\n");
		GsnHttp_Close(cloud_updater.httpConn);
		cloud_updater.httpConn = NULL;
	}
	return retVal;

}
