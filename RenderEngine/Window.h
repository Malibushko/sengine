#pragma once
#include "Traits/Identifiable.h"
#include "Traits/Initable.h"

#include <signals.hpp>
#include <string_view>

#include "Utility/Color.h"

class Window
    : public Identifiable
    , public IInitable<Window>
{
public:
    friend class Game;

    using handler_t = struct GLFWwindow*;

public:
    Window(int _Width, int _Height, std::string_view _Title);
    ~Window();

    bool IsValid() const;
    bool IsShouldClose() const;
    void Clear(Color _Color = Color{255, 255, 255, 255});
    void Show(bool _IsVisible);
    void Close() const;

    void                      ProcessEvents() const;
    std::pair<size_t, size_t> GetSize() const;

public:
    fteng::signal<void()>         OnClosed;
    fteng::signal<void(int, int)> OnSizeChanged;
    fteng::signal<void(bool)>     OnVisibilityChanged;

public:
    static bool Init();

private:
    handler_t GetRawHandler() const;

private:
    size_t             m_Width;
    size_t             m_Height;
    struct GLFWwindow* m_WndHandler;
};
