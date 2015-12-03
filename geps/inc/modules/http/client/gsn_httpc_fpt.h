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
 * $RCSfile: gsn_httpc_fpt.h,v $
 *
 * Description:
 *      This file contains public functions declarations for gsn http client
 *      function pointers
 *
 ******************************************************************************
 */

/**
******************************************************************************
*  @file gsn_httpc_fpt.h
*  @brief Public Header Containing gsn http client function pointers
*
*****************************************************************************/


#ifndef _GSN_HTTPC_FPT_H_
#define _GSN_HTTPC_FPT_H_

#ifdef  __cplusplus
extern "C" {
#endif


/*
 *****************************************************************************************
 * Includes on which the header file depends.
 *****************************************************************************************
 */


#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
#include "modules/ssl/gsn_ssl.h"
#include "modules/http/gsn_httpc.h"

typedef GSN_STATUS
( *GsnHttp_Start_FP_T)(GSN_HTTPC_CONN_HANDLE *pHttpConnHandle, struct sockaddr_storage *pSockAddr,
			  GSN_HTTPC_CONN_PARAMS_T *pHttpcConnParams,
              GSN_HTTPC_CONF_INFO_T * pHttpConfInfo);              
typedef GSN_STATUS
(* GsnHttp_Send_FP_T)(GSN_HTTPC_CONN_HANDLE conHandle, INT8 *respBuff,
			   UINT32 *respBuffLen, INT32 timeOut,	
			   GSN_HTTPC_CONF_INFO_T * pHttpConfInfo);

typedef GSN_STATUS
(* GsnHttp_Alert_FP_T)(GSN_HTTPC_CONN_HANDLE conHandle);			 

typedef GSN_STATUS
(* GsnHttp_Close_FP_T)(GSN_HTTPC_CONN_HANDLE conHandle);

typedef UINT8
(* GsnHttp_IsHeaderPresent_FP_T)(GSN_HTTPC_CONF_INFO_T *pHttpConfInfo,
                        GSN_HTTP_USER_HEADER_TYPE_T headerType);

extern _RPST_ GsnHttp_Start_FP_T GsnHttp_Start_FP;
extern _RPST_ GsnHttp_Send_FP_T GsnHttp_Send_FP;
extern _RPST_ GsnHttp_Alert_FP_T GsnHttp_Alert_FP;
extern _RPST_ GsnHttp_Close_FP_T GsnHttp_Close_FP;
extern _RPST_ GsnHttp_IsHeaderPresent_FP_T GsnHttp_IsHeaderPresent_FP;

#endif /*_GSN_HTTPC_FPT_H_*/
