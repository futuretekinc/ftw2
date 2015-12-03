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
 * Description:     System Description Macro's
 * This file is intended for the user to modify for their hardware/os platform
 * Filename:        trsystem.h
 * Author:          Odile & Paul
 * Date Created:    9/22/97
 * $Source: /home/cvsroot/gs2000_app_sw/afw/system/gsn/src/modules/http/include/trsystem.h,v $
 *
 * Modification History
 * $Revision: 1.2 $
 * $Date: 2013/03/06 09:04:58 $
 * $Author: aravind $
 * $ProjectName: /home/mks/proj/tcpip.pj $
 * $ProjectRevision: 6.0.1.29 $
 */

#ifndef _TRSYSTEM_H_

#define _TRSYSTEM_H_

#ifdef __cplusplus
extern "C" {
#endif

/* comment out the following line if you do not want to use IPv4 protocols */
//#define TM_USE_IPV4

/* uncomment the following line if you want to use IPv6 protocols */
/* #define TM_USE_IPV6 */

/*
 * Uncomment the following line if you want to be able to call tfStopTreck()
 * (resp. tfStopTreckMultipleContext() that will stop the treck stack for
 * the given context (resp. all contexts), and free all Treck stack allocated
 * memory for the given context (resp. all contexts).
 * Warning: All tasks making calls to the Treck stack, should be stopped
 * prior to calling tfStopTreck() or tfStopTreckMultipleContext()
 */
/* #define TM_USE_STOP_TRECK */

/*
 * Uncomment the following line if you want to use a backward compatible
 * version of tf6DhcpSetOption
 */
/* #define TM_6_DHCP_OLD_SET_OPTION */

/*
 * Uncomment TM_DISABLE_SOCKET_HASH_LIST, if you have limited data space,
 * or do not plan on having a lot of sockets. In that case the Treck
 * stack will not use hash tables during a socket table lookup.
 */
/* #define TM_DISABLE_SOCKET_HASH_LIST */

/*
 * Uncomment TM_USE_SOCKET_RB_TREE, if you have limited data space, and
 * therefore disabled the socket hash tables, or reduced their sizes
 * dramatically, and still want a reasonable socket look up table time.
 * This will enable the socket Red Black tree code.
 */
/* #define TM_USE_SOCKET_RB_TREE */

/*
 * Uncomment TM_6_USE_OBSOLETE_TF6GETROUTERID if you want to use the old
 * (obsoleted) version of tf6GetRouterId that returns an aggregate.
 * This function has been replaced by tf6NgGetRouterId() in sockapi6/t6grtrid.c
 */
/* #define TM_6_USE_OBSOLETE_TF6GETROUTERID */

/* comment out the following line if you do not want to use DHCP */

/* comment out the following line if you do not want to use PPP protocols */
#define TM_USE_PPP

/* uncomment the following line if you want to use the new 802.3 Ethernet
   link-layer, which supports Ethernet II (DIX) in addition to IEEE 802.3 */
/* #define TM_USE_ETHER_8023_LL */

/*
 * Uncomment the following line if you want the Ethernet link layer
 * to be able to ignore the VLAN tag on a packet and continue processing it
 */
/* #define TM_CHECK_TAGGED_ETHER_HEADER */

/*
 * Uncomment the following line if you want to use the PPPoE client link layer
 */
/* #define TM_USE_PPPOE_CLIENT */

/*
 * Uncomment the following line if you want to use the PPPoE server link layer
 */
/* #define TM_USE_PPPOE_SERVER */

/*
 * Uncomment the following line, if you want to use the netstat tool for
 * for outputting the routing entries, ARP entries and socket entries
 */
/* #define TM_USE_NETSTAT */

/*
 * Uncomment the following line to enable support for splitting out IPv4
 * and IPv6 traffic in the send path to separate virtual channels to
 * simulate multiple hosts as multiple IP aliases. Note that this is
 * incompatible with the default mode of IPv6 operation, therefore IPv6
 * prefix discovery must be disabled.
 */
/* #define TM_USE_VCHAN */

/*
 * Uncomment the following line to speed up lookup in the recieve-path of IP
 * aliases configured on the interface. This is intended for situations where
 * the user has configured many (i.e. >50) IP aliases on a single interface.
 */
/* #define TM_OPTIMIZE_MANY_MHOMES */

/*
 * Uncomment the following line for SNMPv1 only.
 * (SNMP option only.)
 */
/* #define TM_SNMP_VERSION 1 */

/*
 * Uncomment the following line for SNMPv1 and SNMPv2c (bilingual).
 * (SNMP option only.)
 */
/* #define TM_SNMP_VERSION 2 */

/*
 * Uncomment the following line for SNMPv1, SNMPv2c and SNMPv3 (trilingual).
 * (SNMP option only.)
 */
/* #define TM_SNMP_VERSION 3 */

/*
 * Uncomment the TM_SNMP_CACHE macro if you want the stack to keep a cache of
 * the UDP sockets, TCP vectors, ARP table, and Routing table for SNMP.
 * (SNMP option only.)
 */
/* #define TM_SNMP_CACHE */

/*
 * Comment out TM_USE_RFC1213_MIB2 if you do not want the deprecated RFC1213
 * MIB2 objects that are designed only for IPv4 to be included in the SNMP
 * agent.
 * This option requires to enable TM_USE_IPV4 and TM_USE_SNMP_CACHE to be fully
 * functional). If you are running the stack in dual mode (IPV4 and IPV6), V6
 * objects will not be displayed in those table.
 * (SNMP option only.)
 */
#define TM_USE_RFC1213_MIB2

/*
 * Comment out TM_USE_NG_MIB2 to disable the Next Generation MIB2, which
 * consists of tables that support both IPv4 and IPv6 entities.
 * This option requires to enable TM_SNMP_CACHE to be fully functional.
 * (SNMP option only.)
 */
#define TM_USE_NG_MIB2

/*
 * Uncomment the following line for 8-bit OIDs.
 * (SNMP option only.)
 */
/* #define TM_SNMP_8BIT_SUBIDS */

/*
 * Uncomment the following line 16-bit OIDs.
 * (SNMP option only.)
 */
/* #define TM_SNMP_16BIT_SUBIDS */

/*
 * Uncomment the TM_ALLOW_IP_SRC_CLASS_BROADCAST, if you want to allow IP
 * class broadcast as source address on the network, as long as it does
 * not coincide with a configured IP address directed broadcast.
 * For example, configure the IP stack with 192.168.10.173/16, and allow
 * another host to configure 192.168.10.255 as a host address, i.e.
 * that address won't be considered a broadcast address upon sending,
 * or receiving.
 */
/* #define TM_ALLOW_IP_SRC_CLASS_BROADCAST */

/*
 * TM_IP_FRAGMENT macro. Enable support for IPv4 fragmentation.
 * Comment out to save code space when IPv4 fragmentation is not needed.
 */
#define TM_IP_FRAGMENT

/*
 * TM_IP_REASSEMBLY macro. Enable support for IPv4 reassembly.
 * Comment out to save code space when IPv4 reassembly is not needed.
 */
#define TM_IP_REASSEMBLY

/*
 * This macro is commented out by default.
 * If you define TM_IP_FRAGMENT, and your device driver supports scattered
 * send, then define TM_IP_FRAGMENT_NO_COPY to avoid an extra internal data
 * copy when an IP datagram is fragmented.
 */
/* #define TM_IP_FRAGMENT_NO_COPY */

/*
 * Uncomment the TM_DISABLE_TELNETD macro, if you want to remove the TELNETD code.
 */
/* #define TM_DISABLE_TELNETD */

/*
 * Uncomment the TM_DISABLE_FTP macro, if you want to remove the FTP
 */
/* #define TM_DISABLE_FTP */

/*
 * Uncomment the TM_DISABLE_FTPD macro, if you want to remove the FTPD code.
 */
/* #define TM_DISABLE_FTPD */

/*
 * Uncomment the TM_DISABLE_TFTP macro, if you want to remove the TFTP
 */
/* #define TM_DISABLE_TFTP */

/*
 * Uncomment the TM_DISABLE_TFTPD macro, if you want to remove the TFTPD code.
 */
/* #define TM_DISABLE_TFTPD */

/*
 * Uncomment the TM_DISABLE_TCP macro, if you want to remove the TCP code.
 */
/* #define TM_DISABLE_TCP */

/*
 * Uncomment the TM_DISABLE_TCP_128BIT_RANDOM_ISS macro, if you want to
 * prevent the TCP code from using the MD5 hash algorithm to generate the TCP
 * initial sequence number based on an 128 bit random number.
 * WARNING: If you define that macro, then the code will use a 32-bit random
 * number instead and the stack will be more susceptible to security attacks
 * described in US-CERT VU#498440.
 */
/* #define TM_DISABLE_TCP_128BIT_RANDOM_ISS */

/*
 * Uncomment the TM_DISABLE_TCP_KEEPALIVE if you want to remove the TCP
 * KEEPALIVE code. This will save some code space, but will prevent the
 * use of the TCP keep alive option.
 */
/* #define TM_DISABLE_TCP_KEEPALIVE */

/*
 * Uncomment the TM_DISABLE_TCP_SACK macro, if you want to remove the TCP
 * Selective Acknowlegment Options (RFC2018) code.
 */
/* #define TM_DISABLE_TCP_SACK */

/*
 * Uncomment the TM_DISABLE_TCP_FACK macro if you want to remove the TCP
 * Forward Acknowledgement algorithm code.
 * Disabling TCP FACK prohibits TCP SACK from retransmitting more than
 * one SACK'ed segment. This option is recommended for lossy links and
 * should only be disabled if there is no packet loss on the link.
 * TCP FACK requires TCP SACK, therefore TM_DISABLE_TCP_SACK implies
 * TM_DISABLE_TCP_FACK.
 */
/* #define TM_DISABLE_TCP_FACK */

/*
 * Uncomment the TM_DISABLE_TCP_DRAFT_TCPM_INITCWND macro, if you want to
 * disable the TCP Initial Send Window Increase as described in
 * draft-ietf-tcpm-initcwnd.
 */
/* #define TM_DISABLE_TCP_DRAFT_TCPM_INITCWND */

/*
 * Uncomment the TM_DISABLE_TCP_RFC3390 macro, if you want to disable
 * the TCP Initial Send Window Increase as described in RFC 3390.
 */
/* #define TM_DISABLE_TCP_RFC3390 */

/*
 * Uncomment the TM_DISABLE_TCP_RFC2581 macro, if you want to remove the TCP
 * congestion control update to RFC2001 as described in RFC2581.
 */
/* #define TM_DISABLE_TCP_RFC2581 */

/*
 * Uncomment the TM_DISABLE_TCP_RFC3042 macro, if you want to remove the
 * Limited Transmit Algorithm that enhances TCP's Loss Recovery as described
 * in RFC3042.
 */
/* #define TM_DISABLE_TCP_RFC3042 */

/*
 * Comment out the TM_DISABLE_TCP_ACK_PUSH macro, if you want the
 * stack to send an immediate TCP ACK, when receiving a TCP segment with
 * the PUSH bit set.
 * (Important: this macro should be commented out when the peer runs
 *  windows 2000.)
 */
#define TM_DISABLE_TCP_ACK_PUSH

/*
 * Uncomment the TM_DISABLE_PMTU_DISC macro, if you want to disable automatic
 * Path MTU discovery on indirect routes.
 */
/* #define TM_DISABLE_PMTU_DISC */

/*
 * Uncomment the TM_DISABLE_UDP_CACHE to remove the one socket cache UDP
 * lookup. This could be done to either save code space, or in case the
 * compiler has trouble parsing the one single UDP cache lookup code as
 * that code is somewhat complex. Removing the one socket UDP cache lookup
 * does not change the UDP functionality.
 */
/* #define TM_DISABLE_UDP_CACHE */

/*
 * Uncomment the TM_ARP_UPDATE_ON_RECV, if you want to avoid sending an ARP
 * request every 10 minutes on an active ARP entry, i.e. an ARP entry for
 * a destination IP address that the stack is actively sending to.
 * Note that uncommenting out this macro will affect speed and size, since
 * every incoming packet will be checked for an ARP cache match on its
 * destination IP address.
 */
/* #define TM_ARP_UPDATE_ON_RECV */

/*
 * Uncomment the TM_NO_COPY_OVER_USER_DATA, if you want to prevent the stack
 * from copying the TCP header in acked data area of a user owned buffer.
 */
/* #define TM_NO_COPY_OVER_USER_DATA */

/*
 * Currently the stack will start sending with a full size TCP Initial Window
 * on direct routes
 * Uncomment the TM_USE_TCP_SMALL_IW_DIRECT, if you want the stack to start
 * sending using a reduced TCP Initial Window as it does on indirect routes.
 */
/* #define TM_USE_TCP_SMALL_IW_DIRECT */

/*
 * Currently the stack will discard any SYN segment that have the FIN, or PSH,
 * or URG bit set, and have the ACK bit not set, if there is no data.
 * Uncomment the TM_USE_TCP_CERT_VU464113 macro, if you want the stack
 * to discard these segments even when there is data.
 * Note that defining this macro will not allow T/TCP to work.
 */
/* #define TM_USE_TCP_CERT_VU464113 */

/*
 * Uncomment the TM_USE_TCP_PACKET macro, if you want to modify the
 * TCP behaviour and force TCP to send data on user send packet boundaries.
 * Warning: uncommenting this macro, will make TCP less efficient, and
 * will also disable Path MTU discovery, and TCP Selective Acknowledgements.
 */
/* #define TM_USE_TCP_PACKET */

/*
 * Uncomment the TM_USE_REUSEADDR_LIST macro, if you want to use the
 * SO_REUSEADDR socket level option with setsockopt(). This enables use of
 * the socket reuse address list, i.e. enable binding on the same port using
 * different local IP addresses.
 */
/* #define TM_USE_REUSEADDR_LIST */

/*
 * Uncomment the TM_USE_REUSEPORT macro, if you want to use the
 * SO_REUSEPORT socket level option with setsockopt(). This enables use of
 * the socket reuse address list, and enables binding several sockets on the
 * same port and same local IP address.
 */
/* #define TM_USE_REUSEPORT */

/*
 * Uncomment the TM_USE_AUTO_IP macro, if you want to use Auto configuration,
 * or want to add collision detection.
 */
/* #define TM_USE_AUTO_IP */

/*
 * Uncomment TM_USE_DHCP_FQDN to enable the DHCP FQDN option
 */
/* #define TM_USE_DHCP_FQDN */

/*
 * Uncomment TM_DHCP_CB_WITH_MHOME to also use the multihome index in the
 * address notification callback function.
 * NOTE: This changes the address notification callback function prototype.
 */
/* #define TM_DHCP_CB_WITH_MHOME */

/*
 * If you do not need to select from a collection of DHCP offers, you
 * can uncomment the TM_DISABLE_DHCP_COLLECT macro to remove the code
 * that provides support for this feature.
 */
/* #define TM_DISABLE_DHCP_COLLECT */

/*
 * Uncomment the following line if you do not want to use the DHCP send
 * overload feature. This feature affects how Treck sends large DHCP
 * messages (over 576 bytes). To reduce the overall DHCP message size, the
 * unused "sname" and "file" fields (64 bytes and 128 bytes respectively)
 * will be utilized for option overloading ([RFC2132] section 9.3).
 */
/* #define TM_DISABLE_DHCP_SEND_OVERLOAD */

/*
 * Uncomment the following line to enable the API for retrieving the
 * DHCP Domain Search Option ([RFC3397]) returned from the server.
 */
/* #define TM_USE_DHCP_DOMAIN_SEARCH */

/*
 * Uncomment the following line to configure the DNS resolver for iterative
 * Domain Search based on the domain names returned from a DHCP server.
 * For example, function getaddrinfo() will attempt to resolve the node
 * name provided and, if unsuccessful, will append each of the DHCP
 * domain names to the node name and resubmit the query until it is
 * successful or the domain name list is exhausted.
 */
/* #define TM_USE_DNS_DOMAIN_SEARCH */

/*
 * Uncomment the TM_USE_RAW_SOCKET macro, if you want to use raw sockets.
 * (tfRawSocket() need to be called, instead of socket())
 */
/* #define TM_USE_RAW_SOCKET */

/*
 * Uncomment the TM_RAW_SOCKET_INPUT_ICMP_REQUESTS, if you want ICMP echo
 * requests, and ICMP address mask requests to be delivered to a raw ICMP
 * socket.
 */
/* #define TM_RAW_SOCKET_INPUT_ICMP_REQUESTS */

/*
 * Uncomment TM_PING_REPLY_BROADCAST if you want ICMP replies to be sent
 * when the requested destination is a broadcast or a multicast address.
 */
/* #define TM_PING_REPLY_BROADCAST */

/*
 * Uncomment TM_PING_REPLY_MULTICAST if you want ICMP replies to be sent
 * when the requested destination is a multicast address.
 * (not needed if TM_PING_REPLY_BROADCAST is enabled)
 */
/* #define TM_PING_REPLY_MULTICAST */

/*
 * Uncomment the TM_IGMP macro, if you have purchased the IGMP protocol
 */
/* #define TM_IGMP */

/*
 * Uncomment the TM_USE_IGMPV3 macro, if you have purchased the IGMP protocol
 * and wish to use IGMPv3.
 */
/* #define TM_USE_IGMPV3 */

/*
 * Uncomment TM_DNS_USE_SRV if you want DNS SRV record support.
 * This applies only if you have purchased the DNS Resolver product.
 */
/* #define TM_DNS_USE_SRV */

/*
 * Uncomment TM_DNS_MAX_SOCKETS_ALLOWED if you want to specify the number
 * of simultaneous DNS requests allowed. Default: 1.
 * This applies only if you have purchased the DNS Resolver product.
 */
/* #define TM_DNS_MAX_SOCKETS_ALLOWED 1 */

/*
 * Uncomment TM_DNS_TRANS_ID_BACKLOG_SIZE if you want to specify the size of the
 * backlog of random Transaction IDs. All newly generated Transaction IDs are
 * required to be unique to this list and to all Transaction IDs currently in
 * the DNS cache. The default value is 8. For security purposes this value
 * should remain as small as is reasonably possible.
 * This applies only if you have purchased the DNS Resolver product.
 */
/* #define TM_DNS_TRANS_ID_BACKLOG_SIZE 8 */

/*
 * PPP options
 */
/*
 * Uncomment the TM_PPP_LQM macro, if you want PPP Link Quality Monitoring
 */
/* #define TM_PPP_LQM */

/*
 * Uncomment the TM_USE_IPHC to enable IP header compression (RFC-2507) with
 * PPP.
 */
/* #define TM_USE_IPHC */

/*
 * Uncomment the TM_USE_EAP to enable Extensible Authentication Protocol with
 * PPP.
 */
/* #define TM_USE_EAP */

/* define the following macro to use MSCHAP */
/*#define TM_USE_PPP_MSCHAP*/

/*
 * NAT Options
 */

/* Enable NAT progress display with TM_ERROR_LOGGING, TM_DEBUG_LOGGING */
/* and/or TM_TRACE_LOGGING.  (TM_NAT_TRACE used to do this.)           */

/* To enable tfNatDump(), which can display a list of NAT triggers,    */
/* define TM_DEBUG_LOGGING in this file (TM_NAT_DUMP used to do this)  */

/* Discard packets that NAT does not transform */
#define TM_NAT_STRICT

/*
 * TM_IP_MCAST_FORWARD macro. Enable IP multicast forwarding code.
 * Comment out to save code space when IP multicast forwarding is not needed.
 */
/* #define TM_IP_MCAST_FORWARD */

/*
 * TM_IP_MCAST_ALLOW_ADMIN_FORWARD macro. If IP multicast forwarding is
 * enabled, you can uncomment the following macro to allow forwarding of
 * Administratively Scoped IP (RFC2365) destination addresses,
 * 239.0.0.0 to 239.255.255.255. Normally, these IP addresses are
 * treated as link local only.
 */
/* #define TM_IP_MCAST_ALLOW_ADMIN_FORWARD */

/*
 * Uncomment the TM_USE_UPNP_DEVICE macro to enable UPnP network device
 * support.
 * NOTE: if you enable TM_USE_UPNP_DEVICE, you must also enable TM_USE_HTTPD
 * and TM_USE_HTTPD_SSI, since Treck UPnP uses Treck web server SSI.
 */
/* #define TM_USE_UPNP_DEVICE */

/*
 * Uncomment the TM_USE_SOAP macro to enable SOAP.
 * NOTE: if you enable TM_USE_SOAP, you must also enable TM_USE_HTTPD, since
 * Treck SOAP uses Treck web server.
 * NOTE: TM_USE_SOAP is automatically enabled for you when you enable
 * TM_USE_UPNP_DEVICE.
 */
/* #define TM_USE_SOAP */

/*
 * Uncomment the TM_USE_UNICODE macro to enable Treck UPnP support for
 * Unicode. By default, Treck UPnP assumes that all service state
 * variables of UPnP type "string" or "char" are ASCII, not Unicode.
 */
/* #define TM_USE_UNICODE */

/*
 * Uncomment the TM_USE_FLOATING_POINT macro to enable Treck UPnP support for
 * the UPnP floating point types "r4", "r8", "fixed.14.4" and "float".
 */
/* #define TM_USE_FLOATING_POINT */

/*
 * Uncomment the TM_USE_HTTPD to enable HTTPD (web server)
 */
/* #define TM_USE_HTTPD */

/*
 * Uncomment the TM_USE_HTTPD_CGI to enable CGI support of HTTPD (web server)
 */
/* #define TM_USE_HTTPD_CGI */

/*
 * Uncomment the TM_USE_HTTPD_SSI to enable SSI (Server Side Includes)
 * support of HTTPD (web server)
 */
/* #define TM_USE_HTTPD_SSI */

/*
 * Uncomment the TM_USE_POP3 to enable POP3
 */
/* #define TM_USE_POP3 */

/*
 * Uncomment the TM_USE_SMTP to enable SMTP
 */
/* #define TM_USE_SMTP */

/*
 * Uncomment the TM_MOBILE_IP4 macro, if you have purchased the Mobile IPv4
 * option.
 */
/* #define TM_MOBILE_IP4 */

/*
 * Uncomment the TM_MIP_USE_DHCP macro if you have purchased the Mobile IPv4
 * option and the DHCP option.
 * Note that this option will enable TM_USE_DHCP automatically
 */
/* #define TM_MIP_USE_DHCP */

/*
 * IPsec Option
 * Uncomment the TM_USE_IPSEC macro, if you have purchased the IPSEC option.
 */
/*#define TM_USE_IPSEC */

/*
 * Run IPsec as its own task
 */
/* #define TM_USE_IPSEC_TASK */

/*
 * When running IPsec as its own task, the maximum amount of allocated memory
 * that the task queue can contain
 */
/* #define TM_IPSEC_TASK_MAX_QUEUE_SIZE 16384 */

/*
 * If you are using the IPsec task (TM_USE_IPSEC_TASK), this macro will allow
 * you to set up another task to finish transmission of the packet after
 * crypto processing has completed. This will allow the IPsec task to push
 * another packet into the crypto engine as quickly as possible.
 */
/* #define TM_USE_IPSEC_HANDOFF_TASK */

/*
 * When running the IPsec handoff task, the maximum amount of allocated memory
 * that the task queue can contain
 */
/* #define TM_IPSEC_HANDOFF_TASK_MAX_QUEUE_SIZE 16384 */

/*
 * IPsec SA Timer Option
 * Uncomment the TM_DISABLE_IPSEC_SA_TIMERS macro, if you want to disable the
 * lifetime timers.  If this is done, there should be some external timer that
 * manages the callback to invoke the soft and hard lifetime logic.
 */
/*#define TM_DISABLE_IPSEC_SA_TIMERS */

/*
 * IKE Option
 * Uncomment the TM_USE_IKE macro, if you are going to use KEY management rather
 * than manual keying
 */
/*#define TM_USE_IKE */

/*
 * Uncomment this to set the minimum percentage of the IKE SA hard
 * byte lifetime allowed before the soft byte lifetime expires to 20%.
 * If not set, this defaults to 20%.
 */
/* #define TM_ISAKMPSA_VLIFETIME_SOFT_MARGIN_PCT 20 */

/*
 * Uncomment this to set the minimum percentage of the IPsec SA hard
 * byte lifetime allowed before the soft byte lifetime expires to 20%.
 * If not set, this defaults to 20%.
 */
/* #define TM_IPSECSA_VLIFETIME_SOFT_MARGIN_PCT 20 */


/*
 * Uncomment the TM_USE_IKE_TASK macro, if you want to
 * run IKE as its own task while processing received packets from the network.
 */
/* #define TM_USE_IKE_TASK */

/*
 * Uncomment the TM_USE_IKE_DPD macro, if you want to enable the
 * Dead Peer Detection code in IKE.
 * Needs TM_USE_IKE_POLICIES to be defined.
 */
/* #define TM_USE_IKE_DPD */

/*
 * Uncomment the TM_USE_NATT macro, if you want to enable the
 * Nat traversal code in IKE.
 * Needs TM_USE_IKE_POLICIES to be defined.
 */
/* #define TM_USE_NATT */

/*
 * Multiple Proposal Options
 * Uncomment the TM_USE_MULTIPLE_PROPOSALS macro, if you are going to use
 * bundled SAs (i.e. AH/ESP/IPComp, for example).
 */
/*#define TM_USE_MULTIPLE_PROPOSALS */

/*
 * IPsec Interoperability when AH + ESP are adjacent (no IP header between)
 * Uncomment the TM_USE_IPSEC_ADJACENT_HEADERS macro if you want to process
 * incoming IPsec (AH + ESP) packets using multiple proposals without
 * using an intermediate IP header. Note that this will also force Treck
 * to send IPsec (AH + ESP) packets without the intermediate IP header.
 * This macro requires TM_USE_MULTIPLE_PROPOSALS
 */
/*define TM_USE_IPSEC_ADJACENT_HEADERS */

/*
 * IKE Policy Option
 * Uncomment the TM_USE_IKE_POLICIES macro, if you are going to use IKE
 * policies in conjunction with IPsec policies.
 */
/*#define TM_USE_IKE_POLICIES */

/*
 * IKE Policy Incoming Outgoing Option
 * Uncomment the TM_IKE_VALIDATE_OUTGOING macro, if you want to check to see
 * that outgoing packet selectors match the addresses specified in the IPsec's
 * associated IKE policy.
 */
/*#define TM_IKE_VALIDATE_OUTGOING */

/*
 * IPsec Priorities
 * Uncomment the TM_USE_PRIORITIES macro, if you are going to use IKE policies
 * or Multiple proposals.
 */
/*#define TM_USE_PRIORITIES */

/*
 * IPsec Priority Processing
 * Uncomment the TM_USE_PRI_PROC macro, if you want to process IPsec policies
 * in Priority-based order instead of Index-based order.  This requires
 * TM_USE_PRIORITIES.
 */
/*define TM_USE_PRI_PROC */

/*
 * IPsec Port Range Processing
 * Uncomment the TM_USE_IPSEC_PORT_RANGE macro if you want to permit the
 * addition of IPsec policies that contain port ranges.
 * NOTE 1: IPsec policies with port ranges are only valid when used
 *         as BYPASS or DISCARD policies.
 * NOTE 2: Enabling this feature will change the tsIpsecSelectorInString
 *         structure by adding two more ttUser16Bit elements.
 */
/*#define TM_USE_IPSEC_PORT_RANGE */

/*
 * Enhanced Logging
 * Uncomment the TM_USE_LOGGING_LEVEL macro, if you want to use Enhanced
 * Logging.  Note that each module and level will also need to be defined
 * (i.e. TM_LOG_ENB_ALL_LEVELS and TM_LOG_ENB_ALL_MODULES or specific
 * levels/modules as required).  For more information, see trmacro.h or
 * consult the appropriate user documentation.
 */
/*define TM_USE_LOGGING_LEVELS */

/*
 * SSL Client Option
 * Uncomment the TM_USE_SSL_CLIENT macro, if you are going to use SSL client
 * functionality
 */
/*#define TM_USE_SSL_CLIENT */

/*
 * SSL Server Option
 * Uncomment the TM_USE_SSL_SERVER macro, if you are going to use SSL server
 * functionality
 */
/*#define TM_USE_SSL_SERVER */

/*
 * SMTP client over SSL option
 * Uncomment the TM_USE_SMTP_SSL macro, if you are going to use SMTP client
 * over SSL functionality
 */
/* #define TM_USE_SMTP_SSL */

/*
 * FTP client over SSL option
 * Uncomment the TM_USE_FTP_SSL macro, if you are going to use FTP client
 * over SSL functionality
 */
/*#define TM_USE_FTP_SSL */
/*
 * SSL Debuging option
 * Uncomment the TM_SSL_DEBUG macro, if you are going to debug SSL
 * encrypt/decrypt, MAC, and padding
 */
/*#define TM_SSL_DEBUG */

/*
 * Allow the crypto engine to block while processing data
 */
/* #define TM_USE_ASYNC_CRYPTO */

/*
 * Uncomment the TM_DEV_SEND_OFFLOAD macro, if you want to use the
 * device driver TCP segmentation/checksum offload capabilities.
 */
/* #define TM_DEV_SEND_OFFLOAD */

/*
 * Uncomment the TM_DEV_RECV_OFFLOAD macro, if you want to use the
 * device driver recv packet checksum offload capabilities.
 */
/* #define TM_DEV_RECV_OFFLOAD */

/*
 * Uncomment the TM_USE_DRV_ONE_SCAT_SEND macro, if you want to use
 * a single call to the device driver, passing the packet handle, even
 * when sending a frame with scattered buffers. Note that to enable
 * this feature, this macro needs to be added, and tfUseInterfaceOneScatSend
 * needs to be called on the interface that supports it.
 */
/* #define TM_USE_DRV_ONE_SCAT_SEND */

/*
 * Uncomment the TM_USE_DRV_SCAT_RECV macro, if you want to allow
 * the device driver recv function to pass back a frame to the stack
 * in scattered buffers ("Gather Read"). Note that to enable this feature,
 * this macro needs to be added, and  tfUseInterfaceScatRecv needs to be
 * called on the interface that supports it.
 */
/* #define TM_USE_DRV_SCAT_RECV */

/*
 * Uncommment the TM_USE_USER_PARAM macro if you want Treck to supply and
 * manage a user defined data item that is unique for each TCP connection.
 * This data can be stored and retrieved using the TM_TCP_USER_PARAM option
 * when calling setsockopt() and getsockopt(), respectively.
 * When TM_USE_DRV_SCAT_RECV and TM_USE_DRV_ONE_SCAT_SEND are also defined,
 * this data item can be accessed by your device driver, as follows:
 *  - In the ttDevOneScatSendFuncPtr function you set by calling
 *    tfUseInterfaceOneScatSend(), read the pktuUserParam member of the
 *    ttUserPacketPtr parameter. Treck will copy the user data from the
 *    TCP socket to the ttUserPacket structure before calling your
 *    scattered send function.
 *  - In the ttDevScatRecvFuncPtr function you set by calling
 *    tfUseInterfaceScatRecv(), write the druUserParam member in the first
 *    ttDruBlock you return via the ttDruBlockPtrPtr parameter. Treck will
 *    copy this data from the ttDruBlock to the new TCP socket that is
 *    created for each incoming connection request received by a listening
 *    socket.
 * For an active connection, your application should set the user data
 * prior to calling connect().
 * For a passive connection, your application can retrieve the data from
 * the new socket returned by accept().
 */
/* #define TM_USE_USER_PARAM */

/*
 * Uncommment TM_NEED_ETHER_32BIT_ALIGNMENT and uncomment TM_USE_DRV_SCAT_RECV,
 * without using tfUseInterfaceScatRecv(),
 * if you want tfRecvInterface to make the TCP/IP header aligned on a
 * 4-byte boundary, if it is not aligned coming from a single buffer in
 * an Ethernet device driver.
 */
/* #define TM_NEED_ETHER_32BIT_ALIGNMENT */

/*
 * If your processor has a data cache and your network hardware supports DMA,
 * you should define this macro to be the cache line size (in bytes) of your
 * data cache. This ensures that all packet buffers will be allocated to start
 * and end at cache line boundaries, making cache flushing and invalidation in
 * the driver much easier to handle.
 * This option will cause extra RAM utilization in your system. Up to
 * ((2 * TM_PACKET_BUF_CACHE_ALIGN) - 2) extra bytes will be allocated for
 * each packet buffer to fulfill the alignment requirements.
 */
/* #define TM_PACKET_BUF_CACHE_ALIGN 64 */

/*
 * This macro causes the stack to manage data cache coherency internally. If
 * this is defined, the API's tfUseInterfaceCacheInvalFunc,
 * tfUseInterfaceCacheFlushFunc, and tfGetCacheSafeDrvBuf become available. The
 * driver buffer pool (tfPoolXXX) is also modified to use this functionality.
 * The stack will call the registered callback functions to flush or invalidate
 * data packets as needed. tfGetCacheSafeDrvBuf can be called to pre-allocate
 * receive buffers in the driver, if necessary.
 * TM_PACKET_BUF_CACHE_ALIGN must be correctly defined for this to work.
 * Note: This will not work on byte-stuffing interfaces (PPP, SLIP, etc.)
 */
/* #define TM_USE_DCACHE_MANAGEMENT */

/*
 * Uncomment the TM_LOOP_TO_DRIVER, if you want to loop back all the way
 * to the driver when sending to an Ethernet interface IP address.
 */
/* #define TM_LOOP_TO_DRIVER */

/*
 * Undefine/delete the TM_INDRV_INLINE_SEND_RECV macro to test intra
 * machine driver with a separate recv task. In that case the intra machine
 * received data will no longer be processed in the send path, but will be
 * processed when tfRecvInterface/tfRecvScatInterface is called. In the
 * examples directory, the txscatlp.c, and txscatdr.c modules contain sample
 * code that uses this feature.
 */
#define TM_INDRV_INLINE_SEND_RECV

/*
 * Uncomment the TM_USE_INDRT, if you want to use the GHS INDRT debugging
 * tools . You also need to call tfUseIndrt() on the Ethernet interface
 * you want the INDRT debug messages to be sent and received on.
 */
/* #define TM_USE_INDRT */

/*
 * Uncomment the TM_MULTIPLE_CONTEXT macro, if you want to use multiple
 * instances of the Treck stack.
 */
/* #define TM_MULTIPLE_CONTEXT */

/*
 * Uncomment the TM_USE_KERNEL_CONTEXT macro if you are running multiple
 * Treck contexts and you want the kernel to be responsible for maintaining
 * the current context.
 * You must also provide public functions tfKernelSetContext() and
 * tfKernelGetContext() for Treck to be able to store and retrieve the
 * current context.
 * This would be necessary for a preemptive multithreaded application running
 * different Treck contexts in different threads.
 */
/* #define TM_USE_KERNEL_CONTEXT */

/*
 * Uncomment the TM_USE_STRONG_ESL macro, if you want to bind a socket
 * to an interface/device, which will restrict traffic to and from
 * that socket to traffic on the bound device.
 */
/* #define TM_USE_STRONG_ESL */

/*
 * Uncomment the TM_USE_STRICT_STRONG_ESL macro, if you want the stack
 * to automatically bind a TCP accepted socket (whose listening socket
 * was not bound to a device) to the incoming device.
 */
/* #define TM_USE_STRICT_STRONG_ESL */

/*
 * By default the prototypes in the header files are not declared extern.
 * If your linker dictates that they should be declared extern, then
 * uncomment the following macro.
 */

/* #define TM_PROTO_EXTERN extern */

/*
 * Uncomment the TM_DISABLE_ANSI_LINE_FILE macro if your compiler does not
 * support the ANSI __LINE__ and __FILE__ macros.
 * The tm_assert() macro will use the ANSI __LINE__ and __FILE__ macros (if
 * available) to print the source line number and source file name identifying
 * where in the code an assertion failure occurred for debugging purposes.
 */
/* #define TM_DISABLE_ANSI_LINE_FILE */

/* Uncomment the TM_PC_LINT macro, if you are using PC-LINT */
/*#define TM_PC_LINT */


/*
 * Thread stop is used to stop a thread which has had an unrecoverable error
 * by default defined to be a forever loop
 *
 * Unrecoverable errors dictate that the system MUST be reset!
 * You can define this to the reset for your board
 */

/* #define tm_thread_stop rtosReset() */

/*
 * Define the TM_PING_MILLISECONDS_INTERVAL macro, if you want the
 * pingInterval parameter passed to the obsolete tfPingOpenStart API
 * to be in milliseconds rather than in seconds.
 */
/* #define TM_PING_MILLISECONDS_INTERVAL */


/*
 * Performance Macros
 */

/*
 * If we are using ethernet, we can use it inline to increase speed.
 */
/* #define TM_BYPASS_ETHER_LL */

/*
 * Optimize for speed
 */
/* #define TM_OPTIMIZE_SPEED */

/*
 * Optimize for size
 */
/* #define TM_OPTIMIZE_SIZE */

/*
 * If you have only a single interface, and you only configure a single IP
 * address on that interface (i.e. multi-homing is not required), then
 * uncomment the TM_SINGLE_INTERFACE_HOME macro to reduce code size.
 *
 * Warning: Defining this will prevent addition of the loop back device.
 * 1. Packets sent to the single interface IP address will be sent all the
 *    way to the driver, instead of being loop back by the stack.
 * 2. Packets cannot be sent to the IP loop back address, 127.0.0.1.
 */
/* #define TM_SINGLE_INTERFACE_HOME */

/*
 * If you have only a single interface, and you are using IPv6, then
 * uncomment the TM_SINGLE_INTERFACE macro to reduce code size. Note that
 * all IPv6 interfaces are multi-homed, so you cannot use the
 * TM_SINGLE_INTERFACE_HOME macro with IPv6.
 */
/* #define TM_SINGLE_INTERFACE */

/*
 * Uncomment TM_USE_UDP_LOOKUP_PERF to enhance UDP and raw socket lookup
 * performance when you have a very large number of sockets.
 * This is useful only if your application has UDP or raw sockets that are
 * receiving on the same port but have different address or device bindings.
 * Incoming packets can be dispatched to the proper socket quicker based on
 * detailed binding information.
 * This enhancement will add code (3 to 4 Kbytes for x86) and probably run
 * slightly slower for most applications, so use it only if necessary.
 */
/* #define TM_USE_UDP_LOOKUP_PERF */

/*
 * Uncomment TM_BCAST_RECV_ALL_LOCAL_ADDR if you have defined
 * TM_USE_UDP_LOOKUP_PERF and you want legacy support for receiving
 * IPv4 local multicast packets (addresses 224.0.0.1 to 224.0.0.255).
 * Legacy support allows your sockets to receive multicast packets sent to
 * IPv4 local multicast groups even if the socket has not joined the groups.
 * If you have not defined TM_USE_UDP_LOOKUP_PERF, your sockets automatically
 * have legacy support.
 * Use of this option may degrade performance in applications that use
 * TM_USE_UDP_LOOKUP_PERF.
 * This option has no effect if TM_USE_UDP_LOOKUP_PERF is not defined.
 */
/* #define TM_BCAST_RECV_ALL_LOCAL_ADDR */

/*
 * If you want to use AutoIP on multiple interfaces with Treck dual stack
 * IPv4+IPv6, then uncomment the TM_4_USE_SCOPE_ID macro. When
 * TM_4_USE_SCOPE_ID is enabled, any non-global scope IPv4 address matching
 * 10.0.0.0/8, 172.16.0.0/12, 192.168.0.0/16 or 169.254.0.0/16 (refer to the
 * macro IN4_IS_ADDR_LINKLOCAL in trmacro.h) must be stored in IPv4-mapped
 * IPv6 address format using "struct sockaddr_in6", and you must call the API
 * tf6SockaddrSetScopeId to set the scope ID on this "struct sockaddr_in6"
 * before passing it to any Treck API.
 */
/* #define TM_4_USE_SCOPE_ID */

/*
 * User defined checksum routines.
 * One of either TM_USER_OCS or TM_CUSTOM_OCS may be defined.
 * 1. If neither is defined, the stack will use a standard C implementation of
 *    the checksum or include a CPU-specific implementation if the user has
 *    defined an additional CPU specific macro such as TM_BORLAND_ASM_OCS,
 *    TM_GNUXSCALE_ASM_OCS, etc.
 * 2. TM_USER_OCS will cause the stack to include the file ocksum/trcsuser.c,
 *    which must be created by the user and must contain the function
 *    tfPacketChecksum().
 * 3. TM_CUSTOM_OCS will cause the stack to not compile in any checksum
 *    routine, meaning the user must link in a module containing the function
 *    tfPacketChecksum().
 *
 *    See the file trpkt.c for the standard implementation of this function.
 */
/* #define TM_USER_OCS */
/* #define TM_CUSTOM_OCS */

/*
 * User defined random number generator
 * TM_USE_KERNEL_RNG will cause Treck's internal random number generator
 * to be replaced by the user-defined tfKernelGetRandom function.
 */
/* #define TM_USE_KERNEL_RNG */

/* If you have an different keyword for interrupt, then #define TM_INTERRUPT
   here to be that keyword
*/
/* #define TM_INTERRUPT interrupt */

/* !! NOTE about TM_GLOBAL_QLF and TM_GLOBAL_NEAR: *
 *
 * Only one of them can be redefined to have a value, otherwise compiler
 * errors will occur
 */

/* Default qualifier for global variables. If you would like to put all global
 * variables into one memory type (e.g. far, huge, near), then #define
 * TM_GLOBAL_QLF here to be that qualifier and leave TM_GLOBAL_NEAR undefined
 */
/* #define TM_GLOBAL_QLF */

/* Default qualifier for frequently used global variables.
 * If you would like to put the frequently used global variables into
 * one memory type (e.g. near) and the rest of them into a different
 * memory type (e.g. far, huge), then #define the memory type for frequently
 * used global variables here as TM_GLOBAL_NEAR and leave TM_GLOBAL_QLF
 * undefined
 */
/* #define TM_GLOBAL_NEAR */


/* Default qulifier for constants. If you would like to put all constants
 * into one memory type (e.g. far, huge, near), the #define TM_CONST_QLF
 * here to be that qualifier.
 */
/* #define TM_CONST_QLF */

/*
 * Uncomment the TM_USE_SHEAP macro if your RTOS does not provide heap
 * management routines, or if you do not want the Treck stack to allocate its
 * blocks of memory from the RTOS heap. When TM_USE_SHEAP is defined, the stack
 * allocates its blocks of memory from the Treck simple heap static array.
 */
/* #define TM_USE_SHEAP */

/*
 * Simple heap size (used by simple heap allocation routines in trsheap.c)
 * This is used by tfSheapMalloc() and tfSheapFree() provided in
 * trsheap.c, and called by tfKernelMalloc() and tfKernelFree() when
 * the RTOS does not provide heap support, and you do not want to use
 * C library malloc and free.
 * This is not documented because it is an OS supplement.
 * On a DSP platform, the heap size should be specified in words; on all
 * other targets the heap size should be specified in bytes.
 */
/*#define TM_SHEAP_SIZE TM_UL(48)*TM_UL(1024) */

/*
 * Minimum block size in bytes when using the simple heap, either when
 * allocating a new block, or when refragmenting a freed block.
 * If not defined here, default value is 8 if TM_ERROR_CHECKING is
 * defined, 4 otherwise.
 */
/* #define TM_SHEAP_MIN_BLOCK_SIZE 16 */

/*
 * Uncomment the TM_SHEAP_MARK_MEMORY macro, so that simple heap
 * initial memory is filled with 0xFE, so that allocated simple heap memory
 * is filled with 0xA0, and that, freed simple heap memory is filled with 0xFA.
 * This helps check whether memory is accessed after having been freed.
 */
/* #define TM_SHEAP_MARK_MEMORY */

/*
 * Uncomment the TM_DYNAMIC_CREATE_SHEAP macro if you want the Treck simple
 * heap to be dynamically allocated by calling tfKernelSheapCreate rather
 * than implemented as a static array. It is usually necessary to define
 * TM_DYNAMIC_CREATE_SHEAP, if TM_SHEAP_NUM_PAGE is bigger than 1 (see below).
 */
/* #define TM_DYNAMIC_CREATE_SHEAP */

/*
 * Number of memory pages. Instead of a unique array, the simple heap can be
 * divided into several ones. Uncomment TM_SHEAP_NUM_PAGE and indicate the
 * number of pages if you are using the simple heap with a system that has
 * paged memory and that one page is too small to hold the whole simple heap
 * memory (static or preallocated by tfKernelSheapCreate).
 * In this case the simple heap will be divided in several non-contiguous
 * pages. If you do define TM_SHEAP_NUM_PAGE to a number bigger than 1,
 * then you will likely need to define TM_DYNAMIC_CREATE_SHEAP also.
 * The default for TM_SHEAP_NUM_PAGE is 1. Each page of memory must
 * have the same size. The page size is TM_SHEAP_SIZE/TM_SHEAP_NUM_PAGE.
 * If the page size is lower or equal to 4Kb (TM_BUF_Q6_SIZE), you cannot
 * use dynamic memory and must define TM_DISABLE_DYNAMIC_MEMORY.
 */
/* #define TM_SHEAP_NUM_PAGE 8 */

/*
 * Uncomment TM_DISABLE_DYNAMIC_MEMORY if you need to save ROM and RAM space.
 * Note that this will disable the Treck internal recycled buffer lists, which
 * is part of the "Treck Learn" feature. The system will require less
 * memory, but will be slower, because the system will not be able to take
 * advantage of the "Treck Learn" feature.
 */
/* #define TM_DISABLE_DYNAMIC_MEMORY */

/*
 * Uncomment TM_USE_FILTERING to allow IPv4 datagrams to be delivered
 * to a user-specified callback function on a per-interface basis.  These
 * callbacks can be enabled/disabled for each device however this macro must
 * be enabled before any filter callback processing logic is processed.
 */
/* #define TM_USE_FILTERING */

/*
 * Uncomment TM_USE_FILTERING_CONTIGUOUS_DATA, if you already have uncommented
 * TM_USE_FILTERING, and if you wish to peek at the data in the user-specified
 * call back routine. In that case the data will be contiguous with the IPv4
 * header, and ulp header.
 */
/* #define TM_USE_FILTERING_CONTIGUOUS_DATA */

/*
 * Uncomment TM_6_USE_FILTERING to allow IPv6 datagrams to be delivered
 * to a user-specified callback function on a per-interface basis.  These
 * callbacks can be enabled/disabled for each device however this macro must
 * be enabled before any filter callback processing logic is processed.
 * When TM_6_USE_FILTERING is defined only the IPv6 header followed by
 * two bytes is guaranteed to be contiguous.
 * Please see also TM_6_USE_FILTERING_CONT_DATA below
 */
/* #define TM_6_USE_FILTERING */

/*
 * Uncomment TM_6_USE_FILTERING_CONT_DATA, if you already have uncommented
 * TM_6_USE_FILTERING, and if you wish to peek at the ULP, and/or data in the
 * user-specified call back routine. In that case the ULP and data will be
 * contiguous with the IPv6 header.
 */
/* #define TM_6_USE_FILTERING_CONT_DATA */

/*
 * Uncomment TM_USE_IGMP_FILTERING to allow IPv4 IGMP datagrams to be delivered
 * to a user-specified callback function on a per-interface basis.  These
 * callbacks can be enabled/disabled for each device however this macro must
 * be enabled before any IGMP filter callback processing logic is processed.
 */
/* #define TM_USE_IGMP_FILTERING */

/*
 * Uncomment TM_USE_IGMP_FILTERING_CONTIGUOUS_DATA, if you already have
 * uncommented TM_USE_IGMP_FILTERING, and if you wish to peek at the data in
 * the user-specified call back routine. In that case the entire IGMP header
 * will be contiguous.
 */
/* #define TM_USE_IGMP_FILTERING_CONTIGUOUS_DATA */

/*
 * Uncomment TM_IGMP_REPORT_LOCAL_MCAST if you want the Treck stack to send
 * an IGMP report when a socket joins a local multicast group.
 * Normally, a network switch will forward local multicast packets
 * unconditionally but switches that are designed to reduce network
 * congestion may need notification of all multicast memberships.
 * Note that the "all nodes" address, 224.0.0.1, is a special case and does
 * not send a report.
 */
/* #define TM_IGMP_REPORT_LOCAL_MCAST */

/*
 * Uncomment TM_USE_LBCAST_CONFIG to provide dynamic configuration of IPv4
 * Limited Broadcasting through the use of the TM_OPTION_IP_LBCAST_ENABLE
 * option to tfSetTreckOptions.
 */
/* #define TM_USE_LBCAST_CONFIG */

/*
 * Uncomment TM_USE_ECHO_CONFIG to provide dynamic configuration of IPv4
 * ICMP Echo Reples through the use of the TM_OPTION_ICMP_ECHO_ENABLE
 * option to tfSetTreckOptions.
 */
/* #define TM_USE_ECHO_CONFIG */

/*
 * Uncomment TM_USE_TCP_REXMIT_CONTROL to provide dynamic control of the
 * TCP Retransmission timer (pause, resume, reset).
 */
/* #define TM_USE_TCP_REXMIT_CONTROL */

/* Uncomment TM_USE_TCP_REXMIT_TEST to provide a Treck Demo toggle button
 * that provides for controlling whether TCP packets are dropped or processed
 */
/* #define TM_USE_TCP_REXMIT_TEST */

/* Uncomment TM_USE_IFNAMEINDEX to include support for RFC2553 functions
 * if_nameindex() and if_freenameindex().
 */
/* #define TM_USE_IFNAMEINDEX */

/* If you define TM_OPTIMIZE_SPEED, socket tuple comparisons will not use
 * tm_memcmp(), by default.
 * Uncomment TM_DISABLE_FAST_TUPLE_CMP to force the use of tm_memcmp() when
 * comparing socket tuples.
 * One or more socket tuple comparisons are done for each received packet.
 * If you have not defined TM_USE_CLIB, tm_memcmp() will impact performance.
 */
/* #define TM_DISABLE_FAST_TUPLE_CMP */

/* Uncomment TM_USE_FAST_TUPLE_CMP_STRICT if you are using fast socket tuple
 * comparison (see TM_DISABLE_FAST_TUPLE_CMP above) and your compiler does
 * not resolve comparison expressions to integer 0 for false and 1 for true.
 * This will slow down socket tuple comparisons by requiring the use of
 * TM_STRCMP_LESS, TM_STRCMP_GREATER and TM_STRCMP_EQUAL for result values.
 */
/* #define TM_USE_FAST_TUPLE_CMP_STRICT */

/* Enable only one of the following to choose the file system */
/* #define TM_USE_DOS_FS */
/* #define TM_USE_RAM_FS */
/* #define TM_USE_ROM_FS */

/* preconfigured Win32 projects */
/* #define TM_TRECK_DEMO */
/* #define TM_AUTO_TEST */

/*
 * RTOS/Kernel Macros
 */

/* #define TM_KERNEL_WIN32_X86 */
/* #define TM_KERNEL_VISUAL_X86 */
/* #define TM_KERNEL_VISUAL_X86_64 */
/* #define TM_KERNEL_LINUX_APP */
/* #define TM_KERNEL_ELX_86 */
/* #define TM_KERNEL_UCOS_CPU32 */
/* #define TM_KERNEL_UCOS_X86 */
/* #define TM_KERNEL_UCOS_PPC */
/* #define TM_KERNEL_UCOS_MIPS */
/* #define TM_KERNEL_AMX_CPU32 */
/* #define TM_KERNEL_AMX_X86 */
/* #define TM_KERNEL_DOS_X86 */
/* #define TM_KERNEL_THREADX_ARM7 */
/* #define TM_KERNEL_THREADX_CPU32 */
/* #define TM_KERNEL_NONE_EZ80 */
/* #define TM_KERNEL_RZK_EZ80 */
/* #define TM_KERNEL_UCOS_XSCALE */
/* #define TM_KERNEL_NONE_H8S */
/* #define TM_KERNEL_UCOS_SH2 */
/* #define TM_KERNEL_CMX_C16X */
/* #define TM_KERNEL_REALOS_FR */
/* #define TM_KERNEL_TI_DSP_BIOS */
/* #define TM_KERNEL_QUADROS */
/* #define TM_KERNEL_NONE_S56XX */
/* #define TM_KERNEL_NONE_XILINX_MICROBLAZE */
/* #define TM_KERNEL_NONE_XILINX_POWERPC */
/* #define TM_KERNEL_NONE_RCM3200 */

/*
 * Do we have seperate tasks for processing receive or send complete
 */

/*
 * Received packets are processed in a seperate Receive task
 * This all depends on how we setup our device driver and if we
 * are using mode 2 or mode 4 (see below)
 */
/* #define TM_TASK_RECV */

/*
 * By default, packets are sent in the context of the application
 * sending the data, or of the timer task for retransmission of data,
 * or of the receive task for TCP acks, or PING echo replies for
 * example. If you wish to use a separate transmit task to
 * send the data to the driver, then define TM_TASK_XMIT.
 */
/* #define TM_TASK_XMIT */

/*
 * When a send complete occurs, we process it in a seperate task
 * This all depends on how we setup our device driver and if we
 * are using mode 2 or mode 4 (see below)
 */
/* #define TM_TASK_SEND */

/*
 * Device driver macros
 */

/* #define TM_QUICC */


/*
 * Compiler macros to take advantage on inline assembly (when needed)
 */

/* #define TM_COMPILER_SDS */     /* The SDS Crosscode Compiler for 68K */
/* #define TM_COMPILER_DDI_PPC */ /* The Diab Data Compiler for the PPC */
/* #define TM_COMPILER_GHS_PPC */ /* The Green Hills Compiler for the PPC */
/* #define TM_COMPILER_MRI_68K */ /* The MRI Compiler for 68K           */
/* #define TM_COMPILER_GHS_ARM */ /* The Green Hills Compiler for the ARM */
/* #define TM_COMPILER_GHS_68K */ /* The Green Hills Compiler for the 68K */
/* #define TM_COMPILER_GNU_PPC */ /* GNU GCC Compiler for the PPC */
/* #define TM_COMPILER_CW_5282 */ /* Metrowerks CodeWarrior for Motorola 5282*/

/*
 * Define this macro, if compiler cannot handle nested braces
 * in the constant initialization of in6_addr structure
 * (trsocket.h/trglobal.h/trinit.c)
 */
/* #define TM_IN6ADDR_NO_NESTED_BRACES */
/*
 * Define this macro, if compiler cannot handle nested braces
 * in the constant initialization of tlFtpdCmdArray array (trftpd.c)
 */
/* #define TM_NO_NESTED_BRACES */

/*--------------------------------------------------------------------------*/

/*
 * The following macros are primitives that can be turned on/off to suite
 * your design (use these if you do NOT use the RTOS macros)
 */

/*
 * Processor Macros
 */
/* #define TM_EZ80 */
/* #define TM_INTEL_X86 */
/* #define TM_INTEL_XSCALE */
/* #define TM_MOTOROLA_CPU32 */
/* #define TM_MOTOROLA_68K */
/* #define TM_MOTOROLA_COLDFIRE */
/* #define TM_MOTOROLA_PPC */
/* #define TM_TMS320_C3 */
/* #define TM_TMS320_C3_BIG_ENDIAN */ /* For TI C3 like DSP with byte order reversed */
/* #define TM_TMS320_C5 */
/* #define TM_TMS320_C6 */

/*
 * Processor int size
 */

/*
 * Uncomment to avoid compiler warnings, if your processor integer size is
 * 16-bit
 */
/* #define TM_INT_LE16 */


/*
 * Word Order
 */

/* #define TM_LITTLE_ENDIAN */

/* To perform internal checking for the Treck Stack */
#define TM_ERROR_CHECKING

/*
 * Number of milliseconds per tick
 */
/* #define TM_TICK_LENGTH  10 */

/*
 * Uncomment TM_DISABLE_TIMER_CACHE if you have limited data space,
 * and do not plan on having a lot of sockets, routes, IPSEC SAs, and
 * therefore won't have a lot of timers.
 * In that case the timer code will just use one active timer queue, and won't
 * use a timer wheel for timers set to expire within TM_TIM_MAX_WHEEL_INTV ms.
 * NOTE: The timer execute thread will use more CPU time if this macro is
 * defined.
 * NOTE: If TM_OPTIMIZE_SIZE is defined, the timer cache is already disabled.
 */
/* #define TM_DISABLE_TIMER_CACHE */

/*
 * If you have not uncommented TM_DISABLE_TIMER_CACHE, i.e. are using the
 * timer wheel, you may uncomment TM_USE_TIMER_MULT_ACTIVE_LIST, if you will
 * need a lot of timers, but do not have enough memory to extend the timer
 * wheel. In that case you can keep the timer wheel relatively small, and
 * will have four active lists (instead of one).
 */
/* #define TM_USE_TIMER_MULT_ACTIVE_LIST */

/*
 * Power save macro:
 * Uncomment TM_USE_TIMER_CB if you want to avoid calling
 * tfTimerUpdate/tfTimerExecute periodically, and would rather
 * have the stack call a user defined CB function (registered when the
 * user calls tfRegisterTimerCB()) that lets the user know when to call
 * tfTimerExecute() next.
 * In that case, the user is responsible for updating tvTime, and
 * tvTimeRollOver prior to calling tfTimerExecute().
 * NOTE: cannot uncomment TM_DISABLE_TIMER_CACHE for this to work.
 * NOTE: For power save mode, it is best to also define
 *       TM_USE_TIMER_MULT_ACTIVE_LIST, if the timer wheel is relatively
 *       small
 */
/* #define TM_USE_TIMER_CB */


/*
 * Power save macro:
 * Uncomment TM_USE_TIMER_INTERVAL_QUERY if the user wants to query
 * the stack (tfTimerIntervalQuery()) for the interval before the next call
 * to tfTimerExecute() before going into power save mode.
 * The user is responsible for updating tvTime, and tvTimeRollOver prior
 * to calling tfTimerExecute(), and tfTimerIntervalQuery().
 */
/* #define TM_USE_TIMER_INTERVAL_QUERY */


/*
 * Uncomment TM_USE_TCP_INCOMING_CB if you want to enable code that
 * can provide socket specific notification of valid incoming TCP
 * packets.
 * When enabled, the user can call tfRegisterSocketPacketCB() to
 * install a function on a particular TCP streaming socket that will
 * be called once for every valid incoming packet that is destined
 * for that socket.
 */
/* #define TM_USE_TCP_INCOMING_CB */

/*
 * Uncomment TM_USE_SOCKET_IMPORT if you want to enable code that
 * can create a new connected socket from information provided
 * by the user.
 */
/* #define TM_USE_SOCKET_IMPORT */


/*
 * Mode 1:
 * Treck TCP/IP is used without an RTOS or Kernel
 */
/* #define TM_TRECK_NO_KERNEL */

/*
 * Mode 2:
 * Treck TC/IP is used as a shared library on a non-preemptive RTOS
 */
/* #define TM_TRECK_NONPREEMPTIVE_KERNEL */

/*
 * Mode 3:
 * Treck TCP/IP is used as an independent task on an RTOS
 * (preemptive or nonpreemtive)
 */
/* #define TM_TRECK_TASK */

/*
 * Mode 4:
 * Treck TCP/IP is used as a shared library on a premptive kernel
 */
/* #define TM_TRECK_PREEMPTIVE_KERNEL */

#ifdef  TM_TRECK_DEMO
#define TM_TCP_DEF_INCOMING_CHECKSUM         0
/*
 * Predefined Kernel Macros
 */
#define TM_USE_LOGGING_LEVELS
#define TM_LOG_ENB_ALL_LEVELS
#define TM_LOG_ENB_ALL_MODULES
#define TM_DEBUG_LOGGING

#define TM_USE_TCP_REXMIT_CONTROL
#define TM_USE_TCP_REXMIT_TEST
#ifdef TM_USE_ECHO_CONFIG
#define TM_ICMP_DEF_ECHO_ENABLE 1
#endif /* TM_USE_ECHO_CONFIG */
#ifdef TM_USE_LBCAST_CONFIG
#define TM_IP_DEF_LBCAST_ENABLE 0
#endif /* TM_USE_LBCAST_CONFIG */

#define TM_PROBE_INTERVAL   100
#define TM_MAX_PROBE        2
#ifndef TM_ERROR_CHECKING
#define TM_ERROR_CHECKING
#endif /* TM_ERROR_CHECKING */
#define TM_TRACE_LOGGING
#define TM_ERROR_LOGGING
#define TM_USE_TIMER_CB
#define TM_USE_REUSEADDR_LIST
#define TM_USE_REUSEPORT
#define TM_LOOP_TO_DRIVER
#define TM_KERNEL_WIN32_X86
#define TM_USE_NETSTAT
#define TM_USE_IPV6
#define TM_USE_IPV4
#ifndef TM_USE_RAM_FS /* not enough room in RAM FS for pcap file */
#define TM_USE_SNIFF
#endif /* TM_USE_RAM_FS */
#define TM_APP_CREATE_TIMER_THREAD
#define TM_USE_TEST_POINTS
#define TM_USE_HTTPD
#define TM_USE_HTTPC
#define TM_USE_HTTPD_CGI
#define TM_USE_HTTPD_SSI
#define TM_USE_FTPD_SSL
/* All three IKE macros may be defined */
/* For global IKE */
/* To allow IKEv1 to be used */
#define TM_USE_IKE1
/* To allow IKEv2 to be used */
/* #define TM_USE_IKE2 */
/* If this macro is not defined, the old parser will be used */
/* #define TM_USE_PARSER2 */
/* Choose the version of IPsec to use, TM_USE_IPSEC1 and TM_USE_IPSEC2 may
 * not be defined at the same time
 */
/* Use the old IPsec */
#define TM_USE_IPSEC1
/* Use enhanced IPsec */
/* #define TM_USE_IPSEC2 */
#ifdef _DEBUG
#define TM_IKE_PHASE1_NULL_ENCRYPT
#define TM_IKE_PHASE1_REKEYING_TEST
#define TM_IKE_DEBUG
#else /* _DEBUG */
#ifdef TM_ERROR_CHECKING
/* undef TM_ERROR_CHECKING so that we don't generate memoryleak.dat */
#undef TM_ERROR_CHECKING
#endif /* TM_ERROR_CHECKING*/
#endif /* _DEBUG */
#define TM_SNMP_VERSION     2
#define TM_SNMP_CACHE
#define TM_IGMP
/* SHA-384 and SHA-512 require TM_AALG_VAR_BLOCK_SIZE. */
#define TM_AALG_VAR_BLOCK_SIZE
#define TM_USE_SHA384
#define TM_USE_SHA512

#endif /* TM_TRECK_DEMO */


#ifdef  TM_AUTO_TEST
//#define TM_USE_RAM_FS
//#define TM_USE_ROM_FS
//#define TM_DISABLE_TIMER_CACHE
//#define TM_USE_TIMER_CB
#define TM_USE_STOP_TRECK
#define TM_USE_IFNAMEINDEX
#define TM_USE_FILTERING
#define TM_USE_FILTERING_CONTIGUOUS_DATA
#define TM_6_USE_FILTERING
#define TM_6_USE_FILTERING_CONT_DATA
#define TM_6_USE_IP_FORWARD
#define TM_USE_TIMER_INTERVAL_QUERY
#define TM_6_DEBUG_DHCP
#define TM_6_DHCP_USE_RAPID_COMMIT
#define TM_6_DHCP_USE_CONF_OPEN
#define TM_6_USE_FAST_TEMP_BOOT
#define TM_6_DAD_ALLOW_NO_WAIT
#define TM_6_USE_TEMPADDR
//#define TM_6_PREFER_TEMPADDR
//#define TM_DISABLE_DHCP_SEND_OVERLOAD
#define TM_USE_DHCP_DOMAIN_SEARCH
//#define TM_USE_DNS_DOMAIN_SEARCH
#define TM_DNS_USE_SRV
#define TM_USE_LOGGING_LEVELS
#define TM_LOG_ENB_ALL_LEVELS
#define TM_LOG_ENB_ALL_MODULES
#define TM_TRACE_LOGGING
#define TM_DEBUG_LOGGING
#define TM_ERROR_LOGGING
#define TM_IGMP
#define TM_LOCK_NEEDED
#define TM_DEV_SEND_OFFLOAD
#define TM_DEV_RECV_OFFLOAD
#define TM_SNMP_CACHE
#define TM_MULTIPLE_CONTEXT
#define TM_KERNEL_VISUAL_X86
//#define TM_KERNEL_VISUAL_X86_64
//#define TM_DISABLE_FAST_TUPLE_CMP
//#define TM_USE_FAST_TUPLE_CMP_STRICT
#define TM_USE_REUSEADDR_LIST
#define TM_USE_REUSEPORT
//#define TM_USE_UDP_LOOKUP_PERF
//#define TM_BCAST_RECV_ALL_LOCAL_ADDR
#define TM_USE_NETSTAT
#ifndef TM_USE_RAM_FS /* not enough room in RAM FS for pcap file */
#define TM_USE_SNIFF
#endif /* TM_USE_RAM_FS */
#define TM_USE_TEST_POINTS

/*
 * If TM_USE_CRYPTO_TEST is defined, tests will be run on the following
 * crypto algorithms, if defined:
 *
 * SHA-256 Hash and HMAC tests      TM_USE_SHA256
 * SHA-384 Hash and HMAC tests      TM_USE_SHA384
 * SHA-512 Hash and HMAC tests      TM_USE_SHA512
 * AES-XCBC-MAC Hash test           (TM_USE_AESXCBC && TM_USE_AES)
 * AES-CBC Encryption test          TM_USE_AES
 * AES-CTR Encryption test          TM_USE_AES
 */
#define TM_USE_CRYPTO_TEST
/*
 * Include TM_USE_FAILED_SHA_TESTS to run tests that need extra bits,
 * which are currently not supported
 */
/* #define TM_USE_FAILED_SHA_TESTS */

#define TM_USE_SEC_STAT
/* To allow IKEv1 to be used */
#define TM_USE_IKE1
/* To allow IKEv2 to be used */
/* #define TM_USE_IKE2 */
/* If this macro is not defined, the old parser will be used */
/* #define TM_USE_PARSER2 */
/* Choose the version of IPsec to use, TM_USE_IPSEC1 and TM_USE_IPSEC2 may
 * not be defined at the same time
 */
/* Use the old IPsec */
#define TM_USE_IPSEC1
/* Use enhanced IPsec */
/* #define TM_USE_IPSEC2 */
#define TM_USE_TEST_IKE_PKI
#define TM_IKE_PHASE1_REKEYING_TEST
#define TM_USE_IPV6
#define TM_6_USE_RAW_SOCKET
#define TM_USE_RAW_SOCKET
#define TM_USE_HTTPD
#define TM_USE_HTTPD_CGI
#define TM_USE_HTTPD_SSI
#define TM_USE_FTPD_SSL
#define TM_USE_SMTP_SSL
#define TM_SOC_RECV_Q_DGRAMS  30
#ifdef TM_SINGLE_INTERFACE_HOME
#undef TM_USE_IPV6
#endif /* TM_SINGLE_INTERFACE_HOME */
#ifndef TM_SINGLE_INTERFACE_HOME
#if (   defined(TM_USE_IPV4)            \
     && !defined(TM_DISABLE_PMTU_DISC)  \
     && defined(TM_USE_FILTERING)       \
     && defined(TM_USE_NETSTAT) )
