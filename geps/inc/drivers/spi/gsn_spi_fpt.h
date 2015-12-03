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
* $RCSfile: gsn_spi_fpt.h,v $
*
* Description : This file contains public functions Patch definitions for SPI.
******************************************************************************
*/
#ifndef _GSN_SPI_FPT_H_
#define _GSN_SPI_FPT_H_

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

typedef PUBLIC GSN_STATUS
(* GsnSpi_Open_FP_T)( GSN_SPI_HANDLE_T *spiHandle,
             GSN_SPI_NUM_T spiPortNumber, GSN_SPI_CONFIG_T* gsnSpiConfig);

extern _RPST_ GsnSpi_Open_FP_T GsnSpi_Open_FP;


/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Driver SOD set or clear register.
 *
 * @param spiHandle          - IN pointer to handle
 * @param GSN_SPI_SOD_MODE_T        - SOD mode enum
 *
 * @return none.
 *****************************************************************************/
typedef PUBLIC VOID
(* GsnSpi_SodSet_FP_T)( GSN_SPI_HANDLE_T *spiHandle,
                         GSN_SPI_SOD_MODE_T sodMode );

extern _RPST_ GsnSpi_SodSet_FP_T GsnSpi_SodSet_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Driver SOD set or clear register.
 *
 * @param spiHandle          - IN pointer to handle
 * @param GSN_SPI_SOD_MODE_T        - SOD mode enum
 *
 * @return none.
 *****************************************************************************/
typedef PUBLIC GSN_SPI_SOD_MODE_T
(* GsnSpi_SodGet_FP_T)( GSN_SPI_HANDLE_T *spiHandle);

extern _RPST_ GsnSpi_SodGet_FP_T GsnSpi_SodGet_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI NVIC interrupts enable.
 *
 * @param GSN_SPI_HANDLE_T          - IN pointer to handle
*
 * @return none.
*****************************************************************************/
typedef PUBLIC VOID
(* GsnSpi_NvicEnable_FP_T)(GSN_SPI_HANDLE_T *spiHandle);

extern _RPST_ GsnSpi_NvicEnable_FP_T GsnSpi_NvicEnable_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI NVIC interrupts Disable.
 *
 * @param GSN_SPI_HANDLE_T          - IN pointer to handle
 *
 * @return none.
 *****************************************************************************/
typedef PUBLIC VOID
(* GsnSpi_NvicDisable_FP_T)(GSN_SPI_HANDLE_T *spiHandle);

extern _RPST_ GsnSpi_NvicDisable_FP_T GsnSpi_NvicDisable_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Driver close.
 *
 *    This function closes SPI port for specific handles which allow
 *    re-opening the port, sets the ISR pointer to null and close the
 *    synchronous semaphore
 * @param spiHandle           - IN pointer to handle.
 *
 * @return GSN_FAILURE        - If handle is NULL
 * @return GSN_SUCCESS        - If operation success
 ****************************************************************************/
typedef PUBLIC GSN_STATUS
(* GsnSpi_Close_FP_T)(GSN_SPI_HANDLE_T *spiHandle );

extern _RPST_ GsnSpi_Close_FP_T GsnSpi_Close_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Driver Get serial clock rate register.
 *
 *    This function allows setting the serial clock rate register with the
 *    specified value in clockFrequency. Options are 0 - 255
 * @param spiHandle          - IN pointer to handle
 *
 * @return UINT8.
 *****************************************************************************/
typedef PUBLIC UINT8
(* GsnSpi_SerialClockRateGet_FP_T)( GSN_SPI_HANDLE_T *spiHandle);

extern _RPST_ GsnSpi_SerialClockRateGet_FP_T GsnSpi_SerialClockRateGet_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Driver set serial clock rate register.
 *
 *    This function allows setting the serial clock rate register with the
 *    specified value in clockFrequency. Options are 0 - 255
 * @param spiHandle          - IN pointer to handle
 * @param clockFrequency     - IN hold clock frequency
 *
 * @return none.
 *****************************************************************************/
typedef PUBLIC VOID
(* GsnSpi_SerialClockRateSet_FP_T)( GSN_SPI_HANDLE_T *spiHandle,
                        UINT8 clockFrequency );

extern _RPST_ GsnSpi_SerialClockRateSet_FP_T GsnSpi_SerialClockRateSet_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Driver LopBack mode GET.
 *
 *     This function allows getting the LBM
 *
 * @param spiHandle              - IN pointer to handle.
 * @param GSN_SPI_LoopBack_MODE_T  - IN mode selection.
 * @return none.
 *****************************************************************************/
