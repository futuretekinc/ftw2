
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
* $RCSfile: gsn_br_serial_int.h,v $
*
* Description : Wrapper module for SPI to work with HI
*****************************************************************************/

#ifndef _GSN_BR_SERIAL_INT_H_
#define _GSN_BR_SERIAL_INT_H_

UINT32
GsnBrSerialInt_UartRead ( VOID*        pSerialIntHandle,
                  UINT8*       puBuffer,
                  UINT32       noOfBytesToRead,
                  BOOL         blockRead,
                  GSN_CB32_FCT ptCallBackFunc,
                  VOID*        ctx );

UINT32
GsnBrSerialInt_UartWrite ( VOID*        pSerialIntHandle,
                   UINT8*       puBuffer,
                   UINT32       noOfBytesToWrite,
                   GSN_CB32_FCT ptCallBackFunc,
                   VOID*        ctx );

UINT32
GsnBrSerialInt_SpiRead   (VOID*         pSerialIntHandle,
                  UINT8*        puBuffer,
                  UINT32        noOfBytesToRead,
                  BOOL          blockRead,
                  GSN_CB32_FCT  ptCallBackFunc,
                  VOID*         ctx);

UINT32
GsnBrSerialInt_SpiWrite  (VOID*         pSerialIntHandle,
                  UINT8*        puBuffer,
                  UINT32        noOfBytesToWrite,
                  GSN_CB32_FCT  ptCallBackFunc,
                  VOID*         ctx );

#endif /* _GSN_BR_SERIAL_INT_H_ */



