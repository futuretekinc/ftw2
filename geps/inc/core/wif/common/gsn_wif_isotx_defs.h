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
* $RCSfile: gsn_wif_isotx_defs.h,v $
*
* Description : This file contains common public definitions for ISO Tx.
******************************************************************************/
#ifndef _GSN_WIF_ISOTX_DEFS_H_
#define _GSN_WIF_ISOTX_DEFS_H_
#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
* File Inclusion
*****************************************************************************/
//#include "gsn_wlan_defs.h"
/**
 *****************************************************************************
 * @ingroup coresvcdoc
 * @{
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup GsnWif GSN WLAN Firmware Interface (WIF) module
 * @brief This group provides the interface with WLAN Firmware running on WLAN CPU. 
 *	  
 *		Whole GsnWif module is grouped in two parts, APIs and the Msg_Sys. The APIs provide the handling 
 * of various requests and indications.
 *		Msg_Sys provides the buffer managemnet and shared memeory management infrastructure to
 * trnasfer messages (control/data) between WLAn and APP firmware.
 ******************************************************************************/
 
/**
 *****************************************************************************
 * @}	END of coresvcdoc.
 *****************************************************************************/

  
  
/**
 *****************************************************************************
 * @file gsn_wif_isotx_defs.h
 * @brief GSN WIF ISOTX interface public header.
 * 
 *    This file contains the public APIs and structures of ISOTX control
 *    interface.
 *****************************************************************************/
#define GSN_WIF_WLAN_ISOTX_SUBBLINKS_MAX 8
/**
 *****************************************************************************
 * @ingroup GsnWifIsotxDefs
 * @brief Blink Config.
 * 
 *    This structure defines the Blink Configuration type.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_ISOTX_BLINK_S
{
    UINT32  frequency;      /* synthesizer frequency - use default if value is Null */
    UINT16  subBlinkInt[GSN_WIF_WLAN_ISOTX_SUBBLINKS_MAX]; /* time in ms between sub-blinks */
    UINT8   blinkType;      /* 0=DSSS, 1=OOK/FSK */
    UINT8   bandwidth;      /* 0=normal, 1=Japan */
    UINT8   testMode;       /* 0=normal, 1=continuous mode   */
    UINT8   subBlinkCnt;    /* number of sub-blinks , range 1 - 8 */
    UINT8   gain;           /* Sets the gain of the transmitter in dB */
    UINT8   unused;
} GSN_WIF_WLAN_ISOTX_BLINK_T;

/**
 *****************************************************************************
 * @ingroup GsnWifIsotxDefs
 * @brief Blink Config.
 * 
 *    This structure defines the data returned by the WLAN CPU after each ISO blink.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_ISOTX_RESP_S
{
    INT32   status;  /* status of transmission as number of sub-blinks transmitted */
    UINT16  txVolt; /* battery voltage measured after final sub-blink */
    UINT16  txDet[GSN_WIF_WLAN_ISOTX_SUBBLINKS_MAX];  /* peak power detector value measured during transmission */
} GSN_WIF_WLAN_ISOTX_RESP_T;

typedef struct GSN_WIF_REG_ADDR_VAL_S
{
    UINT16 addr;
    UINT32 val;
}GSN_WIF_REG_ADDR_VAL_T;

typedef struct GSN_WIF_WLAN_REG_WRITE_S
{
    UINT32 numRegVals;
    GSN_WIF_REG_ADDR_VAL_T regAddrVals[0];
}GSN_WIF_WLAN_REG_WRITE_T;



#ifdef __cplusplus
}
#endif
#endif /* _GSN_WIF_ISOTX_DEFS_H_ */






