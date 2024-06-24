#ifndef _gdt_h
#define _gdt_h

#include <stdint.h>

extern const uint16_t GDT_CODE_SELECTOR;
extern const uint16_t GDT_DATA_SELECTOR;

typedef struct gdt_entry
{
    uint64_t limit_low : 16;
    uint64_t base_low : 16;
    uint64_t base_middle : 8;
    uint64_t access_flag : 1; //1 после первого системного обращения
    uint64_t is_readable : 1; 
    uint64_t is_conforming : 1; //может ли высокопривилигированный код обращаться к этому коду? (доступен ли этот код пользователю) 
    uint64_t is_code : 1; // 1-код, 0-данные
    uint64_t is_system : 1;
    uint64_t privilege_level : 2;
    uint64_t is_present: 1;
    uint64_t limit_high : 4;
    uint64_t reserve: 1;
    uint64_t always_zero: 1;
    uint64_t db: 1; //0 - 16bit; 1 - 32bit
    uint64_t granularity : 1; //1 -  4 kB, 0 - 1byte
    uint64_t base_high : 8;
} gdt_entry_t;

typedef struct __attribute__((packed)) gdt_record
{
    uint16_t limit;
    uint32_t base_ptr;
} gdt_record_t;

extern void gdt_initialize();

#endif