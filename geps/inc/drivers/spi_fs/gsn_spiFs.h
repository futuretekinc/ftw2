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
*
* $RCSfile: gsn_spiFs.h,v $
*
* Description : This file contains public functions and definitions for SPI.
******************************************************************************
*/
#ifndef _GSN_SPI_HI_H_
#define _GSN_SPI_HI_H_

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************************************************
*  File inclusion
*****************************************************************************/

#include "drivers/spi_fs/buffer.h"

#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
#include "drivers/clk_ctl/gsn_clk_ctl.h"

/**
 *****************************************************************************
 * @file gsn_spi.h
 * @brief GSN SPI API Definitions.
 *    This file contains the public APIs  definitions and
 *    structures of SPI driver.
 ****************************************************************************/


/**
 *****************************************************************************
 * @ingroup driversdoc
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnSpi GSN SPI API
 *    This group contains public definitions and functions providing access
 *    to the GS2000's SPI.
 ****************************************************************************/

/**
 *****************************************************************************
 *
 * @}
 *****************************************************************************/

#define SET_INTERRUPTS 0x000F
#define RX_STATUS 0x0004
#define TX_STATUS 0x0008
#define RT_STATUS 0x0002
#define ROR_STATUS 0x0001
#define ROR_CLEAR 0x2
#define RT_CLEAR 0x1
#define SPI_FS_DMA_RX_TRANSFER_MIN 32
#define SPI_FS_DMA_TX_TRANSFER_MIN 32

#define SPI_DMA_CHANNELS 0x0000000c

/* SPI CPSDIV values */
#define SPI_FS_CPSDIV_0    0  
#define SPI_FS_CPSDIV_1    1
#define SPI_FS_CPSDIV_2    2
#define SPI_FS_CPSDIV_4    4
#define SPI_FS_CPSDIV_8    8
#define SPI_FS_CPSDIV_16   16
#define SPI_FS_CPSDIV_32   32
#define SPI_FS_CPSDIV_64   64
#define SPI_FS_CLK_EN       1


#define  GSN_SPI_FS_ESC_CHAR               (0xFB)    /* Start transmission indication */
#define  GSN_SPI_FS_IDLE_CHAR              (0xF5)    /* synchronous IDLE */
#define  GSN_SPI_FS_XOFF_CHAR              (0xFA)    /* Stop transmission indication */
#define  GSN_SPI_FS_XON_CHAR               (0xFD)    /* Start transmission indication */
#define  GSN_SPI_FS_INVALID_CHAR_ALL_ONE   (0xFF)    /* Invalid character possibly recieved during reboot */
#define  GSN_SPI_FS_INVALID_CHAR_ALL_ZERO  (0x00)    /* Invalid character possibly recieved during reboot */
#define  GSN_SPI_FS_READY_ACK              (0xF3)    /* SPI link ready */
#define  GSN_SPI_FS_CTRL_BYTE_MASK         (0x80)    /* Control byte mask */

   
   
   
   
#define WRITE_REQUEST          0x01       
#define READ_REQUEST           0x02
#define DATA_FROM_HOST         0x03
  
#define READ_RESPONSE_OK       0x12
#define READ_RESPONSE_NOK      0x14
#define WRITE_RESPONSE_OK      0x11
#define WRITE_RESPONSE_NOK     0x13 
#define DATA_FROM_NODE         0x15
   
#define PENDING_DATA_ON_GS2000 0x01  
   
#define HEADER_LENGTH          8   
  
   
   
   


/****************************************************************************
* Type Definitions
****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI Call Back function.
 *
 *    This call back function takes two arguments,
 *    - argument 1 is Status
 *    - argument 2 is context pointer
 *
 * @param data    -IN SPI number of bytes transmitted or received
 * @param context -IN call back context pointer
 * @see  GSN_SPI_CALLBACK_FUNC_T.
 *
 ****************************************************************************/
typedef VOID ( *GSN_SPI_FS_CALLBACK_FUNC_T )( VOID *context, UINT32 numberOfBytes );

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI Call Back function for block read
 *
 *    This call back function takes two arguments,
 *    - argument 1 is context
 *    - argument 2 is total bytes read
 *
 * @param data    -IN SPI status
 * @param context -IN call back context pointer
 * @see  GSN_SPI_BLOCKREAD_CALLBACK_FUNC_T.
 *
 ****************************************************************************/

