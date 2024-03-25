#include "include/reactivity.hpp"

namespace Liquid {
    static auto effectId = 0;
    static auto currentId = 0;
    static auto currentCallback = std::function<void()>();

    namespace Internal {
        auto currentEffect() -> std::tuple<int, std::function<void()>> {
            return { currentId, currentCallback };
        }

        auto runEffect(int id, const std::function<void()>& callback) -> void {
            currentId = id;
            currentCallback = callback;
            callback();
            currentCallback = nullptr;
        }
    }

    auto createEffect(const std::function<void()>& callback) -> void {
        Internal::runEffect(effectId++, callback);
    }

    auto createSignal(const char* value) -> Signal<std::string> {
        return Signal<std::string>(value);
    }
}