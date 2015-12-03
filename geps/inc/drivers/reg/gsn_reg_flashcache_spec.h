/******************************************************************************
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
* $RCSfile: gsn_reg_flashcache_spec.h,v $
*
* Description : This file contains flash cache definitions.
******************************************************************************/

#ifndef _REG_FLASHCACHE_SPEC_H
#define _REG_FLASHCACHE_SPEC_H

/***************************************************
 *
 *             FLASHCACHE
 *
 ***************************************************/


/*
 *  FLASHCACHE instance offsets
 ****************************************************************************************
 */
#define FLASHCACHE 0x400F0000

/*
 *  FLASHCACHE_INTCTL register defines
 ****************************************************************************************
 */
#define FLASHCACHE_INTCTL_OFFSETADDRESS 0x00000000  /* RW */
#define FLASHCACHE_INTCTL_BITOFFSET    0
#define FLASHCACHE_INTCTL_BITFIELDSIZE 32
#define FLASHCACHE_INTCTL_BITMASK      0xFFFFFFFF
#define FLASHCACHE_INTCTL_INIT         0x00000000
/*
 *  FLASHCACHE_ACCESSERR_INTEN bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_ACCESSERR_INTEN_OFFSETADDRESS FLASHCACHE_INTCTL_OFFSETADDRESS
#define FLASHCACHE_ACCESSERR_INTEN_BITOFFSET    1
#define FLASHCACHE_ACCESSERR_INTEN_BITFIELDSIZE  1
#define FLASHCACHE_ACCESSERR_INTEN_BITMASK      0x00000002
#define FLASHCACHE_ACCESSERR_INTEN_INIT         0x0
/*
 *  FLASHCACHE_DMADONE_INTEN bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_DMADONE_INTEN_OFFSETADDRESS  FLASHCACHE_INTCTL_OFFSETADDRESS
#define FLASHCACHE_DMADONE_INTEN_BITOFFSET      0
#define FLASHCACHE_DMADONE_INTEN_BITFIELDSIZE   1
#define FLASHCACHE_DMADONE_INTEN_BITMASK        0x00000001
#define FLASHCACHE_DMADONE_INTEN_INIT           0x0

/*
 *  FLASHCACHE_INTSTATUS register defines
 ****************************************************************************************
 */
#define FLASHCACHE_INTSTATUS_OFFSETADDRESS 0x00000004  /* RW */
#define FLASHCACHE_INTSTATUS_BITOFFSET 0
#define FLASHCACHE_INTSTATUS_BITFIELDSIZE 32
#define FLASHCACHE_INTSTATUS_BITMASK   0xFFFFFFFF
#define FLASHCACHE_INTSTATUS_INIT      0x00000000
/*
 *  FLASHCACHE_ACCESSERR_INTSTATUS bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_ACCESSERR_INTSTATUS_OFFSETADDRESS FLASHCACHE_INTSTATUS_OFFSETADDRESS
#define FLASHCACHE_ACCESSERR_INTSTATUS_BITOFFSET  1
#define FLASHCACHE_ACCESSERR_INTSTATUS_BITFIELDSIZE  1
#define FLASHCACHE_ACCESSERR_INTSTATUS_BITMASK  0x00000002
#define FLASHCACHE_ACCESSERR_INTSTATUS_INIT     0x0
/*
 *  FLASHCACHE_DMADONE_INTSTATUS bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_DMADONE_INTSTATUS_OFFSETADDRESS FLASHCACHE_INTSTATUS_OFFSETADDRESS
#define FLASHCACHE_DMADONE_INTSTATUS_BITOFFSET  0
#define FLASHCACHE_DMADONE_INTSTATUS_BITFIELDSIZE  1
#define FLASHCACHE_DMADONE_INTSTATUS_BITMASK    0x00000001
#define FLASHCACHE_DMADONE_INTSTATUS_INIT       0x0

/*
 *  FLASHCACHE_FC_VER register defines
 ****************************************************************************************
 */
#define FLASHCACHE_FC_VER_OFFSETADDRESS 0x0000000c  /* RW */
#define FLASHCACHE_FC_VER_BITOFFSET    0
#define FLASHCACHE_FC_VER_BITFIELDSIZE 32
#define FLASHCACHE_FC_VER_BITMASK      0xFFFFFFFF
#define FLASHCACHE_FC_VER_INIT         0x00000123
/*
 *  FLASHCACHE_FC_VER_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_FC_VER_F_OFFSETADDRESS       FLASHCACHE_FC_VER_OFFSETADDRESS
#define FLASHCACHE_FC_VER_F_BITOFFSET           0
#define FLASHCACHE_FC_VER_F_BITFIELDSIZE       32
#define FLASHCACHE_FC_VER_F_BITMASK             0xffffffff
#define FLASHCACHE_FC_VER_F_INIT                0x123

/*
 *  FLASHCACHE_PATCH_FLASH_BASE register defines
 ****************************************************************************************
 */
