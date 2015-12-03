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
* $RCSfile: app_emu.c,v $
*
* Description : 
******************************************************************************/

#ifdef S2W_EMU
/**
  ******************************************************************************
  *
  *  @file gsn_emu_sdadc.c
  *
  *  @brief 
  *
  * Even if EMU module support multiple instances, at application layer (e.g. s2W) we will restrict it
  * to one instance.
  * During system boot up, call 'AppEmu_Init'
  *****************************************************************************/


/**
  ******************************************************************************
  *
  *  File inclusion 
  *
  *****************************************************************************/
#include "emu/app_emu.h"
#include "main/app_main_ctx.h"


/**
  ******************************************************************************
  *
  *  Macros 
  *
  *****************************************************************************/



/**
  ******************************************************************************
  *
  *  Private data types 
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
  *  Public variable 
  *
  *****************************************************************************/

  
/**
  ******************************************************************************
  *
  *  Private Functions Declarations
  *
  *****************************************************************************/

PRIVATE VOID
AppEmu_ConfInit();

PRIVATE GSN_EMU_STATUS_T
AppEmu_TaskNotify (GSN_EMU_MSG_T *pMsg);

PRIVATE VOID
AppEmu_PrivateTask(UINT32 pArg);
/**
  ******************************************************************************
  *
  *  Public Functions Definitions
  *
  *****************************************************************************/
PUBLIC GSN_STATUS_T
AppEmu_Init (GSN_EMU_CTX_T *emuCtx, GSN_EMU_APPNOTIFICATION_FUNC_T appCb, 
                                VOID* cbCtx)                                 
{
    GSN_STATUS_T status = GSN_FAILURE;
    GSN_EMU_STATUS_T emuStatus; 
    
    
    /* Creating the Mailbox to receive messages */
    /* Check message size should be in the order of 2^x */
    UINT32 msgSize = GsnOsal_QueueMsgSizeInWords(sizeof(GSN_EMU_MSG_T));
    GsnOsal_QueueCreate( &(appCtx.appEmuCtx.appEmuMsgQue), msgSize,//sizeof(GSN_EMU_MSG_T),
    ( UINT8* )(appCtx.appEmuCtx.appEmuMsgQueBuf), sizeof( appCtx.appEmuCtx.appEmuMsgQueBuf ));

    /* Create task */
    GsnOsal_ThreadCreate(AppEmu_PrivateTask,NULL, &(appCtx.appEmuCtx.appEmuTcb),
    "APP_EMU_THREAD", APP_EMU_THREAD_PRIORITY, (UINT8 *)(appCtx.appEmuCtx.appEmuStack), 
    sizeof(appCtx.appEmuCtx.appEmuStack), GSN_OSAL_THREAD_INITIAL_READY);

	 /* Initialize the configuration structure */
	 /* Initialize it from nvds if it has valid value, if not assign a safe value */
	 /* Make sure constants are copied from OTP if valid, else assign safe value */
	 AppEmu_ConfInit();

     /* Initialize emu module */
    emuStatus =  GsnEmu_Init((emuCtx),GSN_EMU_MODE_NORMAL,AppEmu_TaskNotify
                                ,appCb,cbCtx);
                             
    if(GSN_EMU_STATUS_SUCCESS == emuStatus)
    {
        /* Update the status as success */
	status = GSN_SUCCESS;
    }
    else
    {
        status = GSN_FAILURE;
    }
	
    return status;
}


