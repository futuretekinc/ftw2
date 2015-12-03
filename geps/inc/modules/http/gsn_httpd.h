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
* $RCSfile: gsn_httpd.h,v $
*
* Description : Header file for gsn httpd public functions and data structures
*******************************************************************************/
#ifndef _GSN_HTTPD_H
#define _GSN_HTTPD_H

//#define GSN_WEB_SERVER

//#ifdef GSN_WEB_SERVER

#include "modules/http/include/trhttpd.h"
#include "gsn_types.h"
#include "modules/ssl/gsn_ssl.h"
/**
 *******************************************************************************
 * @file gsn_httpd.h
 * @brief GSN HTTPD Public header
 *    This file contains definitions for the HTTPD Wrapper and URI Handler
 ******************************************************************************/


/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/


/**
 *******************************************************************************
 * @defgroup GsnHttpd GSN HTTP Server
 * @brief  GSN HTTP Server Wrapper and URI Handler
 *
 *    This file contains public definitions and API's for HTTP Server
 *    Wrapper and URI Handler. <br>
 *
 *   <br>
 *    This file contains public definitions and API's for HTTP Server
 *    Wrapper and URI Handler. The HTTP Server wrapper provides an API around
 *    the native web server making configuration much easier. The URI handler
 *    provides a mechanism for applications to attach handlers to URI's
 *    (resources). This allows applications to build a RESTful architecture
 *    based on HTTP APIs.
 ******************************************************************************/

/**
 *****************************************************************************
 *
 * @}
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Max HTTPD user name length
 *    This macro defines the maximum HTTPD user name length supported
 *****************************************************************************/
#define GSN_HTTPD_MAX_USERNAME_LEN 32
/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Max HTTPD Password length
 *    This macro defines the maximum HTTPD password length supported
 *****************************************************************************/
#define GSN_HTTPD_MAX_PASSWORD_LEN 32


/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Max Number of URI Handlers
 *    This macro defines the size of the URI handler table. This should be
 *    set appropriately to ensure the enough memory is available and that
 *    memory is not wasted.
 *****************************************************************************/
#define GSN_HTTPD_MAX_URI_HANDLERS 10
/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Max Length of the URI
 *    This macro defines the maximum length of the URI that is supported
 *****************************************************************************/
#define GSN_HTTPD_MAX_URI_LENGTH 64
/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Max Length of the URI
 *    This macro defines the maximum length of the URI description that is
 *    supported. The description string should be short and less than this
 *    value.
 *****************************************************************************/
#define GSN_HTTPD_MAX_DESC_LENGTH 64

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Max HTTPD Wrapper/URI Handler status and error codes
 *    This data type defines the various status and error codes that can be
 *    returned by the HTTP Wrapper/URI Handler
 *****************************************************************************/
typedef enum
{
    GSN_HTTPD_SUCCESS = 0,
    GSN_HTTPD_FAILURE,
    GSN_HTTPD_ALREADY_STARTED,
    GSN_HTTPD_URI_HANDLER_NO_MEM,
    GSN_HTTPD_URI_HANDLER_INVALID,
} GSN_HTTPD_STATUS_T;

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Definition of HTTP Method when none is supported
 *****************************************************************************/
#define GSN_HTTPD_URI_METHOD_NONE 0
/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Definition of HTTP GET Method
 *****************************************************************************/
#define GSN_HTTPD_URI_METHOD_GET 0x1
/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Definition of HTTP POST Method
 *****************************************************************************/
#define GSN_HTTPD_URI_METHOD_POST 0x2

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Definition of HTTP PUT Method
 *****************************************************************************/
#define GSN_HTTPD_URI_METHOD_PUT 0x3

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Definition of HTTP PUT Method
 *****************************************************************************/
#define GSN_HTTPD_URI_METHOD_DELETE 0x4

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Definition of HTTP  GET + POST Method
 *****************************************************************************/
