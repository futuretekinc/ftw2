/******************************************************************************
 *
 *               COPYRIGHT (c) 2006-2010 GainSpan Corporation
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
 * $RCSfile: gsn_mac_utils.h,v $
 *
 * Project: GSN APP Software
 *
 * Description:
 *      Mac header structure
 *
 ****************************************************************************************
 */


UINT16 
GsnMacUtil_ExtractBeaconPeriod(GSN_MAC_FRAME_T* FramePtr);
UINT16 
GsnMacUtil_ExtractCapaInfo(GSN_MAC_FRAME_T* FramePtr);
void 
GsnMacUtil_ExtractSsid(GSN_MAC_FRAME_T* FramePtr, UINT16 MaxFrameSize, GSN_MAC_SSID_T* MacSsidPtr);
void 
GsnMacUtil_ExtractTimeStamp(GSN_MAC_FRAME_T* FramePtr, ULONG64* TimeStampPtr);
void 
GsnMacUtil_ExtractRateSet( GSN_MAC_FRAME_T* framePtr, UINT16 maxFrameSize, 
    GSN_MAC_RATESET_T* macRateSetPtr,  UINT8 offset );
UINT8 
GsnMacUtil_ExtractChannel(GSN_MAC_FRAME_T* FramePtr, UINT16 MaxFrameSize);
UINT8*
GsnMacUtil_ExtractFromBeacon(GSN_MAC_FRAME_T* FramePtr, UINT8 ElmtId, UINT16 MaxFrameSize, UINT16 *FrameSizePtr);
UINT8* 
GsnMacUtil_Extract(GSN_MAC_FRAME_T* FramePtr, UINT8 ElmtId, UINT16 MaxFrameSize,
                        UINT16 *FrameSizePtr, UINT16 offset);
UINT8* 
GsnMacUtil_ExtractOUI(GSN_MAC_FRAME_T* FramePtr, UINT8 OUI1, UINT8 OUI2, UINT8 OUI3, UINT8 OUIType,
                        UINT8 OUISubType, UINT16 MaxFrameSize, UINT16 *FrameSizePtr, UINT16 Offset);
UINT8* 
GsnMacUtil_ExtractOUIWifi(GSN_MAC_FRAME_T* FramePtr, UINT8 OUIType, UINT8 OUISubType,
                        UINT16 MaxFrameSize, UINT16 *FrameSizePtr, UINT16 Offset);

void 
GsnMacUtil_RateOrdering(GSN_MAC_RATESET_T *RatePtr);
WLAN_BOOLEAN 
GsnMacUtil_AreBasicRatesMatching(GSN_MAC_RATESET_T *BssRatePtr,
                                     GSN_MAC_RATESET_T *StationRatePtr);
void 
GsnMacUtil_MergeBasicRates(GSN_MAC_RATESET_T *BssRatePtr,
                        GSN_MAC_RATESET_T *DesiredRatePtr,
                        GSN_MAC_RATESET_T *ResultRatePtr);
void 
GsnMacUtil_MergeRates(GSN_MAC_RATESET_T *BssRatePtr,
                    GSN_MAC_RATESET_T *DesiredRatePtr,
                    GSN_MAC_RATESET_T *ResultRatePtr);

UINT8 
GsnMacUtil_ExtractEncryptionStatus(GSN_MAC_FRAME_T* FramePtr, UINT16 MaxFrameSize, UINT16 Offset, UINT8* AuthModePtr);

UINT8 * 
GsnMacUtil_ExtractWpsAttributes( GSN_MAC_FRAME_T  *framePtr, 
                                UINT16        maxFrameSize, 
                                UINT16        offset,
                                GSN_MAC_WPS_IE_ATTR_T   *wpsAttr);

