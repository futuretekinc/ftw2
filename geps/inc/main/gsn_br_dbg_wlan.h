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
* $RCSfile: gsn_br_dbg_wlan.h,v $
*
* Description : This file contains boot rom wlan debug handler. It sends
*               HI debug messages received for wlan to wlan CPU and sends
*               back responses to host over HI.
*****************************************************************************/
#ifndef _GSN_BR_DBG_WLAN_H_
#define _GSN_BR_DBG_WLAN_H_

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_includes.h"
#include "gsn_types.h"


/**
 *****************************************************************************
 * @file gsn_br_dbg_wlan.h
 * @brief GSN boot rom debug handler.
 *    This file contains boot rom debug handler.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GEPSSupport
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnBrDbgWlan GSN Bootrom WLAN Debug Handler
 * @brief This module Contains boot rom wlan debug handler functionality.
 *        It contains functions for sending wlan specific HI messages to 
 *        wlan cpu and sends responses back to host over HI.
 *
 * \verbatim
 * PUBLIC is actually defined as blank.
 * PRIVATE is replaced with the "static" descriptor.
 * TRUE is replaced with 1, FALSE with 0
 * Compile-dependent definitions are provided for INLINE
 * BIT(n) provides n-bit offsets
 * A UINT32 with all bits = 1 is defined.
 *
 *\endverbatim
 *****************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/


/*****************************************************************************
  *  Definitions
  ****************************************************************************/

PUBLIC VOID
GsnBrDbgWlan_Start();

PUBLIC VOID
GsnBrDbgWlan_Stop();

PUBLIC VOID
GsnBrDbgWlan_RegPeek(GSN_WIF_DBG_REG_PEEKPOKE_T *pBuf);

PUBLIC VOID
GsnBrDbgWlan_RegPoke(GSN_WIF_DBG_REG_PEEKPOKE_T *pBuf);

PUBLIC VOID
GsnBrDbgWlan_MemRead(GSN_WIF_DBG_MEM_RW_T *pBuf);

PUBLIC VOID
GsnBrDbgWlan_MemWrite(GSN_WIF_DBG_MEM_RW_T *pBuf);

PUBLIC VOID
GsnBrDbgWlan_Exec(GSN_WIF_DBG_EXEC_T *pBuf);

PUBLIC VOID
GsnBrDbgWlan_FlashRead(GSN_WIF_DBG_FLASH_READ_T *pBuf);



#ifdef __cplusplus
}
#endif

#endif /* _GSN_BR_DBG_WLAN_H_ */


