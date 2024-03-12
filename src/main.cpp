#include <string>

#include "liquid.hpp"

Element MainPage() {
    auto count = createSignal(0);

    bindInput({ Key::Q }, [=]() mutable {
        count.set(count() + 1);
    });

    bindInput({ Key::W }, [=]() mutable {
        navigate("/other");
    });

    return Div({
        Text("[Main Menu]\n"),

        WHEN(count() % 2 == 0) {
            Text(FN(f("Even: {0}\n", count()))),
        } OTHERWISE {
            Text(FN(f("Odd: {0}\n", count()))),
        } END_WHEN,
    });
}

Element OtherPage() {
    auto count = createSignal(0);

    bindInput({ Key::A }, [=]() mutable {
        count.set(count() + 1);
    });

    bindInput({ Key::S }, [=]() mutable {
        navigate("/");
    });

    return Div({
        Text("[Other Menu]\n"),

        WHEN(count() % 2 == 0) {
            Text(FN(f("Even: {0}\n", count()))),
        } OTHERWISE {
            Text(FN(f("Odd: {0}\n", count()))),
        } END_WHEN,
    });
}

int main() {
    const auto app = Div({
        Route("/", MainPage),
        Route("/other", OtherPage),
    });

    return render(app);
}
