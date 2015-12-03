/******************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
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
* $RCSfile: gsn_spi_private_fpt.h,v $
*
* Description : This file contains private functions patch definitions.
*****************************************************************************/

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_includes.h"

/*****************************************************************************
  *  Definitions
  ****************************************************************************/
typedef VOID
(*GsnSpi_ErrorIsr_FP_T)( GSN_SPI_T *spiThis,
                           UINT32 value );
extern _RPST_   GsnSpi_ErrorIsr_FP_T GsnSpi_ErrorIsr_FP;

typedef UINT8
(* GsnSpi_InitialTransmit_FP_T) (GSN_SPI_T *spiThis );
extern _RPST_   GsnSpi_InitialTransmit_FP_T GsnSpi_InitialTransmit_FP;

typedef UINT8
(* GsnSpi_Receive_FP_T)( GSN_SPI_T *spiThis );
extern _RPST_   GsnSpi_Receive_FP_T GsnSpi_Receive_FP;

typedef UINT8
(* GsnSpi_Transmit_FP_T)( GSN_SPI_T *spiThis );
extern _RPST_   GsnSpi_Transmit_FP_T GsnSpi_Transmit_FP;

typedef VOID
(*GsnSpi_Dma_Transmit_FP_T)( GSN_SPI_T *spiThis );
extern _RPST_   GsnSpi_Dma_Transmit_FP_T GsnSpi_Dma_Transmit_FP;

typedef VOID
(* GsnSpi_Dma_Receive_FP_T)( GSN_SPI_T *spiThis );
extern _RPST_   GsnSpi_Dma_Receive_FP_T GsnSpi_Dma_Receive_FP;

typedef VOID
(* GsnSpi_TxProcessing_FP_T)( GSN_SPI_T *spiThis );
extern _RPST_   GsnSpi_TxProcessing_FP_T GsnSpi_TxProcessing_FP;

typedef VOID
(* GsnSpi_RxProcessing_FP_T)( GSN_SPI_T *spiThis );
extern _RPST_   GsnSpi_RxProcessing_FP_T GsnSpi_RxProcessing_FP;

typedef UINT8
(*GsnSpi_ByteDeStuff_FP_T)(UINT8 *pNextData);

extern _RPST_ GsnSpi_ByteDeStuff_FP_T GsnSpi_ByteDeStuff_FP;

typedef UINT32
( *GsnSpi_RingBuffGet_FP_T)(GSN_SPI_T *pGsnSpi,UINT8* usrBuff, UINT32 usrBuffLen );

extern _RPST_ GsnSpi_RingBuffGet_FP_T GsnSpi_RingBuffGet_FP;


typedef VOID
( *GsnSpi_UsrBuffPutFromRbuffer_FP_T)(GSN_SPI_T *spiThis);

extern _RPST_ GsnSpi_UsrBuffPutFromRbuffer_FP_T GsnSpi_UsrBuffPutFromRbuffer_FP;

typedef UINT8
(*GsnSpi_ByteStuff_FP_T)(UINT8 *pNextData);
extern _RPST_ GsnSpi_ByteStuff_FP_T GsnSpi_ByteStuff_FP;

typedef UINT8
(*GsnSpi_TxDataGet_FP_T)(GSN_SPI_T *ptGsnSpi,UINT8* ptUsrBuff);
extern _RPST_ GsnSpi_TxDataGet_FP_T GsnSpi_TxDataGet_FP;