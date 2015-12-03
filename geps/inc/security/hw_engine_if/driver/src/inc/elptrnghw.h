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


#ifndef _ELPTRNG_HW_H_
#define _ELPTRNG_HW_H_

/* Register offset addresses */
#if (defined TRNG_HDAC)
#define TRNG_CTRL       0x0040
#else
#define TRNG_CTRL       0x0000
#endif

#if (defined TRNG_HDAC)
#define TRNG_IRQ_STAT   0x0044
#define TRNG_IRQ_EN     0x0048
#elif (defined TRNG_SASPA)
#define TRNG_IRQ_STAT   0x0800
#define TRNG_IRQ_EN     0x0804
#else
#define TRNG_IRQ_STAT   0x0004
#define TRNG_IRQ_EN     0x0008
#endif

/* start offset of 4 32-bit words */
#if (defined TRNG_HDAC)
#define TRNG_DATA       0x0050
#else
#define TRNG_DATA       0x0010
#endif

#ifdef TRNG_HDAC
#define TRNG_HDAC_CTRL 0x0000
#define TRNG_HDAC_STAT 0x0004
#endif

/* TRNG_CTRL register definitions */
#define TRNG_CTRL_RAND_RESEED          31
#define TRNG_CTRL_NONCE_RESEED         30
#define TRNG_CTRL_NONCE_RESEED_LD      29
#define TRNG_CTRL_NONCE_RESEED_SELECT  28
#define TRNG_CTRL_GEN_NEW_RANDOM        0

#ifdef TRNG_HDAC
#define TRNG_HDAC_CTRL_IE_BIT     30
#define TRNG_HDAC_CTRL_IRQ_ENABLE (1 << TRNG_HDAC_CTRL_IE_BIT)
#define TRNG_HDAC_STAT_IRQ_BIT    30
#define TRNG_HDAC_STAT_IRQ_DONE   (1 << TRNG_HDAC_STAT_IRQ_BIT)
#endif

#define TRNG_RAND_RESEED            (1 << TRNG_CTRL_RAND_RESEED)
#define TRNG_NONCE_RESEED           (1 << TRNG_CTRL_NONCE_RESEED)
#define TRNG_NONCE_RESEED_LD        (1 << TRNG_CTRL_NONCE_RESEED_LD)
#define TRNG_NONCE_RESEED_SELECT    (1 << TRNG_CTRL_NONCE_RESEED_SELECT)
#define TRNG_GET_NEW                (1 << TRNG_CTRL_GEN_NEW_RANDOM)
#define TRNG_BUSY                   (1 << TRNG_CTRL_GEN_NEW_RANDOM)

#define TRNG_IRQ_STAT_BIT              27
#define TRNG_IRQ_DONE               (1 << TRNG_IRQ_STAT_BIT)

#define TRNG_IRQ_EN_BIT                27
#define TRNG_IRQ_ENABLE             (1 << TRNG_IRQ_EN_BIT)

#endif
