#ifndef LIBS_GAME_FRAME_HPP
#define LIBS_GAME_FRAME_HPP

#include "libs/vector.hpp"
#include "liquid.hpp"

#include <functional>
#include <optional>
#include <string>

struct Gate {
    Vector position;
    Vector direction;
};

struct WallsRef {
    std::function<std::optional<Gate>(Vector)> gate;
};

auto Walls(
    const liquid::Prop<Vector>& size,
    const liquid::Prop<liquid::Color>& color,
    liquid::Ref<WallsRef>& ref
) -> liquid::Element;

#endif
