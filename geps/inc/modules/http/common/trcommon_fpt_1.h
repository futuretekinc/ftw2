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
* $RCSfile: trcommon_fpt_1.h,v $
*
* Description : This file contains the function pointers definitions.
*******************************************************************************/
#ifndef TRCOMMON_FPT_1_H_
#define TRCOMMON_FPT_1_H_

#include <string.h>
#include "netx/netx_bsd_layer/nxd_bsd.h"
#include "modules/http/include/trsocket.h"

#include "modules/http/include/trmacro.h"
#include "modules/http/include/trtype.h"
#include "modules/http/include/trproto.h"
#include "modules/http/include/trglobal.h"
//#include "trhttpc.h"

/*typedef void (*gsn_bsd_cb_wrapper_FP_T)(int socket_id, NX_BSD_CB_EVENT_TYPE_T event,
		                        VOID *cbCtx1, VOID *cbCtx2);*/

typedef void
(*tm_call_lock_wait_FP_T)(GSN_OSAL_MUTEX_T **mutexptrptr);

typedef void
(*tm_call_unlock_FP_T)(GSN_OSAL_MUTEX_T **mutexptrptr);

typedef int (*tfIsOvrflwNotifSet_FP_T)(int                   socketDescriptor);

//extern _RPST_ gsn_bsd_cb_wrapper_FP_T gsn_bsd_cb_wrapper_FP;
extern _RPST_ tm_call_lock_wait_FP_T tm_call_lock_wait_FP;
extern _RPST_ tm_call_unlock_FP_T tm_call_unlock_FP;
extern _RPST_ tfIsOvrflwNotifSet_FP_T tfIsOvrflwNotifSet_FP;
#endif /* TRCOMMON_FPT_1_H_ */

