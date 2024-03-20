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
        void initializeColor();
        void enableColor(Color foreground, Color background);
        void disableColor(Color foreground, Color background);
    }
}

#endif
