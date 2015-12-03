/******************************************************************************
*
*               COPYRIGHT (c) 2008-2010 GainSpan Corporation
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
* $RCSfile: gsn_ring_buf.h,v $
*
* Description : Public header for Ring buffer API.
*****************************************************************************/
#ifndef _GSN_RING_BUF_H_
#define _GSN_RING_BUF_H_

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_defines.h"
#include "gsn_types.h"
#include "gsn_error.h"


/**
 *****************************************************************************
 * @file gsn_ring_buf.h
 * @brief GSN Ring buffer implementation.
 *    This file contains the ring buffer functionality.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup coresvcdoc
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnRingBuf GSN Ring Buffer Utilities
 *    This group contains ring buffer implementation.
 *****************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/


/****************************************************************************
  *  Type definitions
  ****************************************************************************/
  
/**
 *****************************************************************************
 * @ingroup GsnRingBuf 
 *    
 *****************************************************************************/  
  
typedef struct GSN_RING_BUF
{
    UINT8 head;
    UINT8 tail;
    UINT8 entrySize;
    UINT8 ringSize;

    VOID *pBuf;
} GSN_RING_BUF_T;


typedef GSN_RING_BUF_T * GSN_RING_BUF_HNDL_T;




/*****************************************************************************
  * Macro Definitions
  ****************************************************************************/


/**
 *****************************************************************************
 * @ingroup GsnRingBuf 
 * @brief Initialize ring buffer.
 *    
 *****************************************************************************/ 



PUBLIC GSN_RING_BUF_HNDL_T
GsnRingBuf_Init(GSN_RING_BUF_T *ringBuf, 
  UINT8 entrySize, UINT8 ringSize, VOID *buf);



/**
 *****************************************************************************
 * @ingroup GsnRingBuf 
 * @brief Put data in the buffer.
 *    
 *****************************************************************************/ 
 
PUBLIC GSN_STATUS_T
GsnRingBuf_Put(GSN_RING_BUF_HNDL_T ringBuf, VOID *pData);


/**
 *****************************************************************************
 * @ingroup GsnRingBuf 
 * @brief Get data from the buffer.
 *    
 *****************************************************************************/ 

PUBLIC GSN_STATUS
GsnRingBuf_Get(GSN_RING_BUF_HNDL_T ringBuf, VOID *pData);



/**
 *****************************************************************************
 * @ingroup GsnRingBuf 
 * @brief Check message queue.
 *    
 *****************************************************************************/ 
 
PUBLIC BOOL
GsnRingBuf_IsMsgQueued(GSN_RING_BUF_HNDL_T ringBuf, VOID *pData);



/**
 *****************************************************************************
 * @ingroup GsnRingBuf 
 * @brief Reset ring buffer.
 *    
 *****************************************************************************/ 
 
PUBLIC INLINE VOID
GsnRingBuf_Reset(GSN_RING_BUF_HNDL_T ringBuf)
{
    ringBuf->head = ringBuf->tail = 0;
}


/**
 *****************************************************************************
 * @ingroup GsnRingBuf 
 * @brief Get message count.
 *    
 *****************************************************************************/ 

PUBLIC INLINE UINT8
GsnRingBuf_MsgCount( GSN_RING_BUF_HNDL_T ringBuf )
{
    UINT8 msgCount;
    if( ringBuf->head < ringBuf->tail )
       msgCount = ringBuf->ringSize - ringBuf->tail + ringBuf->head;
    else
        msgCount = ringBuf->head - ringBuf->tail;

    return msgCount;
}
#endif /* _GSN_RING_BUF_H_ */

/*****************************************************************************/




