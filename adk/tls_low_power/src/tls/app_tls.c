/*****************************************************************
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
* $RCSfile: app_tls.c,v $
*
*******************************************************************
*
* Description : This file contains the source code for the reference
*                   application on the TLS board.
*
*               The reference application collects data for
*               - Light Sensor (APDS-9005)
*               - Temperature sensor (Thermistor DO-35)
*               - Battery charge
*               - Signal strength of the last received data packet
*
*               It then packs all this raw data as per GainSpan Data Packet
*               format in a single UDP or TCP packet and sends it to the data
*               server. The translation of the raw data to the actual values is
*               done on the data server
*
******************************************************************************/

/********************************* File inclusion ****************************/
#include "gsn_includes.h"
#include "app_defines.h"
#include "app_events.h"
#include "config\app_resource_config.h"
#include "app_rtc_mem.h"
#include "config/app_cfg.h"
#include "fs_if/app_fsIf.h"
#include "gsn_ncm.h"
#include "config/app_cfg.h"
#include "app_main_ctx.h"
#include "app_sm.h"
#include "app_ncm.h"
#include "app_resource_config.h"
#include "app_events.h"
#include "app_debug.h"

/************************ Private Variables**************************************/

PRIVATE GSN_ADC_HANDLE_T   adchandle;
PRIVATE GSN_ADC_CONFIG_T 	adcconfig;
PRIVATE GSN_ADC_RW_ARGS_T 	adcrw;

/************************ Private MACRO **************************************/

/* GPIO Pin:20 used for Temp Sensor */
#define APP_TLS_GPIO_TEMP_POWER_OUT     20

/* GPIO Pin:21 used for Light Sensor */
#define APP_TLS_GPIO_LIGHT_POWER_OUT    21

/* GPIO Pin:30 used for RED LED */
#define APP_TLS_GPIO_RED_LED            30

/* GPIO Pin:31 used for RED LED */
#define APP_TLS_GPIO_GREEN_LED          31

/* Enums defining different types in the data frame format
 */
typedef enum APP_TLS_SENSOR
{
    APP_TLS_TEMP      = 1,
    APP_TLS_LIGHT     = 2,
    APP_TLS_BATTERY   = 3
} APP_TLS_SENSOR_T;

/************* Private Function prototype ************/

PUBLIC GSN_STATUS_T
AppTls_TempOrLightGet(UINT32* tlsTempSensorData);

PRIVATE GSN_STATUS_T
AppTls_DataProcess( APP_MAIN_CTX_T*pAppCtx , APP_TLS_SENSOR_T sensor, UINT32 * data);

/*****************************************************************************/

/**************************** Public Function ********************************/

/*****************************************************************************/

/******************************************************************************
*
* Function            : AppTls_Process
*
* Input Parameters    : BOOL bGsnAlarmWakeUp - Tells the weke up reason
*
* Return Types        : VOID
*
* Description         : This function is entry function to the Application.
*
* Assumption          : None
*
* Note (LED Sequence) :
*                       1. Boot Indication        : RED LED ON
*                       2. Initiate Scanning      : GREEN LED ON
*                       3. Association Indication : GREEN LED OFF
*                       4. Application Called     : RED LED OFF & GREEN LED ON
*                       5. System Standby         : BOTH LED OFF
*
******************************************************************************/

PUBLIC VOID
AppTls_TempSensorDataGet( APP_MAIN_CTX_T *pAppCtx, UINT32* data )
{
    APP_TLS_SENSOR_T sensor = APP_TLS_TEMP;
    /* Calling the Entry function of TLS Sensor Application */
    AppTls_DataProcess( pAppCtx , sensor, data);
}

PUBLIC VOID
AppTls_LightSensorDataGet( APP_MAIN_CTX_T *pAppCtx, UINT32* data )
{
    APP_TLS_SENSOR_T sensor = APP_TLS_LIGHT;
    /* Calling the Entry function of TLS Sensor Application */
    AppTls_DataProcess( pAppCtx , sensor, data);
}

PUBLIC VOID
AppTls_BatteryValueGet( APP_MAIN_CTX_T *pAppCtx, UINT32* data )
{
    APP_TLS_SENSOR_T sensor = APP_TLS_BATTERY;
    /* Calling the Entry function of TLS Sensor Application */
    AppTls_DataProcess( pAppCtx , sensor, data);
}

PUBLIC VOID
AppTls_SensorPowerUp()
{
#ifndef POWER_MEASUREMENT_ENABLE
	GsnGpio_OutIndvidualSet(0x00300000);
#endif
}
/*****************************************************************************/

