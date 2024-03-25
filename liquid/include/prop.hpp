// TODO: Migrate to C++17

#ifndef LIQUID_PROP_HPP
#define LIQUID_PROP_HPP

#include <functional>
#include <initializer_list>
#include <type_traits>

template <typename T>
class Prop {
public:
    Prop(T&& value) {
        getter = [=]() { return value; };
    }

    template <typename Fn>
    Prop(
        Fn&& fn,
        typename std::enable_if<std::is_convertible<
            typename std::result_of<Fn()>::type,
            T>::value>::type* = nullptr
    ) {
        getter = fn;
    }

    template <typename Arg>
    Prop(
        Arg&& arg,
        typename std::enable_if<std::is_convertible<Arg, T>::value>::type* = nullptr
    ) {
        const auto value = T(std::forward<Arg>(arg));
        getter = [=]() { return value; };
    }

    template <typename Arg>
    Prop(
        std::initializer_list<Arg>&& list,
        typename std::enable_if<
            std::is_convertible<std::initializer_list<Arg>, T>::value>::type* = nullptr
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

#endif
