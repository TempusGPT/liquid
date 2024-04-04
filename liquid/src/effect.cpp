#include "include/effect.hpp"
#include "include/element.hpp"

namespace Liquid {
    static auto newId = 0;

    namespace Internal {
        auto runEffect(int id, const std::function<void()>& callback) -> void {
            effectId = id;
            effectCallback = callback;
            callback();
            effectCallback = nullptr;
        }
    }

    Effect::~Effect() {
        for (const auto& callback : callbacks) {
            Internal::runEffect(newId++, callback);
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
