#include "PIC.h"
#include "SystemInterrupts.h"
#include "ProgramInterrupts.h"
#include "IDT.h"

void interrupts_initialize()
{
    pic_remap();
    system_interrupts_set_data();
    program_interrupts_set_data();
    idt_flush();
    asm volatile ("sti");
}

void interrupts_register_system_handler(uint32_t intNumber, system_interrupt_handler_t handler)
{
    system_interrupts_register_handler(intNumber, handler);
}

void interrupts_register_program_handler(uint32_t intNumber, program_interrupt_handler_t handler)
{
    program_interrupts_register_handler(intNumber, handler);
}