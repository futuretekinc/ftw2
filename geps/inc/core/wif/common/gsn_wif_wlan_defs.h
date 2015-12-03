/******************************************************************************
*
*               COPYRIGHT (c) 20012-2014 GainSpan Corporation
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
* $RCSfile: gsn_wif_wlan_defs.h,v $
*
* Description : This file contains common public definitions for WLAN CPU 
*               WLAN control command/event definitions.
******************************************************************************/
#ifndef _GSN_WIF_WLAN_DEFS_H_
#define _GSN_WIF_WLAN_DEFS_H_
#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
* File Inclusion
*****************************************************************************/
#include "core/wif/common/gsn_wlan_defs.h"
  
  
/**
 *****************************************************************************
 * @file gsn_wif_wlan_defs.h
 * @brief GSN WIF WLAN interface public header.
 * 
 *    This file contains the public APIs and structures of WLAN control
 *    interface.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup coresvcdoc
 * @{
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup GsnWif GSN WLAN Firmware Interface (WIF) module
 * @brief This group provides the interface with WLAN Firmware running on WLAN CPU. 
 *	  
 *		Whole GsnWif module is grouped in two parts, APIs and the Msg_Sys. The APIs provide the handling 
 * of various requests and indications.
 *		Msg_Sys provides the buffer managemnet and shared memeory management infrastructure to
 * trnasfer messages (control/data) between WLAn and APP firmware.
 ******************************************************************************/
 
/**
 *****************************************************************************
 * @}	END of coresvcdoc.
 *****************************************************************************/



/**
 *****************************************************************************
 * @ingroup GsnWif
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup GsnWifWlanDefs GSN WIF WLAN Control Interface
 *    This group of APIs provides WLAN control definitions like scan,
 *    association, etc.
*****************************************************************************/

/**
 *******************************************************************************
 * @ingroup GsnWdd
 * @brief Maximum WLAN rates.
 *
 *     This macro defines the maximum number of WLAN rates for 802.11b/g/n.
 ******************************************************************************/
#define GSN_WIF_WLAN_MAX_RATES          (12+8)  /**< Max rates for 802.11b/g */

#define GSN_WIF_WLAN_WPA_IE_LEN_MAX     32  /**< Max length of WPA IE */
#define GSN_WIF_WLAN_RSN_IE_LEN_MAX     32  /**< Max length of RSN IE */

#define GSN_WIF_WLAN_KEY_RSC_SIZE 		8
#define GSN_WIF_WLAN_KEY_ID_SIZE 		1
#define GSN_WIF_WLAN_KEY_MAX_SIZE		32
/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief NW type.
 * 
 *    This enum defines the NW type for connection.
*****************************************************************************/
typedef enum GSN_WIF_WLAN_NW_TYPE_E
{
    GSN_WIF_WLAN_NW_TYPE_STA = 0x01,
    GSN_WIF_WLAN_NW_TYPE_AP  = 0x02,
    GSN_WIF_WLAN_NW_TYPE_IBSS = 0x03,
    GSN_WIF_WLAN_NW_TYPE_15_4 = 0x4,
	GSN_WIF_WLAN_NW_TYPE_ISOTX = 0x5,
} GSN_WIF_WLAN_NW_TYPE_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Dot11 Auth type.
 * 
 *    This enum defines the 802.11 authentication to use during association.
*****************************************************************************/
typedef enum GSN_WIF_WLAN_DOT11_AUTH_E
{
    GSN_WIF_WLAN_DOT11_AUTH_OPEN = 0x01,
    GSN_WIF_WLAN_DOT11_AUTH_SHARED = 0x02,
} GSN_WIF_WLAN_DOT11_AUTH_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Auth type.
 * 
 *    This enum defines the authentication type of the connection.
*****************************************************************************/
typedef enum GSN_WIF_WLAN_AUTH_E
{
    GSN_WIF_WLAN_AUTH_NONE           = 0x01,
    GSN_WIF_WLAN_AUTH_WPA            = 0x02,
    GSN_WIF_WLAN_AUTH_WPA2           = 0x04,
    GSN_WIF_WLAN_AUTH_WPA_PSK        = 0x08,
    GSN_WIF_WLAN_AUTH_WPA2_PSK       = 0x10,
    GSN_WIF_WLAN_AUTH_WPA_CCKM       = 0x20,
    GSN_WIF_WLAN_AUTH_WPA2_CCKM      = 0x40,
} GSN_WIF_WLAN_AUTH_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief crypto type.
 * 
 *    This enum defines the crypto type of the connection.
*****************************************************************************/
typedef enum GSN_WIF_WLAN_CRYPTO_E
{
    GSN_WIF_WLAN_CRYPTO_NONE          = 0x01,
    GSN_WIF_WLAN_CRYPTO_WEP           = 0x02,
    GSN_WIF_WLAN_CRYPTO_TKIP          = 0x04,
    GSN_WIF_WLAN_CRYPTO_AES          = 0x08,
} GSN_WIF_WLAN_CRYPTO_T;

 
/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief wps ie set request.
 * 
 *    This structure defines the wps ie set request structure.
*****************************************************************************/

#define MAC_PROPRIETARY_INFO_LEN    250
typedef struct GSN_WIF_WLAN_WPS_IE_SET_REQ_S
{
    UINT8 Length;
    UINT8 Array[MAC_PROPRIETARY_INFO_LEN];
}GSN_WIF_WLAN_WPS_IE_SET_REQ_T;



/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief ie max length.
*****************************************************************************/

#define GSN_WIF_WLAN_RSN_WPA_IE_LEN_MAX 64

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Key type.
 * 
 *    This enum defines the key type used for installing the keys in to WLAN.
*****************************************************************************/
typedef enum GSN_WIF_WLAN_KEY_TYPE_E
{
	GSN_WIF_WLAN_KEY_TYPE_WEP, /*WEP Key*/
	GSN_WIF_WLAN_KEY_TYPE_PTK, /* Pairwise Transient Key*/
	GSN_WIF_WLAN_KEY_TYPE_GTK, /* Group Temporal Key*/
}GSN_WIF_WLAN_KEY_TYPE_T;



/* Test related definitions*/

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Types of patterns available
 * 
 *    This enum defines types of patterns available for tranmission in TX99/TX100 tests.
*****************************************************************************/

typedef enum GSN_WLAN_RF_TEST_TX_99_PATTERN_S
{
    TX99_PATTERN_ALL_ZEROS      = 0,
    TX99_PATTERN_ALL_ONES       = 1,
    TX99_PATTERN_REPEATING_10   = 2,
    TX99_PATTERN_PN7            = 3,
    TX99_PATTERN_PN9            = 4,
    TX99_PATTERN_PN15           = 5,

}GSN_WLAN_RF_TEST_TX_99_PATTERN_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Types of Tests
 * 
 *    This enum defines type of test as Transmission or Reception. 
*****************************************************************************/

typedef enum GSN_WLAN_RF_TEST_TYPE_S
{
    GSN_TEST_TYPE_RX        = 0,
    GSN_TEST_TYPE_TX        = 1,
}GSN_WLAN_RF_TEST_TYPE_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Types of WLAN modes
 * 
 *    This enum defines the available modes in bringing WLAN.
*****************************************************************************/

