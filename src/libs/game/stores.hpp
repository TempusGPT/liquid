#ifndef LIBS_GAME_STORES_HPP
#define LIBS_GAME_STORES_HPP

#include "stage.hpp"

#include <string>

namespace stage {
    auto current() -> Stage;
    auto interval() -> int;
    auto moveNext() -> void;
    auto reset() -> void;
    auto isLast() -> bool;
}

namespace score {
    auto length() -> int;
    auto maxLength() -> int;
    auto honeyApple() -> int;
    auto poisonApple() -> int;
    auto gate() -> int;
    auto exit() -> bool;

    auto initialize() -> void;
    auto eatHoneyApple() -> void;
    auto eatPoisonApple() -> void;
    auto enterGate() -> void;
    auto enterExit() -> void;
}

#endif
