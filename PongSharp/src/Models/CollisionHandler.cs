using System.Numerics;
using PongSharp.Data;

namespace PongSharp.Models;

internal class CollisionHandler(Vector2 mapSize)
{
    private Platform _rightPlatform;
    private Platform _leftPlatform;

    public void Initialize(Platform leftPlatform, Platform rightPlatform)
    {
        _leftPlatform = leftPlatform;
        _rightPlatform = rightPlatform;
    }

    public bool IsCollisionWithMapUp(Rectangle rect) => rect.Up < 0;

    public bool IsCollisionWithMapDown(Rectangle rect) => rect.Down > mapSize.Y;

    public bool IsCollisionWithMapLeft(Rectangle rect) => rect.Left < 0;

    public bool IsCollisionWithMapRight(Rectangle rect) => rect.Right > mapSize.X;

    public bool IsCollisionWithLeftPlatform(Rectangle rectangle) => 
        _leftPlatform.Rectangle.IsCollisionWith(rectangle);

    public bool IsCollisionWithRightPlatform(Rectangle rectangle) =>
        _rightPlatform.Rectangle.IsCollisionWith(rectangle);
}