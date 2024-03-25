#ifndef LIQUID_COLOR_HPP
#define LIQUID_COLOR_HPP

namespace Liquid {
    enum class Color {
        Black,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White,
    };

    namespace Internal {
        auto initializeColor() -> void;
        auto enableColor(Color foreground, Color background) -> void;
        auto disableColor(Color foreground, Color background) -> void;
    }
}

#endif