#define GSN_HTTPD_URI_METHOD_GET_POST  (GSN_HTTPD_URI_METHOD_GET | GSN_HTTPD_URI_METHOD_POST)

#define GSN_HTTPD_URI_METHOD_GET_POST_PUT  (GSN_HTTPD_URI_METHOD_GET | GSN_HTTPD_URI_METHOD_POST | GSN_HTTPD_URI_METHOD_PUT)
#define GSN_HTTPD_URI_METHOD_GET_POST_PUT_DEL (GSN_HTTPD_URI_METHOD_GET | GSN_HTTPD_URI_METHOD_POST | GSN_HTTPD_URI_METHOD_PUT | GSN_HTTPD_URI_METHOD_DELETE)
/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Definition of the callback function for processing events from HTTPD.
 *    Definition of the callback function for processing events from HTTPD.
 *    Each URI handler has to specify a callback function to handle events
 *    being posted from the HTTP server.
 *****************************************************************************/
typedef GSN_HTTPD_STATUS_T (*GSN_HTTPD_URI_HANDLER_FN_T)(ttHttpdUserEvent event,
        const char* uri, ttHttpdUserConHandle conn_handler);

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 *
 * @{
 *****************************************************************************/
/**
 * @brief Definitions of the various HTTP Content types
 *    There are definitions for the various content types that can be returned
 *    by the URI handlers
 *****************************************************************************/
#define GSN_HTTPD_CONTENT_APP_XML  0
#define GSN_HTTPD_CONTENT_APP_JSON 1
#define GSN_HTTPD_CONTENT_APP_HTML 2
#define GSN_HTTPD_CONTENT_IMG_GIF  3
#define GSN_HTTPD_CONTENT_APP_OCTSTRM  4
#define GSN_HTTPD_CONTENT_TYPES_MAX     5
#define GSN_HTTPD_CONTENT_DEFAULT  GSN_HTTPD_CONTENT_APP_XML

#define GSN_USE_IPV6 0x01
#define GSN_USE_IPV4 0x02

/**
 *****************************************************************************
 *
 * @}
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Definition of URI handler structure
 *    Definition of the URI handler structure that is used by the HTTPD
 *    URI handler to dispatch requests to URIs appropriately.
 *****************************************************************************/
typedef struct GSN_HTTPD_URI_HANDLER
{
    UINT8 uri[GSN_HTTPD_MAX_URI_LENGTH];  /**< URI that is being handled */
    GSN_HTTPD_URI_HANDLER_FN_T uri_handler_fn; /**< Callback function for events */
    UINT8 desc[GSN_HTTPD_MAX_DESC_LENGTH]; /**< Description of URI */
    UINT8 methods; /**< Method(s) supported for the URI */
    UINT8 contentType; /**< Content type being served by the URI handler */
} GSN_HTTPD_URI_HANDLER_T;

GSN_HTTPD_URI_HANDLER_T* GsnHttpd_UriHandlerGet();

GSN_HTTPD_STATUS_T
GsnHttpd_UriHandlerConfig(char *uri, UINT8 methods, char* desc,
        GSN_HTTPD_URI_HANDLER_FN_T fnCallback, UINT8 contentType);

int GsnHttpd_UriHandlerUnregister(char *uri, char* desc,
        GSN_HTTPD_URI_HANDLER_FN_T fnCallback);


/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Definition of Config structure governing behavior of HTTPD server
 *    Definition of the Config structure that governs the behavior of the
 *    HTTPD server. Application can set the various parameters of this
 *    structure and the HTTP server will be configured appropriately when
 *    GsnHttpd_Start is called
 *
 * @see GsnHttpd_Start
 *****************************************************************************/
typedef struct GSN_HTTPD_CONFIG
{

	UINT8  ip_flag;
	char  ipAddr6[16];

    UINT32 ipAddr; /**< IP address on which HTTPD should start */

    int port; /**< Port on which HTTPD should start */
    UINT8 maxConnTotal; /**< Maximum connections supported */
    UINT8 maxConnPerIp; /**< Maximum connections supported  per IP */
    UINT8 idleTimeout; /**< Idle timeout after which HTTP server closes conn */
    UINT8 blockingState; /**< Blocking state of HTTPD when started */
    UINT8 threadPriority; /**< Priority of HTTPD task */
    char *redirectUrl; /**< Default page to be served */
    char username[GSN_HTTPD_MAX_USERNAME_LEN]; /**< Username for authentication */
    char password[GSN_HTTPD_MAX_PASSWORD_LEN]; /**< Password for authentication */
    char *rootDir; /**< Root directory for static pages */
    char *defaultFileName; /**< Default page to be served */
    char *rootCgiDir; /**< Root directory for dynamic pages */
    UINT8 *stack; /**< Pointer to memory serving as stack */
    UINT16 stackSize; /**< Size of stack */
    INT32 mallocTimeout; /**< Timeout in ms after which we give up on malloc */
#if 0
	GSN_WDD_L2_DEV_T *pWdd; /* To be used for doing ssl activities in wdd task context*/
#endif

	void  *pool_hdl;

	UINT32 sysQualTskID;
	UINT32 sysQualTicks;
} GSN_HTTPD_CONFIG_T;

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Function that takes the configuration parameters and starts HTTPD
 *   This function starts HTTPD with the parameters specified. In case stack
 *   buffer is not passed, it will attempt to allocate a stack on its own.
 * @see GSN_HTTPD_CONFIG_T
 *****************************************************************************/
INT8 GsnHttpd_Start(GSN_HTTPD_CONFIG_T config
//#ifdef GSN_SSL_SERVER_SUPPORT
	,SERVER_CERT_DETAIL_T* pCred
//#endif
);


/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Function that stops the HTTPD server
 *****************************************************************************/
INT8 GsnHttpd_Stop();

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Function that checks whether the HTTPD server is running
 * @retval TRUE if running, FALSE otherwise
 *****************************************************************************/
UINT8 GsnHttpd_IsRunning();

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Function that checks whether the Authentication is enabled in HTTPD
 * @retval TRUE if enabled, FALSE otherwise
 *****************************************************************************/
UINT8 GsnHttpd_IsAuthEnabled();

/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Base URI for System API's
 *    Base URI for System API's
 *****************************************************************************/
#define GSN_HTTPD_API_SYS_BASE_URI "/gainspan/system"
/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Base URI for Profile API's
 *    Base URI for Profile API's
 *****************************************************************************/
#define GSN_HTTPD_API_PROFILE_BASE_URI "/gainspan/profile"

// TODO - This has since been replaced by GSN_HTTPD_BUF_SIZE. Should be removed
//#define  TM_BODY_BUFFER_LEN  1460
#define  TM_BODY_BUFFER_LEN GSN_HTTPD_BUF_SIZE

/**
 ******************************************************************************
 * @ingroup GsnHttpApis
 * @brief Definition of structure containing HTTPD configuration
 ******************************************************************************/
typedef struct GSN_SYS_CONFIG_HTTPD
{
    UINT8 username[GSN_HTTPD_MAX_USERNAME_LEN]; /**<  HTTPD username */
    UINT8 password[GSN_HTTPD_MAX_PASSWORD_LEN]; /**<  HTTPD password */
    UINT16 port; /**<  HTTPD Port (NOT USED) */
} GSN_SYS_CONFIG_HTTPD_T;

//#endif /* GSN_WEB_SERVER */


/**
 *****************************************************************************
 * @ingroup GsnHttpd
 * @brief Max HTTPD Response buffer size
 *    This macro defines the size of the buffer used for sending HTTP responses
 *****************************************************************************/
//#define GSN_HTTPD_BUF_SIZE (1*1024)
#define GSN_HTTPD_BUF_SIZE (3*512)

GSN_STATUS
GsnHttpd_AddRedirURI(UINT8 *redirUri);

#endif