typedef enum GSN_WLAN_RF_TEST_MODE_S
{
    GSN_MODE_BSS_STA            = 0,
    GSN_MODE_IBSS_STA           = 1,
    GSN_MODE_AP                 = 2,
    GSN_MODE_UNASSOC_MODE       = 3,

    GSN_MODE_HUT_MODE_BSS_STA   = 0x80,
    GSN_MODE_HUT_MODE_IBSS_STA  = 0x81,
    GSN_MODE_HUT_MODE_AP        = 0x82
}GSN_WLAN_RF_TEST_MODE_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Host messages structure
 * 
 *    This structure defines the format of the host messages
*****************************************************************************/

typedef struct GSN_WLAN_PROCESS_MSG
{
    UINT16      msgType;     /**< To specify Ctrl or Data */
    UINT16      msgLen;      /**< Total length of the structure passed msgParams */
    UINT8       *msgParams;  /**< Buffer with parameters to be configured for the tests */
}GSN_WLAN_PROCESS_MSG_T;


/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Test General options.
 * 
 *    This structure defines the general parameters required for all the tests.
*****************************************************************************/

typedef struct GSN_RF_TEST_GENERAL_OPTIONS_S
{
    UINT16      userPrefChannel;    /**< Channel to be used for the tests */
    UINT8       bandWidth;          /**< 20MHz or 40MHz band */
    UINT8       unUsed;             /**< Padding purpose */
}GSN_RF_TEST_GENERAL_OPTIONS_T;


/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Frame TX Test.
 * 
 *    This structure defines the parameters required for TX Test.
*****************************************************************************/

typedef struct GSN_RF_TEST_FRAME_TX_S
{
    /* general options for all tests */
    GSN_RF_TEST_GENERAL_OPTIONS_T generalOptions; /**< general options used for all the tests */

    /* common options for tx-99/tx tests */
    UINT32      numFrames;          /**< No of frames to be transmitted (Use 99 for infinite transmission) */
    UINT16      frameLen;           /**< Length of the frame to be transmitted */
    UINT8       txRate;             /**< Rate at which transmission has to happen
                                         Standard rates in Legacy mode 
                                         and MCS index incase of 11n */
    UINT8       txPower;            /**< Power to be used for transmission */ 

    UINT8       destAddr[6];        /**< Destination MAC address*/
    UINT8       bssid[6];           /**< Source MAC address */                                         

    UINT8       htEnable;           /**< Legacy mode/11n mode */
    UINT8       guardInterval;      /**< Short or Long guardInterval */
    UINT8       greenField;         /**< To enable greenField transmission */
    UINT8       preambleType;       /**< Short or Long Preamble */

    UINT8       qosEnable;          /**< To enable qos parameters */
    UINT8       ackPolicy;          /**< To select the type of ack policy(Normal_ACK or NO_ACK ..etc */
    UINT8       scrambler;          /**< To enable Scrambler  */
    UINT8       aifsnVal;           /**< To configure the interframe space between the packets */

    UINT8       antenna;            /**< Internal or External antenna selection. Future purpose */    
    UINT8       ccaBypass;                /**< To enable bypassing cca */
    UINT8       unused[2];          /**< Padding purpose */

}GSN_RF_TEST_FRAME_TX_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief TX99/TX100 Tests.
 * 
 *    This structure defines the parameters required for TX99/TX100 Tests.
*****************************************************************************/

typedef struct GSN_RF_TEST_TX99_S
{
    /* general options for all tests */
    GSN_RF_TEST_GENERAL_OPTIONS_T generalOptions;   /**< general options used for all the tests */

    /* common options for tx-99/tx tests */
    UINT32      numFrames;          /**< No of frames to be transmitted (Use 99 for infinite transmission) */
    UINT16      frameLen;           /**< Length of the frame to be transmitted */
    UINT8       txRate;             /**< Rate at which transmission has to happen
                                         Standard rates in Legacy mode 
                                         and MCS index incase of 11n */
    UINT8       txPower;            /**< Power to be used for transmission */

    UINT8       destAddr[6];        /**< Destination MAC address*/
    UINT8       bssid[6];           /**< Source MAC address */

    UINT8       guardInterval;      /**< Short or Long guardInterval */
    UINT8       greenField;         /**< To enable greenField transmission */
    UINT8       antenna;            /**< Internal or External antenna selection. Future purpose */

    /* PHY TEST MODE OPTIONS: specific to tx-99/tx-100 */
    UINT8       cca;                /**< To enable bypassing cca */
    UINT8       agc;                /**< To remove agc module */
    UINT8       contPreambleMode;   /**< To enable/disable the mode */
    UINT8       spreader;           /**< To enable/disable the mode */

    UINT8       scrambler;          /**< To remove the scrambler mechanism */
    UINT8       preamble;           /**< To enable/disable the mode */
    UINT8       preambleType;       /**< Short or Long Preamble */
    UINT8       testPatternType;    /**< Selects the test pattern to be transmitted */

    UINT8       phyTestTxRate;      /**< Rate at which transmission has to happen */    
    UINT8       modeSelect;         /**< Mode selection 11b/g/n */
    UINT8       unused[3];          /**< Padding purpose */

}GSN_RF_TEST_TX99_T;
/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief TX100 Test.
 * 
 *    This structure defines the parameters required for TX100 Test.
*****************************************************************************/

typedef struct GSN_RF_TEST_TX100_S
{
    /* general options for all tests */
    GSN_RF_TEST_GENERAL_OPTIONS_T generalOptions;   /**< general options used for all the tests */

    UINT8       txPower;            /**< Power to be used for transmission */
    UINT8       antenna;            /**< Internal or External antenna selection. Future purpose */

    /* PHY TEST MODE OPTIONS: specific to tx-99/tx-100 */
    UINT8       cca;                /**< To enable bypassing cca */
    UINT8       agc;                /**< To remove agc module */
    UINT8       contPreambleMode;   /**< To enable/disable the mode */
    UINT8       spreader;           /**< To enable/disable the mode */

    UINT8       scrambler;          /**< To remove the scrambler mechanism */
    UINT8       preamble;           /**< To enable/disable the mode */
    UINT8       preambleType;       /**< Short or Long Preamble */
    UINT8       testPatternType;    /**< Selects the test pattern to be transmitted */

    UINT8       phyTestTxRate;      /**< Rate at which transmission has to happen */    
    UINT8       modeSelect;         /**< Mode selection 11b/g/n */
}GSN_RF_TEST_TX100_T;


/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Carrier Wave Transmit Test.
 * 
 *    This structure defines the parameters required for Carrier Wave Transmit Test.
*****************************************************************************/

typedef struct GSN_RF_TEST_CARRIER_WAVE_TEST_S
{
    /* general options for all tests */
    GSN_RF_TEST_GENERAL_OPTIONS_T generalOptions;   /**< general options used for all the tests */

    UINT8       txPower;            /**< Power to be used for transmission */
    UINT8       antenna;            /**< Internal or External antenna selection. Future purpose */

    /* carrier wave test specific options */
    UINT8       customWavePeriod;        /**< Period to be used for generating the wave */     
    UINT8       unused;          /**< Padding purpose */    

}GSN_RF_TEST_CARRIER_WAVE_TEST_T;


/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Frame RX Test.
 * 
 *    This structure defines the parameters required for RX Test.
*****************************************************************************/

