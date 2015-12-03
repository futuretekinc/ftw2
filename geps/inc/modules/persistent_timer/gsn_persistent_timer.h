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
* $RCSfile: gsn_persistent_timer.h,v $
*
* Description : This file contains function definations for persistent 
* Timer Driver.
*****************************************************************************/
#ifndef _GSN_PERSISTENT_TIMER_H_
#define _GSN_PERSISTENT_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* File inclusion
******************************************************************************/

/*****************************************************************************
  * Private Macros and Functions
  ****************************************************************************/

/**
 *****************************************************************************
 * @file gsn_persistent_timer.h
 * @brief GSN Soft Timer public header.
 *    This file contains the public APIs and structures of Persistent Timer 
 *    module.
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
 * @defgroup GsnPersistentTimer GSN Persistent Timer
 * @brief This module manages timers whose state persists through Standby. 
 *
 *    This group of API functions manages timers whose state can persist
 *    across Standby/Wakeup cycles. This module permits the user to manage
 *    multiple software timers based on a single hardware timer.
 *
 *    A soft timer provides timer capabilities when the system is running.
 *    Without special provisions, the state of a soft timer will be lost  
 *    in Standby. To retain the timer state through a Standby-Wakeup cycle, 
 *    GEPS provides persistent timers. Persistent timers are soft timers whose 
 *    active timer context is saved in NVRAM(defaulted to RTC) and NVDS(flash). 
 *
 *    The user can decide how many persistent timers to use. Based on this value,
 *    module functions reserve space in NVRAM and NVDS. The user must provide the 
 *    NVRAM and NVDS content reserved for this module in the init routine, and
 *    then can call the restore routine to restore all the context of the active 
 *    persistent timer(s). If a persistent timer has expired, this function calls
 *    the corresponding callback routine. In every boot, the user has to call 
 *    these two routines. Before going to Standby, the user must call the 
 *    store routine to store the context of the persistent timer into the 
 *    NVDS and NVRAM. The user must take care to copy the relevant SRAM data 
 *    into NVDS and NVRAM.
 *
 *    To create a persistent timer, the user calls Tmr_Create; to delete it, call
 *    Tmr_Delete. Tmr_Create is called only once to create a persistent timer.
 *    If deleted, the resources used by this timer are released (soft timer, 
 *    NVRAM and NVDS), so that any other persistent timer can use them. 
 *    Functions are provided to start, stop and restart a persistent
 *    timer. The user must manage the timer Id. The persistent timer module
 *    uses this timer Id as an index to the array stored in the NVRAM / NVDS 
 *    structure, so the timer Id should be between 0 and [(the maximum number
 *    of persistent timers allowed) - 1].
******************************************************************************/

/**
 *****************************************************************************
 * 
 * @}
 *****************************************************************************/	
	
	
	
	
/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief Memory needed in NVDS for persistent timer module.
 *
 *    MACRO to get NVDS memory size for the persistent timer module for a 
 *    given number of persistent timers.
 *
 *    User can allocate memory of this size in NVDS using this MACRO.
 *
 *    Here NVDS is refered to flash memory. The information which rarely 
 *    changes are written to this segment.
 *****************************************************************************/
#define GSN_P_TMR_NVDS_MEM_SIZE( maxNumOfPTmr )                     \
    ( 2 * sizeof( UINT32 )) +                                       \
    (( maxNumOfPTmr ) *                                             \
        ( sizeof( GSN_SOFT_TMR_CALLBACK_T ) + sizeof( ULONG64 )))

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief Memory needed in NVRAM for persistent timer module.
 *
 *    MACRO to get NVRAM memory size for the persistent timer module for a 
 *    given number of const and variable persistent timer.
 *
 *    User can allocate memory of this size in NVRAM using this MACRO. 
 *
 *    Here NVRAM is refered to RTC memory in our case. The information which  
 *    changes frequenty and need to be retained over standby wakeup cycle are 
 *    written to this segment.
 *****************************************************************************/
#define GSN_P_TMR_NVRAM_MEM_SIZE( maxNumOfConstPTmr, maxNumOfVarPTmr )  \
    sizeof( UINT32 ) +                                                  \
    ( sizeof( ULONG64 ) * ( maxNumOfVarPTmr )) +                        \
    ((( maxNumOfConstPTmr ) + ( maxNumOfVarPTmr )) * sizeof( ULONG64 ))

