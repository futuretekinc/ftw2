#include "gsn_includes.h"
#include "main/app_main_ctx.h"
#include "hal/s2w_types.h"

#include "fs/api/api_safe.h"
#include "fs/safe-flash/nor/phy/micron/n25q_32mb_3v_65nm.h"
#include "fs/safe-flash/nor/flashdrv.h"
#include "ftw_config.h"

static const char_ptr _pFullPathDir = "config";

static const FTW_CONFIG  _xDefaultConfig = 
{
    .xNet = 
    {
        .pSSID  =   "FTR-01",
        .pWWPA  =   "4rnekd9wkd"
    },
    
    .xMQTT = 
    {
        .pClientID = "001dc914feae",
        .bEnable = TRUE,
        .xBroker = 
        {
            .xServer    =
            {
                .xIPAddress     = { 54, 178, 154, 197},
                .usPort         = 8883,
            },
            .xKeepalive =
            {
                .ulTime         = 30000,    // ms
                .ulRetryCount   = 5,
            },
            .xAuth = 
            {
                .bEnabled = 1,
                .pUserName = "001dc914feae",
                .pPassword = "Sm4ytjGsPEfGvDhSDJ_ZPiBUXyo="
            },
        },    
        .xTester = 
        {
            .ulStartDelay       = 10000,    // ms
            .xStatus    =
            {
                .ulPeriod       = 60000
            },
            .ulSensorCount      = 1,
            .xSensors   =
            {
                {
                    .pName=     "temperature-001dc914feae-1",
                    .ulPeriod   = 5000
                }
            }
        },
        .ulPubTimeout = 10000,              // ms
    }    
};

static FTW_CONFIG_PTR  _pxConfig  = NULL;

FTW_RET FTW_CONFIG_init(char_ptr pFileName)
{
    if (FTW_CONFIG_load(pFileName) != FTW_RET_OK)
    {
        FTW_TRACE("Default configuration loaded.\n");
        FTW_CONFIG_loadDefault();
    }
    
    return  FTW_RET_OK;
}

FTW_RET FTW_CONFIG_loadDefault(void)
{
    FTW_RET         xRet = FTW_RET_OK;

    if (_pxConfig == NULL)
    {
        _pxConfig = FTW_MEM_allocZero(sizeof(FTW_CONFIG));
        if (_pxConfig == NULL)
        {
            return  FTW_RET_NOT_ENOUGH_MEMORY;
        }
    }

    memcpy(_pxConfig, &_xDefaultConfig, sizeof(FTW_CONFIG));        
    
    return  xRet;
}

FTW_RET FTW_CONFIG_load(char_ptr pFileName)
{
    FTW_RET         xRet = FTW_RET_OK;
    char_ptr        pFullPathName = NULL;
    uint_32         ulFullPathNameLen;
    F_FILE          *pFile;
    FTW_CONFIG_PTR  pxConfig;
    
    ulFullPathNameLen = strlen(_pFullPathDir) + 1 + strlen(pFileName);
    pFullPathName = FTW_MEM_allocZero(ulFullPathNameLen + 1);
    if (pFullPathName == NULL)
    {
        FTW_TRACE("Not enough memory.\n");
        xRet = FTW_RET_NOT_ENOUGH_MEMORY;
        goto error;
    }
    
    snprintf(pFullPathName, ulFullPathNameLen, "%s/%s", _pFullPathDir, pFileName);
    
    if (f_filelength(pFullPathName) != sizeof(FTW_CONFIG))
    {
        FTW_TRACE("Invalid configuration file(file size missmatch).\n");
        xRet = FTW_RET_CONFIG_NOT_EXISTS;
        goto error;
    }
    
    pxConfig = FTW_MEM_allocZero(sizeof(FTW_CONFIG));
    if (pxConfig == NULL)
    {
        FTW_TRACE("Not enough memory.\n");
        xRet = FTW_RET_NOT_ENOUGH_MEMORY;
        goto error;
    }
    
    pFile = f_open(pFullPathName, "r");
    if (pFile == NULL)
    {
        FTW_TRACE("Configuration file not exist.\n");
        xRet = FTW_RET_CONFIG_NOT_EXISTS;
        goto error;
    }
        
    f_read(pxConfig, 1, sizeof(FTW_CONFIG), pFile);
    f_close(pFile);

    if (_pxConfig == NULL)
    {
        _pxConfig = FTW_MEM_allocZero(sizeof(FTW_CONFIG));
        if (_pxConfig == NULL)
        {
            FTW_TRACE("Not enough memory.\n");
            xRet = FTW_RET_NOT_ENOUGH_MEMORY;
            goto error;
        }
    }

    memcpy(_pxConfig, pxConfig, sizeof(FTW_CONFIG));        
    
error:    
    if (pxConfig != NULL)
    {
        FTW_MEM_free(pxConfig);
    }
    
    if (pFullPathName != NULL)
    {
        FTW_MEM_free(pFullPathName);
    }
    
    return  xRet;
}

