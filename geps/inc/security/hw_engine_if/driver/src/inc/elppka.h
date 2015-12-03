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

#ifndef ELPPKA_H_
#define ELPPKA_H_

#include "security/hw_engine_if/driver/src/inc/elppdu.h"

#define PKA_PMULT 		0x9 	/* Elliptic Curve Point Multiplication				*/            
#define PKA_PDBL 		0xB 	/* Elliptic Curve Point Double                      */    
#define PKA_PADD 		0xF 	/* Elliptic Curve Point Addition                    */    
#define PKA_PVER 		0x13 	/* Elliptic Curve Point Verification                */    
#define PKA_MODEXP 		0x17 	/* Modular Exponentiation				x^y mod m   */     
#define PKA_RESIDUE 	0x19 	/* Modular Residue (Montgomery conversion)          */    
#define PKA_MODMULT 	0x1D 	/* Modular Multiplication				x * y mod m */     
#define PKA_MODDIV		0x23	/* Modular division				y / x mod m         */ 
#define PKA_MODADD 		0x1F 	/* Modular Addition				x + y mod m         */ 
#define PKA_MODSUB 		0x21	/* Modular Subtraction				x - y mod m     */    
#define PKA_MODINV 		0x25	/* Modular Inversion				1 / x mod m     */     
#define PKA_REDUCE 		0x27	/* Modular Reduction				x mod m         */     
#define PKA_CALC_MP 	0x29	/* Montgomery m' Precalculation                     */    
#define PKA_CALC_R_INV 	0x2B	/* Montgomery r-1 mod m Precalculation              */    
#define PKA_CALC_R_SQR 	0x2D	/* Montgomery r2 mod m Precalculation               */    

enum {
   PKA_OPERAND_A,
   PKA_OPERAND_B,
   PKA_OPERAND_C,
   PKA_OPERAND_D,
   PKA_OPERAND_MAX
};

void elppka_init( uint32_t *regs );
int elppka_start(uint32_t *regs, uint32_t entry, unsigned size);
void elppka_abort(uint32_t *regs);
int elppka_get_status(uint32_t *regs, unsigned *code);

int elppka_load_operand(uint32_t *regs, unsigned bank, unsigned index,
                                        unsigned size, const uint8_t *data);
int elppka_unload_operand(uint32_t *regs, unsigned bank, unsigned index,
                                          unsigned size, uint8_t *data);
int elppka_copy_operand(uint32_t *regs, unsigned srcBank, unsigned srcIndex,
    unsigned dstBank, unsigned dstIndex, unsigned size );

int elppka_set_mod(uint32_t *regs, unsigned bank, unsigned index,
                                        unsigned size );

void elppka_fw_size(uint32_t *regs, unsigned *ramsize, unsigned *romsize);

void elppka_set_byteswap(uint32_t *regs, int swap);

#endif
