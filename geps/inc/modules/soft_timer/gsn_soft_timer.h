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
* $RCSfile: gsn_soft_timer.h,v $
*
* Description : This file contains function and structure declaration for 
* soft timer module.
*****************************************************************************/
#ifndef _GSN_SOFT_TIMER_H_
#define _GSN_SOFT_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
* File inclusion
******************************************************************************/

/**
 *****************************************************************************
 * @file gsn_soft_timer.h
 * @brief GSN Soft Timer public header.
 *    This file contains the public APIs and structures of Soft Timer module.
 *
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnSoftTimer GSN Soft Timer API
 * @brief This module provides a number of soft timers based on a single hardware timer.
 *
 *    The soft timer module provides multiple timers using a single hardware 
 *    timer. It generates interrupts only when a soft timer expires. Currently
 *    the auxiliary timer of the TSYNC module is used to give a hardware timeout.
 *
 *    The GEPS Timer module, once initialized, creates a queue in which individual timer 
 *    structures are stored.  Each structure consists of an identifying handle, a timer type 
 *    (e.g. one-shot or periodic), an expiration time, a period, and a callback function.  
 *    The Tsync module, which manages the real-time clock functions, will throw an interrupt 
 *    when a timer expires.  This interrupt can be used to cause the Timer module to review 
 *    the queue and call the callback routines for any expired timers.  If the expired timers 
 *    are periodic, their entry receives a new expiration time and is moved to the correct order in the queue.  
 *    The response to the Tsync interrupt should be in a separate operating-system task from 
 *    the main User Application, in order to ensure that response to timer expiration is not blocked.  
 *    Therefore, before any timer is started, the User Application should create a message-handling 
 *    task and associate the message queue of that task with the interrupt handler for timer expiration.  
 *    For example:  
 *
 *    \verbatim
 *    GSN_MSG_HANDLER_CFG_T cfg = {…};     // configure a message queue
 *       tmrCtx = GsnSoftTmr_Init (…);     // initialize the timer
 *       GsnMsgHandler_Create (…);         // start a message handling task
 *    \endverbatim
 *
 *    where the message handler context and handle are passed in as arguments of the call 
 *    to the handler creation function.  After this code is executed, a message-handling
 *    task is started and then waits on its message queue.  Each time a message is received on
 *    that message queue, the task will call the function GsnSoftTmr_Run(), which causes the timer 
 *    module to review and update the timer listing, while calling the callbacks of expired timers.  <br> 
 *    <br>
 *    Once the required initialization steps are completed, new timer instances can be created as 
 *    required with a call to 
 *    \verbatim
 *    GsnSoftTmr_Start(&myTmr, 	// timer handle
 *       GSN_SOFT_TMR_PERIODIC,	// timer type
 *       0,	                    // expire time (see below)
 *       TIMER_INTERRUPT_1_S, 	// period
 *       myCb, 	                // callback
 *       pAppCtx);	            // callback argument
 *    \endverbatim
 *
 *    The timer handle is a pointer to the location in memory where the structure corresponding 
 *    to this timer instance will be stored.  The type is an enumeration, either periodic or 
 *    one-shot as described above.  The expire time can be specified in system time ticks, but 
 *    it will often be convenient to provide a value of 0 for this argument, in which case the 
 *    expire time is computed by adding the current system time to the value of the period given 
 *    in the next argument.  (When a non-zero expiration time is given for a one-shot timer, the 
 *    period argument is ignored.)  The period is a 64-bit number giving a time interval in ticks 
 *    of the constant 225 = 33,554,432 Hz system clock; it is recommended that the human-readable 
 *    macros provided by GEPS be substituted for numeric literals to improve readability and 
 *    maintainability of your code.  <br> 
 *    <br>
 *    Each timer that is created will correspond to an entry in the timer queue, and the 
 *    relevant callback routine will be called when it expires.  If the timer is periodic, 
 *    it will receive a new expiration time and be relocated at the appropriate position in the timer queue.  
 *    GEPS provides a number of API functions for managing timer operation. GsnSoftTmr_Stop() 
 *    removes the corresponding timer from the timer queue. GsnSoftTmr_Ioctl() can perform 
 *    a variety of operations for elements in the queue, including getting the expiration time 
 *    of timers, checking for the existence of a specific timer, or retrieving the next expiration 
 *    time in the queue.  <br>
 *    <br>
 *
 *    
 *    Example code to initialize the soft timer module:
 *    \verbatim
 *    DEFINE VARIABLES IN GLOBAL SPACE:
 *  
 *    GSN_MSG_HANDLER_CTX_T timerMsgHandlerCtx;
 *    UINT8 timerMsgHandlerStack[ 2048 ] - size depends on the stack usage of 
 *                                         the cb passed in soft timer start.
 *    UINT32 mailboxBuff[ 8 ] - mailboxBuff for the mailbox, Since this module
 *                              takes 1 word per message, so in this case max, 
 *                              8 messages can be queued in the mailbox.
 *    UINT32 softTmrMsg;
 *
 *    IN LOCAL SPACE:
 *    
 *    GSN_MSG_HANDLER_CFG_T cfg = { "TMR_MSG_HANDLER", timerMsgHandlerStack,
 *        sizeof( timerMsgHandlerStack ), priority (- should be highest),; 
 *        mailboxBuff, sizeof( mailboxBuff ), 1 };
 *
 *    VOID * tmrCtx = GsnSoftTmr_Init( bootInd, &timerMsgHandlerCtx );  
 *    GsnMsgHandler_Create( GSN_MSG_HANDLER_CTX_T pCtx, &cfg, &softTmrMsg,
 *    GsnSoftTmr_Run, tmrCtx );
 *
 *    \endverbatim
 *    
******************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/
/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief micro, milli seconds to system time and vice-versa conversion.
 *    MACROs to convert time to system time and vice-versa.
 *****************************************************************************/	
