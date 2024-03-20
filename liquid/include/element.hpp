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

    template <typename T>
    class Prop {
    public:
        Prop(T &&value) {
            getter = [=]() { return value; };
        }

        template <typename Fn>
        Prop(
            Fn &&fn,
            typename std::enable_if<std::is_convertible<
                typename std::result_of<Fn()>::type,
                T>::value>::type * = nullptr
        ) {
            getter = fn;
        }

        template <typename Arg>
        Prop(
            Arg &&arg,
            typename std::enable_if<std::is_convertible<Arg, T>::value>::type * = nullptr
        ) {
            const auto value = T(std::forward<Arg>(arg));
            getter = [=]() { return value; };
        }

        template <typename Arg>
        Prop(
            std::initializer_list<Arg> &&list,
            typename std::enable_if<
                std::is_convertible<std::initializer_list<Arg>, T>::value>::type * = nullptr
        ) {
            const auto value = T(std::forward<std::initializer_list<Arg>>(list));
            getter = [=]() { return value; };
        }

        T operator()() const {
            return getter();
        }

    private:
        std::function<T()> getter;
    };
}

#endif
