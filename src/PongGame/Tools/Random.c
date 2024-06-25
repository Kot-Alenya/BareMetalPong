#include <stdint.h>
#include "Datetime.h"

static uint32_t _seed;

static uint32_t lcg_random() 
{
    _seed ^= (_seed << 13);
    _seed ^= (_seed >> 17);
    _seed ^= (_seed << 5);
    return _seed;
}

void Random_Initialize()
{
    datetime_t datetime;
    rtc_datetime_get(&datetime);
    _seed = datetime.hours * datetime.minutes * datetime.seconds;
}

int Random_Next(int min, int max)
{
    int r = min + lcg_random() % (max - min);
    return r;
}