/*
 * Copyright Notice:
 * Copyright Treck Incorporated  1997 - 2012
 * Copyright Elmic Systems Japan 1997 - 2012
 * No portions or the complete contents of this file may be copied or
 * distributed in any form (including but not limited to printed or electronic
 * forms) without the expressed written consent of Treck Incorporated OR
 * Elmic Systems.  Copyright laws and International Treaties protect the
 * contents of this file.  Unauthorized use is prohibited.
 * All rights reserved.
 *
 * Description: Global Definitions for trinit.c.
 * Filename: trglobal.h
 * Author: Odile & Paul
 * Date Created:
 * $Source: /home/cvsroot/gs2000_app_sw/afw/system/gsn/src/modules/http/include/trglobal.h,v $
 *
 * Modification History
 * $Revision: 1.1 $
 * $Date: 2013/02/26 09:28:54 $
 * $Author: aravind $
 * $ProjectName: /home/mks/proj/tcpip.pj $
 * $ProjectRevision: 6.0.1.29 $
 */

#ifndef _TRGLOBAL_H_

#define _TRGLOBAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * All global variables are either in ttGlobal (true global), or in 
 * ttContext (per context variables). If user does not use multiple context
 * context variables are true global variables, but are still kept in separate
 * ttContext structure.
 */
typedef struct tsGlobal
{
#ifdef TM_USE_SHEAP
/* Simple heap variables */
    ttRawMemoryPtr                      tvSheapFreeListPtr;
    ttRawMemoryPtr                      tvSheapFragmentListPtr;
    tt32Bit                             tvSheapUsedLongs;
    tt32Bit                             tvSheapPageSize;
#endif /* TM_USE_SHEAP */

#ifdef TM_LOCK_NEEDED
#ifdef TM_USE_SHEAP
/* Simple heap lock */
#define TM_GLBL_SHEAP_LOCK_IDX      0
#define tvSheapLock                 tvLocks[TM_GLBL_SHEAP_LOCK_IDX]
#else /* !TM_USE_SHEAP */
#define TM_GLBL_SHEAP_LOCK_IDX     -1 
#endif /* !TM_USE_SHEAP */

#ifdef TM_USER_PACKET_DATA_ALLOC
#define TM_GLBL_PKTDATA_LOCK_IDX (TM_GLBL_SHEAP_LOCK_IDX + 1)
/* User packet data alloc lock */
#define tvPacketDataAllocLock       tvLocks[TM_GLBL_PKTDATA_LOCK_IDX]
#else /* !TM_USER_PACKET_DATA_ALLOC */
#define TM_GLBL_PKTDATA_LOCK_IDX TM_GLBL_SHEAP_LOCK_IDX
#endif /* !TM_USER_PACKET_DATA_ALLOC */

#if defined(TM_USE_SNIFF)
#define TM_GLBL_SNIFF_LOCK_IDX  (TM_GLBL_PKTDATA_LOCK_IDX + 1)
/* Packet sniff atomic I/O lock */
#define tvSniffLock                 tvLocks[TM_GLBL_SNIFF_LOCK_IDX]
#else /* !TM_USE_SNIFF */
#define TM_GLBL_SNIFF_LOCK_IDX  TM_GLBL_PKTDATA_LOCK_IDX
#endif /* !TM_USE_SNIFF */

#if defined(TM_USE_SHEAP) || defined(TM_USER_PACKET_DATA_ALLOC) || defined(TM_USE_SNIFF)
#define TM_GLBL_MAX_LOCKS   (TM_GLBL_SNIFF_LOCK_IDX + 1)
    ttLockEntry                         tvLocks[TM_GLBL_MAX_LOCKS];
    ttCountSem                          tvCountSems[TM_GLBL_MAX_LOCKS];
#endif /* TM_USE_SHEAP || TM_USER_PACKET_DATA_ALLOC || TM_USE_SNIFF */
#endif /* TM_LOCK_NEEDED */

#ifdef TM_USE_RAM_FS
/* RAM file system: RAM drive pointer */
    ttVoidPtr                           tvRamfsPtr;
    ttLockEntry                         tvRamfsLockEntry;
#endif /* TM_USE_RAM_FS */
#ifdef TM_MULTIPLE_CONTEXT
    ttList                              tvContextHead; /* head of context lists */
/* Last context ID */
    ttUser32Bit                         tvLastContextId;
/*
 * The current network ID used for multiple context interface driver
 */
    ttUser32Bit                         tvCurrNetworkId;
#endif /* TM_MULTIPLE_CONTEXT */
#if (defined TM_USE_DOS_FS) || (defined TM_USE_EMU_UNIX_FS)
/* Dos Root */
    char                       TM_FAR * tvRootDirPtr;
#endif /* TM_USE_DOS_FS || TM_USE_EMU_UNIX_FS */

#ifdef TM_GLBL_MAX_LOCKS
    tt8Bit                              tvCountSemFlags[TM_GLBL_MAX_LOCKS]; 
#endif /* TM_GLBL_MAX_LOCKS */

/* to make sure ttGlobal is not empty */
    tt8Bit                              tvDummy;
} ttGlobal;

typedef ttGlobal TM_FAR * ttGlobalPtr;

/*
 * Per context variables.
 */

