#include <stdint.h>
#include "Datetime.h"
#include "IOAccess.h"

static uint8_t read_rtc_register(uint8_t reg) 
{
    io_out_byte(0x70, reg);
    return io_in_byte(0x71);
}

static uint8_t bcd_to_binary(uint8_t bcd) 
{
    return (bcd & 0x0F) + ((bcd / 16) * 10);
}

void rtc_datetime_get(datetime_t *datetime) 
{
    datetime->seconds = bcd_to_binary(read_rtc_register(0x00));
    datetime->minutes = bcd_to_binary(read_rtc_register(0x02));
    datetime->hours = bcd_to_binary(read_rtc_register(0x04));
    datetime->day = bcd_to_binary(read_rtc_register(0x07));
    datetime->month = bcd_to_binary(read_rtc_register(0x08));
    datetime->year = bcd_to_binary(read_rtc_register(0x09));
}