#include <stddef.h>
#include <stdint.h>

void *memset(void *dest, int value, size_t length) 
{
    uint8_t *ptr = (uint8_t *)dest;

    while (length--) 
    {
        *ptr = value;
        ptr++;
    }

    return dest;
}

void *memcpy(void *dest, const void *src, size_t count) 
{
    uint8_t *dPtr = dest;
    const uint8_t *sPtr = src;

    while (count--) 
    {
        *dPtr = *sPtr;
        dPtr++;
        sPtr++;
    }

    return dest;
}

void *memmove(void *dest, const void *src, size_t count) 
{
    if (dest == src)
        return dest;

    if (dest < src || (uint8_t *)dest >= ((uint8_t *)src + count)) 
        memcpy(dest, src, count);
    else 
    {
        uint8_t *dPtr = (uint8_t *)dest + count - 1;
        const uint8_t *sPtr = (const uint8_t *)src + count - 1;
        while (count--) 
        {
            *dPtr = *sPtr;
            dPtr--;
            sPtr--;
        }
    }

    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) 
{
    const uint8_t *p1 = s1; 
    const uint8_t *p2 = s2;;

    for (uint32_t i = 0; i < n; i++) 
    {
        if (p1[i] != p2[i]) 
            return p1[i] - p2[i];
    }

    return 0;
}

void memory_set(void *dest, uint8_t value, uint32_t byteLength)
{
    memset(dest, value, byteLength);
}

void memory_copy(void *dest, void *src, uint32_t byteLength) 
{
    memcpy(dest, src, byteLength);
}

uint32_t memory_compare(void *src1, void *src2, uint32_t length) 
{
    return memcmp(src1, src2, length) == 0;
}