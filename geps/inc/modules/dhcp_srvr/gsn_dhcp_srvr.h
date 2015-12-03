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
* $RCSfile: gsn_dhcp_srvr.h,v $
*
* Description : This file contains DHCP server API.
*******************************************************************************/
#ifndef _GSN_DHCP_SRVR_H_
#define _GSN_DHCP_SRVR_H_

#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
* File Inclusion
********************************************************************************/

#include "gsn_types.h"
#include "gsn_defines.h"
//#include "gsn_includes.h"



/**
 *******************************************************************************
 * @file gsn_dhcp_srvr.h
 * @brief GSN DHCP server public header.
 *    This file contains the public APIs and structures of Dhcp Server module.
 ******************************************************************************/


/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/


/**
 *******************************************************************************
 * @defgroup GsnDhcpSrvr GSN Dhcp Server
 * @brief  DHCP Server API's.
 *
 *    This file contains public definitions and API's for Dhcp Server. <br>
 *
 *   <br>
 *   This file contains public definitions and API's for Dhcp Server. DHCP
 * 	 server is started when node acting as a Limited AP. Users can associate
 *   to the node and configure it. The API GsnDhcpSrvr_Start starts the DHCP
 *   server and API GsnDhcpSrvr_Stop stops DHCP server. When a user/STA
 *   disassociates from limited AP its entry can be removed using API
 *   GsnDhcpSrvr_ClientDelete.
 ******************************************************************************/

/**
 *****************************************************************************
 *
 * @} 
 *****************************************************************************/


#define GSN_DHCP_SRVR_MAX_CLIENTS 64

typedef VOID (*GSN_DHCPSRVR_CLIENT_CONNECT_NOTIFY_FP)(UINT32 IpAddr,UINT8 *MacAddr);   
typedef VOID (*GSN_DHCPSRVR_CLIENT_DISCONNECT_NOTIFY_FP)(UINT32 IpAddr,UINT8 *MacAddr);   
   
typedef struct GSN_DHCP_SRVR_DHCP_MSG
{
/* packet op code / message type. '1' = BOOTREQUEST, '2' = BOOTREPLY */
		UINT8		bootOp;
/*
 * hardware address type, see ARP section in "Assigned Numbers" RFC1700.
 * '1' = Ethernet (10 Mb)
 */
		UINT8		bootHtype;
/* hardware address length ('6' for 10mb ethernet).*/
		UINT8		bootHlen;
/*
 * client sets to zero, optionally used by gateways in cross-gateway
 * booting
 */
		UINT8		bootHops;
/*
 * transaction ID, a random number, used to match this boot request with the
 * responses it generates.
 */
		unsigned long 	bootXid;
/* filled in by client, seconds elapsed since client started trying to boot.*/
		UINT16 	bootSecs;
/* Broadcast bit. */
		UINT16 	bootFlags;
/* client IP address: should be set to zero */
		unsigned long bootCiaddr;
/*
 * 'your' (client) IP address; filled by server if client doesn't
 * know its own address (ciaddr was 0).
 */
		unsigned long bootYiaddr;
/*
 * server IP address; returned in BOOTREPLY by server.
 * DHCP clarifies the interpretation of the 'siaddr' field as the
 * address of the server to use in the next step of the client's
 * bootstrap process.  A DHCP server may return its own address in the
 * 'siaddr' field, if the server is prepared to supply the next
 * bootstrap service (e.g., delivery of an operating system executable
 * image), in DHCPOFFER, DHCPACK packets.  A DHCP server always returns
 * its own address in the 'server identifier' option.
 */
		unsigned long bootSiaddr;
/* gateway IP address, used in optional BOOTP relay agent booting. */
		unsigned long bootGiaddr;
/* client hardware address, filled in by client (16 bytes). */
		UINT8		bootChaddr[16];
/* optional TFTP server host name, null terminated string (64 bytes). */
		UINT8		bootSname[64];
/*
 * boot file name, null terminated string; 'generic' name or null in
 * BOOTREQUEST/DHCPDISCOVER, fully qualified directory-path name in
 * BOOTREPLY/DHCPOFFER. (128 bytes)
 */
		UINT8		bootFile[128];
/*
 * optional vendor-specific area, e.g. could be hardware type/serial on
 * request, or 'capability' / remote file system handle on reply.  This
 * info may be set aside for use by a third phase bootstrap or kernel.
 * Called options with DHCP protocol. (64 bytes for BOOTP, 312 bytes
 * for DHCP).
 */
		struct
		{
			unsigned long 	optMagic;
#define optFields    optFieldsUnion.optUnFields
#define optDhcpMsg   optFieldsUnion.optUnDhcpMsg
			union
			{
				UINT8		optUnFields[
								312 - sizeof(unsigned long)];
/* 4-byte aligned DHCP message */
				unsigned long 	optUnDhcpMsg; /* DHCP message */
			} optFieldsUnion;
		} bootOptions;
}GSN_DHCP_SRVR_DHCP_MSG_T;


/**
 *******************************************************************************
 * @ingroup GsnDhcpSrvr
 * @brief DHCP server configuration structure.
 *
 * This structure defines the configuration data of DHCP server. The configuration
 * is provided by the caller.
 ******************************************************************************/