PRIVATE VOID
AppEmu_ConfInit()
{
    //APP_EMU_CONF_MODULE
    appCtx.appEmuCtx.confValue.module = GSN_EMU_MODULE_SIGMADELTA_ADC;
	
    //APP_EMU_CONF_SDADC_VCC
	appCtx.appEmuCtx.confValue.sdadc_vcc = 0;
            
    //APP_EMU_CONF_SDADC_ICC
    appCtx.appEmuCtx.confValue.sdadc_icc = 0;
          
    //APP_EMU_CONF_SDADC_VDCOFFSET
	appCtx.appEmuCtx.confValue.sdadc_vdcoffset = 0;
           
    //APP_EMU_CONF_SDADC_IDCOFFSET
    appCtx.appEmuCtx.confValue.sdadc_idcoffset = 0;
            
    //APP_EMU_CONF_SDADC_VSF
    appCtx.appEmuCtx.confValue.sdadc_vsf = 8752;
            
    //APP_EMU_CONF_SDADC_ISF
    appCtx.appEmuCtx.confValue.sdadc_isf = 13554;
	
    //attenuation constat
    //appCtx.appEmuCtx.emu.attenuationConstFp = 996000;
	
    //APP_EMU_CONF_SDADC_SF
	appCtx.appEmuCtx.confValue.sdadc_samplingFreq = 4000;
      
    //APP_EMU_CONF_SDADC_LCG
    appCtx.appEmuCtx.confValue.sdadc_load_gpio = 28;

    //APP_EMU_CONF_SDADC_VUT
    appCtx.appEmuCtx.confValue.sdadc_vut = 240;
            
    //APP_EMU_CONF_SDADC_IUT
    appCtx.appEmuCtx.confValue.sdadc_iut = 5;
            
    //APP_EMU_CONF_SDADC_FUT:     
    appCtx.appEmuCtx.confValue.sdadc_fut = 65;	
            
    //APP_EMU_CONF_SDADC_VLT
    appCtx.appEmuCtx.confValue.sdadc_vlt = 0;
            
    //APP_EMU_CONF_SDADC_ILT
    appCtx.appEmuCtx.confValue.sdadc_ilt = 0;
            
    //APP_EMU_CONF_SDADC_FLT:
    appCtx.appEmuCtx.confValue.sdadc_flt = 45;
            
    //APP_EMU_CONF_SDADC_VAC 
    appCtx.appEmuCtx.confValue.sdadc_vac = GSN_EMU_SDADC_CHANNEL_2;

    //APP_EMU_CONF_SDADC_IAC
    appCtx.appEmuCtx.confValue.sdadc_iac = GSN_EMU_SDADC_CHANNEL_1;

    //APP_EMU_CONF_SDADC_G0
    appCtx.appEmuCtx.confValue.gain_flag0 = FALSE;

    //APP_EMU_CONF_SDADC_G1
    appCtx.appEmuCtx.confValue.gain_flag1 = FALSE;
            
    //APP_EMU_CONF_SDADC_G2
    appCtx.appEmuCtx.confValue.gain_flag2 = FALSE;
	
    //APP_EMU_CONF_PL722X_SPI_CHANNEL
    appCtx.appEmuCtx.confValue.pl722x_spi_channel = 1;

    //APP_EMU_CONF_PL722X_SET_FREQ_MS     
    appCtx.appEmuCtx.confValue.pl722x_readFreq_ms = 4000;

	//APP_EMU_CONF_PL722X_CS_GPIO
	appCtx.appEmuCtx.confValue.pl722x_gpio_cs = 28;

    //APP_EMU_CONF_PL722X_RST_GPIO
	appCtx.appEmuCtx.confValue.pl722x_gpio_rst = 10;
	
}
/**
  ******************************************************************************
  *
  *****************************************************************************/
PUBLIC GSN_STATUS_T
AppEmu_DeInit (GSN_EMU_CTX_T *emuCtx)
{
    GSN_STATUS_T status = GSN_SUCCESS;
    GSN_EMU_STATUS_T emuStatus;
	
    /* De initialize emu module */
    emuStatus = GsnEmu_DeInit(emuCtx);

    /* Delete the task */
    GsnOsal_ThreadDelete(&(appCtx.appEmuCtx.appEmuTcb));
    
    if(GSN_EMU_STATUS_SUCCESS == emuStatus)
    {
        /* Update the status as success */
	 status = GSN_SUCCESS;
    }
    else
    {
        status = GSN_FAILURE;
    }  
    return (status);
}

