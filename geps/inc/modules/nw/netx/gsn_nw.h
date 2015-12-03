/*******************************************************************************
*
*               COPYRIGHT (c) 2006-2010 GainSpan Corporation
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
* $RCSfile: gsn_nw.h,v $
*
* Description : This file contains the declarations commonly used.
*******************************************************************************/
#ifndef _GSN_NW_H_
#define _GSN_NW_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "netx/nx_api.h"
#include "netx/netx_applications/dhcp/nxd_dhcp_client.h"
#include "netx/netx_applications/dns/nxd_dns.h"

/**
 *******************************************************************************
 * @file gsn_nw.h
 * @brief GSN IP NW module public header.
 *      This file contains the IP NW glue related definitions.
 ******************************************************************************/

/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/



/**
 *******************************************************************************
 * @defgroup GsnNw GSN Network Stack Wrapper
 * @brief This group contains definitions and functions used to initialize,
 * open,  close, and configure IP Network objects.
 *******************************************************************************/

/**
 *****************************************************************************
 *
 * @} 
 *****************************************************************************/

/**
 *******************************************************************************
 * @ingroup GsnNw
 *
 * @brief MACROs defining various protocol parameters.
 * @{
 *******************************************************************************/

/**
 *******************************************************************************
 *
 * @} 
 *
 *******************************************************************************/
#define GSN_NW_ARP_TAGET_IP_OFFSET         	24
#define GSN_NW_ARP_PEER_IP_OFFSET          	14
#define GSN_NW_ARP_PEER_MAC_OFFSET         	8
#define GSN_NW_ARP_OP_OFFSET            	6
#define GSN_NW_ARP_RESPONSE                 0x02
#define GSN_NW_ARP_REQUEST                  0x01
	
#define GSN_NW_IP_HEADER_LEN            	20
#define GSN_NW_IP_PROTO_OFFSET              9
	
#define GSN_NW_ICMP_PROTO               	0x01
#define GSN_NW_ICMP_ECHO                	0x08
#define GSN_NW_TCP_PROTO                    6
	
#define GSN_NW_UDP_PROTO                    17
#define GSN_NW_UDP_DST_PORT_OFFSET          2
#define GSN_NW_UDP_SRC_PORT_OFFSET			0
	
#define GSN_NW_BOOTP_PORT                   68
#define GSN_NW_BOOTPS_PORT                  67
	
#define GSN_NW_IPV6_HEADER_LEN            		20
#define GSN_NW_IPV6_NXT_HDR_OFFSET				6
#define GSN_NW_IPV6_DEST_ADDR_OFFSET			24
	
#define GSN_NW_ICMPV6_PROTO						58 /*0x3a*/
#define GSN_NW_ICMPV6_MSG_NEIGHBOR_ADVTSMNT		136
#define GSN_NW_ICMPV6_MSG_ROUTER_ADVTSMNT		134
#define GSN_NW_IPV6_DHCPV6_CLI_PORT				546 /*0x222*/
#define GSN_NW_HTTP_PORT                   80

/*******************************************************************************
 *  Type Definitions
 *******************************************************************************/
typedef NX_PACKET_POOL	GSN_NW_PKT_POOL_HANDLE;

typedef enum GSN_NW_PKT_POOL_TYPE
{
	GSN_NW_SBUF_PKT_POOL,
	GSN_NW_LBUF_PKT_POOL
}GSN_NW_PKT_POOL_TYPE_T;

/**
 *******************************************************************************
 * @ingroup GsnNw
 *
 * @brief Network structure type, including a message handler, stack timer,
 * ARP context structure, and a pointer for the network interface in use.
 *******************************************************************************/
typedef struct GSN_NW_CTX
{    
	GSN_NW_PKT_POOL_HANDLE sbufPktPoolHndl; /**< Pool of small packets used for receive*/
	UINT32 sbufPktPoolPktSize;
	GSN_NW_PKT_POOL_HANDLE LbufPktPoolHndl; /**< Pool of Large packets used for receive*/
	UINT32 LbufPktPoolPktSize;
  
} GSN_NW_CTX_T;

typedef struct GSN_NW_INIT_PARAMS
{	
	/**< Nw stack will have a common pool of small buffers used across multiple IP instances */
	UINT32 sbufPktPoolPktSize; /**< packet pool will be of fixed Small size buffers. this number must be devisible by 4*/
	INT8 *sbufPktPoolStart; /**< pointer to the Small size buffers pool memory area*/
	UINT32 sbufPktPoolSize; /**< Small size buffers  Pool size*/

	/**<  Nw stack will have a common pool of Big buffers used across multiple IP instances */
	UINT32 LbufPktPoolPktSize; /**< packet pool will be of fixed Big size buffers. this number must be devisible by 4*/
	INT8 *LbufPktPoolStart; /**< pointer to the Big size buffers pool memory area*/
	UINT32 LbufPktPoolSize; /**< Big size buffers Pool size*/

}GSN_NW_INIT_PARAMS_T;


/*******************************************************************************
 *  Public Functions
 ******************************************************************************/

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief NW Initialization.
 *    This function initializes the NW module. 
 *******************************************************************************/
PUBLIC GSN_STATUS
GsnNw_Init(GSN_NW_CTX_T *pNwCtx, GSN_NW_INIT_PARAMS_T *pParam);

PUBLIC GSN_STATUS
GsnNw_PktPoolCreate(GSN_NW_PKT_POOL_HANDLE *pPktPoolHndl, UINT32 pktSize, UINT8 *poolArea,
									UINT32 poolSize);

PUBLIC GSN_NW_PKT_POOL_HANDLE *
GsnNw_PktPoolHndlGet(GSN_NW_CTX_T *pNwCtx, GSN_NW_PKT_POOL_TYPE_T poolType);

PUBLIC NX_PACKET *
GsnNw_PoolPacketGet(GSN_NW_CTX_T *pNwCtx, UINT32 size);
#ifdef __cplusplus
}
#endif

#endif /* _GSN_NW_H_ */





