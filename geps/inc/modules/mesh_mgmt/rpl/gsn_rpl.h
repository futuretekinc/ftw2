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
* $RCSfile: gsn_rpl.h,v $
*
* Description : This file contains function declaration for RPL APIs.
*******************************************************************************/

/*******************************************************************************
* File inclusion
*******************************************************************************/
#ifndef _GSN_RPL_H_
#define _GSN_RPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DBG_PRINT(...)  
  
//#define DBG_TRACE_FUNC DBG_PRINT("%s\n",__FUNCTION__);
#define DBG_TRACE_FUNC    

#define GSN_RPL_EVENT_SCAN_CFM 0
#define GSN_RPL_EVENT_DODAG_CREATE_SUCCESS 1
#define GSN_RPL_EVENT_DODAG_CREATE_FAILURE 2
#define GSN_RPL_EVENT_DODAG_JOIN_SUCCESS   3
#define GSN_RPL_EVENT_DODAG_JOIN_FAILURE   4
#define GSN_RPL_EVENT_SET_ADDRESS          5
#define GSN_RPL_EVENT_SET_CO               6




typedef struct GSN_RPL_DODAG_CFG 
{ 
    /**< All 16-bit parameters are written in htons format */
    UINT8 aPcs; /**< A and PCS Field */    
    UINT8 dioIntervalDoublings; /**< Time in msec, map to trickle Imax */
    UINT8 dioIntervalMin; /**< Time in msec, map to trickle Imin */
    UINT8 dioRedundancyConstant;
    UINT16 maxRankIncrease;    
    UINT16 minHopRankIncrease;
    UINT16 ocp;
    UINT8 reserved;
    UINT8 dfltLifeTime;
    UINT16 lifetimeUnit;
}GSN_RPL_DODAG_CFG_T;

typedef VOID ( *GSN_RPL_CB_T )( VOID *pCtx, UINT32 event, VOID* pResult );

#define GSN_RPL_MODE_HOST   2
#define GSN_RPL_MODE_ROUTER 1
#define GSN_RPL_MODE_BR     0

/**< Configuration flag */
#define GSN_RPL_CFG_FLAG_MULTI_PREFIX_SUPPORT     ( 1 << 0 )
#define GSN_RPL_CFG_FLAG_SHORT_ADDR_SUPPORT       ( 1 << 1 )
#define GSN_RPL_CFG_FLAG_STORING_SUPPORTED        ( 1 << 2 )
#define GSN_RPL_CFG_FLAG_DROUTING_SUPPORTED       ( 1 << 3 )


typedef struct GSN_RPL_CFG
{
    UINT8  maxDODAG; /**< Max number of DODAG supported */
    UINT8  maxNbE; /**< Max number of Neighbour entries */
    UINT8  maxParents; /**< Max number of Parents entries */
    UINT16 maxRtE; /**< Max number of Routing entries */
    UINT8  maxPrefix; /**< Max number of Prefix entries in the network */
    /**< Configuration flag */
    UINT8  flag;   
}GSN_RPL_CFG_T;

typedef struct GSN_RPL_SCAN_RESULT
{
    UINT32 DODAGID[4];
    UINT16 OC;
	UINT8  Storing;
	UINT8  MultiPrefix;
}GSN_RPL_SCAN_RESULT_T;


typedef struct GSN_RPL_SCAN_REQ
{
    INT8   isActive; /**< set to 1 if, active, else 0 */
    UINT32 timeout;
    VOID*  pAppCtx;
    GSN_RPL_CB_T cb;
    UINT16 OC;
    UINT32 resultSize;
    GSN_RPL_SCAN_RESULT_T scanResult[1];
}GSN_RPL_SCAN_REQ_T;

/**< Delay processing callback has to be provided by user. All timer related 
expires are handled in a delay handler. This ensure that no time taking 
activities are not done in the timer thread / isr context. User calls the delay
handler of RPL from a thread context to process the RPL event. */
typedef VOID ( *GSN_RPL_DELAY_PROCESS_T )( VOID *pUsrCtx, VOID *pCtx );
typedef VOID ( *GSN_RPL_EVENT_PROC_CB_T )( VOID *pCtx, UINT32 event );
typedef struct GSN_RPL_EVENT
{
	struct GSN_RPL_EVENT *pNext;
	GSN_RPL_EVENT_PROC_CB_T cb;
	VOID *pCtx;
	UINT32 event;
}GSN_RPL_EVENT_T;
typedef struct GSN_RPL
{
    VOID *pNwkCtx;  /**< Points to the NX_IP */
    VOID *pSrcAddr; /**< Points to NXD_IPV6_ADDRESS *outgoing_address */

    UINT8 state;
	UINT8 flag;
            
    GSN_SOFT_TMR_T tmr;
	GSN_RPL_EVENT_T tmrEvent;
    /**< DODAG context to be allocated based on cfg paremeter */
    VOID *pDODAGHead; 
	VOID *pNDHead;

    GSN_RPL_SCAN_REQ_T *pScanReq;
    UINT8 currentIndex;
    	
    VOID* pRplTbl;

	GSN_RPL_DELAY_PROCESS_T delayProcess;
	VOID *pUsrCtx;
	VOID *pEventHead;
	VOID *pEventTail;
}GSN_RPL_T;

typedef struct GSN_RPL_IP_IF
{
    /**< Including the prefix and the autogenerated Host ID usig MAC address */
    UINT32 ipAddr[ 4 ]; 
    UINT32 lifeTime; /**< Life time of the prefix used */
}GSN_RPL_IP_IF_T;

