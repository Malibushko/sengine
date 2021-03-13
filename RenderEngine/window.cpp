#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cassert>

#include "Game.h"

Window::Window( int _Width, int _Height, std::string_view _Title )
{
    m_WndHandler = glfwCreateWindow( _Width, _Height, _Title.data(), nullptr, nullptr );
    if( m_WndHandler ) {
        glfwSetFramebufferSizeCallback(
           m_WndHandler, []( GLFWwindow* _Window, int _Width, int _Height ) {
               glViewport( 0, 0, _Width, _Height );

               Game&   Instance = Game::GetInstance();
               Window* ActiveWindow = Instance.GetActiveWindow();

               if( ActiveWindow && ActiveWindow->GetRawHandler() == _Window ) {
                   ActiveWindow->m_Width = _Width;
                   ActiveWindow->m_Height = _Height;
                   ActiveWindow->OnSizeChanged( _Width, _Height );
               }
           } );
    }
}
Window::~Window()
{
    if( m_WndHandler )
        glfwDestroyWindow( m_WndHandler );
}
bool Window::IsValid() const
{
    return m_WndHandler;
}

void Window::Show( bool _IsVisible )
{
    assert( m_WndHandler != nullptr );

    if( _IsVisible )
        glfwShowWindow( m_WndHandler );
    else
        glfwHideWindow( m_WndHandler );

    OnVisibilityChanged( _IsVisible );
}

void Window::ProcessEvents() const
{
    assert( m_WndHandler != nullptr );

    glfwSwapBuffers( m_WndHandler );
    glfwPollEvents();
}

void Window::BecomeActive() const
{
    assert( m_WndHandler != nullptr );
    glfwMakeContextCurrent( m_WndHandler );
}

bool Window::Init()
{
    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    return gladLoadGLLoader( reinterpret_cast< GLADloadproc >( glfwGetProcAddress ) );
}

Window::handler_t Window::GetRawHandler() const
{
    return m_WndHandler;
}
