#include "Game.h"

#include "RenderEngine.h"
#include "Utility/Common.h"
#include "Window.h"

Game& Game::GetInstance()
{
    static Game GameInstance;
    return GameInstance;
}

bool Game::Init()
{
    Window::Init();

    return true;
}

Game::Game()
{
    m_Window = nullptr;
}
Game::~Game()
{
    Shutdown();
}

void Game::Start()
{
    m_WorkerThread = std::thread([&]() {
        float LastTick = 0;
        float DeltaTime = 0;

        while(!m_Stop || m_Window->IsShouldClose())
        {
            m_Window->ProcessEvents();

            float CurrentTime = Common::GetTime();
            DeltaTime = CurrentTime - LastTick;
            LastTick = CurrentTime;

            OnGameTick(DeltaTime);
        }
    });
}

void Game::Shutdown()
{
    if(m_WorkerThread.joinable())
        m_WorkerThread.join();
}

Window* Game::GetActiveWindow() const
{
    return m_Window.get();
}

void Game::SetActiveWindow(Window* _Window)
{
    m_Window.reset(_Window);
    if(m_Window)
        m_Window->BecomeActive();
}
