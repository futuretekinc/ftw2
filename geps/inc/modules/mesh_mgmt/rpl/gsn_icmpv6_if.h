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
* $RCSfile: gsn_icmpv6_if.h,v $
*
* Description : This file contains function defination for interfacing ICMPv6.
*******************************************************************************/
#ifndef _GSN_ICMPV6_IF_H_
#define _GSN_ICMPV6_IF_H_

#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
* File inclusion
*******************************************************************************/
#define GSN_NW_ICMPV6_TYPE_RPL 155
#define NX_PROTOCOL_NH_HOP_BY_HOP_OPT_RPL 0x63 
#define GSN_NW_ICMPV6_TYPE_DAR 157
#define GSN_NW_ICMPV6_TYPE_DAC 158

/**
 *****************************************************************************
 * @ingroup GsnRPL
 * @brief  Callback funtion definition for ICMPv6 Frame creation.
 * @param pCtx - IN Buffer pointer to context.
 * @param pBuf - IN Buffer pointer to construct the RPL header.
 * @param pSize - IN/OUT: writes teh available size. The callback function 
 * should return the size it wrote.
 * @retval Returns the ICMPv6 code to be used.
 *****************************************************************************/
typedef GSN_STATUS (*ICMP_PKT_FORM_CB_T)( VOID *pCtx, UINT32 flag, 
    GSN_RPL_NET_BUF_INFO_T *pInfo );

typedef struct GSN_RPL_ICMP_SEND_INFO
{
    ICMP_PKT_FORM_CB_T cb;
    VOID *pCtx;
    UINT32 flag;
    UINT32 hopLimit;
    UINT8 icmpv6Type;
    UINT8 icmpv6Code;
}GSN_RPL_ICMP_SEND_INFO_T;

typedef struct GSN_RPL_ICMP_RECV_INFO
{
    UINT8 *pFrm;
	UINT32 frmLen;
	UINT8  code;
	UINT8* srcIp;
	UINT8* macAdd;
}GSN_RPL_ICMP_RECV_INFO_T;

GSN_STATUS 
GsnNw_ICMPv6Send( VOID *ip_ptr, GSN_RPL_ICMP_SEND_INFO_T *pInfo, 
	UINT8 *pDstAddr, VOID *pIf );


GSN_STATUS 
GsnRpl_ICMPv6PktProcess( VOID* pCtx, GSN_RPL_ICMP_RECV_INFO_T* pRecvInfo );

#ifdef __cplusplus
}
#endif
#endif /* _GSN_ICMPV6_IF_H_ */