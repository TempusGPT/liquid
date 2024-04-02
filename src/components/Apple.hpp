#ifndef COMPONENTS_APPLE_HPP
#define COMPONENTS_APPLE_HPP

#include "libs/random.hpp"
#include "libs/vector.hpp"
#include "liquid.hpp"

using namespace Liquid;

struct AppleRef {
    std::function<Vector()> position;
    std::function<void()> refresh;
};

auto Apple(Signal<AppleRef>& ref, const Prop<Vector>& fieldSize) -> Element {
    auto position = createSignal<Vector>({ fieldSize().x / 2, fieldSize().y / 2 });

    ref.set({
        [=]() {
            return position();
        },
        [=]() mutable {
            position.set({
                random(0, fieldSize().x - 1),
                random(0, fieldSize().y - 1),
            });
        },
    });

    return Group({
        Goto(RP(position().x * 2), RP(position().y)),
        Text("", Color::Red),
    });
}

#endif
