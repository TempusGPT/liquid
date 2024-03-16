#ifndef LIQUID_CONTROL_HPP
#define LIQUID_CONTROL_HPP

#include "component.hpp"
#include "reactivity.hpp"

#include <tuple>
#include <vector>

#define RP \
    {      \
        [=]() mutable { return

#define END_RP \
    ;          \
    }          \
    }

#define WHEN(condition) \
    [=]() mutable {                                                                         \
        auto effect = createEffect();                                                       \
        auto elements = createSignal<std::vector<Element>>({});                             \
        auto prevIndex = createSignal(-1);                                                  \
        const auto args = std::vector<std::tuple<Prop<bool>, Prop<std::vector<Element>>>> { \
            {                                                                               \
                { [=]() mutable { return condition; } },                                    \
                {                                                                           \
                    [=]() mutable { return std::vector<Element>

#define OR(condition)                            \
    ;                                            \
    }                                            \
    }                                            \
    }                                            \
    ,                                            \
    {                                            \
        { [=]() mutable { return condition; } }, \
        {                                        \
            [=]() mutable { return std::vector<Element>

#define OTHERWISE \
    ;             \
    }             \
    }             \
    }             \
    ,             \
    {             \
        true,     \
        {         \
            [=]() mutable { return std::vector<Element>

#define END_WHEN                                             \
    ;                                                        \
    }                                                        \
    }                                                        \
    }                                                        \
    ,                                                        \
    {                                                        \
        true,                                                \
        {                                                    \
            [=]() mutable { return std::vector<Element>(); } \
        }                                                    \
    }                                                        \
    }                                                        \
    ;                                                        \
    const auto cleanup = [=]() {                             \
        for (const auto &element : untrack(elements)) {      \
            element.cleanup();                               \
        }                                                    \
    };                                                       \
    effect([=]() mutable {                                   \
        auto index = 0;                                      \
        for (const auto &arg : args) {                       \
            if (std::get<0>(arg)()) {                        \
                if (untrack(prevIndex) != index) {           \
                    cleanup();                               \
                    elements.set(std::get<1>(arg)());        \
                    prevIndex.set(index);                    \
                }                                            \
                return;                                      \
            }                                                \
            index += 1;                                      \
        }                                                    \
    });                                                      \
    return Element([=](int x, int y) mutable {               \
        for (const auto &element : elements()) {             \
            element.render(x, y);                            \
        }                                                    \
    });                                                      \
    }                                                        \
    ()

#define EACH(collection, item, index) \
    [=]() mutable {                                                                         \
        auto effect = createEffect();                                                       \
        auto elements = createSignal<std::vector<Element>>({});                             \
        auto items = [=]() mutable { return collection; };                                  \
        auto transform = [=](decltype(items())::value_type item, int index) mutable {       \
            return std::vector<Element>

#define END_EACH                                                       \
    ;                                                                  \
    }                                                                  \
    ;                                                                  \
    effect([=]() mutable {                                             \
        auto newElements = std::vector<Element>({});                   \
        auto index = 0;                                                \
        for (const auto &item : items()) {                             \
            auto t = transform(item, index);                           \
            newElements.insert(newElements.end(), t.begin(), t.end()); \
            index += 1;                                                \
        }                                                              \
        elements.set(newElements);                                     \
    });                                                                \
    return Element([=](int x, int y) mutable {                         \
        for (const auto &element : elements()) {                       \
            element.render(x, y);                                      \
        }                                                              \
    });                                                                \
    }                                                                  \
    ()

#endif
