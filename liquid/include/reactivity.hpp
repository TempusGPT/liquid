#ifndef LIQUID_REACTIVITY_HPP
#define LIQUID_REACTIVITY_HPP

#include "app.hpp"

#include <functional>
#include <memory>
#include <vector>

namespace Liquid {
    class Effect;

    Effect createEffect();

    class Effect {
        friend Effect createEffect();

    public:
        class Data {
        public:
            Data();
            Data(const std::function<void()> &callback);

            static Data &getCurrent();

            void run() const;
            bool operator==(const Data &other) const;
            operator bool() const;

        private:
            static Data current;
            static int newId;

            int id;
            std::function<void()> callback;
        };

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
        T &operator()() {
            const auto &currentEffect = Effect::Data::getCurrent();
            const auto iter = std::find(effects->begin(), effects->end(), currentEffect);

            if (currentEffect && iter == effects->end()) {
                effects->push_back(currentEffect);
            }
            return *value;
        }

        void set(const T &newValue) {
            Internal::markDirty();
            *value = newValue;

            for (auto effect : *effects) {
                effect.run();
            }
        }

    private:
        std::shared_ptr<T> value;
        std::shared_ptr<std::vector<Effect::Data>> effects;

        Signal(const T &value)
            : value(std::make_shared<T>(value)),
              effects(std::make_shared<std::vector<Effect::Data>>()) {}
    };
}

#endif
