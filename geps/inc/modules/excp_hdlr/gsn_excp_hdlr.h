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
* $RCSfile: gsn_excp_hdlr.h,v $
*
* Description : This file contains public definitions for WDD. WDD( Wireless Device Driver ) provides APIs for 
* the wireless drivers. These APIs are scan request, connect request,  disconnect request, data request. 
* WDD generates events related to these request. If application has registered its callback function, 
* WDD calls it whenever these events happens.
*******************************************************************************/
#ifndef _GSN_EXCP_HDLR_H_
#define _GSN_EXCP_HDLR_H_
typedef struct GSN_EXCP_INFO
{
	UINT32 R0;
	UINT32 R1;
	UINT32 R2;
	UINT32 R3;
	UINT32 R12;
	UINT32 LR;
	UINT32 PC;
	UINT32 PSR;	

	UINT32 CFSR; /* Configurable Fault Status register*/
	UINT32 HFSR; /* Hard Fault Status register */
	UINT32 DFSR; /* Debug Fault Status register*/
	UINT32 AFSR; /* Auxiliary Fault Status register*/

	UINT8 MFSR;
	UINT8 BFSR;
	UINT16 UFSR;
	UINT32 MMFAR; /* MemManage Fault Address register*/
	UINT32 BFAR; /* Bus Fault Address register*/
}GSN_EXCP_INFO_T;

INLINE GSN_EXCP_INFO_T *
GSN_EXCP_INFO_PTR_GET(VOID)
{	
	return (GSN_EXCP_INFO_T *)GSN_RESET_INFO_LOCATION_GET();
}

VOID
GsnExcpHdlr_Init(VOID);

#endif
