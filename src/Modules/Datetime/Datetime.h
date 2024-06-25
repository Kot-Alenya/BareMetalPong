#ifndef _datetime_h
#define _datetime_h

#include <stdint.h>

typedef struct datetime
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint8_t year;
} datetime_t;

extern void rtc_datetime_get(datetime_t *datetime); 

#endif