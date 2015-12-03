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
* $RCSfile: gsn_clk_ctl_fpt.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/

#ifndef _GSN_CLK_CTL_FTP_H_
#define _GSN_CLK_CTL_FTP_H_
/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "drivers/clk_ctl/gsn_clk_ctl.h"




/*****************************************************************************
  *  Definitions
  ****************************************************************************/
typedef GSN_STATUS_T 
(* GsnClkCtl_ClkStableCheck_FP_T)(GSN_CLK_CTL_CTX_T *pClkCtlCtx, 
                                    GSN_CLK_CTL_CLK_SRC_T src);
extern _RPST_   GsnClkCtl_ClkStableCheck_FP_T GsnClkCtl_ClkStableCheck_FP;

typedef VOID 
(* GsnClkCtl_Init_FP_T)(GSN_CLK_CTL_CTX_T *pClkCtlCtx);
extern _RPST_   GsnClkCtl_Init_FP_T GsnClkCtl_Init_FP;

typedef GSN_STATUS_T 
(* GsnClkCtl_ClkSrcEnable_FP_T)(GSN_CLK_CTL_CTX_T *pClkCtlCtx, 
                                  GSN_CLK_CTL_CLK_SRC_T src);
extern _RPST_   GsnClkCtl_ClkSrcEnable_FP_T GsnClkCtl_ClkSrcEnable_FP;

typedef GSN_STATUS_T 
(* GsnClkCtl_ClkSrcDisable_FP_T)(GSN_CLK_CTL_CTX_T *pClkCtlCtx, 
                                   GSN_CLK_CTL_CLK_SRC_T src);
extern _RPST_   GsnClkCtl_ClkSrcDisable_FP_T GsnClkCtl_ClkSrcDisable_FP;

typedef GSN_STATUS_T 
(* GsnClkCtl_Cm3ClkCfg_FP_T)(GSN_CLK_CTL_CM3_CLK_CFG_T *pCm3ClkCfg);
extern _RPST_   GsnClkCtl_Cm3ClkCfg_FP_T GsnClkCtl_Cm3ClkCfg_FP;

typedef GSN_STATUS_T 
(* GsnClkCtl_Cm3ClkSwitch_FP_T)(GSN_CLK_CTL_CM3_CLK_CFG_T *pCm3ClkCfg, 
                                  GSN_CLK_SEL_T newClk);
extern _RPST_   GsnClkCtl_Cm3ClkSwitch_FP_T GsnClkCtl_Cm3ClkSwitch_FP;


typedef VOID 
(* __GsnClockStable_Isr_FP_T)(VOID);
extern _RPST_   __GsnClockStable_Isr_FP_T __GsnClockStable_Isr_FP;

typedef VOID
( *GsnClkCtl_HsRcCal_FP_T)(GSN_CLK_CTL_CM3_CLK_CFG_T *pCm3ClkCfg);
extern _RPST_ GsnClkCtl_HsRcCal_FP_T GsnClkCtl_HsRcCal_FP;

#endif