#define FLASHCACHE_PATCH_FLASH_BASE_OFFSETADDRESS 0x00000010  /* RW */
#define FLASHCACHE_PATCH_FLASH_BASE_BITOFFSET 0
#define FLASHCACHE_PATCH_FLASH_BASE_BITFIELDSIZE 32
#define FLASHCACHE_PATCH_FLASH_BASE_BITMASK 0xFFFFFFFF
#define FLASHCACHE_PATCH_FLASH_BASE_INIT 0x00000000
/*
 *  FLASHCACHE_PATCH_FLASH_BASE_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_PATCH_FLASH_BASE_F_OFFSETADDRESS FLASHCACHE_PATCH_FLASH_BASE_OFFSETADDRESS
#define FLASHCACHE_PATCH_FLASH_BASE_F_BITOFFSET  0
#define FLASHCACHE_PATCH_FLASH_BASE_F_BITFIELDSIZE 32
#define FLASHCACHE_PATCH_FLASH_BASE_F_BITMASK   0xffffffff
#define FLASHCACHE_PATCH_FLASH_BASE_F_INIT      0x0

/*
 *  FLASHCACHE_PATCH_SRAM_BASE register defines
 ****************************************************************************************
 */
#define FLASHCACHE_PATCH_SRAM_BASE_OFFSETADDRESS 0x00000018  /* RW */
#define FLASHCACHE_PATCH_SRAM_BASE_BITOFFSET 0
#define FLASHCACHE_PATCH_SRAM_BASE_BITFIELDSIZE 32
#define FLASHCACHE_PATCH_SRAM_BASE_BITMASK 0xFFFFFFFF
#define FLASHCACHE_PATCH_SRAM_BASE_INIT 0x00000000
/*
 *  FLASHCACHE_PATCH_SRAM_BASE_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_PATCH_SRAM_BASE_F_OFFSETADDRESS FLASHCACHE_PATCH_SRAM_BASE_OFFSETADDRESS
#define FLASHCACHE_PATCH_SRAM_BASE_F_BITOFFSET  0
#define FLASHCACHE_PATCH_SRAM_BASE_F_BITFIELDSIZE 32
#define FLASHCACHE_PATCH_SRAM_BASE_F_BITMASK    0xffffffff
#define FLASHCACHE_PATCH_SRAM_BASE_F_INIT       0x0

/*
 *  FLASHCACHE_PATCH_CPU_BASE register defines
 ****************************************************************************************
 */
#define FLASHCACHE_PATCH_CPU_BASE_OFFSETADDRESS 0x00000440  /* RW */
#define FLASHCACHE_PATCH_CPU_BASE_BITOFFSET 0
#define FLASHCACHE_PATCH_CPU_BASE_BITFIELDSIZE 32
#define FLASHCACHE_PATCH_CPU_BASE_BITMASK 0xFFFFFFFF
#define FLASHCACHE_PATCH_CPU_BASE_INIT 0x00000000
/*
 *  FLASHCACHE_PATCH_CPU_BASE_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_PATCH_CPU_BASE_F_OFFSETADDRESS FLASHCACHE_PATCH_CPU_BASE_OFFSETADDRESS
#define FLASHCACHE_PATCH_CPU_BASE_F_BITOFFSET   0
#define FLASHCACHE_PATCH_CPU_BASE_F_BITFIELDSIZE 32
#define FLASHCACHE_PATCH_CPU_BASE_F_BITMASK     0xffffffff
#define FLASHCACHE_PATCH_CPU_BASE_F_INIT        0x0

/*
 *  FLASHCACHE_BLK_REMAP_CTL register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP_CTL_OFFSETADDRESS 0x00000800  /* RW */
#define FLASHCACHE_BLK_REMAP_CTL_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP_CTL_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP_CTL_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP_CTL_INIT  0x00000000
/*
 *  FLASHCACHE_BLK_REMAP_EN bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP_EN_OFFSETADDRESS   FLASHCACHE_BLK_REMAP_CTL_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP_EN_BITOFFSET      31
#define FLASHCACHE_BLK_REMAP_EN_BITFIELDSIZE    1
#define FLASHCACHE_BLK_REMAP_EN_BITMASK         0x80000000
#define FLASHCACHE_BLK_REMAP_EN_INIT            0x0

/*
 *  FLASHCACHE_BLK_REMAP_STATUS register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP_STATUS_OFFSETADDRESS 0x00000804  /* RW */
