#include <stdint.h>
#include "Keyboard.h"
#include "Monitor.h"
#include "CommandLine.h"
#include "MyMemory.h"
#include "MyString.h"
#include "Commands.h"

#define _LINE_BUFFER_SIZE 79

static const uint32_t _line_buffer_size = _LINE_BUFFER_SIZE;
static char _line_buffer[_LINE_BUFFER_SIZE];
static uint32_t _line_length;

static command_t _commands[10];
static uint32_t _commands_count;
static uint32_t _is_handle_command_request;

static void handle_command()
{
    if(_line_length == 0)
        return;
    
    for(uint32_t i = 0; i < _commands_count; i++)
    {
        if(memory_compare(_commands[i].name, (char*)_line_buffer, _line_length))
        {
            _commands[i].handler();
            return;
        }
    }

    monitor_push_string("Cant find this command!\n\0");
}

static void on_change_key_status_handler(keyboard_scancode_t key_code, uint32_t status)
{
    if(status == 0)
        return;

    if(key_code == BACKSPACE)
    {
        uint32_t cursor_pos = monitor_get_cursor_position() - 1;
        
        if(cursor_pos >= MONITOR_WIDTH * MONITOR_HEIGHT || _line_length == 0)
            return;

        monitor_set_cursor_position(cursor_pos);
        monitor_set_char(' ', cursor_pos);
        _line_length--;
        return;
    }
    
    if(key_code == ENTER)
    {
        monitor_push_char('\n');
        _is_handle_command_request = 1;
        return;
    }

    char c = keyboard_convert_scancode_to_ASCII(key_code, keyboard_test_key(LEFT_SHIFT), keyboard_is_capslock());

    if(c != 0 && _line_length < _line_buffer_size)
    {
        monitor_push_char(c);
        _line_buffer[_line_length] = c;
        _line_length++;
    }
}

void command_line_register_command(command_t command)
{
    _commands[_commands_count] = command;
    _commands_count++;
}

void command_line_initialize()
{
    keyboard_register_on_change_key_status_handler(on_change_key_status_handler);

    for(uint32_t i = 0; i < initial_commands_count; i++)
        command_line_register_command(initial_commands[i]);
}

void command_line_write_list_of_commands()
{
    monitor_push_string("List of all commands: \n\0");

    for(uint32_t i = 0; i < _commands_count; i++)
    {
        string_build(monitor_get_common_buffer(), 1, "%s\n", _commands[i].name);
        monitor_push_string(monitor_get_common_buffer());
    }
}

void command_line_dispose()
{
    keyboard_unregister_on_change_key_status_handler(on_change_key_status_handler);
    _commands_count = 0;
}

void command_line_update()
{
    if(_is_handle_command_request)
    {
        handle_command();
        _line_length = 0;
        _is_handle_command_request = 0;
    }
}