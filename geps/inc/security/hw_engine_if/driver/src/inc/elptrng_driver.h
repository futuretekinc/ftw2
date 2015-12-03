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


#ifndef __ELLIPTIC_DRIVER_TRNG__
#define __ELLIPTIC_DRIVER_TRNG__

#include "security/hw_engine_if/driver/src/inc/elptrng.h"

#define ELLIPTIC_TRNG_DRIVER_PLATFORM_NAME "trng"
#define ELLIPTIC_HWRNG_DRIVER_NAME "hwrng-elptrng"

#define ELLIPTIC_TRNG_CRYPTO_RESEED_NONCE_SUPPORT 1

typedef struct 
{
  trng_hw trng;
  unsigned int *base_addr;

#ifdef ELPTRNG_HWRANDOM
  void *hwrng_drv;
#endif

#ifdef ELPTRNG_CRYPTO_API
  void *crypto_drv;
#endif
}elliptic_trng_driver;

#ifdef ELPTRNG_HWRANDOM
int elptrng_hwrng_driver_read(struct hwrng *rng, void *buf, size_t max, bool wait);
#endif

#ifdef ELPTRNG_CRYPTO_API
int elptrng_crypto_driver_read(struct crypto_rng *tfm, u8 *rdata, unsigned int dlen);
int elptrng_crypto_driver_reset(struct crypto_rng *tfm, u8 *seed, unsigned int slen);
#endif

#endif /* __ELLIPTIC_DRIVER_TRNG__ */