#define FLASHCACHE_BLK_REMAP_STATUS_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP_STATUS_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP_STATUS_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP_STATUS_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP7_MATCH bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP7_MATCH_OFFSETADDRESS FLASHCACHE_BLK_REMAP_STATUS_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP7_MATCH_BITOFFSET   7
#define FLASHCACHE_BLK_REMAP7_MATCH_BITFIELDSIZE  1
#define FLASHCACHE_BLK_REMAP7_MATCH_BITMASK     0x00000080
#define FLASHCACHE_BLK_REMAP7_MATCH_INIT        0x0
/*
 *  FLASHCACHE_BLK_REMAP6_MATCH bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP6_MATCH_OFFSETADDRESS FLASHCACHE_BLK_REMAP_STATUS_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP6_MATCH_BITOFFSET   6
#define FLASHCACHE_BLK_REMAP6_MATCH_BITFIELDSIZE  1
#define FLASHCACHE_BLK_REMAP6_MATCH_BITMASK     0x00000040
#define FLASHCACHE_BLK_REMAP6_MATCH_INIT        0x0
/*
 *  FLASHCACHE_BLK_REMAP5_MATCH bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP5_MATCH_OFFSETADDRESS FLASHCACHE_BLK_REMAP_STATUS_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP5_MATCH_BITOFFSET   5
#define FLASHCACHE_BLK_REMAP5_MATCH_BITFIELDSIZE  1
#define FLASHCACHE_BLK_REMAP5_MATCH_BITMASK     0x00000020
#define FLASHCACHE_BLK_REMAP5_MATCH_INIT        0x0
/*
 *  FLASHCACHE_BLK_REMAP4_MATCH bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP4_MATCH_OFFSETADDRESS FLASHCACHE_BLK_REMAP_STATUS_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP4_MATCH_BITOFFSET   4
#define FLASHCACHE_BLK_REMAP4_MATCH_BITFIELDSIZE  1
#define FLASHCACHE_BLK_REMAP4_MATCH_BITMASK     0x00000010
#define FLASHCACHE_BLK_REMAP4_MATCH_INIT        0x0
/*
 *  FLASHCACHE_BLK_REMAP3_MATCH bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP3_MATCH_OFFSETADDRESS FLASHCACHE_BLK_REMAP_STATUS_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP3_MATCH_BITOFFSET   3
#define FLASHCACHE_BLK_REMAP3_MATCH_BITFIELDSIZE  1
#define FLASHCACHE_BLK_REMAP3_MATCH_BITMASK     0x00000008
#define FLASHCACHE_BLK_REMAP3_MATCH_INIT        0x0
/*
 *  FLASHCACHE_BLK_REMAP2_MATCH bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP2_MATCH_OFFSETADDRESS FLASHCACHE_BLK_REMAP_STATUS_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP2_MATCH_BITOFFSET   2
#define FLASHCACHE_BLK_REMAP2_MATCH_BITFIELDSIZE  1
#define FLASHCACHE_BLK_REMAP2_MATCH_BITMASK     0x00000004
#define FLASHCACHE_BLK_REMAP2_MATCH_INIT        0x0
/*
 *  FLASHCACHE_BLK_REMAP1_MATCH bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP1_MATCH_OFFSETADDRESS FLASHCACHE_BLK_REMAP_STATUS_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP1_MATCH_BITOFFSET   1
#define FLASHCACHE_BLK_REMAP1_MATCH_BITFIELDSIZE  1
#define FLASHCACHE_BLK_REMAP1_MATCH_BITMASK     0x00000002
#define FLASHCACHE_BLK_REMAP1_MATCH_INIT        0x0
/*
 *  FLASHCACHE_BLK_REMAP0_MATCH bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP0_MATCH_OFFSETADDRESS FLASHCACHE_BLK_REMAP_STATUS_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP0_MATCH_BITOFFSET   0
#define FLASHCACHE_BLK_REMAP0_MATCH_BITFIELDSIZE  1
#define FLASHCACHE_BLK_REMAP0_MATCH_BITMASK     0x00000001
#define FLASHCACHE_BLK_REMAP0_MATCH_INIT        0x0

/*
 *  FLASHCACHE_BLK_REMAP0_BASE register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP0_BASE_OFFSETADDRESS 0x00000808  /* RW */
#define FLASHCACHE_BLK_REMAP0_BASE_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP0_BASE_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP0_BASE_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP0_BASE_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP0_BASE_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP0_BASE_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP0_BASE_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP0_BASE_F_BITOFFSET  0
#define FLASHCACHE_BLK_REMAP0_BASE_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP0_BASE_F_BITMASK    0xffffffff
#define FLASHCACHE_BLK_REMAP0_BASE_F_INIT       0x0

