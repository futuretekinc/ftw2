/******************************************************************************
*
*               COPYRIGHT (c) 2008-2010 GainSpan Corporation
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
* $RCSfile: gsn_dbg.h,v $
*
* Description : This file contains the file numbering and debug MACRO to help
* debugging the system.
******************************************************************************/
#ifndef __GSN_DEBUG_H__
#define __GSN_DEBUG_H__

#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
#include "core/osal/gsn_osal.h"
#include "drivers/uart/gsn_uart.h"

typedef enum GSN_DBG_PORT_TYPE
{
    GSN_DBG_PORT_TYPE_UART,
    GSN_DBG_PORT_TYPE_ITM
} GSN_DBG_PORT_TYPE_T;

//#define GSN_DBG_PRINTF_ENABLE


/**
 ******************************************************************************
 * @ingroup GsnDebug
 * @brief Printf Buffer Size.
 *     This macro defines the size of the printf buffer. The amount of data
 *     that can be printed in one call to printf is limited by this.
 ******************************************************************************/
#define GSN_DBG_PRINTF_BUFFER_SIZE    220


typedef struct GSN_DBG
{
    GSN_OSAL_SEM_T printfSem;
    GSN_DBG_PORT_TYPE_T portType;
    
    /* printf buffer size */
    char printfBuf[GSN_DBG_PRINTF_BUFFER_SIZE];
    
    GSN_UART_HANDLE_T uartHndl;

    #define DBG_UART_RX_BUF_SIZE 16
    UINT8 uartRxBuf[DBG_UART_RX_BUF_SIZE];

    #define DBG_UART_TX_BUF_SIZE 256
    UINT8 uartTxBuf[DBG_UART_TX_BUF_SIZE];

} GSN_DBG_T;

/*
 ****************************************************************************
  *  Public Variables
  *****************************************************************************/

/* debug context */
extern GSN_DBG_T        *gsnDbgCtx;


PUBLIC GSN_STATUS
GsnDbg_Init(GSN_DBG_T *pDbgCtx, GSN_DBG_PORT_TYPE_T portType);

PUBLIC GSN_STATUS
GsnDbg_Start(GSN_DBG_T *pDbgCtx, GSN_UART_CONFIG_T *pConf,
                    UINT32 port);

void
GsnDbg_Printf(GSN_DBG_T *pDbgCtx, char *fmt, ...);



#ifdef GSN_DBG_PRINTF_ENABLE
# define printf(...) GsnDbg_Printf(gsnDbgCtx, __VA_ARGS__)
#else
# define printf(...)
#endif



#endif
