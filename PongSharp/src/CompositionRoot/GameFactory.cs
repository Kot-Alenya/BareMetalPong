using PongSharp.Controllers;
using PongSharp.Data;
using PongSharp.Models;
using PongSharp.Views;

namespace PongSharp.CompositionRoot;

internal class GameFactory(GameStaticData data, GameProgress gameProgress, Game game)
{
    private Screen _screen;
    private BallView _ballView;
    private PlatformView _platformView;
    private CollisionHandler _collisionHandler;
    private Ball _ball;
    private Platform _leftPlatform;
    private Platform _rightPlatform;
    private Controller _controller;
    private GameUpdater _gameUpdater;
    private GameUI _gameUI;

    public void Create()
    {
        CreateViews();
        CreateModels();
        _controller = new Controller(_leftPlatform, _rightPlatform, _ball, game);
        _gameUpdater = new GameUpdater();
        _gameUI = new GameUI(_screen, data.ScreenSize);

        Initialize();
    }

    public void Dispose() => _gameUpdater.Dispose();

    private void CreateViews()
    {
        _screen = new Screen(data.ScreenSize, data.ScreenSize.ToVector2() / data.MapSize);
        _ballView = new BallView(_screen, data.ScreenSize);
        _platformView = new PlatformView(_screen);
    }

    private void CreateModels()
    {
        _collisionHandler = new CollisionHandler(data.MapSize);
        _leftPlatform = new Platform(_collisionHandler, data.LeftPlatformStartPosition, data.MapSize);
        _rightPlatform = new Platform(_collisionHandler, data.RightPlatformStartPosition, data.MapSize);
        _ball = new Ball(_collisionHandler, gameProgress, game, data.MapSize, _leftPlatform, _rightPlatform);
    }

    private void Initialize()
    {
        _screen.Initialize();
        _ball.Initialize();
        _collisionHandler.Initialize(_leftPlatform, _rightPlatform);
        _gameUpdater.Initialize(PhysicsUpdate, GraphicsUpdate);
    }

    private void PhysicsUpdate(float deltaTime) => _controller.Update(deltaTime);

    private void GraphicsUpdate()
    {
        _gameUI.DrawProgress(gameProgress);
        _ballView.DrawBall(_ball);
        _platformView.DrawPlatform(_leftPlatform);
        _platformView.DrawPlatform(_rightPlatform);
        _screen.Update();
    }
}