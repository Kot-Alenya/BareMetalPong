#ifndef _SimpleAllocator_h
#define _SimpleAllocator_h

#include <stdint.h>

extern void* simple_allocator_allocate_advanced(uint32_t byte_size, uint32_t is_aligned, uint32_t* physical_addr);
extern void* simple_allocator_allocate(uint32_t byte_size);
extern void* simple_allocator_get_next_placement_address();

#endif