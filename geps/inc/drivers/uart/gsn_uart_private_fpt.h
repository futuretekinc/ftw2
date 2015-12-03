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
* $RCSfile: gsn_uart_private_fpt.h,v $
*
* Description : This file contains private functions patch definitions.
*****************************************************************************/

#ifndef _GSN_UART_PRIVATE_FTP_H_
#define _GSN_UART_PRIVATE_FTP_H_
/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "drivers/clk_ctl/gsn_clk_ctl.h"
#include "gsn_includes.h"
#include "drivers/uart/gsn_uart.h"



/*****************************************************************************
  *  Definitions
  ****************************************************************************/
typedef VOID
(* GsnUart_DefaultIsr_FP_T)(GSN_UART_T *ptGsnUart);
extern _RPST_   GsnUart_DefaultIsr_FP_T GsnUart_DefaultIsr_FP;

typedef VOID
(*GsnUart_SwFlowIsr_FP_T)(GSN_UART_T *ptGsnUart);
extern _RPST_ GsnUart_SwFlowIsr_FP_T GsnUart_SwFlowIsr_FP;

typedef VOID
(* GsnUart_Isr_ThrEmpty_FP_T)(GSN_UART_T *ptGsnUart );
extern _RPST_ GsnUart_Isr_ThrEmpty_FP_T GsnUart_Isr_ThrEmpty_FP;

typedef VOID
(* GsnUart_Isr_ThrEmptySwFlow_FP_T)( GSN_UART_T *ptGsnUart );
extern _RPST_   GsnUart_Isr_ThrEmptySwFlow_FP_T GsnUart_Isr_ThrEmptySwFlow_FP;

typedef VOID
(* GsnUart_ThrEmpty_FP_T)(GSN_UART_T *ptGsnUart);
extern _RPST_   GsnUart_ThrEmpty_FP_T GsnUart_ThrEmpty_FP;

typedef GSN_OSAL_ERROR_T
(* GsnUart_RingBuffPut_FP_T)(GSN_UART_T *ptGsnUart);
extern _RPST_   GsnUart_RingBuffPut_FP_T GsnUart_RingBuffPut_FP;

typedef GSN_OSAL_ERROR_T
(* GsnUart_UsrBuffPutFromRbuffer_FP_T)(GSN_UART_T *ptGsnUart);
extern _RPST_   GsnUart_UsrBuffPutFromRbuffer_FP_T GsnUart_UsrBuffPutFromRbuffer_FP;

typedef GSN_OSAL_ERROR_T
(* GsnUart_UsrBuffPut_FP_T)(GSN_UART_T *ptGsnUart);
extern _RPST_   GsnUart_UsrBuffPut_FP_T GsnUart_UsrBuffPut_FP;

typedef UINT32
(* GsnUart_RingBuffGet_FP_T)(GSN_UART_T *ptGsnUart,
						       UINT8* usrBuff,
							   UINT32 usrBuffLen );
extern _RPST_   GsnUart_RingBuffGet_FP_T GsnUart_RingBuffGet_FP;


typedef PUBLIC VOID
( *__GsnUart0_Isr_FP_T)();
extern _RPST_  __GsnUart0_Isr_FP_T __GsnUart0_Isr_FP;


typedef PUBLIC VOID
( *__GsnUart1_Isr_FP_T)();
extern _RPST_  __GsnUart1_Isr_FP_T __GsnUart1_Isr_FP;

#endif