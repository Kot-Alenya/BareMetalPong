using System.Numerics;
using System.Runtime.InteropServices;
using PongSharp.CompositionRoot;
using PongSharp.Models;

namespace PongSharp.Controllers;

internal class Controller(Platform leftPlatform, Platform rightPlatform, Ball ball, Game game)
{
    public void Update(float deltaTime)
    {
        if (IsKeyDown(ConsoleKey.Escape))
            game.Exit();

        leftPlatform.ResetDirection();
        rightPlatform.ResetDirection();

        if (IsKeyDown(ConsoleKey.S))
            leftPlatform.Move(deltaTime, Vector2.UnitY);
        if (IsKeyDown(ConsoleKey.W))
            leftPlatform.Move(deltaTime, -Vector2.UnitY);

        if (IsKeyDown(ConsoleKey.DownArrow))
            rightPlatform.Move(deltaTime, Vector2.UnitY);
        if (IsKeyDown(ConsoleKey.UpArrow))
            rightPlatform.Move(deltaTime, -Vector2.UnitY);

        ball.Move(deltaTime);
    }

    private bool IsKeyDown(ConsoleKey key) => (GetAsyncKeyState((int)key) & (1 << 15)) != 0;

    [DllImport("user32.dll")]
    private static extern short GetAsyncKeyState(int vKey);
}