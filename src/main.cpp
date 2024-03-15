#include <string>

#include "liquid.hpp"

using namespace Liquid;

Element MainPage() {
    auto effect = createEffect();
    auto count = createSignal(0);

    bindInput({ Key::Q }, [=]() mutable {
        count.set(count() + 1);
    });

    bindInput({ Key::W }, []() {
        navigate("/other");
    });

    effect.cleanup([]() {
        bindInput({ Key::S }, []() {
            navigate("/");
        });
    });

    return Div({
        Text("[Main Menu]\n"),

        WHEN(count() % 2 == 0) {
            Text(FN format("Even: {0}\n", count()) END_FN),
        } OTHERWISE {
            Text(FN format("Odd: {0}\n", count()) END_FN),
        } END_WHEN,
    });
}

Element OtherPage() {
    auto count = createSignal(0);

    bindInput({ Key::A }, [=]() mutable {
        count.set(count() + 1);
    });

    // bindInput({ Key::S }, []() {
    //     navigate("/");
    // });

    return Div({
        Text("[Other Menu]\n"),

        WHEN(count() % 2 == 0) {
            Text(FN format("Even: {0}\n", count()) END_FN),
        } OTHERWISE {
            Text(FN format("Odd: {0}\n", count()) END_FN),
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
