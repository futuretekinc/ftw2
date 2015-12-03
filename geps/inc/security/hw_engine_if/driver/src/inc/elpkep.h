
/*
 * Copyright (c) 2011 Elliptic Technologies Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#ifndef ELP_KEP_H
#define ELP_KEP_H

#include "security/hw_engine_if/driver/src/inc/elppdu.h"
#include "security/hw_engine_if/driver/inc/elpspacc.h"
#include "security/hw_engine_if/driver/src/inc/elpkephw.h"

#define KEP_MAX_DDT 17

enum {
   KEP_SSL3_KEYGEN=0,
   KEP_SSL3_SIGN,
   KEP_TLS_PRF,
   KEP_TLS_SIGN,
   KEP_TLS2_PRF,
   KEP_TLS2_SIGN
};   

// options for commands
#define KEP_OPT_SSL3_SIGN_MD5   0
#define KEP_OPT_SSL3_SIGN_SHA1  1

#define KEP_OPT_TLS_SIGN_CLIENT 0
#define KEP_OPT_TLS_SIGN_SERVER 1

#define KEP_OPT_TLS2_PRF_MD5    (1UL<<1)
#define KEP_OPT_TLS2_PRF_SHA1   (2UL<<1)
#define KEP_OPT_TLS2_PRF_SHA224 (3UL<<1)
#define KEP_OPT_TLS2_PRF_SHA256 (4UL<<1)
#define KEP_OPT_TLS2_PRF_SHA384 (5UL<<1)
#define KEP_OPT_TLS2_PRF_SHA512 (6UL<<1)

#define KEP_OPT_TLS2_SIGN_CLIENT 0
#define KEP_OPT_TLS2_SIGN_SERVER 1
#define KEP_OPT_TLS2_SIGN_MD5    (1UL<<1)
#define KEP_OPT_TLS2_SIGN_SHA1   (2UL<<1)
#define KEP_OPT_TLS2_SIGN_SHA224 (3UL<<1)
#define KEP_OPT_TLS2_SIGN_SHA256 (4UL<<1)
#define KEP_OPT_TLS2_SIGN_SHA384 (5UL<<1)
#define KEP_OPT_TLS2_SIGN_SHA512 (6UL<<1)

typedef struct {
   int op,
       option,
       job_id,
       job_done;
} elp_kep_ctx;

typedef struct {
	void        *regmap;
   elp_kep_ctx *ctx;   
   PDU_LOCK_TYPE lock;
   spacc_device *spacc;
} kep_device;

int kep_init(void *baseaddr, spacc_device *spacc, kep_device *kep);
void kep_fini(kep_device *kep);

int kep_open(kep_device *kep, int op, int option);
int kep_load_keys(kep_device *kep, int handle, void *s1, uint32_t s1len, void *s2, uint32_t s2len);
int kep_go(kep_device *kep, pdu_ddt *src_ddt, pdu_ddt *dst_ddt, int handle);
int kep_done(kep_device *kep, int handle);
int kep_close(kep_device *kep, int handle);

int kep_is_valid(kep_device *kep, int handle);

#ifdef PDU_USE_KERNEL
kep_device *kep_get_device(void);
#endif

#endif
