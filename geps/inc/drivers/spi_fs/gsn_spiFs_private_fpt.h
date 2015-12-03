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
* $RCSfile: gsn_spiFs_private_fpt.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_includes.h"

/*****************************************************************************
  *  Definitions
  ****************************************************************************/









typedef PUBLIC VOID
(*GsnSpiFS_ErrorIsr_FP_T)( GSN_SPI_FS_T *spiThis, UINT32 value );

extern _RPST_ GsnSpiFS_ErrorIsr_FP_T GsnSpiFS_ErrorIsr_FP;

typedef  PUBLIC UINT8
(*GsnSpiFS_Receive_FP_T)( GSN_SPI_FS_T *spiThis );

extern _RPST_ GsnSpiFS_Receive_FP_T GsnSpiFS_Receive_FP;

typedef  PUBLIC UINT8
(*GsnSpiFS_Transmit_FP_T)( GSN_SPI_FS_T *spiThis );

extern _RPST_ GsnSpiFS_Transmit_FP_T GsnSpiFS_Transmit_FP;

typedef PUBLIC VOID
(*GsnSpiFS_RxProcessing_FP_T)( GSN_SPI_FS_T *spiThis );

extern _RPST_ GsnSpiFS_RxProcessing_FP_T GsnSpiFS_RxProcessing_FP;

typedef PUBLIC UINT32
(*GsnSpiFS_RingBuffGet_FP_T)(GSN_SPI_FS_T *pGsnSpi,UINT8* usrBuff, UINT32 usrBuffLen );

extern _RPST_ GsnSpiFS_RingBuffGet_FP_T GsnSpiFS_RingBuffGet_FP;

typedef PUBLIC UINT8 
(*GsnSpi_Checksum_FP_T)(UINT8* headerBuff,
                    UINT8 length);
                    
extern _RPST_ GsnSpi_Checksum_FP_T GsnSpi_Checksum_FP;
                    
typedef PUBLIC UINT32
(*GsnSpi_ResponseBuffHandler_FP_T)( GSN_SPI_FS_T *spiThis,UINT8 checksum);

extern _RPST_ GsnSpi_ResponseBuffHandler_FP_T GsnSpi_ResponseBuffHandler_FP;