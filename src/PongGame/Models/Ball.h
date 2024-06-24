#ifndef Ball_h
#define Ball_h

#include "Float2.h"
#include "RectangleF.h"
#include "Angel.h"

typedef struct Ball
{
    RectangleF Rectangle;
    Float2 Direction;
    float WayDistance;

    Float2 _position;
    Float2 _size;
    float _velocity;
    Angel _direction;
} Ball;

extern Ball* Ball_Create();
extern void Ball_Dispose(Ball* ball);
extern void Ball_Move(Ball* ball, float deltaTime);

#endif