#include "include/component.hpp"
#include "include/macro.hpp"
#include "include/app.hpp"

#include <ncurses.h>

namespace Liquid {
    Element Goto(const Prop<int> &x, const Prop<int> &y) {
        return Element([=](int xOrigin, int yOrigin) {
            move(yOrigin + y(), xOrigin + x());
        });
    }

    Element Group(const Prop<std::vector<Element>> &elements) {
        return Element([=](int, int) {
            const auto x = getcurx(stdscr);
            const auto y = getcury(stdscr);

            for (auto &element : elements()) {
                element.render(x, y);
            }
        });
    }

    Element Route(const Prop<std::string> &path, const Prop<std::function<Element()>> &component) {
        return WHEN(path() == pathname()) {
            component()(),
        } END_WHEN;
    }

    Element Text(
        const Prop<std::string> &value,
        const Prop<Color> &foreground,
        const Prop<Color> &background
    ) {
        return Element([=](int, int) {
            Internal::enableColor(foreground(), background());
            printw("%s", value().c_str());
            Internal::disableColor(foreground(), background());
        });
    }
}
