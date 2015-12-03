/******************************************************************************
 *
 *               COPYRIGHT (c) 2008-2010 GainSpan Corporation
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
 */

/**
******************************************************************************
*  @file gsn_sdio.h
*  @brief Public Header Containing SDIO Driver Functions.
*
*  This file contains the public APIs and structures of SDIO module.
*****************************************************************************/


/**
 *****************************************************************************
 * @ingroup driversdoc
 *
 * @{
 *****************************************************************************/


/**
 *****************************************************************************
 *  @defgroup GsnSdio GSN SDIO API
 *    This group contains public definitions and functions providing access
 *    to the GS2000 SDIO.
 ****************************************************************************/

/**
 *****************************************************************************
 *
 * @}
 *****************************************************************************/
#ifndef _GSNSDIO_H_
#define _GSNSDIO_H_

/*
 *****************************************************************************************
 * Includes on which the header file depends.
 *****************************************************************************************
 */
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
#include "core/osal/gsn_osal_threadx.h"
#include "drivers/clk_ctl/gsn_clk_ctl.h"

/*
 *****************************************************************************************
 * SDIO macros
 *****************************************************************************************
 */

/*
 *****************************************************************************************
 * Type definitions.
 *****************************************************************************************
 */
/* SDIO call back */
typedef VOID ( *SDIOCALLBACK_FP ) ( VOID*, UINT32 );



#define SDIO_BASE_ADDRESS    0X40300000
#define SDIO_CIS_AREA_BEGIN  0x00001000
#define SDIO_CIS_AREA_END    0X00017FFF

/* Tuple definitions */

#define CISTPL_NULL
#define CISTPL_CHECKSUM
#define CISTPL_VERS_1
#define CISTPL_ALTSTR
#define CISTPL_MANFID
#define CISTPL_FUNCID
#define CISTPL_FUNCE
#define CISTPL_VENDOR
#define CISTPL_END
#define CISTPL_LINK_END


/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief SDIO GSN Structure.
 *    This structure defines a SDIO configuration parameter
 *
 * @see  GSN_SDIO_CONFIG_T.
 *****************************************************************************/
typedef struct GSN_SDIO_CISTPL_FUNCID
{
   UINT8 cisTplFuncId;
   UINT8 link2NextTpl;
   UINT8 cardFuncCode;
   UINT8 notUsed;
}GSN_SDIO_CISTPL_FUNCID_T;
/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief SDIO GSN Structure.
 *    This structure defines a SDIO configuration parameter
 *
 * @see  GSN_SDIO_CONFIG_T.
 *****************************************************************************/
typedef struct GSN_SDIO_CISTPL_FUNCE0
{
    UINT8 cisTplFuncE;
    UINT8 link2NextTpl;
    UINT8 extData;
    UINT8 maxBlkFunc0Support;
    UINT8 transferRate;
}GSN_SDIO_CISTPL_FUNCE0_T;
/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief SDIO GSN Structure.
 *    This structure defines a SDIO configuration parameter
 *
 * @see  GSN_SDIO_CONFIG_T.
 *****************************************************************************/
typedef struct GSN_SDIO_CISTPL_MANFID
{
    UINT8 cisTplManfId;
    UINT8 link2NextTpl;
    UINT8 ManufactureCode;
    UINT8 ManufactureId;
    UINT8 partNumber;
    UINT8 oemId;
}GSN_SDIO_CISTPL_MANFID_T;
/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief SDIO GSN Structure.
 *    This structure defines a SDIO configuration parameter
 *
 * @see  GSN_SDIO_CONFIG_T.
 *****************************************************************************/
/* Extended Function Tuple (Per Function) */
typedef struct SDIO_FUNC_EXT_FUNCTION_TPL
{
    UINT8   cisTplFuncId;
    UINT8   link2NextTpl;
    UINT8   extDataType;
    UINT8   wakeUpSupport;
    UINT8   FunctionInfo;                       /* function info */
    UINT8   SDIORev;                            /* revision */
    UINT32  CardPSN;                            /* product serial number */
    UINT32  CSASize;                            /* CSA size */
    UINT8   CSAProperties;                      /* CSA properties */
    UINT16  MaxBlockSize;                       /* max block size for block transfers */
    UINT32  FunctionOCR;                        /* optimal function OCR */
    UINT8   OpMinPwr;                           /* operational min power */
    UINT8   OpAvgPwr;                           /* operational average power */
    UINT8   OpMaxPwr;                           /* operation maximum power */
    UINT8   SbMinPwr;                           /* standby minimum power */
    UINT8   SbAvgPwr;                           /* standby average power */
    UINT8   SbMaxPwr;                           /* standby maximum power */
    UINT16  MinBandWidth;                       /* minimum bus bandwidth */
    UINT16  OptBandWidth;                       /* optimalbus bandwitdh */
}SDIO_FUNC_EXT_FUNCTION_TPL_T;
/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief SDIO GSN Structure.
 *    This structure defines a SDIO configuration parameter
 *
 * @see  GSN_SDIO_CONFIG_T.
 *****************************************************************************/
