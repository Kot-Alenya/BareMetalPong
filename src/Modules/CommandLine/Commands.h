#ifndef _commands_h
#define _commands_h

#include "CommandLine.h"
#include "Monitor.h"
#include "HeapList.h"
#include "MachineControl.h"

command_t initial_commands[] = 
{
    {.name = "?", .handler = command_line_write_list_of_commands},
    {.name = "help", .handler = command_line_write_list_of_commands},
    {.name = "write_grub_mbi", .handler = memory_write_multiboot_info},
    {.name = "write_heap", .handler = heap_list_write_elements},
    {.name = "clean", .handler = monitor_clean},
    {.name = "reboot", .handler = machine_control_reboot}
};

uint32_t initial_commands_count = 6;

#endif