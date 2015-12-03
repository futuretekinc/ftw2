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
* $RCSfile: gsn_rpl_dodag.h,v $
*
* Description : This file contains structure and function defination for RPL 
* DADAG formation and maintanance.
*****************************************************************************/
#ifndef _GSN_RPL_DODAG_H_
#define _GSN_RPL_DODAG_H_

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
* File inclusion
******************************************************************************/

#define GSN_RPL_DODAG_RANK_INFINITE 0xFFFF
#define GSN_RPL_DODAG_RANK_ROOT( pDCtx ) pDCtx->dodagCfg.minHopRankIncrease

typedef struct GSN_RPL_REACHABLE_PREFIX
{
    struct GSN_RPL_REACHABLE_PREFIX *pNext;
    UINT8 prefixLen;
    UINT8 prf;
    UINT32 lifetime;
    UINT8 prefix[8];
}GSN_RPL_REACHABLE_PREFIX_T;



typedef struct GSN_RPL_DODAG_MATRIX_CONTAINER
{
    UINT8 size;
    UINT8 contenet[1];
}GSN_RPL_DODAG_MATRIX_CONTAINER_T;

#define GSN_DODAG_STATE_JOINING 0
#define GSN_DODAG_STATE_CREATED 1
#define GSN_DODAG_STATE_MEMBER  2

#define GSN_DODAG_MOP_MASK ( 0x7 << 3 )
#define GSN_DODAG_MOP_NO_DROUTE 0
#define GSN_DODAG_MOP_NSTORE ( 1 << 3 )
#define GSN_DODAG_MOP_STORE_NMCAST ( 2 << 3 )
#define GSN_DODAG_MOP_STORE_MCAST ( 3 << 3 )

#define GSN_DODAG_PRF_MASK ( 0x7 )
#define GSN_DODAG_GET_PRF( gMopPrf ) ((gMopPrf) & 0x7 )

#define GSN_IS_DODAG_MODE_NON_STORING( pDCtx ) \
    (((pDCtx)->gMopPrf & GSN_DODAG_MOP_MASK ) ==  GSN_DODAG_MOP_NSTORE )

#define GSN_IS_DODAG_MODE_STORING( pDCtx ) \
    (((pDCtx)->gMopPrf & GSN_DODAG_MOP_MASK ) !=  GSN_DODAG_MOP_NSTORE )

typedef struct GSN_RPL_DODAG_CTX
{
    VOID *pNwkCtx; /**< Points to the NX_IP */
    VOID *pSrcAddr; /**< Points to NXD_IPV6_ADDRESS for link local address */
    VOID *pSiteAddr; /**< Points to NXD_IPV6_ADDRESS for site local address */
    
    struct GSN_RPL_DODAG_CTX *pNext;

    GSN_RPL_DODAG_BASIC_CFG_T cfg;
    UINT8 dodagState;
    UINT8 dodagIdx;

    GSN_SOFT_TMR_T lifetimeTmr; /**< Soft timer for DAO schedulling */
    GSN_RPL_EVENT_T lifetimeEvent;
    GSN_SOFT_TMR_T daoTmr; /**< Soft timer for DAO schedulling */
	GSN_RPL_EVENT_T daoEvent;
	GSN_SOFT_TMR_T daoackTmr; /**< Soft timer for DAO RE-schedulling in case of 
	not receiving DAO-ACK */
	GSN_RPL_EVENT_T daoackEvent;
	
    GSN_TRICKLE_TMR_CFG_T dioTrickleCfg;
    GSN_TRICKLE_TMR_CTX_T dioTrickleTmr;
        
    ULONG dodagId[4];
    UINT32 lbrVersion; /**< Version number used in ABRO*/
    /**< Life time defined in ABRO. Set to 0 if the dodagId is not a BR. */ 
    UINT16 lbrLifeTime;

    /**< Contains the address of the node. In TGT option only prefix or the 
    complete address part is used, based on the nwkFlag setting. */
    UINT32 ipv6Addr[4]; 
    UINT8 ptIndex; /**< Stores the index of the prefixed used by the node */


    UINT8  dodagVer; /**< DODAG Version */
    UINT8  RPLInstanceID;

    UINT16 rank; /* Own rank. 0 if it is DODAG root, 0xFFFF if it is a leaf */
    /**< 0th bit is for Grounded, 2-4 bits are for MOP(Mode of Operation) and 
    5-7 bits are Prf(DODAGPreference) */
    UINT8  gMopPrf;
    UINT8  dstn;
    UINT8  daoSeq;
    UINT8  pathSeq;

    GSN_RPL_OF_IF_T *pOFIF;
    VOID *pOFCtx;
    /**< Prefix that are reachanble from this RPL router */
    GSN_RPL_REACHABLE_PREFIX_T *pPrefixList;

    GSN_RPL_DODAG_CFG_T dodagCfg;

    GSN_RPL_DODAG_MATRIX_CONTAINER_T *pDodagMatrixContainter;
    
    /**< Indicates whether the current node has its own prefix or uses its 
    parent prefix. If set then it uses its own prefix else it uses its parent
    prefix */
    UINT8 nwkFlag; 
    GSN_RPL_TABLE_T *table;
    VOID *pRpl;
    VOID *pND;

    GSN_RPL_CB_T pCb;
    VOID *pAppCtx ;
    
}GSN_RPL_DODAG_CTX_T;


