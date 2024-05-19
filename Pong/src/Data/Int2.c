#include "Int2.h"
#include "Float2.h"
#include "MyMath.h"

Int2 Int2_FromFloat2(Float2 v)
{
    Int2 i = {MyMath_Round(v.X), MyMath_Round(v.Y)};
    return i;
}

Float2 Int2_ToFloat2(Int2 i)
{
    Float2 v = {i.X, i.Y};
    return v;
}