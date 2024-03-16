#include <string>

#include "liquid.hpp"
#include "pages/MainMenu.hpp"

using namespace Liquid;

int main() {
    const auto element = Group({
        Route("/", MainMenu),
    });

    return render(element);
}
