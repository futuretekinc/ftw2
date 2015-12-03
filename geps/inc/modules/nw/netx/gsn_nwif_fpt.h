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
* $RCSfile: gsn_nwif_fpt.h,v $
*
*******************************************************************************/
#ifndef _GSN_NWIF_FPT_H_

#define _GSN_NWIF_FPT_H_

typedef GSN_STATUS
(* GsnNwIf_Init_FP_T)(GSN_NWIF_CTX_T *pNwIf, GSN_NWIF_INIT_PARAMS_T *pParams);

extern _RPST_ GsnNwIf_Init_FP_T GsnNwIf_Init_FP;

typedef GSN_STATUS
( *GsnNwif_BsdInitialize_FP_T)(GSN_NW_BSD_T *pBsd, GSN_NWIF_BSD_INIT_PARAM_T *pParam);

extern _RPST_ GsnNwif_BsdInitialize_FP_T GsnNwif_BsdInitialize_FP;

typedef GSN_STATUS
( *GsnNwif_IPv6Init_FP_T)(GSN_NWIF_CTX_T *pNwIf, GSN_NWIF_IPV6_INIT_PARAM_T *pParams);
 extern _RPST_ GsnNwif_IPv6Init_FP_T GsnNwif_IPv6Init_FP;

typedef GSN_STATUS
(* GsnNwIf_DeInit_FP_T)(GSN_NWIF_CTX_T *pNwIf);

extern _RPST_ GsnNwIf_DeInit_FP_T GsnNwIf_DeInit_FP;

typedef GSN_STATUS_T
(* GsnNwIf_Open_FP_T)(GSN_NWIF_CTX_T *pNwIf,        GSN_NWIF_IP_CONFIG_T *pIpConfig, 
							GSN_NWIF_DHCP_PARAMS_T *pDhcpParams);

extern _RPST_ GsnNwIf_Open_FP_T GsnNwIf_Open_FP;

typedef GSN_STATUS_T
(* GsnNwIf_Close_FP_T)(GSN_NWIF_CTX_T *pNwIf);

extern _RPST_ GsnNwIf_Close_FP_T GsnNwIf_Close_FP;

typedef GSN_STATUS
(*GsnNwif_UpdatePhyAddr_FP_T)(GSN_NWIF_CTX_T *pNwIf);
extern _RPST_ GsnNwif_UpdatePhyAddr_FP_T GsnNwif_UpdatePhyAddr_FP;


typedef GSN_STATUS
( *GsnNwif_IPv4Configure_FP_T)(GSN_NWIF_CTX_T *pNwIf,GSN_NWIF_IPv4_CONFIG_T *pUsrIPv4Cfg,
									GSN_NWIF_DHCP_PARAMS_T *pDhcpParams);
extern _RPST_ GsnNwif_IPv4Configure_FP_T GsnNwif_IPv4Configure_FP;


typedef GSN_STATUS
(*GsnNwif_IPv6Configure_FP_T)(GSN_NWIF_CTX_T *pNwIf,GSN_NWIF_IPv6_CONFIG_T *pUsrIPv6Cfg,
									GSN_NWIF_DHCP_PARAMS_T *pDhcpParams);
extern _RPST_ GsnNwif_IPv6Configure_FP_T GsnNwif_IPv6Configure_FP;


typedef VOID
( *GsnNwIf_DhcpStop_FP_T)(GSN_NWIF_CTX_T *pNwIf);
extern _RPST_ GsnNwIf_DhcpStop_FP_T GsnNwIf_DhcpStop_FP;

typedef VOID 
(*GsnNwIf_DhcpV6Stop_FP_T)(GSN_NWIF_CTX_T *pNwIf);
extern _RPST_ GsnNwIf_DhcpV6Stop_FP_T GsnNwIf_DhcpV6Stop_FP;

typedef GSN_NWIF_RECV_FILTER_FUNC_T
(* GsnNwIf_RecvFilterRegister_FP_T)(GSN_NWIF_CTX_T *pNwIf,
                                           GSN_NWIF_RECV_FILTER_FUNC_T recvFilter);

