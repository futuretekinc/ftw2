/******************************************************************************
*
*               COPYRIGHT (c) 2012-2014 GainSpan Corporation
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
* $RCSfile: gsn_hi_mb.h,v $
*
* Description : This file contains the HI MB definitions.
*****************************************************************************/
#ifndef _GSN_HI_MB_H_
#define _GSN_HI_MB_H_
#ifdef __cplusplus
extern "C" {
#endif
    
/*****************************************************************************
* File Inclusion
*****************************************************************************/
/**
 *****************************************************************************
 * @file gsn_mb.h
 * @brief GSN mailbox public header.
 *    This file contains the public APIs and structures of mailbox driver module.
 *****************************************************************************/
/**
 *****************************************************************************
 * @ingroup coresvcdoc
 * @{
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup GsnMb GSN MB API.
 *    This group of APIs implements the mailbox driver features. 
*****************************************************************************/
/**
*****************************************************************************
* @}	END of coresvcdoc.
*****************************************************************************/

#define GSN_HI_MB_MSG_SB 0      /* MSG send box is SB#1 */
#define GSN_HI_MB_ACK_SB 1      /* ACK send box is SB#0 */

#define GSN_HI_MB_MSG_RB 1      /* MSG rcv box is RB#0 */
#define GSN_HI_MB_ACK_RB 0      /* ACK rcv box is RB#1 */
#define GSN_HI_MB_RESET_REQ_MSG_RB 2      /* MSG rcv box is RB#0 */

typedef struct GSN_HI_MB_CTX
{
	GSN_OSAL_SEM_T sendLock;
    GSN_CB_T recvCb;
	GSN_CB_T resetIndRecvCb;
} GSN_HI_MB_CTX_T;

PUBLIC VOID
GsnHiMb_Init(GSN_HI_MB_CTX_T *pHiMbCtx);

PUBLIC VOID
GsnHiMb_RecvCbRegister(GSN_HI_MB_CTX_T *pHiMbCtx, GSN_CB_T *recvCbInfo);

PUBLIC GSN_STATUS
GsnHiMb_MsgSend(GSN_HI_MB_CTX_T *pHiMbCtx, UINT32 *msg);

PUBLIC VOID
GsnHiMb_AckSend(GSN_HI_MB_CTX_T *pHiMbCtx, UINT32 *ack);

PUBLIC VOID
GsnHiMb_ResetIndRecvCbRegister(GSN_HI_MB_CTX_T *pHiMbCtx, GSN_CB_T *recvCbInfo);

#endif /* _GSN_HI_MB_H_ */

