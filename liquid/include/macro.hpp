// TODO: Migrate to C++17

#ifndef LIQUID_CONTROL_HPP
#define LIQUID_CONTROL_HPP

#include "component.hpp"
#include "reactivity.hpp"

#include <tuple>
#include <vector>

#define FN(expr) [=]() mutable { return expr; }

#define WHEN(condition) \
    [=]() mutable {                                                          \
        auto elements = createSignal<std::vector<Element>>({});              \
        createEffect([=]() mutable {                                         \
            for (const auto &element : untrack(elements)) element.cleanup(); \
            if (condition) return elements.set(

#define OR(condition) \
    );                \
    if (condition) return elements.set(

#define OTHERWISE \
    );            \
    return elements.set(

#define END_WHEN                                 \
    );                                           \
    elements.set({});                            \
    });                                          \
    return Element([=](int x, int y) mutable {   \
        for (const auto& element : elements()) { \
            element.render(x, y);                \
        }                                        \
    });                                          \
    }                                            \
    ()

#define EACH(items, item, index) \
    [=]() mutable {                                                                 \
        auto elements = createSignal<std::vector<Element>>({});                     \
        auto collection = [=]() mutable { return items; };                          \
        auto transform = [=](decltype(items)::value_type item, int index) mutable { \
            return std::vector<Element>

#define END_EACH                                                       \
    ;                                                                  \
    }                                                                  \
    ;                                                                  \
    createEffect([=]() mutable {                                       \
        auto newElements = std::vector<Element> {};                    \
        auto index = 0;                                                \
        for (const auto& item : collection()) {                        \
            const auto t = transform(item, index);                     \
            newElements.insert(newElements.end(), t.begin(), t.end()); \
            index += 1;                                                \
        }                                                              \
        elements.set(newElements);                                     \
    });                                                                \
    return Element([=](int x, int y) mutable {                         \
        for (const auto& element : elements()) {                       \
            element.render(x, y);                                      \
        }                                                              \
    });                                                                \
    }                                                                  \
    ()

#endif
