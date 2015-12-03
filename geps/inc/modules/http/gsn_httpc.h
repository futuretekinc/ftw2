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
* $RCSfile: gsn_httpc.h,v $
*
* Description : This file contains GSN HTTP API.
*******************************************************************************/
#ifndef _GSN_HTTP_H_
#define _GSN_HTTP_H_

#include "netx/netx_bsd_layer/nxd_bsd.h"
#include "modules/http/include/trsocket.h"
#include "modules/http/include/trmacro.h"
#include "modules/http/include/trtype.h"
#include "modules/http/include/trhttpc.h"
#include "netx/nx_api.h"
#include "modules/ssl/gsn_ssl.h"
#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
* File Inclusion
********************************************************************************/

/**
 *******************************************************************************
 * @file gsn_httpc.h
 * @brief GSN HTTP public header.
 *    This file contains the public APIs and structures of HTTP module.
 ******************************************************************************/


/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/


/**
 *******************************************************************************
 * @defgroup GsnHttp GSN HTTP API
 *
 ******************************************************************************/

/**
 *****************************************************************************
 *
 * @} 
 *****************************************************************************/


/*******************************************************************************
* Public Typedefs
 ******************************************************************************/

/**
 *******************************************************************************
 * @ingroup GsnHttp
 * @brief Http Connection handle.
 *
 * This is the HTTP connection handle returned by GsnHttp_Start API. It is passed
 * as a parameter in all subsequent operations for the HTTP connection.
 ******************************************************************************/
typedef void* GSN_HTTPC_CONN_HANDLE;


#if 1//def GSN_HTTP_CUSTOM_SUPPORT
typedef VOID (* GSN_HTTP_RX_HDRS_CB_T) (GSN_HTTPC_CONN_HANDLE conHandle,
        INT32              statusCode,
        INT8              *reasonPhrase,
        INT8             **resHeadersPtr,
        ttHttpcCustomHdr  *customHdrPtr);
#endif

/**
 *******************************************************************************
 * @ingroup GsnHttp
 * @brief Http Rx Buffer Mgmt Callback.
 *
 * A callback function of this type should be provided by caller in GsnHttp_Send
 * API which will be called back by HTTP.
 ******************************************************************************/
typedef VOID (* GSN_HTTP_RX_BUFFER_MGMT_CB_T)(VOID *ctx,
                                                GSN_HTTPC_CONN_HANDLE conHandle,
                                                INT8 *httpRxDataBuf,
                                                INT32 httpRxDataLen,
                                                INT32 *rxBufferMgmtstatus);
/**
 *******************************************************************************
 * @ingroup GsnHttp
 * @brief Http type.
 *
 * This enum defines the type of http - plain or secure.
 ******************************************************************************/
typedef enum GSN_HTTP_TYPE
{
    GSN_HTTP = 0,
    GSN_HTTPS
}GSN_HTTP_TYPE_T;

/**
 *******************************************************************************
 * @ingroup GsnHttp
 * @brief Http version.
 *
 * This enum defines HTTP versions.
 ******************************************************************************/
typedef enum GSN_HTTP_USER_VERSION
{
    GSN_HTTP_VERSION_INVAL  = TM_HTTP_VERSION_INVAL,      /**< special value for invalid version*/
    GSN_HTTP_VERSION_0_9 = TM_HTTP_VERSION_0_9,        /**< HTTP version 0.9 */
    GSN_HTTP_VERSION_1_0 = TM_HTTP_VERSION_1_0,        /**< HTTP version 1.0 */
    GSN_HTTP_VERSION_1_1 = TM_HTTP_VERSION_1_1         /**< HTTP version 1.1 */
} GSN_HTTP_USER_VERSION_T;


/**
 *******************************************************************************
 * @ingroup GsnHttp
 * @brief Http user method.
 *
 * This enum defines HTTP user method types. This is used to select the method
 * in the HTTP exchanges.
 ******************************************************************************/
