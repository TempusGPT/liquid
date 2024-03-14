#ifndef LIQUID_COMPONENT_HPP
#define LIQUID_COMPONENT_HPP

#include "color.hpp"

#include <functional>
#include <string>
#include <vector>

namespace Liquid {
    class Element {
    public:
        Element(
            const std::function<void()> &onRender = nullptr,
            const std::function<void()> &onMount = nullptr,
            const std::function<void()> &onCleanup = nullptr
        );

        void render() const;
        void mount() const;
        void cleanup() const;

    private:
        std::function<void()> onRender;
        std::function<void()> onMount;
        std::function<void()> onCleanup;
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

    Element Div(const std::vector<Element> &elements);

    Element Text(
        const Prop<std::string> &value,
        const Prop<Color> &foreground = Color::White,
        const Prop<Color> &background = Color::Black
    );
}

#endif
