/*******************************************************************************
*
*               COPYRIGHT (c) 2013-2014 GainSpan Corporation
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
* $RCSfile: gsn_coap.h,v
*/

/*
 * gsn-coap.h
 *
 *  Created on: May 07, 2013
 *      Author: DLakshmi
 */

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#ifndef GSN_COAP_H_
#define GSN_COAP_H_

#include "modules/coap/libcoap-4.0.1/net.h"
#include "modules/coap/gsn_pdu_impl.h"
#include "gsn_includes.h"
#include "modules/coap/gsn_coap_impl.h"

/**
 *******************************************************************************
 * @ingroup GsnCoap
 * @brief Coap request parameters.
 *
 *  This structure defines some of the parameters used for sending the Coap
 *  request to the server. This structure needs to be filled and passed to GsnCoap_Send_And_Recieve()
 ******************************************************************************/
typedef struct GSN_COAP_CONN_PARAMS
{
    unsigned char * uri; /*Coap uri to which data is sent to "coap://host:/port/path.*/
    unsigned int uriLength;
    char * payload; /*payload to be sent in the coap request*/
    unsigned char* payloadType; /*payload type*/
    unsigned int payloadSize; /* size of the payload */
    enum coap_conn_method method; /* coap connection method - GET/POST */
    enum coap_conn_type type; /* coap connection type */
    unsigned int responseTimeout; /* time after which reading response times out */
    char * responseBuffer; /* response buffer which is filled in after read */
    unsigned int responseBufLen; /* response buffer length */
} GSN_COAP_CONN_PARAMS_T;

/*******************************************************************************
 * Public Functions
 ******************************************************************************/

/**
 *******************************************************************************
 * @ingroup GsnCoap
 * @brief GSN Coap Init
 *
 * This function initilises the COAP context.Further this context can be used
 * to read or write CoAP messages to a specified destination. This call supports both Confirmable
 * and Non Confirmable connections
 * @param ctx - IN Pointer to coap context if already created.
 *
 * @retval GSN_COAP_CONTEXT_T pointer to coap context on creation
 ******************************************************************************/
GSN_COAP_CONTEXT_T* GsnCoap_Init(GSN_COAP_CONTEXT_T *ctx);


/**
 *******************************************************************************
 * @ingroup GsnCoap
 * @brief GSN Coap Send and receive
 *
 * This function creates a pdu, initialises with the coap options, payload etc the COAP context.
 * Sends the pdu to the final destination, and recieves the response
 * @param pCoapContext - IN Pointer to coap context already created.
 * @param pCoapConnParams - IN Pointer with the coap request parameters.
 *
 * @retval number of bytes received in the coap response
 * @retval -1 , if error in read
 ******************************************************************************/
int GsnCoap_Send_And_Recieve(GSN_COAP_CONTEXT_T* pCoapContext, GSN_COAP_CONN_PARAMS_T * pCoapConnParams);

/**
 *******************************************************************************
 * @ingroup GsnCoap
 * @brief GSN Coap DeInit
 *
 * This function de-initialises the COAP context.
 * It frees the coap context, deletes the pdu
 * @param pCoapContext - IN Pointer to coap context already created.
 *
 * @retval none
 ******************************************************************************/
void GsnCoap_DeInit(GSN_COAP_CONTEXT_T *pCoapContext);

/**
 *******************************************************************************
 * @ingroup GsnCoap
 * @brief GSN Coap SetOptions
 *
 * This functions sets the option key with the option value 
 * These options are sent with the pdu when GsnCoap_Send_And_Recieve is called
 *
 * @param pOptionKey - IN key to the options header.
 * @param pOptionValue - IN option header value.
 * @param pOptionLength = IN option length
 *
 * @retval GSN_SUCCESS on successful adding of the coap header
 ******************************************************************************/
GSN_STATUS GsnCoap_SetOption( unsigned short pOptionKey,unsigned char* pOptionValue,
                             unsigned int pOptionLength);

/**
 *******************************************************************************
 * @ingroup GsnCoap
 * @brief GSN Coap DeleteOptions
 *
 * This functions deletes the option key
 *
 * @param pOptionKey - IN key to the options header.
 *
 * @retval GSN_SUCCESS on successful adding of the coap header
 ******************************************************************************/
GSN_STATUS GsnCoap_DeleteOption(unsigned short pOptionKey);

/**
 *******************************************************************************
 * @ingroup GsnCoap
 * @brief GSN Coap SetToken
 *
 * This functions sets the token header with token value
 * The token are sent with the pdu when GsnCoap_Send_And_Recieve is called
 *
 * @param pTokenValue - IN Token  value.
 * @param pTokenLength = IN Token length
 *
 * @retval GSN_SUCCESS on successful adding of the coap header
 ******************************************************************************/
GSN_STATUS GsnCoap_SetToken(unsigned int pTokenLength, const unsigned char *pTokenValue);


GSN_STATUS GsnCoap_DeleteToken();

#endif /* GSN_COAP_H_ */















