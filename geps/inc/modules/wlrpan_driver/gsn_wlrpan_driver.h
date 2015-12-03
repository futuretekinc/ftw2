/******************************************************************************
*
*               COPYRIGHT (c) 2013 GainSpan Corporation
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
* $RCSfile: gsn_wlrpan_driver.h,v $
*
* Description : This file contains function and structure declaration for 
* WLRPAN Driver.
*****************************************************************************/
#ifndef _GSN_WLRPAN_DRIVER_H_
#define _GSN_WLRPAN_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************
* File inclusion
******************************************************************************/

/**
 *****************************************************************************
 * @file gsn_wlrpan_driver.h
 * @brief GSN WLARPN Driver public header.
 *    This file contains the public APIs and structures of WLARPAN Driver.
 *
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup syssvcdoc
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnWlrPAN
 * @brief 
 *
 *    
******************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/
#define GSN_WLRPAN_ED  0x00 /**< Function as end device */
#define GSN_WLRPAN_CRD 0x01 /**< Function as PAN coordinator */
#define GSN_WLRPAN_RT  0x10 /**< Function as router (coordinator) */

#define GSN_WLRPAN_ADDR_MODE_NONE  0x00/**< no address-addressing fields omitted */
#define GSN_WLRPAN_ADDR_MODE_SHORT 0x02/**< 16-bit short address.*/
#define GSN_WLRPAN_ADDR_MODE_EXTND 0x03/**< 64-bit extended address.*/

/**< For the below option data is not encrypted. Data authenticity is not 
    validated */
#define GSN_WLRPAN_SEC_LEVEL_NONE 
/**< For the below three option Data is not encrypted. Data authenticity is 
    validated. */
#define GSN_WLRPAN_SEC_LEVEL_M32  /**< MIC-32 */
#define GSN_WLRPAN_SEC_LEVEL_M64  /**< MIC-64 */
#define GSN_WLRPAN_SEC_LEVEL_M128 /**< MIC-128 */
/**< For the below option Data is encrypted. Data authenticity is not 
    validated */    
#define GSN_WLRPAN_SEC_LEVEL_E
/**< For the below three option Data is encrypted. Data authenticity is 
    validated */    
#define GSN_WLRPAN_SEC_LEVEL_EM32  /**< MIC-32 */
#define GSN_WLRPAN_SEC_LEVEL_EM64  /**< MIC-65 */
#define GSN_WLRPAN_SEC_LEVEL_EM128 /**< MIC-128 */
    
    
#define GSN_WLRPAN_TX_OPT_ACK      ( 1 << 0 )
#define GSN_WLRPAN_TX_OPT_GTC      ( 1 << 1 )
#define GSN_WLRPAN_TX_OPT_INDIRECT ( 1 << 2 )    
    
    
#define GSN_WLRPAN_ED_SCAN      0x00 /**< ED scan (optional for RFD). */
#define GSN_WLRPAN_ACTIVE_SCAN  0x01 /**< active scan (optional for RFD). */
#define GSN_WLRPAN_PASSIVE_SCAN 0x02 /**< passive scan. */
#define GSN_WLRPAN_ORPHAN_SCAN  0x03 /**< orphan scan. */
 
/* Offset of elements in Superframe Specification field */    
#define GSN_WLRPAN_SFP_BO_OFFSET             0 /**< Beacon Order */
#define GSN_WLRPAN_SFP_SO_OFFSET             4 /**< Superframe Order */
#define GSN_WLRPAN_SFP_FINAL_CAP_SLOT_OFFSET 8 /**< Final CAP Slot */
#define GSN_WLRPAN_SFP_BLE_OFFSET            12/**< Battery Life Extension (BLE)*/
#define GSN_WLRPAN_SFP_PC_OFFSET             14/**< PAN Coordinator*/
#define GSN_WLRPAN_SFP_AP_OFFSET             15/**< Association Permit*/
   
#define GSN_MAX_NUM_OF_SCAN_RESULT        50  


typedef struct GSN_WLRPAN_KEYID_LOOKUP_DESC
{
    UINT8 LookupData[9];
    UINT8 LookupDataSize;

}GSN_WLRPAN_KEYID_LOOKUP_DESC_T;

typedef struct GSN_WLRPAN_KEY_DEVICE_DESC
{
    UINT8 DeviceDescHandle;
    BOOL UniqueDevice;
    BOOL Blacklisted;
    
}GSN_WLRPAN_KEY_DEVICE_DESC_T;

typedef struct GSN_WLRPAN_KEY_USAGE_DESC
{
    UINT8 FrameType;
    UINT8 CmdFrmIdentifier;    
}GSN_WLRPAN_KEY_USAGE_DESC_T;

