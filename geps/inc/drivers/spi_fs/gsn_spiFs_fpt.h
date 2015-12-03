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
* $RCSfile: gsn_spiFs_fpt.h,v $
*
* Description : This file contains public functions and definitions for SPI.
******************************************************************************
*/
#ifndef _GSN_SPI_HI_FPT_H_
#define _GSN_SPI_HI_FPT_H_

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
(*GsnSpiFS_Open_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle,
             GSN_SPI_FS_NUM_T spiPortNumber, GSN_SPI_FS_CONFIG_T* gsnSpiConfig);             
             

extern _RPST_ GsnSpiFS_Open_FP_T GsnSpiFS_Open_FP;




typedef PUBLIC GSN_STATUS
(*GsnSpiFS_Close_FP_T)(GSN_SPI_FS_HANDLE_T *spiHandle );

extern _RPST_  GsnSpiFS_Close_FP_T GsnSpiFS_Close_FP;




typedef PUBLIC VOID
(*GsnSpiFS_NvicEnable_FP_T)(GSN_SPI_FS_HANDLE_T *spiHandle);

extern _RPST_  GsnSpiFS_NvicEnable_FP_T GsnSpiFS_NvicEnable_FP;



typedef PUBLIC VOID
(*GsnSpiFS_NvicDisable_FP_T)(GSN_SPI_FS_HANDLE_T *spiHandle);

extern _RPST_ GsnSpiFS_NvicDisable_FP_T GsnSpiFS_NvicDisable_FP;



typedef PUBLIC VOID
(*GsnSpiFS_SerialClockRateSet_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle,
                        UINT8 clockFrequency );

extern _RPST_ GsnSpiFS_SerialClockRateSet_FP_T GsnSpiFS_SerialClockRateSet_FP;


                        
typedef PUBLIC UINT8
(*GsnSpiFS_SerialClockRateGet_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle);

extern _RPST_ GsnSpiFS_SerialClockRateGet_FP_T GsnSpiFS_SerialClockRateGet_FP;



typedef PUBLIC GSN_SPI_FS_OPERATINGMODE_T
(*GsnSpiFS_OperationModeGet_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle );

extern _RPST_ GsnSpiFS_OperationModeGet_FP_T GsnSpiFS_OperationModeGet_FP;



typedef PUBLIC VOID
(*GsnSpiFS_OperationModeSet_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle,
                         GSN_SPI_FS_OPERATINGMODE_T spiSlaveMasterModeSel );

extern _RPST_  GsnSpiFS_OperationModeSet_FP_T GsnSpiFS_OperationModeSet_FP;


                         
typedef PUBLIC GSN_SPI_FS_SOD_MODE_T
(*GsnSpiFS_SodGet_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle);

extern _RPST_ GsnSpiFS_SodGet_FP_T GsnSpiFS_SodGet_FP;



typedef PUBLIC VOID
(*GsnSpiFS_SodSet_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle,
                         GSN_SPI_FS_SOD_MODE_T sodMode );
                         
extern _RPST_ GsnSpiFS_SodSet_FP_T GsnSpiFS_SodSet_FP;



                         
typedef PUBLIC UINT8
(*GsnSpiFS_ClockDividerGet_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle );

extern _RPST_  GsnSpiFS_ClockDividerGet_FP_T  GsnSpiFS_ClockDividerGet_FP;





typedef PUBLIC VOID
(*GsnSpiFS_ClockDividerSet_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle,
                        UINT8 clkDivider );
extern _RPST_  GsnSpiFS_ClockDividerSet_FP_T  GsnSpiFS_ClockDividerSet_FP;  



                        
typedef PUBLIC GSN_SPI_FS_PROTOCOL_T
(*GsnSpiFS_ProtocolGet_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle );

extern _RPST_ GsnSpiFS_ProtocolGet_FP_T GsnSpiFS_ProtocolGet_FP;




typedef PUBLIC VOID
(*GsnSpiFS_ProtocolSet_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle,
                    GSN_SPI_FS_PROTOCOL_T spiProtocol );
extern _RPST_  GsnSpiFS_ProtocolSet_FP_T GsnSpiFS_ProtocolSet_FP;


                    
                    
typedef PUBLIC GSN_SPI_FS_CLOCKPOLARITY_T
(*GsnSpiFS_ClockPolarityGet_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle );

extern _RPST_ GsnSpiFS_ClockPolarityGet_FP_T GsnSpiFS_ClockPolarityGet_FP;



typedef PUBLIC VOID
(*GsnSpiFS_ClockPolaritySet_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle,
                         GSN_SPI_FS_CLOCKPOLARITY_T  spiClkPolarity );
extern _RPST_  GsnSpiFS_ClockPolaritySet_FP_T  GsnSpiFS_ClockPolaritySet_FP;




typedef PUBLIC GSN_SPI_FS_CLOCKPHASE_T
(*GsnSpiFS_ClockPhaseGet_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle );

extern _RPST_ GsnSpiFS_ClockPhaseGet_FP_T GsnSpiFS_ClockPhaseGet_FP;



