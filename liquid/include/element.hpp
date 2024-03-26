#ifndef LIQUID_ELEMENT_HPP
#define LIQUID_ELEMENT_HPP

#include "color.hpp"

#include <functional>
#include <vector>

namespace Liquid {
    namespace Internal {
        auto onCleanup(const std::function<void()>& callback) -> void;
    }

    class Element {
        friend auto Internal::onCleanup(const std::function<void()>& callback) -> void;

    public:
        Element(
            const std::function<void(int, int)>& renderCallback,
            const std::vector<std::function<void()>>& cleanupCallbacks = {}
        );

        auto render(int x, int y) const -> void;
        auto cleanup() const -> void;

    private:
        std::function<void(int, int)> renderCallback;
        std::vector<std::function<void()>> cleanupCallbacks;
    };
}

#endif
