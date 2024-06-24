#include <stdint.h>
#include "IDT.h"

static idt_enter_t _bases[256];
static idt_record_t _record;

extern void _idt_flush(uint32_t recordPtr);

void idt_set_data(uint32_t num, uint32_t base, uint16_t selector, uint8_t flags)
{
    _bases[num].base_low = base & 0xFFFF;
    _bases[num].base_high = (base >>16) & 0xFFFF;
    _bases[num].selector = selector;
    _bases[num].always_zero = 0;
    _bases[num].flags = flags;
}

void idt_flush()
{
    _record.limit = sizeof(_bases) - 1;
    _record.base_ptr = (uint32_t)&_bases;
    _idt_flush((uint32_t)&_record);
}