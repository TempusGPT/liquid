#include "include/control.hpp"

namespace Liquid {
    void renderElements(const std::initializer_list<Element> &elements) {
        for (const auto &element : elements) {
            element.render();
        }
    }

    int renderAndIncreaseIndex(const int index, const std::initializer_list<Element> &elements) {
        renderElements(elements);
        return index + 1;
    }

    Element When(const std::vector<WhenArg> &args) {
        auto elements = createSignal<std::vector<Element>>({});

        createEffect([=]() mutable {
            for (const auto &arg : args) {
                if (arg.condition()) {
                    elements.set(arg.elements());
                    return;
                }
            }
        });

        return {
            [=]() mutable {
                for (const auto &element : elements()) {
                    element.render();
                }
            }
        };
    }
}
