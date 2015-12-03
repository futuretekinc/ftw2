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
* $RCSfile: app_emu.h,v $
*
* Description : 
*******************************************************************************/
#ifdef S2W_EMU

#ifndef _APP_EMU_H_
#define _APP_EMU_H_

#ifdef  __cplusplus
extern "C" {
#endif


/**
  ******************************************************************************
  *
  *  File inclusion 
  *
  *****************************************************************************/
#include "modules/emu/gsn_emu.h"


/**
  ******************************************************************************
  *
  *  Macros 
  *
  *****************************************************************************/
#ifdef EMU_DEBUG
#define EMU_Printf S2w_Printf
#else
#define EMU_Printf(...)
#endif
    
    
#define APP_EMU_THREAD_PRIORITY 22
#define APP_EMU_STACK_DEPTH (4 * 1024)
#define APP_EMU_MSGQUE_DEPTH (128)

#define APP_EMU_SDADC_BUF_SIZE 1000    
/**
  ******************************************************************************
  *
  *  Public data types 
  *
  *****************************************************************************/

typedef struct APP_EMU_CTX
{
    /*Variables for EMU thread*/
    /*message queue for emu thread*/
    GSN_OSAL_QUEUE_T appEmuMsgQue;
    /*emu stack */
    UINT8 appEmuStack[APP_EMU_STACK_DEPTH];
    UINT8 appEmuMsgQueBuf[APP_EMU_MSGQUE_DEPTH*sizeof(GSN_EMU_MSG_T)];
    /*thread control block for emu*/
    GSN_OSAL_THREAD_TCB_T appEmuTcb;

    /* For SDADC */

    UINT16 *appEmuSdadcPbuf1;
    UINT16 *appEmuSdadcPbuf2;
    UINT16 *appEmuSdadcPbuf3;
    UINT16 *appEmuSdadcPbuf4;
#ifdef S2W_EMU_STATIC          
    UINT16 appEmuSdadcBuf1[APP_EMU_SDADC_BUF_SIZE];
    UINT16 appEmuSdadcBuf2[APP_EMU_SDADC_BUF_SIZE];
    UINT16 appEmuSdadcBuf3[APP_EMU_SDADC_BUF_SIZE];
    UINT16 appEmuSdadcBuf4[APP_EMU_SDADC_BUF_SIZE];
#endif
    GSN_EMU_CTX_T emu;
    GSN_EMU_CONF_VALUE_T confValue;

}APP_EMU_CTX_T;

typedef enum APP_EMU_CONFS
{
    APP_EMU_START = 0,
    
    APP_EMU_CONF_MODULE , //SD-ADC or PL7223
    
    /*enum values from 2 to 20 are reserved for common configurations*/
    APP_EMU_CONF_PL722X_SPI_CHANNEL = 20 ,  //spi channel of pl7223
    APP_EMU_CONF_PL722X_SET_FREQ_MS, //how frequent to read pl7223 for getting values
    APP_EMU_CONF_PL722X_CS_GPIO,	//chip select gpio for pl722x
    APP_EMU_CONF_PL722X_RST_GPIO,	//reset select gpio for pl722x    
    /*enum values from  24 to 40 are reserved for pl722x configurations*/
    
    APP_EMU_CONF_SDADC_VCC = 40 , //voltage calibration constant
    APP_EMU_CONF_SDADC_ICC, //Current calibration constant 
	
    APP_EMU_CONF_SDADC_VDCOFFSET, //voltage dc offset
    APP_EMU_CONF_SDADC_IDCOFFSET, //current dc offset
	
    APP_EMU_CONF_SDADC_VSF,  //voltage scaling factor
    APP_EMU_CONF_SDADC_ISF,  //current scaling factor
	
    APP_EMU_CONF_SDADC_SF,   //sampling frequency
    APP_EMU_CONF_SDADC_LCG,   //load control gpio
	
    APP_EMU_CONF_SDADC_VUT,  //voltage upper threshold
    APP_EMU_CONF_SDADC_IUT,  //current upper threshold
    APP_EMU_CONF_SDADC_FUT,  //Frequency upper threshold

    APP_EMU_CONF_SDADC_VLT,  //voltage lower threshold
    APP_EMU_CONF_SDADC_ILT,  //current lower threshold
    APP_EMU_CONF_SDADC_FLT,  //Frequency lower threshold
	
    APP_EMU_CONF_SDADC_VAC,  //voltage adc channel
    APP_EMU_CONF_SDADC_IAC,  //CURRENT adc channel
       
    APP_EMU_CONF_SDADC_G0,   //gain on channel 0
    APP_EMU_CONF_SDADC_G1,   //gain on channel 1
    APP_EMU_CONF_SDADC_G2,   //gain on channel 2

	APP_EMU_CONF_SDADC_ATTENCONST,   //attenuation constant
	
    APP_EMU_END,

}APP_EMU_CONFS_T;

    
/**
  ******************************************************************************
  *
  *  Public variable 
  *
  *****************************************************************************/



/**
  ******************************************************************************
  *
  *  Private variable 
  *
  *****************************************************************************/



/**
  ******************************************************************************
  *
  *  Public Functions 
  *
  *****************************************************************************/

PUBLIC GSN_STATUS_T
AppEmu_Init (GSN_EMU_CTX_T *emuCtx, GSN_EMU_APPNOTIFICATION_FUNC_T appCb, VOID* cbCtx);


PUBLIC GSN_STATUS_T
AppEmu_DeInit (GSN_EMU_CTX_T *emuCtx);

PUBLIC VOID
AppEmu_Callback(UINT32 arg1, VOID *arg2);

PUBLIC GSN_EMU_STATUS_T
AppEmu_BuffAllocate(VOID);

PUBLIC GSN_EMU_STATUS_T
AppEmu_BuffDeallocate(VOID);




/**
  ******************************************************************************
  *
  *  Private Functions 
  *
  *****************************************************************************/




#ifdef  __cplusplus
}
#endif

#endif //APP__EMU_H_

#endif /*S2W_EMU*/
