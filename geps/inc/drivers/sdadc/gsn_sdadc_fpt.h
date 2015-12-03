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
* $RCSfile: gsn_sdadc_fpt.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/
#ifndef _GSN_SDADC_FPT_H_
#define _GSN_SDADC_FPT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_includes.h"





/*****************************************************************************
  *  Definitions
****************************************************************************/


typedef PUBLIC GSN_STATUS
(* GsnSdadc_Open_FP_T )(GSN_SDADC_HANDLE_T *sdadcHandle,
             GSN_SDADC_CONFIG_T *sdadcConfig);

extern _RPST_ GsnSdadc_Open_FP_T GsnSdadc_Open_FP;

typedef PUBLIC GSN_STATUS
(* GsnSdadc_Close_FP_T)(GSN_SDADC_HANDLE_T *sdadcHandle );

extern _RPST_ GsnSdadc_Close_FP_T GsnSdadc_Close_FP;


typedef PUBLIC GSN_STATUS
(* GsnSdadc_Read_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle,
             GSN_SDADC_RW_ARGS_T *sdadcRW );

extern _RPST_ GsnSdadc_Read_FP_T GsnSdadc_Read_FP;


typedef PUBLIC GSN_STATUS
(* GsnSdadc_ContinousRead_FP_T)(GSN_SDADC_HANDLE_T *sdadcHandle, 
                          GSN_SDADC_RW_ARGS_T *sdadcRW);

extern _RPST_ GsnSdadc_ContinousRead_FP_T GsnSdadc_ContinousRead_FP;

typedef PUBLIC GSN_STATUS
(* GsnSdadc_DacWrite_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle,
                 GSN_SDADC_RW_ARGS_T *sdadcRW );

extern _RPST_ GsnSdadc_DacWrite_FP_T GsnSdadc_DacWrite_FP;


typedef PUBLIC VOID
(* GsnSdadc_StopRead_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle);

extern _RPST_ GsnSdadc_StopRead_FP_T GsnSdadc_StopRead_FP;


typedef PUBLIC GSN_STATUS 
(* GsnSdadc_ChannelSet_FP_T)(GSN_SDADC_HANDLE_T *sdadcHandle,  GSN_SDADCDAC_CHANNEL_T channel);

extern _RPST_ GsnSdadc_ChannelSet_FP_T GsnSdadc_ChannelSet_FP;


typedef PUBLIC VOID
(* GsnSdadc_SupIndicationSet_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle, GSN_ADC_ENAVDD_T avdd);

extern _RPST_ GsnSdadc_SupIndicationSet_FP_T GsnSdadc_SupIndicationSet_FP;



typedef PUBLIC VOID
(* GsnSdadc_EnADC_FIFO_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle, GSN_SDADC_ADC_FIFO_CNTRL_T
                                                          enSdadcFifo );

extern _RPST_ GsnSdadc_EnADC_FIFO_FP_T GsnSdadc_EnADC_FIFO_FP;


typedef PUBLIC VOID
(* GsnSdadc_EnDAC_FIFO_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle, GSN_SDADC_DAC_FIFO_CNTRL_T
                                                        enSddacFifo );

extern _RPST_ GsnSdadc_EnDAC_FIFO_FP_T GsnSdadc_EnDAC_FIFO_FP;


typedef PUBLIC VOID
(* GsnSdadc_AdcWatermarkSet_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle, UINT8 adcWmark);


extern _RPST_ GsnSdadc_AdcWatermarkSet_FP_T GsnSdadc_AdcWatermarkSet_FP;

typedef PUBLIC VOID
(* GsnSdadc_DacWatermarkSet_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle, UINT8 dacWmark);

extern _RPST_ GsnSdadc_DacWatermarkSet_FP_T GsnSdadc_DacWatermarkSet_FP;


typedef PUBLIC VOID
(* GsnSdadc_PhaseStepSet_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle, UINT8 phaseStep );

extern _RPST_ GsnSdadc_PhaseStepSet_FP_T GsnSdadc_PhaseStepSet_FP;


typedef PUBLIC VOID
(* GsnSdadc_RefSet_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle, UINT8 ref );

extern _RPST_ GsnSdadc_RefSet_FP_T GsnSdadc_RefSet_FP;


