#ifndef GameData_h
#define GameData_h

#include "Float2.h"
#include "Int2.h"
#include "Platform.h"
#include "Ball.h"

struct GameStaticData
{
    Float2 MapSize;
    Int2 ScreenSize;

    Float2 LeftPlatformStartPosition;
    Float2 RightPlatformStartPosition;
};

struct GameProgressData
{
    int LeftPlayerScore;
    int RightPlayerScore;
};

struct GameSessionData
{
    Platform* LeftPlatform;
    Platform* RightPlatform;
    Ball* Ball;
};

extern struct GameStaticData GameStaticData;
extern struct GameProgressData* GameProgressData;
extern struct GameSessionData GameSessionData;

#endif