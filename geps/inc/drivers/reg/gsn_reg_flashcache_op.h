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
* $RCSfile: gsn_reg_flashcache_op.h,v $
*
* Description : This file contains flash cache operation macros.
******************************************************************************/

#ifndef _REG_FLASHCACHE_OP_H
#define _REG_FLASHCACHE_OP_H

/***************************************************
 *
 *             FLASHCACHE
 *
 ***************************************************/


/*
 *  FLASHCACHE_INTCTL register macros
 ****************************************************************************************
 */
#define FLASHCACHE_INTCTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_INTCTL))
#define FLASHCACHE_INTCTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_INTCTL, (value))
#define FLASHCACHE_INTCTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_INTCTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_INTCTL) | (value))
#define FLASHCACHE_INTCTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_INTCTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_INTCTL) & (~(value)))

/*
 *  FLASHCACHE_ACCESSERR_INTEN bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_ACCESSERR_INTEN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_ACCESSERR_INTEN)
#define FLASHCACHE_ACCESSERR_INTEN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_ACCESSERR_INTEN, 1)
#define FLASHCACHE_ACCESSERR_INTEN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_ACCESSERR_INTEN, 0)

/*
 *  FLASHCACHE_DMADONE_INTEN bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_DMADONE_INTEN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_DMADONE_INTEN)
#define FLASHCACHE_DMADONE_INTEN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_DMADONE_INTEN, 1)
#define FLASHCACHE_DMADONE_INTEN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_DMADONE_INTEN, 0)


/*
 *  FLASHCACHE_INTSTATUS register macros
 ****************************************************************************************
 */
#define FLASHCACHE_INTSTATUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_INTSTATUS))
#define FLASHCACHE_INTSTATUS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_INTSTATUS, (value))
#define FLASHCACHE_INTSTATUS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_INTSTATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_INTSTATUS) | (value))
#define FLASHCACHE_INTSTATUS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_INTSTATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_INTSTATUS) & (~(value)))

/*
 *  FLASHCACHE_ACCESSERR_INTSTATUS bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_ACCESSERR_INTSTATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_ACCESSERR_INTSTATUS)
#define FLASHCACHE_ACCESSERR_INTSTATUS_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_ACCESSERR_INTSTATUS, 1)
#define FLASHCACHE_ACCESSERR_INTSTATUS_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_ACCESSERR_INTSTATUS, 0)

/*
 *  FLASHCACHE_DMADONE_INTSTATUS bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_DMADONE_INTSTATUS_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_DMADONE_INTSTATUS)
#define FLASHCACHE_DMADONE_INTSTATUS_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_DMADONE_INTSTATUS, 1)
#define FLASHCACHE_DMADONE_INTSTATUS_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_DMADONE_INTSTATUS, 0)


/*
 *  FLASHCACHE_FC_VER register macros
 ****************************************************************************************
 */
#define FLASHCACHE_FC_VER_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_FC_VER))
#define FLASHCACHE_FC_VER_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_FC_VER, (value))
#define FLASHCACHE_FC_VER_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_FC_VER, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_FC_VER) | (value))
#define FLASHCACHE_FC_VER_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_FC_VER, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_FC_VER) & (~(value)))

/*
 *  FLASHCACHE_FC_VER_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_FC_VER_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_FC_VER_F)
#define FLASHCACHE_FC_VER_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_FC_VER_F, (value))


/*
 *  FLASHCACHE_PATCH_FLASH_BASE register macros
 ****************************************************************************************
 */
#define FLASHCACHE_PATCH_FLASH_BASE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_FLASH_BASE))
#define FLASHCACHE_PATCH_FLASH_BASE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_FLASH_BASE, (value))
#define FLASHCACHE_PATCH_FLASH_BASE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_FLASH_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_FLASH_BASE) | (value))
#define FLASHCACHE_PATCH_FLASH_BASE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_FLASH_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_FLASH_BASE) & (~(value)))

/*
 *  FLASHCACHE_PATCH_FLASH_BASE_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_PATCH_FLASH_BASE_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_PATCH_FLASH_BASE_F)
#define FLASHCACHE_PATCH_FLASH_BASE_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_PATCH_FLASH_BASE_F, (value))


/*
 *  FLASHCACHE_PATCH_SRAM_BASE register macros
 ****************************************************************************************
 */
