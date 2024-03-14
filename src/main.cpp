#include <string>

#include "liquid.hpp"

using namespace Liquid;

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
            Text(FN(format("Even: {0}\n", count()))),
        } OTHERWISE {
            Text(FN(format("Odd: {0}\n", count()))),
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
            Text(FN(format("Even: {0}\n", count()))),
        } OTHERWISE {
            Text(FN(format("Odd: {0}\n", count()))),
        } END_WHEN,
    });
}

int main() {
    const auto element = Div({
        Route("/", MainPage),
        Route("/other", OtherPage),
    });

    return render(element);
}
