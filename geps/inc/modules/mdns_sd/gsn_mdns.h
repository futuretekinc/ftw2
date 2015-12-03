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
* $RCSfile: gsn_mdns.h,v $
*
* Description : This file contains mDns-SD module implementation.
*******************************************************************************/
#ifndef _GSN_MDNS_H_
#define _GSN_MDNS_H_
/**
 *******************************************************************************
 * @file gsn_mdns.h
 * @brief GSN mDns-SD  public API implementation.
 *    This file contains the public APIs and structures of mDns-SD  module.
 ******************************************************************************/
 
/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/

/**
 *******************************************************************************
 * @defgroup GsnMdns GSN mDns-SD
 * @brief mDns-SD.
 *
 *   This group contains public definitions for the mDns-SD based Service Discovery provided by GSN .
 *   Functions are provided to initialize mDns-SD module, Register host name and Services, announce,
 *   deregister and discover the services.
 ******************************************************************************/
		
/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/
	
#define GSN_MDNS_LOCAL_DOMAIN "local"
/* standard service types*/
#define GSN_SRVC_TYPE_HTTP "_http"
/* standard proto*/
#define GSN_SRVC_PROTO_TCP  "_tcp"
#define GSN_SRVC_PROTO_UDP  "_udp"

/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief various header structures(Packed Structures)
 *
 ******************************************************************************/
#pragma pack(1)
typedef struct DNS_HEADER
{
    UINT16 id;
    UINT8 flagByte1;
    UINT8 flagByte2;
    UINT16 numQuestion;
    UINT16 numAns;
    UINT16 numAutharity;
    UINT16 numAditional;
}DNS_HEADER_T;
       
typedef struct DNS_RR_COMMON_PART
{
    UINT16 type;
    UINT16 Class;
    UINT32 ttl;
    UINT16 rdLength;
}DNS_RR_COMMON_PART_T;

typedef struct DNS_SRV_RR_RDATA
{
    UINT16 pririty;
    UINT16 weight;
    UINT16 port;
    UINT8 target[1];/* usually it points to an address record. 254 should max limit*/
    
}DNS_SRV_RR_RDATA_T;

typedef struct DNS_QSTN_COMNON_PART
{
    UINT16 qType;
    UINT16 qClass;
}DNS_QSTN_COMNON_PART_T;

#pragma pack()/* reverting back to non-packing of structures*/

typedef enum GSN_MDNS_MSG_ID
{
	GSN_MDNS_MSG_SOCK_RECV,
	GSN_MDNS_MSG_QUERY_TIMEOUT,
	GSN_MDNS_MSG_PROBE_TIMEOUT,
	GSN_MDNS_MSG_DEFFERED_PROBE_TIMEOUT,
	GSN_MDNS_MSG_SHUTDOWN,
}GSN_MDNS_MSG_ID_T;
/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief mDns message queue message structure 
 *
 ******************************************************************************/
typedef struct GSN_MDNS_MSG
{
	GSN_MDNS_MSG_ID_T 	msgId;
	UINT32		msgInfo_1;
	UINT32		msgInfo_2;
	UINT32		msgInfo_3;
}GSN_MDNS_MSG_T;
/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief Status code provided with the Hostname/Service Call Back
 *
 *	   These define the status provided in the call back for Hostname / Service Registration
 ******************************************************************************/
typedef enum GSN_MDNS_REG_CB_STATUS
{
    GSN_MDNS_REG_CONFLICT, /**<Conflict detected in case of registration of Hostname/Service*/
    GSN_MDNS_REG_SUCCESS,/**<Registration of Hostname/Service is successful*/
}GSN_MDNS_MDNS_CB_STATUS_T;

/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief Status code provided with service discover  Call Back
 *
 *	   These define the status provided in the call back for discovering service
 ******************************************************************************/
typedef enum GSN_MDNS_SD_CB_STATUS_T
{
    GSN_MDNS_SD_NO_SRVC_INFO,
    GSN_MDNS_SD_MORE_SRVC_INFO,
    GSN_MDNS_SD_LAST_SRVC_INFO,
}GSN_MDNS_SD_CB_STATUS_T;

/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief Information about a service Discovered
 *
 *	   These define the data structure having various information about the service discovered
 ******************************************************************************/
