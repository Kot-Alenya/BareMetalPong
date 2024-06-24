#ifndef _heap_h
#define _heap_h

#include <stdint.h>

#define GET_CHUNK_SIZE(chunk) (chunk->size << 1)
#define SET_CHUNK_SIZE(chunk, size) (chunk->size = size >> 1)

typedef struct heap_chunk heap_chunk_t;
struct heap_chunk
{
    uint32_t is_allocated : 1;
    uint32_t size : 31;
    heap_chunk_t *previous_chunk;
    heap_chunk_t *next_chunk;
};

extern const uint32_t CHUNK_MINIMUM_BYTE_SIZE;

extern void heap_initialize();
extern void* heap_allocate_advanced(uint32_t byte_size, uint32_t is_aligned, uint32_t* physical_addr);
extern void* heap_allocate(uint32_t byte_size);
extern void heap_free(void *data);

#endif