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
 * $RCSfile: gsn_dma.h,v $
 *
 * Description:
 *      This file contains public functions definitions for DMA Driver
 *
 ******************************************************************************
 */
 

/**
******************************************************************************
*  @file gsn_dma.h
*  @brief Public Header Containing DMA Driver Functions.
*
*  This file contains the public APIs and structures of DMA module.
*****************************************************************************/


/**
 *****************************************************************************
 * @ingroup driversdoc
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 *  @defgroup GsnDma GSN DMA API
 *    This group contains public definitions and functions providing access
 *    to the GS2000 DMA.
 ****************************************************************************/

/**
 *****************************************************************************
 *
 * @}
 *****************************************************************************/



#ifndef _GSNDMA_H_
#define _GSNDMA_H_

#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
#include "core/osal/gsn_osal.h"
#include "core/osal/gsn_osal.h"









/**
 *****************************************************************************

 *DMA_Channel_IDs

 ****************************************************************************/
#define NUMB_OF_DMA_PHERI 							  6   
#define PING_PONG_COMMON                              0x0CFC800B
#define PERIPHERAL_SCATTER_GATHER_PRIMARY_COMMON      0xAAFC800E
#define MEMORY_SCATTER_GATHER_PRIMARY_COMMON          0xAAFC8004
#define N_MINUS_ONE_FIELD_BIT_MASK                    0x00003FF0
#define DMA_CYCLE_TYPE_BIT_MASK                       0x00000007   
#define EXPECTED_BASE_ADDRESS_FOR_10_CHANNELS         0xFFFFFE00
#define SYSTEM_MEMORY_FOR_DATASTRUCTURE               1024
#define MAX_BYTES_PER_DMA_TRANSFER                    1024

#define UARTDMA_MAX_TRANSMIT_COUNT                    1024
#define PSG_MAX_TRANSFER_COUNT                        1024
#define MAX_NO_OF_TASKS_IN_PERIPHERAL_SCATTER_GATHER  10

#define GSN_ACM3CH0_CHANNEL_NO                        0
#define GSN_ACM3CH1_CHANNEL_NO                        1
#define GSN_SPI0_RX_DMA_CHANNEL_NO                    2
#define GSN_SPI0_TX_DMA_CHANNEL_NO                    3
#define GSN_UART0_RX_DMA_CHANNEL_NO                   4
#define GSN_UART0_TX_DMA_CHANNEL_NO                   5
#define GSN_SPI1_RX_DMA_CHANNEL_NO                    6
#define GSN_SPI1_TX_DMA_CHANNEL_NO                    7
#define GSN_UART1_RX_DMA_CHANNEL_NO                   8
#define GSN_UART1_TX_DMA_CHANNEL_NO                   9

#define GSN_SPI0_RX_DMA_CHANNEL_POSITION              0x00000004
#define GSN_SPI0_TX_DMA_CHANNEL_POSITION              0x00000008
#define GSN_UART0_RX_DMA_CHANNEL_POSITION             0x00000010    
#define GSN_UART0_TX_DMA_CHANNEL_POSITION             0x00000020
#define GSN_SPI1_RX_DMA_CHANNEL_POSITION              0x00000040
#define GSN_SPI1_TX_DMA_CHANNEL_POSITION              0x00000080
#define GSN_UART1_RX_DMA_CHANNEL_POSITION             0x00000100    
#define GSN_UART1_TX_DMA_CHANNEL_POSITION             0x00000200

#define GSN_ACM3CH0_CHANNEL                           0X00000001
#define GSN_ACM3CH1_CHANNEL                           0X00000002
#define GSN_SPI0_DMA_CHANNELS                         0x0000000C
#define GSN_SPI1_DMA_CHANNELS                         0x000000C0
#define GSN_UART0_DMA_CHANNELS                        0x00000030
#define GSN_UART1_DMA_CHANNELS                        0x00000300

