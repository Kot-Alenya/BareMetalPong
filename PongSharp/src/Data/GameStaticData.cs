using System.Numerics;

namespace PongSharp.Data;

internal class GameStaticData
{
    public readonly Vector2 MapSize;
    public readonly Int2 ScreenSize;

    public readonly Vector2 LeftPlatformStartPosition;
    public readonly Vector2 RightPlatformStartPosition;

    public GameStaticData()
    {
        MapSize = new Vector2(80, 25);
        ScreenSize = new Int2(80, 25);

        var platformOffset = new Vector2(3, 10);
        LeftPlatformStartPosition = platformOffset;
        RightPlatformStartPosition = platformOffset with { X = MapSize.X - platformOffset.X - 1};
    }
}