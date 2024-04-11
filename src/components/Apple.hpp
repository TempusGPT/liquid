#ifndef COMPONENTS_APPLE_HPP
#define COMPONENTS_APPLE_HPP

#include "libs/random.hpp"
#include "libs/vector.hpp"
#include "liquid.hpp"

using namespace liquid;

struct AppleRef {
    std::function<Vector()> position;
    std::function<void()> refresh;
};

auto Apple(
    State<AppleRef>& ref,
    const Prop<Vector>& fieldSize,
    const Prop<Color>& color
) -> Element {
    auto position = State<Vector>({ fieldSize().x / 2, fieldSize().y / 2 });

    ref.set({
        [=]() { return position(); },
        [=]() mutable {
            position.set({
                random(0, fieldSize().x - 1),
                random(0, fieldSize().y - 1),
            });
        },
    });

    return Group({
        Cursor(RP(position().x * 2), RP(position().y)),
        Text("●", RP(color())),
    });
}

#endif
