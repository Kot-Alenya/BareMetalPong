#ifndef _idt_h
#define _idt_h

#include <stdint.h>

typedef struct __attribute__((packed)) idt_enter
{
    uint16_t base_low;
    uint16_t selector; // Селектор сегмента
    uint8_t  always_zero;
    uint8_t  flags; // Флаги. RTFM.
    uint16_t base_high;
} idt_enter_t;

typedef struct __attribute__((packed)) idt_record 
{
    uint16_t limit;
    uint32_t base_ptr;
} idt_record_t;

extern void idt_flush();
extern void idt_set_data(uint32_t num, uint32_t base, uint16_t selector, uint8_t flags);

#endif