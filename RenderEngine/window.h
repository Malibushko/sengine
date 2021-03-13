#pragma once
#include <signals.hpp>
#include <string_view>

#include "Traits/Identifiable.h"

class Window : public Identifiable
{
 public:
    friend class Game;

    using handler_t = struct GLFWwindow*;

 public:
    Window( int _Width, int _Height, std::string_view _Title );
    ~Window();

    bool IsValid() const;
    void Show( bool _IsVisible );

    void                        ProcessEvents() const;
    void                        BecomeActive() const;
    std::pair< size_t, size_t > GetSize() const;

 public:
    fteng::signal< void() >           OnClosed;
    fteng::signal< void( int, int ) > OnSizeChanged;
    fteng::signal< void( bool ) >     OnVisibilityChanged;
    fteng::signal< void() >           OnBecomeActive;

 public:
    static bool Init();

 private:
    handler_t GetRawHandler() const;

 private:
    size_t             m_Width;
    size_t             m_Height;
    struct GLFWwindow* m_WndHandler;
};