extern _RPST_ GsnNwIf_RecvFilterRegister_FP_T GsnNwIf_RecvFilterRegister_FP;

typedef BOOL
(*GsnNwIf_IsIPv4Configured_FP_T)(GSN_NWIF_CTX_T *pNwIf);
extern _RPST_ GsnNwIf_IsIPv4Configured_FP_T GsnNwIf_IsIPv4Configured_FP;

typedef BOOL
(*GsnNwIf_IsIPv6Configured_FP_T)(GSN_NWIF_CTX_T *pNwIf);
extern _RPST_ GsnNwIf_IsIPv6Configured_FP_T GsnNwIf_IsIPv6Configured_FP;

typedef VOID
(* GsnNwIf_DhcpLeaseTimeSet_FP_T)(GSN_NWIF_CTX_T *pNwIf,
                                        ULONG64 dhcpLeaseTime);

extern _RPST_ GsnNwIf_DhcpLeaseTimeSet_FP_T GsnNwIf_DhcpLeaseTimeSet_FP;

typedef VOID
(* GsnNwIf_IpConfigGet_FP_T)(GSN_NWIF_CTX_T *pNwIf, GSN_NWIF_IP_CONFIG_T *pIpConfig);

extern _RPST_ GsnNwIf_IpConfigGet_FP_T GsnNwIf_IpConfigGet_FP;
/*
typedef VOID
(* GsnNwIf_StatsGet_FP_T)(GSN_NWIF_CTX_T *pNwIf, GSN_NWIF_STATS_T *pStats);

extern _RPST_ GsnNwIf_StatsGet_FP_T GsnNwIf_StatsGet_FP;
*/
typedef GSN_STATUS
(* GsnNwIf_GratArpSend_FP_T)(GSN_NWIF_CTX_T *pNwIf);

extern _RPST_ GsnNwIf_GratArpSend_FP_T GsnNwIf_GratArpSend_FP;


typedef GSN_NWIF_CTX_T *
(* GsnNwIf_NwIfCtxGet_FP_T)(NX_IP *ipHndl);

extern _RPST_ GsnNwIf_NwIfCtxGet_FP_T GsnNwIf_NwIfCtxGet_FP;

typedef VOID
(* GsnNwIf_TableEntrySet_FP_T)(GSN_NWIF_CTX_T * pNwIf, NX_IP *ipHndl);

extern _RPST_ GsnNwIf_TableEntrySet_FP_T GsnNwIf_TableEntrySet_FP;

typedef VOID
(* GsnNwIf_TableEntryClear_FP_T)(GSN_NWIF_CTX_T * pNwIf, NX_IP *ipHndl);

extern _RPST_ GsnNwIf_TableEntryClear_FP_T GsnNwIf_TableEntryClear_FP;

typedef GSN_STATUS_T
(*GsnNwif_PrivateIPv4Config_FP_T)(GSN_NWIF_CTX_T *pNwIf,GSN_NWIF_IPv4_CONFIG_T *pUsrIPv4Cfg,
									GSN_NWIF_DHCP_PARAMS_T *pDhcpParams);
extern _RPST_ GsnNwif_PrivateIPv4Config_FP_T GsnNwif_PrivateIPv4Config_FP;

typedef GSN_STATUS_T
(*GsnNwif_PrivateIPv6Config_FP_T)(GSN_NWIF_CTX_T *pNwIf,GSN_NWIF_IPv6_CONFIG_T *pUsrIPv6Cfg,
									GSN_NWIF_DHCP_PARAMS_T *pDhcpParams);

extern _RPST_ GsnNwif_PrivateIPv6Config_FP_T GsnNwif_PrivateIPv6Config_FP;


typedef BOOL
(* GsnNwIf_IsDhcpLeaseExpired_FP_T)(ULONG64 dhcpLeaseExpireTime);

extern _RPST_ GsnNwIf_IsDhcpLeaseExpired_FP_T GsnNwIf_IsDhcpLeaseExpired_FP;

typedef VOID 
(* GsnNwif_DhcpStateChangeNotify_FP_T)(NX_DHCP *pDhcpHndl, UINT8 newState, VOID *notifyCtx);

