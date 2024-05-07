#ifndef LIQUID_APP_HPP
#define LIQUID_APP_HPP

#include "element.hpp"

#include <string>

namespace liquid {
    struct Options {
        int width;
        int height;
    };

    auto render(const Element& element, const Options& options) -> int;
    auto beep() -> void;
    auto exit() -> void;

    namespace detail {
        auto markDirty() -> void;
    }
}

#endif
