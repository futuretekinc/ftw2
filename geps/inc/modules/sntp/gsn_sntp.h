/*******************************************************************************
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
* $RCSfile: gsn_sntp.h,v $
*
* Description : This file contains SNTP API.
*******************************************************************************/
#ifndef _GSN_SNTP_H_
#define _GSN_SNTP_H_

#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
* File Inclusion
********************************************************************************/
#include "gsn_types.h"
#include "gsn_defines.h"
//#include "gsn_includes.h"


    
/**
 *******************************************************************************
 * @file gsn_sntp.h
 * @brief GSN SNTP public header.
 *    This file contains the public APIs and structures of SNTP module.
 ******************************************************************************/


/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/


/**
 *******************************************************************************
 * @defgroup GsnSntp GSN Simple Network Time Protocol 
 * @brief  SNTP functions.
 *
 *    This file contains public definitions and functions for 
 *    synchronizing TSync time with a specified SNTP server. <br>
 *
 *   <br>
 *   The TSync block, low- and high-power clocks, and associated 
 *   platform software provide a clock that can be synchronized to an external reference by adjusting 
 *   the offset value, and will thereafter maintain synchronization despite sojourns in power-conserving states.
 *   In order to have System Time accurately reflect absolute calendar time, it is merely necessary
 *   to add a means of establishing the value of the offset.  GEPS versions 2.0 and above support the 
 *   use of SNTP for this purpose.  The API function GsnSntp_TimeSync() sends a Time Request to a 
 *   known server address (using the function GsnSntp_Send()), and registers a callback function to
 *   handle the Time Response when it is received.  The callback function (GsnSntp_SocketCb()) 
 *   extracts the difference between the SNTP time and the System Time, and corrects System Time 
 *   for this difference.  The calling application may also pass in its own callback function,
 *   to be launched once the time difference has been established.  <br>
 *    <br>
 *   In setting System Time, the calling application must take into account other activities 
 *   that may depend on the absolute value of System Time.  For example, any soft timers that 
 *   are active will be affected by a Sys-tem Time offset; if the timers are intended to mark
 *   relative rather than absolute times, their values must be reset.  Other relative times, such
 *   as the duration of a DHCP lease, may also need to be adjusted.  The User Application must 
 *   attend to these issues if it adjusts System Time as a consequence of an SNTP synchronization.  
 *
 ******************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/


/*****************************************************************************
 * Public Definitions
 *****************************************************************************/
	
/**
 *******************************************************************************
 * @ingroup GsnSntp 
 * @brief SNTP context structure.
 *        This structure contains the parameters that define an instance of the 
 *        SNTP object.
 *
 ******************************************************************************/
typedef struct GSN_SNTP_CTX
{
    UINT32 serverIpAddr;               /**< Server IP Address */
    GSN_SOFT_TMR_HANDLE_T recvTmrHndl; /**< Receive Timer Handle */
    GSN_SOFT_TMR_T recvTmr;            /**< Receive Timer */
    INT32 sockDesc;                    /**< Socket Descriptor */
    GSN_NOTIFICATION_FUNC_T cb;        /**< Callback Function */
    VOID *cbCtx;                       /**< Context for Callback Function */
    ULONG64 timeDiff;                  /**< Time Difference */
    BOOL diffNegative;                 /**< Difference is additive or negative */
    BOOL sntpDone;                     /**< Flag for SNTP Done */
    GSN_WDD_CTX_T  *pWdd; 
} GSN_SNTP_CTX_T;


/*******************************************************************************
  * Private Macros and Functions
  ******************************************************************************/



/*******************************************************************************
 * Public Functions
 ******************************************************************************/


/**
 *******************************************************************************
 * @ingroup GsnSntp
 * @brief Synchronize time with server.
 * 
 *    This function performs time synchronization with the given SNTP server. It
 *    does not adjust the system time but just gets the server time and computes
 *    the time difference. It is up to application to adjust the time after the
 *    successful callback.
 * @param sntpCtx - IN Pointer to SNTP context provided by user.
 * @param serverIpAddr - IN Server IP address.
 * @param serverTimeout - IN time in seconds to wait for server response.
 * @param cb - IN Function that will be called to notify the result.
 * @param cbCtx - IN User context that will be passed back in callback.
 * @retval GSN_FAILURE Operation failed.
 * @retval GSN_OPERATION_IN_PROGRESS Operation in progress. Callback function
 *                                  will be called to indicate the result.
 * @note
 *    If this function returns anything other than GSN_OPERATION_IN_PROGRESS,
 *    then the API execution is complete and callback will not be called. If
 *    GSN_OPERATION_IN_PROGRESS is returned, then the callback will be called
 *    after the operation is complete to indicate the final result.
 * @note
 *    The callback function is called after the operation is complete or upon
 *    timeout (20sec). If the callback status is GSN_FAILURE, then it indicates
 *    timeout. If the callback status is GSN_SUCCESS, then it indicates the
 *    server response was received and the time difference can be obtained by
 *    calling GsnSntp_TimeDiffGet.
 ******************************************************************************/
PUBLIC GSN_STATUS 
GsnSntp_TimeSync(GSN_SNTP_CTX_T *sntpCtx, UINT32 serverIpAddr, 
                    UINT32 serverTimeout, GSN_NOTIFICATION_FUNC_T cb,
                    VOID *cbCtx);


/**
 *******************************************************************************
 * @ingroup GsnSntp
 * @brief Get adjustment time value.
 * 
 *    This function gives the time adjustment value and whether the adjustment
 *    is negative or positive.
 * @param sntpCtx - IN Pointer to SNTP context provided by user.
 * @param pTimeDiff - OUT Pointer to time difference value.
 * @param pDiffNegative - OUT Pointer to a BOOL for returning the adjustment
 *                            type, positive or negative.
 ******************************************************************************/
PUBLIC INLINE VOID
GsnSntp_TimeDiffGet(GSN_SNTP_CTX_T *sntpCtx, ULONG64 *pTimeDiff,
                    BOOL *pDiffNegative)
{
    *pTimeDiff = sntpCtx->timeDiff;
    *pDiffNegative = sntpCtx->diffNegative;
}


VOID
GsnSntp_ServerRespTmrCb(VOID* pCtx, UINT32 tmrHndl);

VOID
GsnSntp_SocketCb(INT32 sockDesc, NX_BSD_CB_EVENT_TYPE_T flags,  VOID *pCtx);
#ifdef __cplusplus
}
#endif
#endif /* _GSN_SNTP_H_ */




