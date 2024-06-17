#include "mission.hpp"
#include "stores.hpp"

using namespace liquid;

auto ch(bool done) -> char {
    return done ? 'v' : ' ';
}

auto Mission(
    const Prop<int>& targetLength,
    const Prop<int>& targetHoneyApple,
    const Prop<int>& targetPoisonApple,
    const Prop<int>& targetGate,
    const Prop<std::function<void()>>& onComplete
) -> Element {
    auto effect = Effect();

    auto maxLengthDone = Memo<bool>(GET(score::maxLength() >= *targetLength));
    auto honeyAppleDone = Memo<bool>(GET(score::honeyApple() >= *targetHoneyApple));
    auto poisonAppleDone = Memo<bool>(GET(score::poisonApple() >= *targetPoisonApple));
    auto gateDone = Memo<bool>(GET(score::gate() >= *targetGate));

    effect([=]() {
        if (*maxLengthDone && *honeyAppleDone && *poisonAppleDone && *gateDone) {
            (*onComplete)();
        }
    });

    return Group({
        Text("Score Board"),
        Cursor(0, 1),
        Text(GET("B: %0% / %1%"_f % score::length() % score::maxLength())),
        Cursor(0, 2),
        Text(GET("+: %0%"_f % score::honeyApple())),
        Cursor(0, 3),
        Text(GET("-: %0%"_f % score::poisonApple())),
        Cursor(0, 4),
        Text(GET("G: %0%"_f % score::gate())),

        Cursor(0, 6),
        Text("Mission"),
        Cursor(0, 7),
        Text(GET("B: %0% (%1%)"_f % *targetLength % ch(*maxLengthDone))),
        Cursor(0, 8),
        Text(GET("+: %0% (%1%)"_f % *targetHoneyApple % ch(*honeyAppleDone))),
        Cursor(0, 9),
        Text(GET("-: %0% (%1%)"_f % *targetPoisonApple % ch(*poisonAppleDone))),
        Cursor(0, 10),
        Text(GET("G: %0% (%1%)"_f % *targetGate % ch(*gateDone))),
    });
}
