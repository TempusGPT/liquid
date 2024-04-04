#include "include/component.hpp"

#include <ncurses.h>

namespace liquid {
    auto Element::onCleanup(const std::function<void()>& callback) -> void {
        lastMounted->cleanupCallbacks.push_back(callback);
    }

    Element::Element(
        const std::function<void(int, int)>& renderCallback,
        const std::vector<std::function<void()>>& cleanupCallbacks
    ) : renderCallback(renderCallback), cleanupCallbacks(cleanupCallbacks) {
        lastMounted = this;
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
