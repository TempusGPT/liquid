#include "include/lifecycle.hpp"
#include "include/component.hpp"

Lifecycle useLifecycle() {
    return Lifecycle();
}

Lifecycle::~Lifecycle() {
    // Element::setLastOnMount(mount);
    // Element::setLastOnCleanup(cleanup);
}

Lifecycle &Lifecycle::onMount(const std::function<void()> &callback) {
    mount = callback;
    return *this;
}

Lifecycle &Lifecycle::onCleanup(const std::function<void()> &callback) {
    cleanup = callback;
    return *this;
}
