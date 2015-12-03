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
* $RCSfile: gsn_nwif.h,v $
*
* Description : This file contains the declarations commonly used.
*******************************************************************************/
#ifndef _GSN_NWIF_H_
#define _GSN_NWIF_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "netx/nx_api.h"
#include "netx/netx_applications/dhcp/nxd_dhcp_client.h"
#include "netx/netx_applications/dns/nxd_dns.h"

/*******************************************************************************
 * configurable parameters
 ******************************************************************************/
/* DNS related defines */
#define GSN_NWIF_DNS_RETRY_COUNT              2
#define GSN_NWIF_DNS_CASHE_SIZE               5
#define GSN_NWIF_DNS_TIMEOUT                  2

/* DHCP related related defines */
/*[TO DO]*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define GSN_NWIF_HOST_NAME_MAX_LEN          		15
#define MAX_NWIF_SUPPORTED							4

#define GSN_NWIF_IPV6_ADDR_SIZE						16
#define GSN_NWIF_IPV6_ADDR_CPY(destPtr, srcPtr)		memcpy((INT8 *)(destPtr), (const INT8 *)(srcPtr), 16)

/**
 *******************************************************************************
 * @file gsn_nwif.h
 * @brief GSN NWIF module.
 *      This file contains the NWIF specific definitions.
 ******************************************************************************/
typedef VOID (*GSN_NWIF_NOTIF_FUNC_T)(INT32 notifMsg, VOID *ctx);

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief NW Receive Filter function.
 *
 *     This type defines the receive filter function type. The user can define
 *     a function of this type and register with NWIF module. The NWIF will
 *     call this registered function for every received frame. The filter
 *     function should return FALSE to drop the frame and TRUE to pass the
 *     frame for further processing.
 * @see GsnNwIf_RecvFilterRegister.
 ******************************************************************************/
 struct GSN_NWIF_CTX;
typedef BOOL (* GSN_NWIF_RECV_FILTER_FUNC_T)      (struct GSN_NWIF_CTX*, UINT32, GSN_ETHERNET_FRAME_T *);

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief NWIF IP version definition.
 *******************************************************************************/

#define	GSN_NWIF_IP_VERSION_V4		NX_IP_VERSION_V4
#define	GSN_NWIF_IP_VERSION_V6		NX_IP_VERSION_V6

typedef enum IP_VERSION
{
  IP_VERSION_V4=0x01,
  IP_VERSION_V6=0x02,
}IP_VERSION_T;



/* Define IPv4/v6 Address structure */
typedef struct GSN_NWIF_IPADDR
{
    /* Flag indicating IP address format.  Valid values are:
       GSN_NWIF_IP_VERSION_V4 and GSN_NWIF_IP_VERSION_V6.
    */
    ULONG     ipVer;
    /* Union that holds either IPv4 or IPv6 address. */
    union
    {
        ULONG v4;
        ULONG v6[4];
    }addr;
} GSN_NWIF_IPADDR_T;

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief NWIF status.
 *     This enum defines the NWIF status.
 *******************************************************************************/
typedef enum GSN_NWIF_STATUS
{
	GSN_NWIF_STATUS_NOT_INITIALIZED,
    GSN_NWIF_STATUS_INITIALIZED,
    GSN_NWIF_STATUS_OPEN_IN_PROGRESS,
    GSN_NWIF_STATUS_OPEN_DONE,/* open is done. IP configuration may be in progress. This is tracked
    								by GSN_NWIF_IPCFG_STATUS_T*/
} GSN_NWIF_STATUS_T;

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief NWIF IP V4 address configuration status.
 *******************************************************************************/

#define    GSN_NWIF_IPV4_CFG_NOT_DONE 		0
#define    GSN_NWIF_IPV4_CFG_IN_PROGRESS 	1
#define    GSN_NWIF_IPV4_CFG_DONE 			2
#define    GSN_PRIMARY_DNS_SERVER               0
#define    GSN_SECONDARY_DNS_SERVER             1   
/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief NWIF IP V6 address configuration status.
 *******************************************************************************/

