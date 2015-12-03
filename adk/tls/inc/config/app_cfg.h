/******************************************************************************
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
* $RCSfile: app_cfg.h,v $
*
* Description : This file contains public definitions for app configuration 
*****************************************************************************/
#ifndef _APP_CFG_H_
#define _APP_CFG_H_

#include "gsn_sys_config.h"
#include "app_defs.h"

typedef GSN_SYS_CONFIG_T APP_CONFIG_T;

typedef GSN_SYS_CONFIG_CLIENT_T APP_CLIENT_CONFIG_T;

typedef GSN_SYS_CONFIG_AP_T	APP_AP_CONFIG_T;
#define APP_WPS_TYPE_PB 1
#define APP_WPS_TYPE_PIN 2

VOID 
AppConfig_DefaultInit(APP_CONFIG_T * pConfig);

GSN_STATUS 
AppConfig_Load(APP_CONFIG_T *pConfig);

GSN_STATUS 
AppConfig_Save(APP_CONFIG_T *pConfig);

inline const char*
AppConfig_GetAppNameAndVersion()
{
    return APP_NAME_AND_VERSION;
}

inline const char*
AppConfig_GetVersion()
{
    return APP_VERSION;
}

APP_CONFIG_T*
AppConfig_RTCPtrGet();


#endif

