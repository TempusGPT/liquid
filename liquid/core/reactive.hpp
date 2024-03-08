#ifndef LIQUID_REACTIVE_HPP
#define LIQUID_REACTIVE_HPP

#include <unordered_map>

namespace Liquid {
    bool isDirty = true;
    std::function<void()> effectCallback = nullptr;
    int effectCallbackId = 0;

    template <typename T>
    class Signal {
    public:
        Signal(const T &value)
            : value(std::make_shared<T>(value)),
              effects(std::make_shared<std::unordered_map<int, std::function<void()>>>()) {}

        T operator()() {
            if (effectCallback && effects->find(effectCallbackId) == effects->end()) {
                effects->insert({ effectCallbackId, effectCallback });
            }

            return *value;
        }

        void set(const T &newValue) {
            isDirty = true;
            *value = newValue;

            for (auto effect : *effects) {
                effect.second();
            }
        }

    private:
        std::shared_ptr<T> value;
        std::shared_ptr<std::unordered_map<int, std::function<void()>>> effects;
    };
}

template <typename T>
Liquid::Signal<T> createSignal(const T &value) {
    return Liquid::Signal<T>(value);
}

Liquid::Signal<std::string> createSignal(const char *value) {
    return Liquid::Signal<std::string>(value);
}

void createEffect(const std::function<void()> &callback) {
    Liquid::effectCallback = callback;
    Liquid::effectCallback();
    Liquid::effectCallback = nullptr;
    Liquid::effectCallbackId += 1;
}

#endif