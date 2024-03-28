#ifndef PAGES_PLAYPAGE_HPP
#define PAGES_PLAYPAGE_HPP

#include "liquid.hpp"

#include "components/Snake.hpp"
#include "libs/router.hpp"

using namespace Liquid;

auto PlayPage() -> Element {
    auto router = useRouter();
    auto lifecycle = useLifecycle();
    auto snakeRef = createSignal<SnakeRef>();

    auto handleSnakeMove = [=](const Vector& position) {
    };

    auto handleSnakeDeath = [=](int length) mutable {
        router.navigate("/");
    };

    lifecycle.mount([=]() {
        snakeRef().grow();
    });

    return Group({
        Snake(snakeRef, 4, { 20, 20 }, handleSnakeMove, handleSnakeDeath),
    });
}

#endif