typedef struct GSN_RF_TEST_FRAME_RX_S
{
    /* general options for all tests */
    GSN_RF_TEST_GENERAL_OPTIONS_T generalOptions;   /**< general options used for all the tests */

    /* rx test specific options */
    UINT32      rxFrameTypeFilter;      /**< Type of the packets to be filtered (Beacon filter ..etc) */
    UINT8       rxAddrFilter[6];        /**< MAC address of the packets to be filtered */
    UINT8       antenna;                /**< Internal or External antenna selection. Future purpose */        
    UINT8       unused;                 /**< Padding purpose */

}GSN_RF_TEST_FRAME_RX_T;


/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief RX Stop Indication
 * 
 *    This structure defines the stats collected in RX tests which will be indicated
 *    after the test.
*****************************************************************************/

typedef struct GSN_WLAN_RF_TEST_RX_STATS_S
{
    UINT32      rxPackets;          /**< No of packets received */
    UINT32      rxBytes;            /**< No of bytes received */
    UINT32      crcErrors;          /**< No of packets received with CRC Errors */
    UINT32      secErrors;          /**< No of packets received with Security Errors */
    UINT32      dupPackets;         /**< No of duplicate packets received */
    UINT32      headerErrors;       /**< No of packets received with header Errors */
    UINT32      avgRssi;            /**< Average RSSI of the received packets */
 
    UINT32      rxRate1_long;       /**< No of packets received at 1M and Long Preamble */
    UINT32      rxRate2_long;       /**< No of packets received at 2M and Long Preamble */
    UINT32      rxRate5_long;       /**< No of packets received at 5M and Long Preamble */
    UINT32      rxRate11_long;      /**< No of packets received at 11M and Long Preamble */
    UINT32      rxRate2_short;      /**< No of packets received at 2M and Short Preamble */
    UINT32      rxRate5_short;      /**< No of packets received at 5M and Short Preamble */
    UINT32      rxRate11_short;     /**< No of packets received at 11M and Short Preamble */

    UINT32      rxRate6;            /**< No of packets received at 6M */
    UINT32      rxRate9;            /**< No of packets received at 9M */
    UINT32      rxRate12;           /**< No of packets received at 12M */
    UINT32      rxRate18;           /**< No of packets received at 18M */
    UINT32      rxRate24;           /**< No of packets received at 24M */
    UINT32      rxRate36;           /**< No of packets received at 36M */
    UINT32      rxRate48;           /**< No of packets received at 48M */
    UINT32      rxRate54;           /**< No of packets received at 54M */
    
    UINT32      rxMcsSgi[8];        /**< No of packets received at
                                         respective MCS Index with Short GI*/
    UINT32      rxMcsLgi[8];        /**< No of packets received at
                                         respective MCS Index with Long GI*/    
}GSN_WLAN_RF_TEST_RX_STATS_T;

typedef struct GSN_WIF_API_WLAN_RF_TEST_FRAME_TX_DONE_IND_S
{
    UINT32      txPackets;          /**< No of packets transmitted */
}GSN_WIF_API_WLAN_RF_TEST_FRAME_TX_DONE_IND_T;

typedef struct GSN_WIF_WLAN_UNASSOC_MODE_START_REQ_S
{
    UINT32 ifNum;    
} GSN_WIF_API_WLAN_UNASSOC_MODE_START_REQ_T;

typedef struct GSN_WIF_API_WLAN_UNASSOC_MODE_START_RESP_S
{
    UINT32 ifNum;
    UINT8   status; /* 0x00 - Fail, 0x01 - Success */
} GSN_WIF_API_WLAN_UNASSOC_MODE_START_RESP_T;


typedef struct GSN_WIF_WLAN_UNASSOC_MODE_STOP_REQ_S
{
    UINT32 ifNum;    
} GSN_WIF_API_WLAN_UNASSOC_MODE_STOP_REQ_T;

typedef struct GSN_WIF_API_WLAN_UNASSOC_MODE_STOP_RESP_S
{
    UINT32 ifNum;
    UINT8   status; /* 0x00 - Fail, 0x01 - Success */
} GSN_WIF_API_WLAN_UNASSOC_MODE_STOP_RESP_T;

typedef struct GSN_WIF_API_WLAN_UNASSOC_MODE_CCA_SET_RESP_S
{
    UINT32 ifNum;
} GSN_WIF_API_WLAN_UNASSOC_MODE_CCA_SET_RESP_T;

typedef struct GSN_WIF_WLAN_UNASSOC_MODE_CCA_SET_REQ_S
{
    UINT8 ifNum;
    INT8 threshold;    /**< CCA threshold in 2's complement */
    UINT16 timeout;   /**< Tx timeout waiting for CCA idle in ms */
} GSN_WIF_API_WLAN_UNASSOC_MODE_CCA_SET_REQ_T;


typedef enum GSN_WIF_WLAN_UNASSOC_RX_FILTER_E
{
    GSN_WIF_WLAN_UNASSOC_RX_FILTER_BEACON =0x01,
    GSN_WIF_WLAN_UNASSOC_RX_FILTER_PROBEREQ =0x02,
    GSN_WIF_WLAN_UNASSOC_RX_FILTER_PROBERESP =0x04,
    GSN_WIF_WLAN_UNASSOC_RX_FILTER_MCDATA =0x08,
    GSN_WIF_WLAN_UNASSOC_RX_FILTER_UCDATA =0x10,
    GSN_WIF_WLAN_UNASSOC_RX_FILTER_OBSS_UCDATA =0x20,
    GSN_WIF_WLAN_UNASSOC_RX_FILTER_DIRECTED_MGMT = 0x40,
    GSN_WIF_WLAN_UNASSOC_RX_FILTER_NON_DIRECTED_MGMT = 0x80,
    GSN_WIF_WLAN_UNASSOC_RX_FILTER_BC_MC_MGMT = 0x100,
    GSN_WIF_WLAN_UNASSOC_RX_FILTER_UC_OBSS_MGMT = 0x200,
    GSN_WIF_WLAN_UNASSOC_RX_FILTER_BC_MC_OBSS_MGMT = 0x400,
    GSN_WIF_WLAN_UNASSOC_RX_FILTER_MISC_MGMT = 0x800,
    GSN_WIF_WLAN_UNASSOC_RX_FILTER_CTS = 0x1000,
    GSN_WIF_WLAN_UNASSOC_RX_FILTER_RTS = 0x2000,
    GSN_WIF_WLAN_UNASSOC_RX_FILTER_CTRL_NON_DIRECTED = 0x4000,
    GSN_WIF_WLAN_UNASSOC_RX_FILTER_DUPLICATE =0x40000000,/* Duplicate frame enable */
    GSN_WIF_WLAN_UNASSOC_RX_FILTER_RAW =0x80000000, /* Do not remove mac header */
}GSN_WIF_WLAN_UNASSOC_RX_FILTER_T;
#define GSN_WIF_WLAN_UNASSOC_RX_WAIT_INFINITE  (0xFFFFFFFF)
typedef struct GSN_WIF_API_WLAN_UNASSOC_DATA_RX_CONFIG_REQ_S
{
    UINT32 ifNum;
    UINT32 rxFrameTypeBitMap;   /* Frame type to be recieved */
    UINT8  ieFilterEnable;      /* 0 - Disable IE based filtering, 1 - Enable IE based filtering */
    UINT32 ieFilterId;          /* IE id   Valid only if ieFilterEnable  is enabled */
                                /* IE based filtering is applicable for Beacons, Probe request and Probe response */
    GSN_WLAN_MAC_ADDR_T bssid;  /* Reserved for future use */
} GSN_WIF_API_WLAN_UNASSOC_DATA_RX_CONFIG_REQ_T;
typedef struct GSN_WIF_API_WLAN_UNASSOC_DATA_RX_CONFIG_RESP_S
{
    UINT32 ifNum;
    UINT8   status;  /* 0x00 - Fail, 0x01 - Success */
} GSN_WIF_API_WLAN_UNASSOC_DATA_RX_CONFIG_RESP_T;

