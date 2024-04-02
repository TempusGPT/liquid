#ifndef LIQUID_CONTROL_HPP
#define LIQUID_CONTROL_HPP

#include "component.hpp"
#include "effect.hpp"
#include "signal.hpp"

#include <tuple>
#include <vector>

#define RP(expr) [=]() mutable { return expr; }

#define WHEN(condition) \
    [=]() {                                                     \
        auto elements = createSignal<std::vector<Element>>();   \
        auto cleanup = [=]() {                                  \
            for (const auto& element : untrack(elements))       \
                element.cleanup();                              \
        };                                                      \
        createEffect([=]() mutable {                            \
            cleanup();                                          \
            if (condition) return elements.set(

#define OR(condition) \
    );                \
    if (condition) return elements.set(

#define OTHERWISE \
    );            \
    return elements.set(

#define END_WHEN                                     \
    );                                               \
    elements.set({});                                \
    });                                              \
    return Element(                                  \
        [=](int x, int y) {                          \
            for (const auto& element : elements()) { \
                element.render(x, y);                \
            }                                        \
        },                                           \
        { cleanup }                                  \
    );                                               \
    }                                                \
    ()

#define EACH(items, item, index) \
    [=]() {                                                     \
        auto elements = createSignal<std::vector<Element>>();   \
        auto cleanup = [=]() {                                  \
            for (const auto& element : untrack(elements))       \
                element.cleanup();                              \
        };                                                      \
        createEffect([=]() mutable {                            \
            cleanup();                                          \
            auto index = -1;                                    \
            auto newElements = std::vector<Element>();          \
            for (const auto &item : items) {                    \
                index += 1;                                     \
                newElements.insert(newElements.end(),

#define END_EACH                                     \
    );                                               \
    }                                                \
    elements.set(newElements);                       \
    });                                              \
    return Element(                                  \
        [=](int x, int y) {                          \
            for (const auto& element : elements()) { \
                element.render(x, y);                \
            }                                        \
        },                                           \
        { cleanup }                                  \
    );                                               \
    }                                                \
    ()

#endif
