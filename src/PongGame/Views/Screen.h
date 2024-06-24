#ifndef Screen_h
#define Screen_h

#include "RectangleF.h"
#include "PixelColor.h"
#include "Int2.h"

extern void Screen_Initialize();
extern void Screen_Update();
extern void Screen_DrawRectangle(RectangleF rect, PixelColor color);
extern void Screen_DrawNumber(Int2 position, int number);
extern void Screen_Dispose();

#endif