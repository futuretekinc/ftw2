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
* $RCSfile: gsn_uart_fpt.h,v $
*
* Description : This file contains patch definitions.
*****************************************************************************/
#ifndef _GSN_UART_FPT_H_
#define _GSN_UART_FPT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_includes.h"




/*****************************************************************************
  *  Definitions
****************************************************************************/

typedef GSN_OSAL_ERROR_T
(* GsnUart_Open_FP_T)(GSN_UART_NO_T eGsnUartNo,
						GSN_UART_HANDLE_T* ptUartHandle,
						GSN_UART_CONFIG_T* ptUartConfig );

extern _RPST_ GsnUart_Open_FP_T GsnUart_Open_FP;


typedef UINT32
(*GsnUart_Read_FP_T)( GSN_UART_HANDLE_T* ptUartHandle,
              UINT8 *puBuffer, UINT32 noOfBytesToRead, BOOL blockRead,
              UARTCALLBACK_FP ptCallBackFunc, VOID *ctx);
extern _RPST_ GsnUart_Read_FP_T GsnUart_Read_FP;



typedef UINT32
(* GsnUart_Write_FP_T)(GSN_UART_HANDLE_T* ptUartHandle,
                UINT8 *puBuffer, UINT32 noOfBytesToWrite,
                UARTCALLBACK_FP ptCallBackFunc, VOID *ctx);
extern _RPST_ GsnUart_Write_FP_T GsnUart_Write_FP;


typedef GSN_OSAL_ERROR_T
(* GsnUart_Close_FP_T)(GSN_UART_HANDLE_T* ptUartHandle);
extern _RPST_ GsnUart_Close_FP_T GsnUart_Close_FP;


typedef VOID
(* GsnUart_BaudRateSet_FP_T)(GSN_UART_HANDLE_T* ptUartHandle,
							   UINT32 eBaudRate );
extern _RPST_ GsnUart_BaudRateSet_FP_T GsnUart_BaudRateSet_FP;


typedef UINT32
(*GsnUart_BaudRateGet_FP_T)(GSN_UART_HANDLE_T* ptUartHandle);
extern _RPST_ GsnUart_BaudRateGet_FP_T GsnUart_BaudRateGet_FP;


typedef VOID
(* GsnUart_CharFormatSet_FP_T)(GSN_UART_HANDLE_T* ptUartHandle,
								GSN_UART_CHARFORMAT_T eCharFormat );
extern _RPST_ GsnUart_CharFormatSet_FP_T GsnUart_CharFormatSet_FP;


typedef GSN_UART_CHARFORMAT_T
(*GsnUart_CharFormatGet_FP_T)(GSN_UART_HANDLE_T* ptUartHandle);
extern _RPST_ GsnUart_CharFormatGet_FP_T GsnUart_CharFormatGet_FP;


typedef VOID
(* GsnUart_StopBitsSet_FP_T)(GSN_UART_HANDLE_T* ptUartHandle,
							  GSN_UART_STOPBITS_T eStopBits );
extern _RPST_ GsnUart_StopBitsSet_FP_T GsnUart_StopBitsSet_FP;


typedef GSN_UART_STOPBITS_T
(* GsnUart_StopBitsGet_FP_T)(GSN_UART_HANDLE_T* ptUartHandle);
extern _RPST_ GsnUart_StopBitsGet_FP_T GsnUart_StopBitsGet_FP;


typedef VOID
(* GsnUart_ParityBitsSet_FP_T)(GSN_UART_HANDLE_T* ptUartHandle,
								GSN_UART_PARITYBIT_T eParityBits );
extern _RPST_ GsnUart_ParityBitsSet_FP_T GsnUart_ParityBitsSet_FP;


typedef GSN_UART_PARITYBIT_T
(*GsnUart_ParityBitsGet_FP_T)(GSN_UART_HANDLE_T* ptUartHandle);
extern _RPST_ GsnUart_ParityBitsGet_FP_T GsnUart_ParityBitsGet_FP;


