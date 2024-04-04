#ifndef LIQUID_TIMER_HPP
#define LIQUID_TIMER_HPP

#include <functional>

namespace liquid {
    auto setTimeout(int delay, const std::function<void()>& callback) -> int;
    auto setInterval(int delay, const std::function<void()>& callback) -> int;
    auto clearTimer(int id) -> void;

    namespace detail {
        auto processTimer() -> void;
    }
}

#endif
