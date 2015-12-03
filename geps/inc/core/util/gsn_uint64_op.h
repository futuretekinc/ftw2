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
* $RCSfile: gsn_uint64_op.h,v $
*
* Description : This file contains basic types.
*****************************************************************************/
#ifndef _GSN_UINT64_OP_H_
#define _GSN_UINT64_OP_H_

#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
  * File Inclusions
  ****************************************************************************/

/**
 *****************************************************************************
 * @file gsn_uint64_op.h
 * @brief This file defines a type and functions for handling 64-bit integers.
 *****************************************************************************/




/*****************************************************************************
  * Type Definitions
 
  ****************************************************************************/
  
  
/**
 *****************************************************************************
 * @ingroup GsnTypes
 *****************************************************************************/

#ifndef UINT64
typedef struct UINT64
{
    UINT32 l;
    UINT32 h;
}UINT64;
#define SIZE_OF_UINT64 sizeof(UINT64)
#endif

/*****************************************************************************/


INLINE  VOID GsnUint64_Cpy( UINT64 *destPtr, UINT64 *srcPtr )
{
    destPtr->h = srcPtr->h;
    destPtr->l = srcPtr->l;
}

INLINE  VOID GsnUint64_Set( UINT64 *destPtr, UINT32 l, UINT32 h )
{
    destPtr->h = h;
    destPtr->l = l;
}

/**
 *****************************************************************************
 * @ingroup GEPSSupport
 *
 * @{
 *****************************************************************************/



/**
 *****************************************************************************
 * @defgroup GsnUINT64 GSN UINT64 API
 * @brief This module provides arithmetic operations on UINT64 64-bit integers.
*****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnUINT64
 * @brief Adds two UINT64 variables.
 *    This function adds two UINT64 variables. 
 * @param valPtr - IN ValPtr, pointer to base.
 * @param addValPtr - IN AddValPtr, pointer to the operand to add.
 * @param resultPtr - IN ResultPtr, pointer where the result has to be stored.
 * @retval None.
 * @note The ValPtr and ResultPtr can be identical.
 *****************************************************************************/
PUBLIC VOID 
GsnUint64_Add( const UINT64 *const valPtr, const UINT64 *const addValPtr, 
    UINT64 *const resultPtr );
/**
 *****************************************************************************
 * @ingroup GsnUINT64
 * @brief Subtracts two UINT64 variables.
 *    This function subtracts two UINT64 variables. 
 * @param valPtr - IN ValPtr, pointer to base.
 * @param subValPtr - IN AddValPtr, pointer to the operand to subtract.
 * @param resultPtr - IN ResultPtr, pointer where the result has to be stored.
 * @retval None.
 * @note The ValPtr and ResultPtr can be identical.
 *****************************************************************************/
PUBLIC VOID
GsnUint64_Sub( const UINT64 *const valPtr, const UINT64 *const subValPtr, 
    UINT64 *const resultPtr );

/**
 *****************************************************************************
 * @ingroup GsnUINT64
 * @brief conpares two UINT64 variables.
 *    This function comapres two UINT64 variables. 
 * @param valPtr - IN ValPtr, pointer to base.
 * @param cmpValPtr - IN CmpValPtr, value to be compared.
 * @retval 
 *    (like strncmp)
 *    1: Val > CmpVal
 *    0: Val = CmpVal
 *   -1: Val < CmpVal
 *****************************************************************************/
PUBLIC INT32 
GsnUint64_Cmp( const UINT64 *const valPtr, const UINT64 *const cmpValPtr );

/**
 *****************************************************************************
 * @ingroup GsnUINT64
 * @brief convert UINT64 to ULONG64.
 *    This function converts UINT64 variable to ULONG64. 
 * @param valPtr - IN valPtr, UINT64 value to be converted to ULONG64.
 * @retval result - OUT result, ULONG64 value to be written.
 *****************************************************************************/
PUBLIC INLINE ULONG64 
GsnUint64_ToUlong64( const UINT64 *const valPtr )
{
    ULONG64 retVal;
    retVal = valPtr->h;
    retVal <<= 32;
    retVal += valPtr->l;
    return retVal; 
}

/**
 *****************************************************************************
 * @ingroup GsnUINT64
 * @brief convert ULONG64 to UINT64.
 *    This function converts ULONG64 variable to UINT64. 
 * @param valPtr - IN valPtr, ULONG64 value to be converted to UINT64.
 * @retval result - OUT result, UINT64 value to be written.
 *****************************************************************************/
PUBLIC INLINE UINT64 
GsnUint64_FromUlong64( const ULONG64 *const valPtr )
{
    UINT64 retVal;
    retVal.l = *valPtr & 0xFFFFFFFF;
    retVal.h = *valPtr >> 32;
    return retVal;
}

#ifdef __cplusplus
}
#endif
#endif /*_GSN_UINT64_OP_H_ */


/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/

