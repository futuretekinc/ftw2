/******************************************************************************
 *
 *               COPYRIGHT (c) 2008-2010 GainSpan Corporation
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

 */
#ifndef _GSNUART_PRIVATE_H_
#define _GSNUART_PRIVATE_H_

/*
 * Includes on which the header file depends.
 *****************************************************************************************
 */
#include <stdint.h>
#include "gsn_includes.h"



/*
 * General macro definitions.
 * Type definition with macro is not allowed, constants should be defined as const
 * variables or as enumerations and function type macros are defined in the "Function
 * definitions" section.
 *****************************************************************************************
 */

/*
 * Type definitions.
 *****************************************************************************************
 */





#define XOFF 023
#define XON  021



/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief Uart Driver Tx data function..
 *    This function transmit data by putting into the uart fifo
 *    This function calls the callback function for async. write call.
 *    This function release the semaphore for synch. write call.
 * @param ptGsnUart                   - IN pointer to GSN_UART_T structure.
 * @return VOID
 * @note
 *
 *****************************************************************************/
INLINE VOID
GsnUart_Isr_ThrEmpty( GSN_UART_T *ptGsnUart );
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief Uart Driver Tx data function if SW flow is enabled.
 *    This function transmit data by putting into the uart fifo.
 *    This function calls the callback function for async. write call.
 *    This function release the semaphore for synch. write call.
 * @param ptGsnUart                   - IN pointer to GSN_UART_T structure.
 * @return VOID
 * @note
 *
 *****************************************************************************/

INLINE VOID
GsnUart_Isr_ThrEmptySwFlow( GSN_UART_T *ptGsnUart );
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief Uart Driver Tx data function..
 *    This function transmit data by putting into the uart fifo
 *    This function will enable uart Tx interrupt after filling the fifo.
 * @param ptGsnUart                   - IN pointer to GSN_UART_T structure.
 * @return VOID
 * @note
 *
 *****************************************************************************/

VOID
GsnUart_ThrEmpty( GSN_UART_T *ptGsnUart );
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief Uart Driver ISR handling if SW flow contrl is enabled.
 * Combined  interrupt handler.
 * This function is getting called whenever uart interrupt happens
 * @param ptGsnUart           - IN pointer to GSN_UART_T structure.
 * @return VOID
 * @note
 *
 *****************************************************************************/


VOID GsnUart_SwFlowIsr(GSN_UART_T *ptGsnUart);
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief Uart Driver ISR handling if SW flow control is disabled..
 * Combined interrupt handler
 * This function is getting called whenever uart interrupt happens
 * @param ptGsnUart                   - IN pointer to GSN_UART_T structure.
 * @return VOID
 * @note
 *
 *****************************************************************************/

VOID GsnUart_DefaultIsr(GSN_UART_T *ptGsnUart);
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief Uart Driver user buffer put function.
 * putting data from hardware fifo to user buffer.
 * @param ptGsnUart                   - IN pointer to GSN_UART_T structure.
 * @return VOID
 * @note
 *
 *****************************************************************************/

INLINE GSN_OSAL_ERROR_T
GsnUart_UsrBuffPut(GSN_UART_T *ptGsnUart);
/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief Uart Driver ring buffer put function.
 * putting data from hardware fifo to ring buffer
 * @param ptGsnUart                   - IN pointer to GSN_UART_T structure.
 * @return VOID
 * @note
 *
 *****************************************************************************/


INLINE GSN_OSAL_ERROR_T
GsnUart_RingBuffPut(GSN_UART_T *ptGsnUart);

/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief Uart Driver ring buffer get function.
 * taking data from ring buffer to user buffer
 * @param ptGsnUart                   - IN pointer to GSN_UART_T structure.
 * @return VOID
 * @note
 *
 *****************************************************************************/

UINT32
GsnUart_RingBuffGet(GSN_UART_T *ptGsnUart,UINT8* usrBuff, UINT32 usrBuffLen );

/**
 *****************************************************************************
 * @ingroup GsnUart
 * @brief Uart Driver user buffer put from ring buffer function.
 * copying data from ring buffer to user buffer.
 * @param ptGsnUart                   - IN pointer to GSN_UART_T structure.
 * @return 
 * @note
 *
 *****************************************************************************/
GSN_OSAL_ERROR_T
GsnUart_UsrBuffPutFromRbuffer(GSN_UART_T *ptGsnUart);
/**
 *****************************************************************************
 * @ingroup GsnUart0 main ISR handler
 * @brief Uart Driver interrupt handler function.
 * Handling all the uart0 interrupts.
 * @param  NONE
 * @return VOID
 * @note
 *
 *****************************************************************************/

PUBLIC VOID
__GsnUart0_Isr();
/**
 *****************************************************************************
 * @ingroup GsnUart1 main ISR handler
 * @brief Uart Driver interrupt handler function.
 * Handling all the uart1 interrupts.
 * @param  NONE
 * @return VOID
 * @note
 *
 *****************************************************************************/

PUBLIC VOID
__GsnUart1_Isr();

#endif
