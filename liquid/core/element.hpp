#ifndef LIQUID_ELEMENT_HPP
#define LIQUID_ELEMENT_HPP

#include <functional>
#include <initializer_list>
#include <ncurses.h>
#include <string>

using Element = std::function<void()>;

Element text(const std::string &value) {
    return [=]() {
        printw("%s", value.c_str());
    };
}

#endif