typedef struct tsContext
{
#if 0
#ifdef TM_MULTIPLE_CONTEXT
    ttNode                              tvContextNode; /* links in context list */
/* This context ID */        
    ttUser32Bit                         tvContextId;
#endif /* TM_MULTIPLE_CONTEXT */
#ifdef TM_ERROR_CHECKING
/* Temporary buffer used by tm_assert() to build the error message */
    char                                tvAssertTempBuf[256];
#endif  /* TM_ERROR_CHECKING */
#if ( (defined(TM_LOCK_NEEDED) || defined(TM_PEND_POST_NEEDED)) )
    ttCountSemPtr                       tvCountSemListPtrArr[2];
#define TM_COUSEM_ALLOC_INDEX  0
#define TM_COUSEM_RECYC_INDEX  1
/* Counting semaphores allocated list */
#define tvCountSemAllocListPtr          tvCountSemListPtrArr[TM_COUSEM_ALLOC_INDEX]
/* Counting semaphores recycle list */
#define tvCountSemRecycListPtr          tvCountSemListPtrArr[TM_COUSEM_RECYC_INDEX]
/* Keep track of counting semaphores currently in use */
    int                                 tvCountSemUsedCount; 
#endif  /* ( (defined(TM_LOCK_NEEDED) || defined(TM_PEND_POST_NEEDED))  */

#ifdef TM_PEND_POST_NEEDED
/* Select pend entry recycle list */
    ttList                              tvSelPendEntryHead;
#ifdef TM_LOCK_NEEDED
/* Lock for select pend entry recycle list */
    ttLockEntry                         tvSelPendEntryLock;
#endif /* TM_LOCK_NEEDED */
#endif /* TM_PEND_POST_NEEDED */
/*
 * Only used for dynamic memory management.
 */
#ifdef TM_USE_DYNAMIC_MEMORY
/*
 * Raw Memory Queues
 */
    ttRawMemoryPtr                      tvBufQListPtr[TM_BUF_Q_NUM];
/* 
 * Recycled buffer lists.
 */
    ttRcylPtr                           tvRcyListPtr[TM_RECY_NUM];
#ifdef TM_LOCK_NEEDED
/*
 * Dynamic Memory Queue Lock
 */
    ttLockEntry                         tvDynMemLockEntry;
#endif /* TM_LOCK_NEEDED */
/* Amount of memory in use by the stack (not recycled, not freed) */
    tt32Bit                             tvMemRecycledBytes;
#endif /* TM_USE_DYNAMIC_MEMORY */



#ifdef TM_USE_IPV4
#ifdef TM_USE_FILTERING
    ttUserFilterCallback                tvUserFilterCallback;
#endif /* TM_USE_FILTERING */
#ifdef TM_USE_IGMP_FILTERING
    ttUserIgmpFilterCallback            tvUserIgmpFilterCallback;
#endif /* TM_USE_IGMP_FILTERING */
#endif /* TM_USE_IPV4 */
#ifdef TM_USE_IPV6
#ifdef TM_6_USE_FILTERING
    tt6UserFilterCallback               tv6UserFilterCallback;
#endif /* TM_6_USE_FILTERING */
#endif /* TM_USE_IPV6 */
#ifdef TM_USE_TIMER_CB
    ttUserTimerCBFuncPtr                tvTimerCBFuncPtr;
    ttUserGenericUnion                  tvTimerCBParam;
#endif /* TM_USE_TIMER_CB */

/* Low Water Mark for notifying device send completes. Accessed in ISR. */
    tt32Bit                             tvNotifySendCompLowWater;


/* 
 * all crypto engine, software engine or hifn7951 
 * hardware crypto engine, are linked here.
 */
   ttVoidPtr            tvCryptoLibPtr;
#ifdef TM_LOCK_NEEDED
   ttLockEntry          tvCryptoLockEntry;
#endif /* TM_LOCK_NEEDED */







/* when multiple PPP authentication method is used, such as CHAP, 
 * PAP and MSCHAP, we need assign priority value to each method, 
 * so that the authenticator can control the proposal order according
 * to the priority.
 * If MS-CHAP is not used, we always prefer CHAP to PAP
 */
    tt32Bit             tvPppAuthPriority;

#ifdef TM_SNMP_MIB
    ttVoidPtr           tvSnmpdPtr;
#endif /* TM_SNMP_MIB */

#ifdef TM_SNMP_CACHE
    ttSnmpdCacheHead    tvSnmpdCaches[TM_SNMPD_CACHES];
#endif /* TM_SNMP_CACHE */

#ifdef TM_USE_IPV6
    ttDeviceEntryPtr    tv6McastDevPtr;

#ifdef TM_6_USE_PREFIX_DISCOVERY
/* Stateless Address Auto-Configuration prefix aging timer */
    ttTimerPtr          tv6RtPrefixAgingTimerPtr;
#endif /* TM_6_USE_PREFIX_DISCOVERY */

#ifdef TM_6_USE_NUD
/* Neighbor Unreachability Detection reachable timer */
    ttTimerPtr          tv6ReachableTimerPtr;
#endif /* TM_6_USE_NUD */

#ifdef TM_6_IP_REASSEMBLY
/* Timer used for IPv6 reassembly timeouts. */
    ttTimerPtr          tv6IpFHTimerPtr;

/* Queue of fragment heads */
    tt6IpFHEntryPtr     tv6IpFHPtr;
#endif /* TM_6_IP_REASSEMBLY */

#ifdef TM_USE_IPV6
/* IPv6-over-IPv6 virtual link layer handle. */    
    ttLinkLayerEntryPtr tv6Ipv6TunnelLinkLayerHandle; 

#ifdef TM_USE_IPV4
/* IPv6-over-IPv4 virtual link layer handle. */
    ttLinkLayerEntryPtr tv6Ipv4TunnelLinkLayerHandle;

/* Default configured tunnel device entry pointer. */
    ttDeviceEntryPtr    tv6Ipv4DefGwTunnelPtr;

/* IPv6-over-IPv4 automatic tunnel device entry pointer. */
    ttDeviceEntryPtr    tv6Ipv4AutoTunnelPtr;

/* Handles ICMPv4 errors in an IPv6 tunnel */
    tt6TunnelIcmpErrorFuncPtr tv6Ipv4IcmpTunnelFuncPtr;
#endif /* TM_USE_IPV4 */

/* Handles ICMPv6 errors in an IPv6 tunnel */
    tt6TunnelIcmpErrorFuncPtr tv6Ipv6IcmpTunnelFuncPtr;
#endif /* TM_USE_IPV6 */
    
#ifdef TM_6_IP_REASSEMBLY
#ifdef TM_LOCK_NEEDED
/* Lock for the fragment head list. */
    ttLockEntry         tv6IpFHLock;
#endif /* TM_LOCK_NEEDED */
#endif /* TM_6_IP_REASSEMBLY */

/* IPv6 cached routing entry. */
    ttRtCacheEntry      tv6RtIpForwCache;

/* IPv6 cached routing entry lock - needed even if TM_LOCK_NEEDED is not
   defined. */
    ttLockEntry         tv6RtIpForwCacheLock;

/* IPv6 send routing cache entry. */
    ttRtCacheEntry      tv6RtIpSendCache;

/* IPv6 send routing cache lock entry.
   Needed also when TM_LOCK_NEEDED not defined */
    ttLockEntry         tv6RtIpSendCacheLock;

#ifdef TM_6_USE_RAW_SOCKET
/* IPv6 raw socket cache lock */
    ttLockEntry         tv6RawCacheLock;

/* Cached IPv6 raw socket. */
    ttSocketEntryPtr    tv6RawSocketPtr;
#endif /* TM_6_USE_RAW_SOCKET */
#ifdef TM_6_IP_FRAGMENT
/* 
 * Used to populate Identification field in IPv6 Fragment extension header
 * ([RFC2460].R4.5:30)
 */
    tt32Bit             tv6IpFragId;
#endif /* TM_6_IP_FRAGMENT */
#ifdef TM_6_IP_REASSEMBLY
/* Fragmentation resolution (default, 60 seconds). */
    tt32Bit             tv6FragResolution;

/* Maximum size in bytes of an IPv6 datagram waiting to be reassembled */
    tt32Bit             tv6FragEntryMaxSize;
#endif /* TM_6_IP_REASSEMBLY */
    
/* Maximum number of times to send unicast Neighbor Solicitation 
   when trying to resolve an address. */
    tt32Bit             tv6NdUnicastRequestTries;

/* Maximum number of times to send multicast Neighbor Solicitation 
   when trying to resolve an address. */
    tt32Bit             tv6NdMcastRequestTries;
#ifdef TM_6_USE_ARP_QUIET_TIME
/* IPv6 ARP quiet time */
    tt32Bit             tv6NdQuietTime;
#endif /* TM_6_USE_ARP_QUIET_TIME */

/* Limit the rate at which ICMPv6 error messages are sent.
   ([RFC2463].R2.4:100 updated by [RFC4443].R2.4(f)) */
    tt32Bit             tv6IcmpTxErrLastTickCnt;
    tt32Bit             tv6IcmpTxErrTokenCnt;

/* Refer to TM_6_OPTION_ICMP_TX_ERR_LIMIT. ([RFC2463].R2.4:110 updated by
 * [RFC4443].R2.4(f)) */
    tt32Bit             tv6IcmpTxErrLimitMsec;

/* Refer to TM_6_OPTION_ICMP_TX_ERR_BURST. ([RFC4443].R2.4(f)) */
    tt32Bit             tv6IcmpTxErrLimitBurst;



#ifdef TM_6_PMTU_DISC
/* The amount of time (in seconds) to wait before increasing an IPv6
   Path MTU estimate. */
    tt32Bit             tv6RtPathMtuTimeout;
#endif /* TM_6_PMTU_DISC */
#endif /* TM_USE_IPV6 */

#ifdef TM_USE_LOGGING_LEVELS
    ttLogLevelStoragePtr       tvLogLevelStoragePtr;
#endif /* TM_USE_LOGGING_LEVELS */
#if (defined(TM_DEBUG_LOGGING) || defined(TM_TRACE_LOGGING) || \
     defined(TM_ERROR_LOGGING) || defined(TM_MEMORY_LOGGING) || \
     defined(TM_USE_LOGGING_LEVELS))
/* support for debug, error and trace logging to circular buffer */
    ttLogCtrlBlkPtr     tvLogCtrlBlkPtr;
#endif

/* lookup table used to optimize storage of device pointer so that it only
   requires a 16-bit SNMP device index (1-based). */
    ttDeviceEntryPtr    tvDevIndexToDevPtr[TM_MAX_NUM_IFS + 1];

#if (defined(TM_OPTIMIZE_MANY_MHOMES) && !defined(TM_SINGLE_INTERFACE_HOME))
/* sort IP addresses to improve performance of IP address lookup in the
   receive-path when many IP aliases are configured on a single interface.
   The SNMP Agent can use this to speed up non-exact match processing
   in tfIpAddrTableEntryGet. */

#ifdef TM_USE_IPV4
    ttSortedIpAddrCache tv4SortedIpAddrCache;
#endif /* TM_USE_IPV4 */

#ifdef TM_USE_IPV6
    ttSortedIpAddrCache tv6SortedIpAddrCache;
#endif /* TM_USE_IPV6 */
#endif /* TM_OPTIMIZE_MANY_MHOMES and not TM_SINGLE_INTERFACE_HOME */

/* 
 * Globals Initialized Flag
 */
    tt32Bit               tvContextGlobalsSet;
/*
 * Timer variables.
 */
/* Control block for managing timer queues */
    ttTimerCtrl           tvTimerCtrl;
#ifdef TM_USE_TIMER_WHEEL
/* Maximum timer interval on the timer wheel */
    tt32Bit               tvTimerMaxWheelIntv;
#endif /* TM_USE_TIMER_WHEEL */
#ifdef TM_DEMO_TIME_LIMIT
    ttTimer               tvDemoTimer;
#endif /* TM_DEMO_TIME_LIMIT */

/*
 * ARP Resolve Queue
 */
    ttPacketPtr           tvArpResolveQueuePtr;
#ifdef TM_LOCK_NEEDED
    ttLockEntry           tvArpResolveQLock;
    ttLockEntry           tvArpResolveLockEntry;
#endif /* TM_LOCK_NEEDED */

