/******************************************************************************
 *
 *               COPYRIGHT (c) 2006-2010 GainSpan Corporation
 *                         All Rights Reserved
 *
 * The source code contained or described herein and all documents
 * related to the source code ("Material") are owned by Gainspan
 * Corporation or its licensors.  Title to the Material remains
 * with Gainspan Corporation or its suppliers and licensors.
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
 * Unless otherwise agreed by Gainspan in writing, you may not remove or
 * alter this notice or any other notice embedded in Materials by Gainspan
 * or Gainspan's suppliers or licensors in any way.
 *
 * $RCSfile: gsn_reg_op.h,v $
 *
 *
 * Description:
 * Common macro definitions for bit field support. The macros are introduced to get rid 
 * of read-modify-write accesses and to avoid tool dependent usage of C constructs (bit 
 * field structs).
 * The macros require another 3 predefined macros per bitfield which describe the 
 * bitfield layout: 
 * <PERIPHERAL>_<BITFIELD>_OFFSET_ADDRESS
 * <PERIPHERAL>_<BITFIELD>_BIT_OFFSET
 * <PERIPHERAL>_<BITFIELD>_BITFIELD_SIZE
 * These predefined macros together with get- or set-macros then allow straight forward, 
 * object oriented, peripheral specific macro definitions with encapsulated access type.
 * Example: 
 * #define RER1_BF1_OFFSET_ADDRESS       4
 * #define RER1_BF1_OFFSET_BIT_OFFSET    1
 * #define RER1_BF1_OFFSET_BITFIELD_SIZE 1
 * #define RER1_BF2_OFFSET_ADDRESS       4
 * #define RER1_BF2_OFFSET_BIT_OFFSET    2
 * #define RER1_BF2_OFFSET_BITFIELD_SIZE 4
 * #define RER1_BF1_SET(moduleBaseAddress, value) \
 *             SET8_BITFIELD_N(moduleBaseAddress, PER1_BF1, value)
 * Note: Bitfields which are alone within their container (byte, halfword or word) should 
 * use a BITFIELD_SIZE equal to the container size to allow automatic compiler 
 * optimisation.
 *
 *****************************************************************************************
 */
#ifndef _REG_H_
#define _REG_H_

/*
 * Includes on which the header file depends.
 *****************************************************************************************
 */
#include <stdint.h>

/*
 * General macro definitions. 
 * Type definition with macro is not allowed, constants should be defined as const 
 * variables or as enumerations and function type macros are defined in the "Function 
 * definitions" section.
 *****************************************************************************************
 */
/* Bit offset relative to the byte aligned bit field address. */
#define BIT_OFFSET(bitfieldName)  (bitfieldName ## _BITOFFSET % 8)
/* Byte offset relative to the given bit field offset addres. 
 * 8 * BYTE_OFFSET(bitfieldName) + BIT_OFFSET(bitfieldName) = BIT_OFFSET_ ## bitfieldName */
#define BYTE_OFFSET(bitfieldName) (bitfieldName ## _BITOFFSET / 8)

/* Byte aligned bit field offset address. */
#define BYTE_OFFSET_ADDRESS(bitfieldName) (bitfieldName ## _OFFSETADDRESS + BYTE_OFFSET(bitfieldName))
/* Halfword aligned bit field offset address. */
#define HALFWORD_OFFSET_ADDRESS(bitfieldName) (BYTE_OFFSET_ADDRESS(bitfieldName) & ~0x01)
/* Word aligned bit field offset address. */
#define WORD_OFFSET_ADDRESS(bitfieldName) (BYTE_OFFSET_ADDRESS(bitfieldName) & ~0x03)

/* Bit offset for the byte aligned bit field offset address. */
#define BYTE_BIT_OFFSET(bitfieldName) \
            (BIT_OFFSET(bitfieldName) + (8 * (BYTE_OFFSET_ADDRESS(bitfieldName) & 0x00)))
/* Bit offset for the halfword aligned bit field offset address. */
#define HALFWORD_BIT_OFFSET(bitfieldName) \
            (BIT_OFFSET(bitfieldName) + (8 * (BYTE_OFFSET_ADDRESS(bitfieldName) & 0x01)))
/* Bit offset for the word aligned bit field offset address. */
#define WORD_BIT_OFFSET(bitfieldName) \
            (BIT_OFFSET(bitfieldName) + (8 * (BYTE_OFFSET_ADDRESS(bitfieldName) & 0x03)))

