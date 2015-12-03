/******************************************************************************
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
* $RCSfile: gsn_i2c_fpt.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/
#ifndef _GSN_I2C_FPT_H_
#define _GSN_I2C_FPT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/
#include "gsn_includes.h"

/**
 *****************************************************************************
 * @file gsn_defines.h
 * @brief GSN General Definitions.
 *    This file contains general definitions.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GEPSSupport
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnDefines GSN Definitions
 * @brief This module Contains General Definitions.
 *
 * \verbatim
 * PUBLIC is actually defined as blank.
 * PRIVATE is replaced with the "static" descriptor.
 * TRUE is replaced with 1, FALSE with 0
 * Compile-dependent definitions are provided for INLINE
 * BIT(n) provides n-bit offsets
 * A UINT32 with all bits = 1 is defined.
 *
 *\endverbatim
 *****************************************************************************/

/**
 *****************************************************************************
 *
 * @}
 *****************************************************************************/

/*****************************************************************************
  *  Definitions
  ****************************************************************************/

typedef PUBLIC GSN_STATUS
(* GsnI2c_Open_FP_T)(GSN_I2C_HANDLE_T* i2cHandle,
                      GSN_I2C_CONFIG_T* i2cConfig,
                      GSN_I2C_ASYNEVENT_CALLBACK_FP asynEventCallBack );
extern _RPST_ GsnI2c_Open_FP_T GsnI2c_Open_FP;


typedef UINT32
(* GsnI2c_Read_FP_T)( GSN_I2C_HANDLE_T* i2cHandle,
                        UINT8 *userBuffer,
                        UINT8 noOfBytesToRead,
                        BOOL blockMode,
                        GSN_I2C_CALLBACK_FP rdCallBackFunc,
                        VOID* ctext);
extern _RPST_ GsnI2c_Read_FP_T GsnI2c_Read_FP;


typedef UINT32
(* GsnI2c_Write_FP_T)( GSN_I2C_HANDLE_T* i2cHandle,
                        UINT8* userBuffer,
                        UINT8 noOfBytesToWrite,
                        GSN_I2C_CALLBACK_FP writeCallBackFunc,
                        VOID* ctext);
extern _RPST_ GsnI2c_Write_FP_T GsnI2c_Write_FP;


typedef PUBLIC GSN_STATUS
(* GsnI2c_Close_FP_T)(GSN_I2C_HANDLE_T* i2cHandle);

extern _RPST_ GsnI2c_Close_FP_T GsnI2c_Close_FP;


typedef PUBLIC GSN_STATUS
(* GsnI2c_addModeSet_FP_T)(GSN_I2C_HANDLE_T* gsnI2chandle,
                            GSN_I2C_ADMOD_T addrMode);

extern _RPST_ GsnI2c_addModeSet_FP_T GsnI2c_addModeSet_FP;


typedef PUBLIC GSN_STATUS
(* GsnI2c_MSModeSet_FP_T)(GSN_I2C_HANDLE_T* gsnI2chandle,
                            GSN_I2C_MS_MODE_T gsnI2cMSMode);

extern _RPST_ GsnI2c_MSModeSet_FP_T GsnI2c_MSModeSet_FP;


typedef PUBLIC GSN_STATUS
(* GsnI2c_MemAddSet_FP_T)(GSN_I2C_HANDLE_T* gsnI2chandle,
                            GSN_I2C_MEMADD_SEL_T gsnI2cMemAddSel);

extern _RPST_ GsnI2c_MemAddSet_FP_T GsnI2c_MemAddSet_FP;


typedef PUBLIC GSN_STATUS
(* GsnI2c_ByteOverride_FP_T)(GSN_I2C_HANDLE_T* gsnI2chandle,
                              GSN_I2C_BYTECNTORIDE_T gsnI2cBytecntOride);

extern _RPST_  GsnI2c_ByteOverride_FP_T GsnI2c_ByteOverride_FP;


typedef PUBLIC GSN_STATUS
(* GsnI2c_DestSlaveAddSet_FP_T)(GSN_I2C_HANDLE_T* gsnI2chandle,
                                  UINT32 gsnI2cSlaveAddr);

extern _RPST_ GsnI2c_DestSlaveAddSet_FP_T GsnI2c_DestSlaveAddSet_FP;


typedef PUBLIC GSN_STATUS
(* GsnI2c_SlaveLocAddrSet_FP_T)(GSN_I2C_HANDLE_T* gsnI2chandle,
                                  UINT16 gsnI2cSlavelocAddr);

