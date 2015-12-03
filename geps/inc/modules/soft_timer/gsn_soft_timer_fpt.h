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
* $RCSfile: gsn_soft_timer_fpt.h,v $
*
*******************************************************************************/

#ifndef _GSN_SOFT_TIMER_FPT_H_

#define _GSN_SOFT_TIMER_FPT_H_

typedef GSN_SYSTEM_TIME_T
(* GsnSoftTmr_CurrentSystemTime_FP_T)( VOID );

extern _RPST_ GsnSoftTmr_CurrentSystemTime_FP_T GsnSoftTmr_CurrentSystemTime_FP;

typedef VOID *
(* GsnSoftTmr_Init_FP_T) ( int bootInd, GSN_MSG_HANDLER_CTX_T* pMsgHandlerCtx );

extern _RPST_   GsnSoftTmr_Init_FP_T GsnSoftTmr_Init_FP;

typedef GSN_SOFT_TMR_HANDLE_T
( * GsnSoftTmr_Start_FP_T) ( GSN_SOFT_TMR_T* timer, GSN_SOFT_TMR_TYPE_T type,
    GSN_SYSTEM_TIME_T expireTime, ULONG64 period, GSN_SOFT_TMR_CBR_T cbr,
    VOID* context );

extern _RPST_ GsnSoftTmr_Start_FP_T GsnSoftTmr_Start_FP;

typedef   GSN_STATUS
( *GsnSoftTmr_Stop_FP_T)( GSN_SOFT_TMR_HANDLE_T timerHandle );

extern _RPST_ GsnSoftTmr_Stop_FP_T GsnSoftTmr_Stop_FP;

typedef ULONG64
( *GsnSoftTmr_MinRemainingTimeGet_FP_T)();

extern _RPST_ GsnSoftTmr_MinRemainingTimeGet_FP_T GsnSoftTmr_MinRemainingTimeGet_FP;

typedef VOID
(* GsnSoftTmr_ShutDown_FP_T)( VOID );

extern _RPST_ GsnSoftTmr_ShutDown_FP_T GsnSoftTmr_ShutDown_FP;

typedef UINT32
( *GsnSoftTmr_Run_FP_T) ( VOID *context, VOID *pMsg );

extern _RPST_ GsnSoftTmr_Run_FP_T GsnSoftTmr_Run_FP;

typedef GSN_SOFT_TMR_T *
(* GsnSoftTmr_ExpireListNodeDelete_FP_T)( GSN_SOFT_TMR_T *timerLocation );

extern _RPST_ GsnSoftTmr_ExpireListNodeDelete_FP_T GsnSoftTmr_ExpireListNodeDelete_FP;

typedef GSN_SOFT_TMR_HANDLE_T
(* GsnSoftTmr_ActiveListAdd_FP_T)( GSN_SOFT_TMR_T *timer, BOOL addPeriod );

extern _RPST_ GsnSoftTmr_ActiveListAdd_FP_T GsnSoftTmr_ActiveListAdd_FP;
#endif
