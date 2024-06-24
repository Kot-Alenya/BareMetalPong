#ifndef _MyMemory_h
#define _MyMemory_h

#include <stdint.h>
#include "multiboot.h"

extern void memory_set(void *dest, uint8_t value, uint32_t byte_length);
extern void memory_copy(void *dest, void *src, uint32_t byte_length);
extern uint32_t memory_compare(void *src1, void *src2, uint32_t length);

extern void* memory_get_next_placement_address();
extern void* memory_allocate_advanced(uint32_t byte_size, uint32_t is_aligned, void *physical_addr);
extern void* memory_allocate(uint32_t byte_size);
extern void memory_free(void *data);
extern void memory_initialize(multiboot_info_t* multiboot_info);

extern void memory_write_multiboot_info();

#endif