typedef VOID ( *GSN_SPI_FS_BLOCKREAD_CALLBACK_FUNC_T ) ( VOID*, UINT32 );


/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI Enum port types.
 *
 *    This enum defines SPI port number and total number of ports.
 * @see  GSN_SPI_NUM_T.
 ****************************************************************************/
 typedef VOID ( *GSN_SPI_FS_INTR_CALLBACK_FUNC_T )( VOID *context, UINT32 numberOfBytes,UINT32 status );

typedef enum
{
    SPI_FS_NUM_0      = 0,
    SPI_FS_NUM_1      = 1,

    GSN_FS_SPI_NUM_MSPI   = SPI_NUM_0,   /**< Alternate Name is MSPI */
    GSN_FS_SPI_NUM_SSPI   = SPI_NUM_1,   /**< Alternate Name is SSPI */
    GSN_FS_TOTAL_SPIS     = SPI_NUM_1
} GSN_SPI_FS_NUM_T;


/**
 ****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI protocol types.
 *
 *    This enum defines SPI Protocol types
 *    GSN_SPI_PROTOCOL_MOTOROLA stands for Motorola SPI
 *    GSN_SPI_PROTOCOL_TI stands for Texas Instruments SSP
 *    GSN_SPI_PROTOCOL_NATIONAL National Semiconductors Microwire
 * @see  GSN_SPI_PROTOCOL_T.
 ***************************************************************************/
typedef enum GSN_SPI_FS_PROTOCOL
{
    GSN_SPI_FS_PROTOCOL_MOTOROLA,
    GSN_SPI_FS_PROTOCOL_TI,
    GSN_SPI_FS_PROTOCOL_NATIONAL
} GSN_SPI_FS_PROTOCOL_T;


typedef enum GSN_SPI_FS_RX_FLW_CTRL_STATE
{/*Note : Do not modify these values  */
GSN_SPI_FS_RX_FLW_CTRL_READY           = 0x01,   /**< system is ready to recieve data (its default state) */
GSN_SPI_FS_RX_FLW_CTRL_STOP_PENDING    = 0x02,   /**<  threshold cross over detected but GS_SPI_XOFF yet to be transmitted */
GSN_SPI_FS_RX_FLW_CTRL_STOP            = 0x04,   /**<  threshold cross over detected and GS_SPI_XOFF	transmitted to peer system */
GSN_SPI_FS_RX_FLW_CTRL_READY_PENDING   = 0x08   /**<  system is ready to recieve data but GS_SPI_XON yet to be transmitted */

}GSN_SPI_FS_RX_FLW_CTRL_STATE_T;
/**
 ****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI clock polarity types.
 *
 *    This enum defines SPI clock polarity of the inactive serial clock
 *    The field is only valid for Motorola SPI protocol.
 *    GSN_SPI_CLK_POL_ACTIVELOW  - Inactive state of serial clock is low
 *    GSN_SPI_CLK_POL_ACTIVEHIGH - Inactive state of serial clock is high
 *
 * @see  GSN_SPI_CLOCKPOLARITY_T.
 ****************************************************************************/
typedef enum GSN_SPI_FS_CLOCKPOLARITY
{
    GSN_SPI_FS_CLK_POL_INACTIVELOW,
    GSN_SPI_FS_CLK_POL_INACTIVEHIGH
} GSN_SPI_FS_CLOCKPOLARITY_T;


/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI serial Clock Phase types.
 *
 *    This Enum defines the phase of the serial clock determining the
 *    relationship of the serial clock and the slave select signal.
 *    Data is either captured on the first toggling edge of the serial
 *    clock (GSN_SPI_CLK_PHASE_0) or the second edge (GSN_SPI_CLK_PHASE_180)
 *    after the falling edge of slave select signal. The field is only
 *    valid for Motorola SPI protocol
 *    GSN_SPI_CLK_PHASE_0 - serial clock toggles in middle of first data bit
 *    GSN_SPI_CLK_PHASE_180- serial clock toggles at start of first data bit
 *
 *    This enum defines SPI clock phase.
 * @see  GSN_SPI_CLOCKPHASE_T.
 ****************************************************************************/