typedef enum GSN_HTTP_USER_METHOD
{
    GSN_HTTP_METHOD_INVAL = TM_HTTP_METHOD_INVAL,       /**< special value for invalid method */
    GSN_HTTP_METHOD_GET = TM_HTTP_METHOD_GET,         /**< HTTP method GET                  */
    GSN_HTTP_METHOD_HEAD = TM_HTTP_METHOD_HEAD,        /**< HTTP method HEAD                 */
    GSN_HTTP_METHOD_POST = TM_HTTP_METHOD_POST,        /**< HTTP method POST                 */
    GSN_HTTP_METHOD_CONNECT = TM_HTTP_METHOD_CONNECT,     /**< HTTP method CONNECT              */
    GSN_HTTP_METHOD_PUT = TM_HTTP_METHOD_PUT,
    GSN_HTTP_METHOD_DELETE = TM_HTTP_METHOD_DELETE,
    GSN_HTTP_METHOD_COUNT = TM_HTTP_METHOD_COUNT,        /**< Total number of methods above    */   
	GSN_HTTP_METHOD_GETRESP,
	GSN_HTTP_METHOD_POSTRESP,
	GSN_HTTP_METHOD_PUTRESP,
	GSN_HTTP_METHOD_DELETERESP
} GSN_HTTP_USER_METHOD_T;

/**
 *******************************************************************************
 * @ingroup GsnHttp
 * @brief Http user header types.
 *
 * This enum defines http 1.0/1.1 header types.
 ******************************************************************************/
typedef enum GSN_HTTP_USER_HEADER_TYPE
{
    GSN_HTTP_HEADER_INVAL = TM_HTTP_HEADER_INVAL,       /* special value for invalid header */	
    GSN_HTTP_HEADER_ALLOW = TM_HTTP_HEADER_ALLOW,
    GSN_HTTP_HEADER_AUTHORIZATION = TM_HTTP_HEADER_AUTHORIZATION,
    GSN_HTTP_HEADER_CONNECTION = TM_HTTP_HEADER_CONNECTION,
    GSN_HTTP_HEADER_CONTENT_ENCODING = TM_HTTP_HEADER_CONTENT_ENCODING,
    GSN_HTTP_HEADER_CONTENT_LENGTH = TM_HTTP_HEADER_CONTENT_LENGTH,
    GSN_HTTP_HEADER_CONTENT_RANGE = TM_HTTP_HEADER_CONTENT_RANGE,
    GSN_HTTP_HEADER_CONTENT_TYPE = TM_HTTP_HEADER_CONTENT_TYPE,
    GSN_HTTP_HEADER_COOKIE = TM_HTTP_HEADER_COOKIE,
    GSN_HTTP_HEADER_COOKIE2 = TM_HTTP_HEADER_COOKIE2,
    GSN_HTTP_HEADER_DATE = TM_HTTP_HEADER_DATE,
    GSN_HTTP_HEADER_EXPIRES = TM_HTTP_HEADER_EXPIRES,
    GSN_HTTP_HEADER_FROM = TM_HTTP_HEADER_FROM,
    GSN_HTTP_HEADER_HOST= TM_HTTP_HEADER_HOST,
    GSN_HTTP_HEADER_IF_MODIFIED_SINCE = TM_HTTP_HEADER_IF_MODIFIED_SINCE,
    GSN_HTTP_HEADER_LAST_MODIFIED = TM_HTTP_HEADER_LAST_MODIFIED,
    GSN_HTTP_HEADER_LOCATION = TM_HTTP_HEADER_LOCATION,
    GSN_HTTP_HEADER_PRAGMA = TM_HTTP_HEADER_PRAGMA,
    GSN_HTTP_HEADER_RANGE = TM_HTTP_HEADER_RANGE,
    GSN_HTTP_HEADER_REFERER = TM_HTTP_HEADER_REFERER,
    GSN_HTTP_HEADER_SERVER = TM_HTTP_HEADER_SERVER,
    GSN_HTTP_HEADER_SET_COOKIE= TM_HTTP_HEADER_SET_COOKIE,
    GSN_HTTP_HEADER_TRANSFER_ENCODING = TM_HTTP_HEADER_TRANSFER_ENCODING,
    GSN_HTTP_HEADER_USER_AGENT = TM_HTTP_HEADER_USER_AGENT,
    GSN_HTTP_HEADER_WWW_AUTHENTICATE = TM_HTTP_HEADER_WWW_AUTHENTICATE,
    GSN_HTTP_HEADER_COUNT = TM_HTTP_HEADER_COUNT,   /* total number of headers defined above    */
    GSN_HTTP_HEADER_ALL = TM_HTTP_HEADER_ALL,   /* special value to refer to all headers    */
    GSN_HTTP_HEADER_CUSTOM = TM_HTTP_HEADER_CUSTOM,    /* Any custom header*/
    GSN_HTTP_HEADER_CUSTOM_MAX = 0xFFFFFFFF,
}  GSN_HTTP_USER_HEADER_TYPE_T;

