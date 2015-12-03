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
* $RCSfile: app_config.h,v $
*
* Description : This file contains public declaration for app configuration.
*****************************************************************************/
#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/

/**
 *****************************************************************************
 * @file app_config.h
 * @brief App configuration public header.
 *    This file contains the public declaration for app configuration.
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup AppConfig.
 *    This group contains app configuration definitions.
 *****************************************************************************/


/*****************************************************************************
  * Type Definitions
  ****************************************************************************/
#ifdef S2W_PERSISTENT_TMR_SUPPORT
	/**
	 ******************************************************************************
	 * @ingroup AppResourceConfig
	 * @brief Persistenet timer configuration.
	 *	  These MACROs defines the number of different persistent timer used by app.
	 ******************************************************************************/
#define APP_NUM_OF_CONST_PERSIST_TMR 4 /**< config,heart beat,keep alive,ptp */
#define APP_NUM_OF_VAR_PERSIST_TMR   1 /**< sensor reading */
#define APP_NUM_OF_PERSIST_TMR       \
		APP_NUM_OF_VAR_PERSIST_TMR + APP_NUM_OF_CONST_PERSIST_TMR
	typedef struct APP_PERSIST_TMR_CFG
	{
		ULONG64 persistTime[APP_NUM_OF_PERSIST_TMR];
		UINT8	persistTmrNvds[ GSN_P_TMR_NVDS_MEM_SIZE( APP_NUM_OF_PERSIST_TMR )];
	}APP_PERSIST_TMR_CFG_T;
	
#endif

#if 0
/**
 *****************************************************************************
 * @ingroup AppConfig
 * @brief App Config Init
 *    This function initializes the app config module.
 *****************************************************************************/
 PUBLIC INLINE GSN_STATUS
 AppConfig_Init( BOOL grpInit, APP_STAT_CONFIG_T *rtcMem )
 {
     AppCfg_Init( grpInit );
     return GSN_SUCCESS;
 }
#endif
#endif /* _BATT_CHK_CONFIG_H_ */

/*****************************************************************************/


