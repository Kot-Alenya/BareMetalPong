using System.Numerics;

namespace PongSharp.Data;

internal struct Rectangle(Vector2 leftUpCornerPosition, Vector2 size)
{
    public Vector2 LeftUpCornerPosition = leftUpCornerPosition;
    public Vector2 Size = size;

    public float Up => LeftUpCornerPosition.Y;

    public float Down => LeftUpCornerPosition.Y + Size.Y;

    public float Left => LeftUpCornerPosition.X;

    public double Right => LeftUpCornerPosition.X + Size.X;

    public bool IsCollisionWith(Rectangle rectangle)
    {
        return rectangle.LeftUpCornerPosition.X < LeftUpCornerPosition.X + Size.X &&
               LeftUpCornerPosition.X < rectangle.LeftUpCornerPosition.X + rectangle.Size.X &&
               rectangle.LeftUpCornerPosition.Y < LeftUpCornerPosition.Y + Size.Y &&
               LeftUpCornerPosition.Y < rectangle.LeftUpCornerPosition.Y + rectangle.Size.Y;
    }
}