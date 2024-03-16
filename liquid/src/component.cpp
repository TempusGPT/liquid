#include "include/component.hpp"

#include <ncurses.h>

namespace Liquid {
    namespace Internal {
        void onCleanup(const std::function<void()> &callback) {
            Element::lastMounted->cleanupCallbacks.push_back(callback);
        }
    }

    Element::Element(
        const std::function<void(int, int)> &renderCallback
    ) : renderCallback(renderCallback) {
        lastMounted = this;
    }

    void Element::render(int x, int y) const {
        renderCallback(x, y);
    }

    void Element::cleanup() const {
        for (const auto &callback : cleanupCallbacks) {
            callback();
        }
    }

    Element *Element::lastMounted = nullptr;

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
