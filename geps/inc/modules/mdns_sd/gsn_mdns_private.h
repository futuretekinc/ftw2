/*******************************************************************************
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
* $RCSfile: gsn_mdns_private.h,v $
*
* Description : This file contains mDns-Sd module implementation.
*******************************************************************************/
#ifndef _GSN_MDNS_PRIVATE_H_
#define _GSN_MDNS_PRIVATE_H_
/*******************************************************************************
 * Private definitions
 ******************************************************************************/

/* One-Shot timer removes itself after it expires */
#define GSN_MDNS_TMR_TYPE_ONE_SHOT       	GSN_SOFT_TMR_ONESHOT

/* Periodic timer*/
#define GSN_MDNS_TMR_TYPE_PERIODIC      	GSN_SOFT_TMR_PERIODIC

/* Dns header flag mask */
#define DNS_FLAG_MASK_QR            0x80		/* Query = 0 / Response = 1 */
#define DNS_FLAG_MASK_OPCODE        0x78		/* 4 Bits.  					
														1. QUERY - Standard Query = 0
														2. IQUERY - Inverse Query = 1
														3. STATUS, Server Status Request = 2
														4. Notify = 4
														5. Update = 5.
														6.  Reserved = 6 - 15 */

#define DNS_FLAG_MASK_AA		/* Authoritative Answer No Auth = 0, Is Auth = 1 */
#define DNS_FLAG_MASK_TC		/* Truncated. Not Trunc = 0, Msg Trunc = 1 */
#define DNS_FLAG_MASK_RD		/* Recursion Desired. Not Desired = 0, Desired = 1 */        
#define DNS_FLAG_MASK_RA		/* Recursion Available. not avail = 0, Avail = 1        */
#define DNS_FLAG_MASK_Z										                 
#define DNS_FLAG_MASK_RCODE 	/* Return Code. 4 bits */

/* DNS header flags*/
#define DNS_FLAG_Q          0x00
#define DNS_FLAG_OP_SQ      0x00
#define DNS_FLAG_RESP       0x80
#define DNS_FLAG_AUTH_SERV  0x04

/* DNS Qtype */
#define DNS_QTYPE_A     	0x0001
#define DNS_QTYPE_AAAA		0x001C		/* IPv6 Address Query Type */
#define DNS_QTYPE_PTR   	0x000C
#define DNS_QTYPE_SRV   	0x0021   
#define DNS_QTYPE_ANY   	0x00FF

/* DNS RR types*/
#define DNS_RR_TYPE_A      	0x0001		/* Address Record */
#define DNS_RR_TYPE_AAAA   	0x001C		/* Address Record for IPv6. */
#define DNS_RR_TYPE_PTR    	0x000c		/* Pointer Record */
#define DNS_RR_TYPE_SRV    	0x0021		/* Service Record */
#define DNS_RR_TYPE_TXT    	0x0010		/* Text Record */
#define DNS_RR_TYPE_ANY    	0x00FF		/* All cached records. Returns all records of all types known 
											to the name server.*/

/* DNS CLASS */
#define DNS_CLASS_IN    	0x0001
#define DNS_QU_BIT      	0x8000

/* DNS name compression*/
#define DNS_MSG_COMPRSN_MASK            0xC0
#define DNS_MSG_COMPRSN_OFFSET_MASK     0x3FFF

/* mDns protocol specific */
#define MDNS_CASH_FLUSH_BIT  			0x8000
#define MDNS_QU_BIT  					0x8000

/* mDns Module specific definitions */
#define MAX_UDP_MESAGE_SIZE		1472 /*MTU 1500 - 20(IP Header) - 8 (UDP Header)*/
#define MDNS_RECV_BUFF_SIZE     MAX_UDP_MESAGE_SIZE
#define MDNS_SEND_BUFF_SIZE     1024
#define MDNS_BUFF_TYPE_SMALL	256

#define MDNS_MULTICAST_IP_ADDR  0xE00000FB /*"224.0.0.251"*/
#define MDNS_MULTICAST_PORT     5353

#define MDNS_LABEL_FORMAT_STR   1
#define MDNS_LABEL_FORMAT_DNS   2

