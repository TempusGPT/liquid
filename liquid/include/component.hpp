#ifndef LIQUID_COMPONENT_HPP
#define LIQUID_COMPONENT_HPP

#include <functional>
#include <string>
#include <vector>

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

template <typename... Args>
using Component = std::function<Element(Args...)>;
using Page = Component<>;

Element fragment(const std::vector<Element> &elements);
Element text(const Prop<std::string> &value);

#endif
