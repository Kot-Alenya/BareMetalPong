#include <stdio.h>
#include <math.h>

int MyMath_Round(float f)
{
    if (f >= 0) 
        return (int)(f + 0.5);
    else 
        return (int)(f - 0.5);
}

float MyMath_Sqrt(float f)
{
    return sqrtf(f);
}

float MyMath_Clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    
    if (value > max)
        return max;
    
    return value;
}

float MyMath_Sin(float a)
{
    return sinf(a);
}

float MyMath_Cos(float a)
{
    return cosf(a);
}