typedef struct GSN_WIF_API_WLAN_UNASSOC_DATA_RX_START_REQ_S
{
     UINT32 ifNum;    
     UINT8 chNum;
     UINT32 rxWaitTime;   /* Receiver ON time in milli seconds */
                          /* 0xFFFFFFFF - Keep receiver ON, until stop is requested. */	
} GSN_WIF_API_WLAN_UNASSOC_DATA_RX_START_REQ_T;


typedef struct GSN_WIF_API_WLAN_UNASSOC_DATA_RX_START_RESP_S
{
    UINT32 ifNum;
    UINT8   status;  /* 0x00 - Fail, 0x01 - Success */
} GSN_WIF_API_WLAN_UNASSOC_DATA_RX_START_RESP_T;

typedef struct GSN_WIF_API_WLAN_UNASSOC_DATA_RX_STOP_REQ_S
{
    UINT32 ifNum;    
} GSN_WIF_API_WLAN_UNASSOC_DATA_RX_STOP_REQ_T;

typedef struct GSN_WIF_API_WLAN_UNASSOC_DATA_RX_STOP_RESP_S
{
    UINT32 ifNum;    
} GSN_WIF_API_WLAN_UNASSOC_DATA_RX_STOP_RESP_T;

#define GSN_WIF_MAC_DATA_FRAME_LEN      1508

typedef struct GSN_WIF_API_WLAN_UNASSOC_DATAREQ_HDR_S
{/* Make sure this header structure is 16 bit aligned */
    UINT32 ifNum;   
    UINT8 power;
    UINT8 ccaEnable; /* Per frame CCA enable/disable */
    UINT16 frameControl;    
    UINT16 seqControl;
    UINT8 channelNum;
    UINT8 txRate;
    UINT16 macFrameLen; /* Number of bytes in payload */
    GSN_WLAN_MAC_ADDR_T addr1;
    GSN_WLAN_MAC_ADDR_T addr2;
    GSN_WLAN_MAC_ADDR_T addr3;
    GSN_WLAN_MAC_ADDR_T addr4;  /* Addr4 is valid only if  both to-ds and frm-ds */
                                /* are SET  in frame control */
    UINT32 rxWaitTime;   /* Duration in milli sec to keep receiver on.*/ 
                         /* 0x00 - Don't change reciever state  */  

} GSN_WIF_API_WLAN_UNASSOC_DATAREQ_HDR_T;

typedef struct GSN_WIF_API_WLAN_UNASSOC_DATAREQ_S
{
    GSN_WIF_API_WLAN_UNASSOC_DATAREQ_HDR_T hdr;
    UINT8 payload[GSN_WIF_MAC_DATA_FRAME_LEN];    
} GSN_WIF_API_WLAN_UNASSOC_DATAREQ_T;

typedef enum GSN_WIF_WLAN_UNASSOC_FRAME_TYPE_E
{
    GSN_WIF_WLAN_UNASSOC_FRAME_TYPE_BEACON     = 0x01,
    GSN_WIF_WLAN_UNASSOC_FRAME_TYPE_PROB_REQ   = 0x02,
    GSN_WIF_WLAN_UNASSOC_FRAME_TYPE_PROB_RESP  = 0x03,
    GSN_WIF_WLAN_UNASSOC_FRAME_TYPE_UCAST_DATA = 0x04,
    GSN_WIF_WLAN_UNASSOC_FRAME_TYPE_MCAST_DATA = 0x05,
    GSN_WIF_WLAN_UNASSOC_FRAME_TYPE_CTS = 0x06,
    GSN_WIF_WLAN_UNASSOC_FRAME_TYPE_RTS = 0x07,
    GSN_WIF_WLAN_UNASSOC_FRAME_TYPE_ASSOC_REQ = 0x08,
    GSN_WIF_WLAN_UNASSOC_FRAME_TYPE_ASSOC_RESP = 0x09,
    GSN_WIF_WLAN_UNASSOC_FRAME_TYPE_RAW_DATA   = 0x0F,
} GSN_WIF_WLAN_UNASSOC_FRAME_TYPE_T;
typedef struct GSN_WIF_API_WLAN_UNASSOC_DATA_RX_HDR_S
{
    UINT8 ifNum;
    INT8 rssi;
    UINT16 frameLen;
    UINT8 frameType;
    UINT8 reserved[3];
    UINT32 timeStamp;
}GSN_WIF_API_WLAN_UNASSOC_DATA_RX_HDR_T;

typedef struct GSN_WIF_API_WLAN_UNASSOC_DATA_RX_INDICATION_S
{
  GSN_WIF_API_WLAN_UNASSOC_DATA_RX_HDR_T hdr;
  UINT8 frame[GSN_WIF_MAC_DATA_FRAME_LEN];  
} GSN_WIF_API_WLAN_UNASSOC_DATA_RX_INDICATION_T;
typedef struct GSN_WIF_WLAN_UNASSOCIATED_DATACFM_S
{
    UINT16 status; /* 0x00 - failed, 0x01 - success */
    UINT8  reserved[2];
    UINT32 timeStamp;
} GSN_WIF_WLAN_UNASSOCIATED_DATACFM_T;
/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Connect request.
 * 
 *    This structure defines the connect request structure.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_CONNECT_REQ_S
{
    UINT8 nwType;           /**<  GSN_WIF_WLAN_NW_TYPE_T */
    UINT8 hiddenSsid;       /**< indicates if the SSID should be masked out in beacons */
    
    GSN_WLAN_MAC_SSID_T  ssid;                       /**< SSID to connect to. */
    GSN_WLAN_MAC_ADDR_T  bssid;                          /**< BSSID to connect to. */
    UINT8           channel;                         /**< Channel on which to connect. */
    UINT16          beaconInterval;                 /**< Beacon interval. */
    UINT8           dtimPeriod;                     /**< DTIM period. */
    UINT16          listenInterval;                 /**< Listen interval to be
                                                         set in association
                                                         request. */
    UINT8           numRatesValid;                  /**< Number of rates valid
                                                         in rate set. */
    UINT8           rateSet[GSN_WIF_WLAN_MAX_RATES];/**< Array containing rates.
                                                         */
    UINT8           dot11authtype;  /**< GSN_WIF_WLAN_DOT11_AUTH_T */
    UINT8           authtype;       /**< GSN_WIF_WLAN_AUTH_T */
    UINT8           pairwiseCrypto; /**< GSN_WIF_WLAN_CRYPTO_T */
    UINT8           groupCrypto;    /**< GSN_WIF_WLAN_CRYPTO_T */

    UINT16          inactivityTimeoutInSec; /**< valid in AP mode only.
                                                 if connected STA is inactive
                                                 for this many seconds, AP will
                                                 de-auth that STA. */

    UINT8 rsnWpaIeLen;
    UINT8 rsnWpaIe[GSN_WIF_WLAN_RSN_WPA_IE_LEN_MAX];

    UINT16          frameLen;       /**< Len of the frame. 0 means frame not  valid */
    UINT8           frame[512];       /**< Frame */
} GSN_WIF_WLAN_CONNECT_REQ_T;



