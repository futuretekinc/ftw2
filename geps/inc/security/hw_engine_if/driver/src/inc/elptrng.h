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


#ifndef _ELPTRNG_H_
#define _ELPTRNG_H_

#include "security/hw_engine_if/driver/src/inc/elppdu.h"

/* Error codes */
enum
{
   ELPTRNG_OK = 0,
   ELPTRNG_NOT_INITIALIZED,
   ELPTRNG_TIMEOUT,
   ELPTRNG_INVALID_ARGUMENT,
};

/* wait flag */
enum
{
   ELPTRNG_NO_WAIT = 0,
   ELPTRNG_WAIT,
};

/* reseed flag */
enum
{
   ELPTRNG_NO_RESEED = 0,
   ELPTRNG_RESEED,
};

/* IRQ flag */
enum
{
   ELPTRNG_IRQ_PIN_DISABLE = 0,
   ELPTRNG_IRQ_PIN_ENABLE,
};

/* init status */
enum
{
   ELPTRNG_NOT_INIT = 0,
   ELPTRNG_INIT_PROG,
   ELPTRNG_INIT,
};

/* useful constants */
#define TRNG_DATA_SIZE_WORDS 4
#define TRNG_DATA_SIZE_BYTES 16
#define TRNG_NONCE_SIZE_WORDS 8
#define TRNG_NONCE_SIZE_BYTES 32

#define LOOP_WAIT      1000000   /* Configurable delay */

typedef struct trng_hw {
#if (defined TRNG_HDAC)
   uint32_t * trng_hdac_ctrl;
   uint32_t * trng_hdac_stat;
#endif
   PDU_LOCK_TYPE lock; 
   uint32_t * trng_ctrl;
   uint32_t * trng_irq_stat;
   uint32_t * trng_irq_en;
   uint32_t * trng_data;
   uint32_t initialized;
   uint32_t  seed[TRNG_NONCE_SIZE_WORDS];
} trng_hw;

/* Function definitions for external use */
void trng_dump_registers (trng_hw * hw);
int32_t trng_wait_for_done (trng_hw * hw, uint32_t cycles);
int32_t trng_reseed_random (trng_hw * hw, uint32_t wait);
int32_t trng_reseed_nonce (trng_hw * hw, uint32_t seed[TRNG_NONCE_SIZE_WORDS]);
int32_t trng_init (trng_hw * hw, uint32_t base_addr, uint32_t enable_irq, uint32_t reseed);
void trng_close (trng_hw * hw);
int32_t trng_rand (trng_hw * hw, uint8_t * randbuf, uint32_t size);

#if (defined TRNG_HDAC)
void trng_enable(trng_hw * hw);
#endif

#endif

