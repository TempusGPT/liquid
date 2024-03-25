#ifndef LIQUID_TIMER_HPP
#define LIQUID_TIMER_HPP

#include <functional>

namespace Liquid {
    auto setTimeout(int delay, const std::function<void()>& callback) -> int;
    auto setInterval(int delay, const std::function<void()>& callback) -> int;
    auto clearTimer(int id) -> void;

    namespace Internal {
        auto processTimer() -> void;
    }
}

#endif
