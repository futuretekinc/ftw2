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
* $RCSfile: s2w_hal.h,v $
*
* Description : This file defines the function prototypes of the HAL functions.
*****************************************************************************/

#ifndef FTW_HAL_H
#define FTW_HAL_H

/** Link state */
typedef enum
{
    FTW_LINK_STATE_DISCONNECTED,
    FTW_LINK_STATE_CONNECTED,
} FTW_LINK_STATE_T;

typedef struct FTW_SCAN_INFO
{
    GSN_WLAN_MAC_SSID_T  apMacAddr; /**< Mac Address */
    UINT8   rssi;               /**< rssi */
    UINT8   channel;          /**< channel number */
    GSN_WLAN_MAC_SSID_T ssid;    /**< ssid */
    UINT8   nwType;         /**< nw type - BSS / IBSS */         
    INT8 security[20]; /* this is related to web prov module. As of now can have
                    value 0-4, 0 -open, 1-wep, 2 - psk, 3 - enterprise.....*/
}FTW_SCAN_INFO_T;


/* structure defines the parameter for ping
 */
typedef struct PING_PARMS
{
    INT32 pingSock;
    INT8  pingHost[4];
    INT8  pingIP[20];
    INT32 pingIntvl;
    INT32 pingDataLen;
    INT32 pingNumOfTrials;
    INT32 pingTrailCnt;
    INT32 pingResponse;
    INT32 pingRecvCnt;
    INT32 pingttl;
	INT8  payload[16];
}PING_PARMS_T;


/**
 * @defgroup hal Hardware Abstraction Layer
 * @ingroup platform
 */

/** @addtogroup hal */
/** @{ */

/**
 * Configure wireless encryption mode and keys.
 *
 * @param params parameters of the encryption required
 * @return FTW_SUCCESS on success, FTW_FAILURE or specific error code on
 * failure.  FTW_ENOTSUP for unsupported modes.
 *
 * @see FTW_SECURIRTY_T
 */
UINT8 s2w_hal_config_security(FTW_SECURITY_T *params);

/**
 * Configure the TCP/IP network.
 * @param params Pointer to a structure of typre s2w_netconf_t,
 *               which contains the IP address, net mask, default gateway and
 *               the dns server address.
 * @return result, FTW_SUCCESS on success and FTW_FAILURE on failure.
 */
UINT8 AppS2wHal_NetworkConfig(FTW_NETCONF_T *params);

/**
 * This function configures the s2w default host name.
 * @param params - IN the address of the node host name.
 */
PUBLIC void
AppS2wHal_DefaultHostNameSet(UINT8 *hostName);

/**
 * Get the RSSI.
 * @return RSSI in dBm
 */
PUBLIC INT8 AppS2wHal_RssiGet(void);

/**
 * Get the current transmit rate.
 * @return Current Transmit rate in Mbps.
 */
UINT32 AppS2wHal_TxRateGet(void);

/**
 * Set the WiFi transmit power.
 * @param power Power in dBm.
 * @return result, FTW_SUCCESS on success, FTW_FAILURE on failure and
 *         FTW_EINVAL if the data in invalid.
 */
UINT8 AppS2wHal_TxPowerSet(UINT32 power);

/**
 * Set the Wireless retry count.
 * @param count Retry count.
 * @return result, FTW_SUCCESS on success and FTW_FAILURE on failure.
 */
//UINT8 AppS2wHal_RetryCountSet(UINT32 count);

/** Flag to indicate the Auto connect mode field is changed. */
#define FTW_HAL_FLASH_CHANGED_AUTOCONNECT       0x0001
/** Flag to indicate Default profile id is changed. */
#define FTW_HAL_FLASH_CHANGED_DEFAULT_PROFILE   0x0002
/** Flag to indicate Profile 0 is changed. */
#define FTW_HAL_FLASH_CHANGED_PROFILE_0         0x0004
/** Flag to indicate Profile 1 is changed. */
#define FTW_HAL_FLASH_CHANGED_PROFILE_1         0x0008

/*SPI slave used for S2W application interface  */
#define FTW_DEFAULT_SPI_NUMBER       GSN_SPI_NUM_2 


/*SPI#1 chip select pin  */
#define FTW_DEFAULT_SPI_CS_0
//#define FTW_DEFAULT_SPI_CS_1
//#define FTW_DEFAULT_SPI_CS_2
//#define FTW_DEFAULT_SPI_CS_3

/* Fast SPI slave FIFO threshold for S2W application (SPI#3 can have max FIFO size 64)
*/
#define FTW_SPI_FS_RX_THRESHOLD_DEFAULT  8
#define FTW_SPI_FS_TX_THRESHOLD_DEFAULT  32

/*  SPI slave FIFO threshold for S2W application (SPI#1 and SPI#2 can have maximum FIFO threshold 8)
*/
#define FTW_SPI_RX_THRESHOLD_DEFAULT      4
#define FTW_SPI_TX_THRESHOLD_DEFAULT      4

/*  SPI bulk transfer limits
*/
#define FTW_SPI_FS_MAX_BURST_TRANSFER_SIZE  1400
#define FTW_SPI_FS_MAX_BULK_READ_SIZE       500


#define FTW_DEFAULT_KEEP_ALIVE_INTRVL 45
/**
 * Read the profiles from the flash
 * @return Pointer to the structure of type FTW_FLASH_PARAMS_T on success
 *         and NULL on failure.
 */
