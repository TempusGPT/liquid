#ifndef PAGES_PLAYPAGE_HPP
#define PAGES_PLAYPAGE_HPP

#include "components/Apple.hpp"
#include "components/Frame.hpp"
#include "components/Snake.hpp"
#include "libs/router.hpp"
#include "liquid.hpp"

using namespace liquid;

constexpr Vector FIELD_SIZE = { 23, 23 };

auto PlayPage() -> Element {
    auto apple = Signal<AppleRef>();
    auto snake = Signal<SnakeRef>();

    auto handleSnakeMove = [=](const Vector& head) {
        if (head == apple().position()) {
            snake().grow();
            do {
                apple().refresh();
            } while (snake().isOverlap(apple().position()));
        }
    };

    auto handleSnakeDeath = [](int) {
        navigate("/");
    };

    return Group({
        Frame("■", FIELD_SIZE + Vector { 2, 2 }, Color::Green),
        Goto(2, 1),
        Apple(apple, FIELD_SIZE),
        Goto(2, 1),
        Snake(snake, 4, FIELD_SIZE, handleSnakeMove, handleSnakeDeath),
    });
}

#endif
