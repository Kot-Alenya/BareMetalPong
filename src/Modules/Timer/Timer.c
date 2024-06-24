#include <stdint.h>
#include "Registers.h"
#include "Interrupts.h"
#include "IOAccess.h"
#include "MyMath.h"
#include "Timer.h"

static timer_callback_t _callback;

static void callback_handler(registers_t regs __attribute__((unused)))
{
    _callback();
}

static void set_frequency(uint32_t frequency_ms)
{
    float frequency_hz = 1000 / frequency_ms;
    float base_frequency = 3579545 / 3;
    uint32_t divisor = math_round(base_frequency / frequency_hz);

    io_out_byte(0x43, 0x36);

    uint8_t l = (uint8_t)(divisor & 0xFF);
    uint8_t h = (uint8_t)((divisor >> 8) & 0xFF);

    io_out_byte(0x40, l);
    io_out_byte(0x40, h);
}

void timer_initialize(uint32_t frequency_ms, timer_callback_t callback)
{
    _callback = callback;
    set_frequency(frequency_ms);
    interrupts_register_program_handler(0, &callback_handler);
}