#define FLASHCACHE_PATCH_SRAM_BASE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_SRAM_BASE))
#define FLASHCACHE_PATCH_SRAM_BASE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_SRAM_BASE, (value))
#define FLASHCACHE_PATCH_SRAM_BASE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_SRAM_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_SRAM_BASE) | (value))
#define FLASHCACHE_PATCH_SRAM_BASE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_SRAM_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_SRAM_BASE) & (~(value)))

/*
 *  FLASHCACHE_PATCH_SRAM_BASE_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_PATCH_SRAM_BASE_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_PATCH_SRAM_BASE_F)
#define FLASHCACHE_PATCH_SRAM_BASE_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_PATCH_SRAM_BASE_F, (value))


/*
 *  FLASHCACHE_PATCH_CPU_BASE register macros
 ****************************************************************************************
 */
#define FLASHCACHE_PATCH_CPU_BASE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_CPU_BASE))
#define FLASHCACHE_PATCH_CPU_BASE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_CPU_BASE, (value))
#define FLASHCACHE_PATCH_CPU_BASE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_CPU_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_CPU_BASE) | (value))
#define FLASHCACHE_PATCH_CPU_BASE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_CPU_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_PATCH_CPU_BASE) & (~(value)))

/*
 *  FLASHCACHE_PATCH_CPU_BASE_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_PATCH_CPU_BASE_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_PATCH_CPU_BASE_F)
#define FLASHCACHE_PATCH_CPU_BASE_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_PATCH_CPU_BASE_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP_CTL register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP_CTL_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP_CTL))
#define FLASHCACHE_BLK_REMAP_CTL_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP_CTL, (value))
#define FLASHCACHE_BLK_REMAP_CTL_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP_CTL) | (value))
#define FLASHCACHE_BLK_REMAP_CTL_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP_CTL, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP_CTL) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP_EN bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP_EN_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP_EN)
#define FLASHCACHE_BLK_REMAP_EN_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP_EN, 1)
#define FLASHCACHE_BLK_REMAP_EN_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP_EN, 0)


/*
 *  FLASHCACHE_BLK_REMAP_STATUS register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP_STATUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP_STATUS))
#define FLASHCACHE_BLK_REMAP_STATUS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP_STATUS, (value))
#define FLASHCACHE_BLK_REMAP_STATUS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP_STATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP_STATUS) | (value))
#define FLASHCACHE_BLK_REMAP_STATUS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP_STATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP_STATUS) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP7_MATCH bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP7_MATCH_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP7_MATCH)
#define FLASHCACHE_BLK_REMAP7_MATCH_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP7_MATCH, 1)
#define FLASHCACHE_BLK_REMAP7_MATCH_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP7_MATCH, 0)

/*
 *  FLASHCACHE_BLK_REMAP6_MATCH bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP6_MATCH_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP6_MATCH)
#define FLASHCACHE_BLK_REMAP6_MATCH_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP6_MATCH, 1)
#define FLASHCACHE_BLK_REMAP6_MATCH_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP6_MATCH, 0)

/*
 *  FLASHCACHE_BLK_REMAP5_MATCH bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP5_MATCH_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP5_MATCH)
#define FLASHCACHE_BLK_REMAP5_MATCH_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP5_MATCH, 1)
#define FLASHCACHE_BLK_REMAP5_MATCH_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP5_MATCH, 0)

/*
 *  FLASHCACHE_BLK_REMAP4_MATCH bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP4_MATCH_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP4_MATCH)
#define FLASHCACHE_BLK_REMAP4_MATCH_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP4_MATCH, 1)
#define FLASHCACHE_BLK_REMAP4_MATCH_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP4_MATCH, 0)

/*
 *  FLASHCACHE_BLK_REMAP3_MATCH bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP3_MATCH_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP3_MATCH)
#define FLASHCACHE_BLK_REMAP3_MATCH_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP3_MATCH, 1)
#define FLASHCACHE_BLK_REMAP3_MATCH_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP3_MATCH, 0)

/*
 *  FLASHCACHE_BLK_REMAP2_MATCH bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP2_MATCH_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP2_MATCH)
#define FLASHCACHE_BLK_REMAP2_MATCH_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP2_MATCH, 1)
#define FLASHCACHE_BLK_REMAP2_MATCH_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP2_MATCH, 0)

/*
 *  FLASHCACHE_BLK_REMAP1_MATCH bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP1_MATCH_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP1_MATCH)
#define FLASHCACHE_BLK_REMAP1_MATCH_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP1_MATCH, 1)
#define FLASHCACHE_BLK_REMAP1_MATCH_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP1_MATCH, 0)

/*
 *  FLASHCACHE_BLK_REMAP0_MATCH bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP0_MATCH_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP0_MATCH)
#define FLASHCACHE_BLK_REMAP0_MATCH_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP0_MATCH, 1)
#define FLASHCACHE_BLK_REMAP0_MATCH_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP0_MATCH, 0)


/*
 *  FLASHCACHE_BLK_REMAP0_BASE register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP0_BASE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_BASE))
#define FLASHCACHE_BLK_REMAP0_BASE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_BASE, (value))
#define FLASHCACHE_BLK_REMAP0_BASE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_BASE) | (value))
#define FLASHCACHE_BLK_REMAP0_BASE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_BASE) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP0_BASE_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP0_BASE_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP0_BASE_F)
#define FLASHCACHE_BLK_REMAP0_BASE_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP0_BASE_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP0_MASK register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP0_MASK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_MASK))
#define FLASHCACHE_BLK_REMAP0_MASK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_MASK, (value))
#define FLASHCACHE_BLK_REMAP0_MASK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_MASK) | (value))
#define FLASHCACHE_BLK_REMAP0_MASK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_MASK) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP0_MASK_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP0_MASK_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP0_MASK_F)
#define FLASHCACHE_BLK_REMAP0_MASK_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP0_MASK_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP0_DST register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP0_DST_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_DST))
#define FLASHCACHE_BLK_REMAP0_DST_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_DST, (value))
#define FLASHCACHE_BLK_REMAP0_DST_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_DST, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_DST) | (value))
#define FLASHCACHE_BLK_REMAP0_DST_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_DST, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP0_DST) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP0_DST_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP0_DST_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP0_DST_F)
#define FLASHCACHE_BLK_REMAP0_DST_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP0_DST_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP1_BASE register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP1_BASE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_BASE))
#define FLASHCACHE_BLK_REMAP1_BASE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_BASE, (value))
#define FLASHCACHE_BLK_REMAP1_BASE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_BASE) | (value))
#define FLASHCACHE_BLK_REMAP1_BASE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_BASE) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP1_BASE_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP1_BASE_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP1_BASE_F)
#define FLASHCACHE_BLK_REMAP1_BASE_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP1_BASE_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP1_MASK register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP1_MASK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_MASK))
#define FLASHCACHE_BLK_REMAP1_MASK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_MASK, (value))
#define FLASHCACHE_BLK_REMAP1_MASK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_MASK) | (value))
#define FLASHCACHE_BLK_REMAP1_MASK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_MASK) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP1_MASK_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP1_MASK_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP1_MASK_F)
#define FLASHCACHE_BLK_REMAP1_MASK_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP1_MASK_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP1_DST register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP1_DST_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_DST))
#define FLASHCACHE_BLK_REMAP1_DST_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_DST, (value))
#define FLASHCACHE_BLK_REMAP1_DST_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_DST, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_DST) | (value))
#define FLASHCACHE_BLK_REMAP1_DST_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_DST, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP1_DST) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP1_DST_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP1_DST_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP1_DST_F)
#define FLASHCACHE_BLK_REMAP1_DST_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP1_DST_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP2_BASE register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP2_BASE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_BASE))
#define FLASHCACHE_BLK_REMAP2_BASE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_BASE, (value))
#define FLASHCACHE_BLK_REMAP2_BASE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_BASE) | (value))
#define FLASHCACHE_BLK_REMAP2_BASE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_BASE) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP2_BASE_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP2_BASE_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP2_BASE_F)
#define FLASHCACHE_BLK_REMAP2_BASE_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP2_BASE_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP2_MASK register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP2_MASK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_MASK))
#define FLASHCACHE_BLK_REMAP2_MASK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_MASK, (value))
#define FLASHCACHE_BLK_REMAP2_MASK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_MASK) | (value))
#define FLASHCACHE_BLK_REMAP2_MASK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_MASK) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP2_MASK_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP2_MASK_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP2_MASK_F)
#define FLASHCACHE_BLK_REMAP2_MASK_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP2_MASK_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP2_DST register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP2_DST_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_DST))
#define FLASHCACHE_BLK_REMAP2_DST_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_DST, (value))
#define FLASHCACHE_BLK_REMAP2_DST_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_DST, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_DST) | (value))
#define FLASHCACHE_BLK_REMAP2_DST_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_DST, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP2_DST) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP2_DST_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP2_DST_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP2_DST_F)
#define FLASHCACHE_BLK_REMAP2_DST_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP2_DST_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP3_BASE register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP3_BASE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_BASE))
#define FLASHCACHE_BLK_REMAP3_BASE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_BASE, (value))
#define FLASHCACHE_BLK_REMAP3_BASE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_BASE) | (value))
#define FLASHCACHE_BLK_REMAP3_BASE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_BASE) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP3_BASE_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP3_BASE_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP3_BASE_F)
#define FLASHCACHE_BLK_REMAP3_BASE_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP3_BASE_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP3_MASK register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP3_MASK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_MASK))
#define FLASHCACHE_BLK_REMAP3_MASK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_MASK, (value))
#define FLASHCACHE_BLK_REMAP3_MASK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_MASK) | (value))
#define FLASHCACHE_BLK_REMAP3_MASK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_MASK) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP3_MASK_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP3_MASK_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP3_MASK_F)
#define FLASHCACHE_BLK_REMAP3_MASK_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP3_MASK_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP3_DST register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP3_DST_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_DST))
#define FLASHCACHE_BLK_REMAP3_DST_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_DST, (value))
#define FLASHCACHE_BLK_REMAP3_DST_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_DST, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_DST) | (value))
#define FLASHCACHE_BLK_REMAP3_DST_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_DST, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP3_DST) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP3_DST_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP3_DST_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP3_DST_F)
#define FLASHCACHE_BLK_REMAP3_DST_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP3_DST_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP4_BASE register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP4_BASE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_BASE))
#define FLASHCACHE_BLK_REMAP4_BASE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_BASE, (value))
#define FLASHCACHE_BLK_REMAP4_BASE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_BASE) | (value))
#define FLASHCACHE_BLK_REMAP4_BASE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_BASE) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP4_BASE_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP4_BASE_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP4_BASE_F)
#define FLASHCACHE_BLK_REMAP4_BASE_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP4_BASE_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP4_MASK register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP4_MASK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_MASK))
#define FLASHCACHE_BLK_REMAP4_MASK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_MASK, (value))
#define FLASHCACHE_BLK_REMAP4_MASK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_MASK) | (value))
#define FLASHCACHE_BLK_REMAP4_MASK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_MASK) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP4_MASK_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP4_MASK_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP4_MASK_F)
#define FLASHCACHE_BLK_REMAP4_MASK_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP4_MASK_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP4_DST register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP4_DST_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_DST))
#define FLASHCACHE_BLK_REMAP4_DST_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_DST, (value))
#define FLASHCACHE_BLK_REMAP4_DST_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_DST, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_DST) | (value))
#define FLASHCACHE_BLK_REMAP4_DST_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_DST, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP4_DST) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP4_DST_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP4_DST_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP4_DST_F)
#define FLASHCACHE_BLK_REMAP4_DST_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP4_DST_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP5_BASE register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP5_BASE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_BASE))
#define FLASHCACHE_BLK_REMAP5_BASE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_BASE, (value))
#define FLASHCACHE_BLK_REMAP5_BASE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_BASE) | (value))
#define FLASHCACHE_BLK_REMAP5_BASE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_BASE) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP5_BASE_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP5_BASE_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP5_BASE_F)
#define FLASHCACHE_BLK_REMAP5_BASE_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP5_BASE_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP5_MASK register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP5_MASK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_MASK))
#define FLASHCACHE_BLK_REMAP5_MASK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_MASK, (value))
#define FLASHCACHE_BLK_REMAP5_MASK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_MASK) | (value))
#define FLASHCACHE_BLK_REMAP5_MASK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_MASK) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP5_MASK_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP5_MASK_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP5_MASK_F)
#define FLASHCACHE_BLK_REMAP5_MASK_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP5_MASK_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP5_DST register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP5_DST_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_DST))
#define FLASHCACHE_BLK_REMAP5_DST_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_DST, (value))
#define FLASHCACHE_BLK_REMAP5_DST_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_DST, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_DST) | (value))
#define FLASHCACHE_BLK_REMAP5_DST_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_DST, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP5_DST) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP5_DST_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP5_DST_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP5_DST_F)
#define FLASHCACHE_BLK_REMAP5_DST_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP5_DST_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP6_BASE register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP6_BASE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_BASE))
#define FLASHCACHE_BLK_REMAP6_BASE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_BASE, (value))
#define FLASHCACHE_BLK_REMAP6_BASE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_BASE) | (value))
#define FLASHCACHE_BLK_REMAP6_BASE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_BASE) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP6_BASE_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP6_BASE_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP6_BASE_F)
#define FLASHCACHE_BLK_REMAP6_BASE_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP6_BASE_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP6_MASK register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP6_MASK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_MASK))
#define FLASHCACHE_BLK_REMAP6_MASK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_MASK, (value))
#define FLASHCACHE_BLK_REMAP6_MASK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_MASK) | (value))
#define FLASHCACHE_BLK_REMAP6_MASK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_MASK) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP6_MASK_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP6_MASK_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP6_MASK_F)
#define FLASHCACHE_BLK_REMAP6_MASK_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP6_MASK_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP6_DST register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP6_DST_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_DST))
#define FLASHCACHE_BLK_REMAP6_DST_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_DST, (value))
#define FLASHCACHE_BLK_REMAP6_DST_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_DST, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_DST) | (value))
#define FLASHCACHE_BLK_REMAP6_DST_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_DST, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP6_DST) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP6_DST_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP6_DST_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP6_DST_F)
#define FLASHCACHE_BLK_REMAP6_DST_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP6_DST_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP7_BASE register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP7_BASE_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_BASE))
#define FLASHCACHE_BLK_REMAP7_BASE_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_BASE, (value))
#define FLASHCACHE_BLK_REMAP7_BASE_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_BASE) | (value))
#define FLASHCACHE_BLK_REMAP7_BASE_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_BASE, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_BASE) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP7_BASE_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP7_BASE_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP7_BASE_F)
#define FLASHCACHE_BLK_REMAP7_BASE_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP7_BASE_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP7_MASK register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP7_MASK_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_MASK))
#define FLASHCACHE_BLK_REMAP7_MASK_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_MASK, (value))
#define FLASHCACHE_BLK_REMAP7_MASK_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_MASK) | (value))
#define FLASHCACHE_BLK_REMAP7_MASK_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_MASK, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_MASK) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP7_MASK_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP7_MASK_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP7_MASK_F)
#define FLASHCACHE_BLK_REMAP7_MASK_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP7_MASK_F, (value))


/*
 *  FLASHCACHE_BLK_REMAP7_DST register macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP7_DST_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_DST))
#define FLASHCACHE_BLK_REMAP7_DST_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_DST, (value))
#define FLASHCACHE_BLK_REMAP7_DST_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_DST, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_DST) | (value))
#define FLASHCACHE_BLK_REMAP7_DST_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_DST, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_BLK_REMAP7_DST) & (~(value)))

/*
 *  FLASHCACHE_BLK_REMAP7_DST_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_BLK_REMAP7_DST_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP7_DST_F)
#define FLASHCACHE_BLK_REMAP7_DST_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_BLK_REMAP7_DST_F, (value))


/*
 *  FLASHCACHE_DMA_FLASH_ADDR register macros
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_FLASH_ADDR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_FLASH_ADDR))
#define FLASHCACHE_DMA_FLASH_ADDR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_FLASH_ADDR, (value))
#define FLASHCACHE_DMA_FLASH_ADDR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_FLASH_ADDR, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_FLASH_ADDR) | (value))
#define FLASHCACHE_DMA_FLASH_ADDR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_FLASH_ADDR, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_FLASH_ADDR) & (~(value)))

/*
 *  FLASHCACHE_DMA_FLASH_ADDR_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_FLASH_ADDR_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_DMA_FLASH_ADDR_F)
#define FLASHCACHE_DMA_FLASH_ADDR_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_DMA_FLASH_ADDR_F, (value))


/*
 *  FLASHCACHE_DMA_SRAM_ADDR register macros
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_SRAM_ADDR_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_SRAM_ADDR))
#define FLASHCACHE_DMA_SRAM_ADDR_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_SRAM_ADDR, (value))
#define FLASHCACHE_DMA_SRAM_ADDR_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_SRAM_ADDR, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_SRAM_ADDR) | (value))
#define FLASHCACHE_DMA_SRAM_ADDR_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_SRAM_ADDR, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_SRAM_ADDR) & (~(value)))

/*
 *  FLASHCACHE_DMA_SRAM_ADDR_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_SRAM_ADDR_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_DMA_SRAM_ADDR_F)
#define FLASHCACHE_DMA_SRAM_ADDR_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_DMA_SRAM_ADDR_F, (value))


/*
 *  FLASHCACHE_DMA_LEN_TRIG register macros
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_LEN_TRIG_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_LEN_TRIG))
#define FLASHCACHE_DMA_LEN_TRIG_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_LEN_TRIG, (value))
#define FLASHCACHE_DMA_LEN_TRIG_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_LEN_TRIG, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_LEN_TRIG) | (value))
#define FLASHCACHE_DMA_LEN_TRIG_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_LEN_TRIG, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_LEN_TRIG) & (~(value)))

/*
 *  FLASHCACHE_DMA_LEN_TRIG_F bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_LEN_TRIG_F_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_DMA_LEN_TRIG_F)
#define FLASHCACHE_DMA_LEN_TRIG_F_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_DMA_LEN_TRIG_F, (value))


/*
 *  FLASHCACHE_DMA_STATUS register macros
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_STATUS_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_STATUS))
#define FLASHCACHE_DMA_STATUS_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_STATUS, (value))
#define FLASHCACHE_DMA_STATUS_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_STATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_STATUS) | (value))
#define FLASHCACHE_DMA_STATUS_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_STATUS, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_DMA_STATUS) & (~(value)))

/*
 *  FLASHCACHE_PATCH_DMA_CMPL bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_PATCH_DMA_CMPL_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_PATCH_DMA_CMPL)
#define FLASHCACHE_PATCH_DMA_CMPL_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_PATCH_DMA_CMPL, 1)
#define FLASHCACHE_PATCH_DMA_CMPL_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_PATCH_DMA_CMPL, 0)

/*
 *  FLASHCACHE_PATCH_DMA_REQ bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_PATCH_DMA_REQ_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_PATCH_DMA_REQ)
#define FLASHCACHE_PATCH_DMA_REQ_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_PATCH_DMA_REQ, 1)
#define FLASHCACHE_PATCH_DMA_REQ_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_PATCH_DMA_REQ, 0)

/*
 *  FLASHCACHE_DMA_DONE bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_DONE_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_DMA_DONE)
#define FLASHCACHE_DMA_DONE_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_DMA_DONE, 1)
#define FLASHCACHE_DMA_DONE_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_DMA_DONE, 0)

/*
 *  FLASHCACHE_DMA_BUSY bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_BUSY_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_DMA_BUSY)
#define FLASHCACHE_DMA_BUSY_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_DMA_BUSY, 1)
#define FLASHCACHE_DMA_BUSY_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_DMA_BUSY, 0)

/*
 *  FLASHCACHE_DMA_REQ_PENDING bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_DMA_REQ_PENDING_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_DMA_REQ_PENDING)
#define FLASHCACHE_DMA_REQ_PENDING_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_DMA_REQ_PENDING, 1)
#define FLASHCACHE_DMA_REQ_PENDING_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_DMA_REQ_PENDING, 0)


/*
 *  FLASHCACHE_TAG_REG register macros
 ****************************************************************************************
 */