/*
 *  FLASHCACHE_BLK_REMAP0_MASK register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP0_MASK_OFFSETADDRESS 0x0000080c  /* RW */
#define FLASHCACHE_BLK_REMAP0_MASK_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP0_MASK_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP0_MASK_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP0_MASK_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP0_MASK_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP0_MASK_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP0_MASK_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP0_MASK_F_BITOFFSET  0
#define FLASHCACHE_BLK_REMAP0_MASK_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP0_MASK_F_BITMASK    0xffffffff
#define FLASHCACHE_BLK_REMAP0_MASK_F_INIT       0x0

/*
 *  FLASHCACHE_BLK_REMAP0_DST register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP0_DST_OFFSETADDRESS 0x00000810  /* RW */
#define FLASHCACHE_BLK_REMAP0_DST_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP0_DST_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP0_DST_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP0_DST_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP0_DST_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP0_DST_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP0_DST_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP0_DST_F_BITOFFSET   0
#define FLASHCACHE_BLK_REMAP0_DST_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP0_DST_F_BITMASK     0xffffffff
#define FLASHCACHE_BLK_REMAP0_DST_F_INIT        0x0

/*
 *  FLASHCACHE_BLK_REMAP1_BASE register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP1_BASE_OFFSETADDRESS 0x00000814  /* RW */
#define FLASHCACHE_BLK_REMAP1_BASE_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP1_BASE_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP1_BASE_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP1_BASE_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP1_BASE_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP1_BASE_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP1_BASE_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP1_BASE_F_BITOFFSET  0
#define FLASHCACHE_BLK_REMAP1_BASE_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP1_BASE_F_BITMASK    0xffffffff
#define FLASHCACHE_BLK_REMAP1_BASE_F_INIT       0x0

/*
 *  FLASHCACHE_BLK_REMAP1_MASK register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP1_MASK_OFFSETADDRESS 0x00000818  /* RW */
#define FLASHCACHE_BLK_REMAP1_MASK_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP1_MASK_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP1_MASK_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP1_MASK_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP1_MASK_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP1_MASK_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP1_MASK_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP1_MASK_F_BITOFFSET  0
#define FLASHCACHE_BLK_REMAP1_MASK_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP1_MASK_F_BITMASK    0xffffffff
#define FLASHCACHE_BLK_REMAP1_MASK_F_INIT       0x0

/*
 *  FLASHCACHE_BLK_REMAP1_DST register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP1_DST_OFFSETADDRESS 0x0000081c  /* RW */
#define FLASHCACHE_BLK_REMAP1_DST_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP1_DST_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP1_DST_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP1_DST_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP1_DST_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP1_DST_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP1_DST_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP1_DST_F_BITOFFSET   0
#define FLASHCACHE_BLK_REMAP1_DST_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP1_DST_F_BITMASK     0xffffffff
#define FLASHCACHE_BLK_REMAP1_DST_F_INIT        0x0

/*
 *  FLASHCACHE_BLK_REMAP2_BASE register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP2_BASE_OFFSETADDRESS 0x00000820  /* RW */
#define FLASHCACHE_BLK_REMAP2_BASE_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP2_BASE_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP2_BASE_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP2_BASE_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP2_BASE_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP2_BASE_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP2_BASE_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP2_BASE_F_BITOFFSET  0
#define FLASHCACHE_BLK_REMAP2_BASE_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP2_BASE_F_BITMASK    0xffffffff
#define FLASHCACHE_BLK_REMAP2_BASE_F_INIT       0x0

/*
 *  FLASHCACHE_BLK_REMAP2_MASK register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP2_MASK_OFFSETADDRESS 0x00000824  /* RW */
#define FLASHCACHE_BLK_REMAP2_MASK_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP2_MASK_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP2_MASK_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP2_MASK_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP2_MASK_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP2_MASK_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP2_MASK_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP2_MASK_F_BITOFFSET  0
#define FLASHCACHE_BLK_REMAP2_MASK_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP2_MASK_F_BITMASK    0xffffffff
#define FLASHCACHE_BLK_REMAP2_MASK_F_INIT       0x0

/*
 *  FLASHCACHE_BLK_REMAP2_DST register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP2_DST_OFFSETADDRESS 0x00000828  /* RW */
#define FLASHCACHE_BLK_REMAP2_DST_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP2_DST_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP2_DST_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP2_DST_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP2_DST_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP2_DST_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP2_DST_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP2_DST_F_BITOFFSET   0
#define FLASHCACHE_BLK_REMAP2_DST_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP2_DST_F_BITMASK     0xffffffff
#define FLASHCACHE_BLK_REMAP2_DST_F_INIT        0x0

