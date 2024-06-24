#include <stdint.h>
#include "MyMath.h"

#define _pi 3.141593f

int MyMath_Round(float f)
{
    return math_round(f);
}

float MyMath_Sqrt(float f)
{
    if (f < 0) {
        return -1;
    }

    float epsilon = 0.01;
    float guess = f / 2.0;

    while ((guess * guess - f) > epsilon || (f - guess * guess) > epsilon) 
    {
        guess = (guess + f / guess) / 2.0;
    }

    return guess;
}

float MyMath_Clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    
    if (value > max)
        return max;
    
    return value;
}

static float MathSinCos(float x, uint32_t is_sin) 
{
    while (x > _pi) 
    {
        x -= 2 * _pi;
    }

    while (x < -_pi) 
    {
        x += 2 * _pi;
    }

    float term = x;
    float sum = x;
    int n = 1;

    for (int i = 1; i < 4; i++) 
    {
        term *= -x * x / (2 * n * (2 * n + is_sin ? 1 : -1));
        sum += term;
        n++;
    }

    return sum;
}

float MyMath_Sin(float x) 
{
    return MathSinCos(x, 1);
}

float MyMath_Cos(float x) 
{
    return MathSinCos(x, 0);
}