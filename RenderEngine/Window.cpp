#include "Window.h"

#include "Game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cassert>

#include <atomic>
#include <mutex>

Window::Window(int _Width, int _Height, std::string_view _Title)
{
    static std::once_flag IsModuleInit;
    std::call_once(IsModuleInit, []() { Window::Init(); });

    m_WndHandler = glfwCreateWindow(_Width, _Height, _Title.data(), 0, 0);
    if(m_WndHandler)
    {
        glfwMakeContextCurrent(m_WndHandler);
        glfwSetFramebufferSizeCallback(
            m_WndHandler, [](GLFWwindow* _Window, int _Width, int _Height) {
                glViewport(0, 0, _Width, _Height);

                Game&   Instance = Game::GetInstance();
                Window* ActiveWindow = Instance.GetActiveWindow();

                if(ActiveWindow && ActiveWindow->GetRawHandler() == _Window)
                {
                    ActiveWindow->m_Width = _Width;
                    ActiveWindow->m_Height = _Height;
                    ActiveWindow->OnSizeChanged(_Width, _Height);
                }
            });
        gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress));
    }
}
Window::~Window()
{
    if(m_WndHandler)
        glfwDestroyWindow(m_WndHandler);
}
bool Window::IsValid() const
{
    return m_WndHandler;
}

bool Window::IsShouldClose() const
{
    assert(m_WndHandler != nullptr);
    return glfwWindowShouldClose(m_WndHandler);
}

void Window::Clear(Color _Color)
{
    Color Normalized = _Color.Normalize();
    glClearColor(Normalized.r, Normalized.g, Normalized.b, Normalized.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Show(bool _IsVisible)
{
    assert(m_WndHandler != nullptr);

    if(_IsVisible)
        glfwShowWindow(m_WndHandler);
    else
        glfwHideWindow(m_WndHandler);

    OnVisibilityChanged(_IsVisible);
}

void Window::Close() const
{
    glfwSetWindowShouldClose(m_WndHandler, GLFW_TRUE);
}

void Window::ProcessEvents() const
{
    assert(m_WndHandler != nullptr);

    glfwSwapBuffers(m_WndHandler);
    glfwPollEvents();
}

std::pair<size_t, size_t> Window::GetSize() const
{
    return {m_Width, m_Height};
}

bool Window::Init()
{
    bool Result = glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return Result == GLFW_TRUE;
}

Window::handler_t Window::GetRawHandler() const
{
    return m_WndHandler;
}
