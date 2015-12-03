/* coap_time.h -- Clock Handling
 *
 * Copyright (C) 2010,2011 Olaf Bergmann <bergmann@tzi.org>
 *
 * This file is part of the CoAP library libcoap. Please see
 * README for terms of use. 
 */

/** 
 * @file coap_time.h
 * @brief Clock Handling
 */

#ifndef _COAP_TIME_H_
#define _COAP_TIME_H_

#include "modules/coap/libcoap-4.0.1/config.h"
#include <gsn_includes.h> 	/* GainSpan Modified */

/**
 * @defgroup clock Clock Handling
 * Default implementation of internal clock. You should redefine this if
 * you do not have time() and gettimeofday().
 * @{
 */
//typedef ULONG64 GSN_SYSTEM_TIME_T; 
#ifdef WITH_CONTIKI
#include "clock.h"

typedef clock_time_t coap_tick_t;

#define COAP_TICKS_PER_SECOND CLOCK_SECOND

/** Set at startup to initialize the internal clock (time in seconds). */
//extern clock_time_t clock_offset; 	/* GainSpan Modified */
extern GSN_SYSTEM_TIME_T clock_offset;

static inline void
contiki_clock_init_impl(void) {
  clock_init();
  //clock_offset = clock_time(); 	/* GainSpan Modified */
  clock_offset = GsnSoftTmr_CurrentSystemTime();
}

#define coap_clock_init contiki_clock_init_impl

static inline void
contiki_ticks_impl(coap_tick_t *t) {
  //*t = clock_time(); 	/* GainSpan Modified */
  *t = GsnSoftTmr_CurrentSystemTime();
}

#define coap_ticks contiki_ticks_impl

#else /* WITH_CONTIKI */
typedef unsigned long long coap_tick_t; 	/* GainSpan Modified */



#define COAP_TICKS_PER_SECOND TIMER_CLOCK 	/* GainSpan Modified */

/** Set at startup to initialize the internal clock (time in seconds). */
//extern time_t clock_offset; 	/* GainSpan Modified */
extern GSN_SYSTEM_TIME_T  clock_offset;
#endif

#ifndef coap_clock_init
static inline void
coap_clock_init_impl(void) {
#ifdef HAVE_TIME_H
	clock_offset = 0; 	/* GainSpan Modified */
	clock_offset = GsnSoftTmr_CurrentSystemTime();

    printf("coap_clock_init_impl clock_offset = %llu\r\n",clock_offset);
#else
#warn "cannot initialize clock"
  clock_offset = 0;
#endif
}
#define coap_clock_init coap_clock_init_impl
#endif /* coap_clock_init */

#ifndef coap_ticks
static inline void
coap_ticks_impl(coap_tick_t *t) {
#ifdef HAVE_SYS_TIME_H
  //struct timeval tv; 	/* GainSpan Modified */
  //gettimeofday(&tv, NULL);
  //*t = (tv.tv_sec - clock_offset) * COAP_TICKS_PER_SECOND
    //+ (tv.tv_usec * COAP_TICKS_PER_SECOND / 1000000);
	GSN_SYSTEM_TIME_T currentTime = GsnSoftTmr_CurrentSystemTime(); 	/* GainSpan Modified */
  *t = currentTime - clock_offset;
#else
#warning "clock not implemented"
#endif
}
#define coap_ticks coap_ticks_impl
#endif /* coap_ticks */

/** @} */

#endif /* _COAP_TIME_H_ */
