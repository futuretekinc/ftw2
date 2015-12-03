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
* $RCSfile: gsn_mdns_private_fpt.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/
#ifndef _GSN_MDNS_PRIVATE_FPT_H_
#define _GSN_MDNS_PRIVATE_FPT_H_

typedef UINT32
(*GsnMdns_StrToLblLen_FP_T) (INT8 *str);
extern _RPST_ GsnMdns_StrToLblLen_FP_T GsnMdns_StrToLblLen_FP;

typedef UINT16
(*GsnMdns_DnsNameLenGet_FP_T)(UINT8 *name);
extern _RPST_ GsnMdns_DnsNameLenGet_FP_T GsnMdns_DnsNameLenGet_FP;

typedef BOOL
(* GsnMdns_DnsNameCmp_FP_T) (UINT8 *name1, UINT8 *name2);
extern _RPST_ GsnMdns_DnsNameCmp_FP_T GsnMdns_DnsNameCmp_FP;

typedef UINT16
(* GsnMdns_DnsNameCpy_FP_T) (UINT8 *dest, UINT8 *src);
extern _RPST_ GsnMdns_DnsNameCpy_FP_T GsnMdns_DnsNameCpy_FP;

typedef VOID
(* GsnMdns_DnsFormtSrvcNameCreate_FP_T) (UINT8 *inBuf, UINT8 *srvcName, UINT8 *srvcSubType,
                      							UINT8 *srvcType, UINT8 *srvcProto, UINT8 *domain, 
                      							UINT8 format);
extern _RPST_ GsnMdns_DnsFormtSrvcNameCreate_FP_T GsnMdns_DnsFormtSrvcNameCreate_FP;

typedef VOID
(* GsnMdns_DnsNameUpdate_FP_T)(UINT8 *dstName, UINT8 *srcName);
extern _RPST_ GsnMdns_DnsNameUpdate_FP_T GsnMdns_DnsNameUpdate_FP;

typedef UINT8 *
(* GsnMdns_DnsNameSkip_FP_T)(UINT8 *pPkt);
extern _RPST_ GsnMdns_DnsNameSkip_FP_T  GsnMdns_DnsNameSkip_FP;

typedef UINT8 *
(*GsnMdns_DnsNameGet_FP_T)(UINT8 *ptr, UINT8 *pPktStart, UINT8 *pktEnd, UINT8 *name);
extern _RPST_ GsnMdns_DnsNameGet_FP_T GsnMdns_DnsNameGet_FP;

typedef UINT16
(* GsnMdns_LabelCat_FP_T)(UINT8 *lb1, UINT8 *lb2, UINT8 *buff);
extern _RPST_ GsnMdns_LabelCat_FP_T GsnMdns_LabelCat_FP;

typedef UINT8 *
(* GsnMdns_LabelUpdate_FP_T)(UINT8 *label, UINT8 *subLabel, UINT8 format);
extern _RPST_ GsnMdns_LabelUpdate_FP_T GsnMdns_LabelUpdate_FP;

typedef BOOL
(* GsnMdns_LabelCmp_FP_T)(UINT8 *label1, UINT8 *label2);
extern _RPST_ GsnMdns_LabelCmp_FP_T GsnMdns_LabelCmp_FP;

typedef UINT8 *
(* GsnMdns_LableSkip_FP_T)(UINT8 *name);
extern _RPST_ GsnMdns_LableSkip_FP_T GsnMdns_LableSkip_FP;

typedef UINT8 *
(*GsnMdns_LabelGet_FP_T)(UINT8 *pDnsName, UINT8 *label);
extern _RPST_ GsnMdns_LabelGet_FP_T GsnMdns_LabelGet_FP;

typedef UINT8*
(* GsnMdns_MemCopy_FP_T)(UINT8 *dest, UINT8 *src, UINT32 len);
extern _RPST_ GsnMdns_MemCopy_FP_T GsnMdns_MemCopy_FP;

typedef VOID
(* GsnMdns_QustnListAdd_FP_T)(GSN_MDNS_T *pMdns, QUESTION_T **questList, QUESTION_T *qstn);
extern _RPST_ GsnMdns_QustnListAdd_FP_T GsnMdns_QustnListAdd_FP;

