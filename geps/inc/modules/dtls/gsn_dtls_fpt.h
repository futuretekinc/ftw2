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
* $RCSfile: gsn_dtls_fpt.h,v $
*
* Description : This file contains public definitions for DTLS. 
*******************************************************************************/
#ifndef _GSN_DTLS_FPT_H_
#define _GSN_DTLS_FPT_H_
#ifdef __cplusplus
extern "C" {
#endif



 
typedef GSN_STATUS ( *GSNDTLS_OPEN_FP_T)( GSN_DTLS_CONN_T *pDtlsConn, 
	SOCKET_INFO_T *pSockDes, GSN_SSL_CONN_PARAMS_T *sslConParams );


typedef GSN_STATUS
( *GSNDTLS_CLOSE_FP_T)( GSN_DTLS_CONN_T *conn );

typedef GSN_STATUS 
( *GSNDTLS_RECEIVE_FP_T)( GSN_DTLS_CONN_T *dtlsConn, UINT8* pInData, 
    UINT32 *pInDataLen, int recvFlag, VOID *pRecvAddr, int *pAddrLen );

typedef GSN_STATUS
( *GSNDTLS_SEND_FP_T)( GSN_DTLS_CONN_T *dtlsConn,
    u8 *pInData, size_t inLen, int sendFlag );

extern _RPST_ GSNDTLS_OPEN_FP_T GsnDtls_Open_FP;


extern _RPST_ GSNDTLS_CLOSE_FP_T GsnDtls_Close_FP;

extern _RPST_ GSNDTLS_RECEIVE_FP_T GsnDtls_Receive_FP;

extern _RPST_ GSNDTLS_SEND_FP_T GsnDtls_Send_FP;
#ifdef __cplusplus
}
#endif        
#endif /* _GSN_DTLS_FPT_H_ */