#define TIMER_CLOCK  32768	// 2^15

#define GS2000_TMR_INTERRUPT_NUMBER 39

#define USEC_TO_SYSTIME(T)  (( ULONG64 ) (((T) << 15) / 1000000))
#define MSEC_TO_SYSTIME(T)  (( ULONG64 ) (((T) << 15) / 1000))
#define SEC_TO_SYSTIME(T)  (( ULONG64 ) ((T) << 15))

#define SYSTIME_TO_USEC(T)  (( ULONG64 ) ((T * 1000000) >> 15))
#define SYSTIME_TO_MSEC(T)  (( ULONG64 ) ((T * 1000) >> 15))
#define SYSTIME_TO_SEC(T)  (( ULONG64 ) ((T) >> 15))
	
	
/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief Ticks in one millisecond
 *    This macro gives number of ticks in one millisecond.
 *****************************************************************************/
#define TIMER_INTERRUPT_1_MS    ((( ULONG64 ) TIMER_CLOCK ) / 1000 )

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief Milliseconds to ticks coversion
 *    This macro converts time in milliseconds to ticks. msec should be ULONG64.
 *****************************************************************************/
#define GSN_SOFT_TMR_TICKS_TO_MILLISECONDS( sysTicks ) SYSTIME_TO_MSEC(sysTicks)

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief Milliseconds to ticks coversion
 *    This macro converts time in milliseconds to ticks. msec should be ULONG64.
 *****************************************************************************/
#define GSN_SOFT_TMR_MILLISECONDS_TO_TICKS( msec ) MSEC_TO_SYSTIME(msec)


