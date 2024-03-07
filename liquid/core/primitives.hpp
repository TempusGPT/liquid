#ifndef LIQUID_PRIMITIVES_HPP
#define LIQUID_PRIMITIVES_HPP

#include <unordered_map>

#define signal(value) Liquid::Signal<decltype(value)>(value)
#define memo(expression) [=]() mutable { return expression; }

#define effect(codeblock)                 \
    auto function = [&]() codeblock;      \
    Liquid::currentDependency = function; \
    function();                           \
    Liquid::currentDependency = nullptr;  \
    Liquid::currentDependencyId += 1

namespace Liquid
{
    std::function<void()> currentDependency = nullptr;
    int currentDependencyId = 0;

    template <typename T>
    class Signal
    {
    public:
        Signal(const T &value) : value(std::make_shared<T>(value)) {}

        T operator()()
        {
            if (currentDependency && dependencies.find(currentDependencyId) == dependencies.end())
            {
                dependencies[currentDependencyId] = currentDependency;
            }

            return *value;
        }

        void set(const T &newValue)
        {
            *value = newValue;
            for (auto function : dependencies)
            {
                function.second();
            }
        }

    private:
        std::shared_ptr<T> value;
        std::unordered_map<int, std::function<void()>> dependencies;
    };
}

#endif