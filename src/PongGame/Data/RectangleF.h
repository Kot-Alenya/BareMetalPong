#ifndef RectangleF_h
#define RectangleF_h

#include "Float2.h"

typedef struct RectangleF
{
    Float2 LeftUpCornerPosition;
    Float2 Size;
} RectangleF;

extern int RectangleF_IsCollisionWith(RectangleF this, RectangleF other);

#endif