/**
******************************************************************************
*
*****************************************************************************/
PRIVATE VOID
AppEmu_PrivateTask(UINT32 pArg)
{
  
    GSN_EMU_MSG_T msg;

   
    /* Handle events forever */
    while(TRUE)
    {     
        /* wait on message queue */
	GsnOsal_QueueGet(&(appCtx.appEmuCtx.appEmuMsgQue),(UINT8 *)(&msg),GSN_OSAL_WAIT_FOREVER);
             
        /* Process the message */
        GsnEmu_MsgProcess(&msg);
    }

}

/**
  ******************************************************************************
  *
  *****************************************************************************/
PRIVATE GSN_EMU_STATUS_T
AppEmu_TaskNotify (GSN_EMU_MSG_T *pMsg)
{
    GSN_EMU_STATUS_T status = GSN_EMU_STATUS_FAILURE;
	
    GSN_EMU_CTX_T *ctx;

    ctx = (GSN_EMU_CTX_T *)pMsg->ctx;
      
    /* If De-init is in progress, do not post message to queue */	
    /* Since de-init process will delete queue and thread */
    
    if (GSN_EMU_STATE_DEINITINPROGRESS != ctx->state) //protect task notify 
    {
        if (GSN_EMU_EVENT_DEINIT == pMsg->event)
        {
            ctx->state = GSN_EMU_STATE_DEINITINPROGRESS;
        }         
            
        /* Update message to message queue */
        GsnOsal_QueuePut(&(appCtx.appEmuCtx.appEmuMsgQue), (UINT8 *)pMsg);                    
        status = GSN_EMU_STATUS_SUCCESS;
    }

	return (status);
	
}
/**
  ******************************************************************************
  *
  *****************************************************************************/
PUBLIC VOID
AppEmu_Callback(UINT32 arg1, VOID *arg2)
{
    EMU_Printf("\r\n ARG1 = %d\r\n",arg1);
         
    if(GSN_EMU_STATUS_MSG_COMMUNICATION_FAILURE == arg1 )
    {
        EMU_Printf("\r\nCOMMUNICATION_FAILURE\r\n"); 
    }   
    else if( (GSN_EMU_STATUS_MSG_FREQ_UPPER_THRESHOLD_CROSSED)||
            (GSN_EMU_STATUS_MSG_FREQ_LOWER_THRESHOLD_CROSSED) == arg1)
    {
        EMU_Printf("\r\nFREQUENCY THRESHOLD\r\n");
    }
    else if( (GSN_EMU_STATUS_MSG_VOLTAGE_UPPER_THRESHOLD_CROSSED)||
            (GSN_EMU_STATUS_MSG_VOLTAGE_LOWER_THRESHOLD_CROSSED) == arg1)
    {
        EMU_Printf("\r\nVOLTAGE THRESHOLD\r\n");
    }
    else if( (GSN_EMU_STATUS_MSG_CURRENT_UPPER_THRESHOLD_CROSSED)||
            (GSN_EMU_STATUS_MSG_CURRENT_LOWER_THRESHOLD_CROSSED) == arg1)
    {
        EMU_Printf("\r\nCURRENT THRESHOLD\r\n");
    }
    else if (GSN_EMU_STATUS_MSG_REQUESTINPROGRESS == arg1 )
    {
        EMU_Printf("\r\n REQUEST IN PROGRESS \r\n");
    }
}                         

/**
  ******************************************************************************
  *
  *****************************************************************************/