/*
 *  FLASHCACHE_BLK_REMAP3_BASE register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP3_BASE_OFFSETADDRESS 0x0000082c  /* RW */
#define FLASHCACHE_BLK_REMAP3_BASE_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP3_BASE_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP3_BASE_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP3_BASE_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP3_BASE_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP3_BASE_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP3_BASE_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP3_BASE_F_BITOFFSET  0
#define FLASHCACHE_BLK_REMAP3_BASE_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP3_BASE_F_BITMASK    0xffffffff
#define FLASHCACHE_BLK_REMAP3_BASE_F_INIT       0x0

/*
 *  FLASHCACHE_BLK_REMAP3_MASK register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP3_MASK_OFFSETADDRESS 0x00000830  /* RW */
#define FLASHCACHE_BLK_REMAP3_MASK_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP3_MASK_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP3_MASK_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP3_MASK_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP3_MASK_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP3_MASK_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP3_MASK_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP3_MASK_F_BITOFFSET  0
#define FLASHCACHE_BLK_REMAP3_MASK_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP3_MASK_F_BITMASK    0xffffffff
#define FLASHCACHE_BLK_REMAP3_MASK_F_INIT       0x0

/*
 *  FLASHCACHE_BLK_REMAP3_DST register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP3_DST_OFFSETADDRESS 0x00000834  /* RW */
#define FLASHCACHE_BLK_REMAP3_DST_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP3_DST_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP3_DST_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP3_DST_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP3_DST_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP3_DST_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP3_DST_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP3_DST_F_BITOFFSET   0
#define FLASHCACHE_BLK_REMAP3_DST_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP3_DST_F_BITMASK     0xffffffff
#define FLASHCACHE_BLK_REMAP3_DST_F_INIT        0x0

/*
 *  FLASHCACHE_BLK_REMAP4_BASE register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP4_BASE_OFFSETADDRESS 0x00000838  /* RW */
#define FLASHCACHE_BLK_REMAP4_BASE_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP4_BASE_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP4_BASE_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP4_BASE_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP4_BASE_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP4_BASE_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP4_BASE_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP4_BASE_F_BITOFFSET  0
#define FLASHCACHE_BLK_REMAP4_BASE_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP4_BASE_F_BITMASK    0xffffffff
#define FLASHCACHE_BLK_REMAP4_BASE_F_INIT       0x0

/*
 *  FLASHCACHE_BLK_REMAP4_MASK register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP4_MASK_OFFSETADDRESS 0x0000083c  /* RW */
#define FLASHCACHE_BLK_REMAP4_MASK_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP4_MASK_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP4_MASK_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP4_MASK_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP4_MASK_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP4_MASK_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP4_MASK_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP4_MASK_F_BITOFFSET  0
#define FLASHCACHE_BLK_REMAP4_MASK_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP4_MASK_F_BITMASK    0xffffffff
#define FLASHCACHE_BLK_REMAP4_MASK_F_INIT       0x0

/*
 *  FLASHCACHE_BLK_REMAP4_DST register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP4_DST_OFFSETADDRESS 0x00000840  /* RW */
#define FLASHCACHE_BLK_REMAP4_DST_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP4_DST_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP4_DST_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP4_DST_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP4_DST_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP4_DST_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP4_DST_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP4_DST_F_BITOFFSET   0
#define FLASHCACHE_BLK_REMAP4_DST_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP4_DST_F_BITMASK     0xffffffff
#define FLASHCACHE_BLK_REMAP4_DST_F_INIT        0x0

/*
 *  FLASHCACHE_BLK_REMAP5_BASE register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP5_BASE_OFFSETADDRESS 0x00000844  /* RW */
#define FLASHCACHE_BLK_REMAP5_BASE_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP5_BASE_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP5_BASE_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP5_BASE_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP5_BASE_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP5_BASE_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP5_BASE_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP5_BASE_F_BITOFFSET  0
#define FLASHCACHE_BLK_REMAP5_BASE_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP5_BASE_F_BITMASK    0xffffffff
#define FLASHCACHE_BLK_REMAP5_BASE_F_INIT       0x0

/*
 *  FLASHCACHE_BLK_REMAP5_MASK register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP5_MASK_OFFSETADDRESS 0x00000848  /* RW */
#define FLASHCACHE_BLK_REMAP5_MASK_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP5_MASK_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP5_MASK_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP5_MASK_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP5_MASK_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP5_MASK_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP5_MASK_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP5_MASK_F_BITOFFSET  0
#define FLASHCACHE_BLK_REMAP5_MASK_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP5_MASK_F_BITMASK    0xffffffff
#define FLASHCACHE_BLK_REMAP5_MASK_F_INIT       0x0