typedef VOID
(* GsnUart_HwFlowSupportSet_FP_T)(GSN_UART_HANDLE_T* ptUartHandle,
									GSN_UART_HWSUPPORT_T hwFlowSupport);
extern _RPST_ GsnUart_HwFlowSupportSet_FP_T GsnUart_HwFlowSupportSet_FP;


typedef GSN_UART_HWSUPPORT_T
(* GsnUart_HwFlowSupportGet_FP_T)(GSN_UART_HANDLE_T* ptUartHandle);
extern _RPST_ GsnUart_HwFlowSupportGet_FP_T GsnUart_HwFlowSupportGet_FP;


typedef VOID
(* GsnUart_SwFlowSupportSet_FP_T)(GSN_UART_HANDLE_T* ptUartHandle,
                         GSN_UART_SWFLOW_T value);
extern _RPST_ GsnUart_SwFlowSupportSet_FP_T GsnUart_SwFlowSupportSet_FP;


typedef GSN_UART_SWFLOW_T
(* GsnUart_SwFlowSupportGet_FP_T)(GSN_UART_HANDLE_T* ptUartHandle);
extern _RPST_ GsnUart_SwFlowSupportGet_FP_T GsnUart_SwFlowSupportGet_FP;


typedef BOOL
(*GsnUart_TxStatusGet_FP_T)(GSN_UART_HANDLE_T* ptUartHandle);
extern _RPST_ GsnUart_TxStatusGet_FP_T GsnUart_TxStatusGet_FP;


typedef VOID
(* GsnUart_LoopBackEn_FP_T)(GSN_UART_HANDLE_T* ptUartHandle);
extern _RPST_ GsnUart_LoopBackEn_FP_T GsnUart_LoopBackEn_FP;


typedef VOID
( *GsnUart_DmaTxSet_FP_T)( GSN_UART_HANDLE_T *ptUartHandle);
extern _RPST_ GsnUart_DmaTxSet_FP_T GsnUart_DmaTxSet_FP;


typedef VOID
( *GsnUart_DmaTxClear_FP_T )( GSN_UART_HANDLE_T *ptUartHandle);
extern _RPST_ GsnUart_DmaTxClear_FP_T  GsnUart_DmaTxClear_FP;


typedef GSN_UART_DMA_TX_MODE_T
( * GsnUart_DmaTxGet_FP_T )( GSN_UART_HANDLE_T *ptUartHandle );
extern _RPST_ GsnUart_DmaTxGet_FP_T  GsnUart_DmaTxGet_FP;


typedef VOID
( *GsnUart_DmaRxClear_FP_T)( GSN_UART_HANDLE_T *ptUartHandle);
extern _RPST_ GsnUart_DmaRxClear_FP_T GsnUart_DmaRxClear_FP;


typedef VOID
( *GsnUart_DmaRxSet_FP_T )( GSN_UART_HANDLE_T *ptUartHandle);
extern _RPST_ GsnUart_DmaRxSet_FP_T GsnUart_DmaRxSet_FP;


typedef GSN_UART_DMA_RX_MODE_T
( *GsnUart_DmaRxGet_FP_T )(GSN_UART_HANDLE_T *ptUartHandle );
extern _RPST_ GsnUart_DmaRxGet_FP_T GsnUart_DmaRxGet_FP;


typedef VOID
( *GsnUart_ClockEnable_FP_T) (UINT8 gsnUartNo, GSN_UART_CONFIG_T* ptUartConfig);
extern _RPST_ GsnUart_ClockEnable_FP_T GsnUart_ClockEnable_FP;


typedef VOID
( * GsnUart_TxCallBack_FP_T)( VOID *ctx, UINT32 channelID);
extern _RPST_ GsnUart_TxCallBack_FP_T GsnUart_TxCallBack_FP;


typedef VOID
( *GsnUart_RxCallBack_FP_T) ( VOID *ctx, UINT32 channelID);
extern _RPST_ GsnUart_RxCallBack_FP_T GsnUart_RxCallBack_FP;



#ifdef __cplusplus
}
#endif

#endif /* _GSN_UART_FPT_H_ */


