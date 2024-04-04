#include "libs/router.hpp"
#include "liquid.hpp"
#include "pages/MainPage.hpp"
#include "pages/PlayPage.hpp"

using namespace liquid;

auto main() -> int {
    auto element = Group({
        Route("/", MainPage),
        Route("/play", PlayPage),
    });

    return render(element);
}
