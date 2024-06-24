#include "Screen.h"
#include "GameData.h"
#include "Ball.h"
#include "RectangleF.h"
#include "Float2.h"
#include "MyMathTools.h"
#include "StackFloat2.h"

const int MaxTailLength = 3;
StackFloat2* _tailBuffer;

void BallView_Initialize()
{
    _tailBuffer = StackFloat2_Create(MaxTailLength);
}

void BallView_Dispose()
{
    StackFloat2_Free(_tailBuffer);
}

static void SetTailBuffer(Ball ball)
{
    float stepSize = 1;
    Float2 step = Float2_MulFloat(ball.Direction, -stepSize);
    float tailLength = MyMath_Clamp(ball.WayDistance / stepSize / 2, 0, MaxTailLength);
    Float2 previousPosition = ball.Rectangle.LeftUpCornerPosition;

    StackFloat2_Clear(_tailBuffer);

    for (int i = 0; i < tailLength; i++)
    {
        Float2 newPosition = Float2_Add(previousPosition, step);
        Float2 roundedPosition = {MyMath_Round(newPosition.X), MyMath_Round(newPosition.Y)};
        Float2 clampedPosition = Float2_Clamp(roundedPosition, 
            Float2_Sub(previousPosition, Float2_One()),
            Float2_Add(previousPosition, Float2_One()));

        Float2 resultPosition = Float2_Clamp(clampedPosition, Float2_Zero(), 
            Float2_Sub(Int2_ToFloat2(GameStaticData.ScreenSize), Float2_One()));
        
        StackFloat2_Push(_tailBuffer, resultPosition);
        previousPosition = clampedPosition;
    }
}

static void DrawTail(Ball ball)
{
    SetTailBuffer(ball);
    int tailLength = StackFloat2_Count(_tailBuffer);

    for (int i = 0; i < tailLength; i++)
    {
        Float2 position = StackFloat2_Pop(_tailBuffer);
        RectangleF rect = {position, ball.Rectangle.Size};

        if (i == 2)
            Screen_DrawRectangle(rect, PixelColor_Gray1);
        else if (i == 1)
            Screen_DrawRectangle(rect, PixelColor_Gray2);
        else if (i == 0)
            Screen_DrawRectangle(rect, PixelColor_Gray3);
    }
}

static void DrawHead(RectangleF rect) 
{
    Screen_DrawRectangle(rect, PixelColor_White);
}

void BallView_Draw(Ball ball)
{
    if (ball.WayDistance != 0)
        DrawTail(ball);

    DrawHead(ball.Rectangle);
}