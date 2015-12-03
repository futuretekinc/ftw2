#ifndef ELPPKA_HW_H_
#define ELPPKA_HW_H_

/* Control/status registers */
enum {
   PKA_CTRL = 0,
   PKA_ENTRY,
   PKA_RC,
   PKA_BUILD_CONF,
   PKA_F_STACK,
   PKA_INST_SINCE_GO,
   PKA_P_STACK,
   PKA_CONF,
   PKA_STATUS,
   PKA_FLAGS,
   PKA_WATCHDOG,
   PKA_CYCLES_SINCE_GO,
   PKA_INDEX_I,
   PKA_INDEX_J,
   PKA_INDEX_K,
   PKA_INDEX_L,
   PKA_IRQ_EN,
   PKA_JUMP_PROB,
   PKA_LFSR_SEED,

   PKA_BANK_SWITCH_A = 20,
   PKA_BANK_SWITCH_B,
   PKA_BANK_SWITCH_C,
   PKA_BANK_SWITCH_D,

   PKA_OPERAND_A_BASE = 0x100,
   PKA_OPERAND_B_BASE = 0x200,
   PKA_OPERAND_C_BASE = 0x300,
   PKA_OPERAND_D_BASE = 0x400,

   PKA_FIRMWARE_BASE = 0x800
};

#define PKA_MAX_OPERAND_SIZE  512 /* 4096 bits */
#define PKA_OPERAND_BANK_SIZE 0x400

#define PKA_CTRL_PARTIAL_RADIX  0
#define PKA_CTRL_BASE_RADIX     8
#define PKA_CTRL_M521_MODE     16
#define PKA_CTRL_STOP_RQST     27
#define PKA_CTRL_GO            31

#define PKA_RC_BUSY          31
#define PKA_RC_IRQ           30
#define PKA_RC_WR_PENDING    29
#define PKA_RC_ZERO          28
#define PKA_RC_REASON        16
#define PKA_RC_REASON_BITS    8

#define PKA_BC_FW_RAM_SZ       8
#define PKA_BC_FW_RAM_SZ_BITS  2
#define PKA_BC_FW_ROM_SZ      10
#define PKA_BC_FW_ROM_SZ_BITS  2
#define PKA_BC_FW_HAS_RAM     12
#define PKA_BC_FW_HAS_ROM     13

/* Enumerations for the FW_RAM and FW_ROM fields */
enum {
   PKA_FW_SZ_256,
   PKA_FW_SZ_512,
   PKA_FW_SZ_1024,
   PKA_FW_SZ_2048,
};

#define PKA_STAT_IRQ 30

#define PKA_IRQ_EN_STAT 30

#define PKA_FLAG_ZERO   0
#define PKA_FLAG_MEMBIT 1
#define PKA_FLAG_BORROW 2
#define PKA_FLAG_CARRY  3
#define PKA_FLAG_F0     4
#define PKA_FLAG_F1     5
#define PKA_FLAG_F2     6
#define PKA_FLAG_F3     7

#define PKA_CONF_BYTESWAP 26

#endif
