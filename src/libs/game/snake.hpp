#ifndef LIBS_GAME_SNAKE_HPP
#define LIBS_GAME_SNAKE_HPP

#include "libs/vector.hpp"
#include "liquid.hpp"
#include "transform.hpp"

#include <list>

struct SnakeRef {
    std::function<void()> grow;
    std::function<void()> shrink;
    std::function<void(Vector)> changeDirection;
    std::function<bool(Vector)> isOverlap;
};

auto Snake(
    const liquid::Prop<std::list<Vector>>& initialPosition,
    const liquid::Prop<liquid::Color>& color,
    const liquid::Prop<std::function<Vector(Transform)>>& onMove,
    const liquid::Prop<std::function<void()>>& onDeath,
    liquid::Ref<SnakeRef>& ref
) -> liquid::Element;

#endif
