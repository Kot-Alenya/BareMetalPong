using System.Numerics;

namespace PongSharp.Data;

internal struct Angel(int degrees)
{
    private const float DegInRad = 57.2958f;
    private const int MinValue = 0;
    private const int MaxValue = 360;

    public int Degrees
    {
        get => degrees;
        set
        {
            degrees = value switch
            {
                > MaxValue => value - value / MaxValue * MaxValue,
                < MinValue => value + (value / MaxValue + 1) * MaxValue,
                _ => value
            };
        }
    }

    public Vector2 ToVector2() => new(MathF.Cos(degrees / DegInRad), -MathF.Sin(degrees / DegInRad));
}