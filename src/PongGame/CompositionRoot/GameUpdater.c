#include "GameData.h"
#include "Screen.h"
#include "PlatformView.h"
#include "GameUpdater.h"
#include "Controller.h"
#include "GameUI.h"
#include "BallView.h"
#include "Timer.h"

static const int PhysicsUpdateTimeMs = 30;
static const int GraphicsUpdateTimeMs = 15;
static const float PhysicsUpdateDeltaTime = (float)PhysicsUpdateTimeMs / 1000;

static int _isRuning;
static const int _timerIntervalMs = 15;
static int _physicsUpdateCounter = PhysicsUpdateTimeMs;
static int _graphicsUpdateCounter = GraphicsUpdateTimeMs;
    
static void PhysicsUpdate()
{
    Controller_Update(PhysicsUpdateDeltaTime);
}

static void GraphicsUpdate()
{
    GameUI_DrawProgress();
    BallView_Draw(*GameSessionData.Ball);
    PlatformView_Draw(*GameSessionData.LeftPlatform);
    PlatformView_Draw(*GameSessionData.RightPlatform);
    Screen_Update();
}

static void TimerCallback()
{
    if(_physicsUpdateCounter >= PhysicsUpdateTimeMs)
    {
        PhysicsUpdate();
        _physicsUpdateCounter = 0;
    }

    if(_graphicsUpdateCounter >= GraphicsUpdateTimeMs)
    {
        GraphicsUpdate();
        _graphicsUpdateCounter = 0;
    }

    _physicsUpdateCounter += _timerIntervalMs;
    _graphicsUpdateCounter += _timerIntervalMs;
}

void GameUpdater_Initialize()
{
    _isRuning = 1;

    timer_initialize(_timerIntervalMs, TimerCallback);
}

void GameUpdater_Dispose()
{
    _isRuning = 0;
}