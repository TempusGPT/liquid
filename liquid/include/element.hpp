#ifndef LIQUID_ELEMENT_HPP
#define LIQUID_ELEMENT_HPP

#include "color.hpp"

#include <functional>
#include <vector>

namespace liquid {
    class Element {
    public:
        static auto onCleanup(const std::function<void()>& callback) -> void;

        Element(
            const std::function<void(int, int)>& renderCallback,
            const std::vector<std::function<void()>>& cleanupCallbacks = {}
        );

        auto render(int x, int y) const -> void;
        auto cleanup() const -> void;

    private:
        static inline Element* lastMounted = nullptr;
        std::function<void(int, int)> renderCallback;
        std::vector<std::function<void()>> cleanupCallbacks;
    };
}

#endif
