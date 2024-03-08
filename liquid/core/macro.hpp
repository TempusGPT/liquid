#ifndef LIQUID_MACRO_HPP
#define LIQUID_MACRO_HPP

#include "element.hpp"

#define FN \
    {      \
        [=]() mutable { return (

#define EACH(collection, item, index) \
    {                                 \
        [=]() mutable {                         \
            auto index = 0;                      \
            for (const auto &item : collection) \
                index = Liquid::renderAndIncreaseIndex(index,

#define WHEN(condition) \
    {                   \
        [=]() mutable {     \
    if (condition)      \
    Liquid::render(

#define OR(condition)   \
    );                  \
    else if (condition) \
    Liquid::render(

#define OTHERWISE \
    );            \
    else          \
    Liquid::render(

#define X \
    );    \
    }     \
    }

namespace Liquid {
    void render(const std::initializer_list<Element> &elements) {
        for (const auto &element : elements) {
            element();
        }
    }

    int renderAndIncreaseIndex(const int index, const std::initializer_list<Element> &elements) {
        render(elements);
        return index + 1;
    }
}

#endif