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
* $RCSfile: gsn_dma_fpt.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/

#ifndef _GSN_DMA_FTP_H_
#define _GSN_DMA_FTP_H_
/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "drivers/clk_ctl/gsn_clk_ctl.h"
#include "gsn_includes.h"
#include "drivers/dma/gsn_dma.h"



/*****************************************************************************
  *  Definitions
  ****************************************************************************/


typedef GSN_OSAL_ERROR_T
( *GsnDma_Open_FP_T) (GSN_DMA_T* ptGsnDma,
                       GSN_DMACONFIG_T *ptConfig,
                       UINT32 channelsToConfigure);
extern _RPST_ GsnDma_Open_FP_T GsnDma_Open_FP;


typedef GSN_OSAL_ERROR_T
( *GsnDma_IndividualClose_FP_T) (GSN_DMA_T* ptGsnDma,UINT32 channelsToClose);
extern _RPST_ GsnDma_IndividualClose_FP_T GsnDma_IndividualClose_FP;

typedef GSN_OSAL_ERROR_T
( *GsnDma_Close_FP_T) (GSN_DMA_T* ptGsnDma);
extern _RPST_ GsnDma_Close_FP_T GsnDma_Close_FP;


typedef VOID
( *GsnDma_ChannelPriAltSet_FP_T) (GSN_DMA_T* ptGsnDma,UINT32 channelsToConfigure);
extern _RPST_ GsnDma_ChannelPriAltSet_FP_T GsnDma_ChannelPriAltSet_FP;


typedef VOID
( *GsnDma_ChannelPriAltClear_FP_T) (GSN_DMA_T* ptGsnDma,UINT32 channelsToConfigure);
extern _RPST_ GsnDma_ChannelPriAltClear_FP_T GsnDma_ChannelPriAltClear_FP;


typedef BOOL
( *GsnDma_ChannelIDValid_FP_T)(UINT8 ulChannelID);
extern _RPST_ GsnDma_ChannelIDValid_FP_T GsnDma_ChannelIDValid_FP;


typedef VOID
 ( *GsnDma_Enable_FP_T)(GSN_DMA_T* ptGsnDma);
 extern _RPST_ GsnDma_Enable_FP_T GsnDma_Enable_FP;


typedef VOID
( *GsnDma_Disable_FP_T)(GSN_DMA_T* ptGsnDma);
 extern _RPST_ GsnDma_Disable_FP_T GsnDma_Disable_FP;


typedef UINT32
( *GsnDma_StatusGet_FP_T)(GSN_DMA_T* ptGsnDma);
extern _RPST_ GsnDma_StatusGet_FP_T GsnDma_StatusGet_FP;


