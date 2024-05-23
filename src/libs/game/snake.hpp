#ifndef LIBS_GAME_SNAKE_HPP
#define LIBS_GAME_SNAKE_HPP

#include "libs/vector.hpp"
#include "liquid.hpp"

struct SnakeRef {
    std::function<void()> grow;
    std::function<void()> shrink;
    std::function<bool(const Vector&)> isOverlap;
};

auto Snake(
    liquid::Ref<SnakeRef>& ref,
    const liquid::Prop<int>& initialLength,
    const liquid::Prop<Vector>& fieldSize,
    const liquid::Prop<std::function<void(Vector)>>& onMove,
    const liquid::Prop<std::function<void(int)>>& onDeath
) -> liquid::Element;

#endif
