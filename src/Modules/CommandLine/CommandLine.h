#ifndef _command_line_h
#define _command_line_h

#include <stdint.h>

typedef void (*command_handler_t) ();

typedef struct command
{
    char* name;
    command_handler_t handler;
} command_t;

extern void command_line_initialize();
extern void command_line_write_list_of_commands();
extern void command_line_register_command(command_t command);
extern void command_line_dispose();

#endif