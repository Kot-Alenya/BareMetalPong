using PongSharp.Data;

namespace PongSharp.CompositionRoot;

internal class Game
{
    private readonly GameFactory _factory;

    public Game()
    {
        var staticData = new GameStaticData();
        var progress = new GameProgress();
        _factory = new GameFactory(staticData, progress, this);
    }

    public void Start() => _factory.Create();

    public void Restart()
    {
        _factory.Dispose();
        Start();
    }

    public void Exit() => Environment.Exit(0);
}