typedef VOID
(* GsnMdns_QustnListDel_FP_T)(GSN_MDNS_T *pMdns, QUESTION_T **questList, QUESTION_T *outQ);
extern _RPST_ GsnMdns_QustnListDel_FP_T GsnMdns_QustnListDel_FP;

typedef VOID
(* GsnMdns_QustnListClear_FP_T)(GSN_MDNS_T *pMdns, QUESTION_T **questList);;
extern _RPST_ GsnMdns_QustnListClear_FP_T GsnMdns_QustnListClear_FP;

typedef QUESTION_T *
(* GsnMdns_QustnListSearch_FP_T)(QUESTION_T *questList, UINT8 *pName);
extern _RPST_ GsnMdns_QustnListSearch_FP_T GsnMdns_QustnListSearch_FP;

typedef VOID
(*GsnMdns_RrListAdd_FP_T)(GSN_MDNS_T *pMdns, RR_T **listHead, RR_T *entry);
extern _RPST_ GsnMdns_RrListAdd_FP_T GsnMdns_RrListAdd_FP;

typedef VOID
(*GsnMdns_RrListDel_FP_T)(GSN_MDNS_T *pMdns,RR_T **listHead, RR_T *entry);
extern _RPST_ GsnMdns_RrListDel_FP_T GsnMdns_RrListDel_FP;

typedef VOID
(* GsnMdns_RrListClear_FP_T)(GSN_MDNS_T *pMdns, RR_T **listHead);
extern _RPST_ GsnMdns_RrListClear_FP_T GsnMdns_RrListClear_FP;

typedef BOOL
(* GsnMdns_IsRRpresent_FP_T)(RR_T *listHead, RR_T *entry);
extern _RPST_ GsnMdns_IsRRpresent_FP_T GsnMdns_IsRRpresent_FP;

typedef RR_T *
(* GsnMdns_RrNameSearch_FP_T)(RR_T *listHead, UINT8 *name, UINT16 rrType);
extern _RPST_ GsnMdns_RrNameSearch_FP_T GsnMdns_RrNameSearch_FP;

typedef RR_T *
(* GsnMdns_RrTypeSearch_FP_T)(RR_T *listHead, UINT32 rrType);
extern _RPST_ GsnMdns_RrTypeSearch_FP_T GsnMdns_RrTypeSearch_FP;

typedef UINT16
(* GsnMdns_ResourceRecordCreate_FP_T)(UINT8 *buff, UINT8 *bufEnd, UINT8 *name, UINT16 rrType, 
                             UINT16 rrClass, UINT32 rrTTL, UINT16 rdLen, 
                             UINT8 *rData);
extern _RPST_ GsnMdns_ResourceRecordCreate_FP_T GsnMdns_ResourceRecordCreate_FP;

typedef UINT16
(* GsnMdns_QustnSectionCreate_FP_T)(UINT8 *buff, UINT8 *bufEnd, UINT8 *domainName, UINT16 qType, UINT16 qClass,
                          UINT8 unicastResp);
extern _RPST_ GsnMdns_QustnSectionCreate_FP_T GsnMdns_QustnSectionCreate_FP;

typedef UINT8 *
(* GsnMdns_ResponseCreate_FP_T)(GSN_MDNS_T *pMdns, QUESTION_T *questList, UINT32 *respLen, UINT32 *sendType, UINT32 *sendScope);
extern _RPST_ GsnMdns_ResponseCreate_FP_T GsnMdns_ResponseCreate_FP;

typedef VOID 
(* GsnMdns_QueryTmrCb_FP_T)(VOID* context, GSN_SOFT_TMR_HANDLE_T  timerHandle);
extern _RPST_ GsnMdns_QueryTmrCb_FP_T  GsnMdns_QueryTmrCb_FP;

typedef VOID 
(* GsnMdns_QueryTimeoutProcess_FP_T)(VOID* context, GSN_SOFT_TMR_HANDLE_T  timerHandle);
extern _RPST_ GsnMdns_QueryTimeoutProcess_FP_T GsnMdns_QueryTimeoutProcess_FP;

typedef UINT8 *
(* GsnMdns_QueryCreate_FP_T)(GSN_MDNS_T *pMdns, UINT32 *sendLen);
extern _RPST_ GsnMdns_QueryCreate_FP_T GsnMdns_QueryCreate_FP;

