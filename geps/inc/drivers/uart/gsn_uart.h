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
 * $RCSfile: gsn_uart.h,v $
 *
 * Description:
 *      This file contains public functions definitions for UART Driver
 *
 ******************************************************************************
 */

/**
******************************************************************************
*  @file gsn_uart.h
*  @brief Public Header Containing UART Driver Functions.
*
*****************************************************************************/


/**
 *****************************************************************************
 * @ingroup driversdoc
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnUart GSN UART API
 *    This group contains public definitions and functions providing access
 *    to the GS2000's UART.
 ****************************************************************************/

/**
 *****************************************************************************
 *
 * @}
 *****************************************************************************/



#ifndef _GSNUART_H_
#define _GSNUART_H_

/*
 *****************************************************************************************
 * Includes on which the header file depends.
 *****************************************************************************************
 */
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
#include "core/osal/gsn_osal_threadx.h"
#include "drivers/clk_ctl/gsn_clk_ctl.h"





/*
 *****************************************************************************************
 * UART macros
 *****************************************************************************************
 */



#define GSN_UART_NOS                       2







/*
 *****************************************************************************************
 * Type definitions.
 *****************************************************************************************
 */
/* UART call back */
typedef VOID ( *UARTCALLBACK_FP ) ( VOID*, UINT32 );



/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief GSN UART Types.
 *    This enum defines UART Interrupt FIFO levels.
 *****************************************************************************/
typedef enum GSN_UART_IFL
{
    GSN_UART_IFL_1_BY_8,
    GSN_UART_IFL_1_BY_4,
    GSN_UART_IFL_1_BY_2,
    GSN_UART_IFL_3_BY_4,
    GSN_UART_IFL_7_BY_8
}GSN_UART_IFL_T;


/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief GSN UART Types.
 *    This enum defines UART baud rate values.
 * @see  GSN_UART_BAUDRATE_T.
 *****************************************************************************/

typedef enum GSN_UART_BAUDRATE
{
    GSN_UART_BAUDRATE_1K2   =  1200,
    GSN_UART_BAUDRATE_2K4   =  2400,
    GSN_UART_BAUDRATE_4K8   =  4800,
    GSN_UART_BAUDRATE_9K6   =  9600,
    GSN_UART_BAUDRATE_19K2  =  19200,
    GSN_UART_BAUDRATE_38K4  =  38400,
    GSN_UART_BAUDRATE_57K6  =  57600,
    GSN_UART_BAUDRATE_115K2 =  115200,
    GSN_UART_BAUDRATE_230K4 =  230400,
    GSN_UART_BAUDRATE_460K8 =  460800,
    GSN_UART_BAUDRATE_921K6 =  921600,
    GSN_UART_BAUDRATE_UNDEFINED
} GSN_UART_BAUDRATE_T;

/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief GSN UART Types.
 *    This enum defines UART data length.
 * @see  GSN_UART_RXLVL_T.
 *****************************************************************************/
typedef enum GSN_UART_WORDLEN
{
    GSN_UART_WORDLEN_5,
    GSN_UART_WORDLEN_6,
    GSN_UART_WORDLEN_7,
    GSN_UART_WORDLEN_8
}GSN_UART_WORDLEN_T;
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief GSN UART Types.
 *    This enum defines clocks available for UART.
 * @see  GSN_UART_RXLVL_T.
 *****************************************************************************/
typedef enum GSN_UART_CLKSEL
{
    GSN_UART_CLK_RC,
    GSN_UART_CLK_XTAL,
    GSN_UART_CLK_PLL,
}GSN_UART_CLKSEL_T;
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief GSN UART Types.
 *    This enum defines max clock values available for UART.
 * @see  GSN_UART_RXLVL_T.
 *****************************************************************************/
typedef enum GSN_UART_CLK_VALUE_TEST
{
    GSN_UART_CLK_HSRC_MAX  =80000000,
    GSN_UART_CLK_XTAL_MAX  =40000000,
    GSN_UART_CLK_PLL_MAX   =120000000,
}GSN_UART_CLK_VALUE_TEST_T;

/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief GSN UART Types.
 *    This is for tetsing.
 * @see  GSN_UART_RXLVL_T.
 *****************************************************************************/
