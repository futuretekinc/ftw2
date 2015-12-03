/******************************************************************************
 *
 *               COPYRIGHT (c) 2012-2013 GainSpan Corporation
 *                         All Rights Reserved
 *
 * The source code contained or described herein and all documents
 * related to the source code ("Material") are owned by Gainspan
 * Corporation or its licensors.  Title to the Material remains
 * with Gainspan Corporation or its suppliers and licensors.
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
 * Unless otherwise agreed by Gainspan in writing, you may not remove or
 * alter this notice or any other notice embedded in Materials by Gainspan
 * or Gainspan's suppliers or licensors in any way.
 *
 * $RCSfile: gsn_dhcpv6_server.h,v $
 *
 * Description:
 *      This file contains public functions definitions for gsn_dhcpv6_server.h
 * 
 ******************************************************************************
 */



#ifndef DHCPv6_SERVER_H
#define DHCPv6_SERVER_H

#include "gsn_types.h"
#include "netx/nx_api.h"
#include "netx/netx_bsd_layer/nxd_bsd.h"
#include "gsn_includes.h"



#define DHCPV6_HW_TYPE_IEEE_802                        0x06

#define DHCPV6_SERVER_UDP_PORT                          547

#define DHCPV6_SERVER_DUID_VENDOR_ASSIGNED_LENGTH       48

#define MAX_CLIENTS_SUPPORTED                           32

#define DHCPV6_DEFAULT_PREFERRED_TIME                  600

#define DHCPV6_DEFAULT_VALID_TIME                     1200


#define DHCPv6_RESERVED_ADDR                             1

#define GSN_DHCPv6_RUNNING								1


#define htonl_t(a)  NX_CHANGE_ULONG_ENDIAN(a)

#define htons_t(a)  NX_CHANGE_USHORT_ENDIAN(a)

#define REC_BUF_SIZE                                   512
#define SEND_BUF_SIZE                                  256



/*  DHCPv6 Message type */
typedef enum DHCPv6_MSG_TYPE
{
     SOLICIT = 1,
     ADVERTISE,
     REQUEST,
     CONFIRM,
     RENEW,
     REBIND,
     REPLY,
     RELEASE,
     DECLINE,
     RECONFIGURE,
     INFORMATION_REQUEST,
     RELAY_FORW	,
     RELAY_REPL
}DHCPv6_MSG_TYPE_T;


/* DHCPv6 Option type */
#define       OPTION_CLIENTID   	0x01
#define	      OPTION_SERVERID		0x02
#define	      OPTION_IA_NA		0x03
#define	      OPTION_IA_TA		0x04
#define	      OPTION_IAADDR		0x05
#define	      OPTION_ORO   		0x06
#define	      OPTION_PREFERENCE		0x07
#define	      OPTION_ELAPSED_TIME	0x08
#define	      OPTION_RELAY_MSG		0x09
#define	      OPTION_AUTH		0x0A
#define	      OPTION_UNICAST		0x0B
#define	      OPTION_STATUS_CODE	0x0C
#define	      OPTION_RAPID_COMMIT	0x0D
#define	      OPTION_USER_CLASS		0x0E
#define	      OPTION_VENDOR_CLASS	0x0F
#define	      OPTION_VENDOR_OPTS	0x10
#define	      OPTION_INTERFACE_ID	0x11
#define	      OPTION_RECONF_MSG		0x12
#define	      OPTION_RECONF_ACCEPT	0x13


/* GS Error codes */
#define         GSN_DHCPv6_SUCCESS                     0
#define         GSN_DHCPv6_FAILURE                     1
#define         GSN_DHCPv6_BIND_ERROR                  2
#define         GSN_DHCPv6_INIT_ERROR                  3
#define         GSN_DHCPv6_BAD_PACKET                  4
#define         GSN_DHCPv6_INVALID_GLOBAL_ADDR         5
#define         GSN_DHCPv6_MSG_TYPE_NOT_SUPPORTED      6
#define         GSN_DHCPv6_NO_IP                       33


/* DUID type */
typedef enum DHCPv6_DUID_TYPE
{
	DHCPV6_SERVER_DUID_TYPE_LINK_TIME = 1,
	DHCPV6_SERVER_DUID_TYPE_VENDOR_ASSIGNED,
	DHCPV6_SERVER_DUID_TYPE_LINK_ONLY
}DHCPv6_DUID_TYPE_T;


/* DUID */
typedef struct DUID_STRUCT
{
    USHORT            opCode;
    USHORT            optionLength;
    USHORT            duidType;
    USHORT            hardwareType;
    ULONG             duidTime;
    ULONG             duidEnterpriseNumber;
    UCHAR             duidPrivateIdentifier[DHCPV6_SERVER_DUID_VENDOR_ASSIGNED_LENGTH];
    USHORT            linkLayerAddressMsw;
    ULONG             linkLayerAddressLsw;
} DUID_STRUCT_T;

/* IA */
typedef struct IA
{
        UINT16 option;
	UINT16 optionLength;
	UINT32  ipv6Addr[4];
	UINT32  preferedLifeTime;
	UINT32  validLifeTime;
}IA_T;


/* IANA   */
typedef struct DHCPv6_IANA
{
	UINT16 option;
	UINT16 optionLength;
	UINT32  IA_NA_id;
	UINT32  T1;
	UINT32  T2;
	IA_T   ia;

}DHCPv6_IANA_T;



/* Client records*/
typedef struct CLIENT_RECORD
{
  DUID_STRUCT_T clientDuidRecord;
  UINT8 reserved;
  UINT32 availIndex;
}CLIENT_RECORD_T;



/* DHCPv6 server*/
typedef struct GSN_DHCPv6_SERVER
{
  UINT8 state;
  INT32 sockId;
  DUID_STRUCT_T serverId;
  UINT8 *sendRecBuffer;
  UINT32 ipv6PoolStart[4] ;  /* Starts from next IPv6 global address assigned to interface  */
  UINT32 assignedIndex;      /* Each bit index represents availability of IPv6 address */
  CLIENT_RECORD_T dhcpv6CientRecord[MAX_CLIENTS_SUPPORTED];
  GSN_NWIF_CTX_T *pNwif;
  GSN_OSAL_MUTEX_T dhcpv6Lock;

}GSN_DHCPv6_SERVER_T;


typedef struct GSN_DHCPV6_SRVR_INIT_PARAM
{
  UINT32 startAddr[4];
  DUID_STRUCT_T serverId;
  
}GSN_DHCPV6_SRVR_INIT_PARAM_T;



UINT8
GsnDhcpv6Srvr_start(GSN_DHCPv6_SERVER_T *pDhcpv6Server, GSN_DHCPV6_SRVR_INIT_PARAM_T *pDhcpv6InitParams);


UINT8
GsnDhcpv6Srvr_Stop(GSN_DHCPv6_SERVER_T *pDhcpv6Server);

#endif