FTW_RET FTW_CONFIG_save(char_ptr pFileName)
{
    FTW_RET         xRet = FTW_RET_OK;
    char_ptr        pFullPathName = NULL;
    uint_32         ulFullPathNameLen;
    F_FILE          *pFile;
    FTW_CONFIG_PTR  pxConfig;
    
    ulFullPathNameLen = strlen(_pFullPathDir) + 1 + strlen(pFileName);
    pFullPathName = FTW_MEM_allocZero(ulFullPathNameLen + 1);
    if (pFullPathName == NULL)
    {
        xRet = FTW_RET_NOT_ENOUGH_MEMORY;
        goto error;
    }
    
    snprintf(pFullPathName, ulFullPathNameLen, "%s/%s", _pFullPathDir, pFileName);    
    if (f_filelength(pFullPathName) != sizeof(FTW_CONFIG))
    {
        xRet = FTW_RET_CONFIG_NOT_EXISTS;
        goto error;
    }
    
    pFile = f_open(pFullPathName, "w");
    if (pFile == NULL)
    {
	    f_mkdir(_pFullPathDir);
        pFile = f_open(pFullPathName, "w");
        if (pFile == NULL)
        {
            xRet = FTW_RET_CONFIG_CANT_CREATE;
            goto error;
        }
    }
        
    f_write(_pxConfig, 1, sizeof(FTW_CONFIG), pFile);
    f_close(pFile);

error:

    if (pFullPathName != NULL)
    {
        FTW_MEM_free(pFullPathName);
    }
    
    return  xRet;
}

FTW_NET_CONFIG_PTR  FTW_CONFIG_getNet(void)
{
    if (_pxConfig != NULL)
    {
        return  &_pxConfig->xNet;
    }
    
    return  NULL;
}
FTW_MQTT_CONFIG_PTR FTW_CONFIG_getMQTT(void)
{
    if (_pxConfig != NULL)
    {
        return  &_pxConfig->xMQTT;
    }
    
    return  NULL;
}




FTW_PROFILE_PARAMS_T profile_params;

typedef enum f_error_codes
{
  FILE_OPEN_ER=1,
  FILE_WRITE_ER,
  FILE_READ_ER
  
}f_error_codes_t;


UINT8 S2w_SaveS2wProfileParams(FTW_PROFILE_PARAMS_T *defaultProfile);

extern FTW_FLASH_PARAMS_T FlashParams;