/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Connect indication.
 * 
 *    This structure defines the connect indication structure.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_CONNECT_IND_S
{
    UINT8 channel;      /**< channel on which connection happened. */
    GSN_WLAN_MAC_ADDR_T  bssid;  /**< BSSID of the NW. */
    UINT16 beaconInterval;       /**< Beacon interval. */
    UINT8  dtimPeriod;           /**< DTIM period. */
    UINT16 listenInterval;       /**< Listen interval */

    GSN_WLAN_MAC_ADDR_T staAddr; /**< connecting STA addr, valid in AP mode */   
    UINT8 macFrameLen;
    UINT8 macFrame[GSN_WLAN_MAC_MAX_FRAME_LEN];
} GSN_WIF_WLAN_CONNECT_IND_T;




/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief MIC failure indication.
 * 
 *    This structure defines the mic failure indication structure.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_MIC_FAILURE_IND_S
{
    GSN_WLAN_MAC_ADDR_T staAddr;/**< STA's mac addr. valid in AP mode */  
    UINT8 micStatus;            /**< MIC fail status */
} GSN_WIF_WLAN_MIC_FAILURE_IND_T;



/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief rssi get response format.
 * 
 *    This structure defines the rssi get cmd response format.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_RSSI_S
{
    INT8 rssi;
} GSN_WIF_WLAN_RSSI_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief num retries get cmd response format.
 * 
 *    This structure defines the num retries get cmd response format.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_NUM_RETRY_S
{
    UINT16 numRetry;
} GSN_WIF_WLAN_NUM_RETRY_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief wlan tx rate set command structure
 * 
 *    This structure defines the wlan rate struct command/command response format.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_TX_RATE_S
{
    UINT8 dataFrameRate;
    UINT8 mgmtFrameRate;
    UINT8 ctlFrameRate;
} GSN_WIF_WLAN_TX_RATE_T;
/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief tx power set/get format power indexes.
 * 
 *    This structure defines the Memory or Register structure to Peek/Poke from WLAN.
*****************************************************************************/

typedef struct GSN_WIF_WLAN_MEM_REG_S
{
    UINT32  regAddr;
    UINT32  regData;
    UINT8   addrType;    
} GSN_WIF_WLAN_MEM_REG_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief tx power set/get format power indexes.
 * 
 *    This enum defines the types of Memory or Register to Peek/Poke from WLAN.
*****************************************************************************/

typedef enum GSN_WIF_WLAN_MEM_REG_TYPE_E
{
    GSN_WLAN_MEM_REG_TYPE_REG   = 0,
    GSN_WLAN_MEM_REG_TYPE_PHY   = 1,
}GSN_WIF_WLAN_MEM_REG_TYPE_T;
/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief tx power set/get format power indexes.
 * 
 *    This structure defines the tx power get/set cmd format indexes.
*****************************************************************************/
typedef enum GSN_WIF_WLAN_TX_POW_RATE_IDX_E
{
    GSN_TX_POW_802_11B_IDX      = 0,
    GSN_TX_POW_802_11G_LO_IDX   = 1,
    GSN_TX_POW_802_11G_HI_IDX   = 2,
    GSN_TX_POW_802_11N_LO_IDX   = 3,
    GSN_TX_POW_802_11N_HI_IDX   = 4,
    GSN_TX_POW_MAX_IDX          = 5
}GSN_WIF_WLAN_TX_POW_RATE_IDX_T;
/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief tx power set/get format.
 * 
 *    This structure defines the tx power get/set cmd format.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_TX_POWER_S
{
    UINT8 txPow[5];
} GSN_WIF_WLAN_TX_POWER_T;
/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief stat type.
 * 
 *    This enum defines the statistics type for read stats command
*****************************************************************************/
typedef enum GSN_WIF_WLAN_MAC_STATE_E
{
    GSN_WIF_WLAN_MAC_STATE_NOT_CONNECTED    = 0x0,
    GSN_WIF_WLAN_MAC_STATE_CONNECTED        = 0x1
} GSN_WIF_WLAN_MAC_STATE_T;
/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief wlan state get cmd response format.
 * 
 *    This structure defines the wlan state get cmd response format.
*****************************************************************************/


typedef struct GSN_WIF_MAC_STATE_GET_RSP_S
{
    GSN_WIF_WLAN_MAC_STATE_T state;
}GSN_WIF_MAC_STATE_GET_RSP_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief list of connected STA's info
 * 
 *    This structure defines the connected STA list indication structure.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_CONNECTED_STA_LIST_RSP_S
{
    UINT32 numStaConnected; /**< number of STAs connected */
    UINT8 addr[0];            /**< MIC fail status */
} GSN_WIF_WLAN_CONNECTED_STA_LIST_RSP_T;




#ifndef UWORD8
typedef unsigned  char  UWORD8;
#endif

#ifndef UWORD16
typedef unsigned short UWORD16;
#endif

#ifndef UWORD32
typedef unsigned int UWORD32;
#endif



/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief wlan tx statistics get cmd
 * 
 *    This structure defines the wlan tx statistics get command structure
*****************************************************************************/
typedef struct GSN_WIF_WLAN_TX_STATS_S
{
    UINT32 statType;             /* stat type: rx stats/tx stats */
    struct
    {
        UWORD32 itxs;            /* TX Success */
        UWORD32 itxto;           /* TX Timeout */
        UWORD32 itxf;            /* TX Failed */
    } st;

    /* Transmit cipher type structure */
    struct
    {
        UWORD32 wep40;           /* WEP-40 encrypted */
        UWORD32 wep104;          /* WEP-104 encrypted */
        UWORD32 tkip;            /* TKIP encrypted */
        UWORD32 ccmp;            /* CCMP encrypted */
        UWORD32 unencryp;        /* Not encrypted */
        UWORD32 ukencryp;        /* Unknown encryption */
    } cip_type;

    struct
    {
        UWORD32 leg[16][2];                      /* Legacy */
        UWORD32 ht20l[GSN_WLAN_MAX_MCS_SUPPORTED + 1][2]; /* HT-LongGI-20MHz */
        UWORD32 ht20s[GSN_WLAN_MAX_MCS_SUPPORTED + 1][2]; /* HT-ShrtGI-20MHz */
        UWORD32 ht40l[GSN_WLAN_MAX_MCS_SUPPORTED + 1][2]; /* HT-LongGI-40MHz */
        UWORD32 ht40s[GSN_WLAN_MAX_MCS_SUPPORTED + 1][2]; /* HT-ShrtGI-40MHz */
        UWORD32 mcs32s[2];                       /* MCS-32 ShortGI  */
        UWORD32 mcs32l[2];                       /* MCS-32 LongGI   */
    } dr;

    struct
    {
        UWORD32 probersp;        /* Probe response */
        UWORD32 probereq;        /* Probe request */
        UWORD32 mc_data;         /* Multicast data */
        UWORD32 uc_data;         /* Unicast data */
        UWORD32 qos_uc_data;     /* Unicast QoS data */
        UWORD32 qos_mc_data;     /* Multicast QoS data */
        UWORD32 amsdu_uc_data;   /* Unicast AMSDU data */
        UWORD32 amsdu_mc_data;   /* Multicast AMSDU data */
        UWORD32 ampdu_uc_data;   /* Unicast AMPDU data */
        UWORD32 ampdu_mc_data;   /* Multicast AMPDU data */
        UWORD32 oth_mgmt;        /* Other management */
        UWORD32 oth;			 /* Other frames */
        UWORD32 ctrl;
    } type;

    UWORD32 retries;
    UWORD32 multiple_retries;
    UWORD32 fragments;
} GSN_WIF_WLAN_TX_STATS_T;



