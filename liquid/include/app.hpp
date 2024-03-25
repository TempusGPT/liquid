#ifndef LIQUID_APP_HPP
#define LIQUID_APP_HPP

#include "element.hpp"

#include <string>

namespace Liquid {
    auto render(const Element& element) -> int;

    auto path() -> std::string;
    auto navigate(const std::string& path) -> void;
    auto exit() -> void;
    auto beep() -> void;

    namespace Internal {
        auto markDirty() -> void;
    }
}

#endif
