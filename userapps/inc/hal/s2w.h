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
* $RCSfile: s2w.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/

#ifndef FTW_H
#define FTW_H

/* Defining FTW_DEBUG will enable S2w_Debug and FTW_ASSERT. */
/* #define FTW_DEBUG */

/**
 * Size of the command buffer.  Two buffers of this size are statically
 * allocated.  This determines the maximum length of the command.
 */

#define FTW_CMDBUF_SIZE     512   /* Buffer size increased for IOT application */

/**
 * Size of the transmit data buffer.  A buffer of this size is statically
 * allocated.
 */

#define FTW_DATABUF_SIZE    1600

/**
 * Size of the receive data buffer. A buffer of this size is statically
 * allocated.
 */
#define FTW_RX_BUF_SIZE     1500//2920

/* GPIO number  used for serial port selection  */
#define   APP_FTW_SERIAL_PORT_SELECT_GPIO_NUM   (26)

/* GPIO bit mask  used for serial port selection  */
#define   APP_FTW_SERIAL_PORT_SELECT_GPIO_BITMAP   (1 << APP_FTW_SERIAL_PORT_SELECT_GPIO_NUM)


/* GPIO number  used for ext PA selection  */
#define   APP_FTW_EXT_PA_SELECT_GPIO_NUM   (12)

/* GPIO bit mask  used for serial port selection  */
#define   APP_FTW_EXT_PA_SELECT_GPIO_BITMAP   (1 << APP_FTW_EXT_PA_SELECT_GPIO_NUM)

/**
 *  GPIO pins which can be used for  testing via command line
 */
//#define FTW_GPIO_UNDER_USE  (BIT4 | BIT5 | BIT6 | BIT7 | BIT8 | BIT9 | BIT20 | BIT21 | BIT29 | BIT30 | BIT31 )
#define FTW_GPIO_UNDER_USE  (0x10 | 0x20 | 0x40 | 0x80 | 0x100 | 0x200 | 0x100000 | 0x200000 | 0x20000000 | 0x40000000 | 0x80000000 )
/* Macro to get current serial device ID for S2w application */
#define APP_FTW_GET_SERIAL_DEVICE_ID()       (s2wappMainTaskCtxt->serialDeviceId)
/* Macro to set serial device ID for S2w application */
#define APP_FTW_SET_SERIAL_DEVICE_ID(devId)   (s2wappMainTaskCtxt->serialDeviceId=devId)


/* GPIO number mapped to UART#0 RX pin. This GPIO pin is used for deep-sleep wake-up detection via UART#0 port */
#define   APP_FTW_UART_EXT_WAKEUP_GPIO_NUM          (0)
#define   APP_FTW_UART_EXT_WAKEUP_GPIO_BIT_MAP      (1<<APP_FTW_UART_EXT_WAKEUP_GPIO_NUM)

/* GPIO number mapped to UART#1 RX pin. This GPIO pin is used for deep-sleep wake-up detection via UART#1 port */
//#define   APP_FTW_UART_EXT_WAKEUP_GPIO_NUM          (3)
//#define   APP_FTW_UART_EXT_WAKEUP_GPIO_BIT_MAP      (1<<APP_FTW_UART_EXT_WAKEUP_GPIO_NUM)


/* GPIO number mapped to UART#0 RX pin. This GPIO pin is used for deep-sleep wake-up detection via UART#0 port */
#define   APP_FTW_AUTO_EXIT_GPIO_NUM          (8)
#define   APP_FTW_AUTO_EXIT_GPIO_BIT_MAP      (1<<APP_FTW_AUTO_EXIT_GPIO_NUM)

/**
 * Maximum length of the final string that can be printed by a single
 * S2w_Printf.  A buffer of this size is statically allocated.
 */
#define FTW_MAX_PRINT_LEN   256

#define FTW_HTTPC_MAX_HDR_SUPPORTED     FTW_HTTPC_CFG_PARAM_HEADER_COUNT1

typedef struct FTW_SCAN_DISPLAY_INFO
{
	GSN_WLAN_MAC_SSID_T		ssid;
	GSN_WLAN_MAC_ADDR_T		bssid;
	UINT8       channel;
	UINT16 rssi;
	UINT8       capability;
	UINT8       encryptionType;
	UINT8       authType;
}FTW_SCAN_DISPLAY_INFO_T;

typedef enum FTW_NRAW_STATE
{
    FTW_NRAW_NONE,
    FTW_NRAW_NONSNAP,
    FTW_NRAW_ALL,
}FTW_NRAW_STATE_T;

typedef union FTW_SERIAL_PORT_HANDLE
{
GSN_UART_HANDLE_T uartHandle;
GSN_SPI_HANDLE_T  spiHandle;
GSN_SDIO_HANDLE_T sdioHandle;
GSN_SPI_FS_HANDLE_T  spiFsHandle;

}FTW_SERIAL_PORT_HANDLE_T;

typedef enum FTW_I2C_STATE
{
    FTW_I2C_STOPPED =0,
    FTW_I2C_STARTED,

}FTW_I2C_STATE_T;

extern PUBLIC GSN_OSAL_SEM_T s2wSyncSemID;
extern PUBLIC GSN_OSAL_SEM_T s2wSyncSemID1;

#include "hal/s2w_hal_specific.h"
#include "hal/s2w_os_specific.h"

#ifdef FTW_DEBUG

#define FTW_ASSERT(cond) do {                   \
    if (!(cond)) {                      \
        S2w_Debug("Assertion (%s) failed at %s:%d\r\n", \
            #cond, __FILE__, __LINE__);     \
    }                           \
} while (0)

INT32 S2w_Debug(const char *format, ...);

#else

#define FTW_ASSERT(cond) do {} while (0)
#define S2w_Debug(x, ...) do {} while (0)

#endif

INT32 S2w_Printf(const char *format, ...);
INT32 S2w_Printf1(const char *format, ...);
#endif
