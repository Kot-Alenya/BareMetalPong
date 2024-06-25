#include "multiboot.h"
#include "Monitor.h"
#include "GDT.h"
#include "Interrupts.h"
#include "MyMemory.h"
#include "Keyboard.h"
#include "CommandLine.h"
#include "Game.h"
#include "Random.h"

static void start_game_handler();

static void register_game()
{
    command_t start_game_comand =  {.name = "start_pong", .handler = start_game_handler};
    command_line_register_command(start_game_comand);
}

static void start_game_handler()
{
    command_line_dispose();
    Game_Startup();
    command_line_initialize();
    register_game();
}

void program_main(multiboot_info_t* multiboot_info)
{
    monitor_initialize();
    gdt_initialize();
    interrupts_initialize();
    memory_initialize(multiboot_info);
    
    keyboard_initialize();

    command_line_initialize();
    register_game();
/*
    Random_Initialize();
    monitor_push_uint32(Random_Next(0, 10));
    monitor_push_char('\n');
    monitor_push_uint32(Random_Next(0, 10));
    monitor_push_char('\n');
    monitor_push_uint32(Random_Next(0, 10));
    monitor_push_char('\n');
    monitor_push_uint32(Random_Next(0, 10));
    monitor_push_char('\n');
    monitor_push_uint32(Random_Next(0, 10));
    monitor_push_char('\n');
    monitor_push_uint32(Random_Next(0, 10));
    monitor_push_char('\n');
    monitor_push_uint32(Random_Next(0, 10));
    monitor_push_char('\n');
    monitor_push_uint32(Random_Next(0, 10));
    monitor_push_char('\n');
    monitor_push_uint32(Random_Next(0, 10));
    monitor_push_char('\n');
    monitor_push_uint32(Random_Next(0, 10));
    monitor_push_char('\n');
    monitor_push_uint32(Random_Next(0, 10));
    monitor_push_char('\n');
    monitor_push_uint32(Random_Next(0, 10));
    monitor_push_char('\n');
    monitor_push_uint32(Random_Next(0, 10));
    monitor_push_char('\n');
    monitor_push_uint32(Random_Next(0, 10));
    monitor_push_char('\n');
    monitor_push_uint32(Random_Next(0, 10));
*/

    while (1) 
    {
        command_line_update();
    }
}