typedef enum GSN_SPI_FS_CLOCKPHASE
{
    GSN_SPI_FS_CLK_PHASE_0,
    GSN_SPI_FS_CLK_PHASE_180
} GSN_SPI_FS_CLOCKPHASE_T;


/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI data word size types.
 *
 *     This Enum defines the size of data words to be used for next transfer.
 *     If the data word size is a sub-multiple of the FIFO size it is possible
 *     to transfer multiple words per FIFO location.
 *     GSN_SPI_DATAWORDSIZE_4    4 bit to GSN_SPI_DATAWORDSIZE_16  16 bit
 *
 * @see  GSN_SPI_DATAWORDSIZE_T.
 ****************************************************************************/
typedef enum GSN_SPI_FS_DATAWORDSIZE
{
	GSN_SPI_FS_DATAWORDSIZE_8 = 7,
	GSN_SPI_FS_DATAWORDSIZE_16 = 15
} GSN_SPI_FS_DATAWORDSIZE_T;


/**
 ****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI operating mode types.
 *
 *    This enum defines the type of SPI operating modes.
 * @see  GSN_SPI_OPERATINGMODE_T.
 ****************************************************************************/
typedef enum GSN_SPI_FS_OPERATINGMODE
{
	GSN_SPI_FS_OPERATION_MODE_MASTER,
	GSN_SPI_FS_OPERATION_MODE_SLAVE
} GSN_SPI_FS_OPERATINGMODE_T;


/**
 ****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI DMA TX mode types.
 *
 *    This enum defines the type of SPI DMA TX modes.
 * @see  GSN_SPI_DMA_TX_MODE_T.
 ****************************************************************************/
typedef enum GSN_SPI_FS_DMA_TX_MODE
{
	GSN_SPI_FS_DMA_TX_CLEAR,
	GSN_SPI_FS_DMA_TX_SET
} GSN_SPI_FS_DMA_TX_MODE_T;


/**
 ****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI DMA RX mode types.
 *
 *    This enum defines the type of SPI DMA RX modes.
 * @see  GSN_SPI_DMA_RX_MODE_T.
 ****************************************************************************/
typedef enum GSN_SPI_FS_DMA_RX_MODE
{
	GSN_SPI_FS_DMA_RX_CLEAR,
	GSN_SPI_FS_DMA_RX_SET
} GSN_SPI_FS_DMA_RX_MODE_T;


/**
 ****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI SSP enable or disable mode types.
 *
 *    This enum defines enables or clear SSP.
 * @see  GSN_SPI_DMA_RX_MODE_T.
 ****************************************************************************/
typedef enum GSN_SPI_FS_SSE_MODE
{
	GSN_SPI_FS_SSE_CLEAR,
	GSN_SPI_FS_SSE_SET
} GSN_SPI_FS_SSE_MODE_T;


/**
 ****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI LoopBack mode set.
 *
 *    This enum defines the LoopBack mode set or clear.
 * @see  GSN_SPI_LoopBack_MODE_T.
 ****************************************************************************/
typedef enum GSN_SPI_FS_LoopBack_MODE
{
	GSN_SPI_FS_LoopBack_CLEAR,
	GSN_SPI_FS_LoopBack_SET
} GSN_SPI_FS_LoopBack_MODE_T;

/**
 ****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI Slave Mode Output Disable mode set.
 *
 *    This enum defines the SOD mode set or clear.
 * @see  GSN_SPI_SOD_MODE_T.
 ****************************************************************************/
typedef enum GSN_SPI_FS_SOD_MODE
{
	GSN_SPI_FS_SOD_CLEAR,
	GSN_SPI_FS_SOD_SET
} GSN_SPI_FS_SOD_MODE_T;

/**
 ****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI DMA mode set.
 *
 *    This enum defines the DMA mode set or clear.
 * @see  GSN_SPI_DMA_MODE_T.
 ****************************************************************************/
typedef enum GSN_SPI_FS_DMA_MODE
{
	GSN_SPI_FS_DMA_CLEAR,
	GSN_SPI_FS_DMA_SET
} GSN_SPI_FS_DMA_MODE_T;


