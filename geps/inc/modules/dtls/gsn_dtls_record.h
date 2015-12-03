/*******************************************************************************
*
*               COPYRIGHT (c) 2012-2013 GainSpan Corporation
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
* $RCSfile: gsn_dtls_record.h,v $
*
* Description : This file contains public definitions DTLS record layer.
*******************************************************************************/
#ifndef _GSN_DTLS_RECORD_H_
#define _GSN_DTLS_RECORD_H_

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
* File Inclusion
*****************************************************************************/
#include "gsn_includes.h"
#include "supplicant/utils/includes.h"

#include "supplicant/utils/common.h"
#include "supplicant/crypto/md5.h"
#include "supplicant/crypto/sha1.h"
#include "supplicant/tls/tlsv1_common.h"
#include "supplicant/tls/tlsv1_record.h"

/**
 *******************************************************************************
 * @file gsn_sdd.h
 * @brief GSN SDD public API implementation.
 *    This file contains the public APIs and structures of SDD module.
 ******************************************************************************/

#define DTLS_RECORD_HEADER_LEN (TLS_RECORD_HEADER_LEN + 8)

/**
 *******************************************************************************
 * 
 ******************************************************************************/
 

/*******************************************************************************
 * Private Functions prototype
 ******************************************************************************/
typedef struct dtls_record_layer 
{
	struct tlsv1_record_layer rl;

}dtls_record_layer_t;


int dtls_record_set_cipher_suite(struct dtls_record_layer *rl,
				  UINT16 cipher_suite);
int dtls_record_change_write_cipher(struct dtls_record_layer *rl);
int dtls_record_change_read_cipher(struct dtls_record_layer *rl);
int dtls_record_hdr_update(struct dtls_record_layer *drl, UINT8 content_type,
              size_t buf_size, UINT8 *payload, size_t payload_len,
              size_t *out_len);
int dtls_record_receive(struct dtls_record_layer *rl,
			 UINT8 *in_data, size_t in_len,
			 UINT8 *out_data, size_t *out_len, UINT8 *alert);

#ifdef __cplusplus
}
#endif
#endif /* _GSN_DTLS_RECORD_H_ */



