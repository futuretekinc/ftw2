/*******************************************************************************
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
* $RCSfile: app_http_fs.h,v
*/

#ifndef APP_HTTP_FS_H_
#define APP_HTTP_FS_H_
#ifdef TRROM_FILE_SYS
#ifdef S2W_WEB_PAGE_CLIENT_ONLY
#include "trrombld_client.h"
#elif defined (S2W_WEB_PAGE_AP_ONLY)
#include "trrombld_ap.h"
#elif defined (S2W_WEB_PAGE_CLIENT_AND_AP)
#include "trrombld_client_and_ap.h"
#elif defined (S2W_WEB_PAGE_PRO)
#include "trrombld_prov.h"
#elif defined(S2W_WEB_PAGE_PRO_COMBINED)
#include "trrombld_prov_combined.h"
#else
#warning "No Web App configuration defined. Defaulting to PRO+TLS"
#endif
#endif /*TRROM_FILE_SYS*/
#endif /* APP_HTTP_FS_H_ */
