#include "include/reactivity.hpp"

namespace Liquid {
    static auto effectId = 0;
    static auto currentId = 0;
    static auto currentCallback = std::function<void()>();

    namespace Internal {
        std::pair<int, std::function<void()>> currentEffect() {
            return { currentId, currentCallback };
        }

        void runEffect(int id, const std::function<void()> &callback) {
            currentId = id;
            currentCallback = callback;
            callback();
            currentCallback = nullptr;
        }
    }

    void createEffect(const std::function<void()> &callback) {
        Internal::runEffect(effectId++, callback);
    }

    Signal<std::string> createSignal(const char *value) {
        return Signal<std::string>(value);
    }
}