typedef struct GSN_MDNS_SRVC_INFO
{
    /* used during service discovery (continuous query)*/
    struct GSN_MDNS_SRVC_INFO *next;
    
    UINT8 instance[64];/* rfc - max limit is 64 *//**<Service Instance name*/
    UINT8 subType[64]; /* rfc max limit is 69 *//**<ServiceSub type*/
    UINT8 srvcType[24]; /* rfc max limit - 22*//**<Service type*/
    UINT8 protocol[16]; /**<Service protocol*/
    UINT8 domain[12]; /**<domain*/
    
    /* Txt record information*/
	UINT8 *txtInfo;
                            
    /* port number and the ip address on which service is provided */
    UINT16 port;/**<Port on which service is available*/
    UINT32 ipAddr;/**<IP address of the interface  on which service is available*/

}GSN_MDNS_SRVC_INFO_T;

/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief Service Discover call back function prototype
 *
 ******************************************************************************/
typedef VOID (*GSN_MDNS_SD_CB_T)(void *pData, const GSN_MDNS_SRVC_INFO_T *srvinfo, 
                                 	UINT32 status);
/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief Hostname/Service register call back function prototype
 *
 ******************************************************************************/
typedef VOID (*GSN_MDNS_RR_REG_CB_T)(void *pData, UINT8 *rrName, UINT32 status);

/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief call back to be called for posting message to an application task.
 *
 ******************************************************************************/
typedef VOID (*GSN_MDNS_MSG_POST_CB)(VOID *cbCtx, VOID *pMdns);

/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief Resource Record definition
 *
 ******************************************************************************/
/*RFC - TXT record Key=Value : The total size of a typical DNS-SD TXT record is intended to be small
   -- 200 bytes or less.

   6.6 Example TXT Record
   
      The TXT record below contains three syntactically valid key/value
      pairs. (The meaning of these key/value pairs, if any, would depend
      on the definitions pertaining to the service in question that is
      using them.)
   
           -------------------------------------------------------
           | 0x09 | key=value | 0x08 | paper=A4 | 0x07 | passreq |
           -------------------------------------------------------
*/
/*
Service Instance Name = <Instance> . <subtypename>._sub.<Service> . <Domain>
*/
/*
DNS
1.	The maximum length of any dns label is 64 bytes (63 bytes of characters plus 1 byte for length field)
2.	The maximum length of the fully qualified dns name shall be 255 bytes

DNS-SD
a.	Max length of instance part = 63 bytes.
b.	Max len of sub type	= 69 bytes (63 bytes subtype + 1 byte subtype len + 4 bytes of _sub + 1 byte of _sub len)
 
c.	Max len of  service type = 22 bytes (16 bytes of srvc type + 1 byte of servicetype len + 4 bytes of protocol + 1 byte of protocol len
d.	Worst case num Bytes remained for domain name = (255 - (64+69+22)) = 155. We only support .local domain. So domain name len = 7 bytes.
*/
typedef struct RESOURCE_RECORD
{    
    /*Standard fields */
    UINT8 						name[256];/* rfc max limit 256*/
    DNS_RR_COMMON_PART_T 		rrcp;
    UINT8 						rData[128];/* no rfc max limit*/

    /* House Keeping Fields */
	struct RESOURCE_RECORD *	next; 
    struct RESOURCE_RECORD *	pTxtRr;/* TXT RR associated with SRV RR*/
    UINT8 						state;    /* state of the RR */
    UINT8 						autoCorrect;
	UINT8 						scope; /*GSN_MDNS_SCOPE_T*/
    GSN_MDNS_RR_REG_CB_T 		cb;
    VOID *						cbCtx;
    UINT8 						subTypeOffset;
    UINT8 						srvcTypeOffset;
    UINT8 						rrSection;     /* used during response parsing*/
    UINT8 						sendAsAdnlRR;    /* used for query response*/
}RR_T;