#define TM_SNMP_MIB
#define TM_MAX_IPS_PER_IF       12 /* make it a multiple of 4 */
#endif /*    TM_USE_IPV4 && !TM_DISABLE_PMTU_DISC && TM_USE_FILTERING
          && TM_USE_NETSTAT */
#endif /* !TM_SINGLE_INTERFACE_HOME */
#endif /* TM_AUTO_TEST */

#ifdef  TM_KERNEL_REALOS_FR
/*
 * REALOS/FR
 * FUJITSU iTRON(ver3.0) for the MBxxxxx
 * It runs on a Fujitsu MBxxxxx platform
 */
#define TM_BIG_ENDIAN                      /* Use CPU Endian */
#define TM_TRECK_PREEMPTIVE_KERNEL         /* REAL/OS is Pre-Emptive Kernel */
#define TM_TICK_LENGTH  100                /* number of milliseconds per tick */
/*#define TM_BYPASS_ETHER_LL*/             /* Use Ethernet Module */
#define TM_TASK_RECV                       /* Use Recieve Task */
#define TM_USE_SHEAP                       /* Use Simple Heap Memory */
#ifdef  TM_USE_SHEAP
/* Simple Heap Memory Size is 256Kbyte */
#define TM_SHEAP_SIZE TM_UL(256)*TM_UL(1024)
#endif /* TM_USE_SHEAP */
#endif /* TM_KERNEL_REALOS_FR */

