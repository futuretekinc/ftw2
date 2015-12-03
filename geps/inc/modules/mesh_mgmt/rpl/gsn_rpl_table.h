/*******************************************************************************
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
* $RCSfile: gsn_rpl_table.h,v $
*
* Description : This file contains structure and function defination for RPL 
* table management.
*******************************************************************************/
#ifndef _GSN_RPL_TABLE_H_
#define _GSN_RPL_TABLE_H_

#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
* File inclusion
*******************************************************************************/
#define GSN_RPL_MULTI_PREFIX_ENABLE
#define GSN_RPL_16_BIT_ADDRESS_ENABLE
#define GSN_RPL_6_CO_ENABLE

#if !defined( GSN_RPL_MULTI_PREFIX_ENABLE ) && defined( GSN_RPL_6_CO_ENABLE )
#error "MULTI PREFIX SUPPORT NEEDED FOR 6CO"
#endif

#define GSN_RPL_MAX_NB_ENTRIES      32
#define GSN_RPL_MAX_RT_ENTRIES      1000
#define GSN_RPL_MAX_PARENT_ENTRIES  4    
#define GSN_RPL_MAX_PREFIX_SUPPORT  16    

#define GSN_RPL_TENTATIVE_NCE_LIFETIME     20


/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief MACRO to find the IP address size to store in RT table.
 *    MACRO to find the IP address size to store in RT table.
 *
 * Case Multi-prefix    16-bit      6-CO   Address  Description 
 *        network       address    support size
 * 1    TRUE            TRUE        TRUE     3      2 bytes for 16-bit 
 *                                                  address 1 byte to index
 *                                                  to the prefix list.     
 *
 * 2    TRUE            TRUE        FALSE    3      2 bytes for 16-bit 
 *                                                  address.1 byte to index 
 *                                                  to the prefix list. 
 *
 * 3    TRUE            FALSE       TRUE     9      8 bytes for EUI64 
 *                                                  address.1 byte to index 
 *                                                  to the prefix list.
 *
 * 4    TRUE            FALSE       FALSE    9      8 bytes for EUI64 
 *                                                  address.1 byte to index 
 *                                                  to the prefix list.
 *
 * 5    FALSE           TRUE        FALSE    2      2 bytes for 16-bit 
 *                                                  address.    
 *
 * 6    FALSE           FALSE       FALSE    8      8 bytes for EUI64 
 *                                                  address.    
 ******************************************************************************/
#if  defined( GSN_RPL_MULTI_PREFIX_ENABLE ) && defined( GSN_RPL_16_BIT_ADDRESS_ENABLE )
#define GSN_RPL_ADDR_SIZE 3
#elif defined( GSN_RPL_MULTI_PREFIX_ENABLE ) && !defined( GSN_RPL_16_BIT_ADDRESS_ENABLE )
#define GSN_RPL_ADDR_SIZE 9
#elif !defined( GSN_RPL_MULTI_PREFIX_ENABLE ) && defined( GSN_RPL_16_BIT_ADDRESS_ENABLE )
#define GSN_RPL_ADDR_SIZE 2
#elif !defined( GSN_RPL_MULTI_PREFIX_ENABLE ) && !defined( GSN_RPL_16_BIT_ADDRESS_ENABLE )
#define GSN_RPL_ADDR_SIZE 8
#endif

#define GSN_RPL_MAX_ADDR_SIZE 12
    
#define GSN_RPL_CFG_FLAG_MP_ENABLE 1
#define GSN_RPL_CFG_FLAG_16BIT_ADDR_ENABLE 2

