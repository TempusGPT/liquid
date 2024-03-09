#include "include/reactive.hpp"

#include <string>

namespace Liquid {
    bool isDirty = false;
    std::function<void()> effectCallback = nullptr;
    int effectCallbackId = 0;
}

Signal<std::string> createSignal(const char *value) {
    return Signal<std::string>(value);
}

void createEffect(const std::function<void()> &callback) {
    Liquid::effectCallback = callback;
    Liquid::effectCallback();
    Liquid::effectCallback = nullptr;
    Liquid::effectCallbackId += 1;
}
