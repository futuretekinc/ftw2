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
* $RCSfile: gsn_rpl_priv.h,v $
*
* Description : This file contains function declaration for RPL APIs.
*******************************************************************************/

/*******************************************************************************
* File inclusion
*******************************************************************************/
#ifndef _GSN_RPL_PRIV_H_
#define _GSN_RPL_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "modules/mesh_mgmt/rpl/gsn_rpl.h"
/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief macro, for state of the entry.
 *    MACRO defining state of the entry. The state of the NB or RT entry is 
 * based on the time the entry was marked heard.
 ******************************************************************************/
#define GSN_RPL_ENTRY_NOT_PRESENT 0
#define GSN_RPL_ENTRY_ACTIVE      1
#define GSN_RPL_ENTRY_EXPIRED     2
#define GSN_RPL_ENTRY_DAD_IP      3

typedef enum GSN_RPL_OF_STATUS
{
    GSN_RPL_OF_SUCCESS,
    GSN_RPL_OF_FAILURE,
    GSN_RPL_OF_NEW_PARENT    
}GSN_RPL_OF_STATUS_T;

/**< Initializes the OF module */
typedef VOID * (*GSN_RPL_OF_INIT_T)( VOID *pCtx, VOID *pDODAGCtx,
    VOID *pCfg );

/**< Calculates the RANK of the node. */
typedef UINT16 (*GSN_RPL_OF_CALC_RANK_T)( VOID *pOFCtx, UINT8 *pDIOFrm,
    GSN_RPL_DODAG_CFG_T* pCfg, UINT8* pMC );

typedef UINT16 (*GSN_RPL_OF_CHECK_FOR_PARENT_SWITCH_T)( VOID *pOFCtx, 
    UINT16 currentRank, UINT16 bestParentRank );


typedef VOID (*GSN_RPL_OF_SET_DODAG_CTX_T)( VOID *pOFCtx, VOID* pDODAGCtx );

typedef struct GSN_RPL_OF_IF
{
    UINT16 OC;
    UINT16 OFCtxSize;
    GSN_RPL_OF_SET_DODAG_CTX_T setDODAGCtx;
    GSN_RPL_OF_CALC_RANK_T calcRank;  
    GSN_RPL_OF_CHECK_FOR_PARENT_SWITCH_T checkParentSwitch;
}GSN_RPL_OF_IF_T;


extern const UINT32 GsnRpl_AllNodeMCast[ 4 ];


GSN_STATUS GsnRpl_PostDelayEvent( GSN_RPL_T* pRpl, GSN_RPL_EVENT_T *pEvent );

#ifdef __cplusplus
}
#endif
#endif /* _GSN_RPL_PRIV_H_ */


