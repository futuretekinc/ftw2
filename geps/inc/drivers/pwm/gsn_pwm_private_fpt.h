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
* $RCSfile: gsn_pwm_private_fpt.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/

#ifndef _GSN_PWM_PRIVATE_FTP_H_
#define _GSN_PWM_PRIVATE_FTP_H_
/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "drivers/pwm/gsn_pwm_private.h"




/*****************************************************************************
  *  Definitions
  ****************************************************************************/
typedef VOID
( *GsnPwm_Isr_FP_T)( GSN_PWM_HANDLE_T *pPwmHandle );
extern _RPST_ GsnPwm_Isr_FP_T GsnPwm_Isr_FP;

typedef GSN_STATUS
( *GsnPwm_IndividualStart_FP_T)( GSN_PWM_HANDLE_T *pPwmHandle,
    GSN_PWM_NO pwmNumber );
extern _RPST_ GsnPwm_IndividualStart_FP_T GsnPwm_IndividualStart_FP;

typedef GSN_STATUS
( *GsnPwm_IndividualUpdate_FP_T)( GSN_PWM_HANDLE_T *pPwmHandle, GSN_PWM_PATTERN_T *pGsnPwmPattern,
    GSN_PWM_NO pwmNumber );
extern _RPST_ GsnPwm_IndividualUpdate_FP_T GsnPwm_IndividualUpdate_FP;

typedef GSN_STATUS
( *GsnPwm_SynchronizedStart_FP_T)( GSN_PWM_HANDLE_T *pPwmHandle );
extern _RPST_ GsnPwm_SynchronizedStart_FP_T GsnPwm_SynchronizedStart_FP;

typedef GSN_STATUS
( *GsnPwm_SynchronizedUpdate_FP_T)( GSN_PWM_HANDLE_T *pPwmHandle,
    GSN_PWM_PATTERN_T *pGsnPwmPattern );
extern _RPST_ GsnPwm_SynchronizedUpdate_FP_T GsnPwm_SynchronizedUpdate_FP;

typedef VOID
(* GsnPwm_IndividualStop_FP_T)( GSN_PWM_HANDLE_T *pPwmHandle, GSN_PWM_NO pwmNumber );
extern _RPST_ GsnPwm_IndividualStop_FP_T GsnPwm_IndividualStop_FP;

typedef  VOID
( * GsnPwm_SynchronizedStop_FP_T)( GSN_PWM_HANDLE_T *pPwmHandle );
extern _RPST_ GsnPwm_SynchronizedStop_FP_T GsnPwm_SynchronizedStop_FP;

typedef  VOID
( *GsnPwm_IsrOn_FP_T )( GSN_PWM_HANDLE_T* pPwmHandle, UINT32 channelId );
extern _RPST_ GsnPwm_IsrOn_FP_T GsnPwm_IsrOn_FP;

typedef  VOID
( *GsnPwm_LoadValue_FP_T)( GSN_PWM_HANDLE_T *pPwmHandle, GSN_PWM_PATTERN_T *pPwmPattern,
    UINT32 channelId );
extern _RPST_ GsnPwm_LoadValue_FP_T GsnPwm_LoadValue_FP;

typedef PUBLIC VOID
( *__GsnPwm_Isr_FP_T)();
extern _RPST_ __GsnPwm_Isr_FP_T __GsnPwm_Isr_FP;
#endif