/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief wlan rx statistics get cmd
 * 
 *    This structure defines the wlan rx statistics get command structure
*****************************************************************************/
typedef struct GSN_WIF_WLAN_RX_STATS_S
{
    UINT32 statType;             /* stat type: rx stats/tx stats */
    struct
    {
        UWORD32 irx0;            /* Invalid */
        UWORD32 irxf;            /* FCS failure */
        UWORD32 irxs;            /* Rx Successful */
        UWORD32 irxd;            /* Duplicate Detected */
        UWORD32 irxmf;           /* MIC failed */
        UWORD32 irxkf;           /* Key failed */
        UWORD32 irxicvf;         /* ICV failed */
        UWORD32 irxtkipicvf;     /* ICV failed for TKIP */
        UWORD32 irxtkipmf;       /* MIC failed for TKIP */
        UWORD32 irxrf;           /* CCMP Replay Failure */
        UWORD32 irxtkiprf;       /* TKIP Replay Failure */
        UWORD32 irxdip;          /* Defragmentation in Progress */
        UWORD32 irxdf;           /* Defragmentation Failure */
        UWORD32 irxex;           /* Exception - Reserved value */
    } st;

    /* Receive cipher type structure */
    struct
    {
        UWORD32 wep40;           /* WEP-40 encrypted */
        UWORD32 wep104;          /* WEP-104 encrypted */
        UWORD32 tkip;            /* TKIP encrypted */
        UWORD32 ccmp;            /* CCMP encrypted */
        UWORD32 unencryp;        /* Not encrypted */
        UWORD32 ukencryp;        /* Unknown encryption */
    } cip_type;

    struct
    {
        UWORD32 leg[16][2];                      /* Legacy */
        UWORD32 ht20l[GSN_WLAN_MAX_MCS_SUPPORTED + 1][2]; /* HT-LongGI-20MHz */
        UWORD32 ht20s[GSN_WLAN_MAX_MCS_SUPPORTED + 1][2]; /* HT-ShrtGI-20MHz */
        UWORD32 ht40l[GSN_WLAN_MAX_MCS_SUPPORTED + 1][2]; /* HT-LongGI-40MHz */
        UWORD32 ht40s[GSN_WLAN_MAX_MCS_SUPPORTED + 1][2]; /* HT-ShrtGI-40MHz */
        UWORD32 mcs32s[2];                       /* MCS-32 ShortGI  */
        UWORD32 mcs32l[2];                       /* MCS-32 LongGI   */
    } dr;

    struct
    {
        UWORD32 bcn;             /* Beacon */
        UWORD32 rts;             /* RTS */
        UWORD32 cts;             /* CTS */
        UWORD32 ack;             /* ACK */
        UWORD32 probersp;        /* Probe response */
        UWORD32 probereq;        /* Probe request */
        UWORD32 atim;            /* ATIM */
        UWORD32 cfend;           /* CF-End */
        UWORD32 back;            /* Block-Ack */
        UWORD32 bar;             /* Block-Ack Request */
        UWORD32 mc_data;         /* Multicast data */
        UWORD32 uc_data;         /* Unicast data */
        UWORD32 oth_data;        /* Other data */
        UWORD32 qos_uc_data;     /* Multicast QoS data */
        UWORD32 qos_mc_data;     /* Unicast QoS data */
        UWORD32 qos_oth_data;    /* Other QoS data */
        UWORD32 amsdu_uc_data;   /* Multicast AMSDU data */
        UWORD32 amsdu_mc_data;   /* Unicast AMSDU data */
        UWORD32 amsdu_oth_data;  /* Other AMSDU data */
        UWORD32 oth_mgmt;        /* Other Management frame, not listed */
        UWORD32 oth_ctrl;        /* Other Control frame, not listed */
        UWORD32 oth;             /* Other type, not listed */
    } type;
}GSN_WIF_WLAN_RX_STATS_T;



/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief connected STA list get indication
 * 
 *    This structure defines the connected sta list get command response structure
*****************************************************************************/
typedef struct GSN_WIF_CONCTD_STA_LIST_IND_S
{
    UINT32 count;       /**< Num of STA connected */
    INT8 *list;            /**< pointer to the list*/
}GSN_WIF_CONCTD_STA_LIST_IND_T;



/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief TKIP TSC/PN num
 * 
 *    This structure defines the TKIP TSC/PN number get command structure
*****************************************************************************/
typedef struct GSN_WIF_WLAN_TKIP_COUNTER_GET_RSP_S
{
    UINT32 msb;         /**< msb */
    UINT32 lsb;         /**< lsb */
} GSN_WIF_WLAN_TKIP_COUNTER_GET_RSP_T;




/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Disconnect request.
 * 
 *    This structure defines the disconnect request structure.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_DISCONNECT_REQ_S
{
    UINT16  dot11ReasonCode;    /**< Reason code that should be set in 
                                     disassociation/deauthentication frame */
    GSN_WLAN_MAC_ADDR_T staAddr;/**< STA's mac addr. valid in AP mode */  
} GSN_WIF_WLAN_DISCONNECT_REQ_T;


/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Disconnect reason code.
 * 
 *    This enum defines the disconnect reasons indicating the reason for
 *    connect request failure or termination of existing connection if the
 *    failure originated in WFW and not due to receipt of disassoc/deauth
 *    frame.
*****************************************************************************/
typedef enum GSN_WIF_WLAN_DISCONNECT_REASON_E
{
    GSN_WIF_WLAN_DISCONNECT_REASON_AUTH_FAILED,
    GSN_WIF_WLAN_DISCONNECT_REASON_ASSOC_FAILED,
    GSN_WIF_WLAN_DISCONNECT_REASON_RESOURCE_UNAVAIL,
    GSN_WIF_WLAN_DISCONNECT_REASON_SYNC_LOSS,
    GSN_WIF_WLAN_DISCONNECT_REASON_RETRY_EXCEEDED,
    GSN_WIF_WLAN_DISCONNECT_REASON_NW_UNAVAIL,
    GSN_WIF_WLAN_DISCONNECT_REASON_WFW_FAILURE,
    GSN_WIF_WLAN_DISCONNECT_REASON_PROTOCOL_FAILURE,
    GSN_WIF_WLAN_DISCONNECT_REASON_DEAUTH=0xFF,
} GSN_WIF_WLAN_DISCONNECT_REASON_T;


/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Disconnect indication.
 * 
 *    This structure defines the disconnect indication structure.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_DISCONNECT_IND_S
{
    UINT16  dot11ReasonStatusCode;    /**< Reason code that came in  
                                            disassociation/deauthentication
                                            frame or status code that came in
                                            association response failure 
                                            message. */
    UINT8  wfwReasonCode;   /**< GSN_WIF_WLAN_DISCONNECT_REASON_T:
                                 Status code indicating the reason for
                                 connect request failure or termination
                                 of existing connection if the failure
                                 originated in WFW and not due to receipt
                                 of disassoc/deauth frame. */
    GSN_WLAN_MAC_ADDR_T staAddr;/**< STA's mac addr. valid in AP mode */  
} GSN_WIF_WLAN_DISCONNECT_IND_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief set MAC address.
 * 
 *    This structure defines the set MAC address  structure.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_MAC_ADDR_SET_REQ_S
{
	UINT8 macAddr[GSN_WLAN_MAC_ADDR_LEN];
} GSN_WIF_WLAN_MAC_ADDR_SET_REQ_T;

