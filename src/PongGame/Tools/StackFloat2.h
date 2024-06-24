#ifndef StackFloat2_h
#define StackFloat2_h

#include <stddef.h>
#include <Float2.h>

typedef struct StackFloat2
{
    Float2* _data;
    int _capacity;
    int _topElementIndex;
} StackFloat2;

extern StackFloat2* StackFloat2_Create(int capacity);
extern void StackFloat2_Clear(StackFloat2* s);
extern int StackFloat2_Count(StackFloat2* s);
extern Float2 StackFloat2_Pop(StackFloat2 *s);
extern void StackFloat2_Push(StackFloat2 *s, Float2 item);
extern void StackFloat2_Free(StackFloat2 *s);

#endif