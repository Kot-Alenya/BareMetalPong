#include "GameData.h"
#include "Screen.h"
#include "Float2.h"
#include "Platform.h"
#include "GameUpdater.h"
#include "Ball.h"
#include "Random.h"
#include "BallView.h"

struct GameStaticData GameStaticData;
struct GameProgressData GameProgressData;
struct GameSessionData GameSessionData;

void GameFactory_CreateStaticData()
{
    Float2 platformOffset = {3, 10};
    Float2 mapSize = {80, 25};

    struct GameStaticData data = 
    {
        .MapSize = mapSize,
        .ScreenSize = {80, 25},

        .LeftPlatformStartPosition = platformOffset,
        .RightPlatformStartPosition = {mapSize.X - platformOffset.X - 1, platformOffset.Y}
    };

    GameStaticData = data;
}

void GameFactory_CreateProgressData()
{
    struct GameProgressData data = 
    {
        .LeftPlayerScore = 0,
        .RightPlayerScore = 0
    };

    GameProgressData = data;
}

static void CreateSessionData()
{
    struct GameSessionData data = 
    {
        .LeftPlatform = Platform_Create(GameStaticData.LeftPlatformStartPosition),
        .RightPlatform = Platform_Create(GameStaticData.RightPlatformStartPosition),
        .Ball = Ball_Create()
    };

    GameSessionData = data;
}

void GameFactory_Create()
{
    Random_Initialize();
    CreateSessionData();
    Screen_Initialize();
    BallView_Initialize();
    //GameUpdater_Initialize();
}

void GameFactory_Dispose()
{
    Screen_Dispose();
    GameUpdater_Dispose();
    BallView_Dispose();
    Platform_Dispose(GameSessionData.LeftPlatform);
    Platform_Dispose(GameSessionData.RightPlatform);
    Ball_Dispose(GameSessionData.Ball);
}