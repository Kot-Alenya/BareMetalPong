#include <stdarg.h>
#include <stdint.h>
#include "MyString.h"
#include "MyMath.h"
#include "MyError.h"
#include "MyMemory.h"

uint32_t string_from_uint32(char *dest, uint32_t value, uint32_t isSetEnd)
{
	uint32_t charCount = math_get_digits_count(value);

    if (value == 0) 
    {
        dest[0] = '0';

        if(isSetEnd)
            dest[1] = '\0';

        return isSetEnd ? 2 : 1;
    }

    if(isSetEnd)
        dest[charCount] = '\0';

    for(int i = charCount - 1; i >= 0; i--)
    {
        dest[i] = '0' + (value % 10);
        value /= 10;
    }

    return isSetEnd ? (charCount + 1) : charCount;
}

uint32_t string_from_uint32_hex(char *dest, uint32_t value, uint32_t isSetEnd)
{
	const char hexDigits[] = "0123456789ABCDEF";
    const uint32_t length = 8;

    for (int i = length - 1; i >= 0; i--) 
    {
        dest[i] = hexDigits[value & 0xF];
        value >>= 4;
    }

    if(isSetEnd)
        dest[length] = '\0';

    return isSetEnd ? (length + 1) : length;
}

uint32_t string_from_uint32_bin(char *dest, uint32_t value, uint32_t isSetEnd)
{
    const uint32_t length = 32;

    for(uint32_t i = 0; i < length; i++)
        dest[i] = '0' + ((value >> (length - i - 1)) & 0x1);
    
    if(isSetEnd)
        dest[length] = '\0';
    
    return isSetEnd ? (length + 1) : length;
}

uint32_t string_from_int32(char *dest, int32_t value, uint32_t isSetEnd)
{
    uint32_t length = 0;

    if(value < 0)
    {
        value = -value;
        *dest = '-';
        length++;
    }

    length += string_from_uint32(dest + length, value, isSetEnd);
    return length;
}

uint32_t string_from_float(char *dest, float value, uint32_t isSetEnd)
{
    uint32_t length = 0;

    int intPart = (int)value;
    length += string_from_int32(dest, intPart, 0);
    
    *(dest + length) = '.';
    length++;

    float fractPart = value - intPart;

    if(fractPart < 0)
        fractPart = -fractPart;
    
    fractPart *= 1e6;
    length += string_from_uint32(dest + length, fractPart, isSetEnd);

    return length;
}
