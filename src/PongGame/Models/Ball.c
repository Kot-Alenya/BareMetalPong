#include "Ball.h"
#include "Float2.h"
#include "GameData.h"
#include "Angel.h"
#include "Random.h"
#include "RectangleF.h"
#include "CollisionHandler.h"
#include "Game.h"
#include "MyMathTools.h"
#include "MyMemory.h"

const float MinVelocity = 20;
const float MaxVelocity = 45;

static Angel GetInitialBallDirection()
{
    int maxSpread = 5;
    int randomSpread = Random_Next(-maxSpread, maxSpread);
    int side = Random_Next(0, 2); //0 - left, 1 - right
    Angel angel;
    Angel_Set(&angel, side == 0 ? 180 + randomSpread : randomSpread);

    return angel;
}

Ball* Ball_Create()
{
    Ball* result = memory_allocate(sizeof(Ball));
    memory_set(result, 0, sizeof(Ball));
    Float2 size = Float2_One();
    Float2 position = Float2_DivFloat(GameStaticData.MapSize, 2);
    RectangleF rect = {position, size};

    result->_position = position;
    result->_size = size;
    result->_velocity = 20;
    result->_direction =  GetInitialBallDirection();
    result->Rectangle = rect;

    return result;
}

void Ball_Dispose(Ball* ball)
{
    memory_free(ball);
}

static int TryOutside(RectangleF rectangle)
{
    if (CollisionHandler_IsCollisionWithMapLeft(rectangle))
    {
        GameProgressData.RightPlayerScore++;
        Game_Restart();
        return 1;
    }

    if (CollisionHandler_IsCollisionWithMapRight(rectangle))
    {
        GameProgressData.LeftPlayerScore++;
        Game_Restart();
        return 1;
    }

    return 0;
}

static void IncreaseVelocity(Ball *ball, float deltaTime)
{
    int timeFromMinToMaxSec = 60;
    int velocityDelta = MaxVelocity - MinVelocity;

    ball->_velocity = MyMath_Clamp(ball->_velocity + velocityDelta * deltaTime / timeFromMinToMaxSec, MinVelocity, MaxVelocity);
}

static int TryUpDownFlip(Ball *ball, RectangleF rectangle)
{
    if (CollisionHandler_IsCollisionWithMapUp(rectangle) ||
        CollisionHandler_IsCollisionWithMapDown(rectangle))
    {
        int offset = 50; //offset of the reflection angle. The bigger offset the bigger reflection 
        int spread = 20; //random variation of the angle relative to the offset. offset +/- spread between 0, 90

        if (ball->_direction.Degrees >= 0 && ball->_direction.Degrees < 90)//1 quarter to 4
            Angel_Set(&ball->_direction, 270 + offset + Random_Next(-spread, spread + 1));

        else if (ball->_direction.Degrees >= 90 && ball->_direction.Degrees < 180) //2 quarter to 3
            Angel_Set(&ball->_direction, 270 - offset + Random_Next(-spread, spread + 1));

        else if (ball->_direction.Degrees >= 180 && ball->_direction.Degrees < 270) //3 quarter to 2
            Angel_Set(&ball->_direction, 90 + offset + Random_Next(-spread, spread + 1));

        else if (ball->_direction.Degrees >= 270 && ball->_direction.Degrees <= 360) //4 quarter to 1
            Angel_Set(&ball->_direction, 90 - offset + Random_Next(-spread, spread + 1));

        return 1;
    }

    return 0;
}

static void FlipFromPlatform(Ball *ball, Platform platform, int maxSpread, int rightLeftOffset, int upDownOffset)
{
    if (Float2_Equals(platform.Direction, Float2_Up()))
        Angel_Set(&ball->_direction, upDownOffset * -Random_Next(0, maxSpread + 1));
    else if (Float2_Equals(platform.Direction, Float2_Down()))
        Angel_Set(&ball->_direction, upDownOffset * Random_Next(0, maxSpread + 1));
    else
        Angel_Set(&ball->_direction, Random_Next(-maxSpread, maxSpread + 1));

    Angel_Set(&ball->_direction, ball->_direction.Degrees + rightLeftOffset);
}

static int IsPlatformCollision(Ball *ball, RectangleF rectangle)
{
    int maxSpread = 20;

    if (CollisionHandler_IsCollisionWithLeftPlatform(rectangle))
    {
        FlipFromPlatform(ball, *GameSessionData.LeftPlatform, maxSpread, 0, 1);
        return 1;
    }

    if (CollisionHandler_IsCollisionWithRightPlatform(rectangle))
    {
        FlipFromPlatform(ball, *GameSessionData.RightPlatform, maxSpread, 180, -1);
        return 1;
    }

    return 0;
}

static void SetPosition(Ball* ball, Float2 newPosition)
{
    RectangleF newRect = {newPosition, ball->_size};

    ball->_position = newPosition;
    ball->Rectangle = newRect;
}

void Ball_Move(Ball *ball, float deltaTime)
{
    Float2 normalizeDirection = Float2_Normalize(Angel_ToFloat2(&ball->_direction));
    Float2 offset = Float2_MulFloat(normalizeDirection, deltaTime * ball->_velocity);
    Float2 newPosition = Float2_Add(ball->_position, offset);
    RectangleF newRectangle = {newPosition, ball->_size};

    if (TryOutside(newRectangle))
            return;
    
    ball->Direction = normalizeDirection;
    IncreaseVelocity(ball, deltaTime);

    if (TryUpDownFlip(ball, newRectangle) || IsPlatformCollision(ball, newRectangle))
    {
        SetPosition(ball, Float2_Clamp(newPosition, Float2_Zero(), Float2_Sub(GameStaticData.MapSize, Float2_One())));
        ball->WayDistance = 0;
        return;
    }

    SetPosition(ball, newPosition);
    ball->WayDistance += Float2_Length(offset);
}