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
* $RCSfile: gsn_ssl.h,v $
*
* Description : This file contains SSL API.
*******************************************************************************/
#ifndef _GSN_SSL_H_
#define _GSN_SSL_H_

#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
* File Inclusion
********************************************************************************/
#include "gsn_types.h"
#include "gsn_defines.h"
#include "supplicant/tls/tlsv1_gainspan.h"

/**
 *******************************************************************************
 * @file gsn_ssl.h
 * @brief GSN SSL public header.
 *    This file contains the public APIs and structures of SSL module.
 ******************************************************************************/


/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/


/**
 *******************************************************************************
 * @defgroup GsnSsl GSN SSL API
 *
 ******************************************************************************/

/**
 *****************************************************************************
 *
 * @} 
 *****************************************************************************/



/*******************************************************************************
  * Private Macros and Functions
  ******************************************************************************/
#define GSN_TLSV1_CONN_T struct tlsv1_client
#define GSN_SSL_SERVER_PORT 443
#define GSN_SSL_CONN_ESTABLISHED 11
#define GSN_SSL_CONN_STATUS_FAIL 0
#define GSN_SSL_CONN_STATUS_SUCCESS 1
#define GSN_SSL_CONN_ALERT_FATAL 2
#define GSN_SSL_DEFAULT_FRAGMENT_SIZE 1398
#define GSN_SSL_TLS_HEADER_LENGTH 5
#define GSN_SSL_TLS_CONTENT_TYPE_APPLICATION_DATA 23
#define GSN_SSL_TLS_CONTENT_TYPE_ALERT 21
#define GSN_SSL_MAX_ALERT_SIZE 64
#define GSN_SSL_CLOSE_NOTIFICATION 0

#define GSN_SSL_ALERT_LEVEL_WARNING 1

#define GSN_SSL_ALERT_LEVEL_FATAL 2





/**
 *******************************************************************************
 * @ingroup GsnSSL
 * @brief SSL Connection mode enum.
 *
 ******************************************************************************/

typedef enum
{
    GSN_SSL_CONN_MODE_CLIENT,
    GSN_SSL_CONN_MODE_SERVER
}GSN_SSL_CONN_MODE;


/**
 *******************************************************************************
 * @ingroup GsnSSL
 * @brief SSL State enum.
 *
 ******************************************************************************/

typedef enum
{
    GSN_SSL_STATE_INIT,
    GSN_SSL_STATE_HEADER_RECEIVING,
    GSN_SSL_STATE_HEADER_RECEIVED,
    GSN_SSL_STATE_BODY_RECEIVING,
    GSN_SSL_STATE_BODY_RECEIVED,
    GSN_SSL_STATE_RECEIVE_DONE

}GSN_SSL_STATE;

/**
 *******************************************************************************
 * @ingroup GsnSSL
 * @brief SSL State enum.

 *

 ******************************************************************************/



typedef enum

{

    GSN_SSL_CONN_OPEN,

    GSN_SSL_CONN_CLOSING

}GSN_SSL_CONN_STATE;


/**
 *******************************************************************************
 * @ingroup GsnSSL
 * @brief SSL maximum Fragment length extension value.
 *
 ******************************************************************************/
typedef enum
{
    MAX_FRAG_SIZE_512B = 1,
    MAX_FRAG_SIZE_1KB,
    MAX_FRAG_SIZE_2KB,
    MAX_FRAG_SIZE_4KB
        
}MAX_FRAG_SIZE_T;
/**
 *******************************************************************************
 * @ingroup GsnSSL
 * @brief SSL Server context structure.
 *
 ******************************************************************************/
typedef struct GSN_SSL_SERVER_CONN_T
{
    UINT32 connMode;//Can be made UINT8
    struct tlsv1_server * conn;
    UINT8 *sslDataBuf;
    UINT16 expectedLen;
    UINT16 receivedLen;
    UINT16 sslState;
    UINT16 conState;
    UINT8 sslHdr[5];
    UINT8 *sslReassemDataBuf;
    UINT16 sslReassemDataBufSize;
    UINT16 sslReassemDataBufCurSize;
    struct tlsv1_client *tlsv1Conn_Renego;
    UINT8 maxFragLen;
    UINT8 enableRenego;
    UINT32 maxRecordSize;
}GSN_SSL_SERVER_CONN_T;

/**
 *******************************************************************************
 * @ingroup GsnSSL
 * @brief SSL Certificate detail structure for SSL Server.
 *
 ******************************************************************************/
