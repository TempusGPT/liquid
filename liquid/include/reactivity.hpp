#ifndef LIQUID_REACTIVITY_HPP
#define LIQUID_REACTIVITY_HPP

#include "app.hpp"

#include <functional>
#include <memory>
#include <unordered_set>

namespace Liquid {
    class Effect;
}

namespace std {
    template <>
    struct hash<Liquid::Effect> {
        size_t operator()(const Liquid::Effect &effect) const;
    };
}

namespace Liquid {
    class Effect {  
        friend struct std::hash<Liquid::Effect>;

    public:
        static int newId;
        static Effect current;

        Effect();
        Effect(int id, const std::function<void()> &callback);

        void operator()();
        bool operator==(const Effect &other) const;
        operator bool() const;

    private:
        int id;
        std::function<void()> callback;
    };
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
    friend T untrack<T>(const Signal<T> &signal);
    friend Signal<T> createSignal<T>(const T &value);
    friend Signal<std::string> createSignal(const char *value);

public:
    T operator()() {
        if (Liquid::Effect::current && effects->find(Liquid::Effect::current) == effects->end()) {
            auto effect = Liquid::Effect::current;
            effects->insert(effect);
        }

        return *value;
    }

    void set(const T &newValue) {
        App::isDirty = true;
        *value = newValue;

        for (auto effect : *effects) {
            effect();
        }
    }

private:
    std::shared_ptr<T> value;
    std::shared_ptr<std::unordered_set<Liquid::Effect>> effects;

    Signal(const T &value)
        : value(std::make_shared<T>(value)),
          effects(std::make_shared<std::unordered_set<Liquid::Effect>>()) {}
};

#endif