typedef struct GSN_WLRPAN_KEY_DESC
{
    GSN_WLRPAN_KEYID_LOOKUP_DESC_T* KeyIdLookupList;
    UINT8 KeyIdLookupListEntries;
    GSN_WLRPAN_KEY_DEVICE_DESC_T *KeyDeviceList;
    UINT8 KeyDeviceListEntries;
    GSN_WLRPAN_KEY_USAGE_DESC_T *KeyUsageList;
    UINT8 KeyUsageListEntries;
    UINT8 Key[16];    
}GSN_WLRPAN_KEY_DESC_T;

typedef struct GSN_WLRPAN_DEVICE_DESC
{
    UINT16 PANId;
    UINT16 ShortAddress;
    ULONG64 ExtAddress;
    UINT32 FrameCounter;
    BOOL Exempt;
    
}GSN_WLRPAN_DEVICE_DESC_T;

typedef struct GSN_WLRPAN_SECURITY_LEVEL_DESC
{
    UINT8 FrameType;
    UINT8 CmdFrmIdentifier;
    UINT8 SecIMinimum;
    BOOL DeviceOverrideSecIMinimum;
    
}GSN_WLRPAN_SECURITY_LEVEL_DESC_T;


/* Dont Change the sequence of the enum */
typedef enum GSN_WLP_PIB_ID
{
    macAckWaitDuration              = 0     , 
    macBeaconTxTime                 = 1     ,
    macCoordExtendedAddress         = 2     ,   
    macAssociationPermit            = 3     ,
    macCoordShortAddress            = 4     ,
    macMinBE                        = 5     ,
    macMaxBE                        = 6     ,
    macMaxCSMABackoffs              = 7     ,
    macMaxFrameRetries              = 8     ,
    macMinLIFSPeriod                = 9     ,
    macMinSIFSPeriod                = 10    ,
    macPANId                        = 11    ,
    macAutoRequest                  = 12    ,
    macShortAddress                 = 13    ,
    
    
    macBattLifeExt                  = 14    ,
    macBattLifeExtPeriods           = 15    ,
    macBeaconPayload                = 16    ,
    macBeaconPayloadLength          = 17    ,
    macBeaconOrder                  = 18    ,       
    macBSN                          = 19    ,
    macDSN                          = 20    ,
    macGTSPermit                    = 21    ,
    macPromiscuousMode              = 22    ,
    macRxOnWhenIdle                 = 23    ,
    macSuperframeOrder              = 24    ,
    macTransactionPersistenceTime   = 25    ,
    macAssociatedPANCoord           = 26    ,        
    macMaxFrameTotalWaitTime        = 27    ,    
    macResponseWaitTime             = 28    ,
    macSyncSymbolOffset             = 29    ,
    macTimestampSupported           = 30    ,
    macSecurityEnabled              = 31    ,
    macExtendedAddress              = 32    ,

	/**< Security Related */

    macKeyTable                     = 33    ,
    macKeyTableEntries              = 34    ,
    macDeviceTable                  = 35    ,
    macDeviceTableEntries           = 36    ,    
    macSecurityLevelTable           = 37    ,
    macSecurityLevelTableEntries    = 38    ,
    macFrameCounter                 = 39    ,
    macAutoReqSeurityLevel          = 40    ,
    macAutoReqKeyIdMode             = 41    ,
    macAutoReqKeySource             = 42    ,
    macAutoReqKeyIndex              = 43    ,
    macDefaultKeySource             = 44    ,
    macPANCoordExtendedAddress      = 45    ,
    macPANCoordShortAddress         = 46    ,

	/**< PHY related */
    
    phyCurrentChannel               = 47    ,
    phyChannelsSupported            = 48    ,
    phyTransmitPower                = 49    ,
    phyCCAMode                      = 50    ,
    phyCurrentPage                  = 51    ,
    phyMaxFrameDuration             = 52    ,
    phySHRDuration                  = 53    ,
    phySymbolsPerOctet              = 54	,

	/**< New SecI related */

	macKeyTableIndex				= 55	,
	macKeyIdLookupList				= 56	,
	macKeyIdLookupListEntries		= 57	,
	macKeyIdLookupListIndex			= 58	,
	macKeyDeviceList				= 59	,
	macKeyDeviceListEntries			= 60	,
	macKeyDeviceListIndex			= 61	,
	macKeyUsageList					= 62	,
	macKeyUsageListEntries			= 63	,
	macKeyUsageListIndex			= 64	,
	macKey							= 65
    
}GSN_WLP_PIB_ID_T;


/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Structure for WLRPAN Reset Confirmation Structure .
 *****************************************************************************/
typedef struct GSN_WLRPAN_RESET_CFM
{
    GSN_STATUS_T status;
}GSN_WLRPAN_RESET_CFM_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Structure for WLRPAN Security information .
 *****************************************************************************/
typedef struct GSN_WLRPAN_SEC_I
{
    UINT8  SecILevel;
    UINT8  KeyIdMode;
    UINT8  KeyIndex;    
    UINT8  KeySource[8];  
}GSN_WLRPAN_SEC_I_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN address details. 
 *****************************************************************************/