typedef enum GSN_SPI_FS_DEVICE_STATE
{
    GSN_SPI_FS_UNINITIALIZED,
    GSN_SPI_FS_INITIALIZED,
    GSN_SPI_FS_TX_DONE,
    GSN_SPI_FS_RX_DONE,
    GSN_SPI_FS_READ_PROGRESS,
    GSN_SPI_FS_WRITE_PROGRESS,
    GSN_SPI_FS_READ_FINISHED,
    GSN_SPI_FS_WRITE_FINISHED,
    GSN_SPI_FS_RX_ERROR,
    GSN_SPI_FS_COMPLETED,
    GSN_SPI_FS_CLOSED
} GSN_SPI_FS_DEVICE_STATE_T;


typedef enum GSN_SPIDMA_FS_STATE
{
    GSN_SPIDMA_FS_IDLE_STATE,
    GSN_SPIDMA_FS_CMD_RECEIVING_STATE,
    GSN_SPIDMA_FS_CMD_PROCESSING_STATE,
    GSN_SPIDMA_FS_RESP_SENDING_STATE,
    GSN_SPIDMA_FS_DATA_RECEPTION_STATE
    
    
}GSN_SPIDMA_FS_STATE_T;

/**
 ****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI Clock selection.
 *
 *    This enum defines the 3 different SPI clock selections.
 * @see  GSN_SPI_CLK_SEL_T.
 ****************************************************************************/
typedef enum GSN_SPI_FS_CLK_SEL
{
    GSN_SPI_FS_CLK_HSRC,
    GSN_SPI_FS_CLK_XTAL,
    GSN_SPI_FS_CLK_PLL,
}GSN_SPI_FS_CLK_SEL_T;


/**
 ****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI data transfer structure.
 *
 *    This structure defines a SPI data pointer and call back function info
 *
 * @see  GSN_SPI_TXRXCHANNEL_T.
 ****************************************************************************/
typedef struct GSN_SPI_FS_TXRXCHANNEL
{
    BUFFER8             buffer;         /**< SPI read write buffer        */
    UINT32              numberOfBytes;
    VOID*               contextCB;      /**< context pointer for CallBack */
    GSN_SPI_FS_CALLBACK_FUNC_T funcCB;         /**< CallBack function            */
} GSN_SPI_FS_TXRXCHANNEL_T;


/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI read write transfer structure.
 *
 *    This structure defines a SPI data pointer and call back function information
 *    for each channel. For more detail, please see GSN_SPI_TXRXCHANNEL_T
 *
 * @see  GSN_SPI_RW_ARGS_T.
 *****************************************************************************/
typedef struct GSN_SPI_FS_RW_ARGS
{
    GSN_SPI_FS_TXRXCHANNEL_T   tx;             /**< SPI transmit channel      */
    GSN_SPI_FS_TXRXCHANNEL_T   rx;             /**< SPI receive channel       */
} GSN_SPI_FS_RW_ARGS_T ;



typedef struct GSN_SPI_FS_RX_RING_BUFF
{
    UINT8*               spiBuffer;
    UINT8*               spiBufferStart;
    UINT16                dataCountInBuff;
    UINT16                freeSpaceInRingBuff;
    UINT16               spiBuffSize;
    UINT16               spiBuffRunSize;
    UINT16               spiBuffHead;
    UINT16               spiBuffTail;
    UINT16               spiBuffSizeMinusOne;
    UINT8                ringBuffPose; 
    UINT8                spiRxBufferWrapAround;
} GSN_SPI_FS_RX_RING_BUFF_T;


/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI structure.
 *
 *    This structure defines SPI data pointer and base register
 *
 * @see  GSN_SPI_T.
 *****************************************************************************/