#define GSN_RPL_TABLE_ADDR_SIZE( cfgFlag, addrSize )       \
    if(( cfgFlag & GSN_RPL_CFG_FLAG_MP_ENABLE ) &&         \
       ( cfgFlag & GSN_RPL_CFG_FLAG_16BIT_ADDR_ENABLE ))   \
        addrSize = 3;                                      \
    else if(( cfgFlag & GSN_RPL_CFG_FLAG_MP_ENABLE ) &&    \
       !( cfgFlag & GSN_RPL_CFG_FLAG_16BIT_ADDR_ENABLE ))  \
        addrSize = 9;                                      \
    else if(!( cfgFlag & GSN_RPL_CFG_FLAG_MP_ENABLE ) &&   \
       ( cfgFlag & GSN_RPL_CFG_FLAG_16BIT_ADDR_ENABLE ))   \
        addrSize = 2;                                      \
    else if(!( cfgFlag & GSN_RPL_CFG_FLAG_MP_ENABLE ) &&   \
       !( cfgFlag & GSN_RPL_CFG_FLAG_16BIT_ADDR_ENABLE ))  \
        addrSize = 8;


/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief MACRO to find the total size of various table.
 *    MACRO to find the total size of various table.
******************************************************************************/
#define GSN_RPL_TABLE_SIZE( maxDODAG, maxNb, maxParent, maxRt, maxPrefix,    \
    addrSize )                                                               \
    ( maxDODAG ) * sizeof( GSN_RPL_DODAG_ENTRY_T ) +                         \
    ( maxNb ) * sizeof( GSN_RPL_NB_ENTRY_T ) +                               \
    ( maxRt ) * sizeof( GSN_RPL_RT_ENTRY_T ) +                               \
    ( maxParent ) * sizeof( GSN_RPL_PARENT_ENTRY_T ) +                       \
    ( maxPrefix ) * sizeof( GSN_RPL_PREFIX_ENTRY_T ) +                       \
    ( maxNb + maxRt ) *  addrSize +                                          \
    sizeof( GSN_RPL_TABLE_T )    


#define NB_INDEX UINT8
#define RT_INDEX UINT16 
#define NB_INDEX_NULL (( 1 << ( sizeof( NB_INDEX ) * 8 )) - 1 )
#define RT_INDEX_NULL (( 1 << ( sizeof( RT_INDEX ) * 8 )) - 1 )       
        
/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief MACRO defines the relation with the neighbour.
 *    MACRO defines the relation with the neighbour..
******************************************************************************/        
#define GSN_RPL_NB_TYPE_NO_RELATION   ( 0 )
#define GSN_RPL_NB_TYPE_CHILD_HOST    ( 1 )
#define GSN_RPL_NB_TYPE_CHILD_ROUTER  ( 2 )
#define GSN_RPL_NB_TYPE_PARENT        ( 3 )

#define GSN_DODAG_RANK_SAME  0
#define GSN_DODAG_RANK_BIG   1
#define GSN_DODAG_RANK_LESS  2

#define GSN_RPL_PAT_UPDATE_STAT_SUC     0
#define GSN_RPL_PAT_UPDATE_STAT_NB      1
#define GSN_RPL_PAT_UPDATE_STAT_ADDR    2
#define GSN_RPL_PAT_UPDATE_STAT_UPDATE  3

#define GSN_RPL_RTT_SUCCESS             0
#define GSN_RPL_RTT_PARENT_NOT_PRESENT  1
#define GSN_RPL_RTT_CHILD_NOT_PRESENT   2
#define GSN_RPL_RTT_PATH_INCOMPLETE     3


/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Structure, defination for DODAG Table Entry.
 *    Structure defining DODAG Table entries.
 ******************************************************************************/
typedef struct GSN_RPL_DODAG_ENTRY
{
    UINT8 maxNumOfEntries;
    UINT8 numOfEntries;
    NB_INDEX ParentHead;
    NB_INDEX PrefParentHead;
    UINT8 *pDODAGCtx;
}GSN_RPL_DODAG_ENTRY_T;

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Structure, defination for NB Table.
 *    Structure defining Neighbor table.
 ******************************************************************************/
typedef struct GSN_RPL_DODAG_TBL
{
    NB_INDEX maxNumOfEntries;   
    NB_INDEX numOfEntries;    
    GSN_RPL_DODAG_ENTRY_T *dEntries;
}GSN_RPL_DODAG_TBL_T;

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Structure, defination for NB Entry.
 *    Structure defining Neighbor entries.
 ******************************************************************************/
