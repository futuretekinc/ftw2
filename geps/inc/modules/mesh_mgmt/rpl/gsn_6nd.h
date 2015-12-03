/******************************************************************************
*
*               COPYRIGHT (c) 2013 GainSpan Corporation
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
* $RCSfile: gsn_6nd.h,v $
*
* Description : This file contains function defination for 6ND.
*****************************************************************************/

#ifndef _GSN_6ND_H_
#define _GSN_6ND_H_

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
* File inclusion
******************************************************************************/
#include "modules/mesh_mgmt/rpl/gsn_rpl.h"


/**
 *****************************************************************************
 * @ingroup Gsn6ND
 * @brief 6ND device type
 *    These macros defines the 6ND device type.
 *****************************************************************************/
#define GSN_RPL_6ND_MODE_HOST  2
#define GSN_RPL_6ND_MODE_LR    1
#define GSN_RPL_6ND_MODE_LBR   0

/**
 *****************************************************************************
 * @ingroup Gsn6ND
 * @brief Configurable option for 6ND
 *    These macros defines configurable option for 6ND device.
 *****************************************************************************/
#define GSN_RPL_6ND_CID_PREFIX_LEN 16
#define GSN_RPL_6ND_MAX_LBR_SUPPORTED 2
#define GSN_RPL_6ND_MAX_CID_SUPPORTED 16

#define GSN_RPL_6ND_MAX_RTR_SOLICITATIONS 3
#define GSN_RPL_6ND_RTR_SOLICITATION_INTERVAL 10
#define GSN_RPL_6ND_MAX_RTR_SOLICITATION_INTERVAL 60
#define GSN_RPL_6ND_RETRANS_TIMER 1 //1000msec
#define GSN_RPL_6ND_MAX_UNICAST_SOLICIT 3
     
#define GSN_RPL_6ND_ROUTER_DFLT_LIFE_TIME 9000 /**< Taken from RFC 4861*/ 
#define GSN_RPL_6ND_DFLT_REACHANBLE_TIME  30000 /**< Taken from RFC 4861, p.g. 79 */
#define GSN_RPL_6ND_DFLT_RETRANS_TIME     1000 /**< Taken from RFC 4861, p.g. 79 */

/***
Router constants:
	MAX_INITIAL_RTR_ADVERT_INTERVAL 16 seconds
	MAX_INITIAL_RTR_ADVERTISEMENTS 3 transmissions
	MAX_FINAL_RTR_ADVERTISEMENTS 3 transmissions
	MIN_DELAY_BETWEEN_RAS 3 seconds
	MAX_RA_DELAY_TIME .5 seconds
Host constants:
	MAX_RTR_SOLICITATION_DELAY 1 second
	RTR_SOLICITATION_INTERVAL 4 seconds
	MAX_RTR_SOLICITATIONS 3 transmissions
Node constants:
	MAX_MULTICAST_SOLICIT 3 transmissions
	MAX_UNICAST_SOLICIT 3 transmissions
	MAX_ANYCAST_DELAY_TIME 1 second
	MAX_NEIGHBOR_ADVERTISEMENT 3 transmissions
	REACHABLE_TIME 30,000 milliseconds
	RETRANS_TIMER 1,000 milliseconds
	DELAY_FIRST_PROBE_TIME 5 seconds
	MIN_RANDOM_FACTOR .5
	MAX_RANDOM_FACTOR 1.5
***/
#define NW_TICKS_PER_SEC 1 //TODO
//#define NX_IPV6_DEFAULT_ROUTER_TABLE_SIZE 10 //TODO    
/**
 *****************************************************************************
 * @ingroup Gsn6ND
 * @brief 6ND state
 *    These macros defines state of 6ND. These are for internal use.
 *****************************************************************************/
#define GSN_RPL_6ND_STATE_NOT_INIT     0
#define GSN_RPL_6ND_STATE_INIT_IN_PROG 1
#define GSN_RPL_6ND_STATE_READY        2

/**
 *****************************************************************************
 * @ingroup Gsn6ND
 * @brief Callback function of the discovery.
 *    Callback function of the discovery.
 *****************************************************************************/
typedef VOID ( *GSN_RPL_6ND_CB_T )( VOID *pAppCtx, UINT32 event, UINT8* pData, 
    UINT32 len );


/**
 *****************************************************************************
 * @ingroup Gsn6ND
 * @brief CID context structure
 *    The structure defines CID context.
 *****************************************************************************/
typedef struct GSN_RPL_6ND_CFG
{
    GSN_RPL_IP_IF_T *pIpCfg; /**< BR address */
	
	UINT8 ifId;
	UINT8 mode;
	UINT16 maxNumOfNodes;
	VOID *pIP;
	UINT8 RAAdvertEnable; 
    /**< Call back top be called after the router discovery is complete. */	
	GSN_RPL_6ND_CB_T cb;
    VOID * pCbCtx;
	UINT32 MaxRtrAdvInterval;
	UINT32 MinRtrAdvInterval;
	
}GSN_RPL_6ND_CFG_T;

