#include <stdint.h>
#include <stddef.h>
#include "Paging.h"
#include "HeapList.h"
#include "Heap.h"
#include "MyError.h"
#include "MyMemory.h"

const uint32_t CHUNK_MINIMUM_BYTE_SIZE = sizeof(heap_chunk_t);
static const uint32_t CHUNK_BYTE_ALIGNMENT = 2;

static uint32_t get_next_free_frames_count_and_set_them(page_directory_t *directory, uint32_t start_numer, uint32_t all_frames_count)
{
    uint32_t r = 0;
    for(uint32_t i = start_numer; i < all_frames_count; i++)
    {
        if(paging_test_frame(i))
            break;
        
        paging_set_page(directory, i, i, 1);
        r++;
    }

    return r;
}

static heap_chunk_t* create_new_chunk(uint32_t size, uint32_t addr)
{
    if(size < CHUNK_MINIMUM_BYTE_SIZE)
    {
        string_build(monitor_get_common_buffer(), 1, "create_new_chunk: chunk size is less than CHUNK_MINIMUM_BYTE_SIZE!");
        error_throw(monitor_get_common_buffer());
    }

    heap_chunk_t* new_chunk = (heap_chunk_t*)(addr); 
    memory_set(new_chunk, 0, sizeof(heap_chunk_t));

    SET_CHUNK_SIZE(new_chunk, size);

    heap_list_add_chunk(new_chunk);
    return new_chunk;
}

void heap_initialize()
{
	uint32_t all_frames_count = paging_get_frames_count(); 
    page_directory_t *directory = paging_get_directory();

    for(uint32_t i = 0; i < all_frames_count; i++ )
    {
        if(paging_test_frame(i))
            continue;
        
        uint32_t free_frames_count = get_next_free_frames_count_and_set_them(directory, i, all_frames_count);
        uint32_t chunk_size = free_frames_count * 0x1000;
        uint32_t chunk_addr = i * 0x1000;

        create_new_chunk(chunk_size, chunk_addr);

        i += free_frames_count;
    }
}

static void divide_chunk(heap_chunk_t* chunk, uint32_t size, heap_chunk_t** sized_chunk, heap_chunk_t** other_chunk)
{
    uint32_t free_chunk_space = GET_CHUNK_SIZE(chunk) - size;

    heap_list_remove_chunk(chunk);
    heap_chunk_t* s_chunk = create_new_chunk(size, (uint32_t)chunk);
    heap_chunk_t* o_chunk = create_new_chunk(free_chunk_space, (uint32_t)chunk + size);

    if(sized_chunk != NULL)
        *sized_chunk = s_chunk;
    if(other_chunk != NULL)
        *other_chunk = o_chunk;
}

static uint32_t get_aligned_size(uint32_t size)
{
    uint32_t b = 1 << CHUNK_BYTE_ALIGNMENT;
    return (size + b - 1) & ~(b - 1);
}

void* heap_allocate_advanced(uint32_t byte_size, uint32_t is_aligned, uint32_t* physical_addr)
{
    uint32_t size = byte_size + sizeof(heap_chunk_t);

    size = get_aligned_size(size);

    if(size < CHUNK_MINIMUM_BYTE_SIZE)
        size = CHUNK_MINIMUM_BYTE_SIZE;
    
    heap_chunk_t* chunk = heap_list_find_chunk(size, 0, is_aligned);

    if(is_aligned)
        divide_chunk(chunk, GET_CHUNK_SIZE(chunk) & 0x00000FFF, NULL, &chunk);
    
    if(GET_CHUNK_SIZE(chunk) - size >= CHUNK_MINIMUM_BYTE_SIZE)
        divide_chunk(chunk, size, &chunk, NULL);

    chunk->is_allocated = 1;
    
    uint32_t addr = (uint32_t)chunk + sizeof(heap_chunk_t);
    
    if(physical_addr != NULL)
        *physical_addr = paging_get_physical_address((uint32_t)addr);

    return (void*)addr;
}

void* heap_allocate(uint32_t byte_size)
{
    return heap_allocate_advanced(byte_size, 0, NULL);
}

static heap_chunk_t* combine_chunks(heap_chunk_t* left, heap_chunk_t* right)
{
    uint32_t new_size = left->size + right->size;
    heap_list_remove_chunk(right);
    left->size = new_size;

    return left;
}

void heap_free(void *data)
{
    uint32_t chunk_addr = (uint32_t)data - sizeof(heap_chunk_t);
    heap_chunk_t* chunk = (heap_chunk_t*)chunk_addr;

    heap_chunk_t* previous = chunk->previous_chunk;
    heap_chunk_t* next = chunk->next_chunk;

    if(previous != NULL && !previous->is_allocated)
        chunk = combine_chunks(previous, chunk);

    if(next != NULL && !next->is_allocated)
        chunk = combine_chunks(chunk, next);

    chunk->is_allocated = 0;
}