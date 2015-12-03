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
* $RCSfile: gsn_nw_defines.h,v $
*
* Description : This file contains  definitions commonly used by nw layer and the wdd module.
*******************************************************************************/
#ifndef _GSN_NW_DEFINES_H_
#define _GSN_NW_DEFINES_H_

/*******************************************************************************
  * File Inclusions
  ******************************************************************************/
#include "gsn_types.h"

/**
 *******************************************************************************
 * @file gsn_nw_defines.h
 * @brief GSN Network definitions.
 *    This file contains definitions commonly used by nw layer and the wdd module.
 *******************************************************************************/
#define GSN_NW_ETHER2_HEADER_SIZE          	14
#define GSN_NW_ETHER_MTU					1500;

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief Ethernet frame protocol field values.
 *     This enum contains the relevant ethernet protocol field values.
 ******************************************************************************/
typedef enum GSN_ETH_PROTOCOL_TYPE
{
    GSN_ETH_PROTO_TYPE_IP              	= 0x0800,
    GSN_ETH_PROTO_TYPE_ARP             	= 0x0806,
    GSN_ETH_PROTO_TYPE_RARP				= 0x0835,
    GSN_ETH_PROTO_TYPE_IPv6				= 0x86dd,
    GSN_ETH_PROTO_TYPE_EAPOL           	= 0x888E,
    GSN_ETH_PROTO_TYPE_RSN_PREAUTH     	= 0x888C /* FIX: CHECK!!!! */
} GSN_ETH_PROTOCOL_TYPE_T;

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief GSN Ethernet frame format.
 *     This structue defines the format for the data frames between APP and WLAN.
 ******************************************************************************/
typedef struct GSN_ETHERNET_FRAME 
{
    GSN_WLAN_MAC_ADDR_T    DestinationAddress;
    GSN_WLAN_MAC_ADDR_T    SourceAddress;
    UINT16            UpperProtocolType;
    UINT8             Data[1];
} GSN_ETHERNET_FRAME_T;

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief Layer 2 device I/O control (assumes a wireless L2 device).
 *     
 ******************************************************************************/
typedef enum GSN_L2DEV_IOCTL_CODE
{
    GSN_L2DEV_IOCTL_MCAST_RX_ON = 0,
    GSN_L2DEV_IOCTL_MCAST_RX_OFF,
    GSN_L2DEV_IOCTL_RX_ACTIVE_MODE_ON,
    GSN_L2DEV_IOCTL_RX_ACTIVE_MODE_OFF,
    GSN_L2DEV_IOCTL_RX_PS_MODE_ON,
    GSN_L2DEV_IOCTL_RX_PS_MODE_OFF,
    GSN_L2DEV_IOCTL_RX_MODE_COUNTER_CLEAR,
    GSN_L2DEV_IOCTL_PHY_ADDR_SET,
    GSN_L2DEV_IOCTL_PHY_ADDR_GET,
    GSN_L2DEV_IOCTL_RX_IEEEPS_MODE_ON,
    GSN_L2DEV_IOCTL_RX_IEEEPS_MODE_OFF,

} GSN_L2DEV_IOCTL_CODE_T;



struct GSN_L2_DEV;
/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief Receive callback type.
 *     
 ******************************************************************************/
typedef VOID (* GSN_L2_DEV_RX_CB_T)(VOID *pL3Ctx, UINT32 frameLen, VOID *pFrame);

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief Transmit done callback type.
 *     
 ******************************************************************************/
typedef VOID (* GSN_L2_DEV_TX_DONE_CB_T)(VOID *pL3Ctx, VOID *pData);

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief L2Dev will call this call back to copy the data to be sent by L3, in to its own buffer. Different Nw
 *  stack has different packet mechnisms. For example, in cae of NetX the out going packet may be really a
 *  chain of packets and need to call special PAI to copy data from chain of packets in to a single buffer to be 
 *  sent.
 *  This function may do as simple as a memcpy...  
 ******************************************************************************/
typedef VOID (*GSN_L2_DEV_SEND_PKT_COPY_CB)(VOID *pL3Ctx, VOID *inBuf, UINT32 inLen, 
												  INT8 *outBuf);

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief Layer 2 device open type.
 *     
 ******************************************************************************/

typedef GSN_STATUS (*GSN_L2_DEV_OPEN_T)(struct GSN_L2_DEV * pL2Dev,
                        VOID *l3Hndl,
                        GSN_L2_DEV_RX_CB_T rxCb,
                        GSN_L2_DEV_TX_DONE_CB_T txDoneCb,
                        GSN_L2_DEV_SEND_PKT_COPY_CB sendPktCopyCb);
/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief Layer 2 device close type.
 *     
 ******************************************************************************/
typedef GSN_STATUS (*GSN_L2_DEV_CLOSE_T)(struct GSN_L2_DEV * pL2Dev);

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief Layer 2 device send frame type.
 *     
 ******************************************************************************/
typedef GSN_STATUS (*GSN_L2_DEV_SEND_T)(struct GSN_L2_DEV * pL2Dev,
            GSN_ETHERNET_FRAME_T *pFrame, UINT32 frameLen);

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief Layer 2 device send frame 2 type.
 *     
 ******************************************************************************/
typedef GSN_STATUS (*GSN_L2_DEV_SEND2_T)(struct GSN_L2_DEV * pL2Dev,
            GSN_ETHERNET_FRAME_T *pFrame, UINT32 rxOnTime);

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief Layer 2 device receive frame type.
 *     
 ******************************************************************************/
typedef GSN_STATUS (*GSN_L2_DEV_RECEIVE_T)(struct GSN_L2_DEV * pL2Dev,
                            GSN_ETHERNET_FRAME_T *pFrame);

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief Layer 2 device I/O control type.
 *     
 ******************************************************************************/
typedef GSN_STATUS (*GSN_L2_DEV_IOCTL_T)(struct GSN_L2_DEV * pL2Dev, UINT32 cmd,
            									void *pData);

/**
 *******************************************************************************
 * @ingroup GsnNw
 * @brief Layer 2 device open type.
 *     
 ******************************************************************************/
typedef struct GSN_L2_DEV
{
    GSN_L2_DEV_OPEN_T open;
    GSN_L2_DEV_CLOSE_T close;
    GSN_L2_DEV_SEND_T send;
    GSN_L2_DEV_SEND2_T send2;
    GSN_L2_DEV_RECEIVE_T receive;
    GSN_L2_DEV_IOCTL_T ioctl;
    GSN_L2_DEV_RX_CB_T rxCb;
    GSN_L2_DEV_TX_DONE_CB_T txDoneCb;
	GSN_L2_DEV_SEND_PKT_COPY_CB sendPktCopy;
} GSN_L2_DEV_T;
#endif /* _GSN_NW_DEFINES_H_ */


