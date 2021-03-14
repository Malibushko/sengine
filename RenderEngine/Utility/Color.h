#pragma once
#include <cstdint>
template<class T>
struct TColor
{
    T r;
    T g;
    T b;
    T a;

    TColor() = default;
    TColor(T _R, T _G, T _B, T _A)
        : r{_R}
        , g{_G}
        , b{_B}
        , a{_A}
    {
    }
    template<class F, typename = std::enable_if_t<std::is_same_v<T,F> && std::is_integral_v<T>>>
    TColor(uint32_t _RGBA)
    {
        r = (_RGBA >> 24) & 0xF;
        g = (_RGBA >> 16) & 0xFF;
        b = (_RGBA >> 8) & 0XFF;
        a = (_RGBA & 0XFF);
    }

    TColor<float> Normalize() const {
        TColor<float> Normalized;
        Normalized.r = static_cast<float>(r) / 255;
        Normalized.g = static_cast<float>(g) / 255;
        Normalized.b = static_cast<float>(b) / 255;
        Normalized.a = static_cast<float>(a) / 255;
        return Normalized;
    }
};
using Color = TColor<unsigned char>;
using ColorF = TColor<float>;
