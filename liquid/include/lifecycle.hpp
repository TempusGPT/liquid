#ifndef LIQUID_LIFECYCLE_HPP
#define LIQUID_LIFECYCLE_HPP

#include <functional>
#include <vector>

namespace Liquid {
    class Lifecycle;
    Lifecycle useLifecycle();

    class Lifecycle {
        friend Lifecycle useLifecycle();

    public:
        ~Lifecycle();
        void mount(const std::function<void()> &callback);
        void cleanup(const std::function<void()> &callback);

    private:
        std::vector<std::function<void()>> mountCallbacks;
        std::vector<std::function<void()>> cleanupCallbacks;
    };
}

#endif
