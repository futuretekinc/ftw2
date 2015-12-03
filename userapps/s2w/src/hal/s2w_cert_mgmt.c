/*****************************************************************
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
* $RCSfile: s2w_cert_mgmt.c,v $
*
* Description : 
******************************************************************/


/*****************************************************************
  * File Inclusions
  *****************************************************************/

#include "gsn_includes.h"
#include "hal/s2w_cert_mgmt.h"
#include "hal/s2w_types.h"
#include "fs/api/api_safe.h"
#include "main/app_main_ctx.h"
#include "hal/s2w_hal.h"
extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;

S2W_SSL_CERT_SRAM_TABLE_T s2w_ssl_cert_table[S2W_MAX_NUM_CERT];

PUBLIC INT32
S2wCert_MemAlloc (UINT16 size)
{
	UINT32 i = 0;
	UINT8 *pBuf;
	while (i < S2W_MAX_NUM_CERT)
    {
        if (!s2w_ssl_cert_table[i].certAddress)
            break;
        i++;
    }
	if(i == S2W_MAX_NUM_CERT)
	{
		return -1;
	}
    pBuf = gsn_malloc(size + 2);
        if(pBuf == NULL)
            return -1;
    s2w_ssl_cert_table[i].certAddress = pBuf;
    return i;
}

PUBLIC GSN_STATUS
S2wCert_MemFree(UINT8 *name)
{
	UINT32 index = 0;
	while(index < S2W_MAX_NUM_CERT)
	{
		if(!strcmp((const char *)s2w_ssl_cert_table[index].name, (const char *)name))
		{
			gsn_free (s2w_ssl_cert_table[index].certAddress);
			/* Marking the SRAM entry as Invalid */
            gsn_free(s2w_ssl_cert_table[index].name);
            s2w_ssl_cert_table[index].name = NULL;
            s2w_ssl_cert_table[index].certAddress = NULL;
            return GSN_SUCCESS;
		}
		index++;
	}
	return GSN_FAILURE;
}

PUBLIC INT32
S2wCert_SearchRamTable(char *ptr)
{
    INT32 i = 0;
    while(i < S2W_MAX_NUM_CERT)
    {
         //S2w_Printf("name: %s\n\r", s2w_ssl_cert_table[i].cert.name);
         if( !strcmp((const char *)s2w_ssl_cert_table[i].name, ptr))
         {
             /* certificate found */
             //S2w_Printf("found\n\r");
             break;
         }
         i++;
    }
 	if (i == S2W_MAX_NUM_CERT) {

		i = -1;
	}
	return i;

}

INT32
S2wCert_SearchFlash(char *ptr)
{
	F_FILE *fd;
    if(!s2wappMainTaskCtxt->fsInit)
    {
		App_FsInit();
		s2wappMainTaskCtxt->fsInit = TRUE;
        f_enterFS();
	}
	f_chdir("certs");
	fd = f_open(ptr, "r");
	f_chdir("..");

	if(fd)
	{
		f_close(fd);
		return -1;
	}
	else
	{
		return 0;
	}
}

INT32
S2wCert_findFile(char *name)
{
	INT32 retVal;

	retVal = S2wCert_SearchRamTable(name);
	if(retVal == -1)
	{
		return S2wCert_SearchFlash(name);
	}
	else
	{
		return -1;
	}
}
PUBLIC INT32
S2wCert_FlashFileLoad(char *fileName)
{
	INT32 fileLen,index;
	F_FILE *fd; 
	char name[64]={0};
	if(fileName == NULL)
		return -1;
    if(!s2wappMainTaskCtxt->fsInit)
    {
		App_FsInit();
		s2wappMainTaskCtxt->fsInit = TRUE;
        f_enterFS();
	}
	index=sprintf(name,"A:/certs/");	
	index=sprintf(name+index,fileName);	
	fileLen = f_filelength(name);
	if(fileLen == -1)
	{
		name[0]='B';
		fileLen = f_filelength(name);
		if(fileLen == -1)
		{					
			index = -1;		
			goto FlashFileLoadExit;
	}
	}	
	index = S2wCert_MemAlloc (fileLen);
	if(index != -1)
	{
	s2w_ssl_cert_table[index].name = gsn_malloc(strlen(fileName) + 1);
	if(s2w_ssl_cert_table[index].name == NULL)
	{
			S2wCert_MemFree(s2w_ssl_cert_table[index].certAddress);
			index = -1; 	
			goto FlashFileLoadExit;
	}
	strcpy((char*)s2w_ssl_cert_table[index].name, fileName);
	s2w_ssl_cert_table[index].location = CERT_IN_FLASH;
		fd = f_open(name, "r");
		if(fd == NULL)
	{
			S2wCert_MemFree(s2w_ssl_cert_table[index].certAddress);
			gsn_free(s2w_ssl_cert_table[index].name);
			index = -1; 	
			goto FlashFileLoadExit;
		}
		f_read(s2w_ssl_cert_table[index].certAddress+2, 1, fileLen, fd);
		s2w_ssl_cert_table[index].certAddress[0] = (fileLen & 0xff);
		s2w_ssl_cert_table[index].certAddress[1] = ((fileLen >> 8) & 0xff);
		f_close(fd);
	}
FlashFileLoadExit:
	return index;
}
/**
 ******************************************************************
 * @ingroup S2w-Application
 * @brief Process delete SSL certificate. 
 *   This function delete the certificate.
 * @param certName        pointer to to certificate name to delete
 * @param 0   Operation success.
 * @return  1  Operation failed.
 ******************************************************************/
PUBLIC UINT8  
AppS2w_CertDelete(UINT8 *certName)
{
    UINT8 fileName[42]={0};
    INT32 retVal =0;
    UINT32 len;
    if(!s2wappMainTaskCtxt->fsInit)
    {
		App_FsInit();
		s2wappMainTaskCtxt->fsInit = TRUE;
        f_enterFS();
	}
	S2wCert_MemFree(certName);
	len = sprintf((char*)fileName,"A:/certs/");	
	memcpy(fileName+len,certName,strlen((const char *)certName));
	retVal = f_delete((char*)fileName);
	if(retVal == F_NO_ERROR)
	{
		return S2W_SUCCESS; 
	}
	else
		return S2W_FAILURE;			
}
