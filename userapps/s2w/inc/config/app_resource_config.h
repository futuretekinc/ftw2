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
* $RCSfile: app_resource_config.h,v $
*
* Description : This file contains configuration of RTOS resources used in
* application.
*****************************************************************************/
#ifndef _APP_RESOURCE_CONFIG_H_
#define _APP_RESOURCE_CONFIG_H_

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/


/**
 *****************************************************************************
 * @file app_resource_config.h
 * @brief APP resource configuration.
 *    This file contains RTOS resource configuration of the application.
 *****************************************************************************/


/**
 *****************************************************************************
 * @defgroup AppResourceConfig.
 *    This group contains RTOS resource configuration of the application.
 *****************************************************************************/



/*****************************************************************************
 *  Definitions
 ****************************************************************************/
/**
 ******************************************************************************
 * @ingroup AppResourceConfig
 * @brief HI Heap size.
 *    This MACRO defines the heap size for the HI layer in core service
 ******************************************************************************/
#define APP_CFG_HI_HEAP_SIZE  8192


/**
 ****************************************************************************
 * @ingroup AppResourceConfig
 * @brief Data storage flash block.
 *     This macro defines flash block that is used for data storage. There are two
 *     APP flashes - flash block#0 and flash block#1. The flash block#1 is used
 *     for data storage currently. This value is passed to flash driver module to
 *     initialize the flash driver to operate on the specified flash block.
 *     This value is also passed to NVDS module to determine
 *     the NVDS storage address. This macro takes 0 and 1 as values.
 ****************************************************************************/
#define APP_CFG_DATA_STORE_FLASH_BLOCK  GSN_FLASH_BLOCK_1


/**
 ******************************************************************************
 * @ingroup AppResourceConfig
 * @brief Thread priority.
 *    These MACRO defines the priority of all the thread used in the system.
 ******************************************************************************/

#define APP_CFG_SOFT_TMR_THREAD_PRIORITY        1
#define APP_HI_RECV_HANDLER_THREAD_PRIORITY	    2
#define APP_SYS_CTL_HANDLER_THREAD_PRIORITY  	3
#define APP_WDD_MSG_HDLR_THREAD_PRIORITY		4
/* Cannot change DHCP thread priority from here,
 * to change it goto nxd_dhcp_client.h and change below setting */
/* #define NX_DHCP_THREAD_PRIORITY                 6 */
#define APP_CFG_NET_RX_THREAD_PRIORITY          10
#define APP_NWIF_IP_THREAD_PRIORITY				11
#define APP_MDNS_THREAD_PRI                     15
#define APP_HTTPD_THREAD_PRIORITY               16
#define APP_MAIN_CTX_THREAD_PRI     			20
#define APP_CFG_SERIALINPUT_THREAD_PRIORITY     21
#define APP_CFG_SERIALINPUT2_THREAD_PRIORITY    22
#define APP_PING_THREAD_PRI     				24
/**
 ******************************************************************************
 * @ingroup AppResourceConfig
 * @brief App context thread resource config.
 *    These MACRO is used to configure the thread stack size and the number of
 *    messages in mailbox.
 ******************************************************************************/

#define APP_MAIN_STACK_SIZE         		4096
#define APP_CFG_WDD_TASK_STACK_SIZE			(1024 * 8)
#define APP_CFG_HIF_MSG_RCV_STACK_SIZE		(1024 * 4)
#define APP_CFG_WLAN_SYS_STACK_SIZE         2048
#define APP_CFG_WLAN_SYS_MAX_MSG_IN_MBOX    16

#define APP_CFG_SYSCTL_TASK_STACK_SIZE		(1024 * 2)
#define APP_MDNS_STACK_SIZE                 2048

#define APP_CFG_WDD_MAX_MSG_IN_MBOX         16

#define APP_CFG_SYSCTL_MAX_MSG_IN_MBOX			8

#ifndef S2W_IP2WIFI_SUPPORT
#define APP_CFG_NW_TMR_STACK_SIZE           4096
#else
#define APP_CFG_NW_TMR_STACK_SIZE           2048
#endif
#define APP_CFG_NW_TMR_MAX_MSG_IN_MBOX      128

#ifndef S2W_IP2WIFI_SUPPORT
#define APP_CFG_NWIF_STACK_SIZE             4096
#else
#define APP_CFG_NWIF_STACK_SIZE             2048
#endif
#define APP_CFG_NWIF_MAX_MSG_IN_MBOX        16

#define APP_CFG_SOFT_TMR_STACK_SIZE         2048
#define APP_CFG_SOFT_TMR_MAX_MSG_IN_MBOX    8

