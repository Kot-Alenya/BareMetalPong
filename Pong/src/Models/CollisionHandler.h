#ifndef CollisionHandler_h
#define CollisionHandler_h

#include "RectangleF.h"

extern int CollisionHandler_IsCollisionWithMapUp(RectangleF rect);
extern int CollisionHandler_IsCollisionWithMapDown(RectangleF rect);
extern int CollisionHandler_IsCollisionWithMapLeft(RectangleF rect);
extern int CollisionHandler_IsCollisionWithMapRight(RectangleF rect);
extern int CollisionHandler_IsCollisionWithLeftPlatform(RectangleF rect);
extern int CollisionHandler_IsCollisionWithRightPlatform(RectangleF rect);

#endif