typedef union GSN_WLRPAN_ADDR
{
    UINT16  ShortAddr;
    ULONG64 LongAddr;
    UINT8   addr[8];
    UINT32  addr32[2];
}GSN_WLRPAN_ADDR_T;

/**
 *******************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN data request structure. 
 ******************************************************************************/
typedef struct GSN_WLRPAN_DATA_REQ_STRUCT
{
    UINT8  SrcMode;
    UINT8  DstMode;    
    UINT16 DstPanId;
    GSN_WLRPAN_ADDR_T  DstAddr;
    UINT8  Msdu[128];
    UINT8  MsduLen;
    UINT8  MsduHandle;
    UINT8  TxOption;
    GSN_WLRPAN_SEC_I_T SecI;
}GSN_WLRPAN_DATA_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN data confirmation structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_DATA_CFM
{
    UINT8 MsduHandle;
    GSN_STATUS_T Status;
    UINT8 Timestamp;
}GSN_WLRPAN_DATA_CFM_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN data indication structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_DATA_IND
{
    UINT8  SrcMode;
    UINT8  DstMode;
    UINT8  LQI;
    UINT8  DSN;
    UINT16 SrcPanId;
    UINT16 DstPanId;

    UINT32 Timestamp;
    GSN_WLRPAN_ADDR_T  SrcAddr;    
    GSN_WLRPAN_ADDR_T  DstAddr;    
    UINT8  MsduLength;    
    UINT8  Msdu[128];       
    GSN_WLRPAN_SEC_I_T SecI;
}GSN_WLRPAN_DATA_IND_T;



/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN data purge request structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_PURGE_REQ
{
    UINT8  MsduHandle;
}GSN_WLRPAN_PURGE_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN data purge confirmation structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_PURGE_CFM
{
    UINT8  MsduHandle;
    GSN_STATUS_T Status;
}GSN_WLRPAN_PURGE_CFM_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN start request structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_START_REQ
{
    UINT16 PANId;
    UINT8 LogicalChannel;
    UINT8 ChannelPage;
    UINT32 StartTime;
    UINT8 BeaconOrder;
    UINT8 SuperframeOrder;
    UINT8 PANCoordinator;
    UINT8 BatteryLifeExtension;
    UINT8 CoordRealignment;
    GSN_WLRPAN_SEC_I_T CoordRealignSecI;
    GSN_WLRPAN_SEC_I_T BeaconSecI;
}GSN_WLRPAN_START_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN start confirmation structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_START_CFM
{
    GSN_STATUS_T  Status;
}GSN_WLRPAN_START_CFM_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN associate request structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_ASSOCIATE_REQ
{
    UINT8 LogicalChannel;
    UINT8 ChannelPage;
    UINT8 CoordAddrMode;
    UINT16 CoordPANId;
    GSN_WLRPAN_ADDR_T CoordAddress;
    UINT8 CapabilityInformation;
    GSN_WLRPAN_SEC_I_T SecI;
}GSN_WLRPAN_ASSOCIATE_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN associate indication structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_ASSOCIATE_IND
{
    GSN_WLRPAN_ADDR_T DeviceAddress;
    UINT8 CapabilityInformation;
    GSN_WLRPAN_SEC_I_T SecI;
}GSN_WLRPAN_ASSOCIATE_IND_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN associate response structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_ASSOCIATE_RSP
{
    GSN_WLRPAN_ADDR_T DeviceAddress;
    UINT16 AssocShortAddress;
    GSN_STATUS_T  Status;
    GSN_WLRPAN_SEC_I_T SecI;
}GSN_WLRPAN_ASSOCIATE_RSP_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Associate confirmation structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_ASSOCIATE_CFM
{
    UINT16 AssocShortAddress;
    GSN_STATUS_T  Status;
    GSN_WLRPAN_SEC_I_T SecI;
}GSN_WLRPAN_ASSOCIATE_CFM_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN scan request structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_SCAN_REQ
{
    UINT8 ScanType;
    UINT32 ScanChannels;
    UINT8 ScanDuration;
    UINT8 ChannelPage;
    GSN_WLRPAN_SEC_I_T SecI;
}GSN_WLRPAN_SCAN_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN PAN descripter structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_PAN_DESC
{
    UINT16 CoordPANId;
    UINT16 SuperframeSpec;
    UINT8  CoordAddrMode;    
    UINT8  LogicalChannel;
    UINT8  ChannelPage;    
    UINT8  GTSPermit;
    UINT8  LinkQuality;    
    GSN_WLRPAN_ADDR_T  CoordAddress;
    
}GSN_WLRPAN_PAN_DESC_T;
typedef struct GSN_WLRPAN_SUPFRM_SPEC
{
	UINT8 BO			:4;
	UINT8 SO			:4;
	UINT8 FinalCAPSlot	:4;
	UINT8 BLE			:1;
	UINT8 Reserve		:1;
	UINT8 PANCRD		:1;
	UINT8 AssocPermit	:1;
}GSN_WLRPAN_SUPFRM_SPEC_T;
/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Beacon Notification structure. 
 *****************************************************************************/