typedef enum GSN_UART_CLK_VALUE
{
    GSN_UART_CLK_HSRC_MAX_TEST  =50000000,
    GSN_UART_CLK_XTAL_MAX_TEST  =50000000,
    GSN_UART_CLK_PLL_MAX_TEST   =50000000,
}GSN_UART_CLK_VALUE_T;

/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief GSN UART Types.
 *    This enum defines UART char format values.
 * @see  GSN_UART_CHARFORMAT_T.
 *****************************************************************************/

typedef enum GSN_UART_CHARFORMAT
{
    GSN_UART_CHARFORMAT_5 = 0,
    GSN_UART_CHARFORMAT_6 = 1,
    GSN_UART_CHARFORMAT_7 = 2,
    GSN_UART_CHARFORMAT_8 = 3
} GSN_UART_CHARFORMAT_T;



/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief GSN UART Types.
 *    This enum defines UART stop bits values .
 * @see  GSN_UART_STOPBITS_T.
 *****************************************************************************/

typedef enum GSN_UART_STOPBITS
{
    GSN_UART_STOPBITS_1 = 0,
    GSN_UART_STOPBITS_2 = 1
}GSN_UART_STOPBITS_T;


/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief GSN UART Types.
 *    This enum defines UART parity bits values.
 * @see  GSN_UART_PARITYBIT_T.
 *****************************************************************************/

typedef enum GSN_UART_PARITYBIT
{
    GSN_UART_PARITYBIT_ODD   = 0,
    GSN_UART_PARITYBIT_EVEN  = 1,
    GSN_UART_PARITYBIT_MARK  = 2, /* The parity bit is always 1. */
    GSN_UART_PARITYBIT_SPACE = 3, /* The parity bit is always 0. */
    GSN_UART_PARITYBIT_NONE
} GSN_UART_PARITYBIT_T;


/**
  *****************************************************************************
  * @ingroup GsnUart
  * @brief GSN UART Types.
  *    This enum defines UART port numbers.
  * @see  GSN_UART_NO_T.
  *****************************************************************************/

typedef enum GSN_UART_NO
{
    GSN_UART_0  = 0,
    GSN_UART_1  = 1
}GSN_UART_NO_T;


/**
  *****************************************************************************
  * @ingroup GsnUart
  * @brief GSN UART HW flow supports
  *    This enum defines UART HW flow supports.
  * @see  GSN_UART_HWSUPPORT_T.
  *****************************************************************************/


typedef enum GSN_UART_HWSUPPORT
{
    GSN_UART_HW_NO_SUPPORT,
    GSN_UART_HW_SUPPORT
}GSN_UART_HWSUPPORT_T;

/**
  *****************************************************************************
  * @ingroup GsnUart
  * @brief GSN UART SW flow supports
  *    This enum defines UART SW flow supports.
  * @see  GSN_UART_SWSUPPORT_T.
  *****************************************************************************/
typedef enum GSN_UART_SWFLOW
{
    GSN_UART_SWFLOW_NO_SUPPORT,
    GSN_UART_SWFLOW_SUPPORT
}GSN_UART_SWFLOW_T;
/**
  *****************************************************************************
  * @ingroup GsnUart
  * @brief GSN UART DMA supports
  *    This enum defines UART DMA supports.
  * @see  GSN_UART_SWSUPPORT_T.
  *****************************************************************************/
typedef enum GSN_UART_DMA
{
    GSN_UART_DMA_NO_SUPPORT,
    GSN_UART_DMA_SUPPORT
}GSN_UART_DMA_T;

/**
 ****************************************************************************
 * @ingroup GsnUart
 * @brief Gsn UART DMA TX mode types.
 *
 * This enum defines the type of UART DMA TX modes.
 * @see  GSN_UART_DMA_TX_MODE_T.
 ****************************************************************************/
typedef enum GSN_UART_DMA_TX_MODE
{
	GSN_UART_DMA_TX_CLEAR,
	GSN_UART_DMA_TX_SET

} GSN_UART_DMA_TX_MODE_T;


/**
 ****************************************************************************
 * @ingroup GsnUart
 * @brief Gsn UART DMA RX mode types.
 *
 *    This enum defines the type of UART DMA RX modes.
 * @see  GSN_UART_DMA_RX_MODE_T.
 ****************************************************************************/
