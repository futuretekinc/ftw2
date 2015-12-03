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
* $RCSfile: gsn_rpl_netx_if.h,v $
*
* Description : This file contains function defination for RPL Information in
* Data-Plane Datagrams as per RFC 6553.
*****************************************************************************/

/******************************************************************************
* File inclusion
******************************************************************************/
#ifndef _GSN_RPL_NETX_IF_H_
#define _GSN_RPL_NETX_IF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "netx/nx_api.h"

/**<
To add IPv6 optional herader the following things has to be taken care.
- A instance of type GSN_RPL_NET_BUF_INFO_T has to be defined.
- The pBufEnd has to be initialized to the pkt pointer of the IPv6 frame.
- A new net packet has to be allocated and the address of this has to be put in
  pBufStart.
- The IPv6 header alone has to be copied to the prepend location in the new net
  packet and the prepend point has to be updated.
- The prepend pointer of the original IPv6 pakcet has to be advanced by IPv6 
  header size.
- The new optional header has to be written at the append location of the new 
  net packet.
- If the buffer space is not enough for the written the new optional header, 
  then, more net packet call be allocated using GsnRpl_AllocNetBuf, which will
  allocate a new net packet and chain the packet to the orignal IPv6 packet.

To generate a new packet the following steps has to be folloews.
- A instance of type GSN_RPL_NET_BUF_INFO_T has to be defined and all elements 
  has to be initialized to zero.
- Call GsnRpl_AllocNetBuf to allocate packet. If the buffer space is not enough
  call again GsnRpl_AllocNetBuf to get a new buffer space. GsnRpl_AllocNetBuf 
  takes care of chaining all the packets.
 
*/


typedef struct GSN_RPL_NET_BUF_INFO
{
    UINT8  *pBuf;
    UINT16 len;
    UINT16 lenUsed;
    VOID   *pIp;
    UINT8  *pBufStart;
    UINT8  *pBufEnd;
}GSN_RPL_NET_BUF_INFO_T;

typedef struct GSN_RPL_SEND_FRM_INFO
{
    UINT8 l4Protocol;
    UINT8 ipv6NHoption;
    UINT8 *pMac;
    GSN_RPL_NET_BUF_INFO_T *pInfo;
    UINT8 *pDstIp; 
}GSN_RPL_SEND_FRM_INFO_T;

typedef struct GSN_RPL_RECV_FRM_INFO
{    
    UINT8 *pDstMac;
    UINT8  pDstIp[16];
    UINT8 *pRplExtn;
    UINT8  l4Protocol;
    GSN_RPL_NET_BUF_INFO_T *pInfo;    
}GSN_RPL_RECV_FRM_INFO_T;


UINT32 GsnRpl_AllocNetBuf( GSN_RPL_NET_BUF_INFO_T *pNetBufInfo );

GSN_STATUS GsnRpl_AddDataHeader( VOID *pCtx, GSN_RPL_SEND_FRM_INFO_T *pSFI , 
    VOID *pPkt, UINT8 Need_RPL_Extn );
GSN_STATUS GsnRpl_ProcessDataExtn( VOID *pCtx, 
    GSN_RPL_RECV_FRM_INFO_T *pRecvInfo , VOID *pPkt);

BOOL GsnRpl_SrcRtNeeded( VOID *pDODAG );

VOID GsnRpl_NetXInit( GSN_RPL_T *pCtx, VOID *pIpIf );

VOID *GsnRpl_GetNetxIpIfAddr( VOID *pIpIf, UINT8 ifId, UINT32 addr[] );
VOID *GsnRpl_GetNetxIfAddr( VOID *pIpIf, UINT8 ifId );

VOID GsnRpl_GetNetxAddrFromIf( VOID *pIfAddr, ULONG addr[4] );

VOID GsnRpl_ConstructIPAddr( VOID *pIP, UINT8 ifId, UINT8 *pPrefix, UINT32* pAddr );
GSN_STATUS Is_DAO_ACK( NX_PACKET *pPkt);
GSN_STATUS Change_Ip_Next_Header(NX_PACKET * pPkt , UINT8 protocol);
VOID GsnRpl_NetXDeInit( GSN_RPL_T *pCtx, VOID *pIpIf );

#ifdef __cplusplus
}
#endif
#endif /* _GSN_RPL_NETX_IF_H_ */