extern _RPST_ GsnI2c_SlaveLocAddrSet_FP_T GsnI2c_SlaveLocAddrSet_FP;


typedef PUBLIC GSN_STATUS
(* GsnI2c_AddrInSlave_FP_T)( GSN_I2C_HANDLE_T* gsnI2chandle,
                              UINT16 gsnI2cAddrLocInSlave );

extern _RPST_ GsnI2c_AddrInSlave_FP_T GsnI2c_AddrInSlave_FP ;


typedef PUBLIC GSN_STATUS
(* GsnI2c_HighSpeedEnable_FP_T)(GSN_I2C_HANDLE_T* gsnI2chandle,
                                  GSN_I2C_HIGH_SPEED_ENABLE_T HighSpeedEnable);

extern _RPST_ GsnI2c_HighSpeedEnable_FP_T GsnI2c_HighSpeedEnable_FP;


typedef PUBLIC GSN_STATUS
(* GsnI2c_RandomCurrentAddrSet_FP_T)(GSN_I2C_HANDLE_T* gsnI2chandle,
                                      GSN_I2C_RCAS_T gsnI2cRandomCurrentAddr );

extern _RPST_ GsnI2c_RandomCurrentAddrSet_FP_T GsnI2c_RandomCurrentAddrSet_FP;


typedef PUBLIC GSN_STATUS
(* GsnI2c_RateSet_FP_T)(GSN_I2C_HANDLE_T* gsnI2chandle,
                          UINT32 gsnI2cRate, GSN_I2C_CLK_SEL_T clockSelect);

extern _RPST_ GsnI2c_RateSet_FP_T GsnI2c_RateSet_FP;


typedef GSN_I2C_MEMADD_SEL_T
(* gsnI2c_MemAdd_selGet_FP_T)(GSN_I2C_HANDLE_T* gsnI2chandle);

extern _RPST_ gsnI2c_MemAdd_selGet_FP_T gsnI2c_MemAdd_selGet_FP;


typedef GSN_I2C_BYTECNTORIDE_T
(* gsnI2c_BytecntOrideGet_FP_T)(GSN_I2C_HANDLE_T* gsnI2chandle);

extern _RPST_ gsnI2c_BytecntOrideGet_FP_T gsnI2c_BytecntOrideGet_FP;


typedef GSN_I2C_ABORTCUROP_T
(* gsnI2c_AbortCurOpGet_FP_T)(GSN_I2C_HANDLE_T* gsnI2chandle );

extern _RPST_ gsnI2c_AbortCurOpGet_FP_T gsnI2c_AbortCurOpGet_FP;


typedef GSN_I2C_RCAS_T
(* gsnI2c_RCASGet_FP_T)(GSN_I2C_HANDLE_T* gsnI2chandle);

extern _RPST_ gsnI2c_RCASGet_FP_T gsnI2c_RCASGet_FP;


typedef UINT8
(* gsnI2c_OwnSlaveAdd_MSBGet_FP_T)(GSN_I2C_HANDLE_T* gsnI2chandle);

extern _RPST_ gsnI2c_OwnSlaveAdd_MSBGet_FP_T gsnI2c_OwnSlaveAdd_MSBGet_FP;


typedef UINT8
(* gsnI2c_OwnSlaveAdd_LSBGet_FP_T)(GSN_I2C_HANDLE_T* gsnI2chandle);

extern _RPST_ gsnI2c_OwnSlaveAdd_LSBGet_FP_T gsnI2c_OwnSlaveAdd_LSBGet_FP;


typedef GSN_I2C_MS_MODE_T
(* gsnI2c_MSModeGet_FP_T)(GSN_I2C_HANDLE_T* gsnI2chandle);

extern _RPST_ gsnI2c_MSModeGet_FP_T gsnI2c_MSModeGet_FP;


typedef GSN_I2C_ADMOD_T
(* gsnI2c_addModeGet_FP_T)(GSN_I2C_HANDLE_T* gsnI2chandle);

extern _RPST_ gsnI2c_addModeGet_FP_T gsnI2c_addModeGet_FP;


typedef PUBLIC VOID
(* __GsnI2c_Isr_FP_T)();

extern _RPST_ __GsnI2c_Isr_FP_T __GsnI2c_Isr_FP;


#ifdef __cplusplus
}
#endif

#endif /* _GSN_GPIO_FPT_H_ */


