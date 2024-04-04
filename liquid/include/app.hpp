#ifndef LIQUID_APP_HPP
#define LIQUID_APP_HPP

#include "element.hpp"

#include <string>

namespace liquid {
    auto render(const Element& element) -> int;
    auto beep() -> void;
    auto exit() -> void;

    namespace detail {
        auto markDirty() -> void;
    }
}

#endif
