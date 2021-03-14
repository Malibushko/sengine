#include "Painter.h"
#include "Game.h"
#include "RenderEngine.h"
#include "Window.h"
Painter::Painter()
    : m_Brush{}
{
}

Painter::Painter(Brush _Brush)
    : m_Brush(_Brush)
{
}

void Painter::DrawRect(int _X, int _Y, int _Width, int _Height)
{
}

void Painter::DrawLine(int _BeginX, int _BeginY, int _EndX, int _EndY)
{
    auto& Game = Game::GetInstance();
    auto [Width, Height] = Game.GetActiveWindow()->GetSize();

    Game::GetInstance().GetRenderEngine()->DrawLine(float(_BeginX) / Width,
        float(_BeginY) / Height, float(_EndX) / Width, float(_EndY) / Height);
}
