#include "Game.h"
#include <GLFW/glfw3.h>

#include "Window.h"
#include "RenderEngine.h"

#include <iostream>

Game& Game::GetInstance()
{
    static Game GameInstance;
    return GameInstance;
}

bool Game::Init()
{
    Window::Init();

    m_Window = std::make_unique< Window >( 800, 600, "Hi Engine!" );

    return true;
}

Game::Game()
{
}
Game::~Game()
{
    Shutdown();
}

void Game::Start()
{
    std::cout << "Start" << std::endl;
    m_WorkerThread = std::thread( [&]() {
        std::cout << "End" << std::endl;
        float LastTick = 0;
        float DeltaTime = 0;

        m_Window->BecomeActive();
        while( !m_Stop ) {
            m_Window->ProcessEvents();

            float CurrentTime = glfwGetTime();
            DeltaTime = CurrentTime - LastTick;
            LastTick = CurrentTime;

            OnGameTick( DeltaTime );
        }
    } );
}

void Game::Shutdown()
{
    if( m_WorkerThread.joinable() )
        m_WorkerThread.join();
}

Window* Game::GetActiveWindow() const
{
    return m_Window.get();
}
