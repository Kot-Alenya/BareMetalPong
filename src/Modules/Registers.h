#ifndef _registers_h
#define _registers_h

#include <stdint.h>

typedef struct registers
{
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
} registers_t;

#endif