typedef PUBLIC GSN_SPI_LoopBack_MODE_T
(* GsnSpi_LoopBackGet_FP_T)( GSN_SPI_HANDLE_T *spiHandle );

extern _RPST_ GsnSpi_LoopBackGet_FP_T GsnSpi_LoopBackGet_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Driver LopBack mode SET.
 *
 *     This function allows setting the LBM
 *
 * @param spiHandle              - IN pointer to handle.
 * @param GSN_SPI_LoopBack_MODE_T  - IN mode selection.
 * @return none.
 *****************************************************************************/
typedef PUBLIC VOID
(* GsnSpi_LoopBackConfig_FP_T)( GSN_SPI_HANDLE_T *spiHandle,
                         GSN_SPI_LoopBack_MODE_T  LoopBack );

extern _RPST_ GsnSpi_LoopBackConfig_FP_T GsnSpi_LoopBackConfig_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Driver LopBack mode Clear.
 *
 *     This function allows setting the LBM
 *
 * @param spiHandle              - IN pointer to handle.
 * @param GSN_SPI_LoopBack_MODE_T  - IN mode selection.
 * @return none.
 *****************************************************************************/
typedef PUBLIC VOID
(* GsnSpi_LoopBackClear_FP_T)( GSN_SPI_HANDLE_T *spiHandle,
                         GSN_SPI_LoopBack_MODE_T  LoopBack );

extern _RPST_ GsnSpi_LoopBackClear_FP_T GsnSpi_LoopBackClear_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Driver gets operation mode.
 *
 *      This function returns SPI operation mode.
 * @param spiHandle           - IN pointer to handle.
 * @return GSN_SPI_OPERATION_MODE_SLAVE      operation is slave mode
 *         GSN_SPI_OPERATION_MODE_MASTER     operation is master mode
 *
 *
 *****************************************************************************/
typedef PUBLIC GSN_SPI_OPERATINGMODE_T
(* GsnSpi_OperationModeGet_FP_T)( GSN_SPI_HANDLE_T *spiHandle );

extern _RPST_ GsnSpi_OperationModeGet_FP_T GsnSpi_OperationModeGet_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Driver set operation mode.
 *
 *     This function allows setting the operation mode with the specified
 *     value in spiSlaveMasterModeSel.
 * @param spiHandle              - IN pointer to handle.
 * @param spiSlaveMasterModeSel  - IN mode selection.
 * @return none.
 *****************************************************************************/
typedef PUBLIC VOID
(* GsnSpi_OperationModeSet_FP_T)( GSN_SPI_HANDLE_T *spiHandle,
                                   GSN_SPI_OPERATINGMODE_T spiSlaveMasterModeSel );

extern _RPST_ GsnSpi_OperationModeSet_FP_T GsnSpi_OperationModeSet_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Get SPI clock Divider.
 *
 *    This function returns SPI clock divider value; range from 1 to 255
 * @param spiHandle           - IN pointer to handle
 * @return UINT8              - clock divider value range from 1 to 255
 ****************************************************************************/
typedef PUBLIC UINT8
(*GsnSpi_ClockDividerGet_FP_T)( GSN_SPI_HANDLE_T *spiHandle );

extern _RPST_ GsnSpi_ClockDividerGet_FP_T GsnSpi_ClockDividerGet_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Set SPI clock Divider.
 *
 *    This function allows setting the SPI clock divider with specified
 *    value in clkDivider, which helps to decide the clock rate for
 *    SPI master mode
 * @param spiHandle           - IN pointer to handle
 * @param clkDivider          - IN clock divider range from 1 to 255
 * @return none.
 ****************************************************************************/
typedef PUBLIC VOID
(* GsnSpi_ClockDividerSet_FP_T)( GSN_SPI_HANDLE_T *spiHandle,
                                   UINT8 clkDivider );

extern _RPST_ GsnSpi_ClockDividerSet_FP_T GsnSpi_ClockDividerSet_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Get SPI protocol type.
 *
 *    This function returns current protocol type.
 *
 * @param spiHandle                 - IN pointer to handle.
 * @return GSN_SPI_PROTOCOL_MOTOROLA    - Motorola SPI
 * @return GSN_SPI_PROTOCOL_TI          - Texas Instruments SSP
 * @return GSN_SPI_PROTOCOL_NATIONAL    - National Semiconductors Microwire.
 *
 ****************************************************************************/
