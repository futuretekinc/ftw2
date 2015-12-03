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
* $RCSfile: gsn_osal_threadx.h,v $
*
* Descrition : This file contains OS Abstraction layer for the threadx
*****************************************************************************/

#ifndef _GSN_OSAL_THREADX_H_
#define _GSN_OSAL_THREADX_H_


/******************************************************************************
* File inclusion
******************************************************************************/
#include "rtos/tx_api.h"
#include "rtos/tx_port.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 *****************************************************************************
 * @file gsn_osal_threadx.h
 * @brief GSN OSAL public header file for threadx.
 *    This file contains the public APIs and structures of OSAL module.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup coresvcdoc
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnOSALtx GSN OS Abstraction API (threadx)
 * @brief This module abstracts Real-Time OS functions and structures
 *
 * The functions and structures in this module provide RTOS services --
 * kernel management, interrupt management, thread management, semaphores,
 * and message queues -- in an operating-system-independent fashion.
 * Note that enumerations contain macro assignments to threadx entities
 * but the application code that calls these enumerations is independent
 * of the underlying RTOS.

******************************************************************************/
	
/**
 *****************************************************************************
 * 
 *
 * @}
 *****************************************************************************/	
	
	
	
	
/******************************************************************************
* Public data types
******************************************************************************/
/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief GSN OSAL Thread state.
 *    enum for thread state.
 *****************************************************************************/
typedef enum GSN_OSAL_THREAD_STATE_T
{
    /**< Thread is ready to run */
    GSN_OSAL_THREAD_READY = TX_READY, 
    /**< Thread is waiting on any resource */
    GSN_OSAL_THREAD_SUSPENDED = TX_SUSPENDED, 
    GSN_OSAL_THRAAD_HALTED = TX_TERMINATED /**< Thread is halted */
}THREAD_STATE_T;

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief GSN OSAL Thread initial state.
 *    enum for the initial state of the thread.
 *****************************************************************************/
typedef enum GSN_OSAL_THREAD_INITIAL_STATE_T
{
    /**< Thread created and put to ready state */
    GSN_OSAL_THREAD_INITIAL_READY = TX_AUTO_START,    
    /**< Thread is created but put into suspended state */
    GSN_OSAL_THREAD_INITIAL_SUSPENDED = TX_DONT_START 
}GSN_OSAL_THREAD_INITIAL_STATE_T;

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief GSN OSAL Thread entry function prototype.
 *    Prototype of the thread entry function.
 *****************************************************************************/
typedef VOID (*GSN_OSAL_THREAD_ENTRY_T) (UINT32 ctx);
typedef VOID (*THREADX_ENTRY_T) (ULONG);

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief GSN OSAL Wait.
 *    enum for the Wait.
 *****************************************************************************/
typedef enum GSN_OSAL_WAIT_TYPE_T
{
    GSN_OSAL_WAIT_FOREVER = TX_WAIT_FOREVER, 
    GSN_OSAL_NO_WAIT = TX_NO_WAIT
}GSN_OSAL_WAIT_TYPE_T;

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief GSN OSAL priority inheritance type.
 *    enum for the priority inheritance.
 *****************************************************************************/
typedef enum GSN_OSAL_PRI_INHERIT_TYPE
{
    GSN_OSAL_PRI_INHERIT = TX_INHERIT, 
    GSN_OSAL_PRI_NO_INHERIT = TX_NO_INHERIT
} GSN_OSAL_PRI_INHERIT_TYPE_T;


/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief GSN OSAL Thread TCB.
 *    type definition for thread TCB.
 *****************************************************************************/
typedef TX_THREAD GSN_OSAL_THREAD_TCB_T;

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief GSN OSAL Semaphore type.
 *    type definition for semaphore.
 *****************************************************************************/
typedef TX_SEMAPHORE GSN_OSAL_SEM_T;

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief GSN OSAL Queue type.
 *    type definition for Queue.
 *****************************************************************************/
typedef TX_QUEUE GSN_OSAL_QUEUE_T;

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief GSN OSAL Mutex type.
 *    type definition for Mutex.
 *****************************************************************************/
