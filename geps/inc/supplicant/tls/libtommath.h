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
 * $RCSfile: libtommath.h,v $
 *
 * Project: GSN APP Software
 *
 * Description : Functions from libtommath 
 *
 */

/*
 * Minimal code for RSA support from LibTomMath 0.3.9
 * http://math.libtomcrypt.com/
 * http://math.libtomcrypt.com/files/ltm-0.39.tar.bz2
 * This library was released in public domain by Tom St Denis.
 *
 * The combination in this file is not using many of the optimized algorithms
 * (e.g., Montgomery reduction) and is considerable slower than the LibTomMath
 * with its default of SC_RSA_1 settins. The main purpose of having this
 * version here is to make it easier to build bignum.c wrapper without having
 * to install and build an external library. However, it is likely worth the
 * effort to use the full library with SC_RSA_1 instead of this minimized copy.
 * Including the optimized algorithms may increase the size requirements by
 * 15 kB or so (measured with x86 build).
 *
 * If CONFIG_INTERNAL_LIBTOMMATH is defined, bignum.c includes this
 * libtommath.c file instead of using the external LibTomMath library.
 */

#ifndef LIBTOMATH_H
#define LIBTOMATH_H

#ifndef CHAR_BIT
#define CHAR_BIT 8
#endif

#define BN_MP_INVMOD_C
#define BN_S_MP_EXPTMOD_C /* Note: #undef in tommath_superclass.h; this would
			   * require BN_MP_EXPTMOD_FAST_C instead */
#define BN_S_MP_MUL_DIGS_C
//#define BN_MP_INVMOD_SLOW_C
#define BN_S_MP_SQR_C
//#define BN_S_MP_MUL_HIGH_DIGS_C /* Note: #undef in tommath_superclass.h; this
//				 * would require other than mp_reduce */

				 /* RAM */
#define BN_MP_MONTGOMERY_SETUP_C
#define BN_MP_EXPTMOD_FAST_C
#define BN_MP_MONTGOMERY_REDUCE_C
#define BN_MP_REDUCE_2K_SETUP_C
#define BN_MP_REDUCE_2K_C
#define BN_MP_MONTGOMERY_CALC_NORMALIZATION_C
#define BN_FAST_MP_MONTGOMERY_REDUCE_C
#define BN_MP_REDUCE_IS_2K_L_C
#define BN_MP_REDUCE_2K_L_C
#define BN_MP_DR_IS_MODULUS_C
#define BN_MP_REDUCE_IS_2K_C
#define BN_FAST_S_MP_MUL_DIGS_C
#define BN_FAST_S_MP_SQR_C
#define BN_FAST_S_MP_MUL_HIGH_DIGS_C
#define BN_FAST_MP_INVMOD_C

/* from tommath.h */

#ifndef MIN
   #define MIN(x,y) ((x)<(y)?(x):(y))
#endif

#ifndef MAX
   #define MAX(x,y) ((x)>(y)?(x):(y))
#endif

#define  OPT_CAST(x)

//typedef unsigned long mp_digit;
//typedef u64 mp_word;
#define mp_digit   unsigned long
#define mp_word unsigned long long


#define DIGIT_BIT          28
//#define DIGIT_BIT          14
#define MP_28BIT


#define XMALLOC  os_malloc
#define XFREE    os_free
#define XREALLOC os_realloc


#define MP_MASK          ((((mp_digit)1)<<((mp_digit)DIGIT_BIT))-((mp_digit)1))

#define MP_LT        -1   /* less than */
#define MP_EQ         0   /* equal to */
#define MP_GT         1   /* greater than */

#define MP_ZPOS       0   /* positive integer */
#define MP_NEG        1   /* negative */

#define MP_OKAY       0   /* ok result */
#define MP_MEM        -2  /* out of mem */
#define MP_VAL        -3  /* invalid input */

#define MP_YES        1   /* yes response */
#define MP_NO         0   /* no response */

typedef int           mp_err;

/* define this to use lower memory usage routines (exptmods mostly) */
#define MP_LOW_MEM