typedef struct GSN_RPL_NB_ENTRY
{    
    ULONG  macAddr[2];
    UINT8  flag; /**< Stores information about the neighbour node, e.g. a child 
    router or child host or parent */
    UINT8  lqi;
    UINT8  remainingLife;
    /**< Rank of the node if this is selected as patent. It is not the rank 
    advertised in the DIO frame. Suppose Node A is maintaining the NB table
    and receives a DIO frame from Node B, with rank R, node A calcualteshis 
    rank if B is his parent. */
    UINT16 rank; 
    UINT8  daoSeq;
    UINT8  state;      
}GSN_RPL_NB_ENTRY_T;    

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Structure, defination for Parent Entry.
 *    Structure defining Parent entry.
 ******************************************************************************/
typedef struct GSN_RPL_PARENT_ENTRY
{
    NB_INDEX preferedLink; /**< Links the parent list shorted based on the  NB rank */
    /**< Links the parent list. This link stores the actual parent order 
    maintained. This may be diferent than then link in preferedLink. Whenever 
    ndoe decides to change the parent order, it becomes same as the preferedLink. */
    NB_INDEX parentLink; 
    NB_INDEX nbIndex; /**< ND table index */

    UINT8  dtsn;
    UINT8  lifeTime;    
	UINT8  DODAGAEntryIndex;
	UINT8  daosent_count; /** nomber of times DAO Re-send happens to receive DAO-ACK **/
	UINT8  valid;  /** untill receiving DAO-ACk parent is not valid, if valid valid = 1 , else 0 **/
}GSN_RPL_PARENT_ENTRY_T;


/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Structure, defination for routing table entry.
 *    Structure defining routing table entry.
 ******************************************************************************/
typedef struct GSN_RPL_RT_ENTRY
{    
    /**< ND table index through which the node can be reachable */
    RT_INDEX parent; 
    UINT8   remainingLife;
    UINT8   pathSeqNum;
}GSN_RPL_RT_ENTRY_T;

typedef struct GSN_RPL_PREFIX_ENTRY
{
    UINT32  prefix[2];
    UINT32 validLifetime;
    UINT32 preferedLifetime;
    UINT8  prefixFlag;
    UINT8  DODAGAEntryIndex;
    UINT16 path;
    UINT8  cid;
    UINT16 cidLifeTime;
}GSN_RPL_PREFIX_ENTRY_T;

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Structure, defination for DODAG Parent.
 *    Structure defining DODAG Parent.
 ******************************************************************************/
typedef struct GSN_RPL_PARENT
{
    /**< The parent set is a restricted subset of the neighbor set. A node can 
    maintain multiple nodes in its parent set. maxNumOfEntries specifies how 
    many nodes can be maintained in its parent set */
    NB_INDEX maxNumOfEntries;

    GSN_RPL_PARENT_ENTRY_T *parentEntries;
}GSN_RPL_PARENT_T;


/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Structure, defination for NB Table.
 *    Structure defining Neighbor table.
 ******************************************************************************/
typedef struct GSN_RPL_NB
{
    NB_INDEX maxNumOfEntries;   
    NB_INDEX numOfEntries;
    NB_INDEX numOfParents;
    NB_INDEX numOfTentativeEntries;
    GSN_RPL_NB_ENTRY_T *nbEntries;
    UINT8* pAddr; 
}GSN_RPL_NB_T;

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Structure, defination for routing table.
 *    Structure defining routing table.
 ******************************************************************************/
typedef struct GSN_RPL_RT
{
    RT_INDEX maxNumOfEntries;
    UINT16 numOfEntries;
    UINT16 maxDepth;
    GSN_RPL_RT_ENTRY_T *rttEntries;
    UINT8* pAddr;
}GSN_RPL_RT_T;

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Structure, defination for Prefix table.
 *    Structure defining Prefix table.
 ******************************************************************************/
typedef struct GSN_RPL_PT
{
    NB_INDEX maxNumOfEntries;
    NB_INDEX numOfEntries;
    GSN_RPL_PREFIX_ENTRY_T *pPtEntries;
}GSN_RPL_PT_T;

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Structure, defination used internally in RPL table management.
 *    Structure defining routing table.
 ******************************************************************************/
