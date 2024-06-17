#ifndef LIBS_GAME_SNAKE_HPP
#define LIBS_GAME_SNAKE_HPP

#include "libs/vector.hpp"
#include "liquid.hpp"
#include "transform.hpp"

#include <list>
#include <optional>

struct SnakeRef {
    std::function<bool(Vector)> isOverlap;
    std::function<int()> length;
    std::function<void()> grow;
    std::function<void()> shrink;
    std::function<void(Vector)> changeDirection;
};

auto Snake(
    const liquid::Prop<std::list<Vector>>& initialPosition,
    const liquid::Prop<liquid::Color>& color,
    const liquid::Prop<std::function<std::optional<Transform>(Transform)>>& onMove,
    const liquid::Prop<std::function<void()>>& onDeath,
    liquid::Ref<SnakeRef>& ref
) -> liquid::Element;

#endif
