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
* $RCSfile: gsn_mle.h,v $
*
* Description : This file contains function defination for the Mesh Link 
* Establishment module in ZigBee-IP.
*****************************************************************************/

/******************************************************************************
* File inclusion
******************************************************************************/
#ifndef _GSN_MLE_H_
#define _GSN_MLE_H_

#ifdef __cplusplus
extern "C" {
#endif
  
#define GSN_MLE_UDP_PORT 19788
  
#define GSN_MLE_ADV_INTERVAL

#define GSN_MLE_CMD_TYPE_LINK_REQ           0
#define GSN_MLE_CMD_TYPE_LINK_ACCEPT        1
#define GSN_MLE_CMD_TYPE_LINK_ACCEPT_N_REQ  2
#define GSN_MLE_CMD_TYPE_LINK_REJECT        3
#define GSN_MLE_CMD_TYPE_LINK_ADVERTISEMENT 4
#define GSN_MLE_CMD_TYPE_LINK_UPDATE        5
#define GSN_MLE_CMD_TYPE_LINK_UPDATE_REQ    6

#define GSN_MLE_TLV_TYPE_SRC_ADDR       0
#define GSN_MLE_TLV_TYPE_MODE           1
#define GSN_MLE_TLV_TYPE_TIMEOUT        2
#define GSN_MLE_TLV_TYPE_CHALLENGE      3
#define GSN_MLE_TLV_TYPE_RESPONSE       4
#define GSN_MLE_TLV_TYPE_REPLY_COUNTER  5
#define GSN_MLE_TLV_TYPE_LQI            6
#define GSN_MLE_TLV_TYPE_NW_PARAM       7
#define GSN_MLE_TLV_TYPE_MLE_FRM_CNT    8

#define GSN_MLW_NW_PARAM_ID_CHANNEL     0
#define GSN_MLW_NW_PARAM_ID_PAN_ID      1
#define GSN_MLW_NW_PARAM_ID_P_JOIN      2
#define GSN_MLW_NW_PARAM_ID_BCN_PLD     3
    


#define GSN_MLE_WRITE_TLV_SRC_ADDR( pBuf, shortAddr, macAddr )\
    *pBuf++ = GSN_MLE_TLV_TYPE_SRC_ADDR; *pBuf++ = 10;        \
    WRITE_16( pBuf, shortAddr );                              \
    memcpy( pBuf, macAddr, 8 ); pBuf += 8;

#define GSN_MLE_WRITE_TLV_MODE( pBuf, cfg )                   \
    *pBuf++ = GSN_MLE_TLV_TYPE_MODE; *pBuf++ = 1;             \
    *pBuf++ = (( cfg.isFFD << 1 )|( cfg.isRxOnWhenIdle << 3 ));

#define GSN_MLE_WRITE_TLV_TIMEOUT( pBuf, timeOut )            \
    *pBuf++ = GSN_MLE_TLV_TYPE_TIMEOUT; *pBuf++ = 4;          \
    WRITE_32( pBuf, timeOut );

#define GSN_MLE_WRITE_TLV_CHALLENGE( pBuf, challenge )        \
    *pBuf++ = GSN_MLE_TLV_TYPE_CHALLENGE; *pBuf++ = 8;        \
    memcpy( pBuf, challenge, 8 ); pBuf += 8;

#define GSN_MLE_WRITE_TLV_RESPONSE( pBuf, response )          \
    *pBuf++ = GSN_MLE_TLV_TYPE_RESPONSE; *pBuf++ = 8;         \
    memcpy( pBuf, response, 8 ); pBuf += 8;

#define GSN_MLE_WRITE_TLV_COUNTER( pBuf, counter )            \
    *pBuf++ = GSN_MLE_TLV_TYPE_REPLY_COUNTER; *pBuf++ = 4;    \
    WRITE_32( pBuf, counter );


#define GSN_MLE_TLV_SIZE_MODE       3
#define GSN_MLE_TLV_SIZE_SRC_ADDR   12
#define GSN_MLE_TLV_SIZE_TIMEOUT    6
#define GSN_MLE_TLV_SIZE_CHALLENGE  10
#define GSN_MLE_TLV_SIZE_RESPONSE   10
#define GSN_MLE_TLV_SIZE_COUNTER    6

#define GSN_MLE_EVENT_LINK_REQ           0
#define GSN_MLE_EVENT_LINK_ACCEPT        1
#define GSN_MLE_EVENT_LINK_ACCEPT_N_REQ  2
#define GSN_MLE_EVENT_LINK_REJECT        3
#define GSN_MLE_EVENT_LINK_ADVERTISEMENT 4
#define GSN_MLE_EVENT_LINK_UPDATE        5
#define GSN_MLE_EVENT_LINK_UPDATE_REQ    6    
    
    
typedef struct GSN_MLE_CFG
{
    UINT8 isFFD;
    UINT8 isRxOnWhenIdle;
    UINT16 shortAddr;
    UINT8  macAddr[ 8 ];
}GSN_MLE_CFG_T;

typedef struct GSN_MLE_SEC_MAT
{
    UINT8 key[ 16 ];
    UINT8 keyId;
    UINT32 cnt;
}GSN_MLE_SEC_MAT_T;

typedef struct GSN_MLE_LINK_REQ_DATA
{
    GSN_MLE_CFG_T cfg;
}GSN_MLE_LINK_REQ_DATA_T;

typedef VOID ( *GSN_MLE_CB_T )( VOID* pCtx, UINT8 event, UINT8* pEData, 
    UINT8* pSrc, UINT32 srcAddrLen );

typedef struct GSN_MLE_CTX
{
    GSN_MLE_CB_T cb;
    VOID *pCbCtx;
    int socket;
    GSN_MLE_CFG_T cfg;
    UINT32 myCounter;
    UINT32 PCounter;
    UINT8  challenge[ 8 ];
    GSN_MLE_SEC_MAT_T keyInfo;
}GSN_MLE_CTX_T;



GSN_STATUS GsnMle_Init( GSN_MLE_CTX_T *pMle, GSN_MLE_CFG_T *pCfg, 
  GSN_MLE_CB_T cb, VOID *pCbCtx );

GSN_STATUS GsnMle_LinkReqSend( GSN_MLE_CTX_T *pMle, UINT8* pDst );
GSN_STATUS GsnMle_LinkAcceptSend( GSN_MLE_CTX_T *pMle, UINT8* pDst );
GSN_STATUS GsnMle_LinkAcceptNReqSend( GSN_MLE_CTX_T *pMle, UINT8 *pRsp, UINT8* pDst );
GSN_STATUS GsnMle_LinkRejectSend( GSN_MLE_CTX_T *pMle, UINT8* pDst );

GSN_STATUS GsnMle_AdvertisementSend( GSN_MLE_CTX_T *pMle, UINT8* pDst );
GSN_STATUS GsnMle_AdvertisementProc( GSN_MLE_CTX_T *pMle, UINT8* pDst );

GSN_STATUS GsnMle_UpdateSend( GSN_MLE_CTX_T *pMle, UINT8* pDst );
GSN_STATUS GsnMle_UpdateProc( GSN_MLE_CTX_T *pMle, UINT8* pDst );
GSN_STATUS GsnMle_DeInit( GSN_MLE_CTX_T *pMle );

#ifdef __cplusplus
}
#endif
#endif /* _GSN_MLE_H_ */