typedef INT32 ( *GSN_RPL_ADDR_COMAPRE_T )( UINT8 *pSrc, UINT8 *pDst );
typedef struct GSN_RPL_TABLE_INFO
{
    UINT8  tblElemSize;
    UINT16 tblSize;
    GSN_RPL_ADDR_COMAPRE_T compareFn;    
}GSN_RPL_TABLE_INFO_T;

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Structure, defination for rpl table.
 *    Structure defining rpl table.
 ******************************************************************************/
typedef struct GSN_RPL_TABLE
{
    UINT8 addrSize;
    GSN_RPL_DODAG_TBL_T dt;
    GSN_RPL_NB_T nb;
    GSN_RPL_PARENT_T parent;
    GSN_RPL_RT_T rtt;
    GSN_RPL_PT_T pt;
        
    GSN_RPL_TABLE_INFO_T rplNbTblInfo;
    GSN_RPL_TABLE_INFO_T rplRttTblInfo;
    GSN_RPL_TABLE_INFO_T rplPtTblInfo;
}GSN_RPL_TABLE_T;

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Get a Free DODAG entry.
 *    This function gets a free DODAG entry. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @retval if an free entry is found it returns values between 0 to the max 
 * DODAG entry set minus 1, else returns 0xFF.
 * @note
 *    
 ******************************************************************************/
UINT8 GsnRpl_TblDODAGGetFreeId( GSN_RPL_TABLE_T* pRplTbl );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Add a DODAG entry.
 *    This function Adds a DODAG entry. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @param Id - IN ID were the entry has to be added.
 * @param pDODAGCtx - IN Pointer to the DODAG context.
 * @retval if an free entry is found it returns values between 0 to the max 
 * DODAG entry set minus 1, else returns 0xFF.
 * @note
 *    
 ******************************************************************************/
VOID GsnRpl_TblDODAGAddId( GSN_RPL_TABLE_T* pRplTbl, UINT8 Id, 
    VOID *pDODAGCtx );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Initialize the RPL table.
 *    This function initializes the RPL tables. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @param maxNb - IN Maximum number of Neighbour to support.
 * @param maxParent - IN Maximum number of Parents to support.
 * @param maxRt - IN Maximum number of Routing information to support.
 * @param maxPrifix - IN Maximum number of Prefix to support.
 * @retval 
 * @note
 *    
 ******************************************************************************/
GSN_STATUS GsnRpl_TblInit( UINT8 *pRplTable, UINT32 size, UINT8 maxDODAG, 
    UINT8 maxNb, UINT8 maxParent, UINT32 maxRt, UINT32 maxPrefix, 
    UINT32 cfgFlag );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Gets the NB entry for the IP address provided.
 *    This function finds the NB entry for the IP address provided. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pIpAddr - IN Pointer to IPv6 address to search in the NB table.
 * @param pState - OUT Pointer to store the state of the entry.
 * @retval if the entry is found it returns the pointer to the entry else 
 * returns pointer where it can be added. This pointer can be passed to "Add API"
 * to add the entry. The "Add API" would run faster if the pointer is passed.
 * @note
 *    
 ******************************************************************************/
GSN_RPL_NB_ENTRY_T* GsnRpl_TblNbEntryGet( GSN_RPL_TABLE_T* pRplTable, 
    UINT8* pIpAddr, GSN_STATUS* pState );

GSN_RPL_NB_ENTRY_T*
GsnRpl_TblNbMacAddrEntryGet( GSN_RPL_TABLE_T* pRplTbl, UINT32 *pMac );
GSN_RPL_NB_ENTRY_T*
GsnRpl_TblNbMacAddrEntryAdd( GSN_RPL_TABLE_T* pRplTbl, UINT32 *pMac );


/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Adds a NB entry.
 *    This function adds a NB entry. If the entry is already present then it 
 * updates the lastHeard field to mark it active.
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pEntry - IN Pointer to the NB entry, after which this entry has to 
 * be added. 
 * @param pAddr - IN Pointer to the address of the neighbour entry.
 * @retval if an entry is alredy exist or if not it tries to get a free entry 
 * then it returns the pointer to the entry else returns NULL.
 * @note
 *    
 ******************************************************************************/
