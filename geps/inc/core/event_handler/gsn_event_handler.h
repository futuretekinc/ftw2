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
* $RCSfile: gsn_event_handler.h,v $
*
* Description : This file contains public declaration for the event handler
* module.   
******************************************************************************/


/*****************************************************************************
* File Inclusion
*****************************************************************************/
#ifndef _GSN_EVENT_HANDLER_H_
#define _GSN_EVENT_HANDLER_H_

/**
 *****************************************************************************
 * @file gsn_event_handler.h
 * @brief GSN Event Handler public declaration.
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
 * @defgroup GsnEventHandler GSN Event Handler
 *    This group of API functions implements a generic Event handler, by creating 
 *    an event group. Functions can wait on an event or register a callback  
 *    function.
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
 * @ingroup GsnEventHandler
 * @brief GSN Event Handler callback type.
 *    type definition of the handler used in Event handler.
 *****************************************************************************/
typedef VOID (*GSN_EVENT_HANDLER_CB_T)(GSN_OSAL_EVENT_FLAGS_T *) ;

/**
 *****************************************************************************
 * @ingroup GsnEventHandler
 * @brief GSN Event Handler context.
 *    type definition of the Event handler context.
 *****************************************************************************/
typedef struct GSN_EVENT_HANDLER
{
	GSN_OSAL_EVENT_FLAGS_T eventFlagsGroup;
	GSN_OSAL_SEM_T eventSemaphore;
	INT8 *pGroupName;
	VOID *pCtx;
#ifndef TX_DISABLE_NOTIFY_CALLBACKS
	GSN_EVENT_HANDLER_CB_T notifyCb;
#endif
}GSN_EVENT_HANDLER_T;

/*****************************************************************************
 * Public Macros
 ****************************************************************************/


/*****************************************************************************
  * Public Function
  ****************************************************************************/
/**
 *****************************************************************************
 * @ingroup GsnEventHandler
 * @brief Create Event Handler.
 *    This function is used to create a Event handler group. 
 * @param pEventHandler - IN Pointer to event handler context.
 * @note
 *****************************************************************************/
GSN_STATUS_T
GsnEventHandler_Create(GSN_EVENT_HANDLER_T *pEventHandler);

/**
 *****************************************************************************
 * @ingroup GsnEventHandler
 * @brief gets the Events.
 *    This function is used to get the events. 
 * @param pEventHandler - IN Pointer to event handler context.
 * @param requested_flags - IN group of event flags requested.
 * @param get_option - IN 
 *				GSN_OSAL_EVENT_FLAGS_OP_AND : All requested event flags must
 * 					be set in the specified event flags group.
 * 				GSN_OSAL_EVENT_FLAGS_OP_AND_CLEAR : All requested event 
 *					flags must be set in the specified event flags group; 
 *					event flags that satisfy the request are cleared.
 *				GSN_OSAL_EVENT_FLAGS_OP_OR : At least one requested event 
 *					flag must be set in the specified event flags group.
 *				GSN_OSAL_EVENT_FLAGS_OP_OR_CLEAR : At least one requested event 
 *					flag must be set in the specified event flags group; event 
 *					flags that satisfy the request are cleared.
 * @param pActualFlags - OUT Pointer to destination of where the retrieved
 *				event flags are placed.
 * @param wait_option - IN wait option.
 * @note
 *****************************************************************************/
GSN_STATUS_T
GsnEventHandler_EventGet(GSN_EVENT_HANDLER_T *pEventHandler, ULONG requested_flags, 
	GSN_OSAL_EVENT_FLAGS_OP_T get_option, ULONG *pActualFlags, ULONG wait_option);

/**
 *****************************************************************************
 * @ingroup GsnEventHandler
 * @brief Sets Events .
 *    This function is used to set the events. 
 * @param pEventHandler - IN Pointer to event handler context.
 * @param flags_to_set - IN group of event flags requested.
 * @param set_option - IN 
 *				GSN_OSAL_EVENT_FLAGS_OP_AND : The specified event flags are 
 * 					ANDed in to the current event flags in a group.
 *				GSN_OSAL_EVENT_FLAGS_OP_OR : The specified event flags are ORed 
 *					in to the current event flags in a group.
 * @note
 *****************************************************************************/
GSN_STATUS_T
GsnEventHandler_EventSet(GSN_EVENT_HANDLER_T *pEventHandler, ULONG flags_to_set, 
	GSN_OSAL_EVENT_FLAGS_OP_T set_option);

/**
 *****************************************************************************
 * @ingroup GsnEventHandler
 * @brief registers call back for events group.
 *    This function is used to register call back for events group. 
 * @param pEventHandler - IN Pointer to event handler context.
 * @param events_set_notify_cb - IN pointer to call back.
 * @note giving pEventHandler = NULL deregisters callback.
 *****************************************************************************/
GSN_STATUS_T
GsnEventHandler_EventNotifyCb(GSN_EVENT_HANDLER_T *pEventHandler, 
	GSN_EVENT_HANDLER_CB_T events_set_notify_cb);

/**
 *****************************************************************************
 * @ingroup GsnEventHandler
 * @brief deletes event group.
 *    This function is used to delet events group. 
 * @param pEventHandler - IN Pointer to event handler context.
 * @note
 *****************************************************************************/
GSN_STATUS_T
GsnEventHandler_Delete(GSN_EVENT_HANDLER_T *pEventHandler);

#endif