#ifdef TM_64BIT_LINUX_GCC
#define TM_USER_32BIT_TYPE
#define TM_USER_PTR_CAST_TO_INT
typedef unsigned int ttUser32Bit;
typedef signed int   ttUserS32Bit;
typedef uintptr_t ttUserPtrCastToInt;
#endif /* TM_64BIT_LINUX_GCC */

#ifdef TM_64BIT_WINDOWS
#define TM_USER_32BIT_TYPE
#define TM_USER_PTR_CAST_TO_INT
typedef unsigned int ttUser32Bit;
typedef signed int   ttUserS32Bit;
typedef __int64      ttUserPtrCastToInt;
#endif /* TM_64BIT_WINDOWS */

#ifdef TM_KERNEL_ELX_86
/*
 * ELX-86
 * This Kernel runs Treck TCP/IP as it's own task
 * It runs on a Intel x86 platform in Real mode
 * It also uses far memory(heap)
 */
#define TM_TRECK_TASK
#define TM_TICK_LENGTH  100 /* number of milliseconds per tick */
#define TM_INTEL_X86
#define TM_FAR far
/*
 * Define the ELX movsb for high speed copy
 */
void movsb(void TM_FAR *dest, const void TM_FAR *src, unsigned int len);
/* Use movsb for our tm_bcopy */
#define tm_bcopy(src, dest, count)  movsb( (void TM_FAR *)(dest),      \
                                           (const void TM_FAR *)(src), \
                                           (unsigned int)(count))

