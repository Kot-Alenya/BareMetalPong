#ifndef _interrupts_h
#define _interrupts_h

#include <stdint.h>
#include "SystemInterrupts.h"
#include "ProgramInterrupts.h"

extern void interrupts_initialize();
extern void interrupts_register_system_handler(uint32_t intNumber, system_interrupt_handler_t handler);
extern void interrupts_register_program_handler(uint32_t intNumber, program_interrupt_handler_t handler);
extern void interrupts_unregister_program_handler(uint32_t intNumber);

#endif