GSN_RPL_NB_ENTRY_T* GsnRpl_TblNbEntryAdd( GSN_RPL_TABLE_T* pRplTable, 
    GSN_RPL_NB_ENTRY_T* pEntry, UINT8 *pIpAddr );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Remove a NB entry.
 *    This function removes a NB entry. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pEntry - IN Pointer to the NB entry.
 * @param pAddr - IN Pointer to the IPv6 address. If pEntry is NULL then this
 * pointer is used to find the entry to remove it from the list.
 * @retval if an free entry is found it returns the pointer to the entry else 
 * returns NULL.
 * @note
 *    
 ******************************************************************************/
GSN_STATUS GsnRpl_TblNbEntryRemove( GSN_RPL_TABLE_T* pRplTable, 
    GSN_RPL_NB_ENTRY_T* pEntry, UINT8 *pAddr );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Remove a NB entry.
 *    This function removes a NB entry. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pEntry - IN Pointer to the NB entry.
 * @param pAddr - IN Pointer to the IPv6 address location where the IP address 
 * has to be written. 
 * @retval GSN_SUCCESS if IP address is calculated successfully else GSN_FAILURE.
 * @note
 *    
 ******************************************************************************/
GSN_STATUS GsnRpl_TblNbEntryGetIP( GSN_RPL_TABLE_T* pRplTable, 
    GSN_RPL_NB_ENTRY_T* pEntry, UINT8* pIpAddr );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Remove a NB entry.
 *    This function removes a NB entry. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pEntry - OUT Pointer to store the child IP address.
 * @param pEntry - IN Pointer to NB entry for getting the next child.
 * @retval Pointer to store the NB entry for getting the next child. This has to
 * be passed when next call is made to get the next childs IP address.
 * @note
 *    
 ******************************************************************************/
UINT8* GsnRpl_TblGetNextChildIp( GSN_RPL_TABLE_T* pRplTable, UINT8* pIpAddr, 
    UINT8* pEntry );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Get a free entry for parent.
 *    This function gets a free entry for parent. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pAddr - IN Pointer to the IPv6 address. 
 * @retval if an free entry is found it returns the pointer to the entry else 
 * returns NULL.
 * @note
 *    This API adds a parent to the parents table. It checks the if the Address 
 * is already there in the neighbour table, if not then creates an entry. It  
 * then links the neighbour entry in the parent entry.
 ******************************************************************************/
GSN_RPL_PARENT_ENTRY_T* GsnRpl_TblParentEntryAdd( GSN_RPL_TABLE_T* pRplTable, 
    GSN_RPL_NB_ENTRY_T* pEntry,UINT8* pAddr );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Removes entry from parent list.
 *    This function removes an entry from the parent list. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pIpAddr - IN Pointer to the IPv6 address.
 * @retval
 * @note
 *    
 ******************************************************************************/
GSN_STATUS GsnRpl_TblParentEntryRemove( GSN_RPL_TABLE_T* pRplTbl, 
    UINT8 DODAGId, GSN_RPL_PARENT_ENTRY_T* pPAEntry );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Removes entry from parent list.
 *    This function removes an entry from the parent list. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pIpAddr - IN Pointer to the IPv6 address.
 * @retval returns GSN_FAILURE if the parent set is NULL else GSN_SUCCESS
 * @note
 *    
 ******************************************************************************/
GSN_RPL_PARENT_ENTRY_T* GsnRpl_TblParentEntryRemoveGivenIP( 
    GSN_RPL_TABLE_T* pRplTbl, UINT8 DODAGId, UINT8* pIPAddr );


/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Gets the parent entry given the IP address.
 *    This function gets the parent entry given the IP address. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pMacAddr - IN Pointer to the MAC address.
 * @retval
 * @note
 *    
 ******************************************************************************/
GSN_RPL_PARENT_ENTRY_T* GsnRpl_TblParentEntryGetMac( GSN_RPL_TABLE_T* pRplTbl, 
    UINT8 DODAGId, GSN_RPL_PARENT_ENTRY_T* pPEntry, UINT8** pMacAddr );


