#include <stddef.h>
#include <stdint.h>
#include "paging.h"
#include "MyError.h"
#include "MyString.h"
#include "PagingInternal.h"

page_t *paging_get_page(uint32_t page_number, page_directory_t *directory)
{
	uint32_t page_offset = page_number % 1024;
    uint32_t table_index = page_number / 1024;
	page_table_t *table = paging_get_table(directory, table_index);
	
	return &table->pages[page_offset];
}

static uint32_t get_fault_addr()
{
	uint32_t addr;
	__asm__ volatile ("mov %%cr2, %0" : "=r"(addr));
	return addr;
}

void paging_set_page(page_directory_t *directory, uint32_t page_number, uint32_t frame_number, uint32_t rw)
{
	page_t* page = paging_get_page(page_number, directory);
	paging_set_frame(frame_number);
	
	page->present = 1;
	page->rw = rw;
	page->user = 0;
	page->frame_addr = frame_number;
}

void paging_page_fault_handler(registers_t regs __attribute__((unused)), uint32_t error_code)
{
	uint32_t fault_addr = get_fault_addr();

	uint32_t present = error_code & 0x1;
	uint32_t rw = error_code & 0x2;
	uint32_t us = error_code & 0x4;
	uint32_t reserved = error_code & 0x8;
	uint32_t instruction = error_code & 0x10;
	uint32_t frame_allocated = paging_test_frame(fault_addr / 4096);
	uint32_t l = 0;

	l += string_build(monitor_get_common_buffer(), 0, "Page fault at 0x%h!\n", fault_addr);
	l += string_build(monitor_get_common_buffer() + l, 0, "%s-present,%s-write-operation,%s-user-mode,%s-reserved,%s-instruction-fetch, %s-frame-allocated\n",
	present ? "yes" : "no",
	rw ? "yes" : "no",
	us ? "yes" : "no",
	reserved ? "yes" : "no", //зарезервирован ли бит в записи таблицы страниц установлен (обычно указывает на ошибку в таблице страниц) ?
	instruction ? "yes" : "no", //ошибка вызвана операцией с данными ?
	frame_allocated ? "yes" : "no");

	error_throw(monitor_get_common_buffer());
}