typedef PUBLIC VOID
(* GsnSdadc_Gain0Set_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle, UINT8 gain0 );

extern _RPST_ GsnSdadc_Gain0Set_FP_T GsnSdadc_Gain0Set_FP;

typedef PUBLIC VOID
(* GsnSdadc_Gain1Set_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle, UINT8 gain1 );

extern _RPST_ GsnSdadc_Gain1Set_FP_T GsnSdadc_Gain1Set_FP;

typedef PUBLIC VOID
(* GsnSdadc_Gain2Set_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle, UINT8 gain2 );

extern _RPST_ GsnSdadc_Gain2Set_FP_T GsnSdadc_Gain2Set_FP;


typedef PUBLIC GSN_STATUS
(* GsnSdadc_Sel0_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle,  GSN_SDADC_SEL0_T sel0);

extern _RPST_ GsnSdadc_Sel0_FP_T GsnSdadc_Sel0_FP;


typedef PUBLIC GSN_STATUS
(* GsnSdadc_Sel1_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle,  GSN_SDADC_SEL1_T sel1);

extern _RPST_ GsnSdadc_Sel1_FP_T GsnSdadc_Sel1_FP;


typedef PUBLIC GSN_STATUS
(* GsnSdadc_Sel2_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle,  GSN_SDADC_SEL2_T sel2);

extern _RPST_ GsnSdadc_Sel2_FP_T GsnSdadc_Sel2_FP;


typedef PUBLIC GSN_STATUS
(* GsnSdadc_Bias_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle,  UINT8 bias);

extern _RPST_ GsnSdadc_Bias_FP_T GsnSdadc_Bias_FP;


typedef PUBLIC GSN_STATUS
(* GsnSdadc_Phase1set_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle,  UINT8 phase1);

extern _RPST_ GsnSdadc_Phase1set_FP_T GsnSdadc_Phase1set_FP;


typedef PUBLIC GSN_STATUS
(* GsnSdadc_Phase2set_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle,  UINT8 phase2);

extern _RPST_ GsnSdadc_Phase2set_FP_T GsnSdadc_Phase2set_FP;


typedef PUBLIC GSN_STATUS
(* GsnSdadc_SdadcStepSet_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle );

extern _RPST_ GsnSdadc_SdadcStepSet_FP_T GsnSdadc_SdadcStepSet_FP;


typedef PUBLIC VOID
(* GsnSdadc_EnableA3v_FP_T)( GSN_SDADC_HANDLE_T *sdadcHandle, GSN_SDADC_ENA3V_T a3v );

extern _RPST_ GsnSdadc_EnableA3v_FP_T GsnSdadc_EnableA3v_FP;


typedef PUBLIC VOID
(* Gsn_Sdadc_TempcoSet_FP_T)(GSN_SDADC_HANDLE_T *sdadcHandle ,UINT8 tempco);

extern _RPST_ Gsn_Sdadc_TempcoSet_FP_T Gsn_Sdadc_TempcoSet_FP;


typedef PUBLIC VOID
(* __sdadcdacFifoUndrWtrMarkIsr_FP_T)();

extern _RPST_ __sdadcdacFifoUndrWtrMarkIsr_FP_T __sdadcdacFifoUndrWtrMarkIsr_FP;


typedef PUBLIC VOID
(* __sdadcdacFifoOvrWtrMarkIsr_FP_T)();

extern _RPST_ __sdadcdacFifoOvrWtrMarkIsr_FP_T __sdadcdacFifoOvrWtrMarkIsr_FP;

typedef PUBLIC VOID
(* GsnSdadc_SdadcIsr_FP_T)(GSN_SDADC_HANDLE_T *sdadcHandle);

extern _RPST_ GsnSdadc_SdadcIsr_FP_T GsnSdadc_SdadcIsr_FP;

typedef PUBLIC VOID
(* GsnSdadc_DacIsr_FP_T)(GSN_SDADC_HANDLE_T *sdadcHandle);

extern _RPST_ GsnSdadc_DacIsr_FP_T GsnSdadc_DacIsr_FP;




#ifdef __cplusplus
}
#endif

#endif /* _GSN_SDADC_FPT_H_ */


