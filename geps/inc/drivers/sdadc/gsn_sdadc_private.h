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
 * $RCSfile: gsn_sdadc_private.h,v $
 *
 * Description: this file define all private function
 ******************************************************************************
 */
#ifndef _GSN_SDADC_PRIVATE_H_
#define _GSN_SDADC_PRIVATE_H_


#ifdef  __cplusplus
extern "C" {
#endif

/*****************************************************************************
* File inclusion
****************************************************************************/

#include "gsn_includes.h"
#include "sdadc\gsn_sdadc.h "




/*****************************************************************************
* Type Definitions
****************************************************************************/


/*****************************************************************************
*  Public variable
*****************************************************************************/
/**
*****************************************************************************
* \internal
* @file gsn_sdadc_private.h
* @brief GSN SDADC Private Function Header.
*    This file contains low-level functions not normally exposed to the app.
****************************************************************************/


#if 0
/**
 *****************************************************************************
 * \internal
 * @ingroup GsnSdadcPrivate
 * @brief    SDADC Sync Semaphore
 *    This semaphore is used to for synchronous API calls. For example if the read
 *    is synchronous, then this semaphore is held until read is complete and then
 *    only the API reading returns.
 ****************************************************************************/
 PUBLIC GSN_OSAL_SEM_T sdadcSyncSemId;
#endif


/**
 *****************************************************************************
 * \internal
 * @ingroup GsnSdadcPrivate
 * @brief ISR SDADC FIFO FULL Operation
 *   
 *
 * @param sdadcHandle           IN     pointer to handle.
 *
 * @return none
 *
 ****************************************************************************/
 VOID
GsnSdadc_IsrAdcFifoFull(GSN_SDADC_HANDLE_T *sdadcHandle);



/**
 *****************************************************************************
 * \internal
 * @ingroup GsnSdadcPrivate
 * @brief ISR for ADC FIFO Overflow Operation
 *
 * @param sdadcHandle           IN     pointer to handle.
 *
 * @return none
 *
 *****************************************************************************/
VOID
GsnSdadc_IsrAdcFifoOverFlow( GSN_SDADC_HANDLE_T *sdadcHandle );


/**
 *****************************************************************************
 * \internal
 * @ingroup GsnSdadcPrivate
 * @brief ISR for DAC FIFO Empty Operation
 *  
 *
 * @param sdadcHandle           IN     pointer to handle.
 *
 *
 *****************************************************************************/
UINT16
GsnSdadc_IsrDacFifoEmpty(GSN_SDADC_HANDLE_T *sdadcHandle);
/**
 *****************************************************************************
 * \internal
 * @ingroup GsnSdadcPrivate
 * @brief ISR for SDADC DAC FIFO underflow Operation
 *   
 
 * @param sdadcHandle           IN     pointer to handle.
 *
 * 
 *
 *****************************************************************************/
UINT16
GsnSdadc_IsrDacFifoFull(GSN_SDADC_HANDLE_T *sdadcHandle);




#ifdef  __cplusplus
        }
#endif

#endif /* _GSN_SDADC_PRIVATE_H_ */

