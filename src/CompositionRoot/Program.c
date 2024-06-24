#include "multiboot.h"
#include "Monitor.h"
#include "GDT.h"
#include "Interrupts.h"
#include "MyMemory.h"
#include "Keyboard.h"
#include "CommandLine.h"
#include "Game.h"

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
    
    start_game_handler();

    while (1) {}
}