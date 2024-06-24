#ifndef _Timer_h
#define _Timer_h

#include <stdint.h>

typedef void (*timer_callback_t) ();

extern void timer_initialize(uint32_t frequency_ms, timer_callback_t);
extern void timer_dispose();

#endif