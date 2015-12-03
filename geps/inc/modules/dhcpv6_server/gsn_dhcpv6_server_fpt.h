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
* $RCSfile: gsn_dhcpv6_server_fpt.h,v $
*
*******************************************************************************/

#ifndef _GSN_DHCPV6_SRVR_FPT_H_

#define _GSN_DHCPV6_SRVR_FPT_H_

typedef UINT
(*GsnDhcpv6Srvr_isClientExist_FP_T)(GSN_DHCPv6_SERVER_T*,DUID_STRUCT_T*,UINT*);


typedef UINT32
(*GsnDhcpv6Srvr_getAvailableIndex_FP_T)(GSN_DHCPv6_SERVER_T*,DUID_STRUCT_T*);


typedef UINT8
(*GsnDhcpv6Srvr_addClientDuid_FP_T)(GSN_DHCPv6_SERVER_T*,DUID_STRUCT_T*);


typedef UINT8
(*GsnDhcpv6Srvr_getIpAddress_FP_T)(GSN_DHCPv6_SERVER_T*,DUID_STRUCT_T*,UINT32*);


typedef UINT
(*GsnDhcpv6Srvr_GetData_FP_T)(UINT8*,UINT,ULONG*);


typedef UINT
(*GsnDhcpv6Srvr_GetOptionLength_FP_T)(UCHAR*,ULONG*,ULONG*);


typedef UINT
(*GsnDhcpv6Srvr_ProcessDuid_FP_T)(DUID_STRUCT_T*,UINT,UINT8*,UINT);


typedef UINT
(*GsnDhcpv6Srvr_ProcessIa_FP_T)(IA_T*,UINT8*,UINT,UINT);


typedef UINT
(*GsnDhcpv6Srvr_ProcessIana_FP_T)(DHCPv6_IANA_T*,UINT8*,UINT);


typedef UINT
(*GsnDhcpv6Srvr_AddDuid_FP_T)(DUID_STRUCT_T*,UINT8*,UINT*);


typedef UINT
(*GsnDhcpv6Srvr_AddIa_FP_T)(IA_T*,UCHAR*,UINT*);


typedef UINT
(*GsnDhcpv6Srvr_AddIana_FP_T)(GSN_DHCPv6_SERVER_T*,DUID_STRUCT_T*,DHCPv6_IANA_T*,UCHAR*,UINT*,ULONG);


typedef UINT8
(*GsnDhcpv6Srvr_SendResponse_FP_T)(GSN_DHCPv6_SERVER_T*,ULONG,ULONG,DUID_STRUCT_T*,DUID_STRUCT_T*,DHCPv6_IANA_T*,struct  sockaddr_in6*);



typedef UINT8
(*GsnDhcpv6Srvr_parsePacketAndReply_FP_T)(GSN_DHCPv6_SERVER_T*,INT, struct  sockaddr_in6*);


typedef VOID
(*dhcpv6ReceiveNotify_FP_T)(INT,NX_BSD_CB_EVENT_TYPE_T,VOID*);


typedef UINT8
(*GsnDhcpv6Srvr_Init_FP_T)(GSN_DHCPv6_SERVER_T*,GSN_DHCPV6_SRVR_INIT_PARAM_T*);


typedef UINT8
(*GsnDhcpv6Srvr_start_FP_T)(GSN_DHCPv6_SERVER_T*,GSN_DHCPV6_SRVR_INIT_PARAM_T*);



typedef UINT8
(*GsnDhcpv6Srvr_Stop_FP_T)(GSN_DHCPv6_SERVER_T*);


extern _RPST_ GsnDhcpv6Srvr_isClientExist_FP_T GsnDhcpv6Srvr_isClientExist_FP;
extern _RPST_ GsnDhcpv6Srvr_getAvailableIndex_FP_T GsnDhcpv6Srvr_getAvailableIndex_FP;
extern _RPST_ GsnDhcpv6Srvr_addClientDuid_FP_T GsnDhcpv6Srvr_addClientDuid_FP;
extern _RPST_ GsnDhcpv6Srvr_getIpAddress_FP_T GsnDhcpv6Srvr_getIpAddress_FP;
extern _RPST_ GsnDhcpv6Srvr_GetData_FP_T GsnDhcpv6Srvr_GetData_FP;
extern _RPST_ GsnDhcpv6Srvr_GetOptionLength_FP_T GsnDhcpv6Srvr_GetOptionLength_FP;
extern _RPST_ GsnDhcpv6Srvr_ProcessDuid_FP_T GsnDhcpv6Srvr_ProcessDuid_FP;
extern _RPST_ GsnDhcpv6Srvr_ProcessIa_FP_T GsnDhcpv6Srvr_ProcessIa_FP;
extern _RPST_ GsnDhcpv6Srvr_ProcessIana_FP_T GsnDhcpv6Srvr_ProcessIana_FP;
extern _RPST_ GsnDhcpv6Srvr_AddDuid_FP_T GsnDhcpv6Srvr_AddDuid_FP;
extern _RPST_ GsnDhcpv6Srvr_AddIa_FP_T GsnDhcpv6Srvr_AddIa_FP;
extern _RPST_ GsnDhcpv6Srvr_AddIana_FP_T GsnDhcpv6Srvr_AddIana_FP;
extern _RPST_ GsnDhcpv6Srvr_SendResponse_FP_T GsnDhcpv6Srvr_SendResponse_FP;
extern _RPST_ GsnDhcpv6Srvr_parsePacketAndReply_FP_T GsnDhcpv6Srvr_parsePacketAndReply_FP;
extern _RPST_ dhcpv6ReceiveNotify_FP_T dhcpv6ReceiveNotify_FP;
extern _RPST_ GsnDhcpv6Srvr_Init_FP_T GsnDhcpv6Srvr_Init_FP;
extern _RPST_ GsnDhcpv6Srvr_start_FP_T GsnDhcpv6Srvr_start_FP;
extern _RPST_ GsnDhcpv6Srvr_Stop_FP_T GsnDhcpv6Srvr_Stop_FP;

#endif