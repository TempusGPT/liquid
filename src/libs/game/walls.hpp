#ifndef LIBS_GAME_FRAME_HPP
#define LIBS_GAME_FRAME_HPP

#include "libs/vector.hpp"
#include "liquid.hpp"
#include "transform.hpp"

#include <functional>
#include <optional>
#include <set>

struct WallsRef {
    std::function<bool(Vector)> isExit;
    std::function<bool(Vector)> isOverlap;
    std::function<std::optional<Transform>(Transform)> getGate;
};

auto Walls(
    const liquid::Prop<Vector>& fieldSize,
    const liquid::Prop<std::unordered_set<Vector>>& wallPositions,
    const liquid::Prop<std::unordered_set<Vector>>& immuneWallPositions,
    const liquid::Prop<liquid::Color>& wallColor,
    const liquid::Prop<liquid::Color>& gateColor,
    const liquid::Prop<liquid::Color>& exitColor,
    const liquid::Prop<bool>& exitGateOpen,
    liquid::Ref<WallsRef>& ref
) -> liquid::Element;

#endif
