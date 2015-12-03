/******************************************************************************
 *
 *               COPYRIGHT (c) 2006-2010 GainSpan Corporation
 *                         All Rights Reserved
 *
 * The source code contained or described herein and all documents
 * related to the source code ("Material") are owned by Gainspan
 * Corporation or its licensors.  Title to the Material remains
 * with Gainspan Corporation or its suppliers and licensors.
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
 * Unless otherwise agreed by Gainspan in writing, you may not remove or
 * alter this notice or any other notice embedded in Materials by Gainspan
 * or Gainspan's suppliers or licensors in any way.
 *
 * $RCSfile: buffer.h,v $
 *
 * Project: GSN APP Software
 *
 * Description:
 * Definitions for data buffer handling.
 *
 * Revision History:
 * $Source: /home/cvsroot/gs2000_app_sw/afw/system/gsn/inc/drivers/spi/buffer.h,v $
 * $Log: buffer.h,v $
 * Revision 1.3.10.1  2014/01/23 09:40:17  vbatra
 * Remove Doxygen Errors
 *
 * Revision 1.3  2012/08/16 05:05:51  liju
 * moved
 *
 * Revision 1.1  2012/08/16 04:50:37  liju
 * Initial version
 *
 * Revision 1.1  2012/08/10 10:52:18  rdhamarsingh
 * spi feature complete version
 *
 * Revision 1.5  2011/06/06 07:57:41  liju
 * modified headers with correct info
 *
 * Revision 1.4  2010/02/23 10:04:54  rshanmugham
 * Corrected Copyright Information
 *
 * Revision 1.3  2009/09/29 04:15:18  ddobkin
 * minor edits to comments
 *
 * Revision 1.2  2009/09/02 17:03:43  ddobkin
 * Added file doc, defined new group GEPS Buffer Definitions, included in GEPS Support service group, ingroup stmts for type definitions.
 *
 * Revision 1.1.1.1  2009/04/28 07:50:38  spurohit
 * Created
 *
 * Revision 1.1  2009/02/26 11:01:17  ihiremath
 * added core
 *
 * Revision 1.1  2009/02/10 11:27:09  ihiremath
 * added core
 *
 * Revision 1.1  2009/01/19 13:12:22  ihiremath
 * GEPS 2.0 pre-alpha.
 *
 * Revision 1.1  2008/11/12 05:42:40  ihiremath
 * Adding core files.
 *
 * Revision 1.1.1.1  2008/07/10 06:25:49  vbatra
 * Initial Import
 *
 * Revision 1.2  2008/05/24 10:46:09  spurohit
 * Copyright changed to 2008
 *
 * Revision 1.1.1.1  2007/08/17 08:45:35  spurohit
 * Updating the New Directory Structure
 *
 * Revision 1.2  2007/07/04 08:27:17  amarjeet
 * comminting R003 Release
 *
 * Revision 1.1  2007/05/17 04:38:12  kmahesh
 * Initial version
 *
 * Revision 1.2  2007/05/09 10:17:20  kmahesh
 * Added file header.
 *
 * Revision 1.1  2007/01/04 10:28:54  ram
 * Common Folder
 *
 * Revision 1.5  2006/04/07 09:52:58  pschwarz
 * added BUFFER32
 *
 * Revision 1.4  2006/04/03 15:02:41  pschwarz
 * update according to code review
 *
 * Revision 1.3  2006/03/17 12:39:50  pschwarz
 * added 16 data buffer
 *
 * Revision 1.2  2006/01/26 14:54:01  pschwarz
 * applying coding rules
 *
 * Revision 1.0  2005/12/27 15:21:02  pschwarz
 * created
 *
 *****************************************************************************************
 */
 
 
  /**
 *****************************************************************************
 * @file buffer.h
 * @brief Byte, Half-Word, Word Sized Buffer Definitions.
 *    This file contains definitions of buffer types.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GEPSSupport
 *
 * @{
 *****************************************************************************/

 
 
 
 
#ifndef _BUFFER_H_
#define _BUFFER_H_

/*
 * Includes on which the header file depends.
 *****************************************************************************************
 */
#include <stdint.h>

/*
 * General macro definitions. 
 * Type definition with macro is not allowed, constants should be defined as const 
 * variables or as enumerations and function type macros are defined in the "Function 
 * definitions" section.
 *****************************************************************************************
 */
/*
 * Type definitions.
 ******************************************************************************
 */
 

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
 
typedef struct BUFFER8
{
    uint32_t  size;
    uint8_t  *pData;
} BUFFER8;


 
/**
 *****************************************************************************
 * @ingroup GsnBuffers 
 * @brief Definition of a Linked List of Byte Buffers.
 *****************************************************************************/

typedef struct BUFFER8LISTELEMENT
{
    BUFFER8                    buffer;
    struct BUFFER8LISTELEMENT *pNextListItem;
} BUFFER8LISTELEMENT;


/**
 *****************************************************************************
 * @ingroup GsnBuffers 
 * @brief Definition of a Half-Word Buffer.
 *****************************************************************************/

typedef struct BUFFER16
{
    uint32_t  size;
    uint16_t *pData;
//   void *pData;
} BUFFER16;


/**
 *****************************************************************************
 * @ingroup GsnBuffers 
 * @brief Definition of a Linked List of Half-Word Buffers.
 *****************************************************************************/
 
typedef struct BUFFER16LISTELEMENT
{
    BUFFER16                    buffer;
    struct BUFFER16LISTELEMENT *pNextListItem;
} BUFFER16LISTELEMENT;

/**
 *****************************************************************************
 * @ingroup GsnBuffers 
 * @brief Definition of a Word Buffer.
 *****************************************************************************/
 
typedef struct BUFFER32
{
    uint32_t  size;
    uint32_t *pData;
} BUFFER32;

/**
 *****************************************************************************
 * @ingroup GsnBuffers 
 * @brief Definition of a Linked List of Word Buffers.
 *****************************************************************************/
 
 
typedef struct BUFFER32LISTELEMENT
{
    BUFFER32                   buffer;
    struct BUFFER8LISTELEMENT *pNextListItem;
} BUFFER32LISTELEMENT;

/*
 * Constant definitions.
 *****************************************************************************************
 */

/*
 * Global data declarations.
 *****************************************************************************************
 */

/*
 * Function declarations.
 *****************************************************************************************
 */

/*
 * Function definitions.
 * Note, inline specifiers are not defined in ANSI C 1989 and are therefore tool chain 
 * dependent. Furthermore, inline specifiers are only recommendations to compilers, 
 * whereas local functions might be inlined by good compilers without inline specifier.
 *****************************************************************************************
 */

#endif /* _BUFFER_H_ */

/**
 *****************************************************************************
 * 
 * @}
 *****************************************************************************/