/******************************************************************************
* Public data types
******************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief Persistent Timer type definition.
 *
 * A Persistent Constant timer's state can persist during Standby, but the timeout value  
 * can only be changed if we update the timeout in NVDS.
 *
 * A Persistent Variable timer's state persists during Standby, and the timeout value  
 * can be changed in any wakeup cycle. This timer starts with the value 
 * provided in the Create function, and the period of the timer is stored into NVDS. 
 * The timeout can be changed without updating the NVDS, unlike 
 * GSN_TIMER_TYPE_PERSISTENT_CONSTANT timer. 
 * If a persistent timer has to be started with different period frequently 
 * then user should use this timer type, but a variable timer uses 64 bits
 * of NVRAM!  There is not enough room many variable timers; use only when needed.
 *    
 *****************************************************************************/
typedef enum GSN_P_TIMER_TYPE_T
{ 
      
    GSN_TIMER_TYPE_PERSISTENT_CONSTANT,

    GSN_TIMER_TYPE_PERSISTENT_VARIABLE
  
} GSN_P_TIMER_TYPE_T;

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief enum for the reference time for the re-start API.
 *
 *    Reference time to restart the timer. If GSN_TMR_CURRENT_TIME is choosed 
 *    then the timer is restarted with the period from the current time. If
 *    GSN_TMR_PREV_EXP_TIME is choosed then timer is started from the previous  
 *    expire time, and the callback is called after Nth period such that
 *
 *        PrevExpTime + N*Period > CurrentTime, where PrevExpTime is the 
 *        previous expire time and period is the period passed in the 
 *        Restart API.
 *****************************************************************************/
typedef enum GSN_P_TMR_REF_TIME
{
    GSN_P_TMR_CURRENT_TIME,  
    GSN_P_TMR_PREV_EXP_TIME,  
}GSN_P_TMR_REF_TIME_T;



/******************************************************************************
* Public variable
******************************************************************************/

/******************************************************************************
* Public Function
******************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief Initialization for Persistent Timer module.
 *
 *    This function performs initialization of Persistent timer module.
 * @param pNvRamLoc - IN SRAM loc where the NVRAM details for this module is 
 *    stored.
 * @param pNvdsLoc - IN SRAM loc where the NVDS detaild for this module is 
 *    stored.
 * @param numOfVarTimer - IN Number of varibale timer the user wants.
 * @param numOfConstTimer - IN Number of const timer the user wants.
 * @param pSoftTmrStructTbl - IN Pointer to the soft timer table which would be
 *    used to start/stop soft timers. The size of the memory buffer should be 
 *    sizeof( GSN_SOFT_TMR_T ) * ( numOfVarTimer + numOfConstTimer ).
 * @note
 *    This function must be called after calling the initialization function of
 *    the soft timer module.
 *****************************************************************************/
PUBLIC VOID 
GsnPersistTmr_Init( VOID* pNvRamLoc, VOID *pNvdsLoc, UINT32 numOfVarTimer, 
    UINT8 numOfConstTimer, GSN_SOFT_TMR_T *pSoftTmrStructTbl );

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief Persistent timer restore.
 *
 *    Loads the Persistent timer details from the NVDS and NVRAM to the SRAM  
 *    in GSN_SOFT_TMR_T format. And calls callback function of the expired  
 *    persistent timers.
 * @note
 *    This calls the callback function of the expired timer and starts the 
 *    timer.
 *****************************************************************************/
PUBLIC VOID 
GsnPersistTmr_Restore( VOID );

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief Persistent timer Store.
 *
 *    Updates the information that has to be stored in NVRAM section and into 
 *    the NVDS if there is any change in the NVDS data. It return TRUE if NVDS
 *    section has changed.
 *****************************************************************************/
