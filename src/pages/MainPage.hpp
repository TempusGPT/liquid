#ifndef PAGES_MAINPAGE_HPP
#define PAGES_MAINPAGE_HPP

#include "liquid.hpp"

using namespace Liquid;

Element MainPage() {
    auto input = useInput();

    input.bind({ Key::Enter }, []() {
        beep();
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
