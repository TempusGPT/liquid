#include "MainPage.hpp"
#include "libs/router.hpp"

using namespace liquid;

auto MainPage() -> Element {
    auto input = Input();

    input({ Key::Enter }, []() {
        navigate("/play");
    });

    return Group({
        Text("Snake Game!"),
        Cursor(0, 2),
        Text("Move the snake with the arrow keys to eat as many apples as possible."),
        Cursor(0, 3),
        Text("Press enter to continue..."),
    });
}