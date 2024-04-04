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
    auto snake = Signal<SnakeRef>();
    auto apple = Signal<AppleRef>();
    auto poisonedApple = Signal<AppleRef>();

    auto handleSnakeMove = [=](const Vector& head) {
        if (head == apple().position()) {
            snake().grow();
            apple().refresh();
        }

        if (head == poisonedApple().position()) {
            snake().shrink();
            poisonedApple().refresh();
        }
    };

    auto handleSnakeDeath = [](int) {
        navigate("/");
    };

    return Group({
        Frame("■", FIELD_SIZE + Vector { 2, 2 }, Color::Green),
        Goto(2, 1),
        Snake(snake, 4, FIELD_SIZE, handleSnakeMove, handleSnakeDeath),
        Goto(2, 1),
        Apple(apple, FIELD_SIZE, Color::Red),
        Goto(2, 1),
        Apple(poisonedApple, FIELD_SIZE, Color::Magenta),
    });
}

#endif
