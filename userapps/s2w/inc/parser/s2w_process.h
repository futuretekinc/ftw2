/******************************************************************************
*
*               COPYRIGHT (c) 2008-2010 GainSpan Corporation
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
* $RCSfile: s2w_process.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/
#ifndef S2W_PROCESS_H
#define S2W_PROCESS_H

/** @defgroup api API for Platform-Specific Functions */
/** @{ */

void s2w_init(void);
void s2w_process_serial_input(void);
void AppS2wProcess_StatusNotify(UINT8 status, UINT32 arg);
void AppS2wProcess_EventNotify(UINT8 flag);
void AppS2wProcess_DhcpFailNotify();

#ifdef S2W_SNTP
void AppS2wProcess_SntpDoneNotify();
void AppS2wProcess_SntpTimerNotify();
#endif

#ifdef GSN_P2P
void AppS2wProcess_P2pDevFoundNotify();
#endif

void AppS2wScanResult_Print(UINT8 *ssid, UINT8 ssid_len, UINT8 *bssid,
               UINT8 channel, UINT8 rssi, UINT8 adhoc);

//void AppS2wProcess_DefaulConfigtLoad(S2W_FLASH_PARAMS_T *params);

//extern S2W_PROFILE_T s2wCurrent;

PUBLIC UINT8
AppS2w_CidValidate(UINT8 ch);

PUBLIC INT32
S2w_Printf(const char *format, ...);
PUBLIC INT32
S2w_Printf1(const char *format, ...);

PUBLIC VOID
AppS2wProcess_DefaulConfigtLoad(S2W_FLASH_PARAMS_T *params);

PUBLIC VOID
AppS2w_Init(VOID);

PUBLIC VOID
AppS2wProcess_SerialInput(VOID);

VOID AppS2w_SetWlanDfltParams(UINT8 profileNum);


PUBLIC VOID
AppS2w_SetTime(ULONG64 iptime);
PUBLIC ULONG64
AppS2w_GetTime();
VOID
AppS2wRoam_SatusNotify(UINT32 statusMsg,UINT32 asycStatusMsg);
/** @} */
#endif
