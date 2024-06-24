#include <stdint.h>
#include "Registers.h"
#include "SystemInterrupts.h"
#include "IDT.h"
#include "GDT.h"
#include "MyError.h"

static system_interrupt_handler_t _handlers[32];

#define _system_interrupt_set_data_macro(num) idt_set_data(num, (uint32_t)_sys_int##num, GDT_CODE_SELECTOR, 0x8E);
void system_interrupts_set_data()
{
    _system_interrupt_set_data_macro(0);
    _system_interrupt_set_data_macro(1);
    _system_interrupt_set_data_macro(2);
    _system_interrupt_set_data_macro(3);
    _system_interrupt_set_data_macro(4);
    _system_interrupt_set_data_macro(5);
    _system_interrupt_set_data_macro(6);
    _system_interrupt_set_data_macro(7);
    _system_interrupt_set_data_macro(8);
    _system_interrupt_set_data_macro(9);
    _system_interrupt_set_data_macro(10);
    _system_interrupt_set_data_macro(11);
    _system_interrupt_set_data_macro(12);
    _system_interrupt_set_data_macro(13);
    _system_interrupt_set_data_macro(14);
    _system_interrupt_set_data_macro(15);
    _system_interrupt_set_data_macro(16);
    _system_interrupt_set_data_macro(17);
    _system_interrupt_set_data_macro(18);
    _system_interrupt_set_data_macro(19);
    _system_interrupt_set_data_macro(20);
    _system_interrupt_set_data_macro(21);
    _system_interrupt_set_data_macro(22);
    _system_interrupt_set_data_macro(23);
    _system_interrupt_set_data_macro(24);
    _system_interrupt_set_data_macro(25);
    _system_interrupt_set_data_macro(26);
    _system_interrupt_set_data_macro(27);
    _system_interrupt_set_data_macro(28);
    _system_interrupt_set_data_macro(29);
    _system_interrupt_set_data_macro(30);
    _system_interrupt_set_data_macro(31);
}

void system_interrupts_register_handler(uint32_t intNumber, system_interrupt_handler_t handler)
{
    _handlers[intNumber] = handler;
}

void _system_interrupts_common_handler(registers_t registers, uint32_t intNumber, uint32_t errorCode)
{
    if(_handlers[intNumber] != 0)
        _handlers[intNumber](registers, errorCode);
    else
    {
        string_build(monitor_get_common_buffer(), 1, "_system_interrupts_common_handler: No interrupt handler for %d!\nError code: 0x%h", intNumber, errorCode);
        error_throw(monitor_get_common_buffer());
    }
}