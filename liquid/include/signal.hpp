#ifndef LIQUID_SIGNAL_HPP
#define LIQUID_SIGNAL_HPP

#include "app.hpp"
#include "effect.hpp"

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Liquid {
    namespace Internal {
        inline auto track = true;
    }

    template <typename T>
    class Signal {
    public:
        Signal(const T& value) : value(std::make_shared<T>(value)) {}

        auto operator()() const -> T {
            if (
                Internal::track &&
                Internal::effectCallback &&
                effectMap->find(Internal::effectId) == effectMap->end()
            ) {
                effectMap->insert({ Internal::effectId, Internal::effectCallback });
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
        const std::shared_ptr<std::map<int, std::function<void()>>> effectMap =
            std::make_shared<std::map<int, std::function<void()>>>();
    };

    template <typename T>
    auto untrack(const Signal<T>& signal) -> T {
        Internal::track = false;
        auto value = signal();
        Internal::track = true;
        return value;
    }

    template <typename T>
    auto createSignal(const T& value = T()) -> Signal<T> {
        return Signal<T>(value);
    }

    auto createSignal(const char* value) -> Signal<std::string>;
}

#endif