typedef PUBLIC GSN_SPI_PROTOCOL_T
(*GsnSpi_ProtocolGet_FP_T)( GSN_SPI_HANDLE_T *spiHandle );

extern _RPST_ GsnSpi_ProtocolGet_FP_T GsnSpi_ProtocolGet_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Set SPI protocol.
 *
 *    This function allows setting the SPI protocol type with the specified
 *    in spiProtocol. Protocol options are
 *    GSN_SPI_PROTOCOL_MOTOROLA     Motorola SPI,
 *    GSN_SPI_PROTOCOL_TI           Texas Instruments SSP, and
 *    GSN_SPI_PROTOCOL_NATIONAL     National Semiconductors.
 *
 * @param spiHandle              - IN pointer to handle
 * @param spiProtocol            - IN holds protocol type.
 * @return none.
 ****************************************************************************/
typedef PUBLIC VOID
(* GsnSpi_ProtocolSet_FP_T)( GSN_SPI_HANDLE_T *spiHandle,
                               GSN_SPI_PROTOCOL_T spiProtocol );

extern _RPST_ GsnSpi_ProtocolSet_FP_T GsnSpi_ProtocolSet_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Get SPI clock polarity.
 *
 *    This function returns current clock polarity.
 *
 * @param spiHandle           - IN pointer to handle.
 * @return GSN_SPI_CLK_POL_ACTIVELOW  - Inactive state of serial clock is low
 * @return GSN_SPI_CLK_POL_ACTIVEHIGH - Inactive state of serial clock is high
 *
 ****************************************************************************/
typedef PUBLIC GSN_SPI_CLOCKPOLARITY_T
(*GsnSpi_ClockPolarityGet_FP_T)( GSN_SPI_HANDLE_T *spiHandle );

extern _RPST_ GsnSpi_ClockPolarityGet_FP_T GsnSpi_ClockPolarityGet_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Set SPI clock polarity.
 *
 *      This function allows setting the clock polarity with the specified
 *      in spiClkPolarity. Options are
 *      GSN_SPI_CLK_POL_ACTIVELOW  - Inactive state of serial clock is low
 *      GSN_SPI_CLK_POL_ACTIVEHIGH - Inactive state of serial clock is high.
 * @param spiHandle                - IN pointer to handle.
 * @param spiClkPolarity           - IN hold clock polarity.
 * @return none.
 ****************************************************************************/
typedef PUBLIC VOID
(*GsnSpi_ClockPolaritySet_FP_T)( GSN_SPI_HANDLE_T *spiHandle,
                                   GSN_SPI_CLOCKPOLARITY_T  spiClkPolarity );

extern _RPST_ GsnSpi_ClockPolaritySet_FP_T GsnSpi_ClockPolaritySet_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Get SPI clock phase.
 *
 *    This function returns the current clock phase.
 *
 * @param spiHandle          - IN pointer to handle.
 * @return GSN_SPI_CLK_PHASE_0   - serial clock toggles in middle of
 *                             first data bit
 * @return GSN_SPI_CLK_PHASE_180 - serial clock toggles at start of
 *                             first data bit
 *
 ****************************************************************************/
typedef PUBLIC GSN_SPI_CLOCKPHASE_T
(* GsnSpi_ClockPhaseGet_FP_T)( GSN_SPI_HANDLE_T *spiHandle );

extern _RPST_ GsnSpi_ClockPhaseGet_FP_T GsnSpi_ClockPhaseGet_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Set SPI clock phase.
 *
 *    This function allows setting the clock phase with the specified
 *    in spiClkPhase. Options are GSN_SPI_CLK_PHASE_0 and
 *    GSN_SPI_CLK_PHASE_180. For detail refer GSN_SPI_CLOCKPHASE_T
 *
 * @param spiHandle             - IN pointer to handle.
 * @param spiClkPhase           - IN hold clock phase.
 * @return none.
 ****************************************************************************/
typedef PUBLIC VOID
(* GsnSpi_ClockPhaseSet_FP_T)( GSN_SPI_HANDLE_T *spiHandle,
                                 GSN_SPI_CLOCKPHASE_T  spiClkPhase );

extern _RPST_ GsnSpi_ClockPhaseSet_FP_T GsnSpi_ClockPhaseSet_FP;


