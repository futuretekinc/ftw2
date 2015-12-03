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



#ifndef _ELPSPACC_H_
#define _ELPSPACC_H_

#include "security/hw_engine_if/driver/src/inc/elppdu.h"
#include "security/hw_engine_if/driver/src/inc/elpspacchw.h"

enum {
  ICV_HASH = 0,                         /* HASH of plaintext */
  ICV_HASH_ENCRYPT = 1,         /* HASH the plaintext and encrypt the lot */
  ICV_ENCRYPT_HASH = 2,     /* HASH the ciphertext */
  ICV_IGNORE=3,
  IM_MAX,
};

enum {
   SPACC_DMA_UNDEF = 0,
   SPACC_DMA_DDT,
   SPACC_DMA_LINEAR
};


#define CRYPTO_AES_KEY_LENGTH_128   16
#define CRYPTO_AES_KEY_LENGTH_192   24
#define CRYPTO_AES_KEY_LENGTH_256   32

#define CRYPTO_AES_KEY_LENGTH_MIN CRYPTO_AES_KEY_LENGTH_128
#define CRYPTO_AES_KEY_LENGTH_MAX CRYPTO_AES_KEY_LENGTH_256

#define CRYPTO_3DES_KEY_LENGTH            24
#define CRYPTO_3DES_KEY_LENGTH_MIN CRYPTO_3DES_KEY_LENGTH
#define CRYPTO_3DES_KEY_LENGTH_MAX CRYPTO_3DES_KEY_LENGTH

#define CRYPTO_DES_KEY_LENGTH            8
#define CRYPTO_DES_KEY_LENGTH_MIN CRYPTO_DES_KEY_LENGTH
#define CRYPTO_DES_KEY_LENGTH_MAX CRYPTO_DES_KEY_LENGTH

#define CRYPTO_DES_IV_LENGTH            8
#define CRYPTO_DES_MIN_BLOCK_SIZE       8
#define CRYPTO_AES_IV_LENGTH           16
#define CRYPTO_AES_MIN_BLOCK_SIZE      16
#define CRYPTO_HASH_SHA1_SIZE          20
#define CRYPTO_HASH_SHA224_SIZE        28
#define CRYPTO_HASH_SHA256_SIZE        32
#define CRYPTO_HASH_SHA384_SIZE        48
#define CRYPTO_HASH_SHA512_SIZE        64
#define CRYPTO_HASH_MD5_SIZE           16

#define CRYPTO_MAC_XCBC_SIZE           16 
#define CRYPTO_MAC_CMAC_SIZE           16 
#define CRYPTO_MAC_KASUMIF9_SIZE        8 
#define CRYPTO_MAC_SNOW3GUIA2_SIZE      4 
#define CRYPTO_MAC_ZUCUIA3_SIZE         4 
#define CRYPTO_HASH_CRC32_SIZE          4

#define OP_ENCRYPT          0
#define OP_DECRYPT          1

#define SPACC_CRYPTO_OPERATION   1
#define SPACC_HASH_OPERATION     2

#define SPACC_AADCOPY_FLAG        0x80000000

enum crypto_modes {
  CRYPTO_MODE_NULL,
  CRYPTO_MODE_RC4_40,
  CRYPTO_MODE_RC4_128,
  CRYPTO_MODE_RC4_KS,
  CRYPTO_MODE_AES_ECB,
  CRYPTO_MODE_AES_CBC,
  CRYPTO_MODE_AES_CTR,
  CRYPTO_MODE_AES_CCM,
  CRYPTO_MODE_AES_GCM,
  CRYPTO_MODE_AES_F8,
  CRYPTO_MODE_AES_XTS,
  CRYPTO_MODE_AES_CFB,
  CRYPTO_MODE_AES_OFB,
  CRYPTO_MODE_MULTI2_ECB,
  CRYPTO_MODE_MULTI2_CBC,
  CRYPTO_MODE_MULTI2_OFB,
  CRYPTO_MODE_MULTI2_CFB,
  CRYPTO_MODE_3DES_CBC,
  CRYPTO_MODE_3DES_ECB,
  CRYPTO_MODE_DES_CBC,
  CRYPTO_MODE_DES_ECB,
  CRYPTO_MODE_KASUMI_ECB,
  CRYPTO_MODE_KASUMI_F8,
  CRYPTO_MODE_SNOW3G_UEA2,
  CRYPTO_MODE_ZUC_UEA3,

