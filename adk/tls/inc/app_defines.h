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
* $RCSfile: app_defines.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/
#ifndef _APP_DEFINES_H_
#define _APP_DEFINES_H_

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
/*
#include "gsn_sys_define.h"
#include "gsn_types.h"
#include "gsn_macros.h"
#include "gsn_sys_qual.h"
*/
/**
 *****************************************************************************
 * @file gsn_app_defines.h
 * @brief GSN defines.
 *    This file contains general definitions.
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnAppDefines GSN definitions.
 *    This group contains general definitions.
 *****************************************************************************/

/** MAC address size. */
#define APP_MAC_ADDR_SIZE   6
#define APP_DEV_INDX_0	0


/*****************************************************************************
  *  Definitions
  ****************************************************************************/
typedef enum APP_SQ_TASK_MONITOR_ID
{
    APP_SQ_MAIN_TASK_ID = 0,
    APP_SQ_TIMER_TASK_ID,
    APP_SQ_WLAN_SYS_TASK_ID,
    APP_SQ_WDD_TASK_ID,
    APP_SQ_NWIF_TASK_ID,
    APP_SQ_NW_TMR_TASK_ID,
    APP_SQ_IDLE_TASK_ID,
    APP_SQ_NET_RX_TASK_ID,
    APP_SQ_SERIAL_INPUT_TASK_ID,
} APP_SQ_TASK_MONITOR_ID_T;

#endif /* _APP_DEFINES_H_ */
/*****************************************************************************/

