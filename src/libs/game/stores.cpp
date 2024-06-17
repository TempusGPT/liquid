#include "stores.hpp"
#include "liquid.hpp"

#include <array>

using namespace liquid;

namespace stage {
    constexpr auto STAGES = std::array<std::string_view, 4> {
        "tutorial",
        "alpha",
        "beta",
        "finale",
    };

    auto currentIndex = 0;
    auto currentValue = Stage(std::string(STAGES[currentIndex]));

    auto current() -> Stage {
        return currentValue;
    }

    auto moveNext() -> void {
        currentIndex += 1;
        currentValue = Stage(std::string(STAGES[currentIndex]));
    }

    auto reset() -> void {
        currentIndex = 0;
        currentValue = Stage(std::string(STAGES[currentIndex]));
    }

    auto isLast() -> bool {
        return currentIndex == STAGES.size() - 1;
    }
}

namespace score {
    auto lengthState = State<int>();
    auto maxLengthState = State<int>();
    auto honeyAppleState = State<int>();
    auto poisonAppleState = State<int>();
    auto gateState = State<int>();

    auto length() -> int {
        return *lengthState;
    }

    auto maxLength() -> int {
        return *maxLengthState;
    }

    auto honeyApple() -> int {
        return *honeyAppleState;
    }

    auto poisonApple() -> int {
        return *poisonAppleState;
    }

    auto gate() -> int {
        return *gateState;
    }

    auto initialize() -> void {
        lengthState = ::stage::currentValue.snake.size();
        maxLengthState = ::stage::currentValue.snake.size();
        honeyAppleState = 0;
        poisonAppleState = 0;
        gateState = 0;
    }

    auto eatHoneyApple() -> void {
        honeyAppleState = *honeyAppleState + 1;
        lengthState = *lengthState + 1;
        maxLengthState = std::max(*maxLengthState, *lengthState);
    }

    auto eatPoisonApple() -> void {
        poisonAppleState = *poisonAppleState + 1;
        lengthState = *lengthState - 1;
    }

    auto enterGate() -> void {
        gateState = *gateState + 1;
    }
}
