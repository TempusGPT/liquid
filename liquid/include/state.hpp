#ifndef LIQUID_STATE_HPP
#define LIQUID_STATE_HPP

#include "app.hpp"
#include "effect.hpp"
#include "ref.hpp"

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
        State(const T& value = T()) : ref(value) {}

        auto operator*() -> T& {
            registerEffect();
            return *ref;
        }

        auto operator*() const -> const T& {
            registerEffect();
            return *ref;
        }

        auto operator->() -> T* {
            registerEffect();
            return ref.operator->();
        }

        auto operator->() const -> const T* {
            registerEffect();
            return ref.operator->();
        }

        auto operator=(const T& newValue) -> State<T>& {
            detail::markDirty();
            *ref = newValue;

            for (const auto& [id, callback] : *effectMap) {
                detail::runEffect(id, callback);
            }
            return *this;
        }

    private:
        Ref<T> ref;
        const std::shared_ptr<std::map<int, std::function<std::function<void()>()>>> effectMap =
            std::make_shared<std::map<int, std::function<std::function<void()>()>>>();

        auto registerEffect() const -> void {
            if (
                detail::track &&
                detail::effectCallback &&
                effectMap->find(detail::effectId) == effectMap->end()
            ) {
                effectMap->insert({ detail::effectId, detail::effectCallback });
            }
        }
    };

    template <typename T>
    auto untrack(const State<T>& state) -> T {
        detail::track = false;
        auto value = *state;
        detail::track = true;
        return value;
    }

    auto untrack(const std::function<void()>& callback) -> void;
}

#endif
