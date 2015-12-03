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
* $RCSfile: gsn_dns_server.h,v $
*
* Description : This file contains DNS server API.
*******************************************************************************/

#ifndef _GSN_DNS_SRVR_H_
#define _GSN_DNS_SRVR_H_

/*******************************************************************************
* File Inclusion
********************************************************************************/

#include "gsn_types.h"
#include "gsn_defines.h"

/**
 *******************************************************************************
 * @file gsn_dns_server.h
 * @brief GSN DNS server public header.
 *    This file contains the public APIs and structures of DNS Server module.
 ******************************************************************************/





/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/





/**
 *******************************************************************************
 * @defgroup GsnDnsSrvr GSN DNS Server
 * @brief  DNS Server API's.
 *
 *    This file contains public definitions and API's for DNS Server. <br>
 *
 *   <br>
 *   This file contains public definitions and API's for DNS Server. DNS
 * 	 server is started when node acting as a Limited AP. After association user
 *   can open web provision page using node domain name and configure the node.
 *   This DNS server has limited capabilities and only resolves nodes domain
 *   name to its IP address. The API GsnDnsSrvr_Start starts DNS server and
 *   GsnDnsSrvr_Stop stops server.
 ******************************************************************************/



/**
 *****************************************************************************
 *
 * @}
 *****************************************************************************/



/**
 *******************************************************************************
 * @ingroup GsnDnsSrvr
 * @brief DNS Server Structure.
 *
 *     This Structure defines IP address, Domain Name and socket descriptor of
 *     DNS server.
 ******************************************************************************/

typedef struct GSN_DNS_SERVER
{
	UINT32 serverIpAddr;	/**< IP address of Server in Host Byte order */
        ULONG serverIpv6Addr[4];  /* IPv6 address of the server */
        UINT8 *dnsName;	    /**< Pointer to Domain Name of Node */
	INT32 sockDescv6;		    /**< Socket descriptor */
        INT32 sockDescv4;
        UINT8 versionFlag;
        UINT32 GsnDnsSrvr_Status;
        GSN_NWIF_CTX_T *pNwif;
        GSN_OSAL_MUTEX_T dnsLock;
}GSN_DNS_SERVER_T;


typedef struct GSN_DNS_INIT_PARAM
{
	UINT16 flags;
        UINT32 serverIpAddr;
        ULONG serverIpv6Addr[4];
}GSN_DNS_INIT_PARAM_T;




/*******************************************************************************
 * Public Functions
 ******************************************************************************/





/**
 *******************************************************************************
 * @ingroup GsnDnsSrvr
 * @brief Start DNS server.
 *
 *    This function initializes the DNS server, creates a socket,
 *    binds to it and waits for messages on the socket.
 * @param pDnsSrvr - IN Pointer to DNS context provided by user.
 * @param dnsName  - IN Pointer to Domain Name.
 * @param initParams  - IN Pointer to Initialization Parameters
 * @retval GSN_FAILURE Operation failed.
 * @retval GSN_SUCCESS DHCP server started successfully.
 ******************************************************************************/

PUBLIC GSN_STATUS
GsnDnsSrvr_Start(GSN_DNS_SERVER_T *pDnsSrvr, UINT8 *dnsName,GSN_DNS_INIT_PARAM_T *initParams);



/**
 *******************************************************************************
 * @ingroup GsnDnsSrvr
 * @brief Stop DNS server.
 *
 *    This function stops DNS server.
 * @param pDnsSrvr - IN Pointer to DNS context provided by user.
 * @retval GSN_SUCCESS DHCP server stoped successfully.
 * @retval GSN_FAILURE DHCP server stop Failed.
 ******************************************************************************/



PUBLIC GSN_STATUS
GsnDnsSrvr_Stop(GSN_DNS_SERVER_T *pDnsSrvr);



UINT8*
GsnDnsSrvr_DnsNameConfig(UINT8 *pName);

#endif
