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
* $RCSfile: gsn_br_hi.h,v $
*
* Description : This file contains the host interface for boot rom.
*****************************************************************************/

#ifndef GSN_BR_HI_H_
#define GSN_BR_HI_H_

/*   CONSTANTS                 **********************************************************/

/* HI interfaces                                                                        */
#define HI_MB_IF                        0x00
#define HI_UART0_IF                     0x01
#define HI_UART1_IF                     0x02
#define HI_WLAN_IF                      0x03
#define HI_SPI_IF                       0x04
#define HI_MAX_IF                       0x05
#define HI_DEFAULT_IF                   0xFF

/* HI classes                                                                           */
#define HI_HEADER_CLASS_MASK            0xFF
#define HI_HEADER_DATA_CLASS            0x00
#define HI_HEADER_KERNEL_CLASS          0x01
#define HI_HEADER_DWNLD_CLASS           0x02
#define HI_HEADER_DEBUG_CLASS           0x03
#define HI_HEADER_DATACFM_CLASS         0x04
#define HI_HEADER_ABORT_CLASS           0x05
#define HI_HEADER_TRACE_CLASS           0x06
#define HI_HEADER_ROMDEBUG_CLASS        0x07
#define HI_HEADER_POLL_CLASS            0x0E
#define HI_HEADER_CLASS_NUM             0x0F

/* possible allocation selection                                                        */
#define HI_NO_ALLOC                         0x00
#define HI_HEAP_ALLOC                       0x01
#define HI_TXPACKET_ALLOC                   0x02
#define HI_RXPACKET_ALLOC                   0x03
#define HI_DEBUG_ALLOC                      0x04

/* HI SPECIFIC STATUS                                                                   */
#define HI_ADMP_ERROR                    ((CO_STATUS)(CO_STATUS_GROUP_HI        + 2))
#define HI_ASSERT_FAIL                   ((CO_STATUS)(CO_STATUS_GROUP_HI        + 3))

#define HI_HEADER_CHECK_CLASS(class)    (((((class)&HI_HEADER_CLASS_MASK)>=HI_HEADER_DATA_CLASS)&& \
                                          (((class)&HI_HEADER_CLASS_MASK)<HI_HEADER_CLASS_NUM))?TRUE:FALSE)

#define HI_DBG_HEADER_LEN               (sizeof(DBG_MESSAGE_HDR))

/* Number of descriptors should be one more than actual required                        */
#define GSN_HI_FRAME_DESC_MAX               0x04

/* Rx Buffer                                                                            */
#define HI_NUMBER_BUFFER        4
#define HI_MASK_BUFFER          0x03
#define HI_TRANSFER_BUFFER_SIZE 1600

/*   TYPES                     **********************************************************/
/* MANDATORY: the following structure must be naturally PACKED                          */
typedef struct GSN_BR_HI_HEADER_S
{
    UINT8              Class;      /* HI frame class                                       */
    UINT8              Reserved;   /* HI frame reserved space                              */
    UINT16             AddInfo;    /* HI frame additional info                             */
    UINT16             Len;        /* HI frame len                                         */
} GSN_BR_HI_HEADER_T;

/* HI frame descriptor                                                                  */
/* MANDATORY: the Header element MUST be first to make sure it is aligned on 32 bits    */
typedef struct GSN_BR_HI_FRAME_DESC_S
{
    GSN_BR_HI_HEADER_T    Header;     /* Header of the frame                                  */
    UINT8              Interface;  /* Interface on which the frame is rx'd or tx'd         */
    UINT8              Allocation; /* type of allocation of the buffer                     */
    UINT8             *Ptr;        /* Buffer pointer                                       */
    UINT32             Hdl;        /* Buffer handle (only used in case of DATA packet)     */
} GSN_BR_HI_FRAME_DESC_T;

typedef struct GSN_HI_BR_RESOURCES_S
{
    UINT16 * CmdIdPtr;
    UINT8  * CmdParamPtr;
    UINT16 * EvtIdPtr;
    UINT8  * EvtParamPtr;
} GSN_HI_BR_RESOURCES_T;


typedef struct GSN_BR_HI_CALLBACK_PARAM_S
{
    BOOL               TxRxOK;
    BOOL               NeedBufferAllocation;
    GSN_BR_HI_FRAME_DESC_T* HiFrameDescPtr;
}GSN_BR_HI_CALLBACK_PARAM_T;