#define    GSN_NWIF_IPV6_CFG_NOT_DONE 		0
#define    GSN_NWIF_IPV6_CFG_IN_PROGRESS 	1
#define    GSN_NWIF_IPV6_CFG_DONE 			2

#define GsnNwIf_DnsRetryCountSet nx_dns_retry_count_set

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief NWIF IP configuration.
 *
 *     This structure defines the NWIF IP V4configuration used for configuring the
 *     network interface.
 ******************************************************************************/
typedef struct GSN_NWIF_IP4_CONFIG
{
    UINT32          staticIp;            	/**< '1' if static IP configuration, '0' if DHCP needs to be
    											performed. */

    UINT32          ipAddr;              	/**< IP address if already known ie., in case of static IP or in
    											case DHCP has already been done. */

    UINT32          subnetMask;          	/**< Subnet mask if already known.  */

    UINT32          gatewayIpAddr;       /**< Gateway IP address if already known.  */

    ULONG64         dhcpLeaseExpireTime; /**< DHCP lease expiry time if DHCP has already been done. This is used by NW service
											module to renew DHCP IP if DHCP lease has expired. */

    UINT32          dnsPriSrvrIp;        /**< DNS Primary Server IP address.  */
    UINT32          dnsSecSrvrIp;        /**< DNS Secondary Server IP address.  */
    UINT8           hostName[GSN_NWIF_HOST_NAME_MAX_LEN + 1];           /**< Node host name  */
} GSN_NWIF_IPv4_CONFIG_T;

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief NWIF IP v6 configuration flags.
 *
 *     This enum defines the IP v6 configuration flags.
 ******************************************************************************/
typedef enum GSN_NWIF_IP6_FLG
{
	GSN_NWIF_IP6_FLG_MANUAL_LINK_LOCAL_ADDR 		= BIT(0),
	GSN_NWIF_IP6_FLG_MANUAL_GLOBAL_ADDR 			= BIT(1),
	GSN_NWIF_IP6_FLG_STATELESS_AUTO_CONFIG		        = BIT(2),
	GSN_NWIF_IP6_FLG_DHCP_V6_CONFIG				= BIT(3),
        GSN_NWIF_IP6_FLG_AUTO_LINK_LOCAL_ADDR                   =BIT(4)
}GSN_NWIF_IP6_FLG_T;

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief NWIF IP configuration.
 *
 *     This structure defines the NWIF IP V6 configuration used for configuring the
 *     network interface.
 ******************************************************************************/
typedef struct GSN_NWIF_IP6_CONFIG
{
	GSN_NWIF_IP6_FLG_T  	flags;
	ULONG					linkLocalAddr[4];				/**< Link local address */
	ULONG					globalAddr[4];					/**< global address */
	ULONG					prefixLen;						/**< Global Addr prefix Len*/
	/* [TO DO] add "duid type" member, which will be then configured by the user. this will be used
	during the nx_dhcpv6_create_client_duid() in GsnNwIf_DhcpV6Strat() */
	ULONG 					duidTimeField;
	ULONG					ianaID;
	ULONG 					T1;
	ULONG					T2;
	ULONG   				preferredLifeTime;
	ULONG					validLifeTime;
	ULONG					primaryDnsSrvrAddr[4];
	ULONG					secndryDnsSrvrAddr[4];
} GSN_NWIF_IPv6_CONFIG_T;

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief NWIF IP  configuration flags.
 *
 *     This enum defines the IP  configuration flags.
 ******************************************************************************/
typedef enum GSN_NWIF_IPCONFIG_FLAG
{
	GSN_NWIF_IPCONFIG_FLAG_IPV4_INIT = BIT(0),
	GSN_NWIF_IPCONFIG_FLAG_IPV6_INIT = BIT(1),
}GSN_NWIF_IPCONFIG_FLAG_T;


