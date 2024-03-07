#ifndef LIQUID_PRIMITIVES_HPP
#define LIQUID_PRIMITIVES_HPP

#include <unordered_map>

#define SIGNAL(value) Liquid::Signal<decltype(value)>(value)
#define COMPUTED(expression) [=]() mutable { return expression; }

#define EFFECT(codeblock)            \
    auto function = [&]() codeblock; \
    Liquid::currentDep = function;   \
    function();                      \
    Liquid::currentDep = nullptr;    \
    Liquid::currentDepId += 1

namespace Liquid
{
    std::function<void()> currentDep = nullptr;
    int currentDepId = 0;
    bool hasChanged = true;

    template <typename T>
    class Signal
    {
    public:
        Signal(const T &value) : value(std::make_shared<T>(value)) {}

        T operator()()
        {
            if (currentDep && deps.find(currentDepId) == deps.end())
            {
                deps[currentDepId] = currentDep;
            }

            return *value;
        }

        void set(const T &newValue)
        {
            *value = newValue;
            hasChanged = true;

            for (auto dep : deps)
            {
                dep.second();
            }
        }

    private:
        std::shared_ptr<T> value;
        std::unordered_map<int, std::function<void()>> deps;
    };
}

#endif