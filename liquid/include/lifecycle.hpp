#ifndef LIQUID_LIFECYCLE_HPP
#define LIQUID_LIFECYCLE_HPP

#include <functional>
#include <vector>

namespace Liquid {
    class Lifecycle;
    auto useLifecycle() -> Lifecycle;

    class Lifecycle {
    public:
        ~Lifecycle();
        auto mount(const std::function<void()>& callback) -> void;
        auto cleanup(const std::function<void()>& callback) -> void;

    private:
        std::vector<std::function<void()>> mountCallbacks;
        std::vector<std::function<void()>> cleanupCallbacks;
    };
}

#endif
