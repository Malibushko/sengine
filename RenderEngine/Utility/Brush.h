#pragma once
#include <variant>
#include <optional>
#include "Color.h"

class Brush
{
public:
    Brush();
    Brush(Color _Color);

    std::optional<Color> GetColor() const;

private:
    enum class BrushStyle
    {
        UNDEFINED,
        COLOR,
    } m_BrushStyle;
    using brush_t = std::variant<std::monostate, Color>;

    brush_t m_Brush;
};
