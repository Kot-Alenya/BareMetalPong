#include <stddef.h>
#include "paging.h"
#include "MyMemory.h"
#include "MyError.h"
#include "PagingInternal.h"

static page_directory_entry_t create_table()
{
	uint32_t table_addr;
	
	memory_allocate_advanced(sizeof(page_table_t), 1, &table_addr);
	memory_set((void*)table_addr, 0, sizeof(page_table_t));
	
	page_directory_entry_t result = 
	{
		.present = 1,
		.rw = 1,
		.table_addr = table_addr >> 12
	};
	
	return result;
}

void paging_create_tables(page_directory_t* catalog, uint32_t pages_count)
{
	uint32_t addition = ((pages_count % 1024) != 0) ? 1 : 0;
	uint32_t tables_count = pages_count / 1024 + addition;
	
	for(uint32_t i = 0; i < tables_count; i++)
		catalog->tables[i] = create_table();
}

page_table_t *paging_get_table(page_directory_t* catalog, uint32_t table_index)
{
	uint32_t table_base_addr = catalog->tables[table_index].table_addr << 12;
	page_table_t *table_addr = (page_table_t *)table_base_addr;

	if (table_addr == NULL)
	{
		string_build(monitor_get_common_buffer(), 1, "paging_get_table: no such table, index: %d!", table_index);
		error_throw(monitor_get_common_buffer());
	}
	
	return table_addr;	
}