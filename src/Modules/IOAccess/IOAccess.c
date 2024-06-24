#include <stdint.h>

uint8_t io_in_byte(uint16_t port)
{
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

void io_out_byte(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

void io_wait()
{
    io_out_byte(0x80, 0);
}