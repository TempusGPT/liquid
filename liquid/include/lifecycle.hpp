#ifndef LIQUID_LIFECYCLE_HPP
#define LIQUID_LIFECYCLE_HPP

#include <functional>

class Lifecycle;

Lifecycle useLifecycle();

class Lifecycle {
    friend Lifecycle useLifecycle();

public:
    ~Lifecycle();

    Lifecycle &onMount(const std::function<void()> &callback);
    Lifecycle &onCleanup(const std::function<void()> &callback);

private:
    std::function<void()> mount;
    std::function<void()> cleanup;
};

#endif