/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief NWIF IP configuration.
 *
 *     This structure defines the NWIF IP  configuration used for configuring the
 *     network interface. This structure must be filled up for opening the
 *     network interface.
 ******************************************************************************/
typedef struct GSN_NWIF_IP_CONFIG
{
	GSN_NWIF_IPCONFIG_FLAG_T	flag;
	GSN_NWIF_IPv4_CONFIG_T 		ipv4;
	GSN_NWIF_IPv6_CONFIG_T 		ipv6;
} GSN_NWIF_IP_CONFIG_T;


/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief NWIF IP v6 configuration flags.
 *
 *     This enum defines the IP v6 configuration flags.
 ******************************************************************************/
typedef enum GSN_NWIF_FLAGS
{
	GSN_NWIF_FLG_ARP_ENABLE = 			BIT(0),
	GSN_NWIF_FLG_DHCP_CLIENT_ENABLE = 	BIT(1),
	GSN_NWIF_FLG_DNS_CLIENT_ENABLE = 	BIT(2),
	GSN_NWIF_FLG_ICMP_ENABLE = 			BIT(3),
	GSN_NWIF_FLG_IGMP_ENABLE = 			BIT(4),
	GSN_NWIF_FLG_IPV6_ENABLE = 			BIT(5),/**< enable ICMP and IGMP along with this*/
	GSN_NWIF_FLG_RPL_ENABLE = 			BIT(6),/**< enable ICMP and IGMP along with this*/
}GSN_NWIF_FLAGS_T;

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief NWIF IP v6 configuration flags.
 *
 *     This enum defines the IP v6 configuration flags.
 ******************************************************************************/
typedef struct GSN_NWIF_DHCP_PARAMS
{
	UINT32 	dhcpRetryTimeout;/* Retransmission Tiomeout. This will be the time interval 
                                                    (in Sec) between two successive retries*/
	UINT32 	dhcpMaxRetryCnt;
	UINT8 *	pStack;
	UINT32 	stackSize;
	GSN_NW_PKT_POOL_HANDLE *pPktPoolHndl;/**< memory pool handle to be used by dhcp v4/v6 task*/
	
	UINT32	sysQualTskID;	/**< sys qual task ID for the DHCP task*/
	UINT32	sysQualTicks;	/**< sys qual ticks */
        UINT32    ianaID;
        UINT32    T1;
        UINT32    T2;
        UINT32    preferredLifeTime;
        UINT32    validLifeTime;
	NX_DHCP_CLIENT_RECORD *pDhcpCliRecord;	
	ULONG timeElapsed;/* In terms of Nw stack tics*/    
	UINT8 radioMode;/*GSN_WDD_RADIO_MODE_T*/
  
    UINT32 requestLeaseTime; /* Lease time requested. this value will be used in 
                                                    "Lease Time" option in Discover and
                                                    Request packets*/                                                 
}GSN_NWIF_DHCP_PARAMS_T;

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief Network Interface Object.
 *
 *     This type defines the network interface object. The network interface
 *     object is used to configure and open a network interface on a given
 *     L2 device. There could be multiple network interface objects in the
 *     system each providing a network interface.
 ******************************************************************************/