/**
 *******************************************************************************
 * @ingroup GsnHttp
 * @brief Http open parameters.
 *
 *      This structure defines some of the parameters used for opening the HTTP 
 *      connection. This structure needs to be filled and passed to GsnHttp_Start()
 ******************************************************************************/
typedef struct GSN_HTTPC_CONN_PARAMS
{
   GSN_HTTP_TYPE_T type; /*Type of connection required. Non secured/Secured(0/1).*/
   UINT8 proxyPresent; /*flag indicating connection through proxy/not (1/0)*/
   INT32 ConTimeout; /* maximum time to wait for the connection to happen */
   GSN_SSL_CONN_PARAMS_T sslParams; /* SSL parameter ddata structure */
   UINT32 sslExtnType;
   UINT32 sslExtnMaxFragLen;
   UINT8  sslExtnRenegoEnable;
   GSN_SSL_DNS_BUF_INFO_T *dnsBuf;
}GSN_HTTPC_CONN_PARAMS_T;

/**
 *******************************************************************************
 * @ingroup GsnHttp
 * @brief Http Config structure.
 *
 * This structure contains the parameters that define an instance of the Http
 * Configuration.
 ******************************************************************************/
typedef struct GSN_HTTPC_CONF_INFO
{
    /* Information about the Mathod Line */
    GSN_HTTP_USER_VERSION_T reqVersion;
    GSN_HTTP_USER_METHOD_T reqMethod;
    INT8 *reqPathPtr;

    /* Information about the Request Headers */
    GSN_HTTP_USER_HEADER_TYPE_T *reqHeaderTypes;
    INT8    **reqHeaderValues;
    INT32   reqHeaderCount;

    /* Information about the Request Body */
    INT8 *reqBodyPtr;
    INT32 reqBodyLen;
    INT32 reqBodyTotalLen;
    INT32 reqBodySentLen;

    /* Information about the Response Status Line */
#if 0
    GSN_HTTP_USER_VERSION_T resVersion;
    INT32 resStatusCode;
    UINT8 resReasonPhrasePtr;
#endif
    /* Information about the Response Headers*/
    INT8 **resHeadersPtr;

    /* Information about the Response Body*/
    UINT32 copiedLen;/*any response bytes already copied */

#if 1//def GSN_HTTP_CUSTOM_SUPPORT
    GSN_HTTP_RX_HDRS_CB_T        rxHdrsCb;
    UINT32  sendStatus;
    UINT32  httpcHdrBmap;
    UINT32  hconHttpcHdrSent;
#endif
    /* Information about the Response Buffer Management*/
    GSN_HTTP_RX_BUFFER_MGMT_CB_T rxBufferMgmtCb;
    VOID                    *rxBufferMgmtCbCtx;
    
    /* Request and Response state, some flags*/
	UINT32 httpTimeOut;
    UINT8 moredata;
    UINT8 reqSendState;
    /* pointer to packet pool */
	//GSN_NW_PKT_POOL_HANDLE *pktPoolHndl;
} GSN_HTTPC_CONF_INFO_T;

