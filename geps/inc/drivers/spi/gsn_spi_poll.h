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
* $RCSfile: gsn_spi_poll.h,v $
*
* Description : This file contains private functions and definitions for
*               SPI Poll Functionality
********************************************************************************
*/
#ifndef _GSN_SPI_POLL_H_
#define _GSN_SPI_POLL_H_


/****************************************************************************
*  File inclusion
*****************************************************************************/
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"

/**
 *****************************************************************************
 * @file gsn_spi_poll.h
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
 * @ingroup GsnSpi
 * @brief Polling SPI Driver open.
 *
 *	  This function initializes the specified SPI port in polling mode, with required
 *	  configuration parameters provided in GSN_SPI_CONFIG_T. 
 * @param spiHandle 		  - IN pointer to handle.
 * @param spiPortNumber 	  - IN SPI port number. see GSN_SPI_NUM_T
 * @param gsnSpiConfig		  - IN SPI port configuration
 *
 * @return GSN_SUCCESS		  - Initialization successful.
 * @return GSN_FAILURE		  - Initialization failed.
 *
 ****************************************************************************/
PUBLIC GSN_STATUS
GsnSpiPoll_Open( GSN_SPI_HANDLE_T *spiHandle,
			 GSN_SPI_NUM_T spiPortNumber, GSN_SPI_CONFIG_T* gsnSpiConfig);

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Polling method SPI Read and write through specified port in master mode.
 *
 *	  This function Write and read data in master mode using polling method.
 *	  It takes two parameters; one is a valid handle
 *	  pointer and other is a data pointer of structure GSN_SPI_RW_ARGS_T.
 *	  There is no callbacks hence callbacks are NULL.
 *
 * @param spiHandle   - IN pointer to handle.
 * @param spiRW 	  - INOUT pointer to hold read and write data pointers
 *						and data length. 
 *
 * @return GSN_FAILURE	 If data pointer is NULL
 * @return GSN_SUCCESS	 Operation is successful
 *
 ****************************************************************************/
PUBLIC GSN_STATUS
GsnSpiPoll_MasterReadWrite( GSN_SPI_HANDLE_T *spiHandle,
					   GSN_SPI_RW_ARGS_T *spiRW );
	

/**
*****************************************************************************
* \internal
* @ingroup GsnSpiPoll
* @brief SPI Poll Tx processing
*
* @param spiThis        - IN pointer to data and callback function

* @return none
*****************************************************************************/
PUBLIC VOID
GsnSpiPoll_TxProcessing( GSN_SPI_T *spiThis );

/**
*****************************************************************************
* \internal
* @ingroup GsnSpiPoll
* @brief SPI Poll Rx processing
*
* @param spiThis        - IN pointer to data and callback function

* @return none
*****************************************************************************/
PUBLIC VOID
GsnSpiPoll_RxProcessing( GSN_SPI_T *spiThis );

/**
*****************************************************************************
* \internal
* @ingroup GsnSpiPoll
* @brief SPI Poll Rx processing Internal
*
* @param spiThis        - IN pointer to data and callback function

* @return none
*****************************************************************************/
INLINE UINT8
GsnSpiPoll_Rx( GSN_SPI_T *spiThis );

/**
*****************************************************************************
* \internal
* @ingroup GsnSpiPoll
* @brief SPI Poll Tx processing Internal
*
* @param spiThis        - IN pointer to data and callback function

* @return none
*****************************************************************************/
INLINE UINT8
GsnSpiPoll_Tx( GSN_SPI_T *spiThis );

#endif /* _GSN_SPI_PRIVATE_H_ */