#define GSN_ACM3_CH0                           0
#define GSN_ACM3_CH1                           1
#define GSN_SPI0_DMA                           2
#define GSN_SPI1_DMA                           3
#define GSN_UART0_DMA                          4
#define GSN_UART1_DMA                          5

   
#define GSNDMA_CHANNEL_COUNT                        32
#define GSNDMA_FULL_CHANNELS_ENABLE                 0xFFFFFFFF
#define GSNDMA_FULL_CHANNELS_DISABLE                0x00000000

#define GSNDMA_CHANNEL_0          0
#define GSNDMA_CHANNEL_1          1
#define GSNDMA_CHANNEL_2          2
#define GSNDMA_CHANNEL_3          3
#define GSNDMA_CHANNEL_4          4
#define GSNDMA_CHANNEL_5          5
#define GSNDMA_CHANNEL_6          6
#define GSNDMA_CHANNEL_7          7
#define GSNDMA_CHANNEL_8          8
#define GSNDMA_CHANNEL_9          9
#define GSNDMA_CHANNEL_10         10
#define GSNDMA_CHANNEL_11         11
#define GSNDMA_CHANNEL_12         12
#define GSNDMA_CHANNEL_13         13
#define GSNDMA_CHANNEL_14         14
#define GSNDMA_CHANNEL_15         15
#define GSNDMA_CHANNEL_16         16
#define GSNDMA_CHANNEL_17         17
#define GSNDMA_CHANNEL_18         18
#define GSNDMA_CHANNEL_19         19
#define GSNDMA_CHANNEL_20         20
#define GSNDMA_CHANNEL_21         21
#define GSNDMA_CHANNEL_22         22
#define GSNDMA_CHANNEL_23         23
#define GSNDMA_CHANNEL_24         24
#define GSNDMA_CHANNEL_25         25
#define GSNDMA_CHANNEL_26         26
#define GSNDMA_CHANNEL_27         27
#define GSNDMA_CHANNEL_28         28
#define GSNDMA_CHANNEL_29         29
#define GSNDMA_CHANNEL_30         30
#define GSNDMA_CHANNEL_31         31
/*
 *****************************************************************************************
 * Type definitions.
 *****************************************************************************************
*/

typedef VOID ( *DMACALLBACK_FP ) ( VOID*, UINT32 );

/**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief   GSN DMA current state values.
 *    This enum defines DMA controller state
 * @see
 *****************************************************************************/
enum GSN_DMA_CONTROLLER_STATE
{
    GSN_DMA_NOT_INITIALIZED,
    GSN_DMA_INITIALIZED,
    GSN_DMA_READ_PROGRESS,
    GSN_DMA_READ_FINISHED,
    GSN_DMA_WRITE_PROGRESS,
    GSN_DMA_WRITE_FINISHED,
    GSN_DMA_CLOSED
};
/**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief   GSN DMA available peripherals.
 *          This enum defines DMA available peripherals.
 * @see     GSN_DMA_PERIPHERAL_SELECT_T.
 *****************************************************************************/

typedef enum GSN_DMA_PERIPHERAL_SELECT
{
    GSN_DMA_CH0,
    GSN_DMA_CH1,
    GSN_DMA_SSP0_RX,
    GSN_DMA_SSP0_TX,
    GSN_DMA_UART0_RX,
    GSN_DMA_UART0_TX,
    GSN_DMA_SSP1_RX,
    GSN_DMA_SSP1_TX,
    GSN_DMA_UART1_RX,
    GSN_DMA_UART1_TX,
    
   
} GSN_DMA_PERIPHERAL_SELECT_T;
/**
 *****************************************************************************
 * @ingroup  GsnDma
 * @brief    GSN DMA source data sizes.
 *           This enum defines available source data sizes of DMA .
 * @see      GSN_DMA_SRC_SIZE_T.
 *****************************************************************************/

