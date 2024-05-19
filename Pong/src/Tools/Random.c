#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Random_Initialize()
{
    srand(time(0));
}

int Random_Next(int min, int max)
{
    int r = min + rand() % (max - min);
    return r;
}