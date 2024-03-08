#include "../components/Timer.hpp"
#include "liquid.hpp"

Element MainMenu() {
    const auto numbers = std::vector<int> { 2, 4, 8, 16 };

    auto signal = createSignal(0);
    auto title = createSignal("MainMenu");

    createEffect([=]() mutable {
        if (signal() == 0) {
            beep();
        }
    });

    onInput({ Key::UpArrow }, [=]() mutable {
        signal.set(signal() + 1);
    });

    onInput({ Key::DownArrow }, [=]() mutable {
        signal.set(signal() - 1);
    });

    onInput({ Key::Space }, [=]() mutable {
        title.set(title() + "!");
    });

    onInput({ Key::Q, Key::Enter }, []() {
        exitApp();
    });

    return fragment({
        Timer(FN title() X),
        text(FN f("Signal is {0}\n", signal()) X),

        WHEN(signal() < 0) {
            text("Signal is negative\n\n"),
        } OR(signal() > 0) {
            text("Signal is positive\n\n"),
        } OTHERWISE {
            text("Signal is zero\n\n"),
        } X,

        EACH(numbers, n, i) {
            text(FN f("{0}th number is {1}\n", i, n) X),
        } X,
        text("\n"),
    });
}
