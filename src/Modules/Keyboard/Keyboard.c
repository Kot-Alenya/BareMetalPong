#include <stdint.h>
#include "IOAccess.h"
#include "Registers.h"
#include "Interrupts.h"
#include "Keyboard.h"
#include "KeysStatus.h"

static void keyboard_handler(registers_t regs __attribute__((unused))) 
{
	uint8_t key_code = io_in_byte(0x60);

    keys_status_update(key_code);

    uint8_t status = io_in_byte(0x61);
	
	status |= 1;
	io_out_byte(0x61, status);
}

void keyboard_initialize()
{
    interrupts_register_program_handler(1, keyboard_handler);
}