typedef struct GSN_SPI_FS
{
    UINT32                    *pReg;             /**< SPI base register         */
    GSN_SPI_FS_RW_ARGS_T         spiRWArg;          /**< SPI Tx Rx struct          */
    GSN_OSAL_SEM_T            synchReadSemId;    /**< SPI read synch semaphore  */
    GSN_OSAL_SEM_T            synchWriteSemId;   /**< SPI write synch semaphore */
    GSN_OSAL_SEM_T            gpioWriteSemId;    /**< SPI gpio handling semaphore */
    UINT32                    spiStatus;         /**< SPI status holder register*/
    UINT8		      spiInitStatus;	 /**< SPI initialised or NOT    */
    
    GSN_SPI_FS_DEVICE_STATE_T    spiDeviceRxState;
    GSN_SPI_FS_DEVICE_STATE_T    spiDeviceTxState;
    
    GSN_SPIDMA_FS_STATE_T     spiDmaState;
    GSN_SPI_FS_RX_RING_BUFF_T    spiRxBuf;
    UINT16                    actualBytesRead;
    UINT8                     dataWordSize;
    VOID                      *spiDma;
    UINT8                    dummyWrite;
    
    VOID                      *rxDmaPingChannelConfig ;
    VOID                      *rxDmaPongChannelConfig ;
    VOID                      *txDmaPingChannelConfig ;
    VOID                      *txDmaPongChannelConfig; 
    VOID                      *dmaMemChannelConfig; 
    
    
    GSN_SPI_FS_OPERATINGMODE_T   spiMode;          /**< SPI mode status    */
    UINT8                     spiTxWithDma;
    UINT8                     spiRxWithDma;
    GSN_SPI_FS_INTR_CALLBACK_FUNC_T txIntrCB;
    GSN_SPI_FS_INTR_CALLBACK_FUNC_T rxIntrCB;
    UINT16 idlePattern;
    UINT8 byteStuff;
    GSN_SPI_FS_RX_FLW_CTRL_STATE_T spiRxState;
    UINT8				  spiTxStop;			  /*<  0 - peer system is ready to recieve data
												    ** < 1 - peer system is NOT ready to recieve data */
	UINT8                 spiFlowCtrlEnable;       /**<1 -SPI flow control ENABLED
	                                                                                  **<0 -SPI flow control DISABLED   */
	UINT8				  spiReadyAck;		       /*< 0 - Ready ack transmit is not pending */
	UINT8                 spiWriteWaitFlag;
	UINT16                spiAvailableBytes;
	UINT16                spiFlowCtrlThreshHigh;
	UINT16                spiFlowCtrlThreshLow;
        
        
    UINT8  spiSohReceived;
    UINT16  spiHeaderLen;
    UINT8  spiHeaderClass;
    UINT8  spiHeaderRecvBytes;  
    UINT8  spiHeaderChekSum;
    UINT8  prevHeaderStatus;
    LONG64  spiGpioBitMap;
    UINT8  noOfBytesReceived;
    UINT8  noOfBytesTransmited;
    
    UINT8 txResponseBuff[1024];
    UINT8 rxResponseBuff[16];
    UINT8 cmdRecvBuff[1024];
    

} GSN_SPI_FS_T;


/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI configuration structure.
 *
 *    This structure defines SPI configuration parameters
 *
 * @see  GSN_SPI_CONFIG_T.
 *****************************************************************************/
typedef struct GSN_SPI_FS_CONFIG
{
    GSN_SPI_FS_OPERATINGMODE_T   spiMode;          /**< SPI mode status    */
    GSN_SPI_FS_PROTOCOL_T        spiProtocol;      /**< SPI protocol type  */
    GSN_SPI_FS_CLOCKPOLARITY_T   clockPolarity;    /**< SPI clock polarity */
    GSN_SPI_FS_CLOCKPHASE_T      clockPhase;       /**< SPI clock phase    */
    GSN_SPI_FS_DATAWORDSIZE_T    dataWordSize;     /**< SPI data word size */
    GSN_SPI_FS_LoopBack_MODE_T   LoopBack;         /**< SPI LoopBack       */
    GSN_SPI_FS_DMA_MODE_T        dmaMode;          /**< SPI DMA enable     */
    GSN_SPI_FS_SOD_MODE_T        sodMode;          /**< SPI Slave o/p disable mode */
    UINT8		      SerialclockRate;  /**< SPI serial clk rate*/
    UINT8                     clockDivider;     /**< SPI clock divider  */
    GSN_SPI_FS_CLK_SEL_T         clockSelect;       /**< SPI clock Selction  */
    GSN_CLK_CTL_CTX_T        *pclkCtlCtx;         /**< Clock Context      */
    GSN_SPI_FS_RW_ARGS_T         spiRWArg;          /**< SPI Tx Rx struct          */
    UINT8*               spiRxBuffer;        /**< Rx buffer pointer for slave  */
    UINT32               spiRxBuffSize;      /**< Rx buffer size */
    /* application call back for tx and rx interrupt
     */
    GSN_SPI_FS_INTR_CALLBACK_FUNC_T txIntrCB;
    GSN_SPI_FS_INTR_CALLBACK_FUNC_T rxIntrCB;
    UINT8 idleChar;
    UINT8 byteStuff;
    LONG64 spiGpioBitMap;
    UINT8 spiGpioNum;

} GSN_SPI_FS_CONFIG_T;

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Gsn SPI Structure.
 *
 *    This structure defines an SPI handle, which holds SPI configuration and data
 *    parameters
 *
 * @see  GSN_SPI_HANDLE_T.
 *****************************************************************************/