/*
 * ARP resolution
 */

    tt32Bit               tvArpRequestTries;
    tt32Bit               tvArpRetryTime;
    tt32Bit               tvArpQuietTime;


/* 
 * ARP cache
 */

/* ARP entry timeout in milliseconds (600,000) */
    tt32Bit               tvArpTimeout;
/* ARP entries timer resolution in milliseconds (60,000) */
    tt32Bit               tvArpResolution;
/* Maximum number of ARP cache entries */
    int                   tvArpMaxEntries;
/* No socket errorCode */
    int                   tvErrorCode;
/*
 * Proxy ARP table
 */
/* Pointer to first element of proxy Arp table */
    ttProxyEntryPtr       tvProxyHeadPtr;
/* Proxy Lock */
    ttLockEntry           tvProxyLockEntry;


/* array of socket pointers */
    ttSocketEntryPtrPtr   tvSocketArray;
    tt16BitPtr            tvSocketErrorArray;
/* Maximum number of sockets */
    tt32Bit               tvMaxNumberSockets;
/* Number of open sockets */
    tt32Bit               tvNumberOpenSockets;
#ifdef TM_USE_TCP
/* Maximum number of allocated TCP sockets */
    tt32Bit               tvMaxTcpVectAllocCount;
/* Number of allocated TCP sockets */
    tt32Bit               tvTcpVectAllocCount;
/* Maximum number of allocated Time Wait TCP Vectors */
    tt32Bit               tvMaxTcpTmWtAllocCount;
/* Number of Time Wait TCP vectors in hash table lists */
    tt32Bit               tvTcpTmWtTableMembers;
#endif /* TM_USE_TCP */
/* Last slot used in the socket array */
    tt32Bit               tvSocketSearchIndex;
#ifdef TM_LOCK_NEEDED
/* Socket array lock */
    ttLockEntry           tvSocketArrayLock;
#endif /* TM_LOCK_NEEDED */
/*
 * Lookup socket tables (red-black tree roots, or lists)
 * [TM_SOTB_TCP_CON] TCP sockets
 * [TM_SOTB_NON_CON] other sockets (UDP, raw, etc..)
 * [TM_SOTB_MCAST] multicast and broadcast socket lists
 */
#define TM_SOTB_NON_CON         0
#ifdef TM_SOTB_MCAST_ENABLE
#define TM_SOTB_MCAST           1
#else /* !TM_SOTB_MCAST_ENABLE */
#define TM_SOTB_MCAST           0   /* not used */
#endif /* !TM_SOTB_MCAST_ENABLE */
#define TM_SOTB_TCP_CON         (TM_SOTB_MCAST + TM_TCP_INSTANCE)
/* number of socket tables */
#define TM_SOTB_NUM             (TM_SOTB_TCP_CON + 1)
/* 
 * Port conflict resolution:
 * Index in tvSocketPortSearchMembers, and tvSocketPortSearchLastPort arrays:
 * [TM_SOTB_TCP_CON] TCP connected sockets
 * [TM_SOTB_NON_CON] other sockets (UDP, raw, etc..)
 * [TM_SOTB_TCP_NON_CON] TCP non-connected sockets
 */
#define TM_SOTB_TCP_NON_CON     (TM_SOTB_TCP_CON + TM_TCP_INSTANCE)
/* number of port conflict resolution slots */
#define TM_SOTB_NUM_SEARCH_PORT (TM_SOTB_TCP_NON_CON + 1)

#ifdef TM_USE_SOCKET_RB_TREE
#ifdef TM_USE_SOCKET_HASH_LIST
/* Socket tree root hash lists */
    ttSocketEntryPtrPtr   tvSocketTableRootPtrPtr[TM_SOTB_NUM];
#else /* !TM_USE_SOCKET_HASH_LIST */
/* Socket tree roots */
    ttSocketEntryPtr      tvSocketTableRootPtr[TM_SOTB_NUM];
#endif /* !TM_USE_SOCKET_HASH_LIST */
#else /* !TM_USE_SOCKET_RB_TREE */
#ifdef TM_USE_SOCKET_HASH_LIST
/* Socket table hash lists */
    ttListPtr             tvSocketTableListPtr[TM_SOTB_NUM];
/* Number of non empty buckets for each hash list */
    unsigned int          tvSocketTableListHashBucketFilled[TM_SOTB_NUM];
#else /* !TM_USE_SOCKET_HASH_LIST */
/* Socket tables */
    ttList                tvSocketTableList[TM_SOTB_NUM];
#endif /* TM_USE_SOCKET_HASH_LIST */
#endif /* !TM_USE_SOCKET_RB_TREE */
/*
 * Number of [TCP connected sockets, non TCP sockets, non connected TCP sockets]
 * in the socket tables (not counting reuseaddress list members)
 * Value used for port conflict determination.
 */
    tt32Bit               tvSocketPortSearchMembers[TM_SOTB_NUM_SEARCH_PORT];
#ifdef TM_USE_SOCKET_HASH_LIST
/* Size of each hash list */
    unsigned int          tvSocketTableListHashSize[TM_SOTB_NUM];
/* Highest depth of entries in a bucket for each hash list */
    unsigned int          tvSocketTableListHighDepth[TM_SOTB_NUM];
#endif /* TM_USE_SOCKET_HASH_LIST */
/*
 * Number of times through the loop to find a random port. Two for the TCP
 * socket lookup table (TCP connected, TCP non connected), one for the non
 * TCP lookup table.
 */
    unsigned int          tvSocketPortSearchHighLoopCount[TM_SOTB_NUM_SEARCH_PORT];
/*
 * Last random port used, 2 for the TCP socket lookup table (one for connected
 * TCP, and one for non connected TCP), and one for the non TCP one
 */
    tt16Bit               tvSocketPortSearchLastPort[TM_SOTB_NUM_SEARCH_PORT];
/*
 * Threshold of number of sockets in a socket lookup table before we switch
 * from a random local port selection to a sequential local port selection
 */
    unsigned int          tvSocketThresholdSequentialPort[TM_SOTB_NUM];
#ifdef TM_LOCK_NEEDED
/* One lock for all lookup socket tables */
    ttLockEntry           tvSocketRootLock;
/* To lock the number of open sockets */
    ttLockEntry           tvSocketOpenLock;
#endif /* TM_LOCK_NEEDED */
#ifdef TM_USE_TCP
/* Time wait TCP vector hash table */
    ttListPtr             tvTcpTmWtTableListPtr;
#ifdef TM_LOCK_NEEDED
/* Time wait TCP vector hash table lock */
    ttLockEntry           tvTcpTmWtTableLock;
#endif /* TM_LOCK_NEEDED */
/* Time wait TCP vector hash table size */
    unsigned int          tvTcpTmWtTableHashSize;
/* Time Wait TCP vector hash table non empty buckets */
    unsigned int          tvTcpTmWtTableHashBucketFilled;
/* Highest depth of entries in a bucket for Time Wait hash table */
    unsigned int          tvTcpTmWtTableHighDepth;
#endif /* TM_USE_TCP */
/* 
 * Default Socket Queue Sizes
 */
    tt32Bit               tvDefRecvQueueBytes; /* receive queue */
    tt32Bit               tvDefSendQueueBytes; /* send queue */
    tt16Bit               tvDefRecvQueueDgrams; /* receive queue - datagrams */
    tt16Bit               tvDefSendQueueDgrams; /* send queue - datagrams */
/* send OOB data queue */
    tt32Bit               tvDefSendOobQueueBytes;

/* 
 * IP global variables
 */
 
#ifdef TM_USE_IPV4
#ifdef TM_IP_REASSEMBLY
/* Ip collection (reassembly) */
/* default fragmentation timer resolution is 1 second */
    tt32Bit               tvFragResolution; /* in milliseconds */
/* Maximum size in bytes of an IP datagram waiting to be reassembled */
    tt32Bit               tvFragEntryMaxSize;
#endif /* TM_IP_REASSEMBLY */
#ifdef TM_NAT_Q_IP_FRAGMENT
/* Timer resolution for NAT fragmentation reassembly in milliseconds. */
    tt32Bit               tvNatIpFHResolution;
/* Maximum size in bytes of a NAT IP datagram waiting to be reassembled */
    tt32Bit               tvNatIpFHMaxSize;
#endif /* TM_NAT_Q_IP_FRAGMENT */
#endif /* TM_USE_IPV4 */

    tt4IpAddress          tvRouterId; /* Router Id */

#ifdef TM_USE_IPV4
    ttUserIpForwCBFuncPtr tvIpForwCBFuncPtr;
#endif /* TM_USE_IPV4 */
#ifdef TM_USE_IPV6
    tt6UserIpForwCBFuncPtr tv6IpForwCBFuncPtr;
#endif /* TM_USE_IPV6 */

#ifdef TM_USE_IPV4
/* Single routing cache entry for forwarding IP packets */
    ttRtCacheEntry        tvRtIpForwCache;
