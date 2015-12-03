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
* $RCSfile: gsn_spiFs_private.h,v $
*
* Description : This file contains private functions and definitions for
*               SPI driver
********************************************************************************
*/
#ifndef _GSN_SPI_HI_PRIVATE_H_
#define _GSN_SPI_HI_PRIVATE_H_

#ifdef  __cplusplus
extern "C" {
#endif


/****************************************************************************
*  File inclusion
*****************************************************************************/
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
//#include "gsn_spi_hi.h"

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
GsnSpiFS_ErrorIsr( GSN_SPI_FS_T *spiThis, UINT32 value );

INLINE UINT8
GsnSpiFS_Receive( GSN_SPI_FS_T *spiThis );

INLINE UINT8
GsnSpiFS_Transmit( GSN_SPI_FS_T *spiThis );

VOID
GsnSpiFS_RxProcessing( GSN_SPI_FS_T *spiThis );

UINT32
GsnSpiFS_RingBuffGet(GSN_SPI_FS_T *pGsnSpi,UINT8* usrBuff, UINT32 usrBuffLen );

UINT8
GsnSpi_Checksum(UINT8* headerBuff,
                    UINT8 length);
UINT32
GsnSpi_ResponseBuffHandler( GSN_SPI_FS_T *spiThis,UINT8 checksum);




#ifdef  __cplusplus
    }
#endif

#endif /* _GSN_SPI_H_ */