/* default precision */
#ifndef MP_PREC
   #ifndef MP_LOW_MEM
      #define MP_PREC                 32     /* default digits of precision */
   #else
      #define MP_PREC                 8      /* default digits of precision */
   #endif   
#endif

/* size of comba arrays, should be at least 2 * 2**(BITS_PER_WORD - BITS_PER_DIGIT*2) */
#define MP_WARRAY               (((u32)1) << (sizeof(mp_word) * CHAR_BIT - 2 * DIGIT_BIT + 1))

/* the infamous mp_int structure */
typedef struct  {
    int used, alloc, sign;
    mp_digit *dp;
} mp_int;

/*********************************
BELOW MACROS ARE FOR TESTING
*********************************/
/* Uncomment this to test how many times each APIs are called.
This is helpful to know which one to put in SRAM to execute faster 
User has to call void init_libmath_log() function to start the logging
and void print_libmath_log() function to print the information at the end
of the processing. 
The above API uses S2w_Printf for printing over uart
*/
//#define LIB_MATH_API_CALL_TEST

#define	MP_EXPT_D 0	
#define	FAST_S_MP_SQR	1
#define	FAST_MP_INVMOD	2
#define	FAST_S_MP_MUL_HIGH_DIGS	3
#define	MP_REDUCE_IS_2K_L	4
#define	MP_DR_IS_MODULUS	5
#define	MP_REDUCE_IS_2K	6
#define	FAST_MP_MONTGOMERY_REDUCE	7
#define	MP_MUL_2	8
#define	MP_MONTGOMERY_CALC_NORMALIZATION	9
#define	MP_REDUCE_2K_SETUP	10
#define	MP_MONTGOMERY_SETUP	11
#define	MP_MUL_D	12
#define	MP_REDUCE_2K	13
#define	MP_MONTGOMERY_REDUCE	14
#define	MP_EXPTMOD_FAST	15
#define	BN_REVERSE	16
#define	S_MP_ADD	17
#define	S_MP_SUB	18
#define	MP_INIT	19
#define	MP_CLEAR	20
#define	MP_ADD	21
#define	MP_SUB	22
#define	MP_MUL	23
#define	MP_MULMOD	24
#define	MP_MOD	25
#define	MP_EXPTMOD	26
#define	MP_CMP	27
#define	MP_CMP_D	28
#define	MP_INVMOD	29
#define	MP_UNSIGNED_BIN_SIZE	30
#define	MP_INVMOD_SLOW	31
#define	MP_CMP_MAG	32
#define	MP_READ_UNSIGNED_BIN	33
#define	MP_TO_UNSIGNED_BIN	34
#define	MP_DIV_2D	35
#define	MP_INIT_COPY	36
#define	MP_ZERO	37
#define	MP_COPY	38
#define	MP_RSHD	39
#define	MP_EXCH	40
#define	MP_CLAMP	41
#define	MP_GROW	42
#define	MP_ABS	43
#define	MP_SET	44
#define	MP_DIV_2	45
#define	MP_MUL_2D	46
#define	MP_INIT_MULTI	47
#define	MP_CLEAR_MULTI	48
#define	MP_LSHD	49
#define	MP_COUNT_BITS	50
#define	MP_MOD_2D	51
#define	MP_DIV	52
#define	S_MP_EXPTMOD	53
#define	MP_SQR	54
#define	MP_REDUCE_2K_L	55
#define	MP_REDUCE_2K_SETUP_L	56
#define	MP_2EXPT	57
#define	MP_REDUCE_SETUP	58
#define	MP_REDUCE	59
#define	S_MP_MUL_DIGS	60
#define	FAST_S_MP_MUL_DIGS	61
#define	MP_INIT_SIZE	62
#define	S_MP_SQR	63
#define	S_MP_MUL_HIGH_DIGS	64
#define	MAX_LIB_APIS	65

