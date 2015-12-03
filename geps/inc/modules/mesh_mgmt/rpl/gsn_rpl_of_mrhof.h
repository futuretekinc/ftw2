/******************************************************************************
*
*               COPYRIGHT (c) 2013 GainSpan Corporation
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
* $RCSfile: gsn_rpl_of_mrhof.h,v $
*
* Description : This file contains function declaration for RPL APIs.
*******************************************************************************/

/*******************************************************************************
* File inclusion
*******************************************************************************/
#ifndef _GSN_RPL_OF_MRHOF_H_
#define _GSN_RPL_OF_MRHOF_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GSN_RPL_MRHOF_CFG
{
    UINT16 maxLinkMatrix;
    UINT16 maxPathCost;
    UINT16 parentSwitchThr;
    UINT8  parentSetSize;
    UINT8  allowFloatingRoot;
}GSN_RPL_MRHOF_CFG_T;

typedef struct GSN_RPL_MRHOF
{
    VOID *pDCtx;
    GSN_RPL_MRHOF_CFG_T   cfg;
    UINT16 bestParentRank;
    UINT8  parentAdded;
}GSN_RPL_MRHOF_T;

const VOID * GsnRplOf_MRHOFInit( GSN_RPL_MRHOF_T *pCtx,
    VOID *pCfg );

#ifdef __cplusplus
}
#endif
#endif /* _GSN_RPL_OF_MRHOF_H_ */


