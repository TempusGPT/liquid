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

    return Group({
        Goto(0, 10),
        Group({
            Goto(0, 0),
            Text("[Main Menu]\n"),
        }),

        Goto(0, 0),
        WHEN(count() % 2 == 0) {
            Text(RP(format("Even: {0}\n", count()))),
        } OTHERWISE {
            Text(RP(format("Odd: {0}\n", count()))),
        } END_WHEN,
    });
}

Element OtherPage() {
    auto count = createSignal(0);
    auto numbers = createSignal<std::vector<int>>({ 1, 2 });

    bindInput({ Key::A }, [=]() mutable {
        count.set(count() + 1);
    });

    bindInput({ Key::RightArrow }, [=]() mutable {
        auto newNumbers = numbers();
        const auto last = newNumbers[numbers().size() - 1];
        newNumbers.push_back(last * 2);
        numbers.set(newNumbers);
    });

    // bindInput({ Key::S }, []() {
    //     navigate("/");
    // });

    return Group({
        Text("[Other Menu]\n"),

        WHEN(count() % 2 == 0) {
            Text(RP(format("Even: {0}\n", count()))),
        } OTHERWISE {
            Text(RP(format("Odd: {0}\n", count()))),
        } END_WHEN,

        EACH(numbers(), n, i) {
            Text(format("{0}th Number is {1}\n", i, n)),
        } END_EACH,
    });
}

int main() {
    const auto element = Group({
        Route("/", MainPage),
        Route("/other", OtherPage),
    });

    return render(element);
}
