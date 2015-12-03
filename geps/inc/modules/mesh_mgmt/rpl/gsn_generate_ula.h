/******************************************************************************
*
*               COPYRIGHT (c) 2013 GainSpan Corporation
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
* $RCSfile: gsn_generate_ula.h,v $
*
* Description : This file contains function defination to generate ULA (Unique
* Local Address) as per the RFC 4193.
*****************************************************************************/

/******************************************************************************
* File inclusion
******************************************************************************/
#ifndef _GSN_ULA_GENERATE_H_
#define _GSN_ULA_GENERATE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GSN_ULA_CFG
{
    UINT8 macLen;
    UINT8 *pMac;
}GSN_ULA_CFG_T;

#define GSN_BUILD_EU64( mac )                                 \
    (((((UINT8*)mac)[0] & 0xFD ) |                            \
        ((ULONG64)((~( ((UINT8*)mac)[0]) & 0xFD ))) << 56 ) | \
    (((ULONG64)(((UINT8*)mac)[1])) << 48 ) |                  \
    (((ULONG64)(((UINT8*)mac)[2])) << 40 ) |                  \
    (((ULONG64)(0xFF)) << 32 ) |                              \
    (((ULONG64)(0xFE)) << 24 ) |                              \
    (((ULONG64)(((UINT8*)mac)[3])) << 16 ) |                  \
    (((ULONG64)(((UINT8*)mac)[4])) << 8 ) |                   \
    (((ULONG64)(((UINT8*)mac)[5])) ))

GSN_STATUS
GsnUla_Generate( GSN_ULA_CFG_T* pCfg, UINT8 prefix[ 6 ]);

#ifdef __cplusplus
}
#endif
#endif /* _GSN_ULA_GENERATE_H_ */