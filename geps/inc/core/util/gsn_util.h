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
* $RCSfile: gsn_util.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/
#ifndef _GSN_UTIL_H_
#define _GSN_UTIL_H_

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/



/**
 *****************************************************************************
 * @file gsn_util.h
 * @brief GSN defines.
 *    This file contains bit and byte utilities.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GEPSSupport
 *
 * @{
 *****************************************************************************/



/**
 *****************************************************************************
 * @defgroup GsnUtil GSN Bit and Byte Utilities
 *    This group contains utilities for manipulating bits, nibbles, and bytes,
 * including big-endian and little-endian number conversion.
 *****************************************************************************/



/*****************************************************************************
  *  Definitions
  ****************************************************************************/
  
/**
 *****************************************************************************
 * @ingroup GsnUtil 
 * 
 *****************************************************************************/

/*****************************************************************/

#define swap_16(x) (unsigned short)((unsigned short) \
  (((x) >> 8) & 0xffU) | (unsigned short)(((x) & 0xffU) << 8))




/****************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnUtil 
 * 
 *****************************************************************************/

#define GSN_MAX( a, b )      ((( a ) >= ( b )) ? ( a ) : ( b ))


/**
 *****************************************************************************
 * @ingroup GsnUtil 
 * 
 *****************************************************************************/

#define GSN_MIN( a, b )      ((( a ) <= ( b )) ? ( a ) : ( b ))

/**
 *****************************************************************************
 * @ingroup GsnUtil 
 * 
 *****************************************************************************/

#define GSN_NB_ELT( array )  ( sizeof( array )/sizeof(( array )[ 0 ]))

/* Macros to align values on a multiple of 4  */

/**
 *****************************************************************************
 * @ingroup GsnUtil 
 * 
 *****************************************************************************/

#define GSN_ALIGN4_SUP( a ) ((( a ) + 3 ) & ( ~3 ))

/**
 *****************************************************************************
 * @ingroup GsnUtil 
 * 
 *****************************************************************************/

#define GSN_ALIGN4_INF( a ) (( a ) & ( ~3 ))




/**
 *****************************************************************************
 * @ingroup GsnUtil
 * @brief This function places the parts of a UINT16 value in two UINT8 buffer slots.
 *    
 *****************************************************************************/


INLINE  VOID GSN_WR_LITEND_U16 ( UINT8 *const bufferPtr, const  UINT16 value )
{
    bufferPtr[ 0 ] = ( UINT8 ) ( value >>  0 );
    bufferPtr[ 1 ] = ( UINT8 ) ( value >>  8 );
}

/**
 *****************************************************************************
 * @ingroup GsnUtil
 * @brief This function places the parts of a UINT32 value in four UINT8 buffer slots.
 *    
 *****************************************************************************/

INLINE  VOID GSN_WR_LITEND_U32 ( UINT8 *const bufferPtr, const UINT32 value )
{
    bufferPtr[ 0 ] = ( UINT8 ) ( value >>  0 );
    bufferPtr[ 1 ] = ( UINT8 ) ( value >>  8 );
    bufferPtr[ 2 ] = ( UINT8 ) ( value >> 16 );
    bufferPtr[ 3 ] = ( UINT8 ) ( value >> 24 );
}


/**
 *****************************************************************************
 * @ingroup GsnUtil
 * @brief This function constructs a UINT16 value from two UINT8 buffer slots.
 *    
 *****************************************************************************/

INLINE  UINT16 GSN_RD_LITEND_U16 ( const UINT8 *const bufferPtr )
{
    UINT16 value;

    value  = (( UINT16 ) bufferPtr[ 0 ]);
    value |= (( UINT16 ) bufferPtr[ 1 ]) << 8;

    return value;
}



/**
 *****************************************************************************
 * @ingroup GsnUtil
 * @brief This function constructs a UINT32 value from four UINT8 buffer slots.
 *    
 *****************************************************************************/
 
INLINE  UINT32 GSN_RD_LITEND_U32 ( const UINT8 *const bufferPtr )
{
    UINT32 value;

    value  = (( UINT32 ) bufferPtr[ 0 ]);
    value |= (( UINT32 ) bufferPtr[ 1 ]) << 8;
    value |= (( UINT32 ) bufferPtr[ 2 ]) << 16;
    value |= (( UINT32 ) bufferPtr[ 3 ]) << 24;

    return value;
}


/*
 * Macro to write and read a variable in a PDU buffer in BIG ENDIAN
 */
 
 /**
 *****************************************************************************
 * @ingroup GsnUtil
 * @brief This function writes a UINT16 to buffer slots in BIG ENDIAN format.
 *    
 *****************************************************************************/

INLINE  VOID GSN_WR_BIGEND_U16 ( UINT8 *const bufferPtr, const UINT16 value )
{
    bufferPtr[ 1 ] = ( UINT8 ) ( value >>  0 );
    bufferPtr[ 0 ] = ( UINT8 ) ( value >>  8 );
}

 /**
 *****************************************************************************
 * @ingroup GsnUtil
 * @brief This function writes a UINT32 to buffer slots in BIG ENDIAN format.
 *    
 *****************************************************************************/

INLINE  VOID GSN_WR_BIGEND_U32 ( UINT8 *const bufferPtr, const UINT32 value )
{
    bufferPtr[ 3 ] = ( UINT8 ) ( value >>  0 );
    bufferPtr[ 2 ] = ( UINT8 ) ( value >>  8 );
    bufferPtr[ 1 ] = ( UINT8 ) ( value >> 16 );
    bufferPtr[ 0 ] = ( UINT8 ) ( value >> 24 );
}

 /**
 *****************************************************************************
 * @ingroup GsnUtil
 * @brief This function reads a UINT16 from buffer slots in BIG ENDIAN format.
 *    
 *****************************************************************************/

INLINE  UINT16 GSN_RD_BIGEND_U16 ( const UINT8 *const bufferPtr )
{
    UINT16 value;

    value  = (( UINT16 ) bufferPtr[ 1 ]);
    value |= (( UINT16 ) bufferPtr[ 0 ]) << 8;

    return value;
}

 /**
 *****************************************************************************
 * @ingroup GsnUtil
 * @brief This function reads a UINT32 from buffer slots in BIG ENDIAN format.
 *    
 *****************************************************************************/

INLINE  UINT32 GSN_RD_BIGEND_U32 ( const UINT8 *const bufferPtr )
{
    UINT32 value;

    value  = (( UINT32 ) bufferPtr[ 3 ]);
    value |= (( UINT32 ) bufferPtr[ 2 ]) << 8;
    value |= (( UINT32 ) bufferPtr[ 1 ]) << 16;
    value |= (( UINT32 ) bufferPtr[ 0 ]) << 24;

    return value;
}

#endif /* _GSN_UTIL_H_ */



/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/
