#ifndef _PagingIternal_h
#define _PagingIternal_h

#include <stdint.h>
#include "Paging.h"

//frames
extern void paging_create_frame_bitmap(uint32_t frames_count);
extern void paging_set_frame(uint32_t frame_number);
extern void paging_clear_frame(uint32_t frame_number);

//pages
extern void paging_page_fault_handler(registers_t regs, uint32_t error_code);
extern page_t *paging_get_page(uint32_t page_number, page_directory_t *directory);

//tables
extern void paging_create_tables(page_directory_t* directory, uint32_t pages_count);
extern page_table_t *paging_get_table(page_directory_t* directory, uint32_t table_index);

#endif