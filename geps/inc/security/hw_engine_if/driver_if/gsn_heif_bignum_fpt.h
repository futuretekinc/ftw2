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
* $RCSfile: gsn_heif_bignum_fpt.h,v $
*
* Description : This file contains the interfacing APIs used by WPA open source code.
*******************************************************************************/
#ifndef _GSN_HEIF_BIGNUM_FPT_
#define _GSN_HEIF_BIGNUM_FPT_

/*******************************************************************************
 * File Inclusions
 ******************************************************************************/
#include "security/hw_engine_if/gsn_hw_engine_if.h"
#include "supplicant/utils/os.h"

typedef int 
(*s_bg_op_FP_T) (void * a, void * b, void * c, int op, 
         void * mod );
extern _RPST_ s_bg_op_FP_T s_bg_op_FP;

typedef int 
(*s_bg_exptmod_FP_T) ( void * a, void * b, void * mod, 
        void * c );
extern _RPST_ s_bg_exptmod_FP_T s_bg_exptmod_FP;


typedef int (*bg_cmp_mag_FP_T) ( void * a, void * b);
extern _RPST_ bg_cmp_mag_FP_T bg_cmp_mag_FP;

typedef int (*bg_count_bits_FP_T) ( void * a);
extern _RPST_ bg_count_bits_FP_T bg_count_bits_FP;

typedef int
(*bg_s_sub_FP_T)(void * minuend, void * subtrahend, void * difference);
extern _RPST_ bg_s_sub_FP_T bg_s_sub_FP;

typedef int
(*bg_s_add_FP_T)(void* addend1,void * addend2, void * sum);
extern _RPST_ bg_s_add_FP_T bg_s_add_FP;

typedef void * (*bignum_init_FP_T)(void);
extern _RPST_ bignum_init_FP_T bignum_init_FP;

typedef void (*bignum_deinit_FP_T)( void *n);
extern _RPST_ bignum_deinit_FP_T bignum_deinit_FP;

typedef int (*bignum_cmp_FP_T)(void *a, void *b);
extern _RPST_ bignum_cmp_FP_T bignum_cmp_FP;

typedef int (*bignum_cmp_d_FP_T)(void *a, unsigned long b);
extern _RPST_ bignum_cmp_d_FP_T bignum_cmp_d_FP;

typedef int (*bignum_mul_FP_T)(void *a, void *b,
	       void *c);
extern _RPST_ bignum_mul_FP_T bignum_mul_FP;

typedef int (*bignum_mulmod_FP_T)(void *a, void *b,
		  void *c, void *d);
extern _RPST_ bignum_mulmod_FP_T bignum_mulmod_FP;

typedef int (*bignum_exptmod_FP_T)(void *a, void *b,
		   void *c, void *d);
extern _RPST_ bignum_exptmod_FP_T bignum_exptmod_FP;

typedef size_t (*bignum_get_unsigned_bin_len_FP_T)( void *n);
extern _RPST_ bignum_get_unsigned_bin_len_FP_T bignum_get_unsigned_bin_len_FP;

typedef int (*bignum_get_unsigned_bin_FP_T)(void *n, UINT8 *buf, size_t *len);
extern _RPST_ bignum_get_unsigned_bin_FP_T bignum_get_unsigned_bin_FP;

typedef int (*bignum_set_unsigned_bin_FP_T)( void *n, const UINT8 *buf, size_t len);
extern _RPST_ bignum_set_unsigned_bin_FP_T bignum_set_unsigned_bin_FP;

#endif /*_GSN_HEIF_BIGNUM_FPT_*/
