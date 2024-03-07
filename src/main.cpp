#include <clocale>
#include <string>

#include "liquid.hpp"

auto global = SIGNAL(0);

Element Example()
{
    const auto numbers = std::vector<int>{1, 2, 3};

    auto doubled = COMPUTED(global() * 2);

    EFFECT({
        printw("EFFECT: Global is %d\n", global());
    });

    return FRAGMENT({
        text("TEXT: Global is " + std::to_string(global()) + "\n"),
        text("TEXT: Doubled is " + std::to_string(doubled()) + "\n"),

        IF(global() == 0)
            text("IF: Global is zero\n"),
        ELIF(global() == 1)
            text("IF: Global is one\n"),
        ELSE
            text("IF: Global is large\n"),
        END,

        FOR(numbers, n, i)
            text("FOR: Number[" + std::to_string(i) + "] is " + std::to_string(n) + "\n"),
        END,

        text("\n"),
    });
}

int main()
{
    setlocale(LC_ALL, "");
    initscr();
    clear();

    const auto example = Example();

    example();
    global.set(1);
    example();
    global.set(2);
    example();

    refresh();

    getch();
    endwin();
    return 0;
}