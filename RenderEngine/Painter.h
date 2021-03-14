#pragma once
#include "Utility/Brush.h"
#include "Utility/Rect.h"

class Painter
{
public:
    Painter();
    Painter(Brush _Brush);

    void DrawRect(int _X, int _Y, int _Width, int _Height);

    template<class T>
    void DrawRect(TRect<T> _Rect)
    {
        DrawRect(_Rect.X, _Rect.Y, _Rect.Width, _Rect.Height);
    }

    void DrawLine(int _BeginX, int _BeginY, int _EndX, int _EndY);

private:
    Brush m_Brush;
};