#endif /* TM_KERNEL_ELX_86 */

#ifdef TM_KERNEL_UCOS_XSCALE_RTASK
/*
 * uC/OS for the XSCALE Core of INTEL processors
 * uC/OS is preemptive and we use Treck TCP/IP as a shared library
 */
#define TM_KERNEL_UCOS_XSCALE
#define TM_LITTLE_ENDIAN
#define TM_USE_DRV_ONE_SCAT_SEND
#define TM_DEV_SEND_OFFLOAD
#define TM_DEV_RECV_OFFLOAD

#define TM_TICK_LENGTH  5 /* number of milliseconds per tick */
#define TM_OPTIMIZE_SPEED
/*
 * TM_ETHER_HW_ALIGN specifies what type of boundary (4 byte, 16 byte, etc)
 * the ethernet buffer is aligned on.  This is useful for devices that require
 * a DMA'ed recieve buffer to be aligned on a certain boundary.
 */
#define TM_ETHER_HW_ALIGN TM_UL(16) /* The XSCALE requires 16-byte alignment */

#define TM_BYPASS_ETHER_LL
/*
 * large heap size because of the large numbers of driver receive and
 * transmit descriptors.
 */
#define TM_SHEAP_SIZE TM_UL(512)*TM_UL(1024)
#define TM_USE_SHEAP

