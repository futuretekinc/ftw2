/*******************************************************************************
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
* $RCSfile: app_mcu_def.h,v
*/

#ifndef APP_MCU_DEF_H_
#define APP_MCU_DEF_H_

#define APP_MCU_PROFILE_NAME "mcu"
#define APP_MCU_PROFILE_DESC "Generic MCU Profile"
#define APP_MCU_PROFILE_URI "/gainspan/profile/mcu"
#ifdef S2W_WEB_SERVER
GSN_HTTPD_STATUS_T 
McuHttpCb(ttHttpdUserEvent event,const char * uri,ttHttpdUserConHandle conHandle);
PUBLIC VOID
AppMcu_RespTimeoutCb(VOID * context,GSN_SOFT_TMR_HANDLE_T timerHandle);

GSN_HTTPD_STATUS_T
App_McuHttpApiInit();

VOID
AppS2w_GslinkDeInit(UINT8 cid,UINT8 invalidateFlag);

UINT8
AppS2w_GslinkInit(UINT8 cid);

VOID
App_McuHttpApiDeInit();
PUBLIC UINT8
AppS2w_HttpdSetTimeOut(UINT8 cid,UINT32 timeOut);
#endif
#endif /* APP_MCU_DEF_H_ */