typedef struct GSN_WLP_BEACON_NOTIFY
{
	UINT8 BSN;
	GSN_WLRPAN_PAN_DESC_T PANDescriptor;
	UINT8 PendAddrSpec;
	GSN_WLRPAN_ADDR_T AddrList[8];
	UINT8 sduLength;
	UINT8 sdu[128];

}GSN_WLP_BEACON_NOTIFY_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN scan confirmation structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_SCAN_CFM
{
    GSN_STATUS_T Status;
    UINT8 ScanType;
    UINT8 ChannelPage;
    UINT32 UnscannedChannels;
    UINT8 ResultListSize;
    union        
    {
        UINT8 EnergyDetectList[1];
        GSN_WLRPAN_PAN_DESC_T PANDescriptorList[1];
    }Result;
}GSN_WLRPAN_SCAN_CFM_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN get request structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_GET_REQ
{
    UINT16 Attribute;
    UINT16 AttributeIdx;    
}GSN_WLRPAN_GET_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN get confirmation structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_GET_CFM
{
    GSN_STATUS_T status;
    UINT16 Attribute;
    UINT16 AttributeIdx;    
    UINT8  Value[75];
}GSN_WLRPAN_GET_CFM_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN set request structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_SET_REQ
{
    UINT16 Attribute;
    UINT16 AttributeIdx; 
	UINT8 AttributeLength;
    UINT8  Value[75];
}GSN_WLRPAN_SET_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN set confirmation structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_SET_CFM
{
    GSN_STATUS_T status;
    UINT16 Attribute;
    UINT16 AttributeIdx;
}GSN_WLRPAN_SET_CFM_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN PS POLL request structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_POLL_REQ
{
    UINT8 CoordAddrMode;
    UINT16 CoordPANId;    
    GSN_WLRPAN_ADDR_T  CoordAddress;
    GSN_WLRPAN_SEC_I_T SecI;
}GSN_WLRPAN_POLL_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN PS POLL Confirmation structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_POLL_CFM
{
    GSN_STATUS_T status;
}GSN_WLRPAN_POLL_CFM_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrPAN
 * @brief structure declaration for RX Enable structure.   
 *****************************************************************************/
 
 typedef struct GSN_WLRPAN_RXENABLE_REQ
{
	UINT32 RxOnTime;
	UINT32 RxOnDuration;
	BOOL DeferPermit;
	
}GSN_WLRPAN_RXENABLE_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrPAN
 * @brief structure declaration for RX Enable Confirmation structure.   
 *****************************************************************************/
typedef struct GSN_WLRPAN_RXENABLE_CFM
{
	GSN_STATUS_T status;

}GSN_WLRPAN_RXENABLE_CFM_T;    


/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Orphan Response structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_ORPHAN_RSP
{
	ULONG64 OrphanAddr;
	UINT16 ShortAddr;
	BOOL AssociatedMember;
    GSN_WLRPAN_SEC_I_T SecI;

}GSN_WLRPAN_ORPHAN_RSP_T;   

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN GTS Characteristics structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_GTS_CHAR
{
    UINT8 Length   : 4;
    UINT8 Dir      : 1;
    UINT8 CharType : 1;
    UINT8 Res      : 2;
}GSN_WLRPAN_GTS_CHAR_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN GTS Request structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_GTS_REQ
{
    GSN_WLRPAN_GTS_CHAR_T Char;
    GSN_WLRPAN_SEC_I_T SecI;

}GSN_WLRPAN_GTS_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN GTS Confirm structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_GTS_CFM
{
    GSN_WLRPAN_GTS_CHAR_T Char;
    GSN_STATUS_T  Status;
}GSN_WLRPAN_GTS_CFM_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN GTS Indication structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_GTS_IND
{
    UINT16 DevAddr;
    UINT8  Char;
    GSN_WLRPAN_SEC_I_T SecI;
}GSN_WLRPAN_GTS_IND_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Sync Request structure. 
 *****************************************************************************/
     
typedef struct GSN_WLRPAN_SYNC_REQ
{
    UINT8 LogicalChannel;
    UINT8 ChannelPage;
    BOOL TrackBeacon;

}GSN_WLRPAN_SYNC_REQ_T ;
/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Disassociation request structure. 
 *****************************************************************************/
typedef struct GSN_WLP_DISASSOCIATE_REQ
{
    UINT8 DeviceAddrMode;
    UINT16 DevicePANId;
    GSN_WLRPAN_ADDR_T DeviceAddress;
    UINT8 DisAssocReason;
    UINT8 TxIndirect;
    GSN_WLRPAN_SEC_I_T SecI;
}GSN_WLP_DISASSOCIATE_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Disassociation Indication structure. 
 *****************************************************************************/
