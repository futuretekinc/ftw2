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
* $RCSfile: app_bs_config.h,v $
*
* Description : This file contains public definitions for inital board specific
*     configuration.
*****************************************************************************/
#ifndef _APP_BS_CONFIG_H_
#define _APP_BS_CONFIG_H_

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif
/**
 *****************************************************************************
 * @file app_bs_config.h
 * @brief App BS configuration public header.
 *    This file contains the public definition for App board specific
 *    configuration.
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup AppBSConfig board specific configuration definitions.
 *    This group contains board specific configuration definitions.
 *****************************************************************************/

/**
 ******************************************************************************
 * @ingroup AppBSConfig
 * @brief peropharel map.
 *     Peripheral MAP for APP CPU. Read on a cold boot, this is READONLY.
 ****************************************************************************/
#define APP_BS_CFG_PERIPHERAL_MAP GSN_WIF_SYS_APP_CPU_ALL_PERIPHERALS

/**
 ******************************************************************************
 * @ingroup AppBSConfig
 * @brief GPIO map.
 *     GPIO MAP for APP CPU. This is READONLY.
 ****************************************************************************/
#define APP_BS_CFG_GPIO_MAP 0xF1F83FE0 /* ALL GPIOs */


/**
 ******************************************************************************
 * @ingroup AppBSConfig
 * @brief MUX FN VALUE configuration.
 *     Indicates how the pins of GS1010 need to be configured, either as GPIO
 *     or as pheripharal pins
 *     PWM pins are configured as GPIO for testing purpose.
 ****************************************************************************/
#define APP_BS_CFG_MUXFN_VALUE (0xF000 | BIT4 | BIT5 | BIT6 | BIT7)

/**
 ******************************************************************************
 * @ingroup AppBSConfig
 * @brief MUX FN MASK configuration.
 *     Indicates which all bits of gcu32GsnMuxFunctionValue will be read to
 *     configure the MUX Functionality.
 ****************************************************************************/
#define APP_BS_CFG_MUXFN_MASK 0xF0FF

/**
 ******************************************************************************
 * @ingroup AppBSConfig
 * @brief External PA configuration.
 *     Indicates whether to enable external Power Amplifier (PA) or not.
 ****************************************************************************/
#define APP_BS_CFG_EXTERNAL_PA_ENABLED FALSE

/**
 ******************************************************************************
 * @ingroup AppBSConfig
 * @brief Transmit power configuration.
 *     Indicates what tx power to use, Can take value 0 to 7.
 ****************************************************************************/
#define APP_BS_CFG_TX_POWER 0

/**
 ******************************************************************************
 * @ingroup AppBSConfig
 * @brief External HW settleing flag configuration.
 *     Indicates if the External Hardware stettling parameters configuration
 *     requried or not. NOTE: if we set these parameters, it comes into effect
 *     only in the next boot. Flag that tells if the following two parameters
 *     should be updated in HW.
 ****************************************************************************/
#define APP_BS_CFG_UPDATE_EXT_HW_SETTLE_PARAM   FALSE

/**
 ******************************************************************************
 * @ingroup AppBSConfig
 * @brief DC DC wakeup time configuration.
 *     Indicates DC-DC startup time in terms of 32KHz clock cycles. NOTE: if
 *     we set these parameters, it comes into effect
 *     only in the next boot. Flag that tells if the following two parameters
 *     should be updated in HW.
 ****************************************************************************/
#define APP_BS_CFG_DC_DC_WAKEUP_TIME    66

/**
 ******************************************************************************
 * @ingroup AppBSConfig
 * @brief RTC RF EN length configuration.
 *     44 MHz oscillator startup time in terms of 32KHz clock cycles. NOTE: if
 *     we set these parameters, it comes into effect
 *     only in the next boot. Flag that tells if the following two parameters
 *     should be updated in HW.
 ****************************************************************************/
#define APP_BS_CFG_RTC_RF_EN_LENGTH 164