typedef enum GSN_DMA_SRC_SIZE
{
    GSN_DMA_BYTE_SRC_SIZE      = 0,
    GSN_DMA_HALFWORD_SRC_SIZE  = 1,
    GSN_DMA_WORD_SRC_SIZE      = 2, 
   
} GSN_DMA_SRC_SIZE_T;
/**
 *****************************************************************************
 * @ingroup  GsnDma
 * @brief    GSN DMA source data increment.
 *           This enum defines available DMA source data increment values .
 * @see      GSN_DMA_SRC_INC_T.
 *****************************************************************************/

typedef enum GSN_DMA_SRC_INC
{
    GSN_DMA_BYTE_SRC_INC      = 0,
    GSN_DMA_HALFWORD_SRC_INC  = 1,
    GSN_DMA_WORD_SRC_INC      = 2, 
    GSN_DMA_NO_SRC_INC        = 3, 
    
   
} GSN_DMA_SRC_INC_T;
/**
 *****************************************************************************
 * @ingroup  GsnDma
 * @brief    GSN DMA destination data sizes.
 *           This enum defines available Destination data sizes of DMA .
 * @see      GSN_DMA_DEST_SIZE_T.
 *****************************************************************************/

typedef enum GSN_DMA_DEST_SIZE
{
    GSN_DMA_BYTE_DEST_SIZE      = 0,
    GSN_DMA_HALFWORD_DEST_SIZE  = 1,
    GSN_DMA_WORD_DEST_SIZE      = 2, 
   
} GSN_DMA_DEST_SIZE_T;
/**
 *****************************************************************************
 * @ingroup  GsnDma
 * @brief    GSN DMA destination data increment.
 *           This enum defines available DMA destination data increment values .
 * @see      GSN_DMA_DEST_INC_T.
 *****************************************************************************/

typedef enum GSN_DMA_DEST_INC
{
    GSN_DMA_BYTE_DEST_INC      = 0,
    GSN_DMA_HALFWORD_DEST_INC  = 1,
    GSN_DMA_WORD_DEST_INC      = 2, 
    GSN_DMA_NO_DEST_INC        = 3, 
    
   
} GSN_DMA_DEST_INC_T;
/**
 *****************************************************************************
 * @ingroup  GsnDma
 * @brief    GSN DMA arbitration values.
 *           This enum defines Available arbitration values of Dma.
 * @see      GSN_DMA_R_POWER_T.
 *****************************************************************************/

typedef enum GSN_DMA_R_POWER
{
   GSN_ARBITRATION_1_DMATRANSFER         = 0,
   GSN_ARBITRATION_2_DMATRANSFER         = 1,  
   GSN_ARBITRATION_4_DMATRANSFER         = 2,  
   GSN_ARBITRATION_8_DMATRANSFER         = 3,  
   GSN_ARBITRATION_16_DMATRANSFER        = 4,
   GSN_ARBITRATION_32_DMATRANSFER        = 5,  
   GSN_ARBITRATION_64_DMATRANSFER        = 6,  
   GSN_ARBITRATION_128_DMATRANSFER       = 7,  
   GSN_ARBITRATION_256_DMATRANSFER       = 8,  
   GSN_ARBITRATION_512_DMATRANSFER       = 9,
   GSN_ARBITRATION_1024_DMATRANSFER      = 10 
  
    
   
} GSN_DMA_R_POWER_T;
/**
 *****************************************************************************
 * @ingroup  GsnDma
 * @brief    GSN DMA cycle Types.
 *           This enum defines DMA cycle types.
 * @see      GSN_DMA_CYCLE_TYPE_T.
 *****************************************************************************/

