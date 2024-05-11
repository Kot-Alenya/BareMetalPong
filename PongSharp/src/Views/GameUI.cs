using PongSharp.Data;

namespace PongSharp.Views;

internal class GameUI(Screen screen, Int2 screenSize)
{
    public void DrawProgress(GameProgress gameProgress)
    {
        var scoreYPosition = 2;
        var scoreXOffset = 3;
        var screenHalfWidth = screenSize.X / 2;

        screen.DrawNumber(new Int2(screenHalfWidth - scoreXOffset, scoreYPosition), gameProgress.LeftPlayerScore);
        screen.DrawNumber(new Int2(screenHalfWidth + scoreXOffset, scoreYPosition), gameProgress.RightPlayerScore);
    }
}