/*
Other parameters to be supported:
WMM enable/disable
aggregation enable/disable with TID mask
country setting
IE to be set in association request
IE to be set in probe request
IEs to be set in probe response
IEs to be set in association resposne
Number of stations to support
keepalive - ie., wakeup radio, receive next beacon, receive data or send NULL if no data
*/

/* Scan Request*/
typedef struct GSN_WIF_WLAN_SCAN_REQ_S
{
    UINT8             scanType;
    GSN_WLAN_MAC_SSID_T    ssid;
    GSN_WLAN_MAC_ADDR_T    bssid;
    UINT8       channel[GSN_WLAN_MAC_MAX_CHNLS+1];
} GSN_WIF_WLAN_SCAN_REQ_T;

/* Scan Indication*/
typedef struct GSN_WIF_WLAN_SCAN_IND_T
{
    UINT8 nextValid;
    GSN_WLAN_MAC_SSID_T ssid;
    UINT8 bssid[6];
    UINT16 rssi;
    UINT8 channel;
    UINT8 frameType;
    UINT16 frameLen;
    UINT8 frame[GSN_WLAN_MAC_MAX_FRAME_LEN];
}GSN_WIF_WLAN_SCAN_IND_T;

/* Scan Compete indication */
typedef struct GSN_WIF_WLAN_SCAN_COMPLETE_IND_S
{
    UINT32 status;

}GSN_WIF_WLAN_SCAN_COMPLETE_IND_T;

/* Scan Compete indication */
typedef struct GSN_WIF_WLAN_BCN_MISS_IND_S
{
    UINT32 beaconMissCount;       /**< No of beacons missed */

}GSN_WIF_WLAN_BCN_MISS_IND_T;
/* Continuous TX fail indication */
typedef struct GSN_WIF_WLAN_CONT_TX_FAIL_IND_S
{
    UINT32 txFailCount;       /**< No of tx failed */

}GSN_WIF_WLAN_CONT_TX_FAIL_IND_T;

/* AP timestand RST indication */
typedef struct GSN_WIF_WLAN_AP_TIMESTAMP_RST_S
{
    UINT32 status;

}GSN_WIF_WLAN_AP_TIMESTAMP_RST_T;


/* Continuous rx decrypt fail indication */
typedef struct GSN_WIF_WLAN_CONT_DECRYPT_FAIL_IND_S
{
    UINT32 decryptFailCount;       /**< No of decrypt failed */

}GSN_WIF_WLAN_CONT_DECRYPT_FAIL_IND_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief beacon miss command params
 * 
 *    This structure defines the beacon miss command params
*****************************************************************************/

typedef struct GSN_WIF_WLAN_BCN_MISS_THRESHOLD_SET_S
{
    UINT32 beaconMissThresholdTime;     /**< Threshold time */
    UINT32 beaconMissThresholdNo;       /**< Threshold value */
}GSN_WIF_WLAN_BCN_MISS_THRESHOLD_SET_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief RTS enable command parameters
 * 
 *    This structure defines the RTS enable command parameters
*****************************************************************************/

typedef struct GSN_WIF_WLAN_RTS_ENABLE_S
{
    UINT8 txOpEnable;
    UINT16 threshold;
}GSN_WIF_WLAN_RTS_ENABLE_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief stat type.
 * 
 *    This enum defines the statistics type for read stats command
*****************************************************************************/
typedef enum GSN_WIF_WLAN_STAT_TYPE_E
{
    GSN_WIF_WLAN_STAT_TYPE_TX = 0x0,
    GSN_WIF_WLAN_STAT_TYPE_RX = 0x1,
} GSN_WIF_WLAN_STAT_TYPE_T;


/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief read statistics command structure format
 * 
 *    This structure defines the read statistics command structure format
*****************************************************************************/

typedef struct GSN_WIF_WLAN_STATISTICS_READ_REQ_S
{
    UINT8 reset;    /**< reset on read */
    UINT8 statType; /**< GSN_WIF_WLAN_STAT_TYPE_T */
}GSN_WIF_WLAN_STATISTICS_READ_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief set promiscous mode command params
 * 
 *    This structure defines the set promiscous mode command params
*****************************************************************************/

typedef struct GSN_WIF_WLAN_RX_FILTER_SET_S
{
    UINT32 filter;
}GSN_WIF_WLAN_RX_FILTER_SET_T;



/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief scan params set cmd parameters
 * 
 *    This structure defines the format of scan params set command
*****************************************************************************/

typedef struct GSN_WIF_WLAN_SCAN_PARAMS_SET_S
{
    UINT16      minActiveScanTime;     /**< To specify min scan time */
    UINT16      maxActiveScanTime;     /**< To specify min scan time */
    UINT16      passiveScanTime;       /**< To specify passive scan time */
}GSN_WIF_WLAN_SCAN_PARAMS_SET_T;


/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief key install msg format
 * 
 *    This structure defines the format of key install command
*****************************************************************************/

typedef struct GSN_WIF_WLAN_KEY_INSTALL_REQ_S
{
	UINT8                   keyType;                            /* GTK / PTK*/
	UINT8 keyIndex; /**< Key Index*/
	UINT8 keyAlgo; /**< Encryption Algorithm. AES/ TIKIP*/
	UINT8 keyUsage; /**< */
	UINT8 keyRsc[GSN_WIF_WLAN_KEY_RSC_SIZE]; /**< 8 Bytes RSC counter value*/
	UINT8 keyLen; /**< Key length*/
	UINT8                   keyVal[GSN_WIF_WLAN_KEY_MAX_SIZE];  /**< Key*/	
	GSN_WLAN_MAC_ADDR_T     macAddr;                            /**< MAC address. This will be used when 
	                                                                 the Node is acting a AP.
									                                 MAC address of the client for which
									                                 the key is installed is provided.*/
	
}GSN_WIF_WLAN_KEY_INSTALL_REQ_T;



/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief key remove msg format
 * 
 *    This structure defines the format of key remove command
*****************************************************************************/

