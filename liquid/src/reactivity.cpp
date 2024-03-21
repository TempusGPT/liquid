#include "include/reactivity.hpp"

namespace Liquid {
    static auto effectId = 0;
    static auto effectCallback = std::function<void()>();

    namespace Internal {
        EffectData currentEffect() {
            return { effectId, effectCallback };
        }
    }

    Effect createEffect() {
        return Effect();
    }

    Effect::~Effect() {
        for (const auto &callback : callbacks) {
            if (!callback) {
                continue;
            }

            effectCallback = callback;
            callback();
            effectCallback = nullptr;
            effectId += 1;
        }

        for (const auto &callback : cleanupCallbacks) {
            Internal::onCleanup(callback);
        }
    }

    void Effect::operator()(const std::function<void()> &callback) {
        callbacks.push_back(callback);
    }

    void Effect::cleanup(const std::function<void()> &callback) {
        cleanupCallbacks.push_back(callback);
    }

    Signal<std::string> createSignal(const char *value) {
        return Signal<std::string>(value);
    }
}