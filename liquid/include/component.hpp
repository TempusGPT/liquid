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
        Element(const std::function<void(int, int)> &renderCallback = nullptr);

        void render(int x, int y) const;
        void cleanup() const;

    private:
        static Element *lastMounted;
        std::function<void(int, int)> renderCallback;
        std::vector<std::function<void()>> cleanupCallbacks;
    };

    template <typename T>
    class Prop {
    public:
        Prop(const std::function<T()> &getter) : getter(getter) {}
        Prop(const T &value) : getter([=]() { return value; }) {}

        Prop(const char *value) {
            const auto str = std::string(value);
            getter = [=]() { return str; };
        }

        template <typename U>
        Prop(const std::initializer_list<U> &value) {
            const auto vec = std::vector<U>(value);
            getter = [=]() { return vec; };
        }

        T operator()() const {
            return getter();
        }

    private:
        std::function<T()> getter;
    };

    template <typename... Props>
    using Component = std::function<Element(Props...)>;

    Element Goto(const Prop<int> &x, const Prop<int> &y);

    Element Group(const Prop<std::vector<Element>> &elements);

    Element Text(
        const Prop<std::string> &value,
        const Prop<Color> &foreground = Color::White,
        const Prop<Color> &background = Color::Black
    );
}

#endif