/* Value conversion from a plain value to the correctly bit aligned byte value. (DeNormalisation) */
#define BYTE_VALUE_DN(bitfieldName, value)     (((UINT8)  value) << BYTE_BIT_OFFSET(bitfieldName))
/* Value conversion from a plain value to the correctly bit aligned halfword value. (DeNormalisation) */
#define HALFWORD_VALUE_DN(bitfieldName, value) (((UINT16) value) << HALFWORD_BIT_OFFSET(bitfieldName))
/* Value conversion from a plain value to the correctly bit aligned word value. (DeNormalisation) */
#define WORD_VALUE_DN(bitfieldName, value)     (((UINT32)  value) << WORD_BIT_OFFSET(bitfieldName))

/* Normalized bit field mask. */
#define MASK(bitfieldName)          (bitfieldName ## _BITFIELDSIZE == 32 ? ~0 : (((UINT32) 1) << bitfieldName ## _BITFIELDSIZE) - 1)
/* Bitfield mask used with byte accesses. (denormalized) */
#define BYTE_MASK(bitfieldName)     BYTE_VALUE_DN(bitfieldName, MASK(bitfieldName))
/* Bitfield mask used with halfword accesses. (denormalized) */
#define HALFWORD_MASK(bitfieldName) HALFWORD_VALUE_DN(bitfieldName, MASK(bitfieldName))
/* Bitfield mask used with word accesses. (denormalized) */
#define WORD_MASK(bitfieldName)     WORD_VALUE_DN(bitfieldName, MASK(bitfieldName))

/* Masked bitfield value used in conjunction with byte accesses. */
#define BYTE_VALUE(bitfieldName, value)     (((UINT8)  value) & BYTE_MASK(bitfieldName))
/* Masked bitfield value used in conjunction with halfword accesses. */
#define HALFWORD_VALUE(bitfieldName, value) (((UINT16) value) & HALFWORD_MASK(bitfieldName))
/* Masked bitfield value used in conjunction with word accesses. */
#define WORD_VALUE(bitfieldName, value)     (((UINT32)  value) & WORD_MASK(bitfieldName))

/* Normalized and masked bitfield value used in conjunction with byte accesses. */
#define BYTE_VALUE_N(bitfieldName, value)     (BYTE_VALUE(bitfieldName, value) >> BYTE_BIT_OFFSET(bitfieldName))
/* Normalized and masked bitfield value used in conjunction with halfword accesses. */
#define HALFWORD_VALUE_N(bitfieldName, value) (HALFWORD_VALUE(bitfieldName, value) >> HALFWORD_BIT_OFFSET(bitfieldName))
/* Normalized and masked bitfield value used in conjunction with word accesses. */
#define WORD_VALUE_N(bitfieldName, value)     (WORD_VALUE(bitfieldName, value) >> WORD_BIT_OFFSET(bitfieldName))

/*
 * Type definitions.
 *****************************************************************************************
 */

/*
 * Constant definitions.
 *****************************************************************************************
 */

/*
 * Global data declarations.
 *****************************************************************************************
 */

/*
 * Function declarations.
 *****************************************************************************************
 */

/*
 * Function definitions.
 * Note, inline specifiers are not defined in ANSI C 1989 and are therefore tool chain 
 * dependent. Furthermore, inline specifiers are only recommendations to compilers 
 * whereas local functions might be inlined by good compilers without inline specifier.
 *****************************************************************************************
 */
/* Assign a correctly bit aligned value to a bitfield within a byte. */
#define SET_BYTE_BITFIELD(moduleBaseAddress, bitfieldName, value) \
            *((volatile UINT8*) (((UINT8*) moduleBaseAddress) + BYTE_OFFSET_ADDRESS(bitfieldName))) = \
                (*((volatile UINT8*) (((UINT8*) moduleBaseAddress) + BYTE_OFFSET_ADDRESS(bitfieldName))) & ~BYTE_MASK(bitfieldName)) | \
                ((value) & BYTE_MASK(bitfieldName))
/* Assign an unaligned value to a bitfield within a byte. */
#define SET_BYTE_BITFIELD_N(moduleBaseAddress, bitfieldName, value) \
            *((volatile UINT8*) (((UINT8*) moduleBaseAddress) + BYTE_OFFSET_ADDRESS(bitfieldName))) = \
                (*((volatile UINT8*) (((UINT8*) moduleBaseAddress) + BYTE_OFFSET_ADDRESS(bitfieldName))) & ~BYTE_MASK(bitfieldName)) | \
                (BYTE_VALUE_DN(bitfieldName, value) & BYTE_MASK(bitfieldName))