typedef enum GSN_DMA_CYCLE_TYPE
{
   GSN_DMACYCLE_STOP               = 0,  
   GSN_DMACYCLE_BASIC              = 1, 
   GSN_DMACYCLE_AUTOREQUEST        = 2, 
   GSN_DMACYCLE_PING_PONG          = 3,
   GSN_DMACYCLE_MSG_PRIMARY        = 4,  
   GSN_DMACYCLE_MSG_ALTERNATE      = 5, 
   GSN_DMACYCLE_PSG_PRIMARY        = 6, 
   GSN_DMACYCLE_PSG_ALTERNATE      = 7,
    
   
} GSN_DMA_CYCLE_TYPE_T;
/**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    GSN DMA  ping pong parameters.
 *           This enum defines DMA ping pong handling structure.
 * @see      GSN_DMA_PINGPONG_CONTROL_T.
 *****************************************************************************/

typedef struct GSN_DMA_PINGPONG_CONTROL
{
    UINT32             bytesRemainsPingPong;
    UINT32             alternatePingPong;
    UINT32             primaryPingPong;
    UINT32*            srcAddressPingpong;
    UINT32*            destAddressPingpong;
    UINT32*            srcStartAddress;
    UINT32*            destStartAddress;
    UINT32             previousNminus;
    
   
} GSN_DMA_PINGPONG_CONTROL_T;

/**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    GSN DMA control data Structure.
 *           This structure defines DMA control data structure.
 * @see      GSN_DMA_CONTROL_T.
 *****************************************************************************/
typedef struct GSN_DMA_CONTROL
{
    UINT32            *pvSrcAddr;
    UINT32            *pvDstAddr;
    UINT32            ulControl;
    UINT32            unUsed;
}GSN_DMA_CONTROL_T;
/**
 *****************************************************************************
 * @ingroup  GsnDma
 * @brief    GSN DMA Structure.
 *           This structure defines DMA handling parameters.
 * @see      GSN_DMA_T.
 *****************************************************************************/

typedef struct GSN_DMA
{
    UINT32             pReg;
    UINT32            *basePtr;
    UINT32             memPool;
    GSN_DMA_PINGPONG_CONTROL_T gsnPingpongControl[10];
    DMACALLBACK_FP     channelCallback[2];
    VOID               *channelCbCtx[2];
    DMACALLBACK_FP     uartReadCallback[2];
    DMACALLBACK_FP     uartWriteCallback[2];
    VOID              *uartWriteCbCtx[2];
    VOID              *uartReadCbCtx[2];
    DMACALLBACK_FP     spiReadCallback[2];
    DMACALLBACK_FP     spiWriteCallback[2];
    VOID              *spiWriteCbCtx[2];
    VOID              *spiReadCbCtx[2];
    UINT32             dmaDeviceState;
    /* declaring dma data structure to send max of
                     MAX_NO_OF_TASKS_IN_PERIPHERAL_SCATTER_GATHER*1024 bytes */
    GSN_DMA_CONTROL_T dmaControl [10*MAX_NO_OF_TASKS_IN_PERIPHERAL_SCATTER_GATHER]; 
    


}GSN_DMA_T;



/**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief  GSN DMA Structure.
 *    This structure defines DMA base register
 * @see       GSN_DMACONFIG_T.
 *****************************************************************************/
typedef struct GSN_DMACONFIG
{
    UINT32 prioritySet;
    UINT32 alternateDsSet;
    
}GSN_DMACONFIG_T;
/**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief     GSN DMA Channel Configuration union.
 *            This Union defines DMA channel configuration values.
 *
 * @see       GSN_DMA_CHANNEL_CONFIG_T.
 *****************************************************************************/
typedef union GSN_DMACHANNEL_CONFIG
{
  UINT32 ulControl;
  
  struct channelBitField
  {
    unsigned dmaCycleType         :3;
    unsigned nextUserBurst        :1;
    unsigned nMinusOne            :10 ;
    unsigned rPower               :4;
    unsigned srcPrtCntl           :3;
    unsigned destPrtCntl          :3;
    unsigned srcSize              :2;
    unsigned srcInc               :2;
    unsigned destSize             :2;
    unsigned destInc              :2;
  }channelBitField;
    
}GSN_DMA_CHANNEL_CONFIG_T;

