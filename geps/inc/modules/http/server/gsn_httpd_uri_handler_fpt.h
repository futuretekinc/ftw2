/******************************************************************************
 *
 *               COPYRIGHT (c) 2012-2013 GainSpan Corporation
 *                         All Rights Reserved
 *
 * The source code contained or described herein and all documents
 * related to the source code ("Material") are owned by Gainspan
 * Corporation or its licensors.  Title to the Material remains
 * with Gainspan Corporation or its suppliers and licensors.
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
 * Unless otherwise agreed by Gainspan in writing, you may not remove or
 * alter this notice or any other notice embedded in Materials by Gainspan
 * or Gainspan's suppliers or licensors in any way.
 *
 * $RCSfile: gsn_httpd_uri_handler_fpt.h,v $
 *
 * Description:
 *      This file contains public functions declarations for gsn http server
 *      uri handler function pointers
 *
 ******************************************************************************
 */

/**
******************************************************************************
*  @file gsn_httpd_uri_handler_fpt.h
*  @brief Public Header Containing gsn http server uri handler function pointers
*
*****************************************************************************/



#ifndef GSN_HTTPD_URI_HANDLER_FPT_H_
#define GSN_HTTPD_URI_HANDLER_FPT_H_

#ifdef  __cplusplus
extern "C" {
#endif


/*
 *****************************************************************************************
 * Includes on which the header file depends.
 *****************************************************************************************
 */


#include "modules/http/gsn_httpd.h"

typedef int (*GsnHttpd_UriHdlrGetIndex_FP_T) (char* uri);

typedef GSN_HTTPD_URI_HANDLER_T* (*GsnHttpd_UriHandlerGet_FP_T) ();

typedef VOID (*GsnHttpd_UriEventHdlr_FP_T) (ttHttpdUserConHandle conHandle, ttHttpdUserEvent event);

typedef VOID (*GsnHttpd_UriContentType_FP_T) (const INT8 * pathPtr, INT8 *pContentType,
        INT32 flag);

typedef int (*GsnHttpd_UriIdCbFn_FP_T) (ttUserConstCharPtr uri);

typedef GSN_HTTPD_STATUS_T (*GsnHttpd_UriHandlerInit_FP_T) (ttHttpdUserSrvHandle serverHandle);

typedef VOID (*GsnHttpd_UriHandlerDeInit_FP_T) (ttHttpdUserSrvHandle serverHandle);

typedef GSN_HTTPD_STATUS_T (*GsnHttpd_UriHandlerConfig_FP_T) (char *uri, UINT8 methods,
        char* desc, GSN_HTTPD_URI_HANDLER_FN_T fn_cb, UINT8 contentType);

typedef VOID (*Gsnhttpd_UriHandlerPrint_FP_T) ();

extern _RPST_  GsnHttpd_UriHdlrGetIndex_FP_T GsnHttpd_UriHdlrGetIndex_FP;

extern _RPST_  GsnHttpd_UriHandlerGet_FP_T GsnHttpd_UriHandlerGet_FP;

extern _RPST_ GsnHttpd_UriEventHdlr_FP_T GsnHttpd_UriEventHdlr_FP;

extern _RPST_ GsnHttpd_UriContentType_FP_T GsnHttpd_UriContentType_FP;

extern _RPST_ GsnHttpd_UriIdCbFn_FP_T GsnHttpd_UriIdCbFn_FP;

extern _RPST_ GsnHttpd_UriHandlerInit_FP_T GsnHttpd_UriHandlerInit_FP;

extern _RPST_ GsnHttpd_UriHandlerDeInit_FP_T GsnHttpd_UriHandlerDeInit_FP;

extern _RPST_ GsnHttpd_UriHandlerConfig_FP_T GsnHttpd_UriHandlerConfig_FP;

extern _RPST_ Gsnhttpd_UriHandlerPrint_FP_T Gsnhttpd_UriHandlerPrint_FP;

#endif /* GSN_HTTPD_URI_HANDLER_FPT_H_ */
