#ifndef LIQUID_TIMER_HPP
#define LIQUID_TIMER_HPP

#include <chrono>
#include <functional>
#include <queue>
#include <unordered_set>
#include <vector>

#undef timeout

namespace Liquid {
    enum class TimerType {
        Timeout,
        Interval
    };

    class Timer {
    public:
        int id;
        TimerType type;
        std::function<void()> callback;
        std::chrono::milliseconds delay;
        std::chrono::steady_clock::time_point invokeAt;

        Timer(const TimerType type, const int delay, const std::function<void()> &callback)
            : id(newId++), type(type), callback(callback) {
            const auto now = std::chrono::steady_clock::now();
            const auto chronoDelay = std::chrono::milliseconds(delay);
            this->delay = chronoDelay;
            this->invokeAt = now + chronoDelay;
        }

        struct Comparator {
            bool operator()(const Timer &lhs, const Timer &rhs) const {
                return lhs.invokeAt > rhs.invokeAt;
            }
        };

    private:
        static int newId;
    };

    int Timer::newId = 0;
    std::unordered_set<int> timerIds;
    std::priority_queue<Timer, std::vector<Timer>, Timer::Comparator> timerQueue;

    void processTimer() {
        const auto now = std::chrono::steady_clock::now();
        if (timerQueue.empty() || timerQueue.top().invokeAt > now) {
            return;
        }

        auto timer = timerQueue.top();
        timerQueue.pop();
        if (timerIds.count(timer.id) == 0) {
            return;
        }

        timer.callback();
        if (timer.type == TimerType::Interval) {
            timer.invokeAt += timer.delay;
            timerQueue.push(timer);
        }
    }
}

int setTimeout(const int delay, const std::function<void()> &callback) {
    const auto timer = Liquid::Timer(Liquid::TimerType::Timeout, delay, callback);
    Liquid::timerQueue.push(timer);
    Liquid::timerIds.insert(timer.id);
    return timer.id;
}

int setInterval(const int delay, const std::function<void()> &callback) {
    const auto timer = Liquid::Timer(Liquid::TimerType::Interval, delay, callback);
    Liquid::timerQueue.push(timer);
    Liquid::timerIds.insert(timer.id);
    return timer.id;
}

void clearTimer(const int id) {
    Liquid::timerIds.erase(id);
}

#endif
