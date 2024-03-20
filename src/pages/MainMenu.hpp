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

    effect([=]() {
        if (signal() == 0 && untrack(title) == "MainMenu!!!!!") {
            beep();
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
        newNumbers.push_back(newNumbers.back() * 2);
        numbers.set(newNumbers);
    });

    bindInput({ Key::Q, Key::Enter }, []() {
        exit();
    });

    return Group({
        Timer(FN(title())),
        Text(FN("Signal is %0%\n"_f % signal())),

        WHEN(signal() < 0) {
            Text("Signal is negative\n"),
        } OR(signal() > 0) {
            Text("Signal is positive\n"),
        } OTHERWISE {
            Text("Signal is zero\n"),
        } END_WHEN,

        Text("\n"),
        EACH(numbers(), n, i) {
            Text("%0%th Number is %1%\n"_f % i % n),
        } END_EACH,
    });
}

#endif
