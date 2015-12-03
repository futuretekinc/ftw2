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
* $RCSfile: gsn_i2c.h,v $
*
* Description : This file contains function declarations for I2C Driver.
*****************************************************************************/


#ifndef _GSNI2C_H_
#define _GSNI2C_H_

#ifdef  __cplusplus
extern "C" {
#endif


/************************ File inclusion *************************************/


/*****************************************************************************/

# include"gsn_includes.h" 
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
//#include "core\osal\gsn_osal_threadx.h"
#include "drivers/clk_ctl/gsn_clk_ctl.h"


/**
******************************************************************************
*  @file gsn_i2c.h
*  @brief Public Header Containing i2c Driver Functions.
*
*****************************************************************************/


 /**
 *****************************************************************************
 * @ingroup driversdoc
 *
 * @{
 *****************************************************************************/


/**
*****************************************************************************
*   @defgroup GsnI2C GSN I2C API
*   @brief API Functions for the Use of the I2C Interface.
*
*****************************************************************************/

/**
 *****************************************************************************
 * 
 * @} 
 *****************************************************************************/
	
	



/************************ Public MACRO ***************************************/

#define I2C_NCO_VALUE               0x01
#define I2C_CLK_SEL_VALUE           0x00
#define I2C_STEP                    0x40070078
#define I2C_STEP_VALUE_100K         0x25000//0x083126
#define I2C_STEP_VALUE_400K         0x20c49c
#define I2C_STEP_VALUE_34M          0x116827b

#define MAX_FIFO_SIZE               128
#define HOLD_CLOCK_VALUE            0x05  
#define MASTER_CODE_VALUE           0x0B
#define BLOCK_COUNT_VALUE           12   
  
#define I2C_CLEARIRQ_BITMASK        (0x00)
#define I2C_CLEARSTATUSIRQ_BITMASK  (0xff)  
#define GSN_I2C_ERATE_100KBITS	     0        /* 100Kbps */
#define GSN_I2C_ERATE_400KBITS	     1        /* The exact value - 392.86 Kbps*/
#define GSN_I2C_ERATE_HSE	     2        /* High speed mode - 3.4 Mbps*/  

  
/*****************************************************************************/


/************************ Public data types **********************************/

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief (Pclk) Clock Count for the Slave to maintain data hold time.
 *
 *****************************************************************************/

typedef enum GSN_I2C_HOLD_CLK_CNT
{
    GSN_I2C_DATA_HOLD_CLOCK_COUNT  = HOLD_CLOCK_VALUE
} GSN_I2C_HOLD_CLK_CNT_T;


/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Addressing format Selector in the Control Register.
 *
 *****************************************************************************/

typedef enum GSN_I2C_ADMOD
{
    GSN_I2C_ADMOD_7BITS,    /* 7-bit address mode */
    GSN_I2C_ADMOD_10BITS    /* 10-bit address mode */
} GSN_I2C_ADMOD_T;


/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Master / Slave Selector in Control Register.
 *
 *****************************************************************************/
typedef enum GSN_I2C_MS_MODE
{
    GSN_I2C_MNS_SLAVE,    /* Slave Mode */
    GSN_I2C_MNS_MASTER    /* Master Mode */
} GSN_I2C_MS_MODE_T;


/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief E-rate Enumeration.
 *
 *****************************************************************************/

//typedef enum GSN_I2C_ERATE
//{
 // GSN_I2C_ERATE_100KBITS,    /* 100Kbps */ 
 // GSN_I2C_ERATE_400KBITS,    /* The exact value - 392.86 Kbps*/
 // GSN_I2C_ERATE_HSE          /* High speed mode - 3.4 Mbps*/
//} GSN_I2C_ERATE_T;


/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Speed Setting Enumeration.
 *
 *****************************************************************************/

typedef enum GSN_I2C_HIGH_SPEED_ENABLE
{										
  GSN_I2C_FAST_MODE_ENABLE,     /* Fast Mode enable */
  GSN_I2C_HIGH_SPEED_ENABLE	/* High speed enable */					
} GSN_I2C_HIGH_SPEED_ENABLE_T;

/**
*****************************************************************************
 * @ingroup GsnI2C
 * @brief Read/Write Selector in the Control Register.
 *
 *****************************************************************************/
typedef enum GSN_I2C_RWOP
{
    GSN_I2C_RWOP_WRITE,    /*To select write mode */
    GSN_I2C_RWOP_READ      /*To select read mode */	
} GSN_I2C_RWOP_T;

 /**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Abort the current operation selection Enumeration.(Master Mode only)
 *
 *****************************************************************************/
typedef enum GSN_I2C_ABORTCUROP
{
    GSN_I2C_AbortCurOp_reset,  	
    GSN_I2C_AbortCurOp_set		
	
} GSN_I2C_ABORTCUROP_T;

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Byte count override Setting Enumeration.(Master Mode only)
 *
 *****************************************************************************/
 typedef enum GSN_I2C_BYTECNTORIDE
 {
     GSN_I2C_BYTECNT_SET,       /*set byte count override is used*/	  	
     GSN_I2C_BLOCK_SET          /*set block mode */
 } GSN_I2C_BYTECNTORIDE_T;
 
 /**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Random/Current address Selector in Control Register (Master Mode only).
 *
 *****************************************************************************/
 
typedef enum GSN_I2C_RCAS
{
    GSN_I2C_RCAS_CURRENTADD,    /* read at the current address */
    GSN_I2C_RCAS_RANDOMADD      /* write the address */ 
} GSN_I2C_RCAS_T;				

 /**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Memory address selection Enumeration.
 *
 *****************************************************************************/
typedef enum GSN_I2C_MEMADD_SEL
{
    GSN_I2C_MEMADD_SINGLE,      /*set single byte memory address */
    GSN_I2C_MEMADD_DOUBLE       /*set two bytes memory address */
} GSN_I2C_MEMADD_SEL_T;
 
/**
 ****************************************************************************
 * @ingroup GsnI2C
 * @brief Gsn I2C Clock selection.
 *
 *    This enum defines the 3 different I2C clock selections.
 * @see  GSN_I2C_CLK_SEL_T.
 ****************************************************************************/
typedef enum GSN_I2C_CLK_SEL
{
    GSN_I2C_CLK_HSRC,    /*High speed RC clock*/
    GSN_I2C_CLK_XTAL,    /*Crystal clock*/
    GSN_I2C_CLK_PLL      /*PLL clock*/
}GSN_I2C_CLK_SEL_T;

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Asynchronous Event Status Enumeration.
 *
 *****************************************************************************/
typedef enum GSN_I2C_ASYN_EVENT_STATUS
{
    GSN_I2C_MASTER_TO_SLAVE_TRANSITION = 0xF0,
    GSN_I2C_SEND_DATA,
    GSN_I2C_RECV_DATA,
} GSN_I2C_ASYN_EVENT_STATUS_T;

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief I2C Status Enumeration.
 *
 *****************************************************************************/
typedef enum GSN_I2C_STATUS
{
    GSN_I2C_STATUS_OK           = 0x00,
    GSN_I2C_STATUS_ERR,
    GSN_I2C_STATUS_OK_ENDTRANS,
    GSN_I2C_STATUS_OK_FREE,

    GSN_I2C_STATUS_ERR_BADPARAM = 0x10,
    GSN_I2C_STATUS_ERR_INVALID,
    GSN_I2C_STATUS_ERR_OVERSIZE,
    GSN_I2C_STATUS_ERR_ARBITRATION,

    GSN_I2C_STATUS_ERR_BUSBUSY  = 0x20,
    GSN_I2C_STATUS_ERR_NOACK,
    GSN_I2C_STATUS_ERR_OVERREC,

    GSN_I2C_STATUS_MAX
} GSN_I2C_STATUS_T;


/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief I2C Callback Type.
 *
 *****************************************************************************/
typedef void ( *GSN_I2C_CALLBACK_FP )( VOID* ctx,GSN_I2C_STATUS_T);

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief I2C Asynchronous Event Callback Type.
 *
 *****************************************************************************/
typedef void ( *GSN_I2C_ASYNEVENT_CALLBACK_FP )( GSN_I2C_ASYN_EVENT_STATUS_T );

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief I2C Data / Status Structure.
 *
 *****************************************************************************/
typedef struct GSN_I2C
{

   UINT32                        pReg;	/* register pointer */
   BOOL                          readFlag;  /*flag to indicate read status*/
   BOOL                          writeFlag; /*flag to indicate write status*/
   GSN_I2C_MS_MODE_T             masterOrSlave; /* mode of operation */
   UINT8*			 DataWriteBuffer; /* data to write*/ 	
   UINT8*                        DataReadBuffer;  /* data read */
   GSN_OSAL_SEM_T                synchronousSemId;  /* semaphore to enable synchronous operation */
   UINT8                         numBytesToTransfer; /* number of bytes that are to be transferred */
   UINT8                         numBytesTransferred; /* number of bytes actually transferred */
   GSN_I2C_CALLBACK_FP           readWriteCallBack;   /* callback function for normal operation */
   VOID*                         ctxt;	 /* pointer to argument for callback */
   GSN_I2C_ASYNEVENT_CALLBACK_FP asynEventCallBack;  /* callback function for asynchronous events */
   GSN_I2C_STATUS_T              readWriteStatus;  /* status information */
   GSN_I2C_RCAS_T      	         RandomOrCurrentAddr; /* random or current address */
   GSN_I2C_MEMADD_SEL_T          MemAddSel;    /*single or two byte memory address */
   GSN_I2C_CLK_SEL_T             pclockSelect;
   GSN_CLK_CTL_CTX_T             *pclkCtlCtx;   /* Clock Context */    
   
} GSN_I2C_T;

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief I2C Configuration Structure.
 *
 *****************************************************************************/
typedef struct GSN_I2C_CONFIG
{
    GSN_I2C_MS_MODE_T    gsnI2cMode;
    UINT32           	 gsnI2cSlaveAddr;
    UINT16               gsnI2cSlaveLocAddr;
    UINT16               gsnI2cAddrLocInSlave;
    UINT32               gsnI2cRate;
    GSN_I2C_ADMOD_T    	 gsnI2cAddrMode;
    GSN_I2C_RCAS_T       gsnI2cRandomCurrentAddr; 
    GSN_I2C_MEMADD_SEL_T gsnI2cMemAddSel;
    GSN_I2C_CLK_SEL_T    clockSelect;
    GSN_I2C_HOLD_CLK_CNT_T  gsnI2cSlaveDataHoldClkCnt;
    
}GSN_I2C_CONFIG_T;


/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief I2C Handle (Identifier for an Initialized I2C Interface).
 *
 *****************************************************************************/ 
typedef struct GSN_I2C_HANDLE
{
    UINT32 gsnI2cInitialized;
    GSN_I2C_T gsnI2c;

}GSN_I2C_HANDLE_T;


/**
 *****************************************************************************
 * @} 
 *
 *****************************************************************************/


/*****************************************************************************/

/************************ Public variable ************************************/

/*****************************************************************************/

/*************** Public Function prototype with function header **************/


/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief I2c Driver Open.
 *    This function opens an i2c port.
 *    This function initializes the corresponding i2c object.
 * @param ptI2cHandle              - IN pointer to i2c handle.
 * @param ptI2cConfig              - IN pointer to i2c config structure.
 * @param asynEventCallBack        - IN user application call back function.
 * @return GSN_I2C_STATUS_ERROR  on error, GSN_I2C_STATUS_OK on success
 * 
 * @note
 *****************************************************************************/

PUBLIC GSN_STATUS
GsnI2c_Open (GSN_I2C_HANDLE_T* ptI2cHandle,GSN_I2C_CONFIG_T* ptI2cConfig,
              GSN_I2C_ASYNEVENT_CALLBACK_FP asynEventCallBack);
         


/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief i2c Read function.
 *    1. prepare for transmission.
 *    2. Start data reception by enabling the Rx interrupt.
 *    3. wait on the semaphore for a synchronous read.
 * @param i2cHandle       - IN pointer to hold i2c handle.
 * @param userBuffer      - IN pointer to buffer for read data.
 * @param noOfBytesToRead - IN no of bytes to read.
 * @param blockMode       - IN block mode
 * @param rdCallBackFunc  - IN user application call back function.
 * @param ctext           - IN context structure passed to callback function.
 * @return UINT32 the number of bytes received.
 * @note
 *****************************************************************************/
UINT32
GsnI2c_Read( GSN_I2C_HANDLE_T* i2cHandle, UINT8 *userBuffer,
             UINT8 noOfBytesToRead,BOOL blockMode,
             GSN_I2C_CALLBACK_FP rdCallBackFunc,VOID* ctext);

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief i2c Write Function.
 *    1. prepare for transmission.
 *    2. Start data transmission by enabling the Tx interrupt.
 *    3. wait on the semaphore for a synchronous write.
 * @param i2cHandle       - IN pointer to hold i2c handle.
 * @param userBuffer      - IN pointer to data buffer.
 * @param noOfBytesToWrite - IN no of bytes to write.
 * @param writeCallBackFunc - IN user application call back function.
 * @param ctext             - IN context structure passed to callback function.
 * @return UINT32 the number of bytes transmitted..
 * @note
 *****************************************************************************/
UINT32
GsnI2c_Write ( GSN_I2C_HANDLE_T* i2cHandle,
                UINT8* userBuffer,
                UINT8 noOfBytesToWrite,
                GSN_I2C_CALLBACK_FP writeCallBackFunc,
                VOID* ctext);

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief i2c Driver Close.
 *    This function closes the driver.
 *    This function deletes the semaphores and disables the corresponding
 *     i2c port.
 * @param i2cHandle           - IN pointer to handle.
 * @return GSN_I2C_STATUS_OK on success
 * @return GSN_I2C_STATUS_ERR_INVALID on error.
 * @note
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnI2c_Close(GSN_I2C_HANDLE_T* i2cHandle);


/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Set i2c driver address mode.
 *    This function sets the address mode of the i2c port.
 * @param gsnI2chandle             - IN pointer to handle.
 * @param addrMode                 - IN address mode format.
 * @return GSN_I2C_STATUS_OK
 * @note
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnI2c_addModeSet(GSN_I2C_HANDLE_T* gsnI2chandle, GSN_I2C_ADMOD_T addrMode);

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Set i2c Master-Slave Mode.
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnI2c_MSModeSet(GSN_I2C_HANDLE_T* gsnI2chandle, 
                    GSN_I2C_MS_MODE_T gsnI2cMSMode);

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Set i2c Single/Double memory address.
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnI2c_MemAddSet(GSN_I2C_HANDLE_T* gsnI2chandle,
                    GSN_I2C_MEMADD_SEL_T gsnI2cMemAddSel );

/*****************************************************************************
 * @ingroup GsnI2C
 * @brief GsnI2c Byte count override bit Set/reset 
 *    
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnI2c_ByteOverride(GSN_I2C_HANDLE_T* gsnI2chandle,
                        GSN_I2C_BYTECNTORIDE_T gsnI2cBytecntOride);

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Set Destination Slave Address.
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnI2c_DestSlaveAddSet(GSN_I2C_HANDLE_T* gsnI2chandle, UINT32 gsnI2cSlaveAddr);

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Set Local Slave Address.
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnI2c_SlaveLocAddrSet(GSN_I2C_HANDLE_T* gsnI2chandle,
                          UINT16 gsnI2cSlavelocAddr);

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Set Address in Slave location.
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnI2c_AddrInSlave(GSN_I2C_HANDLE_T* gsnI2chandle,
                      UINT16 gsnI2cAddrLocInSlave );
/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Set i2c High speed Mode enable.
 *
 *****************************************************************************/ 
PUBLIC VOID
GsnI2c_High_speed_enableSet(GSN_I2C_HANDLE_T* gsnI2chandle,
                                GSN_I2C_HIGH_SPEED_ENABLE_T HSenable);

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief  Random/Current address selection.
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnI2c_RandomCurrentAddrSet(GSN_I2C_HANDLE_T* gsnI2chandle,
                                GSN_I2C_RCAS_T gsnI2cRepStartEnable );

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Set Data Rate.
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnI2c_RateSet(GSN_I2C_HANDLE_T* gsnI2chandle, UINT32 gsnI2cRate, GSN_I2C_CLK_SEL_T clockSelect);

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Get Local Slave Address.
 *
 *****************************************************************************/
PUBLIC GSN_STATUS
GsnI2c_OwnSlaveAddGet(GSN_I2C_HANDLE_T* gsnI2chandle, 
                        UINT16 gsnI2cSlavelocAddr);
/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Get Master/Slave mode.
 *
 *****************************************************************************/
GSN_I2C_MS_MODE_T
GsnI2c_MSModeGet(GSN_I2C_HANDLE_T* gsnI2chandle);

/**
 *****************************************************************************
 * @ingroup GsnI2C
 * @brief Get Address Mode (7 or 10 Bits)
 *
 *****************************************************************************/
GSN_I2C_ADMOD_T
GsnI2c_addModeGet(GSN_I2C_HANDLE_T* gsnI2chandle);


PUBLIC VOID
__GsnI2c_Isr();

#ifdef  __cplusplus
    }
#endif
#endif /* _GSNI2C_H_ */