/****************************** Private Function *****************************/
/******************************************************************************
*
* Function          : GsnGetTlsTemp
*
* Input Parameters  : UINT32* pu32BattSensorData : Buffer to collect the
*                       Battery sensor data.
*
* Return Types      : GSN_STATUS
*
* Description       : This function reads the battery sensor and returns the
*                     sensor data
*
* Assumption        :
*
******************************************************************************/
PUBLIC GSN_STATUS_T
AppTls_TempOrLightGet(UINT32* tlsTempSensorData)
{
    UINT32 channel;

    memset(&adchandle, 0, sizeof(adchandle));
    memset(&adcconfig, 0, sizeof(adcconfig));
    memset(&adcrw, 0, sizeof(adcrw));

    adcconfig.refVoltage = GSN_ADC_REF_EXTERNAL ;
    adcconfig.readMode = GSN_ADC_MODE_SINGLE;
    adcconfig.pdPolarity = GSN_ADC_PDPOLARITY_H;
    adcconfig.sup1p8 = GSN_ADC_AVDD_3Vrange;
    adcconfig.enlvl =  GSN_ADC_LVL_ENABLE;
    adcconfig.enDvdd = GSN_ADC_DVDD_ENABLE ;
    adcconfig.en100kHz = GSN_ADC_EN100K_ENABLE ;
    adcconfig.enTrim = GSN_ADC_TRIM_DISABLE ;
    //adcconfig.chnSel = 0xf;
    adcconfig.threshselect = GSN_ADC_NO_THRESH_SEL;//GSN_AADC_SET0_THRESH ;
    adcconfig.thresh0.lower = 0;
    adcconfig.thresh0.upper = 0;
    adcconfig.startCycles = 1;
    adcconfig.powerCycles = 200 ;
    adcconfig.samplePeriod = 1 ; //for periodic mode
    adcconfig.adcClk = GSN_ADC_CLK_SEL_XTAL;
    adcconfig.samplingfreq = 100000;
    adcconfig.startPolarity = GSN_ADC_STARTPOLARITY_L;
	adcconfig.singlePolling = TRUE;

	GsnADC_Open(&adchandle,&adcconfig);
#if 0
    // power up sensors 20 & 21 for temp and light sensors
    //GsnGpio_Init(0xC0300000,0x3fcfffff);
    //GsnGpio_Init(0x00300000,0xffcfffff);
#ifdef #ifndef POWER_MEASUREMENT_ENABLE
    GsnGpio_OutIndvidualSet(0x00300000);
#endif
    // put a delay
    {
      int h=0;
      for(h=0;h<3000;h++);

    }
#endif
    channel = GSN_ADC_SOURCE_CH_0 | (GSN_ADC_SOURCE_CH_1 << 4) | (GSN_ADC_SOURCE_CH_END << 8);

    adcrw.buffer.size = 2;
    adcrw.buffer.pData = tlsTempSensorData;
    adcrw.funcCB=NULL;
    * tlsTempSensorData= 0;
#if 0
    GsnAdc_Read(&adchandle,GSN_ADC_MODE_SINGLE, channel,&adcrw,GSN_ADC_REF_EXTERNAL);
#else
    GsnADC_PollRead(&adchandle,GSN_ADC_MODE_SINGLE, channel,&adcrw,GSN_ADC_REF_EXTERNAL);
#endif
    tlsTempSensorData[0] &= 0xfff;
    tlsTempSensorData[1] &= 0xfff;


    GsnADC_Close(&adchandle);
    return GSN_SUCCESS;
}

/******************************************************************************
*
*  Function          :  GsnTLSSensorFunctionEntry
*
*  Input Parameters  :  u32Address - The wakeup source
*                       - TRUE is Alarm Wakeup
*                       - FALSE is RTC Wakeup
*
*  Return Types      :  UV_VALUE - The possible values
*                       - GSN_SUCCESS
*                       - GSN_FAILURE
*
*  Description       :  This function is entry function for "TLS Sensor"
*                       Application.
*
*  Assumption        :
*
******************************************************************/

PRIVATE GSN_STATUS_T
AppTls_DataProcess( APP_MAIN_CTX_T *pAppCtx, APP_TLS_SENSOR_T sensor, UINT32 * data)
{
    UINT32 datalocal[2];
    GSN_STATUS_T status;

#if 0
    /* If Semaphore is not created, create the semaphore and make it unavailable.
       */
    if( !appTlsSensorSettleSemCreated )
    {
        /* Create the Tls Semaphore */
        ( GsnOsal_SemCreate ( &appTlsSensorSettleWaitSem, 0 ) );
        /* Mark the semaphore is created */
        appTlsSensorSettleSemCreated = TRUE;
    }
#endif

    switch (sensor)
    {
        case APP_TLS_TEMP:
        {
#if 0
            status = AppTls_TempSensorInit();

            if ( GSN_SUCCESS == status )
#endif
            {
                /* The Temperature Sensor is connected to the External:1 ADC on TLS
                        * Read the value from the Ext:1 ADC for the Temperature Data
                        */
                status = AppTls_TempOrLightGet( datalocal);
            }
#if 0
            /* Check if reading Data from ADC Failed, go to Standby */
            if ( GSN_FAILURE == status )
            {
                goto AppTls_DataProcessExit;
            }
#endif
            *data = datalocal[0];

        }
        break;

        case APP_TLS_LIGHT:
        {
            /***************************Light Sensor*************************/
#if 0
            /* Initializing the Light sensor */
            status = AppTls_LightSensorInit();

            if ( GSN_SUCCESS == status )
            {

                /* Wait for Settling time of Sensor before taking the reading
                 * The Settling time for light sensor is 100ms */
                 if (appTlsInitialized == FALSE)
                 {
                     status = AppTls_LightSensorSettle();
                     appTlsInitialized = TRUE;
                 }

                 if ( GSN_SUCCESS == status )
#endif
                 {
                     /* The light Sensor is connected to the External:2 ADC on the Tls
                      * Read the value from the Ext:2 ADC for the Light Data */
                     status = AppTls_TempOrLightGet( datalocal );
                 }
#if 0
            }
#endif
            *data = datalocal[1];
        }
        break;

#if 0
        case APP_TLS_BATTERY:
        {
            /* The Battery data is collected from the Internal ADC
             * The macro first initializes the Battery sensor and then reads the
             * internal sensor and returns the Battery Value.
             */
             datalocal = AppBattChk_LatestBattValGet( &pAppSm->battChk );
        }
        break;
#endif

    }
    return status;

}




