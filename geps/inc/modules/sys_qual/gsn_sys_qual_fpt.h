/******************************************************************************
*
*               COPYRIGHT (c) 2006-2010 GainSpan Corporation
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
* $RCSfile: gsn_sys_qual_fpt.h,v $
*
* Description : Main module
*****************************************************************************/

/****************************************************************************
  * File Inclusions
  ****************************************************************************/
#ifndef _GSN_SYS_QUAL_FPT_H_

#define _GSN_SYS_QUAL_FPT_H_

typedef VOID
(*GsnSq_Init_FP_T)(VOID);

extern _RPST_ GsnSq_Init_FP_T GsnSq_Init_FP;

typedef VOID
(*GsnSq_TaskMonitorRegister_FP_T)(UINT32 taskId,GSN_OSAL_THREAD_TCB_T * thread, UINT32 monitorTime);

extern _RPST_ GsnSq_TaskMonitorRegister_FP_T GsnSq_TaskMonitorRegister_FP;

typedef VOID
(*GsnSq_TaskMonitorDeregister_FP_T)(UINT32 taskId);

extern _RPST_ GsnSq_TaskMonitorDeregister_FP_T GsnSq_TaskMonitorDeregister_FP;

typedef VOID
(*GsnSq_TaskMonitorStart_FP_T)(UINT32 taskId, INT32 data);

extern _RPST_ GsnSq_TaskMonitorStart_FP_T GsnSq_TaskMonitorStart_FP;

typedef VOID
(*GsnSq_TaskMonitorEnd_FP_T)(UINT32 taskId);

extern _RPST_ GsnSq_TaskMonitorEnd_FP_T GsnSq_TaskMonitorEnd_FP;

typedef VOID
(*GsnSq_WdTmrStart_FP_T) (VOID);
extern _RPST_ GsnSq_WdTmrStart_FP_T GsnSq_WdTmrStart_FP;


typedef VOID
(*GsnSq_AssertHandler_FP_T)(UINT8 level);
extern _RPST_ GsnSq_AssertHandler_FP_T GsnSq_AssertHandler_FP;
#endif