/*
 * single routing cache entry for sending IP packets (used by non socket
 * IP Send's)
 */
    ttRtCacheEntry        tvRtIpSendCache;
#ifdef TM_LOCK_NEEDED
/* Lock entry to access last sent packet routing cache */
    ttLockEntry           tvRtIpSendCacheLock;
/* Lock entry to access last forwarded packet routing cache */
    ttLockEntry           tvRtIpForwCacheLock;
#endif /* TM_LOCK_NEEDED */

#ifdef TM_IP_REASSEMBLY
/*
 * IP Reassembly global variables.
 */
/* queue of fragment heads */
    ttIpFHEntryPtr        tvIpFHPtr;
#ifdef TM_LOCK_NEEDED
/*
 * lock for the fragment heads list, and recycle queue of fragment heads
 * Use only one lock for the 2 lists, since the recycle list is always
 * accessed when the fragment head list is accessed.
 */
    ttLockEntry           tvIpFHLock;
#endif /* TM_LOCK_NEEDED */
/* Aging timer for fragments */
    ttTimerPtr            tvIpFHTimerPtr;
#endif /* TM_IP_REASSEMBLY */
#ifdef TM_NAT_Q_IP_FRAGMENT
/* Lists of fragment heads (one list for outgoing, and one for incoming) */
    ttList                tvNatIpFHList[2];
/* Aging timer for fragments */
    ttTimerPtr            tvNatIpFHTimerPtr;
#ifdef TM_LOCK_NEEDED
    ttLockEntry           tvNatIpFHLock;
#endif /* TM_LOCK_NEEDED */
#endif /* TM_NAT_Q_IP_FRAGMENT */
/* 
 * Pointer to IP decapsulation routine.  Initialized to null by 
 * tfGlobalVarsInit and set by tfUseIpTunneling
 */
    ttIpHandlerFuncPtr    tvIpDecapFuncPtr;

/*
 * BOOTP/DHCP global variables
 */
/* BOOTP/DHCP client socket lock */
#ifdef TM_LOCK_NEEDED
    ttLockEntry           tvBootSocketLockEntry;
#endif /* TM_LOCK_NEEDED */
#ifndef TM_USE_STRONG_ESL
/* BOOTP/DHCP client socket */
    int                   tvBootSocketDescriptor;
/* BOOTP/DHCP client socket open count */
    int                   tvBootSocketOpenCount;
/* BOOTP/DHCP relay agent socket */
    int                   tvBootRelayAgentDescriptor;
#endif /* !TM_USE_STRONG_ESL */
/* BOOTP/DHCP Relay variables */
    ttDeviceEntryPtr      tvBootServDevEntryPtr;
    tt4IpAddress          tvBootServIpAddress;

/*
 * Maximum user DHCP entries per device (on top of the TM_MAX_IPS_PER_IF
 * automatic configuration entries.)
 * (Default 0)
 */
    int                   tvMaxUserDhcpEntries;
#endif /* TM_USE_IPV4 */

/*
 * Router global variables
 */
#ifdef TM_USE_IPV4
/* RIP socket */
    int                   tvRipSocketDescriptor;
#endif /* TM_USE_IPV4 */
/*
 * Maximum number of routing entries, not including ARP cache entries
 */
    int                   tvRtMaxEntries;
#ifdef TM_ERROR_CHECKING
/* Number of routing entries out of the tree, but not in the recycle queue */
    int                    tvRteLimboCount;
#endif /* TM_ERROR_CHECKING */
/* Number of dynamic routing entries */
    int                    tvRtEntriesCount;
#if defined(TM_PMTU_DISC) || (defined(TM_6_PMTU_DISC))
/* Number of dynamic path MTU entries */
    int                    tvRtPmtuEntriesCount;
/* Maximum number of dynamic path MTU entries */
    int                    tvRtPmtuMaxEntries;
#endif /* TM_PMTU_DISC || TM_6_PMTU_DISC */
/* Number of ARP entries and cloned multicast entries */
    int                    tvRtArpEntriesCount;

#ifdef TM_USE_IPV4
/* Number of IPv4 ARP entries and cloned multicast entries. */
    int                    tv4RtArpEntriesCount;
#endif /* TM_USE_IPV4 */
    
/* Aging Router timer resolution */
    tt32Bit               tvRtTimerResolution;
/* Default RIP/Redirect entry timeout value */
    tt32Bit               tvRtTimeout;

#ifdef TM_PMTU_DISC
/*
 * Default Path MTU host routing entry timeout when the Path MTU estimate
 * is decreased in milliseconds. (10 minutes).
 */
    tt32Bit               tvRtDecreasedMtuTimeout;
/*
 * Default Path MTU host routing entry timeout when a larger path MTU estimate
 * is attempted in milliseconds. (2 minutes).
 */
    tt32Bit               tvRtLargerMtuTimeout;
#endif /* TM_PMTU_DISC */

/*
 * Empty Routing Table:
 * Structure containing three radix root nodes in the Patricia tree.
 * The middle one is the head of the tree. The left one is the root
 * leaf with all bits 0, and the right one is the root leaf with all
 * bits 1 (invalid route entry). (The default gateway in the Patricia
 * tree will be stored as a duplicate of the root left leaf.)
 */
    ttRtRadixHeadEntry     tvRtRadixTreeHead;
/* Point to the top radix node (middle one in tvRtRadixTreeHead) */
    ttRtRadixNodePtr       tvRtTreeHeadPtr;

#ifdef TM_LOCK_NEEDED
/* To lock the tree for read or write access */
    ttLockEntry            tvRtTreeLock;
#endif /* TM_LOCK_NEEDED */

/* Aging route timer */
    ttTimerPtr             tvRtTimerPtr;
    ttTimerPtr             tvRtArpTimerPtr;
/*
 * IGMP global variables
 */
#if (defined(TM_IGMP) && defined(TM_USE_IPV4))
/* Default IGMP V1 Router present timeout in milliseconds (400 seconds) */
    int                   tvIgmpRouterV1Timeout;
/* Default IGMP Unsolicited Report interval (10 secons) */
    int                   tvIgmpUnsolReportIntv;
#endif /* TM_IGMP and TM_USE_IPV4 */

#if (defined(TM_IGMP) || defined(TM_USE_IPV6))
/*
 * Number of Ethernet multicast entries that can be allocated per allocation.
 */
    int                   tvEnetMcastBlockEntries;
/* Maximum number of successive tvEnetMcastBlockEntries allocations
 * (0 = no limit) */
    int                   tvEnetMcastMaxAllocations;
#endif /* TM_IGMP || TM_USE_IPV6 */

#ifdef TM_6_USE_MLD
/* Default MLDv1 Router present timeout in milliseconds (400 seconds) */
    int                   tv6MldRouterV1Timeout;
/* Default MLD Unsolicited Report interval (10 seconds) */
    int                   tv6MldUnsolReportIntv;
#ifdef TM_6_USE_MLDV2
    tt16Bit               tv6MldSoMaxSrcFilter;
    tt16Bit               tv6MldIpMaxSrcFilter;
#endif /* TM_6_USE_MLDV2 */
#endif /* TM_6_USE_MLD */

#ifdef TM_USE_IPV4
/*
 * Arp collision detection global variables.
 */
    ttArpChkIn            tvArpChkInCBFunc;
#ifdef TM_LOCK_NEEDED
    ttLockEntry           tvArpChkListLock;
#endif /* TM_LOCK_NEEDED */
    ttArpChkEntryPtr      tvArpChkList;
    int                   tvArpChkActiveEntries;
#endif /* TM_USE_IPV4 */
/*
 * Raw socket global variables
 */
    ttSocketEntryPtr      tvRawSocketPtr;
    ttLockEntry           tvRawCacheLock;

#ifndef TM_DISABLE_UDP_CACHE
/*
 * UDP global variables (UDP cache)
 */
    ttSocketEntryPtr      tvUdpSocketPtr;
    ttLockEntry           tvUdpCacheLock;
#endif /* !TM_DISABLE_UDP_CACHE */
#ifdef TM_USE_UDP_LOOKUP_PERF
/*
 * Global counters to keep track of how many UDP and raw sockets have the
 * associated characteristics (connected, bound to a specific IP address,
 * bound to any IP address, bound to the wildcard port, bound to a device).
 * When performing a UDP or raw socket lookup, if any of the following
 * counters are zero, we can skip the search for a socket with the
 * corresponding characteristic. This can reduce search time.
 * Note: tvSocketRootLock must be locked while accessing these values.
 */
    unsigned int          tvUdpTotal;
    unsigned int          tvUdpConnect;
    unsigned int          tvUdpBindWild;
    unsigned int          tvUdpBindAnyAddr;
#ifdef TM_USE_IPDUAL
    unsigned int          tvUdpBind4AnyAddr;
