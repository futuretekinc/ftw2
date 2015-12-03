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
* $RCSfile: gsn_rpl_frm.h,v $
*
* Description : This file contains structure and function defination for RPL 
* frame processing and sending.
*****************************************************************************/
#ifndef _GSN_RPL_FRM_H_
#define _GSN_RPL_FRM_H_

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
* File inclusion
******************************************************************************/

#define GSN_RPL_IP_PKT_OPT_HDR_INTERNAL     255

#define GSN_ICMPV6_TYPE_RPL                  155  /**< RPL */

/* ICMP RPL message code */
#define GSN_ICMPV6_RPL_CODE_DIS                0x00/* DODAG Information Solicitation */
#define GSN_ICMPV6_RPL_CODE_DIO                0x01/* DODAG Information Object */
#define GSN_ICMPV6_RPL_CODE_DAO                0x02/* Destination Advertisement Object */
#define GSN_ICMPV6_RPL_CODE_DAO_ACK            0x03/* Destination Advertisement Object Acknowledgment */
#define GSN_ICMPV6_RPL_CODE_SEC_DIS            0x80/* Secure DODAG Information Solicitation */
#define GSN_ICMPV6_RPL_CODE_SEC_DIO            0x81/* Secure DODAG Information Object */
#define GSN_ICMPV6_RPL_CODE_SEC_DAO            0x82/* Secure Destination Advertisement Object */
#define GSN_ICMPV6_RPL_CODE_SEC_DAO_ACK        0x83/* Secure Destination Advertisement Object Acknowledgment */
#define GSN_ICMPV6_RPL_CODE_CONSISTENCY_CHECK  0x8A/* Consistency Check */

#define GSN_RPL_OPT_PAD1                  0
#define GSN_RPL_OPT_PADN                  1
#define GSN_RPL_OPT_DAG_METRIC_CONTAINER  2
#define GSN_RPL_OPT_ROUTE_INFO            3
#define GSN_RPL_OPT_DAG_CFG               4
#define GSN_RPL_OPT_TARGET                5
#define GSN_RPL_OPT_TRANSIT               6
#define GSN_RPL_OPT_SOLICITED_INFO        7
#define GSN_RPL_OPT_PREFIX_INFO           8
#define GSN_RPL_OPT_TARGET_DESC           9

#define GSN_RPL_DIO_OFFSET_DODAG_ID       8


/**< Length of the different RPL frame field */
#define GSN_RPL_DIO_BASE_LEN 24
#define GSN_RPL_OPT_DAG_CFG_LEN               14

#define GSN_RPL_OPTIONAL_FIELD_FLAG_SI   ( 1 << 0 )
#define GSN_RPL_OPTIONAL_FIELD_FLAG_DMC  ( 1 << 1 )
#define GSN_RPL_OPTIONAL_FIELD_FLAG_RIO  ( 1 << 2 )
#define GSN_RPL_OPTIONAL_FIELD_FLAG_CFG  ( 1 << 3 )
#define GSN_RPL_OPTIONAL_FIELD_FLAG_PI   ( 1 << 4 )
#define GSN_RPL_OPTIONAL_FIELD_FLAG_TGT  ( 1 << 5 )
#define GSN_RPL_OPTIONAL_FIELD_FLAG_TI   ( 1 << 6 )
#define GSN_RPL_OPTIONAL_FIELD_FLAG_TD   ( 1 << 7 )

#define GSN_RPL_OPTIONAL_FIELD_FLAG_DAO_ACK   ( 1 << 8 )
#define GSN_RPL_OPTIONAL_FIELD_FLAG_DAO_DODAGID   ( 1 << 9 )

#define GSN_RPL_OPTIONAL_FIELD_FLAG_STORING   ( 1 << 10 )


#define WRITE_16( pos, value ) *(pos)++ = (value) >> 8; \
    *(pos)++ = (value) & 0xff

#define WRITE_32( pos, value ) *(pos)++ = (value) >> 24; \
    *(pos)++ = ((value) >> 16) & 0xff;                   \
    *(pos)++ = ((value) >> 8 ) & 0xff;                   \
    *(pos)++ = (value) & 0xff

#define READ_16( pos, value ) (value) = (*((pos)) << 8 ) + *((pos)+1)

#define READ_32( pos, value ) \
    (value) = (*((pos)) << 24 ) + (*((pos) + 1) << 16 ) + \
    (*((pos) + 2) << 8 ) + (*((pos) + 3) )


#define ADD_PADDING( pPos, padding )                    \
{                                                       \
    if( padding == 1 ) *pPos++ = 0;                     \
    else                                                \
    {                                                   \
        *pPos++ = 0x1;                                  \
        *pPos++ = padding - 2;                          \
        memset( pPos, 0, padding - 2 );                 \
        pPos += padding - 2;                            \
    }                                                   \
}

#define GSN_RPL_IS_MCAST( addr ) ((addr)[0] == 0xff020000)

GSN_STATUS GsnRPL_CreateDIOFrmCb( VOID *pCtx, UINT32 flag,
    GSN_RPL_NET_BUF_INFO_T *pInfo );

