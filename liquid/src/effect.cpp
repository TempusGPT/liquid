#include "include/effect.hpp"
#include "include/element.hpp"

namespace liquid {
    static auto newId = 0;

    namespace detail {
        auto runEffect(
            const std::function<std::function<void()>()>& callback
        ) -> std::function<void()> {
            return runEffect(newId++, callback);
        }

        auto runEffect(
            int id,
            const std::function<std::function<void()>()>& callback
        ) -> std::function<void()> {
            effectId = id;
            effectCallback = callback;
            auto cleanup = callback();
            effectCallback = nullptr;
            return cleanup;
        }
    }

    Effect::~Effect() {
        for (const auto& callback : callbacks) {
            auto cleanup = detail::runEffect(callback);
            if (cleanup) {
                Element::onCleanup(cleanup);
            }
        }
    }
}
