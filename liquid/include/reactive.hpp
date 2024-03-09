#ifndef LIQUID_REACTIVE_HPP
#define LIQUID_REACTIVE_HPP

#include <functional>
#include <memory>
#include <unordered_map>

namespace Liquid {
    extern bool isDirty;
    extern std::function<void()> effectCallback;
    extern int effectCallbackId;
}

template <typename T>
class Signal;

template <typename T>
Signal<T> createSignal(const T &value) {
    return Signal<T>(value);
}

Signal<std::string> createSignal(const char *value);
void createEffect(const std::function<void()> &callback);

template <typename T>
T untrack(const Signal<T> &signal) {
    return *signal.value;
}

template <typename T>
class Signal {
public:
    friend T untrack<T>(const Signal<T> &signal);
    friend Signal<T> createSignal<T>(const T &value);
    friend Signal<std::string> createSignal(const char *value);

    T operator()() {
        if (Liquid::effectCallback && effects->find(Liquid::effectCallbackId) == effects->end()) {
            effects->insert({ Liquid::effectCallbackId, Liquid::effectCallback });
        }

        return *value;
    }

    void set(const T &newValue) {
        Liquid::isDirty = true;
        *value = newValue;

        for (auto effect : *effects) {
            effect.second();
        }
    }

private:
    std::shared_ptr<T> value;
    std::shared_ptr<std::unordered_map<int, std::function<void()>>> effects;

    Signal(const T &value)
        : value(std::make_shared<T>(value)),
          effects(std::make_shared<std::unordered_map<int, std::function<void()>>>()) {}
};

#endif
