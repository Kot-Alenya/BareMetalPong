#include <stdint.h>
#include <stddef.h>

extern uint32_t LINKER_FILE_END;

uint32_t _placement_address = (uint32_t)&LINKER_FILE_END;

void* simple_allocator_allocate_advanced(uint32_t byte_size, uint32_t is_aligned, uint32_t* physical_addr)
{
    if (is_aligned == 1 && (_placement_address & 0x00000FFF))
    {
        _placement_address &= 0xFFFFF000;
        _placement_address += 0x1000;
    }

    if (physical_addr != NULL)
        *physical_addr = _placement_address;
    
    uint32_t tmp = _placement_address;
    _placement_address += byte_size;
    return (void*)tmp;
}

void* simple_allocator_allocate(uint32_t byte_size)
{
    return simple_allocator_allocate_advanced(byte_size, 0, NULL);
}

void* simple_allocator_get_next_placement_address()
{
    return (void*)_placement_address;
}