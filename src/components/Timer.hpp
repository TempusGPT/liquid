#include "liquid.hpp"

Element Timer(const Prop<std::string> &title) {
    auto elapsed = createSignal(0);

    setInterval(1000, [=]() mutable {
        elapsed.set(elapsed() + 1);
    });

    return text(FN f("{0}s in {1}\n", std::to_string(elapsed()), title()) END);
}