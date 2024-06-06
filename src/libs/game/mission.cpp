#include "mission.hpp"

using namespace liquid;

auto ch(bool done) -> char {
    return done ? 'v' : ' ';
}

auto Mission(
    const Prop<int>& initialLength,
    const Prop<int>& targetLength,
    const Prop<int>& targetHoneyApple,
    const Prop<int>& targetPoisonApple,
    const Prop<int>& targetGate,
    const Prop<std::function<void()>>& onComplete,
    Ref<MissionRef>& ref
) -> Element {
    auto effect = Effect();

    auto length = State(*initialLength);
    auto maxLength = State(*initialLength);
    auto honeyApple = State(0);
    auto poisonApple = State(0);
    auto gate = State(0);

    auto maxLengthDone = Memo<bool>(GET(*maxLength >= *targetLength));
    auto honeyAppleDone = Memo<bool>(GET(*honeyApple >= *targetHoneyApple));
    auto poisonAppleDone = Memo<bool>(GET(*poisonApple >= *targetPoisonApple));
    auto gateDone = Memo<bool>(GET(*gate >= *targetGate));

    auto eatHoneyApple = [=]() mutable {
        honeyApple = *honeyApple + 1;
        length = *length + 1;
    };

    auto eatPoisonApple = [=]() mutable {
        poisonApple = *poisonApple + 1;
        length = *length - 1;
    };

    auto enterGate = [=]() mutable {
        gate = *gate + 1;
    };

    *ref = { eatHoneyApple, eatPoisonApple, enterGate };

    effect([=]() mutable {
        maxLength = std::max(untrack(maxLength), *length);
    });

    effect([=]() {
        if (*maxLengthDone && *honeyAppleDone && *poisonAppleDone && *gateDone) {
            (*onComplete)();
        }
    });

    return Group({
        Text("Score Board"),
        Cursor(0, 1),
        Text(GET("B: %0% / %1%"_f % *length % *maxLength)),
        Cursor(0, 2),
        Text(GET("+: %0%"_f % *honeyApple)),
        Cursor(0, 3),
        Text(GET("-: %0%"_f % *poisonApple)),
        Cursor(0, 4),
        Text(GET("G: %0%"_f % *gate)),

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