#define MDNS_PROBE_MAX_RETRY_CNT    3
#define MDNS_PROBE_INTRVL           250 /* 250 mSec*/
#define MDNS_PROBE_DEFER_INTRVL     1000 /* 1 Sec*/

/*
A Multicast DNS Responder on Ethernet [IEEE.802.3] and similar shared
  multiple access networks SHOULD have the capability of delaying its
  responses by up to 500ms */
#define QUERY_ONESHOT_TIMEOUT   		1000*1 /* 1 Sec*/
#define MDNS_TTL                		0x0000000A /* 10 Sec. */

#define SRV_RR_RDATA_FIXED_LEN       	6
#define GSN_MDNS_IPV6_ADDR_CPY(destPtr, srcPtr)	memcpy((UINT8 *)(destPtr), (const UINT8 *)(srcPtr), 16)


#define GSN_MDNS_SMALL_BUFF_SIZE    256
#define GSN_MDNS_BIG_BUFF_SIZE      1024

typedef enum GSN_MDNS_RR_STATE
{
    RR_STATE_PROBE_INIT,/* This state is used in case separate mDns Task is used*/
    RR_STATE_PROBE_IN_PROGRES,
    RR_STATE_STABLE
}GSN_MDNS_RR_STATE_T;

typedef enum QUERY_STATUS
{
    QUERY_STATUS_INIT,
    QUERY_STATUS_INPROGRESS,
    QUERY_STATUS_DONE
}QUERY_STATUS_T;

typedef enum PROBE_STATUS
{
    PROBE_STATUS_INIT,
    PROBE_STATUS_DEFFERED,
    PROBE_STATUS_INPROGRESS,
    PROBE_STATUS_DONE
}PROBE_STATUS_T;


typedef enum QUERY_TYPE
{
    QUERY_TYPE_NORMAL_QUERY,
    QUERY_TYPE_SD,
    QUERY_TYPE_PROBE,    
}QUERY_TYPE_T;

typedef enum MDNS_SEND_TYPE
{
    MDNS_SEND_MULTICAST=1,
    MDNS_SEND_UNICAST
}MDNS_SEND_TYPE_T;

typedef enum DNS_RR_SECTION
{
    DNS_RR_SECTION_QSTN,
    DNS_RR_SECTION_ANS,
    DNS_RR_SECTION_AUTH,
    DNS_RR_SECTION_ADTNL
}DNS_RR_SECTION_T;

#define ISUPPERCASE(C) (((C)>= 'A' && (C)<= 'Z'))
#define GSN_MDNS_HTONS(x)   ((x)= htons(x))
#define GsnMdns_Bzero(ptr, size)    memset((UINT8 *)ptr, 0, size);

#ifdef MDNS_DEBUG
#define mprintf(...)    S2w_Printf(__VA_ARGS__)
	
extern void mdnsPrintbuff(UINT8 *msg, UINT8 *buff, UINT32 len);

extern void mdnsPrintString(UINT8 *msg, UINT8 *buff);
	
#define markFunEntry(str)   mprintf("\r\n\r\n %s %s\r\n\r\n", str,"ENTRY")
#define markFunExit(str)   mprintf("\r\n\r\n %s %s\r\n\r\n", str,"EXit")
#else

extern  INT32
mprintf(const char *format, ...);
extern void mdnsPrintbuff(UINT8 *msg, UINT8 *buff, UINT32 len);
extern void mdnsPrintString(UINT8 *msg, UINT8 *buff);

#define markFunEntry(str)
#define markFunExit(str)
#endif

#ifdef MDNS_MEM_TRACE
extern VOID *mdns_malloc(UINT32 size, UINT32 line);
extern VOID mdns_free(VOID *ptr, UINT32 line);
	
#define MDNS_MALLOC(size)  	mdns_malloc(size, __LINE__);
#define MDNS_FREE(ptr)      mdns_free(ptr, __LINE__);
#else  
#define MDNS_MALLOC(size)  	MALLOC(size);
#define MDNS_FREE(ptr)      FREE(ptr);
#endif


UINT32
GsnMdns_StrToLblLen(INT8 *str);

