#ifndef LIQUID_EFFECT_HPP
#define LIQUID_EFFECT_HPP

#include <functional>

namespace Liquid {
    namespace Internal {
        inline auto effectId = 0;
        inline auto effectCallback = std::function<void()>();
        auto runEffect(int id, const std::function<void()>& callback) -> void;
    }

    auto createEffect(const std::function<void()>& callback) -> void;
}

#endif