#endif /* TM_KERNEL_UCOS_XSCALE_RTASK */

#ifdef TM_KERNEL_UCOS_XSCALE
#define TM_TRECK_PREEMPTIVE_KERNEL
#define TM_TASK_RECV
#endif /*TM_KERNEL_UCOS_XSCALE */

#ifdef TM_KERNEL_UCOS_PPC_RTASK
/*
 * uC/OS for the PPC Core of the Motorola processors
 * PPC includes the MPC860
 * uC/OS is preemptive and we use Treck TCP/IP as a shared library
 */
#define TM_KERNEL_UCOS_PPC
#define TM_TASK_RECV
#endif

#ifdef TM_KERNEL_UCOS_PPC
#define TM_TRECK_PREEMPTIVE_KERNEL
#define TM_TICK_LENGTH  10 /* number of milliseconds per tick */
#define TM_MOTOROLA_PPC

/*
 * TM_ETHER_HW_ALIGN specifies what type of boundary (4 byte, 16 byte, etc)
 * the ethernet buffer is aligned on.  This is useful for devices that require
 * a DMA'ed recieve buffer to be aligned on a certain boundary.
 */
#define TM_ETHER_HW_ALIGN TM_UL(16) /* The MPC860 requires 16-byte alignment */

#define TM_BYPASS_ETHER_LL
/*
 * large heap size because of the large numbers of driver receive and
 * transmit descriptors.
 */
#define TM_SHEAP_SIZE TM_UL(256)*TM_UL(1024)
#define TM_USE_SHEAP
#endif /*TM_KERNEL_UCOS_PPC */

#ifdef TM_KERNEL_NP_UCOS_PPC_RTASK
/*
 * uC/OS for the PPC Core of the Motorola processors
 * PPC includes the MPC860
 * uC/OS is NON-Preemptive and we use Treck TCP/IP as a shared library
 */
#define TM_KERNEL_NP_UCOS_PPC
#define TM_TASK_RECV
#endif

#ifdef TM_KERNEL_NP_UCOS_PPC
#define TM_TRECK_NONPREEMPTIVE_KERNEL
#define TM_TICK_LENGTH  10 /* number of milliseconds per tick */
#define TM_MOTOROLA_PPC

/*
 * TM_ETHER_HW_ALIGN specifies what type of boundary (4 byte, 16 byte, etc)
 * the ethernet buffer is aligned on.  This is useful for devices that require
 * a DMA'ed recieve buffer to be aligned on a certain boundary.
 */
#define TM_ETHER_HW_ALIGN TM_UL(16) /* The MPC860 requires 16-byte alignment */
#define TM_BYPASS_ETHER_LL
/*
 * large heap size because of the large numbers of driver receive and
 * transmit descriptors.
 */
#define TM_SHEAP_SIZE TM_UL(256)*TM_UL(1024)
#define TM_USE_SHEAP
#endif /*TM_KERNEL_NP_UCOS_PPC */

#ifdef TM_KERNEL_NONE_H8S
/*
 * H8S, no kernel
 * CPU: H8S/2674R
 */
#define TM_HITACHI_H8S
#define TM_FAR
#define TM_TICK_LENGTH  10 /* number of milliseconds per tick */
#define TM_BYPASS_ETHER_LL
#define TM_USE_DRV_ONE_SCAT_SEND
#define TM_LOOP_TO_DRIVER
#define TM_USE_SHEAP
#define TM_SHEAP_SIZE TM_UL(128)*TM_UL(1024)
#define TM_TRECK_NO_KERNEL
#define TM_ETHER_POLLING_MODE
#define TM_INTERRUPT
#define TM_IGMP
#endif /*TM_KERNEL_NONE_H8S */

#ifdef TM_KERNEL_UCOS_RTASK
/*
 * uC/OS for the CPU32 Core of the Motorola 68K processors
 * CPU32 includes 68332 and 68360
 * uC/OS is preemptive and we use Treck TCP/IP as a shared library
 */
#define TM_KERNEL_UCOS_CPU32
#define TM_TASK_RECV
#endif

#ifdef TM_KERNEL_UCOS_CPU32
#define TM_TRECK_PREEMPTIVE_KERNEL
#define TM_TICK_LENGTH  10 /* number of milliseconds per tick */
#define TM_MOTOROLA_CPU32
#ifdef TM_QUICC
#ifndef TM_SOC_SEND_Q_BYTES
/* Default send queue size in bytes */
#define TM_SOC_SEND_Q_BYTES 16384
#endif /* TM_SOC_SEND_Q_BYTES */

#define TM_BYPASS_ETHER_LL
#endif /* TM_QUICC */

/*
 * large heap size because of the large numbers of driver receive and
 * transmit descriptors.
 */
#define TM_SHEAP_SIZE TM_UL(256)*TM_UL(1024)
#define TM_USE_SHEAP
#endif /*TM_KERNEL_UCOS_CPU32 */

#ifdef TM_KERNEL_NP_UCOS_RTASK
/*
 * Non Preemptive uC/OS for the CPU32 Core of the
 * Motorola 68K processors
 * CPU32 includes 68332 and 68360
 * uC/OS is non-preemptive and we use Treck TCP/IP as a shared library
 */
#define TM_KERNEL_NP_UCOS_CPU32
#define TM_TASK_RECV
#endif

#ifdef TM_KERNEL_NP_UCOS_CPU32
#define TM_TRECK_NONPREEMPTIVE_KERNEL
#define TM_TICK_LENGTH  10 /* number of milliseconds per tick */
#define TM_MOTOROLA_CPU32
#ifdef TM_QUICC
#ifndef TM_SOC_SEND_Q_BYTES
/* Default send queue size in bytes */
#define TM_SOC_SEND_Q_BYTES 16384
#endif /* TM_SOC_SEND_Q_BYTES */

#define TM_BYPASS_ETHER_LL
#endif /* TM_QUICC */
/*
 * large heap size because of the large numbers of driver receive and
 * transmit descriptors.
 */
#define TM_SHEAP_SIZE TM_UL(256)*TM_UL(1024)
#define TM_USE_SHEAP
#endif /*TM_KERNEL_NP_UCOS_CPU32 */