UINT16
GsnMdns_DnsNameLenGet(UINT8 *name);

BOOL
GsnMdns_DnsNameCmp(UINT8 *name1, UINT8 *name2);

UINT16
GsnMdns_DnsNameCpy(UINT8 *dest, UINT8 *src);

VOID
GsnMdns_DnsFormtSrvcNameCreate(UINT8 *inBuf, UINT8 *srvcName, UINT8 *srvcSubType,
												UINT8 *srvcType, UINT8 *srvcProto, UINT8 *domain, 
												UINT8 format);
VOID
GsnMdns_DnsNameUpdate(UINT8 *dstName, UINT8 *srcName);

UINT8 *
GsnMdns_DnsNameSkip(UINT8 *pPkt);

UINT8 *
GsnMdns_DnsNameGet(UINT8 *ptr, UINT8 *pPktStart, UINT8 *pktEnd, UINT8 *name);

UINT16
GsnMdns_LabelCat(UINT8 *lb1, UINT8 *lb2, UINT8 *buff);

UINT8 *
GsnMdns_LabelUpdate(UINT8 *label, UINT8 *subLabel, UINT8 format);

BOOL
GsnMdns_LabelCmp(UINT8 *label1, UINT8 *label2);

UINT8 *
GsnMdns_LableSkip(UINT8 *name);

UINT8 *
GsnMdns_LabelGet(UINT8 *pDnsName, UINT8 *label);

UINT8*
GsnMdns_MemCopy(UINT8 *dest, UINT8 *src, UINT32 len);

VOID
GsnMdns_QustnListAdd(GSN_MDNS_T *pMdns, QUESTION_T **questList, QUESTION_T *qstn);

VOID
GsnMdns_QustnListDel(GSN_MDNS_T *pMdns, QUESTION_T **questList, QUESTION_T *outQ);

VOID
GsnMdns_QustnListClear(GSN_MDNS_T *pMdns, QUESTION_T **questList);

QUESTION_T *
GsnMdns_QustnListSearch(QUESTION_T *questList, UINT8 *pName);

VOID
GsnMdns_RrListAdd(GSN_MDNS_T *pMdns, RR_T **listHead, RR_T *entry);

VOID
GsnMdns_RrListDel(GSN_MDNS_T *pMdns,RR_T **listHead, RR_T *entry);

VOID
GsnMdns_RrListClear(GSN_MDNS_T *pMdns, RR_T **listHead);

BOOL
GsnMdns_IsRRpresent(RR_T *listHead, RR_T *entry);

RR_T *
GsnMdns_RrNameSearch(RR_T *listHead, UINT8 *name, UINT16 rrType);

RR_T *
GsnMdns_RrTypeSearch(RR_T *listHead, UINT32 rrType);

UINT16
GsnMdns_ResourceRecordCreate(UINT8 *buff, UINT8 *bufEnd, UINT8 *name, UINT16 rrType, 
 							UINT16 rrClass, UINT32 rrTTL, UINT16 rdLen, 
 							UINT8 *rData);
UINT16
GsnMdns_QustnSectionCreate(UINT8 *buff, UINT8 *bufEnd, UINT8 *domainName, UINT16 qType, UINT16 qClass,
										UINT8 unicastResp);

UINT8 *
GsnMdns_ResponseCreate(GSN_MDNS_T *pMdns, QUESTION_T *questList, UINT32 *respLen,
						UINT32 *sendType, UINT32 *sendScope);
VOID 
GsnMdns_QueryTmrCb(VOID* context, GSN_SOFT_TMR_HANDLE_T  timerHandle);

VOID 
GsnMdns_QueryTimeoutProcess(VOID* context, GSN_SOFT_TMR_HANDLE_T	timerHandle);

UINT8 *
GsnMdns_QueryCreate(GSN_MDNS_T *pMdns, UINT32 *sendLen);

UINT8 *
GsnMdns_ProbeCreate(GSN_MDNS_T *pMdns, QUESTION_T *qustn, INT32 *sendLen);

QUESTION_T *
GsnMdns_QustnCreate(UINT8 *pName, UINT16 qType);