/* Retrieve the bit aligned value of a bitfield within a byte. */
#define GET_BYTE_BITFIELD(moduleBaseAddress, bitfieldName) \
            ((*((volatile UINT8*) (((UINT8*) moduleBaseAddress) + BYTE_OFFSET_ADDRESS(bitfieldName)))) & BYTE_MASK(bitfieldName))
/* Retrieve the normalized value of a bitfield within a byte. */
#define GET_BYTE_BITFIELD_N(moduleBaseAddress, bitfieldName) \
            (BYTE_VALUE_N(bitfieldName, GET_BYTE_BITFIELD(moduleBaseAddress, bitfieldName)))

/* Assign a correctly bit aligned value to a bitfield that is the only bitfield within a byte. */
#define SET_BYTE_EXCLUSIVE_BITFIELD(moduleBaseAddress, bitfieldName, value) \
            *((volatile UINT8*) ((UINT8*) moduleBaseAddress + BYTE_OFFSET_ADDRESS(bitfieldName))) = value
/* Assign an unaligned value to a bitfield that is the only bitfield within a byte. */
#define SET_BYTE_EXCLUSIVE_BITFIELD_N(moduleBaseAddress, bitfieldName, value) \
            *((volatile UINT8*) ((UINT8*) moduleBaseAddress + BYTE_OFFSET_ADDRESS(bitfieldName))) = BYTE_VALUE_DN(bitfieldName, value)
/* Retrieve the bit aligned value of a bitfield that is the only bitfield within a byte. */
#define GET_BYTE_EXCLUSIVE_BITFIELD(moduleBaseAddress, bitfieldName) \
            (*((volatile UINT8*) ((UINT8*) moduleBaseAddress + BYTE_OFFSET_ADDRESS(bitfieldName))))
/* Retrieve the normalized value of a bitfield that is the only bitfield within a byte. */
#define GET_BYTE_EXCLUSIVE_BITFIELD_N(moduleBaseAddress, bitfieldName) \
            (BYTE_VALUE_N(bitfieldName, GET_BYTE_EXCLUSIVE_BITFIELD(moduleBaseAddress, bitfieldName)))

/* Assign a correctly bit aligned value to a bitfield within a halfword. */
#define SET_HALFWORD_BITFIELD(moduleBaseAddress, bitfieldName, value) \
            *((volatile UINT16*) (((UINT8*) moduleBaseAddress) + HALFWORD_OFFSET_ADDRESS(bitfieldName))) = \
                (*((volatile UINT16*) (((UINT8*) moduleBaseAddress) + HALFWORD_OFFSET_ADDRESS(bitfieldName))) & ~HALFWORD_MASK(bitfieldName)) | \
                ((value) & HALFWORD_MASK(bitfieldName))
/* Assign an unaligned value to a bitfield within a halfword. */
#define SET_HALFWORD_BITFIELD_N(moduleBaseAddress, bitfieldName, value) \
            *((volatile UINT16*) (((UINT8*) moduleBaseAddress) + HALFWORD_OFFSET_ADDRESS(bitfieldName))) = \
                (*((volatile UINT16*) (((UINT8*) moduleBaseAddress) + HALFWORD_OFFSET_ADDRESS(bitfieldName))) & ~HALFWORD_MASK(bitfieldName)) | \
                (HALFWORD_VALUE_DN(bitfieldName, value) & HALFWORD_MASK(bitfieldName))
/* Retrieve the bit aligned value of a bitfield within a halfword. */
#define GET_HALFWORD_BITFIELD(moduleBaseAddress, bitfieldName) \
            ((*((volatile UINT16*) (((UINT8*) moduleBaseAddress) + HALFWORD_OFFSET_ADDRESS(bitfieldName)))) & HALFWORD_MASK(bitfieldName))
/* Retrieve the normalized value of a bitfield within a halfword. */
#define GET_HALFWORD_BITFIELD_N(moduleBaseAddress, bitfieldName) \
            (HALFWORD_VALUE_N(bitfieldName, GET_HALFWORD_BITFIELD(moduleBaseAddress, bitfieldName)))

/* Assign a correctly bit aligned value to a bitfield that is the only bitfield within a halfword. */
#define SET_HALFWORD_EXCLUSIVE_BITFIELD(moduleBaseAddress, bitfieldName, value) \
            *((volatile UINT16*) ((UINT8*) moduleBaseAddress + HALFWORD_OFFSET_ADDRESS(bitfieldName))) = value
