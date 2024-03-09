#ifndef LIQUID_MACRO_HPP
#define LIQUID_MACRO_HPP

#include "component.hpp"

#include <initializer_list>

#define FN \
    {      \
        [=]() mutable { \
        return (

#define EACH(collection, item, index) \
    {                                 \
        [=]() mutable {                     \
        auto index = 0;                     \
        for (const auto &item : collection) \
            index = Liquid::renderAndIncreaseIndex(index,

#define WHEN(condition) \
    {                   \
        [=]() mutable { \
        if (condition) Liquid::renderElements(

#define OR(condition) \
        );            \
        else if (condition) Liquid::renderElements(

#define OTHERWISE \
        );        \
        else Liquid::renderElements(

#define X  \
        ); \
    }      \
    }

namespace Liquid {
    void renderElements(const std::initializer_list<Element> &elements);
    int renderAndIncreaseIndex(const int index, const std::initializer_list<Element> &elements);
}

#endif