/**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    This function checks the DMA channel ID is valid or not.
 * @param    ulChannelID           - Channel ID.
 * @retval   GSN_SUCCESS on success
 * @note
 *****************************************************************************/

BOOL
GsnDma_ChannelIDValid(UINT8 ulChannelID);
/**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    This function registers all the call back functions
 *           from the peripheral modules in dma driver.  
 * @param    ptGsnDma          - Dma handle structure
 * @param    ptCallBackFunc    - call back function from the peripheral.
 * @param    ctx               - context from the peripheral
 * @param    channelID         - channel ID.
 * @retval   VOID
 * @note
 *****************************************************************************/
VOID
GsnDma_CallBackRegister(GSN_DMA_T* ptGsnDma,DMACALLBACK_FP ptCallBackFunc, 
                                           VOID *ctx ,UINT32 channelID);
/**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    DMA Driver Individual Channel Close API.
 *           This function closes the particular channel.
 * @param    ptGsnDma          - IN pointer to GSN_DMA_T structure  .
 * @param    channelsToClose   - Channel that upper layer want to close.
 * @retval   GSN_DMA_STATUS_ERROR  on error
 * @retval   GSN_DMA_STATUS_OK on success.
 * @note
 *****************************************************************************/
GSN_OSAL_ERROR_T
GsnDma_IndividualClose (GSN_DMA_T* ptGsnDma,UINT32 channelsToClose);
/**
 *****************************************************************************
 * @ingroup  GsnDma
 * @brief    DMA Driver Close API.
 *           This function closes PL230 DMA.
 * @param    ptGsnDma          - IN pointer to GSN_DMA_T structure 
 * @retval GSN_DMA_STATUS_ERROR  on error
 * @retval GSN_DMA_STATUS_OK on success.
 * @note
 *****************************************************************************/
GSN_OSAL_ERROR_T
GsnDma_Close (GSN_DMA_T* ptGsnDma);
/**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief DMA Driver open API.
 * This function initializes PL230 DMA.
 * @param    ptGsnDma           - IN pointer to GSN_DMA_T structure.
 * @param    ptConfig           - IN pointer to DMA Config structure.
 * @param    channelsToConfigure           - IN Channels to Configure
 * @retval GSN_DMA_STATUS_ERROR  on error
 * @retval GSN_DMA_STATUS_OK on success.
 * @note
 *****************************************************************************/
GSN_OSAL_ERROR_T
GsnDma_Open (GSN_DMA_T* ptGsnDma,GSN_DMACONFIG_T *ptConfig,UINT32 channelsToConfigure);
/**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    DMA module enable API.
 *           This function Enables PL230 DMA.
 * @param    ptGsnDma          - IN pointer to GSN_DMA_T structure  .
 * @retval   VOID
 * @note
 *****************************************************************************/
VOID
GsnDma_Enable(GSN_DMA_T* ptGsnDma);
/**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    DMA module Primary-Alternate-Set API.
 *           This function set the alternate data structure of Dma.
 * @param    ptGsnDma          - IN pointer to GSN_DMA_T structure  .
 * @param    channelsToConfigure - Channel no-to enable the alternate data stru
             cture of a particular channel
 * @retval   VOID
 * @note
 *****************************************************************************/
VOID
GsnDma_ChannelPriAltClear (GSN_DMA_T* ptGsnDma,UINT32 channelsToConfigure);
/**
 *****************************************************************************
 * @ingroup  GsnDma
 * @brief    DMA module Primary-Alternate-Clear API.
 *           This function clear the alternate data structure of Dma.
 * @param    ptGsnDma          - IN pointer to GSN_DMA_T structure  .
 * @param    channelsToConfigure - Channel no-to clear the alternate data stru
             cture of a particular channel
 * @retval   VOID
 * @note
 *****************************************************************************/
