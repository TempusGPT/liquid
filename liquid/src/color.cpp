#include "include/color.hpp"

#include <ncurses.h>

short colorAttribute(const Color foreground, const Color background) {
    auto const lhs = static_cast<int>(foreground) * 10;
    auto const rhs = static_cast<int>(background);
    return lhs + rhs;
}

namespace Liquid {
    void initializeColor() {
        start_color();

        for (auto foreground = 0; foreground < 8; foreground++) {
            for (auto background = 0; background < 8; background++) {
                const auto attribute = colorAttribute(
                    static_cast<Color>(foreground),
                    static_cast<Color>(background)
                );
                init_pair(attribute, foreground, background);
            }
        }
    }

    void enableColor(const Color foreground, const Color background) {
        attron(COLOR_PAIR(colorAttribute(foreground, background)));
    }

    void disableColor(const Color foreground, const Color background) {
        attroff(COLOR_PAIR(colorAttribute(foreground, background)));
    }
}