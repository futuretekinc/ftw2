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
* $RCSfile: gsn_wif_sys_defs.h,v $
*
* Description : This file contains common public definitions for WLAN CPU 
*               system control command/event definitions.
******************************************************************************/
#ifndef _GSN_WIF_SYS_DEFS_H_
#define _GSN_WIF_SYS_DEFS_H_
#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************************
* File Inclusion
*****************************************************************************/

/**
 *****************************************************************************
 * @file gsn_wif_sys_defs.h
 * @brief GSN WIF System messages public header.
 * 
 *    This file contains the public APIs and structures of System control
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
 * @defgroup GsnWifSysDefs GSN SOC Platform Configuration
 *    This group of APIs provides system control definitions like access to
 *    chip bootup info, Standby and reset, alarm indications, RTC memory, 
 *    system time, and battery status.
*****************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/	


/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief sysctl device number
 *
 *    all sys control response messages will have this number in dev index field
 *****************************************************************************/

#define GSN_WIF_SYS_CTL_DEV_INDEX 0xff
#define GSN_WIF_SYS_STDBY_MAX_IF_NUM   GSN_WIF_MAX_IF_NUM
#define GSN_WIF_SYS_STDBY_WAKEUP_OFFSET  (300) /* Time in milli seconds */
/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief Boot reason.
 *
 *    enumeration containing the reason for the latest SOC boot.
 *****************************************************************************/

typedef enum GSN_WIF_SYS_BOOT_REASON
{	
    GSN_WIF_SYS_BOOT_FIRST_BOOT = 0,     /**< Power ON       */
    GSN_WIF_SYS_BOOT_NORMAL_BOOT,        /**< RTC or External Alarm */
    GSN_WIF_SYS_BOOT_FW_UPDATE_BOOT,     /**< FW Update             */
    GSN_WIF_SYS_BOOT_WATCHDOG_BOOT,      /**< WD                */
    GSN_WIF_SYS_BOOT_SW_RESET_BOOT,      /**< WLAN S/W Reset        */
    GSN_WIF_SYS_BOOT_EXCEPTION_BOOT,     /**< Exception in S/W */
    GSN_WIF_SYS_BOOT_EXT_RESET_BOOT,     /**< External reset */
    GSN_WIF_SYS_BOOT_DBG_BOOT,           /**< Debug boot */
    GSN_WIF_SYS_BOOT_WLAN_TEST_BOOT,     /**< WLAN test over serial */
    GSN_WIF_SYS_BOOT_FACTORY_FW_BOOT,    /**< Factory firmware restore */
    GSN_WIF_SYS_BOOT_CORE_BROWNOUT_BOOT, /**< Core Brownout */
    GSN_WIF_SYS_BOOT_CRYPTO_SW_BOOT,     /**< Crypto S/W Reset */
    GSN_WIF_SYS_BOOT_SRC_MAX
} GSN_WIF_SYS_BOOT_REASON_T;



/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief Normal boot reason.
 *
 *    Enumeration of possible reasons for normal bootup (timeout or alarm).
 *****************************************************************************/
typedef enum GSN_WIF_SYS_BOOTINFO_NORMALBOOT
{
    GSN_WIF_SYS_BOOTINFO_NORMALBOOT_RTC = 0,
    GSN_WIF_SYS_BOOTINFO_NORMALBOOT_ALARM = 1,
} GSN_WIF_SYS_BOOTINFO_NORMALBOOT_T;

/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief SW Reset boot reason.
 *
 *    Enumeration of possible reasons for bootup after a software reset.
 *****************************************************************************/
typedef enum GSN_WIF_SYS_BOOTINFO_SWRESET
{
    GSN_WIF_SYS_BOOTINFO_SWRESET_WLAN = 0x1,
    GSN_WIF_SYS_BOOTINFO_SWRESET_APP = 0x2,       
} GSN_WIF_SYS_BOOTINFO_SWRESET_T;

/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief Watchdog boot reason.
 *
 *    Enumeration of possible reasons for bootup after a Watchdog timer reset.
 *****************************************************************************/
typedef enum GSN_WIF_SYS_BOOTINFO_WDOG_RESET
{
    GSN_WIF_SYS_BOOTINFO_WDOG_RESET_WLAN = 0x1,
    GSN_WIF_SYS_BOOTINFO_WDOG_RESET_APP = 0x2,       
} GSN_WIF_SYS_BOOTINFO_WDOG_RESET_T;