/**
 ******************************************************************************
 * @ingroup AppBSConfig
 * @brief Deep sleep configuration.
 *     TRUE if deep-sleep is enabled. While debugging suing JTAG this can be
 *     disabled.
 ****************************************************************************/
#define APP_BS_CFG_DEEP_SLEEP_ENABLE    TRUE

/**
 ******************************************************************************
 * @ingroup AppBSConfig
 * @brief TX confirmation configuration.
 *     Configuration to receive TX confirmation. Some application can optimize
 *     the runtime by not processing the tx confirmation.
 ****************************************************************************/
#define APP_BS_CFG_TX_CFM_ENABLE    TRUE

/**
 ******************************************************************************
 * @ingroup AppBSConfig`
 * @brief FWUP External flash based Trigger Mechanism
 *     1st byte consists of BIT no in MUXFN register , 2nd byte consists of GPIO No . for  eg for 
 * GPIO21 , the value of the parameter should be  0xffff150e. 0xffff190c is GPIO 13.   
 ****************************************************************************/
#define APP_FWUP_CFG_DFLT_FACTORY_TRIGGER    0xffff150e

/*****************************************************************************
  * Type Definitions
  ****************************************************************************/

/**
 *****************************************************************************
 * @ingroup AppBSConfig
 * @brief Enum for State machine FWUP coinfiguration Ids.
 *    This enum defines the configuration IDs for State machine FWUP.
 *****************************************************************************/
typedef enum APP_BS_CFG_ID_T
{
    APP_BS_CFG_PERIPHARAL_MAP_ID,
    APP_BS_CFG_GPIO_MAP_ID,
    APP_BS_CFG_MUX_FN_VALUE_ID,
    APP_BS_CFG_MUX_FN_MASK_ID,
    APP_BS_CFG_EXTERNAL_PA_ID,
    APP_BS_CFG_TX_POWER_ID,
    APP_BS_CFG_EXT_HW_SETTLE_ID,
    APP_BS_CFG_DC_DC_WAKEUP_TIME_ID,
    APP_BS_CFG_RTC_RF_EN_LENGTH_ID,
    APP_BS_CFG_DEEP_SLEEP_ENABLE_ID,
    APP_BS_CFG_TX_CFM_ENABLE_ID,
    APP_BS_CFG_MAX_ID
}APP_BS_CFG_ID_T;

/**
 ******************************************************************************
 * @ingroup AppBSConfig
 * @brief Get board specific configuration.
 *    This function gives the board specific configuration for the requested
 *    configuration Id.
 * @param id - IN ID of the ocnfiguration.
 * @param pVal - OUT Pointer where the value has to be written.
 * @return GSN_SUCCESS, if the procedure is success, else GSN_FAILURE. Failure
 *    happens, if id is incorrect or the flash write fails.
 ******************************************************************************/
PUBLIC GSN_STATUS
AppBsCfg_Get( APP_BS_CFG_ID_T id, VOID *pVal );

/**
 ******************************************************************************
 * @ingroup AppBSConfig
 * @brief Set board specific configuration.
 *    This function sets the board specific configuration for the requested
 *    configuration Id.
 * @param id - IN ID of the ocnfiguration.
 * @param pVal - IN Pointer where the configuration value is written.
 * @return GSN_SUCCESS, if the procedure is success, else GSN_FAILURE. Failure
 *    happens, if id is incorrect or the flash write fails.
 ******************************************************************************/
PUBLIC GSN_STATUS
AppBsCfg_Set( APP_BS_CFG_ID_T id, VOID *pVal );

/**
 ******************************************************************************
 * @ingroup AppBSConfig
 * @brief Initializes the board specific configuration.
 *    This function initailizes the board specific configuration to the set
 *    default value.
 * @return GSN_SUCCESS, if the procedure is success, else GSN_FAILURE.
 ******************************************************************************/
PUBLIC GSN_STATUS
AppBsCfg_Init( BOOL grpInit );


#ifdef __cplusplus
}
#endif
#endif /* _APP_BS_CONFIG_H_ */

/*****************************************************************************/


