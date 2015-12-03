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
 * $RCSfile: gsn_httpd_wrap_fpt.h,v $
 *
 * Description:
 *      This file contains public functions declarations for gsn http server
 *      wrapper function pointers
 *
 ******************************************************************************
 */

/**
******************************************************************************
*  @file gsn_httpd_wrap_fpt.h
*  @brief Public Header Containing gsn http server wrapper function pointers
*
*****************************************************************************/



#ifndef GSN_HTTPD_WRAP_FPT_H_
#define GSN_HTTPD_WRAP_FPT_H_


#ifdef  __cplusplus
extern "C" {
#endif


/*
 *****************************************************************************************
 * Includes on which the header file depends.
 *****************************************************************************************
 */



#include "modules/ssl/gsn_ssl.h"

typedef VOID (*GsnHttpd_EventHdlr_FP_T) (ttHttpdUserConHandle conHandle,
        ttHttpdUserEvent event);

typedef void (*Httpd_SockInit_FP_T) (UINT32 ipAddr, int port,
        struct sockaddr_storage* p_sock_addr);

typedef void (*Httpd_SetSockOptions_FP_T) (ttHttpdUserSrvHandle serverHandle);

typedef void (*Httpd_Server_FP_T) (UINT32 ctx);

typedef UINT16 (*GsnHttpd_StackAlloc_FP_T) ();

typedef VOID (*GsnHttpd_StackDeAlloc_FP_T) ();

//#ifdef GSN_SSL_SERVER_SUPPORT
typedef VOID (*GsnHttpd_ExecInWddTskCb_FP_T) (INT32 cbStatus, VOID *ctx, VOID * msg);

typedef VOID (*GsnHttpd_SslReceive_FP_T) (VOID* pSslConn,
    							  INT32 sockDes,
    							  UINT8 **rxDataBuf,
    							  UINT32 *rxDataLen,
    							  INT32 timeOut);

//#endif

typedef INT8 (*GsnHttpd_Start_FP_T) (GSN_HTTPD_CONFIG_T httpdConfig
//#ifdef GSN_SSL_SERVER_SUPPORT
	,SERVER_CERT_DETAIL_T* pCred
//#endif
	);

typedef UINT8 (*GsnHttpd_IsRunning_FP_T) ();

typedef INT8 (*GsnHttpd_Stop_FP_T) ();

typedef GSN_STATUS (*GsnHttpd_AddRedirURI_FP_T) (UINT8 *redirUri);

typedef BOOL (*GsnHttpd_IsAuthEnabled_FP_T) ();

typedef GSN_STATUS_T
(*GsnHttpd_CustomRespStatusLine_FP_T)(ttHttpdUserConHandle conHandle,
							  UINT8                *reasonPhrasePtr,
							  UINT32               reasonPhraseLen);

typedef GSN_STATUS_T
(*GsnHttpd_CustomHdrs_FP_T)(ttHttpdUserConHandle conHandle,
		UINT32                uconCustomHdrcount,
		UINT8               **uconCustomHeaderstype,
		UINT8				**uconCustomHeadersval);

extern _RPST_ GsnHttpd_EventHdlr_FP_T GsnHttpd_EventHdlr_FP;

extern _RPST_ Httpd_SockInit_FP_T Httpd_SockInit_FP;

extern _RPST_ Httpd_SetSockOptions_FP_T Httpd_SetSockOptions_FP;

extern _RPST_ Httpd_Server_FP_T Httpd_Server_FP;

extern _RPST_ GsnHttpd_StackAlloc_FP_T GsnHttpd_StackAlloc_FP;

extern _RPST_ GsnHttpd_StackDeAlloc_FP_T GsnHttpd_StackDeAlloc_FP;

//#ifdef GSN_SSL_SERVER_SUPPORT

extern _RPST_ GsnHttpd_ExecInWddTskCb_FP_T GsnHttpd_ExecInWddTskCb_FP;

extern _RPST_ GsnHttpd_SslReceive_FP_T GsnHttpd_SslReceive_FP;
//#endif

extern _RPST_ GsnHttpd_Start_FP_T GsnHttpd_Start_FP;

extern _RPST_ GsnHttpd_IsRunning_FP_T GsnHttpd_IsRunning_FP;

extern _RPST_ GsnHttpd_Stop_FP_T GsnHttpd_Stop_FP;

extern _RPST_ GsnHttpd_AddRedirURI_FP_T GsnHttpd_AddRedirURI_FP;

extern _RPST_ GsnHttpd_IsAuthEnabled_FP_T GsnHttpd_IsAuthEnabled_FP;

extern _RPST_ GsnHttpd_CustomRespStatusLine_FP_T GsnHttpd_CustomRespStatusLine_FP;

extern _RPST_ GsnHttpd_CustomHdrs_FP_T GsnHttpd_CustomHdrs_FP;

#endif /* GSN_HTTPD_WRAP_FPT_H_ */