PUBLIC GSN_EMU_STATUS_T
AppEmu_BuffAllocate(VOID)
{
    GSN_EMU_STATUS_T status = GSN_EMU_STATUS_FAILURE; 
   
    /*check whether to allocate buffers statically or dymnamically*/

#ifdef S2W_EMU_STATIC 
    
    appCtx.appEmuCtx.appEmuSdadcPbuf1 = appCtx.appEmuCtx.appEmuSdadcBuf1;
    appCtx.appEmuCtx.appEmuSdadcPbuf2 = appCtx.appEmuCtx.appEmuSdadcBuf2;
    appCtx.appEmuCtx.appEmuSdadcPbuf3 = appCtx.appEmuCtx.appEmuSdadcBuf3;
    appCtx.appEmuCtx.appEmuSdadcPbuf4 = appCtx.appEmuCtx.appEmuSdadcBuf4;
    
    status = GSN_EMU_STATUS_SUCCESS;  
    return status;
    
#else   
    
    if(NULL ==(appCtx.appEmuCtx.appEmuSdadcPbuf1 = MALLOC(APP_EMU_SDADC_BUF_SIZE)))
    {
        goto buffAllocateExit1;
    }
    if(NULL == (appCtx.appEmuCtx.appEmuSdadcPbuf2 = MALLOC(APP_EMU_SDADC_BUF_SIZE)))
    {
        goto buffAllocateExit2;
    }
    if(NULL == (appCtx.appEmuCtx.appEmuSdadcPbuf3 = MALLOC(APP_EMU_SDADC_BUF_SIZE)))
    { 
        goto buffAllocateExit3;
    }
    if(NULL == (appCtx.appEmuCtx.appEmuSdadcPbuf4 = MALLOC(APP_EMU_SDADC_BUF_SIZE)))
    {
       goto buffAllocateExit4;
    }
    else
    {
        EMU_Printf("\r\nAllocate SUCCESS \r\n");
        status = GSN_EMU_STATUS_SUCCESS;
    }
    
    return status; 
  
buffAllocateExit4:  
  FREE(appCtx.appEmuCtx.appEmuSdadcPbuf3);
buffAllocateExit3:
  FREE(appCtx.appEmuCtx.appEmuSdadcPbuf2);
buffAllocateExit2:
  FREE(appCtx.appEmuCtx.appEmuSdadcPbuf1);
buffAllocateExit1:
   return status;
  
#endif
	
}

/**
  ******************************************************************************
  *
  *****************************************************************************/
PUBLIC GSN_EMU_STATUS_T
AppEmu_BuffDeallocate(VOID)
{
  GSN_EMU_STATUS_T status = GSN_EMU_STATUS_FAILURE;
#ifndef S2W_EMU_STATIC      
    if((appCtx.appEmuCtx.appEmuSdadcPbuf1 != NULL)&&
       (appCtx.appEmuCtx.appEmuSdadcPbuf2 != NULL)&&
       (appCtx.appEmuCtx.appEmuSdadcPbuf3 != NULL)&&
        (appCtx.appEmuCtx.appEmuSdadcPbuf4 != NULL))
       
    {
        EMU_Printf("\r\nAppEmu_BuffDeallocate\r\n");
        /*clear the buffers allocated for SDADC */
        FREE(appCtx.appEmuCtx.appEmuSdadcPbuf1);
        FREE(appCtx.appEmuCtx.appEmuSdadcPbuf2);
        FREE(appCtx.appEmuCtx.appEmuSdadcPbuf3);
        FREE(appCtx.appEmuCtx.appEmuSdadcPbuf4);
        appCtx.appEmuCtx.appEmuSdadcPbuf1=appCtx.appEmuCtx.appEmuSdadcPbuf2=
        appCtx.appEmuCtx.appEmuSdadcPbuf3=appCtx.appEmuCtx.appEmuSdadcPbuf4=NULL;
        status = GSN_EMU_STATUS_SUCCESS;
    }
    return status;
#else
    
    status = GSN_EMU_STATUS_SUCCESS;
    return status;
#endif /*static flag*/  
    
    
}
#endif /*S2W_EMU*/
