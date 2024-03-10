#include "include/reactivity.hpp"

#include <string>

namespace Liquid {
    int Effect::newId = 0;
    Effect Effect::current = {};

    Effect::Effect() : id(-1), callback(nullptr) {}
    Effect::Effect(const std::function<void()> &callback) : id(newId++), callback(callback) {}

    Effect &Effect::getCurrent() {
        return current;
    }

    void Effect::run() {
        if (callback) {
            current = *this;
            callback();
            current = {};
        }
    }

    bool Effect::operator==(const Effect &other) const {
        return id == other.id;
    }

    Effect::operator bool() const {
        return id >= 0;
    }
}

namespace std {
    size_t hash<Liquid::Effect>::operator()(const Liquid::Effect &effect) const {
        return hash<int>()(effect.id);
    }
}

Signal<std::string> createSignal(const char *value) {
    return Signal<std::string>(value);
}

void createEffect(const std::function<void()> &callback) {
    Liquid::Effect(callback).run();
}
