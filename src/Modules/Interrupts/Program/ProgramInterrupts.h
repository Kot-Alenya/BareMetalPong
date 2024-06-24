#ifndef _program_interrupts_h
#define _program_interrupts_h

#include <stdint.h>
#include "Registers.h"

typedef void (*program_interrupt_handler_t) (registers_t r);

extern void program_interrupts_set_data();
extern void program_interrupts_register_handler(uint32_t intNumber, program_interrupt_handler_t handler);
extern void program_interrupts_unregister_handler(uint32_t intNumber);

#define _define_prog_int_fun(num) extern void _prog_int##num()
_define_prog_int_fun(0);
_define_prog_int_fun(1);
_define_prog_int_fun(2);
_define_prog_int_fun(3);
_define_prog_int_fun(4);
_define_prog_int_fun(5);
_define_prog_int_fun(6);
_define_prog_int_fun(7);
_define_prog_int_fun(8);
_define_prog_int_fun(9);
_define_prog_int_fun(10);
_define_prog_int_fun(11);
_define_prog_int_fun(12);
_define_prog_int_fun(13);
_define_prog_int_fun(14);
_define_prog_int_fun(15);
#endif