typedef TX_MUTEX GSN_OSAL_MUTEX_T;

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief GSN OSAL Event flag group type.
 *    type definition for Event flag group.
 *****************************************************************************/
typedef TX_EVENT_FLAGS_GROUP GSN_OSAL_EVENT_FLAGS_T;

typedef UINT32 GSN_OSAL_EVENT_FLAGS_VAL_T;

typedef enum GSN_OSAL_EVENT_FLAGS_OP
{
    GSN_OSAL_EVENT_FLAGS_OP_OR = 00,
    GSN_OSAL_EVENT_FLAGS_OP_OR_CLEAR = 01,
    GSN_OSAL_EVENT_FLAGS_OP_AND = 02,
    GSN_OSAL_EVENT_FLAGS_OP_AND_CLEAR = 03,
} GSN_OSAL_EVENT_FLAGS_OP_T;


/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief GSN OSAL byte pool.
 *    type definition for byte pool.
 *****************************************************************************/
typedef TX_BYTE_POOL GSN_OSAL_BYTE_POOL_T;

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief GSN OSAL block pool.
 *    type definition for block pool.
 *****************************************************************************/
typedef TX_BLOCK_POOL GSN_OSAL_BLOCK_POOL_T;


/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Disable interrupts.
 *    This function disables interrupts at ARM core level. It returns the 
 *    interrupt status register value which has to be used to enable the 
 *    interrupts again.
 * @retval intrStatus - OUT interrupt status register value. This value has to 
 *     be used in GsnOsal_IntrEnable to enable the interrupt. 
 * @note
 * @see GSN_OSAL_ENABLE_INTERRUPT
 *****************************************************************************/
