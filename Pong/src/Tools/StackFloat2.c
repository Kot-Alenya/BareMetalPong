#include <stdlib.h>
#include "StackFloat2.h"
#include "Float2.h"

StackFloat2* StackFloat2_Create(int capacity)
{
    StackFloat2 *s = (StackFloat2*)malloc(sizeof(StackFloat2));

    s->_data = (Float2*)malloc(capacity * sizeof(Float2));
    s->_capacity = capacity;
    s->_topElementIndex = -1;

    return s;
}

void StackFloat2_Clear(StackFloat2* s)
{
    s->_topElementIndex = -1;
}

int StackFloat2_Count(StackFloat2* s)
{
    return s->_topElementIndex + 1;
}

Float2 StackFloat2_Pop(StackFloat2 *s) 
{
    Float2 r = s->_data[s->_topElementIndex];
    s->_topElementIndex--;
    return r;
}

void StackFloat2_Push(StackFloat2 *s, Float2 item) 
{
    s->_topElementIndex++;
    s->_data[s->_topElementIndex] = item;
}

void StackFloat2_Free(StackFloat2 *s) 
{
    free(s->_data);
    free(s);
}