#ifndef LIBS_GAME_MISSION_HPP
#define LIBS_GAME_MISSION_HPP

#include "liquid.hpp"

#include <functional>

struct MissionRef {
    std::function<void()> eatHoneyApple;
    std::function<void()> eatPoisonApple;
    std::function<void()> enterGate;
};

auto Mission(
    const liquid::Prop<int>& initialLength,
    const liquid::Prop<int>& targetLength,
    const liquid::Prop<int>& targetHoneyApple,
    const liquid::Prop<int>& targetPoisonApple,
    const liquid::Prop<int>& targetGate,
    const liquid::Prop<std::function<void()>>& onComplete,
    liquid::Ref<MissionRef>& ref
) -> liquid::Element;

#endif
