#ifndef _system_interrupts_h
#define _system_interrupts_h

#include  <stdint.h>
#include "Registers.h"

typedef void (*system_interrupt_handler_t) (registers_t r, uint32_t errorCode);

extern void system_interrupts_set_data();
extern void system_interrupts_register_handler(uint32_t intNumber, system_interrupt_handler_t handler);

#define _define_sys_int_fun(num) extern void _sys_int##num()
_define_sys_int_fun(0);
_define_sys_int_fun(1);
_define_sys_int_fun(2);
_define_sys_int_fun(3);
_define_sys_int_fun(4);
_define_sys_int_fun(5);
_define_sys_int_fun(6);
_define_sys_int_fun(7);
_define_sys_int_fun(8);
_define_sys_int_fun(9);
_define_sys_int_fun(10);
_define_sys_int_fun(11);
_define_sys_int_fun(12);
_define_sys_int_fun(13);
_define_sys_int_fun(14);
_define_sys_int_fun(15);
_define_sys_int_fun(16);
_define_sys_int_fun(17);
_define_sys_int_fun(18);
_define_sys_int_fun(19);
_define_sys_int_fun(20);
_define_sys_int_fun(21);
_define_sys_int_fun(22);
_define_sys_int_fun(23);
_define_sys_int_fun(24);
_define_sys_int_fun(25);
_define_sys_int_fun(26);
_define_sys_int_fun(27);
_define_sys_int_fun(28);
_define_sys_int_fun(29);
_define_sys_int_fun(30);
_define_sys_int_fun(31);
#endif