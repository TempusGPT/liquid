#include "include/timer.hpp"

enum class TimerType {
    Timeout,
    Interval
};

struct Timer {
    struct Comparator {
        bool operator()(const Timer &lhs, const Timer &rhs) const {
            return lhs.invokeAt > rhs.invokeAt;
        }
    };

    static std::unordered_set<int> idSet;
    static std::priority_queue<Timer, std::vector<Timer>, Timer::Comparator> queue;
    static int newId;

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
};

std::unordered_set<int> Timer::idSet = {};
std::priority_queue<Timer, std::vector<Timer>, Timer::Comparator> Timer::queue = {};
int Timer::newId = 1;

namespace Liquid {
    void processTimer() {
        const auto now = std::chrono::steady_clock::now();
        if (Timer::queue.empty() || Timer::queue.top().invokeAt > now) {
            return;
        }

        auto timer = Timer::queue.top();
        Timer::queue.pop();
        if (Timer::idSet.count(timer.id) == 0) {
            return;
        }

        timer.callback();
        if (timer.type == TimerType::Interval) {
            timer.invokeAt += timer.delay;
            Timer::queue.push(timer);
        }
    }
}

int setTimeout(const int delay, const std::function<void()> &callback) {
    const auto timer = Timer(TimerType::Timeout, delay, callback);
    Timer::queue.push(timer);
    Timer::idSet.insert(timer.id);
    return timer.id;
}

int setInterval(const int delay, const std::function<void()> &callback) {
    const auto timer = Timer(TimerType::Interval, delay, callback);
    Timer::queue.push(timer);
    Timer::idSet.insert(timer.id);
    return timer.id;
}

void clearTimer(const int id) {
    Timer::idSet.erase(id);
}