typedef struct GSN_SPI_FS_HANDLE
{
    GSN_SPI_FS_T         spi;            /**< SPI parameter */
    UINT8                     clockDivider;       /**< SPI clock divider  */
    GSN_SPI_FS_CLK_SEL_T         clockSelect;        /**< SPI clock Selction  */
    GSN_CLK_CTL_CTX_T        *pclkCtlCtx;         /**< Clock Context      */
    GSN_SPI_FS_DMA_MODE_T        dmaMode;            /**< SPI DMA enable     */
}GSN_SPI_FS_HANDLE_T;


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
 * @param gsnSpiConfig        - IN SPI port configuration
 *
 * @return GSN_SUCCESS        - Initialization successful.
 * @return GSN_FAILURE        - Initialization failed.
 *
 ****************************************************************************/
PUBLIC GSN_STATUS
GsnSpiFS_Open( GSN_SPI_FS_HANDLE_T *spiHandle,
             GSN_SPI_FS_NUM_T spiPortNumber, GSN_SPI_FS_CONFIG_T* gsnSpiConfig);

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Driver SOD set or clear register.
 *
 * @param spiHandle          - IN pointer to handle
 * @param sodMode            - IN SOD mode enum
 *
 * @return VOID
 *****************************************************************************/
PUBLIC VOID
GsnSpiFS_SodSet( GSN_SPI_FS_HANDLE_T *spiHandle,
                         GSN_SPI_FS_SOD_MODE_T sodMode );

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Driver SOD Get register.
 *
 * @param spiHandle          - IN pointer to handle
 *
 * @return GSN_SPI_SOD_MODE_T
 *****************************************************************************/
PUBLIC GSN_SPI_FS_SOD_MODE_T
GsnSpiFS_SodGet( GSN_SPI_FS_HANDLE_T *spiHandle);

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI NVIC interrupts enable.
 *
 * @param spiHandle          - IN pointer to handle
 *
 * @return VOID
 *****************************************************************************/
PUBLIC VOID
GsnSpiFS_NvicEnable(GSN_SPI_FS_HANDLE_T *spiHandle);

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI NVIC interrupts Disable.
 *
 * @param spiHandle          - IN pointer to handle
 *
 * @return VOID
 *****************************************************************************/
PUBLIC VOID
GsnSpiFS_NvicDisable(GSN_SPI_FS_HANDLE_T *spiHandle);

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
PUBLIC GSN_STATUS
GsnSpiFS_Close( GSN_SPI_FS_HANDLE_T *spiHandle );

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
PUBLIC UINT8
GsnSpiFS_SerialClockRateGet( GSN_SPI_FS_HANDLE_T *spiHandle);


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
 * @return VOID.
 *****************************************************************************/
PUBLIC VOID
GsnSpiFS_SerialClockRateSet( GSN_SPI_FS_HANDLE_T *spiHandle,
                        UINT8 clockFrequency );


/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Driver LopBack mode GET.
 *
 *     This function allows getting the LBM
 *
 * @param spiHandle              - IN pointer to handle.
 * @return GSN_SPI_LoopBack_MODE_T  - mode 
 *****************************************************************************/
PUBLIC GSN_SPI_FS_LoopBack_MODE_T
GsnSpiFS_LoopBackGet( GSN_SPI_FS_HANDLE_T *spiHandle );

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Driver LopBack mode SET.
 *
 *     This function allows setting the LBM
 *
 * @param spiHandle              - IN pointer to handle.
 * @param LoopBack               - IN Loopback mode
 * @return VOID.
 *****************************************************************************/