/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Get SPI Dataword size
 *
 *    This function returns current data word size.
 * @param spiHandle           - IN pointer to handle
 * @return GSN_SPI_DATAWORDSIZE_4   - data word size 4 bit
 * @return GSN_SPI_DATAWORDSIZE_5   - data word size 5 bit
 *         .                                                      .
 *         .                                                      .
 *         .                                                      .
 * @return GSN_SPI_DATAWORDSIZE_15 - data word size 15 bit
 * @return GSN_SPI_DATAWORDSIZE_16 - data word size 16 bit
 *****************************************************************************/
typedef PUBLIC GSN_SPI_DATAWORDSIZE_T
(* GsnSpi_DataWordSizeGet_FP_T)( GSN_SPI_HANDLE_T *spiHandle );

extern _RPST_ GsnSpi_DataWordSizeGet_FP_T GsnSpi_DataWordSizeGet_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Set SPI Dataword size.
 *
 *    This function allows setting the data word size to the value specified
 *    in spiDataSize.
 *    GSN_SPI_DATAWORDSIZE_4 stands for 4 bit,
 *    GSN_SPI_DATAWORDSIZE_5  stands for 5 bit,
 *           .                                               .
 *           .                                               .
 *           .                                               .
 *    GSN_SPI_DATAWORDSIZE_15  stands for 15 bit and
 *    GSN_SPI_DATAWORDSIZE_16  stands for 16 bit
 * @param spiHandle             - IN pointer to handle
 * @param spiDataSize           - IN select the slave.
 * @return none.
 ****************************************************************************/
typedef PUBLIC VOID
(* GsnSpi_DataWordSizeSet_FP_T)( GSN_SPI_HANDLE_T *spiHandle,
                                  GSN_SPI_DATAWORDSIZE_T  spiDataSize );

extern _RPST_ GsnSpi_DataWordSizeSet_FP_T GsnSpi_DataWordSizeSet_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Read and write through specified port in master mode.
 *
 *    This function transfers data in master mode.
 *    It checks for transfer possibility and then prepares for
 *    data transfer. It takes two parameters; one is a valid handle
 *    pointer and other is a data pointer of structure GSN_SPI_RW_ARGS_T.
 *    In case of a synchronous call, it returns after data transfer is complete.
 *    In case of a asynchronous call, it returns without waiting for data
 *    transfer. The callback function specified in pSpiRW(GSN_SPI_RW_ARGS_T)
 *    is called after data transfer is complete.
 *
 * @param spiHandle   - IN pointer to handle.
 * @param spiRW       - INOUT pointer to hold read and write data pointers
 *                      and data length. It also holds callback function
                        pointers.
 *
 * @return GSN_FAILURE   If data pointer is NULL
 * @return GSN_SPI_BUSY  If data transfer is running
 * @return GSN_SUCCESS   Operation is successful
 *
 ****************************************************************************/
typedef PUBLIC GSN_STATUS
(* GsnSpi_MasterReadWrite_FP_T)(GSN_SPI_HANDLE_T *spiHandle ,
                       GSN_SPI_RW_ARGS_T *spiRW  );

extern _RPST_ GsnSpi_MasterReadWrite_FP_T GsnSpi_MasterReadWrite_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Read and write through specified port in slave mode.
 *
 *    This function allows transferring data in slave mode.  It waits for
 *    external clock.
 *    It checks for transfer availability and then prepares for
 *    data transfer. It accepts two parameters; one is a valid handle
 *    pointer and other is data pointer of the structure GSN_SPI_RW_ARGS_T.
 *    In case of a synchronous call, it returns after the data transfer done.
 *    In case of an asynchronous call, it returns without waiting for data
 *    transfer. The call back function specified in pSpiRW(GSN_SPI_RW_ARGS_T)
 *    is called after data transfer complete.
 *
 * @param spiHandle         - IN pointer to handle.
 * @param spiRW             - INOUT pointer to hold read write data pointer
 *                            and data length. Also holds callback function
 *                            pointers.
 *
 * @return GSN_FAILURE   If data pointer is NULL
 * @return GSN_SPI_BUSY  If data transfer is running
 * @return GSN_SUCCESS   Operation is successful
 *
 *****************************************************************************/
typedef PUBLIC GSN_STATUS
(* GsnSpi_SlaveReadWrite_FP_T)(GSN_SPI_HANDLE_T *spiHandle ,
                      GSN_SPI_RW_ARGS_T *spiRW);

