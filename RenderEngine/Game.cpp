#include "Game.h"

#include "RenderEngine.h"
#include "Utility/Common.h"
#include "Window.h"
#include <iostream>

Game& Game::GetInstance()
{
    static Game GameInstance;
    return GameInstance;
}

bool Game::Init()
{
    m_RenderEngine = std::make_unique<RenderEngine>();
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

        while(!m_Stop && !m_Window->IsShouldClose())
        {
            m_RenderEngine->ProcessEvents();

            m_Window->Clear({123, 123, 123, 255});
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

    if(m_Window)
        m_Window->Close();
}

Window* Game::GetActiveWindow() const
{
    return m_Window.get();
}

void Game::SetActiveWindow(Window* _Window)
{
    m_Window.reset(_Window);
}

RenderEngine* Game::GetRenderEngine() const
{
    return m_RenderEngine.get();
}
