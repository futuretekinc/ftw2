#include "gsn_types.h"
#include "gsn_includes.h"
#include "gsn_error.h"
#include "app_defines_builder.h"
#include "main/app_main_ctx.h"
#include "hal/s2w_hal_specific.h"
#include "hal/s2w.h"
#include "parser/s2w_process.h"
#include "hal/s2w_types.h"
#include "hal/s2w_hal.h"
#include "app_rtc_mem.h"
#include "config/app_resource_config.h"
#include "fs/api/api_safe.h"
#include "fs/safe-flash/nor/flashdrv.h"
#include "main/gsn_br_flashldr.h"
#include "ftw_config.h"
#include "web_prov\s2w_web_prov.h"
#include "app_rtc_mem.h"
#include "hal/s2w_net.h"
#include "modules/pwr_mgmt/gsn_pwr_mgmt.h"
#include "ext_app/app_ext_flash.h"
#include "parser/s2w_command.h"

extern FTW_PROFILE_PARAMS_T profile_params;

VOID
S2w_macAddrRTCGet(UINT8* mac) // right after profile
{
    
	GSN_MAC_ADDR_T* macAddr = (GSN_MAC_ADDR_T*)(GSN_RTC_SRAM_BLOCK0_ADDR + sizeof(APP_RTC_SECNDRY_MEM_INFO_T) +
                                                sizeof(FTW_PROFILE_PARAMS_T) + sizeof(FTW_FLASH_PARAMS_T));
	memcpy(mac,macAddr,6);
}

VOID
S2w_macAddrRTCSet(UINT8* mac)
{
    
	GSN_MAC_ADDR_T* macAddr = (GSN_MAC_ADDR_T*)(GSN_RTC_SRAM_BLOCK0_ADDR + sizeof(APP_RTC_SECNDRY_MEM_INFO_T) +
                                                sizeof(FTW_PROFILE_PARAMS_T) + sizeof(FTW_FLASH_PARAMS_T));
	memcpy(macAddr, mac,6);
}


void
AppS2wHal_RTCRead(void)
{
    FTW_PROFILE_PARAMS_T* param = S2w_ProfileParamInRTCPtrGet();
    memcpy(&profile_params,param,sizeof(FTW_PROFILE_PARAMS_T));
    s2wFlashParams = S2w_FlashParamInRTCPtrGet();
    
}
