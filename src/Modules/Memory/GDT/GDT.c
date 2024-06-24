#include <stdint.h>
#include "GDT.h"

const uint16_t GDT_CODE_SELECTOR = 0x08;
const uint16_t GDT_DATA_SELECTOR = 0x10;

static gdt_entry_t _bases[3];
static gdt_record_t _record;

extern void _gdt_flush(uint32_t record_ptr);

static gdt_entry_t CreateGDTBase(uint32_t base, uint32_t limit, uint32_t is_readable, uint32_t is_code, uint32_t is_system, uint32_t is_present, uint32_t db, uint32_t granularity)
{
    gdt_entry_t result;

    result.base_low = base;
    result.base_middle = base >> 16;
    result.base_high = base >> 24;

    result.limit_low = limit;
    result.limit_high = limit >> 16;

    result.is_readable = is_readable;
    result.is_code = is_code;
    result.is_system = is_system;
    result.is_present = is_present;
    result.db = db;
    result.granularity = granularity;
    
    return result;
}

void gdt_initialize()
{
    _record.limit = sizeof(_bases) - 1;
    _record.base_ptr = (uint32_t)&_bases;

    _bases[0] = CreateGDTBase(0, 0, 0, 0, 0, 0, 0, 0);
    _bases[1] = CreateGDTBase(0, 0xFFFFF, 1, 1, 1, 1, 1, 1);
    _bases[2] = CreateGDTBase(0, 0xFFFFF, 1, 0, 1, 1, 1, 1);

    _gdt_flush((uint32_t)&_record);
}
