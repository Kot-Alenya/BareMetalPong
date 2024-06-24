#include <stdint.h>
#include "SimpleAllocator.h"
#include "Heap.h"
#include "MyError.h"
#include "Paging.h"
#include "multiboot.h"

static uint32_t _is_paging_enabled;
static multiboot_info_t* _multiboot_info;

void* memory_allocate_advanced(uint32_t byte_size, uint32_t is_aligned, uint32_t* physical_addr)
{
    if(_is_paging_enabled)
        return heap_allocate_advanced(byte_size, is_aligned, physical_addr);
    
    return simple_allocator_allocate_advanced(byte_size, is_aligned, physical_addr);
}

void* memory_allocate(uint32_t byte_size)
{
    if(_is_paging_enabled)
        return heap_allocate(byte_size);
    
    return simple_allocator_allocate(byte_size);
}

void* memory_get_next_placement_address()
{
    if(_is_paging_enabled)
        error_throw("memory_get_next_placement_address: Can`t get placement address when paging enabled!");
    
    return simple_allocator_get_next_placement_address();
}

void memory_free(void *data)
{
    if(_is_paging_enabled)
        return heap_free(data);
    
    error_throw("memory_free: Can`t free when paging not enabled!");
}

static uint32_t get_memory_byte_size(multiboot_info_t* multiboot_info)
{
    uint32_t memory_size = 0;

    for(uint32_t i = 0; i < multiboot_info->mmap_length; i += sizeof(multiboot_memory_map_t)) 
    {
        multiboot_memory_map_t* memory_map = (multiboot_memory_map_t*)(multiboot_info->mmap_addr + i);

        if(memory_map->addr_high > 0 || memory_map->len_high > 0)
            break;
        
        if(memory_map->type == MULTIBOOT_MEMORY_AVAILABLE)
            memory_size = memory_map->addr_low + memory_map->len_low;
    }

    return memory_size;
}

void memory_initialize(multiboot_info_t* multiboot_info)
{
    _multiboot_info = multiboot_info;
    uint32_t memory_size = get_memory_byte_size(multiboot_info);

    paging_initialize(memory_size);
    heap_initialize();

    _is_paging_enabled = 1;
}

void memory_write_multiboot_info()
{
    for(uint32_t i = 0; i < _multiboot_info->mmap_length; i += sizeof(multiboot_memory_map_t)) 
    {
        multiboot_memory_map_t* memory_map = (multiboot_memory_map_t*)(_multiboot_info->mmap_addr + i);

        string_build(monitor_get_common_buffer(), 1,"Start Addr: %h | Length: %h | Type: %d | Size: %h \n",
            memory_map->addr_low, memory_map->len_low, memory_map->type, memory_map->size);
        monitor_push_string(monitor_get_common_buffer());
    }
}
