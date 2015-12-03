/******************************************************************************
*
*               COPYRIGHT (c) 2008-2010 GainSpan Corporation
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
* $RCSfile: s2w_timer.h,v $
*
* Description : This file defines s2w timer related function declarations.
*****************************************************************************/

#ifndef S2W_TIMER_H
#define S2W_TIMER_H


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w Timer init function.
 *    This function initialize the s2w timer.
 * @param timer   - IN Pointer to the timer handler.
 * @param handler - IN Timeout call back function.
 * @param data    - IN Pointer to the buffer which is the argument to
 *        timeout callback function.
 * @retval VOID
 ******************************************************************/
VOID AppS2wHal_TimerInit(S2W_TIMER_T *timer, VOID (*handler)(VOID *), VOID *data);

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w Timer start function.
 *    This function start the timer specified.
 * @param timer  - IN Pointer to the timer handler.
 * @param timeout- IN Timer expiry value,
 * @retval VOID
 ******************************************************************/
VOID AppS2wHal_TimerStart(S2W_TIMER_T *timer, UINT32 timeout);

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w Timer stop function.
 *    This function stop the timer specified.
 * @param timer - IN Pointer to the timer handler.
 * @retval VOID
 ******************************************************************/
GSN_STATUS AppS2wHal_TimerStop(S2W_TIMER_T *timer);

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w Timer delete function.
 *    This function remove the timer specified.
 * @param timer - IN Pointer to the timer handler.
 * @retval VOID
 ******************************************************************/
VOID AppS2wHal_TimerDelete(S2W_TIMER_T *timer);


#endif
