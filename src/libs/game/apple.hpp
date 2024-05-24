#ifndef LIBS_GAME_APPLE_HPP
#define LIBS_GAME_APPLE_HPP

#include "libs/vector.hpp"
#include "liquid.hpp"

#include <functional>

struct AppleRef {
    std::function<Vector()> position;
    std::function<void()> refresh;
};

auto Apple(
    const liquid::Prop<Vector>& fieldSize,
    const liquid::Prop<liquid::Color>& color,
    liquid::Ref<AppleRef>& ref
) -> liquid::Element;

#endif
