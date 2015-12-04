/******************************************************************************
*
*               COPYRIGHT (c) 2008-2010 GainSpan Corporation
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
* $RCSfile: s2w_net.h,v $
*
* Description : This file defines network related function declarations.
*****************************************************************************/

#ifndef FTW_NET_H
#define FTW_NET_H


#define GH_SEM GSN_OSAL_SEM_T

#include "gsn_includes.h"
#include "hal/s2w_os_specific.h"
#include "hal/s2w_types.h"
#include "modules/ssl/gsn_ssl.h"
#include "modules/coap/gsn_coap.h"
#ifdef FTW_GSLINK_XML
#include "modules/xml_string_parser/gsn_xml_string_parser.h"
#endif
#define INVALID_CID     0xff
#define MAX_CID_RANGE   16
#define CID_NCLOSE 0
#define CID_ASAPCLOSE 1
#define CID_NOTINUSE  -1

//#define GSN_HTTP_METHOD_GETRESP 	2
//#define  GSN_HTTP_METHOD_POSTRESP   4 
#define HTTP_STATIC_HDR_COUNT 3

/* Internal representation of connections
 */
#ifdef FTW_GSLINK
typedef struct FTW_HTTPD_CONTEXT
{
	UINT32 httpdBufferLenUsed;	 /*Httpd buffer len */				
	UINT32 httpdMaxBufferSize;	
	INT8 * httpdBuffer;		 /*Httpd buffer pointer */	
	UINT8 moreData;
	UINT8 methodLineReceived;
	GH_SEM s2wGsLinkemID;
	GH_SEM httpdSendSem;
	UINT32 reqBodyLen;
	UINT8 method;
#ifdef FTW_HTTP_CUSTOM_SUPPORT
    UINT8    statusline;
    UINT32   appheadercount;
    UINT32   headercount;
    UINT32   statuscode;
    UINT8   *respphrase;
    UINT32   respphraselen;
    UINT8  **httphdrvalptrptr;
    UINT8  **httphdrnameptrptr;
    ttHttpUserHeaderType *httphdrtypeptr;
    UINT32   httpdHdrsSent;
#endif


}FTW_HTTPD_CONTEXT_T;
#endif

#define ADDR_TYPE_IPv4  0x00
#define ADDR_TYPE_IPv6  0x01

/* Definitions for conType of FTW_CID_T
 */
#define UDP 1
#define TCP 2


#ifdef FTW_THROUGHPUT_TEST
typedef struct FTW_TPSTATS
{
	UINT32 txErr;
	UINT32 rxErr;
	UINT32 udpNxtSeqNo;
	ULONG64 bytesReceived;
	UINT32 packetsReceived;
	GSN_SYSTEM_TIME_T startTime;
	GSN_SYSTEM_TIME_T totalTime;
	GSN_SYSTEM_TIME_T lastPktSndTime;
	UINT32 less1MsCnt;
	UINT32 more1MsCnt;
	UINT32 more2MsCnt;
	UINT32 more3MsCnt;
	UINT32 more5MsCnt;
	UINT32 more10MsCnt;
	UINT32 more20MsCnt;
}FTW_TPSTATS_T;
#endif
typedef struct FTW_CID
{
    UINT8 conType;   /** Type of connection */
    UINT8 conMode;   /** Connection mode */
    UINT16 localPort;
    UINT16 remotePort;
    UINT8 remoteIp[4];
    UINT8 remoteIpv6[16];
    UINT8 socketType;
    UINT8 addrType;  /* IPv4 or IPv6   */
    INT32   sd;         /** Socket descriptor */
	UINT8 maxConn;
	UINT8 clientConCount;
    struct tlsv1_client *tcpTLSConn;
    union{
        GSN_SSL_CONN_T *sslConn;
        GSN_SSL_SERVER_CONN_T *sslServer;
        VOID *pServerCred;
    }ssl;
    UINT8 sslflag;
	UINT8 sslRemoteCliConctng;
	UINT8 serverCid;
    UINT8 httpflag;
    UINT8 allocatedTo;	
#ifdef FTW_HTTPC_SUPPORT
    FTW_HTTP_DATA_T *pHttpData;
#endif  
    GSN_OSAL_SEM_T s2wUserCloseInProgress;
    FTW_TIMER_T s2wUserCloseTimer;
    UINT8 s2wUsrCloseFlag;
    UINT8 s2wSockDataPending;
	#ifdef FTW_GSLINK
	FTW_HTTPD_CONTEXT_T httpdCtx;	
	#ifdef FTW_GSLINK_XML
	GSNXMLSTR_PARSER_CTX_T	*xmlParserCtx;
	#endif
	#endif
	GSN_OSAL_SEM_T s2wUserOpenInProgress;
	VOID *pConnOpenParams;
	INT32 openStatus;
	UINT8 openType;
	//GSN_OSAL_SEM_T s2wSslRecvInProgress;
	VOID *pSslRecvParams;
	INT32 recvStatus;
#ifdef FTW_THROUGHPUT_TEST	
	UINT8 testMode; 	
	UINT8 tpTestInProgress;		
	UINT32 iteration;		
	ULONG64 bytesToReceive;	
	FTW_TPSTATS_T stats;
#endif		
	UINT8 s2wCidCloseInProgress;
#ifdef FTW_COAP_SUPPORT
	GSN_COAP_CONTEXT_T * coapContext;
	GSN_COAP_CONN_PARAMS_T *coapConnParams;
#endif
} FTW_CID_T;

