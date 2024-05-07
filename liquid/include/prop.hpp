#ifndef LIQUID_PROP_HPP
#define LIQUID_PROP_HPP

#include "memo.hpp"

#include <functional>
#include <initializer_list>
#include <type_traits>

namespace liquid {
    namespace detail {
        template <typename T, typename... Args>
        struct is_initializable {
            template <typename... U>
            static auto test(U&&... u) -> decltype(T { std::forward<U>(u)... }, std::true_type());
            static auto test(...) -> std::false_type;

            static constexpr auto value = decltype(test(std::declval<Args>()...))::value;
        };

        template <typename T, typename... Args>
        constexpr auto is_initializable_v = is_initializable<T, Args...>::value;
    }

    template <typename T>
    class Prop {
    public:
        template <typename Fn, std::enable_if_t<std::is_invocable_r_v<T, Fn>, int> = 0>
        Prop(Fn&& fn) : memo(fn) {}

        template <
            typename... Args,
            std::enable_if_t<detail::is_initializable_v<T, Args...>, int> = 0>
        Prop(Args&&... args)
            : memo([value = T { std::forward<Args>(args)... }]() { return value; }) {}

        auto operator*() const -> const T& {
            return *memo;
        }

        auto operator->() const -> const T* {
            return memo.operator->();
        }

    private:
        const Memo<T> memo;
    };
}

#endif
