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
* $RCSfile: gsn_6nd_priv.h,v $
*
* Description : This file contains function defination for 6ND.
*****************************************************************************/

#ifndef _GSN_6ND_PRIV_H_
#define _GSN_6ND_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
* File inclusion
******************************************************************************/

/**
 *****************************************************************************
 * @ingroup Gsn6ND
 * @brief Configurable option for 6ND
 *    These macros defines configurable option for 6ND device.
 *****************************************************************************/
#define GSN_RPL_6ND_MAX_RTR_SOLICITATIONS 3
#define GSN_RPL_6ND_RTR_SOLICITATION_INTERVAL 10
#define GSN_RPL_6ND_MAX_RTR_SOLICITATION_INTERVAL 60
#define GSN_RPL_6ND_RETRANS_TIMER 1 //1000msec
#define GSN_RPL_6ND_MAX_UNICAST_SOLICIT 3
#define GSN_RPL_6ND_TENTATIVE_NCE_LIFETIME  20
     
#define NW_TICKS_PER_SEC 1 //TODO

#define GSN_RPL_6ND_MAX_INITIAL_RTR_ADVERT           3
#define GSN_RPL_6ND_MAX_INITIAL_RTR_ADVERT_INTERVAL  16
#define GSN_RPL_6ND_MAX_FINAL_RTR_ADVERT             3



/**
 *****************************************************************************
 * @ingroup Gsn6ND
 * @brief 6ND state
 *    These macros defines state of 6ND. These are for internal use.
 *****************************************************************************/
#define GSN_RPL_6ND_STATE_NOT_INIT     0
#define GSN_RPL_6ND_STATE_INIT_IN_PROG 1
#define GSN_RPL_6ND_STATE_READY        2

#define GSN_RPL_6ND_RA_BASE_LEN   12
#define GSN_RPL_6ND_RA_OPT_SALLAO 1
#define GSN_RPL_6ND_RA_OPT_CO     34



typedef struct GSN_RPL_6ND_DAD_NODE_INFO
{
    UINT16 regLifeTime;
    UINT32  eui64[2];
    UINT32  addr[4];
}GSN_RPL_6ND_DAD_NODE_INFO_T; 

typedef struct GSN_RPL_6ND_DAD_FRM_CTX
{
    GSN_RPL_6ND_CTX_T *pCtx;
    GSN_RPL_6ND_DAD_NODE_INFO_T *pInfo;
}GSN_RPL_6ND_DAD_FRM_CTX_T;


VOID GsnRpl_6ndSendNbMsg ( GSN_RPL_6ND_CTX_T *pCtx, VOID* srcAddr, ULONG *pDst, 
    UINT8 type, UINT32 flag, int send_sllao, UINT8 status, UINT8* addr );
GSN_STATUS GsnRPL_6ndSendDAR( GSN_RPL_6ND_CTX_T *pCtx, 
    GSN_RPL_6ND_DAD_NODE_INFO_T* pInfo, UINT8 *pDstAddr );
GSN_STATUS GsnRpl_6ndBuildARO( GSN_RPL_6ND_CTX_T *pCtx, UINT8* pAddr,  
    UINT8 status, UINT8 *pBuf, UINT32* pLen );
GSN_STATUS GsnRpl_6ndSendDAR( GSN_RPL_6ND_CTX_T *pCtx, 
    GSN_RPL_6ND_DAD_NODE_INFO_T* pInfo, UINT8 *pDstAddr );
GSN_STATUS GsnRpl_6ndSendDAC( GSN_RPL_6ND_CTX_T *pCtx, 
    GSN_RPL_6ND_DAD_NODE_INFO_T* pInfo, UINT8 status, UINT8 *pDstAddr );
UINT8* GsnRpl_6ndGetOptionalField( UINT8 *pFrm, UINT32 frmLen, UINT8 optionName );
GSN_STATUS GsnRpl_6ndSendRA( GSN_RPL_6ND_CTX_T *pCtx, UINT8 *pDstAddr );
VOID GsnRpl_6ndBuildNSSLLAO( UINT8 *pBuf, UINT16 ll16 );
VOID GsnRpl_ProcessCO( GSN_RPL_6ND_CTX_T *pCtx, UINT8 *pOpt,    UINT32 optLen );
UINT8 GsnRpl_6ndGetDADStatus( GSN_RPL_6ND_CTX_T *pCtx, GSN_RPL_NB_ENTRY_T **pNbNew, 
    UINT32 macAddr[2], UINT32 ipAddr[], UINT8 isNb );
GSN_STATUS GsnRpl_6ndSendRS( GSN_RPL_6ND_CTX_T *pCtx, UINT8 *pDstAddr );
GSN_STATUS GsnRpl_6ndInitRTDiscovery( GSN_RPL_6ND_CTX_T *pCtx );

#ifdef __cplusplus
}
#endif
#endif /* _GSN_6ND_PRIV_H_ */
