#include "GameOverPage.hpp"
#include "libs/game/stores.hpp"
#include "libs/router.hpp"

using namespace liquid;

auto GameOverPage() -> Element {
    auto input = Input();

    input({ Key::Enter }, []() {
        stage::reset();
        navigate("/");
    });

    return Group({
        Text("Game Over\n"),
        Text("Press enter to go back to the main menu.\n"),
    });
}
