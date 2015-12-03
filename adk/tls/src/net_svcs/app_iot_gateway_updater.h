/*******************************************************************************
*
*               COPYRIGHT (c) 2013-2014 GainSpan Corporation
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
* $RCSfile: app_low_power_proxy.h,v
*
*  Created on: 04-Oct-2013
*      Author: Dhanya Lakshmi
*/

#ifndef APP_LOWER_POWER_PROXY_H_
#define APP_LOWER_POWER_PROXY_H_

#include "gsn_httpc.h"

#define RETRIAL_COUNT 5
#define BUF_SIZE 1024
// decide on the thread priority
#define PROXY_UPDATER_THREAD_PRIORITY 12

typedef struct LOW_POWER_PROXY_DATA
{
	GSN_HTTPC_CONF_INFO_T httpConfInfo;
	INT8 HttpRxBuf[BUF_SIZE];
	INT8 HttpRequestBuf[BUF_SIZE];
	INT8 readingPath[256];
	INT8 configPath[256];
	void *httpConn;
	BOOL bConnReady;
	UINT8 IPAddress[4];
	UINT16 portNo;
	UINT32 updateInterval;
	INT8 updtInterval[256];
	INT8 IpAddressString[20];
	INT8 devicePath[256];
	BOOL continueRunning;
	BOOL postingFirstTime;
	GSN_OSAL_SEM_T appTlsServiceDiscoverWaitSem;
}PROXY_UPDATER_DATA;

VOID App_IotGatewayUpdaterStart(APP_MAIN_CTX_T *pAppCtx);

PRIVATE GSN_STATUS
APP_LowPProxyUpdateReadings(APP_MAIN_CTX_T *pAppCtx, BOOL bSSL);

PRIVATE GSN_STATUS
APP_LowPProxyUpdateReadingsWithCoap(APP_MAIN_CTX_T *pAppCtx);



#endif /* APP_LOWER_POWER_PROXY_H_ */
