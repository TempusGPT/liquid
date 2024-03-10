#ifndef LIQUID_COMPONENT_HPP
#define LIQUID_COMPONENT_HPP

#include "color.hpp"

#include <functional>
#include <string>
#include <vector>

#define FN(expression)                     \
    {                                        \
        [=]() mutable { return expression; } \
    }

class Element {
public:
    Element();
    Element(const std::function<void()> &renderer);
    void render() const;

private:
    std::function<void()> renderer;
};

template <typename T>
class Prop {
public:
    Prop(const std::function<T()> &getter) : getter(getter) {}
    Prop(const T &value) : getter([=]() { return value; }) {}
    Prop(const char *value) : getter([=]() { return std::string(value); }) {}

    T operator()() const {
        return getter();
    }

private:
    const std::function<T()> getter;
};

template <typename... Props>
using Component = std::function<Element(Props...)>;
using Page = Component<>;

Element Div(const std::vector<Element> &elements);

Element Text(
    const Prop<std::string> &value,
    const Prop<Color> &foreground = Color::White,
    const Prop<Color> &background = Color::Black
);

namespace Liquid {
    template <typename T>
    Prop<T> createProp(const T &value) {
        return Prop<T>(value);
    }
}

#endif