/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief Exception boot reason.
 *
 *    Enumeration of possible reasons for bootup after a CPU exception.
 *****************************************************************************/
typedef enum GSN_WIF_SYS_BOOTINFO_EXCP
{
    GSN_WIF_SYS_BOOTINFO_EXCP_APP_ABORT = 0,
    GSN_WIF_SYS_BOOTINFO_EXCP_APP_ASSERT = 1,        
    GSN_WIF_SYS_BOOTINFO_EXCP_WLAN_ABORT = 2,
    GSN_WIF_SYS_BOOTINFO_EXCP_WLAN_ASSERT = 3,        
} GSN_WIF_SYS_BOOTINFO_EXCP_T;

/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief FWUP download status.
 *
 *    Enumeration of possible status after a Firmware Update.
 *****************************************************************************/
typedef enum GSN_WIF_SYS_BOOTINFO_FWUP_DWNLD_STATUS
{
    GSN_WIF_SYS_FWUP_DWNLD_STATUS_SUCCESS = 0,
    GSN_WIF_SYS_FWUP_DWNLD_STATUS_CHKSUM_ERROR,
    GSN_WIF_SYS_FWUP_DWNLD_STATUS_FLASH_FAIL,
    GSN_WIF_SYS_FWUP_DWNLD_STATUS_SWAP_ERROR
} GSN_WIF_SYS_BOOTINFO_FWUP_DWNLD_STATUS_T;

 /**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief FWUP other status.
 *    Enumeration of other Firmware Update status options.
 *****************************************************************************/
typedef enum GSN_WIF_SYS_BOOTINFO_FWUP_OTHER_STATUS
{
    GSN_WIF_SYS_FWUP_OTHER_STATUS_NO_ERROR = 0,
    GSN_WIF_SYS_FWUP_OTHER_STATUS_TIMEOUT,
    GSN_WIF_SYS_FWUP_OTHER_STATUS_BAD_SEQNUM,
    GSN_WIF_SYS_FWUP_OTHER_STATUS_BAD_PARAMS
} GSN_WIF_SYS_BOOTINFO_FWUP_OTHER_STATUS_T;



 /**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief host interface type
 *    Enumeration of host interface types
 *****************************************************************************/
typedef enum GSN_WIF_SYS_BOOTINFO_HOST_IF_TYPE
{
    GSN_WIF_SYS_BOOTINFO_HOST_IF_TYPE_MB = 0,
    GSN_WIF_SYS_BOOTINFO_HOST_IF_TYPE_UART = 1
} GSN_WIF_SYS_BOOTINFO_HOST_IF_TYPE_T; 

/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief Boot Indication Message.
 * 
 *    APP puts this boot indication into ctl-rdy queue and release WLAN CPU
 *    reset. The WLAN CPU boots up and reads this message and performs some
 *    internal configuration.
*****************************************************************************/
typedef struct GSN_WIF_SYS_BOOT_REQ_S
{
    UINT32      bootReason      : 4;
    UINT32      bootSubreason   : 4;
    UINT32      confLost        : 1;
	UINT32 		strapVal		: 5;
    UINT32      modType         : 6;
    UINT32      temperature     : 8;    
    UINT32      modVersion      : 4;

    UINT32      bootTimeLow;
    UINT32      bootTimeHigh;

    UINT32      fwFlashAddr;    /**< address in flash of fw image */    

    UINT32      dTxRdyQDescAddr; /**< Addr of data Tx ready Q descriptor */
    UINT32      dTxDoneQDescAddr; /**< Addr of data Tx done Q descriptor */
    UINT32      dRxRdySBufQDescAddr; /**< Addr of data Rx ready Q descriptor
                                           for small buffers */
    UINT32      dRxRdyLBufQDescAddr; /**< Addr of data Rx ready Q descriptor
                                          for large buffers */
    UINT32      dRxDoneQDescAddr; /**< Addr of data Rx done Q descriptor */

    UINT32      cTxRdyQDescAddr; /**< Addr of ctl Tx ready Q descriptor */
    UINT32      cTxDoneQDescAddr; /**< Addr of ctl Tx done Q descriptor */
    UINT32      cRxRdySBufQDescAddr; /**< Addr of ctl Rx ready Q descriptor
                                           for small buffers */
    UINT32      cRxRdyLBufQDescAddr; /**< Addr of ctl Rx ready Q descriptor
                                          for large buffers */
    UINT32      cRxDoneQDescAddr; /**< Addr of ctl Rx done Q descriptor */

    UINT32    numIfs; /**< Number of interfaces to be supported */
    UINT8     ifTypes[GSN_WIF_MAX_IF_NUM]; /* Interface type. Not valid for standby wakeup. */
    UINT8     stdbyCtx[1];  /* This must be the last element. Valid only for standby wake-up case */

} GSN_WIF_SYS_BOOT_REQ_T;


