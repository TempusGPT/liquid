#include "include/component.hpp"

#include <ncurses.h>

namespace Liquid {
    namespace Internal {
        void onCleanup(const std::function<void()> &callback) {
            Element::lastMounted->cleanupCallbacks.push_back(callback);
        }
    }

    Element::Element(
        const std::function<void(int, int)> &renderCallback
    ) : renderCallback(renderCallback) {
        lastMounted = this;
    }

    void Element::render(int x, int y) const {
        renderCallback(x, y);
    }

    void Element::cleanup() const {
        for (const auto &callback : cleanupCallbacks) {
            callback();
        }
    }

    Element *Element::lastMounted = nullptr;
}
