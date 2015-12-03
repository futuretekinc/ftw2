/*****************************************************************
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
* $RCSfile: s2w_net_gainspan.c,v $
*
* Description : s2w GEPS interface file
******************************************************************/


/*****************************************************************
  * File Inclusions
  *****************************************************************/
#include "netx/netx_bsd_layer/nxd_bsd.h"
#include <string.h>
#include "gsn_includes.h"
#include "hal/s2w.h"
#include "hal/s2w_types.h"
#include "hal/s2w_hal.h"
#include "parser/s2w_process.h"
#include "hal/s2w_timer.h"
#include "hal/s2w_net.h"
#include "hal/s2w_cert_mgmt.h"
#include "parser/s2w_command.h"

//#include "l2dev\s2w_l2_dev.h"
#include "main/app_main_ctx.h"
#include "config/app_resource_config.h"
#include "app_defines.h"
#include "app_events.h"
#include "config/app_stat_config.h"
#include "app_rtc_mem.h"
#include "s2w_cert.c"
#include "modules/http/gsn_httpc.h"
#include "parser/s2w_command.h"
#include "parser/s2w_parse.h"
#ifdef S2W_COAP_SUPPORT
#include "modules/coap/gsn_coap.h"
#include "modules/coap/gsn_coap_impl.h"
#endif

//#define GSN_SSL_CLIENT_SUPPORT
//#define GSN_SSL_SERVER_SUPPORT
#ifdef S2W_SSL_SERVER_SUPPORT
#include "modules/ssl/gsn_ssl.h"
#endif
#if defined(S2W_DTLS_CLIENT_SUPPORT)
#include "modules/dtls/gsn_dtls.h"
#endif
#ifdef S2W_IPv6_SUPPORT
#include "Nx_icmp.h"
#endif

#include "ftw_includes.h"
#include "ftw_net.h"
/**
 ******************************************************************************
 * @file s2w_net_gainspan.c
 * @brief S2W Application geps interface routines.
 *      This file contains the s2w application specific implimentation which
 *      Interface the s2w command processing network stack.
******************************************************************************/


/*****************************************************************************
  *  Public Variables
  *****************************************************************************/

extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;
//extern UINT32 nwConfigSuccess ;
extern GSN_NOTIFICATION_FUNC_T s2wappMainTaskNotifier;
extern S2W_PROFILE_T s2wCurrent;
extern UINT8 s2wAutoConnState ;
extern S2W_PROFILE_PARAMS_T profile_params;
/*****************************************************************************
  *  Private Variables
  *****************************************************************************/

GSN_OSAL_SEM_T s2wSocketCloseSem;
GSN_OSAL_SEM_T s2wUdpSocketCloseSem;

#define S2W_TLS_DEFAULT_FRAGMENT_SIZE 1398
#define S2W_TLS_HEADER_LENGTH 5
#define S2W_TLS_CONN_ALERT_FATAL 2
#define S2W_TLS_CONN_STATUS_FAIL 0
#define S2W_TLS_CONN_STATUS_SUCCESS 1

/* Socket descriptor value to indicate unused S2W_CID_T
 */

/* Definitions for conType of S2W_CID_T
 */
#define UDP 1
#define TCP 2

/* Timer for TCP connection timeout
 */
//PRIVATE S2W_TIMER_T s2wTcpConnectTimer;

/* Timer for UDP connection close
 */
//PRIVATE S2W_TIMER_T s2wUdpCloseTimer;

/* Event flags for TCP connection timeout
 */
//PRIVATE GH_EFLAGS s2wTcpConnectEflags;

/* Possible values for s2wTcpConnectEflags
 */
#define CONNECT_SUCCESS  0x01
#define CONNECT_FAIL     0x02
#define CONNECT_TIMEOUT  0x04


__no_init S2W_CID_T s2wCidList[MAX_CID_RANGE];

/**
 * @brief Buffer to hold the recieved data.
 */
__no_init UINT8 s2wRxBuf[S2W_RX_BUF_SIZE];

/* Events to register the socket callback for
 */
#define S2W_RXCALLBACK_FLAGS (NX_BSD_CB_TCP_RECIEVE | NX_BSD_CB_UDP_RECIEVE | NX_BSD_CB_TCP_LISTEN | NX_BSD_CB_TCP_DISCONNECT |	NX_BSD_CB_SOCKET_ERROR)
//#define S2W_RXCALLBACK_FLAGS NX_BSD_CB_TCP_LISTEN
/* stack for net rx task
 */
__no_init PUBLIC UINT8 s2wNetRecvTaskStack[APP_CFG_NET_RX_STACK_SIZE];

extern GSN_OSAL_QUEUE_T appMainThreadMsgQueue;
#ifdef S2W_PING_TRACE
extern UINT8 s2wPingStarted;
#endif
/* Queue for the receive task
 */
PUBLIC GSN_OSAL_QUEUE_T s2wNetQueue;
__no_init UINT32 s2wNetQueueBuffer[ ((APP_CFG_NET_RX_MAX_MSG_IN_MBOX) * sizeof(S2W_MSG_T)) / sizeof(UINT32)];

extern S2W_SSL_CERT_SRAM_TABLE_T s2w_ssl_cert_table[];

#define GSN_MAX_NUM_CERT        8
#define S2W_CERT_NAME_CA        "TLS_CA"
#define S2W_CERT_NAME_CLIENT    "TLS_CLIENT"
#define S2W_CERT_NAME_KEY       "TLS_KEY"

#define S2W_SSL_CERT_NAME_CA        "SSL_CA"
#define S2W_SSL_CERT_NAME_SERVER    "SSL_SERVER"
#define S2W_SSL_CERT_NAME_KEY       "SSL_KEY"

/*****************************************************************************
  *  Private Functions
  *****************************************************************************/

VOID
AppS2wHal_NetRecvTask(UINT32 u32Address);


UINT8
AppS2wHal_CidGet(VOID);

UINT8
AppS2wHal_CidFind(INT32 sd);

PRIVATE VOID
AppS2wHal_RxCallBack(INT32 sock, NX_BSD_CB_EVENT_TYPE_T flags,UINT32 port);


PRIVATE UINT8
AppS2wHal_NetImmediateClose(UINT8 cid);

PUBLIC UINT8
AppS2wHal_CidGet(VOID);

PRIVATE GSN_STATUS
AppS2w_SslLocalClose(UINT8 cid);

PRIVATE VOID
AppS2wHal_HttpCloseTimeout(VOID *unused);

#ifdef S2W_HTTPC_SUPPORT
PRIVATE UINT8
AppS2wHal_HttpLocalClose(UINT32 cid);
#endif
PUBLIC GSN_STATUS 
AppS2w_SslClose(UINT8 cid);

#ifdef S2W_COAP_SUPPORT
PUBLIC GSN_COAP_CONTEXT_T*
AppS2wHal_CoapHandleGet(UINT8 cid);
#endif
extern GSN_HTTPC_CONF_INFO_T httpConfInfo;
extern GSN_HTTP_USER_HEADER_TYPE_T headerTypes[];
extern GSN_HTTP_USER_HEADER_TYPE_T headerTypesModified[];
extern int tlsv1_client_established(struct tlsv1_client *conn);



/*****************************************************************************
  *  Public Functions
  *****************************************************************************/
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Get the pointer to s2wCidList entry for a given cid.
 *
 ******************************************************************/

PUBLIC S2W_CID_T*
AppS2wHal_CidListElementGet(UINT8 cid)
{
	return (&s2wCidList[cid]);
}
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
 * @retval S2W_SUCCESS     - operation successfull.
 * @retval S2W_SOCKFAILURE - operation failed
 * @retval S2W_ENCID       - operation failed- no valid cid.
 ******************************************************************/
PUBLIC UINT8
AppS2wHal_NetUdpClient(S2W_NETDATA_T *peerData, UINT8 *cidNo, UINT16 srcPort)
{
    UINT8 cid;
    INT32 sd,addressLength, ret;

    struct sockaddr_in srcAddr;
    struct sockaddr localAddress;
    
    /* Get free connection identifier list entry. */
    cid = AppS2wHal_CidGet();
    if (cid == INVALID_CID)
    {
        return S2W_ENCID;
    }
    /* check the node has a valid ip */
     //if(nwConfigSuccess != TRUE)
     {
        // return S2W_SOCKFAILURE;
     }

    if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        return S2W_SOCKFAILURE;
    }
    /* if a valid src port passed bind with that else leave it */
    if(srcPort > 0)
    {
        srcAddr.sin_family = AF_INET;
        srcAddr.sin_port = htons(srcPort);
        srcAddr.sin_addr.s_addr = 0;//htonl(INADDR_ANY);
        if (bind(sd, (struct sockaddr *)&srcAddr, sizeof(srcAddr)) == -1)
        {
            soc_close(sd);
            return S2W_SOCKFAILURE;
        }
    }
    else
    {
      srcAddr.sin_family = AF_INET;
      srcAddr.sin_port = NX_ANY_PORT;
      srcAddr.sin_addr.s_addr = 0;//htonl(INADDR_ANY);
      if (bind(sd, (struct sockaddr *)&srcAddr, sizeof(srcAddr)) == -1)
      {
          soc_close(sd);
          return S2W_SOCKFAILURE;
      }
      
    }
    
   
      
     
    /* Update the connection identifier list with the server information. */
    s2wCidList[cid].sd = sd;
    s2wCidList[cid].conType = UDP;
    s2wCidList[cid].conMode = S2W_NETDATA_MODE_CLIENT;
    s2wCidList[cid].remotePort = (peerData->port);
    if(srcPort > 0)
    {
        s2wCidList[cid].localPort = srcPort;
    }
    else
    {
       addressLength = sizeof(localAddress);
       ret = getsockname(sd,&localAddress,&addressLength);
       if(ret < 0)
       {
           AppS2wHal_NetClose(cid);
           return S2W_SOCKFAILURE;
       }
       s2wCidList[cid].localPort = htons(((struct sockaddr_in*)&localAddress)->sin_port);
    }
    
      memcpy(s2wCidList[cid].remoteIp,peerData->ipAddr,4);
    
     

    // setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_SNDTIMEO,(void*)&RecvTime,8);
    // fcntl(s2wCidList[cid].sd , F_SETFL, O_NONBLOCK);
    
    struct timeval TimeOut;
        TimeOut.tv_sec =  0;
        TimeOut.tv_usec = 1 * NX_MICROSECOND_PER_CPU_TICK;
       // setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_SNDTIMEO,(void*)&TimeOut,8);
        ret = setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_RCVTIMEO,(void*)&TimeOut,8);
        if(ret < 0)
        {
            AppS2wHal_NetClose(cid);
            return S2W_SOCKFAILURE;
        }
     
    /* Register the socket callback function to receive the events. */
    nx_bsd_callback_register(s2wCidList[cid].sd, AppS2wHal_RxCallBack,S2W_RXCALLBACK_FLAGS);
    *cidNo = cid;
    return S2W_SUCCESS;

}

#ifdef S2W_IPv6_SUPPORT

PUBLIC UINT8
AppS2wHal_NetUdpClientv6(S2W_NETDATA_T *remoteServerData, UINT8 *cidNo, UINT16 srcPort)
{
    UINT8 cid;
    INT status;
    INT32 sd;
    GSN_NWIF_IP_CONFIG_T nwParams;
    struct sockaddr_in6 CliAddr;

      if ((sd = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP)) == -1)
         {
          return S2W_SOCKFAILURE;
         }

     memset(&CliAddr,0,sizeof(struct sockaddr_in6));
     
    if(srcPort > 0)
    {
      
        CliAddr.sin6_family = AF_INET6;
        CliAddr.sin6_port = srcPort;
       
        GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx,&nwParams);
        
        if(nwParams.ipv6.globalAddr)
          COPY_IPV6_ADDRESS(((ULONG *)&nwParams.ipv6.globalAddr), (ULONG *)&(CliAddr.sin6_addr._S6_un._S6_u32));
        else
          COPY_IPV6_ADDRESS(((ULONG *)&nwParams.ipv6.linkLocalAddr), (ULONG *)&(CliAddr.sin6_addr._S6_un._S6_u32));
         GSN_IPv6_CHANGE_ENDIAN((UINT32 *)CliAddr.sin6_addr._S6_un._S6_u32);
        status = bind (sd, (struct sockaddr *) &CliAddr, sizeof(CliAddr));
          
        if(status < 0)
        {
          soc_close(sd);
          return S2W_SOCKFAILURE;
        }
        
    }
    
    /* Get free connection identifier list entry. */
    
    cid = AppS2wHal_CidGet();
    if (cid == INVALID_CID)
    {
        return S2W_ENCID;
    }
  
     /* Update the connection identifier list with the server information. */
    
    s2wCidList[cid].sd = sd;
    s2wCidList[cid].conType = UDP;
    s2wCidList[cid].conMode = S2W_NETDATA_MODE_CLIENT;
    s2wCidList[cid].remotePort = remoteServerData->port;
    s2wCidList[cid].addrType = ADDR_TYPE_IPv6;
    if(srcPort > 0)
    {
        s2wCidList[cid].localPort = remoteServerData->port;
    }
    
    memcpy(s2wCidList[cid].remoteIpv6,remoteServerData->ipv6Addr,16);
    
     
    // setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_SNDTIMEO,(void*)&RecvTime,8);
     
    // fcntl(s2wCidList[cid].sd , F_SETFL, O_NONBLOCK);
    struct timeval TimeOut;
        TimeOut.tv_sec =  0;
        TimeOut.tv_usec = 1 * NX_MICROSECOND_PER_CPU_TICK;
        //setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_SNDTIMEO,(void*)&TimeOut,8);
        setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_RCVTIMEO,(void*)&TimeOut,8);
    
    nx_bsd_callback_register(s2wCidList[cid].sd, AppS2wHal_RxCallBack,S2W_RXCALLBACK_FLAGS);
    
    *cidNo = cid;
    
    return S2W_SUCCESS;
}

PUBLIC UINT8
AppS2wHal_NetUdpServerv6(S2W_NETDATA_T *serverData, UINT8 *cidNo)
{
  UINT8 cid;
  INT32 sd;
  struct sockaddr_in6 servAddr;
  GSN_NWIF_IP_CONFIG_T nwParams;
  
  cid = AppS2wHal_CidGet();
    if (cid == INVALID_CID)
    {
        return S2W_ENCID;
    }
    
    if ((sd = socket( AF_INET6, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        return S2W_SOCKFAILURE;
    }
    memset(&servAddr,0,sizeof(struct sockaddr_in6));    
    servAddr.sin6_family = AF_INET6;
    servAddr.sin6_port = htons(serverData->port);
    
    GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx,&nwParams);
        
    if(nwParams.ipv6.globalAddr)
      COPY_IPV6_ADDRESS(((ULONG *)&nwParams.ipv6.globalAddr), (ULONG *)&(servAddr.sin6_addr._S6_un._S6_u32));
    else
      COPY_IPV6_ADDRESS(((ULONG *)&nwParams.ipv6.linkLocalAddr), (ULONG *)&(servAddr.sin6_addr._S6_un._S6_u32));
    GSN_IPv6_CHANGE_ENDIAN((UINT32 *)servAddr.sin6_addr._S6_un._S6_u32);
     if (bind(sd,  (struct sockaddr *)&servAddr, sizeof(servAddr)) == -1)
    {
        soc_close(sd);
        return S2W_SOCKFAILURE;
    }
    
    s2wCidList[cid].sd = sd;
    s2wCidList[cid].conType = UDP;
    s2wCidList[cid].conMode = S2W_NETDATA_MODE_SERVER;
    s2wCidList[cid].localPort = serverData->port;
    s2wCidList[cid].remotePort = 0;
    s2wCidList[cid].addrType = ADDR_TYPE_IPv6;
    memset(s2wCidList[cid].remoteIpv6,0,16);

     
     //setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_SNDTIMEO,(void*)&RecvTime,8);
     
     // fcntl(s2wCidList[cid].sd , F_SETFL, O_NONBLOCK);
    
    struct timeval TimeOut;
        TimeOut.tv_sec =  0;
        TimeOut.tv_usec = 1 * NX_MICROSECOND_PER_CPU_TICK;
        //setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_SNDTIMEO,(void*)&TimeOut,8);
        setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_RCVTIMEO,(void*)&TimeOut,8);
    
    nx_bsd_callback_register(s2wCidList[cid].sd, AppS2wHal_RxCallBack,S2W_RXCALLBACK_FLAGS);

    *cidNo = cid;
    
    return S2W_SUCCESS;
   
}


PUBLIC UINT8
AppS2wHal_NetTcpClientv6(S2W_NETDATA_T *remoteServerData, UINT8 *cidNo)
{
  
    UINT32 cid;
    INT32 sd;
    INT32 status;
    struct sockaddr_in6 destAddr;
    
    cid = AppS2wHal_CidGet();
    if (cid == INVALID_CID)
    {
        return S2W_ENCID;
    }
    
    if ((sd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == -1)
    {
        return S2W_SOCKFAILURE;
    }
    
    memset(&destAddr, 0, sizeof(destAddr));
    
    destAddr.sin6_family = AF_INET6;
    COPY_IPV6_ADDRESS((ULONG*)remoteServerData->ipv6Addr, (ULONG *)&(destAddr.sin6_addr._S6_un._S6_u32));
    destAddr.sin6_port = htons(remoteServerData->port);
     GSN_IPv6_CHANGE_ENDIAN((UINT32 *)destAddr.sin6_addr._S6_un._S6_u32);
    
    s2wCidList[cid].sd = sd;
    s2wCidList[cid].conType = TCP;
    s2wCidList[cid].conMode = S2W_NETDATA_MODE_CLIENT;
    s2wCidList[cid].remotePort = remoteServerData->port;
    s2wCidList[cid].addrType = ADDR_TYPE_IPv6;
    
    memcpy(s2wCidList[cid].remoteIpv6,remoteServerData->ipv6Addr,16);
    
     
    // setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_SNDTIMEO,(void*)&RecvTime,8);
     
      
      
    nx_bsd_callback_register(s2wCidList[cid].sd, AppS2wHal_RxCallBack,S2W_RXCALLBACK_FLAGS);
    
    status = connect(sd, (struct sockaddr *)&destAddr, sizeof(destAddr));
    
    if (status < 0 )
    {
        AppS2wHal_NetClose(cid);
        return S2W_SOCKFAILURE;
    }

    *cidNo = cid;

    s2wCidList[cid].sslflag = FALSE;
    
    //fcntl(s2wCidList[cid].sd , F_SETFL, O_NONBLOCK);
    struct timeval TimeOut;
        TimeOut.tv_sec =  0;
        TimeOut.tv_usec = 1 * NX_MICROSECOND_PER_CPU_TICK;
        //setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_SNDTIMEO,(void*)&TimeOut,8);
        setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_RCVTIMEO,(void*)&TimeOut,8);

    return S2W_SUCCESS;
  
}


PUBLIC UINT8
AppS2wHal_NetTcpServerv6(S2W_NETDATA_T *serverData, UINT8 *cidNo)
{
  INT32 sd;
  UINT8 cid;
  struct sockaddr_in6 servAddr;
  GSN_NWIF_IP_CONFIG_T nwParams;

  cid = AppS2wHal_CidGet();
  if (cid == INVALID_CID)
  {
      return S2W_ENCID;
  }
  
  if ((sd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)) == -1)
    {
        return S2W_SOCKFAILURE;
    }
  
  memset(&servAddr, 0, sizeof(servAddr));
  
  servAddr.sin6_family = AF_INET6;
  servAddr.sin6_port = htons(serverData->port);
  
  GsnNwIf_IpConfigGet(&s2wappMainTaskCtxt->if0.nwifCtx,&nwParams);
        
  if(nwParams.ipv6.globalAddr)
     COPY_IPV6_ADDRESS(((ULONG *)&nwParams.ipv6.globalAddr), (ULONG *)&(servAddr.sin6_addr._S6_un._S6_u32));
  else
     COPY_IPV6_ADDRESS(((ULONG *)&nwParams.ipv6.linkLocalAddr), (ULONG *)&(servAddr.sin6_addr._S6_un._S6_u32));
     GSN_IPv6_CHANGE_ENDIAN((UINT32 *)servAddr.sin6_addr._S6_un._S6_u32);
    if (bind(sd, (struct sockaddr *) &servAddr, sizeof(servAddr)) ==  -1)
    {
        soc_close(sd);
        return S2W_SOCKFAILURE;
    }
    
      if (listen(sd, 5) < 0)
    {
        soc_close(sd);
        return S2W_SOCKFAILURE;
    }

    
    s2wCidList[cid].sd = sd;
    s2wCidList[cid].conType = TCP;
    s2wCidList[cid].conMode = S2W_NETDATA_MODE_SERVER;
    s2wCidList[cid].localPort = serverData->port;
    s2wCidList[cid].remotePort = 0;
    memset(s2wCidList[cid].remoteIpv6,0,16);
    s2wCidList[cid].addrType = ADDR_TYPE_IPv6;
    
     
    // setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_SNDTIMEO,(void*)&RecvTime,8);
    
    nx_bsd_callback_register(s2wCidList[cid].sd, AppS2wHal_RxCallBack,S2W_RXCALLBACK_FLAGS);

    *cidNo = cid;

    return S2W_SUCCESS;
 
}



