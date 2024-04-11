#include "include/state.hpp"

namespace liquid {
    auto untrack(const std::function<void()>& callback) -> void {
        detail::track = false;
        callback();
        detail::track = true;
    }
}
