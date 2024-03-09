#ifndef PAGES_MAINMENU_HPP
#define PAGES_MAINMENU_HPP

#include "components/Timer.hpp"
#include "liquid.hpp"

Element MainMenu() {
    const auto numbers = std::vector<int> { 2, 4, 8, 16 };

    auto signal = createSignal(0);
    auto title = createSignal("MainMenu");

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

    bindInput({ Key::Space }, [=]() mutable {
        title.set(title() + "!");
    });

    bindInput({ Key::Q, Key::Enter }, []() {
        exitApp();
    });

    return Div({
        Text(FN f("Signal is {0}\n", signal()) ENDFN),

        WHEN(signal() < 0) {
            Timer("Signal is negative"),
        } OR(signal() > 0) {
            Timer("Signal is positive"),
        } OTHERWISE {
            Timer("Signal is zero"),
        } END,

        // EACH(numbers, n, i) {
        //     Text(f("{0}th number is {1}\n", i, n)),
        // } X,
    });
}

#endif
