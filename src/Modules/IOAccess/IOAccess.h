#ifndef _IOAccess_h
#define _IOAccess_h

#include <stdint.h>

extern uint8_t io_in_byte(uint16_t port);
extern void io_out_byte(uint16_t port, uint8_t value);
extern void io_wait();

#endif