typedef struct GSN_WLP_DISASSOCIATE_IND
{
    ULONG64 DeviceAddr;
    UINT8 DisAssocReason;
    GSN_WLRPAN_SEC_I_T SecI;  
}GSN_WLP_DISASSOCIATE_IND_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Orphan Indication structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_ORPHAN_IND
{
    ULONG64 OrphanAddr;
    GSN_WLRPAN_SEC_I_T SecI;
}GSN_WLRPAN_ORPHAN_IND_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Disassociation confirmation structure. 
 *****************************************************************************/
typedef struct GSN_WLP_DISASSOCIATE_CFM
{
    GSN_STATUS_T  Status;
    UINT8 DeviceAddrMode;
    UINT16 DevicePANId;
    GSN_WLRPAN_ADDR_T DeviceAddr;    
}GSN_WLP_DISASSOCIATE_CFM_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Synchronisation Loss Indication structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_SYNCLOSS_IND
{
	GSN_STATUS_T LossReason;
	UINT16 PANId;
	UINT8 LogicalChannel;
	UINT8 ChannelPage;
	GSN_WLRPAN_SEC_I_T SecI;

}GSN_WLRPAN_SYNCLOSS_IND_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Communication Status Indication structure. 
 *****************************************************************************/
typedef struct GSN_WLRPAN_COMM_STATUS_IND
{
	
	UINT8  SrcMode;
    UINT8  DstMode;
	UINT16 PANId;
	GSN_STATUS_T status;
	GSN_WLRPAN_ADDR_T  SrcAddr;    
    GSN_WLRPAN_ADDR_T  DstAddr;    
	GSN_WLRPAN_SEC_I_T SecI;

}GSN_WLRPAN_COMM_STATUS_IND_T;
    
    
typedef struct GSN_WLP_TMR_REQ
{
    UINT32 NumOfSymbol;
    UINT8 IsPeriodic;    
}GSN_WLP_TMR_REQ_T;

typedef struct GSN_WLP_TMR_CFM
{
    GSN_STATUS_T status;
    UINT8 tmrNum;    
}GSN_WLP_TMR_CFM_T;

typedef struct GSN_WLP_TMR_IND
{
    GSN_STATUS_T status;
    UINT8 tmrNum;    
}GSN_WLP_TMR_IND_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Data Indication CB. 
 *****************************************************************************/
typedef GSN_STATUS (* GSN_WLRPAN_APP_CB_T )
    ( VOID* ctx, UINT32 magId, UINT16 msgLen, VOID *pMsg );

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Management message Ids. 
 *****************************************************************************/
typedef enum GSN_WLRPAN_MGMT_MSG_ID
{
    /**< Primitive received from higher layer */
    GSN_WLRPAN_MGMT_ASSOCIATE_REQ,
    GSN_WLRPAN_MGMT_ASSOCIATE_RSP,    
    GSN_WLRPAN_MGMT_DISASSOCIATE_REQ,        
    GSN_WLRPAN_MGMT_GET_REQ,    
    GSN_WLRPAN_MGMT_GTS_REQ,           
    GSN_WLRPAN_MGMT_ORPHAN_RSP,    
    GSN_WLRPAN_MGMT_RESET_REQ,    
    GSN_WLRPAN_MGMT_RX_ENABLE_REQ,    
    GSN_WLRPAN_MGMT_SCAN_REQ,    
    GSN_WLRPAN_MGMT_SET_REQ,    
    GSN_WLRPAN_MGMT_START_REQ,       
    GSN_WLRPAN_MGMT_SYNC_REQ,    
    GSN_WLRPAN_MGMT_POLL_REQ,
    GSN_WLRPAN_MGMT_MODE_SET_REQ,
    GSN_WLRPAN_MGMT_TMR_REQ,
    GSN_WLRPAN_MGMT_GENERIC_REQ,


    /**< Primitive sent to higher layer */   
    GSN_WLRPAN_MGMT_ASSOCIATE_CFM,
    GSN_WLRPAN_MGMT_ASSOCIATE_IND,
    GSN_WLRPAN_MGMT_DISASSOCIATE_CFM,
    GSN_WLRPAN_MGMT_DISASSOCIATE_IND,
    GSN_WLRPAN_MGMT_BEACON_NOTIFY_IND,
    GSN_WLRPAN_MGMT_GET_CFM,
    GSN_WLRPAN_MGMT_GTS_CFM,
    GSN_WLRPAN_MGMT_GTS_IND,    
    GSN_WLRPAN_MGMT_ORPHAN_IND,
    GSN_WLRPAN_MGMT_RESET_CFM,
    GSN_WLRPAN_MGMT_RX_ENABLE_CFM,
    GSN_WLRPAN_MGMT_SCAN_CFM,
    GSN_WLRPAN_MGMT_COMM_STATUS_IND,
    GSN_WLRPAN_MGMT_SET_CFM,
    GSN_WLRPAN_MGMT_START_CFM, 
    GSN_WLRPAN_MGMT_SYNC_LOSS_IND,
    GSN_WLRPAN_MGMT_POLL_CFM,
    GSN_WLRPAN_MGMT_TMR_CFM,
    GSN_WLRPAN_MGMT_TMR_IND,
    GSN_WLRPAN_MGMT_GEN_CFM,
    GSN_WLRPAN_MGMT_GEN_IND    
}GSN_WLRPAN_MGMT_MSG_ID_T;

