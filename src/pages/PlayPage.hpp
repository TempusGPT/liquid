#ifndef PAGES_PLAYPAGE_HPP
#define PAGES_PLAYPAGE_HPP

#include "components/Snake.hpp"
#include "liquid.hpp"

using namespace Liquid;

auto PlayPage() -> Element {
    auto handleSnakeMove = [](const Vector& position) {
        // Process apple, poison
    };

    auto handleSnakeDeath = [](int length) {
        navigate("/");
    };

    return Group({
        Snake(4, { 20, 20 }, handleSnakeMove, handleSnakeDeath),
    });
}

#endif