  CRYPTO_MODE_HASH_SHA1,
  CRYPTO_MODE_HMAC_SHA1,
  CRYPTO_MODE_HASH_MD5,
  CRYPTO_MODE_HMAC_MD5,
  CRYPTO_MODE_HASH_SHA224,
  CRYPTO_MODE_HMAC_SHA224,
  CRYPTO_MODE_HASH_SHA256,
  CRYPTO_MODE_HMAC_SHA256,
  CRYPTO_MODE_HASH_SHA384,
  CRYPTO_MODE_HMAC_SHA384,
  CRYPTO_MODE_HASH_SHA512,
  CRYPTO_MODE_HMAC_SHA512,
  CRYPTO_MODE_HASH_SHA512_224,
  CRYPTO_MODE_HMAC_SHA512_224,
  CRYPTO_MODE_HASH_SHA512_256,
  CRYPTO_MODE_HMAC_SHA512_256,

  CRYPTO_MODE_MAC_XCBC,
  CRYPTO_MODE_MAC_CMAC,
  CRYPTO_MODE_MAC_KASUMI_F9,
  CRYPTO_MODE_MAC_SNOW3G_UIA2,
  CRYPTO_MODE_MAC_ZUC_UIA3,

  CRYPTO_MODE_SSLMAC_MD5,
  CRYPTO_MODE_SSLMAC_SHA1,
  CRYPTO_MODE_HASH_CRC32,

  CRYPTO_MODE_RC4_256 /* Added by GainSpan */
};

enum {
  SPACC_DEQUEUE_MAP = 0,
  SPACC_DEQUEUE_UNMAP
};


#ifndef MAX_DDT_ENTRIES
   /* add one for null at end of list */
   #define MAX_DDT_ENTRIES (SPACC_MAX_MSG_MALLOC_SIZE / SPACC_MAX_PARTICLE_SIZE) + 1
#endif

#ifndef SPACC_MAX_JOBS
   #define SPACC_MAX_JOBS  (1U<<SPACC_SW_CTRL_ID_W)
#endif

// job descriptor
typedef struct
{
  unsigned long
      enc_mode,                 // Encription Algorith mode
      hash_mode,                // HASH Algorith mode
      icv_len,
      icv_offset,
      op,                       // Operation
      ctrl,                     // CTRL shadoe register
      first_use,                // indicates that context just has been initialized/taken
                                // and this is the first use
      pre_aad_sz, post_aad_sz,  // size of AAD for the latest packet
      hkey_sz, 
      ckey_sz;
      
   unsigned auxinfo_dir, auxinfo_bit_align; // Direction and bit alignment parameters for the AUX_INFO reg
   uint32_t ctx_idx;
   unsigned job_used, job_swid, job_done, job_secure;
   int job_err;
} spacc_job;

#define SPACC_CTX_IDX_UNUSED  0xFFFFFFFF
#define SPACC_JOB_IDX_UNUSED  0xFFFFFFFF

#define DDT_ENTRY_SIZE (sizeof(ddt_entry)*MAX_DDT_ENTRIES)

typedef struct {
   uint32_t *ciph_key;        // Memory context to store cipher keys
   uint32_t *hash_key;        // Memory context to store hash keys
   uint32_t *rc4_key;         // Memory context to store internal RC4 keys
   int      ref_cnt;          // reference count of jobs using this context
   int      ncontig;          // number of contexts following related to this one
} spacc_ctx;

/* forward declaration for callback functions */
struct _spacc_device;

