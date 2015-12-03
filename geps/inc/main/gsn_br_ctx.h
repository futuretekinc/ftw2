
/******************************************************************************
*
*               COPYRIGHT (c) 2009-2010 GainSpan Corporation
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
* $RCSfile: gsn_br_ctx.h,v $
*
* Description : This file contains boot rom.
*****************************************************************************/

#ifndef GSN_BR_CTX_H_
#define GSN_BR_CTX_H_

/*
 * TYPES
 ****************************************************************************************
 */

/* todo --> remove later                                                                */
#define GSN_BR_MAX_FW_INSTANCE_NBR             1  /* Max Emb instance                      */
#define GSN_BR_DEFAULT_IDX                     0

typedef struct GSN_BR_CTX_S
{
    /* High Contexts                                                                    */
    GSN_BR_HI_CONTEXT_T         HiContext;

    /* middle level driver (hi_uart, hi_mb, hi_spi, hi_wlan etc...)                     */
    /*   - UART 0                                                                       */
    GSN_BR_HI_SERIAL_CONTEXT_T  HiUart0Context;

    GSN_BR_HI_SERIAL_CONTEXT_T  HiSpiContext;
    
    GSN_UART_HANDLE_T        HiUartHandle;

    GSN_SPI_HANDLE_T         HiSpiSlaveHandle;

    /* Download context                                                                 */
    GSN_BR_DWNLD_CONTEXT_T      DwnldContext;
    
} GSN_BR_CTX_T;

extern GSN_BR_CTX_T GSN_BR_ContextTab [GSN_BR_MAX_FW_INSTANCE_NBR];

#endif //GSN_BR_CTX_H_