/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief boot indication msg format.
 * 
 *    boot indication msg format
*****************************************************************************/
typedef struct GSN_WIF_SYS_BOOT_IND_S
{
    UINT32      status;

} GSN_WIF_SYS_BOOT_IND_T;



/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief L2 Interface state.
 * 
 *    Layer-2 interface state
*****************************************************************************/
typedef enum GSN_WIF_IF_STATE_S
{
    GSN_WIF_IF_STATE_NOT_INITED = 0,  /**< The interface is not initialized */
    GSN_WIF_IF_STATE_SUSPENDED,       /**< The interface is configured but
                                           suspended right now, may be another
                                           interface is active */
    GSN_WIF_IF_STATE_RUNNING,          /**< The interface is currently running
                                           ie., it owns the RF now */
    GSN_WIF_IF_STATE_STOP_REQUESTED_WAITING_FOR_TX_COMPLETION,         /**< if stop is
                                           requested, waiting for completion of
                                           pending TX s */
    GSN_WIF_IF_STATE_STOPPED,         /**< THe interface is stopped due to
                                           some reason */
} GSN_WIF_IF_STATE_T;


typedef enum GSN_WIF_SYS_WLAN_STA_TYPE_E
{
    GSN_WIF_SYS_WLAN_STA_TYPE_LSSTA = 0, /* Low speed STA */
    GSN_WIF_SYS_WLAN_STA_TYPE_HSSTA = 1, /* High speed STA */
} GSN_WIF_SYS_WLAN_STA_TYPE_T;
/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief Start Interface Message.
 * 
 *    APP sends this message to WFW to start an interface.
*****************************************************************************/
typedef struct GSN_WIF_SYS_IF_START_REQ_S
{
    UINT8 macIfNum;        /**< Interface number, this is the value that will be
                           passed in all messages between APP and WLAN CPU
                           to identify the interface to which the message
                           belongs */

    UINT8 macIfType;       /**< Type of interface, see GSN_WIF_WLAN_NW_TYPE_T */
    UINT8 wlanStaType;     /**< see GSN_WIF_SYS_WLAN_STA_TYPE_T above */
    UINT8 wlanApNumSta;    /**< Number of stations to support in AP mode */
    UINT32      dTxRdyQFrameTO; /**< Time (ms) after which the Tx frames are 
                                     returned to APP if still in HI queues
                                     waiting for i/f switch, etc */
    UINT8 reserved[16];
} GSN_WIF_SYS_IF_START_REQ_T;
/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief Stop Interface Message.
 * 
 *    APP sends this message to WFW to stop an interface.
*****************************************************************************/
typedef struct GSN_WIF_SYS_IF_STOP_REQ_S
{
    UINT8 macIfNum;        /**< Interface number, this is the value that will be
                           passed in all messages between APP and WLAN CPU
                           to identify the interface to which the message
                           belongs */

    UINT8 macIfType;       /**< Type of interface, see GSN_WIF_WLAN_NW_TYPE_T */
                           
    UINT32      waitPeriod; /**< Time (ms) to wait till for pending TX to complete */
} GSN_WIF_SYS_IF_STOP_REQ_T;


typedef struct GSN_WIF_SYS_IF_STOP_RSP_S
{
    UINT32      status;

} GSN_WIF_SYS_IF_STOP_RSP_T;


typedef struct GSN_WIF_SYS_IF_START_RSP_S
{
    UINT32      status;

} GSN_WIF_SYS_IF_START_RSP_T;

