#include "include/component.hpp"

#include <ncurses.h>

namespace Liquid {
    namespace Internal {
        void onCleanup(const std::function<void()> &callback) {
            Element::lastMounted->cleanupCallbacks.push_back(callback);
        }
    }

    Element::Element(const std::function<void()> &renderCallback) : renderCallback(renderCallback) {
        lastMounted = this;
    }

    void Element::render() const {
        renderCallback();
    }

    void Element::cleanup() const {
        for (const auto &callback : cleanupCallbacks) {
            callback();
        }
    }

    Element *Element::lastMounted = nullptr;

    Element Div(const std::vector<Element> &elements) {
        return Element([=]() {
            for (auto &element : elements) {
                element.render();
            }
        });
    }

    Element Text(
        const Prop<std::string> &value,
        const Prop<Color> &foreground,
        const Prop<Color> &background
    ) {
        return Element([=]() {
            Internal::enableColor(foreground(), background());
            printw("%s", value().c_str());
            Internal::disableColor(foreground(), background());
        });
    }
}
