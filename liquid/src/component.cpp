#include "include/component.hpp"
#include "include/app.hpp"
#include "include/macro.hpp"

#include <ncurses.h>

namespace Liquid {
    auto Goto(const Prop<int>& x, const Prop<int>& y) -> Element {
        return Element([=](int xOrigin, int yOrigin) {
            move(yOrigin + y(), xOrigin + x());
        });
    }

    auto Group(const Prop<std::vector<Element>>& elements) -> Element {
        return Element(
            [=](int, int) {
                auto x = getcurx(stdscr);
                auto y = getcury(stdscr);

                for (const auto& element : elements()) {
                    element.render(x, y);
                }
            },
            {
                [=]() {
                    for (const auto& element : elements()) {
                        element.cleanup();
                    }
                },
            }
        );
    }

    auto Route(
        const Prop<std::string>& path,
        const Prop<std::function<Element()>>& component
    ) -> Element {
        return WHEN(path() == Liquid::path()) {
            component()(),
        } END_WHEN;
    }

    auto Text(
        const Prop<std::string>& value,
        const Prop<Color>& foreground,
        const Prop<Color>& background
    ) -> Element {
        return Element([=](int, int) {
            Internal::enableColor(foreground(), background());
            printw("%s", value().c_str());
            Internal::disableColor(foreground(), background());
        });
    }
}
