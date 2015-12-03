/******************************************************************************
*
*               COPYRIGHT (c) 2011-2014 GainSpan Corporation
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
* $RCSfile: app_ctx.h,v $
*
* Description : This file contains application context.
*****************************************************************************/
#ifndef _APP_CTX_H_
#define _APP_CTX_H_

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_includes.h"


#define APP_UART_RX_BUF_SIZE 1024

/*****************************************************************************
 * Type Definitions
 ****************************************************************************/

typedef struct APP_CTX
{
    GSN_DBG_T dbgCtx;
} APP_CTX_T;


#endif /* _APP_CTX_H_ */

/*****************************************************************************/

