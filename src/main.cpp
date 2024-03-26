#include <string>

#include "liquid.hpp"
#include "pages/MainPage.hpp"
#include "pages/PlayPage.hpp"

using namespace Liquid;

auto main() -> int {
    std::vector vec = { 1, 2, 3 };
    auto element = Group({
        Route("/", MainPage),
        Route("/play", PlayPage),
    });

    return render(element);
}