typedef struct GSN_WIF_SYS_FW_VERSION_RSP_S
{
    UINT32      fwVersion;
}GSN_WIF_SYS_FW_VERSION_RSP_T;


typedef enum GSN_WIF_SYS_RESET_REQ_TYPE_E
{
    GSN_WIF_SYS_RESET_REQ_TYPE_WLAN_ONLY = 0x1,
    GSN_WIF_SYS_RESET_REQ_TYPE_SYSTEM = 0x2,
    GSN_WIF_SYS_RESET_REQ_TYPE_FULL_CHIP = 0x3, /**< including RTC */

} GSN_WIF_SYS_RESET_REQ_TYPE_T;

typedef enum GSN_WIF_SYS_RESET_REQ_REASON_E
{
    GSN_WIF_SYS_RESET_REQ_REASON_EXCP = 0x1,
    GSN_WIF_SYS_RESET_REQ_REASON_ASSERT = 0x2,
    GSN_WIF_SYS_RESET_REQ_REASON_SYSQUAL = 0x3, /**< including RTC */

} GSN_WIF_SYS_RESET_REQ_REASON_T;


typedef struct GSN_WIF_SYS_RESET_REQ_S
{
    UINT8 resetType; /**< GSN_WIF_SYS_RESET_REQ_TYPE_T */
    UINT8 resetReason; /**< GSN_WIF_SYS_RESET_REQ_REASON_T */
    UINT8 resetInfoSize; /** Number of 32-bit words of resetInfo */
    UINT8 resetAddlInfo;

    UINT32 resetInfo[16]; /**< resetInfoSize words of resetInfo */

} GSN_WIF_SYS_RESET_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief File Operation codes.
 *
 *    Types for file operation.
*****************************************************************************/
typedef enum GSN_WIF_SYS_FILE_OPCODE_E
{
    GSN_WIF_SYS_FILE_OPCODE_OPEN = 0,
    GSN_WIF_SYS_FILE_OPCODE_CLOSE = 1,
    GSN_WIF_SYS_FILE_OPCODE_READ = 2,
    GSN_WIF_SYS_FILE_OPCODE_WRITE = 3,

} GSN_WIF_SYS_FILE_OPCODE_T;
/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief opt write command format.
 *
 *    Types for opt write command format.
*****************************************************************************/
typedef struct GSN_WIF_SYS_OTP_WRITE_REQ_S
{
    UINT8 id; /**< OTP group ID */
    UINT8 ver;  /**< OTP group ver */
    UINT16 len; /**< length of data to be written */
    UINT8  data[0];
} GSN_WIF_SYS_OTP_WRITE_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief opt write command acknowledge format.
 *
 *    Types for opt write command acknowledge format.
*****************************************************************************/
typedef struct GSN_WIF_SYS_OTP_WRITE_RSP_S
{
    UINT32 status;
    UINT16 len; /**< length of data written */
} GSN_WIF_SYS_OTP_WRITE_RSP_T;
/**
*****************************************************************************
* @ingroup GsnWifSysDefs
* @brief opt read command format.
*
*    Types for opt read command format.
*****************************************************************************/
typedef struct GSN_WIF_SYS_OTP_READ_REQ_S
{
    UINT8 id; /**< OTP group ID */
    UINT8 ver;  /**< OTP group ver */
} GSN_WIF_SYS_OTP_READ_REQ_T;


/**
*****************************************************************************
* @ingroup GsnWifSysDefs
* @brief opt read command acknowledge format.
*
*    Types for opt read command acknowledge format.
*****************************************************************************/
typedef struct GSN_WIF_SYS_OTP_READ_RSP_S
{
    INT32 status;
    UINT16 len; /**< length of data read */
    UINT8  data[0];
} GSN_WIF_SYS_OTP_READ_RSP_T;

/**
*****************************************************************************
* @ingroup GsnWifSysDefs
* @brief Memory/Reg  read/Write command format.
*
*    Types for Memory read/Write  command .
*****************************************************************************/
typedef struct 	GSN_WIF_SYS_MEM_RW_REQ_S
{
    UINT32 addr; /**< memory address */
    UINT32 len;  /**< number of bytes to read/write */
    UINT8  data[0];
}GSN_WIF_SYS_MEM_RW_REQ_T;

