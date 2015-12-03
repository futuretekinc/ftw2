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
* $RCSfile: gsn_br_dbg.h,v $
*
* Description : Firmware Download mechanism header file
*****************************************************************************/


#ifndef GSN_BR_DBG_H
#define GSN_BR_DBG_H


/*
 * CONSTANTS
 *******************************************************************************
 */

/* Just for the WIN32 compiler                                                          */
#if defined(TARGET_WIN32)
    #define DEFPACK
#else
    #define DEFPACK __packed
#endif


/* Message ID                                                        */
typedef enum GSN_BR_DBG_MSGID
{
    GSN_BR_DBG_READ_CMD = 0x01,
    GSN_BR_DBG_WRITE_CMD,
    GSN_BR_DBG_READ_MODIFY_WRITE_CMD,
    GSN_BR_DBG_DUMP_MEM_CMD,
    
    GSN_BR_DBG_REG_PEEK_REQ = 0x41,
    GSN_BR_DBG_REG_POKE_REQ,
    GSN_BR_DBG_MEM_READ_REQ,
    GSN_BR_DBG_MEM_WRITE_REQ,
    GSN_BR_DBG_EXEC_REQ,
    GSN_BR_DBG_FLASH_READ_REQ,
    GSN_BR_DBG_WLAN_START,
    GSN_BR_DBG_WLAN_STOP,
    GSN_BR_DBG_FLASH_ERASE_REQ,
    GSN_BR_DBG_OTP_WRITE_REQ,
    GSN_BR_DBG_OTP_READ_REQ,
    GSN_BR_DBG_FLASH_CHKSUM_REQ,
    GSN_BR_DBG_FLASH_ERASE_CHK_REQ,
    
    GSN_BR_DBG_READ_RSP = 0x011,
    GSN_BR_DBG_WRITE_RSP ,
    GSN_BR_DBG_READ_MODIFY_WRITE_RSP,
    GSN_BR_DBG_DUMP_MEM_RSP,
    
    GSN_BR_DBG_REG_PEEK_RSP = 0x81,
    GSN_BR_DBG_REG_POKE_RSP,
    GSN_BR_DBG_MEM_READ_RSP,
    GSN_BR_DBG_MEM_WRITE_RSP,
    GSN_BR_DBG_EXEC_RSP,
    GSN_BR_DBG_FLASH_READ_RSP,
    GSN_BR_DBG_WLAN_START_RSP,
    GSN_BR_DBG_WLAN_STOP_RSP,
    GSN_BR_DBG_FLASH_ERASE_RSP,
    GSN_BR_DBG_OTP_WRITE_RSP,
    GSN_BR_DBG_OTP_READ_RSP,
    GSN_BR_DBG_FLASH_CHKSUM_RSP,
    GSN_BR_DBG_FLASH_ERASE_CHK_RSP,

} GSN_BR_DBG_MSGID_T;

#define    GSN_BR_DBG_RSP_MASK          0x10
#define    GSN_BR_DBG_ACCESS_U8         8
#define    GSN_BR_DBG_ACCESS_U16        16
#define    GSN_BR_DBG_ACCESS_U32        32

#define    GSN_BR_DBG_BYTES_U8          (0x01)
#define    GSN_BR_DBG_BYTES_U16         (0x01 << 1)
#define    GSN_BR_DBG_BYTES_U32         (0x01 << 2)

#define    GSN_BR_DBG_RSP_HEADER_LEN    1

#define    DBG_READ_BUFFER_LEN_MAX      1514


#define GSN_REG_VAL_U8(val)  (*(volatile UINT8  *)val)
#define GSN_REG_VAL_U16(val) (*(volatile UINT16 *)val)
#define GSN_REG_VAL_U32(val) (*(volatile UINT32 *)val)

/*
 * TYPES
 *******************************************************************************
 */

typedef DEFPACK struct DBG_BR_PARAM
{
    UINT8      MessageId;          /* Message Identifier                         */
    UINT32     StartAddress;
    UINT8      AccessType;
}DBG_BR_PARAM;



typedef DEFPACK struct DBG_BR_READ_PARAM
{
    DBG_BR_PARAM    Param;
} DBG_BR_READ_PARAM;

typedef DEFPACK struct DBG_BR_WRITE_PARAM
{
    DBG_BR_PARAM    Param;
    UINT32     Value;
} DBG_BR_WRITE_PARAM;

typedef DEFPACK struct DBG_BR_RMWRITE_PARAM
{
    DBG_BR_PARAM    Param;
    UINT32     Value;
    UINT32     Mask;
} DBG_BR_RMWRITE_PARAM;

typedef DEFPACK struct DBG_BR_DUMPMEM_PARAM
{
    DBG_BR_PARAM    Param;
    UINT32     Size;
} DBG_BR_DUMPMEM_PARAM;

typedef union DBG_BR_MSG
{
    DBG_BR_PARAM            Param;
    DBG_BR_READ_PARAM       Read;
    DBG_BR_WRITE_PARAM      Write;
    DBG_BR_RMWRITE_PARAM    RMWrite;
    DBG_BR_DUMPMEM_PARAM    DumpMem;
} DBG_BR_MSG;


typedef DEFPACK struct DBG_BR_READRESPONSE_PARAM
{
    UINT8      MessageId;          /* Message Identifier                         */
    UINT8      Length;             /* length of param                            */
    UINT32     Value;
} DBG_BR_READRESPONSE_PARAM;


/* Global                                                                     */


/*
 * MACROS
 *******************************************************************************
 */

#define MEM_WR_8(add, value)         ((*(volatile UINT8 *)(add)) =  (value))
#define MEM_WR_16(add, value)        ((*(volatile UINT16 *)(add)) =  (value))
#define MEM_WR_32(add, value)        ((*(volatile UINT32 *)(add)) =  (value))
#define MEM_RD_8(add)                (*(volatile UINT8 *)(add))
#define MEM_RD_16(add)               (*(volatile UINT16 *)(add))
#define MEM_RD_32(add)               (*(volatile UINT32 *)(add))


/*
 * GLOBAL VARIABLES
 *******************************************************************************
 */

typedef struct DBG_BR_CONTEXT
{
    struct GSN_HI_CONTEXT_S*  HiContextPtr;

}DBG_BR_CONTEXT,*DBG_BR_CONTEXT_PTR;


typedef void (*GSN_BR_DBG_FUNC_PTR)(struct GSN_HI_CONTEXT_S*      HiContextPtr,
                                    UINT8*                        DataPtr,
                                    UINT16                        DataLen);

#endif /* GSN_BR_DBG_H */
