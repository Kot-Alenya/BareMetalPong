#ifndef _pic_h
#define _pic_h

#include <stdint.h>

extern const uint16_t pic_master_command;
extern const uint16_t pic_slave_command;
extern const uint8_t pic_end_of_interrupt;

void pic_remap();
#endif