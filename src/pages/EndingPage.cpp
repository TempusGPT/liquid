#include "EndingPage.hpp"
#include "libs/game/stores.hpp"
#include "libs/router.hpp"

using namespace liquid;

auto EndingPage() -> Element {
    auto input = Input();

    input({ Key::Enter }, []() {
        stage::reset();
        navigate("/");
    });

    return Group({
        Text("Congratulations!\n"),
        Text("Press enter to go back to the main menu.\n"),
    });
}
