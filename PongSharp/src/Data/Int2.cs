using System.Numerics;

namespace PongSharp.Data;

internal struct Int2(int x, int y)
{
    public int X = x;
    public int Y = y;

    public static Int2 FromVector2(Vector2 v) => new((int)MathF.Round(v.X), (int)MathF.Round(v.Y));

    public Vector2 ToVector2() => new(X, Y);
}