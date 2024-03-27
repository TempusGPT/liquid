#include <string>

#include "liquid.hpp"
#include "pages/MainPage.hpp"
#include "pages/PlayPage.hpp"

using namespace Liquid;

auto main() -> int {
    auto element = Group({
        Route("/", MainPage),
        Route("/play", PlayPage),
    });

    return render(element);
}

// #include "liquid.hpp"

// using namespace Liquid;

// auto MainPage() -> Element {
//     auto lifecycle = useLifecycle();

//     auto id = setInterval(1000, []() {
//         navigate("/play");
//     });

//     lifecycle.cleanup([=]() {
//         clearTimer(id);
//     });

//     return Text("MainPage: %0%"_f % id);
// }

// auto PlayPage() -> Element {
//     auto lifecycle = useLifecycle();

//     auto id = setInterval(1500, []() {
//         navigate("/");
//     });

//     lifecycle.cleanup([=]() {
//         clearTimer(id);
//     });

//     return Text("PlayPage: %0%"_f % id);
// }

// auto main() -> int {
//     auto element = Group({
//         Route("/", MainPage),
//         Route("/play", PlayPage),
//     });

//     return render(element);
// };