#endif /* TM_USE_IPDUAL */
#ifdef TM_USE_STRONG_ESL
    unsigned int          tvUdpBindDevice;
#endif /* TM_USE_STRONG_ESL */
#endif /* TM_USE_UDP_LOOKUP_PERF */

#ifdef TM_USE_TCP
/*
 * TCP global context variables
 */
/* 
 * tvTcpIss
 * Initial sequence number (incremented by 1 every 4us) and used by
 * the TCP code to initialize the initial sequence number (corresponding
 * to the SYN) of a new connection.
 */
    tt32Bit               tvTcpIss;
/* 
 * Tcp time stamp to keep track of time changes for update of tvTcpIss in
 * tfTcpGetIss(). 
 */
    tt32Bit               tvTcpTimerTime;
#ifdef TM_USE_TCP_128BIT_RANDOM_ISS
/* TCP secret random number for outgoing connections */
    tt32Bit               tvTcpSecret[4];
#ifndef TM_OPTIMIZE_SIZE
/* TCP secret random number MD5 context */
    ttMd5Ctx              tvTcpSecretMdContext;
#endif /* !TM_OPTIMIZE_SIZE */
#else /* !TM_USE_TCP_128BIT_RANDOM_ISS */
    tt32Bit               tvTcpSecretIss;
#endif /* !TM_USE_TCP_128BIT_RANDOM_ISS */
/* TCP delay ACK timeout in milli-seconds. Disabled is set to zero. */
    tt32Bit               tvTcpDelayAckTime;
/* Tcp connection timeout in milli-seconds */
    tt32Bit               tvTcpConnTime;
/* Default Tcp retransmission time in milli-seconds */
    tt32Bit               tvTcpDefRtoTime;
/* min Tcp retransmission time in milli-seconds */
    tt32Bit               tvTcpMinRtoTime;
/* max Tcp retransmission time in milli-seconds */
    tt32Bit               tvTcpMaxRtoTime;
/* min Tcp zero window probe time in milli-seconds */
    tt32Bit               tvTcpMinProbeWndTime;
/* max Tcp zero window probe time in milli-seconds */
    tt32Bit               tvTcpMaxProbeWndTime;
/* Max retransmission count */
    int                   tvTcpMaxReXmitCnt;
/*
 * Amount of time to stay in FIN WAIT 2 when socket has been closed
 * (Default 10 minutes)
 */
    int                   tvTcpFinWt2Time; /* in seconds */
/* 2 * Maximum segment life time (2 * 30 seconds) (TIME WAIT time) */
    int                   tvTcp2MSLTime; /* in seconds */
#ifdef TM_USE_TCP_KEEPALIVE
/* Keep alive time (2 hours) in seconds */
    int                   tvTcpKeepAliveTime; /* in seconds */
/* Keep alive Probe Interval/Idle update time (75s) in seconds */
    int                   tvTcpIdleIntvTime; /* in seconds */
/* Keep alive Max Probe count (8) */
    int                   tvTcpKeepAliveProbeCnt;
#endif /* TM_USE_TCP_KEEPALIVE */

/* One cache entry for TCP incoming packets */
    ttTcpVectPtr          tvTcpVectPtr;
#ifdef TM_LOCK_NEEDED
/* Lock for the one cache entry for TCP incoming packets */
    ttLockEntry           tvTcpCacheLock;
#endif /* TM_LOCK_NEEDED */
#endif /* TM_USE_TCP */
/*
 * Device Entries
 */
#ifdef TM_SINGLE_INTERFACE_HOME
    ttDeviceEntryPtr      tvDeviceList;       /* The Active Device List */
    ttDeviceEntryPtr      tvDeviceToFreeList; /* The To Free Device List */
#else /* !TM_SINGLE_INTERFACE_HOME */
#define tvDeviceList        tvDeviceListArray[0]
#define tvDeviceToFreeList  tvDeviceToFreeListArray[0]
#define TM_DEV_LISTS        1
#ifdef TM_USE_IPDUAL
#define tv6Ipv4TunnelList           tvDeviceListArray[1]
#define tv6Ipv4TunnelToFreeList     tvDeviceToFreeListArray[1]
#undef TM_DEV_LISTS
#define TM_DEV_LISTS        2
#endif /* TM_USE_IPDUAL */
/* The Active Device Lists */
    ttList                tvDeviceListArray[TM_DEV_LISTS];
/* The To Free Device Lists */
    ttList                tvDeviceToFreeListArray[TM_DEV_LISTS];
#endif /* !TM_SINGLE_INTERFACE_HOME */
#ifdef TM_LOCK_NEEDED
#ifdef TM_USE_IPDUAL
/* IPv6 in IPv4 tunnel Device List Lock */
#define tv6Ipv4TunnelListLock   tvDeviceListLock
#endif /* TM_USE_IPDUAL */
/* Device List/Device to Free list Lock */
    ttLockEntry           tvDeviceListLock;
#endif /* TM_LOCK_NEEDED */
    ttDeviceEntryPtr      tvLoopbackDevPtr; /* loop back device */

    ttLinkLayerEntryPtr   tvLinkLayerListPtr;
#ifdef TM_LOCK_NEEDED
    ttLockEntry           tvLinkLayerListLock;
#endif /* TM_LOCK_NEEDED */
    ttLinkLayerEntryPtr   tvNullLinkLayerHandle; /* Null link layer */

/* Size of trailer to add to tail of outgoing packets.  Initialized to zero */
    ttPktLen              tvPakPktSendTrailerSize;



/* maximum number of timers we execute in a single call to tfTimerExecute,
   a value of 0 means there is no limit */
    int                   tvTimerMaxExecute;

#endif
#ifdef TM_USE_HTTPD
/* Pointer to HTTPd server handles */
    ttVoidPtr             tvHttpdHandlesPtr;
#ifdef TM_USE_HTTPD_SSI
#ifdef TM_HTTPD_SSI_DEBUG
    FILE TM_FAR         * tvHttpdLogFilePtr;
#endif /* TM_HTTPD_SSI_DEBUG */
#endif /* TM_USE_HTTPD_SSI */
    tt16Bit               tvHttpdUpperMaxNumberServers;
    tt16Bit               tvHttpdMaxNumberServers;
    tt16Bit               tvHttpdNumberServers;
/*
 * Maximum buffer size to hold CGI variable names and values, or contiguous
 * received body buffer
 */
    tt16Bit               tvHttpdBodyMaxRecvBufSize;
#ifdef TM_USE_HTTPD_SSI
/*  The maximum SSI tag length in the SSI enabled pages. */
    tt16Bit               tvHttpdSsiMaxTagLen;
#endif /* TM_USE_HTTPD_SSI */

#ifdef TM_USE_HTTPD_CGI
/* minium number of CGI variables per allocation. */
    tt16Bit               tvHttpdCgiMinArgCnt;
/* maximum number of CGI variables. */
    tt16Bit               tvHttpdCgiMaxArgCnt;
#endif /* TM_USE_HTTPD_CGI */
#endif /* TM_USE_HTTPD */

#if 1
#ifdef TM_ERROR_CHECKING
/* Temporary buffer used by tm_assert() to build the error message */
    char                                tvAssertTempBuf[256];
#endif  /* TM_ERROR_CHECKING */

    /* Maximum number of sockets */
        tt32Bit               tvMaxNumberSockets;
    /* Number of open sockets */
        tt32Bit               tvNumberOpenSockets;
#endif
#if 0
#ifdef TM_USE_HTTPC
/* maximum line length */
    tt16Bit               tvHttpcMaxLineLength;
#endif /* TM_USE_HTTPC */

#ifdef TM_USE_IPV4
/* max simultaneous NAT triggers */
    tt16Bit               tvNatMaxEntries;
#endif /* TM_USE_IPV4 */

#if (defined(TM_SNMP_MIB) || defined(TM_PPP_LQM))
/*
 * SNMP AGENT MIB variable shared with PPP LQM.
 */
#ifdef TM_USE_IPV4
    ttIfStatMib           tvDevIpv4Data;
#endif /* TM_USE_IPV4 */
#endif /* TM_SNMP_MIB || TM_PPP_LQM */
#ifdef TM_SNMP_MIB
/*
 * SNMP AGENT MIB variables
 */
#ifdef TM_USE_IPV4
    ttIpMib               tvIpData;
    ttIcmpMib             tvIcmpData;
#endif /* TM_USE_IPV4 */
#ifdef TM_USE_IPV6
    tt6Icmpv6Mib          tvIcmpv6Data;
    ttIfStatMib           tvDevIpv6Data;
#endif /* TM_USE_IPV6 */
    ttUdpMib              tvUdpData;
#ifdef TM_USE_TCP
    ttTcpMib              tvTcpData;
#endif /* TM_USE_TCP */
#endif /* TM_SNMP_MIB */