extern _RPST_ GsnSpi_SlaveReadWrite_FP_T GsnSpi_SlaveReadWrite_FP;


/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Slave Write
 *
 *    This API is called from the APP side if needed for half Duplex transmit only
 *
 * @param spiHandle         - IN pointer to handle.
 * @param tx			     - IN pointer to GSN_SPI_TXRXCHANNEL_T
 *								initialisation parameters for  transmit
 * @return none
 *****************************************************************************/

typedef PUBLIC UINT32
(* GsnSpi_SlaveWrite_FP_T)( GSN_SPI_HANDLE_T *spiHandle,
                       GSN_SPI_TXRXCHANNEL_T *tx );

extern _RPST_ GsnSpi_SlaveWrite_FP_T GsnSpi_SlaveWrite_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Slave Read
 *
 *    This API is called from the APP side if needed for half Duplex receive only
 *
 * @param spiHandle         - IN pointer to handle.
 * @param tx			     - IN pointer to GSN_SPI_TXRXCHANNEL_T
 *								initialisation parameters for  receive
 * @return none
 *****************************************************************************/

typedef PUBLIC UINT32
(* GsnSpi_SlaveRead_FP_T)( GSN_SPI_HANDLE_T *spiHandle,
                             GSN_SPI_TXRXCHANNEL_T *rx );

extern _RPST_ GsnSpi_SlaveRead_FP_T GsnSpi_SlaveRead_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI ISR
 *
 *    This interrupt service routine is called by the
 *    interrupt handler.
 * @param spiHandle         - IN pointer to handle.
 * @return none
 *****************************************************************************/
typedef PUBLIC VOID
(* GsnSpi_Isr_FP_T)( GSN_SPI_HANDLE_T *spiHandle );

extern _RPST_ GsnSpi_Isr_FP_T GsnSpi_Isr_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI ISR
 *
 *    This interrupt service routine is called by the
 *    interrupt handler from nvic when using SPI_0.
 * @param None
 * @return none
 *****************************************************************************/
typedef PUBLIC VOID
(* __GsnSpi0_Isr_FP_T)( );

extern _RPST_ __GsnSpi0_Isr_FP_T __GsnSpi0_Isr_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI ISR
 *
 *    This interrupt service routine is called by the
 *    interrupt handler from nvic when using SPI_1.
 * @param None
 * @return none
 *****************************************************************************/
typedef PUBLIC VOID
(* __GsnSpi1_Isr_FP_T)( );

extern _RPST_ __GsnSpi1_Isr_FP_T __GsnSpi1_Isr_FP;



/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI-0 Dma Tx done ISR
 *
 *    This interrupt service routine is called by the
 *    interrupt handler from nvic when using SPI.
 * @param ctx    - context
 * @param channelID - channel ID
 * @return none
 *****************************************************************************/
typedef VOID
(* GsnSpi0_TxCallBack_FP_T)( VOID *ctx, UINT32 channelID);

extern _RPST_ GsnSpi0_TxCallBack_FP_T GsnSpi0_TxCallBack_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI-0 Dma Rx done ISR
 *
 *    This interrupt service routine is called by the
 *    interrupt handler from nvic when using SPI.
 * @param ctx    - context
 * @param channelID - channel ID
 * @return none
 *****************************************************************************/
typedef VOID
(* GsnSpi0_RxCallBack_FP_T)( VOID *ctx, UINT32 channelID);

extern _RPST_ GsnSpi0_RxCallBack_FP_T GsnSpi0_RxCallBack_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI-1 Dma Tx done ISR
 *
 *    This interrupt service routine is called by the
 *    interrupt handler from nvic when using SPI.
 * @param ctx    - context
 * @param channelID - channel ID
 * @return none
 *****************************************************************************/
typedef VOID
(* GsnSpi1_TxCallBack_FP_T)( VOID *ctx, UINT32 channelID);

extern _RPST_ GsnSpi1_TxCallBack_FP_T GsnSpi1_TxCallBack_FP;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI-1 Dma Rx done ISR
 *
 *    This interrupt service routine is called by the
 *    interrupt handler from nvic when using SPI.
 * @param ctx    - context
 * @param channelID - channel ID
 * @return none
 *****************************************************************************/
typedef VOID
(* GsnSpi1_RxCallBack_FP_T)( VOID *ctx, UINT32 channelID);

extern _RPST_ GsnSpi1_RxCallBack_FP_T GsnSpi1_RxCallBack_FP;


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
