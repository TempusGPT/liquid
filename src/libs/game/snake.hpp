#ifndef LIBS_GAME_SNAKE_HPP
#define LIBS_GAME_SNAKE_HPP

#include "libs/vector.hpp"
#include "liquid.hpp"

struct SnakeRef {
    std::function<void()> grow;
    std::function<void()> shrink;
    std::function<void(Vector)> changeDirection;
    std::function<bool(Vector)> isOverlap;
};

auto Snake(
    const liquid::Prop<int>& initialLength,
    const liquid::Prop<Vector>& fieldSize,
    const liquid::Prop<liquid::Color>& color,
    const liquid::Prop<std::function<Vector(Vector)>>& onMove,
    const liquid::Prop<std::function<void()>>& onDeath,
    liquid::Ref<SnakeRef>& ref
) -> liquid::Element;

#endif
