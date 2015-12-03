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


#ifndef ELP_KEPHW_H
#define ELP_KEPHW_H

#define KEP_REG_IRQ_CTRL           0x0008
#define KEP_REG_FIFO_STAT          0x000C
#define KEP_REG_SRC_PTR            0x0020
#define KEP_REG_DST_PTR            0x0024
#define KEP_REG_OFFSET             0x0028
#define KEP_REG_LEN                0x002C
#define KEP_REG_SW_CTRL            0x003C
#define KEP_REG_CTRL               0x0040
#define KEP_REG_POP                0x0050
#define KEP_REG_STATUS             0x0054

// FIFO STAT
#define _KEP_FIFO_CMD_CNT            0
#define _KEP_FIFO_CMD_FULL           7
#define _KEP_FIFO_STAT_CNT          24
#define _KEP_FIFO_STAT_EMPTY        31

#define KEP_FIFO_CMD_CNT(x)         ((x >> _KEP_FIFO_CMD_CNT)&0x7F)
#define KEP_FIFO_CMD_FULL(x)        ((x >> _KEP_FIFO_CMD_FULL)&0x1)
#define KEP_FIFO_STAT_CNT(x)        ((x >> _KEP_FIFO_STAT_CNT)&0x7F)
#define KEP_FIFO_STAT_EMPTY(x)      ((x >> _KEP_FIFO_STAT_EMPTY)&0x1)

// OFFSET
#define _KEP_SRC_OFFSET              0
#define _KEP_DST_OFFSET             16
#define KEP_OFFSET(src, dst)         ( ((src & 0xFFFF) << _KEP_SRC_OFFSET) | ((dst & 0xFFFF) << _KEP_DST_OFFSET) )

// CTRL
#define _KEP_CTRL_CMD                0
#define _KEP_CTRL_OPT                4
#define _KEP_CTRL_CTX_IDX           16
#define KEP_CTRL(cmd, opt, idx)     (  ((cmd & 7) << _KEP_CTRL_CMD) | ((opt & 0xF) << _KEP_CTRL_OPT) | ((idx & 0xFF) << _KEP_CTRL_CTX_IDX) )

// STATUS
#define _KEP_STATUS_SWID            16
#define _KEP_STATUS_RETCODE         24
#define KEP_STATUS_SWID(x)          ((x >> _KEP_STATUS_SWID) & 0xFF)
#define KEP_STATUS_RETCODE(x)       ((x >> _KEP_STATUS_RETCODE) & 0x03)

#endif
