#ifndef COMPONENTS_TIMER_HPP
#define COMPONENTS_TIMER_HPP

#include "liquid.hpp"

using namespace Liquid;

Element Timer(const Prop<std::string> &title) {
    auto effect = createEffect();
    auto elapsed = createSignal(0);

    const auto id = setInterval(1000, [=]() mutable {
        elapsed.set(elapsed() + 1);
    });

    effect.cleanup([=]() {
        clearTimer(id);
    });

    return Text(FN("%0%s in %1%\n"_f % elapsed() % title()), Color::Black, Color::White);
}

#endif
