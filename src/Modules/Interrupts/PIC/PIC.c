#include <stdint.h>
#include "IOAccess.h"

//https://wiki.osdev.org/PIC

static const uint8_t _master_offset = 0x20;
static const uint8_t _slave_offset = 0x28;

static const uint16_t _master_io_base_addr = 0x20;
static const uint16_t _slave_io_base_addr = 0xA0;

static const uint16_t _master_data  = _master_io_base_addr + 1;
static const uint16_t _slave_data = _slave_io_base_addr + 1;

static const uint8_t ICW1_ICW4 = 0x01; //Indicates that ICW4 will be present
static const uint8_t ICW1_INIT	= 0x10; //Initialization - required!
static const uint8_t ICW4_8086	= 0x01; //8086/88 (MCS-80/85) mode

const uint16_t pic_master_command = _master_io_base_addr;
const uint16_t pic_slave_command = _slave_io_base_addr;
const uint8_t pic_end_of_interrupt = 0x20;

void pic_remap()
{
	uint8_t a1 = io_in_byte(_master_data);                        
	uint8_t a2 = io_in_byte(_slave_data);

    // Send initialization signal
	io_out_byte(pic_master_command, ICW1_INIT | ICW1_ICW4);
	io_wait();
	io_out_byte(pic_slave_command, ICW1_INIT | ICW1_ICW4);
	io_wait();

    // Set offset
	io_out_byte(_master_data, _master_offset);
	io_wait();
	io_out_byte(_slave_data, _slave_offset);
	io_wait();

    // Set master-slave relation
	io_out_byte(_master_data, 0x04);
	io_wait();
	io_out_byte(_slave_data, 0x02);
	io_wait();
    
    // Set 8086 mode
	io_out_byte(_master_data, ICW4_8086);
	io_wait();
	io_out_byte(_slave_data, ICW4_8086);
	io_wait();
    
    // restore saved masks.
	io_out_byte(_master_data, a1);
    io_wait();
	io_out_byte(_slave_data, a2);
}