UINT8 S2w_SaveS2wProfile(FTW_FLASH_PARAMS_T *s2wProfile, UINT8 index)
{
    F_FILE *fp, *fpExt;

    if(index == 0)
    {
        fp = f_open("A:/s2w_profile0.conf","r+");
        if(!fp)
            fp = f_open("A:/s2w_profile0.conf","w");
            
        fpExt = f_open("A:/s2w_profile0_ext.conf", "r+"); 
        if(!fpExt)
            fpExt = f_open("A:/s2w_profile0_ext.conf", "w");
    }
    else if(index == 1)
    {
        fp = f_open("A:/s2w_profile1.conf","r+");
        if(!fp)
            fp = f_open("A:/s2w_profile1.conf","w");
            
        fpExt = f_open("A:/s2w_profile1_ext.conf", "r+"); 
        if(!fpExt)
            fpExt = f_open("A:/s2w_profile1_ext.conf", "w");
    }

    if (!fp || !fpExt)
    {     
        //S2w_Printf("\r\nFile cannot be opened!\r\n");
        if(fpExt)
            f_close(fpExt);
        if(fp)
            f_close(fp);
        return FILE_OPEN_ER;
    }

    if(f_write(&s2wProfile->profile[index], 1, offsetof(FTW_PROFILE_T, socRdCnt),fp) 
                    != offsetof(FTW_PROFILE_T, socRdCnt))
    {
        f_close(fp);
        f_close(fpExt);
        return FILE_WRITE_ER;
    }
    if(f_write(((UINT8 *)&s2wProfile->profile[index])+offsetof(FTW_PROFILE_T, socRdCnt), 1,
                    sizeof(s2wProfile->profile[index]) -  offsetof(FTW_PROFILE_T, socRdCnt), fpExt) 
                    != (sizeof(s2wProfile->profile[index]) -  offsetof(FTW_PROFILE_T, socRdCnt)))
    {
        f_close(fpExt);
        f_close(fp);
        return FILE_WRITE_ER;
    }
    f_close(fp);
    f_close(fpExt);

    return FTW_SUCCESS;
}

UINT8 S2w_LoadS2wProfile(FTW_PROFILE_T *s2wProfile, UINT8 index)
{
    F_FILE *fp = NULL, *fpExt;
    UINT32 extSize = 0;
    UINT32 copySize = 0, profExtSize = 0, file_size = 0;

    if(index == 0)
    {
       fp = f_open("A:/s2w_profile0.conf","r");
       file_size = f_filelength("A:/s2w_profile0.conf");
       extSize = f_filelength("A:/s2w_profile0_ext.conf");
       if((extSize != -1) && extSize != 0)
       {
           fpExt = f_open("A:/s2w_profile0_ext.conf", "r+"); 
       }
       else
       {
           fpExt = f_open("A:/s2w_profile0_ext.conf", "w+");
           extSize = 0;
       }
       
    }
    else if(index == 1)
    {
       fp = f_open("A:/s2w_profile1.conf","r");
       file_size = f_filelength("A:/s2w_profile1.conf");
       extSize = f_filelength("A:/s2w_profile1_ext.conf");
       if((extSize != -1) && extSize != 0)
       {
           fpExt = f_open("A:/s2w_profile1_ext.conf", "r+"); 
       }
       else
       {
           fpExt = f_open("A:/s2w_profile1_ext.conf", "w+"); 
           extSize = 0;
       }
    }

    if (!fp || !fpExt)
    {     
    //S2w_Printf("\r\nFile cannot be opened!\r\n");
        if(fpExt)
            f_close(fpExt);
        if(fp)
            f_close(fp);
        return FILE_OPEN_ER;
    }

    profExtSize = sizeof(FTW_PROFILE_T) - offsetof(FTW_PROFILE_T, socRdCnt);

    if(profExtSize > extSize)
    {
      /* OTAFU from 5.1.X where X is less than or equal to 4  - Upgrade */
        copySize = extSize;
    }
    else
    {
      /* If extSize == profileExtSizeThis then it is same FW boot
         Else if the extSize > profileExtSize it is a downgrade

         In both cases only copy the size equivalent of the profExtSize
       */
        copySize = profExtSize;
    }

    /* Copy the file_size from the profileN.conf to the profile */
    if(f_read(&FlashParams.profile[index],1,file_size,fp) != file_size)
    {
        f_close(fp);
        f_close(fpExt);
        return FILE_READ_ER;
    }

    /* Copy the copySize from the profileN_ext.conf to the profile */
    if (copySize)
    {
        f_read(((UINT8 *)&FlashParams.profile[index]) + offsetof(FTW_PROFILE_T, socRdCnt), 1, copySize, fpExt);
    }

    /* Save Back */

    /* If this is OTAFU and the profile changed - save the extension */
    if (profExtSize > extSize)
    {
        f_seek(fpExt,0, F_SEEK_SET);
        f_write(((UINT8 *)&FlashParams.profile[index]) + offsetof(FTW_PROFILE_T, socRdCnt), 1, profExtSize, fpExt);
    }

    if(s2wProfile != &FlashParams.profile[index])
    {
        memcpy(s2wProfile, &FlashParams.profile[index], sizeof(FTW_PROFILE_T));
    }

    f_close(fpExt);
    f_close(fp);

    return FTW_SUCCESS;  
}