PUBLIC VOID
GsnSpiFS_LoopBackConfig( GSN_SPI_FS_HANDLE_T *spiHandle,
                         GSN_SPI_FS_LoopBack_MODE_T  LoopBack );

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Driver LopBack mode Clear.
 *
 *     This function allows setting the LBM
 *
 * @param spiHandle              - IN pointer to handle.
 * @param LoopBack               - IN Loopback mode
 * @return VOID.
 *****************************************************************************/
PUBLIC VOID
GsnSpiFS_LoopBackClear( GSN_SPI_FS_HANDLE_T *spiHandle,
                         GSN_SPI_FS_LoopBack_MODE_T  LoopBack );


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
PUBLIC GSN_SPI_FS_OPERATINGMODE_T
GsnSpiFS_OperationModeGet( GSN_SPI_FS_HANDLE_T *spiHandle );

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Driver set operation mode.
 *
 *     This function allows setting the operation mode with the specified
 *     value in spiSlaveMasterModeSel.
 * @param spiHandle              - IN pointer to handle.
 * @param spiSlaveMasterModeSel  - IN mode selection.
 * @return VOID.
 *****************************************************************************/
PUBLIC VOID
GsnSpiFS_OperationModeSet( GSN_SPI_FS_HANDLE_T *spiHandle,
                         GSN_SPI_FS_OPERATINGMODE_T spiSlaveMasterModeSel );


/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief Get SPI clock Divider.
 *
 *    This function returns SPI clock divider value; range from 1 to 255
 * @param spiHandle           - IN pointer to handle
 * @return UINT8              - clock divider value range from 1 to 255
 ****************************************************************************/
PUBLIC UINT8
GsnSpiFS_ClockDividerGet( GSN_SPI_FS_HANDLE_T *spiHandle );


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
 * @return VOID.
 ****************************************************************************/
PUBLIC VOID
GsnSpiFS_ClockDividerSet( GSN_SPI_FS_HANDLE_T *spiHandle,
                        UINT8 clkDivider );


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
PUBLIC GSN_SPI_FS_PROTOCOL_T
GsnSpiFS_ProtocolGet( GSN_SPI_FS_HANDLE_T *spiHandle );


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
 * @return VOID.
 ****************************************************************************/
PUBLIC VOID
GsnSpiFS_ProtocolSet( GSN_SPI_FS_HANDLE_T *spiHandle,
                    GSN_SPI_FS_PROTOCOL_T spiProtocol );


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
PUBLIC GSN_SPI_FS_CLOCKPOLARITY_T
GsnSpiFS_ClockPolarityGet( GSN_SPI_FS_HANDLE_T *spiHandle );


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
 * @return VOID.
 ****************************************************************************/
PUBLIC VOID
GsnSpiFS_ClockPolaritySet( GSN_SPI_FS_HANDLE_T *spiHandle,
                         GSN_SPI_FS_CLOCKPOLARITY_T  spiClkPolarity );


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
PUBLIC GSN_SPI_FS_CLOCKPHASE_T
GsnSpiFS_ClockPhaseGet( GSN_SPI_FS_HANDLE_T *spiHandle );


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
 * @return VOID.
 ****************************************************************************/
PUBLIC VOID
GsnSpiFS_ClockPhaseSet( GSN_SPI_FS_HANDLE_T *spiHandle,
                      GSN_SPI_FS_CLOCKPHASE_T  spiClkPhase );

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
PUBLIC GSN_SPI_FS_DATAWORDSIZE_T
GsnSpiFS_DataWordSizeGet( GSN_SPI_FS_HANDLE_T *spiHandle );


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
 * @return VOID.
 ****************************************************************************/
PUBLIC VOID
GsnSpiFS_DataWordSizeSet( GSN_SPI_FS_HANDLE_T *spiHandle,
                        GSN_SPI_FS_DATAWORDSIZE_T  spiDataSize );




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
 * @return UINT32
 *****************************************************************************/

PUBLIC UINT32
GsnSpiFS_SlaveWrite( GSN_SPI_FS_HANDLE_T *spiHandle,
                       GSN_SPI_FS_TXRXCHANNEL_T *tx );


/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Slave Read
 *
 *    This API is called from the APP side if needed for half Duplex receive only
 *
 * @param spiHandle         - IN pointer to handle.
 * @param rx			    - IN pointer to GSN_SPI_TXRXCHANNEL_T
 *								initialisation parameters for  receive
 * @return UINT32
 *****************************************************************************/

