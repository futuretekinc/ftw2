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
* $RCSfile: gsn_mdns_fpt.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/
#ifndef _GSN_MDNS_FPT_H_
#define _GSN_MDNS_FPT_H_

typedef GSN_STATUS
(* GsnMdns_Init_FP_T)(GSN_MDNS_T *pMdns, GSN_MDNS_INIT_PARAM_T *pParam);
extern _RPST_ GsnMdns_Init_FP_T GsnMdns_Init_FP;

typedef GSN_STATUS
(* GsnMdns_ServiceRegister_FP_T)(GSN_MDNS_T *pMdns,       GSN_MDNS_SRVCREG_PARAM_T *pParam);
extern _RPST_ GsnMdns_ServiceRegister_FP_T GsnMdns_ServiceRegister_FP;

typedef GSN_STATUS
(* GsnMdns_HostnameRegister_FP_T)(GSN_MDNS_T *pMdns, GSN_MDNS_HNREG_PARAM_T *pParam);
extern _RPST_ GsnMdns_HostnameRegister_FP_T GsnMdns_HostnameRegister_FP;

typedef UINT32
(* GsnMdns_Announce_FP_T)(GSN_MDNS_T *pMdns, GSN_MDNS_ANNOUNCE_PARAM_T *pParam);
extern _RPST_ GsnMdns_Announce_FP_T GsnMdns_Announce_FP;

typedef GSN_STATUS
(* GsnMdns_HostnameDeregister_FP_T)(GSN_MDNS_T * pMdns, GSN_MDNS_HNDEREG_PAARAM_T *pParam);
extern _RPST_ GsnMdns_HostnameDeregister_FP_T GsnMdns_HostnameDeregister_FP;

typedef GSN_STATUS
(* GsnMdns_ServiceDeRegister_FP_T)(GSN_MDNS_T * pMdns, GSN_MDNS_SRVCDEREG_PARAM_T *pParam);
extern _RPST_ GsnMdns_ServiceDeRegister_FP_T GsnMdns_ServiceDeRegister_FP;

typedef GSN_STATUS
(* GsnMdns_ServiceDiscover_FP_T)(GSN_MDNS_T *pMdns, GSN_MDNS_SRVCDISCVR_PARAM_T *pParam);
extern _RPST_ GsnMdns_ServiceDiscover_FP_T GsnMdns_ServiceDiscover_FP;

typedef VOID 
(* GsnMdns_Execute_FP_T) (GSN_MDNS_T *pMdns);
extern _RPST_ GsnMdns_Execute_FP_T GsnMdns_Execute_FP;

typedef VOID
(* GsnMdns_DeInit_FP_T)(GSN_MDNS_T *pMdns);
extern _RPST_ GsnMdns_DeInit_FP_T GsnMdns_DeInit_FP;

#endif /*_GSN_MDNS_FPT_H_*/
