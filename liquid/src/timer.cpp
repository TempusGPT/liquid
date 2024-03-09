#include "include/timer.hpp"

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

int Timer::newId = 1;
std::unordered_set<int> timerIdSet;
std::priority_queue<Timer, std::vector<Timer>, Timer::Comparator> timerQueue;

namespace Liquid {
    void processTimer() {
        const auto now = std::chrono::steady_clock::now();
        if (timerQueue.empty() || timerQueue.top().invokeAt > now) {
            return;
        }

        auto timer = timerQueue.top();
        timerQueue.pop();
        if (timerIdSet.count(timer.id) == 0) {
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
    const auto timer = Timer(TimerType::Timeout, delay, callback);
    timerQueue.push(timer);
    timerIdSet.insert(timer.id);
    return timer.id;
}

int setInterval(const int delay, const std::function<void()> &callback) {
    const auto timer = Timer(TimerType::Interval, delay, callback);
    timerQueue.push(timer);
    timerIdSet.insert(timer.id);
    return timer.id;
}

void clearTimer(const int id) {
    timerIdSet.erase(id);
}