typedef struct SERVER_CERT_DETAIL
{
	char const *CaCertName;
	unsigned char const *CaCertLocation;
	UINT32 CaCertLen;
	char const *ClientCertName;
	unsigned char const *ClientCertLocation;
	UINT32 ClientCertLen;    
	char const *PrivateKeyName;
	unsigned char const *PrivateKeyLocation;
	UINT32 PrivateKeyLen;
	char const *PrivateKeyPasswd;
	char const *dhFileName;
	char const *dhLocation;
	UINT8 dhLen;
}SERVER_CERT_DETAIL_T;
 

/**

 *******************************************************************************

 * @ingroup GsnSSL

 * @brief SSL context structure for client.
 *
 ******************************************************************************/
typedef struct GSN_SSL_CONN_T
{
    UINT32 connMode;//Can be made UINT8
    struct tlsv1_client *tlsv1Conn;
    UINT8 *sslDataBuf;
    UINT16 expectedLen;
    UINT16 receivedLen;
    UINT16 sslState;
    UINT16 conState;
    UINT8 sslHdr[5];
    UINT8 *sslReassemDataBuf;
    UINT16 sslReassemDataBufSize;
    UINT16 sslReassemDataBufCurSize;
    struct tlsv1_client *tlsv1Conn_Renego;
    UINT8 maxFragLen;
    UINT8 enableRenego;
    UINT32 maxRecordSize;
    GSN_SSL_DNS_BUF_INFO_T *dnsBufPtr;
}GSN_SSL_CONN_T;
/**
 *******************************************************************************
 * @ingroup GsnSSL
 * @brief SSL connection parmeters for client.
 *
 ******************************************************************************/
typedef struct GSN_SSL_CONN_PARAMS
{
    char const *caCertName; 
    unsigned char const *caCert; 
    UINT32 caCertLen;

    char const *clientCertName; 
    unsigned char const *clientCert; 
    UINT32 clientCertLen;
    
    char const *clientKeyName; 
    unsigned char const *clientKey; 
    UINT32 clientKeyLen;
    char const *clientKeyPassWd;
}GSN_SSL_CONN_PARAMS_T;
typedef struct GSN_SSL_RECV_PARAMS
{
	VOID *pSslConn;
	INT32 sockDes;
	UINT8 **rxDataBuf;
	UINT32 *rxDataLen;
	INT32 timeOut;
}GSN_SSL_RECV_PARAMS_T;
/*******************************************************************************
 * Public Functions
 ******************************************************************************/

/**
 *******************************************************************************
 * @ingroup GsnSsl
 * @brief SSL Server Init API.
 *
 *    This function Initializes the SSL Server
 *
 * @param pCert - IN Certificate detail to be used by SSL Server.
 *
 * @retval Valid pointer to the SSL server context, if the operation is 
 * successful else returns NULL. 
 *
 * @note: Once TCP socket is open this API can be called. The context returned 
 * by this API has to passed in GsnSsl_Accept to accept an SSL connection from
 * SSL client.
 ******************************************************************************/
PUBLIC VOID *
GsnSsl_ServerInit( SERVER_CERT_DETAIL_T *pCert);

/**
 *******************************************************************************
 * @ingroup GsnSsl
 * @brief SSL Server Accept API.
 *
 *    This function Accepts an SSL connection from SSL client
 *
 * @param pServerCtx - IN Pointer to the SSL Server context.
 *
 * @retval Valid pointer to the SSL server connection context. 
 *
 * @note: Once a TCP connection is established this API has to be called. The 
 * context returned by this API has to passed in GsnSsl_Encode, GsnSsl_Decode
 * APIs.
 ******************************************************************************/
PUBLIC GSN_SSL_SERVER_CONN_T *
GsnSsl_Accept( VOID *pServerCtx );
/**
 *******************************************************************************
 * @ingroup GsnSsl
 * @brief SSL Open connection API.
 *
 *    This function opens up the SSL session. User has to create a socket and
 *    pass the certificate details to open up the SSL connection.
 *
 * @param pSslConn - IN Context of SSL module.
 * @param sockDes - IN Socket descriptor on which the SSL connection has to be 
 *                      established.
 * @param sslConParams - IN Pointer to structure of type GSN_SSL_CONN_PARAMS_T
 *
 * @retval 1 if Operation successful, else -1.
 ******************************************************************************/
PUBLIC INT32
GsnSsl_Open( VOID *pSslConn, INT32 sockDes, GSN_SSL_CONN_PARAMS_T *sslConParams);

