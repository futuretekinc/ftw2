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
* $RCSfile: gsn_types.h,v $
*
* Description : This file contains basic types.
*****************************************************************************/
#ifndef _GSN_TYPES_H_
#define _GSN_TYPES_H_

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/


/**
 *****************************************************************************
 * @file gsn_types.h
 * @brief GSN Basic types.
 *    This file contains the basic types.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GEPSSupport
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnTypes GSN Integer Types
 * @brief This group contains integer, char, and boolean type definitions.
 *****************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/



/*****************************************************************************
  * Type Definitions
  ****************************************************************************/
  
  
/**
 *****************************************************************************
 * @ingroup GsnTypes 
 *****************************************************************************/  
  
  
#ifndef UINT8
typedef unsigned char UINT8;
#define SIZE_OF_UINT8 sizeof(UINT8)
#endif
    
/**
 *****************************************************************************
 * @ingroup GsnTypes 
 *****************************************************************************/ 	
	
#ifndef INT8
typedef char INT8;
#define SIZE_OF_INT8 sizeof(INT8)
#endif

/**
 *****************************************************************************
 * @ingroup GsnTypes 
 *****************************************************************************/ 

#ifndef INT16
typedef short INT16;
#define SIZE_OF_INT16 sizeof(INT16)
#endif
    
/**
 *****************************************************************************
 * @ingroup GsnTypes 
 *****************************************************************************/ 	
	
#ifndef UINT16
typedef unsigned short UINT16;
#define SIZE_OF_UINT16 sizeof(UINT16)
#endif

/**
 *****************************************************************************
 * @ingroup GsnTypes 
 *****************************************************************************/ 
    
#ifndef INT32
typedef int INT32;
#define SIZE_OF_INT32 sizeof(INT32)
#endif
    
/**
 *****************************************************************************
 * @ingroup GsnTypes 
 *****************************************************************************/ 	
	
#ifndef UINT32
typedef unsigned int UINT32;
#define SIZE_OF_UINT32 sizeof(UINT32)
#endif

/**
 *****************************************************************************
 * @ingroup GsnTypes 
 *****************************************************************************/ 	
	
#ifndef ULONG32
typedef unsigned long ULONG32;
#define SIZE_OF_ULONG32 sizeof(ULONG32)
#endif

/**
 *****************************************************************************
 * @ingroup GsnTypes 
 *****************************************************************************/ 
       
#ifndef BOOL
typedef UINT8 BOOL;
#define SIZE_OF_BOOL sizeof(BOOL)
#endif

/**
 *****************************************************************************
 * @ingroup GsnTypes 
 *****************************************************************************/ 
    
#ifndef LONG64
typedef long long LONG64;
#endif
    
/**
 *****************************************************************************
 * @ingroup GsnTypes 
 *****************************************************************************/ 	
	
#ifndef ULONG64
typedef unsigned long long ULONG64;
#endif

/**
 *****************************************************************************
 * @ingroup GsnTypes 
 *****************************************************************************/ 

typedef INT32 GSN_STATUS;

/*
 * Type definitions.
 *****************************************************************************************
 */
typedef void (*GSN_CB_FCT)(void *pThis, const void *pParam);
typedef void (*GSN_CB32_FCT)(void *pThis, UINT32 value);


/* Callback class */
typedef struct GSN_CB
{
    void *pThis;
    GSN_CB_FCT pFunction;
} GSN_CB_T;

/* Callback class using a 32 bit return parameter */
typedef struct GSN_CB32
{
    void *pThis;
    GSN_CB32_FCT pFunction;
} GSN_CB32_T;


/**
 *****************************************************************************
 * @defgroup GsnBuffers GSN Buffer Definitions
 * @brief This Group Provides Buffer Types with Byte, Half-Word, and Word Elements.
 *****************************************************************************/

 
/**
 *****************************************************************************
 * @ingroup GsnBuffers 
 * @brief Byte Buffer.
 *****************************************************************************/ 
 
typedef struct GSN_BUF8
{
    UINT32  size;
    UINT8   *pData;
} GSN_BUF8_T;


 
/**
 *****************************************************************************
 * @ingroup GsnBuffers 
 * @brief Definition of a Linked List of Byte Buffers.
 *****************************************************************************/

typedef struct GSN_BUF8LISTELMT
{
    GSN_BUF8_T                 buf;
    struct GSN_BUF8LISTELMT *pNextListItem;
} GSN_BUF8LISTELMT_T;


/**
 *****************************************************************************
 * @ingroup GsnBuffers 
 * @brief Definition of a Half-Word Buffer.
 *****************************************************************************/

typedef struct GSN_BUF16
{
    UINT32  size;
    UINT16  *pData;
} GSN_BUF16_T;


/**
 *****************************************************************************
 * @ingroup GsnBuffers 
 * @brief Definition of a Linked List of Half-Word Buffers.
 *****************************************************************************/
 
typedef struct GSN_BUF16LISTELMT
{
    GSN_BUF16_T                 buf;
    struct GSN_BUF16LISTELMT *pNextListItem;
} GSN_BUF16LISTELMT_T;

/**
 *****************************************************************************
 * @ingroup GsnBuffers 
 * @brief Definition of a Word Buffer.
 *****************************************************************************/
 
typedef struct GSN_BUF32
{
    UINT32  size;
    UINT32 *pData;
} GSN_BUF32_T;

/**
 *****************************************************************************
 * @ingroup GsnBuffers 
 * @brief Definition of a Linked List of Word Buffers.
 *****************************************************************************/
 
 
typedef struct GSN_BUF32LISTELMT
{
    GSN_BUF32_T                 buf;
    struct GSN_BUF32LISTELMT *pNextListItem;
} GSN_BUF32LISTELMT_T;






/*****************************************************************************/
#endif /* _GSN_TYPES_H_ */