#define APP_CFG_APP_CTX_MAX_MSG_IN_MBOX		32

#define APP_CFG_SERIALINPUT_STACK_SIZE      (1024 * 8)

#define APP_CFG_NET_TX_STACK_SIZE           2048
#define APP_CFG_NET_TX_MAX_MSG_IN_MBOX      5

#define APP_CFG_NET_RX_STACK_SIZE           4096
#define APP_CFG_NET_RX_MAX_MSG_IN_MBOX      (64)

#define APP_CFG_SSL_WEB_SRVR_STACK_SIZE		(1024 * 4)
#define APP_CFG_WEB_SRVR_STACK_SIZE         (1024 * 4)

#define APP_CFG_NCM_MSG_HDLR_MSG_IN_MBOX		16

#define APP_CFG_PING_MAX_MSG_IN_MBOX		8
#define PING_THRAED_STACK_SIZE				1024

/* Nw stack */
#define APP_NW_RX_SPKT_POOL_PKT_SIZE	128
#define APP_NW_RX_SPKT_POOL_SIZE		(4 *1024)
#define APP_NW_RX_LPKT_POOL_PKT_SIZE	1600
#define APP_NW_RX_LPKT_POOL_SIZE		(24 *1024)
/*BSD layer */
#define APP_NW_BSD_PKT_POOL_PKT_SIZE	1600
#define APP_NW_BSD_PKT_POOL_SIZE		(32 * 1024)
/*Nw Interface (IP instance)*/
#define APP_NWIF_IP_THREAD_STACK_SIZE			(1024 * 4)
#define APP_NWIF_IP_THREAD_POOL_PKT_SIZE		128
#define APP_NWIF_IP_THREAD_POOL_SIZE			(16 * 1024)
#define APP_NWIF_IP_THREAD_ARP_CACHE_SIZE		1024


/**
 ******************************************************************************
 * @ingroup AppResourceConfig
 * @brief System quality related MACRO
 *    These MACRO is used for sys qual module.
 ******************************************************************************/
typedef enum APP_CFG_SQ_TASK_ID
{
	APP_CFG_SQ_SOFT_TMR_TASK_ID = GSN_SQ_TASK_MONITOR_ID_MAX,
	APP_CFG_SQ_HI_RECV_TASK_ID,
	APP_CFG_SQ_SYS_CTL_TASK_ID,
	APP_CFG_SQ_WDD_MSG_HDLR_TASK_ID,
	APP_CFG_SQ_IP_TASK_ID,
	APP_CFG_SQ_DHCPV4_TASK_ID,
	APP_CFG_SQ_HTTPD_TASK_ID,
	APP_CFG_SQ_MAIN_TASK_ID,
	APP_CFG_SQ_NETRX_TASK_ID,
	APP_CFG_SQ_SERIAL_INPUT_TASK_ID,
}APP_CFG_SQ_TASK_ID_T;

#define APP_CFG_SQ_TICKS_FOR_SOFT_TMR_TASK   		30
#define APP_CFG_SQ_TICKS_FOR_HIF_RECV_TASK   		30
#define APP_CFG_SQ_TICKS_FOR_SYS_CTL_TASK   		30
#define APP_CFG_SQ_TICKS_FOR_WDD_MSG_HDLR_TASK   	30
#define APP_CFG_SQ_TICKS_FOR_IP_TASK      			30
#define APP_CFG_SQ_TICKS_FOR_DHCPV4_TASK      		30
#define APP_CFG_SQ_TICKS_FOR_HTTPD_TASK      		120
#define APP_CFG_SQ_TICKS_FOR_MAIN_TASK      		90
#define APP_CFG_SQ_TICKS_FOR_NETRX_TASK      		180
#define APP_CFG_SQ_TICKS_FOR_SERIAL_INPUT_TASK 		300
#define APP_CFG_SQ_TICKS_FOR_MAIN_TASK_WPS			184
#define APP_CFG_SQ_TICKS_FOR_MAIN_TASK_DNSRESOLVE	200



 /******************************************************************************
 * @ingroup AppResourceConfig
 * @brief Number of ARP entries.
 *    This MACRO defines the number of ARP entries supported.
 *@note If this number is increased more than 8 then the data type for arpValidityMap element in
 *    NCM RTC should also be changed.
 ******************************************************************************/
#define APP_CFG_NUM_OF_ARP_ENTRIES 8


#define APP_CFG_NET_RX_QUEUE_MAX                    16
#endif /* _APP_RESOURCE_CONFIG_H_ */
/*****************************************************************************/

