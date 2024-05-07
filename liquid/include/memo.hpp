#ifndef LIQUID_MEMO_HPP
#define LIQUID_MEMO_HPP

#include "effect.hpp"
#include "state.hpp"

namespace liquid {
    template <typename T>
    class Memo {
    public:
        Memo(const std::function<T()>& compute) {
            detail::runEffect([compute, state = state]() mutable {
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
