#include "liquid.hpp"

Element MainMenu()
{
    const auto numbers = std::vector<int>{1, 2, 3};

    auto number = SIGNAL(0);
    auto doubled = DERIVED(number() * 2);

    INPUT(Key::UpArrow, {
        number.set(number() + 1);
    });

    INPUT(Key::DownArrow, {
        number.set(number() - 1);
    });

    INPUT(Key::Enter, {
        exitApp();
    });

    return FRAGMENT({
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