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
* $RCSfile: gsn_dtls_record_fpt.h,v $
*
* Description : This file contains public definitions for DTLS record layer.
*******************************************************************************/

#ifndef _GSN_DTLS_RECORD_FPT_H_
#define _GSN_DTLS_RECORD_FPT_H_
#ifdef __cplusplus
extern "C" {
#endif

 
typedef int (*DTLS_RECORD_SET_CIPHER_SUITE_FP_T)(struct dtls_record_layer *drl,
                  UINT16 cipher_suite);

typedef int (*DTLS_RECORD_CHANGE_WRITE_CIPHER_FP_T)( struct dtls_record_layer *drl );


typedef int (*DTLS_RECORD_CHANGE_READ_CIPHER_FP_T)( struct dtls_record_layer *drl );


typedef int (*DTLS_RECORD_HDR_UPDATE_FP_T)(struct dtls_record_layer *drl, UINT8 content_type,
              size_t buf_size, UINT8 *payload, size_t payload_len,
              size_t *out_len);

typedef int (*DTLS_RECORD_RECEIVE_FP_T)(struct dtls_record_layer *drl,
             u8 *in_data, size_t in_len,
             u8 *out_data, size_t *out_len, u8 *alert);

extern _RPST_ DTLS_RECORD_SET_CIPHER_SUITE_FP_T dtls_record_set_cipher_suite_FP;


extern _RPST_ DTLS_RECORD_CHANGE_WRITE_CIPHER_FP_T dtls_record_change_write_cipher_FP;


extern _RPST_ DTLS_RECORD_CHANGE_READ_CIPHER_FP_T dtls_record_change_read_cipher_FP;


extern _RPST_ DTLS_RECORD_HDR_UPDATE_FP_T dtls_record_hdr_update_FP;

extern _RPST_  DTLS_RECORD_RECEIVE_FP_T dtls_record_receive_FP;

#ifdef __cplusplus
}
#endif        
#endif /* _GSN_DTLS_RECORD_FPT_H_ */







