#ifndef LIQUID_CONTROL_HPP
#define LIQUID_CONTROL_HPP

#define WHEN(condition) \
    [=]() mutable {                                                                         \
        auto elements = createSignal<std::vector<Element>>({});                             \
        auto prevIndex = createSignal(-1);                                                  \
        const auto args = std::vector<std::tuple<Prop<bool>, Prop<std::vector<Element>>>> { \
            {                                                                               \
                { [=]() mutable { return condition; } },                                    \
                { [=]() mutable { return std::vector<Element>

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
    const auto render = [=]() {                              \
        for (const auto &element : untrack(elements)) {      \
            element.render();                                \
        }                                                    \
    };                                                       \
    const auto mount = [=]() {                               \
        for (const auto &element : untrack(elements)) {      \
            element.mount();                                 \
        }                                                    \
    };                                                       \
    const auto cleanup = [=]() {                             \
        for (const auto &element : untrack(elements)) {      \
            element.cleanup();                               \
        }                                                    \
    };                                                       \
    createEffect([=]() mutable {                             \
        auto index = 0;                                      \
        for (const auto &arg : args) {                       \
            if (std::get<0>(arg)()) {                        \
                if (untrack(prevIndex) != index) {           \
                    prevIndex.set(index);                    \
                    cleanup();                               \
                    elements.set(std::get<1>(arg)());        \
                    mount();                                 \
                }                                            \
                return;                                      \
            }                                                \
            index += 1;                                      \
        }                                                    \
    });                                                      \
    return Element(render, mount, cleanup);                  \
    }                                                        \
    ()

#define EACH(collection, item, index) \
    [=]() mutable {                                                                      \
        auto elements = createSignal<std::vector<Element>>({});                          \
        auto items = [=]() mutable { return collection; };                               \
        const auto transform = [](decltype(items())::value_type item, const int index) { \
            return std::vector<Element>

#define END_EACH                                                       \
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

#endif
