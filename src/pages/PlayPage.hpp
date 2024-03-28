#ifndef PAGES_PLAYPAGE_HPP
#define PAGES_PLAYPAGE_HPP

#include "components/Apple.hpp"
#include "components/Snake.hpp"
#include "libs/router.hpp"
#include "liquid.hpp"

using namespace Liquid;

auto PlayPage() -> Element {
    static constexpr Vector fieldSize = { 20, 20 };

    auto router = useRouter();
    auto lifecycle = useLifecycle();
    auto apple = createSignal<AppleRef>();
    auto snake = createSignal<SnakeRef>();

    auto handleSnakeMove = [=](const Vector& head) {
        if (head != apple().position()) {
            return;
        }

        snake().grow();
        apple().refresh();
    };

    auto handleSnakeDeath = [=](int) mutable {
        router.navigate("/");
    };

    return Group({
        Apple(apple, fieldSize),
        Goto(0, 0),
        Snake(snake, 4, fieldSize, handleSnakeMove, handleSnakeDeath),
        Goto(0, 0),
        Text(FN("x: %0%, y: %1%"_fmt % apple().position().x % apple().position().y)),
    });
}

#endif
