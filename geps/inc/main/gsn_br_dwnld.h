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
* $RCSfile: gsn_br_dwnld.h,v $
*
* Description : Firmware Download mechanism header file
*****************************************************************************/

#ifndef _GSN_BR_DWNLD_H_
#define _GSN_BR_DWNLD_H_


/**
 ****************************************************************************
 * Define for initialize the sequence number. Used in order to detect the
 * very first message                                                        
 ****************************************************************************/
#define GSN_BR_DWNLD_SEQNUMBER_INVALID     0xCACA

/* Mask for the More bit in the OpCode   */
#define GSN_BR_DWNLD_MASK_OPCODE           0x7F
#define GSN_BR_DWNLD_MASK_MOREBIT          0x80

/* define for flagMoreBit_MB  */
#define GSN_BR_DWNLD_NO_MOREBIT            0
#define GSN_BR_DWNLD_MOREBIT_SET           1

#define GSN_BR_DWNLD_FLASH_UNKNOWN         0x0000


/* Just for the WIN32 compiler                                                          */
#if defined(TARGET_WIN32)
    #define DEFPACK
#else
    #define DEFPACK __packed
#endif

/* Opcode enumeration    */
typedef enum GSN_BR_DWNLD_OPCODE
{
    GSN_BR_DWNLD_OPCODE_DOWNLOAD = 1,
    GSN_BR_DWNLD_OPCODE_COPY,
    GSN_BR_DWNLD_OPCODE_EXECUTE,
    GSN_BR_DWNLD_OPCODE_ERRORIND, /* Error Indication    */
    GSN_BR_DWNLD_OPCODE_ACK
} GSN_BR_DWNLD_OPCODE;

/* Error type enumeration  */
typedef enum GSN_BR_DWNLD_STATUS_S
{
    GSN_BR_DWNLD_STATUS_OK   = 0,
    GSN_BR_DWNLD_STATUS_IDLE = GSN_BR_DWNLD_STATUS_OK,
    GSN_BR_DWNLD_STATUS_BUSY,
    GSN_BR_DWNLD_STATUS_ERROR_BADPARAM,
    GSN_BR_DWNLD_STATUS_ERROR_MB = 0x10,
    GSN_BR_DWNLD_STATUS_ERROR_TIMEOUT,
    GSN_BR_DWNLD_STATUS_ERROR_CHECKSUM,
    GSN_BR_DWNLD_STATUS_ERROR_FLASHFAILED,
    GSN_BR_DWNLD_STATUS_ERROR_SEQNUMBER,
    GSN_BR_DWNLD_STATUS_ERROR_FLASHOVERLAP,
    GSN_BR_DWNLD_STATUS_ERROR_WAITINGCOPY,
    GSN_BR_DWNLD_STATUS_RESETNAGAIN,
    GSN_BR_DWNLD_STATUS_ERROR_RESOURCES_UNAVAILABLE,
    GSN_BR_DWNLD_STATUS_ERROR_RESOURCES_FREE_FAILED
} GSN_BR_DWNLD_STATUS_T;

/*these macros are declared in gsn_br_dbg.h*/ 
#if 0
/* Message ID */
typedef enum GSN_BR_DBG_MSGID_S
{
    GSN_BR_DBG_READ_CMD = 0x01,
    GSN_BR_DBG_WRITE_CMD,
    GSN_BR_DBG_READ_MODIFY_WRITE_CMD,
    GSN_BR_DBG_DUMP_MEM_CMD,
    GSN_BR_DBG_READ_RSP = 0x011,
    GSN_BR_DBG_WRITE_RSP ,
    GSN_BR_DBG_READ_MODIFY_WRITE_RSP,
    GSN_BR_DBG_DUMP_MEM_RSP,
} GSN_BR_DBG_MSGID_T;
#endif
/* Message structure definitions  */
typedef DEFPACK struct GSN_BR_DWNLD_MSG_HEADER_S
{
    UINT8               OpCode;
    UINT8               SeqNumber;
} GSN_BR_DWNLD_MSG_HEADER_T;

typedef DEFPACK struct GSN_BR_DWNLD_MSG_ACK_S
{
    GSN_BR_DWNLD_MSG_HEADER_T Header;
} GSN_BR_DWNLD_MSG_ACK_T;

typedef DEFPACK struct GSN_BR_DWNLD_MSG_ERROR_S
{
    GSN_BR_DWNLD_MSG_HEADER_T Header;
    UINT16                    ErrorCode;
} GSN_BR_DWNLD_MSG_ERROR_T;

typedef DEFPACK struct GSN_BR_DWNLD_MSG_DOWNLOAD_S
{
    GSN_BR_DWNLD_MSG_HEADER_T Header;
    UINT32                    FileLength;
    UINT16                    BundleLength;
    UINT32                    BundleRamAddr;
    UINT8                     BundleData0;
} GSN_BR_DWNLD_MSG_DOWNLOAD_T;

