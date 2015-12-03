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
* $RCSfile: gsn_dma_fpt_1.h,v $
*
* Description : This file contains function pointer definitions for DMA .
******************************************************************************
*/
#ifndef _GSN_DMA_FPT_1_H_
#define _GSN_DMA_FPT_1_H_

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




typedef GSN_OSAL_ERROR_T
( *GsnDma_IndividualClose_FP_T) (GSN_DMA_T* ptGsnDma,UINT32 channelsToClose);

extern _RPST_ GsnDma_IndividualClose_FP_T GsnDma_IndividualClose_FP;


typedef VOID
( *GsnDma_ChannelPriAltSet_FP_T) (GSN_DMA_T* ptGsnDma,UINT32 channelsToConfigure);

extern _RPST_ GsnDma_ChannelPriAltSet_FP_T GsnDma_ChannelPriAltSet_FP;

typedef VOID
( *GsnDma_ChannelPriAltClear_FP_T) (GSN_DMA_T* ptGsnDma,UINT32 channelsToConfigure);

extern _RPST_ GsnDma_ChannelPriAltClear_FP_T GsnDma_ChannelPriAltClear_FP;

typedef UINT32
( *GsnDma_CurrentDestAddrGetPrimary_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

extern _RPST_ GsnDma_CurrentDestAddrGetPrimary_FP_T GsnDma_CurrentDestAddrGetPrimary_FP;


typedef UINT32
( *GsnDma_RemainTransferCountGetPrimary_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

extern _RPST_ GsnDma_RemainTransferCountGetPrimary_FP_T GsnDma_RemainTransferCountGetPrimary_FP;

typedef UINT32
( *GsnDma_RemainTransferCountGetAlternate_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

extern _RPST_ GsnDma_RemainTransferCountGetAlternate_FP_T GsnDma_RemainTransferCountGetAlternate_FP;

typedef UINT32
( *GsnDma_CycleTypeGetAlternate_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

extern _RPST_ GsnDma_CycleTypeGetAlternate_FP_T GsnDma_CycleTypeGetAlternate_FP;

typedef  UINT32
( *GsnDma_CycleTypeGetPrimary_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

extern _RPST_  GsnDma_CycleTypeGetPrimary_FP_T GsnDma_CycleTypeGetPrimary_FP;

typedef UINT32
( *GsnDma_specificChannelAddressPrimary_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

extern _RPST_ GsnDma_specificChannelAddressPrimary_FP_T GsnDma_specificChannelAddressPrimary_FP;

typedef UINT32
( *GsnDma_specificChannelAddressAlternate_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
extern _RPST_ GsnDma_specificChannelAddressAlternate_FP_T GsnDma_specificChannelAddressAlternate_FP;


#ifdef  __cplusplus
    }
#endif

#endif
