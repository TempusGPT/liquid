#ifndef LIQUID_TIMER_HPP
#define LIQUID_TIMER_HPP

#include <chrono>
#include <functional>
#include <queue>
#include <unordered_set>

namespace Liquid {
    void processTimer();
}

int setTimeout(const int delay, const std::function<void()> &callback);
int setInterval(const int delay, const std::function<void()> &callback);
void clearTimer(const int id);

#endif