typedef enum GSN_UART_DMA_RX_MODE
{
	GSN_UART_DMA_RX_CLEAR,
	GSN_UART_DMA_RX_SET

} GSN_UART_DMA_RX_MODE_T;
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief GSN UART Types.
 *    This enum defines UART return values
 * @see  GSN_UART_STATUS_T.
 *****************************************************************************/
enum GSN_UART_DEVICE_STATE
{
    GSN_UART_NOT_INITIALIZED,
    GSN_UART_INITIALIZED,
    GSN_UART_READ_PROGRESS,
    GSN_UART_READ_FINISHED,
    GSN_UART_WRITE_PROGRESS,
    GSN_UART_WRITE_FINISHED,
    GSN_UART_BLOCK_READ_PROGRESS,
    GSN_UART_RECEIVE_ERROR,
    GSN_UART_CLOSED
};
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART GSN Structure.
 * This structure defines SW flow parameters and HW flow parameters.
 *
 * @see  GSN_UART_CONFIG_T.
 *****************************************************************************/

typedef struct GSN_UART_CONTROLFLOW_CTX
{
    UINT32 XOff[GSN_UART_NOS];
    UINT32 XOn[GSN_UART_NOS];
    UINT32 sndXoff[GSN_UART_NOS];
    UINT32 uartHwFlow[GSN_UART_NOS];
} GSN_UART_CONTROLFLOW_CTX_T;

/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART GSN Structure.
 * This structure defines UART Rx buffer status parameter
 *
 * @see  GSN_UART_CONFIG_T.
 *****************************************************************************/

typedef struct GSN_UART_RX_BUFF
{
    UINT8*               uartBuffer;
    UINT32               uartBuffSize;
    UINT32               uartBuffHead;
    UINT32               uartBuffTail;
    UINT32               dataCountInBuff;
} GSN_UART_RX_BUFF_T;

/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART GSN Structure.
 * This structure defines UART Rx buffer status parameter
 *
 * @see  GSN_UART_CONFIG_T.
 *****************************************************************************/

typedef struct GSN_UART_ERROR_STATUS
{
    UINT32           framingError;
    UINT32           parityError;
    UINT32           overrunError;
    UINT32           totalError;
    UINT32           bytesReturnedWhenError;
}GSN_UART_ERROR_STATUS_T;

/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART GSN Structure.
 *    This structure defines a UART configuration parameter
 *
 * @see  GSN_UART_CONFIG_T.
 *****************************************************************************/

typedef struct GSN_UARTCONFIG
{
    GSN_UART_BAUDRATE_T      eBaudRate;
    GSN_UART_CHARFORMAT_T    eCharFormat;
    GSN_UART_STOPBITS_T      eStopBits;
    GSN_UART_PARITYBIT_T     eParityBits;
    UINT8*                   uartBuffer;
    UINT32                   uartBuffSize;
    GSN_UART_HWSUPPORT_T     HwFlowSupport;
    GSN_UART_SWFLOW_T        swFlowSupport;
    GSN_UART_DMA_T           dmaSupport;
    GSN_UART_CLKSEL_T        uartClk;

} GSN_UART_CONFIG_T;


/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART GSN Structure.
 *    This structure defines a UART driver handling parameters.
 *
 * @see  GSN_UART_T.
 *****************************************************************************/

typedef struct GSN_UART
{
    UINT32                  pReg;
    UINT32                  uartNo;
    UINT32                  noOfBytesToRead;
    UINT32                  noOfBytesToBeWritten;
    UINT32                  actualBytesRead;
    UINT32                  actualBytesWritten;
    UINT8*                  txBuffer;
    UINT8*                  rxUserBuffer;
    GSN_UART_RX_BUFF_T      rxBuffer;
    UARTCALLBACK_FP         ReadCallback;
    VOID                    *ReadCbCtx;
    UARTCALLBACK_FP          WriteCallback;
    VOID                    *WriteCbCtx;
    VOID                     *gsnDma;
    UINT32                   uartDeviceState;
    GSN_UART_HWSUPPORT_T     HwFlowSupport;
    GSN_UART_SWFLOW_T        swFlowSupport;
    GSN_UART_DMA_T           dmaSupport;
    VOID                      *rxDmaChannelConfig;  // for dma on rx
    VOID                      *txDmaChannelConfig;  // for dma on tx
    LONG64                   uartClk;
    GSN_UART_ERROR_STATUS_T  errorStatus;
    GSN_OSAL_SEM_T           uartSyncWriteSemId[GSN_UART_NOS];
    GSN_OSAL_SEM_T           uartBlockReadSemId[GSN_UART_NOS];
    GSN_UART_CONTROLFLOW_CTX_T ctx;
}GSN_UART_T;


