#ifndef PAGES_MAINMENU_HPP
#define PAGES_MAINMENU_HPP

#include "components/Timer.hpp"
#include "liquid.hpp"

using namespace Liquid;

Element MainMenu() {
    auto effect = createEffect();
    auto signal = createSignal(0);
    auto title = createSignal("MainMenu");
    auto numbers = createSignal<std::vector<int>>({ 1, 2 });

    effect([=]() mutable {
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
        auto newNumbers = numbers();
        const auto last = newNumbers[numbers().size() - 1];
        newNumbers.push_back(last * 2);
        numbers.set(newNumbers);
    });

    bindInput({ Key::Q, Key::Enter }, []() {
        exitApp();
    });

    return Group({
        Timer(RP title() END_RP),
        Text(RP format("Signal is {0}\n", signal()) END_RP),

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
