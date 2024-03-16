#ifndef LIQUID_ELEMENT_HPP
#define LIQUID_ELEMENT_HPP

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

    // TODO: Enhance props
    template <typename T>
    class Prop {
    public:
        Prop(const std::function<T()> &getter) : getter(getter) {}
        Prop(const T &value) : getter([=]() { return value; }) {}

        Prop(const char *value) {
            const auto str = std::string(value);
            getter = [=]() { return str; };
        }

        T operator()() const {
            return getter();
        }

    private:
        std::function<T()> getter;
    };

    template <typename T>
    class Prop<std::vector<T>> {
    public:
        Prop(const std::function<std::vector<T>()> &getter) : getter(getter) {}

        Prop(const std::initializer_list<T> &value) {
            const auto vec = std::vector<T>(value);
            getter = [=]() { return vec; };
        }

        std::vector<T> operator()() const {
            return getter();
        }

    private:
        std::function<std::vector<T>()> getter;
    };

    template <typename T, typename... Args>
    class Prop<std::function<T(Args...)>> {
    public:
        Prop(const std::function<std::function<T(Args...)>> &getter) : getter(getter) {}
        Prop(const std::function<T(Args...)> &value) : getter([=]() { return value; }) {}
        Prop(T (*value)(Args...)) : getter([=]() { return value; }) {}

        std::function<T(Args...)> operator()() const {
            return getter();
        }

    private:
        std::function<std::function<T(Args...)>()> getter;
    };
}

#endif
