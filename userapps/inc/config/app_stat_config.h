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
* $RCSfile: app_stat_config.h,v $
*
* Description : This file contains public definitions for inital board specific 
*     configuration.
*****************************************************************************/
#ifndef _APP_STAT_CONFIG_H_
#define _APP_STAT_CONFIG_H_

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif
/**
 *****************************************************************************
 * @file app_stat_config.h
 * @brief App Statistic configuration public header.
 *    This file contains the public definition for App statistic configuration.
 *****************************************************************************/
 
/**
 *****************************************************************************
 * @defgroup AppStatConfig configuration definitions.
 *    This group contains Stat specific configuration definitions.
 *****************************************************************************/


/*****************************************************************************
  * Type Definitions
  ****************************************************************************/
/**
 *****************************************************************************
 * @ingroup BSConfig
 * @brief Board specific coinfiguration group structure.
 *    This structure defines Board specific configuration group structure. This
 *    is private to the module.
 *****************************************************************************/
typedef struct APP_STAT_CONFIG
{
    UINT8 appWdCount;
    UINT8 wlanWdCount;
    UINT8 wlanAssertCount;
    UINT8 wlanAbortCount;

    UINT8 appSwResetCount;
    UINT8 wlanSwResetCount;
    UINT8 sysQualResetCount;
} APP_STAT_CONFIG_T;

/**
 *****************************************************************************
 * @ingroup AppStatConfig
 * @brief Enum for Stat coinfiguration Ids.
 *    This enum defines the configuration IDs for Stat.
 *****************************************************************************/
typedef enum APP_STAT_CFG_ID_T
{
    APP_STAT_CFG_APP_WD_COUNT_ID,
    APP_STAT_CFG_WLAN_WD_COUNT_ID,
    APP_STAT_CFG_WLAN_ASSERT_COUNT_ID,
    APP_STAT_CFG_WLAN_ABORT_COUNT_ID,

    APP_STAT_CFG_APP_SW_RESET_COUNT_ID,
    APP_STAT_CFG_WLAN_SW_RESET_COUNT_ID,

    APP_STAT_CFG_SYS_QUAL_RESET_COUNT_ID,
    APP_STAT_CFG_MAX_ID
}APP_STAT_CFG_ID_T;

/**
 ******************************************************************************
 * @ingroup AppStatConfig
 * @brief Get Stat configuration.
 *    This function gives the Stat configuration for the requested 
 *    configuration Id.
 * @param id - IN ID of the ocnfiguration.
 * @param pVal - OUT Pointer where the value has to be written.
 * @return GSN_SUCCESS, if the procedure is success, else GSN_FAILURE. Failure 
 *    happens, if id is incorrect or the flash write fails.
 ******************************************************************************/
PUBLIC GSN_STATUS 
AppStatCfg_Get( APP_STAT_CFG_ID_T id, UINT8 *pVal );

/**
 ******************************************************************************
 * @ingroup AppStatConfig
 * @brief Set Stat configuration.
 *    This function sets the Stat configuration for the requested 
 *    configuration Id.
 * @param id - IN ID of the ocnfiguration.
 * @param pVal - IN Pointer where the configuration value is written.
 * @return GSN_SUCCESS, if the procedure is success, else GSN_FAILURE. Failure 
 *    happens, if id is incorrect or the flash write fails.
 ******************************************************************************/
PUBLIC GSN_STATUS 
AppStatCfg_Inc( APP_STAT_CFG_ID_T id );

/**
 ******************************************************************************
 * @ingroup AppStatConfig
 * @brief Initializes the Stat configuration.
 *    This function initailizes the Stat configuration to the set 
 *    default value.
 * @return GSN_SUCCESS, if the procedure is success, else GSN_FAILURE.
 ******************************************************************************/
PUBLIC GSN_STATUS 
AppStatCfg_Init( APP_STAT_CONFIG_T *pStatPtr );

#ifdef __cplusplus
}
#endif
#endif /* _APP_STAT_CONFIG_H_ */

/*****************************************************************************/