#ifdef LIB_MATH_API_CALL_TEST
extern UINT16 libNumApiCall[MAX_LIB_APIS];
#define LIB_API_LOG(id) libNumApiCall[id]++
#else
#define LIB_API_LOG(id)
#endif
/*********************************
ABOVE MACROS ARE FOR TESTING
*********************************/
/* ---> Basic Manipulations <--- */
#define mp_iszero(a) (((a)->used == 0) ? MP_YES : MP_NO)
#define mp_iseven(a) (((a)->used > 0 && (((a)->dp[0] & 1) == 0)) ? MP_YES : MP_NO)
#define mp_isodd(a)  (((a)->used > 0 && (((a)->dp[0] & 1) == 1)) ? MP_YES : MP_NO)


/* prototypes for copied functions */
#define s_mp_mul(a, b, c) s_mp_mul_digs(a, b, c, (a)->used + (b)->used + 1)
int s_mp_exptmod(mp_int * G, mp_int * X, mp_int * P, mp_int * Y, int redmode);

#ifdef OS_UVEL
#pragma ghs nothumb
#endif

int s_mp_mul_digs (mp_int * a, mp_int * b, mp_int * c, int digs);
int fast_s_mp_mul_digs (mp_int * a, mp_int * b, mp_int * c, int digs);
int s_mp_sqr(mp_int * a, mp_int * b);
void mp_clamp(mp_int * a);
#ifdef OS_UVEL
#pragma ghs thumb
#endif
int s_mp_mul_high_digs(mp_int * a, mp_int * b, mp_int * c, int digs);
int mp_init_multi(mp_int *mp, ...);
void mp_clear_multi(mp_int *mp, ...);
int mp_lshd(mp_int * a, int b);
void mp_set(mp_int * a, mp_digit b);
void mp_exch(mp_int * a, mp_int * b);
void mp_rshd(mp_int * a, int b);
void mp_zero(mp_int * a);
int mp_mod_2d(mp_int * a, int b, mp_int * c);
int mp_div_2d(mp_int * a, int b, mp_int * c, mp_int * d);
int mp_init_copy(mp_int * a, mp_int * b);
int mp_mul_2d(mp_int * a, int b, mp_int * c);
int mp_div_2(mp_int * a, mp_int * b);
int mp_copy(mp_int * a, mp_int * b);
int mp_count_bits(mp_int * a);
int mp_div(mp_int * a, mp_int * b, mp_int * c, mp_int * d);
int mp_mod(mp_int * a, mp_int * b, mp_int * c);
int mp_grow(mp_int * a, int size);
int mp_cmp_mag(mp_int * a, mp_int * b);
int mp_invmod(mp_int * a, mp_int * b, mp_int * c);
int mp_abs(mp_int * a, mp_int * b);
int mp_invmod_slow(mp_int * a, mp_int * b, mp_int * c);
int mp_sqr(mp_int * a, mp_int * b);
int mp_reduce_2k_l(mp_int *a, mp_int *n, mp_int *d);
int mp_reduce_2k_setup_l(mp_int *a, mp_int *d);
int mp_2expt(mp_int * a, int b);
int mp_reduce_setup(mp_int * a, mp_int * b);
int mp_reduce(mp_int * x, mp_int * m, mp_int * mu);
int mp_init_size(mp_int * a, int size);

int s_mp_add (mp_int * a, mp_int * b, mp_int * c);
int s_mp_sub (mp_int * a, mp_int * b, mp_int * c);
int mp_add (mp_int * a, mp_int * b, mp_int * c);
int mp_sub (mp_int * a, mp_int * b, mp_int * c);
int mp_mul (mp_int * a, mp_int * b, mp_int * c);
int mp_mulmod (mp_int * a, mp_int * b, mp_int * c, mp_int * d);
int mp_cmp (mp_int * a, mp_int * b);
int mp_cmp_d(mp_int * a, mp_digit b);
int mp_init (mp_int * a);
int mp_exptmod_fast (mp_int * G, mp_int * X, mp_int * P, mp_int * Y, int redmode);
void mp_clear (mp_int * a);

#ifdef OS_UVEL
#pragma ghs nothumb
#endif

int mp_montgomery_reduce (mp_int * x, mp_int * n, mp_digit rho);
int fast_mp_montgomery_reduce (mp_int * x, mp_int * n, mp_digit rho);

#ifdef OS_UVEL
#pragma ghs thumb
#endif


#endif /* LIBTOMATH_H */

