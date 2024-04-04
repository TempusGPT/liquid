#ifndef PAGES_MAINPAGE_HPP
#define PAGES_MAINPAGE_HPP

#include "libs/router.hpp"
#include "liquid.hpp"

using namespace liquid;

auto MainPage() -> Element {
    auto input = Input();

    input.bind({ Key::Enter }, []() {
        navigate("/play");
    });

    return Group({
        Text("Snake Game!"),
        Goto(0, 2),
        Text("Move the snake with the arrow keys to eat as many apples as possible."),
        Goto(0, 3),
        Text("Press enter to continue..."),
    });
}

#endif