/*
 *  FLASHCACHE_BLK_REMAP5_DST register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP5_DST_OFFSETADDRESS 0x0000084c  /* RW */
#define FLASHCACHE_BLK_REMAP5_DST_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP5_DST_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP5_DST_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP5_DST_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP5_DST_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP5_DST_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP5_DST_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP5_DST_F_BITOFFSET   0
#define FLASHCACHE_BLK_REMAP5_DST_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP5_DST_F_BITMASK     0xffffffff
#define FLASHCACHE_BLK_REMAP5_DST_F_INIT        0x0

/*
 *  FLASHCACHE_BLK_REMAP6_BASE register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP6_BASE_OFFSETADDRESS 0x00000850  /* RW */
#define FLASHCACHE_BLK_REMAP6_BASE_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP6_BASE_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP6_BASE_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP6_BASE_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP6_BASE_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP6_BASE_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP6_BASE_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP6_BASE_F_BITOFFSET  0
#define FLASHCACHE_BLK_REMAP6_BASE_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP6_BASE_F_BITMASK    0xffffffff
#define FLASHCACHE_BLK_REMAP6_BASE_F_INIT       0x0

/*
 *  FLASHCACHE_BLK_REMAP6_MASK register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP6_MASK_OFFSETADDRESS 0x00000854  /* RW */
#define FLASHCACHE_BLK_REMAP6_MASK_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP6_MASK_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP6_MASK_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP6_MASK_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP6_MASK_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP6_MASK_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP6_MASK_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP6_MASK_F_BITOFFSET  0
#define FLASHCACHE_BLK_REMAP6_MASK_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP6_MASK_F_BITMASK    0xffffffff
#define FLASHCACHE_BLK_REMAP6_MASK_F_INIT       0x0

/*
 *  FLASHCACHE_BLK_REMAP6_DST register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP6_DST_OFFSETADDRESS 0x00000858  /* RW */
#define FLASHCACHE_BLK_REMAP6_DST_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP6_DST_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP6_DST_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP6_DST_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP6_DST_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP6_DST_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP6_DST_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP6_DST_F_BITOFFSET   0
#define FLASHCACHE_BLK_REMAP6_DST_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP6_DST_F_BITMASK     0xffffffff
#define FLASHCACHE_BLK_REMAP6_DST_F_INIT        0x0

/*
 *  FLASHCACHE_BLK_REMAP7_BASE register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP7_BASE_OFFSETADDRESS 0x0000085c  /* RW */
#define FLASHCACHE_BLK_REMAP7_BASE_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP7_BASE_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP7_BASE_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP7_BASE_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP7_BASE_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP7_BASE_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP7_BASE_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP7_BASE_F_BITOFFSET  0
#define FLASHCACHE_BLK_REMAP7_BASE_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP7_BASE_F_BITMASK    0xffffffff
#define FLASHCACHE_BLK_REMAP7_BASE_F_INIT       0x0

/*
 *  FLASHCACHE_BLK_REMAP7_MASK register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP7_MASK_OFFSETADDRESS 0x00000860  /* RW */
#define FLASHCACHE_BLK_REMAP7_MASK_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP7_MASK_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP7_MASK_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP7_MASK_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP7_MASK_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP7_MASK_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP7_MASK_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP7_MASK_F_BITOFFSET  0
#define FLASHCACHE_BLK_REMAP7_MASK_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP7_MASK_F_BITMASK    0xffffffff
#define FLASHCACHE_BLK_REMAP7_MASK_F_INIT       0x0

/*
 *  FLASHCACHE_BLK_REMAP7_DST register defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP7_DST_OFFSETADDRESS 0x00000864  /* RW */
