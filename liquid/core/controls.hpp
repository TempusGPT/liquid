#ifndef LIQUID_CONTROLS_HPP
#define LIQUID_CONTROLS_HPP

#include "elements.hpp"

#define WHEN(condition) \
    [&]() { if (condition) { Liquid::execute({

#define THEN(condition) \
    });                 \
    }                   \
    else if (condition) \
    { Liquid::execute({

#define OTHERWISE \
    });           \
    }             \
    else          \
    { Liquid::execute({

#define EACH(items, item, index) \
    [&]() { auto index = -1; for (const auto &item : items) { index += 1; Liquid::execute({

#define END \
    });     \
    }       \
    }

#endif