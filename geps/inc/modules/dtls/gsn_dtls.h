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
* $RCSfile: gsn_dtls.h,v $
*
* Description : This file contains public definitions for DTLS. 
*******************************************************************************/
#ifndef _GSN_DTLS_H_
#define _GSN_DTLS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
* File Inclusion
*****************************************************************************/
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_includes.h"
#include "modules/ssl/gsn_ssl.h"
/**
 *******************************************************************************
 * @file gsn_dtls.h
 * @brief GSN DTLS public API implementation.
 *    This file contains the public APIs and structures of DTLS module.
 ******************************************************************************/


#define GSN_SSL_STATE_INIT 0
#define GSN_SSL_CONN_CLOSING 1
/**
 *******************************************************************************
 * 
 ******************************************************************************/
 /**
 *****************************************************************************
 * @ingroup GsnDtls
 * @brief GSN DTLS Structure to define socket information.
 *    Structure definition for socket information.
 *****************************************************************************/
typedef struct SOCKET_INFO
{
    int sd; /* Socket return value */
    int dstAddrLen; /* Length of the destionation Address */
    char *dstAddr; /* Pointer to the destination address */
}SOCKET_INFO_T;

#define GSN_DTLS_HANDSHAKE_DONE 1
/**
 *****************************************************************************
 * @ingroup GsnDtls
 * @brief GSN DTLS cb.
 *    Callback function type.
 *****************************************************************************/
typedef VOID (*GSN_DTLS_CB_T)( VOID * pCtx, UINT8 event );

/**
 *****************************************************************************
 * @ingroup GsnDtls
 * @brief GSN DTLS Connection Structure.
 *    Structure definition of DTLS context.
 *****************************************************************************/
typedef struct GSN_DTLS_CONN
{
    UINT8 dtlsState, conState;
    SOCKET_INFO_T sock;
    UINT16 rTime;
    UINT8 rANum;
    UINT8 rCNum;
    GSN_SOFT_TMR_T rTmr;
    UINT8 *pRData;
    GSN_DTLS_CB_T cb;
    VOID *pCtx;
    VOID *dtlsConn;
}GSN_DTLS_CONN_T;



typedef struct GSN_DTLS_CONFIG_PARAM
{
    GSN_SSL_CONN_PARAMS_T certDetails;
    UINT16 rTime;
    UINT8  rCount;
    VOID *pCbCtx;
    GSN_DTLS_CB_T cb;
}GSN_DTLS_CONFIG_PARAM_T;


/*******************************************************************************
 * Private Functions prototype
 ******************************************************************************/

/*******************************************************************************
 * Public Functions
 ******************************************************************************/

/**
 *******************************************************************************
 * @ingroup GsnDtls
 * @brief DTLS Open connection API.
 *
 *    This function opens up the DTLS session. User has to create a socket and
 *    pass the certificate details to open up the DTSL connection.
 *
 * @param pDtlsConn - IN Context of DTSL module.
 * @param pSockDes - IN Socket descriptor on which the DTLS connection has to be
 *                      established.
 * @param dtlsConParams - IN Pointer to structure of type GSN_SSL_CONN_PARAMS_T
 *
 * @retval GSN_SUCCESS if Operation successful, else GSN_FAILURE.
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnDtls_Open( GSN_DTLS_CONN_T *pDtlsConn, SOCKET_INFO_T *pSockDes, 
    GSN_SSL_CONN_PARAMS_T *dtlsConParams );


/**
 *******************************************************************************
 * @ingroup GsnDtls
 * @brief DTLS Close connection API.
 *
 *    This function closes the SSL session
 *
 * @param dtlsConn - IN Context of DTLS module.
 *
 * @retval GSN_SUCCESS if Operation successful, else GSN_FAILURE.

 ******************************************************************************/
PUBLIC GSN_STATUS
GsnDtls_Close( GSN_DTLS_CONN_T *dtlsConn );

/**
 *******************************************************************************
 * @ingroup GsnDtls
 * @brief DTLS Receive API.
 *
 *    This function Processes the data received from the socket descriptor 
 *    given in GsnDtls_Open API. If received data contains user data, it 
 *    updates the pInDataLen.
 *
 * @param dtlsConn - IN Context of DTLS module.
 * @param pInData - IN Pointer to input data.
 * @param pInDataLen - IN/OUT Pointer containing the input data length. This 
 *    pointer is updated to the length of the user data receieved else to 0.
 * @param recvFlag - IN flag to use for socket receive API call. 
 * @param pRecvAddr - OUT Pointer to store the address of the Source device. 
 * @param pAddrLen - IN/OUT Size of the recvAddr.  
 *
 * @retval GSN_SUCCESS if Operation successful, else GSN_FAILURE.
 *
 ******************************************************************************/
PUBLIC GSN_STATUS 
GsnDtls_Receive( GSN_DTLS_CONN_T *dtlsConn, UINT8* pInData, 
    UINT32 *pInDataLen, int recvFlag, VOID *pRecvAddr, int *pAddrLen );

/**
 *******************************************************************************
 * @ingroup GsnDtls
 * @brief DTLS Send API.
 *
 *    This function Send the user data.
 *
 * @param dtlsConn - IN Context of DTLS module.
 * @param pInData - IN Pointer to input data.
 * @param inLen - IN input data length. 
 * @param sendFlag - IN flag to use for socket send API call. 
 *
 * @retval GSN_SUCCESS if Operation successful, else GSN_FAILURE.
 *
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnDtls_Send( GSN_DTLS_CONN_T *dtlsConn,
    UINT8 *pInData, size_t inLen, int sendFlag  );


/**
 *******************************************************************************
 *
 *******************************************************************************/
/*******************************************************************************
 * Private Functions
 ******************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* _GSN_DTLS_H_ */ 
/**
 *******************************************************************************
 * \internal
 * @ingroup GsnSdd
 * @brief Send Confirmation, not for application use.
 * 
 ******************************************************************************/
 






