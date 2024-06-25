#include "Angel.h"
#include "Float2.h"
#include "MyMathTools.h"

const float DegInRad = 57.2958f;
const int MinValue = 0;
const int MaxValue = 360;

void Angel_Set(Angel* angel, int value)
{
    if(value > MaxValue)
        angel->_degrees = value - (value / MaxValue) * MaxValue;
    else if(value < MinValue)
        angel->_degrees = value + (value / MaxValue + 1) * MaxValue;
    else
        angel->_degrees = value;
    
    angel->Degrees = angel->_degrees;
}

Float2 Angel_ToFloat2(Angel* angel)
{
    Float2 r = {MyMath_Cos(angel->_degrees / DegInRad), -MyMath_Sin(angel->_degrees / DegInRad)};
    return r;
}
