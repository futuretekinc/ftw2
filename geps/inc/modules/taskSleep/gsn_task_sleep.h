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
* $RCSfile: gsn_task_sleep.h,v $
*
* Description : This file contains API for task  sleep functionality.
*****************************************************************************/
/**
 *****************************************************************************
 * @file gsn_task_sleep.h
 * @brief GSN Sleep functionality implementation.
 *    This file contains the public APIs for sleep module.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnTaskUtil GSN Task Utilities  
 * @brief This module contains utilities for working with active tasks.
 * 
 ****************************************************************************/
/**
 *****************************************************************************
 * 
 *
 * @{    end Modules group inclusion
 *****************************************************************************/


/**
 *****************************************************************************
 * @ingroup GsnTaskUtil
 * @brief Sleep for given amount of time in mSec.
 *    This function function causes the calling task to sleep for specified time in milliseconds.
 * @param period  - IN amount of time to sleep specified in milliseconds. 
 * @retval GSN_FAILURE if failed else GSN_SUCCESS.
 * @note
 *    This is a blocking call.  It will come out only after specified time is elapsed. However it returns 
 *    immediately in case of failure.
 *    This function should be called only from a task context.
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnTaskSleep(UINT32 period);


