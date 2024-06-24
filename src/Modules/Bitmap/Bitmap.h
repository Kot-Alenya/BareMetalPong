#ifndef _Bitmap_h
#define _Bitmap_h

#include <stdint.h>

extern uint32_t bitmap_get_index(uint32_t value);
extern uint32_t bitmap_get_offset(uint32_t value);
extern void bitmap_set(uint32_t* bitmap, uint32_t number);
extern void bitmap_clear(uint32_t* bitmap, uint32_t number);
extern uint32_t bitmap_test(uint32_t* bitmap, uint32_t number);
uint32_t calculate_byte_size(uint32_t elements_count);

#endif