typedef PUBLIC VOID
(*GsnSpiFS_ClockPhaseSet_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle,
                      GSN_SPI_FS_CLOCKPHASE_T  spiClkPhase );
                      
extern _RPST_ GsnSpiFS_ClockPhaseSet_FP_T GsnSpiFS_ClockPhaseSet_FP;


                      
typedef PUBLIC GSN_SPI_FS_LoopBack_MODE_T
(*GsnSpiFS_LoopBackGet_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle );

extern _RPST_ GsnSpiFS_LoopBackGet_FP_T GsnSpiFS_LoopBackGet_FP;




typedef PUBLIC VOID
(*GsnSpiFS_LoopBackConfig_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle,
                         GSN_SPI_FS_LoopBack_MODE_T  LoopBack );
                         
extern _RPST_ GsnSpiFS_LoopBackConfig_FP_T GsnSpiFS_LoopBackConfig_FP;



                         
typedef PUBLIC VOID
(*GsnSpiFS_LoopBackClear_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle,
                         GSN_SPI_FS_LoopBack_MODE_T  LoopBack);

extern _RPST_  GsnSpiFS_LoopBackClear_FP_T  GsnSpiFS_LoopBackClear_FP;  


                         
                         
typedef PUBLIC GSN_SPI_FS_DATAWORDSIZE_T
(*GsnSpiFS_DataWordSizeGet_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle );

extern _RPST_ GsnSpiFS_DataWordSizeGet_FP_T GsnSpiFS_DataWordSizeGet_FP;




typedef PUBLIC VOID
(*GsnSpiFS_DataWordSizeSet_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle,
                        GSN_SPI_FS_DATAWORDSIZE_T  spiDataSize );
                        
extern _RPST_ GsnSpiFS_DataWordSizeSet_FP_T GsnSpiFS_DataWordSizeSet_FP;




typedef PUBLIC UINT32
(*GsnSpiFS_SlaveRead_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle,
                       GSN_SPI_FS_TXRXCHANNEL_T *rx );
                       
extern _RPST_ GsnSpiFS_SlaveRead_FP_T GsnSpiFS_SlaveRead_FP;




typedef PUBLIC UINT32
(*GsnSpiFS_SlaveWrite_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle,
                       GSN_SPI_FS_TXRXCHANNEL_T *tx );
                       
extern _RPST_ GsnSpiFS_SlaveWrite_FP_T GsnSpiFS_SlaveWrite_FP;




typedef PUBLIC VOID
(*__GsnSpi0FS_Isr_FP_T)( );

extern _RPST_ __GsnSpi0FS_Isr_FP_T __GsnSpi0FS_Isr_FP;




typedef PUBLIC VOID
(*__GsnSpi1FS_Isr_FP_T)( );

extern _RPST_ __GsnSpi1FS_Isr_FP_T __GsnSpi1FS_Isr_FP;




typedef PUBLIC VOID
(*GsnSpiFS_Isr_FP_T)( GSN_SPI_FS_HANDLE_T *spiHandle );

extern _RPST_ GsnSpiFS_Isr_FP_T GsnSpiFS_Isr_FP;




typedef PUBLIC VOID
(*GsnSpi0FS_TxCallBack_FP_T)( VOID *ctx, UINT32 channelID);

extern _RPST_ GsnSpi0FS_TxCallBack_FP_T GsnSpi0FS_TxCallBack_FP;




typedef PUBLIC VOID
(*GsnSpi0FS_RxCallBack_FP_T)( VOID *ctx, UINT32 channelID);

extern _RPST_ GsnSpi0FS_RxCallBack_FP_T GsnSpi0FS_RxCallBack_FP;




typedef PUBLIC VOID
(*GsnSpi1FS_TxCallBack_FP_T)( VOID *ctx, UINT32 channelID);
 
extern _RPST_ GsnSpi1FS_TxCallBack_FP_T GsnSpi1FS_TxCallBack_FP;





typedef PUBLIC VOID
(*GsnSpi1FS_RxCallBack_FP_T)( VOID *ctx, UINT32 channelID);

extern _RPST_ GsnSpi1FS_RxCallBack_FP_T GsnSpi1FS_RxCallBack_FP;



typedef PUBLIC VOID
(*GsnSpiFS_PauseRingBuff_FP_T)(GSN_SPI_FS_HANDLE_T *spiHandle );

extern _RPST_ GsnSpiFS_PauseRingBuff_FP_T GsnSpiFS_PauseRingBuff_FP;




typedef PUBLIC VOID
(*GsnSpiFS_ResumeRingBuff_FP_T)(GSN_SPI_FS_HANDLE_T *spiHandle);

extern _RPST_ GsnSpiFS_ResumeRingBuff_FP_T GsnSpiFS_ResumeRingBuff_FP;




typedef PUBLIC VOID
(*GsnSpiFS_FlushRingBuff_FP_T)(GSN_SPI_FS_HANDLE_T *spiHandle);

extern _RPST_ GsnSpiFS_FlushRingBuff_FP_T GsnSpiFS_FlushRingBuff_FP;


#ifdef  __cplusplus
    }
#endif

#endif