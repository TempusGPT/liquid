#ifndef LIQUID_SIGNAL_HPP
#define LIQUID_SIGNAL_HPP

#include "app.hpp"
#include "effect.hpp"

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace liquid {
    namespace detail {
        inline auto track = true;
    }

    template <typename T>
    class State {
    public:
        State(const T& value = T()) : value(std::make_shared<T>(value)) {}
        State(const char* value) : value(std::make_shared<std::string>(value)) {}

        auto operator()() const -> T {
            if (
                detail::track &&
                detail::effectCallback &&
                effectMap->find(detail::effectId) == effectMap->end()
            ) {
                effectMap->insert({ detail::effectId, detail::effectCallback });
            }

            return *value;
        }

        auto set(const T& newValue) -> void {
            detail::markDirty();
            *value = newValue;

            for (const auto& [id, callback] : *effectMap) {
                detail::runEffect(id, callback);
            }
        }

    private:
        const std::shared_ptr<T> value;
        const std::shared_ptr<std::map<int, std::function<void()>>> effectMap =
            std::make_shared<std::map<int, std::function<void()>>>();
    };

    template <typename T>
    State(const T&) -> State<T>;
    State(const char*) -> State<std::string>;

    template <typename T>
    auto untrack(const State<T>& signal) -> T {
        detail::track = false;
        auto value = signal();
        detail::track = true;
        return value;
    }

    auto untrack(const std::function<void()>& callback) -> void;
}

#endif
