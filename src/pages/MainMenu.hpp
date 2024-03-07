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
        text("TIMER: " + std::to_string(elapsed()) + " Seconds\n"),
        text("TEXT: Number is " + std::to_string(number()) + "\n"),
        text("TEXT: Doubled is " + std::to_string(doubled()) + "\n"),

        IF(number() < 0)
            text("IF: Number is negative\n"),
        ELIF(number() > 0)
            text("IF: Number is positive\n"),
        ELSE
            text("IF: Number is zero\n"),
        END,

        FOR(numbers, n, i)
            text("FOR: Number[" + std::to_string(i) + "] is " + std::to_string(n) + "\n"),
        END,

        text("\n"),
    });
}