UINT8 S2w_SaveS2wProfileParams(FTW_PROFILE_PARAMS_T *defaultProfile)
{
    F_FILE *fp = NULL;
    INT32 fileLen;

    memcpy(&profile_params,defaultProfile,sizeof(FTW_PROFILE_PARAMS_T));
    fileLen = f_filelength("A:/s2w_profile_params.conf");
    if(fileLen != 0 && fileLen != -1)
        fp = f_open("A:/s2w_profile_params.conf","r+");
    else
        fp = f_open("A:/s2w_profile_params.conf","w");

    if (!fp)
    {     
    //S2w_Printf("\r\nFile cannot be opened!\r\n");
        return FILE_OPEN_ER;
    }

    if(f_write(&profile_params,1,sizeof(profile_params),fp) != sizeof(profile_params))
    {
        f_close(fp);
        return FILE_WRITE_ER;
    }

    f_close(fp);

    return FTW_SUCCESS;

}


UINT8 S2w_LoadS2wProfileParams()
{
  F_FILE *fp;
  
  fp = f_open("A:/s2w_profile_params.conf","r");
    
    if (!fp)
  {     
    //S2w_Printf("\r\nFile cannot be opened!\r\n");
     return FILE_OPEN_ER;
  }
  
  long file_size = f_filelength("A:/s2w_profile_params.conf");
  
   if(f_read(&profile_params,1,sizeof(FTW_PROFILE_PARAMS_T),fp) != sizeof(FTW_PROFILE_PARAMS_T))
  {
    f_close(fp);
    return FILE_READ_ER;

  }
  
  f_close(fp);
  
  return FTW_SUCCESS;
}

/* Station Mac addre
 */

UINT8 S2w_SaveMacAddr(const UINT8 *macAddr)
{
  F_FILE *fp;
    fp = f_open("A:/s2w_mac.conf","w+");
    if (!fp)
  {     
     return FILE_OPEN_ER;
  }
  if(f_write(macAddr,1,FTW_MAC_ADDR_SIZE,fp) != FTW_MAC_ADDR_SIZE)
    {
      f_close(fp);
      return FILE_WRITE_ER;
    }
  f_close(fp);
  return FTW_SUCCESS;
}
UINT8 S2w_LoadMacAddr(UINT8 *macAddr)
{
  F_FILE *fp;
 fp = f_open("A:/s2w_mac.conf","r");    
    if (!fp)
  {     
     return FILE_OPEN_ER;
  }
  long file_size = f_filelength("A:/s2w_mac.conf");
   if(f_read(macAddr,1,file_size,fp) != file_size)
  {
    f_close(fp);
    return FILE_READ_ER;
  }
  f_close(fp);
  return FTW_SUCCESS;
}


/* Limited AP mac addr..
 */
UINT8 S2w_SaveApMacAddr(const UINT8 *macAddr)
{
  F_FILE *fp;
    fp = f_open("A:/s2w_ap_mac.conf","w+");
    if (!fp)
  {
     return FILE_OPEN_ER;
  }
  if(f_write(macAddr,1,FTW_MAC_ADDR_SIZE,fp) != FTW_MAC_ADDR_SIZE)
    {
      f_close(fp);
      return FILE_WRITE_ER;
    }
  f_close(fp);
  return FTW_SUCCESS;
}
UINT8 S2w_LoadApMacAddr(UINT8 *macAddr)
{
  F_FILE *fp;
 fp = f_open("A:/s2w_ap_mac.conf","r");
    if (!fp)
  {
     return FILE_OPEN_ER;
  }
  long file_size = f_filelength("A:/s2w_mac.conf");
   if(f_read(macAddr,1,file_size,fp) != file_size)
  {
    f_close(fp);
    return FILE_READ_ER;
  }
  f_close(fp);
  return FTW_SUCCESS;
}