INLINE UINT16 GsnRpl_TblParentRankGet( GSN_RPL_TABLE_T* pRplTbl,
    GSN_RPL_PARENT_ENTRY_T* pPEntry )
{
    return pRplTbl->nb.nbEntries[ pPEntry->nbIndex ].rank;
}

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Remove a NB entry.
 *    This function removes a NB entry. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pEntry - IN Pointer to the Parent entry.
 * @param pIpAddr - IN Pointer to the IPv6 address location where the IP address 
 * has to be written. 
 * @retval GSN_SUCCESS if IP address is calculated successfully else GSN_FAILURE.
 * @note
 *    
 ******************************************************************************/
GSN_STATUS GsnRpl_TblParentGetIP( GSN_RPL_TABLE_T* pRplTbl, 
    UINT8 DODAGId, GSN_RPL_PARENT_ENTRY_T* pPEntry, UINT8 *pIpAddr );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Get next prefered parent.
 *    This function gets the next prefered parent address.
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pPEntry - IN Pointer to the current parent entry.
 * @retval
 * @note
 *    
 ******************************************************************************/
GSN_RPL_PARENT_ENTRY_T * GsnRpl_TblParentGetNextPrefered( 
    GSN_RPL_TABLE_T* pRplTbl, UINT8 DODAGId, GSN_RPL_PARENT_ENTRY_T* pPAEntry );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Get next parent.
 *    This function gets the next prefered parent address.
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pPEntry - IN Pointer to the current parent entry.
 * @retval
 * @note
 *    
 ******************************************************************************/
GSN_RPL_PARENT_ENTRY_T * GsnRpl_TblParentGetNext( 
    GSN_RPL_TABLE_T* pRplTbl, UINT8 DODAGId, GSN_RPL_PARENT_ENTRY_T* pPAEntry );

INLINE UINT8* GsnRpl_TblParentMacGet( GSN_RPL_TABLE_T* pRplTbl, UINT8 DODAGIdx )
{
    GSN_RPL_PARENT_ENTRY_T * pP = GsnRpl_TblParentGetNext( pRplTbl, DODAGIdx, 
        NULL );

    return ( UINT8* )pRplTbl->nb.nbEntries[ pP->nbIndex ].macAddr;
}

INLINE GSN_RPL_NB_ENTRY_T* 
    GsnRpl_TblParentNbEntryGet( GSN_RPL_TABLE_T* pRplTbl, UINT8 DODAGId )
{
    GSN_RPL_PARENT_ENTRY_T* pPEntry = GsnRpl_TblParentGetNext( pRplTbl, DODAGId,
        NULL );
    return &pRplTbl->nb.nbEntries[ pPEntry->nbIndex ];
}

GSN_RPL_PARENT_ENTRY_T* 
GsnRpl_TblParentEntryGetFromMacAddr(GSN_RPL_TABLE_T* pRplTbl, UINT8* pMacAddr );

VOID GsnRpl_TblUpdateParentList( GSN_RPL_TABLE_T* pRplTbl, UINT8 DODAGId );


/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Update the prefered parent list.
 *    This function updates the prefered parent list. It puts the parent with 
 * lowest rank (closer to root) at the head of the parent list. It arranges the 
 * parents in assesnding order of their rank.
 * @param pRplTable - IN Pointer to the RPL table.
 * @retval
 * @note
 *    
 ******************************************************************************/

GSN_RPL_PARENT_ENTRY_T * GsnRpl_TblParentEntryUpdate( GSN_RPL_TABLE_T* pRplTbl, 
    VOID* pNBEntryInfo, UINT8 DODAGId, UINT16 Rank, GSN_STATUS *pStatus );



/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Remove the prefix entry from the prefix table.
 *    This function remove the prefix entry from the prefix table.
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pPrefix - IN Pointer to the Prefix to be removed from the table.
 * @param pPTEntry - IN Pointer to the Prefix entry to be removed. If the user 
 * knows the entry, then this can be passed, so that the function will avoid 
 * seraching the entry from the refix table.
 * @retval returns the index it removed.
 * @note
 *    
 ******************************************************************************/
