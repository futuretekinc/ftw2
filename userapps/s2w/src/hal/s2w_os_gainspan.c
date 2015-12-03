/*****************************************************************
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
* $RCSfile: s2w_os_gainspan.c,v $
*
* Description : s2w GEPS interface file
******************************************************************/


/*****************************************************************
  * File Inclusions
  *****************************************************************/
#include "gsn_includes.h"
#include "hal/s2w.h"
#include "hal/s2w_types.h"
#include "hal/s2w_timer.h"

/*****************************************************************************
  *  Private Variables
  *****************************************************************************/

/*****************************************************************************
  *  Private Functions
  *****************************************************************************/

PRIVATE INLINE ULONG64 AppS2wHal_TimeoutToTsync(UINT32 timeout);


/*****************************************************************************
  *  Public Functions
  *****************************************************************************/

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

PUBLIC VOID
AppS2wHal_TimerInit(S2W_TIMER_T * timer, VOID (*handler) (VOID *), VOID *data)
{
    S2W_ASSERT(handler != NULL);

    //memset(&timer->timer, 0, sizeof(S2W_TIMER_T));
    timer->timeout = 0;
    timer->handler = handler;
    timer->data = data;
    timer->handle = NULL;
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w Timer start function.
 *    This function start the timer specified.
 * @param timer  - IN Pointer to the timer handler.
 * @param timeout- IN Timer expiry value,
 * @retval VOID
 ******************************************************************/
PUBLIC VOID
AppS2wHal_TimerStart(S2W_TIMER_T * timer, UINT32 timeout)
{
    if (timeout == 0)
    {
        return;
    }

    if (timer->handle)
    {
        if (timer->timeout == timeout)
        {
            timer->handle = GsnSoftTmr_Start(&timer->timer,
                            GSN_SOFT_TMR_ONESHOT,0,
            AppS2wHal_TimeoutToTsync(timer->timeout),
            (GSN_SOFT_TMR_CBR_T) timer->handler, timer->data);
            return;
        }
        else
        {
            GsnSoftTmr_Stop(timer->handle);
        }
    }

    timer->timeout = timeout;

    timer->handle = GsnSoftTmr_Start(&timer->timer,
                       GSN_SOFT_TMR_ONESHOT,0,
    AppS2wHal_TimeoutToTsync(timer->timeout),
                      (GSN_SOFT_TMR_CBR_T) timer->handler, timer->data);
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w Timer stop function.
 *    This function stop the timer specified.
 * @param timer - IN Pointer to the timer handler.
 * @retval VOID
 ******************************************************************/
PUBLIC GSN_STATUS
AppS2wHal_TimerStop(S2W_TIMER_T * timer)
{
    return GsnSoftTmr_Stop(timer->handle);
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w Timer delete function.
 *    This function remove the timer specified.
 * @param timer - IN Pointer to the timer handler.
 * @retval VOID
 ******************************************************************/
PUBLIC VOID
AppS2wHal_TimerDelete(S2W_TIMER_T * timer)
{
    timer->handle = NULL;
    memset(&timer->timer, 0, sizeof(GSN_SOFT_TMR_T));
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Convert from the Serial2WiFi timeout value to the Tsync ticks
 *        required by the Gsn Timer functions.
 * @param timeout - IN the timeout in units of 10ms
 * @retval the period in Tsync ticks
 ******************************************************************/
PRIVATE INLINE ULONG64
AppS2wHal_TimeoutToTsync(UINT32 timeout)
{
    /* The hal's timeout value is in 10ms ticks */
    return (ULONG64) timeout * TIMER_INTERRUPT_10_MS;
}

