#include "libs/router.hpp"
#include "liquid.hpp"
#include "pages/ContinuePage.hpp"
#include "pages/GameOverPage.hpp"
#include "pages/MainPage.hpp"
#include "pages/PlayPage.hpp"

auto main() -> int {
    auto element = Router({
        { "/", MainPage },
        { "/play", PlayPage },
        { "/continue", ContinuePage },
        { "/gameover", GameOverPage },
    });

    return liquid::render(element, { 80, 25 });
}