/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART GSN Structure.
 *    This structure defines a UART handle, which holds a UART config and data
 *    parameter
 *
 * @see  GSN_UART_HANDLE_T.
 *****************************************************************************/

typedef struct GSN_UART_HANDLE
{
    UINT32             u32UartRegInit;  /**< initialise status */
    GSN_UART_T         uart;            /**< uart parameter */

}GSN_UART_HANDLE_T;





/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver open API.
 *    This function open a UART port.
 *    This function initializes the corresponding UART.
 * @param eGsnUartNo            - IN Uart number to be initalized.
 * @param ptUartHandle           - IN pointer to uart handle.
 * @param ptUartConfig          - IN pointer to uart configuration.
 * @retval GSN_UART_STATUS_ERROR  on error
 * @retval GSN_UART_STATUS_OK on success.
 * @note
 *****************************************************************************/
GSN_OSAL_ERROR_T
GsnUart_Open ( GSN_UART_NO_T eGsnUartNo,
               GSN_UART_HANDLE_T* ptUartHandle , GSN_UART_CONFIG_T* ptUartConfig);



/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief @brief UART GSN Read throgh specified port
 *    1. prepare for transmission.
 *    2. Start data reception by enabling the Rx interrupt.
 *    3. wait on the semaphore for a synchronous read.
 * @param ptUartHandle    - IN pointer to hold Uart handle.
 * @param puBuffer        - IN pointer to hold read data pointer for data.
 * @param noOfBytesToRead - IN no of bytes to read.
 * @param blockRead       - IN blocking read.
 * @param ptCallBackFunc  - IN the application call back function.
 * @param ctx             - IN the context for application call back function.
 * @return The number bytes received.
 * @note
 *****************************************************************************/
 UINT32
 GsnUart_Read( GSN_UART_HANDLE_T* ptUartHandle,
               UINT8 *puBuffer, UINT32 noOfBytesToRead, BOOL blockRead,
               UARTCALLBACK_FP ptCallBackFunc, VOID *ctx );


/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Write Through Specified Port
 *    1. Prepare for transmission
 *    2. Start transmission by putting data into UART FIFO.
 *    3. Enable the TX interrupt.
 *    4. Wait on the write semaphore for a synchronous write.
 * @param ptUartHandle    - IN pointer to hold Uart handle.
 * @param puBuffer        - IN pointer to hold write data pointer .
                              for data transfer
 * @param noOfBytesToWrite - IN the number of bytes to write.
 * @param ptCallBackFunc  - IN callback function for asynch. write
 * @param ctx             - IN the context for call back function.
 * @return actual bytes written
 *
 *****************************************************************************/
 UINT32
 GsnUart_Write ( GSN_UART_HANDLE_T* ptUartHandle,
                 UINT8 *puBuffer, UINT32 noOfBytesToWrite,
		         UARTCALLBACK_FP ptCallBackFunc, VOID *ctx );


/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Closes API.
 *    This function closes the driver.
 *    This function deletes the semaphores and disables the corresponding
 *    UART port.
 * @param ptUartHandle           - IN pointer to handle.
 * @retval GSN_SUCCESS on success
 * @retval GSN_UART_STATUS_ERROR on error.
 * @note
 *****************************************************************************/
GSN_OSAL_ERROR_T
GsnUart_Close( GSN_UART_HANDLE_T* ptUartHandle);

/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Dma Transmit Set API.
 *    This function set DMA transmit mode in UART.
 * @param ptUartHandle             - IN pointer to handle.
 * @return none
 * @note
 *
 *****************************************************************************/
 VOID
 GsnUart_DmaTxSet( GSN_UART_HANDLE_T *ptUartHandle);
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Dma Transmit Clear API.
 *    This function clear the DMA transmit mode in UART.
 * @param ptUartHandle             - IN pointer to handle.
 * @return none
 * @note
 *
 *****************************************************************************/
 VOID
 GsnUart_DmaTxClear( GSN_UART_HANDLE_T *ptUartHandle);
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Gets DMA transmit mode API.
 *    This function gets the UART_DMA_TX_MODE status..
 * @param ptUartHandle             - IN pointer to handle.
 * @return UART_DMA_TX_MODE status
 * @note
 *
 *****************************************************************************/
 GSN_UART_DMA_TX_MODE_T
 GsnUart_DmaTxGet( GSN_UART_HANDLE_T *ptUartHandle );
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Dma Receive Clear API.
 *    This function clear the DMA receive mode in UART
 * @param ptUartHandle             - IN pointer to handle.
 * @return none
 * @note
 *
 *****************************************************************************/
 VOID
 GsnUart_DmaRxClear( GSN_UART_HANDLE_T *ptUartHandle);
