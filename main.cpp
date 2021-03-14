#include "RenderEngine/Game.h"
#include "RenderEngine/Window.h"
#include "RenderEngine/Painter.h"
int main()
{
    auto& Game = Game::GetInstance();
    Game.Init();
    Painter painter;

    Window* mainWindow = new Window(800, 600, "Hello from Engine");

    Game.SetActiveWindow(mainWindow);
    Game.Start();
    return 0;
}
