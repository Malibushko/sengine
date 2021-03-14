#pragma once
#include <atomic>
#include <memory>
#include <signals.hpp>
#include <thread>

class Window;
class RenderEngine;

class Game
{
public:
    fteng::signal<void()>      OnShutdown;
    fteng::signal<void()>      OnStart;
    fteng::signal<void(float)> OnGameTick;

public:
    static Game& GetInstance();

    bool    Init();
    Window* GetActiveWindow() const;
    void    SetActiveWindow(Window* _Window);

public:
    void Start();
    void Shutdown();

protected:
    Game();
    ~Game();

    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;

private:
    std::atomic<bool>       m_Stop = false;
    std::thread             m_WorkerThread;
    std::unique_ptr<Window> m_Window;
};