PUBLIC BOOL 
GsnPersistTmr_Store( VOID );

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief Create a Persistent Timer.
 *
 *    This function creates a persistent timer.
 * @param timerId - IN ID of the timer to create. It should be less than the 
 *    maximum persistenet timer supported i.e. numOfVarTimer + numOfConstTimer 
 *    - 1 passed in GsnPersistTmr_Init API.
 * @param type - IN Type of the persistent timer.
 * @param period - IN period of the persistent timer.
 * @param cb - IN Callback function of the timer.
 * @param context - IN Context to be passed in the callback function.
 * @param autoStart - IN Starts the timer if passed true.
 * @note
 *    This API is called to give the callback information and the period to 
 *    the persistent timer module. This API is expected to be called when the
 *    cb and context changes, i.e. after doing FWUP(Firmware upgrade).
 *
 *    If autoStart is passed TRUE then the persistent timer is started 
 *    automatically, else user has to call GsnPersistTmr_Start to explictly 
 *    start it. Once started, the cb is called when the timer expires, and 
 *    the persistent timer starts running when GsnPersistTmr_Init is called
 *    after every wakeup. If any persistent timer has expired when 
 *    GsnPersistTmr_Init is called, the cb of the corresponding persistent 
 *    timer is called.
 *
 *    User has to manage the timer Id. 
 *****************************************************************************/
PUBLIC GSN_STATUS 
GsnPersistTmr_Create( UINT32 timerId, GSN_P_TIMER_TYPE_T type, ULONG64 period, 
    GSN_SOFT_TMR_CBR_T cb, VOID* context, BOOL autoStart );

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief Deletes a Persistent Timer.
 *
 *    This function deletes a persistent timer.
 * @param timerId - IN ID of the timer to create. It should be less than the 
 *    maximum persistenet timer supported i.e. numOfVarTimer + numOfConstTimer 
 *    - 1 passed in GsnPersistTmr_Init API.
 * @note
 *    This API is called to delete a persistent timer. Once deleted the timer
 *    Id can be reused and the NVRAM and NVDS resource can be reused for some
 *    other timer.
 *****************************************************************************/
PUBLIC GSN_STATUS 
GsnPersistTmr_Delete( UINT32 timerId );

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief Start the Persistent Timer.
 *
 *    This function starts a persistent timer.
 * @param timerId - IN ID of the timer to create. It should be less than the 
 *    maximum persistenet timer supported i.e. numOfVarTimer + numOfConstTimer 
 *    - 1 passed in GsnPersistTmr_Init API.
 * @note
 *    It is assumed that the input parameter passed is correct.
 *****************************************************************************/
PUBLIC GSN_STATUS 
GsnPersistTmr_Start( UINT32 timerId );

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief Stop the Persistent Timer.
 *
 *    This function stops a persistent timer.
 * @param timerId - IN ID of the timer to create. It should be less than the 
 *    maximum persistenet timer supported i.e. numOfVarTimer + numOfConstTimer 
 *    - 1 passed in GsnPersistTmr_Init API.
 * @note
 *    It is assumed that the input parameter passed is correct.
 *****************************************************************************/
PUBLIC GSN_STATUS 
GsnPersistTmr_Stop( UINT32 timerId );

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief Re-starts a Persistent Timer.
 *
 *    This function re-starts a persistent timer. This API is mainly used to 
 *    change the period of the persistent timer if the timer is already active 
 *    or to start the timer if it is de-active. In case of persistent const 
 *    timer the change in period triggers a NVDS write. 
 * @param timerId - IN ID of the timer to re-start. It should be less than the 
 *    maximum persistenet timer supported i.e. numOfVarTimer + numOfConstTimer
 *    passed in GsnPersistTmr_Init API.
 * @param period - Period in system ticks
 * @param refTime - Reference time to restart the timer. If 
 *    GSN_P_TMR_CURRENT_TIME is passed then the timer is restarted with the  
 *    period from the current time. If GSN_P_TMR_PREV_EXP_TIME is passed then  
 *    timer is started from the previous expire time, and the callback is 
 *    called after Nth period such that 
 *          PrevExpTime + N * Period > CurrentTime, 
 *          where "PrevExpTime" is the previous expire time,
 *          "N" is any integer value and 
 *          "period" is the period passed in this API.
 *
 * @note
 *    This API is expected to be called for a persistent timer, only if the
 *    persistent timer is already started. It returns error if it is do so. A 
 *    persistent timer is assumed to be started if the start API is called 
 *    once in any boot or create API is called with autoStart TRUE. 
 *    It is assumed that all the input parameters are passed correctly.
 *****************************************************************************/
