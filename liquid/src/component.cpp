#include "include/component.hpp"

#include <ncurses.h>

Element::Element() : renderer([]() {}) {}
Element::Element(const std::function<void()> &renderer) : renderer(renderer) {}

void Element::render() const {
    renderer();
}

Element fragment(const std::vector<Element> &elements) {
    return {
        [=]() {
            for (auto &element : elements) {
                element.render();
            }
        }
    };
}

Element text(const Prop<std::string> &value) {
    return {
        [=]() {
            printw("%s", value().c_str());
        }
    };
}
