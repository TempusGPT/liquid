#ifndef LIBS_GAME_STORES_HPP
#define LIBS_GAME_STORES_HPP

#include "stage.hpp"

#include <string>

namespace stage {
    auto current() -> Stage&;
    auto next() -> void;
    auto reset() -> void;
}

namespace score {
    auto length() -> int;
    auto maxLength() -> int;
    auto honeyApple() -> int;
    auto poisonApple() -> int;
    auto gate() -> int;

    auto eatHoneyApple() -> void;
    auto eatPoisonApple() -> void;
    auto enterGate() -> void;
}

#endif
