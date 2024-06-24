#include <stdint.h>

#define _MULTIPLIER 1664525
#define _INCREMENT 1013904223
#define _MODULUS 4294967296 // 2^32

static uint32_t _seed = 18723628; //TODO: system sturtup time value!

static uint32_t lcg_random() 
{
    _seed = (_MULTIPLIER * _seed + _INCREMENT) % _MODULUS;
    return _seed;
}

void Random_Initialize()
{
    //srand(time(0));
}

int Random_Next(int min, int max)
{
    int r = min + lcg_random() % (max - min);
    return r;
}