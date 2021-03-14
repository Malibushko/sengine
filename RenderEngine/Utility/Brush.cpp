#include "Brush.h"

Brush::Brush()
    : m_BrushStyle{BrushStyle::UNDEFINED}
{
}

Brush::Brush(Color _Color)
    : m_BrushStyle{BrushStyle::COLOR}
    , m_Brush{_Color}
{
}

std::optional<Color> Brush::GetColor() const
{
    if(m_BrushStyle == BrushStyle::COLOR)
        return std::get<Color>(m_Brush);
    return {};
}
