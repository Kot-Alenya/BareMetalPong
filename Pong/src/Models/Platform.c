#include <stdlib.h>
#include "Float2.h"
#include "RectangleF.h"
#include "Platform.h"
#include "Int2.h"
#include "CollisionHandler.h"
#include "GameData.h"

Platform* Platform_Create(Float2 position)
{
    Platform* result = calloc(1, sizeof(Platform));
    Float2 size = {1, 7};
    RectangleF rect = {position, size};

    result->_position = position;
    result->_size = size;
    result->_velocity = 20;
    result->Rectangle = rect;

    return result;
}

void Platform_Dispose(Platform* platform)
{
    free(platform);
}

void Platform_Move(Platform* platform, float deltaTime, Float2 direction)
{
    Float2 newPosition = Float2_Add(platform->_position, Float2_MulFloat(direction, deltaTime * platform->_velocity));
    Float2 clampedPosition = Float2_Clamp(newPosition, Float2_Zero(), Float2_Sub(GameStaticData.MapSize, platform->_size));
    RectangleF newRectangle = {clampedPosition, platform->_size};

    platform->_position = clampedPosition;
    platform->Rectangle = newRectangle;
    platform->Direction = direction;
}

void Platform_ResetDirection(Platform* platform)
{
    platform->Direction = Float2_Zero();
}