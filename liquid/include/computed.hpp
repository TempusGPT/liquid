#ifndef LIQUID_COMPUTED_HPP
#define LIQUID_COMPUTED_HPP

#include "effect.hpp"
#include "state.hpp"

namespace liquid {
    template <typename T>
    class Computed {
    public:
        Computed(const std::function<T()>& compute) {
            detail::runEffect([=, state = state]() mutable {
                state = compute();
                return nullptr;
            });
        }

        auto operator*() const -> T& {
            return *state;
        }

        auto operator->() const -> T* {
            return state.operator->();
        }

    private:
        State<T> state;
    };
}

#endif
