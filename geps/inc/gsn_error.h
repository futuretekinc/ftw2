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
* $RCSfile: gsn_error.h,v $
*
* Description : This file contains public definitions for MIB management.
*****************************************************************************/
#ifndef _GSN_ERROR_H_
#define _GSN_ERROR_H_

/*****************************************************************************
  * File Inclusions
  ****************************************************************************/


/**
 *****************************************************************************
 * @file gsn_error.h
 * @brief GSN Error Codes.
 *    This file contains the error codes used throughout the GSN software.
 *****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GEPSSupport
 *
 * @{
 *****************************************************************************/

/**
 *****************************************************************************
 * @defgroup GsnError GSN Errors
 * @brief This group Contains the Error Codes.
 *****************************************************************************/



/*****************************************************************************
  * Type Definitions
  ****************************************************************************/

/**
 *****************************************************************************
 * @ingroup GsnError
 * @brief Error Codes Used in the System.
 *    This enum defines the error codes used in the software. The error codes are
 *    categorized by module for easy identification.
 *****************************************************************************/
typedef enum GSN_STATUS_E
{
    GSN_SUCCESS = 0x00,
    GSN_OSAL_SUCCESS = GSN_SUCCESS, /**< If the API execution is success */
/*************************************************************/
/*                 General status codes start here           				*/
/*************************************************************/
    GSN_FAILURE = 0x80000000,
    GSN_OPERATION_IN_PROGRESS,  /* USED FOR CALLBACKS */
    GSN_READ_SUCCESS,
    GSN_WRITE_SUCCESS,
    GSN_INVALID_PARAM,
    GSN_ALREADY_INITIALIZED,
    GSN_NOT_INITIALIZED,
    GSN_MSGSEND_FAILED,
    GSN_READ_WRITE_BUSY,
    GSN_TIME_OUT,
	GSN_BUFFER_OVERFLOW,
	GSN_BUFFER_FULL,
	GSN_XML_PARTIAL_ELEMENT,
	GSN_XML_ATTRIBUTE_PRESENT,
	GSN_XML_COMPLEX_ELEMENT,
	GSN_XML_COMPLEX_ELEMENT_END,

/*************************************************************/
/*                 System Modules status codes start here    */
/*************************************************************/

    GSN_OSAL_STATUS_CODE_START = 0x90000100,
    /**< Service was unable to retrieve an instance of the counting semaphore
    (semaphore count is zero within the specified time to wait). */
    GSN_OSAL_RESOURCE_NOT_AVAILABLE = GSN_OSAL_STATUS_CODE_START + 0x0D,
    /**< Suspension was aborted by another thread, timer, or ISR.. */
    GSN_OSAL_OPERATION_PREEMPTED = GSN_OSAL_STATUS_CODE_START + 0x1A,
    /**< Counting semaphore was deleted while thread was suspended.. */
    GSN_OSAL_OBJECT_CLOSED = GSN_OSAL_STATUS_CODE_START + 0x01,
    /**< Invalid counting semaphore pointer.*/
    GSN_OSAL_SEMAPHORE_ERROR = GSN_OSAL_STATUS_CODE_START + 0x0C,
    /**< A wait option other than TX_NO_WAIT was specified on a call from a non-thread. */
    GSN_OSAL_WAIT_ERROR = GSN_OSAL_STATUS_CODE_START + 0x04,


/*************************************************************/
/*                 System Driver Modules status codes defined here    		*/
/*************************************************************/
    /* FLASH related return codes */
    GSN_FLASH_WRITE_NOT_ALLOWED = 0xA0000100,
    GSN_FLASH_ERASE_NOT_ALLOWED,

    /* SPI return code */
    GSN_SPI_BUSY = 0xA0000200,
    GSN_SPI_TXDONE,
    GSN_SPI_TXUNDERRUN,
    GSN_SPI_TXOVERFLOW,
    GSN_SPI_RXABOVETHRESHOLD,
    GSN_SPI_RXUNDERFLOW,
    GSN_SPI_RXOVERRUN,
    GSN_SPI_RXTIMEOUT,
    GSN_SPI_TRANSFERDONE,
    GSN_SPI_SIZE_ERROR,
    GSN_SPI_RX_TIME_OUT,

    /* ADC driver return codes */
    GSN_ADC_STATUS_BUSY = 0xA0000300,
    GSN_ADC_STATUS_ERROR,
    GSN_ADC_STATUS_FIFOOVERFLOW,
    GSN_ADC_LOCK_UNAVAILABLE,


    /* PWM return codes */
    GSN_PWM_STATUS_STARTED = 0xA0000400,
    GSN_PWM_STATUS_BUSY,
    GSN_PWM_INVALID_PATTERN,
    GSN_PWM_STATUS_NOTSTARTED,

    /* Flash cache return codes */
    GSN_FLASHCACHE_DMA_BUSY = 0xA0000500,
    GSN_FLASHCACHE_DMAREQ_QED,
    GSN_FLASHCACHE_DMA_STARTED,
    GSN_FLASHIF_MUTEX_LOCK_FAIL,

    /* boot rom return codes */
    GSN_BRFLASHLRD_FLASH_NO_FW = 0xA0000600,

/*************************************************************/
/*				   System Modules status codes defined here			*/
/*************************************************************/
	/* WDD return codes */
    GSN_WDD_BUSY = 0xB0000100,
    GSN_WDD_LISTEN_NXT_BEACON_TIMEOUT,
    GSN_WDD_LISTEN_NXT_BEACON_IN_PROGRESS,
    GSN_WDD_MIC_FAIL_COUNTERMEASURE,
    GSN_WDD_WPS_SESSION_OVERLAP,
    GSN_WDD_SSID_NOT_FOUND,
    GSN_WDD_AUTH_FAIL_INVALID_PSK,
    GSN_WDD_AUTH_FAIL_TIMEOUT,
    GSN_WDD_AUTH_FAIL_EAP_FAILURE,
    GSN_WDD_AUTH_FAIL_EAP_CRED_INVALID,
    GSN_WDD_AUTH_FAIL_EAP_CERT_INVALID,
    GSN_WDD_AUTH_FAIL_EAP_AUTH_INVALID,
    GSN_WDD_ASSO_FAIL_TIMEOUT,
    GSN_WDD_SCAN_COMPLETE,
    GSN_WDD_WPS_DONE,

	/* Nw/ Nw Interface return codes */
    GSN_NW_ALREADY_INITIALIZED = 0xB0000200,
    GSN_NW_NOT_INITIALIZED,
    GSN_NW_DHCP_FAILED,
    GSN_NW_OPEN_FAILED,
    GSN_NW_ALREADY_OPENED,
    GSN_NW_OPEN_IN_PROGRESS,
	GSN_NW_DHCP_LEASE_EXPIRED,

    /* NVDS return codes */
    GSN_NVDS_INIT_FAILED = 0xB0000300,
    GSN_NVDS_NO_VALID_STORE,
    GSN_NVDS_ELMT_NOT_FOUND,
    GSN_NVDS_BAD_PARAMS,
    GSN_NVDS_ALLOC_FAILED,
    GSN_NVDS_ELMT_ALREADY_INITED,

    /*Battery Level check*/
    GSN_BATTERY_LOW = 0xB0000400,

	/* FWUP return codes */
	GSN_FWUP_FAILED_TO_SEND_INITIATION_REQ = 0xB0000500,
	GSN_FWUP_RECOVERY_NEEDED,

	/* SSL return codes */
	GSN_SSL_CLOSE_ALERT = 0xB0000600,

    /* All GEPS error codes should be above this */
    /* APP return codes start at this value */
    GSN_APP_RETURN_CODE_START = 0xC0000000,
    /* UART return codes */
    GSN_UART_STATUS_OK = 0xC0000100,
    GSN_UART_STATUS_BUSY,
    GSN_UART_STATUS_ERROR,
    GSN_UART_BUFF_FULL,
    GSN_UART_BUFF_EMPTY,

    /* DMA return codes */
    GSN_DMA_STATUS_OK= 0xC0000200,
    GSN_DMA_STATUS_BUSY,
    GSN_DMA_STATUS_ERROR,
/*!!!!!! NOTE : Add any ne definitions After C1 ROM Release Here. Donot add in between */
/* Nw/ Nw Interface return codes */
	GSN_NW_IF_CLOSED,
	GSN_NW_IPV4_CONFIG_IN_PROGRESS,
	GSN_NW_IPV6_CONFIG_IN_PROGRESS,
	/* SDIO return codes */
	GSN_SDIO_STATUS_OK= 0xC0000300,
	GSN_SDIO_STATUS_ERROR,
	GSN_SNTP_BUSY       = 0xC0000400,
} GSN_STATUS_T;


/**
 *****************************************************************************
 * @ingroup GsnError
 * @brief Error Codes Used in the OSAL.
 *    This enum defines the error codes used in the OSAL. GSN_OSAL_ERROR_T is
 *    used in OSAL module so just typedef it to GSN_STATUS_T.
 *****************************************************************************/
typedef GSN_STATUS_T GSN_OSAL_ERROR_T;

#endif /* _GSN_ERROR_H_ */