/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Data message ID. 
 *****************************************************************************/
typedef enum GSN_WLRPAN_DATA_MSG_ID
{
    /**< Primitive received from higher layer */
    GSN_WLRPAN_DATA_REQ,    
    GSN_WLRPAN_DATA_PURGE_REQ,   
    GSN_WLRPAN_DATA_6LOWPAN_REQ,    

    /**< Primitive sent to higher layer */ 
    GSN_WLRPAN_DATA_CFM,
    GSN_WLRPAN_DATA_IND,
    GSN_WLRPAN_DATA_PURGE_CFM,
    GSN_WLRPAN_DATA_6LOWPAN_CFM,
    GSN_WLRPAN_DATA_6LOWPAN_IND
}GSN_WLRPAN_DATA_MSG_ID_T;

typedef struct GSN_WLRPAN_MGMT_CB_TABLE
{
    GSN_WLRPAN_APP_CB_T  assocCfm;
    GSN_WLRPAN_APP_CB_T  assocInd;
    GSN_WLRPAN_APP_CB_T  disassocCfm;
    GSN_WLRPAN_APP_CB_T  disassocInd;
    GSN_WLRPAN_APP_CB_T  beaconNotifInd;
    GSN_WLRPAN_APP_CB_T  getCfm;
    GSN_WLRPAN_APP_CB_T  gtsCfm;
    GSN_WLRPAN_APP_CB_T  gtsInd; 
    GSN_WLRPAN_APP_CB_T  orphanInd;
    GSN_WLRPAN_APP_CB_T  resetCfm;
    GSN_WLRPAN_APP_CB_T  rxEnableCfm;
    GSN_WLRPAN_APP_CB_T  scanCfm;
    GSN_WLRPAN_APP_CB_T  commStatusInd;
    GSN_WLRPAN_APP_CB_T  setCfm;
    GSN_WLRPAN_APP_CB_T  startCfm; 
    GSN_WLRPAN_APP_CB_T  syncLossInd;
    GSN_WLRPAN_APP_CB_T  pollCfm; 
    GSN_WLRPAN_APP_CB_T  tmrCfm; 
    GSN_WLRPAN_APP_CB_T  tmrInd;
    GSN_WLRPAN_APP_CB_T  genCfm; 
    GSN_WLRPAN_APP_CB_T  genInd; 
}GSN_WLRPAN_MGMT_CB_TABLE_T;

typedef struct GSN_WLRPAN_DATA_CB_TABLE
{
    GSN_WLRPAN_APP_CB_T  dataCfm;
    GSN_WLRPAN_APP_CB_T  dataInd;
    GSN_WLRPAN_APP_CB_T  dataPurgeCfm;
    GSN_WLRPAN_APP_CB_T  data6LoWPANCfm;
    GSN_WLRPAN_APP_CB_T  data6LoWPANInd;
}GSN_WLRPAN_DATA_CB_TABLE_T;
/**
 *****************************************************************************
 * @internal
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Context. 
 *****************************************************************************/
typedef struct GSN_WLRPAN
{
    UINT8 devIndx;
    GSN_DOT154IF_CTX_T *pDot4IfCtx; /**< Pointer to the Wif conetxt */
    UINT8 handllingReq;
    GSN_WLRPAN_DATA_CB_TABLE_T* pDataTable;
    VOID *pDataCbCtx;
    GSN_WLRPAN_MGMT_CB_TABLE_T *pMgmtTable;
    VOID *pMgmtCbCtx;     
}GSN_WLRPAN_T;

/**
 *****************************************************************************
 * @ingroup GsnWlrPAN
 * @brief structure declaration for Generic testing operation.   
 *****************************************************************************/
#define GSN_WLP_GEN_RF_TEST_RX_START        0
#define GSN_WLP_GEN_RF_TEST_RX_STOP          1
#define GSN_WLP_GEN_RF_TEST_RX_STOP_CFM  2
#define GSN_WLP_GEN_RF_TEST_TX                    3
#define GSN_WLP_GEN_TEST_REQ 4
    
typedef struct GSN_WLP_RF_TEST_TX
{
    UINT8 channel;
    UINT8 frmLen;
    UINT8 txPwr;
    UINT32 numOfFrm;
    UINT32 delay;
}GSN_WLP_RF_TEST_TX_T;