typedef struct QUESTION
{
    UINT8 						qName[256];/*Not expecteng it to be more than 64. rfc - max limit is 254*/
    UINT16 						qType;
    UINT16 						qClass;
	
	struct QUESTION *			next;
	/* used for query*/
    GSN_MDNS_SD_CB_T 			cb;
    VOID *						cbCtx;
    /* used in case of query, probing*/
    UINT8 						status;
	UINT8 						scope;/* scope of the query*/
	VOID *						pMdns; /* This pointer to mdns context will be used in timer call backs*/
    GSN_SOFT_TMR_HANDLE_T 		tmrHandle;/**<  timer handle.*/
    GSN_SOFT_TMR_T 				tmrCtx;/**<timer context.*/
    UINT32 						timeoutVal;
    GSN_MDNS_SRVC_INFO_T *		dscvrdSrvcsLst;    
    UINT8 						removeTmr;
    /* used in case of probeing*/
    UINT8 						probeCnt;
    RR_T *						pProbeRR;      
}QUESTION_T;
/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief scope of the RR / probe
 *
 ******************************************************************************/
typedef enum GSN_MDNS_SCOPE
{
	GSN_MDNS_SCOPE_IPV4_LOCAL,
	GSN_MDNS_SCOPE_IPV6_LOCAL,
	GSN_MDNS_SCOPE_IPV6_SITE
}GSN_MDNS_SCOPE_T;

/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief packet received on IP v4/v6 nw
 *
 ******************************************************************************/
#define GNS_MDNS_RECV_NW_TYPE_IPV4	1
#define GNS_MDNS_RECV_NW_TYPE_IPV6	2

/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief State of the MDNS context structure
 *
 ******************************************************************************/
#define GSN_MDNS_STATE_NOT_INITIALISED				0
#define GSN_MDNS_STATE_INIT_IN_PROGRESS			1
#define GSN_MDNS_STATE_INITIALISED					2
#define GSN_MDNS_STATE_SHUTDON_IN_PROGRESS			3

/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief mDns module context 
 *
 ******************************************************************************/
typedef struct GSN_MDNS
{
	UINT8 					state;
	UINT8					noSeparatetsk;
	UINT8 					blockingOn;
	GSN_OSAL_QUEUE_T 		msgQueue;		/**< message queue handle */

	/* Mutex used protect the mdns context*/
	GSN_OSAL_MUTEX_T		protectionLock;/* When deleted All threads suspended waiting
											   for the mutex are resumed and given a TX_DELETED 
											   return status.*/
	GSN_MDNS_MSG_POST_CB 	msgPostCb;
	VOID *					msgPostcbCtx;

	GSN_NWIF_CTX_T *		pNwIf;
	INT32 					mdnsSock6;
	INT32 					mdnsSock4;

	RR_T *					regstdRrList; /* supported resource records */
	RR_T *					respRrList; /* RRs in response. used during parsing the response */

	QUESTION_T *			questList;/* Used during processing an incomming query. To list out the Questions*/
	QUESTION_T *			queryList;/* Used during creating a query. List of query to be sent*/
	/*QUESTION_T *announceList;*/
	QUESTION_T *			probeList;/* used during creating a probe */

	GSN_OSAL_MUTEX_T 		rrLock;/* protect rr list*/
	GSN_OSAL_MUTEX_T 		qstnLock; /* pritect the question list */

	/* Incomming packet parsing related variables*/ 
	union
	{
		struct sockaddr_in6 	fromAddr6;
		struct sockaddr_in 		fromAddr4;
	};
}GSN_MDNS_T;
/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief define the type of task context in which the mDns server will run
 *
 ******************************************************************************/
#define		GSN_MDNS_TASK_CONTEXT_NONE 		0
#define		GSN_MDNS_TASK_CONTEXT_OWN 		1
#define		GSN_MDNS_TASK_CONTEXT_APP 		2

/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief flag indicating the mDns servr is run in blocking mode or not 
 *
 ******************************************************************************/
#define GSN_MDNS_BLOCKING_OFF	0
#define GSN_MDNS_BLOCKING_ON	1
/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief mDns module init param
 *
 ******************************************************************************/
typedef struct GSN_MDNS_INIT_PARAM
{ 
    
	GSN_NWIF_CTX_T *pNwif;
	UINT32 		ipV4Addr;
	UINT32 		ipV6Addr[4];	
	UINT8 		blockingOn;
	UINT8* 		msgQueueBuff;	    	/**< pointer to message queue buffer*/
	UINT32 		msgQueueBuffSize;   	/**< messsage queue buffer size*/			
	UINT32 		noSeparatetsk;			
	GSN_MDNS_MSG_POST_CB msgPostCb;
	VOID *msgPostCbCtx;
}GSN_MDNS_INIT_PARAM_T;
/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief  Host name Register param
 *
 ******************************************************************************/

