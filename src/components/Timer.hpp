#ifndef COMPONENTS_TIMER_HPP
#define COMPONENTS_TIMER_HPP

#include "liquid.hpp"

Element Timer(const Prop<std::string> &title) {
    auto elapsed = createSignal(0);

    setInterval(1000, [=]() mutable {
        elapsed.set(elapsed() + 1);
    });

    return Text(
        FN f("{0}s in {1}\n", elapsed(), title()) X_FN,
        FN Color::Black X_FN,
        FN Color::White X_FN
    );
}

#endif
