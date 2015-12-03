/******************************************************************************
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
 * $RCSfile: s2w_cfg.c,v $
 *
 * Description:
 *      This file contains public functions definitions for s2w_cfg
 * 
 ******************************************************************************
 */



#include "gsn_includes.h"
#include "main/app_main_ctx.h"
#include "hal/s2w_types.h"

#include "fs/api/api_safe.h"
#include "fs/safe-flash/nor/phy/micron/n25q_32mb_3v_65nm.h"
#include "fs/safe-flash/nor/flashdrv.h"
#include "hal/s2w_config.h"


S2W_PROFILE_PARAMS_T profile_params;

typedef enum f_error_codes
{
  FILE_OPEN_ER=1,
  FILE_WRITE_ER,
  FILE_READ_ER
  
}f_error_codes_t;


UINT8 S2w_SaveS2wProfileParams(S2W_PROFILE_PARAMS_T *defaultProfile);

extern S2W_FLASH_PARAMS_T FlashParams;

UINT8 S2w_SaveS2wProfile(S2W_FLASH_PARAMS_T *s2wProfile, UINT8 index)
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

    if(f_write(&s2wProfile->profile[index], 1, offsetof(S2W_PROFILE_T, socRdCnt),fp) 
                    != offsetof(S2W_PROFILE_T, socRdCnt))
    {
        f_close(fp);
        f_close(fpExt);
        return FILE_WRITE_ER;
    }
    if(f_write(((UINT8 *)&s2wProfile->profile[index])+offsetof(S2W_PROFILE_T, socRdCnt), 1,
                    sizeof(s2wProfile->profile[index]) -  offsetof(S2W_PROFILE_T, socRdCnt), fpExt) 
                    != (sizeof(s2wProfile->profile[index]) -  offsetof(S2W_PROFILE_T, socRdCnt)))
    {
        f_close(fpExt);
        f_close(fp);
        return FILE_WRITE_ER;
    }
    f_close(fp);
    f_close(fpExt);

    return S2W_SUCCESS;
}

UINT8 S2w_LoadS2wProfile(S2W_PROFILE_T *s2wProfile, UINT8 index)
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

    profExtSize = sizeof(S2W_PROFILE_T) - offsetof(S2W_PROFILE_T, socRdCnt);

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
        f_read(((UINT8 *)&FlashParams.profile[index]) + offsetof(S2W_PROFILE_T, socRdCnt), 1, copySize, fpExt);
    }

    /* Save Back */

    /* If this is OTAFU and the profile changed - save the extension */
    if (profExtSize > extSize)
    {
        f_seek(fpExt,0, F_SEEK_SET);
        f_write(((UINT8 *)&FlashParams.profile[index]) + offsetof(S2W_PROFILE_T, socRdCnt), 1, profExtSize, fpExt);
    }

    if(s2wProfile != &FlashParams.profile[index])
    {
        memcpy(s2wProfile, &FlashParams.profile[index], sizeof(S2W_PROFILE_T));
    }

    f_close(fpExt);
    f_close(fp);

    return S2W_SUCCESS;  
}


UINT8 S2w_SaveS2wProfileParams(S2W_PROFILE_PARAMS_T *defaultProfile)
{
    F_FILE *fp = NULL;
    INT32 fileLen;

    memcpy(&profile_params,defaultProfile,sizeof(S2W_PROFILE_PARAMS_T));
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

    return S2W_SUCCESS;

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
  
   if(f_read(&profile_params,1,sizeof(S2W_PROFILE_PARAMS_T),fp) != sizeof(S2W_PROFILE_PARAMS_T))
  {
    f_close(fp);
    return FILE_READ_ER;

  }
  
  f_close(fp);
  
  return S2W_SUCCESS;
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
  if(f_write(macAddr,1,S2W_MAC_ADDR_SIZE,fp) != S2W_MAC_ADDR_SIZE)
    {
      f_close(fp);
      return FILE_WRITE_ER;
    }
  f_close(fp);
  return S2W_SUCCESS;
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
  return S2W_SUCCESS;
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
  if(f_write(macAddr,1,S2W_MAC_ADDR_SIZE,fp) != S2W_MAC_ADDR_SIZE)
    {
      f_close(fp);
      return FILE_WRITE_ER;
    }
  f_close(fp);
  return S2W_SUCCESS;
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
  return S2W_SUCCESS;
}