PUBLIC GSN_STATUS 
GsnPersistTmr_ReStart( UINT32 timerId, ULONG64 period,
    GSN_P_TMR_REF_TIME_T refTime );

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief System time at expire.
 *    Gives the system time at expire for the requested persistent timer.
 * @param timerId - IN ID of the timer. It should be less than the maximum 
 *    persistenet timer supported i.e. numOfVarTimer + numOfConstTimer
 *    passed in GsnPersistTmr_Init API.
 * @retval Remaining time in timer ticks
 * @note
 *
 *****************************************************************************/
PUBLIC ULONG64
GsnPersistTmr_SystemTimeAtExpire( UINT32 timerId );

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief Persistent Timer remaining time.
 *    Gives the remaining time to expire for the requested persistent timer.
 * @param timerId - IN ID of the timer. It should be less than the maximum 
 *    persistenet timer supported i.e. numOfVarTimer + numOfConstTimer
 *    passed in GsnPersistTmr_Init API.
 * @retval Remaining time in timer ticks
 * @note
 *
 *****************************************************************************/
PUBLIC ULONG64
GsnPersistTmr_RemainingTimeGet( UINT32 timerId );

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief Minimum expire time of all persistenet timer.
 *    Gives the min expire time of all persistent timer.
 * @retval Remaining time in timer ticks
 * @note
 *
 *****************************************************************************/
PUBLIC ULONG64
GsnPersistTmr_MinExpireTime();

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief Timer is active or not.
 *    Finds whether the requested persistent timer is active.
 * @param timerId - IN ID of the timer. It should be less than the maximum 
 *    persistenet timer supported i.e. numOfVarTimer + numOfConstTimer
 *    passed in GsnPersistTmr_Init API.
 * @retval TRUE if active else FALSE.
 * @note
 *
 *****************************************************************************/
PUBLIC BOOL
GsnPersistTmr_IsActive( UINT32 timerId );

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief Period of the persistent timer.
 *    Gives the current period of the requested persistent timer. The period 
 *    of the variable persistent timer may be different then the period with 
 *    which it was created or started.
 * @param timerId - IN ID of the timer. It should be less than the maximum 
 *    persistenet timer supported i.e. numOfVarTimer + numOfConstTimer
 *    passed in GsnPersistTmr_Init API.
 * @retval Remaining time in timer ticks
 * @note
 *
 *****************************************************************************/
PUBLIC ULONG64
GsnPersistTmr_PeriodGet( UINT32 timerId );

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief Default period of the persistenet timer.
 *    Gives the period stores in NVDS for the requested persistent timer. 
 *    This is useful for variable persistent timer type to find the period 
 *    passed when it was created or started..
 * @param timerId - IN ID of the timer. It should be less than the maximum 
 *    persistenet timer supported i.e. numOfVarTimer + numOfConstTimer
 *    passed in GsnPersistTmr_Init API.
 * @retval Remaining time in timer ticks
 * @note
 *
 *****************************************************************************/
PUBLIC ULONG64
GsnPersistTmr_DfltPeriodGet( UINT32 timerId );

/**
 *****************************************************************************
 * @ingroup GsnPersistentTimer
 * @brief Set default period of the persistenet timer.
 *    Chnages the default period. It stores the period in NVDS, If it is set 
 *    to 0, the timer is stopped, else it is restarted with the set value 
 *    maintaining the previous reference time.
 * @param timerId - IN ID of the timer. It should be less than the maximum 
 *    persistenet timer supported i.e. numOfVarTimer + numOfConstTimer
 *    passed in GsnPersistTmr_Init API.
 * @param period - IN Period to Set
 * @retval none
 * @note
 *
 *****************************************************************************/
PUBLIC VOID
GsnPersistTmr_DfltPeriodSet( UINT32 timerId, ULONG64 period );

#ifdef __cplusplus
}
#endif
#endif /* _GSN_PERSISTENT_TIMER_H_ */





