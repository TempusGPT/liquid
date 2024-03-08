#ifndef LIQUID_MACRO_HPP
#define LIQUID_MACRO_HPP

#include "element.hpp"

#define RETURN return [=]() mutable { Liquid::render(

#define FOR(collection, item, index) \
    [=]() mutable {                         \
        auto index = 0;                      \
        for (const auto &item : collection) \
            index = Liquid::renderAndIncreaseIndex(index,

#define IF(condition) \
    [=]() mutable {     \
    if (condition)      \
    Liquid::render(

#define ELIF(condition)   \
    );                  \
    else if (condition) \
    Liquid::render(

#define ELSE \
    );            \
    else          \
    Liquid::render(

#define END \
    );      \
    }

namespace Liquid {
    void render(const std::initializer_list<Element> &elements) {
        for (const auto &element : elements) {
            if (element) {
                element();
            }
        }
    }

    int renderAndIncreaseIndex(const int index, const std::initializer_list<Element> &elements) {
        render(elements);
        return index + 1;
    }
}

#endif