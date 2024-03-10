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
        auto newValue = numbers();
        newValue.push_back(last * 2);
        numbers.set(newValue);
    });

    bindInput({ Key::Q, Key::Enter }, []() {
        exitApp();
    });

    return Div({
        Timer(FN title() ENDFN),
        Text(FN f("Signal is {0}\n", signal()) ENDFN),

        WHEN(signal() < 0) {
            Text(FN "Signal is negative\n" ENDFN),
        } OR(signal() > 0) {
            Text(FN "Signal is positive\n" ENDFN),
        } OTHERWISE {
            Text(FN "Signal is zero\n" ENDFN),
        } END,

        Text("\n"),
        EACH(numbers(), n, i) {
            Text(f("{0}th Number is {1}\n", i, n)),
        } ENDEACH,
    });
}

#endif
