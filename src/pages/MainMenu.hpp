#ifndef PAGES_MAINMENU_HPP
#define PAGES_MAINMENU_HPP

#include "components/Timer.hpp"
#include "liquid.hpp"

Element MainMenu() {
    auto signal = createSignal(0);
    auto title = createSignal("MainMenu");
    auto numbers = createSignal(std::vector<int> { 1, 2 });

    createEffect([=]() mutable {
        if (signal() == 0 && untrack(title) == "MainMenu!!!!!") {
            playBeep();
        }
    });

    bindInput({ Key::UpArrow }, [=]() mutable {
        signal.set(signal() + 1);
    });

    bindInput({ Key::DownArrow }, [=]() mutable {
        signal.set(signal() - 1);
    });

    bindInput({ Key::LeftArrow }, [=]() mutable {
        title.set(title() + "!");
    });

    bindInput({ Key::RightArrow }, [=]() mutable {
        const auto last = numbers()[numbers().size() - 1];
        numbers().push_back(last * 2);
        numbers.set();
    });

    bindInput({ Key::Q, Key::Enter }, []() {
        exitApp();
    });

    return Group({
        Timer(FN(title())),
        Text(FN(format("Signal is {0}\n", signal()))),

        WHEN(signal() < 0) {
            Text("Signal is negative\n"),
        } OR(signal() > 0) {
            Text("Signal is positive\n"),
        } OTHERWISE {
            Text("Signal is zero\n"),
        } END_WHEN,

        Text("\n"),
        EACH(numbers(), n, i) {
            Text(format("{0}th Number is {1}\n", i, n)),
        } END_EACH,
    });
}

#endif
