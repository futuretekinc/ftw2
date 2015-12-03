/******************************************************************************
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
* $RCSfile: gsn_msg_handler.h,v $
*
* Description : This file contains public declaration for the message handler
* module.   
******************************************************************************/


/*****************************************************************************
* File Inclusion
*****************************************************************************/

#ifndef _GSN_MSG_HANDLER_H_
#define _GSN_MSG_HANDLER_H_
#ifdef __cplusplus
extern "C" {
#endif


/**
 *****************************************************************************
 * @file gsn_msg_handler.h
 * @brief GSN Message Handler public declaration.
 *      This file contains the public API declaration.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup coresvcdoc
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnMsgHandler GSN Message Handler
 *    This group of API functions implements a generic message handler, by creating 
 *    a thread and mailbox. The entry function waits on the mailbox and calls 
 *    the registered callback function.
 *****************************************************************************/
	
	
/**
 *****************************************************************************
 * 
 * @}
 *****************************************************************************/

/*****************************************************************************
  * Type Definitions
  ****************************************************************************/
/**
 *****************************************************************************
 * @ingroup GsnMsgHandler
 * @brief GSN Message Handler callback type.
 *    type definition of the handler used in message handler.
 *****************************************************************************/
typedef BOOL ( *GSN_MSG_HANDLER_CB_T )( VOID* pCtx, VOID *pMsg );

/**
 *****************************************************************************
 * @ingroup GsnMsgHandler
 * @brief GSN Message Handler context.
 *    type definition of the message handler context.
 *****************************************************************************/
typedef struct GSN_MSG_HANDLER_CTX_T 
{
    GSN_OSAL_THREAD_TCB_T   tcb;
    GSN_OSAL_QUEUE_T msgQueue;
    VOID                    *pMsg;
    VOID                    *pHandlerCtx;
    GSN_MSG_HANDLER_CB_T    handlerCb;
} GSN_MSG_HANDLER_CTX_T;

/**
 *****************************************************************************
 * @ingroup GsnMsgHandler
 * @brief GSN Message Handler configuration.
 *    type definition of the message handler configuration structure.
 *****************************************************************************/
typedef struct GSN_MSG_HANDLER_CFG_T 
{
    UINT8* pThreadName;
    UINT32* pStack; 
    UINT32 stackSize; 
    UINT32 priority; 
    UINT8* msgQueueBuff;
    UINT32 msgQueueBuffSize; 
    UINT8  msgSize;
} GSN_MSG_HANDLER_CFG_T;

/*****************************************************************************
 * Public Macros
 ****************************************************************************/


/*****************************************************************************
  * Public Function
  ****************************************************************************/
/**
 *****************************************************************************
 * @ingroup GsnMsgHandler
 * @brief Create Message Handler.
 *    This function is used to create a message handler. 
 * @param pCtx - IN Pointer to the memory to be used by the message handler.
 * @param pCfg - IN Configuration details for the message handler.
 * @param pMsg - IN Pointer to the memory in SRAM to read the message from 
 *    the mailbox. The size of the memory should be same as the size of 
 *    message stored in mailbox.
 * @param handlerCb - IN Handler function to be called to process the message.
 * @param pHandlerCtx - IN Handler context to be passed to process the message.
 * @note
 *****************************************************************************/
PUBLIC VOID 
GsnMsgHandler_Create( GSN_MSG_HANDLER_CTX_T* pCtx, GSN_MSG_HANDLER_CFG_T *pCfg,
    VOID *pMsg, GSN_MSG_HANDLER_CB_T handlerCb, VOID *pHandlerCtx );

/**
 *****************************************************************************
 * @ingroup GsnMsgHandler
 * @brief Delete Message Handler.
 *    This function is used to create a message handler. 
 * @param pCtx - IN Pointer to the memory used by the message handler. This 
 *    should be same as passed in the Create API.
 * @note
 *****************************************************************************/
INLINE PUBLIC VOID
GsnMsgHandler_Delete( GSN_MSG_HANDLER_CTX_T* pCtx )
{
  /**< Must close task first, otherwise closed mailbox could cause context 
  switch which allows GsnOsal_MailboxGet to return GH_ERROR_OBJECT_CLOSED which 
  would not be handled. */
  GsnOsal_ThreadDelete( &pCtx->tcb );
  GsnOsal_QueueDelete( &pCtx->msgQueue );
}

/**
 *****************************************************************************
 * @ingroup GsnMsgHandler
 * @brief Install handler in Message Handler.
 *    This function is used to install handler and its context in message 
 *    handler. 
 * @param pCtx - IN Pointer to the memory to be used by the message handler.
 * @param handlerCb - IN Handler function to be called to process the message.
 * @param pHandlerCtx - IN Handler context to be passed to process the message.
 * @note Must not be called from msgHandler's own Task!
 * @note Must not be called if msgHandler's handler owns any mutexes!
 *****************************************************************************/
INLINE PUBLIC VOID 
GsnMsgHandler_Install( GSN_MSG_HANDLER_CTX_T* pCtx, VOID *pHandlerCtx, 
    GSN_MSG_HANDLER_CB_T handlerCb )
{
    pCtx->pHandlerCtx = pHandlerCtx;
    pCtx->handlerCb = handlerCb;
}

/**
 *****************************************************************************
 * @ingroup GsnMsgHandler
 * @brief Post message to Message Handler.
 *    This function is used to post a message to a message handler. 
 * @param pCtx - IN Pointer to the memory used by the message handler. This 
 *    should be same as passed in the Create API.
 * @param pMsg - IN Pointer to the memory that contins the message.
 * @note
 *****************************************************************************/
INLINE PUBLIC GSN_STATUS 
GsnMsgHandler_Post( GSN_MSG_HANDLER_CTX_T* pCtx, VOID *pMsg )
{
    GSN_STATUS retCode = GSN_SUCCESS;
    if( GSN_OSAL_SUCCESS != GsnOsal_QueuePut( &pCtx->msgQueue, (UINT8 *)pMsg ))
    {
        retCode = GSN_FAILURE;
    }
    return retCode;
} 

#ifdef __cplusplus
}
#endif
#endif /* _GSN_MSG_HANDLER_H_ */



