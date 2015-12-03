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
* $RCSfile: gsn_trickle_tmr.h,v $
*
* Description : This file contains function declaration for TRICKLE timer.
* This is as per the RFC 6206.
*****************************************************************************/
#ifndef _GSN_TRICKLE_TMR_H_
#define _GSN_TRICKLE_TMR_H_

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
* File inclusion
******************************************************************************/


/**
 *****************************************************************************
 * @file gsn_trickle_tmr.h
 * @brief GSN Trickle Timer public header.
 *    This file contains the public APIs and structures of Trickle Timer 
 * module. For details on the trickle timer refer to RFC 6206.
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
 * @ingroup GsnTrickleTmr
 * @brief  Callback funtion definition for trickle transmit timeout.
 *****************************************************************************/
typedef VOID (*GSN_TRICKLE_TMR_CB_T)( VOID *pCtx );

/**
 *****************************************************************************
 * @ingroup GsnTrickleTmr
 * @brief  Structure definition for the trickle timer configuration.
 *****************************************************************************/
typedef struct GSN_TRICKLE_TMR_CFG
{
    UINT32 Imin; /**< Minimum time in msec */
    UINT32 Imax; /**< Maximum time in msec */
    UINT8  k; /**< The redundancy constant */

    /**< Callback to handle trickle transmit. This callback is called only if 
    transmission is not received for k times. User indicate about the 
    transmission received by calling GSN_TRICKLE_TMR_TX_RECV */
    GSN_TRICKLE_TMR_CB_T cb; 
    
}GSN_TRICKLE_TMR_CFG_T;

/**
 *****************************************************************************
 * @ingroup GsnTrickleTmr
 * @brief  Structure definition for the trickle timer context.
 *****************************************************************************/
typedef struct GSN_TRICKLE_TMR_CTX
{
    const GSN_TRICKLE_TMR_CFG_T *pCfg; /**< configuration */

    VOID *pCtx; /**< User context. This is passed in the user callback */
    
    UINT16 I; /**< Stores the current I used */
    UINT8 counter; /**< Stores the current conter */
    UINT8 doublling;
    /**< Store the random time used to check for supressing the transmission */
    UINT32 t; 
    
    GSN_SOFT_TMR_T tmr; /**< Soft timer */
    GSN_RPL_EVENT_T Event;
    VOID *pEventCtx;
}GSN_TRICKLE_TMR_CTX_T;

/**
 *****************************************************************************
 * @ingroup GsnTrickleTmr
 * @brief Initialization for Trickle Timer module.
 *    This function performs initialization of Trickle timer module.
 * @param pTTCtx - IN Pointer to the trickle timer context.
 * @param pCfg - IN Pointer to thetrickle timer configuration.
 * @param pCtx - IN Pointer to user context. This is passed in the user 
 * callback
 * @param pEventCtx - IN Pointer to Event context. This parameter is passed to
 * the Delay event handler.
 *****************************************************************************/
VOID GsnTrickleTmr_Init( GSN_TRICKLE_TMR_CTX_T *pTTCtx, 
    const GSN_TRICKLE_TMR_CFG_T *pCfg, VOID *pCtx, VOID *pEventCtx );

/**
 *****************************************************************************
 * @ingroup GsnTrickleTmr
 * @brief Transmission receive indication.
 *    This MACRO indicates of receipt of transmission.
 * @param pTTCtx - IN Pointer to the trickle timer context.
 *****************************************************************************/
#define GSN_TRICKLE_TMR_TX_RECV( pTTCtx )   pTTCtx->counter++

/**
 *****************************************************************************
 * @ingroup GsnTrickleTmr
 * @brief Reset the trickle timer.
 *    This function resets the trickle timer and starts it from fresh. User 
 * calls ths API when it finds inconsistency in the network.
 * @param pTTCtx - IN Pointer to the trickle timer context.
 *****************************************************************************/
VOID GsnTrickleTmr_Reset( GSN_TRICKLE_TMR_CTX_T *pTTCtx );

/**
 *****************************************************************************
 * @ingroup GsnTrickleTmr
 * @brief Deinitialize the trickle timer.
 *    This MACRO deinitializes the trickle module.
 * @param pTTCtx - IN Pointer to the trickle timer context.
 *****************************************************************************/
#define GSN_TRICKLE_TMR_DEINIT( pTTCtx )    GsnSoftTmr_Stop( &(pTTCtx)->tmr )

VOID GsnTrickleTmr_GetRandTime( VOID* pCtx, GSN_TRICKLE_TMR_CB_T cb, VOID* pAppCtx,
    UINT16 min, UINT16 max );

VOID GsnTrickleTmr_Stop( GSN_TRICKLE_TMR_CTX_T *pTTCtx );

#ifdef __cplusplus
}
#endif
#endif /* _GSN_TRICKLE_TMR_H_ */
