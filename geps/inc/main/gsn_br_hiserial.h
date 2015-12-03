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
* $RCSfile: gsn_br_hiserial.h,v $
*
* Description : This file contains boot rom code for serial interface.
*****************************************************************************/

#ifndef _GSN_BR_SERIAL_H_
#define _GSN_BR_SERIAL_H_

typedef UINT32 GSN_SERIAL_FCT_READ   (VOID*        pSerialInterfaceHandle,
                                      UINT8*       puBuffer,
                                      UINT32       noOfBytesToRead,
                                      BOOL         blockRead,
                                      GSN_CB32_FCT ptCallBackFunc,
                                      VOID*        ctx);

typedef UINT32 GSN_SERIAL_FCT_WRITE  (VOID*        pSerialInterfaceHandle,
                                      UINT8*       puBuffer,
                                      UINT32       noOfBytesToWrite,
                                      GSN_CB32_FCT ptCallBackFunc,
                                      VOID*        ctx);

typedef struct HI_SERIAL_INTERFACE_API
{
    UINT32 (*Read)    (VOID*        pSerialInterfaceHandle,
                       UINT8*       puBuffer,
                       UINT32       noOfBytesToRead,
                       BOOL         blockRead,
                       GSN_CB32_FCT ptCallBackFunc,
                       VOID*        ctx);
    
    UINT32 (*Write)   (VOID*        pSerialInterfaceHandle,
                       UINT8*       puBuffer,
                       UINT32       noOfBytesToWrite,
		               GSN_CB32_FCT ptCallBackFunc,
                       VOID*        ctx);
 
} HI_SERIAL_INTERFACE_API;

/* it is better for the magic number to be only one char to avoid receiving not aligned */
/* starts and therefore never synchronizing.  with one char start we must be able to    */
/* detect errors on header in order to reduce chances of treating wrong frames          */

#define HISERIAL_START_SIZE 1

typedef struct HISERIAL_START {
    UINT8 Value[HISERIAL_START_SIZE];
} HISERIAL_START;

#define HISERIAL_START_MAGIC_NUMBER 0xA5
#define HISERIAL_START_TEST(__ptr) ((__ptr)->Value[0] == HISERIAL_START_MAGIC_NUMBER)
#define HISERIAL_START_SET(__ptr)   (__ptr)->Value[0] = HISERIAL_START_MAGIC_NUMBER

#define HISERIAL_CHKSUM UINT8
#define HISERIAL_CHKSUM_SIZE sizeof(HISERIAL_CHKSUM)
                           
/* HI context structures                                                                */
typedef struct GSN_HI_SERIAL_CONTEXT_S
{
    GSN_BR_HI_FRAME_DESC_T*   RxHiFrameDescPtr;
    GSN_BR_HI_FRAME_DESC_T*   TxHiFrameDescPtr;

    /* buffer intended to hold the START header [0xA5] over UART interface */
    UINT8                   RxStartHeader [HISERIAL_START_SIZE];
    UINT8                   RxHiHeader [HI_FRAME_HEADER_SIZE + HISERIAL_CHKSUM_SIZE];
    
    UINT8                   TxHiHeader [HISERIAL_START_SIZE + HI_FRAME_HEADER_SIZE + HISERIAL_CHKSUM_SIZE];

    VOID*                   pSerialCtxtInterfaceHandle;  

    GSN_CB_T                Rxcallback;
    GSN_CB_T                Txcallback;

    HI_SERIAL_INTERFACE_API HiSerialInterfacesApi;

    UINT8                   HeaderChecksum;

    UINT8                   TxCallBackTemp;
 
    UINT8                   rxBypassFlag;
} GSN_BR_HI_SERIAL_CONTEXT_T;



/*
 * PROTOTYPES
 ****************************************************************************************
 */
VOID GsnBrHi_SerialInitContext   (GSN_BR_HI_SERIAL_CONTEXT_T*   HiSerialContextPtr,
                             VOID*                      DriverPtr,
                             GSN_SERIAL_FCT_READ*       pFunctionRead,
                             GSN_SERIAL_FCT_WRITE*      pFunctionWrite);

VOID GsnBrHi_SerialReceiveHeader (VOID*                      pHiDriverContext,
                             GSN_BR_HI_FRAME_DESC_T*       HiFrameDescPtr,
                             GSN_CB_T*                  pCallback);

VOID GsnBrHi_SerialReceiveData   (VOID*                      pHiDriverContext,
                             GSN_BR_HI_FRAME_DESC_T*       HiFrameDescPtr,
                             GSN_CB_T*                  pCallback);

VOID GsnBrHi_SerialSend          (VOID*                      pHiDriverContext,
                             GSN_BR_HI_FRAME_DESC_T*       HiFrameDescPtr,
                             GSN_CB_T*                  pCallback);

VOID GsnBrHi_SerialDirectSend    (VOID*                      pHiDriverContext,
                             GSN_BR_HI_FRAME_DESC_T*       HiFrameDescPtr,
                             GSN_CB_T*                  pCallback);



VOID GsnBrHi_SerialReceiveStartCb (VOID*                     pThis,
                              UINT32                    nBytesRead);

VOID GsnBrHi_SerialReceiveHeaderCb (VOID*                    pThis,
                              UINT32                    nBytesRead);

VOID GsnBrHi_SerialReceiveDataCb   (VOID*                    pThis,
                               UINT32                   nBytesRead);

VOID GsnBrHi_SerialWriteCb         (VOID*                    pThis,
                               UINT32                   nBytesWrite);

#endif //_GSN_BR_SERIAL_H_
