#ifndef _datetime_h
#define _datetime_h

#include <stdint.h>

typedef struct rtc_datetime
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint8_t year;
} rtc_datetime_t;

#endif