typedef struct GSN_MDNS_HNREG_PARAM
{
	UINT8 *hostname;
	UINT8 *domain;
	GSN_NWIF_IPADDR_T ipAddr;
	UINT32	ttl;/* Time to live*/
	UINT8 autoCorrect;
	UINT8 scope;/*GSN_MDNS_SCOPE_T*/
	UINT8 conflctDetect;
	GSN_MDNS_RR_REG_CB_T cb; 
	VOID *cbCtx;
}GSN_MDNS_HNREG_PARAM_T;

/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief Service Register param
 *
 ******************************************************************************/
typedef struct GSN_MDNS_SRVCREG_PARAM_T
{
	UINT8 *srvceName;
	UINT8 *srvceSubType;/* Name of the subtype excluding "_sub". "_sub" is added implicitly*/
	UINT8 *srvceType;
	UINT8 *srvceProto;
	UINT8 *domain;
	UINT8 **keyVal;
	UINT16 port;
	UINT32	ttl;/* Time to live*/
	UINT8 autoCorrect;
	UINT8 scope;
	UINT8 conflctDetect;
	GSN_MDNS_RR_REG_CB_T cb;
	VOID *cbCtx;
}GSN_MDNS_SRVCREG_PARAM_T;

/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief Hostname Deregister param
 *
 ******************************************************************************/
typedef struct GSN_MDNS_HNDEREG_PAARAM
{
	UINT8 * hostname;
	UINT8 * domain;	
}GSN_MDNS_HNDEREG_PAARAM_T;

/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief Service Deregister param
 *
 ******************************************************************************/
typedef struct GSN_MDNS_SRVCDEREG_PARAM
{
	UINT8 * srvceName;
	UINT8 * srvceSubType;
	UINT8 * srvceType;
	UINT8 * srvceProto;
	UINT8 * domain;

}GSN_MDNS_SRVCDEREG_PARAM_T;

/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief Announce param
 *
 ******************************************************************************/
typedef struct GSN_MDNS_ANNOUNCE_PARAM_T
{
	UINT8 *srvceName;
	UINT8 *srvceSubType;/* Name of the subtype excluding "_sub". "_sub" is added implicitly*/
	UINT8 *srvceType;
	UINT8 *srvceProto;
	UINT8 *domain;
	
}GSN_MDNS_ANNOUNCE_PARAM_T;

/**
 *******************************************************************************
 * @ingroup GsnMdns
 * @brief service Discover param
 *
 ******************************************************************************/
typedef struct GSN_MDNS_SRVCDISCVR_PARAM
{
	UINT8 *srvcSubType;
	UINT8 *srvcType;
	UINT8 *srvcProto;
	UINT8 *domain;
	UINT8 scope;
	GSN_MDNS_SD_CB_T cb;
	VOID *cbCtx;
}GSN_MDNS_SRVCDISCVR_PARAM_T;

/**
 *********************************************************************************
 * @ingroup GsnMdns
 * @brief Initialization of mDns-SD module
 *		This function does the initialization of the mDns-SD module. 
 * @param  pMdns - IN Pointer to object of type GSN_MDNS_T
 * @param  pParam - IN Pointer to object of type GSN_MDNS_INIT_PARAM_T 
 * @retval GSN_SUCCESS Operation successful.
 * @retval GSN_FAILURE Initialization failed.
 * @note 
 *		This function shall be called before any of the mDns-SD module  call is called.
 *********************************************************************************/
PUBLIC GSN_STATUS
GsnMdns_Init(GSN_MDNS_T *pMdns, GSN_MDNS_INIT_PARAM_T *pParam);

/**
*********************************************************************************
* @ingroup GsnMdns
* @brief 
* @param	pMdns - IN Pointer to object of type GSN_MDNS_T
*********************************************************************************/
 VOID 
 GsnMdns_Execute(GSN_MDNS_T *pMdns);
 /**
 *********************************************************************************
 * @ingroup GsnMdns
 * @brief 
 * @param	 pMdns - IN Pointer to object of type GSN_MDNS_T
 *********************************************************************************/ 
 PUBLIC VOID
 GsnMdns_DeInit(GSN_MDNS_T *pMdns);

