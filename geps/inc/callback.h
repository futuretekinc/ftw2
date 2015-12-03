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
 * $RCSfile: callback.h,v $
 *
 * Project: GSN APP Software
 *
 * Description:
 * Callback function definitions.
 *
 * Revision History:
 * $Source: /home/cvsroot/gs2000_app_sw/afw/system/gsn/inc/callback.h,v $
 * $Log: callback.h,v $
 * Revision 1.1  2012/05/23 08:49:29  aravind
 * no message
 *
 * Revision 1.3  2010/02/23 10:04:54  rshanmugham
 * Corrected Copyright Information
 *
 * Revision 1.2  2009/09/29 04:27:59  ddobkin
 * Minor edits to comments
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
 * Revision 1.2  2007/07/04 08:27:25  amarjeet
 * comminting R003 Release
 *
 * Revision 1.1  2007/05/17 04:38:12  kmahesh
 * Initial version
 *
 * Revision 1.2  2007/05/09 10:17:30  kmahesh
 * Added file header.
 *
 * Revision 1.1  2007/01/04 10:28:54  ram
 * Common Folder
 *
 * Revision 1.9  2006/04/03 15:02:41  pschwarz
 * update according to code review
 *
 * Revision 1.8  2006/02/02 17:43:20  bcarbou
 * Added typedef on pFunction element to use cast
 *
 * Revision 1.7  2006/02/01 13:36:20  pschwarz
 * corrected example in documentation
 *
 * Revision 1.6  2006/01/27 16:00:38  pschwarz
 * removed cost
 *
 * Revision 1.5  2006/01/27 14:14:23  pschwarz
 * changed function handle name in callback classes
 *
 * Revision 1.4  2006/01/26 14:54:01  pschwarz
 * applying coding rules
 *
 * Revision 1.0  2005/12/27 15:21:02  pschwarz
 * created
 *
 *****************************************************************************************
 */
#ifndef _CALLBACK_H_
#define _CALLBACK_H_

/*
 * Includes on which the header file depends.
 *****************************************************************************************
 */
#include <stdint.h>

/*
 * General macro definitions. 
 * Type definition with macro is not allowed.  Constants should be defined as const 
 * variables or as enumerations. Function type macros are defined in the "Function 
 * definitions" section.
 *****************************************************************************************
 */

/*
 * Type definitions.
 *****************************************************************************************
 */
typedef void (*CALLBACK_FCT)(void *pThis, const void *pParam);
typedef void (*CALLBACK32_FCT)(void *pThis, uint32_t value);


/* Callback class */
typedef struct CALLBACK
{
    void *pThis;
    CALLBACK_FCT pFunction;
} CALLBACK;

/* Callback class using a 32 bit return parameter */
typedef struct CALLBACK32
{
    void *pThis;
    CALLBACK32_FCT pFunction;
} CALLBACK32;

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
 * dependent. Furthermore, inline specifiers are only recommendations to compilers 
 * whereas local functions might be inlined by good compilers without inline specifier.
 *****************************************************************************************
 */

#endif /* _CALLBACK_H_ */
