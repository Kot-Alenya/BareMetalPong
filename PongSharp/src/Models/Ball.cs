using System.Numerics;
using PongSharp.CompositionRoot;
using PongSharp.Data;

namespace PongSharp.Models;

internal class Ball(
    CollisionHandler collisionHandler,
    GameProgress gameProgress,
    Game game,
    Vector2 mapSize,
    Platform leftPlatform,
    Platform rightPlatform)
{
    private const float MinVelocity = 20;
    private const float MaxVelocity = 45;

    private readonly Random _random = new();
    private Vector2 _position;
    private Vector2 _size;
    private float _velocity;
    private Angel _direction;

    public Rectangle Rectangle { get; private set; }

    public Vector2 Direction { get; private set; }

    public float WayDistance { get; private set; }

    public void Initialize()
    {
        _position = mapSize / 2;
        _size = new Vector2(1, 1);
        _velocity = 20;
        Rectangle = new Rectangle(_size, _position);
        _direction = GetInitialBallDirection();
    }

    public void Move(float deltaTime)
    {
        var normalizeDirection = Vector2.Normalize(_direction.ToVector2());
        var offset = normalizeDirection * deltaTime * _velocity;
        var newPosition = _position + offset;
        var newRectangle = new Rectangle(newPosition, _size);

        if (TryOutside(newRectangle))
            return;

        Direction = normalizeDirection;
        IncreaseVelocity(deltaTime);

        if (TryUpDownFlip(newRectangle) || IsPlatformCollision(newRectangle))
        {
            SetPosition(Vector2.Clamp(newPosition, Vector2.Zero, mapSize - Vector2.One));
            WayDistance = 0;
            return;
        }

        SetPosition(newPosition);
        WayDistance += offset.Length();
    }

    private void IncreaseVelocity(float deltaTime)
    {
        var timeFromMinToMaxSec = 60;
        var velocityDelta = MaxVelocity - MinVelocity;

        _velocity = Math.Clamp(_velocity + velocityDelta * deltaTime / timeFromMinToMaxSec, MinVelocity, MaxVelocity);
    }

    private void SetPosition(Vector2 newPosition)
    {
        _position = newPosition;
        Rectangle = new Rectangle(newPosition, _size);
    }

    private Angel GetInitialBallDirection()
    {
        var maxSpread = 5;
        var randomSpread = _random.Next(-maxSpread, maxSpread);
        var side = _random.Next(0, 2); //0 - left, 1 - right
        var angel = new Angel(side == 0 ? 180 + randomSpread : randomSpread);

        return angel;
    }

    private bool IsPlatformCollision(Rectangle rectangle)
    {
        var maxSpread = 20;

        if (collisionHandler.IsCollisionWithLeftPlatform(rectangle))
        {
            FlipFromPlatform(leftPlatform, maxSpread, 0, 1);
            return true;
        }

        if (collisionHandler.IsCollisionWithRightPlatform(rectangle))
        {
            FlipFromPlatform(rightPlatform, maxSpread, 180, -1);
            return true;
        }

        return false;
    }

    private void FlipFromPlatform(Platform platform, int maxSpread, int rightLeftOffset, int upDownOffset)
    {
        if (platform.Direction == Vector2.UnitY)
            _direction.Degrees = upDownOffset * -_random.Next(0, maxSpread + 1);
        else if (platform.Direction == -Vector2.UnitY)
            _direction.Degrees = upDownOffset * _random.Next(0, maxSpread + 1);
        else
            _direction.Degrees = _random.Next(-maxSpread, maxSpread + 1);

        _direction.Degrees += rightLeftOffset;
    }

    private bool TryUpDownFlip(Rectangle rectangle)
    {
        if (collisionHandler.IsCollisionWithMapUp(rectangle) ||
            collisionHandler.IsCollisionWithMapDown(rectangle))
        {
            var offset = 50; //offset of the reflection angle. The bigger offset the bigger reflection 
            var spread = 20; //random variation of the angle relative to the offset. offset +/- spread between 0, 90

            _direction.Degrees = _direction.Degrees switch
            {
                //1 quarter to 4
                >= 0 and < 90 => 270 + offset + _random.Next(-spread, spread + 1),
                //2 quarter to 3
                >= 90 and < 180 => 270 - offset + _random.Next(-spread, spread + 1),
                //3 quarter to 2
                >= 180 and < 270 => 90 + offset + _random.Next(-spread, spread + 1),
                //4 quarter to 1
                >= 270 and <= 360 => 90 - offset + _random.Next(-spread, spread + 1),
                _ => _direction.Degrees
            };

            return true;
        }

        return false;
    }

    private bool TryOutside(Rectangle rectangle)
    {
        if (collisionHandler.IsCollisionWithMapLeft(rectangle))
        {
            gameProgress.IncreaseRightPlayerScore();
            game.Restart();
            return true;
        }

        if (collisionHandler.IsCollisionWithMapRight(rectangle))
        {
            gameProgress.IncreaseLeftPlayerScore();
            game.Restart();
            return true;
        }

        return false;
    }
}