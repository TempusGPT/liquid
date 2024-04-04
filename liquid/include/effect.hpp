#ifndef LIQUID_EFFECT_HPP
#define LIQUID_EFFECT_HPP

#include <functional>

namespace Liquid {
    namespace Internal {
        inline auto effectId = 0;
        inline auto effectCallback = std::function<void()>();
        auto runEffect(int id, const std::function<void()>& callback) -> void;
    }

    class Effect {
    public:
        ~Effect();
        auto create(const std::function<void()>& callback) -> void;
        auto cleanup(const std::function<void()>& callback) -> void;

    private:
        std::vector<std::function<void()>> callbacks;
        std::vector<std::function<void()>> cleanupCallbacks;
    };
}

#endif
