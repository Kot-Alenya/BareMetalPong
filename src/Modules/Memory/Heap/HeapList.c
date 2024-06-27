#include <stdint.h>
#include <stddef.h>
#include "Heap.h"
#include "MyError.h"

static heap_chunk_t* _first_chunk = NULL;

void heap_list_write_elements()
{
    for(heap_chunk_t* c = _first_chunk; c != NULL; c = c->next_chunk)
    {
        string_build(monitor_get_common_buffer(), 1, "addr: %h    size: %h    allocated: %d\n", (uint32_t)c, GET_CHUNK_SIZE(c), c->is_allocated);
        monitor_push_string(monitor_get_common_buffer());      
    }
}

//встраивает в список слева от чанка
static void insert_left(heap_chunk_t* new_chunk, heap_chunk_t* chunk)
{
    heap_chunk_t* previous = chunk->previous_chunk;

    if(previous != NULL)
        previous->next_chunk = new_chunk;

    chunk->previous_chunk = new_chunk;

    new_chunk->previous_chunk = previous;
    new_chunk->next_chunk = chunk;
}

//встраивает в список справа от чанка
static void insert_right(heap_chunk_t* new_chunk, heap_chunk_t* chunk)
{
    heap_chunk_t* next = chunk->next_chunk;

    if(next != NULL)
        next->previous_chunk = new_chunk;

    chunk->next_chunk = new_chunk;

    new_chunk->next_chunk = next;
    new_chunk->previous_chunk = chunk;
}

void heap_list_add_chunk(heap_chunk_t* chunk)
{
    if(_first_chunk == NULL)
    {
        _first_chunk = chunk;
        return;
    }

    heap_chunk_t* c = _first_chunk;
    while(c->next_chunk != NULL)
    {
        if((uint32_t)c > (uint32_t)chunk)
        {
            insert_left(chunk, c);
            return;
        }

        c = c->next_chunk;
    }

    insert_right(chunk, c);
}

heap_chunk_t* heap_list_find_chunk(uint32_t size, uint32_t is_allocated_chunk, uint32_t is_aligned)
{
    for(heap_chunk_t* c = _first_chunk; c != NULL; c = c->next_chunk)
    {
        uint32_t c_size = GET_CHUNK_SIZE(c);
        
        if(is_aligned)
        {
            uint32_t c_distance_to_next_page = 0x1000 - ((uint32_t)c & 0x00000FFF);

            if(c_distance_to_next_page >= c_size || c_distance_to_next_page < CHUNK_MINIMUM_BYTE_SIZE)
                continue;
            
            c_size -= c_distance_to_next_page;
        }

        if((c_size >= size) && (c->is_allocated == is_allocated_chunk))
            return c;
    }

    string_build(monitor_get_common_buffer(), 1,"heap_list_find_chunk: can`t find chunk with size: %h", size);
    error_throw(monitor_get_common_buffer());
    return NULL;
}

void heap_list_remove_chunk(heap_chunk_t* chunk)
{
    heap_chunk_t* previous = chunk->previous_chunk;
    heap_chunk_t* next = chunk->next_chunk;

    if(chunk == _first_chunk)
        _first_chunk = next;    
    else
        previous->next_chunk = next;

    if(next != NULL)
        next->previous_chunk = previous;

    chunk->previous_chunk = NULL;
    chunk->next_chunk = NULL;
}