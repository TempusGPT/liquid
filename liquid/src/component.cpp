#include "include/component.hpp"

#include <ncurses.h>

Element::Element() : renderer([]() {}) {}
Element::Element(const std::function<void()> &renderer) : renderer(renderer) {}

void Element::render() const {
    if (renderer) {
        renderer();
    }
}

Element Div(const std::vector<Element> &elements) {
    return {
        [=]() {
            for (auto &element : elements) {
                element.render();
            }
        }
    };
}

Element Text(
    const Prop<std::string> &value,
    const Prop<Color> &foreground,
    const Prop<Color> &background
) {
    return {
        [=]() {
            Liquid::enableColor(foreground(), background());
            printw("%s", value().c_str());
            Liquid::disableColor(foreground(), background());
        }
    };
}
