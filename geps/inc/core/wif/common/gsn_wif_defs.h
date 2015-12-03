/******************************************************************************
*
*               COPYRIGHT (c) 20012-2014 GainSpan Corporation
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
* $RCSfile: gsn_wif_defs.h,v $
*
* Description : This file contains WIF definitions.
******************************************************************************/
#ifndef _GSN_WIF_DEFS_H_
#define _GSN_WIF_DEFS_H_
#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
* File Inclusion
*****************************************************************************/

/**
 *****************************************************************************
 * @file gsn_wif_defs.h
 * @brief GSN WIF definitions public header.
 * 
 *    This file contains the public definitions of WIF.
 *****************************************************************************/



/**
 *****************************************************************************
 * @ingroup GsnWif
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnWifDefs GSN WIF Definitions
 *    This group contains WIF definitions.
*****************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/	


#define GSN_WIF_MAX_IF_NUM  3

/**
 *****************************************************************************
 * @ingroup GsnWifDefs
 * @brief GSN WIF Queue descriptor structure.
 * 
 *    Structure defining the queue descriptor used at WIF.
 *****************************************************************************/
typedef GSN_RING_BUF_T GSN_WIF_Q_DESC_T;
typedef GSN_RING_BUF_HNDL_T GSN_WIF_Q_DESC_HNDL_T;


/**
 *****************************************************************************
 * @ingroup GsnWifDefs
 * @brief GSN WIF Hi header
 * 
 *    Structure defining the control interface Hi header
 *****************************************************************************/
typedef struct GSN_WIF_HIF_HDR_S
{
    UINT8              class;      /* HI frame class                                       */
    UINT8              devIndex;   /*  For concurrent mode */
    UINT16             addInfo;    /* HI frame additional info                             */
    UINT16             len;        /* HI frame len lenth of pBuf --> strlen(pBuf)          */
} GSN_WIF_HIF_HDR_T;

/**
 *****************************************************************************
 * @ingroup GsnWifDefs
 * @brief GSN WIF control transfer descriptor.
 * 
 *    Structure defining the control interface transfer descriptor.
 *****************************************************************************/
typedef struct GSN_WIF_CTL_TD_S
{
    GSN_WIF_HIF_HDR_T hiHdr;
    UINT16 msgId;       /**< Message identifier - API */
    
    UINT32 unused;      /**< Not used - for future use if any */
    
    VOID *pBuf;         /**< pointer to buffer containing CMD */
} GSN_WIF_CTL_TD_T;



/**
 *****************************************************************************
 * @ingroup GsnWifDefs
 * @brief GSN WIF data transfer descriptor.
 * 
 *    Structure defining the data interface transfer descriptor.
 *****************************************************************************/
typedef struct GSN_WIF_DATA_TD_S
{
    GSN_WIF_HIF_HDR_T hiHdr; /**< HI header */
    UINT16 status;       /**< status */
    
    UINT32 msgId;       /* MessageId*/ 
    
    VOID *pBuf;         /**< pointer to buffer containing data */
} GSN_WIF_DATA_TD_T;


#define GSN_WIF_CTL_TD_SIZE     sizeof(GSN_WIF_CTL_TD_T)
#define GSN_WIF_DATA_TD_SIZE    sizeof(GSN_WIF_DATA_TD_T)


typedef enum GSN_WIF_QS
{
    GSN_WIF_D_TXRDY_QDESC_INDEX = 0,
    GSN_WIF_D_TXDONE_QDESC_INDEX,
    GSN_WIF_D_RXRDY_SBUF_QDESC_INDEX,
    GSN_WIF_D_RXRDY_LBUF_QDESC_INDEX,
    GSN_WIF_D_RXDONE_QDESC_INDEX,
    GSN_WIF_C_TXRDY_QDESC_INDEX,
    GSN_WIF_C_TXDONE_QDESC_INDEX,
    GSN_WIF_C_RXRDY_SBUF_QDESC_INDEX,
    GSN_WIF_C_RXRDY_LBUF_QDESC_INDEX,
    GSN_WIF_C_RXDONE_QDESC_INDEX,

    GSN_WIF_MAX_QS
} GSN_WIF_QS_T;


typedef enum GSN_WIF_Q_TYPES
{
    GSN_WIF_Q_TYPE_CTL = 1,
    GSN_WIF_Q_TYPE_DATA
} GSN_WIF_Q_TYPES_T;




#ifdef __cplusplus
}
#endif
#endif /* _GSN_WIF_DEFS_H_ */






