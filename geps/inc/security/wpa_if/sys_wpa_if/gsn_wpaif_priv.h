/*******************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
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
* $RCSfile: gsn_wpaif_priv.h,v $
*
* Description : This file contains the private declaration used across the WPAIF
* modules.
*******************************************************************************/
#ifndef _GSN_WPAIF_PRIV_H_
#define _GSN_WPAIF_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "gsn_includes.h"
#include "supplicant/utils/includes.h"
#include "supplicant/utils/common.h"
#include "supplicant/utils/wpabuf.h"
#include "supplicant/common/defs.h"
#include "supplicant/rsn_supp/wpa.h"

#include "security/wpa_if/gsn_wpaif.h"
//#include "gsn_security.h"
#include "security/wpa_if/sys_wpa_if/inc/gsn_blobif.h"

/**
 *******************************************************************************
 * @file gsn_wpaif_i.h
 * @brief GSN WPAIF module.
 *      This file contains the WPAIF specific definitions.
 ******************************************************************************/

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF mode.
 *     This enum defines the WPAIF operation mode. This mode specifies the Wi-Fi
 * operating mode.
 *******************************************************************************/


#define GSN_WPAIF_WPS_STATE_NONE        0
#define GSN_WPAIF_WPS_STATE_SRCH_REG    1
#define GSN_WPAIF_WPS_STATE_REG_IN_PROG 2

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF Timer notification callback type.
 *
 *     This function type defination defines the WPAIF timer notification
 * callback type.
 ******************************************************************************/
//typedef VOID (*GSN_WPAIF_TMR_NITIF_CB_T)( VOID* pCtx);

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief Context for WPA timer declaration.
 *
 *     This structure defines the WPAIF timer context.
 ******************************************************************************/
struct eloop_timeout {
    struct eloop_timeout *next;
    UINT32 time;
    VOID (*handler)(VOID *eloop_ctx, VOID *timeout_ctx);
    VOID *eloop_data;
    VOID *user_data;
    GSN_SOFT_TMR_T sw_tmr;
};

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF context declaration.
 *
 *     This structure defines the WPAIF context. It stores all the information
 * needed to operate on an Wi-Fi interface.
 ******************************************************************************/
typedef struct GSN_WPAIF
{
    struct GSN_WPAIF *pNext;
    UINT8 own_mac[ETH_ALEN];
    UINT8 state;
    VOID *pWifiDrvCtx; /* WDD context */    
    VOID* (*init)( VOID* pCtx, GSN_WPAIF_MODE_T mode, VOID *pDrvIf, GSN_WPAIF_BASIC_CFG_T *pCfg,
        GSN_WPAIF_SPECFIC_CFG_T *pSpecCfg );
    GSN_STATUS ( *deinit )( void *pCtx );
    GSN_STATUS (*cb)( void *pCtx, UINT32 event, UINT8 *pData, UINT32 length );
    GSN_STATUS (*cfgGet)( void *pCtx, GSN_WPAIF_CFG_OPT_T cfgOpt, UINT8 *pData,
               UINT32* pLen );
    GSN_STATUS (*cfgSet)( void *pCtx, GSN_WPAIF_CFG_OPT_T cfgOpt, UINT8 *pData,
               UINT32 Len );
    VOID*( *optimumStateInit)( void *pCtx );
    //VOID( *getIe)( void *pCtx, UINT8* pIe, UINT32* pIeLen );
}GSN_WPAIF_T;


typedef struct GSN_WPAIF_ETH_HDR
{
    UINT8    dst[6];
    UINT8    src[6];
    UINT16  proto;
    UINT8    data[1500];
}GSN_WPAIF_ETH_HDR_T;

typedef struct GSN_WPAIF_BASE_STATE
{
    struct GSN_WPAIF *pNext;

    GSN_WPAIF_MODE_T mode;
    UINT8 state;
    UINT32 eapol_received;
    VOID *pWifiDrvCtx; /* WDD context */
    GSN_WLAN_MAC_ADDR_T  *pSsid;
    GSN_WPAIF_CFG_T cfg;
    UINT8 bssid[ETH_ALEN];

    UINT8 pmk[PMK_LEN];
    struct wpa_ptk ptk;
}GSN_WPAIF_BASE_STATE_T;



/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF Security context declaration.
 *
 *     This structure defines the security context.
 ******************************************************************************/
typedef struct GSN_WPA_CTX
{
    struct eloop_timeout     *pEloopActive;
    struct eloop_timeout     *pEloopExpired;
    GSN_WPAIF_TMR_NITIF_CB_T cb;
    VOID                     *pCtx;
    GSN_WPAIF_T              *pList;
    GSN_OSAL_SEM_T           tmrSem;
}GSN_WPA_CTX_T;

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief WPAIF Security object declaration.
 *
 *     This object is declare here to be accessed from other files.
 ******************************************************************************/
extern GSN_WPA_CTX_T wpaCtx;

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief Finds whether wpa interface is opend for the WDD driver.
 *
 *    This function returns the WPAIF interface object pointer used by WPAIF, for a particular
 *    WDD driver. It returns NULL if the interface is not opended.
 * @param pWdd - IN pointer to WDD driver object.
 * @return pointer to WPAIF instance.
 ******************************************************************************/
PUBLIC GSN_WPAIF_T *
GsnWpa_FindIf( VOID *pDrvIf );

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief Add the WPAIF instance to the security list.
 *
 *    This function adds the newly created WPAIF instance to the security object.
 * @param pWpaIf - IN pointer to WPAIF instance.
 * @return
 ******************************************************************************/
PUBLIC VOID
GsnWpa_AddIf( GSN_WPAIF_T *pWpaIf );

/**
 *******************************************************************************
 * @ingroup GsnWpaIf
 * @brief Removes the WPAIF instance from the security list.
 *
 *    This function removes the WPAIF instance to the security object.
 * @param pWpaIf - IN pointer to WPAIF instance.
 * @return
 ******************************************************************************/
PUBLIC VOID
GsnWpa_RemoveIf( GSN_WPAIF_T *pWpaIf );



#ifdef __cplusplus
}
#endif
#endif /*  _GSN_WPAIF_PRIV_H_ */
