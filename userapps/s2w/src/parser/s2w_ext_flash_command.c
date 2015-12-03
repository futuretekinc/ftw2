/*****************************************************************
 *
*               COPYRIGHT (c) 20012-2013 GainSpan Corporation
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
* $RCSfile: s2w_ext_flash_command.c,v $
*
* Description : s2w command interprter file
******************************************************************/

/*****************************************************************
  * File Inclusions
  *****************************************************************/
#ifdef S2W_EXT_FLASH_FS_SUPPORT

#include "time.h"
#include <ctype.h>
#include <string.h>
#include "gsn_includes.h"
#include "gsn_version.h"
#include "hal/s2w.h"
#include "hal/s2w_types.h"
#include "hal/s2w_hal.h"
#include "hal/s2w_timer.h"
#include "parser/s2w_parse.h"
#include "parser/s2w_process.h"
#include "parser/s2w_command.h"


#include "config/app_resource_config.h"
#include "main/app_main_ctx.h"

#include "app_events.h"
#include "app_defines_builder.h"
#include "fs/api/api_safe.h"

#include "hal/s2w_config.h"

#include "fs/api/api_safe.h"
#include "fs/safe-flash/nor/flashdrv.h"

#include "gslink\app_mcu_def.h"
#include "ext_app/app_ext_flash.h"

/**
 ******************************************************************
 * Public Declarations
 *****************************************************************/

#define S2W_WR_BUFF_SIZE	1024

extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;


PRIVATE
UINT8 AppS2wCmd_openFile(UINT8 *ptr);

PRIVATE
UINT8 AppS2wCmd_writeFile(UINT8 *pr);

PRIVATE
UINT8 AppS2wCmd_readFile(UINT8 *ptr);

PRIVATE
UINT8 AppS2wCmd_closeFile(UINT8 *ptr);

PRIVATE
UINT8 AppS2wCmd_deleteFile(UINT8 *ptr);
PRIVATE
UINT8 AppS2wCmd_erasePartn(UINT8 *ptr);

PRIVATE UINT8 AppS2wCmd_FsInit(UINT8 *ptr);

/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Table contains all the Serial2WiFi Host commands and
 *        corresponding call backs to process the command.This array
 *        can be exteded to add more host commands.
 ******************************************************************/
PUBLIC const S2W_EXTFLASH_CMD_T s2wExtFlashCmdTable[] =
{
    {"+FINIT", AppS2wCmd_FsInit},
	{"+FOPEN=", AppS2wCmd_openFile},
	{"+FWRITE=", AppS2wCmd_writeFile},
	{"+FREAD", AppS2wCmd_readFile},
	{"+FCLOSE", AppS2wCmd_closeFile},
	{"+FDEL=", AppS2wCmd_deleteFile},
	{"+FPRTNERASE=", AppS2wCmd_erasePartn},
};

PRIVATE
UINT8 AppS2wCmd_FsInit(UINT8 *ptr)
{
    AppExtFlash_FsInit();
    return S2W_SUCCESS;
}

PRIVATE
UINT8 AppS2wCmd_openFile(UINT8 *ptr)
{
	UINT8 *p;
	UINT32 val;

	
	memset(&s2wappMainTaskCtxt->appExtFsCtx.fileInfo, 0, sizeof(s2wappMainTaskCtxt->appExtFsCtx.fileInfo));
	
	/* get the file name file */
    p = AppS2wParse_NextParamGet(&ptr);
	if(!p)
	{
		return S2W_EINVAL;	
	}
	s2wappMainTaskCtxt->appExtFsCtx.fileInfo.pName = p;

	/* get the open flags */
    p = AppS2wParse_NextParamGet(&ptr);
	if(!p)
	{
		return S2W_EINVAL;	
	}

	s2wappMainTaskCtxt->appExtFsCtx.fileInfo.flags = p;

	/* get the partition */
    p = AppS2wParse_NextParamGet(&ptr);
	if(!p)
	{
		return S2W_EINVAL;	
	}
    AppS2wParse_Int(p, &val);
	f_chdrive(val);
	
	s2wappMainTaskCtxt->appExtFsCtx.fileInfo.fd = f_open((const INT8 *)s2wappMainTaskCtxt->appExtFsCtx.fileInfo.pName, (const INT8 *)s2wappMainTaskCtxt->appExtFsCtx.fileInfo.flags);
	
    return S2W_SUCCESS;
}


