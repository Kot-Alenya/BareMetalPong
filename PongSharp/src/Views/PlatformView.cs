using PongSharp.Data;
using PongSharp.Models;

namespace PongSharp.Views;

internal class PlatformView(Screen screen)
{
    public void DrawPlatform(Platform platform) => screen.DrawRectangle(platform.Rectangle, PixelColor.White);
}