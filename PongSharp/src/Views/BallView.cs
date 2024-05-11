using System.Numerics;
using PongSharp.Data;
using PongSharp.Models;

namespace PongSharp.Views;

internal class BallView(Screen screen, Int2 screenSize)
{
    private readonly Stack<Vector2> _tailBuffer = new();

    public void DrawBall(Ball ball)
    {
        if (ball.WayDistance != 0)
            DrawTail(ball);

        DrawHead(ball.Rectangle);
    }

    private void DrawHead(Rectangle rect) => screen.DrawRectangle(rect, PixelColor.White);

    private void DrawTail(Ball ball)
    {
        SetTailBuffer(ball);
        var tailLength = _tailBuffer.Count;

        for (var i = 0; i < tailLength; i++)
        {
            var position = _tailBuffer.Pop();
            var rect = ball.Rectangle with { LeftUpCornerPosition = position };

            if (i == 2)
                screen.DrawRectangle(rect, PixelColor.Gray1);
            else if (i == 1)
                screen.DrawRectangle(rect, PixelColor.Gray2);
            else if (i == 0)
                screen.DrawRectangle(rect, PixelColor.Gray3);
        }
    }

    private void SetTailBuffer(Ball ball)
    {
        var stepSize = 1f;
        var step = -ball.Direction * stepSize;
        var tailLength = Math.Clamp(ball.WayDistance / stepSize / 2, 0, 3);
        var previousPosition = ball.Rectangle.LeftUpCornerPosition;

        _tailBuffer.Clear();

        for (var i = 0; i < tailLength; i++)
        {
            var newPosition = previousPosition + step;
            var roundedPosition = new Vector2(MathF.Round(newPosition.X), MathF.Round(newPosition.Y));
            var clampedPosition = Vector2.Clamp(roundedPosition, previousPosition - Vector2.One,
                previousPosition + Vector2.One);
            var resultPosition = Vector2.Clamp(clampedPosition, Vector2.Zero, screenSize.ToVector2() - Vector2.One);
            
            _tailBuffer.Push(resultPosition);
            previousPosition = clampedPosition;
        }
    }

}