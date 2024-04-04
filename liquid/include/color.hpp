#ifndef LIQUID_COLOR_HPP
#define LIQUID_COLOR_HPP

namespace liquid {
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

    namespace detail {
        auto initializeColor() -> void;
        auto enableColor(Color foreground, Color background) -> void;
        auto disableColor(Color foreground, Color background) -> void;
    }
}

#endif
