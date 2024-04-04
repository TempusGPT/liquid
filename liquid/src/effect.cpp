#include "include/effect.hpp"
#include "include/element.hpp"

namespace liquid {
    static auto newId = 0;

    namespace detail {
        auto runEffect(int id, const std::function<void()>& callback) -> void {
            effectId = id;
            effectCallback = callback;
            callback();
            effectCallback = nullptr;
        }
    }

    Effect::~Effect() {
        for (const auto& callback : callbacks) {
            detail::runEffect(newId++, callback);
        }

        for (const auto& callback : cleanupCallbacks) {
            Element::onCleanup(callback);
        }
    }

    auto Effect::create(const std::function<void()>& callback) -> void {
        callbacks.push_back(callback);
    }

    auto Effect::cleanup(const std::function<void()>& callback) -> void {
        cleanupCallbacks.push_back(callback);
    }
}
