#include "include/component.hpp"

#include <ncurses.h>

Element::Element(
    const std::function<void()> &onRender,
    const std::function<void()> &onMount,
    const std::function<void()> &onCleanup
) : onRender(onRender), onMount(onMount), onCleanup(onCleanup) {}

void Element::render() const {
    if (onRender) {
        onRender();
    }
}

void Element::mount() const {
    if (onMount) {
        onMount();
    }
}

void Element::cleanup() const {
    if (onCleanup) {
        onCleanup();
    }
}

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
        Liquid::enableColor(foreground(), background());
        printw("%s", value().c_str());
        Liquid::disableColor(foreground(), background());
    });
}
