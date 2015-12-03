/******************************************************************************
 *
 *               COPYRIGHT (c) 2009-2010 GainSpan Corporation
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
 * $RCSfile: gsn_mac_utils_fpt.h,v $
 *
 * Project: GSN APP Software
 *
 * Description:
 *      mac common utility function to read frame
 ****************************************************************************************
 */
#ifndef _GSN_MAC_UTILS_FPT_H_
#define _GSN_MAC_UTILS_FPT_H_

typedef void
(* GsnMacUtil_ExtractSsid_FP_T)( GSN_MAC_FRAME_T* framePtr, UINT16 maxFrameSize,
										GSN_MAC_SSID_T* macSsidPtr );
extern _RPST_  GsnMacUtil_ExtractSsid_FP_T GsnMacUtil_ExtractSsid_FP;

typedef void
(* GsnMacUtil_ExtractTimeStamp_FP_T)( GSN_MAC_FRAME_T* framePtr, ULONG64* timeStampPtr);
extern _RPST_  GsnMacUtil_ExtractTimeStamp_FP_T GsnMacUtil_ExtractTimeStamp_FP;

typedef UINT8
(* GsnMacUtil_ExtractChannel_FP_T)( GSN_MAC_FRAME_T* framePtr, UINT16 maxFrameSize );;
extern _RPST_  GsnMacUtil_ExtractChannel_FP_T GsnMacUtil_ExtractChannel_FP;

typedef void
(* GsnMacUtil_ExtractRateSet_FP_T)( GSN_MAC_FRAME_T* framePtr, UINT16 maxFrameSize,
											GSN_MAC_RATESET_T* macRateSetPtr,  UINT8 offset );
extern _RPST_  GsnMacUtil_ExtractRateSet_FP_T GsnMacUtil_ExtractRateSet_FP;

typedef UINT8*
(* GsnMacUtil_Extract_FP_T)( GSN_MAC_FRAME_T* framePtr, UINT8 elmtId, UINT16 maxFrameSize,
									UINT16 *frameSizePtr, UINT16 i);
extern _RPST_  GsnMacUtil_Extract_FP_T GsnMacUtil_Extract_FP;

typedef UINT8*
(* GsnMacUtil_ExtractOUI_FP_T)( GSN_MAC_FRAME_T* framePtr, UINT8 OUI1, UINT8 OUI2, UINT8 OUI3,
										UINT8 OUIType, UINT8 OUISubType, UINT16 maxFrameSize,
										UINT16 *frameSizePtr, UINT16 i );
extern _RPST_  GsnMacUtil_ExtractOUI_FP_T GsnMacUtil_ExtractOUI_FP;


typedef UINT8*
(* GsnMacUtil_ExtractOUIWifi_FP_T)(GSN_MAC_FRAME_T* framePtr, UINT8 OUIType, UINT8 OUISubType,
											UINT16 maxFrameSize, UINT16 *frameSizePtr, UINT16 i);

extern _RPST_  GsnMacUtil_ExtractOUIWifi_FP_T GsnMacUtil_ExtractOUIWifi_FP;

typedef void
(* GsnMacUtil_RateOrdering_FP_T)( GSN_MAC_RATESET_T *ratePtr);
extern _RPST_  GsnMacUtil_RateOrdering_FP_T GsnMacUtil_RateOrdering_FP;

typedef WLAN_BOOLEAN
(* GsnMacUtil_AreBasicRatesMatching_FP_T)( GSN_MAC_RATESET_T *bssRatePtr,
													GSN_MAC_RATESET_T *stationRatePtr);
extern _RPST_  GsnMacUtil_AreBasicRatesMatching_FP_T GsnMacUtil_AreBasicRatesMatching_FP;

typedef void
(* GsnMacUtil_MergeBasicRates_FP_T)( GSN_MAC_RATESET_T *bssRatePtr,
											GSN_MAC_RATESET_T *desiredRatePtr,
											GSN_MAC_RATESET_T *resultRatePtr );
extern _RPST_  GsnMacUtil_MergeBasicRates_FP_T GsnMacUtil_MergeBasicRates_FP;

typedef void
(* GsnMacUtil_MergeRates_FP_T)( GSN_MAC_RATESET_T *bssRatePtr, GSN_MAC_RATESET_T *desiredRatePtr,
										GSN_MAC_RATESET_T *resultRatePtr);
extern _RPST_  GsnMacUtil_MergeRates_FP_T GsnMacUtil_MergeRates_FP;

typedef UINT8
(* GsnMacUtil_ExtractEncryptionStatus_FP_T)( GSN_MAC_FRAME_T  *framePtr,
														UINT16		  maxFrameSize,
														UINT16		  offset,
														UINT8		  *authModePtr);
extern _RPST_  GsnMacUtil_ExtractEncryptionStatus_FP_T GsnMacUtil_ExtractEncryptionStatus_FP;

typedef UINT8
(* GsnMacUtil_GetRsnCipherSuit_FP_T)( UINT8 *rsnPtr,
												UINT8         *authModePtr,
												UINT8         *groupCipher);
extern _RPST_  GsnMacUtil_GetRsnCipherSuit_FP_T GsnMacUtil_GetRsnCipherSuit_FP;

typedef UINT8
(* GsnMacUtil_ExtractRsnEncryptionStatus_FP_T)( GSN_MAC_FRAME_T  *framePtr,
															UINT16        maxFrameSize,
															UINT16        offset,
															UINT8         *authModePtr,
															UINT8         *groupCipher);
extern _RPST_  GsnMacUtil_ExtractRsnEncryptionStatus_FP_T GsnMacUtil_ExtractRsnEncryptionStatus_FP;

typedef UINT8
(* GsnMacUtil_GetWpaCipherSuit_FP_T)( UINT8 *wpaPtr,
												UINT8         *authModePtr,
												UINT8         *groupCipher);
extern _RPST_  GsnMacUtil_GetWpaCipherSuit_FP_T GsnMacUtil_GetWpaCipherSuit_FP;

typedef UINT8
(* GsnMacUtil_ExtractWpaEncryptionStatus_FP_T)( GSN_MAC_FRAME_T  *framePtr,
															UINT16        maxFrameSize,
															UINT16        offset,
															UINT8         *authModePtr,
															UINT8         *groupCipher);

extern _RPST_  GsnMacUtil_ExtractWpaEncryptionStatus_FP_T GsnMacUtil_ExtractWpaEncryptionStatus_FP;

typedef UINT8 *
(* GsnMacUtil_ExtractWpsAttributes_FP_T)( GSN_MAC_FRAME_T  *framePtr,
													UINT16		  maxFrameSize,
													UINT16		  offset,
													GSN_MAC_WPS_IE_ATTR_T	*wpsAttr);
extern _RPST_  GsnMacUtil_ExtractWpsAttributes_FP_T GsnMacUtil_ExtractWpsAttributes_FP;

typedef VOID
(* GsnMacUtil_WpsParseAttr_FP_T)(UINT8 *attrStart, UINT8 *attrEnd,
										UINT8 *attr, UINT16 attrType);
extern _RPST_  GsnMacUtil_WpsParseAttr_FP_T GsnMacUtil_WpsParseAttr_FP;

#endif