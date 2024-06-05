#include "mission.hpp"

using namespace liquid;

auto Mission(const Prop<std::size_t>& initialLength, Ref<MissionRef>& ref) -> Element {
    auto currentLength = State(*initialLength);
    auto maxLength = State(*initialLength);
    auto honeyAppleCount = State(0);
    auto poisonedAppleCount = State(0);
    auto gateCount = State(0);

    auto increaseHoneyAppleCount = [=]() mutable {
        honeyAppleCount = *honeyAppleCount + 1;
        currentLength = *currentLength + 1;
        maxLength = std::max(*maxLength, *currentLength);
    };

    auto increasePoisonedAppleCount = [=]() mutable {
        poisonedAppleCount = *poisonedAppleCount + 1;
        currentLength = *currentLength - 1;
    };

    auto increaseGateCount = [=]() mutable {
        gateCount = *gateCount + 1;
    };

    *ref = { increaseHoneyAppleCount, increasePoisonedAppleCount, increaseGateCount };

    return Group({
        Text(GET("Current Length: %0%"_f % *currentLength)),
        Cursor(0, 1),
        Text(GET("Max Length: %0%"_f % *maxLength)),
        Cursor(0, 2),
        Text(GET("Honey Apple: %0%"_f % *honeyAppleCount)),
        Cursor(0, 3),
        Text(GET("Poisoned Apple: %0%"_f % *poisonedAppleCount)),
        Cursor(0, 4),
        Text(GET("Gate: %0%"_f % *gateCount)),
    });
}
