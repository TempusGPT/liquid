#ifndef LIBS_GAME_MISSION_HPP
#define LIBS_GAME_MISSION_HPP

#include "liquid.hpp"

#include <functional>

struct MissionRef {
    std::function<void()> eatHoneyApple;
    std::function<void()> eatPoisonedApple;
    std::function<void()> enterGate;
};

auto Mission(
    const liquid::Prop<std::size_t>& initialLength,
    liquid::Ref<MissionRef>& ref
) -> liquid::Element;

#endif