#ifdef TM_LOCK_NEEDED
/*
 * tfVSScanF() lock
 */
/* Proxy Arp lock */
    ttLockEntry           tvScanfLockEntry;
#endif /* TM_LOCK_NEEDED */


/*
 * DNS resolver variables
 */
/* List of DNS servers in order of priority (index 0 is primary, etc) */
    ttDnsServerEntry      tvDnsServerList[TM_DNS_MAX_SERVERS];

/* Points to the start of the DNS cache */
    ttDnsCacheEntryPtr    tvDnsCachePtr;

#ifdef TM_USE_STRONG_ESL
    ttDeviceEntryPtr      tvDnsDevPtr;
#endif /* TM_USE_STRONG_ESL */

    ttLockEntry           tvDnsLockEntry;

/* Host table support */
    ttList                      tvDnsHostTable;
    ttDnsHostTableSearchFuncPtr tvDnsHostTableSearchFuncPtr;
#ifdef TM_LOCK_NEEDED
    ttLockEntry                 tvDnsHostTableLockEntry;
#endif /* TM_LOCK_NEEDED */
#ifdef TM_USE_RFC3484
    ttList                tvAddrPolicyTable;
#ifdef TM_LOCK_NEEDED
    ttLockEntry           tvAddrPolicyTableLockEntry;
#endif /* TM_LOCK_NEEDED */
#endif /* TM_USE_RFC3484 */

/* TTL to use for DNS cache entries */
    tt32Bit               tvDnsCacheTtl;
/*
 * The number of DNS sockets allowed to be allocated.
 * This dictates the number of simultaneous requests that are allowed.
 */
    tt32Bit               tvDnsMaxNumberSockets;
/* The number of DNS sockets that have been allocated */
    tt32Bit               tvDnsNumSocksAllocated;
/* The array index of the current Transaction ID */
    tt32Bit               tvDnsCurrentTransId;
/* Number of entries current in the DNS cache */
    int                   tvDnsCacheEntries;
/* indicates blocking mode of resolver: TM_BLOCKING_ON or TM_BLOCKING_OFF */
    int                   tvDnsBlockingMode;
/* Maximum number of entries in the DNS cache.  Settable by user. */
    int                   tvDnsCacheSize;
/* Maximum number of query retransmissions to attempt */
    int                   tvDnsRetries;
/* Time (in seconds) to wait for a response to come back from the DNS server */
    int                   tvDnsTimeout;
/*
 * Device entries
 */
/*
 * Number of added interfaces. Adding interfaces increments this value.
 * Initialized to zero. Does not include Loop back interface.
 */
    unsigned int          tvAddedInterfaces;
#ifdef TM_USE_IPDUAL
/*
 * Number of user added tunnel interfaces. Adding tunnel interfaces increments
 * this value. Initialized to zero.
 */
    unsigned int          tvAddedTunnelInterfaces;
#endif /* TM_USE_IPDUAL */

#ifdef TM_USE_IPV6

#endif /* TM_USE_IPV6 */

/*
 * Variables used for random seed generator.
 */
    tt16Bit               tvVector1;
    tt16Bit               tvVector2;
/*
 * Threshold in bytes below which we try and append to previous send buffer
 * for TCP
 */
    tt16Bit               tvDefSendAppendThreshold;
/*
 * Fraction use of the buffer below which we try and append to previous
 * recv buffer for TCP
 */
    tt16Bit               tvDefRecvAppendFraction;
/*
 * Fraction use of the buffer below which we try and copy to a smaller
 * recv buffer for UDP
 */
    tt16Bit               tvDefRecvCopyFraction;

/* Default Linger time when closing a TCP socket */
    tt16Bit               tvDefLingerTime;

/* Default TCP options: window scale, selective ACK, time stamp options, plus
 * default congestion avoidance
 */
    tt16Bit               tvTcpDefOptions;

/*
 * TCP global variables
 */
    tt16Bit               tvTcpDefMss; /* Default TCP MSS */

#ifdef TM_USE_IPV4
/* 
 * ICMP global variables
 */
    tt16Bit               tvIcmpSeqno; /* for request/reply */
/*
 * SLIP global variables
 */
    tt16Bit               tvSlipMtu;
/*
 * BOOTP/DHCP variables.
 */
    tt16Bit               tvBootServMhomeIndex;
#endif /* TM_USE_IPV4 */

#ifdef TM_USE_DHCP_FQDN
/*
 * FQDN structure
 */
    ttFqdn                              tvFqdnStruct;
#ifdef TM_LOCK_NEEDED
/* Lock for select pend entry recycle list */
    ttLockEntry                         tvFqdnStructLock;
#endif /* TM_LOCK_NEEDED */

#endif /* TM_USE_DHCP_FQDN */

/*
 * DNS resolver variables
 */
/* Last request ID to be sent. */
    tt16Bit               tvDnsTransId[TM_DNS_TRANS_ID_BACKLOG_SIZE];

/* Default socket options */
    tt16Bit               tvSocDefOptions;

#ifdef TM_USE_IPV6
#if (defined(TM_6_USE_PREFIX_DISCOVERY) || defined(TM_6_TAHI_MN_TEST))
    tt16Bit               tv6RtPrefixMhomeIndex;
/* IPv6 prefix aging timer resolution */
    tt16Bit               tv6PrefixTimerResSec;
#endif /* TM_6_USE_PREFIX_DISCOVERY or TM_6_TAHI_MN_TEST */
#endif /* TM_USE_IPV6 */
#ifdef TM_USE_TCP
/* Indicates whether tvTcpSecret has been initialized */
    tt8Bit                tvTcpSecretInit;
#endif /* TM_USE_TCP */
#ifdef TM_USE_IPV4
#ifdef TM_IP_FRAGMENT
/* Fragment bigger than MTU packets */
    tt8Bit                tvIpFragment;  /* default 1, allowed */
#endif /* TM_IP_FRAGMENT */
#ifdef TM_IP_REASSEMBLY
/* Ip collection (reassembly) */
/* Maximum allowed number of IP datagrams waiting to be reassembled. */
    tt8Bit                tvFragMaxQSize;
/* Actual number of IP datagrams waiting to be reassembled */
    tt8Bit                tvFragQSize;
/* Number of IP datagrams that were too big to reassemble, but we're still
 * tracking in case more fragments come in */
    tt8Bit                tvFragFailedQSize;
/* Maximum number of "too big" datagrams to track */
    tt8Bit                tvFragFailedMaxQSize;
#endif /* TM_IP_REASSEMBLY */
#if defined(TM_IP_REASSEMBLY) || defined(TM_SNMP_VERSION)
/* IP Reassembly timeout in seconds. Default is 60 */
    tt8Bit                tvFragTtl;
#endif /* TM_IP_REASSEMBLY || TM_SNMP_VERSION */ 
#ifdef TM_NAT_Q_IP_FRAGMENT
/* Default max number of IP datagrams in NAT reassembly queue */
    tt8Bit                tvNatIpFHMaxListCount;
/* Default max number of IP datagrams in NAT reassembly queue with no trigger */
    tt8Bit                tvNatNoTriggerIpFHMaxListCount;
/* Current number of IP datagrams in NAT reassembly queue with no trigger */
    tt8Bit                tvNatNoTriggerIpFHListCount;
/* Default IP datagram time to live in NAT reassembly queue */
    tt8Bit                tvNatIPFHTtl;
#endif /* TM_NAT_Q_IP_FRAGMENT */
#endif /* TM_USE_IPV4 */

/* Flag for whether DNS is initialized or not */
    tt8Bit                tvDnsInitialized;

#ifdef TM_USE_IPV4
/*
 * ARP cache
 */
/* Whether to store gratuitious ARP cache mappings */
    tt8Bit                tvArpSmart;
/* 
 * IP global variables
 */
/* Host(do not forward) or Router (forward) */
    tt8Bit                tvIpForward; /* 0 means host, 1 router */
/* Forward directed broadcast IP packets (default is 1) */
    tt8Bit                tvIpDbcastForward;
#ifdef TM_IP_MCAST_FORWARD
/* 1 means multicast router */
    tt8Bit                tvIpMcastForward;
/* NAT multicast forwarding, public/private interfaces, addresses, mhomes */
#ifdef TM_LOCK_NEEDED
    ttLockEntry           tvNatGlobalLock;
#endif  /* TM_LOCK_NEEDED */
    ttDeviceEntryPtr      tvNatMcFwdPublicDevPtr;
    ttDeviceEntryPtr      tvNatMcFwdPrivateDevPtr;
    tt4IpAddress          tvNatMcFwdPublicIpAddr;
    tt16Bit               tvNatMcFwdPublicMhome;
#endif /* TM_IP_MCAST_FORWARD */
#ifdef TM_USE_LBCAST_CONFIG
    tt8Bit                tvIpLbcastEnable; /* 1 (def) enabled, 0 disabled */