int GsnRPL_CreateDAOFrmCb( VOID *pCtx, UINT32 flag,
    GSN_RPL_NET_BUF_INFO_T *pInfo );
int GsnRPL_CreateDISFrmCb( VOID *pCtx, UINT32 flag,
    GSN_RPL_NET_BUF_INFO_T *pInfo );
int GsnRPL_CreateDAOAckFrmCb( VOID *pCtx, UINT32 flag,
    GSN_RPL_NET_BUF_INFO_T *pInfo );

INLINE GSN_STATUS
GsnRPL_SendDIO( GSN_RPL_DODAG_CTX_T *pDCtx, UINT8* dstAddr )
{
    GSN_RPL_ICMP_SEND_INFO_T info = { GsnRPL_CreateDIOFrmCb, pDCtx, 
        GSN_RPL_OPTIONAL_FIELD_FLAG_DMC | GSN_RPL_OPTIONAL_FIELD_FLAG_RIO |
        GSN_RPL_OPTIONAL_FIELD_FLAG_CFG | GSN_RPL_OPTIONAL_FIELD_FLAG_PI, 1, 
        GSN_ICMPV6_TYPE_RPL, GSN_ICMPV6_RPL_CODE_DIO };
    DBG_TRACE_FUNC;
    return GsnNw_ICMPv6Send( pDCtx->pNwkCtx, &info, ( UINT8* )dstAddr, 
        pDCtx->pSrcAddr );
}

INLINE GSN_STATUS
GsnRPL_SendDIS( GSN_RPL_T *pCtx, UINT8* dstAddr )
{
    GSN_RPL_ICMP_SEND_INFO_T info = { GsnRPL_CreateDISFrmCb, pCtx, 0, 1,
        GSN_ICMPV6_TYPE_RPL, GSN_ICMPV6_RPL_CODE_DIS };
    DBG_TRACE_FUNC;
    return GsnNw_ICMPv6Send( pCtx->pNwkCtx, &info, ( UINT8* )dstAddr,
        pCtx->pSrcAddr );
}

INLINE GSN_STATUS
GsnRPL_SendDAO( GSN_RPL_DODAG_CTX_T *pDCtx, UINT32* dstAddr )
{
    /**< Check the destination address, if multicast then DAO ACK field should 
    be cleared. Hop limit should be 1 if the dstaAddr is multicast.
    TODO: Need to findout when to send DODAGID */
    GSN_RPL_ICMP_SEND_INFO_T info;
    info.cb = GsnRPL_CreateDAOFrmCb;
    info.pCtx = pDCtx; 
    info.flag = GSN_RPL_OPTIONAL_FIELD_FLAG_TGT | 
        GSN_RPL_OPTIONAL_FIELD_FLAG_TI;
    DBG_TRACE_FUNC;
    if( GSN_RPL_IS_MCAST( dstAddr ))
    {
         info.hopLimit = 1;
    }
    else
    {
        info.hopLimit = 255;
        info.flag |= GSN_RPL_OPTIONAL_FIELD_FLAG_DAO_ACK;
    }

    if( GSN_IS_DODAG_MODE_STORING  (pDCtx )) 
        info.flag |= GSN_RPL_OPTIONAL_FIELD_FLAG_STORING;
    
    info.icmpv6Code = GSN_ICMPV6_RPL_CODE_DAO;
	info.icmpv6Type = GSN_ICMPV6_TYPE_RPL;
	if( GSN_IS_DODAG_MODE_STORING  (pDCtx ))
	{
        return GsnNw_ICMPv6Send( pDCtx->pNwkCtx, &info, ( UINT8* )dstAddr,
            pDCtx->pSrcAddr );
	}
	else
	{
		return GsnNw_ICMPv6Send( pDCtx->pNwkCtx, &info, ( UINT8* )dstAddr,
            pDCtx->pSiteAddr );
	}
}

INLINE GSN_STATUS
GsnRPL_SendDAOAck( GSN_RPL_DODAG_CTX_T *pDCtx, UINT8 *pAddr, UINT32 seqNum )
{
    GSN_RPL_ICMP_SEND_INFO_T info = { GsnRPL_CreateDAOAckFrmCb, pDCtx, seqNum, 
        255, GSN_ICMPV6_TYPE_RPL, GSN_ICMPV6_RPL_CODE_DAO_ACK };
	DBG_PRINT("DAO DST = %08x:%08x:%08x:%08x\n", ((UINT32*)pAddr)[3], ((UINT32*)pAddr)[2],
		((UINT32*)pAddr)[1], ((UINT32*)pAddr)[0]);
	if( GSN_IS_DODAG_MODE_STORING  (pDCtx ))
		return GsnNw_ICMPv6Send( pDCtx->pNwkCtx, &info, pAddr, pDCtx->pSrcAddr );
	else
		return GsnNw_ICMPv6Send( pDCtx->pNwkCtx, &info, pAddr, pDCtx->pSiteAddr );
}

UINT8* GsnRpl_GetOptionalField( UINT8 *pFrm, UINT32 frmLen, UINT8 optionName );

#ifdef __cplusplus
}
#endif
#endif /* _GSN_RPL_FRM_H_ */