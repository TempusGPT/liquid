#ifndef LIBS_GAME_FRAME_HPP
#define LIBS_GAME_FRAME_HPP

#include "libs/vector.hpp"
#include "liquid.hpp"

#include <string>

auto Walls(
    const liquid::Prop<std::string>& ch,
    const liquid::Prop<Vector>& size,
    const liquid::Prop<liquid::Color>& foreground = liquid::Color::White,
    const liquid::Prop<liquid::Color>& background = liquid::Color::Black
) -> liquid::Element;

#endif
