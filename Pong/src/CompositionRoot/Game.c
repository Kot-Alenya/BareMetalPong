#include <stdlib.h>
#include "GameData.h"
#include "GameFactory.h"

struct GameStaticData GameStaticData;
struct GameProgressData* GameProgressData;
struct GameSessionData GameSessionData;

void Game_Initialize()
{
    GameFactory_CreateStaticData();
    GameFactory_CreateProgressData();
}

void Game_Start()
{
    GameFactory_Create();
}

void Game_Restart()
{
    GameFactory_Dispose();
    Game_Start();
}

void Game_Exit()
{
    exit(0);
}