#if defined(FTW_SSL_CLIENT_SUPPORT) || defined(FTW_SSL_SERVER_SUPPORT)


typedef struct FTW_SSL_CONF
{
	UINT32 dnsBufferLen;
	unsigned char  *dnsNameBuf;
}FTW_SSL_CONF_T;
#endif
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief s2w Network initialize function
 *    This function create the network recv task and create queue for that
      task.
 * @retval VOID - None.
 ******************************************************************/
VOID AppS2wHal_NetInit(VOID);

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief s2w network cid status get function.
 *    This function returns the status of the socket corresponding to
 *    the cid.
 * @param cid - IN the cid number
 * @retval TRUE  - the socket opened for that cid.
 * @retval FALSE - the socket not open for that cid.
 ******************************************************************/
UINT8 AppS2wHal_NetIsCidOpen(UINT8 cid);

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w udp client open function.
 *    This function opens a new udp client socket and store the socket info
 *    into the corresponding Cid list and registers any receive events on this
 *    socket with network stack.
 * @param peerData - IN the address of the data structure contain the udp server
 *                      info.
 *.@param cidNo    - IN the address to which the cid number to be stored.
 *.@param srcPort  - IN the source port to which the the udp client socket
 *                     to be bind.
 * @retval FTW_SUCCESS     - operation successfull.
 * @retval FTW_SOCKFAILURE - operation failed
 * @retval FTW_ENCID       - operation failed- no valid cid.
 ******************************************************************/
UINT8 AppS2wHal_NetUdpClient(FTW_NETDATA_T *peerData, UINT8 *cidp,UINT16 srcPort);

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w tcp client open function.
 *    This function opens a new tcp client socket and store the socket info
 *    into the corresponding Cid list and registers any receive events on this
 *    socket with network stack.
 *    This fuction tries to connect to the remote server.
 * @param peerData - IN the address of the data structure contain the tcp server
 *                      info.
 *.@param cidNo    - IN the address to which the cid number to be stored.
 * @retval FTW_SUCCESS     - operation successfull.
 * @retval FTW_SOCKFAILURE - operation failed
 * @retval FTW_ENCID       - operation failed- no valid cid
 ******************************************************************/
UINT8 AppS2wHal_NetTcpClient(FTW_NETDATA_T *peerData, UINT8 *cidp);

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w udp server open function.
 *    This function opens a new udp server socket and store the socket info
 *    into the corresponding Cid list and registers any receive events on this
 *    socket with network stack.
 * @param serverData - IN the address of the data structure contain the udp
 *                     server info.
 *.@param cidNo      - IN the address to which the cid number to be stored.
 * @retval FTW_SUCCESS     - operation successfull.
 * @retval FTW_SOCKFAILURE - operation failed
 * @retval FTW_ENCID       - operation failed- no valid cid
 ******************************************************************/
UINT8 AppS2wHal_NetUdpServer(FTW_NETDATA_T *serverData, UINT8 *cidp);

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w tcp server open function.
 *    This function opens a new tcp server socket and store the socket info
 *    into the corresponding Cid list and registers any receive events on this
 *    socket with network stack.
 * @param serverData - IN the address of the data structure contain the tcp
 *                     server info.
 *.@param cidNo      - IN the address to which the cid number to be stored.
 * @retval FTW_SUCCESS     - operation successfull.
 * @retval FTW_SOCKFAILURE - operation failed
 * @retval FTW_ENCID       - operation failed- no valid cid
 ******************************************************************/
UINT8 AppS2wHal_NetTcpServer(FTW_NETDATA_T *serverData, UINT8 *cidp);


#ifdef FTW_IPv6_SUPPORT

UINT8 AppS2wHal_NetUdpClientv6(FTW_NETDATA_T *remoteServerData, UINT8 *cidNo, UINT16 srcPort);

UINT8 AppS2wHal_NetUdpServerv6(FTW_NETDATA_T *serverData, UINT8 *cidNo);

UINT8 AppS2wHal_NetTcpClientv6(FTW_NETDATA_T *remoteServerData, UINT8 *cidNo);

UINT8 AppS2wHal_NetTcpServerv6(FTW_NETDATA_T *serverData, UINT8 *cidNo);



#endif //FTW_IPv6_SUPPORT



/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w socket close function.
 *    This function close the particular tcp/udp connection specified by cid no.
 *.@param cidNo      - IN the cid number corresponding to the socket to be closed.
 * @retval FTW_SUCCESS     - operation successfull.
 * @retval FTW_FAILURE     - operation failed
 * @retval FTW_EBADCID     - operation failed- cid passed is not valid.
 ******************************************************************/