typedef UINT8 *
(* GsnMdns_ProbeCreate_FP_T)(GSN_MDNS_T *pMdns, QUESTION_T *qustn, INT32 *sendLen);
extern _RPST_ GsnMdns_ProbeCreate_FP_T GsnMdns_ProbeCreate_FP;

typedef QUESTION_T *
(* GsnMdns_QustnCreate_FP_T)(UINT8 *pName, UINT16 qType);
extern _RPST_ GsnMdns_QustnCreate_FP_T GsnMdns_QustnCreate_FP;

typedef GSN_STATUS
(* GsnMdns_QueryListAdd_FP_T)(GSN_MDNS_T *pMdns,UINT8 *name, UINT16 qType, UINT8 scope,
                     			GSN_MDNS_SD_CB_T cb, VOID *cbCtx);
extern _RPST_ GsnMdns_QueryListAdd_FP_T GsnMdns_QueryListAdd_FP;

typedef GSN_STATUS
(* GsnMdns_ProbeListAdd_FP_T)(GSN_MDNS_T *pMdns,RR_T *pRr);
extern _RPST_ GsnMdns_ProbeListAdd_FP_T GsnMdns_ProbeListAdd_FP;

typedef QUESTION_T *
(* GsnMdns_ProbeEntryGet_FP_T)(GSN_MDNS_T *pMdns, RR_T *pSuportdRR);
extern _RPST_ GsnMdns_ProbeEntryGet_FP_T GsnMdns_ProbeEntryGet_FP;

typedef VOID
(* GsnMdns_ProbeEntryRemove_FP_T)(GSN_MDNS_T *pMdns, RR_T *pSuportdRR);
extern _RPST_ GsnMdns_ProbeEntryRemove_FP_T GsnMdns_ProbeEntryRemove_FP;

typedef VOID                   
(* GsnMdns_DeferredProbeTmrCb_FP_T)( VOID* context, GSN_SOFT_TMR_HANDLE_T  timerHandle );
extern _RPST_ GsnMdns_DeferredProbeTmrCb_FP_T GsnMdns_DeferredProbeTmrCb_FP;

typedef VOID                   
(* GsnMdns_DeferredProbeTimeoutProcess_FP_T)(VOID* context, GSN_SOFT_TMR_HANDLE_T  timerHandle);
extern _RPST_ GsnMdns_DeferredProbeTimeoutProcess_FP_T GsnMdns_DeferredProbeTimeoutProcess_FP;

typedef VOID 
(* GsnMdns_ProbeTmrCb_FP_T)( VOID* context, GSN_SOFT_TMR_HANDLE_T  timerHandle );
extern _RPST_ GsnMdns_ProbeTmrCb_FP_T GsnMdns_ProbeTmrCb_FP;

typedef VOID 
(* GsnMdns_ProbeTimeoutProcess_FP_T)( VOID* context, GSN_SOFT_TMR_HANDLE_T  timerHandle );
extern _RPST_ GsnMdns_ProbeTimeoutProcess_FP_T GsnMdns_ProbeTimeoutProcess_FP;

 typedef GSN_STATUS
(* GsnMdns_Probe_FP_T)(GSN_MDNS_T *pMdns, RR_T *probeRr, QUESTION_T *qustn);
extern _RPST_ GsnMdns_Probe_FP_T GsnMdns_Probe_FP;

typedef VOID
(* GsnMdns_ParseQuery_FP_T)(GSN_MDNS_T *pMdns, UINT8 *pkt, UINT32 pktSize);
extern _RPST_ GsnMdns_ParseQuery_FP_T GsnMdns_ParseQuery_FP;

typedef VOID
(* GsnMdns_NameIncrement_FP_T)(UINT8 *pName);
extern _RPST_ GsnMdns_NameIncrement_FP_T GsnMdns_NameIncrement_FP; 

typedef BOOL
(* GsnMdns_IsSubTypePresent_FP_T)(UINT8 *dn);
extern _RPST_ GsnMdns_IsSubTypePresent_FP_T GsnMdns_IsSubTypePresent_FP;

typedef GSN_STATUS
(* GsnMdns_ProcessResponse_FP_T)(GSN_MDNS_T *pMdns);
extern _RPST_ GsnMdns_ProcessResponse_FP_T GsnMdns_ProcessResponse_FP;

