#ifndef LIQUID_COMPONENT_HPP
#define LIQUID_COMPONENT_HPP

#include "color.hpp"

#include <functional>
#include <string>
#include <vector>

namespace Liquid {
    namespace Internal {
        void onCleanup(const std::function<void()> &callback);
    }

    class Element {
        friend void Internal::onCleanup(const std::function<void()> &callback);

    public:
        Element(const std::function<void()> &renderCallback = nullptr);

        void render() const;
        void cleanup() const;

    private:
        static Element *lastMounted;
        std::function<void()> renderCallback;
        std::vector<std::function<void()>> cleanupCallbacks;
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