typedef struct GSN_NWIF_CTX
{
	GSN_NWIF_FLAGS_T flags; /*flags related to the interface*/
	GSN_NW_CTX_T *pNwCtx; /**< Pointer to the Nw module context*/
	/**< L2 and L3 instance handles */
    GSN_L2_DEV_T *pL2Dev;  /**< L2 device object for data transmit and receive */
	UINT32 mtu; /**< MTU for this interface*/
   	NX_IP ipHndl; /**< IP instance */
	GSN_NW_PKT_POOL_HANDLE *pIpPktPoolHndl;/**< IP instatnce memory pool handle*/
	NX_DHCP dhcpCliHndl;/**< DHCP client handle */
	UINT8 	dhcpOldState;/*Note!!! chaged the name from dhcpStateChange after C1 ROM*/
	UINT8	dhcpStopInprogress;
	NX_DHCPV6 dhcpV6CliHndl; /**< IPV6 information */
	GSN_SOFT_TMR_T	radioTmr;/*Note!!! chaged the name  after C1 ROM*/
	GSN_SOFT_TMR_HANDLE_T radioTmrHndl;/*Note!!! chaged the name after C1 ROM*/
	NX_DNS dnsCliHndl; /**< DNS client handle */
	GSN_NWIF_RECV_FILTER_FUNC_T ipRecvFilter; /**< Receive Filter*/

	/**< Pointer to other objects used*/
	/*[TO DO] add pointer to power management module if required*/

	/**< objects used for internal usage*/
	GSN_NWIF_STATUS_T status; /**< status of the Nw Interface*/
	UINT16 ipv4CfgStatus;
	UINT16 ip6CfgStatus;
	UINT32 timeoutCnt; /**< count of 100 mSec timeout */
	GSN_NWIF_IP_CONFIG_T ipConfig; /**< IP configuration of the interface */
	GSN_NWIF_NOTIF_FUNC_T notifyCb; /**< Notification call back*/
        GSN_NWIF_NOTIF_FUNC_T notifyIpv6Cb; /**< IPv6 Notification call back*/
	VOID *notifyCtxt;/**< Call back context*/
	GSN_NWIF_STATS_T *pStats;
	UINT8 radioModeSet;
	GSN_OSAL_MUTEX_T protectionLock;
	UINT8 radioMode;/*GSN_WDD_RADIO_MODE_T*/
} GSN_NWIF_CTX_T;

typedef struct GSN_NW_BSD
{
	NX_IP *pIpHndl;
}GSN_NW_BSD_T;
/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief Info required by NWIF.
 *
 *     This structure defines info needed by NWIF and need to be passed in Init
 *     function.
 ******************************************************************************/
typedef struct GSN_NWIF_INIT_PARAMS
{
	GSN_NWIF_FLAGS_T flags;
    char *nwIfName;         /**< NWIF name */
    GSN_NW_CTX_T *pNwCtx; /**< Pointer to the Nw module context*/
    GSN_L2_DEV_T *pL2Dev;  /**< L2 device object for data transmit and receive */
    /*[TO DO]*/ 			/**< Power management object for power save */
	UINT32 mtu; /**< MTU for this interface*/
	GSN_NWIF_RECV_FILTER_FUNC_T ipRecvFilter; /**< Receive Filter*/
	/**< Each IP instance will run its own thread. Fill in this thread related parameters*/
	INT8 *ipTskStack;
	UINT32 ipTskStackSize;
	UINT32 ipTskPrio;
	UINT32 ipTskSysQualID;	/**< sys qual task ID for the IP task*/
	UINT32 ipTskSysQualTicks;/**< sys qual ticks */

	/**< Each IP instance will have its own memory pool*/
	GSN_NW_PKT_POOL_HANDLE *pIpPktPoolHndl;/**< IP instatnce memory pool handle*/

	/**< Each IP instance will have its own ARP cache. Fill info related to ARP cache*/
	INT8 *arpCache; /**< Pointer to ARP cache area*/
	UINT32 arpCacheSize; /**< ARP cache size */
	GSN_NWIF_STATS_T *pStats;
} GSN_NWIF_INIT_PARAMS_T;

typedef struct GSN_NWIF_REINIT_PARAMS
{
	UINT32 dummy;
}GSN_NWIF_REINIT_PARAMS_T;

typedef struct GSN_NWIF_BSD_INIT_PARAM
{
	NX_IP *pIpHndl;
	GSN_NW_PKT_POOL_HANDLE *pBsdPktPoolHndl;
	INT8 *bsdTskStack;
	UINT32 bsdTskStackSize;
	UINT32 bsdTskPrio;
}GSN_NWIF_BSD_INIT_PARAM_T;

typedef struct GSN_NWIF_IPV6_INIT_PARAM
{
	UINT32 dummy;
}GSN_NWIF_IPV6_INIT_PARAM_T;


