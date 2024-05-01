#include "include/component.hpp"
#include "include/app.hpp"
#include "include/macro.hpp"

#include <ncurses.h>

namespace liquid {
    auto Cursor(const Prop<int>& x, const Prop<int>& y) -> Element {
        return Element([=](int xOrigin, int yOrigin) {
            move(yOrigin + *y, xOrigin + *x);
        });
    }

    auto Group(const Prop<std::vector<Element>>& elements) -> Element {
        return Element(
            [=](int, int) {
                auto x = getcurx(stdscr);
                auto y = getcury(stdscr);

                for (const auto& element : *elements) {
                    element.render(x, y);
                }
            },
            {
                [=]() {
                    for (const auto& element : *elements) {
                        element.cleanup();
                    }
                },
            }
        );
    }

    auto Text(
        const Prop<std::string>& value,
        const Prop<Color>& foreground,
        const Prop<Color>& background
    ) -> Element {
        return Element([=](int, int) {
            detail::enableColor(*foreground, *background);
            printw("%s", value->c_str());
            detail::disableColor(*foreground, *background);
        });
    }
}
