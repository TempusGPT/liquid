#include "include/macro.hpp"

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
}