UINT8 AppS2wHal_NetClose(UINT8 cid);

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w all socket close function.
 *    This function close all tcp/udp connection established in s2w.
 * @retval FTW_SUCCESS     - operation successfull.
 * @retval FTW_FAILURE     - operation failed
 ******************************************************************/
UINT8 AppS2wHal_NetCloseAll(UINT8 flag);

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w udp/tcp tx function
 *    This function send the data to the remote machine specified. This
 *    fuction use either tcp or udp as the protocol type.
 * @param cid      - IN the cid number corresponding to the socket connection.
 * @param destAddr - IN the socket structure for remote machine.
 * @param destPort - IN the remote port.
 * @param buf      - IN the data pointer.
 *.@param len      - IN the length of the buf to send.
 * @retval FTW_SUCCESS           - operation successfull.
 * @retval FTW_ENCID/FTW_EBADCID - operation failed-no valid cid
 * @@retval FTW_FAILURE          - operation failed.
 ******************************************************************/
UINT8 AppS2wHal_NetTx(UINT8 cid, UINT8 *destAddr, UINT16 destPort,
                 VOID *buf, UINT32 len);

/**
 ************************************************************************
 * @ingroup S2w-Application.
 * @brief Receive data from a network connection.
 * @param cid - IN connection identifier on which the data is received.
 * @param buf - IN Pointer to data buffer.
 * @param len - IN Total number of bytes.
 * @param ip  - IN IP address of the client from which the data was received
 *                    (only for UDP servers)
 * @param port- IN Port of the client from which the data was received (only
 *                 for UDP servers)
 * @retval VOID - none.
 ************************************************************************/

VOID AppS2wProcess_NetRx(UINT8 cid, void *buf, UINT32 len, UINT8 *ip, UINT16 port);

/**
 ************************************************************************
 * @ingroup S2w-Application
 * @brief Accept a new connection for a TCP server
 * @param serverCid - IN connection identifier of the server
 * @param newCid    - IN connection identifier of the new connection
 * @param ip        - IN IP address (only for new connection notification)
 * @param port      - IN Port (only for new connection notification)
 * @return FTW_SUCCESS on success.  If any other status, the connection must be
 *                                   closed.
 ************************************************************************/
UINT8 
AppS2wProcess_NetAccept(UINT8 server_cid, UINT8 new_cid, UINT8 *ip, UINT16 port);

PUBLIC UINT8 *
AppS2wSslCertificateGet(char *ptr);

PUBLIC UINT8
AppS2wHal_HttpClose(UINT32 cid);

PUBLIC FTW_CID_T *
AppS2wHal_CidListElementGet(UINT8 cid);

PUBLIC VOID
AppS2w_HttpSemRelease(UINT8 cid);

UINT8
AppS2wHal_CidFind(INT32 sd);

#ifdef FTW_HTTPC_SUPPORT
PUBLIC FTW_HTTP_DATA_T *
AppS2wHal_HttpHandleGet(UINT8 cid);


UINT8
AppS2wHal_HttpOpen(FTW_HTTP_DATA_T *pHttpData, UINT32 *cid);

#endif
PUBLIC VOID
AppS2wHal_HttpdClose(UINT8 parentTask);

PUBLIC VOID
AppS2w_HttpdSemDelete(UINT8 cid);

#ifdef FTW_GSLINK
VOID
AppS2w_HttpdCtxDeInit(FTW_HTTPD_CONTEXT_T *httpdCtx);

UINT8
AppS2w_HttpdCtxInit(FTW_HTTPD_CONTEXT_T *httpdCtx,UINT8 reinit);

#endif
PUBLIC VOID 
AppS2w_HttpdSemCreate(UINT8 cid);

UINT8
AppS2wHal_CidGet(VOID);

PUBLIC VOID
AppS2w_HttpSemAquire(UINT8 cid);


PUBLIC UINT8
AppS2wHal_CidInfoGet(FTW_CID_INFO_T cidInfo[],UINT32* nos);

UINT8
AppS2wHal_SockOpSet(FTW_SOCK_OP_T* params);

PUBLIC UINT8
AppS2w_ConnModeGet(UINT8 cid);

GSN_STATUS 
AppS2w_SslServerOpen(UINT8 cid, char* sslCACertName);

PUBLIC GSN_STATUS 
AppS2w_SslClose(UINT8 cid);

PUBLIC UINT8
AppS2wHal_MdnsServiceDereg(FTW_MDNS_SRV_PARAM_T *pSrvParam);

PUBLIC UINT8
AppS2wHal_MdnsAnnounce(FTW_MDNS_ANNOUNCE_PARAM_T *mdnsAnnceParam);

PUBLIC UINT8 
AppS2w_SslClientOpen(UINT8 cliCid, char* caCertName,UINT8 *clientCertName, UINT8 *clientKeyName);

PUBLIC UINT8
AppS2wHal_NetCloseAll(UINT8 flag);

VOID
S2w_RawNetRx(void *buf, INT16 len);

VOID
DHCP_notify(INT32 status,void * ctx);
#ifdef FTW_PING_TRACE
PUBLIC VOID
AppS2wHal_PingClose(VOID);
#endif
#endif
