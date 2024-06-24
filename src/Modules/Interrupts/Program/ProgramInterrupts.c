#include <stdint.h>
#include "Registers.h"
#include "IOAccess.h"
#include "PIC.h"
#include "GDT.h"
#include "IDT.h"
#include "ProgramInterrupts.h"
#include "MyError.h"

static program_interrupt_handler_t _handlers[16];

#define _program_interrupts_set_data_macro(num) idt_set_data(32 + num, (uint32_t)_prog_int##num, GDT_CODE_SELECTOR, 0x8E);

void program_interrupts_set_data()
{
    _program_interrupts_set_data_macro(0);
    _program_interrupts_set_data_macro(1);
    _program_interrupts_set_data_macro(2);
    _program_interrupts_set_data_macro(3);
    _program_interrupts_set_data_macro(4);
    _program_interrupts_set_data_macro(5);
    _program_interrupts_set_data_macro(6);
    _program_interrupts_set_data_macro(7);
    _program_interrupts_set_data_macro(8);
    _program_interrupts_set_data_macro(9);
    _program_interrupts_set_data_macro(10);
    _program_interrupts_set_data_macro(11);
    _program_interrupts_set_data_macro(12);
    _program_interrupts_set_data_macro(13);
    _program_interrupts_set_data_macro(14);
    _program_interrupts_set_data_macro(15);
}

void program_interrupts_register_handler(uint32_t intNumber, program_interrupt_handler_t handler)
{
    _handlers[intNumber] = handler;
}

void _program_interrupts_common_handler(registers_t registers, uint32_t intNumber)
{
    if (intNumber >= 8)
        io_out_byte(pic_slave_command, pic_end_of_interrupt);

    io_out_byte(pic_master_command, pic_end_of_interrupt);

    if(_handlers[intNumber] != 0)
        _handlers[intNumber](registers);
}