typedef enum GSN_IPv6_TYPE
{
	GSN_IPv6_LINK_LOCAL,
	GSN_IPv6_GLOBAL,
	GSN_IPv6_INVALID,
	GSN_IPv6_UNSPECIFIED,
	GSN_IPv6_LOOPBACK,
	GSN_IPv6_MULTICAST,

}GSN_IPv6_TYPE_T;

PUBLIC INLINE VOID 
GSN_IPv6_CHANGE_ENDIAN(UINT32 *a)
{
	a[0] = htonl(a[0]);
	a[1] = htonl(a[1]);
	a[2] = htonl(a[2]);
	a[3] = htonl(a[3]);
}

PUBLIC INLINE UINT32  
GSN_IPv6_ADDR_TYPE(UINT32 *a)
{
	UINT32 temp;

	if((a[0] & 0xFF000000)==0xFF000000)
	{
		return GSN_IPv6_MULTICAST;
	}

	if((a[0] & 0xFE800000)==0xFE800000) 
	{
		return GSN_IPv6_LINK_LOCAL;
	}
	
	temp = a[0] | a[1] | a[2];
	if(temp == 0)
	{
		if(a[3] == 1)
		{
			return GSN_IPv6_LOOPBACK;
		}
		if(a[3] == 0)
		{
			return GSN_IPv6_UNSPECIFIED;
		}
	}

	return GSN_IPv6_GLOBAL;
}

PUBLIC INLINE VOID
GsnNwif_Ipv6AutoConfig(GSN_NWIF_CTX_T *pNwIf,UINT flags)
{
	pNwIf->ipHndl.ipv6_auto_conf_flag = flags;
}
/*******************************************************************************
 *  Public Functions prototypes
 ******************************************************************************/
/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief Get IP Address.
 *
 *	  This function returns the IP address configured for the given network
 *	  interface.
 * @param pNwIf - IN Pointer to NWIF object.
 * @return IP address.
 *******************************************************************************/
PUBLIC INLINE UINT32
GsnNwIf_IpV4AddrGet(GSN_NWIF_CTX_T *pNwIf)
{
	return pNwIf->ipConfig.ipv4.ipAddr;
}

PUBLIC GSN_STATUS
GsnNwIf_Init(GSN_NWIF_CTX_T *pNwIf, GSN_NWIF_INIT_PARAMS_T *pParams);

PUBLIC GSN_STATUS
GsnNwIf_Reinit(GSN_NWIF_CTX_T *pNwIf, GSN_NWIF_REINIT_PARAMS_T *pParams);

PUBLIC GSN_STATUS
GsnNwif_BsdInitialize(GSN_NW_BSD_T *pBsd, GSN_NWIF_BSD_INIT_PARAM_T *pParam);

PUBLIC GSN_STATUS
GsnNwif_IPv6Init(GSN_NWIF_CTX_T *pNwIf, GSN_NWIF_IPV6_INIT_PARAM_T *pParams);

PUBLIC GSN_STATUS
GsnNwIf_DeInit(GSN_NWIF_CTX_T *pNwIf);

PUBLIC GSN_STATUS
GsnNwif_UpdatePhyAddr(GSN_NWIF_CTX_T *pNwIf);


PUBLIC GSN_STATUS_T
GsnNwIf_Open(GSN_NWIF_CTX_T *pNwIf, 		GSN_NWIF_IP_CONFIG_T *pIpConfig, GSN_NWIF_DHCP_PARAMS_T *pDhcpParams);

PUBLIC GSN_STATUS_T
GsnNwIf_Close(GSN_NWIF_CTX_T *pNwIf);

PUBLIC GSN_NWIF_RECV_FILTER_FUNC_T
GsnNwIf_RecvFilterRegister(GSN_NWIF_CTX_T *pNwIf,
                            GSN_NWIF_RECV_FILTER_FUNC_T recvFilter);

PUBLIC BOOL
GsnNwIf_IpConfigured(GSN_NWIF_CTX_T *pNwIf);

