#include "GameData.h"
#include "Screen.h"

void GameUI_DrawProgress()
{
    int scoreYPosition = 2;
    int scoreXOffset = 3;
    int screenHalfWidth = GameStaticData.ScreenSize.X / 2;
    Int2 leftScorePosition = {screenHalfWidth - scoreXOffset, scoreYPosition};
    Int2 rightScorePosition = {screenHalfWidth + scoreXOffset, scoreYPosition};

    Screen_DrawNumber(leftScorePosition, GameProgressData.LeftPlayerScore);
    Screen_DrawNumber(rightScorePosition, GameProgressData.RightPlayerScore);
}