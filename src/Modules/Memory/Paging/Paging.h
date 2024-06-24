#ifndef _paging_h
#define _paging_h

#include <stdint.h>
#include "Registers.h"

typedef struct page
{
    uint32_t present : 1; //если установлен, страница присутствует в памяти
    uint32_t rw : 1; //если установлен, страница доступна для записи
    uint32_t user : 1; //если установлен, страница доступна всем уровням привилегий
    uint32_t pwt : 1; //Write Through, если установлен, используется режим сквозной записи
    uint32_t pcd : 1; //Указывает, следует ли кэшировать страницу
    uint32_t accessed : 1; //устанавливается процессором при доступе к странице
    uint32_t dirty : 1; //устанавливается процессором при записи в страницу
    uint32_t pat : 1; //Указывает индексацию в PAT
    uint32_t global : 1; //Глобальная страница, не сбрасывается из TLB при изменении CR3.
    uint32_t available : 3; 
    uint32_t frame_addr : 20;
} page_t;

typedef struct page_table
{
	page_t pages[1024];
} page_table_t;

typedef struct page_directory_entry
{
    uint32_t present : 1; //если установлен, страница присутствует в памяти
    uint32_t rw : 1; //если установлен, страница доступна для записи
    uint32_t user : 1; //если установлен, страница доступна всем уровням привилегий
    uint32_t pwt : 1; //Write Through, если установлен, используется режим сквозной записи
    uint32_t pcd : 1; //cache disable, если установлен, то кэширование отключено
    uint32_t accessed : 1; //устанавливается процессором при доступе к странице
    uint32_t dirty : 1; //устанавливается процессором при записи в страницу
    uint32_t ps : 1; //If the bit is set, then the PDE maps to a page that is 4 MiB in size. Otherwise, it maps to a 4 KiB page table. Please note that 4-MiB pages require PSE to be enabled.
    uint32_t global : 1; //Глобальная страница, не сбрасывается из TLB при изменении CR3.
    uint32_t available : 3;
    uint32_t table_addr : 20;
} page_directory_entry_t;

typedef struct page_directory
{
	page_directory_entry_t tables[1024];
} page_directory_t;

extern void paging_initialize(uint32_t memory_byte_size);
extern page_directory_t* paging_get_directory();
extern uint32_t paging_get_frames_count();
extern void paging_set_page(page_directory_t *directory, uint32_t page_number, uint32_t frame_number, uint32_t rw);
extern uint32_t paging_test_frame(uint32_t frame_number);
extern uint32_t paging_get_physical_address(uint32_t virtual_address);

#endif