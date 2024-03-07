#include <string>
#include "liquid.hpp"

auto global = signal(0);

Element Example()
{
    auto doubled = memo(global() * 2);
    auto numbers = std::vector<int>{1, 2, 3, 4, 5};

    return fragment({
        text("Count: " + std::to_string(global()) + "\n"),
        text("Doubled: " + std::to_string(doubled()) + "\n"),

        WHEN(global() == 0)
            text("Value is zero\n"),
        THEN(global() == 1)
            text("Value is one\n"),
        OTHERWISE
            text("Value is large\n"),
        END,

        EACH(numbers, n)
            text("Number: " + std::to_string(n) + "\n"),
        END,

        text("\n"),
    });
}

int main()
{
    const auto example = Example();

    example();
    global.set(1);
    example();
    global.set(2);
    example();
    global.set(3);
    example();

    return 0;
}