#ifndef LIBS_GAME_FRAME_HPP
#define LIBS_GAME_FRAME_HPP

#include "libs/vector.hpp"
#include "liquid.hpp"

#include <string>

auto Walls(
    const liquid::Prop<Vector>& size,
    const liquid::Prop<liquid::Color>& color
) -> liquid::Element;

#endif
