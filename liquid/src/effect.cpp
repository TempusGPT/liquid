#include "include/effect.hpp"

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

    auto createEffect(const std::function<void()>& callback) -> void {
        Internal::runEffect(newId++, callback);
    }
}
