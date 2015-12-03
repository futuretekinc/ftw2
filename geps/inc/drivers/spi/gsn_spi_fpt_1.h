/****************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
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
* $RCSfile: gsn_spi_fpt_1.h,v $
*
* Description : This file contains public functions patch definitions for SPI.
******************************************************************************
*/
#ifndef _GSN_SPI_FPT1_H_
#define _GSN_SPI_FPT1_H_

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************************************************
*  File inclusion
*****************************************************************************/

#include "drivers/spi_fs/buffer.h"
#include "gsn_includes.h"
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"



/*****************************************************************************
* Public Function
******************************************************************************/


/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Driver open.
 *
 *    This function initializes the specified SPI port, with required
 *    configuration parameters provided in GSN_SPI_CONFIG_T. This
 *    function also initializes the pointer "spiHandle " and creates
 *    the synchronous semaphore.
 * @param spiHandle           - IN pointer to handle.
 * @param spiPortNumber       - IN SPI port number. see GSN_SPI_NUM_T
 *
 * @return GSN_SUCCESS        - Initialization successful.
 * @return GSN_FAILURE        - Initialization failed.
 *
  ****************************************************************************/
typedef GSN_STATUS
( *GsnFSpi_OpenFP_T)( GSN_SPI_HANDLE_T *spiHandle,
             GSN_SPI_NUM_T spiPortNumber, GSN_SPI_CONFIG_T* gsnSpiConfig);
extern _RPST_ GsnFSpi_OpenFP_T GsnFSpi_OpenFP;

typedef VOID
(* GsnSpi_PauseRingBuff_FP_T)(GSN_SPI_HANDLE_T *spiHandle );

extern _RPST_ GsnSpi_PauseRingBuff_FP_T GsnSpi_PauseRingBuff_FP;


typedef VOID
( *GsnSpi_ResumeRingBuff_FP_T)(GSN_SPI_HANDLE_T *spiHandle);

extern _RPST_ GsnSpi_ResumeRingBuff_FP_T GsnSpi_ResumeRingBuff_FP;


typedef VOID
( *GsnSpi_FlushRingBuff_FP_T)(GSN_SPI_HANDLE_T *spiHandle);

extern _RPST_ GsnSpi_FlushRingBuff_FP_T GsnSpi_FlushRingBuff_FP;






#ifdef  __cplusplus
    }
#endif

#endif
