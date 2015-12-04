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


extern APP_MAIN_CTX_T *s2wappMainTaskCtxt;
extern PUBLIC UINT8 *pS2wHttpdTaskStack;


VOID FTW_NET_HTTPD_stop(void)
{
    /*De init Gslink URI */
#ifdef S2W_WEB_SERVER 
    
    if(s2wappMainTaskCtxt->webServerStatus == STOP)
    {
        AppS2w_WebServerStop();
    }
    
#endif
    /*De init Provisioning URI URI */
#ifdef S2W_WEB_PROV
    if(s2wappMainTaskCtxt->webProvStatus == STOP)
    {
        S2wWebProv_WebProvStop();
    }
#endif
    if(
#ifdef S2W_WEB_SERVER 
       
       (s2wappMainTaskCtxt->webServerStatus == IDLE) &&
#endif
           
#ifdef S2W_WEB_PROV
           (s2wappMainTaskCtxt->webProvStatus == IDLE) &&
#endif
               (TRUE == GsnHttpd_IsRunning()))
    {   //S_Printf("\r\n GsnHttpd_Stop" );
        GsnHttpd_Stop();
        //w_Printf("\r\n GsnHttpd_Stop1" );
        S2wApp_WebserverStack_Free(pS2wHttpdTaskStack);
        pS2wHttpdTaskStack = NULL;
    }
    
    GsnOsal_SemRelease(&s2wappMainTaskCtxt->webServerSync);
}

