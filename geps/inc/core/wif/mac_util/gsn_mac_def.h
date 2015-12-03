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
 * $RCSfile: gsn_mac_def.h,v $
 *
 * Project: GSN APP Software
 *
 * Description:
 *      Mac header structure
 *
 *****************************************************************************/
 
 
 /**
 *****************************************************************************
 * @file gsn_mac_def.h
 * @brief GSN 802.11 MAC-level definitions.
 *    This file contains macro definitions for authentication, 
 * physical-layer properties, encryption, and various MAC address
 * filtering and comparison operations.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GEPSSupport
 *
 * @{
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup GsnMACDefines GSN MAC Definitions
 * @brief This group contains 802.11 MAC-level definitions.
 *
 * This group contains macro definitions for authentication, 
 * physical-layer properties, encryption, and various MAC address
 * filtering and comparison operations.  Note there are a number of
 * macro sequences where only the first element is included in the
 * documentation for simplicity; click on the source code definition
 * link to see all the options for the given macro type.
 *****************************************************************************/
 

/**
 *****************************************************************************
 * 
 * @}
 *****************************************************************************/
 

#ifndef _GSN_MAC_DEF_H_
#define _GSN_MAC_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

/**
 *****************************************************************************
 * @ingroup GsnMACDefines 
 * @brief authentication definitions.
 * @{
 *****************************************************************************/

#define GSN_MAC_AUTH_ALGO_OPEN         0
#define GSN_MAC_AUTH_ALGO_SHARED       1

#define GSN_MAC_AUTH_FIRST_SEQ         1
#define GSN_MAC_AUTH_SECOND_SEQ        2
#define GSN_MAC_AUTH_THIRD_SEQ         3
#define GSN_MAC_AUTH_FOURTH_SEQ        4

/**
 *****************************************************************************
 * @}
 *****************************************************************************/

/*   *< MIB field values  */

