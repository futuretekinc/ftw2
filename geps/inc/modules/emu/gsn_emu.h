/******************************************************************************
*
*               COPYRIGHT (c) 2013-2014 GainSpan Corporation
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
* $RCSfile: gsn_emu.h,v $
*
* Description : 
*******************************************************************************/
#ifndef _GSN_EMU_H_
#define _GSN_EMU_H_


#ifdef  __cplusplus
extern "C" {
#endif

#define ARM_MATH_CM3
#include "arm_math.h"

/**
 *******************************************************************************
 * @file gsn_emu.h
 * @brief GSN EMU public header.
 *    This file contains the public APIs and structures of EMU
 ******************************************************************************/


/**
 *****************************************************************************
 * @ingroup syssvcdoc
  *
 * @{
  *****************************************************************************/


/**
 *******************************************************************************
 * @defgroup GsnEmu GSN Energy Measurement Unit
 * @brief  GSN Energy Measurement Unit
  *
 ******************************************************************************/

/**
 *****************************************************************************
  *
 * @}
  *****************************************************************************/

#include "gsn_includes.h"
#include "modules/emu/gsn_emu_common.h"

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief List the energy measurment units supported
  *
 * Note: Make sure to provide values in multiples of 2, so that when supported
 *       list is requested or'ed value could be returned back.
 ******************************************************************************/

/**
* List the energy measurment units supported
* Note: Make sure to provide values in multiples of 2, so that when supported 
* list is requested or'ed value could be returned back.          
*/
typedef enum GSN_EMU_MODULE
{
    GSN_EMU_MODULE_SIGMADELTA_ADC  = 1,
    GSN_EMU_MODULE_PL722X    = 2,

    GSN_EMU_LIST_MAX
}GSN_EMU_MODULE_T;

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief Mode (Normal mode or calibration)
 *
 ******************************************************************************/
typedef enum GSN_EMU_MODE
{
    GSN_EMU_MODE_NORMAL = 0,
    GSN_EMU_MODE_CALIB,

}GSN_EMU_MODE_T;


/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief State of EMU
 *
 ******************************************************************************/
typedef enum GSN_EMU_STATE
{
    GSN_EMU_STATE_INITIALIZED,
    GSN_EMU_STATE_RUNNING,
    GSN_EMU_STATE_PAUSED,
    GSN_EMU_STATE_STOPPED,
    GSN_EMU_STATE_DEINITINPROGRESS,
    GSN_EMU_STATE_DEINITIALIZED,    
}GSN_EMU_STATE_T;

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief Structure maintaining the electric parameters
 *
 ******************************************************************************/
typedef struct GSN_EMU_ELECTRIC_PARAMS
{
    float vrms;
    float irms;
    float activePower;
    float powerfactor;
    float frequency;
    float accumulateEnergy;
    BOOL loadState; //on or off 
    
}GSN_EMU_ELECTRIC_PARAMS_T;

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief Enum for ADC Channel
 *
 ******************************************************************************/
typedef enum GSN_EMU_ADC_CHANNEL
{
    GSN_EMU_SDADC_CHANNEL_0 = GSN_SDADCDAC_ADC0,
    GSN_EMU_SDADC_CHANNEL_1 = GSN_SDADCDAC_ADC1,
    GSN_EMU_SDADC_CHANNEL_2 = GSN_SDADCDAC_ADC2,

}GSN_EMU_ADC_CHANNEL_T;

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief Enum for ADC Channel Gain
 *
 ******************************************************************************/
typedef enum GSN_EMU_CHANNEL_GAIN
{
  
  GSN_EMU_SDADC_GAIN0 = 0 ,
  GSN_EMU_SDADC_GAIN1 = 1,
  GSN_EMU_SDADC_GAIN2 = 2,
  GSN_EMU_SDADC_GAIN3 = 3,
  GSN_EMU_NO_GAIN,

}GSN_EMU_CHANNEL_GAIN_T;

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief Structure for EMU Configuration
 *
 ******************************************************************************/
typedef struct GSN_EMU_CONF_VALUE
{
    GSN_EMU_MODULE_T module; /**< SD-ADC or PL7223 */
		
    float sdadc_vcc; /**< voltage calibration constant */
    float sdadc_icc; /**< current calibration constant  */
	
    float sdadc_vdcoffset; /**< voltage dc offset */
    float sdadc_idcoffset; /**< current dc offset */

    UINT32 sdadc_vsf;  /**< voltage scaling factor */
    UINT32 sdadc_isf;  /**< current scaling factor */
	
    UINT32 sdadc_samplingFreq;   /**< sampling frequency */
    UINT32 sdadc_load_gpio;       /**< gpio for load control */
	
    float sdadc_vut;  /**< voltage upper threshold */
    float sdadc_iut;  /**< current upper threshold */
    float sdadc_fut;  /**< frequency upper threshold */

    float sdadc_vlt;  /**< voltage lower threshold */
    float sdadc_ilt;  /**< current lower threshold */
    float sdadc_flt;  /**< frequency lower threshold */

    GSN_EMU_ADC_CHANNEL_T sdadc_vac;  /**< voltage adc channel */
    GSN_EMU_ADC_CHANNEL_T sdadc_iac;  /**< current adc channel */

    GSN_EMU_CHANNEL_GAIN_T sdadc_gain0; /**< select the value of gain on channel 0 */
    GSN_EMU_CHANNEL_GAIN_T sdadc_gain1; /**< select the value of gain on channel 1 */
    GSN_EMU_CHANNEL_GAIN_T sdadc_gain2; /**< select the value of gain on channel 2 */
    
    BOOL gain_flag0 ;
    BOOL gain_flag1 ;
    BOOL gain_flag2 ;
    

    UINT8 pl722x_spi_channel;  /**< spi channel of pl7223 */
    UINT32 pl722x_readFreq_ms; /**< how frequent to read pl7223 for getting values */
    UINT32 pl722x_gpio_cs;      /**< select gpio for chip select */
    UINT32 pl722x_gpio_rst;   /**< select gpio for reset */
	
}GSN_EMU_CONF_VALUE_T;

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief Structure for EMU Message Param Configuration
 *
 ******************************************************************************/
typedef struct GSN_EMU_MSG_PARAM_CONF
{
    GSN_EMU_ELECTRIC_PARAMS_T *elecParams;
    GSN_EMU_CONF_VALUE_T *confvalue;
}GSN_EMU_MSG_PARAM_CONF_T;

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief Structure for EMU Message Buffer Configuration
 *
 ******************************************************************************/
typedef struct GSN_EMU_MSG_BUF_CONF
{
    GSN_EMU_SDADC_PINGPONG_BUFF_T *pbuff;
    GSN_EMU_CONF_VALUE_T *confvalue;
}GSN_EMU_MSG_BUF_CONF_T;

typedef VOID (* GSN_EMU_APPNOTIFICATION_FUNC_T)(UINT32 arg1, VOID *arg2);

typedef struct GSN_EMU_MODULE_FN_PTR
{
    GSN_EMU_MODULE_FN_PTR_START start;
    GSN_EMU_MODULE_FN_PTR_STOP  stop;
    GSN_EMU_MODULE_FN_PTR_RESETENERGY resetEnergy;	
    GSN_EMU_MODULE_FN_PTR_LOADCONTROL loadcontrol;
    GSN_EMU_MODULE_FN_PTR_COMPUTEELECPARAMS computeElecParam;
    GSN_EMU_MODULE_FN_PTR_GETINSTANTVALUES getInstantValues;

} GSN_EMU_MODULE_FN_PTR_T;

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief EMU Context
 *
 ******************************************************************************/
typedef struct GSN_EMU_CTX
{
    GSN_EMU_STATE_T state;

    GSN_EMU_MODE_T mode;
	
    union
    {
        GSN_EMU_PL722X_CTX_T pl722xCtx;
	GSN_EMU_SDADC_CTX_T sdAdcCtx;
    }moduleCtx;
	
    GSN_EMU_MODULE_FN_PTR_T moduleFnPtr;

    GSN_EMU_APPNOTIFICATION_FUNC_T appCbFnPtr;
    VOID *appCbCtx;

    GSN_EMU_ELECTRIC_PARAMS_T elecParams;

    GSN_EMU_CONF_VALUE_T confValue;

    /* Task notifier */
    GSN_EMU_TASKNOTIFICATION_FUNC_T taskNotifier;

	/* Variable to hold the accumilated energy */
    float g_EnergyFp;
   
    /* variabled needed for running FFT */
	q31_t voltage[2048];
	q31_t current[2048];

	q31_t voltageMag[1024];
	q31_t currentMag[1024];

}GSN_EMU_CTX_T;


/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief Get Supported Modules
  *
 * @retval UNIT32 The supported module
 ******************************************************************************/

PUBLIC UINT32
GsnEmu_GetSupportedModules();

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief Get EMU Version
 *
 * @param ptr  - IN/OUT The pointer to the version string
 * @retval VOID
 ******************************************************************************/
PUBLIC VOID
GsnEmu_GetVersion(UINT8 *ptr);

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief EMU Initialization
 *
 * @param pEmuCtx  - IN The pointer to the EMU Context
 * @param mode  - IN The mode for EMU
 * @param taskNotifier  - IN task notification function
 * @param appCb  - IN app notification function
 * @param ctx  - IN app notification function context
 *
 * @retval GSN_EMU_STATUS_SUCCESS   Operation Successful
 * @retval GSN_EMU_STATUS_FAILURE   Operation Not Successful
 *
 ******************************************************************************/
PUBLIC GSN_EMU_STATUS_T
GsnEmu_Init (GSN_EMU_CTX_T* pEmuCtx, GSN_EMU_MODE_T mode,
                  GSN_EMU_TASKNOTIFICATION_FUNC_T taskNotifier,
                  GSN_EMU_APPNOTIFICATION_FUNC_T appCb, 
                  VOID* ctx);
/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief EMU De-Initialization
 *
 * @param pEmuCtx  - IN The pointer to the EMU Context
 *
 * @retval GSN_EMU_STATUS_SUCCESS   Operation Successful
 * @retval GSN_EMU_STATUS_FAILURE   Operation Not Successful
 *
 ******************************************************************************/
PUBLIC GSN_EMU_STATUS_T
GsnEmu_DeInit(GSN_EMU_CTX_T* pEmuCtx);

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief EMU Get State
 *
 * @param pEmuCtx  - IN The pointer to the EMU Context
 * @param state  - IN/OUT The pointer to the EMU State
 *
 * @retval GSN_EMU_STATUS_SUCCESS   Operation Successful
 * @retval GSN_EMU_STATUS_FAILURE   Operation Not Successful
 *
 ******************************************************************************/
PUBLIC GSN_EMU_STATUS_T
GsnEmu_GetState(GSN_EMU_CTX_T* pEmuCtx, GSN_EMU_STATE_T *state);

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief EMU Get State
 *
 * @param pEmuCtx  - IN The pointer to the EMU Context
 * @param mode  - IN/OUT The pointer to the EMU Mode
 *
 * @retval GSN_EMU_STATUS_SUCCESS   Operation Successful
 * @retval GSN_EMU_STATUS_FAILURE   Operation Not Successful
 *
 ******************************************************************************/
PUBLIC GSN_EMU_STATUS_T
GsnEmu_GetMode(GSN_EMU_CTX_T* pEmuCtx, GSN_EMU_MODE_T *mode);

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief EMU Get Electrical Parameters
 *
 * @param pEmuCtx  - IN The pointer to the EMU Context
 * @param elecParams  - IN/OUT The pointer to the EMU Params
 *
 * @retval GSN_EMU_STATUS_SUCCESS   Operation Successful
 * @retval GSN_EMU_STATUS_FAILURE   Operation Not Successful
 *
 ******************************************************************************/
PUBLIC GSN_EMU_STATUS_T
GsnEmu_GetElectricParams(GSN_EMU_CTX_T* pEmuCtx,
                              GSN_EMU_ELECTRIC_PARAMS_T *elecParams);

PUBLIC GSN_EMU_STATUS_T
GsnEmu_GetInstantElectricParams(GSN_EMU_CTX_T* pEmuCtx,
                                  GSN_EMU_ELECTRIC_PARAMS_T*elecParams);
/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief EMU Get Load Status
 *
 * @param pEmuCtx  - IN The pointer to the EMU Context
 * @param onOff  - IN/OUT The pointer to the EMU Load Status Value
 *
 * @retval GSN_EMU_STATUS_SUCCESS   Operation Successful
 * @retval GSN_EMU_STATUS_FAILURE   Operation Not Successful
 *
 ******************************************************************************/
PUBLIC GSN_EMU_STATUS_T
GsnEmu_GetLoadStatus(GSN_EMU_CTX_T* pEmuCtx, BOOL *onOff);

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief EMU Start
 *
 * @param pEmuCtx  - IN The pointer to the EMU Context
 * @param confValue  - IN The EMU Configuration
 * @param pingBuff  - IN The pointer to the Buffer
 *
 * @retval GSN_EMU_STATUS_SUCCESS   Operation Successful
 * @retval GSN_EMU_STATUS_FAILURE   Operation Not Successful
 *
 ******************************************************************************/
PUBLIC GSN_EMU_STATUS_T
GsnEmu_Start(GSN_EMU_CTX_T* pEmuCtx, GSN_EMU_CONF_VALUE_T *confvalue, 
                GSN_EMU_SDADC_PINGPONG_BUFF_T *pingBuff);

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief EMU Stop
 *
 * @param pEmuCtx  - IN The pointer to the EMU Context
 *
 * @retval GSN_EMU_STATUS_SUCCESS   Operation Successful
 * @retval GSN_EMU_STATUS_FAILURE   Operation Not Successful
 *
 ******************************************************************************/
PUBLIC GSN_EMU_STATUS_T
GsnEmu_Stop(GSN_EMU_CTX_T* pEmuCtx);

PUBLIC GSN_EMU_STATUS_T
GsnEmu_Pause(GSN_EMU_CTX_T* pEmuCtx, GSN_EMU_ELECTRIC_PARAMS_T *elecParams);

PUBLIC GSN_EMU_STATUS_T
GsnEmu_Resume(GSN_EMU_CTX_T* pEmuCtx, GSN_EMU_ELECTRIC_PARAMS_T *elecParams, 
              GSN_EMU_CONF_VALUE_T *confvalue);

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief EMU Load Control
 *
 * @param pEmuCtx  - IN The pointer to the EMU Context
 * @param onOff  - IN The load to be ON/OFF
 *
 * @retval GSN_EMU_STATUS_SUCCESS   Operation Successful
 * @retval GSN_EMU_STATUS_FAILURE   Operation Not Successful
 *
 ******************************************************************************/
PUBLIC GSN_EMU_STATUS_T
GsnEmu_LoadControl(GSN_EMU_CTX_T* pEmuCtx, BOOL onOff);

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief EMU Reset Energy
 *
 * @param pEmuCtx  - IN The pointer to the EMU Context
 *
 * @retval GSN_EMU_STATUS_SUCCESS   Operation Successful
 * @retval GSN_EMU_STATUS_FAILURE   Operation Not Successful
 *
 ******************************************************************************/
PUBLIC GSN_EMU_STATUS_T
GsnEmu_ResetEnergy(GSN_EMU_CTX_T* pEmuCtx);

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief EMU Message Process
 *
 * @param pMsg  - IN The pointer to the EMU message
 *
 * @retval none
 *
 ******************************************************************************/
PUBLIC VOID
GsnEmu_MsgProcess(GSN_EMU_MSG_T *pMsg);

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief EMU Get configuration Pointer
 *
 * @param pEmuCtx    - IN The pointer to the EMU Context
 * @param confValue  - IN/OUT pointer to EMU configuration
 *
 * @retval GSN_EMU_STATUS_SUCCESS   Operation Successful
 * @retval GSN_EMU_STATUS_FAILURE   Operation Not Successful
 *
 ******************************************************************************/
PUBLIC GSN_EMU_STATUS_T
GsnEmu_GetConfPtr(GSN_EMU_CTX_T *pCtx, GSN_EMU_CONF_VALUE_T *confValue);

/**
 *******************************************************************************
 * @ingroup GsnEmu
 * @brief EMU Private Threshold check
 *
 * @param pEmuCtx    - IN The pointer to the EMU Context
 *
 * @retval GSN_EMU_STATUS_SUCCESS   Operation Successful
 * @retval GSN_EMU_STATUS_FAILURE   Operation Not Successful
 *
 ******************************************************************************/
PUBLIC GSN_EMU_STATUS_T
GsnEmu_PrivateCheckThreshold(GSN_EMU_CTX_T *pCtx);


#ifdef  __cplusplus
}
#endif
  
#endif //_GSN_EMU_H_


