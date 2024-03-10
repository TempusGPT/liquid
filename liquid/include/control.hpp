#ifndef LIQUID_CONTROL_HPP
#define LIQUID_CONTROL_HPP

#include "component.hpp"
#include "reactive.hpp"

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
    [=]() mutable {                                                               \
        auto elements = createSignal<std::vector<Element>>({});                   \
        auto items = [=]() mutable { return collection; };                        \
        const auto transform = [](decltype(items())::value_type item, const int index) { \
            return std::vector<Element>

#define ENDEACH                                                        \
    ;                                                                  \
    }                                                                  \
    ;                                                                  \
    createEffect([=]() mutable {                                       \
        auto newElements = std::vector<Element>({});                   \
        auto index = 0;                                                \
        for (const auto &item : items()) {                             \
            auto t = transform(item, index);                           \
            newElements.insert(newElements.end(), t.begin(), t.end()); \
            index += 1;                                                \
        }                                                              \
        elements.set(newElements);                                     \
    });                                                                \
    return Element {                                                   \
        [=]() mutable {                                                \
            for (const auto &element : elements()) {                   \
                element.render();                                      \
            }                                                          \
        }                                                              \
    };                                                                 \
    }                                                                  \
    ()

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
