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
* $RCSfile: app_tls.h,v $
*
* Description : This file contains the declarations commonly used.
*******************************************************************************/
#ifndef _APP_TLS_H_
#define _APP_TLS_H_

/*****************************************************************************
  * File Inclusions
  *****************************************************************************/


/**
 ******************************************************************************
 * @file app_tls.h
 * @brief Application TLS sensor.
 *    This file contains the application state machine implementation. The
 *    application state machine consists of state transitions between normal,
 *    FW update and provisioning states.
 ******************************************************************************/

/**
 ******************************************************************************
 * @defgroup AppTls
 *    This group contains the application state machine implementation. The
 *    application state machine consists of state transitions between normal,
 *    FW update and provisioning states.
 ******************************************************************************/

/******************************************************************************
  *  Datatype
  ****************************************************************************/


/****************************************************************************
  *  Public variable
  ****************************************************************************/
/****************************************************************************
  *  Public Functions
  ****************************************************************************/

/**
 ******************************************************************************
 * @ingroup GsnAppSm
 * @brief App Sm boot start.
 *    This function is called by the application to kick start the state machine. It
 *    does some initialization and then starts connecting to NW to do the required
 *    task. It also checks if the wakeup is due to alarm.
 * @param bootInd - IN boot indication message. 
 * @param appNotifCb - IN callback function to be used for notifying events to APP task. 
 * @param context - IN user context that shall be returned in callback.
 * @retval GSN_STATUS - operation successful.
 * @retval GSN_FAILURE - operation failed.
 ******************************************************************************/
	/* Enums defining different types in the data frame format
	 */
	typedef enum APP_TLS_SENSOR
	{
		APP_TLS_TEMP	  = 1,
		APP_TLS_LIGHT	  = 2,
		APP_TLS_BATTERY   = 3
	} APP_TLS_SENSOR_T;

PUBLIC GSN_STATUS_T
	AppTls_TempOrLightGet(UINT32* tlsTempSensorData);
	PRIVATE GSN_STATUS_T
	AppTls_DataProcess( APP_MAIN_CTX_T*pAppCtx , APP_TLS_SENSOR_T sensor, UINT32 * data);

#endif /* _APP_TLS_H_ */
/******************************************************************************/