PUBLIC UINT32
GsnSpiFS_SlaveRead( GSN_SPI_FS_HANDLE_T *spiHandle,
                       GSN_SPI_FS_TXRXCHANNEL_T *rx );


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
PUBLIC GSN_STATUS
GsnSpiFS_SlaveReadWrite(GSN_SPI_FS_HANDLE_T *spiHandle ,
                      GSN_SPI_FS_RW_ARGS_T *spiRW);


/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI ISR
 *
 *    This interrupt service routine is called by the
 *    interrupt handler.
 * @param spiHandle         - IN pointer to handle.
 * @return VOID
 *****************************************************************************/
PUBLIC VOID
GsnSpiFS_Isr( GSN_SPI_FS_HANDLE_T *spiHandle );

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI ISR
 *
 *    This interrupt service routine is called by the
 *    interrupt handler from nvic when using SPI_0.
 * @return VOID
 *****************************************************************************/
PUBLIC VOID
__GsnSpi0FS_Isr( );


/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI ISR
 *
 *    This interrupt service routine is called by the
 *    interrupt handler from nvic when using SPI_1.
 * @return VOID
 *****************************************************************************/
PUBLIC VOID
__GsnSpi1FS_Isr( );



/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI-0 Dma Tx done ISR
 *
 *    This interrupt service routine is called by the
 *    interrupt handler from nvic when using SPI.
 * @param ctx    - context
 * @param channelID - channel ID
 * @return VOID
 *****************************************************************************/
PUBLIC VOID
GsnSpi0FS_TxCallBack( VOID *ctx, UINT32 channelID);

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI-0 Dma Rx done ISR
 *
 *    This interrupt service routine is called by the
 *    interrupt handler from nvic when using SPI.
 * @param ctx    - context
 * @param channelID - channel ID
 * @return VOID
 *****************************************************************************/
PUBLIC VOID
GsnSpi0FS_RxCallBack( VOID *ctx, UINT32 channelID);

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI-1 Dma Tx done ISR
 *
 *    This interrupt service routine is called by the
 *    interrupt handler from nvic when using SPI.
 * @param ctx    - context
 * @param channelID - channel ID
 * @return VOID
 *****************************************************************************/
PUBLIC VOID
GsnSpi1FS_TxCallBack( VOID *ctx, UINT32 channelID);

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI-1 Dma Rx done ISR
 *
 *    This interrupt service routine is called by the
 *    interrupt handler from nvic when using SPI.
 * @param ctx    - context
 * @param channelID - channel ID
 * @return VOID
 *****************************************************************************/
PUBLIC VOID
GsnSpi1FS_RxCallBack( VOID *ctx, UINT32 channelID);

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI 
 * @param spiHandle         - IN pointer to handle.
 * @return VOIDPause RingBuff
 *
 *    This API Pauses writting data into Ring buffer.
 *
 *****************************************************************************/
PUBLIC VOID
GsnSpiFS_PauseRingBuff(GSN_SPI_FS_HANDLE_T *spiHandle );

/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Resume RingBuff
 *
 *    This API Resumes writting data into Ring buffer.
 *
 * @param spiHandle         - IN pointer to handle.
 * @return VOID
 *****************************************************************************/
PUBLIC VOID
GsnSpiFS_ResumeRingBuff(GSN_SPI_FS_HANDLE_T *spiHandle);



/**
 *****************************************************************************
 * @ingroup GsnSpi
 * @brief SPI Flush RingBuff
 *
 *    This API Flushes data from Ring buffer.
 *
 * @param spiHandle         - IN pointer to handle.
 * @return VOID
 *****************************************************************************/
PUBLIC VOID
GsnSpiFS_FlushRingBuff(GSN_SPI_FS_HANDLE_T *spiHandle);



PUBLIC GSN_STATUS
GsnSpiFS_MasterReadWrite( GSN_SPI_FS_HANDLE_T *spiHandle,
                       GSN_SPI_FS_RW_ARGS_T *spiRW );

PUBLIC VOID
GsnSpiFS_MemcpyCallBack( VOID *ctx, UINT32 channelID);

#ifdef  __cplusplus
    }
#endif

#define  SPI_DMA_ENABLE 1

#endif /* _GSN_SPI_H_ */
