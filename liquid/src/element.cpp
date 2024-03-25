#include "include/component.hpp"

#include <ncurses.h>

namespace Liquid {
    namespace Internal {
        auto lastMounted = (Element*)nullptr;

        auto onCleanup(const std::function<void()>& callback) -> void {
            lastMounted->cleanupCallbacks.push_back(callback);
        }
    }

    Element::Element(
        const std::function<void(int, int)>& renderCallback
    ) : renderCallback(renderCallback) {
        Internal::lastMounted = this;
    }

    auto Element::render(int x, int y) const -> void {
        renderCallback(x, y);
    }

    auto Element::cleanup() const -> void {
        for (const auto& callback : cleanupCallbacks) {
            callback();
        }
    }
}