/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief Milliseconds to ticks conversion
 *
 *    These macros give milliseconds-to-ticks conversion for common time periods.
 *    These are just for convenience.  
 * @{
 *****************************************************************************/
#define TIMER_INTERRUPT_5_MS    ((( ULONG64 ) TIMER_CLOCK ) * 5 / 1000 )
#define TIMER_INTERRUPT_10_MS   ((( ULONG64 ) TIMER_CLOCK ) * 5 * 2 / 1000 )
#define TIMER_INTERRUPT_20_MS   ((( ULONG64 ) TIMER_CLOCK ) * 5 * 4 / 1000 )
#define TIMER_INTERRUPT_30_MS   ((( ULONG64 ) TIMER_CLOCK ) * 5 * 6 / 1000 )
#define TIMER_INTERRUPT_40_MS   ((( ULONG64 ) TIMER_CLOCK ) * 5 * 8 / 1000 )
#define TIMER_INTERRUPT_50_MS   ((( ULONG64 ) TIMER_CLOCK ) * 5 * 10 / 1000 )
#define TIMER_INTERRUPT_60_MS   ((( ULONG64 ) TIMER_CLOCK ) * 5 * 12 / 1000 )
#define TIMER_INTERRUPT_70_MS   ((( ULONG64 ) TIMER_CLOCK ) * 5 * 14 / 1000 )
#define TIMER_INTERRUPT_80_MS   ((( ULONG64 ) TIMER_CLOCK ) * 5 * 16 / 1000 )
#define TIMER_INTERRUPT_90_MS   ((( ULONG64 ) TIMER_CLOCK ) * 5 * 18 / 1000 )
#define TIMER_INTERRUPT_100_MS  ((( ULONG64 ) TIMER_CLOCK ) * 5 * 20 / 1000 )
#define TIMER_INTERRUPT_200_MS  ((( ULONG64 ) TIMER_CLOCK ) * 5 * 40 / 1000 )
#define TIMER_INTERRUPT_300_MS  ((( ULONG64 ) TIMER_CLOCK ) * 5 * 60 / 1000 )
#define TIMER_INTERRUPT_400_MS  ((( ULONG64 ) TIMER_CLOCK ) * 5 * 80 / 1000 )
#define TIMER_INTERRUPT_500_MS  ((( ULONG64 ) TIMER_CLOCK ) * 5 * 100 / 1000 )
#define TIMER_INTERRUPT_600_MS  ((( ULONG64 ) TIMER_CLOCK ) * 5 * 120 / 1000 )
#define TIMER_INTERRUPT_700_MS  ((( ULONG64 ) TIMER_CLOCK ) * 5 * 140 / 1000 )
#define TIMER_INTERRUPT_800_MS  ((( ULONG64 ) TIMER_CLOCK ) * 5 * 160 / 1000 )
#define TIMER_INTERRUPT_900_MS  ((( ULONG64 ) TIMER_CLOCK ) * 5 * 180 / 1000 )
#define TIMER_INTERRUPT_1_S     ((( ULONG64 ) TIMER_CLOCK ) * 5 * 200 / 1000 )
#define TIMER_INTERRUPT_2_S     ((( ULONG64 ) TIMER_CLOCK ) * 5 * 400 / 1000 )
#define TIMER_INTERRUPT_3_S     ((( ULONG64 ) TIMER_CLOCK ) * 5 * 600 / 1000 )
#define TIMER_INTERRUPT_4_S     ((( ULONG64 ) TIMER_CLOCK ) * 5 * 800 / 1000 )
#define TIMER_INTERRUPT_5_S     ((( ULONG64 ) TIMER_CLOCK ) * 5 * 1000 / 1000 )
	
/**
 *****************************************************************************
 *  
 * @}
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief Timer status.
 *    MACRO for timer status.
 *****************************************************************************/
#define GSN_SOFT_TMR_STATUS_STOP                  0x0
#define GSN_SOFT_TMR_STATUS_ACTIVE                0x1
#define GSN_SOFT_TMR_STATUS_EXPIRED               0x2
#define GSN_SOFT_TMR_STATUS_STOPPED_AFTER_EXPIRE  0x3

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief  structure to hold the 64-bit time value.
 *****************************************************************************/
typedef struct GSN_GS2000_TIME
{
    UINT32 high;
    UINT32 low;
} GSN_GS2000_TIME_T;


/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief GSN Soft Timer Type.
 *    enum for soft timer timer type.
 *****************************************************************************/
typedef enum GSN_SOFT_TMR_TYPE_T
{
    GSN_SOFT_TMR_ONESHOT,
    GSN_SOFT_TMR_PERIODIC
}GSN_SOFT_TMR_TYPE_T;

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief GSN System Timer Type.
 *    type definition for the system time.
 *****************************************************************************/
typedef ULONG64 GSN_SYSTEM_TIME_T;

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief GSN Soft timer handle.
 *    Timer handle type.
 *****************************************************************************/
typedef struct GSN_SOFT_TMR_T* GSN_SOFT_TMR_HANDLE_T;

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief GSN Soft timer callback prototype.
 *    A Timer Callback routine gets passed:
 *      (1) its execution context and 
 *      (2) a pointer to the Timer structure
 *****************************************************************************/
typedef VOID ( *GSN_SOFT_TMR_CBR_T )( VOID* context,
    GSN_SOFT_TMR_HANDLE_T  timerHandle );

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief GSN Soft timer callback information.
 *    A callback includes both a Callback Routine, and its execution context.
 *****************************************************************************/
typedef struct GSN_SOFT_TMR_CALLBACK_T
{
    VOID*              context; /**< Callback routine execution context. */
    GSN_SOFT_TMR_CBR_T cbr;     /**< Callback routine */
} GSN_SOFT_TMR_CALLBACK_T;

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief GSN Soft timer structure.
 *    Timer structure to store the context of the soft timer.
 *****************************************************************************/
typedef struct GSN_SOFT_TMR_T
{
    struct GSN_SOFT_TMR_T*  next; /**< Next soft timer in the linked-list */
    UINT8                   type; /**< Timer Type */
    UINT8                   status; /**< Status of the timer */
    GSN_SYSTEM_TIME_T       expireTime; /**< SYSTEM Time at which the timer 
    will next expire */

    ULONG64                 period; /**< Timer expiration period:For periodic 
    timers, period is added to expireTime. For one-shot timers, period is 0 */

    GSN_SOFT_TMR_CALLBACK_T callback; /**< callback.pCBR(callback.pContext, 
    &pTimer) is called when timer expires */
} GSN_SOFT_TMR_T;

typedef VOID ( *TMR_EXPR_CALLBACK_FP ) ( VOID );

typedef struct GSN_GS2000_TMR
{
	UINT32 *pReg;
	TMR_EXPR_CALLBACK_FP tmrExpEventHndlrCb;
}GSN_GS2000_TMR_T;
/******************************************************************************
* Public Function
******************************************************************************/
/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief Gets the system time.
 *    This function gives the current system time.
 * @retval 64 bit system time.
 * @note
 *    
 *****************************************************************************/
PUBLIC GSN_SYSTEM_TIME_T 
GsnSoftTmr_CurrentSystemTime( VOID );

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief Initialization for Soft Timer module.
 *    This function performs initialization of Soft timer module.
 * @param bootInd - IN Reason the system woke-up and called this function.
 * @param pMsgHandlerCtx - IN Pointer to the context of message handler, where
 *    the expire events are handled.
 * @retval Returns the context of the soft timer module, which has to be 
 *    passed in GsnSoftTmr_Run API.
 * @note
 *    This function must be called during INIT before calling other soft timer
 * API.
 *****************************************************************************/
PUBLIC VOID * 
GsnSoftTmr_Init( int bootInd, 
	GSN_MSG_HANDLER_CTX_T* pMsgHandlerCtx );

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief Start a soft timer.
 *    This function starts a soft timer with the spcified value.
 * @param timer - IN Pointer to memory location where the soft timer module 
 * stores the context for this timer.
 * @param type       - IN Periodic or One-Shot.
 * @param expireTime - IN System time when timer will first expire.
 *    Set to 0 to trigger the first expiration of a periodic timer immediately.
 *    Set >0 to offset first expiration.
 * @param period     - IN For Periodic Timers, the period of repeating 
 *    expirations, after initial expiration. For One-Shot, period is ignored.
 * @param cbr - IN callback function to be called once the timer expires.
 * @param context - IN Context to be stored by the soft timer module and to be
 * passed with the callback function once the timer expires.
 * @retval Timer handle will have a non-zero value if Operation is successful.
 * @retval zero if failed.
 * @note
 *    
 *****************************************************************************/
PUBLIC GSN_SOFT_TMR_HANDLE_T  
GsnSoftTmr_Start( GSN_SOFT_TMR_T* timer, GSN_SOFT_TMR_TYPE_T type, 
    GSN_SYSTEM_TIME_T expireTime, ULONG64 period, GSN_SOFT_TMR_CBR_T cbr, 
    VOID* context );

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief Stop a soft timer.
 *    This function stops the soft timer.
 * @param timerHandle - IN timer handle returned in the timer start API.
 * @retval GSN_SUCCESS if Operation is successful i.e. the timerHandle passed
 *    is a active and it is removed from the list.
 * @retval GSN_FAILURE if timer is not active.
 * @note
 *    
 *****************************************************************************/
PUBLIC GSN_STATUS  
GsnSoftTmr_Stop( GSN_SOFT_TMR_HANDLE_T timerHandle );

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief Remaining time get.
 *    Returns the remaining time left to expire for a give timer.
 * @param hTmr - IN timer handle returned in the timer start API.
 * @retval remaining time in timer ticks.
 * @note
 *    User should pass a valid timer handle.
 *****************************************************************************/
PUBLIC INLINE ULONG64
GsnSoftTmr_RemainingTimeGet( GSN_SOFT_TMR_HANDLE_T hTmr )
{
    return ((GSN_SOFT_TMR_T*)hTmr)->expireTime -
        GsnSoftTmr_CurrentSystemTime();
}

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief Minimum Remaining time of all active timer get.
 *    Returns the minimum remaining time left to expire of all the active 
 *    timer.
 * @retval remaining time in timer ticks. retunrns 0xFFFFFFFFFFFFFFFF (~0L)
 *    if no timer is active.
 * @note
 *    User should pass a valid timer handle.
 *****************************************************************************/
PUBLIC ULONG64
GsnSoftTmr_MinRemainingTimeGet();

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief A timer is active or not.
 *    Returns whether the timer is active or not.
 * @param hTmr - IN timer handle returned in the timer start API.
 * @retval TRUE if the timer is active else FALSE
 * @note
 *    User should pass a valid timer handle.
 *****************************************************************************/
PUBLIC INLINE BOOL
GsnSoftTmr_IsActive( GSN_SOFT_TMR_HANDLE_T hTmr )
{

    return (((GSN_SOFT_TMR_T*)hTmr)->status == GSN_SOFT_TMR_STATUS_ACTIVE);
}

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief Period of the timer.
 *    Returns the period timer is active or not.
 * @param hTmr - IN timer handle returned in the timer start API.
 * @retval TRUE if the timer is active else FALSE
 * @note
 *    User should pass a valid timer handle.
 *****************************************************************************/
PUBLIC INLINE ULONG64
GsnSoftTmr_PeriodGet( GSN_SOFT_TMR_HANDLE_T hTmr )
{
    return ((GSN_SOFT_TMR_T*)hTmr)->period;
}

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief Shutdown the sfot timer module.
 *   Stops the hardware timer.
 *  
 *****************************************************************************/
PUBLIC VOID 
GsnSoftTmr_ShutDown( VOID );

/**
 *****************************************************************************
 * @ingroup GsnSoftTimer
 * @brief Soft Timer Expire message Handler. 
 *    This is function gets executed once the ISR posts a message to the
 *    message handler. This calls the callback function of the expired 
 *    timer(s) and start the timer with the next expire time.
 *    User has to create an instance of message handler and call this API, in 
 *    the message handler routine to handle the time expire event.
 * @note
 *    
 *****************************************************************************/
PUBLIC UINT32 
GsnSoftTmr_Run ( VOID *context, VOID *pMsg );


VOID GsnSoftTmr_Delay(UINT32 delay);

#ifdef __cplusplus
}
#endif
#endif /* _GSN_SOFT_TIMER_H_ */



