#include <iostream>
#include "RenderEngine/Game.h"

int main()
{
    auto& Game = Game::GetInstance();
    Game.Init();

    Game.Start();

    return 0;
}