#define FLASHCACHE_BLK_REMAP7_DST_BITOFFSET 0
#define FLASHCACHE_BLK_REMAP7_DST_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP7_DST_BITMASK 0xFFFFFFFF
#define FLASHCACHE_BLK_REMAP7_DST_INIT 0x00000000
/*
 *  FLASHCACHE_BLK_REMAP7_DST_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP7_DST_F_OFFSETADDRESS FLASHCACHE_BLK_REMAP7_DST_OFFSETADDRESS
#define FLASHCACHE_BLK_REMAP7_DST_F_BITOFFSET   0
#define FLASHCACHE_BLK_REMAP7_DST_F_BITFIELDSIZE 32
#define FLASHCACHE_BLK_REMAP7_DST_F_BITMASK     0xffffffff
#define FLASHCACHE_BLK_REMAP7_DST_F_INIT        0x0

/*
 *  FLASHCACHE_DMA_FLASH_ADDR register defines
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_FLASH_ADDR_OFFSETADDRESS 0x00000c00  /* RW */
#define FLASHCACHE_DMA_FLASH_ADDR_BITOFFSET 0
#define FLASHCACHE_DMA_FLASH_ADDR_BITFIELDSIZE 32
#define FLASHCACHE_DMA_FLASH_ADDR_BITMASK 0xFFFFFFFF
#define FLASHCACHE_DMA_FLASH_ADDR_INIT 0x00000000
/*
 *  FLASHCACHE_DMA_FLASH_ADDR_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_FLASH_ADDR_F_OFFSETADDRESS FLASHCACHE_DMA_FLASH_ADDR_OFFSETADDRESS
#define FLASHCACHE_DMA_FLASH_ADDR_F_BITOFFSET   0
#define FLASHCACHE_DMA_FLASH_ADDR_F_BITFIELDSIZE 32
#define FLASHCACHE_DMA_FLASH_ADDR_F_BITMASK     0xffffffff
#define FLASHCACHE_DMA_FLASH_ADDR_F_INIT        0x0

/*
 *  FLASHCACHE_DMA_SRAM_ADDR register defines
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_SRAM_ADDR_OFFSETADDRESS 0x00000c04  /* RW */
#define FLASHCACHE_DMA_SRAM_ADDR_BITOFFSET 0
#define FLASHCACHE_DMA_SRAM_ADDR_BITFIELDSIZE 32
#define FLASHCACHE_DMA_SRAM_ADDR_BITMASK 0xFFFFFFFF
#define FLASHCACHE_DMA_SRAM_ADDR_INIT  0x00000000
/*
 *  FLASHCACHE_DMA_SRAM_ADDR_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_SRAM_ADDR_F_OFFSETADDRESS FLASHCACHE_DMA_SRAM_ADDR_OFFSETADDRESS
#define FLASHCACHE_DMA_SRAM_ADDR_F_BITOFFSET    0
#define FLASHCACHE_DMA_SRAM_ADDR_F_BITFIELDSIZE 32
#define FLASHCACHE_DMA_SRAM_ADDR_F_BITMASK      0xffffffff
#define FLASHCACHE_DMA_SRAM_ADDR_F_INIT         0x0

/*
 *  FLASHCACHE_DMA_LEN_TRIG register defines
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_LEN_TRIG_OFFSETADDRESS 0x00000c08  /* RW */
#define FLASHCACHE_DMA_LEN_TRIG_BITOFFSET 0
#define FLASHCACHE_DMA_LEN_TRIG_BITFIELDSIZE 32
#define FLASHCACHE_DMA_LEN_TRIG_BITMASK 0xFFFFFFFF
#define FLASHCACHE_DMA_LEN_TRIG_INIT   0x00000000
/*
 *  FLASHCACHE_DMA_LEN_TRIG_F bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_LEN_TRIG_F_OFFSETADDRESS FLASHCACHE_DMA_LEN_TRIG_OFFSETADDRESS
#define FLASHCACHE_DMA_LEN_TRIG_F_BITOFFSET     0
#define FLASHCACHE_DMA_LEN_TRIG_F_BITFIELDSIZE 32
#define FLASHCACHE_DMA_LEN_TRIG_F_BITMASK       0xffffffff
#define FLASHCACHE_DMA_LEN_TRIG_F_INIT          0x0

/*
 *  FLASHCACHE_DMA_STATUS register defines
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_STATUS_OFFSETADDRESS 0x00000c0c  /* RW */
#define FLASHCACHE_DMA_STATUS_BITOFFSET 0
#define FLASHCACHE_DMA_STATUS_BITFIELDSIZE 32
#define FLASHCACHE_DMA_STATUS_BITMASK  0xFFFFFFFF
#define FLASHCACHE_DMA_STATUS_INIT     0x00000000
/*
 *  FLASHCACHE_PATCH_DMA_CMPL bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_PATCH_DMA_CMPL_OFFSETADDRESS FLASHCACHE_DMA_STATUS_OFFSETADDRESS
#define FLASHCACHE_PATCH_DMA_CMPL_BITOFFSET     4
#define FLASHCACHE_PATCH_DMA_CMPL_BITFIELDSIZE  1
#define FLASHCACHE_PATCH_DMA_CMPL_BITMASK       0x00000010
#define FLASHCACHE_PATCH_DMA_CMPL_INIT          0x0
/*
 *  FLASHCACHE_PATCH_DMA_REQ bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_PATCH_DMA_REQ_OFFSETADDRESS  FLASHCACHE_DMA_STATUS_OFFSETADDRESS
#define FLASHCACHE_PATCH_DMA_REQ_BITOFFSET      3
#define FLASHCACHE_PATCH_DMA_REQ_BITFIELDSIZE   1
#define FLASHCACHE_PATCH_DMA_REQ_BITMASK        0x00000008
#define FLASHCACHE_PATCH_DMA_REQ_INIT           0x0
/*
 *  FLASHCACHE_DMA_DONE bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_DONE_OFFSETADDRESS       FLASHCACHE_DMA_STATUS_OFFSETADDRESS
#define FLASHCACHE_DMA_DONE_BITOFFSET           2
#define FLASHCACHE_DMA_DONE_BITFIELDSIZE        1
#define FLASHCACHE_DMA_DONE_BITMASK             0x00000004
#define FLASHCACHE_DMA_DONE_INIT                0x0
/*
 *  FLASHCACHE_DMA_BUSY bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_BUSY_OFFSETADDRESS       FLASHCACHE_DMA_STATUS_OFFSETADDRESS
#define FLASHCACHE_DMA_BUSY_BITOFFSET           1
#define FLASHCACHE_DMA_BUSY_BITFIELDSIZE        1
#define FLASHCACHE_DMA_BUSY_BITMASK             0x00000002
#define FLASHCACHE_DMA_BUSY_INIT                0x0
/*
 *  FLASHCACHE_DMA_REQ_PENDING bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_REQ_PENDING_OFFSETADDRESS FLASHCACHE_DMA_STATUS_OFFSETADDRESS
#define FLASHCACHE_DMA_REQ_PENDING_BITOFFSET    0
#define FLASHCACHE_DMA_REQ_PENDING_BITFIELDSIZE  1
#define FLASHCACHE_DMA_REQ_PENDING_BITMASK      0x00000001
#define FLASHCACHE_DMA_REQ_PENDING_INIT         0x0

/*
 *  FLASHCACHE_TAG_REG register defines
 ****************************************************************************************
 */
