#include <cstdint>

struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    Color() = default;
    Color(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A)
        : r{_R}
        , g{_G}
        , b{_B}
        , a{_A}
    {
    }
    Color(uint32_t _RGBA)
    {
        r = (_RGBA >> 24) & 0xF;
        g = (_RGBA >> 16) & 0xFF;
        b = (_RGBA >> 8) & 0XFF;
        a = (_RGBA & 0XFF);
    }
};