GSN_STATUS
GsnMdns_QueryListAdd(GSN_MDNS_T *pMdns,UINT8 *name, UINT16 qType, UINT8 scope,
GSN_MDNS_SD_CB_T cb, VOID *cbCtx);

GSN_STATUS
GsnMdns_ProbeListAdd(GSN_MDNS_T *pMdns,RR_T *pRr);

QUESTION_T *
GsnMdns_ProbeEntryGet(GSN_MDNS_T *pMdns, RR_T *pSuportdRR);

VOID
GsnMdns_ProbeEntryRemove(GSN_MDNS_T *pMdns, RR_T *pSuportdRR);


VOID					 
GsnMdns_DeferredProbeTmrCb( VOID* context, GSN_SOFT_TMR_HANDLE_T	timerHandle );

VOID 				  
GsnMdns_DeferredProbeTimeoutProcess(VOID* context, 
												GSN_SOFT_TMR_HANDLE_T  timerHandle);

VOID 
GsnMdns_ProbeTmrCb( VOID* context, GSN_SOFT_TMR_HANDLE_T	timerHandle );

VOID 
GsnMdns_ProbeTimeoutProcess( VOID* context, GSN_SOFT_TMR_HANDLE_T  timerHandle );

GSN_STATUS
GsnMdns_Probe(GSN_MDNS_T *pMdns, RR_T *probeRr, QUESTION_T *qustn);

VOID
GsnMdns_ParseQuery(GSN_MDNS_T *pMdns, UINT8 *pkt, UINT32 pktSize);

VOID
GsnMdns_NameIncrement(UINT8 *pName);

BOOL
GsnMdns_IsSubTypePresent(UINT8 *dn);

GSN_STATUS
GsnMdns_ProcessResponse(GSN_MDNS_T *pMdns);

VOID
GsnMdns_HtonsRrComnPart(DNS_RR_COMMON_PART_T *rrComnPart);

UINT8 *
GsnMdns_RespRrGet(GSN_MDNS_T *pMdns, UINT8 *ptr, UINT8 *pkt, UINT8 *pktEnd,
UINT8 *pName, UINT8 rrSection);

GSN_STATUS
GsnMdns_ParseResponse(GSN_MDNS_T *pMdns, UINT8 *pkt, UINT32 pktSize);

GSN_STATUS
GsnMdns_ParsePacket(GSN_MDNS_T *pMdns, UINT8 *pkt, UINT32 pktSize, UINT8 nwType);

VOID
GsnMdns_GoodbyPktSend(GSN_MDNS_T *pMdns, RR_T *pRr);

VOID
GsnMdns_RsrcRecordDeregister(GSN_MDNS_T *pMdns, UINT8 *pName);

GSN_STATUS
GsnMdns_Query(GSN_MDNS_T *pMdns, UINT8 *pName, UINT16 qType, UINT8 scope,
					GSN_MDNS_SD_CB_T cb, VOID *cbCtx);

GSN_STATUS
GsnMdns_SendMulticast(GSN_MDNS_T *pMdns, UINT8 *buff, INT32 len, UINT8 scope);

GSN_STATUS
GsnMdns_SendUnicast(GSN_MDNS_T *pMdns, UINT8 *buff, INT32 len, UINT8 scope, UINT8 nwType);

VOID
GsnMdns_SendMessage(GSN_MDNS_T *pMdns, UINT8 *buff, INT32 len, UINT8 sendType, 
								UINT8 scope, UINT8 nwType);
VOID
GsnMdns_SocketRecvCb(INT sockId, NX_BSD_CB_EVENT_TYPE_T event, void* cbCtx);

VOID
GsnMdns_SocketRecvProcess(VOID *cbCtx, UINT sockId, UINT32 eventFlg);

VOID
GsnMdns_TaskNotify(GSN_MDNS_T *pMdns, UINT32 msgId, UINT32 msgInfo_1, UINT32 msgInfo_2,
							UINT32 msgInfo_3);
VOID
GsnMdns_PrivateDeInit(GSN_MDNS_T *pMdns);

#endif/*_GSN_MDNS_PRIVATE_H_*/
