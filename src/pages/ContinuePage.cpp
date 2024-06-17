#include "ContinuePage.hpp"
#include "libs/game/stores.hpp"
#include "libs/router.hpp"

using namespace liquid;

auto ContinuePage() -> Element {
    auto input = Input();

    input({ Key::Enter }, []() {
        stage::moveNext();
        navigate("/play");
    });

    return Group({
        Text("Stage "),
        Text("%0% "_f % stage::current().name),
        Text("completed!\n"),
        Text("Press enter to continue.\n"),
    });
}
