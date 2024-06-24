#ifndef _heap_list_h
#define _heap_list_h

#include <stdint.h>
#include "Heap.h"

void heap_list_add_chunk(heap_chunk_t* chunk);
heap_chunk_t* heap_list_find_chunk(uint32_t size, uint32_t is_allocated_chunk, uint32_t is_aligned);
void heap_list_remove_chunk(heap_chunk_t* chunk);
void heap_list_write_elements();

#endif