#ifdef TM_KERNEL_AMX_CPU32
#define TM_TASK_RECV
#define TM_TRECK_PREEMPTIVE_KERNEL
#define TM_TICK_LENGTH  10 /* number of milliseconds per tick */
#define TM_MOTOROLA_CPU32
#ifdef TM_QUICC            /* defined in sds360cc.bat */
#ifndef TM_SOC_SEND_Q_BYTES
/* Default send queue size in bytes */
#define TM_SOC_SEND_Q_BYTES 16384
#endif /* TM_SOC_SEND_Q_BYTES */

#define TM_BYPASS_ETHER_LL
#endif /* TM_QUICC */

/*
 * large heap size because of the large numbers of driver receive and
 * transmit descriptors.
 */
#define TM_SHEAP_SIZE TM_UL(256)*TM_UL(1024)
/* Use AMX memory pool code. Do not use our SHEAP (Simple HEAP) */
#endif /*TM_KERNEL_AMX_CPU32 */


#ifdef TM_KERNEL_AMX_X86
#define TM_TASK_RECV
#define TM_TRECK_PREEMPTIVE_KERNEL
#define TM_TICK_LENGTH  55 /* number of milliseconds per tick */
#define TM_INTEL_X86
#endif /*TM_KERNEL_AMX_X86 */


#ifdef TM_KERNEL_DOS_X86
#define TM_TICK_LENGTH 55
#define TM_TRECK_NO_KERNEL
#define TM_INTEL_X86
/* #define TM_USE_SHEAP */
/* #define TM_SHEAP_SIZE TM_UL(54)*TM_UL(1024) */
/* #define TM_BYPASS_ETHER_LL */
#define TM_FAR far
#endif /* TM_KERNEL_DOS_X86 */


#ifdef TM_KERNEL_UCOS_X86
/*
 * uC/OS for the Intel Family
 * uC/OS is preemptive and we use Treck TCP/IP as a shared library
 */
#define TM_TICK_LENGTH  55 /* number of milliseconds per tick */
#define TM_TRECK_PREEMPTIVE_KERNEL
#define TM_TASK_RECV
#define TM_INTEL_X86
#define TM_OPTIMIZE_SIZE
#define TM_BYPASS_ETHER_LL
#define TM_SHEAP_SIZE TM_UL(29)*TM_UL(1024)
#define TM_USE_SHEAP
#define TM_FAR far
#endif /*TM_KERNEL_UCOS_X86 */

#ifdef TM_KERNEL_WIN32_X86
/*
 * Windows 32 for the x86 family,
 * Treck runs as multi-thread windows application.
 */
/* We now use the EMU_UNIX_FS instead */
/* To detect memory leaks when memory is allocated using tm_kernel_malloc */
#define tm_kernel_free(memPtr)  tm_free_raw_buffer(memPtr)
#define tm_kernel_malloc        tm_get_raw_buffer
#define TM_USE_EMU_UNIX_FS
#define TM_RT_TIMER_RESOLUTION TM_UL(1000) /* interop test: 1 sec resolution */
#define TM_TICK_LENGTH  10 /* number of milliseconds per tick */
#define TM_TRECK_PREEMPTIVE_KERNEL
#define TM_TASK_RECV
#define TM_LITTLE_ENDIAN
#define TM_X86_ASM_SWAP
#define TM_OPTIMIZE_SPEED
#define TM_BYPASS_ETHER_LL
#define TM_SHEAP_SIZE   TM_UL(512)*TM_UL(1024)
#define TM_USE_SHEAP
/* To check for memory corruption */
#define TM_SHEAP_MARK_MEMORY
/* To check for end of allocated memory overwrite */
#define TM_DISABLE_DYNAMIC_MEMORY
#define TM_BSD_CLASH
#define TM_FAR
#define TM_USE_CLIB
#undef TM_INDRV_INLINE_SEND_RECV
#endif /* TM_KERNEL_WIN32_X86 */


#ifdef TM_KERNEL_VISUAL_X86_64
#ifndef TM_KERNEL_VISUAL_X86
#define TM_KERNEL_VISUAL_X86
#endif /* !TM_KERNEL_VISUAL_X86 */
#endif /* TM_KERNEL_VISUAL_X86_64 */

#ifdef TM_KERNEL_VISUAL_X86
/*
 * Loop back testing using Microsoft Visual C++
 */
/* To check for end of allocated memory overwrite */
#define TM_DISABLE_DYNAMIC_MEMORY
#ifdef TM_DISABLE_DYNMIC_MEMORY
/* To detect memory leaks when memory is allocated using tm_kernel_malloc */
#define tm_kernel_free(memPtr)  tm_free_raw_buffer(memPtr)
#define tm_kernel_malloc        tm_get_raw_buffer
#endif /* TM_DISABLE_DYNMIC_MEMORY */
#define TM_USE_EMU_UNIX_FS
#define TM_FAR
#define TM_TICK_LENGTH  10 /* number of milliseconds per tick */
#define TM_TRECK_TASK /* Turbo Treck run in a single task */
#define TM_OPTIMIZE_SPEED
#define TM_LITTLE_ENDIAN
#define TM_X86_ASM_SWAP
#define TM_BYPASS_ETHER_LL
#define TM_SHEAP_SIZE   TM_UL(512)*TM_UL(1024)
#define TM_USE_SHEAP
/* To check for memory corruption */
#define TM_SHEAP_MARK_MEMORY
#define TM_BSD_CLASH
#define TM_USE_CLIB
#define TM_USE_DRV_ONE_SCAT_SEND /* Allow more efficient driver send */
/* Allow incoming scattered device driver recv data */
#define TM_USE_DRV_SCAT_RECV
/*
 * More efficient IP fragmentation when device driver supports scattered
 * send
 */
#define TM_IP_FRAGMENT_NO_COPY

#ifdef TM_KERNEL_VISUAL_X86_64
#ifdef _MSC_VER
#if     _MSC_VER >= 1200    /* MSVC >= 6.0 */
#define TM_USER_64BIT_TYPE
typedef unsigned __int64        ttUser64Bit;
typedef signed   __int64        ttUserS64Bit;
typedef ttUser64Bit  TM_FAR *   ttUser64BitPtr;
typedef ttUserS64Bit TM_FAR *   ttUserS64BitPtr;
#endif /* MSVC >= 6.0 */
#endif /* _MSC_VER */
#endif /* TM_KERNEL_VISUAL_X86_64 */
#endif /* TM_KERNEL_VISUAL_X86 */

/* Linux Raw_socket Driver */
/* #define TM_KERNEL_LINUX_APP */

#ifdef TM_KERNEL_LINUX_APP
/* For swap macro definitions, Linux socket calls */
#define TM_KERNEL_LINUX
#define TM_INTEL_GNU_ASM_SWAP
#define TM_FAR
#define TM_TICK_LENGTH        10 /* number of milliseconds per tick */
#define TM_TRECK_PREEMPTIVE_KERNEL
#define TM_OPTIMIZE_SPEED
#define TM_TASK_RECV
#define TM_LITTLE_ENDIAN
#define TM_BYPASS_ETHER_LL
#define TM_SHEAP_SIZE   TM_UL(256)*TM_UL(1024)
#define TM_USE_SHEAP
#define TM_DYNAMIC_CREATE_SHEAP
#define TM_BSD_CLASH
/* following define is for SNMPD Trace*/
#define TM_DEBUG_LOGGING
#define TM_TRACE_LOGGING
#define TM_ERROR_LOGGING
#define TM_DEF_MAX_LOG_MSG_LEN 4096
#define TM_DEF_NUM_LOG_MSGS    10
#endif /* TM_KERNEL_LINUX_APP */

#ifdef TM_KERNEL_NP_NUCLEUSRTX_C3X
/*
 * Nucleus RTX for the TI TMS320C3x Family
 * Running Nucleus RTX in non-preemptive mode
 */
#define TM_TRECK_NONPREEMPTIVE_KERNEL
#define TM_TICK_LENGTH  10
#define TM_BYPASS_ETHER_LL
#endif /* TM_KERNEL_NUCLEUSRTX_C3X */

#ifdef TM_KERNEL_NONE_ARM7
/*
 * ARM7 processor, no RTOS
 */
#define TM_ARM7
#define TM_TICK_LENGTH 10
#define TM_USE_SHEAP
#define TM_SHEAP_SIZE TM_UL(128)*TM_UL(1024)
#define TM_TRECK_NO_KERNEL
#define TM_BYPASS_ETHER_LL
#endif /* TM_KERNEL_NONE_ARM7 */

#ifdef TM_KERNEL_THREADX_ARM7
/*
 * ThreadX for the ARM7
 */
#define TM_ARM7
#define TM_TICK_LENGTH 10
#define TM_TRECK_PREEMPTIVE_KERNEL
#define TM_TASK_RECV
#define TM_BYPASS_ETHER_LL
#endif /* TM_KERNEL_THREADX_ARM7 */

#ifdef TM_KERNEL_THREADX_CPU32
/*
 * ThreadX for the Motorola CPU32 core (68332 & 68360)
 */
#define TM_MOTOROLA_CPU32
#define TM_TICK_LENGTH 10
#define TM_TRECK_PREEMPTIVE_KERNEL
#define TM_TASK_RECV
#define TM_BYPASS_ETHER_LL
#endif /* TM_KERNEL_THREADX_CPU32 */

#ifdef TM_KERNEL_QUADROS
/*
 * RTXC Quadros for all targets
 *
 * The qnetcfg.h file is part of the example application
 * code located in the Quadros\Examples directory tree.
 */
#include "qnetcfg.h"
#endif /* TM_KERNEL_QUADROS */

#ifdef TM_KERNEL_TI_DSP_BIOS
/*
 * TI DSP BIOS
 */
#define TM_TICK_LENGTH 10
#define TM_TRECK_PREEMPTIVE_KERNEL
#define TM_TASK_RECV
#define TM_TASK_XMIT
#define TM_USE_CLIB
#define TM_OPTIMIZE_SIZE
#define TM_OPTIMIZE_SPEED
#define TM_BYPASS_ETHER_LL
#define TM_IP_FRAGMENT_NO_COPY
/* Default recv queue size in bytes */
#define TM_SOC_RECV_Q_BYTES  16384
/* Default send queue size in bytes */
#define TM_SOC_SEND_Q_BYTES  16384
#endif /* TM_KERNEL_TI_DSP_BIOS */

#ifdef TM_KERNEL_NONE_EZ80
/*
 * EZ80 evaluation board, no kernel
 */
#define TM_EZ80
#define TM_USE_SHEAP
#define TM_SHEAP_SIZE TM_UL(128)*TM_UL(1024)
#define TM_TRECK_NO_KERNEL
#define TM_BYPASS_ETHER_LL
#define TM_Z80L92_ASM_OCS
#endif /* TM_KERNEL_NONE_EZ80 */

#ifdef TM_KERNEL_RZK_EZ80
/*
 * EZ80 evaluation board, RZK(RTOS)
 */
#define TM_EZ80
#define TM_USE_SHEAP
#define TM_SHEAP_SIZE TM_UL(128)*TM_UL(1024)
#define TM_TRECK_PREEMPTIVE_KERNEL
#define TM_TASK_RECV
#define TM_Z80L92_ASM_OCS
#define TM_USE_KERNEL_CRITICAL_STATUS

#ifndef TM_USER_KERNEL_CRITICAL_STATUS_TYPE
#define TM_USER_KERNEL_CRITICAL_STATUS_TYPE
typedef unsigned int ttUserKernelCriticalStatus;
#endif /* TM_USER_KERNEL_CRITICAL_STATUS_TYPE */

extern unsigned int RZKDisableInterrupts(void);
extern void RZKEnableInterrupts(unsigned int interruptsMask);

#define tm_kernel_set_critical \
            tvKernelCriticalStatus = RZKDisableInterrupts()
#define tm_kernel_release_critical \
            RZKEnableInterrupts(tvKernelCriticalStatus)

#endif /*TM_KERNEL_NONE_EZ80 */


#ifdef TM_KERNEL_UCOS_MIPS
/*
 * MIPS4kc, Malta evaluation board, ucos kernel
 * gnu tools: sde-mips
 */
#define TM_KERNEL_MIPS4k
#define TM_TRECK_PREEMPTIVE_KERNEL
#define TM_TASK_RECV
#define TM_TICK_LENGTH        10
#define TM_GNUMIPS4K_ASM_CRITICAL
/* define ENDIAN in makefile for little and big */
#define TM_BYPASS_ETHER_LL
#define TM_SHEAP_SIZE   TM_UL(256)*TM_UL(1024)
#define TM_USE_SHEAP
#define printf tfMipsPrintf
#endif /* TM_KERNEL_UCOS_MIPS */


#ifdef TM_KERNEL_UCOS_SH2
/*
 * HITACHI SH2 Processor - uCOS-II ( big endian )
 *  SH7616 (SH2-DSP) evaluation board.
 */
#define TM_HITACHI_SH2
#define TM_TASK_RECV
#define TM_TASK_SEND
#define TM_TASK_XMIT
#define TM_TICK_LENGTH  10   /* number of milliseconds per tick */
#define TM_TRECK_PREEMPTIVE_KERNEL
#define TM_OPTIMIZE_SPEED
#define TM_BYPASS_ETHER_LL
#define TM_USE_SHEAP
#define TM_SHEAP_SIZE ( 128UL * 1024UL )
#define TM_USE_DRV_ONE_SCAT_SEND
#endif /* TM_KERNEL_UCOS_SH2 */

#ifdef TM_KERNEL_CMX_C16X
/*
 * Infineon  C166 Processor - CMX RTOS
 * Vorne 87AL board.
 */
#define TM_INFINEON_C166
#define TM_TICK_LENGTH 10
#define TM_TRECK_PREEMPTIVE_KERNEL
#define TM_BYPASS_ETHER_LL
#define TM_DISABLE_TCP_SACK
#define TM_USE_DRV_ONE_SCAT_SEND
#define TM_OPTIMIZE_SPEED

#define TM_TASK_RECV
/* #define TM_TASK_XMIT */

/* Dymanically allocate Sheap as pages of 16kbytes */
#define TM_USE_SHEAP
#define TM_DYNAMIC_CREATE_SHEAP
#define TM_SHEAP_SIZE       (TM_UL(128)*TM_UL(1024))
#define TM_SHEAP_PAGE_SIZE  (TM_UL(64)*TM_UL(1024))
#define TM_SHEAP_NUM_PAGE   (TM_SHEAP_SIZE/TM_SHEAP_PAGE_SIZE)

#define TM_FAR huge
#define TM_GLOBAL_QLF huge
#define TM_CONST_QLF huge
#define TM_INTERRUPT

#ifdef TM_ERROR_CHECKING
#undef TM_ERROR_CHECKING
#endif /* TM_ERROR_CHECKING */

#define TM_SINGLE_INTERFACE_HOME

/*inlcude the KEIL compiler library that supports huge argement type */
#include "trkeil.h"
#include <string.h>
#include <ctype.h>

#endif /* TM_KERNEL_CMX_C16X */

#ifdef TM_KERNEL_NONE_RCM3200
/*
 * Rabbit Core Module 3200, no kernel
 */
#define TM_RCM3200

#define TM_LITTLE_ENDIAN

#define TM_DNS_USE_SRV
#define TM_IGMP
#define TM_USE_IPV6
/* #define TM_USE_IPSEC */
/* #define TM_USE_IKE */

/* Prevent definition of TM_USE_SW_CRYPTOENGINE later */
#define TM_X_USE_SW_CRYPTOENGINE

/* Prevent link error in function tfMd5Transform() */
#define TM_DISABLE_TCP_128BIT_RANDOM_ISS

