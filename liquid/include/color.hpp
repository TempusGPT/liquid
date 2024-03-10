#ifndef LIQUID_COLOR_HPP
#define LIQUID_COLOR_HPP

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

namespace Liquid {
    void initializeColor();
    void enableColor(const Color foreground, const Color background);
    void disableColor(const Color foreground, const Color background);
}

#endif
