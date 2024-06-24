ENTRY(_start)
SECTIONS
{
    . = 0x100000;
	
    .text : ALIGN(4K)
    {
		LINKER_SECTION_TEXT_START = .;
		*(.multiboot)
        *(.text)
    }

    .rodata : ALIGN(4K)
    {
		LINKER_SECTION_RODATA_START = .;
        *(.rodata)
    }

    .data : ALIGN(4K)
    {
		LINKER_SECTION_DATA_START = .;
        *(.data)
    }

    .bss : ALIGN(4K)
    {
		LINKER_SECTION_BSS_START = .;
		*(COMMON)
        *(.bss)
		. = ALIGN(4K);
	}
	
	LINKER_FILE_END = .;
}
