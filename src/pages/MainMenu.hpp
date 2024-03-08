#include "liquid.hpp"

Element MainMenu() {
    const auto numbers = std::vector<int> {2, 4, 8, 16};

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
        text(f("{0} Seconds\n\n", elapsed())),
        text(f("Signal is {0}\n", signal())),

        IF(signal() < 0) {
            text("Signal is negative\n\n"),
        } ELIF(signal() > 0) {
            text("Signal is positive\n\n"),
        } ELSE {
            text("Signal is zero\n\n"),
        } END,

        FOR(numbers, n, i) {
            text(f("{0}th number is {1}\n", i, n)),
        } END,
        text("\n"),
    } END;
}
