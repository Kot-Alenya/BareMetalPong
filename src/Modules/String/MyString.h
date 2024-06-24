#ifndef _String_h
#define _String_h

#include <stdint.h>

extern uint32_t string_from_uint32(char *dest, uint32_t value, uint32_t is_set_end);
extern uint32_t string_from_uint32_hex(char *dest, uint32_t value, uint32_t is_set_end);
extern uint32_t string_from_uint32_bin(char *dest, uint32_t value, uint32_t is_set_end);
extern uint32_t string_from_int32(char *dest, int32_t value, uint32_t is_set_end);
extern uint32_t string_from_float(char *dest, float value, uint32_t is_set_end);
extern uint32_t string_build(char* dest, uint32_t is_set_end, char* format, ...);

#endif