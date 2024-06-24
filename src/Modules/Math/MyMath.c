#include <stdint.h>

uint32_t math_get_digits_count(uint32_t value) 
{
    uint32_t digits = 0;
    
    if(value == 0)
        return 1;
    
    while (value != 0)
    {
        digits++;
        value /= 10;
    }

    return digits;
}

int32_t math_round(float value)
{
    if (value >= 0.0f)
        return (int32_t)(value + 0.5f);
    
    return (int32_t)(value - 0.5f);
}
