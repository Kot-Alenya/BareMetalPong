#ifndef Int2_h
#define Int2_h

#include "Float2.h"

typedef struct Int2
{
    int X;
    int Y;
} Int2;

extern Int2 Int2_FromFloat2(Float2 v);
extern Float2 Int2_ToFloat2(Int2 i);

#endif