UINT8 GsnRpl_TblPTEntryRemove( GSN_RPL_TABLE_T* pRplTbl, UINT8 idx , UINT8 DODAGId);

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Adds the prefix entry in the prefix table.
 *    This function adds the prefix entry in the prefix table.
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pPrefix - IN Pointer to the Prefix to be added from the table.
 * @param  DODAGId - IN specifies DODAGIdx
 * @retval returns the index it removed.
 * @note
 *    
 ******************************************************************************/
VOID* GsnRpl_TblPTEntryAdd( GSN_RPL_TABLE_T* pRplTbl, UINT8 *pPrefix, 
    UINT8 DODAGId );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Gets the next prefix address in the prefix table.
 *    This function returns the next prefix entry in the prefix table. This API 
 * is used to get the list of prefix the node has.
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pIdx - IN/OUT Pointer to store the index to the prefix table. User has
 * to populate it with NB_INDEX_NULL for the first time it calls to this API. 
 * This pointer is updated with the current index it points to. 
 * @retval returns the address to the prefix on success, else returns NULL.
 * @note
 *    
 ******************************************************************************/
UINT8* GsnRpl_TblPTEntryGetNext( GSN_RPL_TABLE_T* pRplTable, UINT8 *pIdx );

UINT8 GsnRpl_TblPTEntryGet( GSN_RPL_TABLE_T* pRplTbl, UINT8 *pPrefix );
VOID GsnRpl_TblPTSetPath( GSN_RPL_TABLE_T* pRplTbl, VOID* *pPrefix, 
    VOID* pEntry, UINT8 isNB );
GSN_RPL_PARENT_ENTRY_T * GsnRpl_TblParentEntryRemoveGivenNB( 
    GSN_RPL_TABLE_T* pRplTbl, UINT8 DODAGId, GSN_RPL_NB_ENTRY_T* pNb );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Find entry from the routing list.
 *    This function finds an entry from the routing table list. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pAddr - IN Pointer to the address.
 * @retval
 * @note
 *    
 ******************************************************************************/
GSN_RPL_RT_ENTRY_T*
GsnRpl_TblRttEntryGet( GSN_RPL_TABLE_T* pRplTable, UINT8 *pAddr , GSN_STATUS* pState);

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Adds a routing entry.
 *    This function adds a routing entry from routing table. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pREntry - IN Pointer to RT Entry if the address is already searched, 
 * else user can pass NULL.
 * @param pAddr - IN Pointer to the address of the node.
 * @param newElement - IN specifies whether the element is a new one.
 * @retval if an entry is alredy present in the table then this entry is made 
 * active. If it is not present then a free entry is found. If found it returns 
 * the pointer to the entry else returns NULL.
 * @note
 *    
 ******************************************************************************/
GSN_RPL_RT_ENTRY_T* GsnRpl_TblRttEntryAdd( GSN_RPL_TABLE_T* pRplTable, 
    GSN_RPL_RT_ENTRY_T* pREntry, UINT8 *pAddr );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Removes entry from Routing table.
 *    This function removes an entry from the routing table. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pEntry - IN Pointer to the route entry.
 * @param pAddr - IN Pointer to the address of the node. If pEntry is NULL then 
 * the address mentioned in this pointer is searched in the routing table to 
 * remove the entry.
 * @retval
 * @note
 *    
 ******************************************************************************/
GSN_STATUS
GsnRpl_TblRttEntryRemove( GSN_RPL_TABLE_T* pRplTable, GSN_RPL_RT_ENTRY_T* pEntry, 
    UINT8 *pAddr );

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Marks an Routing table entry as a parent of another routing table 
 * entry .
 *    This function marks an routing table entry as a parent of another routing
 * table entry. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pPEntry - IN Pointer to the parent entry.
 * @param isNb - IN TRUE if the parent entry is a neighbour, else FALSE.     
 * @param pCRtEntry - IN Pointer to the child entry.
 * @param parentIdx - IN Index of parent. A node can declare multiple parents, 
 *    this indicates which parent index. 
 * @retval
 * @note
 *    
 ******************************************************************************/
