/*****************************************************************************
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
* $RCSfile: app_events.h,v $
*
* Description : This file contains definitions of events posted to main task.
*****************************************************************************/
#ifndef _APP_EVENTS_H_
#define _APP_EVENTS_H_

/****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_types.h"
#include "gsn_includes.h"

/**
 *****************************************************************************
 * @file gsn_notifications_app.h
 * @brief GSN application notifications.
 *    This file contains notification related definitions used in the system.
 ****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnNotificationsApp GSN application notifications.
 *    This group contains application notification related definitions.
 ****************************************************************************/



/****************************************************************************
  *  Definitions
  ****************************************************************************/

/****************************************************************************
  *  Type Definitions
  ****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnNotificationsApp
 * @brief Event Notifications used by the application.
 *    This enum defines all the asynchronous event notifications used by the application.
 *    These notification values are not passed in callback status parameters but
 *    are used as notifications to application main task.
 *****************************************************************************/
typedef enum APP_EVENTS
{
    /* Application notifications should start after core notifications */
	APP_EVENT_INVALID,	
    APP_EVENT_NW_START_NCM ,
    APP_EVENT_NW_CONNECT_DONE ,
    APP_EVENT_NW_DISCONNECT_DONE,
    APP_EVENT_NW_CONNECT_FAILED,
    APP_EVENT_NW_DISCONNECT_FAILED,
    APP_EVENT_SYNC_LOSS_DISCONNECT_DONE,
    APP_EVENT_WLAN_DISCONNECT_INDICATION,

    APP_EVENT_BATT_CHK_INITIATED,
    APP_EVENT_BATT_CHK_INDICATION,
    APP_EVENT_STA_DISCONNECT_DONE,
    APP_EVENT_STA_WPS_INITIATE,
    APP_EVENT_FWUP_COPY_TO_INT_FLASH,
	APP_EVENT_NCM_EXECUTE,
	APP_EVENT_MDNS_EXECUTE,
	APP_EVENT_STAT_OUT,
	APP_EVENT_STANDBY,
	APP_EVENT_DAB_INDIACTION,
	APP_EVENT_FWUP_SUCCESS,
	APP_EVENT_MDNS_SERVICE_DISCOVERED,
	APP_EVENT_START_SERVICE_DISCOVER,
} APP_EVENTS_T;



#endif /* _APP_EVENTS_H_ */
