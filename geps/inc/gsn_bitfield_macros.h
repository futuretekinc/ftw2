/******************************************************************************
*
*               COPYRIGHT (c) 2006-2010 GainSpan Corporation
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
* $RCSfile: gsn_bitfield_macros.h,v $
*
* Description : This file contains useful public macros.
*****************************************************************************/
#ifndef _GSN_BITFIELD_MACROS_H_
#define _GSN_BITFIELD_MACROS_H_

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/


/**
 *****************************************************************************
 * @file gsn_bitfield_macros.h
 * @brief GSN Macros public header.
 *
 *    This file contains the public definitions for general macros.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GEPSSupport
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnBitfieldMacros GSN Bitfield Definitions
 * @brief This group contains bitfield macro definitions.
 *****************************************************************************/


/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/


/*****************************************************************************
  * Public Macros
  ****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnBitfieldMacros
 * @brief Create a bitfield.
 *
 *    This macro defines a bitfield.
 * @param bfName - IN Bitfield name. 
 * @param bfLsb - IN Bitfield least significant bit. 
 * @param bfMsb - IN Bitfield most significant bit. 
 * @note
 *    This macro ends up defining 3 enums: bfName_LSB, bfName_MSB, bfName_MASK.
 *****************************************************************************/
#if 0
#define  CREATE_BITFIELD(bfName, bfLsb, bfMsb)  \
    enum {bfName##_LSB = bfLsb, bfName##_MSB = bfMsb, \
                bfName##_MASK = ((UINT32)(((UINT32)2<<bfMsb)-((UINT32)1<<bfLsb)))}
#else
#define  CREATE_BITFIELD(bfName, bfLsb, bfMsb)  \
    enum {bfName##_LSB = bfLsb, bfName##_MSB = bfMsb, \
                bfName##_MASK = \
                ((0xFFFFFFFF>>(31-(bfMsb-bfLsb)))<<bfLsb)}
#endif


/**
 *****************************************************************************
 * @ingroup GsnBitfieldMacros
 * @brief Prepare a bitfield mask.
 *
 *    This macro prepares a mask for the given bitfield.
 * @param fieldLSBBit - IN Bitfield least significant bit. 
 * @param fieldMSBBit - IN Bitfield most significant bit. 
 *****************************************************************************/
#define BITFIELD_MASK(fieldLSBBit, fieldMSBBit) \
    ((UINT32)(((UINT32)2 << (fieldMSBBit)) - ((UINT32)1 << (fieldLSBBit))))



/**
 *****************************************************************************
 * @ingroup GsnBitfieldMacros
 * @brief Test a bitfield.
 *
 *    This macro masks all the fields in the given variable except the one specified.
 * @param var - IN variable in which masking has to be done. 
 * @param fieldName - IN name of the bitfield defined earlier using CREATE_BITFIELD. 
 * @note
 *    This macro can be used to check if any bits are set in the bitfield.
 *****************************************************************************/
#define TEST_BITFIELD(var, fieldName) \
    ((UINT32)(var) & fieldName##_MASK)


/**
 *****************************************************************************
 * @ingroup GsnBitfieldMacros
 * @brief Get a bitfield.
 *
 *    This macro extracts a bitfield from a given variable. The returned value is normalized ie., it
 *    will be available starting from bit position zero.
 * @param var - IN variable from which bitfield has to be extracted. 
 * @param fieldName - IN name of the bitfield defined earlier using CREATE_BITFIELD. 
 *****************************************************************************/
#define GET_BITFIELD(var, fieldName) \
    ((((UINT32)(var) & fieldName##_MASK) >> (fieldName##_LSB)))



/**
 *****************************************************************************
 * @ingroup GsnBitfieldMacros
 * @brief Get a bitfield.
 *
 *    This macro creates a temporary variable with the bitfield set to given value.
 * @param fieldName - IN name of the bitfield defined earlier using CREATE_BITFIELD. 
 * @param bitFieldValue - IN value to set for bitfield. 
 * @note
 *    Multiple MAKE_BITFIELDs can be ORed together to form a variable will various bitfields
 *    within a 32-bit variable set to different values.
 *****************************************************************************/
#define MAKE_BITFIELD(fieldName, bitFieldValue) \
    (((UINT32)(bitFieldValue) << (fieldName##_LSB)) & fieldName##_MASK)
                     

/**
 *****************************************************************************
 * @ingroup GsnBitfieldMacros
 * @brief Set a bitfield.
 *
 *    This macro sets a new value for a bitfield in the given variable.
 * @param var - IN variable in which bitfield has to be set. 
 * @param fieldName - IN name of the bitfield defined earlier using CREATE_BITFIELD. 
 * @param bitFieldValue - IN value to set for the bitfield. 
 *****************************************************************************/
#define SET_BITFIELD(var, fieldName, bitFieldValue) \
    ((var) = (((UINT32)(var) & ~fieldName##_MASK) | \
              MAKE_BITFIELD(fieldName, bitFieldValue)))


/*****************************************************************************/
#endif /* _GSN_BITFIELD_MACROS_H_ */



