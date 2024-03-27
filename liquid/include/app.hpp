#ifndef LIQUID_APP_HPP
#define LIQUID_APP_HPP

#include "element.hpp"

#include <string>

namespace Liquid {
    auto render(const Element& element) -> int;
    auto beep() -> void;
    auto exit() -> void;

    namespace Internal {
        auto markDirty() -> void;
    }
}

#endif