/**
 *******************************************************************************
 * @ingroup GsnSsl
 * @brief SSL Close connection API.
 *
 *    This function closes the SSL session
 *
 * @param sslConn - IN Context of SSL module.
 *
 * @retval 1 if Operation successful, else -1.
 ******************************************************************************/

PUBLIC VOID
GsnSsl_Close( VOID *sslConn);


/**
 *******************************************************************************
 * @ingroup GsnSsl
 * @brief SSL Close Alert API.
 *
 *    This function send the SSL Alert
 *
 * @param pSSLConn - IN Context of SSL module.
 * @param sockDesc - IN The Socket Descriptor
 *
 * @retval 1 if Operation successful, else -1.
 ******************************************************************************/

PUBLIC INT32
GsnSsl_Alert( VOID *pSSLConn, INT32 sockDesc);


/**
 *******************************************************************************
 * @ingroup GsnSsl
 * @brief SSL encode API.
 *
 *    This function encodes the data. User has to pass the input data pointer 
 *    which needs to be encoded. This function does a memory allocation to
 *    store the encoded data and passes the pointer in pOutDataBuf. User has
 *    free to this memory once the encoded data is utilized.
 *
 * @param pSSLConn - IN Context of SSL module.
 * @param pInDataBuf - IN Pointer to the input data which needs to be encoded.
 * @param inDataLen - IN Length of the input data.
 * @param pOutDataBuf - OUT pointer to store the encoded data buffer location.
 * @param pOutDataLen - OUT Length of the encoded data buffer.
 *
 * @retval 1 if Operation successful, else -1. Operation may fail if the memory
 *      allocation fails, or the encoding fails.
 * @note
 *    User has to free up the memory pointed by the pointer pOutDataBuf after
 *    using it.User should call GsnSsl_Free to free up the memory, insted of
 *    gsn_free.
 ******************************************************************************/

PUBLIC INT32
GsnSsl_Encode( VOID *pSSLConn, UINT8* pInDataBuf, UINT32 inDataLen,
    UINT8** pOutDataBuf, UINT32 *pOutDataLen);



/**
 *******************************************************************************
 * @ingroup GsnSsl
 * @brief SSL Decode API.
 *
 *    This function decodes the data. User has to pass the input data pointer 
 *    which needs to be decoded. This function does a memory allocation to
 *    store the decoded data and passes the pointer in pOutDataBuf. User has
 *    free to this memory once the decoded data is utilized.
 *
 * @param pSSLConn - IN Context of SSL module.
 * @param pInDataBuf - IN Pointer to the input data which needs to be decoded.
 * @param inDataLen - IN Length of the input data.
 * @param pOutDataBuf - OUT pointer to store the decoded data buffer location.
 * @param pOutDataLen - OUT Length of the decoded data buffer.
 * @param sockDesc - IN The Socket Descriptor
 *
 * @retval 1 if Operation successful, else -1. Operation may fail if the memory
 *      allocation fails, or the decoding fails.
 * @note
 *    User has to free up the memory pointed by the pointer pOutDataBuf after
 *    using it. User should call GsnSsl_Free to free up the memory, insted of
 *    gsn_free.
 ******************************************************************************/

PUBLIC INT32
GsnSsl_Decode( VOID *pSSLConn, UINT8* pInDataBuf, UINT32 inDataLen,
    UINT8** pOutDataBuf, UINT32 *pOutDataLen, INT32 sockDesc);


/**
 *******************************************************************************
 * @ingroup GsnSsl
 * @brief SSL Receive API.
 *
 *    This function Receives the data on the given socket. Since SSL works on 
 *    TCP, and SSL encryption/decryption is block by nature, the SSL decoing can 
 *    only be called after recepit of a complete SSL packet. This API receives
 *    the complete SSL frame and decodes and gives the frame to user.
 *
 * @param pSSLConn - IN Context of SSL module.
 * @param sockDes - IN Socket descriptor on which SSL frame will be received. 
 * @param pRxDataBuf - OUT pointer to store the received data.
 * @param pRxDataLen - OUT Length of the received data.
 * @param timeOut - IN time in sec after which the receive process will be 
 *    abandoned if it doesn't receive any packet on the given socket.
 *
 * @retval GSN_SUCCESS if Operation successful, else GSN_FAILURE.
 *
 * @note
 *    User has to free up the memory pointed by the pointer pRxDataBuf after
 *    using it.
 ******************************************************************************/
PUBLIC
GSN_STATUS GsnSsl_DataReceive( VOID* pSSLConn, INT32 sockDes,
    UINT8 **pRxDataBuf, UINT32 *pRxDataLen, INT32 timeOut );

