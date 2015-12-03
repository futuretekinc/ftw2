/******************************************************************************
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
*
* $RCSfile: gsn_spi_private.h,v $
*
* Description : This file contains private functions and definitions for
*               SPI driver
********************************************************************************
*/
#ifndef _GSN_SPI_PRIVATE_H_
#define _GSN_SPI_PRIVATE_H_

#ifdef  __cplusplus
extern "C" {
#endif
  
  
/****************************************************************************
*  File inclusion
*****************************************************************************/
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
//#include "Gsn_Spi.h"

/**
 *****************************************************************************
 * @file gsn_spi_private.h
 * @brief GSN SPI API definitions.
 *    This file contains the private (low-level) definitions and
 *    structures for the SPI driver.
 ****************************************************************************/

/**
 *****************************************************************************
 * 
 ****************************************************************************/

/*****************************************************************************
* MACRO
*****************************************************************************/


/*****************************************************************************
*  Public variable
******************************************************************************/


/*****************************************************************************
* Type Definitions
****************************************************************************/

/**
*****************************************************************************
* \internal
* @ingroup GsnSpi
* @brief SPI isr call on receive or transfer error
*    This function gets called from ISR on receive or transfer error
*
* @param spiThis       - IN pointer to data and callback function
* @param value         - IN error type
*
* @return none
*****************************************************************************/
VOID
GsnSpi_ErrorIsr( GSN_SPI_T *spiThis, UINT32 value );


/**
*****************************************************************************
* \internal
* @ingroup GsnSpi
* @brief SPI initial transmit
*    This function gets called Master or Slave ReadWrite
* @param spiThis        - IN pointer to data and callback function
*
* @return UINT8
*****************************************************************************/
UINT8 
GsnSpi_InitialTransmit( GSN_SPI_T *spiThis );

/**
*****************************************************************************
* \internal
* @ingroup GsnSpi
* @brief SPI DMA Rx call 
*    
* @param spiThis        - IN pointer to data and callback function

* @return none
*****************************************************************************/

VOID
GsnSpi_Dma_Receive( GSN_SPI_T *spiThis );

/**
*****************************************************************************
* \internal
* @ingroup GsnSpi
* @brief SPI DMA Tx call 
*    
* @param spiThis        - IN pointer to data and callback function

* @return none
*****************************************************************************/

VOID
GsnSpi_Dma_Transmit( GSN_SPI_T *spiThis );

/**
*****************************************************************************
* \internal
* @ingroup GsnSpi
* @brief SPI isr call on transmit event processing
*    
* @param spiThis        - IN pointer to data and callback function

* @return none
*****************************************************************************/

VOID 
GsnSpi_TxProcessing( GSN_SPI_T *spiThis );


/**
*****************************************************************************
* \internal
* @ingroup GsnSpi
* @brief SPI isr call on recieve event processing
*    
* @param spiThis        - IN pointer to data and callback function

* @return none
*****************************************************************************/

VOID 
GsnSpi_RxProcessing( GSN_SPI_T *spiThis );
/**
*****************************************************************************
* \internal
* @ingroup GsnSpi
* @brief SPI read write using dma scatter gather cycle.
*    
* @param spiThis        - IN pointer to data and callback function

* @return none
*****************************************************************************/
VOID
GsnSpi_Dma_ScatterTxRx( GSN_SPI_T *spiThis );

INLINE UINT8
GsnSpi_Receive( GSN_SPI_T *spiThis );

INLINE UINT8
GsnSpi_Transmit( GSN_SPI_T *spiThis );



UINT32
GsnSpi_RingBuffGet(GSN_SPI_T *pGsnSpi,UINT8* usrBuff, UINT32 usrBuffLen );

VOID
GsnSpi_UsrBuffPutFromRbuffer(GSN_SPI_T *spiThis);

PUBLIC INLINE UINT8
GsnSpi_ByteDeStuff(UINT8 *pNextData);

PUBLIC INLINE UINT8
GsnSpi_ByteStuff(UINT8 *pNextData);

PUBLIC INLINE UINT8
GsnSpi_TxDataGet(GSN_SPI_T *ptGsnSpi,UINT8* ptUsrBuff);

/**
*****************************************************************************
* \internal
* @ingroup GsnSpi Private Patch Functions.
*
*****************************************************************************/

VOID
GsnSpi_Dma_Transmit_Patch( GSN_SPI_T *spiThis );

VOID
GsnSpi_Dma_Receive_Patch( GSN_SPI_T *spiThis );

VOID
GsnSpi_TxProcessing_Patch( GSN_SPI_T *spiThis );
VOID
GsnSpi_RxProcessing_Patch( GSN_SPI_T *spiThis );

#ifdef  __cplusplus
    }
#endif


#endif /* _GSN_SPI_PRIVATE_H_ */
