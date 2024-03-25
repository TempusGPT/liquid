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
        auto currentEffect() -> std::tuple<int, std::function<void()>>;
        auto runEffect(int id, const std::function<void()>& callback) -> void;
    }

    auto createEffect(const std::function<void()>& callback) -> void;

    template <typename T>
    class Signal;

    template <typename T>
    auto untrack(const Signal<T>& signal) -> T {
        return *signal.value;
    }

    template <typename T>
    auto createSignal(const T& value) -> Signal<T> {
        return Signal<T>(value);
    }

    auto createSignal(const char* value) -> Signal<std::string>;

    template <typename T>
    class Signal {
        friend auto untrack<T>(const Signal<T>& signal) -> T;
        friend auto createSignal<T>(const T& value) -> Signal<T>;
        friend auto createSignal(const char* value) -> Signal<std::string>;

    public:
        auto operator()() const -> T {
            auto [id, callback] = Internal::currentEffect();
            if (callback && effectMap->find(id) == effectMap->end()) {
                effectMap->insert({ id, callback });
            }

            return *value;
        }

        auto set(const T& newValue) -> void {
            Internal::markDirty();
            *value = newValue;

            for (const auto& [id, callback] : *effectMap) {
                Internal::runEffect(id, callback);
            }
        }

    private:
        const std::shared_ptr<T> value;
        const std::shared_ptr<std::map<int, std::function<void()>>> effectMap;

        Signal(const T& value)
            : value(std::make_shared<T>(value)),
              effectMap(std::make_shared<std::map<int, std::function<void()>>>()) {}
    };
}

#endif