/**
 *******************************************************************************
 * @ingroup GsnSsl
 * @brief SSL Receive API.
 *
 *    This function sends ssl alerts messages on the given socket. This particular
 *    function can be used by both Client and server, as the pSslConn structures
 *    are similar in a way that the elements needed by this function has same
 *    position.
 *
 * @param pSSLConn - IN Context of SSL module.
 * @param Alert - IN Alert message type.
 * @param Description - IN Alert message description.
 * @param sockDesc - IN Socket descriptor on which SSL alert to be sent.
 *
 * @retval None
 *
 * @note
 *    User has to free up the memory pointed by the pointer pRxDataBuf after
 *    using it.
 ******************************************************************************/
PUBLIC VOID GsnSsl_AlertSend( VOID *pSSLConn, UINT8 Alert,
    UINT8 Description, INT32 sockDesc);

/**
 *******************************************************************************
 * @ingroup GsnSsl
 * @brief SSL Memory allocation API.
 *
 *    This function Allocates memory from the SSL Memory pool
 *
 * @param size - IN Size of the memory to alocate.
 *
 * @retval Address of the allocated buffer if allocation is successful else 
 * NULL.
 *
 * @note: Memory allocated using this API has to be freeded by calling
 * GsnSsl_Free. In case of SSL server to send the SSL packet out the SSL server
 * code uses this API to allocate memory. But incase of SSL client it uses the
 * gsn_malloc.
 ******************************************************************************/
PUBLIC UINT8* 
GsnSsl_Alloc(UINT32 size );

/**
 *******************************************************************************
 * @ingroup GsnSsl
 * @brief SSL Memory Free API.
 *
 *    This function Free memory to the SSL Memory pool
 *
 * @param ptr - IN Memory buffer to be freed.
 *
 * @retval returns -1 if the buffer doesn't belong to SSL memory pool.
 *
 * @note: Memory allocated using SSL alloc API has to be freeded by calling
 * GsnSsl_Free.
 ******************************************************************************/
PUBLIC INT32
GsnSsl_Free(UINT8* ptr );

/**
 *******************************************************************************
 * @ingroup GsnSsl
 * @brief SSL http receive and decode API.
 *
 *    This function recieves and decodes https ssl encoded data and returns
 *    decoded http data.
 *
 * @param sslConn - IN Context of SSL module.
 * @param sockDes - IN Socket descriptor on which SSL alert to be sent.
 * @param rxDataBuf - OUT Pointer containing decoded http data.
 * @param rxDataLen - OUT length of the decoded http data.
 * @param timeOut - IN Socket recieve timeout.
 *
 * @retval GSN_SUCCESS if Operation successful, else GSN_FAILURE.
 *
 ******************************************************************************/
INT32 GsnHttps_DataReceive(GSN_SSL_CONN_T*sslConn,
                         INT32 sockDes,
                         UINT8 **rxDataBuf,
                         UINT32 *rxDataLen,
                         INT32 timeOut);

/**
 *******************************************************************************
 * @ingroup GsnSsl
 * @brief SSL Server Deinit API.
 *
 *    This function Deinitializes the SSL Server
 *
 * @param cred - IN Tls handle to be used by SSL Server.
 *
 * @retval None.
 *
 ******************************************************************************/
VOID
GsnSsl_ServerDeInit( VOID *cred);                         

/**
 *******************************************************************************
 * @ingroup GsnSsl
 * @brief SSL receive API.
 *
 *    This function recieves and decodes ssl encoded data and returns
 *    decoded data.
 *
 * @param pSslConn - IN Context of SSL module.
 * @param sockDes - IN Socket descriptor on which SSL alert to be sent.
 * @param rxDataBuf - OUT Pointer containing decoded data.
 * @param rxDataLen - OUT length of the decoded data.
 * @param timeOut - IN Socket recieve timeout.
 *
 * @retval GSN_SUCCESS if Operation successful, else GSN_FAILURE.
 *
 ******************************************************************************/
GSN_STATUS GsnSsl_Receive(VOID* pSslConn,
                              INT32 sockDes,
                              UINT8 **rxDataBuf,
                              UINT32 *rxDataLen,
                              INT32 timeOut);

int GsnSsl_DecryptAlert(struct tlsv1_client *conn,

             UINT8 *in_data, size_t in_len,

             UINT8 *out_data, size_t out_len);

#ifdef __cplusplus
}
#endif
#endif /* _GSN_SSL_H_ */