#define FLASHCACHE_TAG_REG_GET(addr) \
        (GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_TAG_REG))
#define FLASHCACHE_TAG_REG_SET(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_TAG_REG, (value))
#define FLASHCACHE_TAG_REG_SETBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_TAG_REG, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_TAG_REG) | (value))
#define FLASHCACHE_TAG_REG_CLEARBIT(addr, value) \
        SET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_TAG_REG, GET_WORD_EXCLUSIVE_BITFIELD(addr, FLASHCACHE_TAG_REG) & (~(value)))

/*
 *  FLASHCACHE_TAG_CACHE_INDEX bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_TAG_CACHE_INDEX_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_TAG_CACHE_INDEX)
#define FLASHCACHE_TAG_CACHE_INDEX_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_TAG_CACHE_INDEX, (value))

/*
 *  FLASHCACHE_TAG_LOCK bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_TAG_LOCK_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_TAG_LOCK)
#define FLASHCACHE_TAG_LOCK_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_TAG_LOCK, 1)
#define FLASHCACHE_TAG_LOCK_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_TAG_LOCK, 0)

/*
 *  FLASHCACHE_TAG_VALID bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_TAG_VALID_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_TAG_VALID)
#define FLASHCACHE_TAG_VALID_SET(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_TAG_VALID, 1)
#define FLASHCACHE_TAG_VALID_CLEAR(addr) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_TAG_VALID, 0)

/*
 *  FLASHCACHE_TAG_FLASH_INDEX bit field macros
 ****************************************************************************************
 */
#define FLASHCACHE_TAG_FLASH_INDEX_GET(addr) \
        GET_WORD_BITFIELD_N(addr, FLASHCACHE_TAG_FLASH_INDEX)
#define FLASHCACHE_TAG_FLASH_INDEX_SET(addr, value) \
        SET_WORD_BITFIELD_N(addr, FLASHCACHE_TAG_FLASH_INDEX, (value))

#endif
