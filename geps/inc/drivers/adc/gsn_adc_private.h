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
 * $RCSfile: gsn_adc_private.h,v $
 *
 * Description: this file define all private function
 ******************************************************************************
 */
#ifndef _GSN_AADC_PRIVATE_H_
#define _GSN_AADC_PRIVATE_H_


#ifdef  __cplusplus
extern "C" {
#endif

/*****************************************************************************
* File inclusion
****************************************************************************/

#include "gsn_includes.h"
//#include "buffer.h"
#include "adc\gsn_adc.h "



/*****************************************************************************
* Type Definitions
****************************************************************************/


/*****************************************************************************
*  Public variable
*****************************************************************************/
/**
*****************************************************************************
* \internal
* @file gsn_adc_private.h
* @brief GSN AADC Private Function Header.
*    This file contains low-level functions not normally exposed to the app.
****************************************************************************/



/**
 *****************************************************************************
 * \internal
 * @ingroup GsnAdcPrivate
 * @brief    AADC Sync Semaphore
 *    This semaphore is used to for synchronous API calls. For example if the read
 *    is synchronous, then this semaphore is held until read is complete and then
 *    only the API reading returns.
 ****************************************************************************/
extern PUBLIC GSN_OSAL_SEM_T   adcSyncSemId;



/**
 *****************************************************************************
 * \internal
 * @ingroup GsnAdcPrivate
 * @brief ISR AADC FIFO Data Available Operation
 *     This function is called by ISR if there is data left in
 *     FIFO. If the measurement is started by GsnAadc_Read, then after all
 *     the samples have been read, it calls the callback function if it is
 *     registered; if not, it releases the sync semaphore (for synchronous calls).
 *
 *
 * @param aadcHandle           IN     pointer to handle.
 *
 * @return none
 *
 ****************************************************************************/
PUBLIC VOID
GsnADC_IsrFifoNotEmpty(GSN_ADC_HANDLE_T *adcHandle);



/**
 *****************************************************************************
 * \internal
 * @ingroup GsnAdcPrivate
 * @brief ISR for AADC FIFO Overflow Operation
 *    This function is called from ISR when the data that remains in FIFO is
 *    above a threshold. It serves the FIFO overflow interrupt request. It
 *    also clears the requests and executes the callback function.
 *
 * @param aadcHandle           IN     pointer to handle.
 *
 * @return none
 *
 *****************************************************************************/
PUBLIC VOID
GsnADC_IsrOverFlow( GSN_ADC_HANDLE_T *adcHandle );



#ifdef  __cplusplus
        }
#endif

#endif /* _GSN_ADC_PRIVATE_H_ */
