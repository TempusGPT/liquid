#ifndef LIQUID_CONTROL_HPP
#define LIQUID_CONTROL_HPP

#include "element.hpp"

#define FOR(collection, item, index) \
    [&]()                             \
    {                                 \
        auto index = -1;              \
        for (const auto &item : collection) \
        {                             \
            index += 1;               \
            Liquid::execute({

#define IF(condition) \
    [&]()               \
    {                   \
    if (condition)      \
    {                   \
    Liquid::execute({

#define ELIF(condition) \
    });                 \
    }                   \
    else if (condition) \
    {                   \
    Liquid::execute({

#define ELSE \
    });           \
    }             \
    else          \
    {             \
    Liquid::execute({

#define END \
    });     \
    }       \
    }

#endif