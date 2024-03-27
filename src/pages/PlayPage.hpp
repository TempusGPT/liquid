#ifndef PAGES_PLAYPAGE_HPP
#define PAGES_PLAYPAGE_HPP

#include "liquid.hpp"

#include "components/Snake.hpp"
#include "libs/router.hpp"

using namespace Liquid;

auto PlayPage() -> Element {
    auto router = useRouter();

    auto handleSnakeMove = [](const Vector& position) {
        // Process apple, poison
    };

    auto handleSnakeDeath = [=](int length) mutable {
        router.navigate("/");
    };

    return Group({
        Snake(4, { 20, 20 }, handleSnakeMove, handleSnakeDeath),
    });
}

#endif
