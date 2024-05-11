using System.Numerics;
using PongSharp.Data;

namespace PongSharp.Models;

internal class Platform
{
    private readonly CollisionHandler _collisionHandler;
    private Vector2 _position;
    private readonly Vector2 _mapSize;
    private readonly Vector2 _size;
    private readonly float _velocity;

    public Platform(CollisionHandler collisionHandler, Vector2 position, Vector2 mapSize)
    {
        _collisionHandler = collisionHandler;
        _position = position;
        _mapSize = mapSize;
        _size = new Vector2(1, 7);
        _velocity = 20;
        Rectangle = new Rectangle(_position, _size);
    }

    public Rectangle Rectangle { get; private set; }

    public Vector2 Direction { get; private set; }

    public void Move(float deltaTime, Vector2 direction)
    {
        var newPosition = _position + direction * deltaTime * _velocity;
        var clampedPosition = Vector2.Clamp(newPosition, Vector2.Zero, _mapSize - _size);
        var newRectangle = new Rectangle(clampedPosition, _size);

        _position = clampedPosition;
        Rectangle = newRectangle;
        Direction = direction;
    }

    public void ResetDirection() => Direction = Vector2.Zero;
}