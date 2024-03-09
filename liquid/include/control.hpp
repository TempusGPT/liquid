#ifndef LIQUID_CONTROL_HPP
#define LIQUID_CONTROL_HPP

#include "component.hpp"

#include <initializer_list>
#include <vector>

#define WHEN(condition) \
    Liquid::When({              \
        { FN condition ENDFN, FN std::vector<Element>

#define OR(condition) \
    ENDFN             \
    }                 \
    , {               \
        FN condition ENDFN, FN std::vector<Element>

#define OTHERWISE \
    ENDFN         \
    }             \
    , {           \
        true, FN std::vector<Element>

#define END \
    ENDFN   \
    }       \
    } )

#define EACH(collection, item, index) \
    {                                 \
        [=]() mutable {                     \
        auto index = 0;                     \
        for (const auto &item : collection) \
            index = Liquid::renderAndIncreaseIndex(index,

namespace Liquid {
    void renderElements(const std::initializer_list<Element> &elements);
    int renderAndIncreaseIndex(const int index, const std::initializer_list<Element> &elements);

    struct WhenArg {
        const Prop<bool> condition;
        const Prop<std::vector<Element>> elements;
    };

    Element When(const std::vector<WhenArg> &whenArg);
}

#endif