typedef struct GSN_WLP_RF_TEST_RX_START
{
    UINT8 channel;
    UINT8 filter; 
    UINT8 frmLen;
}GSN_WLP_RF_TEST_RX_START_T;

typedef struct GSN_WLP_RF_TEST_RX_STAT
{
    UINT32 pktRecv;
    UINT32 byteRecv;        
}GSN_WLP_RF_TEST_RX_STAT_T;


typedef struct GSN_WLP_GEN_TEST
{
    UINT32 msgId;
    union
    {
        GSN_WLP_RF_TEST_TX_T txTest;
        GSN_WLP_RF_TEST_RX_START_T rxTestStart;
        GSN_WLP_RF_TEST_RX_STAT_T rxStat;
    }testParam;
}GSN_WLP_GEN_TEST_T;



/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Initialization function. 
 *****************************************************************************/
PUBLIC GSN_STATUS 
GsnWLRPAN_Init( GSN_WLRPAN_T *pCtx, GSN_DOT154IF_CTX_T *pDot4IfCtx,    
    GSN_WLRPAN_MGMT_CB_TABLE_T *pMgmtTable, VOID *pMgmtCbCtx, 
    GSN_WLRPAN_DATA_CB_TABLE_T *pDataTable, VOID *pDataCbCtx );

/**< Private function used in WLRPAN DRIVFER */
GSN_STATUS
GsnWLRPAN_WifMgmtSend( GSN_WLRPAN_T *pCtx, UINT32 msgId, VOID *data, 
  UINT32 dataLen );

GSN_STATUS
GsnWLRPAN_WifDataSend( GSN_WLRPAN_T *pCtx, UINT32 msgId, VOID *data, 
  UINT32 dataLen );

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Associate request function. 
 *****************************************************************************/
PUBLIC INLINE GSN_STATUS 
GsnWLRPAN_AssociateReq( GSN_WLRPAN_T *pWlrpan, 
    GSN_WLRPAN_ASSOCIATE_REQ_T *pReq )
{
    return GsnWLRPAN_WifMgmtSend( pWlrpan, GSN_WLRPAN_MGMT_ASSOCIATE_REQ,
        pReq, sizeof(GSN_WLRPAN_ASSOCIATE_REQ_T) );
}

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Associate request function. 
 *****************************************************************************/
PUBLIC INLINE GSN_STATUS 
GsnWLRPAN_DisAssociateReq( GSN_WLRPAN_T *pWlrpan, 
    GSN_WLP_DISASSOCIATE_REQ_T *pReq )
{
    return GsnWLRPAN_WifMgmtSend( pWlrpan, GSN_WLRPAN_MGMT_DISASSOCIATE_REQ,
        pReq, sizeof(GSN_WLP_DISASSOCIATE_REQ_T) );
}


/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Associate response function. 
 *****************************************************************************/
PUBLIC INLINE GSN_STATUS 
GsnWLRPAN_AssociateRsp( GSN_WLRPAN_T *pWlrpan, 
    GSN_WLRPAN_ASSOCIATE_RSP_T *pRsp )
{
    return GsnWLRPAN_WifMgmtSend( pWlrpan, GSN_WLRPAN_MGMT_ASSOCIATE_RSP, 
        pRsp, sizeof( GSN_WLRPAN_ASSOCIATE_RSP_T ) );
}

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Scan request function. 
 *****************************************************************************/
PUBLIC INLINE GSN_STATUS 
GsnWLRPAN_ScanReq( GSN_WLRPAN_T *pWlrpan, 
    GSN_WLRPAN_SCAN_REQ_T *pReq )
{
    return GsnWLRPAN_WifMgmtSend( pWlrpan, GSN_WLRPAN_MGMT_SCAN_REQ, pReq, 
        sizeof( GSN_WLRPAN_SCAN_REQ_T ) );
}

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Data request function. 
 *****************************************************************************/
PUBLIC INLINE GSN_STATUS 
GsnWLRPAN_DataReq( GSN_WLRPAN_T *pWlrpan, 
    GSN_WLRPAN_DATA_REQ_T *pReq )
{
    return GsnWLRPAN_WifDataSend( pWlrpan, GSN_WLRPAN_DATA_REQ, pReq, 
        sizeof( *pReq ) );
}

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Purge request function. 
 *****************************************************************************/
PUBLIC INLINE GSN_STATUS 
GsnWLRPAN_PurgeReq( GSN_WLRPAN_T *pWlrpan, 
    GSN_WLRPAN_PURGE_REQ_T *pReq )
{
    return GsnWLRPAN_WifDataSend( pWlrpan, GSN_WLRPAN_DATA_PURGE_REQ, pReq, 
        sizeof( *pReq ) );
}

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Start request function. 
 *****************************************************************************/