typedef GSN_WIF_SYS_MEM_RW_REQ_T GSN_WIF_SYS_MEM_READ_RSP_T;
/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief File Operation result codes.
 *
 *    Types for file operation result.
*****************************************************************************/
typedef enum GSN_WIF_SYS_FILE_OP_STATUS_E
{
    GSN_WIF_SYS_FILE_OP_STATUS_SUCCESS = 0,
    /**< anything else is failure */

} GSN_WIF_SYS_FILE_OP_STATUS_T;

/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief File Operation flags.
 *
 *    Special flags for file operation. This is a bitmap, so multiple
 *    operations could be requested.
*****************************************************************************/
typedef enum GSN_WIF_SYS_FILE_OP_FLAGS_E
{
    GSN_WIF_SYS_FILE_OP_FLAGS_CREAT = 1, /**< use with open to create file,
            if not set, then existing file is opened */
    GSN_WIF_SYS_FILE_OP_FLAGS_RD, /**< use with open to open in rd mode */
    GSN_WIF_SYS_FILE_OP_FLAGS_WR, /**< use with open to open in wr mode */
    GSN_WIF_SYS_FILE_OP_FLAGS_RDWR, /**< use with open to open in rd,wr mode */
	GSN_WIF_SYS_FILE_OP_FLAGS_DEL,	 /**< use with close to delete file */

} GSN_WIF_SYS_FILE_OP_FLAGS_T;

typedef enum GSN_WIF_SYS_FILE_WHENCE_E	
{
	GSN_WIF_SYS_FILE_F_SEEK_CUR,
	GSN_WIF_SYS_FILE_F_SEEK_END,
	GSN_WIF_SYS_FILE_F_SEEK_SET 
}GSN_WIF_SYS_FILE_WHENCE_T;
/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief File Operation Request.
 *
 *    WLAN sends this message to APP to request a file operation.
*****************************************************************************/
typedef struct GSN_WIF_SYS_FILE_OP_REQ_S
{
    UINT8 opCode;   /**< open, close, read, write */
    UINT8 fileName[32]; /**< string - NULL character terminated */
	UINT32 fileHandle;/**< This value is returned from APP during open, To be used in all other cases*/
    UINT16 offset; /**< byte offset in file for operation */
	UINT8  whence;/**<GSN_WIF_SYS_FILE_WHENCE_T */
    UINT16 size;   /**< size in bytes for read/write operation */
    UINT32 flags;  /**< flags indicating special request like create */
    UINT8  data[0]; /**< stretch-able array for data */
} GSN_WIF_SYS_FILE_OP_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief File Operation Response.
 *
 *    APP sends this message to WLAN as a response of file operation.
*****************************************************************************/
typedef struct GSN_WIF_SYS_FILE_OP_RSP_S
{
    UINT8 opCode;   /**< read, write */
    UINT8 fileName[32]; /**< string - NULL character terminated */	
	UINT32 fileHandle;/**< This value is returned from APP during open, To be used in all other cases*/
    UINT16 offset; /**< byte offset in file for operation */
    UINT16 size;   /**< size in bytes for read/write operation */
    UINT32 flags;  /**< flags indicating special request like create */
    UINT32 status; /**< status indicating success/failure */
    UINT8  data[0]; /**< stretch-able array for data */
} GSN_WIF_SYS_FILE_OP_RSP_T;


/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief Standby request msg format.
 * 
 *    Standby request msg format
*****************************************************************************/
typedef struct GSN_WIF_SYS_STDBY_REQ_S
{    
    UINT32  wakeUpForWlanEvents;   /**< 0 - don't care for next wakeup event of WLAN    */
                                   /**< 1 - WLAN must honor the next wakeup event */
                                                               
    UINT32  restoreIfBitMap;       /**< Interfaces which needs to be restored */
                                   /**< BIT#0 - First i/f, BIT#1 for second i/f and so on */
    UINT32 waitPeriod[GSN_WIF_MAX_IF_NUM]; /**< Wait period in milliseconds.*/
                                                            /**< 0 - No wait; */
                                                            /**< 0xFFFFFFFF - Wait till TX completion */
} GSN_WIF_SYS_STDBY_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief Standby ready indication msg format.
 * 
 *    Standby ready indication msg format.
