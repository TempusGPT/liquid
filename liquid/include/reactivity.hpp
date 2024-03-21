#ifndef LIQUID_REACTIVITY_HPP
#define LIQUID_REACTIVITY_HPP

#include "app.hpp"

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Liquid {
    namespace Internal {
        struct EffectData {
            int id;
            std::function<void()> callback;
        };

        EffectData currentEffect();
    }

    class Effect;
    Effect createEffect();

    class Effect {
        friend Effect createEffect();

    public:
        ~Effect();
        void operator()(const std::function<void()> &callback);
        void cleanup(const std::function<void()> &callback);

    private:
        std::vector<std::function<void()>> callbacks;
        std::vector<std::function<void()>> cleanupCallbacks;
    };

    template <typename T>
    class Signal;

    template <typename T>
    T untrack(const Signal<T> &signal) {
        return *signal.value;
    }

    template <typename T>
    Signal<T> createSignal(const T &value) {
        return Signal<T>(value);
    }

    Signal<std::string> createSignal(const char *value);

    template <typename T>
    class Signal {
        friend T untrack<T>(const Signal<T> &signal);
        friend Signal<T> createSignal<T>(const T &value);
        friend Signal<std::string> createSignal(const char *value);

    public:
        T operator()() const {
            const auto effect = Internal::currentEffect();
            if (effect.callback && effectMap->find(effect.id) == effectMap->end()) {
                effectMap->insert({ effect.id, effect.callback });
            }

            return *value;
        }

        void set(const T &newValue) {
            Internal::markDirty();
            *value = newValue;

            for (const auto &effect : *effectMap) {
                effect.second();
            }
        }

    private:
        const std::shared_ptr<T> value;
        const std::shared_ptr<std::map<int, std::function<void()>>> effectMap;

        Signal(const T &value)
            : value(std::make_shared<T>(value)),
              effectMap(std::make_shared<std::map<int, std::function<void()>>>()) {}
    };
}

#endif