extern _RPST_ GsnNwif_DhcpStateChangeNotify_FP_T GsnNwif_DhcpStateChangeNotify_FP;

typedef GSN_STATUS_T
(* GsnNwIf_DhcpStrat_FP_T)(GSN_NWIF_CTX_T *pNwIf, GSN_NWIF_DHCP_PARAMS_T *pDhcpParams);

extern _RPST_ GsnNwIf_DhcpStrat_FP_T GsnNwIf_DhcpStrat_FP;

typedef VOID  
(*GsnNwif_Dhcpv6StateChangeNotify_FP_T)(NX_DHCPV6 *pDhcpV6Hndl, UINT oldState, UINT newState, VOID *notifCtx);
extern _RPST_ GsnNwif_Dhcpv6StateChangeNotify_FP_T GsnNwif_Dhcpv6StateChangeNotify_FP;


typedef GSN_STATUS_T 
(*GsnNwIf_DhcpV6Strat_FP_T)(GSN_NWIF_CTX_T *pNwIf, GSN_NWIF_DHCP_PARAMS_T *pDhcpParams);
extern _RPST_ GsnNwIf_DhcpV6Strat_FP_T GsnNwIf_DhcpV6Strat_FP;


typedef VOID
(* GsnNwIf_RecvCb_FP_T)(GSN_NWIF_CTX_T *pNwIf, INT32 frameLen, VOID *pFrame);

extern _RPST_ GsnNwIf_RecvCb_FP_T GsnNwIf_RecvCb_FP;

typedef BOOL
(* GsnNwIf_RecvFilter_FP_T)(GSN_NWIF_CTX_T *pNwIf, UINT32 pktLen,
                                 GSN_ETHERNET_FRAME_T *pEthFrame,
                                 BOOL ipConfigured);

extern _RPST_ GsnNwIf_RecvFilter_FP_T GsnNwIf_RecvFilter_FP;

typedef VOID
(* GsnNwIf_DriverEntryFunc_FP_T)(NX_IP_DRIVER *pRequest);

extern _RPST_ GsnNwIf_DriverEntryFunc_FP_T GsnNwIf_DriverEntryFunc_FP;

typedef VOID
(* GsnNwIf_DriverSend_FP_T)(NX_IP_DRIVER *pRequest, GSN_ETH_PROTOCOL_TYPE_T proto, BOOL broadCast);

extern _RPST_ GsnNwIf_DriverSend_FP_T GsnNwIf_DriverSend_FP;

typedef VOID
(* GsnNwIf_SendPktCopyCb_FP_T)(GSN_NWIF_CTX_T *pNwIf, VOID *inBuf, UINT32 inLen, VOID *outBuf);

extern _RPST_ GsnNwIf_SendPktCopyCb_FP_T GsnNwIf_SendPktCopyCb_FP;

typedef GSN_STATUS
(* GsnNwIf_Reinit_FP_T)(GSN_NWIF_CTX_T *pNwIf, GSN_NWIF_REINIT_PARAMS_T *pParams);

extern _RPST_ GsnNwIf_Reinit_FP_T GsnNwIf_Reinit_FP;

typedef GSN_STATUS
(* GsnNwIf_DnsHostByNameGet_FP_T)(GSN_NWIF_CTX_T *pNwIf,UINT8 *pHostName,ULONG *DnsAddress,ULONG timeout);

extern _RPST_ GsnNwIf_DnsHostByNameGet_FP_T GsnNwIf_DnsHostByNameGet_FP;

typedef UINT16 
(* GsnNwIf_U16FieldGet_FP_T)(UINT8 *pPkt);

extern _RPST_ GsnNwIf_U16FieldGet_FP_T GsnNwIf_U16FieldGet_FP;

typedef VOID
(* GsnNwif_RadioConfig_FP_T)(GSN_NWIF_CTX_T *pNwIf, BOOL state);/*State 1= ON, 0 = OFF*/

extern _RPST_ GsnNwif_RadioConfig_FP_T GsnNwif_RadioConfig_FP;

#endif
