#ifndef Platform_h
#define Platform_h

#include "RectangleF.h"
#include "Float2.h"

typedef struct Platform
{
    RectangleF Rectangle;
    Float2 Direction;

    Float2 _position;
    Float2 _size;
    float _velocity;
} Platform;

extern Platform* Platform_Create(Float2 position);
extern void Platform_Dispose(Platform* platform);
extern void Platform_Move(Platform* platform, float deltaTime, Float2 direction);
extern void Platform_ResetDirection(Platform* platform);

#endif