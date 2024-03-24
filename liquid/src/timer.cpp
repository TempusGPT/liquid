#include "include/timer.hpp"

#include <chrono>
#include <set>

namespace Liquid {
    struct Timer;
    static auto timerSet = std::set<Timer>();
    static auto timerId = 0;

    struct Timer {
        int id;
        bool willRepeat;
        std::function<void()> callback;
        std::chrono::milliseconds delay;
        std::chrono::steady_clock::time_point invokeAt;

        Timer(bool willRepeat, int delay, const std::function<void()> &callback)
            : id(timerId++), willRepeat(willRepeat), callback(callback) {
            const auto now = std::chrono::steady_clock::now();
            const auto chronoDelay = std::chrono::milliseconds(delay);
            this->delay = chronoDelay;
            this->invokeAt = now + chronoDelay;
        }

        bool operator<(const Timer &other) const {
            return invokeAt == other.invokeAt ? id < other.id : invokeAt < other.invokeAt;
        }
    };

    int setTimeout(int delay, const std::function<void()> &callback) {
        const auto timer = Timer(false, delay, callback);
        timerSet.insert(timer);
        return timer.id;
    }

    int setInterval(int delay, const std::function<void()> &callback) {
        const auto timer = Timer(true, delay, callback);
        timerSet.insert(timer);
        return timer.id;
    }

    void clearTimer(int id) {
        for (auto it = timerSet.begin(); it != timerSet.end();) {
            if (it->id == id) {
                it = timerSet.erase(it);
            } else {
                ++it;
            }
        }
    }

    namespace Internal {
        void processTimer() {
            const auto now = std::chrono::steady_clock::now();
            while (!timerSet.empty() && timerSet.begin()->invokeAt <= now) {
                auto timer = *timerSet.begin();
                timerSet.erase(timer);
                timer.callback();

                if (timer.willRepeat) {
                    timer.invokeAt += timer.delay;
                    timerSet.insert(timer);
                }
            }
        }
    }
}
