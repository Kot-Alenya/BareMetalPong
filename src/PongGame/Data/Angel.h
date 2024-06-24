#ifndef Angel_h
#define Angel_h

#include "Float2.h"

typedef struct Angel
{
    int Degrees;

    int _degrees;
} Angel;

extern void Angel_Set(Angel* angel, int d);
extern Float2 Angel_ToFloat2(Angel* angel);

#endif