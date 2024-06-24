#include <stddef.h>
#include "paging.h"
#include "Interrupts.h"
#include "MyMemory.h"
#include "PagingInternal.h"

extern uint32_t LINKER_SECTION_TEXT_START;
extern uint32_t LINKER_SECTION_RODATA_START;
extern uint32_t LINKER_SECTION_DATA_START;
extern uint32_t LINKER_SECTION_BSS_START;
extern uint32_t LINKER_FILE_END;

static page_directory_t* _directory;

static void set_page(page_directory_t *directory, uint32_t *from_addr, uint32_t *to_addr, uint32_t rw)
{
	uint32_t from = (uint32_t)from_addr / 4096;
	uint32_t to = (uint32_t)to_addr / 4096;

	for(uint32_t i = from; i < to; i++)
		paging_set_page(directory, i, i, rw);
}

static page_directory_t* create_directory(uint32_t all_frames_count)
{
	uint32_t directory_addr;
	memory_allocate_advanced(sizeof(page_directory_t), 1, &directory_addr);
	memory_set((void*)directory_addr, 0, sizeof(page_directory_t));
	page_directory_t* directory = (page_directory_t*)directory_addr;

	paging_create_tables(directory, all_frames_count); //сразу создаю таблицы для всех страниц
	
	void* placement_addr = memory_get_next_placement_address();
	set_page(directory, 0, &LINKER_SECTION_TEXT_START, 1); //данные до начала кода.
	set_page(directory, &LINKER_SECTION_TEXT_START, &LINKER_SECTION_RODATA_START, 0); //данные кода.
	set_page(directory, &LINKER_SECTION_RODATA_START, &LINKER_SECTION_DATA_START, 0); //данные только для чтения
	set_page(directory, &LINKER_SECTION_DATA_START, &LINKER_SECTION_BSS_START, 1); //данные для чтения и записи
	set_page(directory, &LINKER_SECTION_BSS_START, &LINKER_FILE_END, 1); //не инициализированные данные.
	set_page(directory, &LINKER_FILE_END, placement_addr, 1); //данные выделенные уже после запуска програмы (стек, таблицы страниц и т.д.)
	
	return directory;
}

static void paging_set_page_directory(page_directory_t *directory)
{
	__asm__ volatile ("mov %0, %%cr3"::"r"(directory));
	uint32_t cr0;
	__asm__ volatile ("mov %%cr0, %0": "=r"(cr0));
	cr0 |= (1 << 31) | (1 << 16);
	__asm__ volatile ("mov %0, %%cr0":: "r"(cr0));
}

void paging_initialize(uint32_t memory_byte_size)
{
	uint32_t all_frames_count = memory_byte_size / 0x1000;
	
	paging_create_frame_bitmap(all_frames_count);
	page_directory_t* directory = create_directory(all_frames_count);
	
	interrupts_register_system_handler(14, paging_page_fault_handler);
	paging_set_page_directory(directory);

	_directory = directory;
}

page_directory_t* paging_get_directory()
{
	return _directory;
}

uint32_t paging_get_physical_address(uint32_t virtual_address)
{
	uint32_t page_number = (virtual_address & 0xFFFFF000) >> 12;
	page_t* page = paging_get_page(page_number, _directory);
	return (page->frame_addr << 12) | (virtual_address & 0x00000FFF);
}