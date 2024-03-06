#ifndef LIQUID_COMPONENT_HPP
#define LIQUID_COMPONENT_HPP

#include <initializer_list>
#include <functional>
#include <string>

#define fragment(elements...) [=]() mutable { Liquid::execute(elements); }

using Element = std::function<void()>;

Element text(const std::string &value)
{
    return [&]()
    {
        printf("%s", value.c_str());
    };
}

namespace Liquid
{
    void execute(const std::initializer_list<std::function<void()>> &fns)
    {
        for (const auto &fn : fns)
        {
            fn();
        }
    }
}

#endif
