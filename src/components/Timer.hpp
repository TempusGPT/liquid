#ifndef COMPONENTS_TIMER_HPP
#define COMPONENTS_TIMER_HPP

#include "liquid.hpp"

using namespace Liquid;

Element Timer(const Prop<std::string> &title) {
    auto elapsed = createSignal(0);

    setInterval(1000, [=]() mutable {
        elapsed.set(elapsed() + 1);
    });

    return Text(RP format("{0}s in {1}\n", elapsed(), title()) END_RP, Color::Black, Color::White);
}

#endif
