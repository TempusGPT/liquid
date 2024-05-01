#ifndef LIQUID_CONTROL_HPP
#define LIQUID_CONTROL_HPP

#include "component.hpp"
#include "effect.hpp"
#include "state.hpp"

#include <tuple>
#include <vector>

#define GET(expr) [=]() mutable { return expr; }

#define WHEN(condition) \
    [=]() {                                                     \
        auto effect = Effect();                                 \
        auto elements = State<std::vector<Element>>();          \
        auto cleanup = [=]() {                                  \
            for (const auto& element : elements())              \
                element.cleanup();                              \
        };                                                      \
        effect([=]() mutable {                                  \
            untrack([=]() { cleanup(); });                      \
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
        auto effect = Effect();                                 \
        auto elements = State<std::vector<Element>>();          \
        auto cleanup = [=]() {                                  \
            for (const auto& element : elements())              \
                element.cleanup();                              \
        };                                                      \
        effect([=]() mutable {                                  \
            untrack([=]() { cleanup(); });                      \
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