#define FLASHCACHE_TAG_REG_OFFSETADDRESS 0x00001000  /* RW */
#define FLASHCACHE_TAG_REG_BITOFFSET   0
#define FLASHCACHE_TAG_REG_BITFIELDSIZE 32
#define FLASHCACHE_TAG_REG_BITMASK     0xFFFFFFFF
#define FLASHCACHE_TAG_REG_INIT        0x00000000
/*
 *  FLASHCACHE_TAG_CACHE_INDEX bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_TAG_CACHE_INDEX_OFFSETADDRESS FLASHCACHE_TAG_REG_OFFSETADDRESS
#define FLASHCACHE_TAG_CACHE_INDEX_BITOFFSET   11
#define FLASHCACHE_TAG_CACHE_INDEX_BITFIELDSIZE  6
#define FLASHCACHE_TAG_CACHE_INDEX_BITMASK      0x0001f800
#define FLASHCACHE_TAG_CACHE_INDEX_INIT         0x0
/*
 *  FLASHCACHE_TAG_LOCK bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_TAG_LOCK_OFFSETADDRESS       FLASHCACHE_TAG_REG_OFFSETADDRESS
#define FLASHCACHE_TAG_LOCK_BITOFFSET          10
#define FLASHCACHE_TAG_LOCK_BITFIELDSIZE        1
#define FLASHCACHE_TAG_LOCK_BITMASK             0x00000400
#define FLASHCACHE_TAG_LOCK_INIT                0x0
/*
 *  FLASHCACHE_TAG_VALID bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_TAG_VALID_OFFSETADDRESS      FLASHCACHE_TAG_REG_OFFSETADDRESS
#define FLASHCACHE_TAG_VALID_BITOFFSET          9
#define FLASHCACHE_TAG_VALID_BITFIELDSIZE       1
#define FLASHCACHE_TAG_VALID_BITMASK            0x00000200
#define FLASHCACHE_TAG_VALID_INIT               0x0
/*
 *  FLASHCACHE_TAG_FLASH_INDEX bit field defines
 ****************************************************************************************
 */
#define FLASHCACHE_TAG_FLASH_INDEX_OFFSETADDRESS FLASHCACHE_TAG_REG_OFFSETADDRESS
#define FLASHCACHE_TAG_FLASH_INDEX_BITOFFSET    0
#define FLASHCACHE_TAG_FLASH_INDEX_BITFIELDSIZE  9
#define FLASHCACHE_TAG_FLASH_INDEX_BITMASK      0x000001ff
#define FLASHCACHE_TAG_FLASH_INDEX_INIT         0x0
#endif