INLINE INT32 
GsnOsal_IntrDisable( VOID )
{
    return tx_interrupt_control(TX_INT_DISABLE);
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Enables interrupts.
 *    This function enables interrupts at ARM core level. It takes the 
 *    interrupt status register value which was returned while disabling the 
 *    interrupts. 
 * @param intrStatus - IN interrupt status register value. This value has to 
 *     be the value returned while disabling the interrupt i.e. in 
 *     GsnOsal_IntrDisable call.
 * @note
 * @see GSN_OSAL_DISABLE_INTERRUPT
 *****************************************************************************/
INLINE VOID 
GsnOsal_IntrEnable( INT32 intrStatus )
{
    tx_interrupt_control( intrStatus );
}

#if 0
/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Lock Scheduler.
 *    This function locks the scheduler, so that no high priority thread can 
 *    run unless unlock scheduler routine is called.
 * @note
 * @see GsnOsal_SchedulerUnlock
 *****************************************************************************/
INLINE VOID 
GsnOsal_SchedulerLock( VOID )
{
    uv_preemption_disable();
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Unlock Scheduler.
 *    This function is called to unlock the scheduler to make the high pririty
 *    thread run if any in ready queue. 
 * @note
 * @see GsnOsal_SchedulerLock
 *****************************************************************************/
INLINE VOID 
GsnOsal_SchedulerUnlock( VOID )
{
    uv_preemption_enable();
}
#endif

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief RTOS initialization.
 *    This function initializes the RTOS. 
 * @note
 *    The API has to be called before calling any of the OSAL API except the 
 *    interrupt enable/disable APIs.
 *****************************************************************************/
INLINE VOID 
GsnOsal_KernelInit( VOID )
{
}
/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief RTOS Start.
 *    This function starts the RTOS. 
 * @note
 *    This API is called to start the Kernel. The control doesn't return 
 *    from this fucntion call.
 *****************************************************************************/
INLINE VOID 
GsnOsal_KernelStart( VOID ) 
{
    tx_kernel_enter();
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Thread Create.
 *    This function creates the thread. 
 * @param fptr - IN Thread entry function pointer
 * @param pCtx - IN Should be of type VOID *, this is passed when the 
 *    thread entry function is called. This can be passed as NULL.
 * @param pTcb - IN Pointer to the thread tcb.
 * @param pName - IN Thread name. 
 * @param priority - IN Should of type UINT32 and should be within 0 to 31. 
 *    Higher the value higher the priority of the thread. There cannot be two
 *    thread with the same priority.
 * @param pStack - IN Pointer to the thread stack.
 * @param stackSize - IN Size of the thread stack.
 * @param defltState - IN Should be of type STACK_STATE_T. If it is 
 *    THREAD_READY, then the thread should be ready when it is created. 
 *    If it is other than that then it should not be put in ready queue.
 * @retval 0, if it is success.
 * @note
 *    User is expected to pass valid parameter to this API.
 * @see GsnOsal_ThreadResume
 * @see GsnOsal_ThreadSuspend
 * @see GsnOsal_ThreadDelete
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_ThreadCreate(GSN_OSAL_THREAD_ENTRY_T fptr, VOID *pCtx, 
    GSN_OSAL_THREAD_TCB_T *pTcb, const UINT8* pName, UINT8 priority, 
    UINT8 *pStack, UINT32 stackSize, GSN_OSAL_THREAD_INITIAL_STATE_T defltState)
{
    UINT32 retValue = tx_thread_create( pTcb, (char *)pName, (THREADX_ENTRY_T)fptr, 
        (UINT32)pCtx, pStack, stackSize, priority, priority, TX_NO_TIME_SLICE,
        defltState);
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Thread terminate.
 *    This function is used to terminate the THREAD regardless of whether
 *    the thread is suspended or not.
 * @param pTcb - IN Pointer to the thread tcb.
 * @retval 0, if it is success.
 * @note
 *    This API should be called after the call to GsnOsal_ThreadCreate for the
 *    pTcb.
 * @see GsnOsal_ThreadDelete
 * @see GsnOsal_ThreadResume
 * @see GsnOsal_ThreadSuspend
 * @see GsnOsal_ThreadCreate
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T
GsnOsal_ThreadTerminate(GSN_OSAL_THREAD_TCB_T *pTcb)
{
    UINT32 retValue = tx_thread_terminate(pTcb);
    retValue = (retValue == TX_SUCCESS) ?
                     (UINT32)GSN_OSAL_SUCCESS :
                     (retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Thread delete.
 *    This function is used to delete the THREAD.IF the thread is not in a
 *    terminated or a completed state will return error
 * @param pTcb - IN Pointer to the thread tcb.
 * @retval 0, if it is success. 
 * @note
 *    This API should be called after the call to GsnOsal_ThreadCreate for the 
 *    pTcb.
 * @see GsnOsal_ThreadResume
 * @see GsnOsal_ThreadSuspend
 * @see GsnOsal_ThreadCreate
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_ThreadDelete(GSN_OSAL_THREAD_TCB_T *pTcb)
{
    UINT32 retValue = tx_thread_delete(pTcb);
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Thread terminate and delete.
 *    This function is used to terminate and delete the THREAD regardless of whether
 *    the thread is suspended or not.
 * @param pTcb - IN Pointer to the thread tcb.
 * @retval 0, if it is success.
 * @note
 *    This API should be called after the call to GsnOsal_ThreadCreate for the
 *    pTcb.
 * @see GsnOsal_ThreadDelete
 * @see GsnOsal_ThreadResume
 * @see GsnOsal_ThreadSuspend
 * @see GsnOsal_ThreadCreate
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T
GsnOsal_ThreadTerminateAndDelete(GSN_OSAL_THREAD_TCB_T *pTcb)
{
    UINT32 retValue = tx_thread_terminate(pTcb);
    if(retValue != TX_SUCCESS)
    {
      retValue = (retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
      return  (GSN_OSAL_ERROR_T)retValue;
    }

    retValue = tx_thread_delete(pTcb);
    retValue = (retValue == TX_SUCCESS) ?
                     (UINT32)GSN_OSAL_SUCCESS :
                     (retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}
/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Thread Run.
 *    This API is used to make the THREAD ready.
 * @param pTcb - IN Pointer to the thread tcb.
 * @retval 0, if it is success. 
 * @note
 *    This API should be called after the call to GsnOsal_ThreadCreate for the 
 *    pTcb.
 * @see GsnOsal_ThreadCreate
 * @see GsnOsal_ThreadSuspend
 * @see GsnOsal_ThreadCre
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_ThreadResume(GSN_OSAL_THREAD_TCB_T *pTcb)
{
    UINT32 retValue = tx_thread_resume(pTcb);
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}
/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Thread suspend.
 *    This function is used to suspend the THREAD.
 * @param pTcb - IN Pointer to the thread tcb.
 * @retval 0, if it is success. 
 * @note
 *    This API should be called after the call to GsnOsal_ThreadCreate for the 
 *    pTcb.
 * @see GsnOsal_ThreadCreate
 * @see GsnOsal_ThreadResume
 * @see GsnOsal_ThreadCre
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_ThreadSuspend(GSN_OSAL_THREAD_TCB_T *pTcb)
{
    UINT32 retValue = tx_thread_suspend(pTcb);
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Semaphore Create.
 *    This function is used to create the semaphore.
 * @param pSem - IN Pointer to the semaphore structure.
 * @param InitialCount - IN Initial count of the semaphore. If it is 0 then
 *    semaphore is not available, meaning acquireing before releasing it makes
 *    the thread to suspend. 
 * @note
 * @see GsnOsal_SemDelete
 * @see GsnOsal_SemAcquire
 * @see GsnOsal_SemRelease
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_SemCreate(GSN_OSAL_SEM_T *pSem, UINT32 InitialCount)
{
    UINT32 retValue = tx_semaphore_create(pSem, NULL, InitialCount);
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}
/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Semaphore Delete.
 *    This function is used to delete the semaphore.
 * @param pSem - IN Pointer to the semaphore structure.
 * @retval A error value from GSN_OSAL_ERROR_T. 
 * @note
 *    This API should be called after calling GsnOsal_SemCreate. All the 
 *    parameters should be passed correctly. Once this API is called for a 
 *    semaphore, the semaphore should not be acquired or released before 
 *    creating it again
 * @see GsnOsal_SemCreate
 * @see GsnOsal_SemAcquire
 * @see GsnOsal_SemRelease
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_SemDelete(GSN_OSAL_SEM_T *pSem)
{
    UINT32 retValue = tx_semaphore_delete(pSem);
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}
/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Semaphore Acquire.
 *    This function is used to acquire the semaphore.
 * @param pSem - IN Pointer to the semaphore structure.
 * @param waitTicks - IN value from GSN_OSAL_WAIT_TYPE_T or a value in terms of
 *    ticks to wait till it gives up. 
 * @retval A error value from GSN_OSAL_ERROR_T. 
 * @note
 *    This API should be called after calling GSN_OSAL_SEM_CREATE. All the 
 *    parameters should be passed correctly.
 * @see GsnOsal_SemCreate
 * @see GsnOsal_SemDelete
 * @see GsnOsal_SemRelease
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_SemAcquire(GSN_OSAL_SEM_T *pSem, UINT32 waitTicks)
{
    UINT32 retValue = tx_semaphore_get(pSem, waitTicks);
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}
/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Semaphore Release.
 *    This function is used to release the semaphore.
 * @param pSem - IN Pointer to the semaphore structure
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 *    This API should be called after calling GsnOsal_SemCreate. All the 
 *    parameters should be passed correctly.
 * @see GsnOsal_SemCreate
 * @see GsnOsal_SemDelete
 * @see GsnOsal_SemAcquire
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_SemRelease(GSN_OSAL_SEM_T *pSem)
{
    UINT32 retValue = tx_semaphore_put(pSem);
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Calculate Queue Message Size in words.
 * 	The message size provided during the que cerate should in terms of number of words. if the message is 
 * a structure, this API helps to calculate the message size in terms of number of words, at run time.
 * @param msgSizeInBytes - IN message size in bytes
 * @ retval - message size in number of words.
 *******************************************************************************/
INLINE UINT32
GsnOsal_QueueMsgSizeInWords(UINT32 msgSizeInBytes)
{
	/* message size should be in the order of 2^x bytes for threadx queue */
	UINT32 size = (msgSizeInBytes & 0x3)?((msgSizeInBytes >> 2)+1): (msgSizeInBytes >> 2);
    if( size < 3 )
		return size;
    if( size <= 4 )
    	return TX_4_ULONG;
    if( size > 4 && size <= 8)
    	return TX_8_ULONG;
    if( size > 8 && size <= 16 )
    	return TX_16_ULONG;
    /* Invalid input */
    return 0xFFFFFFFF;

	//return ((msgSizeInBytes & 0x3)?((msgSizeInBytes >> 2)+1): (msgSizeInBytes >> 2));
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Queue Create.
 *    This function is used to create the mailbox.
 * @param pQueue - IN Pointer to the mailbox structure.
 * @param msgSize - IN Size of the message stored in mailbox. This should be in terms of number of words
 	(4 bytes), not in terms of number of bytes.
 * @param pMsgBuff - IN Pointer to the message buffer.
 * @param msgBuffSize - IN Size of the message buffer in bytes.
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 * @ see GsnOsal_QueueMsgSizeInWords
 * @see GsnOsal_QueueDelete
 * @see GsnOsal_QueuePut
 * @see GsnOsal_QueueGet
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_QueueCreate(GSN_OSAL_QUEUE_T *pQueue, UINT32 msgSize, 
    UINT8 *pMsgBuff, UINT32 msgBuffSize)
{
    UINT32 retValue = tx_queue_create(pQueue, NULL, msgSize, 
                                        pMsgBuff, msgBuffSize);
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Queue Delete.
 *    This function is used to delete the mailbox.
 * @param pQueue - IN Pointer to the mailbox structure.
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 *    This API should be called after calling GsnOsal_QueueCreate. All the 
 *    parameters should be passed correctly.
 * @see GsnOsal_QueueCreate
 * @see GsnOsal_QueuePut
 * @see GsnOsal_QueueGet
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_QueueDelete(GSN_OSAL_QUEUE_T *pQueue)
{
    UINT32 retValue = tx_queue_delete(pQueue);
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue; 
}
/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Queue Put/Send.
 *    This function is used to put/send a message to the mailbox.
 * @param pQueue - IN Pointer to the mailbox structure.
 * @param pMsg - IN Message pointer where the message is written.
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 *    This API should be called after calling GsnOsal_QueueCreate. All the 
 *    parameters should be passed correctly.
 *    IF THE MAILBOX IS FULL THEN THE SEND REQUEST WILL FAIL AND THE CALLING 
 *    TASK DOESN'T GET SUSPENDED.
 * @see GsnOsal_QueueCreate
 * @see GsnOsal_QueueDelete
 * @see GsnOsal_QueueGet
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_QueuePut(GSN_OSAL_QUEUE_T *pQueue, UINT8 *pMsg)
{
    UINT32 retValue = tx_queue_send(pQueue, pMsg, TX_NO_WAIT);
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue; 
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Queue Get/Receive.
 *    This function is used to get/receive a message from the mailbox.
 * @param pQueue - IN Pointer to the mailbox structure.
 * @param pMsg - IN Pointer to the memory where the message is to be written 
 * from the mailbox.
 * @param waitTicks - IN value from GSN_OSAL_WAIT_TYPE_T or a value in terms of
 *    ticks to wait till it gives up. 
 * @retval A error value from GSN_OSAL_ERROR_T. 
 * @note
 *    This API should be called after calling GsnOsal_QueueCreate. All the 
 *    parameters should be passed correctly.
 * @see GsnOsal_QueueCreate
 * @see GsnOsal_QueueDelete
 * @see GsnOsal_QueueGet
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_QueueGet(GSN_OSAL_QUEUE_T *pQueue, UINT8 *pMsg, UINT32 waitTicks)
{
    UINT32 retValue = tx_queue_receive(pQueue, pMsg, waitTicks);
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue; 
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Mutex Create.
 *    This function is used to create the mutex.
 * @param pMutex - IN Pointer to the mutex structure.
 * @param priInheritance - IN priority inheritance type.
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 * @see GsnOsal_MutexDelete
 * @see GsnOsal_MutexPut
 * @see GsnOsal_MutexGet
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_MutexCreate(GSN_OSAL_MUTEX_T *pMutex, 
                    GSN_OSAL_PRI_INHERIT_TYPE_T priInheritance)
{
    UINT32 retValue = tx_mutex_create(pMutex, NULL, priInheritance);
    
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Mutex Delete.
 *    This function is used to delete the mutex.
 * @param pMutex - IN Pointer to the mutex structure.
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 *    This API should be called after calling GsnOsal_MutexCreate. All the 
 *    parameters should be passed correctly.
 * @see GsnOsal_MutexDelete
 * @see GsnOsal_MutexPut
 * @see GsnOsal_MutexGet
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_MutexDelete(GSN_OSAL_MUTEX_T *pMutex)
{
    UINT32 retValue = tx_mutex_delete(pMutex);
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue; 
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Mutex Put.
 *    This function is used to take the mutex.
 * @param pMutex - IN Pointer to the mutex structure.
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 *    This API should be called after calling GsnOsal_MutexCreate. All the 
 *    parameters should be passed correctly.
 * @see GsnOsal_MutexDelete
 * @see GsnOsal_MutexCreate
 * @see GsnOsal_MutexGet
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_MutexPut(GSN_OSAL_MUTEX_T *pMutex)
{
    UINT32 retValue = tx_mutex_put(pMutex);
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue; 
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Mutex Get.
 *    This function is used to get the mutex.
 * @param pMutex - IN Pointer to the mutex structure.
 * @param waitTicks - IN value from GSN_OSAL_WAIT_TYPE_T or a value in terms of
 *    ticks to wait till it gives up. 
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 *    This API should be called after calling GsnOsal_MutexCreate. All the 
 *    parameters should be passed correctly.
 * @see GsnOsal_MutexDelete
 * @see GsnOsal_MutexCreate
 * @see GsnOsal_MutexPut
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_MutexGet(GSN_OSAL_MUTEX_T *pMutex, UINT32 waitTicks)
{
    UINT32 retValue = tx_mutex_get(pMutex, waitTicks);
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue; 
}


/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Byte Pool Create.
 *    This function is used to create a byte pool - a pool of memory for
 *    dynamic allocation, similar to malloc.
 * @param pBytePool - IN Pointer to the byte pool structure.
 * @param pPoolStart - IN Starting pointer to pool memory.
 * @param poolSize - IN pool size in bytes.
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 * @see GsnOsal_BytePoolDelete
 * @see GsnOsal_ByteAllocate
 * @see GsnOsal_ByteRelease
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_BytePoolCreate(GSN_OSAL_BYTE_POOL_T *pBytePool, 
                        VOID *pPoolStart, UINT32 poolSize)
{
    UINT32 retValue = tx_byte_pool_create(pBytePool, NULL, pPoolStart,
                                            poolSize);
    
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Byte Pool Delete.
 *    This function is used to delete an already created byte pool.
 * @param pBytePool - IN Pointer to the byte pool structure.
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 *    This API should be called after calling GsnOsal_BytePoolCreate. All the 
 *    parameters should be passed correctly.
 * @see GsnOsal_BytePoolCreate
 * @see GsnOsal_ByteAllocate
 * @see GsnOsal_ByteRelease
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_BytePoolDelete(GSN_OSAL_BYTE_POOL_T *pBytePool)
{
    UINT32 retValue = tx_byte_pool_delete(pBytePool);
    
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Byte Allocate.
 *    This function is used to allocate memory from byte pool.
 * @param pBytePool - IN Pointer to the byte pool structure.
 * @param pMem - IN Pointer to return the pointer of allocated memory.
 * @param size - IN Size of memory to allocate.
 * @param waitTicks - IN value from GSN_OSAL_WAIT_TYPE_T or a value in terms of
 *    ticks to wait till it gives up. 
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 *    This API should be called after calling GsnOsal_BytePoolCreate. All the 
 *    parameters should be passed correctly.
 * @see GsnOsal_BytePoolCreate
 * @see GsnOsal_BytePoolDelete
 * @see GsnOsal_ByteRelease
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_ByteAllocate(GSN_OSAL_BYTE_POOL_T *pBytePool, VOID **pMem,
                        UINT32 size, UINT32 waitTicks)
{
    UINT32 retValue = tx_byte_allocate(pBytePool, pMem, size, waitTicks);
    
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Byte Release.
 *    This function is used to release the allocated memory.
 * @param pMem - IN Pointer allocated memory.
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 *    This API should be called after calling GsnOsal_BytePoolCreate. All the 
 *    parameters should be passed correctly.
 * @see GsnOsal_BytePoolCreate
 * @see GsnOsal_BytePoolDelete
 * @see GsnOsal_ByteAllocate
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_ByteRelease(VOID *pMem)
{
    UINT32 retValue = tx_byte_release(pMem);
    
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}


/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Block Pool Create.
 *    This function is used to create a block pool - a pool of memory for
 *    dynamic allocation of fixed size blocks.
 * @param pBlockPool - IN Pointer to the block pool structure.
 * @param pPoolStart - IN Starting pointer to pool memory.
 * @param poolSize - IN pool size in bytes.
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 * @see GsnOsal_BlockPoolDelete
 * @see GsnOsal_BlockAllocate
 * @see GsnOsal_BlockRelease
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_BlockPoolCreate(GSN_OSAL_BYTE_POOL_T *pBlockPool, 
                        VOID *pPoolStart, UINT32 poolSize)
{
    UINT32 retValue = tx_byte_pool_create(pBlockPool, NULL, pPoolStart,
                                            poolSize);
    
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Byte Pool Delete.
 *    This function is used to delete an already created block pool.
 * @param pBlockPool - IN Pointer to the block pool structure.
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 *    This API should be called after calling GsnOsal_BlockPoolCreate. All the 
 *    parameters should be passed correctly.
 * @see GsnOsal_BlockPoolCreate
 * @see GsnOsal_BlockAllocate
 * @see GsnOsal_BlockRelease
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_BlockPoolDelete(GSN_OSAL_BYTE_POOL_T *pBlockPool)
{
    UINT32 retValue = tx_byte_pool_delete(pBlockPool);
    
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Byte Allocate.
 *    This function is used to allocate memory from block pool.
 * @param pBlockPool - IN Pointer to the block pool structure.
 * @param pMem - IN Pointer to return the pointer of allocated memory.
 * @param size - IN Size of memory to allocate.
 * @param waitTicks - IN value from GSN_OSAL_WAIT_TYPE_T or a value in terms of
 *    ticks to wait till it gives up. 
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 *    This API should be called after calling GsnOsal_BlockPoolCreate. All the 
 *    parameters should be passed correctly.
 * @see GsnOsal_BlockPoolCreate
 * @see GsnOsal_BlockPoolDelete
 * @see GsnOsal_BlockRelease
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_BlockAllocate(GSN_OSAL_BYTE_POOL_T *pBlockPool, VOID **pMem,
                        UINT32 size, UINT32 waitTicks)
{
    UINT32 retValue = tx_byte_allocate(pBlockPool, pMem, size, waitTicks);
    
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Byte Release.
 *    This function is used to release the allocated memory.
 * @param pMem - IN Pointer allocated memory.
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 *    This API should be called after calling GsnOsal_BlockPoolCreate. All the 
 *    parameters should be passed correctly.
 * @see GsnOsal_BlockPoolCreate
 * @see GsnOsal_BlockPoolDelete
 * @see GsnOsal_BlockAllocate
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_BlockRelease(VOID *pMem)
{
    UINT32 retValue = tx_byte_release(pMem);
    
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Event flags Create.
 *    This function is used to create the event flags.
 * @param pEventFlags - IN Pointer to the mutex structure.
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 * @see GsnOsal_EventFlagsDelete
 * @see GsnOsal_EventFlagsSet
 * @see GsnOsal_EventFlagsGet
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_EventFlagsCreate(GSN_OSAL_EVENT_FLAGS_T *pEventFlags)
{
    UINT32 retValue = tx_event_flags_create(pEventFlags, NULL);
    
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue;
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Event Flags Delete.
 *    This function is used to delete the event flags.
 * @param pEventFlags - IN Pointer to the mutex structure.
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 *    This API should be called after calling GsnOsal_EventFlagsCreate. All the 
 *    parameters should be passed correctly.
 * @see GsnOsal_EventFlagsCreate
 * @see GsnOsal_EventFlagsSet
 * @see GsnOsal_EventFlagsGet
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_EventFlagsDelete(GSN_OSAL_EVENT_FLAGS_T *pEventFlags)
{
    UINT32 retValue = tx_event_flags_delete(pEventFlags);
    
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue; 
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Event Flags Put.
 *    This function is used to take the event flags.
 * @param pEventFlags - IN Pointer to the mutex structure.
 * @param eventFlagsVal - IN value to set into event flags.
 * @param eventFlagsOp - IN event flags operation, ie., specifies how the new
 *                          flags should be set.
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 *    This API should be called after calling GsnOsal_EventFlagsCreate. All the 
 *    parameters should be passed correctly.
 * @see GsnOsal_EventFlagsDelete
 * @see GsnOsal_EventFlagsCreate
 * @see GsnOsal_EventFlagsGet
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_EventFlagsSet(GSN_OSAL_EVENT_FLAGS_T *pEventFlags, 
                        GSN_OSAL_EVENT_FLAGS_VAL_T eventFlagsVal, 
                        GSN_OSAL_EVENT_FLAGS_OP_T eventFlagsOp)
{
    UINT32 retValue = tx_event_flags_set(pEventFlags, eventFlagsVal, eventFlagsOp);
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue; 
}

/**
 *****************************************************************************
 * @ingroup GsnOSALtx
 * @brief Event Flags Get.
 *    This function is used to get the event flags.
 * @param pEventFlags - IN Pointer to the event flags structure.
 * @param eventFlagsGet - IN Event Bitmask to get 
 * @param eventFlagsOp - IN Event Flag Operation
 * @param pEventFlagsVal - OUT Event Flag Value for the Bitmask requested
 * @param waitTicks - IN value from GSN_OSAL_WAIT_TYPE_T or a value in terms of
 *    ticks to wait till it gives up. 
 * @retval A error value from GSN_OSAL_ERROR_T.
 * @note
 *    This API should be called after calling GsnOsal_EventFlagsCreate. All the 
 *    parameters should be passed correctly.
 * @see GsnOsal_EventFlagsDelete
 * @see GsnOsal_EventFlagsCreate
 * @see GsnOsal_EventFlagsSet
 *****************************************************************************/
INLINE GSN_OSAL_ERROR_T 
GsnOsal_EventFlagsGet(GSN_OSAL_EVENT_FLAGS_T *pEventFlags, 
                        GSN_OSAL_EVENT_FLAGS_VAL_T eventFlagsGet,
                        GSN_OSAL_EVENT_FLAGS_OP_T eventFlagsOp,
                        GSN_OSAL_EVENT_FLAGS_VAL_T *pEventFlagsVal, 
                        UINT32 waitTicks)
{
    UINT32 retValue = tx_event_flags_get(pEventFlags, eventFlagsGet, 
                                            eventFlagsOp, (ULONG *)pEventFlagsVal, 
                                            waitTicks);
    retValue = (retValue == TX_SUCCESS) ? 
                     (UINT32)GSN_OSAL_SUCCESS : 
                     (UINT32)(retValue + (UINT32)GSN_OSAL_STATUS_CODE_START);
    return (GSN_OSAL_ERROR_T)retValue; 
}

INLINE VOID
GsnOsal_SchedulerLock(VOID)
{
	/* [TO DO]*/
}

INLINE VOID
GsnOsal_SchedulerUnlock(VOID)
{
	/* [TO DO]*/
}

#ifdef __cplusplus
}
#endif

#endif /* _GSN_OSAL_THREADX_H_ */
/*****************************************************************************/