UINT32 GsnRpl_TblRttMarkParent( GSN_RPL_TABLE_T* pRplTable, UINT8 *pPEntry, 
    UINT8 isNb, GSN_RPL_RT_ENTRY_T *pCRtEntry, UINT8 parentIdx );
    

/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Gets the child information.
 *    This function gets the child information like its entry, its depth and 
 * the next hop to reach the child.
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pDstAddr - IN Pointer to the destination address of the child.
 * @param pDepth - OUT Pointer to the depth field. This API will fill the depth 
 * field to this pointer. 
 * @param pDEntry - OUT Pointer to the routing entry for this child.   
 * @retval Returns a valid pointer to an neighbor entry through which this 
 * child can be reached. If the pDEntry is NULL then the child entry is an 
 * immediate neighbor. If it returns NULL then it is not a child or grand child 
 * of the node.
 * @note 
 ******************************************************************************/
GSN_RPL_NB_ENTRY_T* 
GsnRpl_TblRttGetChildInfo( GSN_RPL_TABLE_T* pRplTable, UINT8 *pDstAddr, 
    UINT32* pDepth, GSN_RPL_RT_ENTRY_T** pDEntry );



/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Build hop information.
 *    This function builds the hop information which can be used to build source
 * route table. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pDstAddr - IN Pointer to the destination address for which the path 
 * has to be serached.
 * @param pLen - OUT Pointer to the length field. This API will fill the length 
 * required to write the Hop infromation. User should make sure that the 
 * buffer passed to build the Hop information has this much of available length. 
 * @param pDepth - OUT Pointer to the depth field. This API will fill the depth 
 * field to this pointer.  
 * @retval Returns a valid pointer to an routing entry for the destination. If 
 * return NULL then there is no route for the specified destination. the return 
 * address should be passed to build the Hop inforemation.
 * @note User has to call GsnRpl_RttHopInfoSize before calling this API. If the
 * return of GsnRpl_RttHopInfoSize is NULL, that means there is no path 
 * availabe for the destination device.
 ******************************************************************************/
GSN_RPL_NB_ENTRY_T*
GsnRpl_TblRttHopInfoSize( GSN_RPL_TABLE_T* pRplTable, UINT8 *pDstAddr, 
    UINT32* pLen, GSN_RPL_RT_ENTRY_T** pDepth );


/**
 *******************************************************************************
 * @ingroup GsnRPL
 * @brief Build hop information.
 *    This function builds the hop information which can be used to build source route table. 
 * @param pRplTable - IN Pointer to the RPL table.
 * @param pBuf - IN Pointer to the buffer to build the source route table.
 * @param pEntry - IN Pointer to destionation node entry. The pointer returned 
 * in the GsnRpl_RttHopInfoSize API call.
 * @retval
 * @note User has to call GsnRpl_RttHopInfoSize before calling this API. If the
 * return of GsnRpl_RttHopInfoSize is NULL, that means there is no path 
 * availabe for the destination device.
 ******************************************************************************/
GSN_STATUS GsnRpl_TblRttBuildHopInfo( GSN_RPL_TABLE_T* pRplTable, UINT8* pBuf,
    UINT32 *pBufSize, UINT8 *pEntry );

UINT8*
GsnRpl_TblEntryFind( const GSN_RPL_TABLE_INFO_T *pTblInfo, UINT8 *pAddr, 
    UINT8* pTbl, UINT32 elemUsed, GSN_STATUS *pStatus );
GSN_STATUS
GsnRpl_TblSpaceCreate( UINT8 *pLoc, const GSN_RPL_TABLE_INFO_T *pInfo, 
    UINT8 *pTbl, UINT32 elemUsed );
GSN_STATUS
GsnRpl_TblSpaceRemove( UINT8 *pLoc, const GSN_RPL_TABLE_INFO_T *pInfo, 
    UINT8 *pTbl, UINT32 elemUsed );

GSN_STATUS 
GsnRpl_TblBldIPAddr( GSN_RPL_TABLE_T* pRplTable, UINT8* pIp, 
    UINT8* pAddr );



#ifdef __cplusplus
}
#endif
#endif /* _GSN_RPL_TABLE_H_ */
