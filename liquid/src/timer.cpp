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

        auto operator<(const Timer& other) const -> bool {
            return invokeAt == other.invokeAt ? id < other.id : invokeAt < other.invokeAt;
        }
    };

    auto newTimer(bool willRepeat, int delay, const std::function<void()>& callback) -> Timer {
        auto now = std::chrono::steady_clock::now();
        auto chronoDelay = std::chrono::milliseconds(delay);
        return { timerId++, willRepeat, callback, chronoDelay, now + chronoDelay };
    }

    auto setTimeout(int delay, const std::function<void()>& callback) -> int {
        auto timer = newTimer(false, delay, callback);
        timerSet.insert(timer);
        return timer.id;
    }

    auto setInterval(int delay, const std::function<void()>& callback) -> int {
        auto timer = newTimer(true, delay, callback);
        timerSet.insert(timer);
        return timer.id;
    }

    auto clearTimer(int id) -> void {
        for (auto it = timerSet.begin(); it != timerSet.end();) {
            if (it->id == id) {
                it = timerSet.erase(it);
            } else {
                ++it;
            }
        }
    }

    namespace Internal {
        auto processTimer() -> void {
            auto now = std::chrono::steady_clock::now();
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
