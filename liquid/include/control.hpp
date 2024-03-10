#ifndef LIQUID_CONTROL_HPP
#define LIQUID_CONTROL_HPP

#define WHEN(condition) \
    [=]() mutable {                                                                         \
        auto elements = createSignal<std::vector<Element>>({});                             \
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

#define END_WHEN                                     \
    ;                                                \
    }                                                \
    }                                                \
    }                                                \
    }                                                \
    ;                                                \
    createEffect([=]() mutable {                     \
        for (const auto &arg : args) {               \
            if (std::get<0>(arg)()) {                \
                elements.set(std::get<1>(arg)());    \
                return;                              \
            }                                        \
        }                                            \
    });                                              \
    return Element {                                 \
        [=]() mutable {                              \
            for (const auto &element : elements()) { \
                element.render();                    \
            }                                        \
        }                                            \
    };                                               \
    }                                                \
    ()

#define EACH(collection, item, index) \
    [=]() mutable {                                                               \
        auto elements = createSignal<std::vector<Element>>({});                   \
        auto items = [=]() mutable { return collection; };                        \
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