typedef VOID
(* GsnMdns_HtonsRrComnPart_FP_T)(DNS_RR_COMMON_PART_T *rrComnPart);
extern _RPST_  GsnMdns_HtonsRrComnPart_FP_T GsnMdns_HtonsRrComnPart_FP;

typedef UINT8 *
(* GsnMdns_RespRrGet_FP_T)(GSN_MDNS_T *pMdns, UINT8 *ptr, UINT8 *pkt, UINT8 *pktEnd,
                  UINT8 *pName, UINT8 rrSection);
extern _RPST_ GsnMdns_RespRrGet_FP_T GsnMdns_RespRrGet_FP;

typedef GSN_STATUS
(* GsnMdns_ParseResponse_FP_T)(GSN_MDNS_T *pMdns, UINT8 *pkt, UINT32 pktSize);
extern _RPST_ GsnMdns_ParseResponse_FP_T GsnMdns_ParseResponse_FP;

 typedef GSN_STATUS
(* GsnMdns_ParsePacket_FP_T)(GSN_MDNS_T *pMdns, UINT8 *pkt, UINT32 pktSize, UINT8 nwType);
extern _RPST_ GsnMdns_ParsePacket_FP_T GsnMdns_ParsePacket_FP;

typedef VOID
(* GsnMdns_GoodbyPktSend_FP_T)(GSN_MDNS_T *pMdns, RR_T *pRr);
extern _RPST_ GsnMdns_GoodbyPktSend_FP_T GsnMdns_GoodbyPktSend_FP;

typedef VOID
(* GsnMdns_RsrcRecordDeregister_FP_T)(GSN_MDNS_T *pMdns, UINT8 *pName);
extern _RPST_ GsnMdns_RsrcRecordDeregister_FP_T GsnMdns_RsrcRecordDeregister_FP;

typedef GSN_STATUS
(* GsnMdns_Query_FP_T)(GSN_MDNS_T *pMdns, UINT8 *pName, UINT16 qType, UINT8 scope,
              		  GSN_MDNS_SD_CB_T cb, VOID *cbCtx);
extern _RPST_ GsnMdns_Query_FP_T GsnMdns_Query_FP;

typedef GSN_STATUS
(* GsnMdns_SendMulticast_FP_T)(GSN_MDNS_T *pMdns, UINT8 *buff, INT32 len, UINT8 scope);
extern _RPST_ GsnMdns_SendMulticast_FP_T GsnMdns_SendMulticast_FP;

typedef GSN_STATUS
(* GsnMdns_SendUnicast_FP_T)(GSN_MDNS_T *pMdns, UINT8 *buff, INT32 len, UINT8 scope, UINT8 nwType);
extern _RPST_ GsnMdns_SendUnicast_FP_T GsnMdns_SendUnicast_FP;


typedef VOID
(* GsnMdns_SendMessage_FP_T)(GSN_MDNS_T *pMdns, UINT8 *buff, INT32 len, UINT8 sendType, 
								UINT8 scope, UINT8 nwType);
extern _RPST_ GsnMdns_SendMessage_FP_T GsnMdns_SendMessage_FP;

typedef VOID
(* GsnMdns_SocketRecvCb_FP_T)(INT sockId, NX_BSD_CB_EVENT_TYPE_T event, void* cbCtx);
extern _RPST_ GsnMdns_SocketRecvCb_FP_T GsnMdns_SocketRecvCb_FP;

typedef VOID
(* GsnMdns_SocketRecvProcess_FP_T)(VOID *cbCtx, UINT sockId, UINT32 eventFlg);
extern _RPST_ GsnMdns_SocketRecvProcess_FP_T GsnMdns_SocketRecvProcess_FP;

typedef VOID
(* GsnMdns_TaskNotify_FP_T)(GSN_MDNS_T *pMdns, UINT32 msgId, UINT32 msgInfo_1, UINT32 msgInfo_2,
							UINT32 msgInfo_3);
extern _RPST_ GsnMdns_TaskNotify_FP_T GsnMdns_TaskNotify_FP;

typedef VOID
(* GsnMdns_PrivateDeInit_FP_T)(GSN_MDNS_T *pMdns);
extern _RPST_ GsnMdns_PrivateDeInit_FP_T GsnMdns_PrivateDeInit_FP;

#endif/*_GSN_MDNS_PRIVATE_FPT_H_*/