#endif /* TM_USE_LBCAST_CONFIG */
/* default IP time to live */
    tt8Bit                tvIpDefTtl;
/* Default IP TOS */
    tt8Bit                tvIpDefTos;

/*
 * RIP variables
 */
/* Rip enabled/disabled */
    tt8Bit                tvRipOn;
/*
 * tvRipSendMode has 4 possible values that determine the RIP packets being
 * sent: TM_RIP_NONE (no RIP packets are being sent),
 * TM_RIP_1 (only RIP 1 packets are being sent), TM_RIP_1_COMPAT
 * (default, sending only RIP 2 packets, broadcasting them ),
 * TM_RIP_2 (sending only RIP 2 packets, multicasting them)
 */
    tt8Bit                tvRipSendMode;
/*
 * tvRipRecvMode has 4 possible values that determine the RIP packets being
 * received: TM_RIP_NONE (no RIP packets are being received),
 * TM_RIP_1 (only RIP 1 packets are being received),
 * TM_RIP_2 (only RIP 2 packets are being received),
 * TM_RIP_1|TM_RIP_2 (both RIP 1 and Rip 2 packets are being received)
 */
    tt8Bit                tvRipRecvMode;
/* 
 * ICMP global variables
 */
    tt8Bit                tvIcmpAddrMaskAgent;
    tt8Bit                tvIcmpRouteReply;
#ifdef TM_USE_ECHO_CONFIG
    tt8Bit                tvIcmpEchoEnable;
#endif /* TM_USE_ECHO_CONFIG */

#ifndef TM_SINGLE_INTERFACE_HOME
    tt8Bit                tvIcmpErrDstAsSrc;
#endif /* TM_SINGLE_INTERFACE_HOME */
#endif /* TM_USE_IPV4 */
/*
 * UDP global variable
 */
/* Enable/disable Udp cheksum. Default is 1 (enabled). */
    tt8Bit                tvUdpChecksumOn;
/* Enable/disable Incoming check on Udp cheksum. Default is 1 (enabled). */
    tt8Bit                tvUdpIncomingChecksumOn;
/* Enable/disable Incoming check on TCP cheksum. Default is 1 (enabled). */
    tt8Bit                tvTcpIncomingChecksumOn;

#ifdef TM_USE_IPV6

#ifdef TM_6_IP_REASSEMBLY
/* Maximum allowed number of IP datagrams waiting to be reassembled. */
    tt8Bit                tv6FragMaxQSize;
    
/* Actual number of IP datagrams waiting to be reassembled */
    tt8Bit                tv6FragQSize;

/* Maximum number of "too big" datagrams to track */
    tt8Bit                tv6FragFailedMaxQSize;

/* Number of IP datagrams that were too big to reassemble, but we're still
 * tracking in case more fragments come in */
    tt8Bit                tv6FragFailedQSize;
#endif /* TM_6_IP_REASSEMBLY */

#if defined(TM_6_IP_REASSEMBLY) || defined(TM_SNMP_VERSION)
/* IP Reassembly timeout in seconds. Default is 60 */
    tt8Bit                tv6FragTtl;
#endif /* TM_6_IP_REASSEMBLY || TM_SNMP_VERSION */ 
    
/* Enables/disables IPv6 forwarding at the IPv6 level. Refer to 
   TM_6_OPTION_IP_FORWARDING. */
    tt8Bit                tv6IpForward;
/*
 * The default IPv6 hop limit.
 * Initialized to the compile-time default TM_6_IP_DEF_HOPS.
 * Can be overwritten via SNMP.
 * Will be superceeded by a Router Advertisement value.
 * Will also be superseded via setsockopt() with IPV6_UNICAST_HOPS.
 */
    tt8Bit                tv6DefaultHopLimit;
/* Refer to TM_6_OPTION_IP_DEPRECATE_ADDR. ([RFC2462].R5.5.4:70) */
    tt8Bit                tv6IpDeprecateAddr;

#ifdef TM_6_IP_FRAGMENT
/* Refer to TM_6_OPTION_IP_FRAGMENT. ([RFC2460].R5:70) */
    tt8Bit                tv6IpFragment;
#endif /* TM_6_IP_FRAGMENT */



#endif /* TM_USE_IPV6 */


/* Context Globals */
#ifdef TM_USE_TCP_REXMIT_TEST
    int             tvFtpSockDesc;
    ttUser8Bit      tvTcpDropPackets;
    ttUser8Bit      tvTcpDataOnly;
    ttUser8Bit      tvSocketDisableRecv;
#endif /* TM_USE_TCP_REXMIT_TEST */
#ifdef TM_ERROR_CHECKING
    tt32Bit          tvGetRawCount;
    tt32Bit          tvFreeRawCount;
#ifdef TM_USE_ANSI_LINE_FILE
#if (defined(TM_KERNEL_VISUAL_X86) || defined(TM_KERNEL_WIN32_X86) \
     || defined(TM_MEMORY_LOGGING))
#if (defined(TM_KERNEL_VISUAL_X86) || defined(TM_KERNEL_WIN32_X86))
    FILE *           tvMemoryLeakDetector;
#endif /* defined(TM_KERNEL_VISUAL_X86) || defined(TM_KERNEL_WIN32_X86) */
#ifdef TM_LOCK_NEEDED
    ttLockEntry      tvMemoryLeakLock;
#endif /* TM_LOCK_NEEDED */
#endif /* Win32 or TM_MEMORY_LOGGING */
#endif /*  TM_USE_ANSI_LINE_FILE */
#endif /* TM_ERROR_CHECKING */
#ifdef TM_USE_FTPD_SSL
#ifdef TM_AUTO_TEST
    ttUserFtpHandle  tvClientFtpHandle;
#endif /* TM_AUTO_TEST */
#endif /* TM_USE_FTPD_SSL */
#ifdef TM_USE_IPV4
/*
 * IP header Id incremented every time an IP datagram is sent.
 */
    tt16Bit          tvIpId;
#ifndef TM_USE_PREDICTABLE_IPID
#ifdef TM_USE_TCP
/*
 * IP header Id incremented every time a TCP segment is sent.
 */
    tt16Bit          tvTcpIpId;
#endif /* TM_USE_TCP */
#endif /* !TM_USE_PREDICTABLE_IPID */
#endif /* TM_USE_IPV4 */

#ifdef TM_6_USE_TEMPADDR
/*
 * Global data for managing autoconfigured temporary global IPv6 addresses
 * ([RFC4941], Privacy Extensions for Stateless Address Autoconfig in IPv6).
 */
/* Interval (seconds) that a temporary address is valid */
    tt32Bit         tv6TempValidLifetime;
/* Interval (seconds) that a temporary address is preferred */
    tt32Bit         tv6TempPreferLifetime;
/* Maximum desynchronizing factor (seconds) */
    tt32Bit         tv6TempMaxDesyncFactor;
/* Maximum attempts to generate a valid address */
    unsigned int    tv6TempRegenMaxRetry;
/* Default device flags for autoconfigured temporary addresses */
    tt8Bit          tv6TempDevFlags;
#endif /* TM_6_USE_TEMPADDR */
#endif
} ttContext;

typedef ttContext TM_FAR * ttContextPtr;

/*
 * Global variables for all contexts.
 */
/* Current context */
#ifdef TM_MULTIPLE_CONTEXT
TM_EXTERN ttContextPtr          TM_GLOBAL_QLF tvCurrentContext;
#else /* !TM_MULTIPLE_CONTEXT */
TM_EXTERN ttContext             TM_GLOBAL_QLF tvCurrentContextStruct;
#endif /* !TM_MULTIPLE_CONTEXT */

#ifdef TM_USE_FTPD_SSL
#ifdef TM_AUTO_TEST
TM_EXTERN ttUserContext         TM_GLOBAL_QLF tvContextHandleServer;
TM_EXTERN ttUserContext         TM_GLOBAL_QLF tvContextHandleClient;
#endif /* TM_AUTO_TEST */
#endif /* TM_USE_FTPD_SSL */
/*
 * Structure containing global variables, other than per context, and other
 * than OS interface variables
 */
TM_EXTERN ttGlobal              TM_GLOBAL_QLF tvGlobals;

/*
 * (non context) Global variables set or not. Cannot be in ttGlobal, 
 * because it is checked prior to tvGlobals initialization.
 */
TM_EXTERN tt32Bit               TM_GLOBAL_QLF tvGlobalsSet;

/*
 * Timer global variables
 */
#ifndef tvTime
/* 
 * tvTime not declared in ttGlobal structure to save value across reboots 
 * and because can be changed from Timer ISR.
 * Note: User could define tvTime/tvTimeRollOver in their trsystem.h file
 * so that they can keep track of the time themselves, and avoid having
 * to call tfTimerUpdate() periodically.
 */
