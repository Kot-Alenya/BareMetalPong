#include "Float2.h"
#include "MyMath.h"

Float2 Float2_Add(Float2 a, Float2 b)
{
    Float2 r = {a.X + b.X, a.Y + b.Y};
    return r;
}

Float2 Float2_Sub(Float2 a, Float2 b)
{
    Float2 r = {a.X - b.X, a.Y - b.Y};
    return r;
}

Float2 Float2_MulFloat(Float2 a, float b)
{
    Float2 r = {a.X * b, a.Y * b};
    return r;
}

Float2 Float2_MulFloat2(Float2 a, Float2 b)
{
    Float2 r = {a.X * b.X, a.Y * b.Y};
    return r;
}

Float2 Float2_DivFloat(Float2 a, float b)
{
    Float2 r = {a.X / b, a.Y / b};
    return r;
}

Float2 Float2_DivFloat2(Float2 a, Float2 b)
{
    Float2 r = {a.X / b.X, a.Y / b.Y};
    return r;
}

Float2 Float2_Clamp(Float2 value, Float2 min, Float2 max)
{
    Float2 r = 
    {
        MyMath_Clamp(value.X, min.X, max.X), 
        MyMath_Clamp(value.Y, min.Y, max.Y)
    };
    return r;
}

float Dot(Float2 a, Float2 b)
{
    return (a.X * b.X) + (a.Y * b.Y);
}

float Float2_Length(Float2 value)
{
    float lengthSquared = Dot(value, value);
    return MyMath_Sqrt(lengthSquared);
}

Float2 Float2_Normalize(Float2 value)
{
    return Float2_DivFloat(value, Float2_Length(value));
}

int Float2_Equals(Float2 a, Float2 b)
{
    return a.X == b.X && a.Y == b.Y;
}

Float2 Float2_One()
{
    Float2 r = {1, 1};
    return r;
}

Float2 Float2_Zero()
{
    Float2 r = {0, 0};
    return r;
}

Float2 Float2_Up()
{
    Float2 r = {0, 1};
    return r;
}

Float2 Float2_Down()
{
    Float2 r = {0, -1};
    return r;
}