FTW_FLASH_PARAMS_T *AppS2wHal_FlashRead(void);

FTW_PROFILE_PARAMS_T*
S2w_ProfileParamInRTCPtrGet(void);


FTW_FLASH_PARAMS_T*
S2w_FlashParamInRTCPtrGet(void);

void
S2w_macAddrRTCGet(UINT8* mac);


VOID
S2w_macAddrRTCSet(UINT8* mac);
void
AppS2wHal_RTCRead(void);

VOID 
AppS2w_ExitDpSleep();



/**
 * @brief Set 802.11 power save mode.
 * @param  mode Power save mode to be set, 0: disable, 1: Enable.
 * @return status, FTW_SUCCESS on success, FTW_ENOTSUP if
 *         feature is not supported, FTW_FAILURE on failure.
 *
 */
UINT8 FTW_PS_modeSet(UINT8 bMode);

/**
 * @brief Set 802.11 radio mode.
 * @param mode Radio mode, 0 to Disable and 1 to enable.
 *
 * @return FTW_SUCCESS on success, FTW_FAILURE on failure, FTW_ENOTSUP if it is
 *         not supported.
 */
UINT8 AppS2wHal_RadioModeConfig(UINT8 mode);


/**
 * @brief Execute the power save deep-sleep command
 * @param data Pointer to the buffer which contains the power save command.
 * @result status.
 */
//UINT8 AppS2wHal_PsDpSleepStart(UINT32 timeout);

/**
 * @brief Execute the power save standby command
 * @param data Pointer to the buffer which contains the power save command.
 * @result status.
 */
UINT8 AppS2wHal_PsStbyRequest(ULONG64 val,UINT32 dtime, FTW_ALARM_INFO_T* data);

UINT8 AppS2wHal_NwContextStore();

UINT8 s2w_hal_handle_restore_cmd();
/**
 * @brief Set the MAC address.
 * @param mac_addr MAC address to be set.
 *
 * @return FTW_SUCCESS on success, FTW_FAILURE on failure
 */
UINT8 s2w_hal_config_mac(UINT8 *mac_addr);

UINT8 FTW_PS_pollIntervelSet(UINT32 interval);


PUBLIC BOOL
S2wUart_TxStatusGet();

PUBLIC VOID
AppS2wHal_Register(GSN_NOTIFICATION_FUNC_T notifier, VOID *context);

UINT8 
AppS2wHal_RadioModeConfig(UINT8 mode);

PUBLIC VOID
AppS2wHal_AppEntry (UINT32 bootInfo);

UINT8 AppS2wHal_NstatGet(FTW_STATUS_INFO_T* statusInfo);

UINT8 AppS2wHal_SyncLossIntrvlSet(UINT32 interval);

UINT8 AppS2wHal_McastRecvSet(UINT8 set);

PUBLIC UINT8
AppS2wHal_WpaPskCompute(FTW_WPAPSK_T* wpaPsk );

PUBLIC UINT8
AppS2wParse_Psk(UINT8 *temp, UINT8 *psk);

UINT8 AppS2wHal_PskKeyStore(UINT8* psk);
/** @} */

UINT8 AppS2wHal_InfoGet(FTW_WLANINFO_T *info);

UINT8
AppS2wHal_PsDpSleepStart(UINT32 timeout, FTW_ALARM_INFO_T* data, UINT8 pwrMeasure);

VOID
AppS2w_GpioWkUpDisable();

PUBLIC VOID
AppS2wHal_Cm3ClkCfg();
PUBLIC VOID
AppS2w_ProfileInit(VOID);
VOID
AppS2wHal_MdnsInit(UINT8 *ptr);
PUBLIC UINT8
AppS2wCmd_MdnsAnnounceAll(UINT8 *ptr);
UINT8
AppS2wProcess_NcmAutoConnectL4Connect();
#ifdef FTW_DNS_SERVER_ENABLE

VOID S2wDnsConfigGet(GSN_DNS_INIT_PARAM_T *gsnDnsInitParams);
#endif
PUBLIC VOID
AppS2wProcess_DhcpIpChangeNotify();
 PUBLIC VOID
 AppS2wProcess_DhcpStop();
PUBLIC VOID
AppS2wProcess_IpConflict();


 
VOID
s2wPingStart();
VOID
s2wPingStop();
VOID
s2wDisassocCb(VOID *ctx,GSN_WDD_DISASSOCIATION_CB_INFO *pDisAssocInfo);
VOID
s2wDisassocSyncLossCb(VOID *ctx,UINT32 missBeacon);

PUBLIC VOID
AppArp_Invalidate();
VOID 
GratiousArpHandler(NX_IP *ip_ptr,NX_PACKET *packet_ptr);
PUBLIC UINT8
AppS2wHal_NwContextRestore();
UINT8 
AppS2wHal_IeeePSConfig(UINT8 mode);

PUBLIC VOID
AppS2w_PingTaskNotify(INT32 msg);

VOID
s2wSpiFs_Flush();
VOID
AppS2wHal_TcpSrvMaxConSet(UINT8 cid,UINT32 maxCon);

#ifdef FTW_RF_TEST
extern GSN_OSAL_SEM_T s2wWlanOpSyncSem;
#endif

#endif

#if defined(FTW_SSL_CLIENT_SUPPORT)
UINT8
AppS2wHal_HttpCheckDns(UINT8 *reqPath);
#endif
