#include "libs/router.hpp"
#include "liquid.hpp"
#include "pages/MainPage.hpp"
#include "pages/PlayPage.hpp"

using namespace liquid;

auto main() -> int {
    auto element = Router({
        { "/", MainPage },
        { "/play", PlayPage },
    });

    return render(element);
}
