#include "liquid.hpp"

Element HomePage()
{
    auto count = signal(1);
    auto doubled = memo(count() * 2);

    effect({
        printf("Effect Count: %d\n", count());
        printf("Effect Doubled: %d\n", doubled());
    });

    count.set(2);

    return fragment({
        text("Count: " + std::to_string(count()) + "\n"),
        text("Doubled: " + std::to_string(doubled()) + "\n"),
    });
}