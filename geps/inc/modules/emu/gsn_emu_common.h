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
* $RCSfile: gsn_emu_common.h,v $
*
* Description : 
*******************************************************************************/
#ifndef _GSN_EMUCOMMON_H_
#define _GSN_EMUCOMMON_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include "gsn_includes.h"
//#include "emu\gsn_sdadc.h"
  
/*
* Status
*/
typedef enum GSN_EMU_STATUS
{
    GSN_EMU_STATUS_FAILURE = 0,
    GSN_EMU_STATUS_SUCCESS,

}GSN_EMU_STATUS_T;


/*
* Error message
*/
typedef enum GSN_EMU_STATUS_MSG
{
    GSN_EMU_STATUS_MSG_COMMUNICATION_FAILURE = 1,
	
    GSN_EMU_STATUS_MSG_VOLTAGE_UPPER_THRESHOLD_CROSSED = 2,
    GSN_EMU_STATUS_MSG_VOLTAGE_LOWER_THRESHOLD_CROSSED = 4,
	
    GSN_EMU_STATUS_MSG_CURRENT_UPPER_THRESHOLD_CROSSED = 8,
    GSN_EMU_STATUS_MSG_CURRENT_LOWER_THRESHOLD_CROSSED = 16,
	
    GSN_EMU_STATUS_MSG_FREQ_UPPER_THRESHOLD_CROSSED = 32,
    GSN_EMU_STATUS_MSG_FREQ_LOWER_THRESHOLD_CROSSED = 64,

    GSN_EMU_STATUS_MSG_REQUESTINPROGRESS = 128, 
    GSN_EMU_STATUS_MSG_REQUESTCOMPLETED = 256,

	GSN_EMU_STATUS_MSG_COMPUTATION_FAILURE = 512,

}GSN_EMU_STATUS_MSG_T;

/*
* EMU Events
*/
typedef enum GSN_EMU_EVENTS
{
    GSN_EMU_EVENT_START ,
    GSN_EMU_EVENT_STOP,
    GSN_EMU_EVENT_PAUSE,
    GSN_EMU_EVENT_RESUME,
    GSN_EMU_EVENT_DEINIT,
    GSN_EMU_EVENT_LOADCONTROL,
    GSN_EMU_EVENT_RESETENERGY,
    GSN_EMU_EVENT_COMPUTE_ELECPARAMS,
    GSN_EMU_EVENT_GETINSTANTVALUES,
    GSN_EMU_EVENT_GETSTATE,
    GSN_EMU_EVENT_GETMODE,
    GSN_EMU_EVENT_GETELECPARAMS,
    GSN_EMU_EVENT_GETLOADSTATUS,
    
}GSN_EMU_EVENTS_T;


/**
* EMU PL722x context
*/
typedef struct GSN_EMU_PL722X_CTX
{
    /* Timer pointer */
    GSN_SOFT_TMR_T timer;
    UINT32 csGpio;
    UINT32 rstGpio;
    UINT8 spiChannel;

}GSN_EMU_PL722X_CTX_T;


typedef struct GSN_EMU_SDADC_PINGPONG_BUFF
{
    UINT16 *vPriBuff;
    UINT16 *iPriBuff;
    UINT16 *vSecBuff;
    UINT16 *iSecBuff;
    UINT32 size;
}GSN_EMU_SDADC_PINGPONG_BUFF_T;

/**
* EMU SD-ADC context
*/
typedef struct GSN_EMU_SDADC_CTX
{
    /* Flag which says whether values has to be discarded */
    /* immidielty after starting the ADC or not */
    BOOL discardSamples;
	
    /* How many samples has to be discarded */
    UINT32 discardsampleCnt;
	
    /* Ping-pong primary and secondary buffer pointers */
    GSN_EMU_SDADC_PINGPONG_BUFF_T pingPongBuff;
	
    /* Variable which decides the buffer (primary or secondary) */
    /* to be processed */
    UINT8 pingPongState;
	
    /* ADC handle */
    /* This holds the configuration and rw arguments too */
    GSN_SDADC_HANDLE_T	handle;
	
    /* Parameters for computation */
    float  g_freq_actual ;
    UINT8  g_zcrossing;
    LONG64 g_freq_val;
    UINT16 g_cycles;
    UINT16 g_Power_Factor;
    LONG64 g_freq_total;
    LONG64 g_Vi;
    LONG64 g_Ii;
    LONG64 g_Samples;
    LONG64 g_Vn_In;
    LONG64 g_Avg_Power;
    LONG64 g_Energy;
    LONG64 g_Raw_Energy;
    float g_Vrms;
    float g_Irms;
    float g_App_Power;
        
}GSN_EMU_SDADC_CTX_T;


/**
* Element strcuture in message queue
*/
typedef struct GSN_EMU_MSG
{
    /* Event */
    UINT32 event;
	
    /* Semaphore */
    VOID *sem;

    /* input argument */
    VOID *arg;

    /* status */
    VOID *status;

    /* EMU context */
    VOID *ctx;
	
}GSN_EMU_MSG_T;


typedef GSN_EMU_STATUS_T (* GSN_EMU_TASKNOTIFICATION_FUNC_T)(GSN_EMU_MSG_T *msg);
typedef GSN_EMU_STATUS_T  (* GSN_EMU_MODULE_FN_PTR_START)(VOID* arg1, VOID *arg2);
typedef GSN_EMU_STATUS_T (* GSN_EMU_MODULE_FN_PTR_STOP)(VOID* arg1, VOID *arg2);
typedef GSN_EMU_STATUS_T (* GSN_EMU_MODULE_FN_PTR_LOADCONTROL)(BOOL onOff, VOID *arg1, VOID *arg2);
typedef GSN_EMU_STATUS_T (* GSN_EMU_MODULE_FN_PTR_RESETENERGY)(VOID *arg1, VOID *arg2);
typedef GSN_EMU_STATUS_T (* GSN_EMU_MODULE_FN_PTR_COMPUTEELECPARAMS)(VOID *arg1, VOID *arg2, VOID *arg3);
typedef GSN_EMU_STATUS_T (* GSN_EMU_MODULE_FN_PTR_GETINSTANTVALUES)(VOID *arg1, VOID *arg2, VOID *arg3);
VOID
GsnEmu_TimerCb( VOID* context, GSN_SOFT_TMR_HANDLE_T timerHandle );

#ifdef  __cplusplus
}
#endif

#endif //_GSN_EMUCOMMON_H_


