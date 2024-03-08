#ifndef LIQUID_CONTROL_HPP
#define LIQUID_CONTROL_HPP

#include "element.hpp"

#define EACH(collection, item) \
    [=]() mutable {                         \
        for (const auto &item : collection) \
            Liquid::execute(

#define WHEN(condition) \
    [=]() mutable {     \
    if (condition)      \
    Liquid::execute(

#define OR(condition)   \
    );                  \
    else if (condition) \
    Liquid::execute(

#define OTHERWISE \
    );            \
    else          \
    Liquid::execute(

#define END \
    );      \
    }

#endif