TM_EXTERN tt32Bit               TM_GLOBAL_QLF tvTime;
#endif /* tvTime */
#if defined(TM_USE_TIM_ROLLOVER) || defined(TM_SNMP_VERSION)
#ifndef tvTimeRollOver
TM_EXTERN tt32Bit               TM_GLOBAL_QLF tvTimeRollOver;
#endif /* tvTimeRollOver */
#endif /* TM_USE_TIM_ROLLOVER || TM_SNMP_VERSION */
/* tvTimerTickLength used during timer ISR */
TM_EXTERN unsigned              TM_GLOBAL_QLF tvTimerTickLength;

/*
 * OS interface global variables.
 */
#ifdef TM_USE_KERNEL_CRITICAL_STATUS
/* Not in ttGlobal because just used to store/restore critical status */
TM_EXTERN ttUserKernelCriticalStatus tvKernelCriticalStatus;
#endif /* TM_USE_KERNEL_CRITICAL_STATUS */

/*
 * Pend/Post global variable. Not in ttGlobal, because can be initialized
 * in tfKernelInitialize().
 */
TM_EXTERN tt8Bit                TM_GLOBAL_QLF tvPendPostEnabled;

#ifdef TM_LOCK_NEEDED
/*
 * lock global variable.
 */
TM_EXTERN tt8Bit                TM_GLOBAL_QLF tvLockEnabled;
#endif /* TM_LOCK_NEEDED */


/* Default file system working direectory has been set */
TM_EXTERN tt8Bit                TM_GLOBAL_QLF tvFSInitWorkingDirSet;
/* Initial File system drive */
TM_EXTERN int                   TM_GLOBAL_QLF tvFSInitDrive;


/*
 * Device driver ISR parameters global variable. Not in ttGlobal because
 * accessed from device driver ISR.
 */
TM_EXTERN ttDeviceIsrPara       TM_GLOBAL_QLF tvDeviceIsrPara[
                                                    TM_MAX_NUMBER_DEVICES];

/*
 * Win32 Thread Local Storage index, needed for each thread to store
 * and retriece it's context pointer. Not in ttGlobal, because win32 variable.
 */
#if ( defined(TM_KERNEL_WIN32_X86) && defined(TM_MULTIPLE_CONTEXT) )
TM_EXTERN tt32Bit               TM_GLOBAL_QLF tvTlsIndex;
#endif /* defined(TM_KERNEL_WIN32_X86) && defined(TM_MULTIPLE_CONTEXT) */

/*
 * Global constants
 */

#ifndef TM_GLOBAL
/*
 * Lookup table used to convert prefix length to netmask. Not declared
 * in ttGlobal, because pointer to constant table.
 * Initialized in trinit.c which defines TM_GLOBAL
 */
TM_EXTERN const tt4IpAddress  TM_CONST_QLF tvRt32ContiguousBitsPtr[]; 
#endif /* TM_GLOBAL */


#if (defined(TM_USE_HTTPD) || defined(TM_USE_HTTPC) || defined(TM_USE_HTTPU))
/* 
 * HTTP pointers to shared constant tables, initialized in trhttp.c.
 * Not declared in ttGlobal, because pointers to constant tables
 */
#ifndef TM_HTTP_GLOBAL
/*
 * Declared as extern (and not TM_EXTERN) because initialized in trhttp.c, and
 * not in trinit.c
 */
extern ttConstCharPtr const TM_CONST_QLF tvHttpVersionStr[];
extern ttConstCharPtr const TM_CONST_QLF tvHttpMethodStr[];
extern ttConstCharPtr const TM_CONST_QLF tvHttpHeaderNames[];
#endif /* !TM_HTTP_GLOBAL */
#endif /* !(TM_USE_HTTPD) || TM_USE_HTTPC || TM_USE_HTTPU) */
#if defined(TM_USE_PPP) || defined(TM_USE_PPPOE)
/*
 * PPP constant global variable. Kludge to return a non null pointer to the
 * user.
 * Will always have zero in it. Not declared in ttGlobal, because it is 
 * a constant. Pointer to this constant char is returned by the user
 * MSCHAP function to specify a null password.
 */
#ifdef TM_GLOBAL
const char TM_GLOBAL_QLF tvChapEmptyChar = '\0';
#endif /* TM_GLOBAL */
#endif /* TM_USE_PPP || TM_USE_PPPOE */

/*
 * Constant Ethernet broadcast address. Not declared in ttGlobal, because
 * constant.
 */
#ifdef TM_GLOBAL
/*
 * Ethernet global constant variables when TM_GLOBAL is defined.
 */
/* Constant initialization */
#ifdef TM_NO_NESTED_BRACES
const ttEnetAddressUnion  TM_CONST_QLF tvEtherBroadcast =
    {0xFFFF, 0xFFFF, 0xFFFF};
#else /* !TM_NO_NESTED_BRACES */
const ttEnetAddressUnion  TM_CONST_QLF tvEtherBroadcast =
    {{ 0xFFFF, 0xFFFF, 0xFFFF}};
#endif /* !TM_NO_NESTED_BRACES */
#else /* !TM_GLOBAL */
TM_EXTERN const ttEnetAddressUnion  TM_CONST_QLF tvEtherBroadcast;
#endif /* !TM_GLOBAL */

#ifdef TM_USE_IPV6

#ifdef TM_GLOBAL
/* 
 * These variables are not part of ttGlobal because they are just constant
 * initialized at compile time.
 */
/* Initialized only when included by trinit.c which defines TM_GLOBAL */
TM_EXTERN const struct in6_addr TM_CONST_QLF in6addr_any = 
        IN6ADDR_ANY_INIT;
TM_EXTERN const struct in6_addr TM_CONST_QLF in6addr_loopback = 
        IN6ADDR_LOOPBACK_INIT;
TM_EXTERN const struct in6_addr TM_CONST_QLF in6addr_nodelocal_allnodes =
        IN6ADDR_NODELOCAL_ALLNODES_INIT;
TM_EXTERN const struct in6_addr TM_CONST_QLF in6addr_linklocal_allnodes =
        IN6ADDR_LINKLOCAL_ALLNODES_INIT;
TM_EXTERN const struct in6_addr TM_CONST_QLF in6addr_linklocal_allrouters =
        IN6ADDR_LINKLOCAL_ALLROUTERS_INIT;
TM_EXTERN const struct in6_addr TM_CONST_QLF tvIn6AddrHostMask = 
        TM_IN6ADDR_HOST_MASK;
TM_EXTERN const struct in6_addr TM_CONST_QLF tvIn6AddrIpv4Any = 
    TM_IN6ADDR_IPV4_ANY_INIT;
#ifdef TM_6_USE_MLDV2
TM_EXTERN const struct in6_addr TM_CONST_QLF tvIn6AddrAllMldV2Routers =
        TM_IN6ADDR_ALL_MLDV2_ROUTERS;
#endif /* TM_6_USE_MLDV2 */
#else /* !TM_GLOBAL */
/* Declared here because, not declared in trsocket.h */
TM_EXTERN const struct in6_addr TM_CONST_QLF tvIn6AddrHostMask;
TM_EXTERN const struct in6_addr TM_CONST_QLF tvIn6AddrIpv4Any;
#ifdef TM_6_USE_MLDV2
TM_EXTERN const struct in6_addr TM_CONST_QLF tvIn6AddrAllMldV2Routers;
#endif /* TM_6_USE_MLDV2 */
#endif /* !TM_GLOBAL */
#endif /* TM_USE_IPV6 */



#ifndef TM_IKE_GLOBAL
/*
 * Declared as extern (and not TM_EXTERN) because initialized in trike.c, and
 * not in trinit.c
 */

/*
 * Treck IKE Vendor ID Hash. 
 * Not declared in ttGlobal, because pointer to constant table.
 */
extern const tt8Bit TM_GLOBAL_QLF tvTreckVendorIdPtr[];
#endif /* !TM_IKE_GLOBAL */

#ifndef TM_IPSEC_GLOBAL
#ifdef TM_USE_IPSEC_64BIT_KB_LIFETIMES
/* IPsec 64-bit KByte lifetime max value */
extern const ttUser64Bit TM_GLOBAL_QLF tvIpsecMaxLifetime;
#endif /* TM_USE_IPSEC_64BIT_KB_LIFETIMES */
#endif /* !TM_IPSEC_GLOBAL */


#ifdef __cplusplus
}
#endif

#endif /* _TRGLOBAL_H_ */

/* Processed by Treck Shipping Tool v2.62 
 * 2012/11/21 10:16:05      For: gainspan_2411
 * File Name: trglobal.h    File Revision: 6.0.2.25 
 * Project Name: tcpip.pj   Project Release: 6.0.1.29
 * Input checksum: 43090    Output checksum: 29254
 */
