#ifndef LIQUID_ELEMENT_HPP
#define LIQUID_ELEMENT_HPP

#include <functional>
#include <ncurses.h>
#include <string>
#include <vector>

class Element {
public:
    Element() : callback([]() {}) {}
    Element(const std::function<void()> &callback) : callback(callback) {}

    void operator()() const {
        callback();
    }

private:
    std::function<void()> callback;
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

Element fragment(const std::vector<Element> &elements) {
    return {
        [=]() {
            for (auto &element : elements) {
                element();
            }
        }
    };
}

Element text(const Prop<std::string> &value) {
    return {
        [=]() {
            printw("%s", value().c_str());
        }
    };
}

#endif
