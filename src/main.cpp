#include <string>

#include "liquid.hpp"
// #include "pages/MainMenu.hpp"

Element MainMenu() {
    auto count = createSignal(0);

    bindInput({ Key::Space }, [=]() mutable {
        count.set(count() + 1);
    });

    return createElement().with({
        WHEN(count() % 2 == 0) {
            Text(FN(f("Count: {0}\n", count()))),
            Text(FN(f("Count: {0}\n", count()))),
        } END_WHEN,
    });
}

int main() {
    return initializeApp()
        .route("MainMenu", MainMenu)
        .run("MainMenu");
}