typedef struct _spacc_device {
   void                  *regmap;
   unsigned              version, project;

   // hardware configuration
   int num_ctx,         // # of contexts
       num_rc4_ctx,     // # of RC4 contexts
       num_sec_ctx,     // # of SKP contexts
       sec_ctx_page_size, // page size of SKP context in bytes
       ciph_page_size,  // cipher context page size in bytes
       hash_page_size,  // hash context page size in bytes
       is_qos,          // QOS spacc?
       is_pdu,          // PDU spacc?
       is_hsm_virtual,  // Is this an HSM Virtual spacc?
       is_hsm_shared,   // Is this an HSM Shared spacc?
       is_secure,       // OR of the previous two bits (basically is this an HSM or not)
       is_secure_port,  // Are we on the secure port?
       is_partial,      // Is partial processing enabled?
       dma_type,        // Which type of DMA linear or scattergather
       idx,             // Which virtual spacc IDX is this?
       ctx_mask;        // CTX mask used by shared HSM
   
   spacc_ctx *ctx;        // This size changes per configured device
   spacc_job *job;        // allocate memory for [SPACC_MAX_JOBS];
   int job_lookup[SPACC_MAX_JOBS];  // correlate SW_ID back to job index

   PDU_LOCK_TYPE lock;           // lock for register access
   PDU_LOCK_TYPE ctx_lock;       // lock for context manager
   
   /* callback functions for IRQ processing */
   void (*irq_cb_cmdx)(struct _spacc_device *spacc, int x);
   void (*irq_cb_stat)(struct _spacc_device *spacc);
   void (*irq_cb_rc4_dma)(struct _spacc_device *spacc);

   // testing
   struct {
      unsigned char *OUTCT;
      unsigned char *IN_BUFF;
   } testing;
} spacc_device;

extern int spacc_endian;

int spacc_init(void *baseaddr, spacc_device *spacc, pdu_info *info);
void spacc_fini(spacc_device *spacc);


int spacc_request_hsm_semaphore(spacc_device *spacc);
void spacc_free_hsm_semaphore(spacc_device *spacc);

int spacc_load_skp(spacc_device *spacc, uint32_t *key, int keysz, int idx, int alg, int mode, int size, int enc, int dec);
void spacc_set_secure_mode (spacc_device *spacc, int src, int dst, int ddt, int global_lock);
void spacc_set_debug (int dflag);
unsigned char * spacc_error_msg (int err);
void spacc_dump_ctx(spacc_device *spacc, int ctx );
/*
The spacc_open() function allocates a single context from a given SPAcc device and assigns the
cipher and hash modes.

Where enc is one of the enumerated cipher modes,
hash is one of the enumerated hash modes, 
ctxid is used for resource allocation strategies (use -1 for a new context or pass a known one), and
secure_mode indicates whether this job is executing in secure mode or not. Secure jobs use a
secure key context and require the key to be loaded via spacc_load_skp().

The allocated job is setup by default to run in complete packet mode, that is the message begin and
end flags will be set. In order to run jobs in partial processing mode the caller must clear these flags
and set them as appropriate. See src/core/kernel/spaccdiag.c for an example FSM that executes
partial processing mode.
*/
int spacc_open (spacc_device *spacc, int enc, int hash, int ctx, int secure_mode);
int spacc_close (spacc_device *spacc, int job_idx);
/*
This function sets the encryption direction, ICV protocol, position, offset, and size.

The op parameter should be set to OP_ENCRYPT for encryption or OP_DECRYPT for decryption.

The prot variable is set to one of the following three values: ICV_HASH,
ICV_HASH_ENCRYPT, or ICV_ENCRYPT_HASH which either produce a hash (or MAC tag)
on the plaintext, on the plaintext and then encrypt the tag, or on the ciphertext respectively.

The icvoff parameter must be set to one of: IP_ICV_OFFSET, IP_ICV_APPEND, or
IP_ICV_IGNORE. These tell the engine to store the ICV (hash or MAC tag) at a fixed location,
append to the ciphertext, or ignore the setting (for jobs that do not have a hash component).

The ICV offset is set by the icvoff parameter and only used in IP_ICV_OFFSET mode. The size

of the ICV is passed as icvsz and can be used to tell the engine to truncate the (or expect a
truncated) ICV.

The sec_key parameter is used to indicate whether secure key port is to be used.
*/
int spacc_set_operation (spacc_device *spacc, int job_idx, int op, uint32_t prot, uint32_t icvpos, uint32_t icvoff, uint32_t icvsz, uint32_t sec_key);
int spacc_set_key_exp(spacc_device *spacc, int job_idx);

