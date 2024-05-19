#include <windows.h>
#include <ConsoleKey.h>
#include "Game.h"
#include "GameData.h"
#include "Platform.h"
#include "Float2.h"
#include "Ball.h"

int IsKeyDown(ConsoleKey key) 
{
    return (GetAsyncKeyState((int)key) & (1 << 15)) != 0;
} 

void Controller_Update(float deltaTime)
{    
    if (IsKeyDown(ConsoleKey_Escape))
        Game_Exit();

    Platform_ResetDirection(GameSessionData.LeftPlatform);
    Platform_ResetDirection(GameSessionData.RightPlatform);

    if (IsKeyDown(ConsoleKey_S))
        Platform_Move(GameSessionData.LeftPlatform, deltaTime, Float2_Up());
    if (IsKeyDown(ConsoleKey_W))
        Platform_Move(GameSessionData.LeftPlatform, deltaTime, Float2_Down());

    if (IsKeyDown(ConsoleKey_DownArrow))
        Platform_Move(GameSessionData.RightPlatform, deltaTime, Float2_Up());
    if (IsKeyDown(ConsoleKey_UpArrow))
        Platform_Move(GameSessionData.RightPlatform, deltaTime, Float2_Down());
    
    Ball_Move(GameSessionData.Ball, deltaTime);
}