PRIVATE
UINT8 AppS2wCmd_writeFile(UINT8 *ptr)
{
    UINT8 *p;
	UINT32 val;

    /* get file the size of the file to be written */
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }
    AppS2wParse_Int(p, &val);
	s2wappMainTaskCtxt->appExtFsCtx.fileInfo.size = val;

    return S2W_SUCCESS;
}


PRIVATE
UINT8 AppS2wCmd_readFile(UINT8 *ptr)
{
	INT32 readBytes;
	F_FILE *fd;
	UINT8 *p;
	S2w_Printf("\r\n");/*Response start with a new line*/
    do
    {
    	readBytes = f_read(s2wappMainTaskCtxt->appExtFsCtx.extDataBuffFs,1,1024,s2wappMainTaskCtxt->appExtFsCtx.fileInfo.fd);
		if(readBytes > 0)
		{
//		    S2w_Printf("%c%c%d%04d", S2W_ESC, 'F', fileInfo.fd, readBytes);
			AppS2wHal_CharNPut(s2wappMainTaskCtxt->appExtFsCtx.extDataBuffFs, readBytes);
		}
    }while(readBytes > 0);
	
    return S2W_SUCCESS;
}


PRIVATE
UINT8 AppS2wCmd_closeFile(UINT8 *ptr)
{
    f_close(s2wappMainTaskCtxt->appExtFsCtx.fileInfo.fd);
	s2wappMainTaskCtxt->appExtFsCtx.fileInfo.fd = NULL;
	s2wappMainTaskCtxt->appExtFsCtx.fileInfo.flags = NULL;
	s2wappMainTaskCtxt->appExtFsCtx.fileInfo.pName = NULL;
	s2wappMainTaskCtxt->appExtFsCtx.fileInfo.size = 0;
    
    return S2W_SUCCESS;
}

PRIVATE
UINT8 AppS2wCmd_erasePartn(UINT8 *ptr)
{
    UINT8 *p;
    UINT32 partn;
    p = AppS2wParse_NextParamGet(&ptr);
    if (!p)
    {
        return S2W_EINVAL;
    }

    AppS2wParse_Int(p, (UINT32 *)&partn);
  	f_format(partn);  
	
    return S2W_SUCCESS;
}

PRIVATE
UINT8 AppS2wCmd_deleteFile(UINT8 *ptr)
{

    INT32 retVal;
	UINT8 *p;
	UINT8 *fileName;
	UINT8 partnNum;
	UINT32 val = 0;
	/* get the file name file */
    p = AppS2wParse_NextParamGet(&ptr);
	if(!p)
	{
		return S2W_EINVAL;	
	}
	fileName = p;
	p = AppS2wParse_NextParamGet(&ptr);
	if(!p)
	{
		return S2W_EINVAL;	
	}
    AppS2wParse_Int(p, (UINT32 *)&val);
	partnNum = val;
	retVal = f_delete((const INT8 *) fileName);
	if(retVal < 0)
	{
		return S2W_FAILURE;
	}
	else
	{
		return S2W_SUCCESS;
	}
}


PUBLIC UINT8
AppS2wHal_FileWriteDataGet(F_FILE *fd, UINT32 dataLen)
{
    GSN_STATUS status = S2W_SUCCESS;
	UINT32 writeLen = 0;

	memset(s2wappMainTaskCtxt->appExtFsCtx.extDataBuffFs, 0, sizeof(s2wappMainTaskCtxt->appExtFsCtx.extDataBuffFs));

	S2w_Printf("\r\nLoad the File to be written\r\n");
    if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush();
    }

    while(dataLen)
    {
        writeLen = dataLen >= S2W_WR_BUFF_SIZE? S2W_WR_BUFF_SIZE:dataLen;

        AppS2wHal_CharNGet(s2wappMainTaskCtxt->appExtFsCtx.extDataBuffFs,writeLen);
		/* write in to file */
		f_write(s2wappMainTaskCtxt->appExtFsCtx.extDataBuffFs, 1, writeLen, fd);
		dataLen -= writeLen;
    }

	S2w_Printf("\r\nOK\r\n");
    if(s2wappMainTaskCtxt->serialDeviceId == S2W_PORT_FS_SPI)
    {
        s2wSpiFs_Flush();
    }

   return status;
}

#endif