typedef struct GSN_DHCP_SRVR_CFG
{
    UINT32 serverIpAddr;
    UINT32 startIpAddr;
    UINT32 subnetMask;
    UINT32 gateway;
    UINT32 dns1;
    UINT32 dns2;
    GSN_NWIF_CTX_T *pNwif;
    GSN_WDD_CTX_T *pWdd;
    UINT32 numOfClients;
    UINT32 leaseTime;
    GSN_DHCPSRVR_CLIENT_CONNECT_NOTIFY_FP ClientConnectNotify;
    GSN_DHCPSRVR_CLIENT_DISCONNECT_NOTIFY_FP ClientDisconnNotify;

} GSN_DHCP_SRVR_CFG_T;

/**
 *******************************************************************************
 * @ingroup GsnDhcpSrvr
 * @brief DHCP server client structure.
 *
 * This structure defines the information stored for each client.
 ******************************************************************************/
typedef struct GSN_DHCP_SRVR_CLIENT
{
    UINT32 ipAddr;
    UINT32 leaseStartTime;     /**< in seconds */
    UINT8  macAddr[GSN_MAC_ADDR_LEN];
    UINT8  valid;
    UINT8  allocated;
} GSN_DHCP_SRVR_CLIENT_T;

/**
 *******************************************************************************
 * @ingroup GsnDhcpSrvr
 * @brief DHCP server context structure.
 *
 * This structure contains the parameters that define an instance of the DHCP
 * server.
 ******************************************************************************/
typedef struct GSN_DHCP_SRVR
{
    UINT32 serverIpAddr;
    GSN_SOFT_TMR_HANDLE_T recvTmrHndl;
    GSN_SOFT_TMR_T recvTmr;
    INT32 sockDesc;

    GSN_DHCP_SRVR_CFG_T srvrCfg;
    GSN_DHCP_SRVR_DHCP_MSG_T *dhcpPkt;
    INT32 dhcpMsgLen;

    GSN_DHCP_SRVR_CLIENT_T clients[GSN_DHCP_SRVR_MAX_CLIENTS];
    
    GSN_NWIF_CTX_T *pNwif;
    GSN_WDD_CTX_T *pWdd;

} GSN_DHCP_SRVR_T;


/*******************************************************************************
  * Private Macros and Functions
  ******************************************************************************/



/*******************************************************************************
 * Public Functions
 ******************************************************************************/


/**
 *******************************************************************************
 * @ingroup GsnDhcpSrvr
 * @brief Start DHCP server.
 *
 *    This function initializes the DHCP server context, creates a socket,
 *    binds to it and waits for messages on the socket.
 * @param dhcpSrvr - IN Pointer to DHCP context provided by user.
 * @param dhcpSrvrCfg - IN DHCP server configuration.
 * @retval GSN_FAILURE Operation failed.
 * @retval GSN_SUCCESS DHCP server started successfully.
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnDhcpSrvr_Start(GSN_DHCP_SRVR_T *dhcpSrvr, GSN_DHCP_SRVR_CFG_T *dhcpSrvrCfg);


/**
 *******************************************************************************
 * @ingroup GsnDhcpSrvr
 * @brief Stop the DHCP server.
 *
 *    This function stops the DHCP server.
 * @param dhcpSrvr - IN Pointer to DHCP context provided by user.
 * @retval GSN_FAILURE Operation failed.
 * @retval GSN_SUCCESS DHCP server stopped successfully.
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnDhcpSrvr_Stop(GSN_DHCP_SRVR_T *dhcpSrvr);

/**
 *******************************************************************************
 * @ingroup GsnDhcpSrvr
 * @brief Delete the dhcp client entry.
 *
 *    This function Delete the dhcp client entry on the server.
 * @param dhcpSrvr - IN Pointer to DHCP context provided by user.
 * @param macAddr  - IN Pointer to mac address provided by user.
 * @retval GSN_FAILURE Operation failed.
 * @retval GSN_SUCCESS DHCP server stopped successfully.
 ******************************************************************************/
PUBLIC GSN_STATUS
GsnDhcpSrvr_ClientDelete(GSN_DHCP_SRVR_T *dhcpSrvr, GSN_MAC_ADDR_T* macAddr);

/**
 *******************************************************************************
 * @ingroup GsnDhcpSrvr
 * @brief Query the dhcp client entries.
 *
 *    This function get the dchp client entries and return that info to the
 *    caller.
 * @param pDhcpSrvr - IN Pointer to DHCP context provided by user.
 * @param clients  - IN Pointer to client entry address provided by user.
 * @param count    - IN The max number of entry needed provided by user.
 * @retval The number of entries available.
 ******************************************************************************/

PUBLIC UINT8
GsnDhcpSrvr_ClientQuery(GSN_DHCP_SRVR_T *pDhcpSrvr,
                        GSN_DHCP_SRVR_CLIENT_T* clients, UINT8 count);

PUBLIC INLINE VOID
GsnDhcpSrvr_ClientConnectNotify(GSN_DHCP_SRVR_CFG_T *dhcpSrvrCfg, GSN_DHCPSRVR_CLIENT_CONNECT_NOTIFY_FP ClientConnectNotify)
{
  dhcpSrvrCfg->ClientConnectNotify = ClientConnectNotify;  
}

PUBLIC INLINE VOID
GsnDhcpSrvr_ClientDisconnectNotify(GSN_DHCP_SRVR_CFG_T *dhcpSrvrCfg, GSN_DHCPSRVR_CLIENT_DISCONNECT_NOTIFY_FP ClientDisconnNotify)
{
  dhcpSrvrCfg->ClientDisconnNotify = ClientDisconnNotify;  
}

#ifdef __cplusplus
}
#endif
#endif /* _GSN_DHCP_SRVR_H_ */