VOID
GsnDma_ChannelPriAltSet (GSN_DMA_T* ptGsnDma,UINT32 channelsToConfigure);
/**
 *****************************************************************************
 * @ingroup  GsnDma
 * @brief    DMA module disable API.
 *           This function disables PL230 DMA.
 * @param    ptGsnDma           - IN pointer to GSN_DMA_T structure  .
 * @retval   VOID
 * @note
 *****************************************************************************/
VOID
GsnDma_Disable(GSN_DMA_T* ptGsnDma);
/**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    DMA Driver DMA status (enable or disable) get  API.
 *           This API can use for getting the current status of DMA.
 * @param    ptGsnDma           - IN pointer to GSN_DMA_T structure  .
 * @retval   If 1 DMA is enabled.
 * @note
 *****************************************************************************/
UINT32
GsnDma_StatusGet(GSN_DMA_T* ptGsnDma);
/**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief
 *           This function will enable the specified dma channel
 * @param    ptGsnDma           - IN pointer to GSN_DMA_T structure  
 * @param ulChannelID            - ulChannelID is the DMA channel ID.
 * @return   VOID
 * @note
 *****************************************************************************/
VOID
GsnDma_ChannelEnable(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

 /**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief
 * This function will disable the specified channel
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure  
 * @param ulChannelID            - ulChannelID is the DMA channel ID.
 * @return   VOID
 * @note
 *****************************************************************************/
VOID
GsnDma_ChannelDisable(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

/**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief
 *           This function can use for the software request for a channel
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure  
 * @param ulChannelID            - ulChannelID is the DMA channel ID.
 * @return   VOID
 * @note
 *****************************************************************************/
VOID
GsnDma_ChannelSoftwareRequest(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
 /**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    In PL230 DMA ,transfer can done using one of the 5 dma cycle types.
             1.)basic 2.)auto request 3.)memory scatter gather
             4.)peripheral scatter gather 5.)ping pong
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure
 * @param    ptChannelConfig        - IN pointer to GSN_DMA_CHANNEL_CONFIG_T
 * @param    ulChannelID            -  ulChannelID is the DMA channel ID.
 * @param    noOfBytesToTransfer    -  No of bytes to transfer.
 * @param    pvSrcAddr              -  Source address of dma transfer.
 * @param    pvDstAddr              -  Destination address of dma transfer.
 * @return  VOID
 * @note
 *****************************************************************************/
VOID
GsnDma_CycleControl(GSN_DMA_T* ptGsnDma,GSN_DMA_CHANNEL_CONFIG_T *ptChannelConfig,
    UINT8 ulChannelID,UINT32 noOfBytesToTransfer,VOID *pvSrcAddr,VOID *pvDstAddr);

/**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    Sets the control parameter for a particular channel in primarary
 *            data structure.
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure
 * @param ulChannelID -  ulChannelID is the DMA channel ID.
 * @param    ulControl   -  channel configuration parameter.
 * @return   VOID
 * @note
 *****************************************************************************/
VOID
GsnDma_ChannelControlSetPrimary(GSN_DMA_T* ptGsnDma, UINT32 ulControl,UINT8 ulChannelID);
/**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    Sets the control parameter for a particular channel in Alternate
 *           data structure.
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure
 * @param ulChannelID -  ulChannelID is the DMA channel ID.
 * @param    ulControl              -  channel configuration parameter.
 * @return   VOID
 * @note
 *****************************************************************************/
VOID
GsnDma_ChannelControlSetAlternate(GSN_DMA_T* ptGsnDma, UINT32 ulControl,UINT8 ulChannelID);
 /**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    This API gets the channel configuration of a particular channel 
 *           in primary data structure.
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure
 * @param ulChannelID -  ulChannelID is the DMA channel ID.
 * @return   Channel configuration value.
 * @note
 *****************************************************************************/
UINT32
GsnDma_ChannelControlGetPrimary(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
 /**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    This API gets the channel configuration of a particular channel 
 *           in alternate data structure.
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure
 * @param ulChannelID -  ulChannelID is the DMA channel ID.
 * @return   Channel configuration value.
 * @note
 *****************************************************************************/
UINT32
GsnDma_ChannelControlGetAlternate(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
 /**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    This API sets the source address and destination address of a particular  
             channel in primary data structure.
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure
 * @param    ulChannelID            -  ulChannelID is the DMA channel ID.
 * @param    pvSrcAddr              -is the source address for the DMA transfer.
 * @param    pvDstAddr              -is the destination address for the DMA transfer.
 * @return   VOID
 * @note
 *****************************************************************************/
VOID
GsnDma_ChannelTransferSetPrimary(GSN_DMA_T* ptGsnDma, VOID *pvSrcAddr,
                       VOID *pvDstAddr,UINT8 ulChannelID);
 /**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    This API sets the source address and destination address of a particular  
             channel in Alternate data structure.
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure
 * @param    ulChannelID            -  ulChannelID is the DMA channel ID.
 * @param    pvSrcAddr              -is the source address for the DMA transfer.
 * @param    pvDstAddr              -is the destination address for the DMA transfer.
 * @return   VOID
 * @note
 *****************************************************************************/
VOID
GsnDma_ChannelTransferSetAlternate(GSN_DMA_T* ptGsnDma, VOID *pvSrcAddr,
                       VOID *pvDstAddr,UINT8 ulChannelID);

 /**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    This API Gets the  Current Source Address of a  particular channel.
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure
 * @param    ulChannelID            -  ulChannelID is the DMA channel ID.
 * @return   current source address
 * @note
 *****************************************************************************/
UINT32
GsnDma_CurrentSourceAddrGet(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

 /**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    This API Gets the  Current Destination Address of a  particular channel.
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure
 * @param    ulChannelID            -  ulChannelID is the DMA channel ID.
 * @return   current destination address
 * @note
 *****************************************************************************/
UINT32
GsnDma_CurrentDestAddrGet(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

 /**
 *****************************************************************************
 * @ingroup  GsnDma
 * @brief    This API Gets the  Current Destination Address of a  particular channel
             in primary data structure.
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure
 * @param    ulChannelID            -  ulChannelID is the DMA channel ID.
 * @return   current destination address
 * @note
 *****************************************************************************/
UINT32
GsnDma_CurrentDestAddrGetPrimary(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

 /**
 *****************************************************************************
 * @ingroup  GsnDma
 * @brief    This API gets the current N_MINUS_1 value of a particular channel
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure
 * @param    ulChannelID            -  ulChannelID is the DMA channel ID.
 * @retval   Remaining transfer count
 * @note
 *****************************************************************************/
UINT32
GsnDma_RemainTransferCountGet(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
/**
 *****************************************************************************
* @ingroup  GsnDma
 * @brief   This API gets the current N_MINUS_1 value of a particular channel
            in primary data structure.
 * @param   ptGsnDma               - IN pointer to GSN_DMA_T structure
 * @param   ulChannelID            -  ulChannelID is the DMA channel ID.
 * @retval  Remaining transfer count
 * @note
 *****************************************************************************/
UINT32
GsnDma_RemainTransferCountGetPrimary(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
/**
 *****************************************************************************
 * @ingroup  GsnDma
 * @brief    This API gets the current N_MINUS_1 value of a particular channel
             in alternate data structure.
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure
 * @param    ulChannelID            -  ulChannelID is the DMA channel ID.
 * @retval   Remaining transfer count
 * @note
 *****************************************************************************/
UINT32
GsnDma_RemainTransferCountGetAlternate(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
/**
 *****************************************************************************
 * @ingroup  GsnDma
 * @brief    This API gets the current dma cycle type value of a particular channel
             in alternate data structure.
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure
 * @param    ulChannelID            -  ulChannelID is the DMA channel ID.
 * @retval   current dma cycle type
 * @note
 *****************************************************************************/
UINT32
GsnDma_CycleTypeGetAlternate(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
/**
 *****************************************************************************
* @ingroup   GsnDma
 * @brief    This API gets the current dma cycle type value of a particular channel
             in primary data structure.
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure
 * @param    ulChannelID            -  ulChannelID is the DMA channel ID.
 * @retval   current dma cycle type
 * @note
 *****************************************************************************/
UINT32
GsnDma_CycleTypeGetPrimary(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
 /**
 *****************************************************************************
 * @ingroup  GsnDma
 * @brief    This API gets the current channel address of a particular channel 
 *           in primary data structure.
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure
 * @param    ulChannelID            -  ulChannelID is the DMA channel ID.
 * @retval   channel address
 * @note
 *****************************************************************************/

UINT32
GsnDma_specificChannelAddressPrimary(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

 /**
 *****************************************************************************
 * @ingroup GsnDma
 * @brief    This API gets the current channel address of a particular channel 
 *           in alternate data structure.
 * @param    ptGsnDma               - IN pointer to GSN_DMA_T structure
 * @param    ulChannelID            -  ulChannelID is the DMA channel ID.
 * @retval   channel address
 * @note
 *****************************************************************************/
UINT32
GsnDma_specificChannelAddressAlternate(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);


PUBLIC VOID 
__GsnDma_Ch0Done_Isr();


PUBLIC VOID 
__GsnDma_Ch1Done_Isr();

PUBLIC VOID 
__GsnDma_Uart0RxDone_Isr();


PUBLIC VOID 
__GsnDma_Uart0TxDone_Isr();

PUBLIC VOID 
__GsnDma_Ssp1RxDone_Isr();

PUBLIC VOID 
__GsnDma_Ssp1TxDone_Isr();

PUBLIC VOID 
__GsnDma_Uart1RxDone_Isr();

PUBLIC VOID 
__GsnDma_Uart1TxDone_Isr();

PUBLIC VOID 
__GsnDma_Ssp0RxDone_Isr();

PUBLIC VOID 
__GsnDma_Ssp0TxDone_Isr();

PUBLIC VOID 
__GsnDma_Error_Isr();


/* Dma Patch Functions */

VOID
GsnDma_CycleControl_Patch(GSN_DMA_T* ptGsnDma,GSN_DMA_CHANNEL_CONFIG_T *ptChannelConfig,
UINT8 ulChannelID,UINT32 noOfBytesToTransfer,VOID *pvSrcAddr,VOID *pvDstAddr);

PUBLIC VOID 
__GsnDma_Ch0Done_Isr_Patch();

PUBLIC VOID 
__GsnDma_Ch1Done_Isr_Patch();

PUBLIC VOID 
__GsnDma_Ssp1RxDone_Isr_Patch();

PUBLIC VOID 
__GsnDma_Ssp1TxDone_Isr_Patch();

PUBLIC VOID 
__GsnDma_Ssp0TxDone_Isr_Patch();

PUBLIC VOID 
__GsnDma_Ssp0RxDone_Isr_Patch();

PUBLIC VOID 
__GsnDma_Uart1TxDone_Isr_Patch();

PUBLIC VOID 
__GsnDma_Uart1RxDone_Isr_Patch();

PUBLIC VOID 
__GsnDma_Uart0TxDone_Isr_Patch();

PUBLIC VOID 
__GsnDma_Uart0RxDone_Isr_Patch();

VOID
GsnDma_CallBackRegister_Patch(GSN_DMA_T* ptGsnDma,DMACALLBACK_FP ptCallBackFunc, 
													VOID *ctx ,UINT32 channelID);

GSN_OSAL_ERROR_T
GsnDma_Open_Patch (GSN_DMA_T* ptGsnDma,GSN_DMACONFIG_T *ptConfig,
			 UINT32 channelsToConfigure);

GSN_OSAL_ERROR_T
GsnDma_IndividualClose_Patch (GSN_DMA_T* ptGsnDma,UINT32 channelsToClose);


#endif