PUBLIC VOID
GsnNwIf_IpConfigGet(GSN_NWIF_CTX_T *pNwIf, GSN_NWIF_IP_CONFIG_T *pIpConfig);

PUBLIC VOID
GsnNwIf_StatsGet(GSN_NWIF_CTX_T *pNwIf, GSN_NWIF_STATS_T *pStats);

PUBLIC GSN_STATUS
GsnNwIf_GratArpSend(GSN_NWIF_CTX_T *pNwIf);

PUBLIC VOID
GsnNwIf_DhcpLeaseTimeSet(GSN_NWIF_CTX_T *pNwIf,
                            ULONG64 dhcpLeaseTime);

PUBLIC BOOL
GsnNwIf_DhcpLeaseExpired(ULONG64 dhcpLeaseExpireTime);

PUBLIC GSN_STATUS_T
GsnNwIf_DhcpStrat(GSN_NWIF_CTX_T *pNwIf, GSN_NWIF_DHCP_PARAMS_T *pDhcpParams);

VOID
GsnNwIf_DhcpStop(GSN_NWIF_CTX_T *pNwIf);

VOID
GsnNwIf_DhcpV6Stop(GSN_NWIF_CTX_T *pNwIf);

GSN_STATUS_T
GsnNwif_PrivateIPv4Config(GSN_NWIF_CTX_T *pNwIf,GSN_NWIF_IPv4_CONFIG_T *pUsrIPv4Cfg,
									GSN_NWIF_DHCP_PARAMS_T *pDhcpParams);

PUBLIC GSN_STATUS
GsnNwIf_DnsHostByNameGet(GSN_NWIF_CTX_T *pNwIf,UINT8 *pHostName,ULONG *DnsAddress,ULONG timeout);

PUBLIC GSN_STATUS
GsnNwif_IPv4Configure(GSN_NWIF_CTX_T *pNwIf,GSN_NWIF_IPv4_CONFIG_T *pUsrIPv4Cfg,
									GSN_NWIF_DHCP_PARAMS_T *pDhcpParams);

PUBLIC GSN_STATUS
GsnNwif_IPv6Configure(GSN_NWIF_CTX_T *pNwIf,GSN_NWIF_IPv6_CONFIG_T *pUsrIPv6Cfg,
									GSN_NWIF_DHCP_PARAMS_T *pDhcpParams);


/*******************************************************************************
 * Private definitions, to be used inside the module
 ******************************************************************************/
typedef struct GSN_NWIF_TBL_ELEMENT
{
	GSN_NWIF_CTX_T *pNwIf;
	NX_IP *ipHndl;
}GSN_NWIF_TBL_ELEMENT_T;

GSN_NWIF_CTX_T *
GsnNwIf_NwIfCtxGet(NX_IP *ipHndl);

UINT16
GsnNwIf_U16FieldGet(UINT8 *pPkt);

VOID
GsnNwIf_TableEntrySet(GSN_NWIF_CTX_T * pNwIf, NX_IP *ipHndl);

VOID
GsnNwIf_TableEntryClear(GSN_NWIF_CTX_T * pNwIf, NX_IP *ipHndl);

GSN_STATUS_T
GsnNwif_DnsServerAdd(GSN_NWIF_CTX_T *pNwIf,ULONG dnsServerAddr,UINT32 index);

GSN_STATUS_T
GsnNwif_DnsServerGet(GSN_NWIF_CTX_T *pNwIf,ULONG *dnsServerAddr,UINT32 index);

GSN_STATUS_T
GsnNwIf_dhcpClientCreateRecord(GSN_NWIF_CTX_T *pNwIf,NX_DHCP_CLIENT_RECORD *pDhcpClientRecord);

GSN_STATUS_T
GsnNwIf_dhcpClientRestoreRecord(GSN_NWIF_CTX_T *pNwIf,NX_DHCP_CLIENT_RECORD *pDhcpClientRecord,ULONG timeElapsed);

#ifdef __cplusplus
}
#endif

#endif /* _GSN_NWIF_H_ */


