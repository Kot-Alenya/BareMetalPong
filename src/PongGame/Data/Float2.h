#ifndef Float2_h
#define Float2_h

typedef struct Float2
{
    float X;
    float Y;
} Float2;

extern Float2 Float2_Add(Float2 a, Float2 b);
extern Float2 Float2_Sub(Float2 a, Float2 b);
extern Float2 Float2_MulFloat(Float2 a, float b);
extern Float2 Float2_MulFloat2(Float2 a, Float2 b);
extern Float2 Float2_DivFloat(Float2 a, float b);
extern Float2 Float2_DivFloat2(Float2 a, Float2 b);

extern Float2 Float2_Clamp(Float2 value, Float2 min, Float2 max);
extern float Float2_Length(Float2 value);
extern Float2 Float2_Normalize(Float2 value);
extern int Float2_Equals(Float2 a, Float2 b);

extern Float2 Float2_One();
extern Float2 Float2_Zero();
extern Float2 Float2_Up();
extern Float2 Float2_Down();

#endif