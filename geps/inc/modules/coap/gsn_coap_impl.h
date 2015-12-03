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
* gsn_coap_impl.h
*
*  Created on: 05-Jul-2013
*      Author: Dhanya Lakshmi
*/

#ifndef GSN_COAP_IMPL_H_
#define GSN_COAP_IMPL_H_


#include "modules/coap/libcoap-4.0.1/net.h"
#include "modules/coap/gsn_pdu_impl.h"
#include "gsn_includes.h"

typedef unsigned short gsn_coap_tid;


typedef coap_context_t GSN_COAP_CONTEXT_T;

typedef coap_address_t GSN_COAP_ADDR_T;


/**
 * This function Starts the COAP connection.Further this connection can be used
 * to read or write CoAP messages to a specified destination. This call supports both Confirmable
 * and Non Confirmable connections
 * Returns a new CoAP context
 *
 * @return GSN_COAP_CONTEXT_T Coap context object is returned
 */

GSN_COAP_CONTEXT_T* GsnCoap_New_Context();


// sends a non-confirmed CoAP message to given destination
gsn_coap_tid GsnCoap_Send(GSN_COAP_CONTEXT_T* context, GSN_COAP_ADDR_T * dest, GSN_COAP_PDU_T *pdu);


int GsnCoap_Read(GSN_COAP_CONTEXT_T* context);

//Do we need a non blocking read()?

gsn_coap_tid GsnCoap_Send_Ack(GSN_COAP_CONTEXT_T *context,
                              const GSN_COAP_ADDR_T *dst,
                              GSN_COAP_PDU_T *request);

/* CoAP stack context must be released with coap_free_context() */
void GsnCoap_Free_Context( GSN_COAP_CONTEXT_T *context );


/**
 * Sends an RST message with code @c 0 for the specified @p request to
 * @p dst. This function returns the corresponding transaction id if
 * the message was sent or @c COAP_INVALID_TID on error.
 *
 * @param context The context to use.
 * @param dst     The destination address.
 * @param request The request to be reset.
 *
 * @return The transaction id if RST was sent or @c COAP_INVALID_TID
 * on error.
 */
gsn_coap_tid GsnCoap_Send_Rst(GSN_COAP_CONTEXT_T *context,
                              const GSN_COAP_ADDR_T *dst,
                              GSN_COAP_PDU_T *request);

/** Dispatches the PDUs from the receive queue in given context. */
void GsnCoap_Dispatch( GSN_COAP_CONTEXT_T *context );

/** Returns 1 if there are no messages to send or to dispatch in the context's queues. */
int GsnCoap_Can_Exit( GSN_COAP_CONTEXT_T *context );


/** Message handler that is used as call-back in GSN_COAP_CONTEXT_T */
typedef void (*GsnCoap_Response_Handler)(GSN_COAP_CONTEXT_T  *,
        const GSN_COAP_ADDR_T *remote,
        GSN_COAP_PDU_T *sent,
        GSN_COAP_PDU_T *received,
        const gsn_coap_tid id);

void GsnCoap_Register_Response_Handler(GSN_COAP_CONTEXT_T *context,
                                       GsnCoap_Response_Handler handler);



/* Loops through the send queue, retranmits the nodes whose timer has expired
 * and removes from queue if max no of transmissions is reached.
 * It does not return the tid of the retransmitted messages, it will be given in the callback
 */
void GsnCoap_Retransmit_ProcessResponse(GSN_COAP_CONTEXT_T *context);


/**
 * Calculates a unique transaction id from given arguments @p peer and
 * @p pdu. The id is returned in @p id.
 *
 * @param peer The remote party who sent @p pdu.
 * @param pdu  The message that initiated the transaction.
 * @param id   Set to the new id.
 */
void GSnCoap_transaction_id(const GSN_COAP_ADDR_T *peer, const GSN_COAP_PDU_T *pdu,
                            gsn_coap_tid *id);

GSN_COAP_ADDR_T* GsnCoap_Fill_IpAddress(char * address, int port);

int GsnCoap_Read_With_Timeout(GSN_COAP_CONTEXT_T *context,int timeout);

#endif /* GSN_COAP_IMPL_H_ */
