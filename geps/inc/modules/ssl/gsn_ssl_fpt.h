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
* $RCSfile: gsn_ssl_fpt.h,v $
*
* Description : This file contains Gsn SSL APIs.
*******************************************************************************/

#ifndef _GSN_SSL_FPT_
#define _GSN_SSL_FPT_

/*******************************************************************************
 * File Inclusion
 ******************************************************************************/


/*******************************************************************************
 * Public Functions
 ******************************************************************************/
typedef
GSN_STATUS (*GSNSSL_DATARECEIVE_FP_T)(VOID *pSslConn,
                              INT32 sockDes,
                              UINT8 **rxDataBuf,
                              UINT32 *rxDataLen,
                              INT32 timeOut);

extern _RPST_ GSNSSL_DATARECEIVE_FP_T GsnSsl_DataReceive_FP;

typedef int (*GSNSSL_DECRYPTALERT_FP_T)(struct tlsv1_client *conn,
             UINT8 *in_data, size_t in_len,
             UINT8 *out_data, size_t out_len);
extern _RPST_ GSNSSL_DECRYPTALERT_FP_T GsnSsl_DecryptAlert_FP;

typedef void (*GSNSSL_ALERTSEND_FP_T)( VOID *pSslConn, UINT8 Alert,
    UINT8 Description, INT32 sockDesc);
extern _RPST_ GSNSSL_ALERTSEND_FP_T GsnSsl_AlertSend_FP;

typedef INT32
(*GSNSSL_OPEN_FP_T)( VOID *pSslConn, INT32 sockDes,
            GSN_SSL_CONN_PARAMS_T *sslConParams);
extern _RPST_ GSNSSL_OPEN_FP_T GsnSsl_Open_FP;

typedef INT32
(*GSNSSL_ALERT_FP_T)( VOID *pSslConn, INT32 sockDesc);
extern _RPST_ GSNSSL_ALERT_FP_T GsnSsl_Alert_FP;

typedef void
(*GSNSSL_CLOSE_FP_T)(VOID *pSslConn);
extern _RPST_ GSNSSL_CLOSE_FP_T GsnSsl_Close_FP;

typedef INT32
(*GSNSSL_ENCODE_FP_T)(VOID *pSslConn,
              UINT8* inDataBuf,
              UINT32 inDataLen,
              UINT8**outDataBuf,
              UINT32 *outDataLen);
extern _RPST_ GSNSSL_ENCODE_FP_T GsnSsl_Encode_FP;

typedef INT32
(*GSNSSL_DECODE_FP_T)(VOID *pSslConn, UINT8* inDataBuf,
              UINT32 inDataLen, UINT8**outDataBuf,
              UINT32 *outDataLen, INT32 sockDes);
extern _RPST_ GSNSSL_DECODE_FP_T GsnSsl_Decode_FP;

typedef int(*GSNHTTPS_DATARECEIVE_FP_T)(GSN_SSL_CONN_T*sslConn,
                         INT32 sockDes,
                         UINT8 **rxDataBuf,
                         UINT32 *rxDataLen,
                         INT32 timeOut);
extern _RPST_ GSNHTTPS_DATARECEIVE_FP_T GsnHttps_DataReceive_FP;

typedef GSN_SSL_SERVER_CONN_T *
(*GSNSSL_ACCEPT_FP_T)( void *pServerCtx );
extern _RPST_ GSNSSL_ACCEPT_FP_T GsnSsl_Accept_FP;


typedef void *
(*GSNSSL_SERVERINIT_FP_T)( SERVER_CERT_DETAIL_T *pCert);
extern _RPST_ GSNSSL_SERVERINIT_FP_T GsnSsl_ServerInit_FP;

typedef void
(*GSNSSL_SERVERDEINIT_FP_T)( struct tlsv1_credentials *cred);
extern _RPST_ GSNSSL_SERVERDEINIT_FP_T GsnSsl_ServerDeInit_FP;

typedef GSN_STATUS
(*GSNSSL_SERVERCONNECTPROCESS_FP_T)( GSN_SSL_SERVER_CONN_T *sslConn, INT32 sd );
extern _RPST_ GSNSSL_SERVERCONNECTPROCESS_FP_T GsnSsl_ServerConnectProcess_FP;

typedef GSN_STATUS
(*GSNSSL_RECORDRECEIVE_FP_T)(VOID * pSslConn,
                              INT32 sockDes,
                              INT32 timeOut);
extern _RPST_ GSNSSL_RECORDRECEIVE_FP_T GsnSsl_RecordReceive_FP;

typedef GSN_STATUS (*GSNSSL_RECEIVE_FP_T)(VOID* pSslConn,
                              INT32 sockDes,
                              UINT8 **rxDataBuf,
                              UINT32 *rxDataLen,
                              INT32 timeOut);
extern _RPST_ GSNSSL_RECEIVE_FP_T GsnSsl_Receive_FP;

typedef GSN_STATUS
(*GSNSSL_INIT_FP_T)( VOID );
extern _RPST_ GSNSSL_INIT_FP_T GsnSsl_Init_FP;

typedef UINT8*
(*GSNSSL_ALLOC_FP_T)(UINT32 size );
extern _RPST_ GSNSSL_ALLOC_FP_T GsnSsl_Alloc_FP;

typedef INT32
(*GSNSSL_FREE_FP_T)(UINT8* ptr );
extern _RPST_ GSNSSL_FREE_FP_T GsnSsl_Free_FP;

#endif /* _GSN_SSL_FPT_ */