typedef DEFPACK struct GSN_BR_DWNLD_MSG_COPY_S
{
    GSN_BR_DWNLD_MSG_HEADER_T Header;
    UINT32                    FlashAddr;
    UINT32                    Length;
    UINT32                    Addr;
    UINT32                    CheckSum; 
    UINT32                    SwapFlashAddr;
} GSN_BR_DWNLD_MSG_COPY_T;

typedef DEFPACK struct GSN_BR_DWNLD_MSG_EXECUTE_S
{
    GSN_BR_DWNLD_MSG_HEADER_T Header;
    UINT32                    Processor;
    UINT32                    Length;
    UINT32                    Addr;
    UINT32                    CheckSum; 
} GSN_BR_DWNLD_MSG_EXECUTE_T;

typedef union GSN_BR_DWNLD_MSG_S
{
    GSN_BR_DWNLD_MSG_HEADER_T   Header;
    GSN_BR_DWNLD_MSG_DOWNLOAD_T Download;
    GSN_BR_DWNLD_MSG_COPY_T     Copy;
    GSN_BR_DWNLD_MSG_EXECUTE_T  Execute;
    GSN_BR_DWNLD_MSG_ERROR_T    Error;
    GSN_BR_DWNLD_MSG_ACK_T      Ack;
} GSN_BR_DWNLD_MSG_T;


typedef void (*GSN_BR_DWNLD_PUSHFN)        (struct GSN_BR_HI_CONTEXT_S* HiContextPtr, UINT8* MsgPtr, UINT16 Len);
typedef void (*GSN_BR_DWNLD_LASTACTIONSFN) (struct GSN_BR_CTX_T* GsnBrContextPtr);
typedef void (*GSN_BR_DWNLD_NODEEPSLEEP)   (struct GSN_BR_CTX_T* GsnBrContextPtr);

typedef struct GSN_BR_DWNLD_CONTEXT_S
{
    /* external contexts references  */
    /* GSN Boot Rom Context pointer  */
    struct GSN_BR_CTX_S*          GsnBrContextPtr;

    /* Hi Context pointer            */
    struct GSN_BR_HI_CONTEXT_S*      HiContextPtr;

    /* The more bit indication is saved */
    UINT32                        flagMoreBit_MB;         

    GSN_BR_DWNLD_STATUS_T         status;
    UINT32                        lastSeqNumber;

    /* Timer used for time-out  */
    /* T_TIMER*       TimerPtr; */

    /* function pointer to return in HI  */
    GSN_BR_DWNLD_PUSHFN        PushFn;

    /* function to invoke before initiating last flash copy */
    GSN_BR_DWNLD_LASTACTIONSFN LastActionsFn;

    /* function to invoke before initiating a flash copy */
    GSN_BR_DWNLD_NODEEPSLEEP   NoDeepSleepFn;

    /* record the download status from one download to another  */
    UINT32            AdditionalInfoField; 

    UINT8*          pSramAddressReserved;
    
} GSN_BR_DWNLD_CONTEXT_T;

PRIVATE VOID
GsnBrDwnld_AckMsg (struct GSN_BR_DWNLD_CONTEXT_S   * const pThisDwnld,
                   union  GSN_BR_DWNLD_MSG_S const * const MsgPtr);

PRIVATE VOID
GsnBrDwnld_Error (struct  GSN_BR_DWNLD_CONTEXT_S   * const pThisDwnld,
                  GSN_BR_DWNLD_STATUS_T                    status);

PRIVATE UINT32
GsnBrDwnld_Checksum (struct GSN_BR_DWNLD_CONTEXT_S* const pThisDwnld,
                     union GSN_BR_DWNLD_MSG_S const * const ptMsg);

VOID
GsnBrDwnld_InitContext (struct GSN_BR_DWNLD_CONTEXT_S * const pThisDwnld,
                           struct GSN_BR_CTX_S *        const GsnBrContextPtr,
                           struct GSN_BR_HI_CONTEXT_S *    const HiContextPtr,
                           /* struct T_TIMER * const       TimerPtr, */
                           GSN_BR_DWNLD_NODEEPSLEEP const    DwnldNoDeepSleepFn,
                           GSN_BR_DWNLD_LASTACTIONSFN const  DwnldLastActionsFn,
                           GSN_BR_DWNLD_PUSHFN const         DwnldPushFn,
                           UINT32 const                    ErasePageThreshold,
                           UINT32 const                    FirmwareCaller,
                           UINT8                           ClockMultiplier);

void
GsnBrDwnld_PerformService (struct GSN_BR_DWNLD_CONTEXT_S*   const  DwnldContextPtr,
                           union  GSN_BR_DWNLD_MSG_S const* const MsgPtr);

#undef LINKAGE
#endif /*GSN_BR_DWNLD_H_                                                                     */