typedef struct GSN_WIF_WLAN_KEY_REMOVE_REQ_S
{
	UINT8                   keyType;                            /* GTK / PTK*/
	UINT8 keyIndex; /**< Key Index*/
	UINT8 keyAlgo; /**< Encryption Algorithm. AES/ TIKIP*/
	UINT8 keyUsage; /**< */
	UINT8 keyRsc[GSN_WIF_WLAN_KEY_RSC_SIZE]; /**< 8 Bytes RSC counter value*/
	UINT8 keyLen; /**< Key length*/
	UINT8                   keyVal[GSN_WIF_WLAN_KEY_MAX_SIZE];  /**< Key*/	
	GSN_WLAN_MAC_ADDR_T     macAddr;                            /**< MAC address. This will be used when
	                                                                 the Node is acting a AP.
									                                 MAC address of the client for which
									                                 the key is installed is provided.*/
}GSN_WIF_WLAN_KEY_REMOVE_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Addba Set
 * 
 *    This structure defines the ADDBA Set structure.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_BA_REQ_S
{
    UINT8 ra[GSN_WLAN_MAC_ADDR_LEN];
    UINT8 tid;    /**< tid for which the block ack session needs to be enabled */
} GSN_WIF_WLAN_BA_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief AMSDU Setup/Removal
 * 
 *    This structure defines the AMSDU Session preparation structure.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_AMSDU_REQ_S
{
    UINT8 ra[GSN_WLAN_MAC_ADDR_LEN];
    UINT8 tid;    /**< tid for which the aggregation needs to be enabled */
} GSN_WIF_WLAN_AMSDU_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief AMPDU Setup/Removal
 * 
 *    This structure defines the AMPDU Session preparation structure.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_AMPDU_REQ_S
{
    UINT8 ra[GSN_WLAN_MAC_ADDR_LEN];
    UINT8 tid;    /**< tid for which the aggregation needs to be enabled */
} GSN_WIF_WLAN_AMPDU_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Frame Tx Fail Count Threshold Setup
 * 
 *    This structure defines the AMPDU Session preparation structure.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_FRAME_TX_FAIL_COUNT_THRESHOLD_REQ_S
{
    UINT8 frameTxFailCountThreshold;
} GSN_WIF_WLAN_FRAME_TX_FAIL_COUNT_THRESHOLD_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Frame Tx Fail Count Threshold Setup
 * 
 *    This structure defines the AMPDU Session preparation structure.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_FRAME_TX_FAIL_IND_S
{
    UINT8 frameTxFailCount;
} GSN_WIF_WLAN_FRAME_TX_FAIL_IND_T;

typedef struct GSN_WIF_WLAN_PHY_MODE_REQ_S
{
    UINT8 phyMode;
} GSN_WIF_WLAN_PHY_MODE_REQ_T;


/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Frame Tx Fail Count Threshold Setup
 * 
 *    This structure defines the structure.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_TXPOWER_REQ_S
{
    UINT8 txPower;
} GSN_WIF_WLAN_TXPOWER_REQ_T;

typedef enum GSN_WIF_WLAN_STA_PS_STATE_S
{
  GSN_WIF_WLAN_STA_PS_STATE_ACTIVE=1,
  GSN_WIF_WLAN_STA_PS_STATE_PS,
  GSN_WIF_WLAN_STA_PS_STATE_OFF
}GSN_WIF_WLAN_STA_PS_STATE_T;


typedef enum GSN_WIF_WLAN_STA_PS_WAKEUP_S
{
    GSN_WIF_WLAN_STA_PS_WAKEUP_DTIM=1,
    GSN_WIF_WLAN_STA_PS_WAKEUP_LISTEN_INTERVAL,
    GSN_WIF_WLAN_STA_PS_WAKEUP_CUSTOM
}GSN_WIF_WLAN_STA_PS_WAKEUP_T;

typedef enum GSN_WIF_WLAN_STA_PS_DATA_RX_TYPE_S
{
    GSN_WIF_WLAN_STA_PS_DATA_RX_TYPE_PS_POLL=1,
    GSN_WIF_WLAN_STA_PS_DATA_RX_TYPE_SWITCH_TO_ACTIVE
}GSN_WIF_WLAN_STA_PS_DATA_RX_TYPE_T;


typedef struct GSN_WIF_WLAN_STA_PS_CFG_S
{
    GSN_WIF_WLAN_STA_PS_WAKEUP_T wakeupType;
    UINT16 wakeupInterval; /**< for custom and listenInterval wakeup */
    UINT16 listenIntervalAssoc; /**< for association request */
    GSN_WIF_WLAN_STA_PS_DATA_RX_TYPE_T dataRxType;
    UINT8 uapsdEnable;/**< Not in use*/
	UINT8 txAtTbttWakeup;  /**< Tx Immediate or in next TBTT wakeup */
    UINT16 beaconWaitTimeout; /**< beacon wait time offset duation in ms */
    UINT16 activeToOffTimeout; /**< Active to off switch timeout offset in ms */
	UINT16 switchToActivePeriod; /**< Periodicity  to switch to Active in case of no data transfer (in ms) */	
}GSN_WIF_WLAN_STA_PS_CFG_T;

typedef struct GSN_WIF_WLAN_STA_PS_STATE_SET_S
{
    GSN_WIF_WLAN_STA_PS_STATE_T psState;
}GSN_WIF_WLAN_STA_PS_STATE_SET_T;

typedef struct GSN_WIF_WLAN_STA_PS_DAB_DONE_IND_EN_S
{
    UINT8 dabDoneIndEnable;
}GSN_WIF_WLAN_STA_PS_DAB_DONE_IND_EN_T;
/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief   deep sleep ap configuration
 * 
 *    This structure defines the deep sleep ap configuration structure.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_AP_PS_CFG_S
{
    UINT8  deepSleepEnable;      /**< deepsleep ap configuration */ 
    UINT8  ctsToSelfBeforeSleep; /**< should ap send cts to self before sleep */
    UINT32 rxOnAfterTx;          /**< in milli seconds */
}GSN_WIF_WLAN_AP_PS_CFG_T;
/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief KeepAlive set/get format.
 * 
 *    This structure defines the KeepAlive get/set cmd format.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_KEEP_ALIVE_SET_S
{
    UINT8 timeout_in_sec;
} GSN_WIF_WLAN_KEEP_ALIVE_SET_T;


/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @brief Mcst Rx set/get format.
 * 
 *    This structure defines the Mcst Rx get/set cmd format.
*****************************************************************************/
typedef struct GSN_WIF_WLAN_MCST_RX_SET_S
{
    UINT8 mcst_rx_enable;
} GSN_WIF_WLAN_MCST_RX_SET_T;

/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @ba_tx_tid and ba_rx_tid.
 * 
 *    This structure defines the Ba_Tx and Ba_Rx bitmap.
 *****************************************************************************/
typedef struct GSN_WIF_WLAN_ALLOW_BA_TID_BITMAP_S
{
    UINT16 ba_tx_tid;
    UINT16 ba_rx_tid;
}GSN_WIF_WLAN_ALLOW_BA_TID_BITMAP_T;
/**
 *****************************************************************************
 * @ingroup GsnWifWlanDefs
 * @ie_data and ie_data_len.
 * 
 *    This structure defines the propritery (Vender Specific - VS) ie details.
 *****************************************************************************/
typedef struct GSN_WIF_WLAN_VS_IE_S
{
    UINT8  ieDataLen;
    UINT8  ieData[64];
}GSN_WIF_WLAN_VS_IE_T;
/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/	
	

typedef GSN_RF_TEST_FRAME_TX_T              GSN_WIF_API_WLAN_RF_TEST_TX_START_REQ_T; 
typedef GSN_RF_TEST_FRAME_RX_T              GSN_WIF_API_WLAN_RF_TEST_RX_START_REQ_T ;
typedef GSN_RF_TEST_TX99_T                  GSN_WIF_API_WLAN_RF_TEST_TX99_START_REQ_T;
typedef GSN_RF_TEST_TX100_T                 GSN_WIF_API_WLAN_RF_TEST_TX100_START_REQ_T;
typedef GSN_RF_TEST_CARRIER_WAVE_TEST_T     GSN_WIF_API_WLAN_RF_TEST_CARRIER_WAVE_START_REQ_T;
typedef GSN_WLAN_RF_TEST_RX_STATS_T         GSN_WIF_API_WLAN_RF_TEST_FRAME_RX_STOP_RESP_T;


#ifdef __cplusplus
}
#endif
#endif /* _GSN_WIF_WLAN_DEFS_H_ */






