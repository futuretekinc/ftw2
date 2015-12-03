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
* $RCSfile: gsn_wif_cal_defs.h,v $
*
* Description : This file contains common public definitions for calibration.
******************************************************************************/
#ifndef _GSN_WIF_CAL_DEFS_H_
#define _GSN_WIF_CAL_DEFS_H_
#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
* File Inclusion
*****************************************************************************/
//#include "gsn_wlan_defs.h"
  
  
/**
 *****************************************************************************
 * @file gsn_wif_cal_defs.h
 * @brief GSN WIF CAL interface public header.
 * 
 *    This file contains the public APIs and structures of CAL control
 *    interface.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnWifCalDefs
 * @brief WIF CAL API.
 * 
 *    This enum defines the calibration types.
*****************************************************************************/
typedef enum GSN_WIF_CAL_TYPE_E
{
    GSN_WIF_CAL_TYPE_AX_CTUNE = 0,
    GSN_WIF_CAL_TYPE_AX_QTUNE = 1,
    GSN_WIF_CAL_TYPE_AX_REFTRIM = 2,
    GSN_WIF_CAL_TYPE_AX_RES = 3,
    GSN_WIF_CAL_TYPE_AX_BG = 4,

    GSN_WIF_CAL_TYPE_LX_SWCVCO = 5,

    GSN_WIF_CAL_TYPE_RX_DCO = 6,
    GSN_WIF_CAL_TYPE_RX_IQ_PHASE_MISMATCH = 7,
    GSN_WIF_CAL_TYPE_RX_IQ_GAIN_MISMATCH = 8,

    GSN_WIF_CAL_TYPE_TX_MIX_DCO = 9,
    GSN_WIF_CAL_TYPE_TX_IQ_PHASE_MISMATCH = 10,
    GSN_WIF_CAL_TYPE_TX_IQ_GAIN_MISMATCH = 11,
    GSN_WIF_CAL_TYPE_MODULE                 = 0xFE,
    GSN_WIF_CAL_TYPE_ALL                    = 0xff
} GSN_WIF_CAL_TYPE_T;

/**
 *****************************************************************************
 * @ingroup GsnWifCalDefs
 * @brief WIF CAL API.
 *
 *    This enum defines the calibration subtypes.
*****************************************************************************/
typedef enum GSN_WIF_CAL_SUBTYPE_E
{
    GSN_WIF_CAL_SUBTYPE_80211B = 0,
    GSN_WIF_CAL_SUBTYPE_80211N = 1,
    GSN_WIF_CAL_SUBTYPE_80211N40 = 2,
    GSN_WIF_CAL_SUBTYPE_802154 = 3,

} GSN_WIF_CAL_SUBTYPE_T;


/**
 *****************************************************************************
 * @ingroup GsnWifCalDefs
 * @brief WIF CAL API.
 *
 *    This structure defines the calibration run request.
*****************************************************************************/
typedef struct GSN_WIF_CAL_RUN_REQ_S
{
    UINT16 calType;
    UINT16 calSubtype;
    UINT32 channel;
    UINT8  modType;
    UINT8  unused[2];
} GSN_WIF_CAL_RUN_REQ_T;

typedef enum GSN_WIF_CAL_STATUS_E
{
    GSN_WIF_CAL_SUCCESS = 0,
    GSN_WIF_CAL_FAILED = 1,
} GSN_WIF_CAL_STATUS_T;

/**
 *****************************************************************************
 * @ingroup GsnWifCalDefs
 * @brief WIF CAL OTP VERSION.
 *
 *    This enum defines the CAL OTP VERSION.
*****************************************************************************/
typedef enum GSN_WIF_RF_CAL_OTP_VER_E
{
	GSN_WIF_RF_CAL_OTP_VER_0    = 0,
    GSN_WIF_RF_CAL_OTP_VER_1    = 1,
    GSN_WIF_RF_CAL_OTP_VER_2    = 2
}GSN_WIF_RF_CAL_OTP_VER_T;



/**
 *****************************************************************************
 * @ingroup GsnWifCalDefs
 * @brief WIF CAL API response.
 * 
 *    This structure defines the calibration run response.
*****************************************************************************/
typedef struct GSN_WIF_CAL_RUN_RSP_S
{
    UINT8 status;  /**< 0 - success, 1 - failed */
    UINT16 len;     /* len of valid data */
    UINT8 data[1024]; /**< data type is dependent on cal Id,
                         but max size is 1024 as of now */

} GSN_WIF_CAL_RUN_RSP_T;



#ifdef __cplusplus
}
#endif
#endif /* _GSN_WIF_CAL_DEFS_H_ */