/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief 802.11 physical layer type (classic, a, b, g, etc.).
 * @{
 *****************************************************************************/

#define GSN_MAC_PHYTYPE_FHSS           1     /* not used                     */
#define GSN_MAC_PHYTYPE_DSSS           2     /* 802.11,   legacy 1 or 2 Mbps */
#define GSN_MAC_PHYTYPE_IR             3     /* not used                     */
#define GSN_MAC_PHYTYPE_OFDM           4     /* 802.11 a, on 5GHz            */
#define GSN_MAC_PHYTYPE_HRDSSS         5     /* 802.11 b                     */
#define GSN_MAC_PHYTYPE_ERP            6     /* 802.11 g, on 2.4Ghz          */

/**
 *****************************************************************************
 * @}
 * @ingroup GsnMACDefines
 * @brief BSS type - infrastructure (AP) or independent service set.
 * @{
 *****************************************************************************/

#define GSN_MAC_BSSTYPE_INFRASTRUCTURE 1
#define GSN_MAC_BSSTYPE_INDEPENDENT    0

/**
 *****************************************************************************
 * @}
 * @ingroup GsnMACDefines
 * @brief Authentication algorithm; used with OID type b.
 * @{
 *****************************************************************************/

#define GSN_MAC_AUTH_OPEN              1
#define GSN_MAC_AUTH_SHARED            2
#define GSN_MAC_AUTH_AUTO              3
#define GSN_MAC_AUTH_WPA               4
#define GSN_MAC_AUTH_WPAPSK            5
#define GSN_MAC_AUTH_WPANONE           6
#define GSN_MAC_AUTH_WPA2              7
#define GSN_MAC_AUTH_WPA2PSK           8


/**
 *****************************************************************************
 * @}
 * @ingroup GsnMACDefines
 * @brief 802.11 power management mode (active or PowerSave).
 *
 *****************************************************************************/

#define GSN_MAC_POWERMODE_ACTIF        1
#define GSN_MAC_POWERMODE_POWERSAVE    2

/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief 802.11 power mode.
 * @{
 *****************************************************************************/

#define GSN_MAC_POWERMODE_CAM          1
#define GSN_MAC_POWERMODE_MAXPSP       2
#define GSN_MAC_POWERMODE_FASTPSP      3


/**
 *****************************************************************************
 @ @}
 * @ingroup GsnMACDefines
 * @brief encryption type / status.
 *
 *  These values are essentially the values of the MIB element
 * GSN_WIF_ME_CONF_ENCRYPTIONSTATUS in the WLAN Firmware (WFW) MIB.
 * 
 * Note:  The original value of GSN_MAC_ENC_NONE is 0, as required
 * to set GSN_WIF_ME_CONF_ENCRYPTIONSTATUS to 0 in the WFW MIB.  However,
 * it is redefined here to 0x80 to allow the APP CPU to specify NONE
 * as one of the security modes.  It is then internally mapped back
 * to 0 when the WFW MIB element value is set.
 * @{
 *****************************************************************************/
 

#define GSN_MAC_ENC_WEP               0x01
#define GSN_MAC_ENC_WPA               0x02
#define GSN_MAC_ENC_TKIP              0x04
#define GSN_MAC_ENC_WPA2              0x10
#define GSN_MAC_ENC_CCMP              0x20
/* IMPORTANT NOTE: The original value of GSN_MAC_ENC_NONE as required to
   set GSN_WIF_ME_CONF_ENCRYPTIONSTATUS WLAN MIB is zero (0). But it is
   redefined here to 0x80 to allow APP to specify NONE as one of the security
   modes. Internally it is mapped to zero before setting the
   GSN_WIF_ME_CONF_ENCRYPTIONSTATUS WLAN MIB */
//#define GSN_MAC_ENC_NONE              0
#define GSN_MAC_ENC_NONE              0x80
#define GSN_MAC_ENC_ALL (GSN_MAC_ENC_NONE | GSN_MAC_ENC_WEP | GSN_MAC_ENC_TKIP \
                            | GSN_MAC_ENC_CCMP)

/**
 *****************************************************************************
 * @}
 * @ingroup GsnMACDefines
 * @brief Boolean type.
 *
 *****************************************************************************/

typedef UINT8 WLAN_BOOLEAN;

/**< MAC SSID type and macros */

/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief SSID length options (broadcast or standard).
 * @{
 *****************************************************************************/

#define GSN_MAC_BROADCAST_SSID_LEN     0
#define GSN_MAC_SSID_LEN              32


/**
 *****************************************************************************
 * @}
 * @ingroup GsnMACDefines
 * @brief structured type for storing an SSID.
 *
 *****************************************************************************/


typedef GSN_WLAN_MAC_SSID_T	GSN_MAC_SSID_T;


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief structured type for CMP SSID.
 *
 *****************************************************************************/


#define GSN_MAC_SSID_CMP( ssid1Ptr,ssid2Ptr )                            \
    ((( ssid1Ptr)->length == (ssid2Ptr)->length ) &&                 \
    ( memcmp((&( ssid1Ptr)->array[ 0 ]), (&( ssid2Ptr)->array[ 0 ]), \
    ( ssid1Ptr)->length) == 0 ))


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief utility for copying an SSID to a new memory location.
 *
 *****************************************************************************/

INLINE  void GSN_MAC_SSID_CPY( GSN_MAC_SSID_T *const dstSsidPtr, 
    const GSN_MAC_SSID_T *const srcSsidPtr )
{
    memcpy(( dstSsidPtr)->array, ( srcSsidPtr)->array, 
        ( size_t )(( srcSsidPtr)->length));
    dstSsidPtr->length = srcSsidPtr->length;
}


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief SSID empty pointer.
 *
 *****************************************************************************/
 
#define GSN_MAC_SSID_ISEMPTY( ssidPtr )   (( ssidPtr)->length == 0 )


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief physical layer radio channel type, including internal data for VCO control.
 *
 *****************************************************************************/

typedef struct
{
    UINT32        lastLock;    /**< Store old successful lock     */
    INT16         VCOFc;
    INT16         VCOBuffFc;
    UINT16        PLLInt;
    INT16         PLLFract;
    UINT8         LnaTrim;     /**< Only Necessary for 5 GHz      */
    UINT8         TXFreqTrim;  /**< Only Necessary for 5 GHz      */
    UINT8         data;        /**< b3 | b2 | VCOHiPwr | VCOBandHi*/
    UINT8         mode;        /**< b3 | G | B | A                */
    UINT8         channel;     /**< Channel code                  */
    UINT8         lockFailed;  /**< LockFailed counter            */
    INT8          txIQPhase;   /**< IQ Phase                      */
} GSN_MAC_PHY_CHANNEL_T, *GSN_MAC_PHY_CHANNELPTR_T;


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief default value of the length of a MAC address.
 *
 *****************************************************************************/


#define GSN_MAC_ADDR_LEN       GSN_WLAN_MAC_ADDR_LEN

/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief structured type for holding MAC address.
 *
 *****************************************************************************/

typedef GSN_WLAN_MAC_ADDR_T GSN_MAC_ADDR_T;



/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief utility function for copying a MAC address to a new memory location.
 *
 *****************************************************************************/

INLINE  void GSN_MAC_ADDR_CPY( void *const DstAddrPtr,
    const void *const SrcAddrPtr)
{
    (*(( UINT8* )( DstAddrPtr )  ) = *(( UINT8* )( SrcAddrPtr )));
    (*(( UINT8* )( DstAddrPtr ) + 1 ) = *(( UINT8* )( SrcAddrPtr ) + 1 ));
    (*(( UINT8* )( DstAddrPtr ) + 2 ) = *(( UINT8* )( SrcAddrPtr ) + 2 ));
    (*(( UINT8* )( DstAddrPtr ) + 3 ) = *(( UINT8* )( SrcAddrPtr ) + 3 ));
    (*(( UINT8* )( DstAddrPtr ) + 4 ) = *(( UINT8* )( SrcAddrPtr ) + 4 ));
    (*(( UINT8* )( DstAddrPtr ) + 5 ) = *(( UINT8* )( SrcAddrPtr ) + 5 ));
}


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief utility for comparing two MAC addresses; returns TRUE if they are equal.
 *
 *****************************************************************************/

INLINE  WLAN_BOOLEAN GSN_MAC_ADDR_CMP( const void *const Addr1Ptr,
    const void *const Addr2Ptr )
{   WLAN_BOOLEAN result;

    result = 
        (  
            ((*(( UINT8* )( Addr1Ptr )    ) == *(( UINT8* )( Addr2Ptr )))
            &&(*(( UINT8* )( Addr1Ptr ) +1 ) == *(( UINT8* )( Addr2Ptr ) +1 ))
            &&(*(( UINT8* )( Addr1Ptr ) +2 ) == *(( UINT8* )( Addr2Ptr ) +2 ))
            &&(*(( UINT8* )( Addr1Ptr ) +3 ) == *(( UINT8* )( Addr2Ptr ) +3 ))
            &&(*(( UINT8* )( Addr1Ptr ) +4 ) == *(( UINT8* )( Addr2Ptr ) +4 ))
            &&(*(( UINT8* )( Addr1Ptr ) +5 ) == *(( UINT8* )( Addr2Ptr ) +5 )))
        );
   return( result );
}

/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief utility to mask and filter the given address by the given mask/filter.
 *
 * This utility takes an input address, a mask, and a filter.  The input
 * address is bitwise-masked by the mask, and then compared to the
 * filter. If the masked address is the same as the filter, the function 
 * returns TRUE. 
 *
 *****************************************************************************/


INLINE  WLAN_BOOLEAN GSN_MAC_ADDR_FILTER( const GSN_MAC_ADDR_T* const addrPtr,
	const GSN_MAC_ADDR_T* const maskPtr, const GSN_MAC_ADDR_T * const filterPtr )
{
    GSN_MAC_ADDR_T masked;
    UINT8  i;

    for ( i = 0; i < GSN_MAC_ADDR_LEN; i++ )
    {
        masked.array[ i ] = addrPtr->array[ i ] & maskPtr->array[ i ];
    }
    return GSN_MAC_ADDR_CMP( &masked, filterPtr );
}


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief macro returns TRUE if the argument is a broadcast address.
 *
 *****************************************************************************/

#define GSN_MAC_ADDR_BCAST( Addr1Ptr )                                          \
     ((*(( UINT8* )( Addr1Ptr )  ) == 0xFF )                                \
    &&(*(( UINT8* )( Addr1Ptr ) + 1 ) == 0xFF )                             \
    &&(*(( UINT8* )( Addr1Ptr ) + 2 ) == 0xFF )                             \
    &&(*(( UINT8* )( Addr1Ptr ) + 3 ) == 0xFF )                             \
    &&(*(( UINT8* )( Addr1Ptr ) + 4 ) == 0xFF )                             \
    &&(*(( UINT8* )( Addr1Ptr ) + 5 ) == 0xFF ))


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief macro returns TRUE if the argument is a group address, and masks the group bit.
 *
 *****************************************************************************/

#define GSN_MAC_ADDR_GROUP( MacAddrPtr ) ((*( MacAddrPtr )) & GSN_MAC_HEAD_ADDR_GROUP_MASK )


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief macro sets an address to the broadcast address 0xFF FF FF FF FF FF.
 *
 *****************************************************************************/

#define GSN_MAC_ADDR_BCAST_SET( MacAddrPtr ) \
    memset(( UINT8* )( MacAddrPtr ), 0xFF, GSN_MAC_ADDR_LEN )


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief 802.11h (power control) type.
 *
 *****************************************************************************/ 
 
typedef struct GSN_MAC_POWER_CAPABILITY_IE_T
{
    UINT8  eltId ;
    UINT8  length;
    UINT8  powerCapaMin ;
    UINT8  powerCapaMax ;
} GSN_MAC_POWER_CAPABILITY_IE_T;




/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief maximum supported channels.
 *
 *****************************************************************************/ 

#define GSN_MAC_SUPPORTED_CHANNELS_TUPLE_MAX   4


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief supported channel tuple type.
 *
 *****************************************************************************/ 
typedef struct GSN_MAC_SUPPORTED_CHANNELS_IE_T
{
    UINT8  eltId ;
    UINT8  length;
    struct {
       UINT8  firstChannel ;
       UINT8  nbChannel ;
    } tuple[GSN_MAC_SUPPORTED_CHANNELS_TUPLE_MAX] ;
} GSN_MAC_SUPPORTED_CHANNELS_IE_T;


#define GSN_MAC_RAW_ASSOC_11H_IE_LEN     ( sizeof( GSN_MAC_POWER_CAPABILITY_IE ) +  \
    sizeof( GSN_MAC_SUPPORTED_CHANNELS_IE ))


/**<  WPA Key and RSN informations (WPA Extention)
*/
/**< KEY TYPE 
*/


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Key length for TKIP.
 *
 *****************************************************************************/ 


#define GSN_MAC_SEC_KEY_LEN            32  /**< TKIP keys 256 bits (max length) with MIC keys  */


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Key structured type.
 *
 *****************************************************************************/ 
 
typedef struct GSN_MAC_SEC_KEY_T
{
    UINT8 length;                 /**< Key material length */
    UINT8 array[GSN_MAC_SEC_KEY_LEN]; /**< Key material        */
} GSN_MAC_SEC_KEY_T;

/**< Descriptor values */
/**< [bit 0 1 2] Cipher suite selectors (table 2 p20) */


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Cipher suite selectors (table 2 p 20); Descriptor values [bit 0 1 2]
 * @{
 *****************************************************************************/ 


#define GSN_MAC_RSNIE_CIPHER_MASK    0x07
#define GSN_MAC_RSNIE_CIPHER_WEP40   0x01
#define GSN_MAC_RSNIE_CIPHER_TKIP    0x02
#define GSN_MAC_RSNIE_CIPHER_CCMP    0x04
#define GSN_MAC_RSNIE_CIPHER_WEP104  0x05
#define GSN_MAC_RSNIE_CIPHER_NOSEC   0xFE
#define GSN_MAC_RSNIE_CIPHER_INVALID 0xFF

/**
 *****************************************************************************
 * @}
 *****************************************************************************/ 

/**
 ***************************************************************************
 * @ingroup GsnMacDefines
 * @brief RSN Information Element field of the beacon frame (WPA Extension)
 ****************************************************************************/
 
 
#define GSN_MAC_RSN_OUI_LEN             3

/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief RSN Information Element field type for the beacon frame (WPA Extension)
 *
 *****************************************************************************/ 

typedef struct GSN_MAC_RSN_SUITE_SELECTOR_T
{
    UINT8  oui[GSN_MAC_RSN_OUI_LEN];
    UINT8  suiteType;
} GSN_MAC_RSN_SUITE_SELECTOR_T;

/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Raw RSN Information Element length
 *
 *****************************************************************************/ 

#define GSN_MAC_RAW_RSN_IE_LEN         34

/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Raw Information Element field of the beacon frame (WPA Extension)
 *
 *****************************************************************************/ 


typedef struct GSN_MAC_RAW_RSN_IE_T
{
    UINT8 data[ 2 + GSN_MAC_RAW_RSN_IE_LEN ];
} GSN_MAC_RAW_RSN_IE_T;


#define GSN_MAC_RAW_ENC_EMPTY_WIFI                                            \
{{                                                                        \
    GSN_MAC_ELTID_OUI, 0x04,                                                  \
    0x00, 0x50, 0xF2, GSN_MAC_OUI_TYPE_WPA          /* additionnal WPA OUI */ \
}}

#define GSN_MAC_RAW_ENC_WPA                                                         \
{{                                                                              \
    GSN_MAC_ELTID_OUI, 0x16,                                                        \
    0x00, 0x50, 0xF2, GSN_MAC_OUI_TYPE_WPA,     /* additionnal WPA OUI                                                     */ \
    0x01, 0x00,                             /* version                                                                 */ \
    0x00, 0x50, 0xF2, GSN_MAC_RSNIE_CIPHER_TKIP,/* group key cipher (00==none, 01=WEP40, 02==TKIP, 04==CCMP, 05==WEP104)*/    \
    0x01, 0x00,                             /* pairwise key cipher number                                              */ \
    0x00, 0x50, 0xF2, GSN_MAC_RSNIE_CIPHER_TKIP,/* pairwise key cipher (00==none, 01=WEP40, 02==TKIP, 04==CCMP, 05==WEP104)*/ \
    0x01, 0x00,                             /* authentication key management number                                    */ \
    0x00, 0x50, 0xF2, GSN_MAC_RSNIE_KEYMGT_PSK  /* authentication key management (01==802.1X auth, 02==PSK)                */ \
}}

#define GSN_MAC_RAW_ENC_WPA2                                                         \
{{                                                                               \
    GSN_MAC_ELTID_OUI, 0x16,                                                         \
    0x00, 0x50, 0xF2, GSN_MAC_OUI_TYPE_WPA,         /* additionnal WPA OUI                                                     */ \
    0x01, 0x00,                                 /* version                                                                 */ \
    0x00, 0x50, 0xF2, GSN_MAC_RSNIE_CIPHER_CCMP,    /* group key cipher    (00==none, 01=WEP40, 02==TKIP, 04==CCMP, 05==WEP104)*/ \
    0x01, 0x00,                                 /* pairwise key cipher number                                              */ \
    0x00, 0x50, 0xF2, GSN_MAC_RSNIE_CIPHER_CCMP,    /* pairwise key cipher (00==none, 01=WEP40, 02==TKIP, 04==CCMP, 05==WEP104)*/ \
    0x01, 0x00,                                 /* authentication key management number                                    */ \
    0x00, 0x50, 0xF2, GSN_MAC_RSNIE_KEYMGT_PSK      /* authentication key management (01==802.1X auth, 02==PSK)                */ \
}}

#define GSN_MAC_AUTHALGO_WIFI_OFFSET       23       /* Offset of the Authentication algorithm
                                                   byte in the WIFI WPA2 OUI            */
#define GSN_MAC_RAW_ENC_WPA_MIXED                                                            \
{{                                                                                       \
    GSN_MAC_ELTID_OUI, 0x1A,                                                               \
    0x00, 0x50, 0xF2, GSN_MAC_OUI_TYPE_WPA,         /* additionnal WPA OUI                                                     */ \
    0x01, 0x00,                                 /* version                                                                 */ \
    0x00, 0x50, 0xF2, GSN_MAC_RSNIE_CIPHER_TKIP,    /* group key cipher    (00==none, 01=WEP40, 02==TKIP, 04==CCMP, 05==WEP104)*/ \
    0x01, 0x00,                                 /* pairwise key cipher number                                              */ \
    0x00, 0x50, 0xF2, GSN_MAC_RSNIE_CIPHER_CCMP,    /* pairwise key cipher (00==none, 01=WEP40, 02==TKIP, 04==CCMP, 05==WEP104)*/ \
    0x01, 0x00,                                 /* authentication key management number                                    */ \
    0x00, 0x50, 0xF2, GSN_MAC_RSNIE_KEYMGT_PSK      /* authentication key management (01==802.1X auth, 02==PSK)                */ \
}}


#define GSN_MAC_RAW_ENC_EMPTY_IEEE                                                           \
{{                                                                                       \
    GSN_MAC_ELTID_RSN_IEEE, 0x00                                                             \
}}

#define GSN_MAC_RAW_ENC_TKIP                                                                 \
{{                                                                                       \
    GSN_MAC_ELTID_RSN_IEEE, 0x14,                                                            \
    0x01, 0x00,                                 /* version                                                                 */ \
    0x00, 0x0F, 0xAC, GSN_MAC_RSNIE_CIPHER_TKIP,    /* group key cipher    (00==none, 01=WEP40, 02==TKIP, 04==CCMP, 05==WEP104)*/ \
    0x01, 0x00,                                 /* pairwise key cipher number                                              */ \
    0x00, 0x0F, 0xAC, GSN_MAC_RSNIE_CIPHER_TKIP,    /* pairwise key cipher (00==none, 01=WEP40, 02==TKIP, 04==CCMP, 05==WEP104)*/ \
    0x01, 0x00,                                 /* authentication key management number                                    */ \
    0x00, 0x0F, 0xAC, GSN_MAC_RSNIE_KEYMGT_PSK,     /* authentication key management (01==802.1X auth, 02==PSK)                */ \
    0x00, 0x00                                  /* no pre-authentication capabilities   */                                    \
}}

#define GSN_MAC_RAW_ENC_RSN_MIXED_BCST_UCAST                                                 \
{{                                                                                       \
    GSN_MAC_ELTID_RSN_IEEE, 0x14,                                                            \
    0x01, 0x00,                                 /* version                                                                 */ \
    0x00, 0x0F, 0xAC, GSN_MAC_RSNIE_CIPHER_TKIP,    /* group key cipher    (00==none, 01=WEP40, 02==TKIP, 04==CCMP, 05==WEP104)*/ \
    0x01, 0x00,                                 /* pairwise key cipher number                                              */ \
    0x00, 0x0F, 0xAC, GSN_MAC_RSNIE_CIPHER_CCMP,    /* pairwise key cipher (00==none, 01=WEP40, 02==TKIP, 04==CCMP, 05==WEP104)*/ \
    0x01, 0x00,                                 /* authentication key management number                                    */ \
    0x00, 0x0F, 0xAC, GSN_MAC_RSNIE_KEYMGT_PSK,     /* authentication key management (01==802.1X auth, 02==PSK)                */ \
    0x00, 0x00                                  /* no pre-authentication capabilities   */                                    \
}}

#define GSN_MAC_RAW_ENC_CCMP                                                                 \
{{                                                                                       \
    GSN_MAC_ELTID_RSN_IEEE, 0x14,                                                            \
    0x01, 0x00,                                 /* version                                                                 */ \
    0x00, 0x0F, 0xAC, GSN_MAC_RSNIE_CIPHER_CCMP,    /* group key cipher    (00==none, 01=WEP40, 02==TKIP, 04==CCMP, 05==WEP104)*/ \
    0x01, 0x00,                                 /* pairwise key cipher number                                              */ \
    0x00, 0x0F, 0xAC, GSN_MAC_RSNIE_CIPHER_CCMP,    /* pairwise key cipher (00==none, 01=WEP40, 02==TKIP, 04==CCMP, 05==WEP104)*/ \
    0x01, 0x00,                                 /* authentication key management number                                    */ \
    0x00, 0x0F, 0xAC, GSN_MAC_RSNIE_KEYMGT_PSK,     /* authentication key management (01==802.1X auth, 02==PSK)                */ \
    0x00, 0x00                                  /* no pre-authentication capabilities   */                                    \
}}

#define GSN_MAC_AUTHALGO_IEEE_OFFSET       19       /* Offset of the Authentication algorithm
                                                   byte in the IEEE CCMP RSNIE          */

/**< GSN_MAC_OUI_TYPE_WME -> GSN_MAC_OUI_SUBTYPE_WME_PARAMETER */
#define GSN_MAC_RAW_WME_DEFAULT_NONE                                                         \
{{                                                                                       \
    GSN_MAC_ELTID_OUI, 0x05,                                                                 \
    0x00, 0x50, 0xF2, GSN_MAC_OUI_TYPE_WME,                                                  \
    GSN_MAC_OUI_SUBTYPE_WME_PARAMETER                                                        \
}}

#define GSN_MAC_RAW_WME_DEFAULT_b                                                            \
{{                                                                                       \
    GSN_MAC_ELTID_OUI, 0x18,                                                                 \
    0x00, 0x50, 0xF2, GSN_MAC_OUI_TYPE_WME,                                                  \
    GSN_MAC_OUI_SUBTYPE_WME_PARAMETER, 0x01,        /* OUI subtype and version            */ \
    0x00,                                       /* QoS field                          */ \
    0x00,                                       /* reserved                           */ \
    (GSN_MAC_ACI_BE<<5)|GSN_MAC_AIFSN_BE, (GSN_MAC_ECW_BE_MAX_b<<4)|GSN_MAC_ECW_BE_MIN_b, (GSN_MAC_AC_BE_TXOP_b & 0xFF),(UINT8)(GSN_MAC_AC_BE_TXOP_b>>8), \
    (GSN_MAC_ACI_BK<<5)|GSN_MAC_AIFSN_BK, (GSN_MAC_ECW_BK_MAX_b<<4)|GSN_MAC_ECW_BK_MIN_b, (GSN_MAC_AC_BK_TXOP_b & 0xFF),(UINT8)(GSN_MAC_AC_BK_TXOP_b>>8), \
    (GSN_MAC_ACI_VI<<5)|GSN_MAC_AIFSN_VI, (GSN_MAC_ECW_VI_MAX_b<<4)|GSN_MAC_ECW_VI_MIN_b, (GSN_MAC_AC_VI_TXOP_b & 0xFF),(UINT8)(GSN_MAC_AC_VI_TXOP_b>>8), \
    (GSN_MAC_ACI_VO<<5)|GSN_MAC_AIFSN_VO, (GSN_MAC_ECW_VO_MAX_b<<4)|GSN_MAC_ECW_VO_MIN_b, (GSN_MAC_AC_VO_TXOP_b & 0xFF),(UINT8)(GSN_MAC_AC_VO_TXOP_b>>8), \
}}

#define GSN_MAC_RAW_WME_DEFAULT_ag                                                           \
{{                                                                                       \
    GSN_MAC_ELTID_OUI, 0x18,                                                                 \
    0x00, 0x50, 0xF2, GSN_MAC_OUI_TYPE_WME,         /* additionnal WPA OUI                */ \
    GSN_MAC_OUI_SUBTYPE_WME_PARAMETER, 0x01,        /* OUI subtype and version            */ \
    0x00,                                       /* QoS field                          */ \
    0x00,                                       /* reserved                           */ \
    (GSN_MAC_ACI_BE<<5)|GSN_MAC_AIFSN_BE, (GSN_MAC_ECW_BE_MAX_a<<4)|GSN_MAC_ECW_BE_MIN_a, (GSN_MAC_AC_BE_TXOP_ag & 0xFF),(UINT8)(GSN_MAC_AC_BE_TXOP_ag>>8), \
    (GSN_MAC_ACI_BK<<5)|GSN_MAC_AIFSN_BK, (GSN_MAC_ECW_BK_MAX_a<<4)|GSN_MAC_ECW_BK_MIN_a, (GSN_MAC_AC_BK_TXOP_ag & 0xFF),(UINT8)(GSN_MAC_AC_BK_TXOP_ag>>8), \
    (GSN_MAC_ACI_VI<<5)|GSN_MAC_AIFSN_VI, (GSN_MAC_ECW_VI_MAX_a<<4)|GSN_MAC_ECW_VI_MIN_a, (GSN_MAC_AC_VI_TXOP_ag & 0xFF),(UINT8)(GSN_MAC_AC_VI_TXOP_ag>>8), \
    (GSN_MAC_ACI_VO<<5)|GSN_MAC_AIFSN_VO, (GSN_MAC_ECW_VO_MAX_a<<4)|GSN_MAC_ECW_VO_MIN_a, (GSN_MAC_AC_VO_TXOP_ag & 0xFF),(UINT8)(GSN_MAC_AC_VO_TXOP_ag>>8), \
}}

#define GSN_MAC_RAW_WME_DEFAULT_FOR_AP_ag                                                   \
{                                                                                       \
 /* (GSN_MAC_ACI_BE<<5)|GSN_MAC_AIFSN_BE, (GSN_MAC_ECW_BE_MIN_a<<4)|GSN_MAC_ECW_BE_MAX_a, (GSN_MAC_AC_BE_TXOP_ag & 0xFF),(UINT8)(GSN_MAC_AC_BE_TXOP_ag>>8),*/ \
    (GSN_MAC_ACI_BE<<5)|3           , ( 6<<4)|4,                              (GSN_MAC_AC_BE_TXOP_ag & 0xFF),(UINT8)(GSN_MAC_AC_BE_TXOP_ag>>8), \
    (GSN_MAC_ACI_BK<<5)|7           , (10<<4)|4,                              (GSN_MAC_AC_BK_TXOP_ag & 0xFF),(UINT8)(GSN_MAC_AC_BK_TXOP_ag>>8), \
    (GSN_MAC_ACI_VI<<5)|1           , ( 4<<4)|3,                              (GSN_MAC_AC_VI_TXOP_ag & 0xFF),(UINT8)(GSN_MAC_AC_VI_TXOP_ag>>8), \
    (GSN_MAC_ACI_VO<<5)|1           , ( 3<<4)|2,                              (GSN_MAC_AC_VO_TXOP_ag & 0xFF),(UINT8)(GSN_MAC_AC_VO_TXOP_ag>>8)  \
}

#define GSN_MAC_RAW_WME_DEFAULT_FOR_AP_b                                                    \
{                                                                                       \
 /* (GSN_MAC_ACI_BE<<5)|GSN_MAC_AIFSN_BE, (GSN_MAC_ECW_BE_MIN_a<<4)|GSN_MAC_ECW_BE_MAX_a, (GSN_MAC_AC_BE_TXOP_ag & 0xFF),(UINT8)(GSN_MAC_AC_BE_TXOP_ag>>8),*/ \
    (GSN_MAC_ACI_BE<<5)|3           , ( 7<<4)|5,                              (GSN_MAC_AC_BE_TXOP_b & 0xFF),(UINT8)(GSN_MAC_AC_BE_TXOP_b>>8), \
    (GSN_MAC_ACI_BK<<5)|7           , (10<<4)|5,                              (GSN_MAC_AC_BK_TXOP_b & 0xFF),(UINT8)(GSN_MAC_AC_BK_TXOP_b>>8), \
    (GSN_MAC_ACI_VI<<5)|1           , ( 5<<4)|4,                              (GSN_MAC_AC_VI_TXOP_b & 0xFF),(UINT8)(GSN_MAC_AC_VI_TXOP_b>>8), \
    (GSN_MAC_ACI_VO<<5)|1           , ( 4<<4)|3,                              (GSN_MAC_AC_VO_TXOP_b & 0xFF),(UINT8)(GSN_MAC_AC_VO_TXOP_b>>8), \
}


#define GSN_MAC_RAW_WME_INFO_ELMT_DEFAULT                                                    \
{{                                                                                       \
    GSN_MAC_ELTID_OUI, 0x07,                                                                 \
    0x00, 0x50, 0xF2, GSN_MAC_OUI_TYPE_WME,         /* additionnal WPA OUI                */ \
    GSN_MAC_OUI_SUBTYPE_WME_INFORMATION, 0x01,      /* OUI subtype and version            */ \
    0x00                                        /* QoS field                          */ \
}}

#define GSN_MAC_RAW_EDCA_RECORD_DEFAULT_a  (GSN_MAC_AIFSN + (((GSN_MAC_ECWMAX_a<<4)|GSN_MAC_ECWMIN_a)<<8) + ((GSN_MAC_AC_TXOP & 0xFF)<<16) + (GSN_MAC_AC_TXOP>>24))
#define GSN_MAC_RAW_EDCA_RECORD_DEFAULT_b  (GSN_MAC_AIFSN + (((GSN_MAC_ECWMAX_b<<4)|GSN_MAC_ECWMIN_b)<<8) + ((GSN_MAC_AC_TXOP & 0xFF)<<16) + (GSN_MAC_AC_TXOP>>24))

/**< SUITE SELECTOR VALUES (WPA Extention) 
*/
#define GSN_MAC_RSNIE_OUI_DEF       0x0050F2                /* WPA Default OUI value        */


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief authentication and key management suite selectors (table 1 p 20)
 * @{
 *****************************************************************************/ 

#define GSN_MAC_RSNIE_KEYMGT_8021X  1
#define GSN_MAC_RSNIE_KEYMGT_PSK    2


/**
 *****************************************************************************
 * @}
 * @ingroup GsnMACDefines
 * @brief RSNA statistics type (WPA Extension)
 *
 *****************************************************************************/ 

typedef struct GSN_MAC_RSNA_STAT_T
{
    UINT32 tkipICVErrors;
    UINT32 tkipLocalMICFailures;
    UINT32 ccmpReplays;
    UINT32 ccmpDecryptErrors;
    UINT32 tkipReplays;
} GSN_MAC_RSNA_STAT_T;



/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Mask to test for basic rate (BIT(7))
 * 
 *****************************************************************************/ 

#define GSN_MAC_BASIC_RATE      0x80         /* BIT(7) */

/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief rateset length
 * 
 *****************************************************************************/

#define GSN_MAC_RATESET_LEN       12

/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Rate set type.  
 *
 *****************************************************************************/ 
 
typedef struct GSN_MAC_RATESET_T
{
    UINT8 length;
    UINT8 array[GSN_MAC_RATESET_LEN];
} GSN_MAC_RATESET_T;




/* Preformatted rateset per station length */
#define GSN_MAC_STA_RATESET_LEN   8


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Preformatted rate set per station length
 *
 *****************************************************************************/ 

typedef struct GSN_MAC_STA_RATESET_T
{
    UINT8 array[GSN_MAC_STA_RATESET_LEN];
} GSN_MAC_STA_RATESET_T;


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief enumerated type describing the various available rates.
 *
 *****************************************************************************/ 

typedef enum GSN_MAC_RATE_T
{
    GSN_MAC_RATE_1MBPS   =   2,
    GSN_MAC_RATE_2MBPS   =   4,
    GSN_MAC_RATE_5_5MBPS =  11,
    GSN_MAC_RATE_6_5MBPS =  13,
    GSN_MAC_RATE_6MBPS   =  12,
    GSN_MAC_RATE_9MBPS   =  18,
    GSN_MAC_RATE_11MBPS  =  22,
    GSN_MAC_RATE_12MBPS  =  24,
    GSN_MAC_RATE_13MBPS  =  26,
    GSN_MAC_RATE_18MBPS  =  36,
    GSN_MAC_RATE_19_5MBPS  =  39,
    GSN_MAC_RATE_24MBPS  =  48,
    GSN_MAC_RATE_26MBPS  =  52,
    GSN_MAC_RATE_36MBPS  =  72,
    GSN_MAC_RATE_39MBPS  =  78,
    GSN_MAC_RATE_48MBPS  =  96,
    GSN_MAC_RATE_52MBPS  =  104,
    GSN_MAC_RATE_54MBPS  = 108,
    GSN_MAC_RATE_58_5MBPS  = 117,
    GSN_MAC_RATE_65MBPS  =  130
} GSN_MAC_RATE_T;

/**< TIME */
typedef UINT16 GSN_MAC_TIME_TU;
typedef UINT32 GSN_MAC_TIME_US;


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Convert time to 802.11 time units (1024 microseconds)
 *
 *****************************************************************************/ 

#define TIME_TUtoUs( MacTimeTU )   (( MacTimeTU ) * 1024 )



/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Station class flags.
 * @{
 *****************************************************************************/ 
 
                                                                     
#define GSN_MAC_STA_CLASS_MASK  0x30         /* BIT(4) | BIT(5)                             */
#define GSN_MAC_STA_CLASS1      0x00
#define GSN_MAC_STA_CLASS2      0x10         /* BIT(4)                                      */
#define GSN_MAC_STA_CLASS3      0x30         /* BIT(4) | BIT(5)                             */


/**
 *****************************************************************************
 * @}
 * @ingroup GsnMACDefines
 * @brief station power save mode
 * @{
 *****************************************************************************/ 
#define GSN_MAC_STA_PS_MODE        1
#define GSN_MAC_STA_ACTIVE         0

/**
 *****************************************************************************
 * @}
 *****************************************************************************/ 
 
/* *< MAC_BSS_PARAM */


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief MAC direct sequence channel type
 *
 *****************************************************************************/

typedef struct GSN_MAC_PHY_DS_T
{
    UINT8 dsChannel;
} GSN_MAC_PHY_DS_T;


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief MAC frequency hopping channel type
 *
 *****************************************************************************/

typedef struct GSN_MAC_PHY_FH_T
{
    UINT16 dwellTime;
    UINT8  hopSet;
    UINT8  hopPat;
    UINT8  hopIdx;
} GSN_MAC_PHY_FH_T;


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief MACC CFP type
 *
 *****************************************************************************/


typedef struct GSN_MAC_CFP_T
{
    UINT8  count;
    UINT8  period;
    UINT16 maxDuration;
    UINT16 durRemaining;
} GSN_MAC_CFP_T;

/**<
  ME_COUNTRY and ME_CHANNELS should be moved to MeDef since only the ME will use them
  However, so far, we need to send these structures to the LMAC which formats the beacon,
  so they are temporary placed in MacDef
*/


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief MACC Channel set type.
 *
 *****************************************************************************/

typedef struct GSN_MAC_CHANNELSET_T
{
    UINT8 first;
    UINT8 nbr;
    UINT8 maxTxPower;
} GSN_MAC_CHANNELSET_T;


#define GSN_MAC_MAX_CHANNELSET_PER_COUNTRY       3


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Country type (describing the channels available in a jurisdiction)
 *
 *****************************************************************************/


typedef struct GSN_MAC_COUNTRY_T
{
    WLAN_BOOLEAN dot11MultiDomainCapabilityEnabled;
    UINT8 string[3]; /* 2 first bytes described in http://en.wikipedia.org/wiki/ISO_3166-1 */
    UINT8 nbrChanSet;
    GSN_MAC_CHANNELSET_T chanSet[GSN_MAC_MAX_CHANNELSET_PER_COUNTRY];
} GSN_MAC_COUNTRY_T;


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Transmit power settings type.
 *
 *****************************************************************************/

typedef struct GSN_MAC_TXPOWERSET_T
{
    UINT8 length;
    UINT8 array[8];
} GSN_MAC_TXPOWERSET_T;


#define GSN_MAC_MAX_CHANNELDOMAIN_BG 14
#define GSN_MAC_MAX_CHANNELDOMAIN_A  40



/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Channel domain type
 *
 *****************************************************************************/

typedef struct GSN_MAC_CHANNELDOMAIN_T
{
    UINT8 length;
    UINT8 array[GSN_MAC_MAX_CHANNELDOMAIN_A];
} GSN_MAC_CHANNELDOMAIN_T;



/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Channel domain definitions
 * @{
 *****************************************************************************/

#define GSN_MAC_CHANNELDOMAIN_X10_24GHZ /* FCC    */ {11, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11}}
#define GSN_MAC_CHANNELDOMAIN_X10_5GHZ  /* FCC    */ {12, {36, 40, 44, 48, 52, 56, 60, 64, 149, 153, 157, 161}}
#define GSN_MAC_CHANNELDOMAIN_X20    /* IC     */ {11, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11}}
#define GSN_MAC_CHANNELDOMAIN_X30    /* ETSI   */ {13, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13}}
#define GSN_MAC_CHANNELDOMAIN_X31    /* Spain  */ {2,  {10, 11}}
#define GSN_MAC_CHANNELDOMAIN_X32    /* France */ {4,  {10, 11, 12, 13}}
#define GSN_MAC_CHANNELDOMAIN_X40    /* MKK    */ {1,  {14}}
#define GSN_MAC_CHANNELDOMAIN_X41    /* Japan  */ {24, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 240, 244, 248, 252, 8, 12, 16, 34, 38, 42, 46}}

#define GSN_MAC_CHANNELDOMAIN_24_ONLY             {14, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14}}
//#define GSN_MAC_CHANNELDOMAIN_5_ONLY              {12, {36, 40, 44, 48, 52, 56, 60, 64, 149, 153, 157, 161}}
#define GSN_MAC_CHANNELDOMAIN_5_ONLY              {33, { 7,  8, 11, 12, 16, 36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 149, 153, 157, 161, 183, 184, 188, 192, 196 }}

#define GSN_MAC_MAX_RAWCHANNELDOMAIN (1 + 1 + 3 + 3*3)   /* ID + len + string + channel     */


/**
 *****************************************************************************
 * @}
 * @ingroup GsnMACDefines
 * @brief Channel raw channel domain type
 *****************************************************************************/ 


typedef struct GSN_MAC_RAWCHANNELDOMAIN_T
{
    UINT8 Length;
    UINT8 Array[GSN_MAC_MAX_RAWCHANNELDOMAIN];
} GSN_MAC_RAWCHANNELDOMAIN_T;

/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Channel raw channel domain entries
 * @{
 *****************************************************************************/

/* 2 first bytes described in http://en.wikipedia.org/wiki/ISO_3166-1                   */
#define GSN_MAC_RAWCHANNELDOMAIN_EMPTY /* EMPTY  */ {3, GSN_MAC_ELTID_COUNTRY, 0}
#define GSN_MAC_RAWCHANNELDOMAIN_X10_24GHZ   /* FCC    */ {8, GSN_MAC_ELTID_COUNTRY, 6, 'U', 'S', ' ', 1, 11, 10}
#define GSN_MAC_RAWCHANNELDOMAIN_X10_5GHZ   /* FCC    */  {8, GSN_MAC_ELTID_COUNTRY, 6, 'U', 'S', ' ',36,  7, 10}
#define GSN_MAC_RAWCHANNELDOMAIN_X20   /* IC     */ {8, GSN_MAC_ELTID_COUNTRY, 6, ' ', ' ', ' ', 1, 11, 10}
#define GSN_MAC_RAWCHANNELDOMAIN_X30   /* ETSI   */ {8, GSN_MAC_ELTID_COUNTRY, 6, ' ', ' ', ' ', 1, 13, 10}
#define GSN_MAC_RAWCHANNELDOMAIN_X31   /* Spain  */ {8, GSN_MAC_ELTID_COUNTRY, 6, 'E', 'S', ' ', 10, 1, 10}
#define GSN_MAC_RAWCHANNELDOMAIN_X32   /* France */ {8, GSN_MAC_ELTID_COUNTRY, 6, 'F', 'R', ' ', 10, 4, 10}
#define GSN_MAC_RAWCHANNELDOMAIN_X40   /* MKK    */ {8, GSN_MAC_ELTID_COUNTRY, 6, ' ', ' ', ' ', 14, 1, 10}
#define GSN_MAC_RAWCHANNELDOMAIN_X41   /* Japan  */ {8, GSN_MAC_ELTID_COUNTRY, 6, 'J', 'P', ' ', 1, 13, 10}

#define GSN_MAC_MAX_PMKIDLIST               80
typedef struct GSN_MAC_PMKIDLIST_T

{
    UINT16 PmkIdCount;
    UINT8 Array[GSN_MAC_MAX_PMKIDLIST];
} GSN_MAC_PMKIDLIST_T;
/**
 *****************************************************************************
 * @}
 *****************************************************************************/



/* *< MAC_SCAN_PARAM */

/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Scan type.  
 *
 *****************************************************************************/
typedef enum GSN_MAC_SCAN_TYPE
{
    GSN_MAC_SCAN_TYPE_PASSIVE = 0,      /**< passive scan */
    GSN_MAC_SCAN_TYPE_ACTIVE,           /**< active scan */
    GSN_MAC_SCAN_TYPE_P2P_ONLY,         /**< scan for p2p devices only */
    GSN_MAC_SCAN_TYPE_P2P_DEVTYPE,      /**< scan for given p2p device type */
    GSN_MAC_SCAN_TYPE_P2P_DEVID,        /**< scan for given p2p device Id */
    GSN_MAC_SCAN_TYPE_WLAN_AND_P2PGRPS, /**< scan for wlan and p2p groups */
    GSN_MAC_SCAN_TYPE_WLAN_AND_P2PDEVS, /**< scan for wlan and p2p devices */
} GSN_MAC_SCAN_TYPE_T;


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Scan parameter type.  
 *
 *****************************************************************************/


typedef struct GSN_MAC_SCAN_PARAM_T
{
    UINT8            bssType;        /**< BSSType                         */
    GSN_MAC_ADDR_T   bssid;          /**< BSSID - 0xFF...FF for broadcast */
    GSN_MAC_SSID_T   ssid;           /**< SSID - up to 32 bytes           */
    UINT8            scanType;       /**< Scan Type (active or passive)   */
    UINT32           probeDelay;     /**< Probe delay                     */
    UINT8            scanChannel;    /**< Channel                         */
    UINT8            maxTxPower;     /**< Max Tx Power on that channel    */
    GSN_MAC_TIME_TU  minChannelTime; /**< Min Channel time                */
    GSN_MAC_TIME_TU  maxChannelTime; /**< Max Channel time                */
} MAC_SCAN_PARAM_T;

/**< FRAME type
 */

#ifdef GS1010
#define GSN_MAC_FRAME_LEN                300
#else
#define GSN_MAC_FRAME_LEN                512
#endif


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief MAC frame type.
 *
 *****************************************************************************/


typedef struct GSN_MAC_FRAME_T
{
    UINT8 array[GSN_MAC_FRAME_LEN];
} GSN_MAC_FRAME_T;

#define GSN_MAC_ASSOC_FRAME_LEN           80



/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Association frame type.
 *
 *****************************************************************************/


typedef struct GSN_MAC_ASSOC_FRAME_T
{
    UINT8  length;
    UINT16 frameType;
    UINT8  arraySize;
    UINT8  array[GSN_MAC_ASSOC_FRAME_LEN];
} GSN_MAC_ASSOC_FRAME_T;


#define GSN_MAC_WMM_FRAME_LEN           32


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Wireless management frame type.
 *
 *****************************************************************************/


typedef struct GSN_MAC_WMM_FRAME_T
{
    UINT8  array[GSN_MAC_WMM_FRAME_LEN];
} GSN_MAC_WMM_FRAME_T;

#define GSN_MAC_WPA_FRAME_LEN           32


/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief WPA frame type.
 *
 *****************************************************************************/
 
typedef struct GSN_MAC_WPA_FRAME_T
{
    UINT8  array[GSN_MAC_WPA_FRAME_LEN];
} GSN_MAC_WPA_FRAME_T;


#define GSN_MAC_PROPRIETARY_INFO_LEN    250

/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Proprietary information frame type.
 *
 *****************************************************************************/
 
typedef struct GSN_MAC_PROPRIETARY_INFO_T
{
    UINT8 length;
    UINT8 array[GSN_MAC_PROPRIETARY_INFO_LEN];
} GSN_MAC_PROPRIETARY_INFO_T;

/* *< MAC_PUBLIC_HDR
 */
 
/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Public header type.
 *
 *****************************************************************************/ 
 
typedef struct GSN_MAC_PUBLIC_HDR_T
{
    GSN_MAC_ADDR_T srcAddr;
    GSN_MAC_ADDR_T destAddr;
    GSN_MAC_ADDR_T bssid;

    UINT16   frameCtl;

    /**< For TX only */
    UINT16   ackTaskId; /* UINT16: KE_TASK_ID */

    /**< For RX only */
    UINT8    rssi;
    UINT8    channel;
    UINT8    rxRate;
} GSN_MAC_PUBLIC_HDR_T;



/* *< BSS_ELMT structure */

/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief BSS element values.
 * @{
 *****************************************************************************/
#define GSN_MAC_BSS_VALID                0x01
#define GSN_MAC_AUTHENTICATED            0x02
#define GSN_MAC_ASSOCIATED               0x04

#define GSN_MAC_SCAN_MARKED              0x80



/**
 *****************************************************************************
 * @}
 * @ingroup GsnMACDefines
 * @brief MAC BSS element type
 *
 *****************************************************************************/



typedef struct GSN_MAC_BSS_ELMT_T
{
    GSN_MAC_ADDR_T   bssid;
    UINT16           macFrameLen;
    GSN_MAC_FRAME_T  macFrame;
    UINT8            staFlags;
    INT8             rssi;
    INT8             wewRssi;
    UINT8            channel;
    UINT8            receptionChannel;
    UINT8            phyType;
    UINT8            encryptionStatus;
} GSN_MAC_BSS_ELMT_T;



/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief MAC BSS information type.
 *
 *****************************************************************************/


typedef struct GSN_MAC_BSS_INFO_T
{
    GSN_MAC_ADDR_T    bssid;
    GSN_MAC_ADDR_T    macAddr;

    UINT16            beaconPeriod;
    UINT16            capaInfo;
    GSN_MAC_SSID_T    ssid;
    GSN_MAC_RATESET_T supRates;
    UINT8             phyType;  /**< GSN_MAC_ELTID_DS or GSN_MAC_ELTID_FH  */
    GSN_MAC_PHY_FH_T  fh;
    GSN_MAC_CFP_T     cfp;
    UINT16            atimWindow;
    UINT8             dtimPeriod;

    UINT8             channel;
    UINT8             ERPStatus;
    WLAN_BOOLEAN      WmeCapability;
    GSN_MAC_WMM_FRAME_T  WmmFrame;
//    GSN_MAC_RAW_RSN_IE RsnieRaw;
} GSN_MAC_BSS_INFO_T;

/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief TBTT Error information type.
 *
 *****************************************************************************/
typedef struct GSN_MAC_TBTT_ERROR_INFO
{
    INT32   tbttError; /**< TBTT error in microseconds, this is signed */
    ULONG64 tbttErrorInterval; /**< Interval over which error was calculated.
                                    This gives correct interval only when the
                                    system is awake (sleep,deep-sleep are fine)
                                    but not when system goes to standby in
                                    between. */
    ULONG64 beaconTimestamp; /**< timestamp in the received beacon (microseconds) */
    UINT32  beaconInterval;  /**< beacon interval in TUs (1TU=1024us) of current WLAN */
    ULONG64 tbttErrorUpdateTime; /**< RTC time at which TBTT error was computed */
    ULONG64 tbttSta; /**< tbttSta is the estimated TBTT programmed for radio
                            wakeup for receiving beacon; Upon receiving the beacon,
                            the TBTT error info is updated and AFW signaled. */

} GSN_MAC_TBTT_ERROR_INFO_T;

/* *<
 The structure MAC_MIB_ELMT_UNION contains all the type available from the MIB
   interface. This allow to check the size of the maximum element stored within the
   MIB [sizeof(MAC_MIB_ELMT_UNION)]
 */
 
 /**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Available MIB types.
 *
 * The structure MAC_MIB_ELMT_UNION contains all the types available from the MIB
 * interface. This allows us to check the size of the maximum element stored within the
 * MIB [sizeof(MAC_MIB_ELMT_UNION)].
 *
 *****************************************************************************/

typedef union GSN_MAC_MIB_ELMT_UNION_T
{
    UINT8                        elmtU8;
    INT8                         elmtS8;
    UINT16                       elmtU16;
    UINT32                       elmtU32;
    ULONG64                       elmtU64;
    WLAN_BOOLEAN                 elmt_BOOLEAN;
    GSN_MAC_ADDR_T               elmtMAC_ADDR;
    GSN_MAC_SSID_T               elmtMAC_SSID;
    GSN_MAC_RATESET_T            elmtMAC_RATESET;
    GSN_MAC_STA_RATESET_T        elmtMAC_STA_RATESET;
    GSN_MAC_CHANNELSET_T         elmtMAC_CHANNELSET;
    GSN_MAC_CHANNELDOMAIN_T      elmtMAC_CHANNELDOMAIN;
    GSN_MAC_SEC_KEY_T            elmtMAC_SEC_KEY;
    GSN_MAC_RSNA_STAT_T          elmtMAC_RSNA_STAT;
    GSN_MAC_ASSOC_FRAME_T        elmtMAC_ASSOC_FRAME;
    GSN_MAC_RAWCHANNELDOMAIN_T   elmtMAC_RAWCHANNELDOMAIN;
    GSN_MAC_PHY_CHANNEL_T        elmtMAC_PHY_CHANNEL;
    INT16                        elmtS16;
    GSN_MAC_TBTT_ERROR_INFO_T    elmtMAC_TBTT_ERROR_INFO;
    GSN_MAC_PROPRIETARY_INFO_T      elmtMAC_PROP_INFO; 
} GSN_MAC_MIB_ELMT_UNION_T;


/**< Slot duration for different PHY */

 /**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief Slot duration for different PHY types.
 * @{
 *****************************************************************************/


#define GSN_MAC_SLOTTIME_LONG                 20
#define GSN_MAC_SLOTTIME_SHORT                 9


/**
 *****************************************************************************
 * @}
 * @ingroup GsnMACDefines
 * @brief Enumeration of protection modes for 802.11g operation
 *
 *  These modes define how a g station protects its transmissions
 *  against interference by b stations that can't hear a native
 *  OFDM transmission.
 *
 *****************************************************************************/

typedef enum
{
    GSN_MAC_PROTECT_NONE          = 0,
    GSN_MAC_PROTECT_CTS_TO_SELF,
    GSN_MAC_PROTECT_RTS_CTS
} GSN_MAC_PROTECT_MODE_T;

/* *< RSSI and antenna diversity */

 /**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief antenna diversity / RSSI defines.
 *
 * RSSI (Received Signal Strength Indication) can be used to choose
 * the antenna with the best signal strength for a given frame or series
 * of frames. 
 * @{
 *
 *****************************************************************************/

#define GSN_MAC_SET_RSSI_ANTENNA( my_rssi, my_antenna ) \
    ( ( my_antenna << 7 ) | ( my_rssi & ( ~0x80 )))

#define GSN_MAC_GET_RSSI(rssi) (rssi | 0x80)
#define GSN_MAC_GET_ANTENNA(rssi) ((rssi & 0x80)?1:0)



/**
 *****************************************************************************
 * @}
 * @ingroup GsnMACDefines
 * @brief Antenna diversity operating modes.
 *
 *****************************************************************************/

typedef enum
{
    GSN_MAC_DIVERSITY_ANTENNA0_ONLY  = 0,
    GSN_MAC_DIVERSITY_ANTENNA1_ONLY,
    GSN_MAC_DIVERSITY_ALWAYS_TOGGLING,
    GSN_MAC_DIVERSITY_FOR_AP = 3,           /* Antenna diversity for AP only        */
    GSN_MAC_DIVERSITY_ALGO_START = 4,       /* Mesure PER on current antenna        */
    GSN_MAC_DIVERSITY_ALGO_MESURE_OTHER,    /* Mesure PER on the other antenna      */
    GSN_MAC_DIVERSITY_ALGO_LOCK_ON_BEST     /* Stay on the best antenna for a while */
} GSN_MAC_DIVERSITY_MODE_T;



/**
 *******************************************************************************
 * @ingroup GsnMACDefines
 * @brief WPS attribute types.
 *      This enum defines the WPS attribute type values.
 ******************************************************************************/
typedef enum GSN_MAC_WPS_ATTR {
	GSN_MAC_WPS_ATTR_AP_CHANNEL = 0x1001,
	GSN_MAC_WPS_ATTR_ASSOC_STATE = 0x1002,
	GSN_MAC_WPS_ATTR_AUTH_TYPE = 0x1003,
	GSN_MAC_WPS_ATTR_AUTH_TYPE_FLAGS = 0x1004,
	GSN_MAC_WPS_ATTR_AUTHENTICATOR = 0x1005,
	GSN_MAC_WPS_ATTR_CONFIG_METHODS = 0x1008,
	GSN_MAC_WPS_ATTR_CONFIG_ERROR = 0x1009,
	GSN_MAC_WPS_ATTR_CONFIRM_URL4 = 0x100a,
	GSN_MAC_WPS_ATTR_CONFIRM_URL6 = 0x100b,
	GSN_MAC_WPS_ATTR_CONN_TYPE = 0x100c,
	GSN_MAC_WPS_ATTR_CONN_TYPE_FLAGS = 0x100d,
	GSN_MAC_WPS_ATTR_CRED = 0x100e,
	GSN_MAC_WPS_ATTR_ENCR_TYPE = 0x100f,
	GSN_MAC_WPS_ATTR_ENCR_TYPE_FLAGS = 0x1010,
	GSN_MAC_WPS_ATTR_DEV_NAME = 0x1011,
	GSN_MAC_WPS_ATTR_DEV_PASSWORD_ID = 0x1012,
	GSN_MAC_WPS_ATTR_E_HASH1 = 0x1014,
	GSN_MAC_WPS_ATTR_E_HASH2 = 0x1015,
	GSN_MAC_WPS_ATTR_E_SNONCE1 = 0x1016,
	GSN_MAC_WPS_ATTR_E_SNONCE2 = 0x1017,
	GSN_MAC_WPS_ATTR_ENCR_SETTINGS = 0x1018,
	GSN_MAC_WPS_ATTR_ENROLLEE_NONCE = 0x101a,
	GSN_MAC_WPS_ATTR_FEATURE_ID = 0x101b,
	GSN_MAC_WPS_ATTR_IDENTITY = 0x101c,
	GSN_MAC_WPS_ATTR_IDENTITY_PROOF = 0x101d,
	GSN_MAC_WPS_ATTR_KEY_WRAP_AUTH = 0x101e,
	GSN_MAC_WPS_ATTR_KEY_ID = 0x101f,
	GSN_MAC_WPS_ATTR_MAC_ADDR = 0x1020,
	GSN_MAC_WPS_ATTR_MANUFACTURER = 0x1021,
	GSN_MAC_WPS_ATTR_MSG_TYPE = 0x1022,
	GSN_MAC_WPS_ATTR_MODEL_NAME = 0x1023,
	GSN_MAC_WPS_ATTR_MODEL_NUMBER = 0x1024,
	GSN_MAC_WPS_ATTR_NETWORK_INDEX = 0x1026,
	GSN_MAC_WPS_ATTR_NETWORK_KEY = 0x1027,
	GSN_MAC_WPS_ATTR_NETWORK_KEY_INDEX = 0x1028,
	GSN_MAC_WPS_ATTR_NEW_DEVICE_NAME = 0x1029,
	GSN_MAC_WPS_ATTR_NEW_PASSWORD = 0x102a,
	GSN_MAC_WPS_ATTR_OOB_DEVICE_PASSWORD = 0x102c,
	GSN_MAC_WPS_ATTR_OS_VERSION = 0x102d,
	GSN_MAC_WPS_ATTR_POWER_LEVEL = 0x102f,
	GSN_MAC_WPS_ATTR_PSK_CURRENT = 0x1030,
	GSN_MAC_WPS_ATTR_PSK_MAX = 0x1031,
	GSN_MAC_WPS_ATTR_PUBLIC_KEY = 0x1032,
	GSN_MAC_WPS_ATTR_RADIO_ENABLE = 0x1033,
	GSN_MAC_WPS_ATTR_REBOOT = 0x1034,
	GSN_MAC_WPS_ATTR_REGISTRAR_CURRENT = 0x1035,
	GSN_MAC_WPS_ATTR_REGISTRAR_ESTABLISHED = 0x1036,
	GSN_MAC_WPS_ATTR_REGISTRAR_LIST = 0x1037,
	GSN_MAC_WPS_ATTR_REGISTRAR_MAX = 0x1038,
	GSN_MAC_WPS_ATTR_REGISTRAR_NONCE = 0x1039,
	GSN_MAC_WPS_ATTR_REQUEST_TYPE = 0x103a,
	GSN_MAC_WPS_ATTR_RESPONSE_TYPE = 0x103b,
	GSN_MAC_WPS_ATTR_RF_BANDS = 0x103c,
	GSN_MAC_WPS_ATTR_R_HASH1 = 0x103d,
	GSN_MAC_WPS_ATTR_R_HASH2 = 0x103e,
	GSN_MAC_WPS_ATTR_R_SNONCE1 = 0x103f,
	GSN_MAC_WPS_ATTR_R_SNONCE2 = 0x1040,
	GSN_MAC_WPS_ATTR_SELECTED_REGISTRAR = 0x1041,
	GSN_MAC_WPS_ATTR_SERIAL_NUMBER = 0x1042,
	GSN_MAC_WPS_ATTR_WPS_STATE = 0x1044,
	GSN_MAC_WPS_ATTR_SSID = 0x1045,
	GSN_MAC_WPS_ATTR_TOTAL_NETWORKS = 0x1046,
	GSN_MAC_WPS_ATTR_UUID_E = 0x1047,
	GSN_MAC_WPS_ATTR_UUID_R = 0x1048,
	GSN_MAC_WPS_ATTR_VENDOR_EXT = 0x1049,
	GSN_MAC_WPS_ATTR_VERSION = 0x104a,
	GSN_MAC_WPS_ATTR_X509_CERT_REQ = 0x104b,
	GSN_MAC_WPS_ATTR_X509_CERT = 0x104c,
	GSN_MAC_WPS_ATTR_EAP_IDENTITY = 0x104d,
	GSN_MAC_WPS_ATTR_MSG_COUNTER = 0x104e,
	GSN_MAC_WPS_ATTR_PUBKEY_HASH = 0x104f,
	GSN_MAC_WPS_ATTR_REKEY_KEY = 0x1050,
	GSN_MAC_WPS_ATTR_KEY_LIFETIME = 0x1051,
	GSN_MAC_WPS_ATTR_PERMITTED_CFG_METHODS = 0x1052,
	GSN_MAC_WPS_ATTR_SELECTED_REGISTRAR_CONFIG_METHODS = 0x1053,
	GSN_MAC_WPS_ATTR_PRIMARY_DEV_TYPE = 0x1054,
	GSN_MAC_WPS_ATTR_SECONDARY_DEV_TYP_ELIST = 0x1055,
	GSN_MAC_WPS_ATTR_PORTABLE_DEV = 0x1056,
	GSN_MAC_WPS_ATTR_AP_SETUP_LOCKED = 0x1057,
	GSN_MAC_WPS_ATTR_APPLICATION_EXT = 0x1058,
	GSN_MAC_WPS_ATTR_EAP_TYPE = 0x1059,
	GSN_MAC_WPS_ATTR_IV = 0x1060,
	GSN_MAC_WPS_ATTR_KEY_PROVIDED_AUTO = 0x1061,
	GSN_MAC_WPS_ATTR_802_1X_ENABLED = 0x1062,
	GSN_MAC_WPS_ATTR_APPSESSIONKEY = 0x1063,
	GSN_MAC_WPS_ATTR_WEPTRANSMITKEY = 0x1064
} GSN_MAC_WPS_ATTR_T;


/**
 *******************************************************************************
 * @ingroup GsnMACDefines
 * @brief WPS attributes.
 *      This structure contains relevant WPS attributes extracted from WPS IE.
 ******************************************************************************/
typedef struct GSN_MAC_WPS_IE_ATTR
{
    BOOL    selectedRegistar;
    UINT16  selectedRegistarConfigMethod;
    UINT16  devicePasswordId;
} GSN_MAC_WPS_IE_ATTR_T;



/**
 *****************************************************************************
 * @ingroup GsnMACDefines
 * @brief utility to copy a security key to a new memory location.
 *
 *****************************************************************************/

INLINE  void GSN_MAC_KEY_CPY( GSN_MAC_SEC_KEY_T *const macKeyPtr,
    const GSN_MAC_SEC_KEY_T *const srcKeyPtr)
{
    memcpy(( macKeyPtr )->array, ( srcKeyPtr )->array, 
        ( size_t )(( srcKeyPtr)->length ));
    macKeyPtr->length = srcKeyPtr->length;
}

#ifdef __cplusplus
}
#endif
#endif


