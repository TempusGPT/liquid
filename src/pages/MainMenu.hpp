#include "liquid.hpp"

Element MainMenu() {
    const auto numbers = std::vector<int> {1, 2, 3};

    auto elapsed = createSignal(0);
    auto number = createSignal(0);
    auto doubled = [=]() mutable { return number() * 2; };

    createEffect([=]() mutable {
        if (number() == 0) {
            beep();
        }
    });

    onInput(Key::UpArrow, [=]() mutable {
        number.set(number() + 1);
    });

    onInput(Key::DownArrow, [=]() mutable {
        number.set(number() - 1);
    });

    onInput(Key::Enter, []() {
        exitApp();
    });

    setInterval(1000, [=]() mutable {
        elapsed.set(elapsed() + 1);
    });

    return FRAGMENT(
        text(f("{0} Seconds\n", elapsed())),
        text(f("Number is {0}\n", number())),
        text(f("Doubled is {0}\n", doubled())),

        IF(number() < 0)
            text("Number is negative\n"),
        ELIF(number() > 0)
            text("Number is positive\n"),
        ELSE
            text("Number is zero\n"),
        END,

        FOR(numbers, n, i)
            text(f("Number[{0}] is {1}\n", i, n)),
        END,

        text("\n"),
    );
}
