#include <stdint.h>
#include "KeyboardScancodes.h"

static char _numbers[] = {'1','2','3','4','5','6','7','8','9','0'};
static char _numbers_shift[] = {'!','@','#','$','%','^','&','*','(',')'};

static char _up_letter[] = {'q','w','e','r','t','y','u','i','o','p'};
static char _middle_letter[] = {'a','s','d','f','g','h','j','k','l'};
static char _down_letter[] = {'z','x','c','v','b','n','m'};

char keyboard_convert_scancode_to_ASCII(uint8_t key_code, uint32_t is_shift, uint32_t is_capslock)
{
    if(key_code > 0x1 && key_code < 0x0C)
    {
        if(is_shift)
            return _numbers_shift[key_code - 0x2];
        return _numbers[key_code - 0x2];
    }
    
    if(key_code == 0x0C)
    {
        if(is_shift)
            return '-';
        return '_';
    }
    
    if(key_code == 0x0D)
    {
        if(is_shift)
            return '+';
        return '=';
    }

    if(key_code > 0x0F && key_code < 0x1A)
    {
        if((is_shift && !is_capslock) || (is_capslock && !is_shift))
            return _up_letter[key_code - 0x10] - 32;
        return _up_letter[key_code - 0x10];
    }

    if(key_code == 0x1A)
    {
        if(is_shift)
            return '}';
        return '[';
    }
    
    if(key_code == 0x1B)
    {
        if(is_shift)
            return '}';
        return ']';
    }

    if(key_code > 0x1D && key_code < 0x27)
    {
        if((is_shift && !is_capslock) || (is_capslock && !is_shift))
            return _middle_letter[key_code - 0x1E] - 32;
        return _middle_letter[key_code - 0x1E];
    }

    if(key_code == 0x27)
    {
        if(is_shift)
            return ':';
        return ';';
    }
    
    if(key_code == 0x28)
    {
        if(is_shift)
            return '"';
        return '\'';
    }
    
    if(key_code == 0x29)
    {
        if(is_shift)
            return '~';
        return '`';
    }
    
    if(key_code == 0x2B)
    {
        if(is_shift)
            return '|';
        return '\\';
    }

    if(key_code > 0x2B && key_code < 0x33)
    {
        if((is_shift && !is_capslock) || (is_capslock && !is_shift))
            return _down_letter[key_code - 0x2C] - 32;
        return _down_letter[key_code - 0x2C];
    }

    if(key_code == 0x33)
    {
        if(is_shift)
            return '<';
        return ',';
    }

    if(key_code == 0x34)
    {
        if(is_shift)
            return '>';
        return '.';
    }

    if(key_code == 0x35)
    {
        if(is_shift)
            return '?';
        return '/';
    }

    if(key_code == 0x39)
        return ' ';

    return 0;
}