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
* $RCSfile: gsn_tmrif_fpt.h,v $
*
* Description : This file contains the API implementation to interface with timer module and 
* the wpa supplicant module.
*******************************************************************************/
#ifndef _GSN_TMRIF_FPT_
#define _GSN_TMRIF_FPT_

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "gsn_includes.h"
#include "security/wpa_if/sys_wpa_if/gsn_wpaif_priv.h"

/**
 *******************************************************************************
 * @file gsn_tmrif.h
 * @brief GSN WPAIF module.
 *      This file contains the TIMER IF specific definitions. The WPA supplicant uses the ELOOP
 * timer implementation. In this implementation a timer is expired or not is always checked in 
 * a loop. This feature is ported using SOFT TMR in this module. To start an ELOOP timer, this 
 * module gives its callback to the SOFT TMR module and when the SOFT TMR module calls the
 * callback, this module adds the timed out ELOOP object to the expired list and then calls the
 * registered callback. User has to register the callback in which the ELOOP timeout has to be
 * handled in GsnWpa_Init API. This API is expected to either post a message to another thread
 * or call the GsnSec_TmrIfHandler API. This API handles all the expired ELOOP timer. Since the
 * SOFT TMR is used to handle time critical functionality, it is always better to call 
 * GsnSec_TmrIfHandler in some other thread context other than SOFT TMR thread context.
 ******************************************************************************/

typedef VOID (*GsnWpaTmrIf_TimeoutCb_FP_T)( VOID* ctx,
    GSN_SOFT_TMR_HANDLE_T  timerHandle );
extern _RPST_ GsnWpaTmrIf_TimeoutCb_FP_T GsnWpaTmrIf_TimeoutCb_FP;

typedef VOID (*GsnWpaTmrIf_Handler_FP_T)( VOID );
extern _RPST_ GsnWpaTmrIf_Handler_FP_T GsnWpaTmrIf_Handler_FP;

typedef VOID (*GsnWpaTmrIf_StopAllTmr_FP_T)( VOID );
extern _RPST_ GsnWpaTmrIf_StopAllTmr_FP_T GsnWpaTmrIf_StopAllTmr_FP;

typedef int (*eloop_register_timeout_FP_T)(unsigned int secs, unsigned int usecs,
			   void (*handler)(void *eloop_ctx, void *timeout_ctx),
			   void *eloop_data, void *user_data, int line );
extern _RPST_ eloop_register_timeout_FP_T eloop_register_timeout_FP;

typedef int (*eloop_cancel_timeout_FP_T)(void (*handler)(void *eloop_ctx, void *sock_ctx),
			 void *eloop_data, void *user_data);
extern _RPST_ eloop_cancel_timeout_FP_T eloop_cancel_timeout_FP;

typedef int (*eloop_is_timeout_registered_FP_T)(void (*handler)(void *eloop_ctx,
						void *timeout_ctx),
				void *eloop_data, void *user_data);
extern _RPST_ eloop_is_timeout_registered_FP_T eloop_is_timeout_registered_FP;

#endif /* _GSN_TMRIF_FPT_ */