int spacc_set_auxinfo (spacc_device *spacc, int job_idx, uint32_t direction, uint32_t bitsize);
void spacc_virtual_set_weight(spacc_device *spacc, int weight);
int spacc_virtual_request_rc4(spacc_device *spacc);
int spacc_packet_enqueue_ddt (spacc_device *spacc, int job_idx, pdu_ddt *src_ddt, pdu_ddt *dst_ddt, uint32_t proc_sz, uint32_t aad_offset, uint32_t pre_aad_sz, uint32_t post_aad_sz, uint32_t iv_offset, uint32_t prio);
int spacc_pop_packets (spacc_device * spacc, int *num_popped);
int spacc_packet_dequeue (spacc_device *spacc, int job_idx);

uint32_t spacc_get_version (void);

/* IRQ handling functions */
void spacc_irq_cmdx_enable (spacc_device *spacc, int cmdx, int cmdx_cnt);
void spacc_irq_cmdx_disable (spacc_device *spacc, int cmdx);
void spacc_irq_stat_enable (spacc_device *spacc, int stat_cnt);
void spacc_irq_stat_disable (spacc_device *spacc);
void spacc_irq_rc4_dma_enable (spacc_device *spacc);
void spacc_irq_rc4_dma_disable (spacc_device *spacc);
void spacc_irq_glbl_enable (spacc_device *spacc);
void spacc_irq_glbl_disable (spacc_device *spacc);
uint32_t spacc_process_irq(spacc_device *spacc);

/* Context Manager */
void spacc_ctx_init_all (spacc_device *spacc);
int spacc_ctx_request (spacc_device *dev, int ctx_idx, int ncontig);
int spacc_ctx_release (spacc_device *dev, int ctx_idx);

/* SPAcc specific manipulation of context memory */
/*
The function assigns values to the context identified by job_idx and operates 
on the cipher (and RC4) or hash context pages depending on the value of op. 
When set to SPACC_CRYPTO_OPERATION it sets the cipher/RC4 pages, when set to
SPACC_HASH_OPERATION it sets the hash pages.
The key is passed as key of ksz bytes length, and the IV/salt as iv of ivsz bytes length. 
In certain modes the lengths are implicit. See the SPAcc User Guide for more details.
When calling this function to load a fully scheduled RC4 key the key (cipher mode
CRYPTO_MODE_RC4_KS) is assumed to be 258 bytes long. The first two bytes are i and j
respectfully (see spacc_write_rc4_context()) and the remaining 256 bytes are the shuffle array. The
calling application is responsible for scheduling the key as the SDK does not contain any
cryptographic software.
*/
int spacc_write_context (spacc_device *spacc, int job_idx, int op, unsigned char * key, int ksz, unsigned char * iv, int ivsz);
int spacc_read_context (spacc_device * spacc, int job_idx, int op, unsigned char * key, int ksz, unsigned char * iv, int ivsz);
int spacc_write_rc4_context (spacc_device *spacc, int job_idx, unsigned char i, unsigned char j, unsigned char *ctxdata);
int spacc_read_rc4_context (spacc_device *spacc, int job_idx, unsigned char *i, unsigned char *j, unsigned char *ctxdata);


/* Job Manager */
void spacc_job_init_all (spacc_device *spacc);
int spacc_job_request (spacc_device * dev, int job_idx);
int spacc_job_release (spacc_device * dev, int job_idx);
/* helper functions */
spacc_ctx *context_lookup_by_job (spacc_device *spacc, int job_idx);
spacc_job *job_lookup_by_swid (spacc_device * spacc, int swid);

/* Debug MACROs */
#define ELPHW_PRINT(...)

#endif
