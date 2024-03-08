#ifndef LIQUID_ELEMENT_HPP
#define LIQUID_ELEMENT_HPP

#include <functional>
#include <ncurses.h>
#include <string>
#include <vector>

template <typename T>
using Prop = std::function<T()>;
using Element = std::function<void()>;

Element fragment(const std::vector<Element> &elements) {
    return [=]() {
        for (auto &element : elements) {
            element();
        }
    };
}

Element text(const Prop<std::string> &value) {
    return [=]() {
        printw("%s", value().c_str());
    };
}

#endif
