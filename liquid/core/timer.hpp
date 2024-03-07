#ifndef LIQUID_TIMER_HPP
#define LIQUID_TIMER_HPP

#include <chrono>
#include <functional>
#include <queue>
#include <unordered_set>
#include <vector>

#undef timeout

namespace Liquid
{
    struct Timer
    {
    public:
        int id;
        bool isInterval;
        std::function<void()> callback;
        std::chrono::milliseconds delay;
        std::chrono::steady_clock::time_point invokeAt;

        static Timer timeout(const int delay, const std::function<void()> &callback)
        {
            const auto id = newID++;
            const auto chronoDelay = std::chrono::milliseconds(delay);

            return Timer{
                .id = id,
                .isInterval = false,
                .callback = callback,
                .delay = chronoDelay,
                .invokeAt = std::chrono::steady_clock::now() + chronoDelay,
            };
        }

        static Timer interval(const int delay, const std::function<void()> &callback)
        {
            const auto id = newID++;
            const auto chronoDelay = std::chrono::milliseconds(delay);

            return Timer{
                .id = id,
                .isInterval = true,
                .callback = callback,
                .delay = chronoDelay,
                .invokeAt = std::chrono::steady_clock::now() + chronoDelay,
            };
        }

        struct Comparator
        {
            bool operator()(const Timer &lhs, const Timer &rhs) const
            {
                return lhs.invokeAt > rhs.invokeAt;
            }
        };

    private:
        static int newID;
    };

    int Timer::newID = 0;
    std::priority_queue<Timer, std::vector<Timer>, Timer::Comparator> timerQueue;
    std::unordered_set<int> timerIds;

    void processTimer()
    {
        const auto &now = std::chrono::steady_clock::now();
        if (timerQueue.empty() || timerQueue.top().invokeAt > now)
        {
            return;
        }

        auto timer = timerQueue.top();
        timerQueue.pop();
        if (timerIds.count(timer.id) == 0)
        {
            return;
        }

        timer.callback();
        if (timer.isInterval)
        {
            timer.invokeAt += timer.delay;
            timerQueue.push(timer);
        }
    }
}

int setTimeout(const int delay, const std::function<void()> &callback)
{
    const auto &timer = Liquid::Timer::timeout(delay, callback);
    Liquid::timerQueue.push(timer);
    Liquid::timerIds.insert(timer.id);
    return timer.id;
}

int setInterval(const int delay, const std::function<void()> &callback)
{
    const auto &timer = Liquid::Timer::interval(delay, callback);
    Liquid::timerQueue.push(timer);
    Liquid::timerIds.insert(timer.id);
    return timer.id;
}

void clearTimer(const int id)
{
    Liquid::timerIds.erase(id);
}

#endif