/*******************************************************************************
 * Public Functions
 ******************************************************************************/


/**
 *******************************************************************************
 * @ingroup GsnHttp
 * @brief GSN HTTP Start
 *
 *    This function Starts the HTTP connection.Furhter this connection can be used 
 * to get or post http data to a http server. This call supports both nonsecured 
 * and secured(ssl) connections.
 * @param pHttpConnHandle - OUT Pointer to Http handle which will be returned 
                              after successful connection.
 * @param pSockAddr - IN Pointer to IP address of server.
 * @param pHttpcConnParams - pointer to the structure of type GSN_HTTPC_CONN_PARAMS_T
 * @param pHttpConfInfo - IN Pointer to the Gsn http conf info
 *
 * @retval GSN_SUCCESS HTTP client Connection successful.
 * @retval GSN_FAILURE http client open failed.
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnHttp_Start(GSN_HTTPC_CONN_HANDLE *pHttpConnHandle, struct sockaddr_storage *pSockAddr,
			  GSN_HTTPC_CONN_PARAMS_T *pHttpcConnParams,
              GSN_HTTPC_CONF_INFO_T * pHttpConfInfo);

/**
 *******************************************************************************
 * @ingroup GsnHttp
 * @brief GSN HTTP Send
 *
 *    This function Sends and receives data over HTTP connection.
 * @param conHandle - IN Pointer to http connection handle obtained by successful
 *                        http open using GsnHttp_Start() call.
 * @param respBuff - OUT Pointer to receive buffer. Data received on this
 *                             connection is copied in to the buffer for further
 *                             processing by user application.
 * @param respBuffLen - IN/OUT while calling max length of the receive buffer
 *                           is passed.when the call completes, actual data
 *                           received
 *                           will be returned through this.
 * @param timeOut - IN receive timeout in seconds.
 * @param pHttpConfInfo - IN  pointer to http header configuration.
 *
 * @retval GSN_SUCCESS HTTP client Connection successful.
 * @retval GSN_FAILURE http client open failed.
 * @retval GSN_BUFFER_OVERFLOW http client GET/POST failed as receive buffer is
 * not sufficiet to hold the response and rxBufferMgmtCb is not present.
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnHttp_Send(GSN_HTTPC_CONN_HANDLE conHandle, INT8 *respBuff,
             UINT32 *respBuffLen, INT32 timeOut,  
             GSN_HTTPC_CONF_INFO_T * pHttpConfInfo);
/**
 *******************************************************************************
 * @ingroup GsnHttp
 * @brief GSN Http close
 *
 *    This function closes HTTP connection
 * @param conHandle - IN Pointer to http connection handle obtained by successful
                         http open using GsnHttp_Start() call.
 * @retval GSN_SUCCESS HTTP client Connection close successful.
 * @retval GSN_FAILURE http client close failed.
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnHttp_Close(GSN_HTTPC_CONN_HANDLE conHandle);

/**
 *******************************************************************************
 * @ingroup GsnHttp
 * @brief GSN Http close
 *
 *    This function sends HTTP Alert
 * @param conHandle - IN Pointer to http connection handle obtained by successful
                         http open using GsnHttp_Start() call.
 * @retval GSN_SUCCESS HTTP Alert send successful.
 * @retval GSN_FAILURE http Alert send failed.
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnHttp_Alert(GSN_HTTPC_CONN_HANDLE conHandle);



#ifdef __cplusplus
}
#endif

#endif /* _GSN_HTTP_H_ */




