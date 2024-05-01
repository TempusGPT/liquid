#ifndef LIQUID_DERIVED_HPP
#define LIQUID_DERIVED_HPP

#include "effect.hpp"
#include "state.hpp"

namespace liquid {
    template <typename T>
    class Derived {
    public:
        Derived(const std::function<T()>& compute) {
            detail::runEffect([=, state = state]() mutable {
                state.set(compute());
                return nullptr;
            });
        }

        auto operator()() const -> T {
            return state();
        }

    private:
        State<T> state;
    };
}

#endif
