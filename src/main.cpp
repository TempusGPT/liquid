#include <string>
#include "liquid.hpp"

auto global = signal(0);

Element Example()
{
    auto doubled = memo(global() * 2);
    auto numbers = std::vector<int>{1, 2, 3};

    effect({
        printf("EFFECT: Global is %d\n", global());
    });

    return fragment({
        text("TEXT: Global is " + std::to_string(global()) + "\n"),
        text("TEXT: Doubled is " + std::to_string(doubled()) + "\n"),

        WHEN(global() == 0)
            text("WHEN: Global is zero\n"),
        THEN(global() == 1)
            text("WHEN: Global is one\n"),
        OTHERWISE
            text("WHEN: Global is large\n"),
        END,

        EACH(numbers, n, i)
            text("EACH: Number[" + std::to_string(i) + "] is " + std::to_string(n) + "\n"),
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

    return 0;
}