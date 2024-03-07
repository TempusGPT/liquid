#ifndef LIQUID_ELEMENTS_HPP
#define LIQUID_ELEMENTS_HPP

#include <initializer_list>
#include <functional>
#include <string>
#include <ncurses.h>

#define FRAGMENT(elements...) [=]() mutable { Liquid::execute(elements); }

using Element = std::function<void()>;

Element text(const std::string &value)
{
    return [&]()
    {
        printw("%s", value.c_str());
    };
}

namespace Liquid
{
    void execute(const std::initializer_list<std::function<void()>> &fns)
    {
        for (const auto &fn : fns)
        {
            if (fn)
            {
                fn();
            }
        }
    }
}

#endif
