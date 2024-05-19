#include <windows.h>
#include "GameData.h"
#include "Screen.h"
#include "PlatformView.h"
#include "GameUpdater.h"
#include "Controller.h"
#include "Timer.h"
#include "GameUI.h"
#include "BallView.h"

const int PhysicsUpdateTimeMs = 30;
const int GraphicsUpdateTimeMs = 15;
const float PhysicsUpdateDeltaTime = (float)PhysicsUpdateTimeMs / 1000;

int _isRuning;

void PhysicsUpdate()
{
    Controller_Update(PhysicsUpdateDeltaTime);
}

void GraphicsUpdate()
{
    GameUI_DrawProgress();
    BallView_Draw(*GameSessionData.Ball);
    PlatformView_Draw(*GameSessionData.LeftPlatform);
    PlatformView_Draw(*GameSessionData.RightPlatform);
    Screen_Update();
}

void GameUpdater_Initialize()
{
    int physicsUpdateCounter = PhysicsUpdateTimeMs;
    int graphicsUpdateCounter = GraphicsUpdateTimeMs;
    int intervalMs = 15;

    _isRuning = 1;
    ULONG res = {intervalMs * 10000};
    LARGE_INTEGER interval = {QuadPart: -intervalMs * 10000};
    NtSetTimerResolution(res, TRUE, &res);

    while (_isRuning)
    {
        if(physicsUpdateCounter >= PhysicsUpdateTimeMs)
        {
            PhysicsUpdate();
            physicsUpdateCounter = 0;
        }

        if(graphicsUpdateCounter >= GraphicsUpdateTimeMs)
        {
            GraphicsUpdate();
            graphicsUpdateCounter = 0;
        }

        NtDelayExecution(FALSE, &interval);

        physicsUpdateCounter += intervalMs;
        graphicsUpdateCounter += intervalMs;
    }
}

void GameUpdater_Dispose()
{
    _isRuning = 0;
}