typedef VOID
( *GsnDma_ChannelEnable_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
extern _RPST_ GsnDma_ChannelEnable_FP_T GsnDma_ChannelEnable_FP;


typedef VOID
( *GsnDma_ChannelDisable_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
extern _RPST_ GsnDma_ChannelDisable_FP_T GsnDma_ChannelDisable_FP;


typedef VOID
( *GsnDma_ChannelSoftwareRequest_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
extern _RPST_ GsnDma_ChannelSoftwareRequest_FP_T GsnDma_ChannelSoftwareRequest_FP;


typedef VOID
( *GsnDma_CycleControl_FP_T)(GSN_DMA_T* ptGsnDma,GSN_DMA_CHANNEL_CONFIG_T *ptChannelConfig,
UINT8 ulChannelID,UINT32 noOfBytesToTransfer,VOID *pvSrcAddr,VOID *pvDstAddr);
extern _RPST_ GsnDma_CycleControl_FP_T GsnDma_CycleControl_FP;



typedef VOID
( *GsnDma_CallBackRegister_FP_T)(GSN_DMA_T* ptGsnDma,DMACALLBACK_FP ptCallBackFunc,
                                                    VOID *ctx ,UINT32 channelID);
extern _RPST_ GsnDma_CallBackRegister_FP_T GsnDma_CallBackRegister_FP;

typedef VOID
( *GsnDma_ChannelControlSetPrimary_FP_T)(GSN_DMA_T* ptGsnDma,
                                             UINT32 ulControl,UINT8 ulChannelID);
extern _RPST_ GsnDma_ChannelControlSetPrimary_FP_T GsnDma_ChannelControlSetPrimary_FP;

typedef VOID
( *GsnDma_ChannelControlSetAlternate_FP_T)(GSN_DMA_T* ptGsnDma,
                                             UINT32 ulControl,UINT8 ulChannelID);
extern _RPST_ GsnDma_ChannelControlSetAlternate_FP_T   GsnDma_ChannelControlSetAlternate_FP ;

typedef UINT32
( *GsnDma_ChannelControlGetPrimary_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
  extern _RPST_ GsnDma_ChannelControlGetPrimary_FP_T GsnDma_ChannelControlGetPrimary_FP;


typedef UINT32
( *GsnDma_ChannelControlGetAlternate_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
extern _RPST_ GsnDma_ChannelControlGetAlternate_FP_T GsnDma_ChannelControlGetAlternate_FP;

typedef VOID
( *GsnDma_ChannelTransferSetPrimary_FP_T)(GSN_DMA_T* ptGsnDma, VOID *pvSrcAddr,
                       VOID *pvDstAddr,UINT8 ulChannelID);
extern _RPST_ GsnDma_ChannelTransferSetPrimary_FP_T GsnDma_ChannelTransferSetPrimary_FP;

typedef VOID
(* GsnDma_ChannelTransferSetAlternate_FP_T)(GSN_DMA_T* ptGsnDma, VOID *pvSrcAddr,
                       VOID *pvDstAddr,UINT8 ulChannelID);
extern _RPST_ GsnDma_ChannelTransferSetAlternate_FP_T GsnDma_ChannelTransferSetAlternate_FP;

typedef UINT32
( *GsnDma_CurrentSourceAddrGet_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannel);
extern _RPST_ GsnDma_CurrentSourceAddrGet_FP_T GsnDma_CurrentSourceAddrGet_FP;

typedef UINT32
( *GsnDma_CurrentDestAddrGet_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
extern _RPST_ GsnDma_CurrentDestAddrGet_FP_T GsnDma_CurrentDestAddrGet_FP;

typedef  UINT32
( *GsnDma_CurrentDestAddrGetPrimary_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
extern _RPST_ GsnDma_CurrentDestAddrGetPrimary_FP_T GsnDma_CurrentDestAddrGetPrimary_FP;

typedef  UINT32
( *GsnDma_RemainTransferCountGet_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
extern _RPST_ GsnDma_RemainTransferCountGet_FP_T GsnDma_RemainTransferCountGet_FP;

typedef  UINT32
( *GsnDma_RemainTransferCountGetPrimary_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
extern _RPST_ GsnDma_RemainTransferCountGetPrimary_FP_T GsnDma_RemainTransferCountGetPrimary_FP;

typedef UINT32
( *GsnDma_CycleTypeGetPrimary_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
extern _RPST_ GsnDma_CycleTypeGetPrimary_FP_T GsnDma_CycleTypeGetPrimary_FP;

typedef UINT32
( *GsnDma_CycleTypeGetAlternate_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
extern _RPST_ GsnDma_CycleTypeGetAlternate_FP_T GsnDma_CycleTypeGetAlternate_FP;

typedef  UINT32
( *GsnDma_RemainTransferCountGetAlternate_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
extern _RPST_ GsnDma_RemainTransferCountGetAlternate_FP_T GsnDma_RemainTransferCountGetAlternate_FP;

typedef UINT32
( *GsnDma_specificChannelAddressPrimary_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
extern _RPST_ GsnDma_specificChannelAddressPrimary_FP_T GsnDma_specificChannelAddressPrimary_FP;

typedef UINT32
( *GsnDma_specificChannelAddressAlternate_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
extern _RPST_ GsnDma_specificChannelAddressAlternate_FP_T GsnDma_specificChannelAddressAlternate_FP;

typedef  PUBLIC VOID
( *__GsnDma_Ch0Done_Isr_FP_T)();
extern _RPST_ __GsnDma_Ch0Done_Isr_FP_T __GsnDma_Ch0Done_Isr_FP;

typedef PUBLIC VOID
( *__GsnDma_Ch1Done_Isr_FP_T)();
extern _RPST_ __GsnDma_Ch1Done_Isr_FP_T __GsnDma_Ch1Done_Isr_FP;

typedef PUBLIC VOID
(*__GsnDma_Uart0RxDone_Isr_FP_T )();
extern _RPST_ __GsnDma_Uart0RxDone_Isr_FP_T  __GsnDma_Uart0RxDone_Isr_FP;

typedef PUBLIC VOID
( *__GsnDma_Uart0TxDone_Isr_FP_T)();
extern _RPST_ __GsnDma_Uart0TxDone_Isr_FP_T __GsnDma_Uart0TxDone_Isr_FP;

typedef PUBLIC VOID
( *__GsnDma_Ssp1RxDone_Isr_FP_T)();
extern _RPST_ __GsnDma_Ssp1RxDone_Isr_FP_T __GsnDma_Ssp1RxDone_Isr_FP;

typedef PUBLIC VOID
( *__GsnDma_Ssp1TxDone_Isr_FP_T )();
extern _RPST_ __GsnDma_Ssp1TxDone_Isr_FP_T __GsnDma_Ssp1TxDone_Isr_FP;

typedef PUBLIC VOID
( *__GsnDma_Uart1RxDone_Isr_FP_T)();
extern _RPST_ __GsnDma_Uart1RxDone_Isr_FP_T __GsnDma_Uart1RxDone_Isr_FP;

typedef PUBLIC VOID
( *__GsnDma_Uart1TxDone_Isr_FP_T)();
extern _RPST_ __GsnDma_Uart1TxDone_Isr_FP_T __GsnDma_Uart1TxDone_Isr_FP;

typedef PUBLIC VOID
( *__GsnDma_Ssp0RxDone_Isr_FP_T)();
extern _RPST_ __GsnDma_Ssp0RxDone_Isr_FP_T __GsnDma_Ssp0RxDone_Isr_FP;

typedef PUBLIC VOID
( *__GsnDma_Ssp0TxDone_Isr_FP_T)();
extern _RPST_ __GsnDma_Ssp0TxDone_Isr_FP_T __GsnDma_Ssp0TxDone_Isr_FP;

typedef PUBLIC VOID
( *__GsnDma_Error_Isr_FP_T)();
extern _RPST_ __GsnDma_Error_Isr_FP_T __GsnDma_Error_Isr_FP;

#if 0
typedef GSN_OSAL_ERROR_T
( *GsnDma_IndividualClose_FP_T) (GSN_DMA_T* ptGsnDma,UINT32 channelsToClose);

extern _RPST_ GsnDma_IndividualClose_FP_T GsnDma_IndividualClose_FP;


typedef VOID
( *GsnDma_ChannelPriAltSet_FP_T) (GSN_DMA_T* ptGsnDma,UINT32 channelsToConfigure);

extern _RPST_ GsnDma_ChannelPriAltSet_FP_T GsnDma_ChannelPriAltSet_FP;

typedef VOID
( *GsnDma_ChannelPriAltClear_FP_T) (GSN_DMA_T* ptGsnDma,UINT32 channelsToConfigure);

extern _RPST_ GsnDma_ChannelPriAltClear_FP_T GsnDma_ChannelPriAltClear_FP;

typedef UINT32
( *GsnDma_CurrentDestAddrGetPrimary_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

extern _RPST_ GsnDma_CurrentDestAddrGetPrimary_FP_T GsnDma_CurrentDestAddrGetPrimary_FP;


typedef UINT32
( *GsnDma_RemainTransferCountGetPrimary_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

extern _RPST_ GsnDma_RemainTransferCountGetPrimary_FP_T GsnDma_RemainTransferCountGetPrimary_FP;

typedef UINT32
( *GsnDma_RemainTransferCountGetAlternate_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

extern _RPST_ GsnDma_RemainTransferCountGetAlternate_FP_T GsnDma_RemainTransferCountGetAlternate_FP;

typedef UINT32
( *GsnDma_CycleTypeGetAlternate_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

extern _RPST_ GsnDma_CycleTypeGetAlternate_FP_T GsnDma_CycleTypeGetAlternate_FP;

typedef  UINT32
( *GsnDma_CycleTypeGetPrimary_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

extern _RPST_  GsnDma_CycleTypeGetPrimary_FP_T GsnDma_CycleTypeGetPrimary_FP;

typedef UINT32
( *GsnDma_specificChannelAddressPrimary_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);

extern _RPST_ GsnDma_specificChannelAddressPrimary_FP_T GsnDma_specificChannelAddressPrimary_FP;

typedef UINT32
( *GsnDma_specificChannelAddressAlternate_FP_T)(GSN_DMA_T* ptGsnDma,UINT8 ulChannelID);
extern _RPST_ GsnDma_specificChannelAddressAlternate_FP_T GsnDma_specificChannelAddressAlternate_FP;


#endif
#endif