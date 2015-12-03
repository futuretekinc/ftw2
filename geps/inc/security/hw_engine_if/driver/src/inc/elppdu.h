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
#ifndef _GSN_ELPPDU_H_
#define _GSN_ELPPDU_H_
#include "gsn_types.h"
#include "gsn_defines.h"
#include "gsn_error.h"
#include "core/osal/gsn_osal_threadx.h"
#ifdef STANDALONE_TEST
extern uint8_t SPACC_REG[];
#define GSN_ELP_CRYPTO_HW_REGISTER_BASE (uint8_t*)SPACC_REG
#else
#define GSN_ELP_CRYPTO_HW_REGISTER_BASE (uint8_t*)0x40200000
#define GSN_ELP_CRYPTO_HW_SPACC_REGISTER_BASE (uint8_t*)0x40240000
#define GSN_ELP_CRYPTO_HW_PKA_REGISTER_BASE (uint32_t*)0x40220000
#define GSN_ELP_CRYPTO_HW_TRANG_REGISTER_BASE (uint32_t)0x40218000
#endif

#define CPU_YIELD
#define ELPHW_MEMCPY memcpy

#define PDU_LOCK_TYPE                GSN_OSAL_SEM_T
#define PDU_INIT_LOCK(lock)          GsnOsal_SemCreate((lock), 1)
#define PDU_LOCK(lock, flags)        GsnOsal_SemAcquire((lock), GSN_OSAL_WAIT_FOREVER);flags = 1
#define PDU_UNLOCK(lock, flags)      GsnOsal_SemRelease((lock));(void)flags

/* Platform Generic */

#define PDU_IRQ_EN_GLBL (1UL<<31)
#define PDU_IRQ_EN_VSPACC(x) (1UL<<x)
#define PDU_IRQ_EN_RNG  (1UL<<16)
#define PDU_IRQ_EN_PKA  (1UL<<17)
#define PDU_IRQ_EN_RE   (1UL<<18)
#define PDU_IRQ_EN_KEP  (1UL<<19)
#define PDU_IRQ_EN_EA   (1UL<<20)
#define PDU_IRQ_EN_MPM  (1UL<<21)

#include "security/hw_engine_if/driver/src/inc/elppdu_error.h"

typedef struct {
   unsigned minor,
            major,
            qos,
            is_spacc,
            is_pdu,
            is_hsm,
            aux,
            vspacc_idx,
            partial,
            project;
} spacc_version_block;

typedef struct {
   unsigned num_ctx,
            num_rc4_ctx,
            num_vspacc,
            ciph_ctx_page_size,
            hash_ctx_page_size,
            dma_type;
} spacc_config_block;

typedef struct {
   unsigned minor,
            major,
            is_rng,
            is_pka,
            is_re,
            is_kep,
            is_ea;
} pdu_config_block;

typedef struct {
   unsigned minor,
            major,
            paradigm,
            num_ctx,
            ctx_page_size;
} hsm_config_block;

typedef struct {
   spacc_version_block spacc_version;
   spacc_config_block  spacc_config;
   pdu_config_block    pdu_config;
   hsm_config_block    hsm_config;
} pdu_info;

typedef struct {
   unsigned long *phys, *virt;
   unsigned long  idx, limit, len;
} pdu_ddt;

void pdu_io_write32(void *addr, unsigned long val);
unsigned long pdu_io_read32(void *addr);

void pdu_to_dev32(void *addr, uint32_t *src, unsigned long nword);
void pdu_from_dev32(uint32_t *dst, void *addr, unsigned long nword);
void pdu_to_dev32_big(void *addr, unsigned char *src, unsigned long nword);
void pdu_from_dev32_big(unsigned char *dst, void *addr, unsigned long nword);
void pdu_to_dev32_little(void *addr, unsigned char *src, unsigned long nword);
void pdu_from_dev32_little(unsigned char *dst, void *addr, unsigned long nword);
void pdu_from_dev32_s(unsigned char *dst, void *addr, unsigned long nword, int endian);
void pdu_to_dev32_s(void *addr, unsigned char *src, unsigned long nword, int endian);

void *pdu_malloc(unsigned long n);
void pdu_free(void *p);

int pdu_ddt_init(pdu_ddt *ddt, unsigned long limit);
int pdu_ddt_add(pdu_ddt *ddt, unsigned long *phys, unsigned long size);
int pdu_ddt_reset(pdu_ddt *ddt);
int pdu_ddt_free(pdu_ddt *ddt);

int pdu_error_code(int code);

int pdu_get_version(void *dev, pdu_info *inf);

#ifdef DO_PCIM
#include <linux/pci.h>
void pdu_pci_set_trng_ring_off(struct pci_dev *tif);
void pdu_pci_set_trng_ring_on(struct pci_dev *tif);
void pdu_pci_set_little_endian(struct pci_dev *tif);
void pdu_pci_set_big_endian(struct pci_dev *tif);
void pdu_pci_set_secure_off(struct pci_dev *tif);
void pdu_pci_set_secure_on(struct pci_dev *tif);
void pdu_pci_interrupt_enabled(struct pci_dev *tif);
void pdu_pci_reset(struct pci_dev *tif);
#endif

#ifdef PCI_INDIRECT
void elppci_indirect_trigger(void);
#endif

#endif /* _GSN_ELPPDU_H_ */