*****************************************************************************/
typedef struct GSN_WIF_SYS_STDBY_RDY_IND_S
{
   UINT32	readyFlag; /* 0 - not ready  1- ready for standby*/
	ULONG64    nextWakeUp; /* Next absolute wakeup time */
	UINT32  totalSize;	   /* Total size of standby context.  */
	UINT8	 ctxData[1];   /* Standby state context */
} GSN_WIF_SYS_STDBY_RDY_IND_T;

/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief Battery Measurement Deatials.
 * 
 *    This structure defines the Battery measurement Start cmd format.
*****************************************************************************/

typedef struct GSN_WIF_SYS_BATT_CHK_REQ_S
{
    UINT32 repeatNumTx;  /**< if repeatNumTx is 0, 
                            then it is one-shot otherwise 
                            it is done for every repeatNumTx transmissions.
                            Value 0xFFFFFFFF to stop the operations
                            */
} GSN_WIF_SYS_BATT_CHK_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief Battery Measurement Deatials.
 * 
 *    This structure defines the Battery measurement Indication format.
*****************************************************************************/

typedef struct GSN_WIF_SYS_BATT_CHK_IND_S
{
    UINT32 batteryMeasure;       /**< Volatage Measured at that time */

}GSN_WIF_SYS_BATT_CHK_IND_T;

typedef struct GSN_WIF_SYS_FEATURE_BMAP_RSP_S
{
    ULONG64 featureBmap;
}GSN_WIF_SYS_FEATURE_BMAP_RSP_T;

typedef struct GSN_WIF_SYS_TEMP_GET_RSP_S
{
    INT8 wlanTemperature;       /**< Temperature Measured at that time */
}GSN_WIF_SYS_TEMP_GET_RSP_T;

typedef struct GSN_WIF_SYS_TEMP_SET_REQ_S
{
    INT8 temperature;       /**< Temperature Measured at APP */
}GSN_WIF_SYS_TEMP_SET_REQ_T;

/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @Concurrent mode types.
 * 
 *    This enum defines concurrent mode types.
 *****************************************************************************/


typedef enum GSN_WIF_CM_TYPE_S
{
    GSN_WIF_SYS_CM_TYPE_STA_AP          = 1,
    GSN_WIF_SYS_CM_TYPE_STA_STA,
    GSN_WIF_SYS_CM_TYPE_STA_STA_15DOT4,
    GSN_WIF_SYS_CM_TYPE_AP_15DOT4,

    GSN_WIF_SYS_CM_TYPE_MAX
}GSN_WIF_CM_TYPE_T;



/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief Start concurrent mode Message.
 * 
 *    APP sends this message to WFW to start concurrent mode
*****************************************************************************/

typedef struct GSN_WIF_SYS_CMS_START_REQ_S
{
    GSN_WIF_CM_TYPE_T cmType;
    UINT8 apActiveTimePercentage;
    UINT8 staActiveTimePercentage;
    UINT8 wlrpanActiveTimePercentage;
}GSN_WIF_SYS_CMS_START_REQ_T;


/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief concurrent mode Start response message.
 * 
 *    response message structure of concurrent mode start command
*****************************************************************************/

typedef struct GSN_WIF_SYS_CMS_START_RSP_S
{
    UINT32 status;
}GSN_WIF_SYS_CMS_START_RSP_T;

/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief Temperature and PA supply voltage.
 *
 *    APP sends this message to WFW after measurements.
*****************************************************************************/
typedef struct GSN_WIF_SYS_TEMP_PAVOLT_IND_S
{
    UINT16 temperature; /**< in degree celsius */ //aaaa
    UINT16 paSupplyVolt; /**< */
} GSN_WIF_SYS_TEMP_PAVOLT_IND_T;

/**
 *****************************************************************************
 * @ingroup GsnWifSysDefs
 * @brief RF Calib data write.
 *
 *    WFW  sends this message to APP for storing RF calib data in to File system.
*****************************************************************************/
typedef struct GSN_WIF_SYS_RF_CALIB_DATA_WR_REQ_S
{
    UINT32 dataLen;
    UINT8  data[1];
    
} GSN_WIF_SYS_RF_CALIB_DATA_WR_REQ_T;


#ifdef __cplusplus
}
#endif
#endif /* _GSN_WIF_SYS_DEFS_H_ */