#define GSN_RPL_MODE_DAG_ROOT   0/**< Acts as a DODAG ROOT */
#define GSN_RPL_MODE_DAG_ROUTER 1/**< Can act as a DODAG ROOT and a Host */
#define GSN_RPL_MODE_DAG_HOST   2/**< Acts as a DODAG Host */

/**< RPL will be in scan state before joining any DAG */
#define GSN_RPL_STATE_IDLE      0
#define GSN_RPL_STATE_SCANNING  1
#define GSN_RPL_STATE_READY     2


#define DAO_ACK_TIMEOUT_TIME 100
#define MAX_DAO_RE_SEND 2

/* DODAG Sequence Operation */
        
#define GSN_RPL_SEQ_COUNTER_MAX_VALUE           255
#define GSN_RPL_SEQ_COUNTER_HALF_VALUE          127
#define GSN_RPL_SEQ_COUNTER_SEQUENCE_WINDOWS    16
        
/**< Recommended value of initial value is 240 (256 - SEQUENCE_WINDOW) */        
#define GSN_RPL_SEQ_COUNTER_INIT()                 \
    ( GSN_RPL_SEQ_COUNTER_MAX_VALUE -              \
    GSN_RPL_SEQ_COUNTER_SEQUENCE_WINDOWS + 1)

/**< When incrementing a sequence counter greater than or equal to 128, 
the maximum value is 255. When incrementing a sequence counter less than
128, the maximum value is 127. The value is assumed to be of type UINT8*/
#define GSN_RPL_SEQ_COUNTER_INCREMENT( value )              \
  ((value) > GSN_RPL_SEQ_COUNTER_HALF_VALUE ?               \
   ++(value) : ++(value) & GSN_RPL_SEQ_COUNTER_HALF_VALUE )


UINT32 GsnRpl_DODAGCmpRank( GSN_RPL_DODAG_CTX_T *pDCtx, UINT16 Rank1, 
    UINT16 Rank2 );

/**< Finds whether the current node can be added to the parent list, if yes,
then adds to the parent list. This will add the device as its neighbour and to
the parent list. This API will be called during parent selection procedure. */
GSN_RPL_OF_STATUS_T
GsnRpl_DODAGAddParent( GSN_RPL_DODAG_CTX_T *pDCtx, 
    GSN_RPL_ICMP_RECV_INFO_T* pRecvInfo, GSN_RPL_NB_ENTRY_T* nbEntry );

/**< After a parent is selected, if we receive information from a new node
which joined the DODAG and has the capability to act as a parent, then this
API is called to find whether we should consider it to be our parent or not */
GSN_RPL_OF_STATUS_T GsnRpl_DODAGCheckParent( GSN_RPL_DODAG_CTX_T *pDCtx );

GSN_STATUS 
GsnRpl_StartAsBR( GSN_RPL_DODAG_CTX_T *pDCtx );


GSN_STATUS GsnRpl_StartAsHost( GSN_RPL_DODAG_CTX_T *pDCtx );
GSN_STATUS GsnRpl_StartAsRouter( GSN_RPL_DODAG_CTX_T *pDCtx );

VOID 
GsnRpl_DODAGSelectionTimeOut( VOID* pCtx, GSN_SOFT_TMR_HANDLE_T timerHandle );
VOID GsnRpl_DODAGLocalRepair( GSN_RPL_DODAG_CTX_T *pDCtx );
int GsnRpl_IsSeqCounterGreater( UINT8 a, UINT8 b );
VOID GsnRpl_DODAGGlobalRepair( GSN_RPL_DODAG_CTX_T *pDCtx );
GSN_STATUS GsnRpl_TriggerDAOSend( GSN_RPL_DODAG_CTX_T *pDCtx );
GSN_STATUS GsnRpl_DODAGJoinNewParent( GSN_RPL_DODAG_CTX_T *pDCtx );
GSN_STATUS GsnRpl_Is_DIS_Response( UINT8 *pSrcAddr , GSN_RPL_DODAG_CTX_T *pDCtx );

#ifdef __cplusplus
}
#endif
#endif /* _GSN_RPL_DODAG_H_ */
