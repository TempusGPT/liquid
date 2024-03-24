#include "include/reactivity.hpp"

namespace Liquid {
    static auto effectId = 0;
    static auto effectCallback = std::function<void()>();

    namespace Internal {
        std::pair<int, std::function<void()>> currentEffect() {
            return { effectId, effectCallback };
        }
    }

    void createEffect(const std::function<void()> &callback) {
        effectCallback = callback;
        callback();
        effectCallback = nullptr;
        effectId += 1;
    }

    Signal<std::string> createSignal(const char *value) {
        return Signal<std::string>(value);
    }
}