typedef struct GSN_BR_HI_CONTEXT_S
{
    GSN_BR_HI_FRAME_DESC_T TxFrameDescPool[GSN_HI_FRAME_DESC_MAX-1] ;

    /* these are for managing the tx frame descriptors */
    GSN_RING_BUF_T      TxQueue;
    GSN_RING_BUF_HNDL_T TxQueueHandle;
    GSN_BR_HI_FRAME_DESC_T *TxQueueBuf[GSN_HI_FRAME_DESC_MAX] ;

    GSN_RING_BUF_T      TxFreeQueue;
    GSN_RING_BUF_HNDL_T TxFreeQueueHandle;
    GSN_BR_HI_FRAME_DESC_T *TxFreeQueueBuf[GSN_HI_FRAME_DESC_MAX] ;


    GSN_BR_HI_FRAME_DESC_T RxFrameDescPool[GSN_HI_FRAME_DESC_MAX-1] ;

    /* these are for managing the rx frame descriptors */
    GSN_RING_BUF_T      RxQueue;
    GSN_RING_BUF_HNDL_T RxQueueHandle;
    GSN_BR_HI_FRAME_DESC_T *RxQueueBuf[GSN_HI_FRAME_DESC_MAX] ;

    GSN_RING_BUF_T      RxFreeQueue;
    GSN_RING_BUF_HNDL_T RxFreeQueueHandle;
    GSN_BR_HI_FRAME_DESC_T *RxFreeQueueBuf[GSN_HI_FRAME_DESC_MAX] ;
    
    /* Pool packet Buffers                                                              */
    BOOL                TxInProgress ;

    /* middle level driver (hi_uart, hi_mb, hi_spi, hi_wlan etc...)                     */
    /* HI Download context                                                              */
    struct GSN_BR_DWNLD_CONTEXT_S*   DwnldContextPtr;

    /* Save the current interface used                                                  */
    UINT8                  CurrentInterface;

#if 0
    /* Rx buffer                                                                        */
    UINT8                  RxBuffer[HI_NUMBER_BUFFER-1][HI_TRANSFER_BUFFER_SIZE];
    UINT8                  RxBufferNext;


    /* Tx buffer                                                                        */
    UINT8                  TxBuffer[HI_NUMBER_BUFFER-1][HI_TRANSFER_BUFFER_SIZE];
#endif

} GSN_BR_HI_CONTEXT_T;

#define HI_FRAME_HEADER_SIZE            (sizeof(GSN_BR_HI_HEADER_T))

/*
 * PROTOTYPES
 ****************************************************************************************
 */

/* callback functions for HI interfaces support                                         */
void GsnBrHi_ReceiveHeaderCb (void*    pThis,
                         const void* pParam);

void GsnBrHi_ReceiveDataCb (void*    pThis,
                       const void* pParam);

void GsnBrHi_SendCb (void*    pThis,
                const void* pParam);

void GsnBrHi_PushRomDebugClass (GSN_BR_HI_CONTEXT_T*                HiContextPtr,
                             UINT8*                  DataPtr,
                             UINT16                  DataLen);

void GsnBrHi_PushDwnldClass (GSN_BR_HI_CONTEXT_T* HiContextPtr,
                          UINT8*         MsgPtr,
                          UINT16         Len);

void GsnBrHi_Background (GSN_BR_HI_CONTEXT_T* HiContextPtr);

void
GsnBrHi_InitContext (struct GSN_BR_HI_CONTEXT_S*    const HiContextPtr,
                struct GSN_BR_DWNLD_CONTEXT_S* const DwnldContextPtr);
void GsnBrHi_FreeBuffer (GSN_BR_HI_CONTEXT_T*    HiContextPtr,
                    GSN_BR_HI_FRAME_DESC_T* HiFrameDescPtr);

/* merging functions                                                                    */
void GsnBrHi_MergeReceiveHeader (GSN_BR_HI_CONTEXT_T* HiContextPtr,
                            UINT8       Interface);

void GsnBrHi_MergeReceiveData (GSN_BR_HI_CONTEXT_T*    HiContextPtr,
                          UINT8          Interface,
                          GSN_BR_HI_FRAME_DESC_T* HiFrameDescPtr);

void GsnBrHi_MergeSend (GSN_BR_HI_CONTEXT_T* HiContextPtr);

/* initialization functions                                                             */
void GsnBrHi_InitEmbeddedFifo (GSN_BR_HI_CONTEXT_T* HiContextPtr);

/* receive FIFO extraction functions                                                    */
void GsnBrHi_PopDwnldClass (GSN_BR_HI_CONTEXT_T*    HiContextPtr,
                          GSN_BR_HI_FRAME_DESC_T* HiFrameDescPtr);

void GsnBrHi_PopKernelClass (GSN_BR_HI_CONTEXT_T*    HiContextPtr,
                        GSN_BR_HI_FRAME_DESC_T* HiFrameDescPtr);

void GsnBrHi_PopDataClass (GSN_BR_HI_CONTEXT_T*    HiContextPtr,
                      GSN_BR_HI_FRAME_DESC_T* HiFrameDescPtr);

void GsnBrHi_Pop (GSN_BR_HI_CONTEXT_T* HiContextPtr);

void GsnBrHi_PushDebug (GSN_BR_HI_CONTEXT_T* HiContextPtr) ;

GSN_STATUS GsnBrHi_Push (GSN_BR_HI_CONTEXT_T* HiContextPtr,
                   UINT8        Class,
                   UINT16       AddInfo,
                   UINT16       Len,
                   UINT8        Allocation,
                   UINT32       Hdl,
                   UINT8*       Ptr);


#endif //GSN_BR_HI_H_
