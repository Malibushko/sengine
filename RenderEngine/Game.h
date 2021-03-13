#pragma once
#include <memory>

#include <signals.hpp>
#include <thread>
#include <atomic>
#include "Utility/Singletone.h"

class Window;
class RenderEngine;

class Game
{
 public:
    fteng::signal< void() >        OnShutdown;
    fteng::signal< void() >        OnStart;
    fteng::signal< void( float ) > OnGameTick;

 public:
    static Game& GetInstance();

    bool    Init();
    Window* GetActiveWindow() const;

 protected:
    Game();
    ~Game();

    Game& operator=( const Game& ) = delete;
    Game& operator=( Game&& ) = delete;

 public:
    void Start();
    void Shutdown();

 private:
    std::atomic< bool >             m_Stop = false;
    std::thread                     m_WorkerThread;
    std::unique_ptr< Window >       m_Window = nullptr;
    std::unique_ptr< RenderEngine > m_RenderEngine = nullptr;
};