#endif

PUBLIC UINT8 AppS2w_ConnModeGet(UINT8 cid)
{
    return (s2wCidList[cid].conMode);
}


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
 * @retval S2W_SUCCESS     - operation successfull.
 * @retval S2W_SOCKFAILURE - operation failed
 * @retval S2W_ENCID       - operation failed- no valid cid
 ******************************************************************/
PUBLIC UINT8
AppS2wHal_NetTcpClient(S2W_NETDATA_T *peerData, UINT8 *cidNo)
{
    struct sockaddr_in destAddr;
    UINT32 cid;
    INT32 sd;
    INT32 ret;
    ULONG connect_timeout =  (s2wCurrent.registers[S2W_REG_TCP_CONNECT_TIMEOUT]/100);
    ULONG rexTimeOut=75,retransRate=1;

    /* get  a valid cid */
    cid = AppS2wHal_CidGet();
    if (cid == INVALID_CID)
    {
        return S2W_ENCID;
    }

    /* open a tcp client socket */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        return S2W_SOCKFAILURE;
    }

    /** Make the socket non blocking. */
    //tfBlockingState(sd, TM_BLOCKING_OFF);

    ret = setsockopt(sd,IP_PROTOTCP,TCP_REX_TIMER_RATE,(void*)&retransRate,4);
    if (ret < 0 )
    {
    	soc_close(sd);
        return S2W_FAILURE;
    }
    ret = setsockopt(sd,IP_PROTOTCP,TCP_MAXRT,(void*)&rexTimeOut,4);
    if (ret < 0 )
    {
    	soc_close(sd);
        return S2W_FAILURE;
    }

    ret = setsockopt(sd,IP_PROTOTCP,CONNECT_TIMEOUT_TM,(void*)&connect_timeout,4);
    if (ret < 0 )
    {
    	soc_close(sd);
        return S2W_FAILURE;
    }

    /** Connect the socket to the server. */
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(peerData->port);
    memcpy(&(destAddr.sin_addr.s_addr),&peerData->ipAddr,sizeof(destAddr.sin_addr.s_addr));


    /* register the callback for any socket events */
    nx_bsd_callback_register(sd, AppS2wHal_RxCallBack,S2W_RXCALLBACK_FLAGS);

    ret = connect(sd, (struct sockaddr *)&destAddr, sizeof(destAddr));
     /*
     * Update the connection identifier list with connection information
     * except the type.
     */
    s2wCidList[cid].sd = sd;
    s2wCidList[cid].conType = TCP;
    s2wCidList[cid].conMode = S2W_NETDATA_MODE_CLIENT_TRANSIENT;
    s2wCidList[cid].remotePort = peerData->port;
    memcpy(s2wCidList[cid].remoteIp,(UINT8*)peerData->ipAddr,4);

    if (ret < 0 )
    {
        //S2w_Debug("connect failed: %d\r\n", tfGetSocketError(sd));

        AppS2wHal_NetClose(cid);
        return S2W_FAILURE;
    }
    *cidNo = cid;
	s2wCidList[cid].conMode = S2W_NETDATA_MODE_CLIENT;
    s2wCidList[cid].sslflag = FALSE;
	 s2wCidList[cid].serverCid = INVALID_CID;
    /* reconfigure connect timeout, since we are making it non blocking */
    connect_timeout =5;
    
    //fcntl(sd , F_SETFL, O_NONBLOCK);
    struct timeval TimeOut;
    TimeOut.tv_sec =  0;
    TimeOut.tv_usec = 1 * NX_MICROSECOND_PER_CPU_TICK;
    setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_RCVTIMEO,(void*)&TimeOut,8);
    setsockopt(s2wCidList[cid].sd,IP_PROTOTCP,CONNECT_TIMEOUT_TM,(void*)&connect_timeout,4);

    return S2W_SUCCESS;
}


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
 * @retval S2W_SUCCESS     - operation successfull.
 * @retval S2W_SOCKFAILURE - operation failed
 * @retval S2W_ENCID       - operation failed- no valid cid
 ******************************************************************/
PUBLIC UINT8
AppS2wHal_NetUdpServer(S2W_NETDATA_T *serverData, UINT8 *cidNo)
{
    UINT8 cid;
    INT32 sd, ret;
    struct sockaddr_in srcAddr;

    cid = AppS2wHal_CidGet();
    if (cid == INVALID_CID)
    {
        return S2W_ENCID;
    }

    /* check the node has a valid ip
     */
     //if(nwConfigSuccess != TRUE)
     {
         //return S2W_SOCKFAILURE;
     }
    /* open the udp server socket
     */
    if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        return S2W_SOCKFAILURE;
    }
    srcAddr.sin_family = AF_INET;
    srcAddr.sin_port = htons(serverData->port);
    srcAddr.sin_addr.s_addr = 0;//htonl(INADDR_ANY);

    /* bind the socket with source addess
     */
    if (bind(sd, (struct sockaddr *)&srcAddr,
          sizeof(srcAddr)) == -1)
    {
        soc_close(sd);
        return S2W_SOCKFAILURE;
    }

    /* fill the cid list the socket parameters
     */
    s2wCidList[cid].sd = sd;
    s2wCidList[cid].conType = UDP;
    s2wCidList[cid].conMode = S2W_NETDATA_MODE_SERVER;
    s2wCidList[cid].localPort = serverData->port;
    s2wCidList[cid].remotePort = 0;
    memset(s2wCidList[cid].remoteIp,0,4);
    
    
     
    // setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_SNDTIMEO,(void*)&RecvTime,8);
     
         //    fcntl(s2wCidList[cid].sd , F_SETFL, O_NONBLOCK);
    struct timeval TimeOut;
        TimeOut.tv_sec =  0;
        TimeOut.tv_usec = 1 * NX_MICROSECOND_PER_CPU_TICK;
       // setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_SNDTIMEO,(void*)&TimeOut,8);
        ret = setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_RCVTIMEO,(void*)&TimeOut,8);
        if(ret < 0)
        {
            AppS2wHal_NetClose(cid);
            return S2W_SOCKFAILURE;
        }

  
      /* register the callback for any socket events
     */
    nx_bsd_callback_register(s2wCidList[cid].sd, AppS2wHal_RxCallBack,S2W_RXCALLBACK_FLAGS);

    *cidNo = cid;
    return S2W_SUCCESS;
}


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
 * @retval S2W_SUCCESS     - operation successfull.
 * @retval S2W_SOCKFAILURE - operation failed
 * @retval S2W_ENCID       - operation failed- no valid cid
 ******************************************************************/
PUBLIC UINT8
AppS2wHal_NetTcpServer(S2W_NETDATA_T *serverData, UINT8 *cidNo)
{
    INT32 sd, ret;
    struct sockaddr_in srcAddr;
    UINT8 cid;
    ULONG rexTimeOut=25;

    cid = AppS2wHal_CidGet();
    if (cid == INVALID_CID)
    {
        return S2W_ENCID;
    }

    /* open the tcp server socket */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        return S2W_SOCKFAILURE;
    }

    srcAddr.sin_family = AF_INET;
    srcAddr.sin_port = htons(serverData->port);
    srcAddr.sin_addr.s_addr = htonl(0);

    /*  bind the source port  */
    if (bind(sd, (struct sockaddr *)&srcAddr, sizeof(srcAddr)) == -1)
    {
        soc_close(sd);
        return S2W_SOCKFAILURE;
    }
    if (listen(sd, 5) < 0)
    {
        soc_close(sd);
        return S2W_SOCKFAILURE;
    }

    /* fill the cid list */
    s2wCidList[cid].sd = sd;
    s2wCidList[cid].conType = TCP;
    s2wCidList[cid].conMode = S2W_NETDATA_MODE_SERVER;
    s2wCidList[cid].localPort = serverData->port;
    s2wCidList[cid].remotePort = 0;
    s2wCidList[cid].maxConn = 15;
    memset(s2wCidList[cid].remoteIp,0,4);
    //sockOption = -1;
    //setsockopt(sd, 0, TCP_MAXRT, (const char*)&sockOption,
    //           sizeof(sockOption));
    ret = setsockopt(sd,IP_PROTOTCP,TCP_MAXRT,(void*)&rexTimeOut,4);
    if(ret < 0)
    {
        AppS2wHal_NetClose(cid);
        return S2W_SOCKFAILURE;
    }
    //sockOption1 = 2000;
    //setsockopt(sd, SOL_SOCKET, SO_RCVBUF,(const char*)&sockOption1,
     //          sizeof(sockOption1));
    
    
     
     //setsockopt(s2wCidList[cid].sd,SOL_SOCKET,SO_SNDTIMEO,(void*)&RecvTime,8);
    /* register the callback for any socket events */
 
    nx_bsd_callback_register(s2wCidList[cid].sd, AppS2wHal_RxCallBack,S2W_RXCALLBACK_FLAGS);
    *cidNo = cid;
    return S2W_SUCCESS;
}

VOID AppS2wHal_TcpSrvMaxConSet(UINT8 cid,UINT32 maxCon)
{
	s2wCidList[cid].maxConn= maxCon;
}

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w socket close function.
 *    This function close the particular tcp/udp connection specified by cid no.
 *.@param cidNo      - IN the cid number corresponding to the socket to be closed.
 * @retval S2W_SUCCESS     - operation successfull.
 * @retval S2W_FAILURE     - operation failed
 * @retval S2W_EBADCID     - operation failed- cid passed is not valid.
 ******************************************************************/

VOID GsnSocketCallback ( INT32 SocketDescriptor, INT32 Flags )
{
    GsnOsal_SemRelease(&s2wSocketCloseSem);
}

PUBLIC UINT8
AppS2wHal_NetClose(UINT8 cid)
{
    S2W_CID_T *p;
    UINT32 opt=2;
    /* Validate the connection identifier.
     */
    if (cid >= MAX_CID_RANGE)
    {
        return S2W_EBADCID;
    }

    p = &s2wCidList[cid];
    if ((p->sd == CID_NOTINUSE) || (p->s2wCidCloseInProgress == TRUE))
    {
        return S2W_EBADCID;
    }
    p->s2wCidCloseInProgress = TRUE;
    /* Close the connection.
     */
     if(s2wCidList[cid].allocatedTo == 1)
	 	return S2W_FAILURE;

    if((p->conType == TCP) && (p->conMode == S2W_NETDATA_MODE_CLIENT))
    {
    	setsockopt(p->sd, IP_PROTOTCP, TCP_MAX_REXMIT, (const char*)&opt,
               sizeof(opt));
    }
	nx_bsd_callback_register(p->sd, NULL, 0);

#if defined (S2W_HTTPS_SUPPORT) || (S2W_HTTPC_SUPPORT)
    /* if an http connection close using http close */
    if(p->httpflag == 1 )
    {
        AppS2wHal_HttpLocalClose(cid);
    }
    else
#endif
#if defined(S2W_SSL_CLIENT_SUPPORT) || defined(S2W_SSL_SERVER_SUPPORT)
    if(p->sslflag == 1 )
    {
        AppS2w_SslLocalClose(cid);
    }
    else
#endif

    {
        soc_close(p->sd);
	}
        if((p->conType == TCP) && (p->conMode == S2W_NETDATA_MODE_CLIENT))
        {
		 	if(s2wCidList[cid].serverCid != INVALID_CID)
		 	{
		 		GsnOsal_SemAcquire ( &(s2wappMainTaskCtxt->s2wTcpClientCntSyncSem), GSN_OSAL_WAIT_FOREVER );
				s2wCidList[s2wCidList[cid].serverCid].clientConCount--;
			 	GsnOsal_SemRelease(&s2wappMainTaskCtxt->s2wTcpClientCntSyncSem);
		 	}
        }
    
#if 0   
     UINT32 i=0;
     if((p->conType == TCP) && (p->conMode == S2W_NETDATA_MODE_SERVER))
     {
       /* Close all the client CIDs connected to server as well */
        for (i = 0; i < MAX_CID_RANGE; i++)
        {
          if(s2wCidList[i].serverCid == cid)
          {
            soc_close(s2wCidList[i].sd);
            nx_bsd_callback_register(p->sd, NULL, 0);
            s2wCidList[i].sd = CID_NOTINUSE;
            s2wCidList[i].localPort = 0;
            s2wCidList[i].remotePort = 0;
            s2wCidList[i].addrType = 0;
            s2wCidList[i].s2wCidCloseInProgress = FALSE;
            
          }
        }
     }
#endif
    /* Remove the entry from the connection identifier list.
     */

    p->sd = CID_NOTINUSE;
    s2wCidList[cid].localPort = 0;
    s2wCidList[cid].remotePort = 0;
    s2wCidList[cid].addrType = 0;
    p->s2wCidCloseInProgress = FALSE;
    return S2W_SUCCESS;
}


PRIVATE UINT8
AppS2wHal_NetImmediateClose(UINT8 cid)
{
    S2W_CID_T *p;
    UINT32 opt=2;

    /* Validate the connection identifier.
     */
    if (cid >= MAX_CID_RANGE)
    {
        return S2W_EBADCID;
    }

    p = &s2wCidList[cid];
    if ((p->sd == CID_NOTINUSE) || (p->s2wCidCloseInProgress == TRUE))
    {
        return S2W_EBADCID;
    }

    /* Close the connection.*/
    p->s2wCidCloseInProgress = TRUE;
    setsockopt(p->sd, IP_PROTOTCP, TCP_MAX_REXMIT, (const char*)&opt,
               sizeof(opt));
 #if defined (S2W_HTTPS_SUPPORT) || (S2W_HTTPC_SUPPORT)
     if(p->httpflag == 1 )
     {
         AppS2wHal_HttpLocalClose(cid);
     }
     else
 #endif
 #if defined(S2W_SSL_CLIENT_SUPPORT) || defined(S2W_SSL_SERVER_SUPPORT)
     if(p->sslflag == 1 )
     {
         AppS2w_SslLocalClose(cid);

     }
     else
 #endif
    {
  		nx_bsd_callback_register(p->sd, NULL, 0);
        soc_close(p->sd);

   }


    p->sd = CID_NOTINUSE;
    s2wCidList[cid].localPort = 0;
    s2wCidList[cid].remotePort = 0;
    p->s2wCidCloseInProgress = FALSE;
    return S2W_SUCCESS;
}



/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief S2w all socket close function.
 *    This function close all tcp/udp connection established in s2w.
 * @retval S2W_SUCCESS     - operation successfull.
 * @retval S2W_FAILURE     - operation failed
 ******************************************************************/
PUBLIC UINT8
AppS2wHal_NetCloseAll(UINT8 flag)
{
    UINT8 status = S2W_SUCCESS;
    INT32 i;

    for (i = 0; i < MAX_CID_RANGE; i++)
    {
        if (s2wCidList[i].sd != CID_NOTINUSE && s2wCidList[i].allocatedTo != 1)
        {
	         if(flag == CID_NCLOSE)
	         {
	            status = AppS2wHal_NetClose(i);
	         }
	         else
	         {
	            status = AppS2wHal_NetImmediateClose(i);
	         }

        }
        s2wCidList[i].localPort = 0;
        s2wCidList[i].remotePort = 0;
    }
    return status;
}


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
 * @retval S2W_SUCCESS           - operation successfull.
 * @retval S2W_ENCID/S2W_EBADCID - operation failed-no valid cid
 * @@retval S2W_FAILURE          - operation failed.
 ******************************************************************/