#define TM_TICK_LENGTH 10
#define TM_TRECK_TASK
#define TM_BYPASS_ETHER_LL
#define TM_DISABLE_TCP_SACK
#define TM_OPTIMIZE_SIZE

#define TM_USE_SHEAP
#define TM_DYNAMIC_CREATE_SHEAP
#define TM_SHEAP_SIZE       (TM_UL(30)*TM_UL(1024))
#define TM_SHEAP_PAGE_SIZE  (TM_UL(30)*TM_UL(1024))

#define TM_FAR
#define TM_CODE_FAR
#define TM_GLOBAL_QLF
#define TM_CONST_QLF
#define TM_INTERRUPT
#define TM_NEARCALL _nearcall

/* The following definitions are for debugging only */
/* #define TM_LOOP_TO_DRIVER */
/* #undef TM_INDRV_INLINE_SEND_RECV */

#ifdef TM_USE_PPP
#undef TM_USE_PPP
#endif /* TM_USE_PPP */

#ifdef TM_ERROR_CHECKING
#undef TM_ERROR_CHECKING
#endif /* TM_ERROR_CHECKING */

#include <string.h>
#include <ctype.h>

#endif /* TM_KERNEL_NONE_RCM3200 */

#ifdef TM_KERNEL_NONE_S56XX
/*
 * Stretch S56XX with no OS
 */
/* Assembly critical sections */
extern unsigned rval;
#ifndef XTSTR
#define _XTSTR(x)   # x
#define XTSTR(x)    _XTSTR(x)
#endif
#define tm_kernel_set_critical      rval = \
    ({ unsigned __tmp; \
       __asm__ __volatile__(    "rsil   %0, " XTSTR(15) "\n" \
                        : "=a" (__tmp) : : "memory" ); \
            __tmp;})
#define tm_kernel_release_critical \
    do{ unsigned __tmp = (rval); \
            __asm__ __volatile__(   "wsr    %0, " XTSTR(PS) " ; rsync\n" \
                        : : "a" (__tmp) : "memory" ); \
        }while(0)
/* Custom checksum in source\kernel\none\s56xx\checksum.c */
#define TM_CUSTOM_OCS
#define TM_USE_CLIB
#define TM_BSD_CLASH
#define TM_USE_SHEAP
#define TM_SHEAP_SIZE (TM_UL(255)*TM_UL(1024))
#define TM_DYNAMIC_CREATE_SHEAP
#define TM_SHEAP_NUM_PAGE 1
#define TM_LITTLE_ENDIAN
#define TM_TICK_LENGTH  10
#define TM_TRECK_NO_KERNEL
#endif /* TM_KERNEL_NONE_S56XX */


#ifdef TM_KERNEL_NONE_XILINX_MICROBLAZE
#define TM_TRECK_NO_KERNEL
#define TM_BSD_CLASH
#define TM_BIG_ENDIAN
#define TM_TICK_LENGTH  10
#define TM_USE_SHEAP
#define TM_SHEAP_SIZE TM_UL(4)*TM_UL(1024)*TM_UL(1024)
#define TM_OPTIMIZE_SPEED
#define TM_BYPASS_ETHER_LL
#define TM_USE_DRV_ONE_SCAT_SEND
#define TM_NEED_ETHER_32BIT_ALIGNMENT
#define TM_USE_DRV_SCAT_RECV
#define TM_ETHER_HW_TX_ALIGN 4
#define TM_DEV_SEND_OFFLOAD
/* These are for debugging */
/* #define TM_ERROR_CHECKING */
/* #define TM_DISABLE_DYNAMIC_MEMORY */
/* #define TM_SHEAP_MARK_MEMORY */
#endif /* TM_KERNEL_NONE_XILINX_MICROBLAZE */

#ifdef TM_KERNEL_NONE_XILINX_POWERPC
#define TM_TRECK_NO_KERNEL
#define TM_BSD_CLASH
#define TM_BIG_ENDIAN
#define TM_TICK_LENGTH  10
#define TM_USE_SHEAP
#define TM_SHEAP_SIZE TM_UL(4)*TM_UL(1024)*TM_UL(1024)
#define TM_OPTIMIZE_SPEED
#define TM_BYPASS_ETHER_LL
#define TM_DEV_SEND_OFFLOAD
#define TM_USE_DRV_ONE_SCAT_SEND
/* This is for debugging */
/* #define TM_ERROR_CHECKING */
#endif /* TM_KERNEL_NONE_XILINX_POWERPC */


#ifdef TM_INTEL_X86
/*
 * Intel x86
 */
#define TM_LITTLE_ENDIAN
#ifdef __BORLANDC__
/* In line assembly critical section */
#define TM_X86_ASM_CRITICAL
/* In line network byte ordering */
#define TM_X86_ASM_SWAP
/* Use assembly checksum routine */
#define TM_BORLAND_ASM_OCS
#endif /* __BORLANDC__ */
#ifdef _MSC_VER
/* In line assembly critical section */
#define TM_X86_ASM_CRITICAL
/* In line network byte ordering */
#define TM_X86_ASM_SWAP
#endif /* _MSC_VER */
#endif /* TM_INTEL_X86 */

#ifdef TM_INTEL_XSCALE
/*
 * Intel XScale (80200)
 */
#define TM_LITTLE_ENDIAN
/* Use assembly checksum routine */
#define TM_GNUXSCALE_ASM_OCS
#endif /* TM_INTEL_XSCALE */

#ifdef TM_MOTOROLA_PPC
/*
 * Motorola Power PC Core
 */
#undef TM_LITTLE_ENDIAN
#ifdef TM_COMPILER_DDI_PPC
/* In line assembly critical section */
#define TM_DDIPPC_ASM_CRITICAL
#define TM_DDIPPC_ASM_OCS
#endif /* TM_COMPILER_DDI_PPC */

#ifdef TM_COMPILER_GHS_PPC
#define TM_GHSPPC_ASM_CRITICAL
#define TM_GHSPPC_ASM_OCS
#endif /* TM_COMPILER_GHS_PPC */

#ifdef TM_COMPILER_GNU_PPC
#define TM_GNUPPC_ASM_CRITICAL
#define TM_GNUPPC_ASM_OCS
#endif /* TM_COMPILER_GNU_PPC */
#endif /* TM_MOTOROLA_PPC */

#ifdef TM_MOTOROLA_CPU32
/*
 * Motorola CPU32 Core (68332 & 68360)
 */
#undef TM_LITTLE_ENDIAN
#ifdef TM_COMPILER_SDS
/* In line assembly critical section */
#define TM_SDS68K_ASM_CRITICAL
#define TM_SDS68K_ASM_OCS
#endif /* TM_COMPILER_SDS */

#ifdef TM_COMPILER_MRI
#define TM_MRI_ASM_CRITICAL
#endif /* TM_COMPILER_MRI */

#endif /* TM_MOTOROLA_CPU32 */

#ifdef TM_COMPILER_CW_5282
/* Metrowerks CodeWarrior for Motorola 5282 (Coldfire) */
#define TM_CW5282_ASM_OCS
#endif /* TM_COMPILER_CW_5282 */

#ifdef TM_MOTOROLA_68K
/*
 * Motorola 68000 (EC) Core
 */
#undef TM_LITTLE_ENDIAN

#ifdef TM_COMPILER_SDS
#define TM_SDS68K_ASM_CRITICAL
#endif /* TM_COMPILER_SDS */

#ifdef TM_COMPILER_MRI
#define TM_MRI_ASM_CRITICAL
#endif /* TM_COMPILER_MRI */

#endif /* TM_MOTOROLA_68K */

#ifdef TM_MOTOROLA_COLDFIRE
/* Motorola Coldfire - MCF5282, MCF5485 */
#undef TM_LITTLE_ENDIAN
#define TM_ETHER_HW_ALIGN       16 /* ethernet receive buffer alignment */
#endif /* TM_MOTOROLA_COLDFIRE */

#ifdef TM_HITACHI_H8S
/*
 * Hitachi H8S
 */
#undef TM_LITTLE_ENDIAN
#endif /* TM_HITACHI_H8S */

#ifdef TM_HITACHI_SH2
/*
 * Hitachi SH2
 */
#define TM_BIG_ENDIAN
#endif /* TM_HITACHI_SH2 */


#ifdef TM_INFINEON_C166
/*
 * TM_INFINEON_C166
 */
#define TM_LITTLE_ENDIAN
#define TM_C166_OCS
#endif /* TM_INFINEON_C166 */


#ifdef TM_ARM7
/*
 * ARM7 Core
 */
#define TM_LITTLE_ENDIAN

#ifdef TM_COMPILER_GHS_ARM
#define TM_GHSARM7_ASM_CRITICAL
#define TM_GHSARM7_ASM_OCS
#endif /* TM_COMPILER_GHS_ASM */

#endif /* TM_ARM7 */




/*
 * Texas Instruments TMS320C5x Core
 */

#ifdef TM_TMS320_C6
/*
 * Texas Instruments TMS320C6000 core
 */
#define TM_USER_32BIT_TYPE
typedef unsigned int ttUser32Bit;
typedef signed int   ttUserS32Bit;

#define TM_UL(x) x##U
#define TM_L(x) x

#define TM_TI_C6000_ASM_OCS
#endif /* TM_TMS320_C6 */


#ifdef TM_EZ80
/*
 * Zilog eZ80 processor
 */
#define TM_FAR
#define TM_TICK_LENGTH  55 /* number of milliseconds per tick */
#define TM_LITTLE_ENDIAN
#endif /* TM_EZ80 */

#ifndef TM_TICK_LENGTH
#define TM_TICK_LENGTH 0
#endif /* TM_TICK_LENGTH */

#ifdef TM_USE_GENERIC_TESTER
#include <txGenericTester.h>
#endif /* TM_USE_GENERIC_TESTER */

#ifdef TM_TAHI_TESTER
#include <txTahiTester2.h>
#endif /* TM_TAHI_TESTER */

#ifdef TM_SNMP_TESTER
#define TM_SNMP_CACHE
#define TM_SNMP_TEST_SC
#ifndef TM_SNMP_TEST_SC
#define TM_SNMP_USE_CUSTOM_MIB
#define TM_USE_SNMP_EXAMPLE_MIB
#endif /* TM_SNMP_TEST_SC */
#endif /* TM_SNMP_TESTER */

#ifdef TM_USE_IPV6
/*
 * TM_6_IP_FRAGMENT macro. Enable support for IPv6 fragmentation.
 * Comment out to save code space when IPv6 fragmentation is
 * not needed.
 */
#define TM_6_IP_FRAGMENT

/*
 * TM_6_IP_REASSEMBLY macro. Enable support for IPv6 reassembly.
 * Comment out to save code space when IPv6 reassembly is
 * not needed.
 */
#define TM_6_IP_REASSEMBLY

/*
 * Disable source address selection as defined in RFC 3484
 */
/* #define TM_DISABLE_RFC3484 */

/*
 * TM_6_USE_IP_FORWARD macro. Enable IPv6 forwarding code. Comment out to save
 * code space when IPv6 forwarding is not needed.
 */
/* #define TM_6_USE_IP_FORWARD */

/* Uncomment the TM_6_IP_SRC_ERROR_CHECKING macro if you want validation of
   the source address of received IPv6 packets. */
/* #define TM_6_IP_SRC_ERROR_CHECKING */

/*
 * Uncomment the TM_6_DISABLE_PMTU_DISC macro, if you want to disable automatic
 * IPv6 Path MTU discovery.
 */
/* #define TM_6_DISABLE_PMTU_DISC */


/*
 * TM_6_USE_NUD macro. Enable IPv6 Neighbor Unreachability Detection code.
 * Comment out to save code space when IPv6 Neighbor Unreachability Detection
 * is not needed.
 */
#define TM_6_USE_NUD

/*
 * TM_6_USE_MLD macro. Enable IPv6 Multicast Listener Discovery code. Comment
 * out to save code space when IPv6 Multicast Listener Discovery is not needed.
 */
#define TM_6_USE_MLD

/*
 * TM_6_USE_MLDV2 macro. Enable IPv6 Multicast Listener Discovery Version 2
 * code. Comment out to save code space when IPv6 Multicast Listener
 * Discovery Version 2 is not needed.
 */
#define TM_6_USE_MLDV2

/*
 * TM_6_USE_MULTICAST_LOOP macro. Enable support for the IPV6_MULTICAST_LOOP
 * socket option described in RFC3493:
 *      "If a multicast datagram is sent to a group to which the sending
 *       host itself belongs (on the outgoing interface), a copy of the
 *       datagram is looped back by the IP layer for local delivery."
 * If TM_6_USE_MULTICAST_LOOP is undefined, outgoing IPv6 multicast packets
 * are never looped back unless the user's device driver explicitly does so.
 * If TM_6_USE_MULTICAST_LOOP is defined, loopback of outgoing IPv6 multicast
 * packets is controlled by the IPV6_MULTICAST_LOOP socket option, with
 * loopback being the default action (as stated in RFC3493).
 */
/* #define TM_6_USE_MULTICAST_LOOP */

/*
 * TM_USE_RFC_3590 macro.  Enable Source Address Selection for the Multicast
 * Listener Discovery (MLD) Protocol as defined in RFC 3590.
 */
/* #define TM_USE_RFC_3590 */

/*
 * TM_6_USE_DAD macro. Enable IPv6 Duplicate Address Detection code. Comment
 * out to save code space when IPv6 Duplicate Address Detection is not needed.
 */
#define TM_6_USE_DAD

/*
 * Uncomment the TM_6_DAD_ALLOW_NO_WAIT macro to allow an interface to bypass
 * the typical 1 second wait for responses when performing Duplicate Address
 * Detection.
 * Call tfInterfaceSetOptions() with the TM_6_DEV_OPTIONS_DAD_NO_WAIT option
 * to enable the option for an interface.
 * Addresses affected include the default link-local address for the interface
 * and addresses manually configured with the TM_6_DEV_IP_FAST_BOOT or
 * TM_6_DEV_IP_TEMPORARY ipv6flags.
 * Use this option after a reboot or power-off sleep to quickly resume using
 * addresses that were previously configured on the interface.
 * For faster resumption, use this option in combination with
 * macro TM_6_USE_FAST_TEMP_BOOT and tfInterfaceSetOptions() option
 * TM_6_DEV_OPTIONS_NO_INIT_DELAY.
 * (Note that option TM_6_DEV_OPTIONS_NO_INIT_DELAY eliminates the delay
 * prior to starting Duplicate Address Detection for the first time on an
 * interface.)
 * Leave this macro commented out to reduce code size and ensure RFC
 * compliance.
 */
/* #define TM_6_DAD_ALLOW_NO_WAIT */

/*
 * TM_6_USE_PREFIX_DISCOVERY macro. Enable IPv6 Prefix Discovery code, part
 * of stateless address auto-configuration. Comment out to save code space
 * when IPv6 Prefix Discovery is not needed.
 */
#define TM_6_USE_PREFIX_DISCOVERY

/*
 * TM_6_ENABLE_ONLINK_ASSUMPTION macro.
 * Neighbor Discovery for IPv6 [RFC4861] replaces [RFC2461] and removes the
 * following text from section 5.2 for reasons explained in [RFC4943]:
 *      "If the Default Router List is empty, the sender assumes that the
 *       destination is on-link."
 * Uncomment the following macro to undo this change and re-enable the
 * on-link assumption code.
 */
/* #define TM_6_ENABLE_ONLINK_ASSUMPTION */

