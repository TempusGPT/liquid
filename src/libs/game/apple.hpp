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
    liquid::Ref<AppleRef>& ref,
    const liquid::Prop<Vector>& fieldSize,
    const liquid::Prop<liquid::Color>& color
) -> liquid::Element;

#endif
