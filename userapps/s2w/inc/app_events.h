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
* Description : This file contains general definitions.
*****************************************************************************/
#ifndef _APP_EVENTS_H_
#define _APP_EVENTS_H_

/****************************************************************************
  * File Inclusions
  ****************************************************************************/

/**
 *****************************************************************************
 * @file gsn_events_app.h
 * @brief GSN application events.
 *    This file contains event related definitions used in the system.
 ****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnEventsApp GSN application events.
 *    This group contains application event related definitions.
 ****************************************************************************/



/****************************************************************************
  *  Definitions
  ****************************************************************************/

/****************************************************************************
  *  Type Definitions
  ****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnEventsApp
 * @brief Event events used by the application.
 *    This enum defines all the asynchronous event events used by the application.
 *    These event values are not passed in callback status parameters but
 *    are used as events to application main task.
 *****************************************************************************/
typedef enum APP_EVENTS
{
    /**< Application events should start after core events */
    APP_EVENT_HEART_BEAT_TIMEOUT = 0,//GSN_WIF_SYS_MAX_MSG,
    APP_EVENT_REMOTE_MGMT_TIMEOUT,
    APP_EVENT_SENSOR_READ_TIMEOUT,
    APP_EVENT_ASSOC_KEEP_ALIVE_TIMEOUT,
    APP_EVENT_SYNC_LOSS_INDICATION,

    APP_EVENT_NW_UP_SUCCESS,
    APP_EVENT_NW_UP_FAILURE,
    APP_EVENT_NW_LINK_FAILURE,
    APP_EVENT_DHCP_RENEW_FAILURE,
    APP_EVENT_NW_DOWN_FAILURE,
    APP_EVENT_NW_SHUTDOWN_SUCCESS,
    APP_EVENT_NW_SHUTDOWN_FAILURE,
    APP_EVENT_ASSOC_KEEP_ALIVE_DONE,
    APP_NOTIFICATION_BATT_INDICATION,
    APP_NOTIFICATION_IPRF_START,
    APP_NOTIFICATION_PING_INDICATION,
    APP_NOTIFICATION_TRACE_START,
    APP_NOTIFICATION_AUTO_SEND,
    APP_NOTIFICATION_ASYNC_RX,
    APP_EVENT_STA_DISCONNECT_DONE,
#ifdef S2W_SNTP
    APP_EVENT_TIME_SYNC_INDICATION,
    APP_TIME_SYNC_TIMER_INDICATION,
#endif
#ifdef GSN_P2P
    APP_EVENT_P2P_DEV_FOUND,
    APP_EVENT_P2P_ASYNC_REQUEST,
#endif
	APP_EVENT_FWUP_SUCCESS,
   APP_EVENT_NCM_L2CONNECT,
    APP_EVENT_NCM_L4CONNECT,
    APP_NOTIFICATION_WPS_START,
    APP_NOTIFICATION_SRVR_STOP,
    APP_NOTIFICATION_SRVR_ONLY_STOP,
    APP_NOTIFICATION_PROV_ONLY_STOP,
    APP_NOTIFICATION_SRVR_START,
    APP_NOTIFICATION_PROV_START,
    APP_EVENT_DHCP_RENEW_IP_CHANGED,
    APP_EVENT_DHCP_STOP_REQUEST,
    APP_EVENT_DHCP_LEASETIME_EXPIRED,
    APP_EVENT_PING_REQUEST,
    APP_EVENT_PING_STOP,
#ifdef S2W_IPv6_SUPPORT
    APP_EVENT_DHCPv6_STOP_REQUEST,
#endif
    APP_EVENT_NCM_EXECUTE,
    APP_EVENT_MDNS_EXECUTE,
#ifdef S2W_PERSISTENT_TMR_SUPPORT    
    APP_EVENT_PERSISTANT_TMR_0_TIMEOUT,
    APP_EVENT_PERSISTANT_TMR_1_TIMEOUT,
    APP_EVENT_PERSISTANT_TMR_2_TIMEOUT,
    APP_EVENT_PERSISTANT_TMR_3_TIMEOUT,
    APP_EVENT_PERSISTANT_TMR_4_TIMEOUT,
#endif    
    APP_EVENT_WPS_ASSOC,
    APP_EVENT_DHCPv4_IP_CONFLICT,
    APP_ZIP_DELAY_PROCESS_EVENT,
    APP_EVENT_GRPPROV_VERIFICATION,
    APP_NOTIFICATION_APPLY_SYS_REST,
    APP_EVENT_EXIT_DP_SLEEP,
    APP_EVENT_CID_FAILURE,
    APP_EVENT_DATA_SEND_FAILURE,
    APP_EVENT_S2W_EINVAL,
	APP_EVENT_MAX
} APP_EVENTS_T;



#endif /* _APP_EVENTS_H_ */
