/******************************************************************************
 *
 *               COPYRIGHT (c) 2009-2010 GainSpan Corporation
 *                         All Rights Reserved
 *
 * The source code contained or described herein and all documents
 * related to the source code ("Material") are owned by Gainspan
 * Corporation or its licensors.  Title to the Material remains
 * with Gainspan Corporation or its suppliers and licensors.
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
 * Unless otherwise agreed by Gainspan in writing, you may not remove or
 * alter this notice or any other notice embedded in Materials by Gainspan
 * or Gainspan's suppliers or licensors in any way.
 *
 * $RCSfile: gsn_pwm_private.h,v $
 *
 * Description: this file define all private function
 ******************************************************************************
 */

#ifndef _GSNPWM_PRIVATE_H_
#define _GSNPWM_PRIVATE_H_




#include "drivers/pwm/gsn_pwm.h"

/**
 *******************************************************************************
 * @file gsn_pwm_private.h
 * @brief GSN PWM Private header.
 *    This file contains the private definitions of PWM module.
 ******************************************************************************/

#ifdef  __cplusplus
extern "C" {
#endif

/**
 *****************************************************************************
 * @defgroup gsnPwm_Private
 * @ingroup gsnPwm
 * The GSN timer API used to provide persistent timers.
 *****************************************************************************/


/*******************************************************************************
* Public Functions
*******************************************************************************/

/**
 *******************************************************************************
 * \internal
 * @ingroup GsnPwm_Private
 * @brief start individual pwm output.
 *    This function starts individual pwm output.
 * @param gsnPwmHandle - IN pointer to pwm handle.
 * @param eAppPwmNo - IN channel number.
 * @retval GSN_SUCCESS Operation successfull.
 * @retval GSN_PWM_INVALID_PATTERN invalid frame period.
 * @retval GSN_PWM_STATUS_BUSY channel is busy.
 * @note
 ******************************************************************************/

GSN_STATUS
GsnPwm_IndividualStart( GSN_PWM_HANDLE_T *gsnPwmHandle, GSN_PWM_NO eAppPwmNo );


/**
 *******************************************************************************
 * \internal
 * @ingroup GsnPwm_Private
 * @brief synchronized start.
 *    This function starts pwm in synchronized mode.
 * @param gsnPwmHandle - IN pointer to pwm handle.
 * @retval GSN_SUCCESS Operation successfull.
 * @note
 ******************************************************************************/

GSN_STATUS
GsnPwm_SynchronizedStart( GSN_PWM_HANDLE_T *ptGsnPwmHandle );

/**
 *******************************************************************************
 * \internal 
 * @ingroup GsnPwm_Private
 * @brief individual pattern update.
 *    This function updates pattern of individual pwm output.
 * @param gsnPwmHandle - IN pointer to pwm handle.
 * @param gsnPwmPattern - IN pointer to pwm pattern structure.
 * @param eAppPwmNo - IN channel number.
 * @retval GSN_SUCCESS Operation successfull.
 * @retval GSN_PWM_INVALID_PATTERN invalid frame period.
 * @retval GSN_PWM_STATUS_BUSY channel is busy.
 * @retval GSN_PWM_STATUS_NOTSTARTED selected channel not enabled.
 * @note
 ******************************************************************************/

GSN_STATUS 
GsnPwm_IndividualUpdate( GSN_PWM_HANDLE_T *ptThis, GSN_PWM_PATTERN_T *gsnPwmPattern,
    GSN_PWM_NO eAppPwmNo );


/**
 *******************************************************************************
 * \internal 
 * @ingroup GsnPwm_Private
 * @brief synchronized pattern upadte.
 *    This function updates pattern of synchronized pwm output.
 * @param gsnPwmHandle - IN pointer to pwm handle.
 * @param gsnPwmPattern - IN pointer to pwm pattern structure.
 * @retval GSN_SUCCESS Operation successfull.
 * @retval GSN_PWM_INVALID_PATTERN invalid frame period.
 * @retval GSN_PWM_STATUS_BUSY channel is busy.
 * @retval GSN_PWM_STATUS_NOTSTARTED selected channel not enabled.
 * @note
 ******************************************************************************/
 
GSN_STATUS
GsnPwm_SynchronizedUpdate(GSN_PWM_HANDLE_T *ptThis, GSN_PWM_PATTERN_T *gsnPwmPattern);


/**
 *******************************************************************************
 * \internal 
 * @ingroup GsnPwm_Private
 * @brief stops individual pwm output.
 *    This function stops individual pwm output.
 * @param gsnPwmHandle - IN pointer to pwm handle.
 * @param eAppPwmNo - IN pwm channel number.
 * @note
 ******************************************************************************/
 
VOID 
GsnPwm_IndividualStop( GSN_PWM_HANDLE_T *pPwmHandle, GSN_PWM_NO eAppPwmNo );


/**
 *******************************************************************************
 * \internal 
 * @ingroup GsnPwm_Private
 * @brief stops all pwm output.
 *    This function stops all pwm output.
 * @param gsnPwmHandle - IN pointer to pwm handle.
  * @note
 ******************************************************************************/

VOID 
GsnPwm_SynchronizedStop( GSN_PWM_HANDLE_T *pPwmHandle );


/**
 *******************************************************************************
 * \internal 
 * @ingroup GsnPwm_Private
 * @brief pwm ISR.
 *    This is interrupt service routine of pwm driver.
 * @param gsnPwmHandle - IN pointer to pwm handle.
 * @retval GSN_SUCCESS Operation successfu.
 * @note
 ******************************************************************************/

VOID
GsnPwm_Isr(GSN_PWM_HANDLE_T *pThis);



#ifdef  __cplusplus
    }
#endif


# endif