using PongSharp.Tools;

namespace PongSharp.CompositionRoot;

internal class GameUpdater
{
    private const int PhysicsUpdateTimeMs = 30;
    private const int GraphicsUpdateTimeMs = 15;

    private readonly TimerWithNtDelayExecution _physicsUpdateTimer = new();
    private readonly TimerWithNtDelayExecution _graphicsUpdateTimer = new();

    public void Initialize(Action<float> physicsUpdate, Action graphicsUpdate)
    {
        var physicsDeltaTime = (float)PhysicsUpdateTimeMs / 1000;

        _physicsUpdateTimer.Start(PhysicsUpdateTimeMs, () => physicsUpdate.Invoke(physicsDeltaTime));
        _graphicsUpdateTimer.Start(GraphicsUpdateTimeMs, graphicsUpdate);
    }

    public void Dispose()
    {
        _physicsUpdateTimer.Stop();
        _graphicsUpdateTimer.Stop();
    }
}