#include "Game.h"
#include "GameData.h"
#include "Platform.h"
#include "Float2.h"
#include "Ball.h"
#include "Keyboard.h"

static int IsKeyDown(keyboard_scancode_t key) 
{
    return keyboard_test_key(key) != 0;
} 

void Controller_Update(float deltaTime)
{    
    if (IsKeyDown(ESC))
        Game_Exit();

    Platform_ResetDirection(GameSessionData.LeftPlatform);
    Platform_ResetDirection(GameSessionData.RightPlatform);

    if (IsKeyDown(S))
        Platform_Move(GameSessionData.LeftPlatform, deltaTime, Float2_Up());
    if (IsKeyDown(W))
        Platform_Move(GameSessionData.LeftPlatform, deltaTime, Float2_Down());

    if (IsKeyDown(DOWN_ARROW))
        Platform_Move(GameSessionData.RightPlatform, deltaTime, Float2_Up());
    if (IsKeyDown(UP_ARROW))
        Platform_Move(GameSessionData.RightPlatform, deltaTime, Float2_Down());
    
    Ball_Move(GameSessionData.Ball, deltaTime);
}