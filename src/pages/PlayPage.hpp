#ifndef PAGES_PLAYPAGE_HPP
#define PAGES_PLAYPAGE_HPP

#include "components/Apple.hpp"
#include "components/Snake.hpp"
#include "libs/router.hpp"
#include "liquid.hpp"

using namespace Liquid;

constexpr Vector FIELD_SIZE = { 20, 20 };

auto PlayPage() -> Element {
    auto router = useRouter();
    auto apple = createSignal<AppleRef>();
    auto snake = createSignal<SnakeRef>();

    auto handleSnakeMove = [=](const Vector& head) {
        if (head == apple().position()) {
            snake().grow();
            do {
                apple().refresh();
            } while (snake().isOverlap(apple().position()));
        }
    };

    auto handleSnakeDeath = [=](int) mutable {
        router.navigate("/");
    };

    return Group({
        Apple(apple, FIELD_SIZE),
        Goto(0, 0),
        Snake(snake, 4, FIELD_SIZE, handleSnakeMove, handleSnakeDeath),
    });
}

#endif
