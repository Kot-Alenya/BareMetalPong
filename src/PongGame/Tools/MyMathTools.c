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

double Factorial(int n) 
{
    double result = 1.0;

    for (int i = 1; i <= n; i++) 
        result *= i;

    return result;
}

double Power(float base, int exp) 
{
    double result = 1.0;

    for (int i = 0; i < exp; i++) 
        result *= base;

    return result;
}

float sin_or_cos(float x, uint32_t is_sin) 
{
    double sum = 0.0;
    int n = 10; // Количество итераций (чем больше, тем точнее)

    for (int i = 0; i < n; i++) 
    {
        int sign = (i % 2 == 0) ? 1 : -1;
        double term = sign * (Power(x, 2 * i + is_sin) / Factorial(2 * i + is_sin));
        sum += term;
    }

    return sum;
}

float MyMath_Sin(float x) 
{
    return sin_or_cos(x, 1);
}

float MyMath_Cos(float x) 
{
    return sin_or_cos(x, 0);
}