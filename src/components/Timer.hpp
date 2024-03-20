#ifndef COMPONENTS_TIMER_HPP
#define COMPONENTS_TIMER_HPP

#include "liquid.hpp"

using namespace Liquid;

Element Timer(const Prop<std::string> &title) {
    auto elapsed = createSignal(0);

    setInterval(1000, [=]() mutable {
        elapsed.set(elapsed() + 1);
    });

    return Text(FN("%0%s in %1%\n"_f % elapsed() % title()), Color::Black, Color::White);
}

#endif
