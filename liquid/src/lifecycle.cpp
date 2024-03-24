#include "include/lifecycle.hpp"
#include "include/element.hpp"

namespace Liquid {
    Lifecycle useLifecycle() {
        return Lifecycle();
    }

    Lifecycle::~Lifecycle() {
        for (const auto &callback : mountCallbacks) {
            callback();
        }

        for (const auto &callback : cleanupCallbacks) {
            Internal::onCleanup(callback);
        }
    }

    void Lifecycle::mount(const std::function<void()> &callback) {
        mountCallbacks.push_back(callback);
    }

    void Lifecycle::cleanup(const std::function<void()> &callback) {
        cleanupCallbacks.push_back(callback);
    }
}
