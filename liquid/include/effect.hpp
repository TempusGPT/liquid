#ifndef LIQUID_EFFECT_HPP
#define LIQUID_EFFECT_HPP

#include <functional>

namespace liquid {
    namespace detail {
        inline auto effectId = 0;
        inline auto effectCallback = std::function<std::function<void()>()>();
        auto runEffect(int id, const std::function<std::function<void()>()>& callback) -> std::function<void()>;
    }

    class Effect {
    public:
        ~Effect();

        template <typename Fn, std::enable_if_t<std::is_same_v<void, std::invoke_result_t<Fn>>, int> = 0>
        auto operator()(Fn&& callback) -> void {
            callbacks.push_back([=]() mutable {
                callback();
                return nullptr;
            });
        }

        template <typename Fn, std::enable_if_t<std::is_invocable_v<std::invoke_result_t<Fn>>, int> = 0>
        auto operator()(Fn&& callback) -> void {
            callbacks.push_back(callback);
        }

    private:
        std::vector<std::function<std::function<void()>()>> callbacks;
    };
}

#endif
