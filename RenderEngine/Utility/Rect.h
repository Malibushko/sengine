#pragma once
#include <type_traits>
template<class T>
struct TRect
{
    static_assert(std::is_arithmetic_v<T>);

    T X;
    T Y;
    T Width;
    T Height;

    TRect() = default;

    TRect(T _X, T _Y, T _Width, T _Height)
        : X{_X}
        , Y{_Y}
        , Width{_Width}
        , Height{_Height}
    {
    }
};

using Rect = TRect<int>;
using RectF = TRect<float>;
