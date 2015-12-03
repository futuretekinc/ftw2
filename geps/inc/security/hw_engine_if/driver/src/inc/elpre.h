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



#ifndef ELP_RE_H
#define ELP_RE_H

#include "security/hw_engine_if/driver/src/inc/elppdu.h"
#include "security/hw_engine_if/driver/inc/elpspacc.h"

#define MAX_RE_DDT_SIZE 18432 
#define RE_SA_SIZE 1024
#define CRYPTO_MODULE_RE  0x0100

typedef struct elp_re_ctx_{

   unsigned char * sa;   //Pointer to the SA

   void * samap; //Physical address of the SA
   int spacc_handle; //The handle from the spacc that this context has

   int curjob_swid;
   int jobdone;
   int ret_stat;
   int ret_prot;
   int ret_size;
   int ret_err;
   
   int datalength;
} elp_re_ctx;

typedef struct {
	void *regmap;
   int module_initialized;
   int num_ctx;
   elp_re_ctx *re_contexts;
   void *sa_pool_virt, *sa_pool_phys;
   unsigned long sa_pool_size;
   PDU_LOCK_TYPE lock;
   spacc_device *spacc;
} re_device;

int re_init(void *baseaddr, spacc_device *spacc, re_device *re);
void re_fini(re_device *re);

int re_reset_sa(re_device *re, int handle, uint32_t version);

int re_set_next_read(re_device *re, 
                     int handle, 
                     unsigned char *iv,              uint32_t ivlen, 
                     unsigned char *key,             uint32_t keylen, 
                     unsigned char *mackey,          uint32_t mackeylen,
                     unsigned char *params,          uint32_t paramlength, 
                     unsigned char *sequence_number, uint32_t seqlength);

int re_set_next_write(re_device *re, 
                      int handle, 
                      unsigned char *iv,              uint32_t ivlen, 
                      unsigned char *key,             uint32_t keylen, 
                      unsigned char *mackey,          uint32_t mackeylen,
                      unsigned char *params,          uint32_t paramlength, 
                      unsigned char *sequence_number, uint32_t seqlength);


int re_start_operation(re_device *re, int handle, pdu_ddt *src_ddt, pdu_ddt *dst_ddt, uint32_t type);
int re_finish_operation(re_device *re, int handle, uint32_t * length, int * id);
int re_error_msg (int err, unsigned char * buff, uint32_t length);

int re_retrieve_sa(re_device *re, int handle, unsigned char * sabuff, uint32_t bufflength);
int re_write_sa(re_device *re, int handle, unsigned char * sa, uint32_t bufflength);

int re_init_context(re_device *re, int handle);
int re_get_context(re_device *re);
int re_release_context(re_device *re, int handle);

int re_set_next_read_iv (re_device *re, int handle, unsigned char * iv, uint32_t length);
int re_set_next_read_key (re_device *re, int handle, unsigned char * key, uint32_t length);
int re_set_next_read_mackey (re_device *re, int handle, unsigned char * mackey, uint32_t length);
int re_set_next_read_params (re_device *re, int handle, unsigned char * params, uint32_t length);
int re_set_next_read_sequence_number (re_device *re, int handle, unsigned char * sequence_number, uint32_t length);

int re_set_next_write_iv (re_device *re, int handle, unsigned char * iv, uint32_t length);
int re_set_next_write_key (re_device *re, int handle, unsigned char * key, uint32_t length);
int re_set_next_write_mackey (re_device *re, int handle, unsigned char * mackey, uint32_t length);
int re_set_next_write_params (re_device *re, int handle, unsigned char * params, uint32_t length);
int re_set_next_write_sequence_number (re_device *re, int handle, unsigned char * sequence_number, uint32_t length);

int re_packet_dequeue (re_device *re, int context);

void re_print_diag(re_device *re, int handle);

#ifdef PDU_USE_KERNEL
re_device *re_get_device(void);
#endif

#endif //ELP_RE_H