typedef struct GSN_SDIO_CISTPL_FUNCE1
{
    SDIO_FUNC_EXT_FUNCTION_TPL_T CommonInfo;  /* from 1.0*/
    UINT16  EnableTimeOut;                    /* timeout for enable */
    UINT16  OperPwrAvgPwr;
    UINT16  OperPwrMaxPwr;
    UINT16  HiPwrAvgPwr;
    UINT16  HiPwrPeakPwr;
    UINT16  LowPwrAvgPwr;
    UINT16  LowPwrPeakPwr;

}GSN_SDIO_CISTPL_FUNCE1_T;
/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief SDIO GSN Structure.
 *    This structure defines a SDIO configuration parameter
 *
 * @see  GSN_SDIO_CONFIG_T.
 *****************************************************************************/
typedef struct GSN_SDIO_CISTPL_SDIO_STD
{
    UINT8   cisTplSdioStd;
    UINT8   tplLink;
    UINT8   ioDeviceType;
    UINT8   dataFormat;
    UINT8   formatSpec;

}GSN_SDIO_CISTPL_SDIO_STD_T;
/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief SDIO GSN Structure.
 *    This structure defines a SDIO configuration parameter
 *
 * @see  GSN_SDIO_CONFIG_T.
 *****************************************************************************/
typedef struct GSN_SDIO_CIS0_STRUCTURE
{
    GSN_SDIO_CISTPL_FUNCID_T cisTplFuncId;
    GSN_SDIO_CISTPL_FUNCE0_T cisTplFuncE0;
    GSN_SDIO_CISTPL_MANFID_T cisTplManufactureId;
    UINT8 cisTplEnd;
}GSN_SDIO_CIS0_STRUCTURE_T;
/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief SDIO GSN Structure.
 *    This structure defines a SDIO configuration parameter
 *
 * @see  GSN_SDIO_CONFIG_T.
 *****************************************************************************/
typedef struct GSN_SDIO_CIS1_STRUCTURE
{
    GSN_SDIO_CISTPL_FUNCID_T cisTplFuncId;
    GSN_SDIO_CISTPL_FUNCE1_T cisTplFuncE1;
    GSN_SDIO_CISTPL_SDIO_STD_T cisTplStd;
    UINT8 cisTplEnd;

}GSN_SDIO_CIS1_STRUCTURE_T;


/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief GSN SDIO Types.
 *    This enum defines SDIO return values
 * @see  GSN_SDIO_STATUS_T.
 *****************************************************************************/
enum GSN_SDIO_DEVICE_STATE
{
    GSN_SDIO_NOT_INITIALIZED,
    GSN_SDIO_INITIALIZED,
    GSN_SDIO_READ_PROGRESS,
    GSN_SDIO_READ_FINISHED,
    GSN_SDIO_WRITE_PROGRESS,
    GSN_SDIO_WRITE_FINISHED,
    GSN_SDIO_BLOCK_READ_PROGRESS,
    GSN_SDIO_RECEIVE_ERROR,
    GSN_SDIO_CLOSED
};
/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief SDIO GSN Structure.
 *    This structure defines a SDIO configuration parameter
 *
 * @see  GSN_SDIO_CONFIG_T.
 *****************************************************************************/
typedef  enum GSN_SDIO_CSA_SUPPORT
{
    GSN_SDIO_CSA_NO_SUPPORT,
    GSN_SDIO_CSA_SUPPORT

}GSN_SDIO_CSA_SUPPORT_T;
/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief SDIO GSN Structure.
 *    This structure defines a SDIO configuration parameter
 *
 * @see  GSN_SDIO_CONFIG_T.
 *****************************************************************************/
typedef  enum GSN_SDIO_TRANSFER_MODE
{
    GSN_SDIO_SPI_MODE,
    GSN_SDIO_SD1_MODE,
    GSN_SDIO_SD4_MODE
}GSN_SDIO_TRANSFER_MODE_T;
/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief SDIO GSN Structure.
 * This structure defines SDIO Rx buffer status parameter
 *
 * @see  GSN_SDIO_CONFIG_T.
 *****************************************************************************/

typedef struct GSN_SDIO_RX_BUFF
{
    UINT8*               sdioBufferStart;
    UINT8*               sdioBuffer;
    UINT32               sdioBuffSize;
    INT32                sdioBuffHead;
    INT32                sdioBuffTail;
    UINT32               dataCountInBuff;
    UINT32               sdioBuffRunSize;
    UINT8                sdioRxIntClear;
    UINT8                sdioRxBufferWrapAround;
    UINT8                txPending;
} GSN_SDIO_RX_BUFF_T;
/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief SDIO GSN Structure.
 *    This structure defines a SDIO configuration parameter
 *
 * @see  GSN_SDIO_CONFIG_T.
 *****************************************************************************/