PUBLIC UINT8
AppS2wHal_NetTx(UINT8 cid, UINT8 *destAddr, UINT16 destPort,
                 VOID *buf, UINT32 len)
{
    UINT32 status = S2W_SUCCESS;
    S2W_CID_T *p;
	UINT8 *outDataBuf;
    p = &s2wCidList[cid];
    if (p->conMode == S2W_NETDATA_MODE_SERVER)
    {
        struct sockaddr_in addr;
        if (p->conType == TCP)
        {
            return S2W_FAILURE;
        }
#ifdef S2W_IPv6_SUPPORT
      
        if(p->addrType & ADDR_TYPE_IPv6)
        {
          struct sockaddr_in6 servAddr;
          servAddr.sin6_family = AF_INET6;
          servAddr.sin6_port = htons(destPort);
          
          memcpy(servAddr.sin6_addr._S6_un._S6_u32,destAddr,16);
          GSN_IPv6_CHANGE_ENDIAN((UINT32 *)servAddr.sin6_addr._S6_un._S6_u32); 
            if (sendto(p->sd, buf, len, 0,(struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
        {
            status = S2W_FAILURE;
        }
          
        }
      else
      
#endif //S2W_IPv6_SUPPORT 
      {
        addr.sin_family = AF_INET;
        addr.sin_port = htons(destPort);
        //*(ULONG*)destAddr = htonl(*(ULONG*)destAddr);
        memcpy(&(addr.sin_addr.s_addr), destAddr, sizeof(addr.sin_addr.s_addr));

        GsnSq_TaskMonitorStart(APP_CFG_SQ_SERIAL_INPUT_TASK_ID, (UINT32)cid);
        if (sendto(p->sd, buf, len, 0,
           (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            //S2w_Debug("udp sendto fail: %d\r\n", tfGetSocketError(p->sd));
            //S2w_Debug("destaddr = %x\n\r", *(UINT32 *) destAddr);
            //S2w_Debug("destport = %x\n\r", destPort);
            status = S2W_FAILURE;
        }
        GsnSq_TaskMonitorStop( APP_CFG_SQ_SERIAL_INPUT_TASK_ID);
      }
    }
    else if((p->conType == UDP) && (p->conMode == S2W_NETDATA_MODE_CLIENT))
    {
#if defined(S2W_DTLS_CLIENT_SUPPORT)
        if ((s2wCidList[cid].sslflag == TRUE))
 		{
 			/*NOTE: IMP: The ssl can encode a max of 1338 bytes. Its beter to encode 1K at a time
 			and send it. So we need a loop mechanism to send the incomming data in 1K encoded
 			chunks....*/
 			//UINT32 outDataLen;
            UINT32 dataSent = 0;
 			UINT32 sendLen = 0;
 			while(len)
 			{
 				sendLen = (len > 1024)?1024:len;
                GsnDtls_Send( (GSN_DTLS_CONN_T *)s2wCidList[cid].ssl.sslConn,
                		(UINT8 *)((UINT8*)buf + dataSent), sendLen, 0 );
 				dataSent += sendLen;
 				len -= sendLen;
 			}
 		}
        else
#endif
        {
      #ifdef S2W_IPv6_SUPPORT
        if(p->addrType & ADDR_TYPE_IPv6)
        {
          struct sockaddr_in6 servAddr;
          servAddr.sin6_family = AF_INET6;
          servAddr.sin6_port = htons(s2wCidList[cid].remotePort);
          
          
          memcpy(servAddr.sin6_addr._S6_un._S6_u32,s2wCidList[cid].remoteIpv6,16);
          GSN_IPv6_CHANGE_ENDIAN((UINT32 *)servAddr.sin6_addr._S6_un._S6_u32); 
            if (sendto(p->sd, buf, len, 0,(struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
        {
            status = S2W_FAILURE;
        }

        }
      else
      
#endif //S2W_IPv6_SUPPORT       
      {
        struct sockaddr_in addr1;
        addr1.sin_family = AF_INET;
        addr1.sin_port = htons(s2wCidList[cid].remotePort);
        memcpy(&(addr1.sin_addr.s_addr),s2wCidList[cid].remoteIp ,
                  sizeof(addr1.sin_addr.s_addr));

        GsnSq_TaskMonitorStart(APP_CFG_SQ_SERIAL_INPUT_TASK_ID, (UINT32)cid);
        if (sendto(p->sd, buf, len, 0,
           (struct sockaddr *)&addr1, sizeof(addr1)) < 0)
        {
            S2w_Debug("udp sendto fail: %d\r\n", 1);
        }
        GsnSq_TaskMonitorStop( APP_CFG_SQ_SERIAL_INPUT_TASK_ID);
      }
    }
    }
    else
    {
        /* do a socket send
         */

        //S2w_Debug("\r\nData sd %d, %d\r\n",s2wCidList[cid].sd,
            //tlsv1_client_established(s2wCidList[cid].ssl.sslConn->tlsv1Conn));

 #if defined(S2W_SSL_CLIENT_SUPPORT) || defined(S2W_SSL_SERVER_SUPPORT)
         if ((s2wCidList[cid].sslflag == TRUE))
 		{
 			/*NOTE: IMP: The ssl can encode a max of 1338 bytes. Its beter to encode 1K at a time
 			and send it. So we need a loop mechanism to send the incomming data in 1K encoded
 			chunks....*/
 			UINT32 outDataLen, u32NoOfBytesSent;
 			UINT32 dataSent = 0;
 			UINT32 sendLen = 0;
 			while(len)
 			{
 				sendLen = (len > 1024)?1024:len;
 #ifdef S2W_APP_SSL_PROVISION
 				ULONG64 curTime;
 				UINT32 diffTime, timeInMsec;

 				encryptStartTime = GsnSoftTmr_CurrentSystemTime();
 #endif
 				GsnSsl_Encode(s2wCidList[cid].ssl.sslConn, (UINT8 *)((UINT8*)buf + dataSent),
 							  sendLen, &outDataBuf,&outDataLen);
 #ifdef S2W_APP_SSL_PROVISION
 				curTime  = GsnSoftTmr_CurrentSystemTime();
 				diffTime = (curTime - encryptStartTime);
 				timeInMsec =   diffTime/(TIMER_INTERRUPT_1_MS);
 				S2w_Printf("\r\nSSL Tx Encryption Time in ms %d\r\n", timeInMsec);
 #endif

 				u32NoOfBytesSent = send(s2wCidList[cid].sd, (const char*)outDataBuf,
 										outDataLen, 0);

 				GsnSsl_Free(outDataBuf);

 				if ( outDataLen != u32NoOfBytesSent )
 				{
 					AppS2w_SslClose(cid);
 					return S2W_FAILURE;
 				}
 				dataSent += sendLen;
 				len -= sendLen;
 			}
 		}
         else
#endif
        {
           GsnSq_TaskMonitorStart(APP_CFG_SQ_SERIAL_INPUT_TASK_ID, (UINT32)cid);
          
#ifdef S2W_IPv6_SUPPORT
        if(p->addrType & ADDR_TYPE_IPv6)
        {
          if (send(p->sd, buf, len, 0) < 0)
        {
	        /*GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
	        // if the auto connection is enabled do not print this message
	             if((!s2wAutoConnState ) && (!profile_params.autoConnect))
       	      {
            			//S2w_Printf("send() failed: %d\r\n", 1);
			 }
		         GsnOsal_SemRelease(&s2wSyncSemID);
            		*/
            status = S2W_FAILURE;
        }
          
          
        }
        else
#endif //S2W_IPv6_SUPPORT 
        {
        if (send(p->sd, buf, len, 0) < 0)
        {
            //GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
            //if((!s2wAutoConnState ) && (!profile_params.autoConnect))
            //{
            //S2w_Printf("send() failed: %d\r\n", 1);
			//}
            //GsnOsal_SemRelease(&s2wSyncSemID);
            status = S2W_FAILURE;
        }
	}
        }
        GsnSq_TaskMonitorStop( APP_CFG_SQ_SERIAL_INPUT_TASK_ID);

    }
    if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
    {
         s2wSpiFs_Flush();
    }
    return status;
}


/**
 ******************************************************************
 * @brief S2w cid info get function.
 *    This function get all info of the active active cids present.
 *.@param cidInfo      - IN the cid info structure pointer.
 * @param nos          - IN the address to which the number of active
 *                           cids to be stored.
 * @retval S2W_SUCCESS     - operation successfull.
 ******************************************************************/
PUBLIC UINT8
AppS2wHal_CidInfoGet(S2W_CID_INFO_T cidInfo[],UINT32* nos)
{
    UINT8 i=0,j=0;
    struct sockaddr_in sockAddr;
    INT32 len = sizeof(sockAddr), ret;
    for(i=0;i<MAX_CID_RANGE;i++)
    {
        if(s2wCidList[i].sd != CID_NOTINUSE) // valid cid
        {
            cidInfo[j].cid = AppS2wHal_CidFind(s2wCidList[i].sd);
            if(s2wCidList[i].localPort > 0)
            {
                cidInfo[j].localPort = s2wCidList[i].localPort;
            }
            else
            {
                ret = getsockname(s2wCidList[i].sd, (struct sockaddr *)&sockAddr,
                             &len);
                if(ret < 0)
                {
                    //AppS2wHal_NetClose(cid);
                    return S2W_SOCKFAILURE;
                }
                cidInfo[j].localPort = ntohs(sockAddr.sin_port);
            }
            if (s2wCidList[i].conMode != S2W_NETDATA_MODE_SERVER)
            {
                memcpy(cidInfo[j].remoteIp, s2wCidList[i].remoteIp,4);
            }
            cidInfo[j].remotePort = s2wCidList[i].remotePort;
            cidInfo[j].conType = s2wCidList[i].conType;
            cidInfo[j].conMode = s2wCidList[i].conMode;
            j = j+1;
        }

    }
    *nos = j;
    return S2W_SUCCESS;
}


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
PUBLIC UINT8
AppS2wHal_NetIsCidOpen(UINT8 cid)
{
    return !(cid >= MAX_CID_RANGE || s2wCidList[cid].sd == CID_NOTINUSE);
}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief s2w Network initialize function
 *    This function create the network recv task and create queue for that
      task.
 * @retval VOID - None.
 ******************************************************************/
PUBLIC VOID
AppS2wHal_NetInit(VOID)
{
    UINT32 i;

    /* Mark all socket descriptor as 'not in use'.
     */
    for (i = 0; i < MAX_CID_RANGE; i++)
    {
        s2wCidList[i].sd = CID_NOTINUSE;
        s2wCidList[i].httpflag = 0;
        s2wCidList[i].localPort = 0;
    }
    s2wappMainTaskCtxt->lastCidCreated = MAX_CID_RANGE-1;

    //AppS2wHal_TimerInit(&s2wTcpConnectTimer, AppS2wHal_ConnectTimeout, NULL);
    //gh_eflags_create(&s2wTcpConnectEflags);

    GsnOsal_SemCreate  ( &s2wUdpSocketCloseSem, 0 );
    //AppS2wHal_TimerInit(&s2wUdpCloseTimer, AppS2wHal_CloseTimeout, NULL);

    /* create the queue for the network receive task
     */
    GsnOsal_QueueCreate(&s2wNetQueue, 2,
                          (UINT8*)s2wNetQueueBuffer,
                          (sizeof(s2wNetQueueBuffer)));

    /* create the network  receive task
     */

    GsnOsal_ThreadCreate(AppS2wHal_NetRecvTask,s2wappMainTaskCtxt,
                                &s2wappMainTaskCtxt->s2wNetRxTask,
                                "s2wNetRecvtask",
                                APP_CFG_NET_RX_THREAD_PRIORITY,
                                s2wNetRecvTaskStack,
                                sizeof(s2wNetRecvTaskStack),
                                GSN_OSAL_THREAD_INITIAL_READY);

}


/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief s2w Data receive task.
 *    This task waits on a message queue.  The network stack callback function
 *    will, when the event that data is available on a socket is received, send a
 *    message to this message queue containing the socket descriptor.  This task
 *    will receive the data from the socket and pass it on to the Serial2WiFi
 *    core, which will output the data on the serial port.
 *
 *   The purpose of this task is to avoid doing too much work in the
 *   network stack's callback function.
 ******************************************************************/

VOID
AppS2wHal_NetRecvTask(UINT32 ctx)
{
    INT32 dataLen=0,buffOfset,totalBytesToSnd;
    UINT8 cid,newcid,status;
    INT32 new_sd;
    struct sockaddr_in addr;
#ifdef S2W_IPv6_SUPPORT
    struct sockaddr_in6 fromAddr;
    INT32 addrlen1 = sizeof(struct sockaddr_in6);
    S2W_IPv6ADDR_T ipv6;

#endif
    INT32 addrlen = sizeof(struct sockaddr_in);//, ret;
    
    UINT16 port;
    S2W_IPADDR_T ip;
    S2W_MSG_T recvMsg;
    UINT8 *rxDataBuf;
    INT32 semStat;
    UINT32 sentLen=0;

    //UINT8 status, *rcvBuf = NULL;
    //UINT32 rcvLen;
    INT32 ret;
#ifdef S2W_THROUGHPUT_TEST                       	
	UINT32 *seqNo;	
	GSN_SYSTEM_TIME_T endTime,totalTime;	
#endif	
#ifdef S2W_HTTPC_SUPPORT
    ttHttpcConEntryPtr      conEntryPtr;
#ifndef S2W_IP2WIFI_SUPPORT
#ifdef S2W_HTTPS_SUPPORT

    UINT8 *rcvBuf = NULL;
    UINT32 rcvLen;
#endif
#endif
#endif
    //INT32 semStat;
	GSN_STATUS sslRet=GSN_FAILURE;
#ifndef S2W_IP2WIFI_SUPPORT
    INT32 sslDataRxTimeout=5;
#endif
    UINT8 socketRecvLoopCount=0;

    while (1)

    {
        /* Task done with job, stop monitoring */
        /*GsnSq_TaskMonitorEnd( APP_SQ_NET_RX_TASK_ID);*/

        GsnOsal_QueueGet(&s2wNetQueue, (UINT8 *)&recvMsg, GSN_OSAL_WAIT_FOREVER);
        /* Task starting to process a job, start monitoring */
        switch (recvMsg.msgType)
        {
			case S2W_RECV_TYPE_SOCK_DATA_DISCONNECT:
            case S2W_RECV_TYPE_SOCKET:
            {
                cid = AppS2wHal_CidFind(recvMsg.rData.dataSock);
                if (cid == INVALID_CID)
                {
                	#ifdef S2W_SEPARATE_NET_RX_TASK
                    	continue;
					#else
						break;
					#endif /*S2W_SEPARATE_NET_RX_TASK*/
                }
                S2W_ASSERT(s2wCidList[cid].conType != 0);

					INT32 intrStatus;

					intrStatus = GsnOsal_IntrDisable();
					s2wCidList[cid].s2wSockDataPending = 0;
					/*re-enable all interrupts */
                    GsnOsal_IntrEnable(intrStatus );
                    socketRecvLoopCount=0;
                do
                {
                    socketRecvLoopCount++;
                    GsnSq_TaskMonitorStart(APP_CFG_SQ_NETRX_TASK_ID, cid);
                    if (s2wCidList[cid].conType == UDP)
                    {
#ifdef S2W_IPv6_SUPPORT                              
                      if(s2wCidList[cid].addrType & ADDR_TYPE_IPv6)
                        dataLen = recvfrom(recvMsg.rData.dataSock,(char *)s2wRxBuf,sizeof(s2wRxBuf), 0,(struct sockaddr *) &fromAddr, &addrlen1);
                      else
#endif //S2W_IPv6_SUPPORT
#if defined(S2W_DTLS_CLIENT_SUPPORT)
              			if (s2wCidList[cid].sslflag == TRUE /*&& (dataLen > 0)*/)
                        {
                            dataLen = sizeof(s2wRxBuf);
                            addrlen = sizeof(struct sockaddr_in);
              			    GsnDtls_Receive( (GSN_DTLS_CONN_T *)s2wCidList[cid].ssl.sslConn,
              				    /*rxDataBuf*/s2wRxBuf, (UINT32*)&dataLen, 0/*MSG_DONTWAIT*/,
              				    (struct sockaddr *)&addr, &addrlen );
              			}
              			else
#endif
                        dataLen = recvfrom(recvMsg.rData.dataSock, (char *)s2wRxBuf,
                                  sizeof(s2wRxBuf), 0,
                                  (struct sockaddr *)&addr, &addrlen);

                        if (dataLen > 0)
                        {
                            if( s2wCidList[cid].conMode == S2W_NETDATA_MODE_SERVER)
                            {
#ifdef S2W_IPv6_SUPPORT                              
                              if(s2wCidList[cid].addrType & ADDR_TYPE_IPv6)
                              {
                                //port = ntohs(fromAddr.sin6_port);
                                port = htons(fromAddr.sin6_port);
                                memcpy(ipv6,fromAddr.sin6_addr._S6_un._S6_u32,sizeof(ipv6));
                                GSN_IPv6_CHANGE_ENDIAN((UINT32 *)ipv6);
                              }
                              else
#endif //S2W_IPv6_SUPPORT                                
                              {                                
                                port = htons(addr.sin_port);
                                memcpy(ip, &(addr.sin_addr.s_addr), sizeof(ip));
                                *(ULONG*)ip = htonl(*(ULONG*)ip);
                              }
                            }
                            else  /* Client  */
                            {
#ifdef S2W_IPv6_SUPPORT
                              if(s2wCidList[cid].addrType & ADDR_TYPE_IPv6)  /* IPv6 */
                              {
                                //if(!memcmp(s2wCidList[cid].remoteIpv6,fromAddr.sin6_addr._S6_un._S6_u32,sizeof(fromAddr.sin6_addr._S6_un._S6_u32)))
                                {
                                  //port = ntohs(fromAddr.sin6_port);
                                  port = htons(fromAddr.sin6_port);
                                  memcpy(ipv6,fromAddr.sin6_addr._S6_un._S6_u32,sizeof(ipv6));
                                  GSN_IPv6_CHANGE_ENDIAN(ipv6);
                                }
                                                                
                              }
                              else 
                              
#endif  //S2W_IPv6_SUPPORT
                              {

                                    //port = ntohs(addr.sin_port);
                                port = 0;
                                    //memcpy(ip, &(addr.sin_addr.s_addr), sizeof(ip));
                                    //*(ULONG*)ip = htonl(*(ULONG*)ip);
                                *(ULONG*)ip=0;
                                }

                              }
                            }
                        }
                    else
                    {
#ifndef S2W_IP2WIFI_SUPPORT
                        /*dataLen = recv(recvMsg.rData.dataSock, (char *)s2wRxBuf,
                        sizeof(s2wRxBuf), MSG_DONTWAIT);*/
                        port = 0;

                        if (s2wCidList[cid].sslflag == TRUE /*&& (dataLen > 0)*/)
                        {
#if defined(S2W_SSL_CLIENT_SUPPORT) || defined(S2W_SSL_SERVER_SUPPORT)
                            s2wCidList[cid].ssl.sslConn->sslState = GSN_SSL_STATE_INIT;
#ifdef S2W_SSL_SERVER_SUPPORT
							if(TRUE == s2wCidList[cid].sslRemoteCliConctng)
							{
								/* a Remote client is setting up the ssl connection with tcp server.
								  ssl connenction is done in WDD task context*/
								//UINT32 msg;
								GSN_SSL_RECV_PARAMS_T sslRecvParams;
								sslRecvParams.pSslConn = s2wCidList[cid].ssl.sslConn;
								sslRecvParams.sockDes = s2wCidList[cid].sd;
								sslRecvParams.rxDataBuf = &rxDataBuf;
								sslRecvParams.rxDataLen = (UINT32 *)&dataLen;
								sslRecvParams.timeOut = 5;
								//GsnOsal_SemCreate(&s2wCidList[cid].s2wSslRecvInProgress, 0);
								s2wCidList[cid].pSslRecvParams = &sslRecvParams;
								//msg = (S2W_MOD_NOTIF_CONN_START + cid);
								//GsnMsgHandler_Post(s2wappMainTaskCtxt->pMsgHdlrExecInWddTsk, &msg);
								//GsnOsal_SemAcquire(&s2wCidList[cid].s2wSslRecvInProgress,GSN_OSAL_WAIT_FOREVER);
								ret = s2wCidList[cid].recvStatus;
								//GsnOsal_SemDelete(&s2wCidList[cid].s2wSslRecvInProgress);
								port = htons(s2wCidList[cid].remotePort);
								memcpy(ip, &(s2wCidList[cid].remoteIp), sizeof(ip));
								*(UINT32*)ip = htonl(*(UINT32*)ip);
								ret = AppS2wProcess_NetAccept(s2wCidList[cid].serverCid,
															  cid, ip,port);
						        if (ret != S2W_SUCCESS)
						        {
						            soc_close(s2wCidList[cid].sd);
						            return;
						        }
#if 1
                            	ret = GsnSsl_DataReceive(s2wCidList[cid].ssl.sslConn,
                                                         s2wCidList[cid].sd,
                                                         &rxDataBuf,
                                                         (UINT32 *)&dataLen,
                                                         5);
#endif
								s2wCidList[cid].sslRemoteCliConctng = FALSE;
							}
							else
#endif
							{
								if(0 == sslDataRxTimeout)
								{
									/* if the timeout is zero, make the socket as non blocking*/
									fcntl(s2wCidList[cid].sd, F_SETFL, O_NONBLOCK);
								}
                            	sslRet = GsnSsl_DataReceive(s2wCidList[cid].ssl.sslConn,
                                                         s2wCidList[cid].sd,
                                                         &rxDataBuf,
                                                         (UINT32 *)&dataLen,
                                                         sslDataRxTimeout);
								if(0 == sslDataRxTimeout)
								{
									/*restore back to blocking*/
									fcntl(s2wCidList[cid].sd, F_SETFL, 0);
								}
							}
                            if(sslRet != GSN_SUCCESS)
                            {/*Error!*/
                            	dataLen = 0;/*Need to set explicitely as DataReceive() does not do so*/
                            }
							sslDataRxTimeout=1;
#endif
                        }
                        else if(s2wCidList[cid].httpflag ==  1)
                        { /* This section should be executed when http send not in progress.
                             This is ensured by opInProgress semophore */
#ifdef S2W_HTTPS_SUPPORT
                            conEntryPtr = (ttHttpcConEntryPtr)s2wCidList[cid].pHttpData->pHttpHandle;
                            semStat = GsnOsal_SemAcquire(&s2wCidList[cid].pHttpData->opInProgress, GSN_OSAL_NO_WAIT);
                            if((semStat == GSN_OSAL_SUCCESS) && (conEntryPtr->hconHttpType == GSN_HTTPS))
                            {
                                /* http send not in progress. Docode the data recieved */
                                ret = GsnHttps_DataReceive(conEntryPtr->hConSsl, s2wCidList[cid].sd, &rcvBuf, &rcvLen, 5);
                                if(rcvBuf != NULL)
                                {
                                    GsnSsl_Free(rcvBuf);
                                }
                                if(ret == GSN_SSL_CLOSE_ALERT)
                                {
                                    /* Recieved data is a Close alert. Send the alert back to server */
                                    GsnHttp_Alert(s2wCidList[cid].pHttpData->pHttpHandle);

                                }

                            }
                            dataLen = 0;
                            if(semStat == GSN_OSAL_SUCCESS)
                            {
                                GsnOsal_SemRelease(&s2wCidList[cid].pHttpData->opInProgress);
                            }
#endif
                        }

                        else
                        {
                          
#ifdef S2W_IPv6_SUPPORT
                          if(s2wCidList[cid].addrType & ADDR_TYPE_IPv6)
                            dataLen = recv(recvMsg.rData.dataSock, (char *)s2wRxBuf,sizeof(s2wRxBuf), 0);
                          else
#endif //S2W_IPv6_SUPPORT                          
                            dataLen = recv(recvMsg.rData.dataSock, (char *)s2wRxBuf,
                                      sizeof(s2wRxBuf), 0);
                        }
#endif
                    }
                    if (dataLen <= 0)
                    {
                        S2w_Debug("Data len: %d\r\n", dataLen);
						if(s2wCidList[cid].sslflag == TRUE && (sslRet == GSN_SUCCESS))
							dataLen=1;
                    }
                    else
                    {
                        if((s2wCidList[cid].sslflag == TRUE) && (s2wCidList[cid].conType == TCP))
                        {
                        	totalBytesToSnd = dataLen;
                        	buffOfset=0;
                       		while(totalBytesToSnd)
                       		{
                       			GsnSq_TaskMonitorStop( APP_CFG_SQ_NETRX_TASK_ID);
								GsnSq_TaskMonitorStart(APP_CFG_SQ_NETRX_TASK_ID, cid);
								sentLen =totalBytesToSnd >= S2W_RX_BUF_SIZE? S2W_RX_BUF_SIZE:totalBytesToSnd;
                        		FTW_NET_rx(cid, (rxDataBuf+buffOfset), sentLen, 
														(UINT8*)ip, port);
								buffOfset += sentLen;
								totalBytesToSnd -= sentLen;                        		
                        	}
                            GsnSsl_Free(rxDataBuf);
                        }
#if defined(S2W_DTLS_CLIENT_SUPPORT)
                        else if((s2wCidList[cid].sslflag == TRUE) && (s2wCidList[cid].conType == UDP))
                        {
                            /* For DTLS client*/
                            FTW_NET_rx(cid, s2wRxBuf, dataLen, (UINT8*)ip, port);
                            dataLen = 0;
							GsnSsl_Free(rxDataBuf);
                        }
#endif
                        else
                        {
#ifdef S2W_THROUGHPUT_TEST                       
                        	if(s2wCidList[cid].tpTestInProgress == 0)	
                        	{
#endif                        	
#ifdef S2W_IPv6_SUPPORT
                          if(s2wCidList[cid].addrType & ADDR_TYPE_IPv6)
                            FTW_NET_rx(cid, s2wRxBuf, dataLen, (UINT8*)ipv6, port);
                          else
#endif
                            FTW_NET_rx(cid, s2wRxBuf, dataLen, (UINT8*)ip, port);
#ifdef S2W_THROUGHPUT_TEST                       
                        	}
							else
							{
								if(s2wCidList[cid].stats.packetsReceived== 0)
								{
									s2wCidList[cid].stats.startTime = GsnSoftTmr_CurrentSystemTime();										
								}
								//dataPattern = (UINT32 *)&s2wRxBuf[8];		
								if(s2wCidList[cid].conType == UDP)
								{
									seqNo= (UINT32 *)&s2wRxBuf[0];																
									if(s2wCidList[cid].stats.udpNxtSeqNo  !=  *seqNo )
										s2wCidList[cid].stats.rxErr += (*seqNo - s2wCidList[cid].stats.udpNxtSeqNo);
									s2wCidList[cid].stats.udpNxtSeqNo =  *seqNo + 1; 
									s2wCidList[cid].stats.packetsReceived++;
									s2wCidList[cid].stats.bytesReceived += dataLen;										
								}
								else
								{
									s2wCidList[cid].stats.packetsReceived++;
									s2wCidList[cid].stats.bytesReceived += dataLen;
								}
								if(s2wCidList[cid].testMode == 4)
								{
									endTime = GsnSoftTmr_CurrentSystemTime();									
									totalTime = SYSTIME_TO_SEC(endTime - s2wCidList[cid].stats.startTime);
									s2wCidList[cid].stats.totalTime=totalTime;
								}
								else if(s2wCidList[cid].bytesToReceive == s2wCidList[cid].stats.bytesReceived)
								{
									endTime = GsnSoftTmr_CurrentSystemTime();									
									totalTime = SYSTIME_TO_SEC(endTime - s2wCidList[cid].stats.startTime);
									if(s2wCidList[cid].conType == UDP)
									{
									    S2w_Printf("\r\n Packet Received  : %d",s2wCidList[cid].stats.packetsReceived);
										S2w_Printf("\r\n Packet Lost      : %d",s2wCidList[cid].stats.rxErr);
									}
									else
									{
										S2w_Printf("\r\n Bytes Received   : %lld",s2wCidList[cid].stats.bytesReceived); 
									}									
									S2w_Printf("\r\n Total Time Taken : %lld sec",totalTime);																		
									S2w_Printf("\r\n Throuhput        : %lld Kbps",((s2wCidList[cid].stats.bytesReceived*8)/(1024*totalTime)));										
									s2wCidList[cid].tpTestInProgress=0;										
									if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
									{
									    s2wSpiFs_Flush();
                                    }
								}
                        	}
#endif                          						
                        }
                    }
                    GsnSq_TaskMonitorStop( APP_CFG_SQ_NETRX_TASK_ID);
                }while((dataLen>0) && (socketRecvLoopCount<s2wCurrent.socRdCnt)); // max three packets read at a time, if data pending schedule the
                                                                // task again so that data from other socket not get delayed.

                // post a msg to its own
                if((dataLen > 0) && (s2wCidList[cid].s2wSockDataPending == 0))
                {

                    intrStatus = GsnOsal_IntrDisable();
                    s2wCidList[cid].s2wSockDataPending = 1;
                    /*re-enable all interrupts */
                    GsnOsal_IntrEnable(intrStatus );
                    GsnOsal_QueuePut(&s2wNetQueue,(UINT8*)&recvMsg);
                    break;
			    }

                if(S2W_RECV_TYPE_SOCK_DATA_DISCONNECT == recvMsg.msgType)

                {
#if defined(S2W_SSL_CLIENT_SUPPORT) || defined(S2W_SSL_SERVER_SUPPORT)
                    if (s2wCidList[cid].sslflag == TRUE)
                    {
                        if(s2wCidList[cid].s2wUsrCloseFlag)
                        {
                            /* stop the http close waiting timer */
							if(GSN_SUCCESS == AppS2wHal_TimerStop(&s2wCidList[cid].s2wUserCloseTimer))
							{
							  	/* release the semaphore so the close can finish */
								GsnOsal_SemRelease(&s2wCidList[cid].s2wUserCloseInProgress);
							}

							#ifdef S2W_SEPARATE_NET_RX_TASK
                            	continue;/*!! Donot remove this*/
							#else
								break; /*!! Do not remove this*/
							#endif/*S2W_SEPARATE_NET_RX_TASK*/
                        }
						/* Close is not initialted by user. s2wCidList[cid].s2wUsrCloseFlag = 0
						That's why we are here*/
					   	GsnSsl_Alert(s2wCidList[cid].ssl.sslConn, s2wCidList[cid].sd);

                    }
#else
					if(0)
					{
                    }
#endif      					
#ifdef S2W_HTTPC_SUPPORT
					else if(s2wCidList[cid].httpflag && s2wCidList[cid].pHttpData)
					{

#ifdef S2W_HTTPS_SUPPORT
                        conEntryPtr = (ttHttpcConEntryPtr)s2wCidList[cid].pHttpData->pHttpHandle;
						if(conEntryPtr->hconHttpType == GSN_HTTPS && s2wCidList[cid].s2wUsrCloseFlag)
						{
							/* stop the http close waiting timer */
							if(GSN_SUCCESS == AppS2wHal_TimerStop(&s2wCidList[cid].s2wUserCloseTimer))
							{
								/* release the semaphore so the close can finish */
								GsnOsal_SemRelease(&s2wCidList[cid].s2wUserCloseInProgress);
							}

							#ifdef S2W_SEPARATE_NET_RX_TASK
                            	continue;
							#else
								break;
							#endif/*S2W_SEPARATE_NET_RX_TASK*/
						}
						/* Close is not initialted by user. s2wCidList[cid].s2wUsrCloseFlag = 0
						That's why we are here*/
						if(conEntryPtr->hconHttpType == GSN_HTTPS)
						{
							GsnOsal_SemAcquire(&s2wCidList[cid].pHttpData->opInProgress, GSN_OSAL_WAIT_FOREVER);
							GsnSsl_Alert(s2wCidList[cid].ssl.sslConn, s2wCidList[cid].sd);
							GsnOsal_SemRelease(&s2wCidList[cid].pHttpData->opInProgress);
						}
#endif /*S2W_HTTPS_SUPPORT*/
						if(s2wCidList[cid].httpflag && s2wCidList[cid].pHttpData && s2wCidList[cid].pHttpData->httpType == GSN_HTTP)
						{
							GsnOsal_SemAcquire(&s2wCidList[cid].pHttpData->opInProgress, GSN_OSAL_WAIT_FOREVER);
							/* opInProgress semaphore will be deleted in AppS2wHal_NetClose, release it here */
							GsnOsal_SemRelease(&s2wCidList[cid].pHttpData->opInProgress);
						}
					}

#endif

					status = AppS2wHal_NetClose(cid);
					if(s2wCidList[cid].s2wUsrCloseFlag == 0 && status == S2W_SUCCESS)
					{
/* Check the L2 connection exists
    Bug FIX 5083 - L2 disconnection while getting the data throws ERROR:SOCKET FAILURE and Disassociation Event
*/						
						if(TRUE != GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx))
						{
							break;
						}
											
    	                GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
#ifdef S2W_ASYNC_MSG
						if(s2wCurrent.asyncMsgFormat)
						{
							AppS2wProcess_AsyncStatusNotify(S2W_ASYNC_ECIDCLOSE, cid);
						}
						else
#endif
                   		{
                        	AppS2wProcess_StatusNotify(S2W_ECIDCLOSE, cid);
                    	}
	                    GsnOsal_SemRelease(&s2wSyncSemID);
					}
                    if(((s2wCurrent.ncmAutoLvl != 0)  && (cid == s2wCurrent.ncmAutoCid) && (s2wCurrent.ncmAutoMgr == 1))
                       || profile_params.autoConnect )
                    {
                        UINT32 message = APP_EVENT_NCM_L4CONNECT;
                        (s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
                    }
                }
            }
            break;

#ifndef S2W_IP2WIFI_SUPPORT
            case S2W_RECV_TYPE_SOCK_ERROR:

                cid = AppS2wHal_CidFind(recvMsg.rData.dataSock);
                if (cid == INVALID_CID)
                {
                	#ifdef S2W_SEPARATE_NET_RX_TASK
                    	continue;
					#else
						break;
					#endif /*S2W_SEPARATE_NET_RX_TASK*/
                }
                // if data is pending on that socket defer the socket close
                if(s2wCidList[cid].s2wSockDataPending)
                {
					GsnOsal_QueuePut(&s2wNetQueue,(UINT8*)&recvMsg);
					break;
				}
#if defined(S2W_SSL_CLIENT_SUPPORT) || defined(S2W_SSL_SERVER_SUPPORT)
				if (s2wCidList[cid].sslflag == TRUE)
                {
                     if(s2wCidList[cid].s2wUsrCloseFlag)
                     {
                        /* stop the http close waiting timer */
						if(GSN_SUCCESS == AppS2wHal_TimerStop(&s2wCidList[cid].s2wUserCloseTimer))
						{
						  	/* release the semaphore so the close can finish */
							GsnOsal_SemRelease(&s2wCidList[cid].s2wUserCloseInProgress);
						}
                          #ifdef S2W_SEPARATE_NET_RX_TASK
                          	continue;
						  #else
						  	break;
						  #endif /*S2W_SEPARATE_NET_RX_TASK*/
                     }
                }
#ifdef S2W_HTTPS_SUPPORT
				else if(s2wCidList[cid].httpflag ==  1 && s2wCidList[cid].pHttpData)
                {
					conEntryPtr = (ttHttpcConEntryPtr)s2wCidList[cid].pHttpData->pHttpHandle;

					if(conEntryPtr->hconHttpType == GSN_HTTPS && s2wCidList[cid].s2wUsrCloseFlag)
					{
						/* stop the http close waiting timer */
						if(GSN_SUCCESS == AppS2wHal_TimerStop(&s2wCidList[cid].s2wUserCloseTimer))
						{
						  	/* release the semaphore so the close can finish */
							GsnOsal_SemRelease(&s2wCidList[cid].s2wUserCloseInProgress);
						}
						#ifdef S2W_SEPARATE_NET_RX_TASK
							continue; /*!! Donot remove this*/
						#else
							break; /*!! Donot remove this*/
						#endif /*S2W_SEPARATE_NET_RX_TASK*/
					}
                }
#endif /*GSN_HTTPS_SUPPORT*/
#endif
    			AppS2wHal_NetClose(cid);
				/* Check the L2 connection exists
					Bug FIX 5083 - L2 disconnection while getting the data throws ERROR:SOCKET FAILURE and Disassociation Event
				*/						
				if(TRUE != GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx))
				{
					break;
				}


                GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
#ifdef S2W_UART_ENABLE
                //while(0 == S2wUart_TxStatusGet());
#endif
                if((!s2wAutoConnState ) ||(( s2wState == S2W_STATE_CMD) && (s2wIsAutoconnected)))
                {
#ifdef S2W_ASYNC_MSG                
					if(s2wCurrent.asyncMsgFormat)
					{
						AppS2wProcess_AsyncStatusNotify(S2W_ASYNC_SOCKFAILURE, cid);
					}
					else
#endif
	                {
	                    AppS2wProcess_StatusNotify(S2W_SOCKFAILURE, cid);
	                }
			    }
#ifdef S2W_UART_ENABLE
                // while(0 == S2wUart_TxStatusGet());
#endif
                 GsnOsal_SemRelease(&s2wSyncSemID);
             
                if(((s2wCurrent.ncmAutoLvl != 0)  && (cid == s2wCurrent.ncmAutoCid) && (s2wCurrent.ncmAutoMgr == 1))
                   || profile_params.autoConnect )
                {
                    UINT32 message = APP_EVENT_NCM_L4CONNECT;
                    //S2w_Printf("\r\n Rclose-connect back\r\n");
                    (s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
                }
            break;

            case S2W_RECV_TYPE_SOCK_DISCONNECT:

                cid = AppS2wHal_CidFind(recvMsg.rData.dataSock);
                if (cid == INVALID_CID)
                {
                	#ifdef S2W_SEPARATE_NET_RX_TASK
                    	continue;
					#else
						break;
					#endif /*S2W_SEPARATE_NET_RX_TASK*/
                }
                // if data is pending on that socket defer the socket close
                if(s2wCidList[cid].s2wSockDataPending)
                {
					GsnOsal_QueuePut(&s2wNetQueue,(UINT8*)&recvMsg);
					break;
				}

#if defined(S2W_SSL_CLIENT_SUPPORT) || defined(S2W_SSL_SERVER_SUPPORT)
				if (s2wCidList[cid].sslflag == TRUE)
                {
                     if(s2wCidList[cid].s2wUsrCloseFlag)
                     {
						  if(GSN_SUCCESS == AppS2wHal_TimerStop(&s2wCidList[cid].s2wUserCloseTimer))
						  {
							GsnOsal_SemRelease(&s2wCidList[cid].s2wUserCloseInProgress);
						  }
                          #ifdef S2W_SEPARATE_NET_RX_TASK
                          	continue;
						  #else
							break;
						  #endif /*S2W_SEPARATE_NET_RX_TASK*/
                     }
 					/* Send Alert*/
        			GsnSsl_Alert(s2wCidList[cid].ssl.sslConn, s2wCidList[cid].sd);
                }
#else
				if(0)
				{
				}
#endif    
#ifdef S2W_HTTPC_SUPPORT	
				else if(s2wCidList[cid].httpflag ==  1 && s2wCidList[cid].pHttpData)
                {

					semStat =GsnOsal_SemAcquire(&s2wCidList[cid].pHttpData->opInProgress, GSN_OSAL_WAIT_FOREVER);
#ifdef S2W_HTTPS_SUPPORT                
					conEntryPtr = (ttHttpcConEntryPtr)s2wCidList[cid].pHttpData->pHttpHandle;
					/* The remote close can along with the data so if the send acquired the semaphore then need to
					wait here so that the close operation can be performed.
					*/
					if(conEntryPtr->hconHttpType == GSN_HTTPS && s2wCidList[cid].s2wUsrCloseFlag)
					{
						/* stop the http close waiting timer */
						if(GSN_SUCCESS == AppS2wHal_TimerStop(&s2wCidList[cid].s2wUserCloseTimer))
						{
						  	/* release the semaphore so the close can finish */
							GsnOsal_SemRelease(&s2wCidList[cid].s2wUserCloseInProgress);
						}

						#ifdef S2W_SEPARATE_NET_RX_TASK
							continue; /*!! Donot remove this*/
						#else
							break; /*!! Donot remove this*/
						#endif /*S2W_SEPARATE_NET_RX_TASK*/
					}
					/* The close is from remote and no alert gone out. Send an alert */
					GsnHttp_Alert(s2wCidList[cid].pHttpData->pHttpHandle);
#endif
					//if(s2wCidList[cid].pHttpData->httpType == GSN_HTTP)
						//GsnOsal_SemAcquire(&s2wCidList[cid].pHttpData->opInProgress, GSN_OSAL_WAIT_FOREVER);
					GsnOsal_SemRelease(&s2wCidList[cid].pHttpData->opInProgress);
				}

#endif
				status = AppS2wHal_NetClose(cid);
				/* Check the L2 connection exists
					Bug FIX 5083 - L2 disconnection while getting the data throws ERROR:SOCKET FAILURE and Disassociation Event
				*/						
				if(TRUE != GsnWdd_AssocStatusGet(&s2wappMainTaskCtxt->if0.wddCtx))
				{
					break;
				}

                
				
				if(s2wCidList[cid].s2wUsrCloseFlag == 0 && status == S2W_SUCCESS)
				{
					GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
					if((!s2wAutoConnState ) ||(( s2wState == S2W_STATE_CMD) && (s2wIsAutoconnected)))
				 	{
#ifdef S2W_ASYNC_MSG
						if(s2wCurrent.asyncMsgFormat)
				   		{
					   		AppS2wProcess_AsyncStatusNotify(S2W_ASYNC_ECIDCLOSE, cid);
				   		}
				   		else
#endif
                		{
		                    AppS2wProcess_StatusNotify(S2W_ECIDCLOSE, cid);
        		        }
			       }                
					GsnOsal_SemRelease(&s2wSyncSemID);
				}
                
                
                if(((s2wCurrent.ncmAutoLvl != 0)  && (cid == s2wCurrent.ncmAutoCid) && (s2wCurrent.ncmAutoMgr == 1))
                   || profile_params.autoConnect )
                {

                    UINT32 message = APP_EVENT_NCM_L4CONNECT;
                    (s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
                }
            break;

#endif
#ifdef S2W_HTTPC_SUPPORT
            case S2W_RECV_TYPE_HTTPS_CLOSE:
				/*Control is here, becase an Alert has been received*/
                cid = AppS2wHal_CidFind(recvMsg.rData.dataSock);
                if (cid == INVALID_CID)
                {
                    #ifdef S2W_SEPARATE_NET_RX_TASK
                    	continue;
					#else
						break;
					#endif /*S2W_SEPARATE_NET_RX_TASK*/
                }
                // if data is pending on that socket defer the socket close
                if(s2wCidList[cid].s2wSockDataPending)
                {
					GsnOsal_QueuePut(&s2wNetQueue,(UINT8*)&recvMsg);
				}
				/*Send Alert back*/
                GsnHttp_Alert(s2wCidList[cid].pHttpData->pHttpHandle);

				/* Close HTTP connection*/
				AppS2wHal_HttpLocalClose(cid);

                GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
#ifdef S2W_UART_ENABLE
                //while(0 == S2wUart_TxStatusGet());
#endif
#ifdef S2W_ASYNC_MSG
                if(s2wCurrent.asyncMsgFormat)
                {
                    AppS2wProcess_AsyncStatusNotify(S2W_ASYNC_ECIDCLOSE, cid);
                }
                else
#endif
                {
                    AppS2wProcess_StatusNotify(S2W_ECIDCLOSE, cid);
                }
#ifdef S2W_UART_ENABLE
               // while(0 == S2wUart_TxStatusGet());
#endif
                GsnOsal_SemRelease(&s2wSyncSemID);

                break;
#endif
#ifdef S2W_IP2WIFI_SUPPORT
                case S2W_RECV_TYPE_RAWDATA:
                {

                    S2w_RawNetRx (recvMsg.rData.dataPtr, recvMsg.msgLen);

                }
                break;
#endif

#ifdef S2W_UNASSOC_TXRX_SUPPORT
                case S2W_RECV_TYPE_UAMDATA:
                {

                    S2w_UamRx (recvMsg.rData.dataPtr, recvMsg.msgLen);

                }
                break;
#endif

			    case S2W_RECV_TYPE_SOCK_ACCEPT:
			        newcid = AppS2wHal_CidFind(recvMsg.rData.dataSock);
			        cid = s2wCidList[newcid].serverCid;
			        new_sd =   s2wCidList[newcid].sd;
			        port = s2wCidList[newcid].remotePort;
#ifdef S2W_IPv6_SUPPORT
                    if(s2wCidList[newcid].addrType & ADDR_TYPE_IPv6)
                    {
                        ret = AppS2wProcess_NetAccept(cid, newcid, (UINT8*)s2wCidList[newcid].remoteIpv6, port);
				    }
				    else
#endif
                    {
		                memcpy((UINT8*)ip,s2wCidList[newcid].remoteIp,4);
		                *(UINT32*)ip = htonl(*(UINT32*)ip);
				        ret = AppS2wProcess_NetAccept(cid, newcid, (UINT8*)ip, port);
				    }
				    if (ret != S2W_SUCCESS)
				    {
					    soc_close(new_sd);
					    //return;
	                }
				break;
            default :
                break;
}

    }
}


/**
 ******************************************************************
 * @ingroup S2w-Application
<<<<<<< s2w_net_gainspan.c
 * @brief Get the free connection identifier.
 * @retval Connection Identifier on success
 *         Error on failure
 ******************************************************************/
UINT8
AppS2wHal_CidGet(VOID)
{
    INT32 i,j,k;
    j= ((s2wappMainTaskCtxt->lastCidCreated+1)&(MAX_CID_RANGE-1));
    for (i = j,k=0; k < MAX_CID_RANGE ;(i=((i+1)&(MAX_CID_RANGE-1))),k++)
    {
        if (s2wCidList[i].sd == CID_NOTINUSE)
        {
        	memset((INT8 *)&s2wCidList[i], 0, sizeof(S2W_CID_T));
			s2wCidList[i].sd = CID_NOTINUSE;
			s2wappMainTaskCtxt->lastCidCreated = i;
            return i;
        }
    }
    return INVALID_CID;
}


/**
 ******************************************************************
 * @ingroup S2w-Application
=======
>>>>>>> 1.48.2.11
 * @brief Searches for the connection identifier
 *         corresponding to specified socket descriptor.
 * @param  sd the socket descriptor to be searched in the list.
 * @retval Connection identifier on success (value 0 - F).
 *          Error on failure (value 0xFF).
 ******************************************************************/
UINT8
AppS2wHal_CidFind(INT32 sd)
{
    UINT32 i;
    for (i = 0; i < MAX_CID_RANGE; i++)
    {
        if (sd == s2wCidList[i].sd)
       {
           return i;
       }
    }
    return INVALID_CID;
}
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Callback registerd to the network stack to recieve the socket events.
 * @param sock - IN the Socket descriptor on which event occurred.
 * @param flags- IN bit mask for events.
 ******************************************************************/
PRIVATE VOID
AppS2wHal_RxCallBack(INT32 sock, NX_BSD_CB_EVENT_TYPE_T flags, UINT port)
{
    struct sockaddr_in srcAddr;
    UINT8 cid;
    INT32 dataLen;
    S2W_MSG_T recvMsg;
    //GSN_OSAL_ERROR_T err;
    cid = AppS2wHal_CidFind(sock);
    if (cid == INVALID_CID)
    {
        S2W_ASSERT(0);
        return;
    }
    if(s2wappMainTaskCtxt->dpSleep )

    {
        AppS2w_GpioWkUpDisable();
		AppS2w_ExitDpSleep();
    }
    /* Data is available     */
    if ((NX_BSD_CB_TCP_RECIEVE & flags) || (NX_BSD_CB_UDP_RECIEVE & flags))
    {

        recvMsg.rData.dataSock = sock;
        recvMsg.msgLen = 0;
		if (NX_BSD_CB_TCP_DISCONNECT & flags)
		{
	        recvMsg.msgType = S2W_RECV_TYPE_SOCK_DATA_DISCONNECT;
		}
		else
		{
			recvMsg.msgType = S2W_RECV_TYPE_SOCKET;
                }
		if((s2wCidList[cid].s2wSockDataPending !=1) ||
		   (recvMsg.msgType == S2W_RECV_TYPE_SOCK_DATA_DISCONNECT))
		{
			INT32 intrStatus;
            intrStatus = GsnOsal_IntrDisable();
            s2wCidList[cid].s2wSockDataPending = 1;
            /*re-enable all interrupts */
            GsnOsal_IntrEnable(intrStatus );
			GsnOsal_QueuePut(&s2wNetQueue,(UINT8*)&recvMsg);
            //err = AppS2wHal_NetRxMsgPost(&recvMsg);

		}

    }

    /* Incoming connection (TCP servers only) */
    if (NX_BSD_CB_TCP_LISTEN & flags)
    {
        UINT8 newcid;
        INT32 new_sd;
        S2W_IPADDR_T ip;
#ifdef S2W_IPv6_SUPPORT
        S2W_IPv6ADDR_T ipv6;
        struct sockaddr_in6 ClientAddr;
        INT32 Clientlen;
#endif
        UINT16 localport;
        INT32 ret;
        struct timeval TimeOut;
        dataLen = sizeof(srcAddr);

#ifdef S2W_IPv6_SUPPORT
      
        if(s2wCidList[cid].addrType & ADDR_TYPE_IPv6)
        {
          Clientlen = sizeof(struct sockaddr_in6); 
        new_sd = accept(sock, (struct sockaddr*)&ClientAddr, &Clientlen);
        }
        else
#endif
        {
        new_sd = accept(sock, (struct sockaddr *)&srcAddr, &dataLen);
	    }
        if (new_sd < 0)
        {
            return;
        }

        if ((newcid = AppS2wHal_CidGet()) == INVALID_CID)
        {
            soc_close(new_sd);
            return;
        }
		GsnOsal_SemAcquire ( &(s2wappMainTaskCtxt->s2wTcpClientCntSyncSem), GSN_OSAL_WAIT_FOREVER);
		if(s2wCidList[cid].maxConn <= s2wCidList[cid].clientConCount)
		{
			tfResetConnection(new_sd);
			tfClose(new_sd);
			GsnOsal_SemRelease( &(s2wappMainTaskCtxt->s2wTcpClientCntSyncSem));
            return;
        }
		GsnOsal_SemRelease( &(s2wappMainTaskCtxt->s2wTcpClientCntSyncSem));
        
        if (s2wCidList[cid].sslflag != TRUE)
        {
#ifdef S2W_IPv6_SUPPORT
            if(s2wCidList[cid].addrType & ADDR_TYPE_IPv6)
            {
                localport = htons(ClientAddr.sin6_port);
                memcpy(ipv6,ClientAddr.sin6_addr._S6_un._S6_u32,sizeof(ipv6));
                        GSN_IPv6_CHANGE_ENDIAN(ipv6);
        
                s2wCidList[newcid].addrType |= ADDR_TYPE_IPv6;
                memcpy(s2wCidList[newcid].remoteIpv6,(UINT8*)ipv6,16);
            }
            else
#endif //S2W_IPv6_SUPPORT
            {
                localport = htons(srcAddr.sin_port);
                memcpy(ip, &(srcAddr.sin_addr.s_addr), sizeof(ip));
                *(UINT32*)ip = htonl(*(UINT32*)ip);


                memcpy(s2wCidList[newcid].remoteIp,(UINT8*)ip,4);
	            *((ULONG*)s2wCidList[newcid].remoteIp) = htonl(*(ULONG*)s2wCidList[newcid].remoteIp);
	        }
	        ULONG rexTimeOut=75;
	        setsockopt(new_sd,IP_PROTOTCP,TCP_MAXRT,(void*)&rexTimeOut,4);
			// update the new cid table
            s2wCidList[newcid].conType = TCP;
            s2wCidList[newcid].conMode = S2W_NETDATA_MODE_CLIENT;
            s2wCidList[newcid].sd = new_sd;
            s2wCidList[newcid].remotePort = localport;
	        s2wCidList[newcid].serverCid = cid;
            // fill the msg que structure
		    recvMsg.msgType = S2W_RECV_TYPE_SOCK_ACCEPT;
		    recvMsg.rData.dataSock = new_sd;
		    recvMsg.msgLen = 0;
		    // post a msg to netRx task
			GsnOsal_QueuePut(&s2wNetQueue,(UINT8*)&recvMsg);
        }
        
#ifdef S2W_SSL_SERVER_SUPPORT
        if (s2wCidList[cid].sslflag == TRUE)
        {



        localport = htons(srcAddr.sin_port);
        memcpy(ip, &(srcAddr.sin_addr.s_addr), sizeof(ip));
        *(UINT32*)ip = htonl(*(UINT32*)ip);




            s2wCidList[newcid].ssl.sslServer =
                GsnSsl_Accept( s2wCidList[cid].ssl.sslServer );
            if( NULL == s2wCidList[newcid].ssl.sslServer )
            {
                soc_close(new_sd);
                return;
            }

        s2wCidList[newcid].conType = TCP;
        s2wCidList[newcid].conMode = S2W_NETDATA_MODE_CLIENT;
        s2wCidList[newcid].sd = new_sd;
        s2wCidList[newcid].remotePort = localport;
        memcpy(s2wCidList[newcid].remoteIp,(UINT8*)ip,4);
		s2wCidList[newcid].serverCid = cid;
        *((ULONG*)s2wCidList[newcid].remoteIp) = htonl(*(ULONG*)s2wCidList[newcid].remoteIp);


            s2wCidList[newcid].sslflag = TRUE;
	        s2wCidList[newcid].sslRemoteCliConctng = TRUE;
			GsnOsal_SemCreate(&s2wCidList[newcid].s2wUserCloseInProgress, 0);			
			AppS2wHal_TimerInit(&s2wCidList[newcid].s2wUserCloseTimer, AppS2wHal_HttpCloseTimeout, (VOID*)newcid);
        }
#endif

        TimeOut.tv_sec =  0;
        TimeOut.tv_usec = 1 * NX_MICROSECOND_PER_CPU_TICK;/* 1 tick*/
        ret = setsockopt(s2wCidList[newcid].sd,SOL_SOCKET,SO_RCVTIMEO,(void*)&TimeOut,8);
        if(ret < 0)
        {
            //AppS2wHal_NetClose(cid);
            //return;
        }
        nx_bsd_callback_register(s2wCidList[newcid].sd,AppS2wHal_RxCallBack, S2W_RXCALLBACK_FLAGS);
		GsnOsal_SemAcquire ( &(s2wappMainTaskCtxt->s2wTcpClientCntSyncSem), GSN_OSAL_WAIT_FOREVER);
		s2wCidList[cid].clientConCount++;
		GsnOsal_SemRelease( &(s2wappMainTaskCtxt->s2wTcpClientCntSyncSem));

        return;
    }

    /* Socket error */
    if (NX_BSD_CB_SOCKET_ERROR & flags)
    {
        if (s2wCidList[cid].conType != 0)
        {
			/* for auto connection (data pipe make the async gpio low-so that host will not send data)
			 */
		    if(s2wIsAutoconnected)
		    {
			   S2w_AsyncMsgGpioOp(0);
            }
           recvMsg.msgType = S2W_RECV_TYPE_SOCK_ERROR;
           recvMsg.rData.dataSock = sock;
           recvMsg.msgLen = 0;
           GsnOsal_QueuePut(&s2wNetQueue,(UINT8*)&recvMsg);
        }

    }

    /* Remote close (for TCP sockets)
     */
    if (NX_BSD_CB_TCP_DISCONNECT & flags)
    {

        {
	        /* for auto connection (data pipe make the async gpio low-so that host will not send data)
			 */
		    if(s2wIsAutoconnected)
		    {
			   S2w_AsyncMsgGpioOp(0);
            }
           recvMsg.msgType = S2W_RECV_TYPE_SOCK_DISCONNECT;
           recvMsg.rData.dataSock = sock;
           recvMsg.msgLen = 0;

           GsnOsal_QueuePut(&s2wNetQueue,(UINT8*)&recvMsg);
        }
    }
}

UINT8
AppS2wHal_SockOpSet(S2W_SOCK_OP_T* params)
{
     //UINT8 status;
     VOID *optValue;
     S2W_CID_T *p;
     struct sock_linger linger;
     INT32 ret;
     
    if (params->cid >= MAX_CID_RANGE)
    {
        return S2W_EBADCID;
    }

    p = &s2wCidList[params->cid];
    if (p->sd == CID_NOTINUSE)
    {
        return S2W_EBADCID;
    }

    switch(params->param)
    {
        case SO_LINGER:
        {
            linger.l_onoff = TRUE;
            linger.l_linger = params->paramValue;
            optValue = (void*)&linger;
        }
        break;

        case SO_RCVTIMEO:
        {
            struct timeval RecvTime;
            RecvTime.tv_sec =  params->paramValue;
            RecvTime.tv_usec = 0;
            optValue = (void*)&RecvTime;
        }
        break;

        case SO_SNDTIMEO:
        {
            struct timeval SendTime;
            SendTime.tv_sec =  params->paramValue;
            SendTime.tv_usec = 0;
            optValue = (void*)&SendTime;
        }
        break;
        default:
        {
            optValue = (void*)&params->paramValue;
        }
        break;
    }
    
    ret = setsockopt(p->sd,params->type,params->param,optValue,params->paramSize);
    if(ret < 0)
    {
        return S2W_SOCKFAILURE;
    }
  
	return S2W_SUCCESS;
}


#if defined(S2W_SSL_CLIENT_SUPPORT)

extern S2W_SSL_CONF_T s2wSslConf;
UINT8
AppS2wHal_HttpCheckDns(UINT8 *reqPath)
{
    unsigned char *name = s2wSslConf.dnsNameBuf, *tmp = NULL;
    int i = 0;
    while((name[i]) && (i < s2wSslConf.dnsBufferLen))
    {
    	if(!strncmp((const char*)name+i, (const char*)reqPath, strlen((const char*)name+i)))
    	{
    		return S2W_SUCCESS;
    	}
        else if(('*' == *(name+i)) && ('.' == *(name+i+1)))
        {
            /* for removing 'www.' */
            tmp = (unsigned char*)strstr((const char*)reqPath, ".");
            tmp++;
            if(!strncmp((const char*)name+i+2, (const char*)reqPath, strlen((const char*)name+i+2)))
            {
                return S2W_SUCCESS;
            }

            else if(!strncmp((const char*)name+i+2, (const char*)tmp, strlen((const char*)name+i+2)))
            {
                return S2W_SUCCESS;
            }
            else
            {
                i += strlen((const char*)name+i);
                i++;
            }
        }
    	else
    	{
    		i += strlen((const char*)name+i);
    		i++;
    	}
    }
    if(1 == s2wCurrent.logLevel)
    {
    	S2w_Printf("\r\n warning: certificate mismatch");
    }
    else if(2 == s2wCurrent.logLevel)
    {
    	S2w_Printf("\r\n warning: certificate mismatch:");
    	name = s2wSslConf.dnsNameBuf;
        i = 0;
		while(*name && (i < s2wSslConf.dnsBufferLen))
		{
			S2w_Printf("\r\n %s", name);
    		name += strlen((const char*)name);
    		name++;
		}
    }
    return S2W_FAILURE;
}
UINT8 AppS2w_SslClientOpen(UINT8 cliCid, char* caCertName,
                           UINT8 *clientCertName, UINT8 *clientKeyName)
{
    //INT32 u32NoOfBytesSent;
    UINT32 status;
    UINT8 *certBuf = NULL;
    UINT16 caCertsize = 0;
    INT32  index=0;
    //void *pSslConn;
    GSN_SSL_CONN_PARAMS_T sslConnParams;
	UINT32 cid = cliCid;

#ifdef S2W_APP_SSL_PROVISION
    initStartTime = GsnSoftTmr_CurrentSystemTime();
#endif

    /* Avoid warning*/
    (void)certBuf ;
    (void)caCertsize ;
    memset((INT8 *)&sslConnParams, 0, sizeof(sslConnParams));
    if (s2wCidList[cid].sslflag == TRUE)
    {
        S2w_Printf("\r\nSocket is already SSL Enabled");
        return S2W_FAILURE;
    }

    if(caCertName != NULL)
    {
        index = S2wCert_SearchRamTable(caCertName);
        if(index == -1)
        {
        	index = S2wCert_FlashFileLoad(caCertName);
        }
        if(index == -1)
        {
            S2w_Printf("\n\rca Certificate %s Not Found", caCertName);
            return S2W_FAILURE;
        }

        // currently use the hardcoded certificate
        sslConnParams.caCertLen = *(UINT16 *)s2w_ssl_cert_table[index].certAddress;
        sslConnParams.caCert = s2w_ssl_cert_table[index].certAddress + 2;
        sslConnParams.caCertName = (char const*)caCertName;
    }


    if(clientCertName != NULL)
    {
        index = S2wCert_SearchRamTable((char*)clientCertName);
        if(index == -1)
        {
        	index = S2wCert_FlashFileLoad((char*)clientCertName);
        }
        if(index == -1)
        {
            S2w_Printf("\n\rclient Certificate %s Not Found", clientCertName);
            return S2W_FAILURE;
        }
        sslConnParams.clientCertLen = *(UINT16 *)s2w_ssl_cert_table[index].certAddress;
        sslConnParams.clientCert =  s2w_ssl_cert_table[index].certAddress + 2;
        sslConnParams.clientCertName = (char const*)clientCertName;

    }


    if(clientKeyName != NULL)
    {
        index = S2wCert_SearchRamTable((char*)clientKeyName);
        if(index == -1)
        {
        	index = S2wCert_FlashFileLoad((char*)clientKeyName);
        }
        if(index == -1)
        {
            S2w_Printf("\n\rclient key Certificate %s Not Found", clientKeyName);
            return S2W_FAILURE;
        }
        sslConnParams.clientKeyLen = *(UINT16 *)s2w_ssl_cert_table[index].certAddress;
        sslConnParams.clientKey =  s2w_ssl_cert_table[index].certAddress + 2;
        sslConnParams.clientKeyName = (char const*)clientKeyName;

    }

    nx_bsd_callback_register(s2wCidList[cid].sd, NULL, 0);    //deregister callback

    s2wCidList[cid].ssl.sslConn = (GSN_SSL_CONN_T*)MALLOC(sizeof(GSN_SSL_CONN_T));

    if(NULL == s2wCidList[cid].ssl.sslConn)
    {
        return S2W_FAILURE;
    }
	memset((INT8 *)s2wCidList[cid].ssl.sslConn, 0, sizeof(GSN_SSL_CONN_T));
       s2wCidList[cid].ssl.sslConn->sslState = GSN_SSL_STATE_INIT;
	s2wCidList[cid].ssl.sslConn->connMode = GSN_SSL_CONN_MODE_CLIENT;
	s2wCidList[cid].sslflag = TRUE;

#ifdef S2W_SSL_EXT_MAX_FRAG_LEN
    s2wCidList[cid].ssl.sslConn->maxFragLen = S2W_SSL_EXT_MAX_FRAG_LEN;
#else
    s2wCidList[cid].ssl.sslConn->maxFragLen = 0;
#endif

#if 1 /*SSl open is now done in Wdd task context*/
    status = GsnSsl_Open(s2wCidList[cid].ssl.sslConn, s2wCidList[cid].sd,
                         &sslConnParams);
#else
	{
		UINT32 msg;
		/*create open sem*/
		GsnOsal_SemCreate(&s2wCidList[cid].s2wUserOpenInProgress, 0);
		s2wCidList[cid].pConnOpenParams = &sslConnParams;
		/*post message */
		msg = (S2W_MOD_NOTIF_CONN_START + cid);
		GsnMsgHandler_Post(s2wappMainTaskCtxt->pMsgHdlrExecInWddTsk, &msg);
		GsnOsal_SemAcquire(&s2wCidList[cid].s2wUserOpenInProgress,GSN_OSAL_WAIT_FOREVER);
		status = s2wCidList[cid].openStatus;
		/*Delete the semaphore*/
		GsnOsal_SemDelete(&s2wCidList[cid].s2wUserOpenInProgress);
	}
#endif
    if(status == GSN_SUCCESS)
    {
        nx_bsd_callback_register(s2wCidList[cid].sd, AppS2wHal_RxCallBack, S2W_RXCALLBACK_FLAGS);
		s2wCidList[cid].sslflag = TRUE;

        GsnOsal_SemCreate(&s2wCidList[cid].s2wUserCloseInProgress, 0);
        AppS2wHal_TimerInit(&s2wCidList[cid].s2wUserCloseTimer, AppS2wHal_HttpCloseTimeout, (VOID*)cid);
        s2wCidList[cid].s2wUsrCloseFlag = 0;
        return S2W_SUCCESS;
    }
    else
    {
        s2wCidList[cid].sslflag = 0;
        if(s2wCidList[cid].ssl.sslConn != NULL)
        {
            gsn_free(s2wCidList[cid].ssl.sslConn);
        }

           soc_close(s2wCidList[cid].sd);
           s2wCidList[cid].sd = CID_NOTINUSE;
           s2wCidList[cid].localPort = 0;
           s2wCidList[cid].remotePort = 0;
        return S2W_FAILURE;
    }
}
#endif


#ifdef S2W_SSL_SERVER_SUPPORT
GSN_STATUS AppS2w_SslServerOpen(UINT8 cid, char* sslCACertName)
{
    //UINT8 retVal = S2W_FAILURE;
    //INT32 u32NoOfBytesSent;
    UINT32 /*status,*/ certLength ;
    INT32  index=0;
    SERVER_CERT_DETAIL_T certDetail;
#ifdef S2W_APP_SSL_PROVISION
    initStartTime = GsnSoftTmr_CurrentSystemTime();
#endif

    if (s2wCidList[cid].sslflag == TRUE)
    {
        S2w_Printf("\r\nSocket is already SSL Enabled");
        return S2W_FAILURE;
    }


    s2wCidList[cid].sslflag = TRUE;
    /* Fill the certificate details here. For testing it takes the below
       certificates */
 #ifndef S2W_SSL_SERVER_TEST
 	memset((INT8 *)&certDetail, 0, sizeof(certDetail));

    index = S2wCert_SearchRamTable(S2W_SSL_CERT_NAME_CA);
    if(index == -1)
    {
    	index = S2wCert_FlashFileLoad(S2W_SSL_CERT_NAME_CA);
    }
    if(index == -1)
    {
        S2w_Printf("\n\rCertificate %s Not Found", S2W_SSL_CERT_NAME_CA);
        return S2W_FAILURE;
    }

    certDetail.CaCertName = (char const *)s2w_ssl_cert_table[index].name;
    certDetail.CaCertLocation = s2w_ssl_cert_table[index].certAddress + 2;
    certLength = *(s2w_ssl_cert_table[index].certAddress + 1);
    certLength <<= 8;
    certLength = certLength | (*(s2w_ssl_cert_table[index].certAddress));
    certDetail.CaCertLen = certLength;

	index = S2wCert_SearchRamTable(S2W_SSL_CERT_NAME_SERVER);
    if(index == -1)
    {
    	index = S2wCert_FlashFileLoad(S2W_SSL_CERT_NAME_SERVER);
    }
    if(index == -1)
    {
        S2w_Printf("\n\rCertificate %s Not Found", S2W_SSL_CERT_NAME_SERVER);
        return S2W_FAILURE;
    }

    certDetail.ClientCertName = (char const *)s2w_ssl_cert_table[index].name;
    certDetail.ClientCertLocation = s2w_ssl_cert_table[index].certAddress + 2;
    certLength = *(s2w_ssl_cert_table[index].certAddress + 1);
    certLength <<= 8;
    certLength = certLength | (*(s2w_ssl_cert_table[index].certAddress));
    certDetail.ClientCertLen = certLength;

	index = S2wCert_SearchRamTable(S2W_SSL_CERT_NAME_KEY);
    if(index == -1)
    {
    	index = S2wCert_FlashFileLoad(S2W_SSL_CERT_NAME_KEY);
    }
    if(index == -1)
    {
        S2w_Printf("\n\rCertificate %s Not Found", S2W_SSL_CERT_NAME_KEY);
        return S2W_FAILURE;
    }
    
    certDetail.PrivateKeyName = (char const *)s2w_ssl_cert_table[index].name;
    certDetail.PrivateKeyLocation = s2w_ssl_cert_table[index].certAddress + 2;
    certLength = *(s2w_ssl_cert_table[index].certAddress + 1);
    certLength <<= 8;
    certLength = certLength | (*(s2w_ssl_cert_table[index].certAddress));
    certDetail.PrivateKeyLen = certLength;

#else

    certDetail.CaCertName = "ca_cert.crt";
    certDetail.CaCertLocation = ca_cert;
    certDetail.CaCertLen = sizeof(ca_cert);
    certDetail.ClientCertName = "server_cert.crt";
    certDetail.ClientCertLocation = server_cert;
    certDetail.ClientCertLen = sizeof(server_cert);
    certDetail.PrivateKeyName = "server_key.key";
    certDetail.PrivateKeyLocation = server_key;
    certDetail.PrivateKeyLen = sizeof(server_key);
#endif
    s2wCidList[cid].ssl.pServerCred =
        GsnSsl_ServerInit( &certDetail );

    if(s2wCidList[cid].ssl.pServerCred == NULL )
        return GSN_FAILURE;
    return S2W_SUCCESS;

}
#endif


PUBLIC GSN_STATUS
AppS2w_SslClose(UINT8 cid)
{
    if (s2wCidList[cid].sslflag == TRUE)
    {
    	if(s2wCidList[cid].conMode == S2W_NETDATA_MODE_CLIENT)
    	{
	        s2wCidList[cid].s2wUsrCloseFlag = 1;
			/* start a timer for 10 seconds, to come ou if the sever does not respond
			*/
	        AppS2wHal_TimerStart(&s2wCidList[cid].s2wUserCloseTimer, 1000);
			/* Send Alert*/
	        GsnSsl_Alert(s2wCidList[cid].ssl.sslConn, s2wCidList[cid].sd);
			/* wait on the semaphore to recv the remote close. This semaphore will be relesed in case of
			1. Socket error OR
			2. Remote socket close OR
			3. Socket Disconnect OR
			4. Time out
			*/
	        GsnOsal_SemAcquire(&s2wCidList[cid].s2wUserCloseInProgress, GSN_OSAL_WAIT_FOREVER);
    	}
		/*Either close or Timeout happened*/
		AppS2w_SslLocalClose(cid);
        return S2W_SUCCESS;
    }
    else
    {
        return S2W_EBADCID;
    }
}

PRIVATE GSN_STATUS
AppS2w_SslLocalClose(UINT8 cid)
{
    nx_bsd_callback_register(s2wCidList[cid].sd, NULL, 0);
	if(s2wCidList[cid].conMode == S2W_NETDATA_MODE_CLIENT)
    {
        GsnSsl_Close(s2wCidList[cid].ssl.sslConn);
	}
	else if(s2wCidList[cid].conMode == S2W_NETDATA_MODE_SERVER)
	{
#ifdef S2W_SSL_SERVER_SUPPORT
		GsnSsl_ServerDeInit(s2wCidList[cid].ssl.pServerCred);
#endif
	}
    s2wCidList[cid].ssl.sslConn = NULL;
    s2wCidList[cid].sslflag = FALSE;
    soc_close(s2wCidList[cid].sd);
    s2wCidList[cid].localPort = 0;
    s2wCidList[cid].remotePort = 0;

	/* Delete Close In progress semaphore*/
	GsnOsal_SemDelete(&s2wCidList[cid].s2wUserCloseInProgress);
	s2wCidList[cid].sd = CID_NOTINUSE;
    return S2W_SUCCESS;
}

PRIVATE VOID
AppS2wHal_HttpCloseTimeout(VOID *data)
{
    UINT32 cid = (UINT32)data;
    GsnOsal_SemRelease(&s2wCidList[cid].s2wUserCloseInProgress);
}

#ifdef S2W_HTTPC_SUPPORT
UINT8
AppS2wHal_HttpClose(UINT32 cid)
{
#ifdef S2W_HTTPS_SUPPORT
		ttHttpcConEntryPtr		conEntryPtr;
#endif
	s2wCidList[cid].s2wUsrCloseFlag = 1;
         if(s2wCidList[cid].pHttpData)
         {
#ifdef S2W_HTTPS_SUPPORT
		conEntryPtr = (ttHttpcConEntryPtr)s2wCidList[cid].pHttpData->pHttpHandle;
		if(conEntryPtr->hconHttpType == GSN_HTTPS)
            {

			AppS2wHal_TimerStart(&s2wCidList[cid].s2wUserCloseTimer, 1000);
			GsnHttp_Alert(s2wCidList[cid].pHttpData->pHttpHandle);
			GsnOsal_SemAcquire(&s2wCidList[cid].s2wUserCloseInProgress, GSN_OSAL_WAIT_FOREVER);
			AppS2wHal_HttpLocalClose(cid);
            }
		else /* normal http directly close the connection */
#endif    
		{
			AppS2wHal_HttpLocalClose(cid);
        }
	}
        else
        {
            return S2W_EBADCID;
    }
    return S2W_SUCCESS;
}

UINT8
AppS2wHal_HttpOpen(S2W_HTTP_DATA_T *pHttpData, UINT32 *cid)
{
    GSN_STATUS status;
    //UINT32 ip;
    GSN_HTTPC_CONN_PARAMS_T connParams;
	struct sockaddr_in sockAddr;
	INT32 len = sizeof(sockAddr), ret;

    *cid = AppS2wHal_CidGet();
    if (*cid == INVALID_CID)
    {
            return S2W_ENCID;
    }

    connParams.ConTimeout = pHttpData->connTimeOut;
    connParams.proxyPresent = pHttpData->proxyServer;
    connParams.type = pHttpData->httpType;
#if defined(S2W_SSL_CLIENT_SUPPORT)
    connParams.sslParams.caCert = pHttpData->pCaCert;
    connParams.sslParams.caCertLen = pHttpData->caCertLen;
    connParams.sslParams.caCertName = NULL;

    connParams.sslParams.clientCert= pHttpData->pClientCert;
    connParams.sslParams.clientCertLen = pHttpData->clientCertLen;
    connParams.sslParams.clientCertName = NULL;

    connParams.sslParams.clientKey = pHttpData->pClientKey;
    connParams.sslParams.clientKeyLen = pHttpData->clientKeyLen;
    connParams.sslParams.clientKeyName = NULL;
#endif    
	s2wCidList[*cid].httpflag = 1;
    s2wCidList[*cid].conMode = S2W_NETDATA_MODE_CLIENT_TRANSIENT;

#ifdef S2W_SSL_EXT_MAX_FRAG_LEN
    connParams.sslExtnMaxFragLen = S2W_SSL_EXT_MAX_FRAG_LEN;
#else
    connParams.sslExtnMaxFragLen = 0;
#endif

	//if(pHttpData->httpType == GSN_HTTP)
	{
		//httpConfInfo.pktPoolHndl = GsnNw_PktPoolHndlGet(&appCtx.nwCtx, GSN_NW_LBUF_PKT_POOL);
#if defined(S2W_SSL_CLIENT_SUPPORT)
    	if((pHttpData->httpType == GSN_HTTPS) && (0 != s2wSslConf.dnsBufferLen))
    	{
			connParams.dnsBuf = gsn_malloc(sizeof(GSN_SSL_DNS_BUF_INFO_T));
			s2wSslConf.dnsNameBuf = gsn_malloc(s2wSslConf.dnsBufferLen);
			memset(s2wSslConf.dnsNameBuf, 0, s2wSslConf.dnsBufferLen);
			connParams.dnsBuf->bufStart = connParams.dnsBuf->bufCurrent =  s2wSslConf.dnsNameBuf;
			connParams.dnsBuf->bufLen = s2wSslConf.dnsBufferLen;
    	}
    	else
    	{
    		connParams.dnsBuf = NULL;
    	}
#endif		
        status = GsnHttp_Start(&pHttpData->pHttpHandle, &pHttpData->sockAddr,
            &connParams, &httpConfInfo);
        if(NULL != connParams.dnsBuf)
        	gsn_free(connParams.dnsBuf);
        connParams.dnsBuf = NULL;
	}
	

    if(status != GSN_SUCCESS)
    {
		s2wCidList[*cid].httpflag = 0;
        return S2W_FAILURE;
    }

    s2wCidList[*cid].sd = ((ttHttpcConEntryPtr)pHttpData->pHttpHandle)->hconSd;
    s2wCidList[*cid].conType = TCP;
    s2wCidList[*cid].conMode = S2W_NETDATA_MODE_CLIENT;
    s2wCidList[*cid].remotePort = ntohs(pHttpData->sockAddr.ss_port);
    s2wCidList[*cid].pHttpData = pHttpData;
    s2wCidList[*cid].httpflag = 1;
	s2wCidList[*cid].serverCid = INVALID_CID;
	ret = getsockname(s2wCidList[*cid].sd, (struct sockaddr *)&sockAddr,&len);
    if(ret < 0)
    {
        AppS2wHal_NetClose(*cid);
        return S2W_SOCKFAILURE;
    }
	s2wCidList[*cid].localPort  = ntohs(sockAddr.sin_port);
    GsnOsal_SemCreate(&pHttpData->opInProgress, 1);
    /* create the samaphore for close */
    GsnOsal_SemCreate(&s2wCidList[*cid].s2wUserCloseInProgress, 0);
	s2wCidList[*cid].s2wUsrCloseFlag = 0;

    AppS2wHal_TimerInit(&s2wCidList[*cid].s2wUserCloseTimer, AppS2wHal_HttpCloseTimeout, (VOID*)*cid);

    memcpy(s2wCidList[*cid].remoteIp,(UINT8*)&(pHttpData->sockAddr.addr.ipv4.sin_addr.s_addr),4);

    /* register the callback for any socket events
     */
    nx_bsd_callback_register(s2wCidList[*cid].sd, AppS2wHal_RxCallBack, NX_BSD_CB_TCP_DISCONNECT |	NX_BSD_CB_SOCKET_ERROR);
    return S2W_SUCCESS;
}

PRIVATE UINT8
AppS2wHal_HttpLocalClose(UINT32 cid)
{
    UINT8 status = GSN_SUCCESS;
    if(!s2wCidList[cid].httpflag)
    {
        return GSN_SUCCESS;
    }
    s2wCidList[cid].httpflag = 0;
    /* close the connection and release the resources..*/
    status = GsnHttp_Close(s2wCidList[cid].pHttpData->pHttpHandle);
    if( status == GSN_SUCCESS )
    {
        s2wCidList[cid].httpflag = 0;
        s2wCidList[cid].conMode= 0;
    	s2wCidList[cid].conType = 0;
        if(s2wCidList[cid].pHttpData != NULL)
        {
            GsnOsal_SemDelete(&s2wCidList[cid].pHttpData->opInProgress);
            gsn_free(s2wCidList[cid].pHttpData);
            s2wCidList[cid].pHttpData = NULL;
        }

    }
    
    /* Delete Close In progress semaphore*/ 
    GsnOsal_SemDelete(&s2wCidList[cid].s2wUserCloseInProgress);
        s2wCidList[cid].sd = CID_NOTINUSE;
    return status;
}

PUBLIC S2W_HTTP_DATA_T *
AppS2wHal_HttpHandleGet(UINT8 cid)
{
    return s2wCidList[cid].pHttpData;
}

#ifdef S2W_HTTP_CUSTOM_SUPPORT
PUBLIC void
AppS2w_HttpRxHdrsCb (GSN_HTTPC_CONN_HANDLE conHandle,
                     INT32              statusCode,
                     INT8              *reasonPhrase,
                     INT8             **resHeadersPtr,
                     ttHttpcCustomHdr  *customHdrPtr)
{
    UINT8 cid;
    UINT32 i;
    UINT32 bitmap;
    UINT32 count;
    UINT32 len;
	UINT8 delim = ':';
    ttHttpcConEntryPtr conEntryPtr = (ttHttpcConEntryPtr)conHandle;
    INT8 header[15],headerLen;

    if((NULL == conEntryPtr) || (1 == httpConfInfo.hconHttpcHdrSent))
    {
        return;
    }
    cid = AppS2wHal_CidFind(conEntryPtr->hconSd);

    if((1 == httpConfInfo.sendStatus) && (NULL != reasonPhrase))
    {
        /* arg_len should be request uri length + 3 char of status code + 1 char of delim ':' */
        len = strlen(reasonPhrase) + 3 + 1;
        headerLen = sprintf((char *)header,"%cG%x%d%04d%03d%c", S2W_ESC, cid, S2W_HTTP_RESPONSE_LINE, len, statusCode, S2W_COLON);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
        AppS2wHal_CharNPut(header, headerLen);
        AppS2wHal_CharNPut(reasonPhrase, (len - 4));
#else
        AppS2wHal_CharNPut1(header, headerLen);
        AppS2wHal_CharNPut1(reasonPhrase, (len - 4));
#endif
    }
    /* If http header bitmap is not registered */
    if(0 == httpConfInfo.httpcHdrBmap)
    {
        goto AppS2w_HttpRxHdrsCbExit;
    }
    bitmap = httpConfInfo.httpcHdrBmap;
    count = 1;
    /* Parse all the headers given by Http server */
    for(i = 1; i < TM_HTTP_HEADER_COUNT ; i++)
    {
         if((NULL != resHeadersPtr[i]) && (bitmap & count))
         {
             /* hdr_len should be 2 chars of hdr_type number + hdr_val + 1 char of delim ':' */
             len = strlen(tvHttpHeaderNames[i]) + strlen(resHeadersPtr[i]) + 1;
             headerLen = sprintf((char *)header,"%cG%x%d%04d", S2W_ESC, cid, S2W_HTTP_HEADER, len);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
             AppS2wHal_CharNPut(header, headerLen);
             AppS2wHal_CharNPut(tvHttpHeaderNames[i], strlen(tvHttpHeaderNames[i]));
             AppS2wHal_CharNPut(&delim,1);
             AppS2wHal_CharNPut(resHeadersPtr[i], strlen(resHeadersPtr[i]));
#else
             AppS2wHal_CharNPut1(header, headerLen);
             AppS2wHal_CharNPut1(tvHttpHeaderNames[i], strlen(tvHttpHeaderNames[i]));
             AppS2wHal_CharNPut1(&delim,1);
             AppS2wHal_CharNPut1(resHeadersPtr[i], strlen(resHeadersPtr[i]));
#endif
         }
         count = (count << 1);
    }
    /* If user has registered for custom headers and custom headers are present, pass it */
    bitmap = bitmap >> 31;
    if((NULL != customHdrPtr) && (0 != customHdrPtr->hconCustomHdrcount) && (bitmap))
    {
        for(i = 0; i < customHdrPtr->hconCustomHdrcount ; i++)
        {
            len = strlen(customHdrPtr->hconCustomHeaderstype[i]) + strlen(customHdrPtr->hconCustomHeadersval[i] + 1);
            headerLen = sprintf((char *)header,"%cG%x%d%04d", S2W_ESC, cid, S2W_HTTP_HEADER, len);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
            AppS2wHal_CharNPut(header, headerLen);
            AppS2wHal_CharNPut(customHdrPtr->hconCustomHeaderstype[i], strlen(customHdrPtr->hconCustomHeaderstype[i]));
            AppS2wHal_CharNPut(&delim,1);
            AppS2wHal_CharNPut(customHdrPtr->hconCustomHeadersval[i], strlen(customHdrPtr->hconCustomHeadersval[i]));
#else
            AppS2wHal_CharNPut1(header, headerLen);
            AppS2wHal_CharNPut1(customHdrPtr->hconCustomHeaderstype[i], strlen(customHdrPtr->hconCustomHeaderstype[i]));
            AppS2wHal_CharNPut1(&delim,1);
            AppS2wHal_CharNPut1(customHdrPtr->hconCustomHeadersval[i], strlen(customHdrPtr->hconCustomHeadersval[i]));
#endif
        }
    }
AppS2w_HttpRxHdrsCbExit:
    httpConfInfo.hconHttpcHdrSent = 1;
#ifndef S2W_DUAL_INTERFACE_SUPPORT
    if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush();
    }
#else
    if(s2wappMainTaskCtxt->serialDeviceId1 == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush1();
    }
#endif
    return;
}
#endif

#endif


PUBLIC void
AppS2w_HttpRxBufferMgmtCb(VOID *context,
	             	 GSN_HTTPC_CONN_HANDLE conHandle,
                     INT8 *httpRxDataBuf,
                     INT32 httpRxDataLen,
                     INT32* rxBufferOffset)
{
    UINT8 cid;
    INT8 startMark[10];
    ttHttpcConEntryPtr conEntryPtr = (ttHttpcConEntryPtr)conHandle;

    cid = AppS2wHal_CidFind(conEntryPtr->hconSd);
#ifdef S2W_THROUGHPUT_TEST                       
	if( s2wCidList[cid].tpTestInProgress == 1)
	{
		s2wCidList[cid].stats.bytesReceived += httpRxDataLen;
	}
	else
#endif				
	{
    sprintf(startMark,"%c%c%x%04d", S2W_ESC, 'H', cid,httpRxDataLen);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
    AppS2wHal_CharNPut(startMark, strlen(startMark));

    AppS2wHal_CharNPut(httpRxDataBuf, httpRxDataLen);
#else
    AppS2wHal_CharNPut1(startMark, strlen(startMark));
    AppS2wHal_CharNPut1(httpRxDataBuf, httpRxDataLen);
#endif

    *rxBufferOffset = 0;
#ifndef S2W_DUAL_INTERFACE_SUPPORT
        if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
        {
             s2wSpiFs_Flush();
        }
#else
        if(s2wappMainTaskCtxt->serialDeviceId1 == S2W_PORT_FS_SPI)
        {
            s2wSpiFs_Flush1();
        }
#endif
	}
    return;

}
#ifdef S2W_GSLINK
PUBLIC VOID AppS2w_HttpdSemCreate(UINT8 cid)
{
	GsnOsal_SemCreate  ( &s2wCidList[cid].httpdCtx.s2wGsLinkemID, 0 );
}
PUBLIC VOID AppS2w_HttpSemAquire(UINT8 cid)
{
	GsnOsal_SemAcquire(&s2wCidList[cid].httpdCtx.s2wGsLinkemID,GSN_OSAL_WAIT_FOREVER);

}
PUBLIC VOID AppS2w_HttpSemRelease(UINT8 cid)
{
	GsnOsal_SemRelease(&s2wCidList[cid].httpdCtx.s2wGsLinkemID);
#if 0
	GsnOsal_SemRelease(&s2wappMainTaskCtxt->gslinkSync);
#endif

}
PUBLIC VOID AppS2w_HttpdSemDelete(UINT8 cid)
{
	GsnOsal_SemDelete(&s2wCidList[cid].httpdCtx.s2wGsLinkemID);
}


#endif
PUBLIC UINT8 AppS2w_ConnStateGet(UINT8 cid)
{
    return tlsv1_client_established(s2wCidList[cid].ssl.sslConn->tlsv1Conn);
}
PUBLIC UINT8 AppS2w_ConnHttpStateGet(UINT8 cid)
{
    return (s2wCidList[cid].httpflag);
}
#ifdef S2W_HTTPC_SUPPORT

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Http client send function.
 * @param cid                - IN the cid needs to be closed
 * @retval S2W_SUCCESS     - operation successfull.
 * @retval S2W_EBADCID     - cid is not valid.
 * @retval S2W_FAILURE     - operation failed.
 ******************************************************************/
PUBLIC GSN_STATUS 
S2wHttp_Send(UINT8 cid)
{
    UINT8 *httpRxDataBuf = NULL;
    UINT32 httpRxDataLen = 0;
    UINT32 ret = S2W_SUCCESS;//et1= S2W_SUCCESS, bytesLeft = 0;
    S2W_HTTP_DATA_T *pHttpData;
    INT8 startMark[10];
    //UINT8 *rcvBuf = NULL;
    //UINT32 rcvLen;
#ifdef S2W_HTTPS_SUPPORT
    //ttHttpcConEntryPtr      conEntryPtr;
#endif
    //S2W_MSG_T recvMsg;

    pHttpData = (S2W_HTTP_DATA_T *)AppS2wHal_HttpHandleGet(cid);

    if(pHttpData == NULL)
    {
         return S2W_FAILURE;
    }

    if(0 == httpConfInfo.moredata)
    {/* prepare to receive response */
        httpRxDataLen = 2048 ;
        httpRxDataBuf = gsn_malloc(2048);
        if(NULL == httpRxDataBuf)
        {
            ret = S2W_FAILURE;
        }
        httpConfInfo.rxBufferMgmtCb = AppS2w_HttpRxBufferMgmtCb;
		httpConfInfo.rxBufferMgmtCbCtx = NULL;
#ifdef S2W_HTTP_CUSTOM_SUPPORT
        httpConfInfo.rxHdrsCb = AppS2w_HttpRxHdrsCb;
		httpConfInfo.hconHttpcHdrSent = 0;
#endif
    }
	/*Make all the custom headers types as 255 - This is done to coply withi the ROM code which is
	compiled with header type array being defined as array of UINT8 */
	{
		UINT8 i;
		for( i = 0; i < S2W_HTTPC_MAX_HDR_SUPPORTED; i++)
        {
        	if(headerTypes[i] >= (GSN_HTTP_USER_HEADER_TYPE_T)TM_HTTP_HEADER_CUSTOM)
			{
				headerTypesModified[i] = (GSN_HTTP_USER_HEADER_TYPE_T)TM_HTTP_HEADER_CUSTOM;
			}
			else
			{
        		headerTypesModified[i] = headerTypes[i];
			}
        }
	}
    ret = GsnHttp_Send(pHttpData->pHttpHandle, (INT8 *)httpRxDataBuf,
                       &httpRxDataLen, httpConfInfo.httpTimeOut, &httpConfInfo);

    if(GSN_SUCCESS == ret)
    {
        if(0 == httpConfInfo.moredata)
        {
#ifdef S2W_THROUGHPUT_TEST                       
        	if( s2wCidList[cid].tpTestInProgress == 1)
			{
				s2wCidList[cid].stats.bytesReceived += httpRxDataLen;
        	}
			else
#endif				
			{
                if(GSN_HTTP_METHOD_HEAD != httpConfInfo.reqMethod)
                {
                    sprintf(startMark,"%c%c%x%04d", S2W_ESC, 'H', cid,httpRxDataLen);
#ifndef S2W_DUAL_INTERFACE_SUPPORT
                    AppS2wHal_CharNPut(startMark, strlen(startMark));
                    AppS2wHal_CharNPut(httpRxDataBuf, httpRxDataLen);
#else
                    AppS2wHal_CharNPut1(startMark, strlen(startMark));
                    AppS2wHal_CharNPut1(httpRxDataBuf, httpRxDataLen);
#endif
                }
			}
        }
        ret = S2W_SUCCESS;
    }
    else /* ERROR or TimeOut */
    {
        ret = S2W_FAILURE;
    }

    if(NULL != httpRxDataBuf)
    {
        gsn_free(httpRxDataBuf);
        httpRxDataBuf = NULL;
    }
    if(NULL != httpConfInfo.reqPathPtr 
#ifdef S2W_THROUGHPUT_TEST
		&& ( s2wCidList[cid].tpTestInProgress == 0)
#endif		
	   )
    {
        gsn_free(httpConfInfo.reqPathPtr);
        httpConfInfo.reqPathPtr = NULL;
    }
#if 0//def GSN_HTTPS_SUPPORT
    conEntryPtr = (ttHttpcConEntryPtr)s2wCidList[cid].pHttpData->pHttpHandle;
    if(0 == httpConfInfo.moredata)
    {
        /* check whether some data still remaining in nw buffer or not */
        bytesLeft = tfGetWaitingBytes(s2wCidList[cid].sd);
    }
    if((bytesLeft > 0) && (conEntryPtr->hconHttpType == GSN_HTTPS))
    {
        /* Still data remaining in NW buffer. Decode that data */
        ret1 = GsnSsl_DataReceive(conEntryPtr->hConSsl, s2wCidList[cid].sd, &rcvBuf, &rcvLen, 5);
        if(rcvBuf != NULL)
        {
            GsnSsl_Free(rcvBuf);
        }
        if(ret1 == GSN_SSL_CLOSE_ALERT)
        {
            /* Data is a Close alert from server. Post message to rcv task */
            recvMsg.msgType = S2W_RECV_TYPE_HTTPS_CLOSE;
            recvMsg.rData.dataSock = s2wCidList[cid].sd;
            recvMsg.msgLen = 0;
            AppS2wHal_NetRxMsgPost(&recvMsg);
        }

    }
#endif
#ifndef S2W_DUAL_INTERFACE_SUPPORT
    if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush();
    }
#else
    if(s2wappMainTaskCtxt->serialDeviceId1 == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush1();
    }
#endif
    return ret;

}
#endif

PUBLIC VOID
AppS2wHal_HttpdClose(UINT8 parentTask)
{
    UINT32 message;
#if defined(S2W_WEB_SERVER) || defined(S2W_WEB_PROV)
    if(!parentTask)
    {
        if( TRUE == GsnHttpd_IsRunning())
        {
            message = APP_NOTIFICATION_SRVR_STOP;
            (s2wappMainTaskNotifier)(message, s2wappMainTaskCtxt);
            GsnOsal_SemAcquire(&s2wappMainTaskCtxt->webServerSync,GSN_OSAL_WAIT_FOREVER);
        }
    }
    else
    {
        if( TRUE == GsnHttpd_IsRunning() )
        {
#ifdef S2W_WEB_PROV
            if((TRUE == GsnHttpd_IsRunning() )&& s2wappMainTaskCtxt->webProvStatus== RUNNING)
                s2wappMainTaskCtxt->webProvStatus=STOP;
#endif
#ifdef S2W_WEB_SERVER
            if((TRUE == GsnHttpd_IsRunning() )&& s2wappMainTaskCtxt->webServerStatus == RUNNING)
                s2wappMainTaskCtxt->webServerStatus=STOP;
#endif
            AppS2wHttpd_Stop();
        }
    }
#endif
}


#ifdef S2W_MDNS_ENABLE
PUBLIC VOID
AppS2wHal_MdnsRegCb(void *pCtx, UINT8 *rrName, UINT32 status)
{
	UINT8 syncId,asyncId;
    if(GSN_MDNS_REG_CONFLICT == status)
    {
	    syncId =  S2W_MDNS_REG_FAILED_ID;
		asyncId = S2W_ASYNC_MDNS_REG_FAILED_ID;
    }
    else
    {
	    syncId =  S2W_MDNS_REG_SUCESS_ID;
		asyncId = S2W_ASYNC_MDNS_REG_SUCESS_ID;
    }
	if(s2wCurrent.asyncMsgFormat == 1)
	{
		AppS2wProcess_AsyncStatusNotify(asyncId,(UINT32)rrName);
	}
	else
	{
		AppS2wProcess_StatusNotify(syncId,(UINT32)rrName);
	}
}

//GSN_MDNS_T mdns;
S2W_MDNS_HN_PARAM_T mdnsHnParam;

//#define APP_MDNS_STACK_SIZE     4*1024
//#define APP_MDNS_MSG_Q_BUFF_SIZE        256


//UINT8  mdnsMsgBuff[APP_MDNS_MSG_Q_BUFF_SIZE];

VOID s2w_mdnsCb(VOID *cbCtx, VOID *pMdns)
{
  AppMainCtx_TaskNotify(APP_EVENT_MDNS_EXECUTE);
  
}

#if 0

PRIVATE VOID   
App_MdnsThreadEntry(UINT32 ctx)
{

    /*UINT status;*/
    //UINT32 msg = 0;

   /* Start debug UART before starting the idle handler because the 
       debug UART flushing is done in idle handler context */

    /**< Initialize debug module */
   APP_MAIN_CTX_T *pAppCtx;
   pAppCtx = (APP_MAIN_CTX_T *)ctx;
   
   
    GsnMdns_Execute(&pAppCtx->mdns);/* This will not exit*/
}
#endif


UINT8 mdnsFlag=0;
__no_init UINT8 mdnsMsgQueueBuf[512];

VOID
AppS2wHal_MdnsInit(UINT8 *ptr)
{
    GSN_MDNS_INIT_PARAM_T initParam;
    UINT32 param;
    UINT8 *p;
    if(mdnsFlag)
    return ;
    memset((INT8*)&initParam, 0, sizeof(initParam));

    if((p=(UINT8*)AppS2wParse_NextParamGet(&ptr)) != NULL)
    {    
    AppS2wParse_Int(p, &param);
    if(param == 6)
    memcpy(initParam.ipV6Addr,appCtx.if0.nwifCtx.ipConfig.ipv6.globalAddr,16);
    }
    else
    initParam.ipV4Addr = appCtx.if0.nwifCtx.ipConfig.ipv4.ipAddr;
    
    initParam.pNwif = &appCtx.if0.nwifCtx;

              
    initParam.msgQueueBuff = mdnsMsgQueueBuf;                           /**< pointer to message queue buffer*/
    initParam.msgQueueBuffSize = 512;       /**< messsage queue buffer size*/                                      
    initParam.noSeparatetsk = 0;
    initParam.blockingOn = 0;
    //initParam.msgPostCb = NULL;
    initParam.msgPostCb = s2w_mdnsCb;
    initParam.msgPostCbCtx = NULL;

    GsnMdns_Init(&appCtx.mdns, &initParam);
    mdnsFlag=1;
    /* create a mdns task*/
   //GsnOsal_ThreadCreate(App_MdnsThreadEntry, &appCtx, &appMdnsThread,
   //     "App Mdns Ctx", APP_MDNS_THREAD_PRI, (UINT8 *)appMdnsThreadStack,
   //     sizeof(appMdnsThreadStack), GSN_OSAL_THREAD_INITIAL_READY);
}

VOID
AppS2wHal_MdnsDeInit()
{
        
	GsnMdns_DeInit(&appCtx.mdns);
        mdnsFlag=0;
}



PUBLIC UINT8
AppS2wHal_MdnsHostNameReg(S2W_MDNS_HN_PARAM_T *pHNparam)
{
    GSN_STATUS retVal;
    GSN_MDNS_HNREG_PARAM_T pParam;
    //UINT32 arr[4];
    //UINT8 i;
    
    pParam.hostname = pHNparam ->hostname;
    pParam.domain   = pHNparam -> domain;
    pParam.ttl   = pHNparam ->ttl;
    pParam.scope = pHNparam->scope;
     
    pParam.autoCorrect  = pHNparam ->autoCorrect;
    pParam.conflctDetect = pHNparam ->conflctDetect;

    if(pHNparam->IpVersion & ADDR_TYPE_IPv6)
    {
        memcpy(pParam.ipAddr.addr.v6,appCtx.if0.nwifCtx.ipConfig.ipv6.globalAddr,16);
        pParam.ipAddr.ipVer = GSN_NWIF_IP_VERSION_V6;
    }
    else
        pParam.ipAddr.addr.v4 = appCtx.if0.nwifCtx.ipConfig.ipv4.ipAddr;

    pParam.cb           = AppS2wHal_MdnsRegCb;
    pParam.cbCtx        = NULL;
    
    retVal = GsnMdns_HostnameRegister(&appCtx.mdns, &pParam);

    if(GSN_SUCCESS != retVal)
        return S2W_FAILURE;
    return S2W_SUCCESS;
}


PUBLIC UINT8
AppS2wHal_MdnsServiceReg(S2W_MDNS_SRV_PARAM_T *pSrvParam)
{
    GSN_STATUS retVal;
    GSN_MDNS_SRVCREG_PARAM_T pParam;
    
    pParam.srvceName     = pSrvParam ->srvcInstance;
    pParam.srvceSubType  = pSrvParam ->subType;
    pParam.srvceType     = pSrvParam ->srvcType;
    pParam.srvceProto    = pSrvParam ->proto;
    pParam.domain        = pSrvParam ->domain;
    pParam.port          = pSrvParam ->port;
    pParam.ttl           = pSrvParam ->ttl;
    pParam.keyVal        = pSrvParam ->keyVal;
    pParam.autoCorrect   = pSrvParam ->autoCorrect;
    pParam.scope         = pSrvParam ->scope;
    pParam.conflctDetect = pSrvParam ->conflctDetect;
      
    pParam.cb           =   AppS2wHal_MdnsRegCb;
    pParam.cbCtx        =   NULL;
    
     retVal = GsnMdns_ServiceRegister(&appCtx.mdns,&pParam);


      if(GSN_SUCCESS != retVal)
        return S2W_FAILURE;
    return S2W_SUCCESS;
}


PUBLIC UINT8
AppS2wHal_MdnsHostNameDereg(S2W_MDNS_HN_PARAM_T *pHNparam)
{
    GSN_MDNS_HNDEREG_PAARAM_T pParam;
    
    pParam.hostname = pHNparam->hostname;
    pParam.domain   = pHNparam -> domain;

   GsnMdns_HostnameDeregister(&appCtx.mdns, &pParam);

    return S2W_SUCCESS;
}

PUBLIC UINT8
AppS2wHal_MdnsServiceDereg(S2W_MDNS_SRV_PARAM_T *pSrvParam)
{
     GSN_MDNS_SRVCDEREG_PARAM_T pParam;
     
     pParam.srvceName = pSrvParam->srvcInstance;
     pParam.srvceSubType = pSrvParam->subType;
     pParam.srvceType = pSrvParam -> srvcType;
     pParam.srvceProto = pSrvParam -> proto;
     pParam.domain = pSrvParam -> domain;
       
    GsnMdns_ServiceDeRegister(&appCtx.mdns, &pParam);
    return S2W_SUCCESS;
}

PUBLIC VOID
AppS2wHal_MdnsSdCb(void *pCtx, const GSN_MDNS_SRVC_INFO_T *srvinfo, UINT32 status)
{
    UINT8 *addr = (UINT8 *)&srvinfo->ipAddr;
	GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
    if(GSN_MDNS_SD_NO_SRVC_INFO == status)
    {
        S2w_Printf("Service Discovery Failed\r\n");
    }
    else
    {
        S2w_Printf("\nA Service Discovered: %d\r\n", status);
        S2w_Printf("\r\n");
        S2w_Printf("Service Instance name     = %s\r\n", srvinfo->instance);
        S2w_Printf("Service Sub type          = %s\r\r", srvinfo->subType);
        S2w_Printf("Service app protocol      = %s\r\n", srvinfo->srvcType);
        S2w_Printf("Service protocol          = %s\r\n", srvinfo->protocol);
        S2w_Printf("Service domain            = %s\r\n", srvinfo->domain);         
        
        S2w_Printf("Service IP address        = %d.%d.%d.%d  Port = %d\r\n",
            addr[0], addr[1], addr[2], addr[3], srvinfo->port);
        if(NULL != srvinfo->txtInfo)
        {
            UINT8 txtStrLen = *(srvinfo->txtInfo);
            UINT8 txtNxtStrLen ;
            UINT8 *txtInfo = srvinfo->txtInfo ;

			txtInfo ++;
            while(txtStrLen)
            {
                txtNxtStrLen = *(txtInfo + txtStrLen);
				*(txtInfo + txtStrLen)  = 0;

				S2w_Printf("\nService Text Info          = %s\r\n", txtInfo);
                txtInfo += (txtStrLen + 1);
                txtStrLen = txtNxtStrLen;
            }
        }
    }
    if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush();
    }
	GsnOsal_SemRelease(&s2wSyncSemID);
}
PUBLIC UINT8
AppS2wHal_MdnsSrvcDiscover(S2W_MDNS_SRVCDISCVR_PARAM_T *mdnsSrvDscr)
{
    GSN_STATUS retVal;
    GSN_MDNS_SRVCDISCVR_PARAM_T pParam;
    
    
    pParam.srvcSubType = mdnsSrvDscr ->srvcSubType;
    pParam.srvcType    = mdnsSrvDscr ->srvcType;
    pParam.srvcProto   = mdnsSrvDscr ->srvcProto;
    pParam.domain      = mdnsSrvDscr ->domain;
   
    pParam.scope       = mdnsSrvDscr ->scope;
    pParam.cb          =  AppS2wHal_MdnsSdCb;
    pParam.cbCtx       =  NULL;
    

    retVal = GsnMdns_ServiceDiscover(&appCtx.mdns, &pParam);
     if(GSN_SUCCESS != retVal)
        return S2W_FAILURE;
    return S2W_SUCCESS;
}

PUBLIC UINT8
AppS2wHal_MdnsAnnounce(S2W_MDNS_ANNOUNCE_PARAM_T *mdnsAnnceParam)
{
    GSN_MDNS_ANNOUNCE_PARAM_T pParam;
    
    pParam.srvceName = mdnsAnnceParam->srvceName;
    pParam.domain = mdnsAnnceParam->domain;
    
    if(mdnsAnnceParam->type == 2)
    {
        pParam.srvceSubType = mdnsAnnceParam ->srvceSubType;
        pParam.srvceType = mdnsAnnceParam->srvceType;
        pParam.srvceProto = mdnsAnnceParam ->srvceProto;
    } 
    else
    {
         pParam.srvceSubType = NULL;
         pParam.srvceType = NULL;
         pParam.srvceProto = NULL;
    }
    GsnMdns_Announce(&appCtx.mdns, &pParam);

    return S2W_SUCCESS;
}

#endif
#define S2W_GS2000_TIMER_TICK_IN_MILLI_SECOND   0.030517578125
#ifdef S2W_PING_TRACE
S2W_PING_STATS_T s2wPingStats;

VOID s2wPingStart()
{
    NX_PACKET *response_ptr;
    ULONG rtt0,rtt1,ttl=64;
    UINT32 interval;
    UINT8 *pingBuf;
  	INT32 icmpRetVal;
	UINT32 milliSecPerTick = (1000/NX_CPU_TICKS_PER_SECOND); 
    interval = (s2wappMainTaskCtxt->pingParams.interval != 0) ? (s2wappMainTaskCtxt->pingParams.interval) : 3000;
	/* Convert from milli sec to ticks*/
	interval  = (interval / milliSecPerTick);
#ifdef S2W_IPv6_SUPPORT
    INT8 ipv6str[INET6_ADDRSTRLEN];
    S2w_ntop(s2wappMainTaskCtxt->pingParams.ip_address.nxd_ip_address.v6,ipv6str);
#endif
 
    if(s2wPingStarted == TRUE)
    {
        if(s2wappMainTaskCtxt->pingParams.payload[0])
        {
            pingBuf = (UINT8 *)MALLOC(strlen(s2wappMainTaskCtxt->pingParams.payload) + 1);
            if(NULL == pingBuf)
            {
                return;
            }
            memcpy(pingBuf,s2wappMainTaskCtxt->pingParams.payload,strlen(s2wappMainTaskCtxt->pingParams.payload));
            pingBuf[strlen(s2wappMainTaskCtxt->pingParams.payload)] = '\0';
        }
        else if(s2wappMainTaskCtxt->pingParams.dataLen)
        {
            if(s2wappMainTaskCtxt->pingParams.dataLen >= 1024)
            {
                return;
            }
            pingBuf = (UINT8 *)MALLOC(s2wappMainTaskCtxt->pingParams.dataLen + 1);
            if(NULL == pingBuf)
            {
                return;
            }
            memset(pingBuf,'G',s2wappMainTaskCtxt->pingParams.dataLen);
            pingBuf[s2wappMainTaskCtxt->pingParams.dataLen]='\0';
        }
        else
        {
            pingBuf = (UINT8 *)MALLOC(56 + 1);
            if(NULL == pingBuf)
            {
                return;
            }
            memset(pingBuf,'G',56);
            pingBuf[56]='\0';
        }

#ifdef S2W_IPv6_SUPPORT
        if(s2wappMainTaskCtxt->pingParams.IpVersion & ADDR_TYPE_IPv6)
        {
            rtt0 = GsnTod_Get();
     icmpRetVal =  _nxd_icmp_ping(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl,&s2wappMainTaskCtxt->pingParams.ip_address, (INT8*)pingBuf,strlen((const char*)pingBuf),&response_ptr, interval);
        }
        else
#endif   
        {
            rtt0 = GsnTod_Get();
      icmpRetVal = nx_icmp_ping(&s2wappMainTaskCtxt->if0.nwifCtx.ipHndl,(s2wappMainTaskCtxt->pingParams.Ipv4Addr),(INT8*)pingBuf,strlen((const char*)pingBuf)/*strlen((const char*)s2wappMainTaskCtxt->pingParams.payload)*/,&response_ptr,interval);
        }
        s2wPingStats.pingSentCnt++;
        GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);
        FREE(pingBuf);
      if(icmpRetVal == S2W_SUCCESS && response_ptr != NULL )
        {
            rtt1 = GsnTod_Get();
#ifdef S2W_IPv6_SUPPORT    
            if(s2wappMainTaskCtxt->pingParams.IpVersion & ADDR_TYPE_IPv6)
            {
                S2w_Printf("\r\nReply from %s bytes=%d time=%d ms TTL %d",ipv6str,response_ptr->nx_packet_length,(ULONG)((rtt1-rtt0)*S2W_GS2000_TIMER_TICK_IN_MILLI_SECOND),ttl );
            }
            else
#endif     
            {
                S2w_Printf("\r\nReply from %d.%d.%d.%d: bytes=%d time=%d ms TTL %d",(s2wappMainTaskCtxt->pingParams.Ipv4Addr& 0xff000000)>>24,(s2wappMainTaskCtxt->pingParams.Ipv4Addr& 0x00ff0000)>>16,(s2wappMainTaskCtxt->pingParams.Ipv4Addr& 0x0000ff00)>>8,(s2wappMainTaskCtxt->pingParams.Ipv4Addr & 0x000000ff),response_ptr->nx_packet_length,(ULONG)((rtt1-rtt0)*S2W_GS2000_TIMER_TICK_IN_MILLI_SECOND),ttl );
            }
            s2wPingStats.pingRecvCnt++;
            if(((rtt1-rtt0)*S2W_GS2000_TIMER_TICK_IN_MILLI_SECOND)>s2wPingStats.rttMax)
            {
                s2wPingStats.rttMax=(ULONG)((rtt1-rtt0)*S2W_GS2000_TIMER_TICK_IN_MILLI_SECOND);
            }
            if(!s2wPingStats.rttMin)
            {
                s2wPingStats.rttMin=s2wPingStats.rttMax;
            }
            if(((rtt1-rtt0)*S2W_GS2000_TIMER_TICK_IN_MILLI_SECOND) < s2wPingStats.rttMin)
            {
                s2wPingStats.rttMin=(ULONG)((rtt1-rtt0)*S2W_GS2000_TIMER_TICK_IN_MILLI_SECOND);
            }
            s2wPingStats.rttAvg +=((rtt1-rtt0)*S2W_GS2000_TIMER_TICK_IN_MILLI_SECOND);
			nx_packet_release(response_ptr);
            GsnTaskSleep(100);
        }
        else
        {
           S2w_Printf("\r\nRequest timed out" );
        }     

        if(s2wappMainTaskCtxt->pingParams.trails)
        {
            s2wappMainTaskCtxt->pingParams.trails--;
            if(!s2wappMainTaskCtxt->pingParams.trails)
            {
                 s2wPingStarted = FALSE;
				AppS2w_PingTaskNotify(APP_EVENT_PING_STOP);
            }
        }
          
		  AppS2w_PingTaskNotify(APP_EVENT_PING_REQUEST);
		  if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
		  {
		      s2wSpiFs_Flush();
          }
          GsnOsal_SemRelease(&s2wSyncSemID);
    }

}
                        
VOID s2wPingStop()
{
  if( s2wPingStarted == FALSE)
  {
      GsnOsal_SemAcquire(&s2wSyncSemID, GSN_OSAL_WAIT_FOREVER);

#ifdef S2W_IPv6_SUPPORT    
         if(s2wappMainTaskCtxt->pingParams.IpVersion & ADDR_TYPE_IPv6)
         {
           INT8 ipv6str[INET6_ADDRSTRLEN];
           S2w_ntop(s2wappMainTaskCtxt->pingParams.ip_address.nxd_ip_address.v6,ipv6str);
           S2w_Printf("\r\nPing Statistics for %s \r\n",ipv6str);
         }
         else
#endif     
        S2w_Printf("\r\nPing Statistics for %d.%d.%d.%d:\r\n",(s2wappMainTaskCtxt->pingParams.Ipv4Addr& 0xff000000)>>24,(s2wappMainTaskCtxt->pingParams.Ipv4Addr& 0x00ff0000)>>16,(s2wappMainTaskCtxt->pingParams.Ipv4Addr& 0x0000ff00)>>8,(s2wappMainTaskCtxt->pingParams.Ipv4Addr & 0x000000ff));
        S2w_Printf("\r\tPackets: Sent = %d, Received = %d, Lost = %d percent\r\n",s2wPingStats.pingSentCnt,s2wPingStats.pingRecvCnt,((s2wPingStats.pingSentCnt-s2wPingStats.pingRecvCnt)*100)/s2wPingStats.pingSentCnt);
        S2w_Printf("\rApproximate round trip times in milliseconds\r\n");
        S2w_Printf("\r\tMinimum = %dms, Maximum = %dms, Average = %dms\r\n",s2wPingStats.rttMin,s2wPingStats.rttMax,s2wPingStats.rttAvg/s2wPingStats.pingRecvCnt);
        GsnOsal_SemRelease(&s2wSyncSemID);
        memset(&s2wPingStats,0,sizeof(S2W_PING_STATS_T));
  }

}
VOID AppS2wHal_PingClose()
{
      s2wPingStarted = FALSE;
	  AppS2w_PingTaskNotify(APP_EVENT_PING_STOP);
}

#endif

BOOL 
App_IsArpReqstPkt(GSN_NWIF_CTX_T *pNwIf, GSN_ETHERNET_FRAME_T *pEthFrame, 
								UINT32 protocol)
{
	UINT32 ipAddr;
	ipAddr = htonl(GsnNwIf_IpV4AddrGet(pNwIf));
	/* An ARP Request Pkt with  Destination address being  the node address */
	return ((GSN_ETH_PROTO_TYPE_ARP == protocol) &&
		  	(GSN_NW_ARP_REQUEST ==
					  htons((GsnNwIf_U16FieldGet)(pEthFrame->Data + GSN_NW_ARP_OP_OFFSET))) &&
			(0 == memcmp(&ipAddr, (pEthFrame->Data + GSN_NW_ARP_TAGET_IP_OFFSET), 4)));
}

BOOL 
App_IsArpReplyPkt(GSN_NWIF_CTX_T *pNwIf, GSN_ETHERNET_FRAME_T *pEthFrame, 
								UINT32 protocol)
{
	//UINT32 ipAddr;
	//ipAddr = htonl(GsnNwIf_IpV4AddrGet(pNwIf));
	/* An ARP Request Pkt with  Destination address being  the node address */
	return ((GSN_ETH_PROTO_TYPE_ARP == protocol) &&
		  	(GSN_NW_ARP_RESPONSE ==
					  htons((GsnNwIf_U16FieldGet)(pEthFrame->Data + GSN_NW_ARP_OP_OFFSET))));
}

PRIVATE INLINE UINT16
AppS2w_NwIfU16FieldGet(UINT8 *pPkt)
{
    UINT16 val = 0;
    memcpy(&val, pPkt, sizeof(UINT16));
    return val;
}
UINT32 AppS2w_isForValidCid(UINT16 dst_port , UINT16 src_port)
{
    BOOL filterPass = FALSE;
    UINT32 i;
    for (i = 0; i < MAX_CID_RANGE; i++)
    {
        if (((s2wCidList[i].sd != CID_NOTINUSE) &&((dst_port == s2wCidList[i].localPort ) ||
            (s2wCidList[i].conMode == S2W_NETDATA_MODE_CLIENT_TRANSIENT)))||
            ((s2wCidList[i].conMode == S2W_NETDATA_MODE_CLIENT_TRANSIENT) && 
            (s2wCidList[i].httpflag == 1) &&  ((src_port == S2W_HTTPS_PORT ) || (src_port == S2W_HTTP_PORT ))))
           {
               filterPass = TRUE;
               break;
           }
    }
#ifdef S2W_COAP_SUPPORT
    for (i = 0; i < MAX_CID_RANGE; i++)
    {
        if ((s2wCidList[i].sd != CID_NOTINUSE) &&
            (s2wCidList[i].conType == UDP) &&
            (src_port == S2W_COAP_PORT ) && (s2wCidList[i].coapContext != NULL))
           {
               filterPass = TRUE;
               break;
           }
    }
#endif
    return filterPass;
}
BOOL
AppS2wRecv_Filter(GSN_NWIF_CTX_T *pNwIf, UINT32 pktLen,
                    GSN_ETHERNET_FRAME_T *pEthFrame
                    )
{
	BOOL filterPass = TRUE;
	UINT16 protocol;
	UINT8 getOutOfDpSleep = 0;
	
	UINT16 dst_port= htons(AppS2w_NwIfU16FieldGet(pEthFrame->Data
				                                                    + GSN_NW_IP_HEADER_LEN
                                                    + GSN_NW_UDP_DST_PORT_OFFSET));
	UINT16 src_port =htons(AppS2w_NwIfU16FieldGet(pEthFrame->Data+ GSN_NW_IP_HEADER_LEN
																	+ GSN_NW_UDP_SRC_PORT_OFFSET));	 
																	
	protocol = swap_16(pEthFrame->UpperProtocolType);
    if(GSN_ETH_PROTO_TYPE_ARP == protocol)
    {
		filterPass = FALSE;
		if(TRUE == App_IsArpReqstPkt(pNwIf, pEthFrame, protocol) || 
			TRUE == App_IsArpReplyPkt(pNwIf, pEthFrame, protocol))
		{
			filterPass = TRUE;
		}
	}

    /* Get protocol type if the l2 is configured to disable any protocol*/
    if(s2wappMainTaskCtxt->l2ConfigBitField)
    {
	    if (GSN_ETH_PROTO_TYPE_IP == protocol)
	    {
			/* If it is an ICMP and disable flag enabled by the at command, then return false */
		    if((GSN_NW_ICMP_PROTO == *(pEthFrame->Data + GSN_NW_IP_PROTO_OFFSET)) &&
		       (s2wappMainTaskCtxt->l2ConfigBitField & S2W_ICMP_MASK))
		    {
				filterPass = FALSE;
			}

		    /* If it is an UDP/TCP and disable flag enabled by the at command, then return false */
		    else if(((GSN_NW_UDP_PROTO == *(pEthFrame->Data + GSN_NW_IP_PROTO_OFFSET)) ||
		    (GSN_NW_TCP_PROTO == *(pEthFrame->Data + GSN_NW_IP_PROTO_OFFSET)))&&
			    (s2wappMainTaskCtxt->l2ConfigBitField & S2W_UDP_TCP_MASK))
		    {
				filterPass = FALSE;
                /* It has to be packet for an existing socket */
				if((GSN_NW_UDP_PROTO == *(pEthFrame->Data + GSN_NW_IP_PROTO_OFFSET)))
				{
					if((S2W_DNS_PORT == src_port)|| (S2W_SNTP_PORT == src_port))
					{
						filterPass = TRUE;
                    	goto AppS2wRecv_Filter_1;
					}
				}	
                // check first the pkt is dhcp/dns/mdns/http
                if( (S2W_MDNS_PORT == dst_port) || (GSN_NW_BOOTPS_PORT == dst_port)
                    ||  (GSN_NW_BOOTP_PORT == dst_port)|| (S2W_DNS_PORT == dst_port)                   
#ifdef S2W_WEB_SERVER                   
                     ||  (((S2W_HTTPS_PORT == dst_port) || (S2W_HTTP_PORT == dst_port)) && (GsnHttpd_IsRunning()))
#endif                    
                    )
                {
                    filterPass = TRUE;
                    goto AppS2wRecv_Filter_1;
				}
                // check the port exists in the cid list, if not drop the pkt
                if(AppS2w_isForValidCid(dst_port, src_port) == TRUE)
                {
                    filterPass = TRUE;
                    getOutOfDpSleep = 1;
                }
                
  		    }
	    }
	}
	else if((GSN_NW_UDP_PROTO == *(pEthFrame->Data + GSN_NW_IP_PROTO_OFFSET)) ||
	    			(GSN_NW_TCP_PROTO == *(pEthFrame->Data + GSN_NW_IP_PROTO_OFFSET)))
    {
        if(AppS2w_isForValidCid(dst_port, src_port) == TRUE)
        {
            filterPass = TRUE;
            getOutOfDpSleep = 1;
        }
    }
	

AppS2wRecv_Filter_1:

	if(s2wappMainTaskCtxt->dpSleep)
	{
	    /* If it is an UDP/TCP and disable flag enabled by the at command, then return false */
	    if((GSN_NW_UDP_PROTO == *(pEthFrame->Data + GSN_NW_IP_PROTO_OFFSET)) ||
	    			(GSN_NW_TCP_PROTO == *(pEthFrame->Data + GSN_NW_IP_PROTO_OFFSET)))
	    {
			//filterPass = FALSE;
	        /* It has to be packet for an existing socket */
	        UINT16 dst_port= htons(AppS2w_NwIfU16FieldGet(pEthFrame->Data
			                                                    + GSN_NW_IP_HEADER_LEN
	                                            + GSN_NW_UDP_DST_PORT_OFFSET));
			UINT16 src_port =htons(AppS2w_NwIfU16FieldGet(pEthFrame->Data+ GSN_NW_IP_HEADER_LEN
																+ GSN_NW_UDP_SRC_PORT_OFFSET));				
#ifdef S2W_WEB_SERVER
	        if(((S2W_HTTPS_PORT == dst_port) || (S2W_HTTP_PORT == dst_port)) && (GsnHttpd_IsRunning()))
	        {
	            getOutOfDpSleep = 1;
			}
#endif          			
	        
		}
		if(s2wappMainTaskCtxt->dpSleep && (1 == getOutOfDpSleep))
		{
			AppS2w_ExitDpSleep();
		}
	}
    return filterPass;

}

#if defined(S2W_DTLS_CLIENT_SUPPORT)
extern const unsigned char dtlsClientCA[895];
extern const unsigned char dtlsClientClient[641];
extern const unsigned char dtlsClentKey[608];

VOID  AppS2w_DtslClientCb( VOID * pCtx, UINT8 event )
{
	int i;
	for(i = 0; i< MAX_CID_RANGE; i++)
	{
		if(pCtx == (void*)s2wCidList[i].ssl.sslConn)
		{
			break;
		}
	}
	if((i < MAX_CID_RANGE) && (GSN_DTLS_HANDSHAKE_DONE == event))
	{
		GsnOsal_SemRelease(&s2wCidList[i].s2wUserOpenInProgress);
	}
}

UINT8 AppS2w_DtslClientOpen(UINT8 cliCid, char* caCertName,
                           UINT8 *clientCertName, UINT8 *clientKeyName)
{
    //INT32 u32NoOfBytesSent;
    UINT32 status;
    UINT8 *certBuf = NULL;
    UINT16 caCertsize = 0;
    INT32  index=0;
    //void *pSslConn;
    GSN_SSL_CONN_PARAMS_T sslConnParams;
	UINT32 cid = cliCid;
#if 1
#ifdef S2W_APP_SSL_PROVISION
    initStartTime = GsnSoftTmr_CurrentSystemTime();
#endif

    /* Avoid warning*/
    (void)certBuf ;
    (void)caCertsize ;
    memset((INT8 *)&sslConnParams, 0, sizeof(sslConnParams));
    if (s2wCidList[cid].sslflag == TRUE)
    {
        S2w_Printf("\r\nSocket is already SSL Enabled");
        return S2W_FAILURE;
    }

    if(caCertName != NULL)
    {
        index = S2wCert_SearchRamTable(caCertName);
        if(index == -1)
        {
        	index = S2wCert_FlashFileLoad(caCertName);
        }
        if(index == -1)
        {
            S2w_Printf("\n\rca Certificate %s Not Found", caCertName);
            return S2W_FAILURE;
        }

        // currently use the hardcoded certificate
        sslConnParams.caCertLen = *(UINT16 *)s2w_ssl_cert_table[index].certAddress;
        sslConnParams.caCert = s2w_ssl_cert_table[index].certAddress + 2;
        sslConnParams.caCertName = (char const*)caCertName;
    }


    if(clientCertName != NULL)
    {
        index = S2wCert_SearchRamTable((char*)clientCertName);
        if(index == -1)
        {
        	index = S2wCert_FlashFileLoad((char*)clientCertName);
        }
        if(index == -1)
        {
            S2w_Printf("\n\rclient Certificate %s Not Found", clientCertName);
            return S2W_FAILURE;
        }
        sslConnParams.clientCertLen = *(UINT16 *)s2w_ssl_cert_table[index].certAddress;
        sslConnParams.clientCert =  s2w_ssl_cert_table[index].certAddress + 2;
        sslConnParams.clientCertName = (char const*)clientCertName;

    }


    if(clientKeyName != NULL)
    {
        index = S2wCert_SearchRamTable((char*)clientKeyName);
        if(index == -1)
        {
        	index = S2wCert_FlashFileLoad((char*)clientKeyName);
        }
        if(index == -1)
        {
            S2w_Printf("\n\rclient key Certificate %s Not Found", clientKeyName);
            return S2W_FAILURE;
        }
        sslConnParams.clientKeyLen = *(UINT16 *)s2w_ssl_cert_table[index].certAddress;
        sslConnParams.clientKey =  s2w_ssl_cert_table[index].certAddress + 2;
        sslConnParams.clientKeyName = (char const*)clientKeyName;

    }

#if 0
    //if(caCertName != NULL)
    {

        sslConnParams.caCertLen = sizeof(dtlsClientCA);//*(UINT16 *)s2w_ssl_cert_table[index].certAddress;
        sslConnParams.caCert =  (UINT8*)dtlsClientCA;//s2w_ssl_cert_table[index].certAddress + 2;
        sslConnParams.caCertName = NULL;
    }


    //if(clientCertName != NULL)
    {
        sslConnParams.clientCertLen = sizeof(dtlsClientClient);//*(UINT16 *)s2w_ssl_cert_table[index].certAddress;
        sslConnParams.clientCert =  (UINT8*)dtlsClientClient;//s2w_ssl_cert_table[index].certAddress + 2;
        sslConnParams.clientCertName = NULL;

    }


    //(clientKeyName != NULL)
    {

        sslConnParams.clientKeyLen = sizeof(dtlsClentKey);//*(UINT16 *)s2w_ssl_cert_table[index].certAddress;
        sslConnParams.clientKey =  (UINT8*)dtlsClentKey;//s2w_ssl_cert_table[index].certAddress + 2;
        sslConnParams.clientKeyName = NULL;

    }
#endif
    nx_bsd_callback_register(s2wCidList[cid].sd, NULL, 0);    //deregister callback

    s2wCidList[cid].ssl.sslConn = (GSN_SSL_CONN_T*)gsn_malloc(sizeof(GSN_DTLS_CONN_T));

    if(NULL == s2wCidList[cid].ssl.sslConn)
    {
        return S2W_FAILURE;
    }
	memset((INT8 *)s2wCidList[cid].ssl.sslConn, 0, sizeof(GSN_DTLS_CONN_T));
    s2wCidList[cid].ssl.sslConn->sslState = GSN_SSL_STATE_INIT;
	s2wCidList[cid].ssl.sslConn->connMode = GSN_SSL_CONN_MODE_CLIENT;
	s2wCidList[cid].sslflag = TRUE;
	((GSN_DTLS_CONN_T *)(s2wCidList[cid].ssl.sslConn))->cb = AppS2w_DtslClientCb;
	GsnOsal_SemCreate(&s2wCidList[cid].s2wUserOpenInProgress, 0);
#endif
#if 1 /*SSl open is now done in Wdd task context*/
//S2w_Printf("Calling DTLS OPEN\r\n");
{
    //UINT8 *pOutData, outDataLen = 0;
    struct sockaddr_in *srvaddr = gsn_malloc(sizeof(struct sockaddr_in));
    SOCKET_INFO_T sockInfo;
    srvaddr->sin_family = AF_INET;
    srvaddr->sin_port = htons(s2wCidList[cid].remotePort);
    memcpy(&srvaddr->sin_addr.s_addr,s2wCidList[cid].remoteIp, 4);//inet_addr((char *)"192.168.1.146");

    sockInfo.sd = s2wCidList[cid].sd;
    sockInfo.dstAddrLen = sizeof(struct sockaddr_in);
    sockInfo.dstAddr = (char*)srvaddr;

    status = GsnDtls_Open((GSN_DTLS_CONN_T *)s2wCidList[cid].ssl.sslConn, &sockInfo,
        &sslConnParams );
    //S2w_Printf("Status = %d\r\n", status);
}
#else
	{
		UINT32 msg;
		/*create open sem*/
		GsnOsal_SemCreate(&s2wCidList[cid].s2wUserOpenInProgress, 0);
		s2wCidList[cid].pConnOpenParams = &sslConnParams;
		/*post message */
		msg = (S2W_MOD_NOTIF_CONN_START + cid);
		GsnMsgHandler_Post(s2wappMainTaskCtxt->pMsgHdlrExecInWddTsk, &msg);
		GsnOsal_SemAcquire(&s2wCidList[cid].s2wUserOpenInProgress,GSN_OSAL_WAIT_FOREVER);
		status = s2wCidList[cid].openStatus;
		/*Delete the semaphore*/
		GsnOsal_SemDelete(&s2wCidList[cid].s2wUserOpenInProgress);
	}
#endif
    if(status == GSN_SUCCESS)
    {
        nx_bsd_callback_register(s2wCidList[cid].sd, AppS2wHal_RxCallBack, S2W_RXCALLBACK_FLAGS);
		s2wCidList[cid].sslflag = TRUE;
	    if(GSN_OSAL_RESOURCE_NOT_AVAILABLE == GsnOsal_SemAcquire(&s2wCidList[cid].s2wUserOpenInProgress, 2000))
            return S2W_FAILURE;
        else
            return S2W_SUCCESS;
    }
    else
    {
        s2wCidList[cid].sslflag = 0;
        if(s2wCidList[cid].ssl.sslConn != NULL)
        {
            gsn_free(s2wCidList[cid].ssl.sslConn);
        }

           soc_close(s2wCidList[cid].sd);
           s2wCidList[cid].sd = CID_NOTINUSE;
           s2wCidList[cid].localPort = 0;
           s2wCidList[cid].remotePort = 0;
        return S2W_FAILURE;
    }

}
#endif
#ifdef S2W_COAP_SUPPORT
PUBLIC GSN_COAP_CONTEXT_T*
AppS2wHal_CoapHandleGet(UINT8 cid)
{
	return s2wCidList[cid].coapContext;
}

PUBLIC GSN_COAP_CONN_PARAMS_T*
AppS2wHal_CoapParamsGet(UINT8 cid)
{
	return s2wCidList[cid].coapConnParams;
}
#endif
