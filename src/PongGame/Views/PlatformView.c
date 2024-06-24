#include "Platform.h"
#include "Screen.h"

void PlatformView_Draw(Platform platform)
{
    Screen_DrawRectangle(platform.Rectangle, PixelColor_White);
}