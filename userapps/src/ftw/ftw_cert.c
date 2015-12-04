#include "gsn_includes.h"
#include "hal/s2w_types.h"
#include "fs/api/api_safe.h"
#include "main/app_main_ctx.h"
#include "hal/s2w_hal.h"
#include "ftw_cert.h"
#include "ftw_mem.h"
#include "ftw_fs.h"

extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;

static FTW_SSL_CERT_SRAM_TABLE _pxSSLCertTable[FTW_CERT_MAX_NUM];

FTW_SSL_CERT_SRAM_TABLE_PTR FTW_CERT_create(UINT16 size)
{
	UINT32 i = 0;
	UINT8 *pBuf;
	while (i < FTW_CERT_MAX_NUM)
    {
        if (!_pxSSLCertTable[i].pCertAddress)
        {
            break;
        }
        i++;
    }
    
	if(i == FTW_CERT_MAX_NUM)
	{
		return NULL;
	}
    
    pBuf = FTW_MEM_allocZero(size + 2);
    if(pBuf == NULL)
    {
        return NULL;
    }
    
    _pxSSLCertTable[i].pCertAddress = pBuf;
    
    return &_pxSSLCertTable[i];
}

FTW_RET FTW_CERT_free(FTW_SSL_CERT_SRAM_TABLE_PTR pxCert)
{
	UINT32 index = 0;
	while(index < FTW_CERT_MAX_NUM)
	{
		if(&_pxSSLCertTable[index] == pxCert)
		{
            if (_pxSSLCertTable[index].pCertAddress != NULL)
            {
                FTW_MEM_free(_pxSSLCertTable[index].pCertAddress);
                _pxSSLCertTable[index].pCertAddress = NULL;
            }
			/* Marking the SRAM entry as Invalid */
            if (_pxSSLCertTable[index].pName != NULL)
            {
                FTW_MEM_free(_pxSSLCertTable[index].pName);
                _pxSSLCertTable[index].pName = NULL;
            }
            
            return GSN_SUCCESS;
		}
		index++;
	}
	return GSN_FAILURE;
}

FTW_SSL_CERT_SRAM_TABLE_PTR FTW_CERT_searchRamTable(char *ptr)
{
    INT32 i = 0;
    while(i < FTW_CERT_MAX_NUM)
    {
         if( !strcmp((const char *)_pxSSLCertTable[i].pName, ptr))
         {
             break;
         }
         i++;
    }
    
 	if (i == FTW_CERT_MAX_NUM) 
    {
        return  NULL;
	}
    
	return &_pxSSLCertTable[i];

}

INT32 FTW_CERT_searchFlash(char *ptr)
{
	F_FILE *fd;

    FTW_FS_init();

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

INT32 FTW_CERT_findFile(char *name)
{
	INT32 retVal;

	if (FTW_CERT_searchRamTable(name) == NULL)
	{
		return FTW_CERT_searchFlash(name);
	}
	else
	{
		return -1;
	}
}

FTW_SSL_CERT_SRAM_TABLE_PTR FTW_CERT_flashFileLoad(char *fileName)
{
	INT32 fileLen,index;
	F_FILE *fd; 
	char name[64]={0};
    FTW_SSL_CERT_SRAM_TABLE_PTR pxCert;
    
	if(fileName == NULL)
    {
		return NULL;
    }
    
    FTW_FS_init();

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
	pxCert = FTW_CERT_create(fileLen);
	if(pxCert != NULL)
	{
        pxCert->pName = FTW_MEM_allocZero(strlen(fileName) + 1);
        if(pxCert->pName == NULL)
        {
            FTW_CERT_free(pxCert);
            pxCert = NULL;
			goto FlashFileLoadExit;
        }
        
        strcpy((char*)pxCert->pName, fileName);
        pxCert->xLocation = FTW_CERT_IN_FLASH;
		fd = f_open(name, "r");
		if(fd == NULL)
        {
			FTW_CERT_free(pxCert);
            pxCert = NULL;
			goto FlashFileLoadExit;
		}
        
		f_read(pxCert->pCertAddress+2, 1, fileLen, fd);
		pxCert->pCertAddress[0] = (fileLen & 0xff);
		pxCert->pCertAddress[1] = ((fileLen >> 8) & 0xff);
		f_close(fd);
	}
    
FlashFileLoadExit:
    
    return  pxCert;
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
FTW_RET FTW_CERT_delete(UINT8 *certName)
{
    UINT8 fileName[42]={0};
    INT32 retVal =0;
    UINT32 len;
    
	FTW_FS_init();
    
    FTW_CERT_delete(certName);
	len = sprintf((char*)fileName,"A:/certs/");	
	memcpy(fileName+len,certName,strlen((const char *)certName));
	retVal = f_delete((char*)fileName);
	if(retVal == F_NO_ERROR)
	{
		return FTW_RET_OK; 
	}
	else
		return FTW_RET_ERROR;			
}
