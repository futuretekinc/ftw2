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
* $RCSfile: s2w_l2_dev.h,v $
*
* Description : This file contains general NW definitions.
*******************************************************************************/
#ifndef _S2W_L2_NW_DEFINES_H_
#define _S2W_L2_DEFINES_H_

/*******************************************************************************
  * File Inclusions
  ******************************************************************************/

#include "gsn_types.h"
#include "gsn_defines.h"


#define S2W_NUM_RAW_BUFS 3



/**
 *******************************************************************************
 * @file s2w_l2_dev.h
 * @brief S2W L2 Network definitions.
 *    This file contains general networking definitions.
 *******************************************************************************/

/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/

/**
 *******************************************************************************
 * @defgroup GsnNwDefines GSN Network Definitions
 *    This group contains general networking definitions.
 ******************************************************************************/


/*******************************************************************************
 *  Type Definitions
 ******************************************************************************/
typedef struct S2W_L2_DEV
{
    GSN_L2_DEV_T s2wL2Dev;
    GSN_L2_DEV_T *pL2Dev;
    VOID *l3Hndl;
    GSN_RING_BUF_T  s2wRawBufQ;
    UINT32 s2wRawBufQBuf[S2W_NUM_RAW_BUFS+1];
} S2W_L2_DEV_T;


PUBLIC GSN_STATUS
s2wL2Dev_Send(struct GSN_L2_DEV * pL2Dev, GSN_ETHERNET_FRAME_T *pFrame,
                        UINT32 frameLen);

/******************************************************************************
  *  Public Functions
  *****************************************************************************/
PUBLIC GSN_STATUS
s2wL2Dev_Open(struct GSN_L2_DEV *pL2Dev,
                        VOID *l3Hndl,
                        GSN_L2_DEV_RX_CB_T rxCb,
                        GSN_L2_DEV_TX_DONE_CB_T txDoneCb,GSN_L2_DEV_SEND_PKT_COPY_CB sendPktCopyCb);
PUBLIC GSN_STATUS
s2wL2Dev_Init(S2W_L2_DEV_T *ps2wL2Dev,
                 char *nwIfName,
                 GSN_L2_DEV_T *pwdd);

#endif /* _GSN_NW_DEFINES_H_ */





/**
 *****************************************************************************
 *
 * @}     END of System Services group include
 *****************************************************************************/
