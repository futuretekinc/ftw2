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
 * Note:
 *	level 0 - Highest Priority 
 *	level 31 - Lowest Proiority 
 ******************************************************************************/
 /* System Threads*/
typedef enum APP_SYS_THREAD_PRIO
{
	APP_CFG_SOFT_TMR_THREAD_PRIORITY = 1,
	APP_HI_RECV_HANDLER_THREAD_PRIORITY,
	APP_SYS_CTL_HANDLER_THREAD_PRIORITY,
	APP_WDD_MSG_HDLR_THREAD_PRIORITY,
	APP_NWIF_IP_THREAD_PRIORITY,
}APP_SYS_THREAD_PRIO_T;
/* App threads*/
typedef enum APP_APPLICATION_THREAD_PRIO
{
	APP_CFG_MAIN_THREAD_PRIORITY = 15,
	APP_CFG_WEB_SRVR_THREAD_PRIORITY,
	APP_CFG_SYS_REBOOT_THREAD_PRIORITY,
}APP_APPLICATION_THREAD_PRIO_T;
/**
 ******************************************************************************
 * @ingroup AppResourceConfig
 * @brief App context thread resource config.
 *    These MACRO is used to configure the thread stack size and the number of
 *    messages in mailbox.
 ******************************************************************************/
/* System tasks*/
#define APP_CFG_HI_RCV_TASK_STACK_SIZE			4096 	/* Wif Msg Recv Task*/

#define APP_CFG_SYS_CTL_TASK_STACK_SIZE			2048 	/* Wif Msg Recv Task*/
#define APP_CFG_SYSCTL_MAX_MSG_IN_MBOX			8

#define APP_CFG_WDD_MSG_HDLR_STACK_SIZE			4096	/* Wdd message handler*/
#define APP_CFG_WDD_MSG_HDLR_MAX_MSG_IN_MBOX	16

#define APP_CFG_SOFT_TMR_STACK_SIZE				2048 	/* Soft timer*/
#define APP_CFG_SOFT_TMR_MAX_MSG_IN_MBOX 		8

#define APP_NWIF_IP_THREAD_STACK_SIZE			4096 	/* Netx IP instance */

#define APP_CFG_NCM_MSG_HDLR_MAX_MSG_IN_MBOX	16 

#define APP_CFG_MDNS_MSG_HDLR_MAX_MSG_IN_MBOX	16

/* User Application  tasks */
#define APP_MAIN_THREAD_STACK_SIZE				2048 *2
#define APP_CFG_APP_CTX_MAX_MSG_IN_MBOX			32

#define APP_CFG_SSL_WEB_SRVR_STACK_SIZE			4096
#define APP_CFG_WEB_SRVR_STACK_SIZE          	4096

#define APP_CFG_MDNS_STACK_SIZE            		4096


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
}APP_CFG_SQ_TASK_ID_T;

#define APP_CFG_SQ_TICKS_FOR_SOFT_TMR_TASK   		30
#define APP_CFG_SQ_TICKS_FOR_HI_RECV_TASK   	30
#define APP_CFG_SQ_TICKS_FOR_WDD_MSG_HDLR_TASK   	30
#define APP_CFG_SQ_TICKS_FOR_IP_TASK      			30
#define APP_CFG_SQ_TICKS_FOR_DHCPV4_TASK      		30
#define APP_CFG_SQ_TICKS_FOR_HTTPD_TASK      		30
#define APP_CFG_SQ_TICKS_FOR_MAIN_TASK      		30
#define APP_CFG_SQ_TICKS_FOR_MAIN_TASK_WPS			184

#ifndef APP_CFG_DCDC_TMR_VAL
#ifdef GS2100M_EVB
#define APP_CFG_DCDC_TMR_VAL 20       //600us
#else
#define APP_CFG_DCDC_TMR_VAL 41       //1.25ms
#endif
#endif

 /******************************************************************************
 * @ingroup AppResourceConfig
 * @brief Number of ARP entries.
 *    This MACRO defines the number of ARP entries supported.
 *@note If this number is increased more than 8 then the data type for arpValidityMap element in
 *    NCM RTC should also be changed.
 ******************************************************************************/
#define APP_CFG_NUM_OF_ARP_ENTRIES 8


/* Netx  Packet pool definetions */
#define APP_NW_SPKT_POOL_PKT_SIZE	128
#define APP_NW_SPKT_POOL_SIZE		(16 *1024)
#define APP_NW_LPKT_POOL_PKT_SIZE	1600
#define APP_NW_LPKT_POOL_SIZE		(32 *1024)

#define APP_NWIF_IP_THREAD_ARP_CACHE_SIZE		256

#define APP_DFLT_AP_DHCPSRVR_LEASE_TIME    0x80510100   // 24 hours

#define LED_GPIO_8	0x00000100 /*Amber LED*/
#define LED_GPIO_9	0x00000200 

#endif /* _APP_RESOURCE_CONFIG_H_ */
/*****************************************************************************/

