#include "include/color.hpp"

#include <ncurses.h>

namespace Liquid {
    auto colorAttribute(Color foreground, Color background) -> short {
        auto lhs = static_cast<int>(foreground) * 10;
        auto rhs = static_cast<int>(background);
        return lhs + rhs;
    }

    namespace Internal {
        auto initializeColor() -> void {
            start_color();

            for (auto foreground = 0; foreground < 8; foreground++) {
                for (auto background = 0; background < 8; background++) {
                    auto attribute = colorAttribute(
                        static_cast<Color>(foreground),
                        static_cast<Color>(background)
                    );
                    init_pair(attribute, foreground, background);
                }
            }
        }

        auto enableColor(Color foreground, Color background) -> void {
            attron(COLOR_PAIR(colorAttribute(foreground, background)));
        }

        auto disableColor(Color foreground, Color background) -> void {
            attroff(COLOR_PAIR(colorAttribute(foreground, background)));
        }
    }
}
