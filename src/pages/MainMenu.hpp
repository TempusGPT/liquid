#include "liquid.hpp"

Element MainMenu() {
    const auto numbers = std::vector<int> {1, 2, 3};

    auto elapsed = createSignal(0);
    auto signal = createSignal(0);

    createEffect([=]() mutable {
        if (signal() == 0) {
            beep();
        }
    });

    onInput(Key::UpArrow, [=]() mutable {
        signal.set(signal() + 1);
    });

    onInput(Key::DownArrow, [=]() mutable {
        signal.set(signal() - 1);
    });

    onInput(Key::Enter, []() {
        exitApp();
    });

    setInterval(1000, [=]() mutable {
        elapsed.set(elapsed() + 1);
    });

    RETURN {
        text(f("{0} Seconds\n", elapsed())),
        text(f("Signal is {0}\n", signal())),

        WHEN(signal() < 0) {
            text("Signal is negative\n"),
        } OR(signal() > 0) {
            text("Signal is positive\n"),
        } OTHERWISE {
            text("Signal is zero\n"),
        } END,

        text("Numbers: "),
        EACH(numbers, n) {
            text(f("{0}, ", n)),
        } END,
        text("\n"),
    } END;
}