typedef struct GSN_SDIOCONFIG
{
    UINT32                     sdioClk;
    GSN_SDIO_TRANSFER_MODE_T   transferMode;
    GSN_SDIO_CIS0_STRUCTURE_T  sdioCis0Structure;
    GSN_SDIO_CIS1_STRUCTURE_T  sdioCis1Structure;
    GSN_SDIO_CSA_SUPPORT_T     csaSupport;
    UINT8*                     sdioBufferStart;
    UINT32                     sdioBuffSize;

} GSN_SDIO_CONFIG_T;


/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief SDIO GSN Structure.
 *    This structure defines a SDIO driver handling parameters.
 *
 * @see  GSN_SDIO_T.
 *****************************************************************************/

typedef struct GSN_SDIO
{
    UINT32                  pReg;
    UINT32                  blockRead;
    UINT32                  noOfBytesToRead;
    UINT32                  noOfBytesToBeWritten;
    UINT32                  actualBytesRead;
    UINT32                  actualBytesWritten;
    UINT8*                  txBuffer;
    UINT8*                  rxUserBuffer;
    GSN_SDIO_RX_BUFF_T      rxBuffer;
    SDIOCALLBACK_FP         ReadCallback;
    VOID                    *ReadCbCtx;
    SDIOCALLBACK_FP          WriteCallback;
    VOID                    *WriteCbCtx;
    UINT32                   sdioDeviceState;
    GSN_OSAL_SEM_T           sdioSyncWriteSemId;
    GSN_OSAL_SEM_T           sdioBlockReadSemId;
    GSN_SDIO_CIS0_STRUCTURE_T  sdioCis0Structure;
    GSN_SDIO_CIS1_STRUCTURE_T  sdioCis1Structure;
}GSN_SDIO_T;


/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief SDIO GSN Structure.
 *    This structure defines a SDIO handle, which holds a SDIO config and data
 *    parameter
 *
 * @see  GSN_SDIO_HANDLE_T.
 *****************************************************************************/

typedef struct GSN_SDIO_HANDLE
{
    UINT32             u32SdioRegInit;  /**< initialise status */
    GSN_SDIO_T         sdio;            /**< SDIO parameter */

}GSN_SDIO_HANDLE_T;

/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief SDIO Driver open API.
 *    This function open a SDIO port.
 *    This function initializes the corresponding SDIO.
 * @param ptSdioHandle           - IN pointer to sdio handle.
 * @param ptConfig               - IN pointer to sdio configuration.
 * @retval GSN_SDIO_STATUS_ERROR  on error
 * @retval GSN_SDIO_STATUS_OK on success.
 * @note
 *****************************************************************************/
GSN_OSAL_ERROR_T
GsnSdio_Open (GSN_SDIO_HANDLE_T* ptSdioHandle,GSN_SDIO_CONFIG_T *ptConfig);

/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief @brief SDIO GSN Read throgh specified port
 *    1. prepare for transmission.
 *    2. Start data reception by enabling the Rx interrupt.
 *    3. wait on the semaphore for a synchronous read.
 * @param ptSdioHandle    - IN pointer to hold Sdio handle.
 * @param puBuffer        - IN pointer to hold read data pointer for data.
 * @param noOfBytesToRead - IN no of bytes to read.
 * @param blockRead       - IN block read.
 * @param ptCallBackFunc  - IN the application call back function.
 * @param ctx             - IN the context for application call back function.
 * @return The number bytes received.
 * @note
 *****************************************************************************/

UINT32
GsnSdio_Read( GSN_SDIO_HANDLE_T* ptSdioHandle,
              UINT8 *puBuffer, UINT32 noOfBytesToRead, BOOL blockRead,
              SDIOCALLBACK_FP ptCallBackFunc, VOID *ctx);
/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief SDIO Write Through Specified Port
 * @param ptSdioHandle    - IN pointer to hold Sdio handle.
 * @param puBuffer        - IN pointer to hold write data pointer .
 *                            for data transfer
 * @param noOfBytesToWrite - IN the number of bytes to write.
 * @param ptCallBackFunc  - IN callback function for asynch. write
 * @param ctx             - IN the context for call back function.
 * @return actual bytes written
 *
 *****************************************************************************/
UINT32
GsnSdio_Write(GSN_SDIO_HANDLE_T* ptSdioHandle,
                UINT8 *puBuffer, UINT32 noOfBytesToWrite,
                SDIOCALLBACK_FP ptCallBackFunc, VOID *ctx);
/**
 *****************************************************************************
 * @ingroup GsnSdio
 * @brief Sdio Driver ISR handling.
 * Combined interrupt handler
 * This function is getting called whenever sdio interrupt happens
 * @param ptGsnSdio                   - IN pointer to GSN_SDIO_T structure.
 * @return VOID
 * @note
 *
 *****************************************************************************/
VOID
GsnSdio_DefaultIsr(GSN_SDIO_T *ptGsnSdio);

GSN_OSAL_ERROR_T
GsnSdio_Close(GSN_SDIO_HANDLE_T* ptSdioHandle);

UINT32
GsnSdio_RingBuffGet(GSN_SDIO_T *ptGsnSdio,UINT8* usrBuff, UINT32 usrBuffLen );

PUBLIC VOID
__GsnSdio_Isr();
#endif