/**
 *****************************************************************************
 * @ingroup Gsn6ND
 * @brief Structre to define LBR information
 *    The structure stores LBR information.
 *****************************************************************************/

typedef struct GSN_RPL_6ND_LR_INFO
{
    UINT8 status;
}GSN_RPL_6ND_LR_INFO_T;

/**< addr and macAddr are of type UINT32* */
#define GSN_RPL_6ND_WRITE_LL64( addr, macAddr )                     \
{                                                                   \
    ( addr )[0] = 0xfe800000; ( addr )[1] = 0;                      \
    ( addr )[2] = ( macAddr )[1];                                   \
    ( addr )[3] = ( macAddr )[0];                                   \
}

typedef struct GSN_RPL_6ND_MAC_ADDR
{
	UINT32 macAddr[2];
}GSN_RPL_6ND_MAC_ADDR_T;
typedef struct GSN_RPL_MAC_TBL
{
	GSN_RPL_TABLE_INFO_T macTblFindInfo;
	UINT16 numOfEntries;
	UINT16 *pRplTblIndex;
	GSN_RPL_6ND_MAC_ADDR_T * pMacAddr;
}GSN_RPL_MAC_TBL;

/**
 *****************************************************************************
 * @ingroup Gsn6ND
 * @brief Context structure of 6ND
 *    The structure defines the context of 6ND.
 *****************************************************************************/
typedef struct GSN_RPL_6ND_CTX
{
	VOID *pNext;
    UINT8 mode; /**< Host, 6LR or 6LBR */
    UINT8 state;
	UINT8 RAAdvertEnable; 
	VOID *pRpl;
	VOID *pGAddrPtr;
	VOID *pLLAddrPtr;
	
    VOID *pIP; /**< stores the context of the IP stack */
    UINT8 ifId; /**< stores the context of the interface of in the stack */

    UINT16 shortAddr;
    UINT32 macAddr[2];

	UINT8 raFlag; /**< Stores the value of M and O flag */
	UINT16 routerLT; /**< Router life time */
	UINT32 reachableTime;
	UINT32 retransTime;

    /**< Indicates Router solicitation message send is in progress. A non zero 
    value indicates RS send is in progress. This variable stores number of RS 
    frames sent after initiating the Router discovery procedure. The discovery
    process can start 
    - default router list is empty, 
    - one of its default routers becomes unreachable, or
    - the lifetime of the prefixes and contexts in the previous RA is about to 
    expire.
    */
    UINT8 rsSendInP;
	UINT8 be; /**< backoff exponential */
    INT32 rsSendRemainingTick;

	UINT16 MinRtrAdvInterval; /**< Min and Max are configured by user */
	UINT16 MaxRtrAdvInterval;	
	/**< This is calculated as a random value between Min and Max. Once this 
	becomes 0, RT ADV is sent and again this value is polulated. */
	UINT16 RtrAdvInterval; 
	UINT8  advIf; /**< None zero when Advertising Interface. */

	/**< Callback to indicate events to the user */
	GSN_RPL_6ND_CB_T cb;
    VOID * pCbCtx;

	GSN_RPL_MAC_TBL macTbl;
}GSN_RPL_6ND_CTX_T;

#define GSN_RPL_6ND_SUCCESS        0
#define GSN_RPL_6ND_DUPLICATE_ADDR 1
#define GSN_RPL_6ND_NB_CACHE_FULL  2

#define GSN_RPL_6ND_EVENT_INIT_SUCCESS 0
#define GSN_RPL_6ND_EVENT_INIT_FAILURE 1
#define GSN_RPL_6ND_EVENT_ADDR_SET     2



/**
 *****************************************************************************
 * @ingroup Gsn6ND
 * @brief Initialization for 6ND module.
 *    This function performs initialization of 6ND module.
 * @param pCtx - IN Pointer to store the context.
 * @param pCfg - IN Configuration parameters.
 * @param pRpl - IN Pointer to the RPL context.
 * @retval Returns GSN_SUCCESS or GSN_FAILURE.
 * @note
 *    This function must be called during INIT before calling other 6ND API.
 *****************************************************************************/
GSN_STATUS GsnRpl_6ndInit( GSN_RPL_6ND_CTX_T *pCtx, GSN_RPL_6ND_CFG_T *pCfg, 
    VOID *pRpl, UINT32 * pMac );

VOID GsnRpl_6ndRASendCheck( VOID *pRplCtx );
VOID GsnRpl_6ndRSSendCheck( VOID *pRplCtx );
VOID GsnRpl_6ndDARSendCheck( VOID *pRplCtx );

VOID GsnRpl_6ndDeInit( GSN_RPL_6ND_CTX_T *pCtx );

#ifdef __cplusplus
}
#endif
#endif /* _GSN_6ND_H_ */