/**
 *********************************************************************************
 * @ingroup GsnMdns
 * @brief Register the host name
 *		This function is used for registering the host name of the interface(node). 
 * @param  pMdns - IN Pointer to object of type GSN_MDNS_T
 * @param  pParam - IN Pointer to object of type GSN_MDNS_HNREG_PARAM_T 
 * @retval GSN_SUCCESS Operation successful.
 * @retval GSN_FAILURE Registration  failed.
 * @note 
 *		This function will return GSN_SUCCESS in case the registration is successfully initiated. However the
 *		status of the actual registration process will be known only through the call back.
 *********************************************************************************/
 PUBLIC GSN_STATUS
 GsnMdns_HostnameRegister(GSN_MDNS_T *pMdns, GSN_MDNS_HNREG_PARAM_T *pParam);
/**
 *********************************************************************************
 * @ingroup GsnMdns
 * @brief Register the Service
 * 	 This function is used for registering the a service. 
 * @param	pMdns - IN Pointer to object of type GSN_MDNS_T
 * @param  pParam - IN Pointer to object of type GSN_MDNS_SRVCREG_PARAM_T
 *  @retval GSN_SUCCESS Operation successful.
 * @retval GSN_FAILURE Registration  failed.
 * @note 
 *		 This function will return GSN_SUCCESS in case the registration is successfully initiated.However the
 *		 status of the actual registration process will be known only through the call back
 *********************************************************************************/
 PUBLIC GSN_STATUS
 GsnMdns_ServiceRegister(GSN_MDNS_T *pMdns, 		  GSN_MDNS_SRVCREG_PARAM_T *pParam);

/**
*********************************************************************************
* @ingroup GsnMdns
* @brief Announce the Service/s
*		This function is used for announcing the  given services 
* @param  pMdns - IN Pointer to object of type GSN_MDNS_T
* @param  pParam - IN Pointer to MDNS announce parameters
* @retval UINT32
*@note
*	
*********************************************************************************/
PUBLIC UINT32
GsnMdns_Announce(GSN_MDNS_T *pMdns, GSN_MDNS_ANNOUNCE_PARAM_T *pParam);

PUBLIC UINT32
GsnMdns_AnnounceAll(GSN_MDNS_T *pMdns);

/**
 *********************************************************************************
 * @ingroup GsnMdns
 * @brief De register host name
 *		This function is used for Deregistering the host name of the interface(node). 
 * @param  pMdns - IN Pointer to object of type GSN_MDNS_T
 * @param  pParam - IN Pointer to object of type GSN_MDNS_HNDEREG_PAARAM_T 
 * @retval GSN_SUCCESS Operation successful
 * @retval GSN_FAILURE Deregistration Failed
 *********************************************************************************/
PUBLIC GSN_STATUS
GsnMdns_HostnameDeregister(GSN_MDNS_T * pMdns, GSN_MDNS_HNDEREG_PAARAM_T *pParam);

/**
 *********************************************************************************
 * @ingroup GsnMdns
 * @brief Register the Service
 *		This function is used for Deregistering the a service. 
 * @param  pMdns - IN Pointer to object of type GSN_MDNS_T
 * @param  pParam - IN Pointer to object of type GSN_MDNS_SRVCDEREG_PARAM_T 
 * @retval GSN_SUCCESS Operation successful
 * @retval GSN_FAILURE Deregistration Failed
 *********************************************************************************/
PUBLIC GSN_STATUS
GsnMdns_ServiceDeRegister(GSN_MDNS_T * pMdns, GSN_MDNS_SRVCDEREG_PARAM_T *pParam );

/**
 *********************************************************************************
 * @ingroup GsnMdns
 * @brief Discover the Service
 *		This function is used for discovering services of given type
 * @param  pMdns - IN Pointer to object of type GSN_MDNS_T
 * @param  pParam - IN Pointer to object of type GSN_MDNS_SRVCDISCVR_PARAM_T 
 * @retval GSN_SUCCESS Operation successful.
 * @retval GSN_FAILURE service discover failed.
 * @note 
 * 	 This function will return GSN_SUCCESS in case the service Discovery is successfully initiated.However the
 *	 status of the actual discovery process will be known only through the call back
 *********************************************************************************/
PUBLIC GSN_STATUS
GsnMdns_ServiceDiscover(GSN_MDNS_T *pMdns, GSN_MDNS_SRVCDISCVR_PARAM_T *pParam);

#endif




















































