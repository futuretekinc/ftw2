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
* $RCSfile: gsn_6lowpan_driver.h,v $
*
* Description : This file contains function and structure declaration for 
* 6LOWPAN Driver.
*****************************************************************************/

#ifndef _GSN_6LOWPAN_DRIVER_H_
#define _GSN_6LOWPAN_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* File inclusion
******************************************************************************/

/**
 *****************************************************************************
 * @file gsn_wlrpan_driver.h
 * @brief GSN WLARPN Driver public header.
 *    This file contains the public APIs and structures of WLARPAN Driver.
 *
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnWlrPAN
 * @brief 
 *
 *    
******************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/
/**
 *****************************************************************************
 * @ingroup Gsn6LoWPAN
 * @brief Definition for 6LoWPAN data request structure. 
 *****************************************************************************/
typedef struct GSN_6LOWPAN_DATA_REQ_HDR
{
    UINT16            frmLen;
    GSN_WLRPAN_ADDR_T dstAddr; 
}GSN_6LOWPAN_DATA_REQ_HDR_T;

/**
 *****************************************************************************
 * @ingroup Gsn6LoWPAN
 * @brief Definition for 6LoWPAN data indication structure. 
 *****************************************************************************/
typedef struct GSN_6LOWPAN_DATA_IND
{
    GSN_WLRPAN_ADDR_T dstAddr; 
    UINT32  timeStamp;    
    UINT8   lqi;
    UINT16  frmLen;
    UINT8   Frm[1];
}GSN_6LOWPAN_DATA_IND_T;


typedef struct GSN_6LOWPAN_CTX
{
    GSN_L2_DEV_T l2Dev;	 /**< Mandatory subclass for every L2 device */	
    VOID*        l3Hndl; /**< L3 handle. This is passed in call backs like receive */
    GSN_DOT154IF_CTX_T *pDot154ifCtx;
}GSN_6LOWPAN_CTX_T;


GSN_STATUS Gsn6LoWPAN_Init( GSN_6LOWPAN_CTX_T *pCtx, 
    GSN_DOT154IF_CTX_T *pDot154ifCtx );

 

#ifdef __cplusplus
}
#endif
#endif /* _GSN_6LOWPAN_DRIVER_H_ */