/* Assign an unaligned value to a bitfield that is the only bitfield within a halfword. */
#define SET_HALFWORD_EXCLUSIVE_BITFIELD_N(moduleBaseAddress, bitfieldName, value) \
            *((volatile UINT16*) ((UINT8*) moduleBaseAddress + HALFWORD_OFFSET_ADDRESS(bitfieldName))) = HALFWORD_VALUE_DN(bitfieldName, value)
/* Retrieve the bit aligned value of a bitfield that is the only bitfield within a halfword. */
#define GET_HALFWORD_EXCLUSIVE_BITFIELD(moduleBaseAddress, bitfieldName) \
            (*((volatile UINT16*) ((UINT8*) moduleBaseAddress + HALFWORD_OFFSET_ADDRESS(bitfieldName))))
/* Retrieve the normalized value of a bitfield that is the only bitfield within a halfword. */
#define GET_HALFWORD_EXCLUSIVE_BITFIELD_N(moduleBaseAddress, bitfieldName) \
            (HALFWORD_VALUE_N(bitfieldName, GET_HALFWORD_EXCLUSIVE_BITFIELD(moduleBaseAddress, bitfieldName)))

/* Assign a correctly bit aligned value to a bitfield within a word. */
#define SET_WORD_BITFIELD(moduleBaseAddress, bitfieldName, value) \
            *((volatile UINT32*) (((UINT8*) moduleBaseAddress) + WORD_OFFSET_ADDRESS(bitfieldName))) = \
                (*((volatile UINT32*) (((UINT8*) moduleBaseAddress) + WORD_OFFSET_ADDRESS(bitfieldName))) & ~WORD_MASK(bitfieldName)) | \
                ((value) & WORD_MASK(bitfieldName))
/* Assign an unaligned value to a bitfield within a word. */
#define SET_WORD_BITFIELD_N(moduleBaseAddress, bitfieldName, value) \
            *((volatile UINT32*) (((UINT8*) moduleBaseAddress) + WORD_OFFSET_ADDRESS(bitfieldName))) = \
                (*((volatile UINT32*) (((UINT8*) moduleBaseAddress) + WORD_OFFSET_ADDRESS(bitfieldName))) & ~WORD_MASK(bitfieldName)) | \
                (WORD_VALUE_DN(bitfieldName, value) & WORD_MASK(bitfieldName))
/* Retrieve the bit aligned value of a bitfield within a word. */
#define GET_WORD_BITFIELD(moduleBaseAddress, bitfieldName) \
            ((*((volatile UINT32*) (((UINT8*) moduleBaseAddress) + WORD_OFFSET_ADDRESS(bitfieldName)))) & WORD_MASK(bitfieldName))
/* Retrieve the normalized value of a bitfield within a word. */
#define GET_WORD_BITFIELD_N(moduleBaseAddress, bitfieldName) \
            (WORD_VALUE_N(bitfieldName, GET_WORD_BITFIELD(moduleBaseAddress, bitfieldName)))

/* Assign a correctly bit aligned value to a bitfield that is the only bitfield within a word. */
#define SET_WORD_EXCLUSIVE_BITFIELD(moduleBaseAddress, bitfieldName, value) \
            *((volatile UINT32*) ((UINT8*) moduleBaseAddress + WORD_OFFSET_ADDRESS(bitfieldName))) = value
/* Assign an unaligned value to a bitfield that is the only bitfield within a word. */
#define SET_WORD_EXCLUSIVE_BITFIELD_N(moduleBaseAddress, bitfieldName, value) \
            *((volatile UINT32*) ((UINT8*) moduleBaseAddress + WORD_OFFSET_ADDRESS(bitfieldName))) = WORD_VALUE_DN(bitfieldName, value)
/* Retrieve the bit aligned value of a bitfield that is the only bitfield within a word. */
#define GET_WORD_EXCLUSIVE_BITFIELD(moduleBaseAddress, bitfieldName) \
            (*((volatile UINT32*) ((UINT8*) moduleBaseAddress + WORD_OFFSET_ADDRESS(bitfieldName))))
/* Retrieve the normalized value of a bitfield that is the only bitfield within a word. */
#define GET_WORD_EXCLUSIVE_BITFIELD_N(moduleBaseAddress, bitfieldName) \
            (WORD_VALUE_N(bitfieldName, GET_WORD_EXCLUSIVE_BITFIELD(moduleBaseAddress, bitfieldName)))

#endif /* _REG_H_ */
