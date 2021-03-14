#pragma once
#include <tbb/concurrent_vector.h>
#include <tbb/task_arena.h>
#include <tbb/task_group.h>

class RenderEngine
{
public:
    RenderEngine();

    void DrawLine(float _BeginX, float _BeginY, float _EndX, float _EndY);
    void ProcessEvents();

private:
    tbb::concurrent_vector<std::function<void()>> m_RenderCommands;
    tbb::task_arena                               m_TasksArena;
    tbb::task_group                               m_TaskGroup;
};