typedef struct GSN_RPL_DODAG_BASIC_CFG
{      
    /**< Mode */
    UINT8 mode; /**< 0: Host, 1: Router, 2: Border Router */
    UINT8 dfltDAODelay;

    /**< Objective function the user wants to use */
    UINT16 OF;
	UINT8  ifId;
}GSN_RPL_DODAG_BASIC_CFG_T;

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Initialize the RPL module.
 *    This function initailize the RPL module. 
 * @param pCtx - IN Pointer to the RPL context.
 * @retval
 * @note
 *    
 ******************************************************************************/
GSN_STATUS GsnRpl_Init( GSN_RPL_T *pCtx, VOID *pNWCtx, 
	GSN_RPL_DELAY_PROCESS_T delayProcess, VOID *pUsrCtx );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Set the RPL configuration.
 *    This function sets the RPL configuration. This API should be called after 
 * initializing RPL modele. User can scan for DODAG. Based on the decision made
 * user can use this function to configure the RPL module.  
 * @param pCtx - IN Pointer to the RPL context.
 * @param pCfg - IN Pointer to configure RPL module.
 * @retval
 * @note
 *    This API has to be called before calling DODAG Init.
 ******************************************************************************/
GSN_STATUS GsnRpl_ConfigSet( GSN_RPL_T *pCtx, GSN_RPL_CFG_T* pCfg );


INLINE GSN_RPL_SCAN_REQ_T *
    GsnRpl_AllocMemForScanReq( UINT16 resultSize )
{
    return (GSN_RPL_SCAN_REQ_T *)malloc( sizeof( GSN_RPL_SCAN_REQ_T ) +
        ( resultSize - 1 ) * sizeof( GSN_RPL_SCAN_RESULT_T ));
}

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Scans for DODAG.
 *    This function scans for DODAG. 
 * @param pCtx - IN Pointer to the RPL context.
 * @param pCtx - IN Pointer to the Scan Configuration.
 * @retval
 * @note This API should be called after Init API. This API can be used to find
 * a suitable DODAG and configurare the RPL accordingly. If the user is aware of
 * of the presense of the DODAG or wants to creates a DODAG then directly 
 * DODAGInit can be called without doing the scanning.
 ******************************************************************************/
GSN_STATUS GsnRpl_DODAGScan( GSN_RPL_T *pCtx, GSN_RPL_SCAN_REQ_T *pScanReq, UINT8 ifId );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Initialize the DODAG module.
 *    This function initializes the DODAG module. 
 * @param pCtx - IN Pointer to the RPL context.
 * @param pCtx - IN Pointer to the RPL Configuration.
 * @retval Returns pointer to the DODAG pointer created by this API. This 
 * pointer has to be passed in other APIs related to DODAG.
 * @note This API should be called after RPL Init API. This API installs the OF
 * function pointer and the configuration on DODAG mode the node will be 
 * operating and the details to allocate memory to create DODAG tables.
 ******************************************************************************/
VOID* GsnRpl_DODAGInit( GSN_RPL_T *pCtx, GSN_RPL_DODAG_BASIC_CFG_T *pCfg, 
    GSN_RPL_CB_T pCb, VOID *pAppCtx );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Create DODAG.
 *    This function creates DODAG. 
 * @param pCtx - IN Pointer to the RPL context.
 * @param pDODAGCtx - IN Pointer to the DODAG context returned in DODAG Init API.
 * @param pCtx - IN Pointer to the DODAG Configuration.
 * @retval
 * @note This API should be called after DODAG Init API. 
 ******************************************************************************/
GSN_STATUS GsnRpl_DODAGCreate( GSN_RPL_T *pCtx, VOID* pDODAGCtx, 
    GSN_RPL_DODAG_CFG_T *pDODAGCfg, GSN_RPL_IP_IF_T *pIpIf, UINT32* pMacAddr );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Join DODAG.
 *    This function joins a DODAG. 
 * @param pCtx - IN Pointer to the RPL context.
 * @param pDODAGCtx - IN Pointer to the DODAG context returned in DODAG Init API.
 * @param DODAGSelectionTime - IN Time spent in selecting DODAG parent. RPL will
 * start receiving for the DIO messages and once the DODAGSelectionTime elapse 
 * it start selection pricedure.
 * @retval
 * @note This API should be called after DODAG Init API. Selection of DODAG is
 * based on the parameter given in the DODAG Init. Based on the DODAG mode the 
 * module will either act as a router or a host.
 ******************************************************************************/
GSN_STATUS GsnRpl_DODAGJoin( VOID* pDODAGCtx, 
    UINT32 DODAGSelectionTime, UINT8 CO6Enable, UINT32* pMacAddr );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Stop DODAG.
 *    This function Stop a DODAG. 
 * @param pDODAGCtx - IN Pointer to the DODAG context returned in DODAG Init API.
 * @retval
 * @note This API should be called after DODAG Init API. By calling this the 
 * node disconnets itself from the DIDAG and frees up all the memory allocated 
 * to maintain the DODAG.
 ******************************************************************************/
GSN_STATUS GsnRpl_DODAGStop( VOID* pDODAGCtx );


GSN_STATUS GsnRpl_DelayHandler( GSN_RPL_T *pCtx );
GSN_STATUS GsnRpl_DeInit( GSN_RPL_T *pCtx );
GSN_STATUS GsnRpl_DODAGGetAddr( VOID* pDCtx, UINT32 *pLLAddr, UINT32 *pGAddr );

#ifdef __cplusplus
}
#endif
#endif /* _GSN_RPL_H_ */


