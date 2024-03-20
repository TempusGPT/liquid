#ifndef LIQUID_TIMER_HPP
#define LIQUID_TIMER_HPP

#include <chrono>
#include <functional>
#include <queue>
#include <unordered_set>

namespace Liquid {
    int setTimeout(int delay, const std::function<void()> &callback);
    int setInterval(int delay, const std::function<void()> &callback);
    void clearTimer(int id);

    namespace Internal {
        void processTimer();
    }
}

#endif
