#include "include/signal.hpp"

namespace Liquid {
    auto createSignal(const char* value) -> Signal<std::string> {
        return Signal<std::string>(value);
    }
}