/**
 *****************************************************************************
 * @ingroup GsnUart
  * @brief UART Driver Dma Receive Set API.
 *    This function set DMA Receive mode in UART.
 * @param ptUartHandle             - IN pointer to handle.
 * @return none
 * @note
 *
  *****************************************************************************/
 VOID
 GsnUart_DmaRxSet( GSN_UART_HANDLE_T *ptUartHandle);
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Gets DMA  Receive mode API.
 *    This function gets the UART_DMA_RX_MODE status.
 * @param ptUartHandle             - IN pointer to handle.
 * @return GSN_UART_DMA_RX_MODE status.
 * @note
 *
 *****************************************************************************/
 GSN_UART_DMA_RX_MODE_T
 GsnUart_DmaRxGet(GSN_UART_HANDLE_T *ptUartHandle );


/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Set Baud rate API.
 *    This function set the baud rate settings of UART.
 * @param ptUartHandle             - IN pointer to handle.
 * @param eBaudRate                - IN  UART baud rate.
 * @return none
 * @note
 *
 *****************************************************************************/
VOID
GsnUart_BaudRateSet(GSN_UART_HANDLE_T* ptUartHandle,
                   UINT32 eBaudRate );


/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Gets Baud Rate API.
 *    This function gets the UART baud rate settings.
 * @param ptUartHandle           - IN pointer to handle.
 * @return GSN_UART_BAUDRATE_T
 * @note
 *
 *****************************************************************************/
UINT32
GsnUart_BaudRateGet(GSN_UART_HANDLE_T* ptUartHandle);



/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Set Char Format Bit API.
 *    This function set the stop bit settings of UART.
 * @param ptUartHandle             - IN pointer to handle.
 * @param eCharFormat              - IN Char format settings.
 * @return VOID
 * @note
 *
 *****************************************************************************/
VOID
GsnUart_CharFormatSet(GSN_UART_HANDLE_T* ptUartHandle,
                     GSN_UART_CHARFORMAT_T eCharFormat );


/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Gets Char Format API.
 *    This function gets the char format settings of UART.
 * @param ptUartHandle           - IN pointer to handle.
 * @return GSN_UART_CHARFORMAT_T
 * @note
 *
 *****************************************************************************/
GSN_UART_CHARFORMAT_T
GsnUart_CharFormatGet(GSN_UART_HANDLE_T* ptUartHandle);


/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Sets Stop Bit API.
 *    This function sets the UART stop bit settings.
 * @param ptUartHandle           - IN pointer to handle.
 * @param eStopBits              - IN stop bits.
 * @return VOID
 * @note
 *
 *****************************************************************************/
VOID
GsnUart_StopBitsSet(GSN_UART_HANDLE_T* ptUartHandle,
                    GSN_UART_STOPBITS_T eStopBits );



/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Gets Stop Bit API.
 *    This function gets the UART stop bit settings.
 * @param ptUartHandle           - IN pointer to handle.
 * @return GSN_UART_STOPBITS_T
 * @note
 *
 *****************************************************************************/
GSN_UART_STOPBITS_T
GsnUart_StopBitsGet(GSN_UART_HANDLE_T* ptUartHandle);


/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Set Parity Bit API.
 *    This function sets the UART parity bit.
 * @param ptUartHandle           - IN pointer to handle.
 * @param eParityBits            - IN parity.
 * @return VOID
 * @note
 *
 *****************************************************************************/
VOID
GsnUart_ParityBitsSet(GSN_UART_HANDLE_T* ptUartHandle,
                   GSN_UART_PARITYBIT_T eParityBits );


