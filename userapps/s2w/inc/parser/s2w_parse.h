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
* $RCSfile: s2w_parse.h,v $
*
* Description : This file contains general definitions.
*****************************************************************************/
#ifndef S2W_PARSE_H
#define S2W_PARSE_H

UINT8 *AppS2wParse_NextParamGet(UINT8 **temp);

UINT8 AppS2wParse_Int(UINT8 *ptr, UINT32 *val);
UINT8 AppS2wParse_Hex(UINT8 *ptr, UINT32 *val);
UINT8 AppS2wParse_Boolean(UINT8 *ptr, UINT8 *val);

UINT8 AppS2wParse_AddrPort(UINT8 **temp, S2W_NETDATA_T *peer_data);
UINT8 AppS2wParse_WepKey(UINT8 *ptr, S2W_WEPDATA_T *wep, UINT8 idx);
UINT8
AppS2wParse_64BitNumber(UINT8 *ptr, ULONG64 *val);

enum pwc_command
{
    pwc_scan,
    pwc_assoc,
    pwc_wauto
};

UINT8 AppS2wParse_Wcmd(UINT8 *ptr, S2W_WLANDATA_T *params, enum pwc_command cmd);
UINT8 AppS2wParse_Nset(UINT8 **temp, S2W_NETCONF_T *config);
UINT8 AppS2wParse_Mac(UINT8 *s, UINT8 *mac_addr);

#define is_valid_port(x) ((x) > 0 && (x) <= 65535)

#ifdef S2W_HAVE_STRNCASECMP
#include <strings.h>
#else
int AppS2wParse_StrnCaseCmp(const char *s1, const char *s2, unsigned int n);
#endif

PUBLIC UINT8
AppS2wParse_Int(UINT8 *ptr, UINT32 *val);

PUBLIC UINT8
AppS2wParse_Ip(UINT8 *p, UINT8 *ip);


PUBLIC UINT8
AppS2wParse_ToHex(UINT8 c);

PUBLIC UINT8
AppS2wParse_Ssid(UINT8 *p, UINT8 *ssid, UINT8 *lenp);
PUBLIC BOOL
AppS2wParse_MdnsKeyValidate(UINT8 * str,UINT32 len);
PUBLIC VOID
AppS2wParse_IntToStr(UINT8 *inPtr ,UINT8 *val, UINT32 len);
#endif
