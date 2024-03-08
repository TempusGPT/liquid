#ifndef LIQUID_ELEMENT_HPP
#define LIQUID_ELEMENT_HPP

#include <functional>
#include <initializer_list>
#include <ncurses.h>
#include <string>

#define FRAGMENT(elements...) [=]() mutable { Liquid::execute({elements}); }

using Element = std::function<void()>;

Element text(const std::string &value) {
    return [=]() {
        printw("%s", value.c_str());
    };
}

namespace Liquid {
    void execute(const std::initializer_list<Element> &elements) {
        for (const auto &element : elements) {
            if (element) {
                element();
            }
        }
    }
}

#endif
