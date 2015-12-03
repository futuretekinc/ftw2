/*
 * SHA256 hash implementation and interface functions
 * Copyright (c) 2003-2006, Jouni Malinen <j@w1.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 * See README and COPYING for more details.
 */

#ifndef SHA256_PATCH_H
#define SHA256_PATCH_H

/*
 * TODO: 64-bit variable not available. Using long as a workaround to test the
 * build, but this will likely not work for all operations.
 */
typedef unsigned long long uint64;

#define SHA256_MAC_LEN 32
#define SHA256_BLOCK_SIZE 64

struct sha256_state1 {
	uint64 length;
	u32 state[8], curlen;
	u8 buf[64];
};

#define WPA_GET_BE641(a) ((((uint64) (a)[0]) << 56) | (((uint64) (a)[1]) << 48) | \
			 (((uint64) (a)[2]) << 40) | (((uint64) (a)[3]) << 32) | \
			 (((uint64) (a)[4]) << 24) | (((uint64) (a)[5]) << 16) | \
			 (((uint64) (a)[6]) << 8) | ((uint64) (a)[7]))
#define WPA_PUT_BE641(a, val)				\
	do {						\
		(a)[0] = (u8) (((uint64) (val)) >> 56);	\
		(a)[1] = (u8) (((uint64) (val)) >> 48);	\
		(a)[2] = (u8) (((uint64) (val)) >> 40);	\
		(a)[3] = (u8) (((uint64) (val)) >> 32);	\
		(a)[4] = (u8) (((uint64) (val)) >> 24);	\
		(a)[5] = (u8) (((uint64) (val)) >> 16);	\
		(a)[6] = (u8) (((uint64) (val)) >> 8);	\
		(a)[7] = (u8) (((uint64) (val)) & 0xff);	\
	} while (0)

#define WPA_GET_LE641(a) ((((uint64) (a)[7]) << 56) | (((uint64) (a)[6]) << 48) | \
			 (((uint64) (a)[5]) << 40) | (((uint64) (a)[4]) << 32) | \
			 (((uint64) (a)[3]) << 24) | (((uint64) (a)[2]) << 16) | \
			 (((uint64) (a)[1]) << 8) | ((uint64) (a)[0]))

void sha256_init1(struct sha256_state1 *md);
int sha256_process1(struct sha256_state1 *md, const unsigned char *in,
			  unsigned long inlen);
int sha256_done1(struct sha256_state1 *md, unsigned char *out);

void hmac_sha256_vector1(const u8 *key, size_t key_len, size_t num_elem,
		      const u8 *addr[], const size_t *len, u8 *mac);
#if 0
void hmac_sha256(const u8 *key, size_t key_len, const u8 *data,
		 size_t data_len, u8 *mac);
void sha256_prf(const u8 *key, size_t key_len, const char *label,
	      const u8 *data, size_t data_len, u8 *buf, size_t buf_len);
#endif
#endif /* SHA256_H */