PUBLIC INLINE GSN_STATUS 
GsnWLRPAN_StartReq( GSN_WLRPAN_T *pWlrpan, 
    GSN_WLRPAN_START_REQ_T *pReq )
{
    return GsnWLRPAN_WifMgmtSend( pWlrpan, GSN_WLRPAN_MGMT_START_REQ, pReq, 
        sizeof( *pReq ) );
}

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Get request function. 
 *****************************************************************************/
PUBLIC INLINE GSN_STATUS 
GsnWLRPAN_GetReq( GSN_WLRPAN_T *pWlrpan, 
    GSN_WLRPAN_GET_REQ_T *pReq )
{
    return GsnWLRPAN_WifMgmtSend( pWlrpan, GSN_WLRPAN_MGMT_GET_REQ, pReq, 
        sizeof( *pReq ) );
}

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Set request function. 
 *****************************************************************************/
PUBLIC INLINE GSN_STATUS 
GsnWLRPAN_SetReq( GSN_WLRPAN_T *pWlrpan, 
    GSN_WLRPAN_SET_REQ_T *pReq )
{
    return GsnWLRPAN_WifMgmtSend( pWlrpan, GSN_WLRPAN_MGMT_SET_REQ, pReq, 
        sizeof( *pReq ) );
}

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN PS POLL request function. 
 *****************************************************************************/
PUBLIC INLINE GSN_STATUS 
GsnWLRPAN_PsPollReq( GSN_WLRPAN_T *pWlrpan, 
    GSN_WLRPAN_POLL_REQ_T *pReq )
{
    return GsnWLRPAN_WifMgmtSend( pWlrpan, GSN_WLRPAN_MGMT_POLL_REQ, pReq, 
        sizeof( *pReq ) );
}

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN RX Enable request function. 
 *****************************************************************************/
PUBLIC INLINE GSN_STATUS 
GsnWLRPAN_RXEnReq( GSN_WLRPAN_T *pWlrpan, 
    GSN_WLRPAN_RXENABLE_REQ_T *pReq )
{
    return GsnWLRPAN_WifMgmtSend( pWlrpan, GSN_WLRPAN_MGMT_RX_ENABLE_REQ, pReq, 
        sizeof( GSN_WLRPAN_RXENABLE_REQ_T ) );
}

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Orphan Response function. 
 *****************************************************************************/
PUBLIC INLINE GSN_STATUS 
GsnWLRPAN_OrphanRsp( GSN_WLRPAN_T *pWlrpan, 
    GSN_WLRPAN_ORPHAN_RSP_T *pRsp )
{
    return GsnWLRPAN_WifMgmtSend( pWlrpan, GSN_WLRPAN_MGMT_ORPHAN_RSP, pRsp, 
        sizeof( GSN_WLRPAN_ORPHAN_RSP_T  ) );
}

/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN GTS Request function. 
 *****************************************************************************/
PUBLIC INLINE GSN_STATUS 
GsnWLRPAN_GTSReq( GSN_WLRPAN_T *pWlrpan, 
    GSN_WLRPAN_GTS_REQ_T *pReq )
{
    return GsnWLRPAN_WifMgmtSend( pWlrpan,  GSN_WLRPAN_MGMT_GTS_REQ, pReq, 
        sizeof( GSN_WLRPAN_GTS_REQ_T  ) );
}
                     
/**
 *****************************************************************************
 * @ingroup GsnWlrpan
 * @brief Definition for WLRPAN Sync Request function. 
 *****************************************************************************/
PUBLIC INLINE GSN_STATUS 
GsnWLRPAN_SyncReq( GSN_WLRPAN_T *pWlrpan, 
    GSN_WLRPAN_SYNC_REQ_T *pReq )
{
    return GsnWLRPAN_WifMgmtSend( pWlrpan, GSN_WLRPAN_MGMT_SYNC_REQ, pReq, 
        sizeof( GSN_WLRPAN_SYNC_REQ_T  ) );
}


PUBLIC INLINE GSN_STATUS 
GsnWLRPAN_TmrReq( GSN_WLRPAN_T *pWlrpan, 
    GSN_WLP_TMR_REQ_T *pReq )
{
    return GsnWLRPAN_WifMgmtSend( pWlrpan, GSN_WLRPAN_MGMT_TMR_REQ, pReq, 
        sizeof( GSN_WLP_TMR_REQ_T ) );
}

PUBLIC INLINE GSN_STATUS 
GsnWLRPAN_GenericReq( GSN_WLRPAN_T *pWlrpan, UINT8 type,
    VOID *pReq )
{
    GSN_WLP_GEN_TEST_T msg;
    
    msg.msgId = type;

    memcpy( &msg.testParam, (UINT8*)pReq, sizeof( GSN_WLP_GEN_TEST_T ));

    return GsnWLRPAN_WifMgmtSend( pWlrpan, GSN_WLRPAN_MGMT_GENERIC_REQ, &msg, 
        sizeof( GSN_WLP_GEN_TEST_T ) );
}

                                  
#ifdef __cplusplus
}
#endif
#endif /* _GSN_WLRPAN_DRIVER_H_ */



