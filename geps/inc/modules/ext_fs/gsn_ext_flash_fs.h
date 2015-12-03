/****************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
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
* $RCSfile: gsn_ext_flash_fs.h,v $
*
* Description : This file contains public functions and definitions for External Flash.
******************************************************************************
*/


/*******************************************************************************
*                          Include Files
*******************************************************************************/

#ifndef _EXT_FLASH_FS_H_
#define _EXT_FLASH_FS_H_




#ifdef __cplusplus
extern "C" {
#endif

/* functions implemented */

//#define CONFIG_FROM_SUPERBLOCK_E

void
GsnExtFlash_FsInit(GSN_EXTFLASH_CTX_T *extFlashCtxFs);

PUBLIC 
int GsnExtFlash_FsErase ( long block );

PUBLIC 
int GsnExtFlash_FsWrite ( void * data, long block, long relsector, long size, long relpos );

PUBLIC 
int GsnExtFlash_FsVerifyFlash ( void * data, long block, long relsector, long size, long relpos );

PUBLIC 
int GsnExtFlash_FsRead ( void * data, long block, long blockrel, long datalen );

int GsnExtFlash_FsBlockCopy( long destblock, long soublock );


#ifdef __cplusplus
}
#endif

#endif