/*
 * TM_6_USE_TEMPADDR macro. Enable [RFC4941] Privacy Extensions for Stateless
 * Address Autoconfiguration in IPv6.
 * This enables the code to allocate a temporary global address for each
 * autonomous address-configuration prefix advertised by a router (see
 * [RFC4861] section 4.6.2, Prefix Information).
 * This temporary address is distinct from and additional to the public global
 * address configured from the static interface identifier that was installed
 * manually or automatically with tf6Eui48SetInterfaceId() or
 * tf6Eui64SetInterfaceId() (see [RFC4862] section 5.5.3, Router Advertisement
 * Processing).
 * New temporary addresses are regenerated periodically (1 day by default),
 * thereby deprecating the previous address, which will still be valid for a
 * period of time (1 week by default).
 * Enable this option and bind your socket to a temporary address if you
 * want to avoid being tracked based on your static interface identifier.
 * Prerequisites: TM_6_USE_DAD and TM_6_USE_PREFIX_DISCOVERY
 */
/* #define TM_6_USE_TEMPADDR */

/*
 * Uncomment the following line to enable strict RFC 4861 conformance.
 * The only effect this has is that it prevents Treck from sending
 * Router Solicitation messages when a prefix address expires.
 */
/* #define TM_USE_RFC4861_STRICT */

/*
 * TM_6_PREFER_TEMPADDR macro. Select temporary addresses in preference
 * to other global addresses for new outbound messages.
 * By default, non-temporary addresses are preferred over temporary ones.
 * If this macro is defined, new sockets with global destinations will
 * automatically choose an appropriate temporary local address as the source
 * address in outbound packets.
 * If this macro is undefined, you must explicitly bind to a temporary
 * address or use tfSendToFrom() (or equivalent) to use it as the source
 * address.
 */
/* #define TM_6_PREFER_TEMPADDR */

/*
 * Uncomment macro TM_6_USE_DHCP to enable the Treck DHCPv6 client.
 * You may also wish to define macro TM_6_MAX_DHCP_IPS_PER_IA to be the
 * maximum number of DHCPv6 assigned addresses per interface (default: 4).
 * Leave it commented out to save code space.
 */
/* #define TM_6_USE_DHCP */

/*
 * Uncomment macro TM_6_DHCP_USE_FQDN to enable the DHCPv6 FQDN option.
 * You may also wish to define macro TM_6_DHCP_FQDN_MAX_ASCII_LEN to be the
 * maximum storage for a FQDN received from the server (default: 256 bytes).
 * Leave it commented out to save code space.
 * Requires macro TM_6_USE_DHCP.
 */
/* #define TM_6_DHCP_USE_FQDN */

/*
 * Uncomment macro TM_6_DHCP_USE_AUTH to enable DHCPv6 authentication.
 * Leave it commented out to save code space.
 * Requires macro TM_6_USE_DHCP.
 */
/* #define TM_6_DHCP_USE_AUTH */

/*
 * Uncomment the TM_6_DHCP_USE_RAPID_COMMIT macro to enable support for the
 * DHCPv6 Rapid Commit option ([RFC 3315] section 22.14).
 * To enable the Rapid Commit option on an interface, you must also call
 * tfInterfaceSetOptions() to set option TM_6_DEV_OPTIONS_DHCP_RAPID_CMT.
 * Leave this macro commented out to reduce code size.
 * Requires macro TM_6_USE_DHCP.
 */
/* #define TM_6_DHCP_USE_RAPID_COMMIT */

/*
 * Uncomment the TM_6_DHCP_USE_CONF_OPEN macro to enable support for fast
 * DHCPv6 reboot using a Confirm/Reply message exchange.
 * Call tf6DhcpSetAddrOption() or tf6DhcpSetBootEntry() to set the addresses
 * that were previously autoconfigured on the interface by DHCPv6 prior to
 * the reboot. Then, call tfNgOpenInterface() with ipv6flags set to
 * (TM_6_DEV_USER_DHCP | TM_6_DEV_USER_DHCP_CONF_OPEN) to open the interface
 * and start DHCPv6 with a Confirm message containing the preferred addresses
 * you set via tf6DhcpSetAddrOption() or tf6DhcpSetBootEntry().
 * Leave this macro commented out to reduce code size.
 * Requires macro TM_6_USE_DHCP.
 */
/* #define TM_6_DHCP_USE_CONF_OPEN */

/*
 * Uncomment the TM_6_USE_FAST_TEMP_BOOT macro to enable support for fast
 * stack startup using manually configured temporary IPv6 addresses.
 * Call tfNgOpenInterface() with the TM_6_DEV_IP_FAST_BOOT ipv6flag to
 * enable the option for an interface and set a temporary address
 * (the TM_6_DEV_IP_TEMPORARY flag is also set automatically).
 * The temporary addresses set with this option are expected to be confirmed
 * and replaced in time by address autoconfiguration via DHCPv6 or Router
 * Advertisement Prefix Information.
 * Use this option after a reboot or power-off sleep to quickly resume using
 * addresses that were previously configured on the interface.
 * For faster resumption, use this option in combination with
 * macro TM_6_DAD_ALLOW_NO_WAIT and tfInterfaceSetOptions() options
 * TM_6_DEV_OPTIONS_NO_INIT_DELAY and TM_6_DEV_OPTIONS_DAD_NO_WAIT.
 * Leave this macro commented out to reduce code size.
 */
/* #define TM_6_USE_FAST_TEMP_BOOT */

/*
 * TM_6_USE_MIP_CN macro. Enable Mobile IPv6 correspondent node code.
 * Comment out to save code space when Mobile IPv6 correspondent node
 * functionality is not needed.
 */
/* #define TM_6_USE_MIP_CN */

/*
 * TM_6_USE_MIP_MN macro. Enable Mobile IPv6 mobile node code. Comment out
 * to save code space when Mobile IPv6 mobile node functionality is not
 * needed.
 */
/* #define TM_6_USE_MIP_MN */

/*
 * TM_6_MIP_DRAFT24 macro. Use Mobility Header protocol ID and ICMPv6
 * message types per draft-ietf-mobileip-ipv6-24.txt, rather than IANA
 * assignments.
 */
/* #define TM_6_MIP_DRAFT24 */

/*
 * TM_6_USE_MIP_HA macro. Enable Mobile IPv6 home agent code. Comment out
 * to save code space when Mobile IPv6 mobile node functionality is not
 * needed.
 * NOTE: As of IPv6 phase II release, this is only a HA lite that dones't
 *       implement the whole functionality of a MIP6 home agent
 */
/* #define TM_6_USE_MIP_HA */

/*
 * TM_6_USE_MIP_RO macro. Enable Mobile IPv6 route optimization. Comment
 * out to save code space when Mobile IPv6 route optimization is not needed.
 * ([MIPV6_18++].R14.4.5:10, [MIPV6_18++]R14.4.5:20)
 */

/*
 * TM_6_MN_DISABLE_HOME_DETECT macro. Disable Mobile IPv6 Mobile Node home
 * detection/return to home functionality. If you know that the mobile node
 * never returns home, then you can define this macro to save some code
 * space.
 */
/* #define TM_6_MN_DISABLE_HOME_DETECT */

/*
 * TM_6_USE_MIP_RA_RTR_ADDR macro. When enabled, the mobile node uses the
 * Router Address option (when available) in received Router Advertisement
 * messages to determine if a Router Advertisement is from the current
 * default router.
 */

#endif /* TM_USE_IPV6 */


/*
 * For phase 1 negotiation, Elmic IKE supports digital signature
 * authentication method. It includes RSA/DSA algorithm, PEM/DER
 * certification, X509v3 and ASN1 format, multi CA and CRL. TM_USE_PKI
 * macro shoule be defined in order to use this part. Whenever you define
 * TM_USE_SSL_CLIENT or TM_USE_SSL_SERVER, this macro is automatically
 * defined
 */
/* #define TM_USE_PKI */







/*
 * SSL TLS options
 */
/* Uncomment the following macro if user doesn't want SSL 3.0 */
#define TM_USE_SSL_VERSION_30

/* Uncomment the following macro if user doesn't want SSL 3.1, i.e TLS 1.0 */
#define TM_USE_SSL_VERSION_31

/* uncomment the following macro if you don't want to accept SSL 2.0 hello */
#define TM_SSL_ACCEPT_20_CLIENTHELLO
/* If the following macro is defined, upon receiving close_notify, we will
 * immediately flush our send queue and send back close_notify to the peer,
 * and shutdown SSL send path. If this macro is not defined, it is up to the
 * user to call tfSslConnectUserClose or tfClose to shutdown the SSL send
 * path. Note that, if user doesn't call anything, the SSL send path is
 * still ON until the socket is closed.
 */
#define TM_SSL_IMMEDIATE_CLOSE_NOTIFY

/* The minimum user data bytes to TRIGGER SSL send. Data less than this size
 * will not trigger SSL send, instead, it will be queued.  Once SSL send
 * has been triggered up, all pending user data will be sent out and after
 * that SSL waits for the next trigger event to send again. The default value
 * is set to zero, ie, SSL wont queue any packet. If user chooses to set it
 * to something else, user should be aware that if application data is smaller
 * than this threshold, it won't be sent out unless user flush the channel
 * by calling tfSslUserSendFlush()
 */
#define TM_SSL_SEND_DATA_MIN_SIZE                0

/* The maximum value of user data in one single SSL record. By RFC, this value
 * is 16384. However, considering that peer may not have enough receive buffer
 * to queue, we use the following value (8000). So if user wants to send more
 * than 8000 bytes of data, see 8100 bytes, we have to cut it into two SSL
 * records, one contains 8000 user data bytes, another one contains 100 user
 * data bytes (Note that even if 100 is less than TM_SSL_SEND_DATA_MIN_SIZE,
 * we still send it out, because we used 8100 bytes to trigger up SSL send.)
 */
#define TM_SSL_SEND_DATA_MAX_SIZE                8000

/* uncomment the following macro, if you don't want to use any ephemeral
 * Diffie-Hellman key exchange method. For example, if your SSL cipher suite
 * is something like SSL_RSA_XXXX or TLS_RSA_XXXX (The most popular case in
 * real world), you don't need this macro.
 */
#define TM_SSL_USE_EPHEMERAL_DH

/* uncomment the following macro if you don't want do mutual authentication*/
#define TM_SSL_USE_MUTUAL_AUTH

/* If you don't define TM_EXPORT_RESTRICT, you may want to reject any
 * exportable cipher suites by defining the following macro. Note that,
 * by defining the following macro, you get higher security because you
 * reject any exportable cipher suite, the cost is that you may not be
 * able to negotiation with clients which offer exportable cipher suites
 * only. If you do define TM_EXPORT_RESTRICT, this macro has no effect
 * to the behavior. Default not to be defined
 */
/*#define TM_SSL_REJECT_EXPORTABLE_CIPHER*/

/* uncomment the following macro only if 1) you want to negotiate EDH_DSS_XXX
 * cipher 2) negotiate with Netscape only 3) in SSL version 3.0 version only.
 * If any of these three conditions is false, don't uncomment this macro.
 * The description of how to encode DSS signature in the SSLv3 specification
 * is insufficiently specific and Netscape interprets it differently from most
 * other vendors. Instead of DER encoding r and s, Netscape merely
 * concatenates them into a single 40-byte field. Thus, although Netscape
 * implements DSS for client authentication, it is not interoperable with
 * other implementations. Despite widespread agreement on the "right thing"
 * Netscape has refused to change their implementation, claiming that it
 * complies with the SSL v3 specification and citing installed base. The TLS
 * specification clears up this issue; ALL TLS implementations must DER
 * encode DSS signature
 */
/* #define TM_SSL30_DSSSIGN_NETSCAPE_FORMAT */

/*The following Diffie-Hellman parameters take effect only if Ephemeral Diffie
 * hellman is enabled and is chosen as the key exchange method.
 */

/* if you don't have export restrict, we use OAKLEY group 1 prime
 * (768 bits)if Ephemeral Diffie-Hellman is going to be used. TM_
 * DHGROUP_2 is 1024 bits, and TM_DHGROUP_EXPORT is 512 bits. According
 * to draft draft-ietf-tls-56-bit-ciphersuites-01.txt, Changes in US export
 * regulations in 1999 permitted the export of software programs
 * using 56-bit data encryption and 1024-bit key exchange
 */
#define TM_SSL_DHE_PRIME_GROUP             TM_DHGROUP_1

/* Diffie-Hellman generator is 2 */
#define TM_SSL_DHE_GENERATOR               TM_DH_GENERATOR_2

/* Diffie-Hellman private secret default size*/
#define TM_SSL_DHSECRET_DEFAULT_SIZE       32

/*
 * In Treck releases prior to 5.0.1.40, Treck did not strip the leading zeros
 * off of the padded Diffie-Hellman shared secret before performing the hash.
 * This caused hash mismatches between peers on rare occasions where the
 * shared secret length was != to the prime length. These hash mismatches were
 * recoverable but required a new SSL negotiation to take place.
 * This macro is here for interoperability with old versions.
 * This macro only has an effect when TM_USE_DIFFIEHELLMAN_PADDING is defined.
 */
/* TM_SSL_DH_HASH_WITH_PADDING */

/* Uncomment the following macro if the client allows no certificate
 * operation even in client-authentication situation. If the macro is
 * defined, the SSL_CLIENT will ignore Cert_Request message if it
 * doesn't have any certificate, and continue normal SSL negotiation.
 * To close the connection or not will be up to the server to decide.
 * In any case the client will send an alert-warning message to server.
 */
/* #define TM_SSL_CLIENT_ALLOW_NO_CERT */

/*
 * Uncomment the following line if you want to disable
 * the client-side secure renegotiation code.
 * This will force Treck to act as an un-upgraded (legacy) client.
 * This is highly discouraged and should only be used to target specific
 * cases where renegotiation is required and the server is unable to
 * handle upgraded clients.
 */
/* #define TM_SSL_DISABLE_CLIENT_SEC_RENEG */

/*
 * Uncomment the following line if you want to disable
 * the server-side secure renegotiation code.
 * This will force Treck to act as an un-upgraded (legacy) server.
 * This is highly discouraged and should only be used to target specific
 * cases where renegotiation is required and the client is unable to
 * handle upgraded servers.
 */
/* #define TM_SSL_DISABLE_SERVER_SEC_RENEG */

/*
 * Uncomment the following line, if you want to use C library routines,
 * instead of the equivalent library routines provided by the Turbo Treck
 * stack.
 */
/* #define TM_USE_CLIB */

#ifdef TM_USE_CLIB
/* NOTE: you may need to modify the following, if you #define TM_USE_CLIB
 *
 * For isupper, tolower ... */
#include <ctype.h>
/* For memcpy, strchr ...   */
#include <string.h>
/* For printf, sprintf...   */
#include <stdio.h>
/* For strtoul... */
#include <stdlib.h>
#endif /* TM_USE_CLIB */

/*
 * if TM_USE_SNIFF is defined, interface drivers will dump the packets to the
 * file system in libpcap format, to be opened by tcpdump, windump, ethereal,
 * or other libpcap file readers.
 */
#ifndef TM_USE_RAM_FS /* not enough room in RAM FS for pcap file */
/* #define TM_USE_SNIFF */
#endif /* TM_USE_RAM_FS */


#ifdef TM_DISABLE_ALL_FILE_LOGGING
#define TM_DISABLE_ANSI_LINE_FILE /* Disable memoryleak.dat */
#undef TM_USE_SNIFF
#endif /* TM_DISABLE_ALL_FILE_LOGGING */

#ifdef __cplusplus
}
#endif

#endif /* _TRSYSTEM_H_ */

/* Processed by Treck Shipping Tool v2.62 
 * 2012/11/21 10:16:06      For: gainspan_2411
 * File Name: trsystem.h    File Revision: 6.0.2.46 
 * Project Name: tcpip.pj   Project Release: 6.0.1.29
 * Input checksum: 28417    Output checksum: 49556
 */
