#include "liquid.hpp"

Element MainMenu() {
    const auto numbers = std::vector<int>{1, 2, 3};

    auto elapsed = SIGNAL(0);
    auto number = SIGNAL(0);
    auto doubled = DERIVED(number() * 2);

    EFFECT({
        const auto id = setInterval(1000, [=]() mutable {
            elapsed.set(elapsed() + 1);
        });

        // TODO: Implement cleaup
        return [=]() {
            clearTimer(id);
        };
    });

    onInput(Key::UpArrow, [=]() mutable {
        number.set(number() + 1);
    });

    onInput(Key::DownArrow, [=]() mutable {
        number.set(number() - 1);
    });

    onInput(Key::Enter, [=]() {
        exitApp();
    });

    return FRAGMENT({
        text(f("TIMER: {0} Seconds\n", elapsed())),
        text(f("TEXT: Number is {0}\n", number())),
        text(f("TEXT: Doubled is {0}\n", doubled())),

        IF(number() < 0)
            text("IF: Number is negative\n"),
        ELIF(number() > 0)
            text("IF: Number is positive\n"),
        ELSE
            text("IF: Number is zero\n"),
        END,

        FOR(numbers, n, i)
            text(f("FOR: Number[{0}] is {1}\n", i, n)),
        END,

        text("\n"),
    });
}