#include "RectangleF.h"
#include "GameData.h"

int CollisionHandler_IsCollisionWithMapUp(RectangleF rect)
{
    return rect.LeftUpCornerPosition.Y < 0;
}

int CollisionHandler_IsCollisionWithMapDown(RectangleF rect) 
{
    return (rect.LeftUpCornerPosition.Y + rect.Size.Y) > GameStaticData.MapSize.Y;
} 

int CollisionHandler_IsCollisionWithMapLeft(RectangleF rect) 
{ 
    return rect.LeftUpCornerPosition.X < 0;
}

int CollisionHandler_IsCollisionWithMapRight(RectangleF rect) 
{ 
    return (rect.LeftUpCornerPosition.X + rect.Size.X) > GameStaticData.MapSize.X;
}

int CollisionHandler_IsCollisionWithLeftPlatform(RectangleF rect) 
{
    return RectangleF_IsCollisionWith(GameSessionData.LeftPlatform->Rectangle, rect);
}

int CollisionHandler_IsCollisionWithRightPlatform(RectangleF rect) 
{
    return RectangleF_IsCollisionWith(GameSessionData.RightPlatform->Rectangle, rect);
}