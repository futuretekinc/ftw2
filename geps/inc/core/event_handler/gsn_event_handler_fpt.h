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
* $RCSfile: gsn_event_handler_fpt.h,v $
*
* Description : This file contains function poointer definitions for the event handler
* module.
******************************************************************************/


/*****************************************************************************
* File Inclusion
*****************************************************************************/

#ifndef _GSN_EVENT_HANDLER_FPT_H_
#define _GSN_EVENT_HANDLER_FPT_H_


#include "gsn_includes.h"
#include "core/event_handler/gsn_event_handler.h"

typedef GSN_STATUS_T
(*GsnEventHandler_Create_FP_T) (GSN_EVENT_HANDLER_T *pEventHandler);

extern _RPST_ GsnEventHandler_Create_FP_T GsnEventHandler_Create_FP;

typedef GSN_STATUS_T
(*GsnEventHandler_EventGet_FP_T)(GSN_EVENT_HANDLER_T *pEventHandler, ULONG requested_flags,
	GSN_OSAL_EVENT_FLAGS_OP_T get_option, ULONG *pActualFlags, ULONG wait_option);

extern _RPST_ GsnEventHandler_EventGet_FP_T GsnEventHandler_EventGet_FP;

typedef GSN_STATUS_T
(*GsnEventHandler_EventSet_FP_T)(GSN_EVENT_HANDLER_T *pEventHandler, ULONG flags_to_set,
	GSN_OSAL_EVENT_FLAGS_OP_T set_option);

extern _RPST_ GsnEventHandler_EventSet_FP_T GsnEventHandler_EventSet_FP;

#ifndef TX_DISABLE_NOTIFY_CALLBACKS
typedef GSN_STATUS_T
(*GsnEventHandler_EventNotifyCb_FP_T)(GSN_EVENT_HANDLER_T *pEventHandler,
	GSN_EVENT_HANDLER_CB_T events_set_notify_cb);

extern _RPST_ GsnEventHandler_EventNotifyCb_FP_T GsnEventHandler_EventNotifyCb_FP;
#endif

typedef GSN_STATUS_T
(*GsnEventHandler_Delete_FP_T)(GSN_EVENT_HANDLER_T *pEventHandler);

extern _RPST_ GsnEventHandler_Delete_FP_T GsnEventHandler_Delete_FP;

#endif