/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Gets Parity Bit API.
 *    This function gets the UART parity bit settings.
 * @param ptUartHandle           - IN pointer to handle.
 * @return GSN_UART_PARITYBIT_T
 * @note
 *
 *****************************************************************************/
GSN_UART_PARITYBIT_T
GsnUart_ParityBitsGet(GSN_UART_HANDLE_T* ptUartHandle);

/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Set HW Flow Support.
 *    This function sets and enables the UART HW flow support.
 * @param ptUartHandle           - IN pointer to handle.
 * @param hwFlowSupport            - IN Hw flow support
 * @return VOID
 * @note
 *
 *****************************************************************************/
VOID
GsnUart_HwFlowSupportSet(GSN_UART_HANDLE_T* ptUartHandle,
                   GSN_UART_HWSUPPORT_T hwFlowSupport );


/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Get Hw flow support API.
 *    This function gets Hw flow support settings of UART.
 * @param ptUartHandle           - IN pointer to handle.
 * @return GSN_UART_HWSUPPORT_T
 * @note
 *
 *****************************************************************************/
GSN_UART_HWSUPPORT_T
GsnUart_HwFlowSupportGet(GSN_UART_HANDLE_T* ptUartHandle);

/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Get Tx Status
 *    This function gets Tx Status for the UART
 * @param ptUartHandle           - IN pointer to handle.
 * @return Status of UART TX
 * @note
 *
 *****************************************************************************/


BOOL
GsnUart_TxStatusGet(GSN_UART_HANDLE_T* ptUartHandle);
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Set SW Flow Support.
 *    This function sets and enables the UART SW flow support.
 * @param ptUartHandle           - IN pointer to handle.
 * @param value                  - IN sw flow support
 * @return VOID
 * @note
 *
 *****************************************************************************/
VOID
GsnUart_SwFlowSupportSet(GSN_UART_HANDLE_T* ptUartHandle,
                         GSN_UART_SWFLOW_T value);
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Get SW Flow Support.
 *    This function gets  the UART SW flow support status.
 * @param ptUartHandle           - IN pointer to handle.
 * @return GSN_UART_SWFLOW_T  enum.
 * @note
 *
 *****************************************************************************/
GSN_UART_SWFLOW_T
GsnUart_SwFlowSupportGet(GSN_UART_HANDLE_T* ptUartHandle);
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Loop Back Enable.
 *    This function enable loop back in UART.TX line is connected to RX line.
 * @param ptUartHandle           - IN pointer to handle.
 * @return VOID
 * @note
 *
 *****************************************************************************/
VOID
GsnUart_LoopBackEn(GSN_UART_HANDLE_T* ptUartHandle);
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver Enable UART clock
 *    This function will Enable UART clock.
 * @param gsnUartNo              - UART NO.
 * @param ptUartConfig           - IN pointer to config.
 * @return                       - VOID
 * @note
 *
 *****************************************************************************/
VOID
GsnUart_ClockEnable (UINT8 gsnUartNo, GSN_UART_CONFIG_T* ptUartConfig);
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver   - GsnUart_TxCallBack
 *     This function will call asynchronously by dma driver.
 * @param ptUartHandle    - IN context structure pointer from uart driver.
 * @param channelId       - IN channel id.
 * @return                - VOID
 * @note
 *
 *****************************************************************************/
VOID
GsnUart_TxCallBack (VOID* ptUartHandle, UINT32 channelId);
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief UART Driver-GsnUart_RxCallBack
 *    This function will call asynchronously by dma driver.
 * @param ptUartHandle    - IN context structure pointer from uart driver.
 * @param channelId       - IN channel id.
 * @return                - VOID
 * @note
 *
 *****************************************************************************/
VOID
GsnUart_RxCallBack (VOID* ptUartHandle, UINT32 channelId);

GSN_STATUS
GsnUart_IntrFifoRxLevelSet(GSN_UART_HANDLE_T* ptUartHandle,GSN_UART_IFL_T level) ;/* >= 1/8 FULL */
UINT8
GsnUart_IntrFifoTxLevelGet(GSN_UART_HANDLE_T* ptUartHandle);
UINT8
GsnUart_IntrFifoRxLevelGet(GSN_UART_HANDLE_T* ptUartHandle);
UINT8
GsnUart_IntrFifoTxLevelSet(GSN_UART_HANDLE_T* ptUartHandle,GSN_UART_IFL_T level);
#endif /* _UART_H_ */



