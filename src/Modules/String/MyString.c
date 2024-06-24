#include <stdarg.h>
#include <stdint.h>
#include "MyString.h"
#include "MyMath.h"
#include "MyError.h"

static uint32_t concat(char* dest, char* s)
{
    uint32_t length = 0;

    for (uint32_t i = 0; s[i] != '\0'; i++)
    {
        *(dest + i) = s[i];
        length++;
    }
    
    return length;
}

uint32_t string_build(char* dest, uint32_t isSetEnd, char* format, ...)
{
    uint32_t length = 0;
    va_list args;
    va_start(args, format);

    for(uint32_t i = 0; format[i] != '\0'; i++)
    {
        if(format[i] != '%')
        {
            *(dest + length) = format[i];
            length++;
            continue;
        }

        if(format[i + 1] == '%')
        {
            *(dest + length) = '%';
            length++;
        }
        else if(format[i + 1] == 's')
        {
            char* s = va_arg(args, char*);
            length += concat(dest + length, s);
        }
        else if(format[i + 1] == 'd')
        {
            uint32_t d = va_arg(args, uint32_t);
            length += string_from_uint32(dest + length, d, 0);
        }
        else if(format[i + 1] == 'h')
        {
            uint32_t h = va_arg(args, uint32_t);
            length += string_from_uint32_hex(dest + length, h, 0); 
        }
        else if(format[i + 1] == 'c')
        {
            uint32_t c = va_arg(args, uint32_t);
            *(dest + length) = (char)c;
            length++; 
        }
        else if(format[i + 1] == 'b')
        {
            uint32_t b = va_arg(args, uint32_t);
            length += string_from_uint32_bin(dest + length, b, 0); 
        }
        else if(format[i + 1] == 'f')
        {
            float f = va_arg(args, double);
            length += string_from_float(dest + length, f, 0); 
        }
        else
        {
            string_build(monitor_get_common_buffer(), 1, "string_build: unrecognized key: %%%c", format[i + 1]);
            error_throw(monitor_get_common_buffer());
        }
        
        i++;
    }

    va_end(args);

    if(isSetEnd)
        dest[length] = '\0';
    
    return isSetEnd ? length + 1 : length;
}
